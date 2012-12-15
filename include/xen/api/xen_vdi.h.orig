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


#ifndef XEN_VDI_H
#define XEN_VDI_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_crashdump_decl.h>
#include <xen/api/xen_on_boot.h>
#include <xen/api/xen_pool_decl.h>
#include <xen/api/xen_sr_decl.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_vdi_operations_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vbd_decl.h>
#include <xen/api/xen_vdi_decl.h>
#include <xen/api/xen_vdi_operations.h>
#include <xen/api/xen_vdi_type.h>
#include <xen/api/xen_vdi_xen_vdi_record_map.h>


/*
 * The VDI class.
 * 
 * A virtual disk image.
 */


/**
 * Free the given xen_vdi.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_vdi_free(xen_vdi vdi);


typedef struct xen_vdi_set
{
    size_t size;
    xen_vdi *contents[];
} xen_vdi_set;

/**
 * Allocate a xen_vdi_set of the given size.
 */
extern xen_vdi_set *
xen_vdi_set_alloc(size_t size);

/**
 * Free the given xen_vdi_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_vdi_set_free(xen_vdi_set *set);


typedef struct xen_vdi_record
{
    xen_vdi handle;
    char *uuid;
    char *name_label;
    char *name_description;
    struct xen_vdi_operations_set *allowed_operations;
    xen_string_vdi_operations_map *current_operations;
    struct xen_sr_record_opt *sr;
    struct xen_vbd_record_opt_set *vbds;
    struct xen_crashdump_record_opt_set *crash_dumps;
    int64_t virtual_size;
    int64_t physical_utilisation;
    enum xen_vdi_type type;
    bool sharable;
    bool read_only;
    xen_string_string_map *other_config;
    bool storage_lock;
    char *location;
    bool managed;
    bool missing;
    struct xen_vdi_record_opt *parent;
    xen_string_string_map *xenstore_data;
    xen_string_string_map *sm_config;
    bool is_a_snapshot;
    struct xen_vdi_record_opt *snapshot_of;
    struct xen_vdi_record_opt_set *snapshots;
    time_t snapshot_time;
    struct xen_string_set *tags;
    bool allow_caching;
    enum xen_on_boot on_boot;
    struct xen_pool_record_opt *metadata_of_pool;
    bool metadata_latest;
} xen_vdi_record;

/**
 * Allocate a xen_vdi_record.
 */
extern xen_vdi_record *
xen_vdi_record_alloc(void);

/**
 * Free the given xen_vdi_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_vdi_record_free(xen_vdi_record *record);


typedef struct xen_vdi_record_opt
{
    bool is_record;
    union
    {
        xen_vdi handle;
        xen_vdi_record *record;
    } u;
} xen_vdi_record_opt;

/**
 * Allocate a xen_vdi_record_opt.
 */
extern xen_vdi_record_opt *
xen_vdi_record_opt_alloc(void);

/**
 * Free the given xen_vdi_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_vdi_record_opt_free(xen_vdi_record_opt *record_opt);


typedef struct xen_vdi_record_set
{
    size_t size;
    xen_vdi_record *contents[];
} xen_vdi_record_set;

/**
 * Allocate a xen_vdi_record_set of the given size.
 */
extern xen_vdi_record_set *
xen_vdi_record_set_alloc(size_t size);

/**
 * Free the given xen_vdi_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_vdi_record_set_free(xen_vdi_record_set *set);



typedef struct xen_vdi_record_opt_set
{
    size_t size;
    xen_vdi_record_opt *contents[];
} xen_vdi_record_opt_set;

/**
 * Allocate a xen_vdi_record_opt_set of the given size.
 */
extern xen_vdi_record_opt_set *
xen_vdi_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vdi_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_vdi_record_opt_set_free(xen_vdi_record_opt_set *set);


/**
 * Get a record containing the current state of the given VDI.
 */
extern bool
xen_vdi_get_record(xen_session *session, xen_vdi_record **result, xen_vdi vdi);


/**
 * Get a reference to the VDI instance with the specified UUID.
 */
extern bool
xen_vdi_get_by_uuid(xen_session *session, xen_vdi *result, char *uuid);


/**
 * Create a new VDI instance, and return its handle.
 */
extern bool
xen_vdi_create(xen_session *session, xen_vdi *result, xen_vdi_record *record);

