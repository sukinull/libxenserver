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
#include <xen/api/xen_blob.h>
#include <xen/api/xen_blob_xen_blob_record_map.h>
#include <xen/api/xen_common.h>


XEN_FREE(xen_blob)
XEN_SET_ALLOC_FREE(xen_blob)
XEN_ALLOC(xen_blob_record)
XEN_SET_ALLOC_FREE(xen_blob_record)
XEN_ALLOC(xen_blob_record_opt)
XEN_RECORD_OPT_FREE(xen_blob)
XEN_SET_ALLOC_FREE(xen_blob_record_opt)


static const struct_member xen_blob_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_blob_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_blob_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_blob_record, name_description) },
        { .key = "size",
          .type = &abstract_type_int,
          .offset = offsetof(xen_blob_record, size) },
        { .key = "public",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_blob_record, pubblic) },
        { .key = "last_updated",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_blob_record, last_updated) },
        { .key = "mime_type",
          .type = &abstract_type_string,
          .offset = offsetof(xen_blob_record, mime_type) }
    };

const abstract_type xen_blob_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_blob_record),
       .member_count =
           sizeof(xen_blob_record_struct_members) / sizeof(struct_member),
       .members = xen_blob_record_struct_members
    };


static const struct struct_member xen_blob_xen_blob_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_blob_xen_blob_record_map_contents, key)
    },
    {
        .type = &xen_blob_record_abstract_type_,
        .offset = offsetof(xen_blob_xen_blob_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_blob_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_blob_xen_blob_record_map_contents),
    .members = xen_blob_xen_blob_record_members
};


void
xen_blob_record_free(xen_blob_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    free(record->mime_type);
    free(record);
}


bool
xen_blob_get_record(xen_session *session, xen_blob_record **result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = xen_blob_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("blob.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_blob_get_by_uuid(xen_session *session, xen_blob *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("blob.get_by_uuid");
    return session->ok;
}


bool
xen_blob_get_by_name_label(xen_session *session, struct xen_blob_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("blob.get_by_name_label");
    return session->ok;
}


bool
xen_blob_get_name_label(xen_session *session, char **result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("blob.get_name_label");
    return session->ok;
}


bool
xen_blob_get_name_description(xen_session *session, char **result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("blob.get_name_description");
    return session->ok;
}


bool
xen_blob_get_size(xen_session *session, int64_t *result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("blob.get_size");
    return session->ok;
}


bool
xen_blob_get_public(xen_session *session, bool *result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("blob.get_public");
    return session->ok;
}


bool
xen_blob_get_last_updated(xen_session *session, time_t *result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("blob.get_last_updated");
    return session->ok;
}


bool
xen_blob_get_mime_type(xen_session *session, char **result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("blob.get_mime_type");
    return session->ok;
}


bool
xen_blob_set_name_label(xen_session *session, xen_blob blob, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob },
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    xen_call_(session, "blob.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_blob_set_name_description(xen_session *session, xen_blob blob, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    xen_call_(session, "blob.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_blob_set_public(xen_session *session, xen_blob blob, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    xen_call_(session, "blob.set_public", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_blob_create(xen_session *session, xen_blob *result, char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("blob.create");
    return session->ok;
}


bool
xen_blob_destroy(xen_session *session, xen_blob self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "blob.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_blob_get_all(xen_session *session, struct xen_blob_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "blob.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_blob_get_all_records(xen_session *session, xen_blob_xen_blob_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_blob_record_map;

    *result = NULL;
    xen_call_(session, "blob.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_blob_get_uuid(xen_session *session, char **result, xen_blob blob)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = blob }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("blob.get_uuid");
    return session->ok;
}

