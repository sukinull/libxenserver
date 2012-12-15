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


#ifndef XEN_NETWORK_H
#define XEN_NETWORK_H

#include <xen/api/xen_blob_decl.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_network_decl.h>
#include <xen/api/xen_network_default_locking_mode.h>
#include <xen/api/xen_network_operations.h>
#include <xen/api/xen_network_xen_network_record_map.h>
#include <xen/api/xen_pif_decl.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_network_operations_map.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vif_decl.h>


/*
 * The network class.
 * 
 * A virtual network.
 */


/**
 * Free the given xen_network.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_network_free(xen_network network);


typedef struct xen_network_set
{
    size_t size;
    xen_network *contents[];
} xen_network_set;

/**
 * Allocate a xen_network_set of the given size.
 */
extern xen_network_set *
xen_network_set_alloc(size_t size);

/**
 * Free the given xen_network_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_network_set_free(xen_network_set *set);


typedef struct xen_network_record
{
    xen_network handle;
    char *uuid;
    char *name_label;
    char *name_description;
    struct xen_network_operations_set *allowed_operations;
    xen_string_network_operations_map *current_operations;
    struct xen_vif_record_opt_set *vifs;
    struct xen_pif_record_opt_set *pifs;
    int64_t mtu;
    xen_string_string_map *other_config;
    char *bridge;
    xen_string_blob_map *blobs;
    struct xen_string_set *tags;
    enum xen_network_default_locking_mode default_locking_mode;
} xen_network_record;

/**
 * Allocate a xen_network_record.
 */
extern xen_network_record *
xen_network_record_alloc(void);

/**
 * Free the given xen_network_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_network_record_free(xen_network_record *record);


typedef struct xen_network_record_opt
{
    bool is_record;
    union
    {
        xen_network handle;
        xen_network_record *record;
    } u;
} xen_network_record_opt;

/**
 * Allocate a xen_network_record_opt.
 */
extern xen_network_record_opt *
xen_network_record_opt_alloc(void);

/**
 * Free the given xen_network_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_network_record_opt_free(xen_network_record_opt *record_opt);


typedef struct xen_network_record_set
{
    size_t size;
    xen_network_record *contents[];
} xen_network_record_set;

/**
 * Allocate a xen_network_record_set of the given size.
 */
extern xen_network_record_set *
xen_network_record_set_alloc(size_t size);

/**
 * Free the given xen_network_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_network_record_set_free(xen_network_record_set *set);



typedef struct xen_network_record_opt_set
{
    size_t size;
    xen_network_record_opt *contents[];
} xen_network_record_opt_set;

/**
 * Allocate a xen_network_record_opt_set of the given size.
 */
extern xen_network_record_opt_set *
xen_network_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_network_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_network_record_opt_set_free(xen_network_record_opt_set *set);


/**
 * Get a record containing the current state of the given network.
 */
extern bool
xen_network_get_record(xen_session *session, xen_network_record **result, xen_network network);


/**
 * Get a reference to the network instance with the specified UUID.
 */
extern bool
xen_network_get_by_uuid(xen_session *session, xen_network *result, char *uuid);


/**
 * Create a new network instance, and return its handle.
 */
extern bool
xen_network_create(xen_session *session, xen_network *result, xen_network_record *record);

/**
 * Create a new network instance, and return its handle.
 */
extern bool
xen_network_create_async(xen_session *session, xen_task *result, xen_network_record *record);


/**
 * Destroy the specified network instance.
 */
extern bool
xen_network_destroy(xen_session *session, xen_network network);

/**
 * Destroy the specified network instance.
 */
extern bool
xen_network_destroy_async(xen_session *session, xen_task *result, xen_network network);


/**
 * Get all the network instances with the given label.
 */
extern bool
xen_network_get_by_name_label(xen_session *session, struct xen_network_set **result, char *label);


/**
 * Get the uuid field of the given network.
 */
extern bool
xen_network_get_uuid(xen_session *session, char **result, xen_network network);


/**
 * Get the name/label field of the given network.
 */
extern bool
xen_network_get_name_label(xen_session *session, char **result, xen_network network);