/**
 * Create a new VDI instance, and return its handle.
 */
extern bool
xen_vdi_create_async(xen_session *session, xen_task *result, xen_vdi_record *record);


/**
 * Destroy the specified VDI instance.
 */
extern bool
xen_vdi_destroy(xen_session *session, xen_vdi vdi);

/**
 * Destroy the specified VDI instance.
 */
extern bool
xen_vdi_destroy_async(xen_session *session, xen_task *result, xen_vdi vdi);


/**
 * Get all the VDI instances with the given label.
 */
extern bool
xen_vdi_get_by_name_label(xen_session *session, struct xen_vdi_set **result, char *label);


/**
 * Get the uuid field of the given VDI.
 */
extern bool
xen_vdi_get_uuid(xen_session *session, char **result, xen_vdi vdi);


/**
 * Get the name/label field of the given VDI.
 */
extern bool
xen_vdi_get_name_label(xen_session *session, char **result, xen_vdi vdi);


/**
 * Get the name/description field of the given VDI.
 */
extern bool
xen_vdi_get_name_description(xen_session *session, char **result, xen_vdi vdi);


/**
 * Get the allowed_operations field of the given VDI.
 */
extern bool
xen_vdi_get_allowed_operations(xen_session *session, struct xen_vdi_operations_set **result, xen_vdi vdi);


/**
 * Get the current_operations field of the given VDI.
 */
extern bool
xen_vdi_get_current_operations(xen_session *session, xen_string_vdi_operations_map **result, xen_vdi vdi);


/**
 * Get the SR field of the given VDI.
 */
extern bool
xen_vdi_get_sr(xen_session *session, xen_sr *result, xen_vdi vdi);


/**
 * Get the VBDs field of the given VDI.
 */
extern bool
xen_vdi_get_vbds(xen_session *session, struct xen_vbd_set **result, xen_vdi vdi);


/**
 * Get the crash_dumps field of the given VDI.
 */
extern bool
xen_vdi_get_crash_dumps(xen_session *session, struct xen_crashdump_set **result, xen_vdi vdi);


/**
 * Get the virtual_size field of the given VDI.
 */
extern bool
xen_vdi_get_virtual_size(xen_session *session, int64_t *result, xen_vdi vdi);


/**
 * Get the physical_utilisation field of the given VDI.
 */
extern bool
xen_vdi_get_physical_utilisation(xen_session *session, int64_t *result, xen_vdi vdi);


/**
 * Get the type field of the given VDI.
 */
extern bool
xen_vdi_get_type(xen_session *session, enum xen_vdi_type *result, xen_vdi vdi);


/**
 * Get the sharable field of the given VDI.
 */
