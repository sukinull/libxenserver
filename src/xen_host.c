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

#include "xen_host_allowed_operations_internal.h"
#include "xen_internal.h"
#include "xen_string_host_allowed_operations_map_internal.h"
#include <xen/api/xen_blob.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_host.h>
#include <xen/api/xen_host_allowed_operations.h>
#include <xen/api/xen_host_cpu.h>
#include <xen/api/xen_host_crashdump.h>
#include <xen/api/xen_host_metrics.h>
#include <xen/api/xen_host_patch.h>
#include <xen/api/xen_host_xen_host_record_map.h>
#include <xen/api/xen_network.h>
#include <xen/api/xen_pbd.h>
#include <xen/api/xen_pci.h>
#include <xen/api/xen_pgpu.h>
#include <xen/api/xen_pif.h>
#include <xen/api/xen_sr.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_host_allowed_operations_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vm.h>
#include <xen/api/xen_vm_string_set_map.h>


XEN_FREE(xen_host)
XEN_SET_ALLOC_FREE(xen_host)
XEN_ALLOC(xen_host_record)
XEN_SET_ALLOC_FREE(xen_host_record)
XEN_ALLOC(xen_host_record_opt)
XEN_RECORD_OPT_FREE(xen_host)
XEN_SET_ALLOC_FREE(xen_host_record_opt)


static const struct_member xen_host_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, name_description) },
        { .key = "memory_overhead",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_record, memory_overhead) },
        { .key = "allowed_operations",
          .type = &xen_host_allowed_operations_set_abstract_type_,
          .offset = offsetof(xen_host_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_host_allowed_operations_map_abstract_type_,
          .offset = offsetof(xen_host_record, current_operations) },
        { .key = "API_version_major",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_record, api_version_major) },
        { .key = "API_version_minor",
          .type = &abstract_type_int,
          .offset = offsetof(xen_host_record, api_version_minor) },
        { .key = "API_version_vendor",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, api_version_vendor) },
        { .key = "API_version_vendor_implementation",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, api_version_vendor_implementation) },
        { .key = "enabled",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_host_record, enabled) },
        { .key = "software_version",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, software_version) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, other_config) },
        { .key = "capabilities",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_host_record, capabilities) },
        { .key = "cpu_configuration",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, cpu_configuration) },
        { .key = "sched_policy",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, sched_policy) },
        { .key = "supported_bootloaders",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_host_record, supported_bootloaders) },
        { .key = "resident_VMs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, resident_vms) },
        { .key = "logging",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, logging) },
        { .key = "PIFs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, pifs) },
        { .key = "suspend_image_sr",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_host_record, suspend_image_sr) },
        { .key = "crash_dump_sr",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_host_record, crash_dump_sr) },
        { .key = "crashdumps",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, crashdumps) },
        { .key = "patches",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, patches) },
        { .key = "PBDs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, pbds) },
        { .key = "host_CPUs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, host_cpus) },
        { .key = "cpu_info",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, cpu_info) },
        { .key = "hostname",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, hostname) },
        { .key = "address",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, address) },
        { .key = "metrics",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_host_record, metrics) },
        { .key = "license_params",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, license_params) },
        { .key = "ha_statefiles",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_host_record, ha_statefiles) },
        { .key = "ha_network_peers",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_host_record, ha_network_peers) },
        { .key = "blobs",
          .type = &abstract_type_string_ref_map,
          .offset = offsetof(xen_host_record, blobs) },
        { .key = "tags",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_host_record, tags) },
        { .key = "external_auth_type",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, external_auth_type) },
        { .key = "external_auth_service_name",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, external_auth_service_name) },
        { .key = "external_auth_configuration",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, external_auth_configuration) },
        { .key = "edition",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, edition) },
        { .key = "license_server",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, license_server) },
        { .key = "bios_strings",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, bios_strings) },
        { .key = "power_on_mode",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, power_on_mode) },
        { .key = "power_on_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, power_on_config) },
        { .key = "local_cache_sr",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_host_record, local_cache_sr) },
        { .key = "chipset_info",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, chipset_info) },
        { .key = "PCIs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, pcis) },
        { .key = "PGPUs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, pgpus) }
    };

const abstract_type xen_host_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_host_record),
       .member_count =
           sizeof(xen_host_record_struct_members) / sizeof(struct_member),
       .members = xen_host_record_struct_members
    };


