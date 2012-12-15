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


#ifndef XEN_VM_OPERATIONS_H
#define XEN_VM_OPERATIONS_H


#include <xen/api/xen_common.h>


enum xen_vm_operations
{
    /**
     * refers to the operation "snapshot"
     */
    XEN_VM_OPERATIONS_SNAPSHOT,

    /**
     * refers to the operation "clone"
     */
    XEN_VM_OPERATIONS_CLONE,

    /**
     * refers to the operation "copy"
     */
    XEN_VM_OPERATIONS_COPY,

    /**
     * refers to the operation "create_template"
     */
    XEN_VM_OPERATIONS_CREATE_TEMPLATE,

    /**
     * refers to the operation "revert"
     */
    XEN_VM_OPERATIONS_REVERT,

    /**
     * refers to the operation "checkpoint"
     */
    XEN_VM_OPERATIONS_CHECKPOINT,

    /**
     * refers to the operation "snapshot_with_quiesce"
     */
    XEN_VM_OPERATIONS_SNAPSHOT_WITH_QUIESCE,

    /**
     * refers to the operation "provision"
     */
    XEN_VM_OPERATIONS_PROVISION,

    /**
     * refers to the operation "start"
     */
    XEN_VM_OPERATIONS_START,

    /**
     * refers to the operation "start_on"
     */
    XEN_VM_OPERATIONS_START_ON,

    /**
     * refers to the operation "pause"
     */
    XEN_VM_OPERATIONS_PAUSE,

    /**
     * refers to the operation "unpause"
     */
    XEN_VM_OPERATIONS_UNPAUSE,

    /**
     * refers to the operation "clean_shutdown"
     */
    XEN_VM_OPERATIONS_CLEAN_SHUTDOWN,

    /**
     * refers to the operation "clean_reboot"
     */
    XEN_VM_OPERATIONS_CLEAN_REBOOT,

    /**
     * refers to the operation "hard_shutdown"
     */
    XEN_VM_OPERATIONS_HARD_SHUTDOWN,

    /**
     * refers to the operation "power_state_reset"
     */
    XEN_VM_OPERATIONS_POWER_STATE_RESET,

    /**
     * refers to the operation "hard_reboot"
     */
    XEN_VM_OPERATIONS_HARD_REBOOT,

    /**
     * refers to the operation "suspend"
     */
    XEN_VM_OPERATIONS_SUSPEND,

    /**
     * refers to the operation "csvm"
     */
    XEN_VM_OPERATIONS_CSVM,

    /**
     * refers to the operation "resume"
     */
    XEN_VM_OPERATIONS_RESUME,

    /**
     * refers to the operation "resume_on"
     */
    XEN_VM_OPERATIONS_RESUME_ON,

    /**
     * refers to the operation "pool_migrate"
     */
    XEN_VM_OPERATIONS_POOL_MIGRATE,

    /**
     * refers to the operation "migrate_send"
     */
    XEN_VM_OPERATIONS_MIGRATE_SEND,

    /**
     * refers to the operation "get_boot_record"
     */
    XEN_VM_OPERATIONS_GET_BOOT_RECORD,

    /**
     * refers to the operation "send_sysrq"
     */
    XEN_VM_OPERATIONS_SEND_SYSRQ,

    /**
     * refers to the operation "send_trigger"
     */
    XEN_VM_OPERATIONS_SEND_TRIGGER,

    /**
     * refers to the operation "query_services"
     */
    XEN_VM_OPERATIONS_QUERY_SERVICES,

    /**
     * Changing the memory settings
     */
    XEN_VM_OPERATIONS_CHANGING_MEMORY_LIVE,

    /**
     * Waiting for the memory settings to change
     */
    XEN_VM_OPERATIONS_AWAITING_MEMORY_LIVE,

    /**
     * Changing the memory dynamic range
     */
    XEN_VM_OPERATIONS_CHANGING_DYNAMIC_RANGE,

    /**
     * Changing the memory static range
     */
    XEN_VM_OPERATIONS_CHANGING_STATIC_RANGE,

    /**
     * Changing the memory limits
     */
    XEN_VM_OPERATIONS_CHANGING_MEMORY_LIMITS,

    /**
     * Changing the shadow memory for a halted VM.
     */
    XEN_VM_OPERATIONS_CHANGING_SHADOW_MEMORY,

    /**
     * Changing the shadow memory for a running VM.
     */
    XEN_VM_OPERATIONS_CHANGING_SHADOW_MEMORY_LIVE,

    /**
     * Changing VCPU settings for a halted VM.
     */
    XEN_VM_OPERATIONS_CHANGING_VCPUS,

    /**
     * Changing VCPU settings for a running VM.
     */
    XEN_VM_OPERATIONS_CHANGING_VCPUS_LIVE,

    /**
     * 
     */
    XEN_VM_OPERATIONS_ASSERT_OPERATION_VALID,

    /**
     * Add, remove, query or list data sources
     */
    XEN_VM_OPERATIONS_DATA_SOURCE_OP,

    /**
     * 
     */
    XEN_VM_OPERATIONS_UPDATE_ALLOWED_OPERATIONS,

    /**
     * Turning this VM into a template
     */
    XEN_VM_OPERATIONS_MAKE_INTO_TEMPLATE,

    /**
     * importing a VM from a network stream
     */
    XEN_VM_OPERATIONS_IMPORT,

    /**
     * exporting a VM to a network stream
     */
    XEN_VM_OPERATIONS_EXPORT,

    /**
     * exporting VM metadata to a network stream
     */
    XEN_VM_OPERATIONS_METADATA_EXPORT,

    /**
     * Reverting the VM to a previous snapshotted state
     */
    XEN_VM_OPERATIONS_REVERTING,

    /**
     * refers to the act of uninstalling the VM
     */
    XEN_VM_OPERATIONS_DESTROY,

    /**
     * Unknown to this version of the bindings.
     */
    XEN_VM_OPERATIONS_UNDEFINED
};


typedef struct xen_vm_operations_set
{
    size_t size;
    enum xen_vm_operations contents[];
} xen_vm_operations_set;

/**
 * Allocate a xen_vm_operations_set of the given size.
 */
extern xen_vm_operations_set *
xen_vm_operations_set_alloc(size_t size);

/**
 * Free the given xen_vm_operations_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_vm_operations_set_free(xen_vm_operations_set *set);


/**
 * Return the name corresponding to the given code.  This string must
 * not be modified or freed.
 */
extern const char *
xen_vm_operations_to_string(enum xen_vm_operations val);


/**
 * Return the correct code for the given string, or set the session
 * object to failure and return an undefined value if the given string does
 * not match a known code.
 */
extern enum xen_vm_operations
xen_vm_operations_from_string(xen_session *session, const char *str);


#endif
