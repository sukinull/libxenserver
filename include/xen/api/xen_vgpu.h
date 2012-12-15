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


#ifndef XEN_VGPU_H
#define XEN_VGPU_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_gpu_group_decl.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vgpu_decl.h>
#include <xen/api/xen_vgpu_xen_vgpu_record_map.h>
#include <xen/api/xen_vm_decl.h>


/*
 * The VGPU class.
 * 
 * A virtual GPU (vGPU).
 */


/**
 * Free the given xen_vgpu.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_vgpu_free(xen_vgpu vgpu);


typedef struct xen_vgpu_set
{
    size_t size;
    xen_vgpu *contents[];
} xen_vgpu_set;

/**
 * Allocate a xen_vgpu_set of the given size.
 */
extern xen_vgpu_set *
xen_vgpu_set_alloc(size_t size);

/**
 * Free the given xen_vgpu_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_vgpu_set_free(xen_vgpu_set *set);


typedef struct xen_vgpu_record
{
    xen_vgpu handle;
    char *uuid;
    struct xen_vm_record_opt *vm;
    struct xen_gpu_group_record_opt *gpu_group;
    char *device;
    bool currently_attached;
    xen_string_string_map *other_config;
} xen_vgpu_record;

/**
 * Allocate a xen_vgpu_record.
 */
extern xen_vgpu_record *
xen_vgpu_record_alloc(void);

/**
 * Free the given xen_vgpu_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_vgpu_record_free(xen_vgpu_record *record);


typedef struct xen_vgpu_record_opt
{
    bool is_record;
    union
    {
        xen_vgpu handle;
        xen_vgpu_record *record;
    } u;
} xen_vgpu_record_opt;

/**
 * Allocate a xen_vgpu_record_opt.
 */
extern xen_vgpu_record_opt *
xen_vgpu_record_opt_alloc(void);

/**
 * Free the given xen_vgpu_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_vgpu_record_opt_free(xen_vgpu_record_opt *record_opt);


typedef struct xen_vgpu_record_set
{
    size_t size;
    xen_vgpu_record *contents[];
} xen_vgpu_record_set;

/**
 * Allocate a xen_vgpu_record_set of the given size.
 */
extern xen_vgpu_record_set *
xen_vgpu_record_set_alloc(size_t size);

/**
 * Free the given xen_vgpu_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_vgpu_record_set_free(xen_vgpu_record_set *set);



typedef struct xen_vgpu_record_opt_set
{
    size_t size;
    xen_vgpu_record_opt *contents[];
} xen_vgpu_record_opt_set;

/**
 * Allocate a xen_vgpu_record_opt_set of the given size.
 */
extern xen_vgpu_record_opt_set *
xen_vgpu_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vgpu_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_vgpu_record_opt_set_free(xen_vgpu_record_opt_set *set);


/**
 * Get a record containing the current state of the given VGPU.
 */
extern bool
xen_vgpu_get_record(xen_session *session, xen_vgpu_record **result, xen_vgpu vgpu);


/**
 * Get a reference to the VGPU instance with the specified UUID.
 */
extern bool
xen_vgpu_get_by_uuid(xen_session *session, xen_vgpu *result, char *uuid);


/**
 * Get the uuid field of the given VGPU.
 */
extern bool
xen_vgpu_get_uuid(xen_session *session, char **result, xen_vgpu vgpu);


/**
 * Get the VM field of the given VGPU.
 */
extern bool
xen_vgpu_get_vm(xen_session *session, xen_vm *result, xen_vgpu vgpu);


/**
 * Get the GPU_group field of the given VGPU.
 */
extern bool
xen_vgpu_get_gpu_group(xen_session *session, xen_gpu_group *result, xen_vgpu vgpu);


/**
 * Get the device field of the given VGPU.
 */
extern bool
xen_vgpu_get_device(xen_session *session, char **result, xen_vgpu vgpu);


/**
 * Get the currently_attached field of the given VGPU.
 */
extern bool
xen_vgpu_get_currently_attached(xen_session *session, bool *result, xen_vgpu vgpu);


/**
 * Get the other_config field of the given VGPU.
 */
extern bool
xen_vgpu_get_other_config(xen_session *session, xen_string_string_map **result, xen_vgpu vgpu);


/**
 * Set the other_config field of the given VGPU.
 */
extern bool
xen_vgpu_set_other_config(xen_session *session, xen_vgpu vgpu, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * VGPU.
 */
extern bool
xen_vgpu_add_to_other_config(xen_session *session, xen_vgpu vgpu, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given VGPU.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_vgpu_remove_from_other_config(xen_session *session, xen_vgpu vgpu, char *key);


/**
 * .
 */
extern bool
xen_vgpu_create(xen_session *session, xen_vgpu *result, xen_vm vm, xen_gpu_group gpu_group, char *device, xen_string_string_map *other_config);

/**
 * .
 */
extern bool
xen_vgpu_create_async(xen_session *session, xen_task *result, xen_vm vm, xen_gpu_group gpu_group, char *device, xen_string_string_map *other_config);


/**
 * .
 */
extern bool
xen_vgpu_destroy(xen_session *session, xen_vgpu self);

/**
 * .
 */
extern bool
xen_vgpu_destroy_async(xen_session *session, xen_task *result, xen_vgpu self);


/**
 * Return a list of all the VGPUs known to the system.
 */
extern bool
xen_vgpu_get_all(xen_session *session, struct xen_vgpu_set **result);


/**
 * Return a map of VGPU references to VGPU records for all VGPUs known
 * to the system.
 */
extern bool
xen_vgpu_get_all_records(xen_session *session, xen_vgpu_xen_vgpu_record_map **result);


#endif
