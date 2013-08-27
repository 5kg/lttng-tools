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

extern "C" {
#include "ust-app.h"
#include "ust-instrument.h"
}

int ust_instrument_probe(struct ust_app* app,
		const char* object_path,
		const char* name,
		enum lttng_ust_instrumentation instrumentation,
		uint64_t addr,
		const char *symbol,
		uint64_t offset)
{
	return 0;
}
