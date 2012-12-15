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
#include "xen_on_crash_behaviour_internal.h"
#include "xen_on_normal_exit_internal.h"
#include "xen_string_vm_operations_map_internal.h"
#include "xen_vm_operations_internal.h"
#include "xen_vm_operations_string_map_internal.h"
#include "xen_vm_power_state_internal.h"
#include <xen/api/xen_blob.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_console.h>
#include <xen/api/xen_crashdump.h>
#include <xen/api/xen_host.h>
#include <xen/api/xen_host_string_set_map.h>
#include <xen/api/xen_pci.h>
#include <xen/api/xen_sr.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_vm_operations_map.h>
#include <xen/api/xen_vbd.h>
#include <xen/api/xen_vdi.h>
#include <xen/api/xen_vdi_sr_map.h>
#include <xen/api/xen_vgpu.h>
#include <xen/api/xen_vif.h>
#include <xen/api/xen_vif_network_map.h>
#include <xen/api/xen_vm.h>
#include <xen/api/xen_vm_appliance.h>
#include <xen/api/xen_vm_guest_metrics.h>
#include <xen/api/xen_vm_metrics.h>
#include <xen/api/xen_vm_operations.h>
#include <xen/api/xen_vm_operations_string_map.h>
#include <xen/api/xen_vm_xen_vm_record_map.h>
#include <xen/api/xen_vmpp.h>
#include <xen/api/xen_vtpm.h>


XEN_FREE(xen_vm)
XEN_SET_ALLOC_FREE(xen_vm)
XEN_ALLOC(xen_vm_record)
XEN_SET_ALLOC_FREE(xen_vm_record)
XEN_ALLOC(xen_vm_record_opt)
XEN_RECORD_OPT_FREE(xen_vm)
XEN_SET_ALLOC_FREE(xen_vm_record_opt)


static const struct_member xen_vm_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, uuid) },
        { .key = "allowed_operations",
          .type = &xen_vm_operations_set_abstract_type_,
          .offset = offsetof(xen_vm_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_vm_operations_map_abstract_type_,
          .offset = offsetof(xen_vm_record, current_operations) },
        { .key = "power_state",
          .type = &xen_vm_power_state_abstract_type_,
          .offset = offsetof(xen_vm_record, power_state) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, name_description) },
        { .key = "user_version",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, user_version) },
        { .key = "is_a_template",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vm_record, is_a_template) },
        { .key = "suspend_VDI",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, suspend_vdi) },
        { .key = "resident_on",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, resident_on) },
        { .key = "affinity",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, affinity) },
        { .key = "memory_overhead",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, memory_overhead) },
        { .key = "memory_target",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, memory_target) },
        { .key = "memory_static_max",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, memory_static_max) },
        { .key = "memory_dynamic_max",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, memory_dynamic_max) },
        { .key = "memory_dynamic_min",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, memory_dynamic_min) },
        { .key = "memory_static_min",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, memory_static_min) },
        { .key = "VCPUs_params",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, vcpus_params) },
        { .key = "VCPUs_max",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, vcpus_max) },
        { .key = "VCPUs_at_startup",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, vcpus_at_startup) },
        { .key = "actions_after_shutdown",
          .type = &xen_on_normal_exit_abstract_type_,
          .offset = offsetof(xen_vm_record, actions_after_shutdown) },
        { .key = "actions_after_reboot",
          .type = &xen_on_normal_exit_abstract_type_,
          .offset = offsetof(xen_vm_record, actions_after_reboot) },
        { .key = "actions_after_crash",
          .type = &xen_on_crash_behaviour_abstract_type_,
          .offset = offsetof(xen_vm_record, actions_after_crash) },
        { .key = "consoles",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, consoles) },
        { .key = "VIFs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, vifs) },
        { .key = "VBDs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, vbds) },
        { .key = "crash_dumps",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, crash_dumps) },
        { .key = "VTPMs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, vtpms) },
        { .key = "PV_bootloader",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, pv_bootloader) },
        { .key = "PV_kernel",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, pv_kernel) },
        { .key = "PV_ramdisk",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, pv_ramdisk) },
        { .key = "PV_args",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, pv_args) },
        { .key = "PV_bootloader_args",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, pv_bootloader_args) },
        { .key = "PV_legacy_args",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, pv_legacy_args) },
        { .key = "HVM_boot_policy",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, hvm_boot_policy) },
        { .key = "HVM_boot_params",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, hvm_boot_params) },
        { .key = "HVM_shadow_multiplier",
          .type = &abstract_type_float,
          .offset = offsetof(xen_vm_record, hvm_shadow_multiplier) },
        { .key = "platform",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, platform) },
        { .key = "PCI_bus",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, pci_bus) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, other_config) },
        { .key = "domid",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, domid) },
        { .key = "domarch",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, domarch) },
        { .key = "last_boot_CPU_flags",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, last_boot_cpu_flags) },
        { .key = "is_control_domain",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vm_record, is_control_domain) },
        { .key = "metrics",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, metrics) },
        { .key = "guest_metrics",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, guest_metrics) },
        { .key = "last_booted_record",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, last_booted_record) },
        { .key = "recommendations",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, recommendations) },
        { .key = "xenstore_data",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, xenstore_data) },
        { .key = "ha_always_run",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vm_record, ha_always_run) },
        { .key = "ha_restart_priority",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, ha_restart_priority) },
        { .key = "is_a_snapshot",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vm_record, is_a_snapshot) },
        { .key = "snapshot_of",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, snapshot_of) },
        { .key = "snapshots",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, snapshots) },
        { .key = "snapshot_time",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_vm_record, snapshot_time) },
        { .key = "transportable_snapshot_id",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, transportable_snapshot_id) },
        { .key = "blobs",
          .type = &abstract_type_string_ref_map,
          .offset = offsetof(xen_vm_record, blobs) },
        { .key = "tags",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_vm_record, tags) },
        { .key = "blocked_operations",
          .type = &vm_operations_string_map_abstract_type_,
          .offset = offsetof(xen_vm_record, blocked_operations) },
        { .key = "snapshot_info",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, snapshot_info) },
        { .key = "snapshot_metadata",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vm_record, snapshot_metadata) },
        { .key = "parent",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, parent) },
        { .key = "children",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, children) },
        { .key = "bios_strings",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vm_record, bios_strings) },
        { .key = "protection_policy",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, protection_policy) },
        { .key = "is_snapshot_from_vmpp",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vm_record, is_snapshot_from_vmpp) },
        { .key = "appliance",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, appliance) },
        { .key = "start_delay",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, start_delay) },
        { .key = "shutdown_delay",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, shutdown_delay) },
        { .key = "order",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, order) },
        { .key = "VGPUs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, vgpus) },
        { .key = "attached_PCIs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vm_record, attached_pcis) },
        { .key = "suspend_SR",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vm_record, suspend_sr) },
        { .key = "version",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vm_record, version) }
    };

