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
#include "xen_string_vbd_operations_map_internal.h"
#include "xen_vbd_mode_internal.h"
#include "xen_vbd_operations_internal.h"
#include "xen_vbd_type_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_vbd_operations_map.h>
#include <xen/api/xen_vbd.h>
#include <xen/api/xen_vbd_metrics.h>
#include <xen/api/xen_vbd_operations.h>
#include <xen/api/xen_vbd_xen_vbd_record_map.h>
#include <xen/api/xen_vdi.h>
#include <xen/api/xen_vm.h>


XEN_FREE(xen_vbd)
XEN_SET_ALLOC_FREE(xen_vbd)
XEN_ALLOC(xen_vbd_record)
XEN_SET_ALLOC_FREE(xen_vbd_record)
XEN_ALLOC(xen_vbd_record_opt)
XEN_RECORD_OPT_FREE(xen_vbd)
XEN_SET_ALLOC_FREE(xen_vbd_record_opt)


static const struct_member xen_vbd_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vbd_record, uuid) },
        { .key = "allowed_operations",
          .type = &xen_vbd_operations_set_abstract_type_,
          .offset = offsetof(xen_vbd_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_vbd_operations_map_abstract_type_,
          .offset = offsetof(xen_vbd_record, current_operations) },
        { .key = "VM",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vbd_record, vm) },
        { .key = "VDI",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vbd_record, vdi) },
        { .key = "device",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vbd_record, device) },
        { .key = "userdevice",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vbd_record, userdevice) },
        { .key = "bootable",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vbd_record, bootable) },
        { .key = "mode",
          .type = &xen_vbd_mode_abstract_type_,
          .offset = offsetof(xen_vbd_record, mode) },
        { .key = "type",
          .type = &xen_vbd_type_abstract_type_,
          .offset = offsetof(xen_vbd_record, type) },
        { .key = "unpluggable",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vbd_record, unpluggable) },
        { .key = "storage_lock",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vbd_record, storage_lock) },
        { .key = "empty",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vbd_record, empty) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vbd_record, other_config) },
        { .key = "currently_attached",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vbd_record, currently_attached) },
        { .key = "status_code",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vbd_record, status_code) },
        { .key = "status_detail",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vbd_record, status_detail) },
        { .key = "runtime_properties",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vbd_record, runtime_properties) },
        { .key = "qos_algorithm_type",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vbd_record, qos_algorithm_type) },
        { .key = "qos_algorithm_params",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vbd_record, qos_algorithm_params) },
        { .key = "qos_supported_algorithms",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_vbd_record, qos_supported_algorithms) },
        { .key = "metrics",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vbd_record, metrics) }
    };

const abstract_type xen_vbd_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_vbd_record),
       .member_count =
           sizeof(xen_vbd_record_struct_members) / sizeof(struct_member),
       .members = xen_vbd_record_struct_members
    };


static const struct struct_member xen_vbd_xen_vbd_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_vbd_xen_vbd_record_map_contents, key)
    },
    {
        .type = &xen_vbd_record_abstract_type_,
        .offset = offsetof(xen_vbd_xen_vbd_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_vbd_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_vbd_xen_vbd_record_map_contents),
    .members = xen_vbd_xen_vbd_record_members
};


void
xen_vbd_record_free(xen_vbd_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_vbd_operations_set_free(record->allowed_operations);
    xen_string_vbd_operations_map_free(record->current_operations);
    xen_vm_record_opt_free(record->vm);
    xen_vdi_record_opt_free(record->vdi);
    free(record->device);
    free(record->userdevice);
    xen_string_string_map_free(record->other_config);
    free(record->status_detail);
    xen_string_string_map_free(record->runtime_properties);
    free(record->qos_algorithm_type);
    xen_string_string_map_free(record->qos_algorithm_params);
    xen_string_set_free(record->qos_supported_algorithms);
    xen_vbd_metrics_record_opt_free(record->metrics);
    free(record);
}


