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


#ifndef XEN_EVENT_OPERATION_H
#define XEN_EVENT_OPERATION_H


#include <xen/api/xen_common.h>


enum xen_event_operation
{
    /**
     * An object has been created
     */
    XEN_EVENT_OPERATION_ADD,

    /**
     * An object has been deleted
     */
    XEN_EVENT_OPERATION_DEL,

    /**
     * An object has been modified
     */
    XEN_EVENT_OPERATION_MOD,

    /**
     * Unknown to this version of the bindings.
     */
    XEN_EVENT_OPERATION_UNDEFINED
};


typedef struct xen_event_operation_set
{
    size_t size;
    enum xen_event_operation contents[];
} xen_event_operation_set;

/**
 * Allocate a xen_event_operation_set of the given size.
 */
extern xen_event_operation_set *
xen_event_operation_set_alloc(size_t size);

/**
 * Free the given xen_event_operation_set.  The given set must have
 * been allocated by this library.
 */
extern void
xen_event_operation_set_free(xen_event_operation_set *set);


/**
 * Return the name corresponding to the given code.  This string must
 * not be modified or freed.
 */
extern const char *
xen_event_operation_to_string(enum xen_event_operation val);


/**
 * Return the correct code for the given string, or set the session
 * object to failure and return an undefined value if the given string does
 * not match a known code.
 */
extern enum xen_event_operation
xen_event_operation_from_string(xen_session *session, const char *str);


#endif
