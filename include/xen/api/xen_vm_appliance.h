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


#ifndef XEN_VM_APPLIANCE_H
#define XEN_VM_APPLIANCE_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_string_vm_appliance_operation_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vm_appliance_decl.h>
#include <xen/api/xen_vm_appliance_operation.h>
#include <xen/api/xen_vm_appliance_xen_vm_appliance_record_map.h>
#include <xen/api/xen_vm_decl.h>


/*
 * The VM_appliance class.
 * 
 * VM appliance.
 */


/**
 * Free the given xen_vm_appliance.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_vm_appliance_free(xen_vm_appliance vm_appliance);


typedef struct xen_vm_appliance_set
{
    size_t size;
    xen_vm_appliance *contents[];
} xen_vm_appliance_set;

/**
 * Allocate a xen_vm_appliance_set of the given size.
 */
extern xen_vm_appliance_set *
xen_vm_appliance_set_alloc(size_t size);

/**
 * Free the given xen_vm_appliance_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_vm_appliance_set_free(xen_vm_appliance_set *set);


typedef struct xen_vm_appliance_record
{
    xen_vm_appliance handle;
    char *uuid;
    char *name_label;
    char *name_description;
    struct xen_vm_appliance_operation_set *allowed_operations;
    xen_string_vm_appliance_operation_map *current_operations;
    struct xen_vm_record_opt_set *vms;
} xen_vm_appliance_record;

/**
 * Allocate a xen_vm_appliance_record.
 */
extern xen_vm_appliance_record *
xen_vm_appliance_record_alloc(void);

/**
 * Free the given xen_vm_appliance_record, and all referenced values. 
 * The given record must have been allocated by this library.
 */
extern void
xen_vm_appliance_record_free(xen_vm_appliance_record *record);


typedef struct xen_vm_appliance_record_opt
{
    bool is_record;
    union
    {
        xen_vm_appliance handle;
        xen_vm_appliance_record *record;
    } u;
} xen_vm_appliance_record_opt;

/**
 * Allocate a xen_vm_appliance_record_opt.
 */
extern xen_vm_appliance_record_opt *
xen_vm_appliance_record_opt_alloc(void);

/**
 * Free the given xen_vm_appliance_record_opt, and all referenced
 * values.  The given record_opt must have been allocated by this library.
 */
extern void
xen_vm_appliance_record_opt_free(xen_vm_appliance_record_opt *record_opt);


typedef struct xen_vm_appliance_record_set
{
    size_t size;
    xen_vm_appliance_record *contents[];
} xen_vm_appliance_record_set;

/**
 * Allocate a xen_vm_appliance_record_set of the given size.
 */
extern xen_vm_appliance_record_set *
xen_vm_appliance_record_set_alloc(size_t size);

/**
 * Free the given xen_vm_appliance_record_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_vm_appliance_record_set_free(xen_vm_appliance_record_set *set);



typedef struct xen_vm_appliance_record_opt_set
{
    size_t size;
    xen_vm_appliance_record_opt *contents[];
} xen_vm_appliance_record_opt_set;

/**
 * Allocate a xen_vm_appliance_record_opt_set of the given size.
 */
extern xen_vm_appliance_record_opt_set *
xen_vm_appliance_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vm_appliance_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_vm_appliance_record_opt_set_free(xen_vm_appliance_record_opt_set *set);


/**
 * Get a record containing the current state of the given VM_appliance.
 */
extern bool
xen_vm_appliance_get_record(xen_session *session, xen_vm_appliance_record **result, xen_vm_appliance vm_appliance);


/**
 * Get a reference to the VM_appliance instance with the specified
 * UUID.
 */
extern bool
xen_vm_appliance_get_by_uuid(xen_session *session, xen_vm_appliance *result, char *uuid);


/**
 * Create a new VM_appliance instance, and return its handle.
 */
extern bool
xen_vm_appliance_create(xen_session *session, xen_vm_appliance *result, xen_vm_appliance_record *record);

/**
 * Create a new VM_appliance instance, and return its handle.
 */
extern bool
xen_vm_appliance_create_async(xen_session *session, xen_task *result, xen_vm_appliance_record *record);


/**
 * Destroy the specified VM_appliance instance.
 */
extern bool
xen_vm_appliance_destroy(xen_session *session, xen_vm_appliance vm_appliance);

/**
 * Destroy the specified VM_appliance instance.
 */
