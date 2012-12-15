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
#include <xen/api/xen_int_float_map.h>
#include <xen/api/xen_int_int_map.h>
#include <xen/api/xen_int_string_set_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vm_metrics.h>
#include <xen/api/xen_vm_metrics_xen_vm_metrics_record_map.h>


XEN_FREE(xen_vm_metrics)
XEN_SET_ALLOC_FREE(xen_vm_metrics)
XEN_ALLOC(xen_vm_metrics_record)
XEN_SET_ALLOC_FREE(xen_vm_metrics_record)
XEN_ALLOC(xen_vm_metrics_record_opt)
XEN_RECORD_OPT_FREE(xen_vm_metrics)
XEN_SET_ALLOC_FREE(xen_vm_metrics_record_opt)


static const struct_member xen_vm_metrics_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_metrics_record, uuid) },
        { .key = "memory_actual",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_metrics_record, memory_actual) },
        { .key = "VCPUs_number",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_metrics_record, vcpus_number) },
        { .key = "VCPUs_utilisation",
          .type = &abstract_type_int_float_map,
          .offset = offsetof(xen_vm_metrics_record, vcpus_utilisation) },
        { .key = "VCPUs_CPU",
          .type = &abstract_type_int_int_map,
          .offset = offsetof(xen_vm_metrics_record, vcpus_cpu) },
        { .key = "VCPUs_params",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_metrics_record, vcpus_params) },
        { .key = "VCPUs_flags",
          .type = &abstract_type_int_string_set_map,
          .offset = offsetof(xen_vm_metrics_record, vcpus_flags) },
        { .key = "state",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_vm_metrics_record, state) },
        { .key = "start_time",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_vm_metrics_record, start_time) },
        { .key = "install_time",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_vm_metrics_record, install_time) },
        { .key = "last_updated",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_vm_metrics_record, last_updated) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_metrics_record, other_config) }
    };

const abstract_type xen_vm_metrics_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_vm_metrics_record),
       .member_count =
           sizeof(xen_vm_metrics_record_struct_members) / sizeof(struct_member),
       .members = xen_vm_metrics_record_struct_members
    };


static const struct struct_member xen_vm_metrics_xen_vm_metrics_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_vm_metrics_xen_vm_metrics_record_map_contents, key)
    },
    {
        .type = &xen_vm_metrics_record_abstract_type_,
        .offset = offsetof(xen_vm_metrics_xen_vm_metrics_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_vm_metrics_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_vm_metrics_xen_vm_metrics_record_map_contents),
    .members = xen_vm_metrics_xen_vm_metrics_record_members
};


void
xen_vm_metrics_record_free(xen_vm_metrics_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_int_float_map_free(record->vcpus_utilisation);
    xen_int_int_map_free(record->vcpus_cpu);
    xen_string_string_map_free(record->vcpus_params);
    xen_int_string_set_map_free(record->vcpus_flags);
    xen_string_set_free(record->state);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_vm_metrics_get_record(xen_session *session, xen_vm_metrics_record **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = xen_vm_metrics_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_vm_metrics_get_by_uuid(xen_session *session, xen_vm_metrics *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_by_uuid");
    return session->ok;
}


bool
xen_vm_metrics_get_memory_actual(xen_session *session, int64_t *result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM_metrics.get_memory_actual");
    return session->ok;
}


bool
xen_vm_metrics_get_vcpus_number(xen_session *session, int64_t *result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM_metrics.get_VCPUs_number");
    return session->ok;
}


bool
xen_vm_metrics_get_vcpus_utilisation(xen_session *session, xen_int_float_map **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_int_float_map;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_VCPUs_utilisation");
    return session->ok;
}


bool
xen_vm_metrics_get_vcpus_cpu(xen_session *session, xen_int_int_map **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_int_int_map;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_VCPUs_CPU");
    return session->ok;
}


bool
xen_vm_metrics_get_vcpus_params(xen_session *session, xen_string_string_map **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_VCPUs_params");
    return session->ok;
}


bool
xen_vm_metrics_get_vcpus_flags(xen_session *session, xen_int_string_set_map **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_int_string_set_map;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_VCPUs_flags");
    return session->ok;
}


bool
xen_vm_metrics_get_state(xen_session *session, struct xen_string_set **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_state");
    return session->ok;
}


bool
xen_vm_metrics_get_start_time(xen_session *session, time_t *result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("VM_metrics.get_start_time");
    return session->ok;
}


bool
xen_vm_metrics_get_install_time(xen_session *session, time_t *result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("VM_metrics.get_install_time");
    return session->ok;
}


bool
xen_vm_metrics_get_last_updated(xen_session *session, time_t *result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("VM_metrics.get_last_updated");
    return session->ok;
}


bool
xen_vm_metrics_get_other_config(xen_session *session, xen_string_string_map **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_other_config");
    return session->ok;
}


bool
xen_vm_metrics_set_other_config(xen_session *session, xen_vm_metrics vm_metrics, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "VM_metrics.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_metrics_add_to_other_config(xen_session *session, xen_vm_metrics vm_metrics, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM_metrics.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vm_metrics_remove_from_other_config(xen_session *session, xen_vm_metrics vm_metrics, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VM_metrics.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_metrics_get_all(xen_session *session, struct xen_vm_metrics_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "VM_metrics.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vm_metrics_get_all_records(xen_session *session, xen_vm_metrics_xen_vm_metrics_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_vm_metrics_record_map;

    *result = NULL;
    xen_call_(session, "VM_metrics.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vm_metrics_get_uuid(xen_session *session, char **result, xen_vm_metrics vm_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_metrics }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM_metrics.get_uuid");
    return session->ok;
}