const abstract_type xen_vm_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_vm_record),
       .member_count =
           sizeof(xen_vm_record_struct_members) / sizeof(struct_member),
       .members = xen_vm_record_struct_members
    };


static const struct struct_member xen_vm_xen_vm_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_vm_xen_vm_record_map_contents, key)
    },
    {
        .type = &xen_vm_record_abstract_type_,
        .offset = offsetof(xen_vm_xen_vm_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_vm_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_vm_xen_vm_record_map_contents),
    .members = xen_vm_xen_vm_record_members
};


void
xen_vm_record_free(xen_vm_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_vm_operations_set_free(record->allowed_operations);
    xen_string_vm_operations_map_free(record->current_operations);
    free(record->name_label);
    free(record->name_description);
    xen_vdi_record_opt_free(record->suspend_vdi);
    xen_host_record_opt_free(record->resident_on);
    xen_host_record_opt_free(record->affinity);
    xen_string_string_map_free(record->vcpus_params);
    xen_console_record_opt_set_free(record->consoles);
    xen_vif_record_opt_set_free(record->vifs);
    xen_vbd_record_opt_set_free(record->vbds);
    xen_crashdump_record_opt_set_free(record->crash_dumps);
    xen_vtpm_record_opt_set_free(record->vtpms);
    free(record->pv_bootloader);
    free(record->pv_kernel);
    free(record->pv_ramdisk);
    free(record->pv_args);
    free(record->pv_bootloader_args);
    free(record->pv_legacy_args);
    free(record->hvm_boot_policy);
    xen_string_string_map_free(record->hvm_boot_params);
    xen_string_string_map_free(record->platform);
    free(record->pci_bus);
    xen_string_string_map_free(record->other_config);
    free(record->domarch);
    xen_string_string_map_free(record->last_boot_cpu_flags);
    xen_vm_metrics_record_opt_free(record->metrics);
    xen_vm_guest_metrics_record_opt_free(record->guest_metrics);
    free(record->last_booted_record);
    free(record->recommendations);
    xen_string_string_map_free(record->xenstore_data);
    free(record->ha_restart_priority);
    xen_vm_record_opt_free(record->snapshot_of);
    xen_vm_record_opt_set_free(record->snapshots);
    free(record->transportable_snapshot_id);
    xen_string_blob_map_free(record->blobs);
    xen_string_set_free(record->tags);
    xen_vm_operations_string_map_free(record->blocked_operations);
    xen_string_string_map_free(record->snapshot_info);
    free(record->snapshot_metadata);
    xen_vm_record_opt_free(record->parent);
    xen_vm_record_opt_set_free(record->children);
    xen_string_string_map_free(record->bios_strings);
    xen_vmpp_record_opt_free(record->protection_policy);
    xen_vm_appliance_record_opt_free(record->appliance);
    xen_vgpu_record_opt_set_free(record->vgpus);
    xen_pci_record_opt_set_free(record->attached_pcis);
    xen_sr_record_opt_free(record->suspend_sr);
    free(record);
}


