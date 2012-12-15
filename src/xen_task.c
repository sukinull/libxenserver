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
#include "xen_string_task_allowed_operations_map_internal.h"
#include "xen_task_allowed_operations_internal.h"
#include "xen_task_status_type_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_host.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_task_allowed_operations_map.h>
#include <xen/api/xen_task.h>
#include <xen/api/xen_task_allowed_operations.h>
#include <xen/api/xen_task_xen_task_record_map.h>


XEN_FREE(xen_task)
XEN_SET_ALLOC_FREE(xen_task)
XEN_ALLOC(xen_task_record)
XEN_SET_ALLOC_FREE(xen_task_record)
XEN_ALLOC(xen_task_record_opt)
XEN_RECORD_OPT_FREE(xen_task)
XEN_SET_ALLOC_FREE(xen_task_record_opt)


static const struct_member xen_task_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_task_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_task_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_task_record, name_description) },
        { .key = "allowed_operations",
          .type = &xen_task_allowed_operations_set_abstract_type_,
          .offset = offsetof(xen_task_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_task_allowed_operations_map_abstract_type_,
          .offset = offsetof(xen_task_record, current_operations) },
        { .key = "created",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_task_record, created) },
        { .key = "finished",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_task_record, finished) },
        { .key = "status",
          .type = &xen_task_status_type_abstract_type_,
          .offset = offsetof(xen_task_record, status) },
        { .key = "resident_on",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_task_record, resident_on) },
        { .key = "progress",
          .type = &abstract_type_float,
          .offset = offsetof(xen_task_record, progress) },
        { .key = "type",
          .type = &abstract_type_string,
          .offset = offsetof(xen_task_record, type) },
        { .key = "result",
          .type = &abstract_type_string,
          .offset = offsetof(xen_task_record, result) },
        { .key = "error_info",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_task_record, error_info) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_task_record, other_config) },
        { .key = "subtask_of",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_task_record, subtask_of) },
        { .key = "subtasks",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_task_record, subtasks) }
    };

const abstract_type xen_task_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_task_record),
       .member_count =
           sizeof(xen_task_record_struct_members) / sizeof(struct_member),
       .members = xen_task_record_struct_members
    };


static const struct struct_member xen_task_xen_task_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_task_xen_task_record_map_contents, key)
    },
    {
        .type = &xen_task_record_abstract_type_,
        .offset = offsetof(xen_task_xen_task_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_task_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_task_xen_task_record_map_contents),
    .members = xen_task_xen_task_record_members
};


void
xen_task_record_free(xen_task_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_task_allowed_operations_set_free(record->allowed_operations);
    xen_string_task_allowed_operations_map_free(record->current_operations);
    xen_host_record_opt_free(record->resident_on);
    free(record->type);
    free(record->result);
    xen_string_set_free(record->error_info);
    xen_string_string_map_free(record->other_config);
    xen_task_record_opt_free(record->subtask_of);
    xen_task_record_opt_set_free(record->subtasks);
    free(record);
}


bool
xen_task_get_record(xen_session *session, xen_task_record **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = xen_task_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("task.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_task_get_by_uuid(xen_session *session, xen_task *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_by_uuid");
    return session->ok;
}


bool
xen_task_get_by_name_label(xen_session *session, struct xen_task_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("task.get_by_name_label");
    return session->ok;
}


bool
xen_task_get_name_label(xen_session *session, char **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_name_label");
    return session->ok;
}


bool
xen_task_get_name_description(xen_session *session, char **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_name_description");
    return session->ok;
}


bool
xen_task_get_allowed_operations(xen_session *session, struct xen_task_allowed_operations_set **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = xen_task_allowed_operations_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("task.get_allowed_operations");
    return session->ok;
}


bool
xen_task_get_current_operations(xen_session *session, xen_string_task_allowed_operations_map **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = string_task_allowed_operations_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("task.get_current_operations");
    return session->ok;
}


bool
xen_task_get_created(xen_session *session, time_t *result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("task.get_created");
    return session->ok;
}


bool
xen_task_get_finished(xen_session *session, time_t *result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("task.get_finished");
    return session->ok;
}


bool
xen_task_get_status(xen_session *session, enum xen_task_status_type *result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = xen_task_status_type_abstract_type_;
    XEN_CALL_("task.get_status");
    return session->ok;
}


bool
xen_task_get_resident_on(xen_session *session, xen_host *result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_resident_on");
    return session->ok;
}


bool
xen_task_get_progress(xen_session *session, double *result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_float;

    XEN_CALL_("task.get_progress");
    return session->ok;
}


bool
xen_task_get_type(xen_session *session, char **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_type");
    return session->ok;
}


bool
xen_task_get_result(xen_session *session, char **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_result");
    return session->ok;
}


bool
xen_task_get_error_info(xen_session *session, struct xen_string_set **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("task.get_error_info");
    return session->ok;
}


bool
xen_task_get_other_config(xen_session *session, xen_string_string_map **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("task.get_other_config");
    return session->ok;
}


bool
xen_task_get_subtask_of(xen_session *session, xen_task *result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_subtask_of");
    return session->ok;
}


bool
xen_task_get_subtasks(xen_session *session, struct xen_task_set **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("task.get_subtasks");
    return session->ok;
}


bool
xen_task_set_other_config(xen_session *session, xen_task task, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "task.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_task_add_to_other_config(xen_session *session, xen_task task, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "task.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_task_remove_from_other_config(xen_session *session, xen_task task, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "task.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_task_create(xen_session *session, xen_task *result, char *label, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.create");
    return session->ok;
}


bool
xen_task_destroy(xen_session *session, xen_task self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "task.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_task_cancel(xen_session *session, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    xen_call_(session, "task.cancel", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_task_cancel_async(xen_session *session, xen_task *result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.task.cancel");
    return session->ok;
}

bool
xen_task_get_all(xen_session *session, struct xen_task_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "task.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_task_get_all_records(xen_session *session, xen_task_xen_task_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_task_record_map;

    *result = NULL;
    xen_call_(session, "task.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_task_get_uuid(xen_session *session, char **result, xen_task task)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = task }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("task.get_uuid");
    return session->ok;
}

