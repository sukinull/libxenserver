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


#ifndef XEN_VBD_H
#define XEN_VBD_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_vbd_operations_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vbd_decl.h>
#include <xen/api/xen_vbd_metrics_decl.h>
#include <xen/api/xen_vbd_mode.h>
#include <xen/api/xen_vbd_operations.h>
#include <xen/api/xen_vbd_type.h>
#include <xen/api/xen_vbd_xen_vbd_record_map.h>
#include <xen/api/xen_vdi_decl.h>
#include <xen/api/xen_vm_decl.h>


/*
 * The VBD class.
 * 
 * A virtual block device.
 */


/**
 * Free the given xen_vbd.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_vbd_free(xen_vbd vbd);


typedef struct xen_vbd_set
{
    size_t size;
    xen_vbd *contents[];
} xen_vbd_set;

/**
 * Allocate a xen_vbd_set of the given size.
 */
extern xen_vbd_set *
xen_vbd_set_alloc(size_t size);

/**
 * Free the given xen_vbd_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_vbd_set_free(xen_vbd_set *set);


typedef struct xen_vbd_record
{
    xen_vbd handle;
    char *uuid;
    struct xen_vbd_operations_set *allowed_operations;
    xen_string_vbd_operations_map *current_operations;
    struct xen_vm_record_opt *vm;
    struct xen_vdi_record_opt *vdi;
    char *device;
    char *userdevice;
    bool bootable;
    enum xen_vbd_mode mode;
    enum xen_vbd_type type;
    bool unpluggable;
    bool storage_lock;
    bool empty;
    xen_string_string_map *other_config;
    bool currently_attached;
    int64_t status_code;
    char *status_detail;
    xen_string_string_map *runtime_properties;
    char *qos_algorithm_type;
    xen_string_string_map *qos_algorithm_params;
    struct xen_string_set *qos_supported_algorithms;
    struct xen_vbd_metrics_record_opt *metrics;
} xen_vbd_record;

/**
 * Allocate a xen_vbd_record.
 */
extern xen_vbd_record *
xen_vbd_record_alloc(void);

/**
 * Free the given xen_vbd_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_vbd_record_free(xen_vbd_record *record);


typedef struct xen_vbd_record_opt
{
    bool is_record;
    union
    {
        xen_vbd handle;
        xen_vbd_record *record;
    } u;
} xen_vbd_record_opt;

/**
 * Allocate a xen_vbd_record_opt.
 */
extern xen_vbd_record_opt *
xen_vbd_record_opt_alloc(void);

/**
 * Free the given xen_vbd_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_vbd_record_opt_free(xen_vbd_record_opt *record_opt);


typedef struct xen_vbd_record_set
{
    size_t size;
    xen_vbd_record *contents[];
} xen_vbd_record_set;

/**
 * Allocate a xen_vbd_record_set of the given size.
 */
extern xen_vbd_record_set *
xen_vbd_record_set_alloc(size_t size);

/**
 * Free the given xen_vbd_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_vbd_record_set_free(xen_vbd_record_set *set);



typedef struct xen_vbd_record_opt_set
{
    size_t size;
    xen_vbd_record_opt *contents[];
} xen_vbd_record_opt_set;

/**
 * Allocate a xen_vbd_record_opt_set of the given size.
 */
extern xen_vbd_record_opt_set *
xen_vbd_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vbd_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_vbd_record_opt_set_free(xen_vbd_record_opt_set *set);


/**
 * Get a record containing the current state of the given VBD.
 */
extern bool
xen_vbd_get_record(xen_session *session, xen_vbd_record **result, xen_vbd vbd);


/**
 * Get a reference to the VBD instance with the specified UUID.
 */
extern bool
xen_vbd_get_by_uuid(xen_session *session, xen_vbd *result, char *uuid);


/**
 * Create a new VBD instance, and return its handle.
 */
extern bool
xen_vbd_create(xen_session *session, xen_vbd *result, xen_vbd_record *record);

/**
 * Create a new VBD instance, and return its handle.
 */
extern bool
xen_vbd_create_async(xen_session *session, xen_task *result, xen_vbd_record *record);


/**
 * Destroy the specified VBD instance.
 */
extern bool
xen_vbd_destroy(xen_session *session, xen_vbd vbd);

/**
 * Destroy the specified VBD instance.
 */
