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

#ifndef _LTT_UST_INSTRUMENT_H
#define _LTT_UST_INSTRUMENT_H

#include <stdint.h>

#include "trace-ust.h"

#ifdef HAVE_LIBLTTNG_UST_CTL

int lttng_ust_instrument_probe(int sobjd,
		enum lttng_ust_instrumentation instrumentation,
		uint64_t addr,
		const char *symbol,
		uint64_t offset);

#else /* HAVE_LIBLTTNG_UST_CTL */

static inline
int lttng_ust_instrument_probe(int sobjd,
		enum lttng_ust_instrumentation instrumentation,
		uint64_t addr, const char *symbol, uint64_t offset)
{
	return -ENOSYS;
}

#endif /* HAVE_LIBLTTNG_UST_CTL */

#endif /* _LTT_UST_INSTRUEMENT_H */