static const struct struct_member xen_host_xen_host_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_host_xen_host_record_map_contents, key)
    },
    {
        .type = &xen_host_record_abstract_type_,
        .offset = offsetof(xen_host_xen_host_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_host_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_host_xen_host_record_map_contents),
    .members = xen_host_xen_host_record_members
};


void
xen_host_record_free(xen_host_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_host_allowed_operations_set_free(record->allowed_operations);
    xen_string_host_allowed_operations_map_free(record->current_operations);
    free(record->api_version_vendor);
    xen_string_string_map_free(record->api_version_vendor_implementation);
    xen_string_string_map_free(record->software_version);
    xen_string_string_map_free(record->other_config);
    xen_string_set_free(record->capabilities);
    xen_string_string_map_free(record->cpu_configuration);
    free(record->sched_policy);
    xen_string_set_free(record->supported_bootloaders);
    xen_vm_record_opt_set_free(record->resident_vms);
    xen_string_string_map_free(record->logging);
    xen_pif_record_opt_set_free(record->pifs);
    xen_sr_record_opt_free(record->suspend_image_sr);
    xen_sr_record_opt_free(record->crash_dump_sr);
    xen_host_crashdump_record_opt_set_free(record->crashdumps);
    xen_host_patch_record_opt_set_free(record->patches);
    xen_pbd_record_opt_set_free(record->pbds);
    xen_host_cpu_record_opt_set_free(record->host_cpus);
    xen_string_string_map_free(record->cpu_info);
    free(record->hostname);
    free(record->address);
    xen_host_metrics_record_opt_free(record->metrics);
    xen_string_string_map_free(record->license_params);
    xen_string_set_free(record->ha_statefiles);
    xen_string_set_free(record->ha_network_peers);
    xen_string_blob_map_free(record->blobs);
    xen_string_set_free(record->tags);
    free(record->external_auth_type);
    free(record->external_auth_service_name);
    xen_string_string_map_free(record->external_auth_configuration);
    free(record->edition);
    xen_string_string_map_free(record->license_server);
    xen_string_string_map_free(record->bios_strings);
    free(record->power_on_mode);
    xen_string_string_map_free(record->power_on_config);
    xen_sr_record_opt_free(record->local_cache_sr);
    xen_string_string_map_free(record->chipset_info);
    xen_pci_record_opt_set_free(record->pcis);
    xen_pgpu_record_opt_set_free(record->pgpus);
    free(record);
}


bool
xen_host_get_record(xen_session *session, xen_host_record **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = xen_host_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("host.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_host_get_by_uuid(xen_session *session, xen_host *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_by_uuid");
    return session->ok;
}


bool
xen_host_get_by_name_label(xen_session *session, struct xen_host_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_by_name_label");
    return session->ok;
}


bool
xen_host_get_name_label(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_name_label");
    return session->ok;
}


bool
xen_host_get_name_description(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_name_description");
    return session->ok;
}


bool
xen_host_get_memory_overhead(xen_session *session, int64_t *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host.get_memory_overhead");
    return session->ok;
}


bool
xen_host_get_allowed_operations(xen_session *session, struct xen_host_allowed_operations_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = xen_host_allowed_operations_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("host.get_allowed_operations");
    return session->ok;
}


bool
xen_host_get_current_operations(xen_session *session, xen_string_host_allowed_operations_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = string_host_allowed_operations_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("host.get_current_operations");
    return session->ok;
}


bool
xen_host_get_api_version_major(xen_session *session, int64_t *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host.get_API_version_major");
    return session->ok;
}


bool
xen_host_get_api_version_minor(xen_session *session, int64_t *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host.get_API_version_minor");
    return session->ok;
}


