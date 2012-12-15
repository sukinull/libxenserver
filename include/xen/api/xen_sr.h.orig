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


#ifndef XEN_SR_H
#define XEN_SR_H

#include <xen/api/xen_blob_decl.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_dr_task_decl.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_pbd_decl.h>
#include <xen/api/xen_sr_decl.h>
#include <xen/api/xen_sr_xen_sr_record_map.h>
#include <xen/api/xen_storage_operations.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_storage_operations_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vdi_decl.h>


/*
 * The SR class.
 * 
 * A storage repository.
 */


/**
 * Free the given xen_sr.  The given handle must have been allocated by
 * this library.
 */
extern void
xen_sr_free(xen_sr sr);


typedef struct xen_sr_set
{
    size_t size;
    xen_sr *contents[];
} xen_sr_set;

/**
 * Allocate a xen_sr_set of the given size.
 */
extern xen_sr_set *
xen_sr_set_alloc(size_t size);

/**
 * Free the given xen_sr_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_sr_set_free(xen_sr_set *set);


typedef struct xen_sr_record
{
    xen_sr handle;
    char *uuid;
    char *name_label;
    char *name_description;
    struct xen_storage_operations_set *allowed_operations;
    xen_string_storage_operations_map *current_operations;
    struct xen_vdi_record_opt_set *vdis;
    struct xen_pbd_record_opt_set *pbds;
    int64_t virtual_allocation;
    int64_t physical_utilisation;
    int64_t physical_size;
    char *type;
    char *content_type;
    bool shared;
    xen_string_string_map *other_config;
    struct xen_string_set *tags;
    xen_string_string_map *sm_config;
    xen_string_blob_map *blobs;
    bool local_cache_enabled;
    struct xen_dr_task_record_opt *introduced_by;
} xen_sr_record;

/**
 * Allocate a xen_sr_record.
 */
extern xen_sr_record *
xen_sr_record_alloc(void);

/**
 * Free the given xen_sr_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_sr_record_free(xen_sr_record *record);


typedef struct xen_sr_record_opt
{
    bool is_record;
    union
    {
        xen_sr handle;
        xen_sr_record *record;
    } u;
} xen_sr_record_opt;

/**
 * Allocate a xen_sr_record_opt.
 */
extern xen_sr_record_opt *
xen_sr_record_opt_alloc(void);

/**
 * Free the given xen_sr_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_sr_record_opt_free(xen_sr_record_opt *record_opt);


typedef struct xen_sr_record_set
{
    size_t size;
    xen_sr_record *contents[];
} xen_sr_record_set;

/**
 * Allocate a xen_sr_record_set of the given size.
 */
extern xen_sr_record_set *
xen_sr_record_set_alloc(size_t size);

/**
 * Free the given xen_sr_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_sr_record_set_free(xen_sr_record_set *set);



typedef struct xen_sr_record_opt_set
{
    size_t size;
    xen_sr_record_opt *contents[];
} xen_sr_record_opt_set;

/**
 * Allocate a xen_sr_record_opt_set of the given size.
 */
extern xen_sr_record_opt_set *
xen_sr_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_sr_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_sr_record_opt_set_free(xen_sr_record_opt_set *set);


/**
 * Get a record containing the current state of the given SR.
 */
extern bool
xen_sr_get_record(xen_session *session, xen_sr_record **result, xen_sr sr);


/**
 * Get a reference to the SR instance with the specified UUID.
 */
extern bool
xen_sr_get_by_uuid(xen_session *session, xen_sr *result, char *uuid);


/**
 * Get all the SR instances with the given label.
 */
extern bool
xen_sr_get_by_name_label(xen_session *session, struct xen_sr_set **result, char *label);


/**
 * Get the uuid field of the given SR.
 */
extern bool
xen_sr_get_uuid(xen_session *session, char **result, xen_sr sr);


/**
 * Get the name/label field of the given SR.
 */
extern bool
xen_sr_get_name_label(xen_session *session, char **result, xen_sr sr);


/**
 * Get the name/description field of the given SR.
 */
extern bool
xen_sr_get_name_description(xen_session *session, char **result, xen_sr sr);


/**
 * Get the allowed_operations field of the given SR.
 */
extern bool
xen_sr_get_allowed_operations(xen_session *session, struct xen_storage_operations_set **result, xen_sr sr);


/**
 * Get the current_operations field of the given SR.
 */
extern bool
xen_sr_get_current_operations(xen_session *session, xen_string_storage_operations_map **result, xen_sr sr);


/**
 * Get the VDIs field of the given SR.
 */
extern bool
xen_sr_get_vdis(xen_session *session, struct xen_vdi_set **result, xen_sr sr);


/**
 * Get the PBDs field of the given SR.
 */
extern bool
xen_sr_get_pbds(xen_session *session, struct xen_pbd_set **result, xen_sr sr);


/**
 * Get the virtual_allocation field of the given SR.
 */
extern bool
xen_sr_get_virtual_allocation(xen_session *session, int64_t *result, xen_sr sr);


/**
 * Get the physical_utilisation field of the given SR.
 */
extern bool
xen_sr_get_physical_utilisation(xen_session *session, int64_t *result, xen_sr sr);