bool
xen_vm_get_record(xen_session *session, xen_vm_record **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = xen_vm_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_vm_get_by_uuid(xen_session *session, xen_vm *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_by_uuid");
    return session->ok;
}


bool
xen_vm_create(xen_session *session, xen_vm *result, xen_vm_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vm_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.create");
    return session->ok;
}

bool
xen_vm_create_async(xen_session *session, xen_task *result, xen_vm_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vm_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.create");
    return session->ok;
}

bool
xen_vm_destroy(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_destroy_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.destroy");
    return session->ok;
}

bool
xen_vm_get_by_name_label(xen_session *session, struct xen_vm_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_by_name_label");
    return session->ok;
}


bool
xen_vm_get_allowed_operations(xen_session *session, struct xen_vm_operations_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = xen_vm_operations_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM.get_allowed_operations");
    return session->ok;
}


bool
xen_vm_get_current_operations(xen_session *session, xen_string_vm_operations_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = string_vm_operations_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM.get_current_operations");
    return session->ok;
}


bool
xen_vm_get_power_state(xen_session *session, enum xen_vm_power_state *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = xen_vm_power_state_abstract_type_;
    XEN_CALL_("VM.get_power_state");
    return session->ok;
}


bool
xen_vm_get_name_label(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_name_label");
    return session->ok;
}


bool
xen_vm_get_name_description(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_name_description");
    return session->ok;
}


bool
xen_vm_get_user_version(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_user_version");
    return session->ok;
}


bool
xen_vm_get_is_a_template(xen_session *session, bool *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VM.get_is_a_template");
    return session->ok;
}


bool
xen_vm_get_suspend_vdi(xen_session *session, xen_vdi *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_suspend_VDI");
    return session->ok;
}


bool
xen_vm_get_resident_on(xen_session *session, xen_host *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_resident_on");
    return session->ok;
}


bool
xen_vm_get_affinity(xen_session *session, xen_host *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_affinity");
    return session->ok;
}


bool
xen_vm_get_memory_overhead(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_memory_overhead");
    return session->ok;
}


bool
xen_vm_get_memory_target(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_memory_target");
    return session->ok;
}


bool
xen_vm_get_memory_static_max(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_memory_static_max");
    return session->ok;
}


bool
xen_vm_get_memory_dynamic_max(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_memory_dynamic_max");
    return session->ok;
}


bool
xen_vm_get_memory_dynamic_min(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_memory_dynamic_min");
    return session->ok;
}


bool
xen_vm_get_memory_static_min(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_memory_static_min");
    return session->ok;
}


bool
xen_vm_get_vcpus_params(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_VCPUs_params");
    return session->ok;
}


bool
xen_vm_get_vcpus_max(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_VCPUs_max");
    return session->ok;
}


bool
xen_vm_get_vcpus_at_startup(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_VCPUs_at_startup");
    return session->ok;
}


bool
xen_vm_get_actions_after_shutdown(xen_session *session, enum xen_on_normal_exit *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = xen_on_normal_exit_abstract_type_;
    XEN_CALL_("VM.get_actions_after_shutdown");
    return session->ok;
}


bool
xen_vm_get_actions_after_reboot(xen_session *session, enum xen_on_normal_exit *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = xen_on_normal_exit_abstract_type_;
    XEN_CALL_("VM.get_actions_after_reboot");
    return session->ok;
}


bool
xen_vm_get_actions_after_crash(xen_session *session, enum xen_on_crash_behaviour *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = xen_on_crash_behaviour_abstract_type_;
    XEN_CALL_("VM.get_actions_after_crash");
    return session->ok;
}


bool
xen_vm_get_consoles(xen_session *session, struct xen_console_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_consoles");
    return session->ok;
}


bool
xen_vm_get_vifs(xen_session *session, struct xen_vif_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_VIFs");
    return session->ok;
}


bool
xen_vm_get_vbds(xen_session *session, struct xen_vbd_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_VBDs");
    return session->ok;
}


bool
xen_vm_get_crash_dumps(xen_session *session, struct xen_crashdump_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_crash_dumps");
    return session->ok;
}


bool
xen_vm_get_vtpms(xen_session *session, struct xen_vtpm_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_VTPMs");
    return session->ok;
}


bool
xen_vm_get_pv_bootloader(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_PV_bootloader");
    return session->ok;
}


bool
xen_vm_get_pv_kernel(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_PV_kernel");
    return session->ok;
}


bool
xen_vm_get_pv_ramdisk(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_PV_ramdisk");
    return session->ok;
}


bool
xen_vm_get_pv_args(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_PV_args");
    return session->ok;
}


bool
xen_vm_get_pv_bootloader_args(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_PV_bootloader_args");
    return session->ok;
}


bool
xen_vm_get_pv_legacy_args(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_PV_legacy_args");
    return session->ok;
}


bool
xen_vm_get_hvm_boot_policy(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_HVM_boot_policy");
    return session->ok;
}


bool
xen_vm_get_hvm_boot_params(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_HVM_boot_params");
    return session->ok;
}


bool
xen_vm_get_hvm_shadow_multiplier(xen_session *session, double *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_float;

    XEN_CALL_("VM.get_HVM_shadow_multiplier");
    return session->ok;
}


bool
xen_vm_get_platform(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_platform");
    return session->ok;
}


bool
xen_vm_get_pci_bus(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_PCI_bus");
    return session->ok;
}


bool
xen_vm_get_other_config(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_other_config");
    return session->ok;
}


bool
xen_vm_get_domid(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_domid");
    return session->ok;
}


bool
xen_vm_get_domarch(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_domarch");
    return session->ok;
}


bool
xen_vm_get_last_boot_cpu_flags(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_last_boot_CPU_flags");
    return session->ok;
}


bool
xen_vm_get_is_control_domain(xen_session *session, bool *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VM.get_is_control_domain");
    return session->ok;
}


bool
xen_vm_get_metrics(xen_session *session, xen_vm_metrics *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_metrics");
    return session->ok;
}


bool
xen_vm_get_guest_metrics(xen_session *session, xen_vm_guest_metrics *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_guest_metrics");
    return session->ok;
}


bool
xen_vm_get_last_booted_record(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_last_booted_record");
    return session->ok;
}


bool
xen_vm_get_recommendations(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_recommendations");
    return session->ok;
}


bool
xen_vm_get_xenstore_data(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_xenstore_data");
    return session->ok;
}


bool
xen_vm_get_ha_always_run(xen_session *session, bool *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VM.get_ha_always_run");
    return session->ok;
}


bool
xen_vm_get_ha_restart_priority(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_ha_restart_priority");
    return session->ok;
}


bool
xen_vm_get_is_a_snapshot(xen_session *session, bool *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VM.get_is_a_snapshot");
    return session->ok;
}


bool
xen_vm_get_snapshot_of(xen_session *session, xen_vm *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_snapshot_of");
    return session->ok;
}


bool
xen_vm_get_snapshots(xen_session *session, struct xen_vm_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_snapshots");
    return session->ok;
}


bool
xen_vm_get_snapshot_time(xen_session *session, time_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("VM.get_snapshot_time");
    return session->ok;
}


bool
xen_vm_get_transportable_snapshot_id(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_transportable_snapshot_id");
    return session->ok;
}


bool
xen_vm_get_blobs(xen_session *session, xen_string_blob_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_blobs");
    return session->ok;
}


bool
xen_vm_get_tags(xen_session *session, struct xen_string_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_tags");
    return session->ok;
}


bool
xen_vm_get_blocked_operations(xen_session *session, xen_vm_operations_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = vm_operations_string_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM.get_blocked_operations");
    return session->ok;
}


bool
xen_vm_get_snapshot_info(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_snapshot_info");
    return session->ok;
}


bool
xen_vm_get_snapshot_metadata(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_snapshot_metadata");
    return session->ok;
}


bool
xen_vm_get_parent(xen_session *session, xen_vm *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_parent");
    return session->ok;
}


bool
xen_vm_get_children(xen_session *session, struct xen_vm_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_children");
    return session->ok;
}


bool
xen_vm_get_bios_strings(xen_session *session, xen_string_string_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.get_bios_strings");
    return session->ok;
}


bool
xen_vm_get_protection_policy(xen_session *session, xen_vmpp *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_protection_policy");
    return session->ok;
}


bool
xen_vm_get_is_snapshot_from_vmpp(xen_session *session, bool *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VM.get_is_snapshot_from_vmpp");
    return session->ok;
}


bool
xen_vm_get_appliance(xen_session *session, xen_vm_appliance *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_appliance");
    return session->ok;
}


bool
xen_vm_get_start_delay(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_start_delay");
    return session->ok;
}


bool
xen_vm_get_shutdown_delay(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_shutdown_delay");
    return session->ok;
}


bool
xen_vm_get_order(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_order");
    return session->ok;
}


bool
xen_vm_get_vgpus(xen_session *session, struct xen_vgpu_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_VGPUs");
    return session->ok;
}


bool
xen_vm_get_attached_pcis(xen_session *session, struct xen_pci_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_attached_PCIs");
    return session->ok;
}


bool
xen_vm_get_suspend_sr(xen_session *session, xen_sr *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_suspend_SR");
    return session->ok;
}


bool
xen_vm_get_version(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.get_version");
    return session->ok;
}


bool
xen_vm_set_name_label(xen_session *session, xen_vm vm, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    xen_call_(session, "VM.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_name_description(xen_session *session, xen_vm vm, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    xen_call_(session, "VM.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_user_version(xen_session *session, xen_vm vm, int64_t user_version)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_int,
              .u.int_val = user_version }
        };

    xen_call_(session, "VM.set_user_version", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_is_a_template(xen_session *session, xen_vm vm, bool is_a_template)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_bool,
              .u.bool_val = is_a_template }
        };

    xen_call_(session, "VM.set_is_a_template", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_affinity(xen_session *session, xen_vm vm, xen_host affinity)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = affinity }
        };

    xen_call_(session, "VM.set_affinity", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_vcpus_params(xen_session *session, xen_vm vm, xen_string_string_map *params)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)params }
        };

    xen_call_(session, "VM.set_VCPUs_params", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_add_to_vcpus_params(xen_session *session, xen_vm vm, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.add_to_VCPUs_params", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vm_remove_from_vcpus_params(xen_session *session, xen_vm vm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VM.remove_from_VCPUs_params", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_actions_after_shutdown(xen_session *session, xen_vm vm, enum xen_on_normal_exit after_shutdown)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &xen_on_normal_exit_abstract_type_,
              .u.enum_val = after_shutdown }
        };

    xen_call_(session, "VM.set_actions_after_shutdown", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_actions_after_reboot(xen_session *session, xen_vm vm, enum xen_on_normal_exit after_reboot)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &xen_on_normal_exit_abstract_type_,
              .u.enum_val = after_reboot }
        };

    xen_call_(session, "VM.set_actions_after_reboot", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_actions_after_crash(xen_session *session, xen_vm vm, enum xen_on_crash_behaviour after_crash)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &xen_on_crash_behaviour_abstract_type_,
              .u.enum_val = after_crash }
        };

    xen_call_(session, "VM.set_actions_after_crash", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_pv_bootloader(xen_session *session, xen_vm vm, char *bootloader)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = bootloader }
        };

    xen_call_(session, "VM.set_PV_bootloader", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_pv_kernel(xen_session *session, xen_vm vm, char *kernel)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = kernel }
        };

    xen_call_(session, "VM.set_PV_kernel", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_pv_ramdisk(xen_session *session, xen_vm vm, char *ramdisk)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = ramdisk }
        };

    xen_call_(session, "VM.set_PV_ramdisk", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_pv_args(xen_session *session, xen_vm vm, char *args)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = args }
        };

    xen_call_(session, "VM.set_PV_args", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_pv_bootloader_args(xen_session *session, xen_vm vm, char *bootloader_args)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = bootloader_args }
        };

    xen_call_(session, "VM.set_PV_bootloader_args", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_pv_legacy_args(xen_session *session, xen_vm vm, char *legacy_args)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = legacy_args }
        };

    xen_call_(session, "VM.set_PV_legacy_args", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_hvm_boot_policy(xen_session *session, xen_vm vm, char *boot_policy)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = boot_policy }
        };

    xen_call_(session, "VM.set_HVM_boot_policy", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_hvm_boot_params(xen_session *session, xen_vm vm, xen_string_string_map *boot_params)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)boot_params }
        };

    xen_call_(session, "VM.set_HVM_boot_params", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_add_to_hvm_boot_params(xen_session *session, xen_vm vm, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.add_to_HVM_boot_params", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vm_remove_from_hvm_boot_params(xen_session *session, xen_vm vm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VM.remove_from_HVM_boot_params", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_platform(xen_session *session, xen_vm vm, xen_string_string_map *platform)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)platform }
        };

    xen_call_(session, "VM.set_platform", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_add_to_platform(xen_session *session, xen_vm vm, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.add_to_platform", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vm_remove_from_platform(xen_session *session, xen_vm vm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VM.remove_from_platform", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_pci_bus(xen_session *session, xen_vm vm, char *pci_bus)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = pci_bus }
        };

    xen_call_(session, "VM.set_PCI_bus", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_other_config(xen_session *session, xen_vm vm, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "VM.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_add_to_other_config(xen_session *session, xen_vm vm, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vm_remove_from_other_config(xen_session *session, xen_vm vm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VM.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_recommendations(xen_session *session, xen_vm vm, char *recommendations)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = recommendations }
        };

    xen_call_(session, "VM.set_recommendations", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_xenstore_data(xen_session *session, xen_vm vm, xen_string_string_map *xenstore_data)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)xenstore_data }
        };

    xen_call_(session, "VM.set_xenstore_data", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_add_to_xenstore_data(xen_session *session, xen_vm vm, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.add_to_xenstore_data", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vm_remove_from_xenstore_data(xen_session *session, xen_vm vm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VM.remove_from_xenstore_data", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_tags(xen_session *session, xen_vm vm, struct xen_string_set *tags)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)tags }
        };

    xen_call_(session, "VM.set_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_add_tags(xen_session *session, xen_vm vm, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.add_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_remove_tags(xen_session *session, xen_vm vm, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.remove_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_blocked_operations(xen_session *session, xen_vm vm, xen_vm_operations_string_map *blocked_operations)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &vm_operations_string_map_abstract_type_,
              .u.set_val = (arbitrary_set *)blocked_operations }
        };

    xen_call_(session, "VM.set_blocked_operations", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_add_to_blocked_operations(xen_session *session, xen_vm vm, enum xen_vm_operations key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &xen_vm_operations_abstract_type_,
              .u.enum_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.add_to_blocked_operations", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vm_remove_from_blocked_operations(xen_session *session, xen_vm vm, enum xen_vm_operations key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &xen_vm_operations_abstract_type_,
              .u.enum_val = key }
        };

    xen_call_(session, "VM.remove_from_blocked_operations", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_suspend_sr(xen_session *session, xen_vm vm, xen_sr suspend_sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = suspend_sr }
        };

    xen_call_(session, "VM.set_suspend_SR", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_snapshot(xen_session *session, xen_vm *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.snapshot");
    return session->ok;
}

bool
xen_vm_snapshot_async(xen_session *session, xen_task *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.snapshot");
    return session->ok;
}

bool
xen_vm_snapshot_with_quiesce(xen_session *session, xen_vm *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.snapshot_with_quiesce");
    return session->ok;
}

bool
xen_vm_snapshot_with_quiesce_async(xen_session *session, xen_task *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.snapshot_with_quiesce");
    return session->ok;
}

bool
xen_vm_clone(xen_session *session, xen_vm *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.clone");
    return session->ok;
}

bool
xen_vm_clone_async(xen_session *session, xen_task *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.clone");
    return session->ok;
}

bool
xen_vm_copy(xen_session *session, xen_vm *result, xen_vm vm, char *new_name, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name },
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.copy");
    return session->ok;
}

