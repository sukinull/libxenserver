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
#include <xen/api/xen_role_xen_role_record_map.h>


XEN_FREE(xen_role)
XEN_SET_ALLOC_FREE(xen_role)
XEN_ALLOC(xen_role_record)
XEN_SET_ALLOC_FREE(xen_role_record)
XEN_ALLOC(xen_role_record_opt)
XEN_RECORD_OPT_FREE(xen_role)
XEN_SET_ALLOC_FREE(xen_role_record_opt)


static const struct_member xen_role_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_role_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_role_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_role_record, name_description) },
        { .key = "subroles",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_role_record, subroles) }
    };

const abstract_type xen_role_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_role_record),
       .member_count =
           sizeof(xen_role_record_struct_members) / sizeof(struct_member),
       .members = xen_role_record_struct_members
    };


static const struct struct_member xen_role_xen_role_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_role_xen_role_record_map_contents, key)
    },
    {
        .type = &xen_role_record_abstract_type_,
        .offset = offsetof(xen_role_xen_role_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_role_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_role_xen_role_record_map_contents),
    .members = xen_role_xen_role_record_members
};


void
xen_role_record_free(xen_role_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_role_record_opt_set_free(record->subroles);
    free(record);
}


bool
xen_role_get_record(xen_session *session, xen_role_record **result, xen_role role)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = role }
        };

    abstract_type result_type = xen_role_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("role.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_role_get_by_uuid(xen_session *session, xen_role *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("role.get_by_uuid");
    return session->ok;
}


bool
xen_role_get_by_name_label(xen_session *session, struct xen_role_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("role.get_by_name_label");
    return session->ok;
}


bool
xen_role_get_name_label(xen_session *session, char **result, xen_role role)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = role }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("role.get_name_label");
    return session->ok;
}


bool
xen_role_get_name_description(xen_session *session, char **result, xen_role role)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = role }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("role.get_name_description");
    return session->ok;
}


bool
xen_role_get_subroles(xen_session *session, struct xen_role_set **result, xen_role role)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = role }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("role.get_subroles");
    return session->ok;
}


bool
xen_role_get_permissions(xen_session *session, struct xen_role_set **result, xen_role self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("role.get_permissions");
    return session->ok;
}


bool
xen_role_get_permissions_name_label(xen_session *session, struct xen_string_set **result, xen_role self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("role.get_permissions_name_label");
    return session->ok;
}


bool
xen_role_get_by_permission(xen_session *session, struct xen_role_set **result, xen_role permission)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = permission }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("role.get_by_permission");
    return session->ok;
}


bool
xen_role_get_by_permission_name_label(xen_session *session, struct xen_role_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("role.get_by_permission_name_label");
    return session->ok;
}


bool
xen_role_get_all(xen_session *session, struct xen_role_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "role.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_role_get_all_records(xen_session *session, xen_role_xen_role_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_role_record_map;

    *result = NULL;
    xen_call_(session, "role.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_role_get_uuid(xen_session *session, char **result, xen_role role)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = role }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("role.get_uuid");
    return session->ok;
}