extern bool
xen_vdi_get_sharable(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Get the read_only field of the given VDI.
 */
extern bool
xen_vdi_get_read_only(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Get the other_config field of the given VDI.
 */
extern bool
xen_vdi_get_other_config(xen_session *session, xen_string_string_map **result, xen_vdi vdi);


/**
 * Get the storage_lock field of the given VDI.
 */
extern bool
xen_vdi_get_storage_lock(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Get the location field of the given VDI.
 */
extern bool
xen_vdi_get_location(xen_session *session, char **result, xen_vdi vdi);


/**
 * Get the managed field of the given VDI.
 */
extern bool
xen_vdi_get_managed(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Get the missing field of the given VDI.
 */
extern bool
xen_vdi_get_missing(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Get the parent field of the given VDI.
 */
extern bool
xen_vdi_get_parent(xen_session *session, xen_vdi *result, xen_vdi vdi);


/**
 * Get the xenstore_data field of the given VDI.
 */
extern bool
xen_vdi_get_xenstore_data(xen_session *session, xen_string_string_map **result, xen_vdi vdi);


/**
 * Get the sm_config field of the given VDI.
 */
extern bool
xen_vdi_get_sm_config(xen_session *session, xen_string_string_map **result, xen_vdi vdi);


/**
 * Get the is_a_snapshot field of the given VDI.
 */
extern bool
xen_vdi_get_is_a_snapshot(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Get the snapshot_of field of the given VDI.
 */
extern bool
xen_vdi_get_snapshot_of(xen_session *session, xen_vdi *result, xen_vdi vdi);


/**
 * Get the snapshots field of the given VDI.
 */
extern bool
xen_vdi_get_snapshots(xen_session *session, struct xen_vdi_set **result, xen_vdi vdi);


/**
 * Get the snapshot_time field of the given VDI.
 */
extern bool
xen_vdi_get_snapshot_time(xen_session *session, time_t *result, xen_vdi vdi);


/**
 * Get the tags field of the given VDI.
 */
extern bool
xen_vdi_get_tags(xen_session *session, struct xen_string_set **result, xen_vdi vdi);


/**
 * Get the allow_caching field of the given VDI.
 */
extern bool
xen_vdi_get_allow_caching(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Get the on_boot field of the given VDI.
 */
extern bool
xen_vdi_get_on_boot(xen_session *session, enum xen_on_boot *result, xen_vdi vdi);


/**
 * Get the metadata_of_pool field of the given VDI.
 */
extern bool
xen_vdi_get_metadata_of_pool(xen_session *session, xen_pool *result, xen_vdi vdi);


/**
 * Get the metadata_latest field of the given VDI.
 */
extern bool
xen_vdi_get_metadata_latest(xen_session *session, bool *result, xen_vdi vdi);


/**
 * Set the other_config field of the given VDI.
 */
extern bool
xen_vdi_set_other_config(xen_session *session, xen_vdi vdi, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * VDI.
 */
extern bool
xen_vdi_add_to_other_config(xen_session *session, xen_vdi vdi, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given VDI.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_vdi_remove_from_other_config(xen_session *session, xen_vdi vdi, char *key);


/**
 * Set the xenstore_data field of the given VDI.
 */
extern bool
xen_vdi_set_xenstore_data(xen_session *session, xen_vdi vdi, xen_string_string_map *xenstore_data);


/**
 * Add the given key-value pair to the xenstore_data field of the given
 * VDI.
 */
extern bool
xen_vdi_add_to_xenstore_data(xen_session *session, xen_vdi vdi, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * xenstore_data field of the given VDI.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_vdi_remove_from_xenstore_data(xen_session *session, xen_vdi vdi, char *key);


/**
 * Set the sm_config field of the given VDI.
 */
extern bool
xen_vdi_set_sm_config(xen_session *session, xen_vdi vdi, xen_string_string_map *sm_config);


/**
 * Add the given key-value pair to the sm_config field of the given
 * VDI.
 */
extern bool
xen_vdi_add_to_sm_config(xen_session *session, xen_vdi vdi, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the sm_config
 * field of the given VDI.  If the key is not in that Map, then do nothing.
 */
extern bool
xen_vdi_remove_from_sm_config(xen_session *session, xen_vdi vdi, char *key);


/**
 * Set the tags field of the given VDI.
 */
extern bool
xen_vdi_set_tags(xen_session *session, xen_vdi vdi, struct xen_string_set *tags);


/**
 * Add the given value to the tags field of the given VDI.  If the
 * value is already in that Set, then do nothing.
 */
extern bool
xen_vdi_add_tags(xen_session *session, xen_vdi vdi, char *value);


/**
 * Remove the given value from the tags field of the given VDI.  If the
 * value is not in that Set, then do nothing.
 */
extern bool
xen_vdi_remove_tags(xen_session *session, xen_vdi vdi, char *value);


/**
 * Take a read-only snapshot of the VDI, returning a reference to the
 * snapshot. If any driver_params are specified then these are passed through
 * to the storage-specific substrate driver that takes the snapshot. NB the
 * snapshot lives in the same Storage Repository as its parent.
 */
extern bool
xen_vdi_snapshot(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_string_string_map *driver_params);

/**
 * Take a read-only snapshot of the VDI, returning a reference to the
 * snapshot. If any driver_params are specified then these are passed through
 * to the storage-specific substrate driver that takes the snapshot. NB the
 * snapshot lives in the same Storage Repository as its parent.
 */
extern bool
xen_vdi_snapshot_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_string_string_map *driver_params);


/**
 * Take an exact copy of the VDI and return a reference to the new
 * disk. If any driver_params are specified then these are passed through to
 * the storage-specific substrate driver that implements the clone operation.
 * NB the clone lives in the same Storage Repository as its parent.
 */
extern bool
xen_vdi_clone(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_string_string_map *driver_params);

/**
 * Take an exact copy of the VDI and return a reference to the new
 * disk. If any driver_params are specified then these are passed through to
 * the storage-specific substrate driver that implements the clone operation.
 * NB the clone lives in the same Storage Repository as its parent.
 */
extern bool
xen_vdi_clone_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_string_string_map *driver_params);


/**
 * Resize the VDI.
 */
extern bool
xen_vdi_resize(xen_session *session, xen_vdi vdi, int64_t size);

/**
 * Resize the VDI.
 */
extern bool
xen_vdi_resize_async(xen_session *session, xen_task *result, xen_vdi vdi, int64_t size);


/**
 * Resize the VDI which may or may not be attached to running guests.
 */
extern bool
xen_vdi_resize_online(xen_session *session, xen_vdi vdi, int64_t size);

/**
 * Resize the VDI which may or may not be attached to running guests.
 */
extern bool
xen_vdi_resize_online_async(xen_session *session, xen_task *result, xen_vdi vdi, int64_t size);


/**
 * Create a new VDI record in the database only.
 */
extern bool
xen_vdi_introduce(xen_session *session, xen_vdi *result, char *uuid, char *name_label, char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of);

/**
 * Create a new VDI record in the database only.
 */
extern bool
xen_vdi_introduce_async(xen_session *session, xen_task *result, char *uuid, char *name_label, char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of);


/**
 * Create a new VDI record in the database only.
 */
extern bool
xen_vdi_db_introduce(xen_session *session, xen_vdi *result, char *uuid, char *name_label, char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of);

/**
 * Create a new VDI record in the database only.
 */
extern bool
xen_vdi_db_introduce_async(xen_session *session, xen_task *result, char *uuid, char *name_label, char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of);


/**
 * Removes a VDI record from the database.
 */
extern bool
xen_vdi_db_forget(xen_session *session, xen_vdi vdi);

/**
 * Removes a VDI record from the database.
 */
extern bool
xen_vdi_db_forget_async(xen_session *session, xen_task *result, xen_vdi vdi);


/**
 * Ask the storage backend to refresh the fields in the VDI object.
 */
extern bool
xen_vdi_update(xen_session *session, xen_vdi vdi);

/**
 * Ask the storage backend to refresh the fields in the VDI object.
 */
extern bool
xen_vdi_update_async(xen_session *session, xen_task *result, xen_vdi vdi);


/**
 * Make a fresh VDI in the specified SR and copy the supplied VDI's
 * data to the new disk.
 */
extern bool
xen_vdi_copy(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_sr sr);

/**
 * Make a fresh VDI in the specified SR and copy the supplied VDI's
 * data to the new disk.
 */
extern bool
xen_vdi_copy_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_sr sr);


/**
 * Sets the VDI's managed field.
 */
extern bool
xen_vdi_set_managed(xen_session *session, xen_vdi self, bool value);


/**
 * Removes a VDI record from the database.
 */
extern bool
xen_vdi_forget(xen_session *session, xen_vdi vdi);

/**
 * Removes a VDI record from the database.
 */
extern bool
xen_vdi_forget_async(xen_session *session, xen_task *result, xen_vdi vdi);


/**
 * Sets the VDI's sharable field.
 */
extern bool
xen_vdi_set_sharable(xen_session *session, xen_vdi self, bool value);


/**
 * Sets the VDI's read_only field.
 */
extern bool
xen_vdi_set_read_only(xen_session *session, xen_vdi self, bool value);


/**
 * Sets the VDI's missing field.
 */
extern bool
xen_vdi_set_missing(xen_session *session, xen_vdi self, bool value);


/**
 * Sets the VDI's virtual_size field.
 */
extern bool
xen_vdi_set_virtual_size(xen_session *session, xen_vdi self, int64_t value);


/**
 * Sets the VDI's physical_utilisation field.
 */
extern bool
xen_vdi_set_physical_utilisation(xen_session *session, xen_vdi self, int64_t value);


/**
 * Sets whether this VDI is a snapshot.
 */
extern bool
xen_vdi_set_is_a_snapshot(xen_session *session, xen_vdi self, bool value);


/**
 * Sets the VDI of which this VDI is a snapshot.
 */
extern bool
xen_vdi_set_snapshot_of(xen_session *session, xen_vdi self, xen_vdi value);


/**
 * Sets the snapshot time of this VDI.
 */
extern bool
xen_vdi_set_snapshot_time(xen_session *session, xen_vdi self, time_t value);


/**
 * Records the pool whose metadata is contained by this VDI.
 */
extern bool
xen_vdi_set_metadata_of_pool(xen_session *session, xen_vdi self, xen_pool value);


/**
 * Set the name label of the VDI. This can only happen when then its SR
 * is currently attached.
 */
extern bool
xen_vdi_set_name_label(xen_session *session, xen_vdi self, char *value);

/**
 * Set the name label of the VDI. This can only happen when then its SR
 * is currently attached.
 */
extern bool
xen_vdi_set_name_label_async(xen_session *session, xen_task *result, xen_vdi self, char *value);


/**
 * Set the name description of the VDI. This can only happen when its
 * SR is currently attached.
 */
extern bool
xen_vdi_set_name_description(xen_session *session, xen_vdi self, char *value);

/**
 * Set the name description of the VDI. This can only happen when its
 * SR is currently attached.
 */
extern bool
xen_vdi_set_name_description_async(xen_session *session, xen_task *result, xen_vdi self, char *value);


/**
 * Set the value of the on_boot parameter. This value can only be
 * changed when the VDI is not attached to a running VM.
 */
extern bool
xen_vdi_set_on_boot(xen_session *session, xen_vdi self, enum xen_on_boot value);

/**
 * Set the value of the on_boot parameter. This value can only be
 * changed when the VDI is not attached to a running VM.
 */
extern bool
xen_vdi_set_on_boot_async(xen_session *session, xen_task *result, xen_vdi self, enum xen_on_boot value);


/**
 * Set the value of the allow_caching parameter. This value can only be
 * changed when the VDI is not attached to a running VM. The caching behaviour
 * is only affected by this flag for VHD-based VDIs that have one parent and
 * no child VHDs. Moreover, caching only takes place when the host running the
 * VM containing this VDI has a nominated SR for local caching.
 */
extern bool
xen_vdi_set_allow_caching(xen_session *session, xen_vdi self, bool value);

/**
 * Set the value of the allow_caching parameter. This value can only be
 * changed when the VDI is not attached to a running VM. The caching behaviour
 * is only affected by this flag for VHD-based VDIs that have one parent and
 * no child VHDs. Moreover, caching only takes place when the host running the
 * VM containing this VDI has a nominated SR for local caching.
 */
extern bool
xen_vdi_set_allow_caching_async(xen_session *session, xen_task *result, xen_vdi self, bool value);


/**
 * Load the metadata found on the supplied VDI and return a session
 * reference which can be used in XenAPI calls to query its contents.
 */
extern bool
xen_vdi_open_database(xen_session *session, xen_session **result, xen_vdi self);

/**
 * Load the metadata found on the supplied VDI and return a session
 * reference which can be used in XenAPI calls to query its contents.
 */
extern bool
xen_vdi_open_database_async(xen_session *session, xen_task *result, xen_vdi self);


/**
 * Check the VDI cache for the pool UUID of the database on this VDI.
 */
extern bool
xen_vdi_read_database_pool_uuid(xen_session *session, char **result, xen_vdi self);

/**
 * Check the VDI cache for the pool UUID of the database on this VDI.
 */
extern bool
xen_vdi_read_database_pool_uuid_async(xen_session *session, xen_task *result, xen_vdi self);


/**
 * Migrate a VDI, which may be attached to a running guest, to a
 * different SR. The destination SR must be visible to the guest.
 */
extern bool
xen_vdi_pool_migrate(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_sr sr, xen_string_string_map *options);

/**
 * Migrate a VDI, which may be attached to a running guest, to a
 * different SR. The destination SR must be visible to the guest.
 */
extern bool
xen_vdi_pool_migrate_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_sr sr, xen_string_string_map *options);


/**
 * Return a list of all the VDIs known to the system.
 */
extern bool
xen_vdi_get_all(xen_session *session, struct xen_vdi_set **result);


/**
 * Return a map of VDI references to VDI records for all VDIs known to
 * the system.
 */
extern bool
xen_vdi_get_all_records(xen_session *session, xen_vdi_xen_vdi_record_map **result);


#endif
