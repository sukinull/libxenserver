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
#include "xen_string_vm_appliance_operation_map_internal.h"
#include "xen_vm_appliance_operation_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_string_vm_appliance_operation_map.h>
#include <xen/api/xen_vm.h>
#include <xen/api/xen_vm_appliance.h>
#include <xen/api/xen_vm_appliance_operation.h>
#include <xen/api/xen_vm_appliance_xen_vm_appliance_record_map.h>


XEN_FREE(xen_vm_appliance)
XEN_SET_ALLOC_FREE(xen_vm_appliance)
XEN_ALLOC(xen_vm_appliance_record)
XEN_SET_ALLOC_FREE(xen_vm_appliance_record)
XEN_ALLOC(xen_vm_appliance_record_opt)
XEN_RECORD_OPT_FREE(xen_vm_appliance)
XEN_SET_ALLOC_FREE(xen_vm_appliance_record_opt)


static const struct_member xen_vm_appliance_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_appliance_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_appliance_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_appliance_record, name_description) },
        { .key = "allowed_operations",
          .type = &xen_vm_appliance_operation_set_abstract_type_,
          .offset = offsetof(xen_vm_appliance_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_vm_appliance_operation_map_abstract_type_,
          .offset = offsetof(xen_vm_appliance_record, current_operations) },
        { .key = "VMs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_appliance_record, vms) }
    };

const abstract_type xen_vm_appliance_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_vm_appliance_record),
       .member_count =
           sizeof(xen_vm_appliance_record_struct_members) / sizeof(struct_member),
       .members = xen_vm_appliance_record_struct_members
    };


static const struct struct_member xen_vm_appliance_xen_vm_appliance_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_vm_appliance_xen_vm_appliance_record_map_contents, key)
    },
    {
        .type = &xen_vm_appliance_record_abstract_type_,
        .offset = offsetof(xen_vm_appliance_xen_vm_appliance_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_vm_appliance_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_vm_appliance_xen_vm_appliance_record_map_contents),
    .members = xen_vm_appliance_xen_vm_appliance_record_members
};


void
xen_vm_appliance_record_free(xen_vm_appliance_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_vm_appliance_operation_set_free(record->allowed_operations);
    xen_string_vm_appliance_operation_map_free(record->current_operations);
    xen_vm_record_opt_set_free(record->vms);
    free(record);
}


bool
xen_vm_appliance_get_record(xen_session *session, xen_vm_appliance_record **result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = xen_vm_appliance_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_vm_appliance_get_by_uuid(xen_session *session, xen_vm_appliance *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_by_uuid");
    return session->ok;
}


bool
xen_vm_appliance_create(xen_session *session, xen_vm_appliance *result, xen_vm_appliance_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vm_appliance_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM_appliance.create");
    return session->ok;
}

bool
xen_vm_appliance_create_async(xen_session *session, xen_task *result, xen_vm_appliance_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vm_appliance_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.create");
    return session->ok;
}

bool
xen_vm_appliance_destroy(xen_session *session, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    xen_call_(session, "VM_appliance.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_appliance_destroy_async(xen_session *session, xen_task *result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.destroy");
    return session->ok;
}

bool
xen_vm_appliance_get_by_name_label(xen_session *session, struct xen_vm_appliance_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_by_name_label");
    return session->ok;
}


bool
xen_vm_appliance_get_name_label(xen_session *session, char **result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_name_label");
    return session->ok;
}


bool
xen_vm_appliance_get_name_description(xen_session *session, char **result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_name_description");
    return session->ok;
}


bool
xen_vm_appliance_get_allowed_operations(xen_session *session, struct xen_vm_appliance_operation_set **result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = xen_vm_appliance_operation_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_allowed_operations");
    return session->ok;
}


bool
xen_vm_appliance_get_current_operations(xen_session *session, xen_string_vm_appliance_operation_map **result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = string_vm_appliance_operation_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_current_operations");
    return session->ok;
}


bool
xen_vm_appliance_get_vms(xen_session *session, struct xen_vm_set **result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_VMs");
    return session->ok;
}


bool
xen_vm_appliance_set_name_label(xen_session *session, xen_vm_appliance vm_appliance, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance },
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    xen_call_(session, "VM_appliance.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_appliance_set_name_description(xen_session *session, xen_vm_appliance vm_appliance, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    xen_call_(session, "VM_appliance.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_appliance_start(xen_session *session, xen_vm_appliance self, bool paused)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = paused }
        };

    xen_call_(session, "VM_appliance.start", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_appliance_start_async(xen_session *session, xen_task *result, xen_vm_appliance self, bool paused)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = paused }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.start");
    return session->ok;
}

bool
xen_vm_appliance_clean_shutdown(xen_session *session, xen_vm_appliance self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VM_appliance.clean_shutdown", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_appliance_clean_shutdown_async(xen_session *session, xen_task *result, xen_vm_appliance self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.clean_shutdown");
    return session->ok;
}

bool
xen_vm_appliance_hard_shutdown(xen_session *session, xen_vm_appliance self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VM_appliance.hard_shutdown", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_appliance_hard_shutdown_async(xen_session *session, xen_task *result, xen_vm_appliance self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.hard_shutdown");
    return session->ok;
}

bool
xen_vm_appliance_shutdown(xen_session *session, xen_vm_appliance self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VM_appliance.shutdown", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_appliance_shutdown_async(xen_session *session, xen_task *result, xen_vm_appliance self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.shutdown");
    return session->ok;
}

bool
xen_vm_appliance_assert_can_be_recovered(xen_session *session, xen_vm_appliance self, xen_session *session_to)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = session_to->session_id }
        };

    xen_call_(session, "VM_appliance.assert_can_be_recovered", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_appliance_assert_can_be_recovered_async(xen_session *session, xen_task *result, xen_vm_appliance self, xen_session *session_to)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = session_to->session_id }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.assert_can_be_recovered");
    return session->ok;
}

bool
xen_vm_appliance_recover(xen_session *session, xen_vm_appliance self, xen_session *session_to, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = session_to->session_id },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    xen_call_(session, "VM_appliance.recover", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_appliance_recover_async(xen_session *session, xen_task *result, xen_vm_appliance self, xen_session *session_to, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = session_to->session_id },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM_appliance.recover");
    return session->ok;
}

bool
xen_vm_appliance_get_all(xen_session *session, struct xen_vm_appliance_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "VM_appliance.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vm_appliance_get_all_records(xen_session *session, xen_vm_appliance_xen_vm_appliance_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_vm_appliance_record_map;

    *result = NULL;
    xen_call_(session, "VM_appliance.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vm_appliance_get_uuid(xen_session *session, char **result, xen_vm_appliance vm_appliance)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm_appliance }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM_appliance.get_uuid");
    return session->ok;
}

