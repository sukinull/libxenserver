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
#include "xen_vmpp_archive_frequency_internal.h"
#include "xen_vmpp_archive_target_type_internal.h"
#include "xen_vmpp_backup_frequency_internal.h"
#include "xen_vmpp_backup_type_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vm.h>
#include <xen/api/xen_vmpp.h>
#include <xen/api/xen_vmpp_xen_vmpp_record_map.h>


XEN_FREE(xen_vmpp)
XEN_SET_ALLOC_FREE(xen_vmpp)
XEN_ALLOC(xen_vmpp_record)
XEN_SET_ALLOC_FREE(xen_vmpp_record)
XEN_ALLOC(xen_vmpp_record_opt)
XEN_RECORD_OPT_FREE(xen_vmpp)
XEN_SET_ALLOC_FREE(xen_vmpp_record_opt)


static const struct_member xen_vmpp_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vmpp_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vmpp_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vmpp_record, name_description) },
        { .key = "is_policy_enabled",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vmpp_record, is_policy_enabled) },
        { .key = "backup_type",
          .type = &xen_vmpp_backup_type_abstract_type_,
          .offset = offsetof(xen_vmpp_record, backup_type) },
        { .key = "backup_retention_value",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vmpp_record, backup_retention_value) },
        { .key = "backup_frequency",
          .type = &xen_vmpp_backup_frequency_abstract_type_,
          .offset = offsetof(xen_vmpp_record, backup_frequency) },
        { .key = "backup_schedule",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vmpp_record, backup_schedule) },
        { .key = "is_backup_running",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vmpp_record, is_backup_running) },
        { .key = "backup_last_run_time",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_vmpp_record, backup_last_run_time) },
        { .key = "archive_target_type",
          .type = &xen_vmpp_archive_target_type_abstract_type_,
          .offset = offsetof(xen_vmpp_record, archive_target_type) },
        { .key = "archive_target_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vmpp_record, archive_target_config) },
        { .key = "archive_frequency",
          .type = &xen_vmpp_archive_frequency_abstract_type_,
          .offset = offsetof(xen_vmpp_record, archive_frequency) },
        { .key = "archive_schedule",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vmpp_record, archive_schedule) },
        { .key = "is_archive_running",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vmpp_record, is_archive_running) },
        { .key = "archive_last_run_time",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_vmpp_record, archive_last_run_time) },
        { .key = "VMs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vmpp_record, vms) },
        { .key = "is_alarm_enabled",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vmpp_record, is_alarm_enabled) },
        { .key = "alarm_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vmpp_record, alarm_config) },
        { .key = "recent_alerts",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_vmpp_record, recent_alerts) }
    };

const abstract_type xen_vmpp_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_vmpp_record),
       .member_count =
           sizeof(xen_vmpp_record_struct_members) / sizeof(struct_member),
       .members = xen_vmpp_record_struct_members
    };


static const struct struct_member xen_vmpp_xen_vmpp_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_vmpp_xen_vmpp_record_map_contents, key)
    },
    {
        .type = &xen_vmpp_record_abstract_type_,
        .offset = offsetof(xen_vmpp_xen_vmpp_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_vmpp_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_vmpp_xen_vmpp_record_map_contents),
    .members = xen_vmpp_xen_vmpp_record_members
};


void
xen_vmpp_record_free(xen_vmpp_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_string_string_map_free(record->backup_schedule);
    xen_string_string_map_free(record->archive_target_config);
    xen_string_string_map_free(record->archive_schedule);
    xen_vm_record_opt_set_free(record->vms);
    xen_string_string_map_free(record->alarm_config);
    xen_string_set_free(record->recent_alerts);
    free(record);
}


