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


#ifndef XEN_CRASHDUMP_H
#define XEN_CRASHDUMP_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_crashdump_decl.h>
#include <xen/api/xen_crashdump_xen_crashdump_record_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vdi_decl.h>
#include <xen/api/xen_vm_decl.h>


/*
 * The crashdump class.
 * 
 * A VM crashdump.
 */


/**
 * Free the given xen_crashdump.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_crashdump_free(xen_crashdump crashdump);


typedef struct xen_crashdump_set
{
    size_t size;
    xen_crashdump *contents[];
} xen_crashdump_set;

/**
 * Allocate a xen_crashdump_set of the given size.
 */
extern xen_crashdump_set *
xen_crashdump_set_alloc(size_t size);

/**
 * Free the given xen_crashdump_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_crashdump_set_free(xen_crashdump_set *set);


typedef struct xen_crashdump_record
{
    xen_crashdump handle;
    char *uuid;
    struct xen_vm_record_opt *vm;
    struct xen_vdi_record_opt *vdi;
    xen_string_string_map *other_config;
} xen_crashdump_record;

/**
 * Allocate a xen_crashdump_record.
 */
extern xen_crashdump_record *
xen_crashdump_record_alloc(void);

/**
 * Free the given xen_crashdump_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_crashdump_record_free(xen_crashdump_record *record);


typedef struct xen_crashdump_record_opt
{
    bool is_record;
    union
    {
        xen_crashdump handle;
        xen_crashdump_record *record;
    } u;
} xen_crashdump_record_opt;

/**
 * Allocate a xen_crashdump_record_opt.
 */
extern xen_crashdump_record_opt *
xen_crashdump_record_opt_alloc(void);

/**
 * Free the given xen_crashdump_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_crashdump_record_opt_free(xen_crashdump_record_opt *record_opt);


typedef struct xen_crashdump_record_set
{
    size_t size;
    xen_crashdump_record *contents[];
} xen_crashdump_record_set;

/**
 * Allocate a xen_crashdump_record_set of the given size.
 */
extern xen_crashdump_record_set *
xen_crashdump_record_set_alloc(size_t size);

/**
 * Free the given xen_crashdump_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_crashdump_record_set_free(xen_crashdump_record_set *set);



typedef struct xen_crashdump_record_opt_set
{
    size_t size;
    xen_crashdump_record_opt *contents[];
} xen_crashdump_record_opt_set;

/**
 * Allocate a xen_crashdump_record_opt_set of the given size.
 */
extern xen_crashdump_record_opt_set *
xen_crashdump_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_crashdump_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_crashdump_record_opt_set_free(xen_crashdump_record_opt_set *set);


/**
 * Get a record containing the current state of the given crashdump.
 */
extern bool
xen_crashdump_get_record(xen_session *session, xen_crashdump_record **result, xen_crashdump crashdump);


/**
 * Get a reference to the crashdump instance with the specified UUID.
 */
extern bool
xen_crashdump_get_by_uuid(xen_session *session, xen_crashdump *result, char *uuid);


/**
 * Get the uuid field of the given crashdump.
 */
extern bool
xen_crashdump_get_uuid(xen_session *session, char **result, xen_crashdump crashdump);


/**
 * Get the VM field of the given crashdump.
 */
extern bool
xen_crashdump_get_vm(xen_session *session, xen_vm *result, xen_crashdump crashdump);


/**
 * Get the VDI field of the given crashdump.
 */
extern bool
xen_crashdump_get_vdi(xen_session *session, xen_vdi *result, xen_crashdump crashdump);


/**
 * Get the other_config field of the given crashdump.
 */
extern bool
xen_crashdump_get_other_config(xen_session *session, xen_string_string_map **result, xen_crashdump crashdump);


/**
 * Set the other_config field of the given crashdump.
 */
extern bool
xen_crashdump_set_other_config(xen_session *session, xen_crashdump crashdump, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * crashdump.
 */
extern bool
xen_crashdump_add_to_other_config(xen_session *session, xen_crashdump crashdump, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given crashdump.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_crashdump_remove_from_other_config(xen_session *session, xen_crashdump crashdump, char *key);


/**
 * Destroy the specified crashdump.
 */
extern bool
xen_crashdump_destroy(xen_session *session, xen_crashdump self);

/**
 * Destroy the specified crashdump.
 */
extern bool
xen_crashdump_destroy_async(xen_session *session, xen_task *result, xen_crashdump self);


/**
 * Return a list of all the crashdumps known to the system.
 */
extern bool
xen_crashdump_get_all(xen_session *session, struct xen_crashdump_set **result);


/**
 * Return a map of crashdump references to crashdump records for all
 * crashdumps known to the system.
 */
extern bool
xen_crashdump_get_all_records(xen_session *session, xen_crashdump_xen_crashdump_record_map **result);


#endif