/**
 * Get the physical_size field of the given SR.
 */
extern bool
xen_sr_get_physical_size(xen_session *session, int64_t *result, xen_sr sr);


/**
 * Get the type field of the given SR.
 */
extern bool
xen_sr_get_type(xen_session *session, char **result, xen_sr sr);


/**
 * Get the content_type field of the given SR.
 */
extern bool
xen_sr_get_content_type(xen_session *session, char **result, xen_sr sr);


/**
 * Get the shared field of the given SR.
 */
extern bool
xen_sr_get_shared(xen_session *session, bool *result, xen_sr sr);


/**
 * Get the other_config field of the given SR.
 */
extern bool
xen_sr_get_other_config(xen_session *session, xen_string_string_map **result, xen_sr sr);


/**
 * Get the tags field of the given SR.
 */
extern bool
xen_sr_get_tags(xen_session *session, struct xen_string_set **result, xen_sr sr);


/**
 * Get the sm_config field of the given SR.
 */
extern bool
xen_sr_get_sm_config(xen_session *session, xen_string_string_map **result, xen_sr sr);


/**
 * Get the blobs field of the given SR.
 */
extern bool
xen_sr_get_blobs(xen_session *session, xen_string_blob_map **result, xen_sr sr);


/**
 * Get the local_cache_enabled field of the given SR.
 */
extern bool
xen_sr_get_local_cache_enabled(xen_session *session, bool *result, xen_sr sr);


/**
 * Get the introduced_by field of the given SR.
 */
extern bool
xen_sr_get_introduced_by(xen_session *session, xen_dr_task *result, xen_sr sr);


/**
 * Set the other_config field of the given SR.
 */
extern bool
xen_sr_set_other_config(xen_session *session, xen_sr sr, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * SR.
 */
extern bool
xen_sr_add_to_other_config(xen_session *session, xen_sr sr, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given SR.  If the key is not in that Map, then do
 * nothing.
 */
extern bool
xen_sr_remove_from_other_config(xen_session *session, xen_sr sr, char *key);


/**
 * Set the tags field of the given SR.
 */
extern bool
xen_sr_set_tags(xen_session *session, xen_sr sr, struct xen_string_set *tags);


/**
 * Add the given value to the tags field of the given SR.  If the value
 * is already in that Set, then do nothing.
 */
extern bool
xen_sr_add_tags(xen_session *session, xen_sr sr, char *value);


/**
 * Remove the given value from the tags field of the given SR.  If the
 * value is not in that Set, then do nothing.
 */
extern bool
xen_sr_remove_tags(xen_session *session, xen_sr sr, char *value);


/**
 * Set the sm_config field of the given SR.
 */
extern bool
xen_sr_set_sm_config(xen_session *session, xen_sr sr, xen_string_string_map *sm_config);


/**
 * Add the given key-value pair to the sm_config field of the given SR.
 */
extern bool
xen_sr_add_to_sm_config(xen_session *session, xen_sr sr, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the sm_config
 * field of the given SR.  If the key is not in that Map, then do nothing.
 */
extern bool
xen_sr_remove_from_sm_config(xen_session *session, xen_sr sr, char *key);


/**
 * Create a new Storage Repository and introduce it into the managed
 * system, creating both SR record and PBD record to attach it to current host
 * (with specified device_config parameters).
 */
extern bool
xen_sr_create(xen_session *session, xen_sr *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, char *name_label, char *name_description, char *type, char *content_type, bool shared, xen_string_string_map *sm_config);

/**
 * Create a new Storage Repository and introduce it into the managed
 * system, creating both SR record and PBD record to attach it to current host
 * (with specified device_config parameters).
 */
extern bool
xen_sr_create_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, char *name_label, char *name_description, char *type, char *content_type, bool shared, xen_string_string_map *sm_config);


/**
 * Introduce a new Storage Repository into the managed system.
 */
extern bool
xen_sr_introduce(xen_session *session, xen_sr *result, char *uuid, char *name_label, char *name_description, char *type, char *content_type, bool shared, xen_string_string_map *sm_config);

/**
 * Introduce a new Storage Repository into the managed system.
 */
extern bool
xen_sr_introduce_async(xen_session *session, xen_task *result, char *uuid, char *name_label, char *name_description, char *type, char *content_type, bool shared, xen_string_string_map *sm_config);


/**
 * Create a new Storage Repository on disk. This call is deprecated:
 * use SR.create instead.
 */
extern bool
xen_sr_make(xen_session *session, char **result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, char *name_label, char *name_description, char *type, char *content_type, xen_string_string_map *sm_config);

/**
 * Create a new Storage Repository on disk. This call is deprecated:
 * use SR.create instead.
 */
extern bool
xen_sr_make_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, char *name_label, char *name_description, char *type, char *content_type, xen_string_string_map *sm_config);


/**
 * Destroy specified SR, removing SR-record from database and remove SR
 * from disk. (In order to affect this operation the appropriate device_config
 * is read from the specified SR's PBD on current host).
 */
extern bool
xen_sr_destroy(xen_session *session, xen_sr sr);

/**
 * Destroy specified SR, removing SR-record from database and remove SR
 * from disk. (In order to affect this operation the appropriate device_config
 * is read from the specified SR's PBD on current host).
 */
extern bool
xen_sr_destroy_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * Removing specified SR-record from database, without attempting to
 * remove SR from disk.
 */
extern bool
xen_sr_forget(xen_session *session, xen_sr sr);

/**
 * Removing specified SR-record from database, without attempting to
 * remove SR from disk.
 */
extern bool
xen_sr_forget_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * Refresh the fields on the SR object.
 */
extern bool
xen_sr_update(xen_session *session, xen_sr sr);

/**
 * Refresh the fields on the SR object.
 */
extern bool
xen_sr_update_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * Return a set of all the SR types supported by the system.
 */
extern bool
xen_sr_get_supported_types(xen_session *session, struct xen_string_set **result);


/**
 * Refreshes the list of VDIs associated with an SR.
 */
extern bool
xen_sr_scan(xen_session *session, xen_sr sr);

/**
 * Refreshes the list of VDIs associated with an SR.
 */
extern bool
xen_sr_scan_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * Perform a backend-specific scan, using the given device_config.  If
 * the device_config is complete, then this will return a list of the SRs
 * present of this type on the device, if any.  If the device_config is
 * partial, then a backend-specific scan will be performed, returning results
 * that will guide the user in improving the device_config.
 */
extern bool
xen_sr_probe(xen_session *session, char **result, xen_host host, xen_string_string_map *device_config, char *type, xen_string_string_map *sm_config);

/**
 * Perform a backend-specific scan, using the given device_config.  If
 * the device_config is complete, then this will return a list of the SRs
 * present of this type on the device, if any.  If the device_config is
 * partial, then a backend-specific scan will be performed, returning results
 * that will guide the user in improving the device_config.
 */
extern bool
xen_sr_probe_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, char *type, xen_string_string_map *sm_config);


