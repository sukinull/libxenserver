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


#ifndef XEN_VTPM_H
#define XEN_VTPM_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vm_decl.h>
#include <xen/api/xen_vtpm_decl.h>


/*
 * The VTPM class.
 * 
 * A virtual TPM device.
 */


/**
 * Free the given xen_vtpm.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_vtpm_free(xen_vtpm vtpm);


typedef struct xen_vtpm_set
{
    size_t size;
    xen_vtpm *contents[];
} xen_vtpm_set;

/**
 * Allocate a xen_vtpm_set of the given size.
 */
extern xen_vtpm_set *
xen_vtpm_set_alloc(size_t size);

/**
 * Free the given xen_vtpm_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_vtpm_set_free(xen_vtpm_set *set);


typedef struct xen_vtpm_record
{
    xen_vtpm handle;
    char *uuid;
    struct xen_vm_record_opt *vm;
    struct xen_vm_record_opt *backend;
} xen_vtpm_record;

/**
 * Allocate a xen_vtpm_record.
 */
extern xen_vtpm_record *
xen_vtpm_record_alloc(void);

/**
 * Free the given xen_vtpm_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_vtpm_record_free(xen_vtpm_record *record);


typedef struct xen_vtpm_record_opt
{
    bool is_record;
    union
    {
        xen_vtpm handle;
        xen_vtpm_record *record;
    } u;
} xen_vtpm_record_opt;

/**
 * Allocate a xen_vtpm_record_opt.
 */
extern xen_vtpm_record_opt *
xen_vtpm_record_opt_alloc(void);

/**
 * Free the given xen_vtpm_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_vtpm_record_opt_free(xen_vtpm_record_opt *record_opt);


typedef struct xen_vtpm_record_set
{
    size_t size;
    xen_vtpm_record *contents[];
} xen_vtpm_record_set;

/**
 * Allocate a xen_vtpm_record_set of the given size.
 */
extern xen_vtpm_record_set *
xen_vtpm_record_set_alloc(size_t size);

/**
 * Free the given xen_vtpm_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_vtpm_record_set_free(xen_vtpm_record_set *set);



typedef struct xen_vtpm_record_opt_set
{
    size_t size;
    xen_vtpm_record_opt *contents[];
} xen_vtpm_record_opt_set;

/**
 * Allocate a xen_vtpm_record_opt_set of the given size.
 */
extern xen_vtpm_record_opt_set *
xen_vtpm_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vtpm_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_vtpm_record_opt_set_free(xen_vtpm_record_opt_set *set);


/**
 * Get a record containing the current state of the given VTPM.
 */
extern bool
xen_vtpm_get_record(xen_session *session, xen_vtpm_record **result, xen_vtpm vtpm);


/**
 * Get a reference to the VTPM instance with the specified UUID.
 */
extern bool
xen_vtpm_get_by_uuid(xen_session *session, xen_vtpm *result, char *uuid);


/**
 * Create a new VTPM instance, and return its handle.
 */
extern bool
xen_vtpm_create(xen_session *session, xen_vtpm *result, xen_vtpm_record *record);

/**
 * Create a new VTPM instance, and return its handle.
 */
extern bool
xen_vtpm_create_async(xen_session *session, xen_task *result, xen_vtpm_record *record);


/**
 * Destroy the specified VTPM instance.
 */
extern bool
xen_vtpm_destroy(xen_session *session, xen_vtpm vtpm);

/**
 * Destroy the specified VTPM instance.
 */
extern bool
xen_vtpm_destroy_async(xen_session *session, xen_task *result, xen_vtpm vtpm);


/**
 * Get the uuid field of the given VTPM.
 */
extern bool
xen_vtpm_get_uuid(xen_session *session, char **result, xen_vtpm vtpm);


/**
 * Get the VM field of the given VTPM.
 */
extern bool
xen_vtpm_get_vm(xen_session *session, xen_vm *result, xen_vtpm vtpm);


/**
 * Get the backend field of the given VTPM.
 */
extern bool
xen_vtpm_get_backend(xen_session *session, xen_vm *result, xen_vtpm vtpm);


#endif
