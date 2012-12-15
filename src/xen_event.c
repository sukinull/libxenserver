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



#include <stddef.h>
#include <stdlib.h>

#include "xen_event_operation_internal.h"
#include "xen_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_event.h>


XEN_ALLOC(xen_event_record)
XEN_SET_ALLOC_FREE(xen_event_record)


static const struct_member xen_event_record_struct_members[] =
    {
        { .key = "id",
          .type = &abstract_type_int,
          .offset = offsetof(xen_event_record, id) },
        { .key = "timestamp",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_event_record, timestamp) },
        { .key = "class",
          .type = &abstract_type_string,
          .offset = offsetof(xen_event_record, XEN_CLAZZ) },
        { .key = "operation",
          .type = &xen_event_operation_abstract_type_,
          .offset = offsetof(xen_event_record, operation) },
        { .key = "ref",
          .type = &abstract_type_string,
          .offset = offsetof(xen_event_record, ref) },
    };

const abstract_type xen_event_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_event_record),
       .member_count =
           sizeof(xen_event_record_struct_members) / sizeof(struct_member),
       .members = xen_event_record_struct_members
    };


const abstract_type xen_event_record_set_abstract_type_ =
    {
       .typename = SET,
        .child = &xen_event_record_abstract_type_
    };


void
xen_event_record_free(xen_event_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->XEN_CLAZZ);
    free(record->ref);
    free(record->obj_uuid);
    free(record);
}


bool
xen_event_register(xen_session *session, struct xen_string_set *classes)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)classes }
        };

    xen_call_(session, "event.register", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_event_register_async(xen_session *session, xen_task *result, struct xen_string_set *classes)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)classes }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.event.register");
    return session->ok;
}

bool
xen_event_unregister(xen_session *session, struct xen_string_set *classes)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)classes }
        };

    xen_call_(session, "event.unregister", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_event_unregister_async(xen_session *session, xen_task *result, struct xen_string_set *classes)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)classes }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.event.unregister");
    return session->ok;
}

bool
xen_event_next(xen_session *session, struct xen_event_record_set **result)
{

    abstract_type result_type = xen_event_record_set_abstract_type_;

    *result = NULL;
    xen_call_(session, "event.next", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_event_from(xen_session *session, struct xen_event_record_set **result, struct xen_string_set *classes, char *token, double timeout)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)classes },
            { .type = &abstract_type_string,
              .u.string_val = token },
            { .type = &abstract_type_float,
              .u.float_val = timeout }
        };

    abstract_type result_type = xen_event_record_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("event.from");
    return session->ok;
}


bool
xen_event_get_current_id(xen_session *session, int64_t *result)
{

    abstract_type result_type = abstract_type_int;

    xen_call_(session, "event.get_current_id", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_event_inject(xen_session *session, char **result, char *XEN_CLAZZ, char *ref)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = XEN_CLAZZ },
            { .type = &abstract_type_string,
              .u.string_val = ref }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("event.inject");
    return session->ok;
}