/**
 * Sets the shared flag on the SR.
 */
extern bool
xen_sr_set_shared(xen_session *session, xen_sr sr, bool value);

/**
 * Sets the shared flag on the SR.
 */
extern bool
xen_sr_set_shared_async(xen_session *session, xen_task *result, xen_sr sr, bool value);


/**
 * Set the name label of the SR.
 */
extern bool
xen_sr_set_name_label(xen_session *session, xen_sr sr, char *value);

/**
 * Set the name label of the SR.
 */
extern bool
xen_sr_set_name_label_async(xen_session *session, xen_task *result, xen_sr sr, char *value);


/**
 * Set the name description of the SR.
 */
extern bool
xen_sr_set_name_description(xen_session *session, xen_sr sr, char *value);

/**
 * Set the name description of the SR.
 */
extern bool
xen_sr_set_name_description_async(xen_session *session, xen_task *result, xen_sr sr, char *value);


/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this SR.
 */
extern bool
xen_sr_create_new_blob(xen_session *session, xen_blob *result, xen_sr sr, char *name, char *mime_type, bool pubblic);

/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this SR.
 */
extern bool
xen_sr_create_new_blob_async(xen_session *session, xen_task *result, xen_sr sr, char *name, char *mime_type, bool pubblic);


/**
 * Sets the SR's physical_size field.
 */
extern bool
xen_sr_set_physical_size(xen_session *session, xen_sr self, int64_t value);


/**
 * Sets the SR's virtual_allocation field.
 */
extern bool
xen_sr_set_virtual_allocation(xen_session *session, xen_sr self, int64_t value);


/**
 * Sets the SR's physical_utilisation field.
 */
extern bool
xen_sr_set_physical_utilisation(xen_session *session, xen_sr self, int64_t value);


/**
 * Returns successfully if the given SR can host an HA statefile.
 * Otherwise returns an error to explain why not.
 */
extern bool
xen_sr_assert_can_host_ha_statefile(xen_session *session, xen_sr sr);

/**
 * Returns successfully if the given SR can host an HA statefile.
 * Otherwise returns an error to explain why not.
 */
extern bool
xen_sr_assert_can_host_ha_statefile_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * Returns successfully if the given SR supports database replication.
 * Otherwise returns an error to explain why not.
 */
extern bool
xen_sr_assert_supports_database_replication(xen_session *session, xen_sr sr);

/**
 * Returns successfully if the given SR supports database replication.
 * Otherwise returns an error to explain why not.
 */
extern bool
xen_sr_assert_supports_database_replication_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * .
 */
extern bool
xen_sr_enable_database_replication(xen_session *session, xen_sr sr);

/**
 * .
 */
extern bool
xen_sr_enable_database_replication_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * .
 */
extern bool
xen_sr_disable_database_replication(xen_session *session, xen_sr sr);

/**
 * .
 */
extern bool
xen_sr_disable_database_replication_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * Return a list of all the SRs known to the system.
 */
extern bool
xen_sr_get_all(xen_session *session, struct xen_sr_set **result);


/**
 * Return a map of SR references to SR records for all SRs known to the
 * system.
 */
extern bool
xen_sr_get_all_records(xen_session *session, xen_sr_xen_sr_record_map **result);


#endif