/**
 * Get the name/description field of the given network.
 */
extern bool
xen_network_get_name_description(xen_session *session, char **result, xen_network network);


/**
 * Get the allowed_operations field of the given network.
 */
extern bool
xen_network_get_allowed_operations(xen_session *session, struct xen_network_operations_set **result, xen_network network);


/**
 * Get the current_operations field of the given network.
 */
extern bool
xen_network_get_current_operations(xen_session *session, xen_string_network_operations_map **result, xen_network network);


/**
 * Get the VIFs field of the given network.
 */
extern bool
xen_network_get_vifs(xen_session *session, struct xen_vif_set **result, xen_network network);


/**
 * Get the PIFs field of the given network.
 */
extern bool
xen_network_get_pifs(xen_session *session, struct xen_pif_set **result, xen_network network);


/**
 * Get the MTU field of the given network.
 */
extern bool
xen_network_get_mtu(xen_session *session, int64_t *result, xen_network network);


/**
 * Get the other_config field of the given network.
 */
extern bool
xen_network_get_other_config(xen_session *session, xen_string_string_map **result, xen_network network);


/**
 * Get the bridge field of the given network.
 */
extern bool
xen_network_get_bridge(xen_session *session, char **result, xen_network network);


/**
 * Get the blobs field of the given network.
 */
extern bool
xen_network_get_blobs(xen_session *session, xen_string_blob_map **result, xen_network network);


/**
 * Get the tags field of the given network.
 */
extern bool
xen_network_get_tags(xen_session *session, struct xen_string_set **result, xen_network network);


/**
 * Get the default_locking_mode field of the given network.
 */
extern bool
xen_network_get_default_locking_mode(xen_session *session, enum xen_network_default_locking_mode *result, xen_network network);


/**
 * Set the name/label field of the given network.
 */
extern bool
xen_network_set_name_label(xen_session *session, xen_network network, char *label);


/**
 * Set the name/description field of the given network.
 */
extern bool
xen_network_set_name_description(xen_session *session, xen_network network, char *description);


/**
 * Set the MTU field of the given network.
 */
extern bool
xen_network_set_mtu(xen_session *session, xen_network network, int64_t mtu);


/**
 * Set the other_config field of the given network.
 */
extern bool
xen_network_set_other_config(xen_session *session, xen_network network, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * network.
 */
extern bool
xen_network_add_to_other_config(xen_session *session, xen_network network, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given network.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_network_remove_from_other_config(xen_session *session, xen_network network, char *key);


/**
 * Set the tags field of the given network.
 */
extern bool
xen_network_set_tags(xen_session *session, xen_network network, struct xen_string_set *tags);


/**
 * Add the given value to the tags field of the given network.  If the
 * value is already in that Set, then do nothing.
 */
extern bool
xen_network_add_tags(xen_session *session, xen_network network, char *value);


/**
 * Remove the given value from the tags field of the given network.  If
 * the value is not in that Set, then do nothing.
 */
extern bool
xen_network_remove_tags(xen_session *session, xen_network network, char *value);


/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this pool.
 */
extern bool
xen_network_create_new_blob(xen_session *session, xen_blob *result, xen_network network, char *name, char *mime_type, bool pubblic);

/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this pool.
 */
extern bool
xen_network_create_new_blob_async(xen_session *session, xen_task *result, xen_network network, char *name, char *mime_type, bool pubblic);


/**
 * Set the default locking mode for VIFs attached to this network.
 */
extern bool
xen_network_set_default_locking_mode(xen_session *session, xen_network network, enum xen_network_default_locking_mode value);

/**
 * Set the default locking mode for VIFs attached to this network.
 */
extern bool
xen_network_set_default_locking_mode_async(xen_session *session, xen_task *result, xen_network network, enum xen_network_default_locking_mode value);


/**
 * Return a list of all the networks known to the system.
 */
extern bool
xen_network_get_all(xen_session *session, struct xen_network_set **result);


/**
 * Return a map of network references to network records for all
 * networks known to the system.
 */
extern bool
xen_network_get_all_records(xen_session *session, xen_network_xen_network_record_map **result);


#endif
