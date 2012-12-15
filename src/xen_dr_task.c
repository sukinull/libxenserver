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
#include <xen/api/xen_dr_task.h>
#include <xen/api/xen_dr_task_xen_dr_task_record_map.h>
#include <xen/api/xen_sr.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_dr_task)
XEN_SET_ALLOC_FREE(xen_dr_task)
XEN_ALLOC(xen_dr_task_record)
XEN_SET_ALLOC_FREE(xen_dr_task_record)
XEN_ALLOC(xen_dr_task_record_opt)
XEN_RECORD_OPT_FREE(xen_dr_task)
XEN_SET_ALLOC_FREE(xen_dr_task_record_opt)


static const struct_member xen_dr_task_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_dr_task_record, uuid) },
        { .key = "introduced_SRs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_dr_task_record, introduced_srs) }
    };

const abstract_type xen_dr_task_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_dr_task_record),
       .member_count =
           sizeof(xen_dr_task_record_struct_members) / sizeof(struct_member),
       .members = xen_dr_task_record_struct_members
    };


static const struct struct_member xen_dr_task_xen_dr_task_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_dr_task_xen_dr_task_record_map_contents, key)
    },
    {
        .type = &xen_dr_task_record_abstract_type_,
        .offset = offsetof(xen_dr_task_xen_dr_task_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_dr_task_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_dr_task_xen_dr_task_record_map_contents),
    .members = xen_dr_task_xen_dr_task_record_members
};


void
xen_dr_task_record_free(xen_dr_task_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_sr_record_opt_set_free(record->introduced_srs);
    free(record);
}


bool
xen_dr_task_get_record(xen_session *session, xen_dr_task_record **result, xen_dr_task dr_task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = dr_task }
        };

    abstract_type result_type = xen_dr_task_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("DR_task.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_dr_task_get_by_uuid(xen_session *session, xen_dr_task *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("DR_task.get_by_uuid");
    return session->ok;
}


bool
xen_dr_task_get_introduced_srs(xen_session *session, struct xen_sr_set **result, xen_dr_task dr_task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = dr_task }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("DR_task.get_introduced_SRs");
    return session->ok;
}


bool
xen_dr_task_create(xen_session *session, xen_dr_task *result, char *type, xen_string_string_map *device_config, struct xen_string_set *whitelist)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)whitelist }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("DR_task.create");
    return session->ok;
}

bool
xen_dr_task_create_async(xen_session *session, xen_task *result, char *type, xen_string_string_map *device_config, struct xen_string_set *whitelist)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)whitelist }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.DR_task.create");
    return session->ok;
}

bool
xen_dr_task_destroy(xen_session *session, xen_dr_task self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "DR_task.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_dr_task_destroy_async(xen_session *session, xen_task *result, xen_dr_task self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.DR_task.destroy");
    return session->ok;
}

bool
xen_dr_task_get_all(xen_session *session, struct xen_dr_task_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "DR_task.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_dr_task_get_all_records(xen_session *session, xen_dr_task_xen_dr_task_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_dr_task_record_map;

    *result = NULL;
    xen_call_(session, "DR_task.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_dr_task_get_uuid(xen_session *session, char **result, xen_dr_task dr_task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = dr_task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("DR_task.get_uuid");
    return session->ok;
}