extern bool
xen_vbd_destroy_async(xen_session *session, xen_task *result, xen_vbd vbd);


/**
 * Get the uuid field of the given VBD.
 */
extern bool
xen_vbd_get_uuid(xen_session *session, char **result, xen_vbd vbd);


/**
 * Get the allowed_operations field of the given VBD.
 */
extern bool
xen_vbd_get_allowed_operations(xen_session *session, struct xen_vbd_operations_set **result, xen_vbd vbd);


/**
 * Get the current_operations field of the given VBD.
 */
extern bool
xen_vbd_get_current_operations(xen_session *session, xen_string_vbd_operations_map **result, xen_vbd vbd);


/**
 * Get the VM field of the given VBD.
 */
extern bool
xen_vbd_get_vm(xen_session *session, xen_vm *result, xen_vbd vbd);


/**
 * Get the VDI field of the given VBD.
 */
extern bool
xen_vbd_get_vdi(xen_session *session, xen_vdi *result, xen_vbd vbd);


/**
 * Get the device field of the given VBD.
 */
extern bool
xen_vbd_get_device(xen_session *session, char **result, xen_vbd vbd);


/**
 * Get the userdevice field of the given VBD.
 */
extern bool
xen_vbd_get_userdevice(xen_session *session, char **result, xen_vbd vbd);


/**
 * Get the bootable field of the given VBD.
 */
extern bool
xen_vbd_get_bootable(xen_session *session, bool *result, xen_vbd vbd);


/**
 * Get the mode field of the given VBD.
 */
extern bool
xen_vbd_get_mode(xen_session *session, enum xen_vbd_mode *result, xen_vbd vbd);


/**
 * Get the type field of the given VBD.
 */
extern bool
xen_vbd_get_type(xen_session *session, enum xen_vbd_type *result, xen_vbd vbd);


/**
 * Get the unpluggable field of the given VBD.
 */
extern bool
xen_vbd_get_unpluggable(xen_session *session, bool *result, xen_vbd vbd);


/**
 * Get the storage_lock field of the given VBD.
 */
extern bool
xen_vbd_get_storage_lock(xen_session *session, bool *result, xen_vbd vbd);


/**
 * Get the empty field of the given VBD.
 */
extern bool
xen_vbd_get_empty(xen_session *session, bool *result, xen_vbd vbd);


/**
 * Get the other_config field of the given VBD.
 */
extern bool
xen_vbd_get_other_config(xen_session *session, xen_string_string_map **result, xen_vbd vbd);


/**
 * Get the currently_attached field of the given VBD.
 */
extern bool
xen_vbd_get_currently_attached(xen_session *session, bool *result, xen_vbd vbd);


/**
 * Get the status_code field of the given VBD.
 */
extern bool
xen_vbd_get_status_code(xen_session *session, int64_t *result, xen_vbd vbd);


/**
 * Get the status_detail field of the given VBD.
 */
extern bool
xen_vbd_get_status_detail(xen_session *session, char **result, xen_vbd vbd);


/**
 * Get the runtime_properties field of the given VBD.
 */
extern bool
xen_vbd_get_runtime_properties(xen_session *session, xen_string_string_map **result, xen_vbd vbd);


/**
 * Get the qos/algorithm_type field of the given VBD.
 */
extern bool
xen_vbd_get_qos_algorithm_type(xen_session *session, char **result, xen_vbd vbd);


/**
 * Get the qos/algorithm_params field of the given VBD.
 */
extern bool
xen_vbd_get_qos_algorithm_params(xen_session *session, xen_string_string_map **result, xen_vbd vbd);


/**
 * Get the qos/supported_algorithms field of the given VBD.
 */
extern bool
xen_vbd_get_qos_supported_algorithms(xen_session *session, struct xen_string_set **result, xen_vbd vbd);


/**
 * Get the metrics field of the given VBD.
 */
extern bool
xen_vbd_get_metrics(xen_session *session, xen_vbd_metrics *result, xen_vbd vbd);


/**
 * Set the userdevice field of the given VBD.
 */
extern bool
xen_vbd_set_userdevice(xen_session *session, xen_vbd vbd, char *userdevice);


/**
 * Set the bootable field of the given VBD.
 */
extern bool
xen_vbd_set_bootable(xen_session *session, xen_vbd vbd, bool bootable);


