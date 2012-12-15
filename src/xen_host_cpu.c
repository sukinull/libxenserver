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
#include <xen/api/xen_host.h>
#include <xen/api/xen_host_cpu.h>
#include <xen/api/xen_host_cpu_xen_host_cpu_record_map.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_host_cpu)
XEN_SET_ALLOC_FREE(xen_host_cpu)
XEN_ALLOC(xen_host_cpu_record)
XEN_SET_ALLOC_FREE(xen_host_cpu_record)
XEN_ALLOC(xen_host_cpu_record_opt)
XEN_RECORD_OPT_FREE(xen_host_cpu)
XEN_SET_ALLOC_FREE(xen_host_cpu_record_opt)


static const struct_member xen_host_cpu_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_cpu_record, uuid) },
        { .key = "host",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_host_cpu_record, host) },
        { .key = "number",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_cpu_record, number) },
        { .key = "vendor",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_cpu_record, vendor) },
        { .key = "speed",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_cpu_record, speed) },
        { .key = "modelname",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_cpu_record, modelname) },
        { .key = "family",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_cpu_record, family) },
        { .key = "model",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_cpu_record, model) },
        { .key = "stepping",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_cpu_record, stepping) },
        { .key = "flags",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_cpu_record, flags) },
        { .key = "features",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_cpu_record, features) },
        { .key = "utilisation",
          .type = &abstract_type_float,
          .offset = offsetof(xen_host_cpu_record, utilisation) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_cpu_record, other_config) }
    };

const abstract_type xen_host_cpu_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_host_cpu_record),
       .member_count =
           sizeof(xen_host_cpu_record_struct_members) / sizeof(struct_member),
       .members = xen_host_cpu_record_struct_members
    };


static const struct struct_member xen_host_cpu_xen_host_cpu_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_host_cpu_xen_host_cpu_record_map_contents, key)
    },
    {
        .type = &xen_host_cpu_record_abstract_type_,
        .offset = offsetof(xen_host_cpu_xen_host_cpu_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_host_cpu_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_host_cpu_xen_host_cpu_record_map_contents),
    .members = xen_host_cpu_xen_host_cpu_record_members
};


void
xen_host_cpu_record_free(xen_host_cpu_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_host_record_opt_free(record->host);
    free(record->vendor);
    free(record->modelname);
    free(record->stepping);
    free(record->flags);
    free(record->features);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_host_cpu_get_record(xen_session *session, xen_host_cpu_record **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = xen_host_cpu_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("host_cpu.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_host_cpu_get_by_uuid(xen_session *session, xen_host_cpu *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_by_uuid");
    return session->ok;
}


bool
xen_host_cpu_get_host(xen_session *session, xen_host *result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_host");
    return session->ok;
}


bool
xen_host_cpu_get_number(xen_session *session, int64_t *result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host_cpu.get_number");
    return session->ok;
}


bool
xen_host_cpu_get_vendor(xen_session *session, char **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_vendor");
    return session->ok;
}


bool
xen_host_cpu_get_speed(xen_session *session, int64_t *result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host_cpu.get_speed");
    return session->ok;
}


bool
xen_host_cpu_get_modelname(xen_session *session, char **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_modelname");
    return session->ok;
}


bool
xen_host_cpu_get_family(xen_session *session, int64_t *result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host_cpu.get_family");
    return session->ok;
}


bool
xen_host_cpu_get_model(xen_session *session, int64_t *result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host_cpu.get_model");
    return session->ok;
}


bool
xen_host_cpu_get_stepping(xen_session *session, char **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_stepping");
    return session->ok;
}


bool
xen_host_cpu_get_flags(xen_session *session, char **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_flags");
    return session->ok;
}


bool
xen_host_cpu_get_features(xen_session *session, char **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_features");
    return session->ok;
}


bool
xen_host_cpu_get_utilisation(xen_session *session, double *result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_float;

    XEN_CALL_("host_cpu.get_utilisation");
    return session->ok;
}


bool
xen_host_cpu_get_other_config(xen_session *session, xen_string_string_map **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host_cpu.get_other_config");
    return session->ok;
}


bool
xen_host_cpu_set_other_config(xen_session *session, xen_host_cpu host_cpu, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "host_cpu.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_cpu_add_to_other_config(xen_session *session, xen_host_cpu host_cpu, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "host_cpu.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_host_cpu_remove_from_other_config(xen_session *session, xen_host_cpu host_cpu, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "host_cpu.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_cpu_get_all(xen_session *session, struct xen_host_cpu_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "host_cpu.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_cpu_get_all_records(xen_session *session, xen_host_cpu_xen_host_cpu_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_host_cpu_record_map;

    *result = NULL;
    xen_call_(session, "host_cpu.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_cpu_get_uuid(xen_session *session, char **result, xen_host_cpu host_cpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_cpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_cpu.get_uuid");
    return session->ok;
}

