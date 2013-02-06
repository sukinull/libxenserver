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


#ifndef XEN_HOST_H
#define XEN_HOST_H

#include <xen/api/xen_blob_decl.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_host_allowed_operations.h>
#include <xen/api/xen_host_cpu_decl.h>
#include <xen/api/xen_host_crashdump_decl.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_host_metrics_decl.h>
#include <xen/api/xen_host_patch_decl.h>
#include <xen/api/xen_host_xen_host_record_map.h>
#include <xen/api/xen_network_decl.h>
#include <xen/api/xen_pbd_decl.h>
#include <xen/api/xen_pci_decl.h>
#include <xen/api/xen_pgpu_decl.h>
#include <xen/api/xen_pif_decl.h>
#include <xen/api/xen_sr_decl.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_host_allowed_operations_map.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vm_decl.h>
#include <xen/api/xen_vm_string_set_map.h>


/*
 * The host class.
 * 
 * A physical host.
 */


/**
 * Free the given xen_host.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_host_free(xen_host host);


typedef struct xen_host_set
{
    size_t size;
    xen_host *contents[];
} xen_host_set;

/**
 * Allocate a xen_host_set of the given size.
 */
extern xen_host_set *
xen_host_set_alloc(size_t size);

/**
 * Free the given xen_host_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_host_set_free(xen_host_set *set);


typedef struct xen_host_record
{
    xen_host handle;
    char *uuid;
    char *name_label;
    char *name_description;
    int64_t memory_overhead;
    struct xen_host_allowed_operations_set *allowed_operations;
    xen_string_host_allowed_operations_map *current_operations;
    int64_t api_version_major;
    int64_t api_version_minor;
    char *api_version_vendor;
    xen_string_string_map *api_version_vendor_implementation;
    bool enabled;
    xen_string_string_map *software_version;
    xen_string_string_map *other_config;
    struct xen_string_set *capabilities;
    xen_string_string_map *cpu_configuration;
    char *sched_policy;
    struct xen_string_set *supported_bootloaders;
    struct xen_vm_record_opt_set *resident_vms;
    xen_string_string_map *logging;
    struct xen_pif_record_opt_set *pifs;
    struct xen_sr_record_opt *suspend_image_sr;
    struct xen_sr_record_opt *crash_dump_sr;
    struct xen_host_crashdump_record_opt_set *crashdumps;
    struct xen_host_patch_record_opt_set *patches;
    struct xen_pbd_record_opt_set *pbds;
    struct xen_host_cpu_record_opt_set *host_cpus;
    xen_string_string_map *cpu_info;
    char *hostname;
    char *address;
    struct xen_host_metrics_record_opt *metrics;
    xen_string_string_map *license_params;
    struct xen_string_set *ha_statefiles;
    struct xen_string_set *ha_network_peers;
    xen_string_blob_map *blobs;
    struct xen_string_set *tags;
    char *external_auth_type;
    char *external_auth_service_name;
    xen_string_string_map *external_auth_configuration;
    char *edition;
    xen_string_string_map *license_server;
    xen_string_string_map *bios_strings;
    char *power_on_mode;
    xen_string_string_map *power_on_config;
    struct xen_sr_record_opt *local_cache_sr;
    xen_string_string_map *chipset_info;
    struct xen_pci_record_opt_set *pcis;
    struct xen_pgpu_record_opt_set *pgpus;
} xen_host_record;

/**
 * Allocate a xen_host_record.
 */
extern xen_host_record *
xen_host_record_alloc(void);

/**
 * Free the given xen_host_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_host_record_free(xen_host_record *record);


typedef struct xen_host_record_opt
{
    bool is_record;
    union
    {
        xen_host handle;
        xen_host_record *record;
    } u;
} xen_host_record_opt;

/**
 * Allocate a xen_host_record_opt.
 */
extern xen_host_record_opt *
xen_host_record_opt_alloc(void);

/**
 * Free the given xen_host_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_host_record_opt_free(xen_host_record_opt *record_opt);


typedef struct xen_host_record_set
{
    size_t size;
    xen_host_record *contents[];
} xen_host_record_set;

/**
 * Allocate a xen_host_record_set of the given size.
 */