bool
xen_host_get_api_version_vendor(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_API_version_vendor");
    return session->ok;
}


bool
xen_host_get_api_version_vendor_implementation(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_API_version_vendor_implementation");
    return session->ok;
}


bool
xen_host_get_enabled(xen_session *session, bool *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("host.get_enabled");
    return session->ok;
}


bool
xen_host_get_software_version(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_software_version");
    return session->ok;
}


bool
xen_host_get_other_config(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_other_config");
    return session->ok;
}


bool
xen_host_get_capabilities(xen_session *session, struct xen_string_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_capabilities");
    return session->ok;
}


bool
xen_host_get_cpu_configuration(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_cpu_configuration");
    return session->ok;
}


bool
xen_host_get_sched_policy(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_sched_policy");
    return session->ok;
}


bool
xen_host_get_supported_bootloaders(xen_session *session, struct xen_string_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_supported_bootloaders");
    return session->ok;
}


bool
xen_host_get_resident_vms(xen_session *session, struct xen_vm_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_resident_VMs");
    return session->ok;
}


bool
xen_host_get_logging(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_logging");
    return session->ok;
}


bool
xen_host_get_pifs(xen_session *session, struct xen_pif_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_PIFs");
    return session->ok;
}


bool
xen_host_get_suspend_image_sr(xen_session *session, xen_sr *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_suspend_image_sr");
    return session->ok;
}


bool
xen_host_get_crash_dump_sr(xen_session *session, xen_sr *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_crash_dump_sr");
    return session->ok;
}


bool
xen_host_get_crashdumps(xen_session *session, struct xen_host_crashdump_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_crashdumps");
    return session->ok;
}


bool
xen_host_get_patches(xen_session *session, struct xen_host_patch_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_patches");
    return session->ok;
}


bool
xen_host_get_pbds(xen_session *session, struct xen_pbd_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_PBDs");
    return session->ok;
}


bool
xen_host_get_host_cpus(xen_session *session, struct xen_host_cpu_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_host_CPUs");
    return session->ok;
}


bool
xen_host_get_cpu_info(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_cpu_info");
    return session->ok;
}


bool
xen_host_get_hostname(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_hostname");
    return session->ok;
}


bool
xen_host_get_address(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_address");
    return session->ok;
}


bool
xen_host_get_metrics(xen_session *session, xen_host_metrics *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_metrics");
    return session->ok;
}


bool
xen_host_get_license_params(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_license_params");
    return session->ok;
}


bool
xen_host_get_ha_statefiles(xen_session *session, struct xen_string_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_ha_statefiles");
    return session->ok;
}


bool
xen_host_get_ha_network_peers(xen_session *session, struct xen_string_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_ha_network_peers");
    return session->ok;
}


bool
xen_host_get_blobs(xen_session *session, xen_string_blob_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_blobs");
    return session->ok;
}


bool
xen_host_get_tags(xen_session *session, struct xen_string_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_tags");
    return session->ok;
}


bool
xen_host_get_external_auth_type(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_external_auth_type");
    return session->ok;
}


bool
xen_host_get_external_auth_service_name(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_external_auth_service_name");
    return session->ok;
}


bool
xen_host_get_external_auth_configuration(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_external_auth_configuration");
    return session->ok;
}


bool
xen_host_get_edition(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_edition");
    return session->ok;
}


bool
xen_host_get_license_server(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_license_server");
    return session->ok;
}


bool
xen_host_get_bios_strings(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_bios_strings");
    return session->ok;
}


bool
xen_host_get_power_on_mode(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_power_on_mode");
    return session->ok;
}


bool
xen_host_get_power_on_config(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_power_on_config");
    return session->ok;
}


bool
xen_host_get_local_cache_sr(xen_session *session, xen_sr *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_local_cache_sr");
    return session->ok;
}


bool
xen_host_get_chipset_info(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_chipset_info");
    return session->ok;
}


bool
xen_host_get_pcis(xen_session *session, struct xen_pci_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_PCIs");
    return session->ok;
}


