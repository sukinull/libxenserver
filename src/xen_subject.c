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
#include <xen/api/xen_role.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_subject.h>
#include <xen/api/xen_subject_xen_subject_record_map.h>


XEN_FREE(xen_subject)
XEN_SET_ALLOC_FREE(xen_subject)
XEN_ALLOC(xen_subject_record)
XEN_SET_ALLOC_FREE(xen_subject_record)
XEN_ALLOC(xen_subject_record_opt)
XEN_RECORD_OPT_FREE(xen_subject)
XEN_SET_ALLOC_FREE(xen_subject_record_opt)


static const struct_member xen_subject_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_subject_record, uuid) },
        { .key = "subject_identifier",
          .type = &abstract_type_string,
          .offset = offsetof(xen_subject_record, subject_identifier) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_subject_record, other_config) },
        { .key = "roles",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_subject_record, roles) }
    };

const abstract_type xen_subject_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_subject_record),
       .member_count =
           sizeof(xen_subject_record_struct_members) / sizeof(struct_member),
       .members = xen_subject_record_struct_members
    };


static const struct struct_member xen_subject_xen_subject_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_subject_xen_subject_record_map_contents, key)
    },
    {
        .type = &xen_subject_record_abstract_type_,
        .offset = offsetof(xen_subject_xen_subject_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_subject_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_subject_xen_subject_record_map_contents),
    .members = xen_subject_xen_subject_record_members
};


void
xen_subject_record_free(xen_subject_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->subject_identifier);
    xen_string_string_map_free(record->other_config);
    xen_role_record_opt_set_free(record->roles);
    free(record);
}


bool
xen_subject_get_record(xen_session *session, xen_subject_record **result, xen_subject subject)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject }
        };

    abstract_type result_type = xen_subject_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("subject.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_subject_get_by_uuid(xen_session *session, xen_subject *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("subject.get_by_uuid");
    return session->ok;
}


bool
xen_subject_create(xen_session *session, xen_subject *result, xen_subject_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_subject_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("subject.create");
    return session->ok;
}

bool
xen_subject_create_async(xen_session *session, xen_task *result, xen_subject_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_subject_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.subject.create");
    return session->ok;
}

bool
xen_subject_destroy(xen_session *session, xen_subject subject)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject }
        };

    xen_call_(session, "subject.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_subject_destroy_async(xen_session *session, xen_task *result, xen_subject subject)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.subject.destroy");
    return session->ok;
}

bool
xen_subject_get_subject_identifier(xen_session *session, char **result, xen_subject subject)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("subject.get_subject_identifier");
    return session->ok;
}


bool
xen_subject_get_other_config(xen_session *session, xen_string_string_map **result, xen_subject subject)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("subject.get_other_config");
    return session->ok;
}


bool
xen_subject_get_roles(xen_session *session, struct xen_role_set **result, xen_subject subject)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("subject.get_roles");
    return session->ok;
}


bool
xen_subject_add_to_roles(xen_session *session, xen_subject self, xen_role role)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = role }
        };

    xen_call_(session, "subject.add_to_roles", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_subject_remove_from_roles(xen_session *session, xen_subject self, xen_role role)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = role }
        };

    xen_call_(session, "subject.remove_from_roles", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_subject_get_permissions_name_label(xen_session *session, struct xen_string_set **result, xen_subject self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("subject.get_permissions_name_label");
    return session->ok;
}


bool
xen_subject_get_all(xen_session *session, struct xen_subject_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "subject.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_subject_get_all_records(xen_session *session, xen_subject_xen_subject_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_subject_record_map;

    *result = NULL;
    xen_call_(session, "subject.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_subject_get_uuid(xen_session *session, char **result, xen_subject subject)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("subject.get_uuid");
    return session->ok;
}

