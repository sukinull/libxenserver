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


#ifndef XEN_POOL_PATCH_H
#define XEN_POOL_PATCH_H

#include <xen/api/xen_after_apply_guidance.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_host_patch_decl.h>
#include <xen/api/xen_pool_patch_decl.h>
#include <xen/api/xen_pool_patch_xen_pool_patch_record_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The pool_patch class.
 * 
 * Pool-wide patches.
 */


/**
 * Free the given xen_pool_patch.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_pool_patch_free(xen_pool_patch pool_patch);


typedef struct xen_pool_patch_set
{
    size_t size;
    xen_pool_patch *contents[];
} xen_pool_patch_set;

/**
 * Allocate a xen_pool_patch_set of the given size.
 */
extern xen_pool_patch_set *
xen_pool_patch_set_alloc(size_t size);

/**
 * Free the given xen_pool_patch_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_pool_patch_set_free(xen_pool_patch_set *set);


typedef struct xen_pool_patch_record
{
    xen_pool_patch handle;
    char *uuid;
    char *name_label;
    char *name_description;
    char *version;
    int64_t size;
    bool pool_applied;
    struct xen_host_patch_record_opt_set *host_patches;
    struct xen_after_apply_guidance_set *after_apply_guidance;
    xen_string_string_map *other_config;
} xen_pool_patch_record;

/**
 * Allocate a xen_pool_patch_record.
 */
extern xen_pool_patch_record *
xen_pool_patch_record_alloc(void);

/**
 * Free the given xen_pool_patch_record, and all referenced values. 
 * The given record must have been allocated by this library.
 */
extern void
xen_pool_patch_record_free(xen_pool_patch_record *record);


typedef struct xen_pool_patch_record_opt
{
    bool is_record;
    union
    {
        xen_pool_patch handle;
        xen_pool_patch_record *record;
    } u;
} xen_pool_patch_record_opt;

/**
 * Allocate a xen_pool_patch_record_opt.
 */
extern xen_pool_patch_record_opt *
xen_pool_patch_record_opt_alloc(void);

/**
 * Free the given xen_pool_patch_record_opt, and all referenced values.
 *  The given record_opt must have been allocated by this library.
 */
extern void
xen_pool_patch_record_opt_free(xen_pool_patch_record_opt *record_opt);


typedef struct xen_pool_patch_record_set
{
    size_t size;
    xen_pool_patch_record *contents[];
} xen_pool_patch_record_set;

/**
 * Allocate a xen_pool_patch_record_set of the given size.
 */
extern xen_pool_patch_record_set *
xen_pool_patch_record_set_alloc(size_t size);

/**
 * Free the given xen_pool_patch_record_set, and all referenced values.
 *  The given set must have been allocated by this library.
 */
extern void
xen_pool_patch_record_set_free(xen_pool_patch_record_set *set);



typedef struct xen_pool_patch_record_opt_set
{
    size_t size;
    xen_pool_patch_record_opt *contents[];
} xen_pool_patch_record_opt_set;

/**
 * Allocate a xen_pool_patch_record_opt_set of the given size.
 */
extern xen_pool_patch_record_opt_set *
xen_pool_patch_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_pool_patch_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_pool_patch_record_opt_set_free(xen_pool_patch_record_opt_set *set);


/**
 * Get a record containing the current state of the given pool_patch.
 */
extern bool
xen_pool_patch_get_record(xen_session *session, xen_pool_patch_record **result, xen_pool_patch pool_patch);


/**
 * Get a reference to the pool_patch instance with the specified UUID.
 */
extern bool
xen_pool_patch_get_by_uuid(xen_session *session, xen_pool_patch *result, char *uuid);


/**
 * Get all the pool_patch instances with the given label.
 */
extern bool
xen_pool_patch_get_by_name_label(xen_session *session, struct xen_pool_patch_set **result, char *label);