bool
xen_host_get_pgpus(xen_session *session, struct xen_pgpu_set **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_PGPUs");
    return session->ok;
}


bool
xen_host_set_name_label(xen_session *session, xen_host host, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    xen_call_(session, "host.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_name_description(xen_session *session, xen_host host, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    xen_call_(session, "host.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_other_config(xen_session *session, xen_host host, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "host.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_add_to_other_config(xen_session *session, xen_host host, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "host.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_host_remove_from_other_config(xen_session *session, xen_host host, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "host.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_logging(xen_session *session, xen_host host, xen_string_string_map *logging)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)logging }
        };

    xen_call_(session, "host.set_logging", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_add_to_logging(xen_session *session, xen_host host, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "host.add_to_logging", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_host_remove_from_logging(xen_session *session, xen_host host, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "host.remove_from_logging", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_suspend_image_sr(xen_session *session, xen_host host, xen_sr suspend_image_sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = suspend_image_sr }
        };

    xen_call_(session, "host.set_suspend_image_sr", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_crash_dump_sr(xen_session *session, xen_host host, xen_sr crash_dump_sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = crash_dump_sr }
        };

    xen_call_(session, "host.set_crash_dump_sr", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_hostname(xen_session *session, xen_host host, char *hostname)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = hostname }
        };

    xen_call_(session, "host.set_hostname", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_address(xen_session *session, xen_host host, char *address)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = address }
        };

    xen_call_(session, "host.set_address", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_tags(xen_session *session, xen_host host, struct xen_string_set *tags)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)tags }
        };

    xen_call_(session, "host.set_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_add_tags(xen_session *session, xen_host host, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "host.add_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_remove_tags(xen_session *session, xen_host host, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "host.remove_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_license_server(xen_session *session, xen_host host, xen_string_string_map *license_server)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)license_server }
        };

    xen_call_(session, "host.set_license_server", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_add_to_license_server(xen_session *session, xen_host host, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "host.add_to_license_server", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_host_remove_from_license_server(xen_session *session, xen_host host, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "host.remove_from_license_server", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_disable(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.disable", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_disable_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.disable");
    return session->ok;
}

bool
xen_host_enable(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.enable", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_enable_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.enable");
    return session->ok;
}

bool
xen_host_shutdown(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.shutdown", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_shutdown_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.shutdown");
    return session->ok;
}

bool
xen_host_reboot(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.reboot", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_reboot_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.reboot");
    return session->ok;
}

bool
xen_host_dmesg(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.dmesg");
    return session->ok;
}

bool
xen_host_dmesg_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.dmesg");
    return session->ok;
}

bool
xen_host_dmesg_clear(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.dmesg_clear");
    return session->ok;
}

bool
xen_host_dmesg_clear_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.dmesg_clear");
    return session->ok;
}

bool
xen_host_get_log(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_log");
    return session->ok;
}

bool
xen_host_get_log_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.get_log");
    return session->ok;
}

bool
xen_host_send_debug_keys(xen_session *session, xen_host host, char *keys)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = keys }
        };

    xen_call_(session, "host.send_debug_keys", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_host_send_debug_keys_async(xen_session *session, xen_task *result, xen_host host, char *keys)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = keys }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.send_debug_keys");
    return session->ok;
}

bool
xen_host_bugreport_upload(xen_session *session, xen_host host, char *url, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = url },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    xen_call_(session, "host.bugreport_upload", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_host_bugreport_upload_async(xen_session *session, xen_task *result, xen_host host, char *url, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = url },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.bugreport_upload");
    return session->ok;
}

bool
xen_host_list_methods(xen_session *session, struct xen_string_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "host.list_methods", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_license_apply(xen_session *session, xen_host host, char *contents)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = contents }
        };

    xen_call_(session, "host.license_apply", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_host_license_apply_async(xen_session *session, xen_task *result, xen_host host, char *contents)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = contents }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.license_apply");
    return session->ok;
}

bool
xen_host_destroy(xen_session *session, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "host.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_destroy_async(xen_session *session, xen_task *result, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.destroy");
    return session->ok;
}