bool
xen_vmpp_get_record(xen_session *session, xen_vmpp_record **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = xen_vmpp_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VMPP.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_vmpp_get_by_uuid(xen_session *session, xen_vmpp *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VMPP.get_by_uuid");
    return session->ok;
}


bool
xen_vmpp_create(xen_session *session, xen_vmpp *result, xen_vmpp_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vmpp_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VMPP.create");
    return session->ok;
}

bool
xen_vmpp_create_async(xen_session *session, xen_task *result, xen_vmpp_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vmpp_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VMPP.create");
    return session->ok;
}

bool
xen_vmpp_destroy(xen_session *session, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    xen_call_(session, "VMPP.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vmpp_destroy_async(xen_session *session, xen_task *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VMPP.destroy");
    return session->ok;
}

bool
xen_vmpp_get_by_name_label(xen_session *session, struct xen_vmpp_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VMPP.get_by_name_label");
    return session->ok;
}


bool
xen_vmpp_get_name_label(xen_session *session, char **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VMPP.get_name_label");
    return session->ok;
}


bool
xen_vmpp_get_name_description(xen_session *session, char **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VMPP.get_name_description");
    return session->ok;
}


bool
xen_vmpp_get_is_policy_enabled(xen_session *session, bool *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VMPP.get_is_policy_enabled");
    return session->ok;
}


bool
xen_vmpp_get_backup_type(xen_session *session, enum xen_vmpp_backup_type *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = xen_vmpp_backup_type_abstract_type_;
    XEN_CALL_("VMPP.get_backup_type");
    return session->ok;
}


bool
xen_vmpp_get_backup_retention_value(xen_session *session, int64_t *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VMPP.get_backup_retention_value");
    return session->ok;
}


bool
xen_vmpp_get_backup_frequency(xen_session *session, enum xen_vmpp_backup_frequency *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = xen_vmpp_backup_frequency_abstract_type_;
    XEN_CALL_("VMPP.get_backup_frequency");
    return session->ok;
}


bool
xen_vmpp_get_backup_schedule(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VMPP.get_backup_schedule");
    return session->ok;
}


bool
xen_vmpp_get_is_backup_running(xen_session *session, bool *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VMPP.get_is_backup_running");
    return session->ok;
}


bool
xen_vmpp_get_backup_last_run_time(xen_session *session, time_t *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("VMPP.get_backup_last_run_time");
    return session->ok;
}


bool
xen_vmpp_get_archive_target_type(xen_session *session, enum xen_vmpp_archive_target_type *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = xen_vmpp_archive_target_type_abstract_type_;
    XEN_CALL_("VMPP.get_archive_target_type");
    return session->ok;
}


bool
xen_vmpp_get_archive_target_config(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VMPP.get_archive_target_config");
    return session->ok;
}


bool
xen_vmpp_get_archive_frequency(xen_session *session, enum xen_vmpp_archive_frequency *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = xen_vmpp_archive_frequency_abstract_type_;
    XEN_CALL_("VMPP.get_archive_frequency");
    return session->ok;
}


bool
xen_vmpp_get_archive_schedule(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VMPP.get_archive_schedule");
    return session->ok;
}


bool
xen_vmpp_get_is_archive_running(xen_session *session, bool *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VMPP.get_is_archive_running");
    return session->ok;
}


bool
xen_vmpp_get_archive_last_run_time(xen_session *session, time_t *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("VMPP.get_archive_last_run_time");
    return session->ok;
}


bool
xen_vmpp_get_vms(xen_session *session, struct xen_vm_set **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VMPP.get_VMs");
    return session->ok;
}


bool
xen_vmpp_get_is_alarm_enabled(xen_session *session, bool *result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VMPP.get_is_alarm_enabled");
    return session->ok;
}


bool
xen_vmpp_get_alarm_config(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VMPP.get_alarm_config");
    return session->ok;
}


bool
xen_vmpp_get_recent_alerts(xen_session *session, struct xen_string_set **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VMPP.get_recent_alerts");
    return session->ok;
}


bool
xen_vmpp_set_name_label(xen_session *session, xen_vmpp vmpp, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp },
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    xen_call_(session, "VMPP.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_name_description(xen_session *session, xen_vmpp vmpp, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    xen_call_(session, "VMPP.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_is_policy_enabled(xen_session *session, xen_vmpp vmpp, bool is_policy_enabled)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp },
            { .type = &abstract_type_bool,
              .u.bool_val = is_policy_enabled }
        };

    xen_call_(session, "VMPP.set_is_policy_enabled", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_backup_type(xen_session *session, xen_vmpp vmpp, enum xen_vmpp_backup_type backup_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp },
            { .type = &xen_vmpp_backup_type_abstract_type_,
              .u.enum_val = backup_type }
        };

    xen_call_(session, "VMPP.set_backup_type", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_protect_now(xen_session *session, char **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VMPP.protect_now");
    return session->ok;
}


bool
xen_vmpp_archive_now(xen_session *session, char **result, xen_vm snapshot)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = snapshot }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VMPP.archive_now");
    return session->ok;
}