bool
xen_vm_copy_async(xen_session *session, xen_task *result, xen_vm vm, char *new_name, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name },
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.copy");
    return session->ok;
}

bool
xen_vm_revert(xen_session *session, xen_vm snapshot)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = snapshot }
        };

    xen_call_(session, "VM.revert", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_revert_async(xen_session *session, xen_task *result, xen_vm snapshot)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = snapshot }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.revert");
    return session->ok;
}

bool
xen_vm_checkpoint(xen_session *session, xen_vm *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.checkpoint");
    return session->ok;
}

bool
xen_vm_checkpoint_async(xen_session *session, xen_task *result, xen_vm vm, char *new_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = new_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.checkpoint");
    return session->ok;
}

bool
xen_vm_provision(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.provision", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_provision_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.provision");
    return session->ok;
}

bool
xen_vm_start(xen_session *session, xen_vm vm, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    xen_call_(session, "VM.start", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_start_async(xen_session *session, xen_task *result, xen_vm vm, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.start");
    return session->ok;
}

bool
xen_vm_start_on(xen_session *session, xen_vm vm, xen_host host, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    xen_call_(session, "VM.start_on", param_values, 4, NULL, NULL);
    return session->ok;
}

bool
xen_vm_start_on_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.start_on");
    return session->ok;
}

bool
xen_vm_pause(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.pause", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_pause_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.pause");
    return session->ok;
}