bool
xen_host_power_on(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.power_on", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_power_on_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.power_on");
    return session->ok;
}

bool
xen_host_emergency_ha_disable(xen_session *session)
{

    xen_call_(session, "host.emergency_ha_disable", NULL, 0, NULL, NULL);
    return session->ok;
}


bool
xen_host_record_data_source(xen_session *session, xen_host host, char *data_source)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = data_source }
        };

    xen_call_(session, "host.record_data_source", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_query_data_source(xen_session *session, double *result, xen_host host, char *data_source)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = data_source }
        };

    abstract_type result_type = abstract_type_float;

    XEN_CALL_("host.query_data_source");
    return session->ok;
}


bool
xen_host_forget_data_source_archives(xen_session *session, xen_host host, char *data_source)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = data_source }
        };

    xen_call_(session, "host.forget_data_source_archives", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_assert_can_evacuate(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.assert_can_evacuate", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_assert_can_evacuate_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.assert_can_evacuate");
    return session->ok;
}

bool
xen_host_get_vms_which_prevent_evacuation(xen_session *session, xen_vm_string_set_map **result, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string_string_set_map;

    *result = NULL;
    XEN_CALL_("host.get_vms_which_prevent_evacuation");
    return session->ok;
}

bool
xen_host_get_vms_which_prevent_evacuation_async(xen_session *session, xen_task *result, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.get_vms_which_prevent_evacuation");
    return session->ok;
}

bool
xen_host_get_uncooperative_resident_vms(xen_session *session, struct xen_vm_set **result, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_uncooperative_resident_VMs");
    return session->ok;
}

bool
xen_host_get_uncooperative_resident_vms_async(xen_session *session, xen_task *result, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.get_uncooperative_resident_VMs");
    return session->ok;
}

bool
xen_host_evacuate(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.evacuate", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_evacuate_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.evacuate");
    return session->ok;
}

bool
xen_host_syslog_reconfigure(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.syslog_reconfigure", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_syslog_reconfigure_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.syslog_reconfigure");
    return session->ok;
}

bool
xen_host_management_reconfigure(xen_session *session, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    xen_call_(session, "host.management_reconfigure", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_management_reconfigure_async(xen_session *session, xen_task *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.management_reconfigure");
    return session->ok;
}

bool
xen_host_local_management_reconfigure(xen_session *session, char *interface)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = interface }
        };

    xen_call_(session, "host.local_management_reconfigure", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_management_disable(xen_session *session)
{

    xen_call_(session, "host.management_disable", NULL, 0, NULL, NULL);
    return session->ok;
}


bool
xen_host_get_management_interface(xen_session *session, xen_pif *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_management_interface");
    return session->ok;
}

bool
xen_host_get_management_interface_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.get_management_interface");
    return session->ok;
}

bool
xen_host_get_system_status_capabilities(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_system_status_capabilities");
    return session->ok;
}


bool
xen_host_restart_agent(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.restart_agent", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_restart_agent_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.restart_agent");
    return session->ok;
}

bool
xen_host_shutdown_agent(xen_session *session)
{

    xen_call_(session, "host.shutdown_agent", NULL, 0, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_hostname_live(xen_session *session, xen_host host, char *hostname)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = hostname }
        };

    xen_call_(session, "host.set_hostname_live", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_compute_free_memory(xen_session *session, int64_t *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host.compute_free_memory");
    return session->ok;
}

bool
xen_host_compute_free_memory_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.compute_free_memory");
    return session->ok;
}

bool
xen_host_compute_memory_overhead(xen_session *session, int64_t *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("host.compute_memory_overhead");
    return session->ok;
}

bool
xen_host_compute_memory_overhead_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.compute_memory_overhead");
    return session->ok;
}