extern bool
xen_vm_appliance_destroy_async(xen_session *session, xen_task *result, xen_vm_appliance vm_appliance);


/**
 * Get all the VM_appliance instances with the given label.
 */
extern bool
xen_vm_appliance_get_by_name_label(xen_session *session, struct xen_vm_appliance_set **result, char *label);


/**
 * Get the uuid field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_get_uuid(xen_session *session, char **result, xen_vm_appliance vm_appliance);


/**
 * Get the name/label field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_get_name_label(xen_session *session, char **result, xen_vm_appliance vm_appliance);


/**
 * Get the name/description field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_get_name_description(xen_session *session, char **result, xen_vm_appliance vm_appliance);


/**
 * Get the allowed_operations field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_get_allowed_operations(xen_session *session, struct xen_vm_appliance_operation_set **result, xen_vm_appliance vm_appliance);


/**
 * Get the current_operations field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_get_current_operations(xen_session *session, xen_string_vm_appliance_operation_map **result, xen_vm_appliance vm_appliance);


/**
 * Get the VMs field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_get_vms(xen_session *session, struct xen_vm_set **result, xen_vm_appliance vm_appliance);


/**
 * Set the name/label field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_set_name_label(xen_session *session, xen_vm_appliance vm_appliance, char *label);


/**
 * Set the name/description field of the given VM_appliance.
 */
extern bool
xen_vm_appliance_set_name_description(xen_session *session, xen_vm_appliance vm_appliance, char *description);


/**
 * Start all VMs in the appliance.
 */
extern bool
xen_vm_appliance_start(xen_session *session, xen_vm_appliance self, bool paused);

/**
 * Start all VMs in the appliance.
 */
extern bool
xen_vm_appliance_start_async(xen_session *session, xen_task *result, xen_vm_appliance self, bool paused);


/**
 * Perform a clean shutdown of all the VMs in the appliance.
 */
extern bool
xen_vm_appliance_clean_shutdown(xen_session *session, xen_vm_appliance self);

/**
 * Perform a clean shutdown of all the VMs in the appliance.
 */
extern bool
xen_vm_appliance_clean_shutdown_async(xen_session *session, xen_task *result, xen_vm_appliance self);


/**
 * Perform a hard shutdown of all the VMs in the appliance.
 */
extern bool
xen_vm_appliance_hard_shutdown(xen_session *session, xen_vm_appliance self);

/**
 * Perform a hard shutdown of all the VMs in the appliance.
 */
extern bool
xen_vm_appliance_hard_shutdown_async(xen_session *session, xen_task *result, xen_vm_appliance self);


/**
 * For each VM in the appliance, try to shut it down cleanly. If this
 * fails, perform a hard shutdown of the VM.
 */
extern bool
xen_vm_appliance_shutdown(xen_session *session, xen_vm_appliance self);

/**
 * For each VM in the appliance, try to shut it down cleanly. If this
 * fails, perform a hard shutdown of the VM.
 */
extern bool
xen_vm_appliance_shutdown_async(xen_session *session, xen_task *result, xen_vm_appliance self);


/**
 * Assert whether all SRs required to recover this VM appliance are
 * available.
 */
extern bool
xen_vm_appliance_assert_can_be_recovered(xen_session *session, xen_vm_appliance self, xen_session *session_to);

/**
 * Assert whether all SRs required to recover this VM appliance are
 * available.
 */
extern bool
xen_vm_appliance_assert_can_be_recovered_async(xen_session *session, xen_task *result, xen_vm_appliance self, xen_session *session_to);


/**
 * Recover the VM appliance.
 */
extern bool
xen_vm_appliance_recover(xen_session *session, xen_vm_appliance self, xen_session *session_to, bool force);

/**
 * Recover the VM appliance.
 */
extern bool
xen_vm_appliance_recover_async(xen_session *session, xen_task *result, xen_vm_appliance self, xen_session *session_to, bool force);


/**
 * Return a list of all the VM_appliances known to the system.
 */
extern bool
xen_vm_appliance_get_all(xen_session *session, struct xen_vm_appliance_set **result);


/**
 * Return a map of VM_appliance references to VM_appliance records for
 * all VM_appliances known to the system.
 */
extern bool
xen_vm_appliance_get_all_records(xen_session *session, xen_vm_appliance_xen_vm_appliance_record_map **result);


#endif