bool
xen_vm_unpause(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.unpause", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_unpause_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.unpause");
    return session->ok;
}

bool
xen_vm_clean_shutdown(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.clean_shutdown", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_clean_shutdown_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.clean_shutdown");
    return session->ok;
}

bool
xen_vm_clean_reboot(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.clean_reboot", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_clean_reboot_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.clean_reboot");
    return session->ok;
}

bool
xen_vm_hard_shutdown(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.hard_shutdown", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_hard_shutdown_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.hard_shutdown");
    return session->ok;
}

bool
xen_vm_power_state_reset(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.power_state_reset", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_power_state_reset_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.power_state_reset");
    return session->ok;
}

bool
xen_vm_hard_reboot(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.hard_reboot", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_hard_reboot_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.hard_reboot");
    return session->ok;
}

bool
xen_vm_suspend(xen_session *session, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    xen_call_(session, "VM.suspend", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_suspend_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.suspend");
    return session->ok;
}

bool
xen_vm_resume(xen_session *session, xen_vm vm, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    xen_call_(session, "VM.resume", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_resume_async(xen_session *session, xen_task *result, xen_vm vm, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.resume");
    return session->ok;
}

bool
xen_vm_resume_on(xen_session *session, xen_vm vm, xen_host host, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    xen_call_(session, "VM.resume_on", param_values, 4, NULL, NULL);
    return session->ok;
}

bool
xen_vm_resume_on_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host, bool start_paused, bool force)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_bool,
              .u.bool_val = start_paused },
            { .type = &abstract_type_bool,
              .u.bool_val = force }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.resume_on");
    return session->ok;
}

