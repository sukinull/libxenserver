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
#include <xen/api/xen_sm.h>
#include <xen/api/xen_sm_xen_sm_record_map.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_sm)
XEN_SET_ALLOC_FREE(xen_sm)
XEN_ALLOC(xen_sm_record)
XEN_SET_ALLOC_FREE(xen_sm_record)
XEN_ALLOC(xen_sm_record_opt)
XEN_RECORD_OPT_FREE(xen_sm)
XEN_SET_ALLOC_FREE(xen_sm_record_opt)


static const struct_member xen_sm_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, name_description) },
        { .key = "type",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, type) },
        { .key = "vendor",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, vendor) },
        { .key = "copyright",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, copyright) },
        { .key = "version",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, version) },
        { .key = "required_api_version",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, required_api_version) },
        { .key = "configuration",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_sm_record, configuration) },
        { .key = "capabilities",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_sm_record, capabilities) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_sm_record, other_config) },
        { .key = "driver_filename",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sm_record, driver_filename) }
    };

const abstract_type xen_sm_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_sm_record),
       .member_count =
           sizeof(xen_sm_record_struct_members) / sizeof(struct_member),
       .members = xen_sm_record_struct_members
    };


static const struct struct_member xen_sm_xen_sm_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_sm_xen_sm_record_map_contents, key)
    },
    {
        .type = &xen_sm_record_abstract_type_,
        .offset = offsetof(xen_sm_xen_sm_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_sm_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_sm_xen_sm_record_map_contents),
    .members = xen_sm_xen_sm_record_members
};


void
xen_sm_record_free(xen_sm_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    free(record->type);
    free(record->vendor);
    free(record->copyright);
    free(record->version);
    free(record->required_api_version);
    xen_string_string_map_free(record->configuration);
    xen_string_set_free(record->capabilities);
    xen_string_string_map_free(record->other_config);
    free(record->driver_filename);
    free(record);
}


bool
xen_sm_get_record(xen_session *session, xen_sm_record **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = xen_sm_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("SM.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_sm_get_by_uuid(xen_session *session, xen_sm *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_by_uuid");
    return session->ok;
}


bool
xen_sm_get_by_name_label(xen_session *session, struct xen_sm_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("SM.get_by_name_label");
    return session->ok;
}


bool
xen_sm_get_name_label(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_name_label");
    return session->ok;
}


bool
xen_sm_get_name_description(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_name_description");
    return session->ok;
}


bool
xen_sm_get_type(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_type");
    return session->ok;
}


bool
xen_sm_get_vendor(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_vendor");
    return session->ok;
}


bool
xen_sm_get_copyright(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_copyright");
    return session->ok;
}


bool
xen_sm_get_version(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_version");
    return session->ok;
}


bool
xen_sm_get_required_api_version(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_required_api_version");
    return session->ok;
}


bool
xen_sm_get_configuration(xen_session *session, xen_string_string_map **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("SM.get_configuration");
    return session->ok;
}


bool
xen_sm_get_capabilities(xen_session *session, struct xen_string_set **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("SM.get_capabilities");
    return session->ok;
}


bool
xen_sm_get_other_config(xen_session *session, xen_string_string_map **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("SM.get_other_config");
    return session->ok;
}


bool
xen_sm_get_driver_filename(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_driver_filename");
    return session->ok;
}


bool
xen_sm_set_other_config(xen_session *session, xen_sm sm, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "SM.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sm_add_to_other_config(xen_session *session, xen_sm sm, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "SM.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_sm_remove_from_other_config(xen_session *session, xen_sm sm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "SM.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sm_get_all(xen_session *session, struct xen_sm_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "SM.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_sm_get_all_records(xen_session *session, xen_sm_xen_sm_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_sm_record_map;

    *result = NULL;
    xen_call_(session, "SM.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_sm_get_uuid(xen_session *session, char **result, xen_sm sm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SM.get_uuid");
    return session->ok;
}

