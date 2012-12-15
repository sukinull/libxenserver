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
#include <xen/api/xen_host_metrics.h>
#include <xen/api/xen_host_metrics_xen_host_metrics_record_map.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_host_metrics)
XEN_SET_ALLOC_FREE(xen_host_metrics)
XEN_ALLOC(xen_host_metrics_record)
XEN_SET_ALLOC_FREE(xen_host_metrics_record)
XEN_ALLOC(xen_host_metrics_record_opt)
XEN_RECORD_OPT_FREE(xen_host_metrics)
XEN_SET_ALLOC_FREE(xen_host_metrics_record_opt)


static const struct_member xen_host_metrics_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_metrics_record, uuid) },
        { .key = "memory_total",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_metrics_record, memory_total) },
        { .key = "memory_free",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_metrics_record, memory_free) },
        { .key = "live",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_host_metrics_record, live) },
        { .key = "last_updated",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_host_metrics_record, last_updated) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_metrics_record, other_config) }
    };

const abstract_type xen_host_metrics_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_host_metrics_record),
       .member_count =
           sizeof(xen_host_metrics_record_struct_members) / sizeof(struct_member),
       .members = xen_host_metrics_record_struct_members
    };


static const struct struct_member xen_host_metrics_xen_host_metrics_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_host_metrics_xen_host_metrics_record_map_contents, key)
    },
    {
        .type = &xen_host_metrics_record_abstract_type_,
        .offset = offsetof(xen_host_metrics_xen_host_metrics_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_host_metrics_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_host_metrics_xen_host_metrics_record_map_contents),
    .members = xen_host_metrics_xen_host_metrics_record_members
};


void
xen_host_metrics_record_free(xen_host_metrics_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_host_metrics_get_record(xen_session *session, xen_host_metrics_record **result, xen_host_metrics host_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics }
        };

    abstract_type result_type = xen_host_metrics_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("host_metrics.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_host_metrics_get_by_uuid(xen_session *session, xen_host_metrics *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_metrics.get_by_uuid");
    return session->ok;
}


bool
xen_host_metrics_get_memory_total(xen_session *session, int64_t *result, xen_host_metrics host_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host_metrics.get_memory_total");
    return session->ok;
}


bool
xen_host_metrics_get_memory_free(xen_session *session, int64_t *result, xen_host_metrics host_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host_metrics.get_memory_free");
    return session->ok;
}


bool
xen_host_metrics_get_live(xen_session *session, bool *result, xen_host_metrics host_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("host_metrics.get_live");
    return session->ok;
}


bool
xen_host_metrics_get_last_updated(xen_session *session, time_t *result, xen_host_metrics host_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("host_metrics.get_last_updated");
    return session->ok;
}


bool
xen_host_metrics_get_other_config(xen_session *session, xen_string_string_map **result, xen_host_metrics host_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host_metrics.get_other_config");
    return session->ok;
}


bool
xen_host_metrics_set_other_config(xen_session *session, xen_host_metrics host_metrics, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "host_metrics.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_metrics_add_to_other_config(xen_session *session, xen_host_metrics host_metrics, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "host_metrics.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_host_metrics_remove_from_other_config(xen_session *session, xen_host_metrics host_metrics, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "host_metrics.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_metrics_get_all(xen_session *session, struct xen_host_metrics_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "host_metrics.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_metrics_get_all_records(xen_session *session, xen_host_metrics_xen_host_metrics_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_host_metrics_record_map;

    *result = NULL;
    xen_call_(session, "host_metrics.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_metrics_get_uuid(xen_session *session, char **result, xen_host_metrics host_metrics)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host_metrics }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host_metrics.get_uuid");
    return session->ok;
}