bool
xen_vmpp_get_alerts(xen_session *session, struct xen_string_set **result, xen_vmpp vmpp, int64_t hours_from_now)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp },
            { .type = &abstract_type_int,
              .u.int_val = hours_from_now }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VMPP.get_alerts");
    return session->ok;
}


bool
xen_vmpp_set_backup_retention_value(xen_session *session, xen_vmpp self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VMPP.set_backup_retention_value", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_backup_frequency(xen_session *session, xen_vmpp self, enum xen_vmpp_backup_frequency value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_vmpp_backup_frequency_abstract_type_,
              .u.enum_val = value }
        };

    xen_call_(session, "VMPP.set_backup_frequency", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_backup_schedule(xen_session *session, xen_vmpp self, xen_string_string_map *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)value }
        };

    xen_call_(session, "VMPP.set_backup_schedule", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_archive_frequency(xen_session *session, xen_vmpp self, enum xen_vmpp_archive_frequency value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_vmpp_archive_frequency_abstract_type_,
              .u.enum_val = value }
        };

    xen_call_(session, "VMPP.set_archive_frequency", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_archive_schedule(xen_session *session, xen_vmpp self, xen_string_string_map *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)value }
        };

    xen_call_(session, "VMPP.set_archive_schedule", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_archive_target_type(xen_session *session, xen_vmpp self, enum xen_vmpp_archive_target_type value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_vmpp_archive_target_type_abstract_type_,
              .u.enum_val = value }
        };

    xen_call_(session, "VMPP.set_archive_target_type", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_archive_target_config(xen_session *session, xen_vmpp self, xen_string_string_map *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)value }
        };

    xen_call_(session, "VMPP.set_archive_target_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_is_alarm_enabled(xen_session *session, xen_vmpp self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VMPP.set_is_alarm_enabled", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_alarm_config(xen_session *session, xen_vmpp self, xen_string_string_map *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)value }
        };

    xen_call_(session, "VMPP.set_alarm_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_add_to_backup_schedule(xen_session *session, xen_vmpp self, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VMPP.add_to_backup_schedule", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_add_to_archive_target_config(xen_session *session, xen_vmpp self, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VMPP.add_to_archive_target_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_add_to_archive_schedule(xen_session *session, xen_vmpp self, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VMPP.add_to_archive_schedule", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_add_to_alarm_config(xen_session *session, xen_vmpp self, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VMPP.add_to_alarm_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_remove_from_backup_schedule(xen_session *session, xen_vmpp self, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VMPP.remove_from_backup_schedule", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_remove_from_archive_target_config(xen_session *session, xen_vmpp self, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VMPP.remove_from_archive_target_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_remove_from_archive_schedule(xen_session *session, xen_vmpp self, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VMPP.remove_from_archive_schedule", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_remove_from_alarm_config(xen_session *session, xen_vmpp self, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VMPP.remove_from_alarm_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_backup_last_run_time(xen_session *session, xen_vmpp self, time_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_datetime,
              .u.datetime_val = value }
        };

    xen_call_(session, "VMPP.set_backup_last_run_time", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_set_archive_last_run_time(xen_session *session, xen_vmpp self, time_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_datetime,
              .u.datetime_val = value }
        };

    xen_call_(session, "VMPP.set_archive_last_run_time", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vmpp_get_all(xen_session *session, struct xen_vmpp_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "VMPP.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vmpp_get_all_records(xen_session *session, xen_vmpp_xen_vmpp_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_vmpp_record_map;

    *result = NULL;
    xen_call_(session, "VMPP.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vmpp_get_uuid(xen_session *session, char **result, xen_vmpp vmpp)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vmpp }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VMPP.get_uuid");
    return session->ok;
}

