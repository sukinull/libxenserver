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


#ifndef XEN_PBD_H
#define XEN_PBD_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_pbd_decl.h>
#include <xen/api/xen_pbd_xen_pbd_record_map.h>
#include <xen/api/xen_sr_decl.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The PBD class.
 * 
 * The physical block devices through which hosts access SRs.
 */


/**
 * Free the given xen_pbd.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_pbd_free(xen_pbd pbd);


typedef struct xen_pbd_set
{
    size_t size;
    xen_pbd *contents[];
} xen_pbd_set;

/**
 * Allocate a xen_pbd_set of the given size.
 */
extern xen_pbd_set *
xen_pbd_set_alloc(size_t size);

/**
 * Free the given xen_pbd_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_pbd_set_free(xen_pbd_set *set);


typedef struct xen_pbd_record
{
    xen_pbd handle;
    char *uuid;
    struct xen_host_record_opt *host;
    struct xen_sr_record_opt *sr;
    xen_string_string_map *device_config;
    bool currently_attached;
    xen_string_string_map *other_config;
} xen_pbd_record;

/**
 * Allocate a xen_pbd_record.
 */
extern xen_pbd_record *
xen_pbd_record_alloc(void);

/**
 * Free the given xen_pbd_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_pbd_record_free(xen_pbd_record *record);


typedef struct xen_pbd_record_opt
{
    bool is_record;
    union
    {
        xen_pbd handle;
        xen_pbd_record *record;
    } u;
} xen_pbd_record_opt;

/**
 * Allocate a xen_pbd_record_opt.
 */
extern xen_pbd_record_opt *
xen_pbd_record_opt_alloc(void);

/**
 * Free the given xen_pbd_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_pbd_record_opt_free(xen_pbd_record_opt *record_opt);


typedef struct xen_pbd_record_set
{
    size_t size;
    xen_pbd_record *contents[];
} xen_pbd_record_set;

/**
 * Allocate a xen_pbd_record_set of the given size.
 */
extern xen_pbd_record_set *
xen_pbd_record_set_alloc(size_t size);

/**
 * Free the given xen_pbd_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_pbd_record_set_free(xen_pbd_record_set *set);



typedef struct xen_pbd_record_opt_set
{
    size_t size;
    xen_pbd_record_opt *contents[];
} xen_pbd_record_opt_set;

/**
 * Allocate a xen_pbd_record_opt_set of the given size.
 */
extern xen_pbd_record_opt_set *
xen_pbd_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_pbd_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_pbd_record_opt_set_free(xen_pbd_record_opt_set *set);


/**
 * Get a record containing the current state of the given PBD.
 */
extern bool
xen_pbd_get_record(xen_session *session, xen_pbd_record **result, xen_pbd pbd);


/**
 * Get a reference to the PBD instance with the specified UUID.
 */
extern bool
xen_pbd_get_by_uuid(xen_session *session, xen_pbd *result, char *uuid);


/**
 * Create a new PBD instance, and return its handle.
 */
extern bool
xen_pbd_create(xen_session *session, xen_pbd *result, xen_pbd_record *record);

/**
 * Create a new PBD instance, and return its handle.
 */
extern bool
xen_pbd_create_async(xen_session *session, xen_task *result, xen_pbd_record *record);


/**
 * Destroy the specified PBD instance.
 */
extern bool
xen_pbd_destroy(xen_session *session, xen_pbd pbd);

/**
 * Destroy the specified PBD instance.
 */
extern bool
xen_pbd_destroy_async(xen_session *session, xen_task *result, xen_pbd pbd);


/**
 * Get the uuid field of the given PBD.
 */
extern bool
xen_pbd_get_uuid(xen_session *session, char **result, xen_pbd pbd);


/**
 * Get the host field of the given PBD.
 */
extern bool
xen_pbd_get_host(xen_session *session, xen_host *result, xen_pbd pbd);


/**
 * Get the SR field of the given PBD.
 */
extern bool
xen_pbd_get_sr(xen_session *session, xen_sr *result, xen_pbd pbd);


/**
 * Get the device_config field of the given PBD.
 */
extern bool
xen_pbd_get_device_config(xen_session *session, xen_string_string_map **result, xen_pbd pbd);


/**
 * Get the currently_attached field of the given PBD.
 */
extern bool
xen_pbd_get_currently_attached(xen_session *session, bool *result, xen_pbd pbd);


/**
 * Get the other_config field of the given PBD.
 */
extern bool
xen_pbd_get_other_config(xen_session *session, xen_string_string_map **result, xen_pbd pbd);


/**
 * Set the other_config field of the given PBD.
 */
extern bool
xen_pbd_set_other_config(xen_session *session, xen_pbd pbd, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * PBD.
 */
extern bool
xen_pbd_add_to_other_config(xen_session *session, xen_pbd pbd, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given PBD.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_pbd_remove_from_other_config(xen_session *session, xen_pbd pbd, char *key);


/**
 * Activate the specified PBD, causing the referenced SR to be attached
 * and scanned.
 */
extern bool
xen_pbd_plug(xen_session *session, xen_pbd self);

/**
 * Activate the specified PBD, causing the referenced SR to be attached
 * and scanned.
 */
extern bool
xen_pbd_plug_async(xen_session *session, xen_task *result, xen_pbd self);


/**
 * Deactivate the specified PBD, causing the referenced SR to be
 * detached and nolonger scanned.
 */
extern bool
xen_pbd_unplug(xen_session *session, xen_pbd self);

/**
 * Deactivate the specified PBD, causing the referenced SR to be
 * detached and nolonger scanned.
 */
extern bool
xen_pbd_unplug_async(xen_session *session, xen_task *result, xen_pbd self);


/**
 * Sets the PBD's device_config field.
 */
extern bool
xen_pbd_set_device_config(xen_session *session, xen_pbd self, xen_string_string_map *value);

/**
 * Sets the PBD's device_config field.
 */
extern bool
xen_pbd_set_device_config_async(xen_session *session, xen_task *result, xen_pbd self, xen_string_string_map *value);


/**
 * Return a list of all the PBDs known to the system.
 */
extern bool
xen_pbd_get_all(xen_session *session, struct xen_pbd_set **result);


/**
 * Return a map of PBD references to PBD records for all PBDs known to
 * the system.
 */
extern bool
xen_pbd_get_all_records(xen_session *session, xen_pbd_xen_pbd_record_map **result);


#endif