/**
 * Get the uuid field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_uuid(xen_session *session, char **result, xen_pool_patch pool_patch);


/**
 * Get the name/label field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_name_label(xen_session *session, char **result, xen_pool_patch pool_patch);


/**
 * Get the name/description field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_name_description(xen_session *session, char **result, xen_pool_patch pool_patch);


/**
 * Get the version field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_version(xen_session *session, char **result, xen_pool_patch pool_patch);


/**
 * Get the size field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_size(xen_session *session, int64_t *result, xen_pool_patch pool_patch);


/**
 * Get the pool_applied field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_pool_applied(xen_session *session, bool *result, xen_pool_patch pool_patch);


/**
 * Get the host_patches field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_host_patches(xen_session *session, struct xen_host_patch_set **result, xen_pool_patch pool_patch);


/**
 * Get the after_apply_guidance field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_after_apply_guidance(xen_session *session, struct xen_after_apply_guidance_set **result, xen_pool_patch pool_patch);


/**
 * Get the other_config field of the given pool_patch.
 */
extern bool
xen_pool_patch_get_other_config(xen_session *session, xen_string_string_map **result, xen_pool_patch pool_patch);


/**
 * Set the other_config field of the given pool_patch.
 */
extern bool
xen_pool_patch_set_other_config(xen_session *session, xen_pool_patch pool_patch, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * pool_patch.
 */
extern bool
xen_pool_patch_add_to_other_config(xen_session *session, xen_pool_patch pool_patch, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given pool_patch.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_pool_patch_remove_from_other_config(xen_session *session, xen_pool_patch pool_patch, char *key);


/**
 * Apply the selected patch to a host and return its output.
 */
extern bool
xen_pool_patch_apply(xen_session *session, char **result, xen_pool_patch self, xen_host host);

/**
 * Apply the selected patch to a host and return its output.
 */
extern bool
xen_pool_patch_apply_async(xen_session *session, xen_task *result, xen_pool_patch self, xen_host host);


/**
 * Apply the selected patch to all hosts in the pool and return a map
 * of host_ref -> patch output.
 */
extern bool
xen_pool_patch_pool_apply(xen_session *session, xen_pool_patch self);

/**
 * Apply the selected patch to all hosts in the pool and return a map
 * of host_ref -> patch output.
 */
extern bool
xen_pool_patch_pool_apply_async(xen_session *session, xen_task *result, xen_pool_patch self);


/**
 * Execute the precheck stage of the selected patch on a host and
 * return its output.
 */
extern bool
xen_pool_patch_precheck(xen_session *session, char **result, xen_pool_patch self, xen_host host);

/**
 * Execute the precheck stage of the selected patch on a host and
 * return its output.
 */
extern bool
xen_pool_patch_precheck_async(xen_session *session, xen_task *result, xen_pool_patch self, xen_host host);


/**
 * Removes the patch's files from the server.
 */
extern bool
xen_pool_patch_clean(xen_session *session, xen_pool_patch self);

/**
 * Removes the patch's files from the server.
 */
extern bool
xen_pool_patch_clean_async(xen_session *session, xen_task *result, xen_pool_patch self);


/**
 * Removes the patch's files from all hosts in the pool, but does not
 * remove the database entries.
 */
extern bool
xen_pool_patch_pool_clean(xen_session *session, xen_pool_patch self);

/**
 * Removes the patch's files from all hosts in the pool, but does not
 * remove the database entries.
 */
extern bool
xen_pool_patch_pool_clean_async(xen_session *session, xen_task *result, xen_pool_patch self);


/**
 * Removes the patch's files from all hosts in the pool, and removes
 * the database entries.  Only works on unapplied patches.
 */
extern bool
xen_pool_patch_destroy(xen_session *session, xen_pool_patch self);

/**
 * Removes the patch's files from all hosts in the pool, and removes
 * the database entries.  Only works on unapplied patches.
 */
extern bool
xen_pool_patch_destroy_async(xen_session *session, xen_task *result, xen_pool_patch self);


/**
 * Removes the patch's files from the specified host.
 */
extern bool
xen_pool_patch_clean_on_host(xen_session *session, xen_pool_patch self, xen_host host);

/**
 * Removes the patch's files from the specified host.
 */
extern bool
xen_pool_patch_clean_on_host_async(xen_session *session, xen_task *result, xen_pool_patch self, xen_host host);


/**
 * Return a list of all the pool_patchs known to the system.
 */
extern bool
xen_pool_patch_get_all(xen_session *session, struct xen_pool_patch_set **result);


/**
 * Return a map of pool_patch references to pool_patch records for all
 * pool_patchs known to the system.
 */
extern bool
xen_pool_patch_get_all_records(xen_session *session, xen_pool_patch_xen_pool_patch_record_map **result);


#endif
