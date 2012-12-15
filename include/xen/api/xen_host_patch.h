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


#ifndef XEN_HOST_PATCH_H
#define XEN_HOST_PATCH_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_host_patch_decl.h>
#include <xen/api/xen_host_patch_xen_host_patch_record_map.h>
#include <xen/api/xen_pool_patch_decl.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The host_patch class.
 * 
 * Represents a patch stored on a server.
 */


/**
 * Free the given xen_host_patch.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_host_patch_free(xen_host_patch host_patch);


typedef struct xen_host_patch_set
{
    size_t size;
    xen_host_patch *contents[];
} xen_host_patch_set;

/**
 * Allocate a xen_host_patch_set of the given size.
 */
extern xen_host_patch_set *
xen_host_patch_set_alloc(size_t size);

/**
 * Free the given xen_host_patch_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_host_patch_set_free(xen_host_patch_set *set);


typedef struct xen_host_patch_record
{
    xen_host_patch handle;
    char *uuid;
    char *name_label;
    char *name_description;
    char *version;
    struct xen_host_record_opt *host;
    bool applied;
    time_t timestamp_applied;
    int64_t size;
    struct xen_pool_patch_record_opt *pool_patch;
    xen_string_string_map *other_config;
} xen_host_patch_record;

/**
 * Allocate a xen_host_patch_record.
 */
extern xen_host_patch_record *
xen_host_patch_record_alloc(void);

/**
 * Free the given xen_host_patch_record, and all referenced values. 
 * The given record must have been allocated by this library.
 */
extern void
xen_host_patch_record_free(xen_host_patch_record *record);


typedef struct xen_host_patch_record_opt
{
    bool is_record;
    union
    {
        xen_host_patch handle;
        xen_host_patch_record *record;
    } u;
} xen_host_patch_record_opt;

/**
 * Allocate a xen_host_patch_record_opt.
 */
extern xen_host_patch_record_opt *
xen_host_patch_record_opt_alloc(void);

/**
 * Free the given xen_host_patch_record_opt, and all referenced values.
 *  The given record_opt must have been allocated by this library.
 */
extern void
xen_host_patch_record_opt_free(xen_host_patch_record_opt *record_opt);


typedef struct xen_host_patch_record_set
{
    size_t size;
    xen_host_patch_record *contents[];
} xen_host_patch_record_set;

/**
 * Allocate a xen_host_patch_record_set of the given size.
 */
extern xen_host_patch_record_set *
xen_host_patch_record_set_alloc(size_t size);

/**
 * Free the given xen_host_patch_record_set, and all referenced values.
 *  The given set must have been allocated by this library.
 */
extern void
xen_host_patch_record_set_free(xen_host_patch_record_set *set);



typedef struct xen_host_patch_record_opt_set
{
    size_t size;
    xen_host_patch_record_opt *contents[];
} xen_host_patch_record_opt_set;

/**
 * Allocate a xen_host_patch_record_opt_set of the given size.
 */
extern xen_host_patch_record_opt_set *
xen_host_patch_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_host_patch_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_host_patch_record_opt_set_free(xen_host_patch_record_opt_set *set);


/**
 * Get a record containing the current state of the given host_patch.
 */
extern bool
xen_host_patch_get_record(xen_session *session, xen_host_patch_record **result, xen_host_patch host_patch);


/**
 * Get a reference to the host_patch instance with the specified UUID.
 */
extern bool
xen_host_patch_get_by_uuid(xen_session *session, xen_host_patch *result, char *uuid);


/**
 * Get all the host_patch instances with the given label.
 */
extern bool
xen_host_patch_get_by_name_label(xen_session *session, struct xen_host_patch_set **result, char *label);


/**
 * Get the uuid field of the given host_patch.
 */
extern bool
xen_host_patch_get_uuid(xen_session *session, char **result, xen_host_patch host_patch);


/**
 * Get the name/label field of the given host_patch.
 */
extern bool
xen_host_patch_get_name_label(xen_session *session, char **result, xen_host_patch host_patch);


/**
 * Get the name/description field of the given host_patch.
 */
extern bool
xen_host_patch_get_name_description(xen_session *session, char **result, xen_host_patch host_patch);


/**
 * Get the version field of the given host_patch.
 */
extern bool
xen_host_patch_get_version(xen_session *session, char **result, xen_host_patch host_patch);


/**
 * Get the host field of the given host_patch.
 */
extern bool
xen_host_patch_get_host(xen_session *session, xen_host *result, xen_host_patch host_patch);


/**
 * Get the applied field of the given host_patch.
 */
extern bool
xen_host_patch_get_applied(xen_session *session, bool *result, xen_host_patch host_patch);


/**
 * Get the timestamp_applied field of the given host_patch.
 */
extern bool
xen_host_patch_get_timestamp_applied(xen_session *session, time_t *result, xen_host_patch host_patch);


/**
 * Get the size field of the given host_patch.
 */
extern bool
xen_host_patch_get_size(xen_session *session, int64_t *result, xen_host_patch host_patch);


/**
 * Get the pool_patch field of the given host_patch.
 */
extern bool
xen_host_patch_get_pool_patch(xen_session *session, xen_pool_patch *result, xen_host_patch host_patch);


/**
 * Get the other_config field of the given host_patch.
 */
extern bool
xen_host_patch_get_other_config(xen_session *session, xen_string_string_map **result, xen_host_patch host_patch);


/**
 * Set the other_config field of the given host_patch.
 */
extern bool
xen_host_patch_set_other_config(xen_session *session, xen_host_patch host_patch, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * host_patch.
 */
extern bool
xen_host_patch_add_to_other_config(xen_session *session, xen_host_patch host_patch, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given host_patch.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_host_patch_remove_from_other_config(xen_session *session, xen_host_patch host_patch, char *key);


/**
 * Destroy the specified host patch, removing it from the disk. This
 * does NOT reverse the patch.
 */
extern bool
xen_host_patch_destroy(xen_session *session, xen_host_patch self);

/**
 * Destroy the specified host patch, removing it from the disk. This
 * does NOT reverse the patch.
 */
extern bool
xen_host_patch_destroy_async(xen_session *session, xen_task *result, xen_host_patch self);


/**
 * Apply the selected patch and return its output.
 */
extern bool
xen_host_patch_apply(xen_session *session, char **result, xen_host_patch self);

/**
 * Apply the selected patch and return its output.
 */
extern bool
xen_host_patch_apply_async(xen_session *session, xen_task *result, xen_host_patch self);


/**
 * Return a list of all the host_patchs known to the system.
 */
extern bool
xen_host_patch_get_all(xen_session *session, struct xen_host_patch_set **result);


/**
 * Return a map of host_patch references to host_patch records for all
 * host_patchs known to the system.
 */
extern bool
xen_host_patch_get_all_records(xen_session *session, xen_host_patch_xen_host_patch_record_map **result);


#endif