bool
xen_vm_pool_migrate(xen_session *session, xen_vm vm, xen_host host, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    xen_call_(session, "VM.pool_migrate", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_pool_migrate_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.pool_migrate");
    return session->ok;
}

bool
xen_vm_set_vcpus_number_live(xen_session *session, xen_vm self, int64_t nvcpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = nvcpu }
        };

    xen_call_(session, "VM.set_VCPUs_number_live", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_vcpus_number_live_async(xen_session *session, xen_task *result, xen_vm self, int64_t nvcpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = nvcpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_VCPUs_number_live");
    return session->ok;
}

bool
xen_vm_add_to_vcpus_params_live(xen_session *session, xen_vm self, char *key, char *value)
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

    xen_call_(session, "VM.add_to_VCPUs_params_live", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_add_to_vcpus_params_live_async(xen_session *session, xen_task *result, xen_vm self, char *key, char *value)
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

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.add_to_VCPUs_params_live");
    return session->ok;
}

bool
xen_vm_set_ha_restart_priority(xen_session *session, xen_vm self, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.set_ha_restart_priority", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_ha_always_run(xen_session *session, xen_vm self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VM.set_ha_always_run", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_compute_memory_overhead(xen_session *session, int64_t *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.compute_memory_overhead");
    return session->ok;
}

bool
xen_vm_compute_memory_overhead_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.compute_memory_overhead");
    return session->ok;
}

bool
xen_vm_set_memory_dynamic_max(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_memory_dynamic_max", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_memory_dynamic_min(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_memory_dynamic_min", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_memory_dynamic_range(xen_session *session, xen_vm self, int64_t min, int64_t max)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = min },
            { .type = &abstract_type_int,
              .u.int_val = max }
        };

    xen_call_(session, "VM.set_memory_dynamic_range", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_memory_dynamic_range_async(xen_session *session, xen_task *result, xen_vm self, int64_t min, int64_t max)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = min },
            { .type = &abstract_type_int,
              .u.int_val = max }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_memory_dynamic_range");
    return session->ok;
}

bool
xen_vm_set_memory_static_max(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_memory_static_max", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_memory_static_min(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_memory_static_min", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_memory_static_range(xen_session *session, xen_vm self, int64_t min, int64_t max)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = min },
            { .type = &abstract_type_int,
              .u.int_val = max }
        };

    xen_call_(session, "VM.set_memory_static_range", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_memory_static_range_async(xen_session *session, xen_task *result, xen_vm self, int64_t min, int64_t max)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = min },
            { .type = &abstract_type_int,
              .u.int_val = max }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_memory_static_range");
    return session->ok;
}

