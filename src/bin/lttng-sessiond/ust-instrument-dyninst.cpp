/*
 * Copyright (C) 2013 - Zifei Tong <soariez@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2 only,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <dyninst/BPatch.h>
#include <dyninst/BPatch_object.h>
#include <dyninst/BPatch_function.h>
#include <dyninst/BPatch_point.h>
#include <dyninst/Symtab.h>

extern "C" {
#include "ust-app.h"
#include "ust-instrument.h"
}

namespace {

BPatch_object* findMatchObject(BPatch_image* image, const char* path)
{
	std::vector<BPatch_object*> objects;
	image->getObjects(objects);
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->pathName() == path) {
			return objects[i];
		}
	}
	return NULL;
}

}

int ust_instrument_probe(struct ust_app* app,
		const char* object_path,
		const char* name,
		enum lttng_ust_instrumentation instrumentation,
		uint64_t addr,
		const char *symbol,
		uint64_t offset)
{
	BPatch bpatch;
	BPatch_process *proc = bpatch.processAttach(object_path, app->pid);
	BPatch_image *image = proc->getImage();
	int ret;

	BPatch_object *object = findMatchObject(image, object_path);
	if (object == NULL) {
		ERR("Can not find object %s in process %d", object_path, app->pid);
		proc->detach(true);
		return -1;
	}

	Dyninst::Address address;
	if (symbol[0] != '\0') {
		/* symbol+offset provided */
		Dyninst::SymtabAPI::Symtab *symtab = Dyninst::SymtabAPI::convert(object);
		std::vector<Dyninst::SymtabAPI::Symbol *> symbols;
		ret = symtab->findSymbol(symbols, name,
				Dyninst::SymtabAPI::Symbol::ST_UNKNOWN);

		if (!ret) {
			ERR("Can not find symbol %s in process %d", symbol, app->pid);
			proc->detach(true);
			return -1;
		}
		if (symbols.size() > 1) {
			ERR("Multiple instances of symbol %s founded in process %d", symbol, app->pid);
			proc->detach(true);
			return -1;
		}
		address = object->fileOffsetToAddr(symbols[0]->getOffset() + offset);
	} else {
		/* addr (offset) provided */
		address = object->fileOffsetToAddr(addr);
	}

	std::vector<BPatch_point*> points;
	std::vector<BPatch_function *> functions;
	std::vector<BPatch_point *>* func_points;
	switch (instrumentation) {
	case LTTNG_UST_PROBE:
		image->findPoints(address, points);
	case LTTNG_UST_FUNCTION:
		image->findFunction(address, functions);
		if (functions.size() > 1) {
			ERR("Multiple functions founded in process %d", symbol, app->pid);
			proc->detach(true);
			return -1;
		}

		func_points = functions[0]->findPoint(BPatch_entry);
		points.insert(points.end(), func_points->begin(), func_points->end());
		func_points = functions[0]->findPoint(BPatch_exit);
		points.insert(points.end(), func_points->begin(), func_points->end());
	default:
		ERR("Multiple instances of symbol %s founded in process %d", symbol, app->pid);
		proc->detach(true);
		return -1;
	}

	std::vector<BPatch_function *> probes;
	/* For now, assume there is a function wrap the tracepoint, e.g.
	 * void tptest() { tracepoint(tptest); }
	*/
	image->findFunction(name, probes);
	if (probes.size() == 0) {
		ERR("Can not find probe wrapper %s in process %d", name, app->pid);
		proc->detach(true);
		return -1;
	}
	if (probes.size() > 1) {
		ERR("Multiple instances of probe wrapper %s founded in process %d", name, app->pid);
		proc->detach(true);
		return -1;
	}

	std::vector<BPatch_snippet*> args;
	BPatch_funcCallExpr call_probe(*probes[0], args);

	for (int i = 0; i < points.size(); i++) {
		if (proc->insertSnippet(call_probe, *points[i]) == NULL) {
			ERR("Insert snippet failed in process %d", name, app->pid);
			proc->detach(true);
			return -1;
		}
	}

	proc->detach(true);
	return 0;
}
