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


#ifndef XEN_TASK_STATUS_TYPE_H
#define XEN_TASK_STATUS_TYPE_H


#include <xen/api/xen_common.h>


enum xen_task_status_type
{
    /**
     * task is in progress
     */
    XEN_TASK_STATUS_TYPE_PENDING,

    /**
     * task was completed successfully
     */
    XEN_TASK_STATUS_TYPE_SUCCESS,

    /**
     * task has failed
     */
    XEN_TASK_STATUS_TYPE_FAILURE,

    /**
     * task is being cancelled
     */
    XEN_TASK_STATUS_TYPE_CANCELLING,

    /**
     * task has been cancelled
     */
    XEN_TASK_STATUS_TYPE_CANCELLED,

    /**
     * Unknown to this version of the bindings.
     */
    XEN_TASK_STATUS_TYPE_UNDEFINED
};


typedef struct xen_task_status_type_set
{
    size_t size;
    enum xen_task_status_type contents[];
} xen_task_status_type_set;

/**
 * Allocate a xen_task_status_type_set of the given size.
 */
extern xen_task_status_type_set *
xen_task_status_type_set_alloc(size_t size);

/**
 * Free the given xen_task_status_type_set.  The given set must have
 * been allocated by this library.
 */
extern void
xen_task_status_type_set_free(xen_task_status_type_set *set);


/**
 * Return the name corresponding to the given code.  This string must
 * not be modified or freed.
 */
extern const char *
xen_task_status_type_to_string(enum xen_task_status_type val);


/**
 * Return the correct code for the given string, or set the session
 * object to failure and return an undefined value if the given string does
 * not match a known code.
 */
extern enum xen_task_status_type
xen_task_status_type_from_string(xen_session *session, const char *str);


#endif