bool
xen_vm_set_memory_limits(xen_session *session, xen_vm self, int64_t static_min, int64_t static_max, int64_t dynamic_min, int64_t dynamic_max)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = static_min },
            { .type = &abstract_type_int,
              .u.int_val = static_max },
            { .type = &abstract_type_int,
              .u.int_val = dynamic_min },
            { .type = &abstract_type_int,
              .u.int_val = dynamic_max }
        };

    xen_call_(session, "VM.set_memory_limits", param_values, 5, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_memory_limits_async(xen_session *session, xen_task *result, xen_vm self, int64_t static_min, int64_t static_max, int64_t dynamic_min, int64_t dynamic_max)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = static_min },
            { .type = &abstract_type_int,
              .u.int_val = static_max },
            { .type = &abstract_type_int,
              .u.int_val = dynamic_min },
            { .type = &abstract_type_int,
              .u.int_val = dynamic_max }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_memory_limits");
    return session->ok;
}

bool
xen_vm_set_memory_target_live(xen_session *session, xen_vm self, int64_t target)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = target }
        };

    xen_call_(session, "VM.set_memory_target_live", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_memory_target_live_async(xen_session *session, xen_task *result, xen_vm self, int64_t target)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = target }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_memory_target_live");
    return session->ok;
}

bool
xen_vm_wait_memory_target_live(xen_session *session, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VM.wait_memory_target_live", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_wait_memory_target_live_async(xen_session *session, xen_task *result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.wait_memory_target_live");
    return session->ok;
}

bool
xen_vm_get_cooperative(xen_session *session, bool *result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VM.get_cooperative");
    return session->ok;
}

bool
xen_vm_get_cooperative_async(xen_session *session, xen_task *result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.get_cooperative");
    return session->ok;
}

bool
xen_vm_set_hvm_shadow_multiplier(xen_session *session, xen_vm self, double value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_float,
              .u.float_val = value }
        };

    xen_call_(session, "VM.set_HVM_shadow_multiplier", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_shadow_multiplier_live(xen_session *session, xen_vm self, double multiplier)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_float,
              .u.float_val = multiplier }
        };

    xen_call_(session, "VM.set_shadow_multiplier_live", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_shadow_multiplier_live_async(xen_session *session, xen_task *result, xen_vm self, double multiplier)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_float,
              .u.float_val = multiplier }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_shadow_multiplier_live");
    return session->ok;
}

bool
xen_vm_set_vcpus_max(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_VCPUs_max", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_vcpus_at_startup(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_VCPUs_at_startup", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_send_sysrq(xen_session *session, xen_vm vm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VM.send_sysrq", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_send_sysrq_async(xen_session *session, xen_task *result, xen_vm vm, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.send_sysrq");
    return session->ok;
}

bool
xen_vm_send_trigger(xen_session *session, xen_vm vm, char *trigger)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = trigger }
        };

    xen_call_(session, "VM.send_trigger", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_send_trigger_async(xen_session *session, xen_task *result, xen_vm vm, char *trigger)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = trigger }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.send_trigger");
    return session->ok;
}

bool
xen_vm_maximise_memory(xen_session *session, int64_t *result, xen_vm self, int64_t total, bool approximate)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = total },
            { .type = &abstract_type_bool,
              .u.bool_val = approximate }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VM.maximise_memory");
    return session->ok;
}

bool
xen_vm_maximise_memory_async(xen_session *session, xen_task *result, xen_vm self, int64_t total, bool approximate)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = total },
            { .type = &abstract_type_bool,
              .u.bool_val = approximate }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.maximise_memory");
    return session->ok;
}

bool
xen_vm_migrate_send(xen_session *session, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)dest },
            { .type = &abstract_type_bool,
              .u.bool_val = live },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vdi_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vif_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    xen_call_(session, "VM.migrate_send", param_values, 6, NULL, NULL);
    return session->ok;
}

bool
xen_vm_migrate_send_async(xen_session *session, xen_task *result, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)dest },
            { .type = &abstract_type_bool,
              .u.bool_val = live },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vdi_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vif_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.migrate_send");
    return session->ok;
}

bool
xen_vm_assert_can_migrate(xen_session *session, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)dest },
            { .type = &abstract_type_bool,
              .u.bool_val = live },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vdi_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vif_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    xen_call_(session, "VM.assert_can_migrate", param_values, 6, NULL, NULL);
    return session->ok;
}

bool
xen_vm_assert_can_migrate_async(xen_session *session, xen_task *result, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)dest },
            { .type = &abstract_type_bool,
              .u.bool_val = live },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vdi_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)vif_map },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.assert_can_migrate");
    return session->ok;
}

bool
xen_vm_get_boot_record(xen_session *session, xen_vm_record **result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = xen_vm_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VM.get_boot_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_vm_record_data_source(xen_session *session, xen_vm self, char *data_source)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = data_source }
        };

    xen_call_(session, "VM.record_data_source", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_query_data_source(xen_session *session, double *result, xen_vm self, char *data_source)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = data_source }
        };

    abstract_type result_type = abstract_type_float;

    XEN_CALL_("VM.query_data_source");
    return session->ok;
}


bool
xen_vm_forget_data_source_archives(xen_session *session, xen_vm self, char *data_source)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = data_source }
        };

    xen_call_(session, "VM.forget_data_source_archives", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_assert_operation_valid(xen_session *session, xen_vm self, enum xen_vm_operations op)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_vm_operations_abstract_type_,
              .u.enum_val = op }
        };

    xen_call_(session, "VM.assert_operation_valid", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_assert_operation_valid_async(xen_session *session, xen_task *result, xen_vm self, enum xen_vm_operations op)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_vm_operations_abstract_type_,
              .u.enum_val = op }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.assert_operation_valid");
    return session->ok;
}