extern xen_host_record_set *
xen_host_record_set_alloc(size_t size);

/**
 * Free the given xen_host_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_host_record_set_free(xen_host_record_set *set);



typedef struct xen_host_record_opt_set
{
    size_t size;
    xen_host_record_opt *contents[];
} xen_host_record_opt_set;

/**
 * Allocate a xen_host_record_opt_set of the given size.
 */
extern xen_host_record_opt_set *
xen_host_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_host_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_host_record_opt_set_free(xen_host_record_opt_set *set);


/**
 * Get a record containing the current state of the given host.
 */
extern bool
xen_host_get_record(xen_session *session, xen_host_record **result, xen_host host);


/**
 * Get a reference to the host instance with the specified UUID.
 */
extern bool
xen_host_get_by_uuid(xen_session *session, xen_host *result, const char *uuid);


/**
 * Get all the host instances with the given label.
 */
extern bool
xen_host_get_by_name_label(xen_session *session, struct xen_host_set **result, const char *label);


/**
 * Get the uuid field of the given host.
 */
extern bool
xen_host_get_uuid(xen_session *session, char **result, xen_host host);


/**
 * Get the name/label field of the given host.
 */
extern bool
xen_host_get_name_label(xen_session *session, char **result, xen_host host);


/**
 * Get the name/description field of the given host.
 */
extern bool
xen_host_get_name_description(xen_session *session, char **result, xen_host host);


/**
 * Get the memory/overhead field of the given host.
 */
extern bool
xen_host_get_memory_overhead(xen_session *session, int64_t *result, xen_host host);


/**
 * Get the allowed_operations field of the given host.
 */
extern bool
xen_host_get_allowed_operations(xen_session *session, struct xen_host_allowed_operations_set **result, xen_host host);


/**
 * Get the current_operations field of the given host.
 */
extern bool
xen_host_get_current_operations(xen_session *session, xen_string_host_allowed_operations_map **result, xen_host host);


/**
 * Get the API_version/major field of the given host.
 */
extern bool
xen_host_get_api_version_major(xen_session *session, int64_t *result, xen_host host);


/**
 * Get the API_version/minor field of the given host.
 */
extern bool
xen_host_get_api_version_minor(xen_session *session, int64_t *result, xen_host host);


/**
 * Get the API_version/vendor field of the given host.
 */
extern bool
xen_host_get_api_version_vendor(xen_session *session, char **result, xen_host host);


/**
 * Get the API_version/vendor_implementation field of the given host.
 */
