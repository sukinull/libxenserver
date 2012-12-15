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

#include "xen_cls_internal.h"
#include "xen_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_message.h>
#include <xen/api/xen_message_xen_message_record_map.h>


XEN_FREE(xen_message)
XEN_SET_ALLOC_FREE(xen_message)
XEN_ALLOC(xen_message_record)
XEN_SET_ALLOC_FREE(xen_message_record)
XEN_ALLOC(xen_message_record_opt)
XEN_RECORD_OPT_FREE(xen_message)
XEN_SET_ALLOC_FREE(xen_message_record_opt)


static const struct_member xen_message_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_message_record, uuid) },
        { .key = "name",
          .type = &abstract_type_string,
          .offset = offsetof(xen_message_record, name) },
        { .key = "priority",
          .type = &abstract_type_int,
          .offset = offsetof(xen_message_record, priority) },
        { .key = "cls",
          .type = &xen_cls_abstract_type_,
          .offset = offsetof(xen_message_record, cls) },
        { .key = "obj_uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_message_record, obj_uuid) },
        { .key = "timestamp",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_message_record, timestamp) },
        { .key = "body",
          .type = &abstract_type_string,
          .offset = offsetof(xen_message_record, body) }
    };

const abstract_type xen_message_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_message_record),
       .member_count =
           sizeof(xen_message_record_struct_members) / sizeof(struct_member),
       .members = xen_message_record_struct_members
    };


static const struct struct_member xen_message_xen_message_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_message_xen_message_record_map_contents, key)
    },
    {
        .type = &xen_message_record_abstract_type_,
        .offset = offsetof(xen_message_xen_message_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_message_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_message_xen_message_record_map_contents),
    .members = xen_message_xen_message_record_members
};


void
xen_message_record_free(xen_message_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name);
    free(record->obj_uuid);
    free(record->body);
    free(record);
}


bool
xen_message_create(xen_session *session, xen_message *result, char *name, int64_t priority, enum xen_cls cls, char *obj_uuid, char *body)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_int,
              .u.int_val = priority },
            { .type = &xen_cls_abstract_type_,
              .u.enum_val = cls },
            { .type = &abstract_type_string,
              .u.string_val = obj_uuid },
            { .type = &abstract_type_string,
              .u.string_val = body }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("message.create");
    return session->ok;
}


bool
xen_message_destroy(xen_session *session, xen_message self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "message.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_message_get_all(xen_session *session, struct xen_message_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "message.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_message_get_since(xen_session *session, xen_message_xen_message_record_map **result, time_t since)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_datetime,
              .u.datetime_val = since }
        };

    abstract_type result_type = abstract_type_string_xen_message_record_map;

    *result = NULL;
    XEN_CALL_("message.get_since");
    return session->ok;
}


bool
xen_message_get_record(xen_session *session, xen_message_record **result, xen_message self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = xen_message_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("message.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_message_get_by_uuid(xen_session *session, xen_message *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("message.get_by_uuid");
    return session->ok;
}


bool
xen_message_get_all_records(xen_session *session, xen_message_xen_message_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_message_record_map;

    *result = NULL;
    xen_call_(session, "message.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_message_get_all_records_where(xen_session *session, xen_message_xen_message_record_map **result, char *expr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = expr }
        };

    abstract_type result_type = abstract_type_string_xen_message_record_map;

    *result = NULL;
    XEN_CALL_("message.get_all_records_where");
    return session->ok;
}

