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


#ifndef XEN_MESSAGE_H
#define XEN_MESSAGE_H

#include <xen/api/xen_cls.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_message_decl.h>
#include <xen/api/xen_message_xen_message_record_map.h>


/*
 * The message class.
 * 
 * An message for the attention of the administrator.
 */


/**
 * Free the given xen_message.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_message_free(xen_message message);


typedef struct xen_message_set
{
    size_t size;
    xen_message *contents[];
} xen_message_set;

/**
 * Allocate a xen_message_set of the given size.
 */
extern xen_message_set *
xen_message_set_alloc(size_t size);

/**
 * Free the given xen_message_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_message_set_free(xen_message_set *set);


typedef struct xen_message_record
{
    xen_message handle;
    char *uuid;
    char *name;
    int64_t priority;
    enum xen_cls cls;
    char *obj_uuid;
    time_t timestamp;
    char *body;
} xen_message_record;

/**
 * Allocate a xen_message_record.
 */
extern xen_message_record *
xen_message_record_alloc(void);

/**
 * Free the given xen_message_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_message_record_free(xen_message_record *record);


typedef struct xen_message_record_opt
{
    bool is_record;
    union
    {
        xen_message handle;
        xen_message_record *record;
    } u;
} xen_message_record_opt;

/**
 * Allocate a xen_message_record_opt.
 */
extern xen_message_record_opt *
xen_message_record_opt_alloc(void);

/**
 * Free the given xen_message_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_message_record_opt_free(xen_message_record_opt *record_opt);


typedef struct xen_message_record_set
{
    size_t size;
    xen_message_record *contents[];
} xen_message_record_set;

/**
 * Allocate a xen_message_record_set of the given size.
 */
extern xen_message_record_set *
xen_message_record_set_alloc(size_t size);

/**
 * Free the given xen_message_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_message_record_set_free(xen_message_record_set *set);



typedef struct xen_message_record_opt_set
{
    size_t size;
    xen_message_record_opt *contents[];
} xen_message_record_opt_set;

/**
 * Allocate a xen_message_record_opt_set of the given size.
 */
extern xen_message_record_opt_set *
xen_message_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_message_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_message_record_opt_set_free(xen_message_record_opt_set *set);


/**
 * .
 */
extern bool
xen_message_create(xen_session *session, xen_message *result, char *name, int64_t priority, enum xen_cls cls, char *obj_uuid, char *body);


/**
 * .
 */
extern bool
xen_message_destroy(xen_session *session, xen_message self);


/**
 * .
 */
extern bool
xen_message_get_all(xen_session *session, struct xen_message_set **result);


/**
 * .
 */
extern bool
xen_message_get_since(xen_session *session, xen_message_xen_message_record_map **result, time_t since);


/**
 * .
 */
extern bool
xen_message_get_record(xen_session *session, xen_message_record **result, xen_message self);


/**
 * .
 */
extern bool
xen_message_get_by_uuid(xen_session *session, xen_message *result, char *uuid);


/**
 * .
 */
extern bool
xen_message_get_all_records(xen_session *session, xen_message_xen_message_record_map **result);


/**
 * .
 */
extern bool
xen_message_get_all_records_where(xen_session *session, xen_message_xen_message_record_map **result, char *expr);


#endif