bool
xen_vbd_get_record(xen_session *session, xen_vbd_record **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = xen_vbd_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VBD.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_vbd_get_by_uuid(xen_session *session, xen_vbd *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_by_uuid");
    return session->ok;
}


bool
xen_vbd_create(xen_session *session, xen_vbd *result, xen_vbd_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vbd_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.create");
    return session->ok;
}

bool
xen_vbd_create_async(xen_session *session, xen_task *result, xen_vbd_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vbd_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.create");
    return session->ok;
}

bool
xen_vbd_destroy(xen_session *session, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    xen_call_(session, "VBD.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vbd_destroy_async(xen_session *session, xen_task *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.destroy");
    return session->ok;
}

bool
xen_vbd_get_allowed_operations(xen_session *session, struct xen_vbd_operations_set **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = xen_vbd_operations_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("VBD.get_allowed_operations");
    return session->ok;
}


bool
xen_vbd_get_current_operations(xen_session *session, xen_string_vbd_operations_map **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = string_vbd_operations_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("VBD.get_current_operations");
    return session->ok;
}


bool
xen_vbd_get_vm(xen_session *session, xen_vm *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_VM");
    return session->ok;
}


bool
xen_vbd_get_vdi(xen_session *session, xen_vdi *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_VDI");
    return session->ok;
}


bool
xen_vbd_get_device(xen_session *session, char **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_device");
    return session->ok;
}


bool
xen_vbd_get_userdevice(xen_session *session, char **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_userdevice");
    return session->ok;
}


bool
xen_vbd_get_bootable(xen_session *session, bool *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VBD.get_bootable");
    return session->ok;
}


bool
xen_vbd_get_mode(xen_session *session, enum xen_vbd_mode *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = xen_vbd_mode_abstract_type_;
    XEN_CALL_("VBD.get_mode");
    return session->ok;
}


bool
xen_vbd_get_type(xen_session *session, enum xen_vbd_type *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = xen_vbd_type_abstract_type_;
    XEN_CALL_("VBD.get_type");
    return session->ok;
}


bool
xen_vbd_get_unpluggable(xen_session *session, bool *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VBD.get_unpluggable");
    return session->ok;
}


bool
xen_vbd_get_storage_lock(xen_session *session, bool *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VBD.get_storage_lock");
    return session->ok;
}


bool
xen_vbd_get_empty(xen_session *session, bool *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VBD.get_empty");
    return session->ok;
}


bool
xen_vbd_get_other_config(xen_session *session, xen_string_string_map **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VBD.get_other_config");
    return session->ok;
}


bool
xen_vbd_get_currently_attached(xen_session *session, bool *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VBD.get_currently_attached");
    return session->ok;
}


bool
xen_vbd_get_status_code(xen_session *session, int64_t *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VBD.get_status_code");
    return session->ok;
}


bool
xen_vbd_get_status_detail(xen_session *session, char **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_status_detail");
    return session->ok;
}


bool
xen_vbd_get_runtime_properties(xen_session *session, xen_string_string_map **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VBD.get_runtime_properties");
    return session->ok;
}


bool
xen_vbd_get_qos_algorithm_type(xen_session *session, char **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_qos_algorithm_type");
    return session->ok;
}


bool
xen_vbd_get_qos_algorithm_params(xen_session *session, xen_string_string_map **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VBD.get_qos_algorithm_params");
    return session->ok;
}


bool
xen_vbd_get_qos_supported_algorithms(xen_session *session, struct xen_string_set **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VBD.get_qos_supported_algorithms");
    return session->ok;
}


bool
xen_vbd_get_metrics(xen_session *session, xen_vbd_metrics *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_metrics");
    return session->ok;
}


bool
xen_vbd_set_userdevice(xen_session *session, xen_vbd vbd, char *userdevice)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = userdevice }
        };

    xen_call_(session, "VBD.set_userdevice", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_set_bootable(xen_session *session, xen_vbd vbd, bool bootable)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_bool,
              .u.bool_val = bootable }
        };

    xen_call_(session, "VBD.set_bootable", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_set_mode(xen_session *session, xen_vbd vbd, enum xen_vbd_mode mode)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &xen_vbd_mode_abstract_type_,
              .u.enum_val = mode }
        };

    xen_call_(session, "VBD.set_mode", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_set_type(xen_session *session, xen_vbd vbd, enum xen_vbd_type type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &xen_vbd_type_abstract_type_,
              .u.enum_val = type }
        };

    xen_call_(session, "VBD.set_type", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_set_unpluggable(xen_session *session, xen_vbd vbd, bool unpluggable)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_bool,
              .u.bool_val = unpluggable }
        };

    xen_call_(session, "VBD.set_unpluggable", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_set_other_config(xen_session *session, xen_vbd vbd, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "VBD.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_add_to_other_config(xen_session *session, xen_vbd vbd, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VBD.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_remove_from_other_config(xen_session *session, xen_vbd vbd, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VBD.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_set_qos_algorithm_type(xen_session *session, xen_vbd vbd, char *algorithm_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = algorithm_type }
        };

    xen_call_(session, "VBD.set_qos_algorithm_type", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_set_qos_algorithm_params(xen_session *session, xen_vbd vbd, xen_string_string_map *algorithm_params)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)algorithm_params }
        };

    xen_call_(session, "VBD.set_qos_algorithm_params", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_add_to_qos_algorithm_params(xen_session *session, xen_vbd vbd, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VBD.add_to_qos_algorithm_params", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_remove_from_qos_algorithm_params(xen_session *session, xen_vbd vbd, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VBD.remove_from_qos_algorithm_params", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vbd_eject(xen_session *session, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    xen_call_(session, "VBD.eject", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vbd_eject_async(xen_session *session, xen_task *result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.eject");
    return session->ok;
}

bool
xen_vbd_insert(xen_session *session, xen_vbd vbd, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    xen_call_(session, "VBD.insert", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vbd_insert_async(xen_session *session, xen_task *result, xen_vbd vbd, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd },
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.insert");
    return session->ok;
}

bool
xen_vbd_plug(xen_session *session, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VBD.plug", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vbd_plug_async(xen_session *session, xen_task *result, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.plug");
    return session->ok;
}

bool
xen_vbd_unplug(xen_session *session, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VBD.unplug", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vbd_unplug_async(xen_session *session, xen_task *result, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.unplug");
    return session->ok;
}

bool
xen_vbd_unplug_force(xen_session *session, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VBD.unplug_force", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vbd_unplug_force_async(xen_session *session, xen_task *result, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.unplug_force");
    return session->ok;
}

bool
xen_vbd_assert_attachable(xen_session *session, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VBD.assert_attachable", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vbd_assert_attachable_async(xen_session *session, xen_task *result, xen_vbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VBD.assert_attachable");
    return session->ok;
}

bool
xen_vbd_get_all(xen_session *session, struct xen_vbd_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "VBD.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vbd_get_all_records(xen_session *session, xen_vbd_xen_vbd_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_vbd_record_map;

    *result = NULL;
    xen_call_(session, "VBD.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vbd_get_uuid(xen_session *session, char **result, xen_vbd vbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VBD.get_uuid");
    return session->ok;
}