/**
 * Set the mode field of the given VBD.
 */
extern bool
xen_vbd_set_mode(xen_session *session, xen_vbd vbd, enum xen_vbd_mode mode);


/**
 * Set the type field of the given VBD.
 */
extern bool
xen_vbd_set_type(xen_session *session, xen_vbd vbd, enum xen_vbd_type type);


/**
 * Set the unpluggable field of the given VBD.
 */
extern bool
xen_vbd_set_unpluggable(xen_session *session, xen_vbd vbd, bool unpluggable);


/**
 * Set the other_config field of the given VBD.
 */
extern bool
xen_vbd_set_other_config(xen_session *session, xen_vbd vbd, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * VBD.
 */
extern bool
xen_vbd_add_to_other_config(xen_session *session, xen_vbd vbd, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given VBD.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_vbd_remove_from_other_config(xen_session *session, xen_vbd vbd, char *key);


/**
 * Set the qos/algorithm_type field of the given VBD.
 */
extern bool
xen_vbd_set_qos_algorithm_type(xen_session *session, xen_vbd vbd, char *algorithm_type);


/**
 * Set the qos/algorithm_params field of the given VBD.
 */
extern bool
xen_vbd_set_qos_algorithm_params(xen_session *session, xen_vbd vbd, xen_string_string_map *algorithm_params);


/**
 * Add the given key-value pair to the qos/algorithm_params field of
 * the given VBD.
 */
extern bool
xen_vbd_add_to_qos_algorithm_params(xen_session *session, xen_vbd vbd, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * qos/algorithm_params field of the given VBD.  If the key is not in that
 * Map, then do nothing.
 */
extern bool
xen_vbd_remove_from_qos_algorithm_params(xen_session *session, xen_vbd vbd, char *key);


/**
 * Remove the media from the device and leave it empty.
 */
extern bool
xen_vbd_eject(xen_session *session, xen_vbd vbd);

/**
 * Remove the media from the device and leave it empty.
 */
extern bool
xen_vbd_eject_async(xen_session *session, xen_task *result, xen_vbd vbd);


/**
 * Insert new media into the device.
 */
extern bool
xen_vbd_insert(xen_session *session, xen_vbd vbd, xen_vdi vdi);

/**
 * Insert new media into the device.
 */
extern bool
xen_vbd_insert_async(xen_session *session, xen_task *result, xen_vbd vbd, xen_vdi vdi);


/**
 * Hotplug the specified VBD, dynamically attaching it to the running
 * VM.
 */
extern bool
xen_vbd_plug(xen_session *session, xen_vbd self);

/**
 * Hotplug the specified VBD, dynamically attaching it to the running
 * VM.
 */
extern bool
xen_vbd_plug_async(xen_session *session, xen_task *result, xen_vbd self);


/**
 * Hot-unplug the specified VBD, dynamically unattaching it from the
 * running VM.
 */
extern bool
xen_vbd_unplug(xen_session *session, xen_vbd self);

/**
 * Hot-unplug the specified VBD, dynamically unattaching it from the
 * running VM.
 */
extern bool
xen_vbd_unplug_async(xen_session *session, xen_task *result, xen_vbd self);


/**
 * Forcibly unplug the specified VBD.
 */
extern bool
xen_vbd_unplug_force(xen_session *session, xen_vbd self);

/**
 * Forcibly unplug the specified VBD.
 */
extern bool
xen_vbd_unplug_force_async(xen_session *session, xen_task *result, xen_vbd self);


/**
 * Throws an error if this VBD could not be attached to this VM if the
 * VM were running. Intended for debugging.
 */
extern bool
xen_vbd_assert_attachable(xen_session *session, xen_vbd self);

/**
 * Throws an error if this VBD could not be attached to this VM if the
 * VM were running. Intended for debugging.
 */
extern bool
xen_vbd_assert_attachable_async(xen_session *session, xen_task *result, xen_vbd self);


/**
 * Return a list of all the VBDs known to the system.
 */
extern bool
xen_vbd_get_all(xen_session *session, struct xen_vbd_set **result);


/**
 * Return a map of VBD references to VBD records for all VBDs known to
 * the system.
 */
extern bool
xen_vbd_get_all_records(xen_session *session, xen_vbd_xen_vbd_record_map **result);


#endif
