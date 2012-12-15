/*
 * Copyright (c) Citrix Systems, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * 
 *   2) Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef XEN_HOST_CRASHDUMP_XEN_HOST_CRASHDUMP_RECORD_MAP_H
#define XEN_HOST_CRASHDUMP_XEN_HOST_CRASHDUMP_RECORD_MAP_H


#include <xen/api/xen_common.h>


typedef struct xen_host_crashdump_xen_host_crashdump_record_map_contents
{
  xen_host_crashdump key;
  struct xen_host_crashdump_record *val;
} xen_host_crashdump_xen_host_crashdump_record_map_contents;


typedef struct xen_host_crashdump_xen_host_crashdump_record_map
{
    size_t size;
    xen_host_crashdump_xen_host_crashdump_record_map_contents contents[];
} xen_host_crashdump_xen_host_crashdump_record_map;

/**
 * Allocate a xen_host_crashdump_xen_host_crashdump_record_map of the
 * given size.
 */
extern xen_host_crashdump_xen_host_crashdump_record_map *
xen_host_crashdump_xen_host_crashdump_record_map_alloc(size_t size);

/**
 * Free the given xen_host_crashdump_xen_host_crashdump_record_map, and
 * all referenced values.  The given map must have been allocated by this
 * library.
 */
extern void
xen_host_crashdump_xen_host_crashdump_record_map_free(xen_host_crashdump_xen_host_crashdump_record_map *map);


#endif
