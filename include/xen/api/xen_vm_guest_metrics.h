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


#ifndef XEN_VM_GUEST_METRICS_H
#define XEN_VM_GUEST_METRICS_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vm_guest_metrics_decl.h>
#include <xen/api/xen_vm_guest_metrics_xen_vm_guest_metrics_record_map.h>


/*
 * The VM_guest_metrics class.
 * 
 * The metrics reported by the guest (as opposed to inferred from outside).
 */


/**
 * Free the given xen_vm_guest_metrics.  The given handle must have
 * been allocated by this library.
 */
extern void
xen_vm_guest_metrics_free(xen_vm_guest_metrics vm_guest_metrics);


typedef struct xen_vm_guest_metrics_set
{
    size_t size;
    xen_vm_guest_metrics *contents[];
} xen_vm_guest_metrics_set;

/**
 * Allocate a xen_vm_guest_metrics_set of the given size.
 */
extern xen_vm_guest_metrics_set *
xen_vm_guest_metrics_set_alloc(size_t size);

/**
 * Free the given xen_vm_guest_metrics_set.  The given set must have
 * been allocated by this library.
 */
extern void
xen_vm_guest_metrics_set_free(xen_vm_guest_metrics_set *set);


typedef struct xen_vm_guest_metrics_record
{
    xen_vm_guest_metrics handle;
    char *uuid;
    xen_string_string_map *os_version;
    xen_string_string_map *pv_drivers_version;
    bool pv_drivers_up_to_date;
    xen_string_string_map *memory;
    xen_string_string_map *disks;
    xen_string_string_map *networks;
    xen_string_string_map *other;
    time_t last_updated;
    xen_string_string_map *other_config;
    bool live;
} xen_vm_guest_metrics_record;

/**
 * Allocate a xen_vm_guest_metrics_record.
 */
extern xen_vm_guest_metrics_record *
xen_vm_guest_metrics_record_alloc(void);

/**
 * Free the given xen_vm_guest_metrics_record, and all referenced
 * values.  The given record must have been allocated by this library.
 */
extern void
xen_vm_guest_metrics_record_free(xen_vm_guest_metrics_record *record);


typedef struct xen_vm_guest_metrics_record_opt
{
    bool is_record;
    union
    {
        xen_vm_guest_metrics handle;
        xen_vm_guest_metrics_record *record;
    } u;
} xen_vm_guest_metrics_record_opt;

/**
 * Allocate a xen_vm_guest_metrics_record_opt.
 */
extern xen_vm_guest_metrics_record_opt *
xen_vm_guest_metrics_record_opt_alloc(void);

/**
 * Free the given xen_vm_guest_metrics_record_opt, and all referenced
 * values.  The given record_opt must have been allocated by this library.
 */
extern void
xen_vm_guest_metrics_record_opt_free(xen_vm_guest_metrics_record_opt *record_opt);


typedef struct xen_vm_guest_metrics_record_set
{
    size_t size;
    xen_vm_guest_metrics_record *contents[];
} xen_vm_guest_metrics_record_set;

/**
 * Allocate a xen_vm_guest_metrics_record_set of the given size.
 */
extern xen_vm_guest_metrics_record_set *
xen_vm_guest_metrics_record_set_alloc(size_t size);

/**
 * Free the given xen_vm_guest_metrics_record_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_vm_guest_metrics_record_set_free(xen_vm_guest_metrics_record_set *set);



typedef struct xen_vm_guest_metrics_record_opt_set
{
    size_t size;
    xen_vm_guest_metrics_record_opt *contents[];
} xen_vm_guest_metrics_record_opt_set;

/**
 * Allocate a xen_vm_guest_metrics_record_opt_set of the given size.
 */
extern xen_vm_guest_metrics_record_opt_set *
xen_vm_guest_metrics_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vm_guest_metrics_record_opt_set, and all
 * referenced values.  The given set must have been allocated by this library.
 */
extern void
xen_vm_guest_metrics_record_opt_set_free(xen_vm_guest_metrics_record_opt_set *set);


/**
 * Get a record containing the current state of the given
 * VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_record(xen_session *session, xen_vm_guest_metrics_record **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get a reference to the VM_guest_metrics instance with the specified
 * UUID.
 */
extern bool
xen_vm_guest_metrics_get_by_uuid(xen_session *session, xen_vm_guest_metrics *result, char *uuid);


/**
 * Get the uuid field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_uuid(xen_session *session, char **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the os_version field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_os_version(xen_session *session, xen_string_string_map **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the PV_drivers_version field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_pv_drivers_version(xen_session *session, xen_string_string_map **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the PV_drivers_up_to_date field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_pv_drivers_up_to_date(xen_session *session, bool *result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the memory field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_memory(xen_session *session, xen_string_string_map **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the disks field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_disks(xen_session *session, xen_string_string_map **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the networks field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_networks(xen_session *session, xen_string_string_map **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the other field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_other(xen_session *session, xen_string_string_map **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the last_updated field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_last_updated(xen_session *session, time_t *result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the other_config field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_other_config(xen_session *session, xen_string_string_map **result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Get the live field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_get_live(xen_session *session, bool *result, xen_vm_guest_metrics vm_guest_metrics);


/**
 * Set the other_config field of the given VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_set_other_config(xen_session *session, xen_vm_guest_metrics vm_guest_metrics, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * VM_guest_metrics.
 */
extern bool
xen_vm_guest_metrics_add_to_other_config(xen_session *session, xen_vm_guest_metrics vm_guest_metrics, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given VM_guest_metrics.  If the key is not in
 * that Map, then do nothing.
 */
extern bool
xen_vm_guest_metrics_remove_from_other_config(xen_session *session, xen_vm_guest_metrics vm_guest_metrics, char *key);


/**
 * Return a list of all the VM_guest_metrics instances known to the
 * system.
 */
extern bool
xen_vm_guest_metrics_get_all(xen_session *session, struct xen_vm_guest_metrics_set **result);


/**
 * Return a map of VM_guest_metrics references to VM_guest_metrics
 * records for all VM_guest_metrics instances known to the system.
 */
extern bool
xen_vm_guest_metrics_get_all_records(xen_session *session, xen_vm_guest_metrics_xen_vm_guest_metrics_record_map **result);


#endif