bool
xen_vm_update_allowed_operations(xen_session *session, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VM.update_allowed_operations", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_update_allowed_operations_async(xen_session *session, xen_task *result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.update_allowed_operations");
    return session->ok;
}

bool
xen_vm_get_allowed_vbd_devices(xen_session *session, struct xen_string_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_allowed_VBD_devices");
    return session->ok;
}


bool
xen_vm_get_allowed_vif_devices(xen_session *session, struct xen_string_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_allowed_VIF_devices");
    return session->ok;
}


bool
xen_vm_get_possible_hosts(xen_session *session, struct xen_host_set **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VM.get_possible_hosts");
    return session->ok;
}

bool
xen_vm_get_possible_hosts_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.get_possible_hosts");
    return session->ok;
}

bool
xen_vm_assert_can_boot_here(xen_session *session, xen_vm self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "VM.assert_can_boot_here", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_assert_can_boot_here_async(xen_session *session, xen_task *result, xen_vm self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.assert_can_boot_here");
    return session->ok;
}

bool
xen_vm_create_new_blob(xen_session *session, xen_blob *result, xen_vm vm, char *name, char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.create_new_blob");
    return session->ok;
}

bool
xen_vm_create_new_blob_async(xen_session *session, xen_task *result, xen_vm vm, char *name, char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.create_new_blob");
    return session->ok;
}

bool
xen_vm_assert_agile(xen_session *session, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "VM.assert_agile", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vm_assert_agile_async(xen_session *session, xen_task *result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.assert_agile");
    return session->ok;
}

bool
xen_vm_retrieve_wlb_recommendations(xen_session *session, xen_host_string_set_map **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string_string_set_map;

    *result = NULL;
    XEN_CALL_("VM.retrieve_wlb_recommendations");
    return session->ok;
}

bool
xen_vm_retrieve_wlb_recommendations_async(xen_session *session, xen_task *result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.retrieve_wlb_recommendations");
    return session->ok;
}

bool
xen_vm_copy_bios_strings(xen_session *session, xen_vm vm, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "VM.copy_bios_strings", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_copy_bios_strings_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.copy_bios_strings");
    return session->ok;
}

bool
xen_vm_set_protection_policy(xen_session *session, xen_vm self, xen_vmpp value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.set_protection_policy", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vm_set_start_delay(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_start_delay", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_start_delay_async(xen_session *session, xen_task *result, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_start_delay");
    return session->ok;
}

bool
xen_vm_set_shutdown_delay(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_shutdown_delay", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_shutdown_delay_async(xen_session *session, xen_task *result, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_shutdown_delay");
    return session->ok;
}

bool
xen_vm_set_order(xen_session *session, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VM.set_order", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_order_async(xen_session *session, xen_task *result, xen_vm self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_order");
    return session->ok;
}

bool
xen_vm_set_suspend_vdi(xen_session *session, xen_vm self, xen_vdi value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.set_suspend_VDI", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_suspend_vdi_async(xen_session *session, xen_task *result, xen_vm self, xen_vdi value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_suspend_VDI");
    return session->ok;
}

bool
xen_vm_assert_can_be_recovered(xen_session *session, xen_vm self, xen_session *session_to)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = session_to->session_id }
        };

    xen_call_(session, "VM.assert_can_be_recovered", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_assert_can_be_recovered_async(xen_session *session, xen_task *result, xen_vm self, xen_session *session_to)
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
    XEN_CALL_("Async.VM.assert_can_be_recovered");
    return session->ok;
}

bool
xen_vm_recover(xen_session *session, xen_vm self, xen_session *session_to, bool force)
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

    xen_call_(session, "VM.recover", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_vm_recover_async(xen_session *session, xen_task *result, xen_vm self, xen_session *session_to, bool force)
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
    XEN_CALL_("Async.VM.recover");
    return session->ok;
}

bool
xen_vm_import_convert(xen_session *session, char *type, char *username, char *password, xen_sr sr, xen_string_string_map *remote_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = username },
            { .type = &abstract_type_string,
              .u.string_val = password },
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)remote_config }
        };

    xen_call_(session, "VM.import_convert", param_values, 5, NULL, NULL);
    return session->ok;
}

bool
xen_vm_import_convert_async(xen_session *session, xen_task *result, char *type, char *username, char *password, xen_sr sr, xen_string_string_map *remote_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = username },
            { .type = &abstract_type_string,
              .u.string_val = password },
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)remote_config }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.import_convert");
    return session->ok;
}

bool
xen_vm_set_appliance(xen_session *session, xen_vm self, xen_vm_appliance value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VM.set_appliance", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vm_set_appliance_async(xen_session *session, xen_task *result, xen_vm self, xen_vm_appliance value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.set_appliance");
    return session->ok;
}

bool
xen_vm_query_services(xen_session *session, xen_string_string_map **result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VM.query_services");
    return session->ok;
}

bool
xen_vm_query_services_async(xen_session *session, xen_task *result, xen_vm self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VM.query_services");
    return session->ok;
}

bool
xen_vm_get_all(xen_session *session, struct xen_vm_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "VM.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vm_get_all_records(xen_session *session, xen_vm_xen_vm_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_vm_record_map;

    *result = NULL;
    xen_call_(session, "VM.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vm_get_uuid(xen_session *session, char **result, xen_vm vm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VM.get_uuid");
    return session->ok;
}