extern bool
xen_host_get_api_version_vendor_implementation(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the enabled field of the given host.
 */
extern bool
xen_host_get_enabled(xen_session *session, bool *result, xen_host host);


/**
 * Get the software_version field of the given host.
 */
extern bool
xen_host_get_software_version(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the other_config field of the given host.
 */
extern bool
xen_host_get_other_config(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the capabilities field of the given host.
 */
extern bool
xen_host_get_capabilities(xen_session *session, struct xen_string_set **result, xen_host host);


/**
 * Get the cpu_configuration field of the given host.
 */
extern bool
xen_host_get_cpu_configuration(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the sched_policy field of the given host.
 */
extern bool
xen_host_get_sched_policy(xen_session *session, char **result, xen_host host);


/**
 * Get the supported_bootloaders field of the given host.
 */
extern bool
xen_host_get_supported_bootloaders(xen_session *session, struct xen_string_set **result, xen_host host);


/**
 * Get the resident_VMs field of the given host.
 */
extern bool
xen_host_get_resident_vms(xen_session *session, struct xen_vm_set **result, xen_host host);


/**
 * Get the logging field of the given host.
 */
extern bool
xen_host_get_logging(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the PIFs field of the given host.
 */
extern bool
xen_host_get_pifs(xen_session *session, struct xen_pif_set **result, xen_host host);


/**
 * Get the suspend_image_sr field of the given host.
 */
extern bool
xen_host_get_suspend_image_sr(xen_session *session, xen_sr *result, xen_host host);


/**
 * Get the crash_dump_sr field of the given host.
 */
extern bool
xen_host_get_crash_dump_sr(xen_session *session, xen_sr *result, xen_host host);


/**
 * Get the crashdumps field of the given host.
 */
extern bool
xen_host_get_crashdumps(xen_session *session, struct xen_host_crashdump_set **result, xen_host host);


/**
 * Get the patches field of the given host.
 */
extern bool
xen_host_get_patches(xen_session *session, struct xen_host_patch_set **result, xen_host host);


/**
 * Get the PBDs field of the given host.
 */
extern bool
xen_host_get_pbds(xen_session *session, struct xen_pbd_set **result, xen_host host);


/**
 * Get the host_CPUs field of the given host.
 */
extern bool
xen_host_get_host_cpus(xen_session *session, struct xen_host_cpu_set **result, xen_host host);


/**
 * Get the cpu_info field of the given host.
 */
extern bool
xen_host_get_cpu_info(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the hostname field of the given host.
 */
extern bool
xen_host_get_hostname(xen_session *session, char **result, xen_host host);


/**
 * Get the address field of the given host.
 */
extern bool
xen_host_get_address(xen_session *session, char **result, xen_host host);


/**
 * Get the metrics field of the given host.
 */
extern bool
xen_host_get_metrics(xen_session *session, xen_host_metrics *result, xen_host host);


/**
 * Get the license_params field of the given host.
 */
extern bool
xen_host_get_license_params(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the ha_statefiles field of the given host.
 */
extern bool
xen_host_get_ha_statefiles(xen_session *session, struct xen_string_set **result, xen_host host);


/**
 * Get the ha_network_peers field of the given host.
 */
extern bool
xen_host_get_ha_network_peers(xen_session *session, struct xen_string_set **result, xen_host host);


/**
 * Get the blobs field of the given host.
 */
extern bool
xen_host_get_blobs(xen_session *session, xen_string_blob_map **result, xen_host host);


/**
 * Get the tags field of the given host.
 */
extern bool
xen_host_get_tags(xen_session *session, struct xen_string_set **result, xen_host host);


/**
 * Get the external_auth_type field of the given host.
 */
extern bool
xen_host_get_external_auth_type(xen_session *session, char **result, xen_host host);


/**
 * Get the external_auth_service_name field of the given host.
 */
extern bool
xen_host_get_external_auth_service_name(xen_session *session, char **result, xen_host host);


/**
 * Get the external_auth_configuration field of the given host.
 */
extern bool
xen_host_get_external_auth_configuration(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the edition field of the given host.
 */
extern bool
xen_host_get_edition(xen_session *session, char **result, xen_host host);


/**
 * Get the license_server field of the given host.
 */
extern bool
xen_host_get_license_server(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the bios_strings field of the given host.
 */
extern bool
xen_host_get_bios_strings(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the power_on_mode field of the given host.
 */
extern bool
xen_host_get_power_on_mode(xen_session *session, char **result, xen_host host);


/**
 * Get the power_on_config field of the given host.
 */
extern bool
xen_host_get_power_on_config(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the local_cache_sr field of the given host.
 */
extern bool
xen_host_get_local_cache_sr(xen_session *session, xen_sr *result, xen_host host);


/**
 * Get the chipset_info field of the given host.
 */
extern bool
xen_host_get_chipset_info(xen_session *session, xen_string_string_map **result, xen_host host);


/**
 * Get the PCIs field of the given host.
 */
extern bool
xen_host_get_pcis(xen_session *session, struct xen_pci_set **result, xen_host host);


/**
 * Get the PGPUs field of the given host.
 */
extern bool
xen_host_get_pgpus(xen_session *session, struct xen_pgpu_set **result, xen_host host);


/**
 * Set the name/label field of the given host.
 */
extern bool
xen_host_set_name_label(xen_session *session, xen_host host, const char *label);


/**
 * Set the name/description field of the given host.
 */
extern bool
xen_host_set_name_description(xen_session *session, xen_host host, const char *description);


/**
 * Set the other_config field of the given host.
 */
extern bool
xen_host_set_other_config(xen_session *session, xen_host host, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * host.
 */
extern bool
xen_host_add_to_other_config(xen_session *session, xen_host host, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given host.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_host_remove_from_other_config(xen_session *session, xen_host host, const char *key);


/**
 * Set the logging field of the given host.
 */
extern bool
xen_host_set_logging(xen_session *session, xen_host host, xen_string_string_map *logging);


/**
 * Add the given key-value pair to the logging field of the given host.
 */
extern bool
xen_host_add_to_logging(xen_session *session, xen_host host, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the logging
 * field of the given host.  If the key is not in that Map, then do nothing.
 */
extern bool
xen_host_remove_from_logging(xen_session *session, xen_host host, const char *key);


/**
 * Set the suspend_image_sr field of the given host.
 */
extern bool
xen_host_set_suspend_image_sr(xen_session *session, xen_host host, xen_sr suspend_image_sr);


/**
 * Set the crash_dump_sr field of the given host.
 */
extern bool
xen_host_set_crash_dump_sr(xen_session *session, xen_host host, xen_sr crash_dump_sr);


/**
 * Set the hostname field of the given host.
 */
extern bool
xen_host_set_hostname(xen_session *session, xen_host host, const char *hostname);


/**
 * Set the address field of the given host.
 */
extern bool
xen_host_set_address(xen_session *session, xen_host host, const char *address);


/**
 * Set the tags field of the given host.
 */
extern bool
xen_host_set_tags(xen_session *session, xen_host host, struct xen_string_set *tags);


/**
 * Add the given value to the tags field of the given host.  If the
 * value is already in that Set, then do nothing.
 */
extern bool
xen_host_add_tags(xen_session *session, xen_host host, const char *value);


/**
 * Remove the given value from the tags field of the given host.  If
 * the value is not in that Set, then do nothing.
 */
extern bool
xen_host_remove_tags(xen_session *session, xen_host host, const char *value);


/**
 * Set the license_server field of the given host.
 */
extern bool
xen_host_set_license_server(xen_session *session, xen_host host, xen_string_string_map *license_server);


/**
 * Add the given key-value pair to the license_server field of the
 * given host.
 */
extern bool
xen_host_add_to_license_server(xen_session *session, xen_host host, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * license_server field of the given host.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_host_remove_from_license_server(xen_session *session, xen_host host, const char *key);


/**
 * Puts the host into a state in which no new VMs can be started.
 * Currently active VMs on the host continue to execute.
 */
extern bool
xen_host_disable(xen_session *session, xen_host host);

/**
 * Puts the host into a state in which no new VMs can be started.
 * Currently active VMs on the host continue to execute.
 */
extern bool
xen_host_disable_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Puts the host into a state in which new VMs can be started.
 */
extern bool
xen_host_enable(xen_session *session, xen_host host);

/**
 * Puts the host into a state in which new VMs can be started.
 */
extern bool
xen_host_enable_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Shutdown the host. (This function can only be called if there are no
 * currently running VMs on the host and it is disabled.).
 */
extern bool
xen_host_shutdown(xen_session *session, xen_host host);

/**
 * Shutdown the host. (This function can only be called if there are no
 * currently running VMs on the host and it is disabled.).
 */
extern bool
xen_host_shutdown_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Reboot the host. (This function can only be called if there are no
 * currently running VMs on the host and it is disabled.).
 */
extern bool
xen_host_reboot(xen_session *session, xen_host host);

/**
 * Reboot the host. (This function can only be called if there are no
 * currently running VMs on the host and it is disabled.).
 */
extern bool
xen_host_reboot_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Get the host xen dmesg.
 */
extern bool
xen_host_dmesg(xen_session *session, char **result, xen_host host);

/**
 * Get the host xen dmesg.
 */
extern bool
xen_host_dmesg_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Get the host xen dmesg, and clear the buffer.
 */
extern bool
xen_host_dmesg_clear(xen_session *session, char **result, xen_host host);

/**
 * Get the host xen dmesg, and clear the buffer.
 */
extern bool
xen_host_dmesg_clear_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Get the host's log file.
 */
extern bool
xen_host_get_log(xen_session *session, char **result, xen_host host);

/**
 * Get the host's log file.
 */
extern bool
xen_host_get_log_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Inject the given string as debugging keys into Xen.
 */
extern bool
xen_host_send_debug_keys(xen_session *session, xen_host host, const char *keys);

/**
 * Inject the given string as debugging keys into Xen.
 */
extern bool
xen_host_send_debug_keys_async(xen_session *session, xen_task *result, xen_host host, const char *keys);


/**
 * Run xen-bugtool --yestoall and upload the output to Citrix support.
 */
extern bool
xen_host_bugreport_upload(xen_session *session, xen_host host, const char *url, xen_string_string_map *options);

/**
 * Run xen-bugtool --yestoall and upload the output to Citrix support.
 */
extern bool
xen_host_bugreport_upload_async(xen_session *session, xen_task *result, xen_host host, const char *url, xen_string_string_map *options);


/**
 * List all supported methods.
 */
extern bool
xen_host_list_methods(xen_session *session, struct xen_string_set **result);


/**
 * Apply a new license to a host.
 */
extern bool
xen_host_license_apply(xen_session *session, xen_host host, const char *contents);

/**
 * Apply a new license to a host.
 */
extern bool
xen_host_license_apply_async(xen_session *session, xen_task *result, xen_host host, const char *contents);


/**
 * Destroy specified host record in database.
 */
extern bool
xen_host_destroy(xen_session *session, xen_host self);

/**
 * Destroy specified host record in database.
 */
extern bool
xen_host_destroy_async(xen_session *session, xen_task *result, xen_host self);


/**
 * Attempt to power-on the host (if the capability exists).
 */
extern bool
xen_host_power_on(xen_session *session, xen_host host);

/**
 * Attempt to power-on the host (if the capability exists).
 */
extern bool
xen_host_power_on_async(xen_session *session, xen_task *result, xen_host host);


/**
 * This call disables HA on the local host. This should only be used
 * with extreme care.
 */
extern bool
xen_host_emergency_ha_disable(xen_session *session);


/**
 * Start recording the specified data source.
 */
extern bool
xen_host_record_data_source(xen_session *session, xen_host host, const char *data_source);


/**
 * Query the latest value of the specified data source.
 */
extern bool
xen_host_query_data_source(xen_session *session, double *result, xen_host host, const char *data_source);


/**
 * Forget the recorded statistics related to the specified data source.
 */
extern bool
xen_host_forget_data_source_archives(xen_session *session, xen_host host, const char *data_source);


/**
 * Check this host can be evacuated.
 */
extern bool
xen_host_assert_can_evacuate(xen_session *session, xen_host host);

/**
 * Check this host can be evacuated.
 */
extern bool
xen_host_assert_can_evacuate_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Return a set of VMs which prevent the host being evacuated, with
 * per-VM error codes.
 */
extern bool
xen_host_get_vms_which_prevent_evacuation(xen_session *session, xen_vm_string_set_map **result, xen_host self);

/**
 * Return a set of VMs which prevent the host being evacuated, with
 * per-VM error codes.
 */
extern bool
xen_host_get_vms_which_prevent_evacuation_async(xen_session *session, xen_task *result, xen_host self);


/**
 * Return a set of VMs which are not co-operating with the host's
 * memory control system.
 */
extern bool
xen_host_get_uncooperative_resident_vms(xen_session *session, struct xen_vm_set **result, xen_host self);

/**
 * Return a set of VMs which are not co-operating with the host's
 * memory control system.
 */
extern bool
xen_host_get_uncooperative_resident_vms_async(xen_session *session, xen_task *result, xen_host self);


/**
 * Migrate all VMs off of this host, where possible.
 */
extern bool
xen_host_evacuate(xen_session *session, xen_host host);

/**
 * Migrate all VMs off of this host, where possible.
 */
extern bool
xen_host_evacuate_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Re-configure syslog logging.
 */
extern bool
xen_host_syslog_reconfigure(xen_session *session, xen_host host);

/**
 * Re-configure syslog logging.
 */
extern bool
xen_host_syslog_reconfigure_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Reconfigure the management network interface.
 */
extern bool
xen_host_management_reconfigure(xen_session *session, xen_pif pif);

/**
 * Reconfigure the management network interface.
 */
extern bool
xen_host_management_reconfigure_async(xen_session *session, xen_task *result, xen_pif pif);


/**
 * Reconfigure the management network interface. Should only be used if
 * Host.management_reconfigure is impossible because the network configuration
 * is broken.
 */
extern bool
xen_host_local_management_reconfigure(xen_session *session, const char *interface);


/**
 * Disable the management network interface.
 */
extern bool
xen_host_management_disable(xen_session *session);


/**
 * Returns the management interface for the specified host.
 */
extern bool
xen_host_get_management_interface(xen_session *session, xen_pif *result, xen_host host);

/**
 * Returns the management interface for the specified host.
 */
extern bool
xen_host_get_management_interface_async(xen_session *session, xen_task *result, xen_host host);


/**
 * .
 */
extern bool
xen_host_get_system_status_capabilities(xen_session *session, char **result, xen_host host);


/**
 * Restarts the agent after a 10 second pause. WARNING: this is a
 * dangerous operation. Any operations in progress will be aborted, and
 * unrecoverable data loss may occur. The caller is responsible for ensuring
 * that there are no operations in progress when this method is called.
 */
extern bool
xen_host_restart_agent(xen_session *session, xen_host host);

/**
 * Restarts the agent after a 10 second pause. WARNING: this is a
 * dangerous operation. Any operations in progress will be aborted, and
 * unrecoverable data loss may occur. The caller is responsible for ensuring
 * that there are no operations in progress when this method is called.
 */
extern bool
xen_host_restart_agent_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Shuts the agent down after a 10 second pause. WARNING: this is a
 * dangerous operation. Any operations in progress will be aborted, and
 * unrecoverable data loss may occur. The caller is responsible for ensuring
 * that there are no operations in progress when this method is called.
 */
extern bool
xen_host_shutdown_agent(xen_session *session);


/**
 * Sets the host name to the specified string.  Both the API and
 * lower-level system hostname are changed immediately.
 */
extern bool
xen_host_set_hostname_live(xen_session *session, xen_host host, const char *hostname);


/**
 * Computes the amount of free memory on the host.
 */
extern bool
xen_host_compute_free_memory(xen_session *session, int64_t *result, xen_host host);

/**
 * Computes the amount of free memory on the host.
 */
extern bool
xen_host_compute_free_memory_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Computes the virtualization memory overhead of a host.
 */
extern bool
xen_host_compute_memory_overhead(xen_session *session, int64_t *result, xen_host host);

/**
 * Computes the virtualization memory overhead of a host.
 */
extern bool
xen_host_compute_memory_overhead_async(xen_session *session, xen_task *result, xen_host host);


/**
 * This causes the synchronisation of the non-database data (messages,
 * RRDs and so on) stored on the master to be synchronised with the host.
 */
extern bool
xen_host_sync_data(xen_session *session, xen_host host);


/**
 * This causes the RRDs to be backed up to the master.
 */
extern bool
xen_host_backup_rrds(xen_session *session, xen_host host, double delay);


/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this host.
 */
extern bool
xen_host_create_new_blob(xen_session *session, xen_blob *result, xen_host host, const char *name, const char *mime_type, bool pubblic);

/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this host.
 */
extern bool
xen_host_create_new_blob_async(xen_session *session, xen_task *result, xen_host host, const char *name, const char *mime_type, bool pubblic);


/**
 * Call a XenAPI plugin on this host.
 */
extern bool
xen_host_call_plugin(xen_session *session, char **result, xen_host host, const char *plugin, const char *fn, xen_string_string_map *args);

/**
 * Call a XenAPI plugin on this host.
 */
extern bool
xen_host_call_plugin_async(xen_session *session, xen_task *result, xen_host host, const char *plugin, const char *fn, xen_string_string_map *args);


/**
 * This call queries the host's clock for the current time.
 */
extern bool
xen_host_get_servertime(xen_session *session, time_t *result, xen_host host);


/**
 * This call queries the host's clock for the current time in the
 * host's local timezone.
 */
extern bool
xen_host_get_server_localtime(xen_session *session, time_t *result, xen_host host);


/**
 * This call enables external authentication on a host.
 */
extern bool
xen_host_enable_external_auth(xen_session *session, xen_host host, xen_string_string_map *config, const char *service_name, const char *auth_type);


/**
 * This call disables external authentication on the local host.
 */
extern bool
xen_host_disable_external_auth(xen_session *session, xen_host host, xen_string_string_map *config);


/**
 * Retrieves recommended host migrations to perform when evacuating the
 * host from the wlb server. If a VM cannot be migrated from the host the
 * reason is listed instead of a recommendation.
 */
extern bool
xen_host_retrieve_wlb_evacuate_recommendations(xen_session *session, xen_vm_string_set_map **result, xen_host self);

/**
 * Retrieves recommended host migrations to perform when evacuating the
 * host from the wlb server. If a VM cannot be migrated from the host the
 * reason is listed instead of a recommendation.
 */
extern bool
xen_host_retrieve_wlb_evacuate_recommendations_async(xen_session *session, xen_task *result, xen_host self);


/**
 * Get the installed server SSL certificate.
 */
extern bool
xen_host_get_server_certificate(xen_session *session, char **result, xen_host host);

/**
 * Get the installed server SSL certificate.
 */
extern bool
xen_host_get_server_certificate_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Change to another edition, or reactivate the current edition after a
 * license has expired. This may be subject to the successful checkout of an
 * appropriate license.
 */
extern bool
xen_host_apply_edition(xen_session *session, xen_host host, const char *edition);


/**
 * Refresh the list of installed Supplemental Packs.
 */
extern bool
xen_host_refresh_pack_info(xen_session *session, xen_host host);

/**
 * Refresh the list of installed Supplemental Packs.
 */
extern bool
xen_host_refresh_pack_info_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Set the power-on-mode, host, user and password .
 */
extern bool
xen_host_set_power_on_mode(xen_session *session, xen_host self, const char *power_on_mode, xen_string_string_map *power_on_config);

/**
 * Set the power-on-mode, host, user and password .
 */
extern bool
xen_host_set_power_on_mode_async(xen_session *session, xen_task *result, xen_host self, const char *power_on_mode, xen_string_string_map *power_on_config);


/**
 * Set the CPU features to be used after a reboot, if the given
 * features string is valid.
 */
extern bool
xen_host_set_cpu_features(xen_session *session, xen_host host, const char *features);


/**
 * Remove the feature mask, such that after a reboot all features of
 * the CPU are enabled.
 */
extern bool
xen_host_reset_cpu_features(xen_session *session, xen_host host);


/**
 * Enable the use of a local SR for caching purposes.
 */
extern bool
xen_host_enable_local_storage_caching(xen_session *session, xen_host host, xen_sr sr);


/**
 * Disable the use of a local SR for caching purposes.
 */
extern bool
xen_host_disable_local_storage_caching(xen_session *session, xen_host host);


/**
 * Prepare to receive a VM, returning a token which can be passed to
 * VM.migrate.
 */
extern bool
xen_host_migrate_receive(xen_session *session, xen_string_string_map **result, xen_host host, xen_network network, xen_string_string_map *options);

/**
 * Prepare to receive a VM, returning a token which can be passed to
 * VM.migrate.
 */
extern bool
xen_host_migrate_receive_async(xen_session *session, xen_task *result, xen_host host, xen_network network, xen_string_string_map *options);


/**
 * Return a list of all the hosts known to the system.
 */
extern bool
xen_host_get_all(xen_session *session, struct xen_host_set **result);


/**
 * Return a map of host references to host records for all hosts known
 * to the system.
 */
extern bool
xen_host_get_all_records(xen_session *session, xen_host_xen_host_record_map **result);


#endif
