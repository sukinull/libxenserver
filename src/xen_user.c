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

#include "xen_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_user.h>


XEN_FREE(xen_user)
XEN_SET_ALLOC_FREE(xen_user)
XEN_ALLOC(xen_user_record)
XEN_SET_ALLOC_FREE(xen_user_record)
XEN_ALLOC(xen_user_record_opt)
XEN_RECORD_OPT_FREE(xen_user)
XEN_SET_ALLOC_FREE(xen_user_record_opt)


static const struct_member xen_user_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_user_record, uuid) },
        { .key = "short_name",
          .type = &abstract_type_string,
          .offset = offsetof(xen_user_record, short_name) },
        { .key = "fullname",
          .type = &abstract_type_string,
          .offset = offsetof(xen_user_record, fullname) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_user_record, other_config) }
    };

const abstract_type xen_user_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_user_record),
       .member_count =
           sizeof(xen_user_record_struct_members) / sizeof(struct_member),
       .members = xen_user_record_struct_members
    };


void
xen_user_record_free(xen_user_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->short_name);
    free(record->fullname);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_user_get_record(xen_session *session, xen_user_record **result, xen_user user)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user }
        };

    abstract_type result_type = xen_user_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("user.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_user_get_by_uuid(xen_session *session, xen_user *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("user.get_by_uuid");
    return session->ok;
}


bool
xen_user_create(xen_session *session, xen_user *result, xen_user_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_user_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("user.create");
    return session->ok;
}

bool
xen_user_create_async(xen_session *session, xen_task *result, xen_user_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_user_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.user.create");
    return session->ok;
}

bool
xen_user_destroy(xen_session *session, xen_user user)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user }
        };

    xen_call_(session, "user.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_user_destroy_async(xen_session *session, xen_task *result, xen_user user)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.user.destroy");
    return session->ok;
}

bool
xen_user_get_short_name(xen_session *session, char **result, xen_user user)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("user.get_short_name");
    return session->ok;
}


bool
xen_user_get_fullname(xen_session *session, char **result, xen_user user)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("user.get_fullname");
    return session->ok;
}


bool
xen_user_get_other_config(xen_session *session, xen_string_string_map **result, xen_user user)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("user.get_other_config");
    return session->ok;
}


bool
xen_user_set_fullname(xen_session *session, xen_user user, char *fullname)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user },
            { .type = &abstract_type_string,
              .u.string_val = fullname }
        };

    xen_call_(session, "user.set_fullname", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_user_set_other_config(xen_session *session, xen_user user, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "user.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_user_add_to_other_config(xen_session *session, xen_user user, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "user.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_user_remove_from_other_config(xen_session *session, xen_user user, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "user.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_user_get_uuid(xen_session *session, char **result, xen_user user)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = user }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("user.get_uuid");
    return session->ok;
}