bool
xen_host_sync_data(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.sync_data", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_backup_rrds(xen_session *session, xen_host host, double delay)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_float,
              .u.float_val = delay }
        };

    xen_call_(session, "host.backup_rrds", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_create_new_blob(xen_session *session, xen_blob *result, xen_host host, char *name, char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.create_new_blob");
    return session->ok;
}

bool
xen_host_create_new_blob_async(xen_session *session, xen_task *result, xen_host host, char *name, char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.create_new_blob");
    return session->ok;
}

bool
xen_host_call_plugin(xen_session *session, char **result, xen_host host, char *plugin, char *fn, xen_string_string_map *args)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = plugin },
            { .type = &abstract_type_string,
              .u.string_val = fn },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)args }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.call_plugin");
    return session->ok;
}

bool
xen_host_call_plugin_async(xen_session *session, xen_task *result, xen_host host, char *plugin, char *fn, xen_string_string_map *args)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = plugin },
            { .type = &abstract_type_string,
              .u.string_val = fn },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)args }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.call_plugin");
    return session->ok;
}

bool
xen_host_get_servertime(xen_session *session, time_t *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("host.get_servertime");
    return session->ok;
}


bool
xen_host_get_server_localtime(xen_session *session, time_t *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("host.get_server_localtime");
    return session->ok;
}


bool
xen_host_enable_external_auth(xen_session *session, xen_host host, xen_string_string_map *config, char *service_name, char *auth_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)config },
            { .type = &abstract_type_string,
              .u.string_val = service_name },
            { .type = &abstract_type_string,
              .u.string_val = auth_type }
        };

    xen_call_(session, "host.enable_external_auth", param_values, 4, NULL, NULL);
    return session->ok;
}


bool
xen_host_disable_external_auth(xen_session *session, xen_host host, xen_string_string_map *config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)config }
        };

    xen_call_(session, "host.disable_external_auth", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_retrieve_wlb_evacuate_recommendations(xen_session *session, xen_vm_string_set_map **result, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string_string_set_map;

    *result = NULL;
    XEN_CALL_("host.retrieve_wlb_evacuate_recommendations");
    return session->ok;
}

bool
xen_host_retrieve_wlb_evacuate_recommendations_async(xen_session *session, xen_task *result, xen_host self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.retrieve_wlb_evacuate_recommendations");
    return session->ok;
}

bool
xen_host_get_server_certificate(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_server_certificate");
    return session->ok;
}

bool
xen_host_get_server_certificate_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.get_server_certificate");
    return session->ok;
}

bool
xen_host_apply_edition(xen_session *session, xen_host host, char *edition)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = edition }
        };

    xen_call_(session, "host.apply_edition", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_refresh_pack_info(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.refresh_pack_info", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_host_refresh_pack_info_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.refresh_pack_info");
    return session->ok;
}

bool
xen_host_set_power_on_mode(xen_session *session, xen_host self, char *power_on_mode, xen_string_string_map *power_on_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = power_on_mode },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)power_on_config }
        };

    xen_call_(session, "host.set_power_on_mode", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_host_set_power_on_mode_async(xen_session *session, xen_task *result, xen_host self, char *power_on_mode, xen_string_string_map *power_on_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = power_on_mode },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)power_on_config }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.set_power_on_mode");
    return session->ok;
}

bool
xen_host_set_cpu_features(xen_session *session, xen_host host, char *features)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = features }
        };

    xen_call_(session, "host.set_cpu_features", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_reset_cpu_features(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.reset_cpu_features", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_enable_local_storage_caching(xen_session *session, xen_host host, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "host.enable_local_storage_caching", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_disable_local_storage_caching(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.disable_local_storage_caching", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_migrate_receive(xen_session *session, xen_string_string_map **result, xen_host host, xen_network network, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.migrate_receive");
    return session->ok;
}

bool
xen_host_migrate_receive_async(xen_session *session, xen_task *result, xen_host host, xen_network network, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.host.migrate_receive");
    return session->ok;
}

bool
xen_host_get_all(xen_session *session, struct xen_host_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "host.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_get_all_records(xen_session *session, xen_host_xen_host_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_host_record_map;

    *result = NULL;
    xen_call_(session, "host.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_get_uuid(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_uuid");
    return session->ok;
}

