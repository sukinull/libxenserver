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


#ifndef XEN_VM_H
#define XEN_VM_H

#include <xen/api/xen_blob_decl.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_console_decl.h>
#include <xen/api/xen_crashdump_decl.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_host_string_set_map.h>
#include <xen/api/xen_on_crash_behaviour.h>
#include <xen/api/xen_on_normal_exit.h>
#include <xen/api/xen_pci_decl.h>
#include <xen/api/xen_sr_decl.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_vm_operations_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vbd_decl.h>
#include <xen/api/xen_vdi_decl.h>
#include <xen/api/xen_vdi_sr_map.h>
#include <xen/api/xen_vgpu_decl.h>
#include <xen/api/xen_vif_decl.h>
#include <xen/api/xen_vif_network_map.h>
#include <xen/api/xen_vm_appliance_decl.h>
#include <xen/api/xen_vm_decl.h>
#include <xen/api/xen_vm_guest_metrics_decl.h>
#include <xen/api/xen_vm_metrics_decl.h>
#include <xen/api/xen_vm_operations.h>
#include <xen/api/xen_vm_operations_string_map.h>
#include <xen/api/xen_vm_power_state.h>
#include <xen/api/xen_vm_xen_vm_record_map.h>
#include <xen/api/xen_vmpp_decl.h>
#include <xen/api/xen_vtpm_decl.h>


/*
 * The VM class.
 * 
 * A virtual machine (or 'guest').
 */


/**
 * Free the given xen_vm.  The given handle must have been allocated by
 * this library.
 */
extern void
xen_vm_free(xen_vm vm);


typedef struct xen_vm_set
{
    size_t size;
    xen_vm *contents[];
} xen_vm_set;

/**
 * Allocate a xen_vm_set of the given size.
 */
extern xen_vm_set *
xen_vm_set_alloc(size_t size);

/**
 * Free the given xen_vm_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_vm_set_free(xen_vm_set *set);


typedef struct xen_vm_record
{
    xen_vm handle;
    char *uuid;
    struct xen_vm_operations_set *allowed_operations;
    xen_string_vm_operations_map *current_operations;
    enum xen_vm_power_state power_state;
    char *name_label;
    char *name_description;
    int64_t user_version;
    bool is_a_template;
    struct xen_vdi_record_opt *suspend_vdi;
    struct xen_host_record_opt *resident_on;
    struct xen_host_record_opt *affinity;
    int64_t memory_overhead;
    int64_t memory_target;
    int64_t memory_static_max;
    int64_t memory_dynamic_max;
    int64_t memory_dynamic_min;
    int64_t memory_static_min;
    xen_string_string_map *vcpus_params;
    int64_t vcpus_max;
    int64_t vcpus_at_startup;
    enum xen_on_normal_exit actions_after_shutdown;
    enum xen_on_normal_exit actions_after_reboot;
    enum xen_on_crash_behaviour actions_after_crash;
    struct xen_console_record_opt_set *consoles;
    struct xen_vif_record_opt_set *vifs;
    struct xen_vbd_record_opt_set *vbds;
    struct xen_crashdump_record_opt_set *crash_dumps;
    struct xen_vtpm_record_opt_set *vtpms;
    char *pv_bootloader;
    char *pv_kernel;
    char *pv_ramdisk;
    char *pv_args;
    char *pv_bootloader_args;
    char *pv_legacy_args;
    char *hvm_boot_policy;
    xen_string_string_map *hvm_boot_params;
    double hvm_shadow_multiplier;
    xen_string_string_map *platform;
    char *pci_bus;
    xen_string_string_map *other_config;
    int64_t domid;
    char *domarch;
    xen_string_string_map *last_boot_cpu_flags;
    bool is_control_domain;
    struct xen_vm_metrics_record_opt *metrics;
    struct xen_vm_guest_metrics_record_opt *guest_metrics;
    char *last_booted_record;
    char *recommendations;
    xen_string_string_map *xenstore_data;
    bool ha_always_run;
    char *ha_restart_priority;
    bool is_a_snapshot;
    struct xen_vm_record_opt *snapshot_of;
    struct xen_vm_record_opt_set *snapshots;
    time_t snapshot_time;
    char *transportable_snapshot_id;
    xen_string_blob_map *blobs;
    struct xen_string_set *tags;
    xen_vm_operations_string_map *blocked_operations;
    xen_string_string_map *snapshot_info;
    char *snapshot_metadata;
    struct xen_vm_record_opt *parent;
    struct xen_vm_record_opt_set *children;
    xen_string_string_map *bios_strings;
    struct xen_vmpp_record_opt *protection_policy;
    bool is_snapshot_from_vmpp;
    struct xen_vm_appliance_record_opt *appliance;
    int64_t start_delay;
    int64_t shutdown_delay;
    int64_t order;
    struct xen_vgpu_record_opt_set *vgpus;
    struct xen_pci_record_opt_set *attached_pcis;
    struct xen_sr_record_opt *suspend_sr;
    int64_t version;
} xen_vm_record;

/**
 * Allocate a xen_vm_record.
 */
extern xen_vm_record *
xen_vm_record_alloc(void);

/**
 * Free the given xen_vm_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_vm_record_free(xen_vm_record *record);


typedef struct xen_vm_record_opt
{
    bool is_record;
    union
    {
        xen_vm handle;
        xen_vm_record *record;
    } u;
} xen_vm_record_opt;

/**
 * Allocate a xen_vm_record_opt.
 */
extern xen_vm_record_opt *
xen_vm_record_opt_alloc(void);

/**
 * Free the given xen_vm_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_vm_record_opt_free(xen_vm_record_opt *record_opt);


typedef struct xen_vm_record_set
{
    size_t size;
    xen_vm_record *contents[];
} xen_vm_record_set;

/**
 * Allocate a xen_vm_record_set of the given size.
 */
extern xen_vm_record_set *
xen_vm_record_set_alloc(size_t size);

/**
 * Free the given xen_vm_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_vm_record_set_free(xen_vm_record_set *set);



typedef struct xen_vm_record_opt_set
{
    size_t size;
    xen_vm_record_opt *contents[];
} xen_vm_record_opt_set;

/**
 * Allocate a xen_vm_record_opt_set of the given size.
 */
extern xen_vm_record_opt_set *
xen_vm_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vm_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_vm_record_opt_set_free(xen_vm_record_opt_set *set);


/**
 * Get a record containing the current state of the given VM.
 */
extern bool
xen_vm_get_record(xen_session *session, xen_vm_record **result, xen_vm vm);


/**
 * Get a reference to the VM instance with the specified UUID.
 */
extern bool
xen_vm_get_by_uuid(xen_session *session, xen_vm *result, const char *uuid);


/**
 * Create a new VM instance, and return its handle.
 */
extern bool
xen_vm_create(xen_session *session, xen_vm *result, const xen_vm_record *record);

/**
 * Create a new VM instance, and return its handle.
 */
extern bool
xen_vm_create_async(xen_session *session, xen_task *result, const xen_vm_record *record);


/**
 * Destroy the specified VM.  The VM is completely removed from the
 * system.  This function can only be called when the VM is in the Halted
 * State.
 */
extern bool
xen_vm_destroy(xen_session *session, xen_vm vm);

/**
 * Destroy the specified VM.  The VM is completely removed from the
 * system.  This function can only be called when the VM is in the Halted
 * State.
 */
extern bool
xen_vm_destroy_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Get all the VM instances with the given label.
 */
extern bool
xen_vm_get_by_name_label(xen_session *session, struct xen_vm_set **result, const char *label);


/**
 * Get the uuid field of the given VM.
 */
extern bool
xen_vm_get_uuid(xen_session *session, char **result, xen_vm vm);


/**
 * Get the allowed_operations field of the given VM.
 */
extern bool
xen_vm_get_allowed_operations(xen_session *session, struct xen_vm_operations_set **result, xen_vm vm);


/**
 * Get the current_operations field of the given VM.
 */
extern bool
xen_vm_get_current_operations(xen_session *session, xen_string_vm_operations_map **result, xen_vm vm);


/**
 * Get the power_state field of the given VM.
 */
extern bool
xen_vm_get_power_state(xen_session *session, enum xen_vm_power_state *result, xen_vm vm);


/**
 * Get the name/label field of the given VM.
 */
extern bool
xen_vm_get_name_label(xen_session *session, char **result, xen_vm vm);


/**
 * Get the name/description field of the given VM.
 */
extern bool
xen_vm_get_name_description(xen_session *session, char **result, xen_vm vm);


/**
 * Get the user_version field of the given VM.
 */
extern bool
xen_vm_get_user_version(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the is_a_template field of the given VM.
 */
extern bool
xen_vm_get_is_a_template(xen_session *session, bool *result, xen_vm vm);


/**
 * Get the suspend_VDI field of the given VM.
 */
extern bool
xen_vm_get_suspend_vdi(xen_session *session, xen_vdi *result, xen_vm vm);


/**
 * Get the resident_on field of the given VM.
 */
extern bool
xen_vm_get_resident_on(xen_session *session, xen_host *result, xen_vm vm);


/**
 * Get the affinity field of the given VM.
 */
extern bool
xen_vm_get_affinity(xen_session *session, xen_host *result, xen_vm vm);


/**
 * Get the memory/overhead field of the given VM.
 */
extern bool
xen_vm_get_memory_overhead(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the memory/target field of the given VM.
 */
extern bool
xen_vm_get_memory_target(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the memory/static_max field of the given VM.
 */
extern bool
xen_vm_get_memory_static_max(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the memory/dynamic_max field of the given VM.
 */
extern bool
xen_vm_get_memory_dynamic_max(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the memory/dynamic_min field of the given VM.
 */
extern bool
xen_vm_get_memory_dynamic_min(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the memory/static_min field of the given VM.
 */
extern bool
xen_vm_get_memory_static_min(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the VCPUs/params field of the given VM.
 */
extern bool
xen_vm_get_vcpus_params(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the VCPUs/max field of the given VM.
 */
extern bool
xen_vm_get_vcpus_max(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the VCPUs/at_startup field of the given VM.
 */
extern bool
xen_vm_get_vcpus_at_startup(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the actions/after_shutdown field of the given VM.
 */
extern bool
xen_vm_get_actions_after_shutdown(xen_session *session, enum xen_on_normal_exit *result, xen_vm vm);


/**
 * Get the actions/after_reboot field of the given VM.
 */
extern bool
xen_vm_get_actions_after_reboot(xen_session *session, enum xen_on_normal_exit *result, xen_vm vm);


/**
 * Get the actions/after_crash field of the given VM.
 */
extern bool
xen_vm_get_actions_after_crash(xen_session *session, enum xen_on_crash_behaviour *result, xen_vm vm);


/**
 * Get the consoles field of the given VM.
 */
extern bool
xen_vm_get_consoles(xen_session *session, struct xen_console_set **result, xen_vm vm);


/**
 * Get the VIFs field of the given VM.
 */
extern bool
xen_vm_get_vifs(xen_session *session, struct xen_vif_set **result, xen_vm vm);


/**
 * Get the VBDs field of the given VM.
 */
extern bool
xen_vm_get_vbds(xen_session *session, struct xen_vbd_set **result, xen_vm vm);


/**
 * Get the crash_dumps field of the given VM.
 */
extern bool
xen_vm_get_crash_dumps(xen_session *session, struct xen_crashdump_set **result, xen_vm vm);


/**
 * Get the VTPMs field of the given VM.
 */
extern bool
xen_vm_get_vtpms(xen_session *session, struct xen_vtpm_set **result, xen_vm vm);


/**
 * Get the PV/bootloader field of the given VM.
 */
extern bool
xen_vm_get_pv_bootloader(xen_session *session, char **result, xen_vm vm);


/**
 * Get the PV/kernel field of the given VM.
 */
extern bool
xen_vm_get_pv_kernel(xen_session *session, char **result, xen_vm vm);


/**
 * Get the PV/ramdisk field of the given VM.
 */
extern bool
xen_vm_get_pv_ramdisk(xen_session *session, char **result, xen_vm vm);


/**
 * Get the PV/args field of the given VM.
 */
extern bool
xen_vm_get_pv_args(xen_session *session, char **result, xen_vm vm);


/**
 * Get the PV/bootloader_args field of the given VM.
 */
extern bool
xen_vm_get_pv_bootloader_args(xen_session *session, char **result, xen_vm vm);


/**
 * Get the PV/legacy_args field of the given VM.
 */
extern bool
xen_vm_get_pv_legacy_args(xen_session *session, char **result, xen_vm vm);


/**
 * Get the HVM/boot_policy field of the given VM.
 */
extern bool
xen_vm_get_hvm_boot_policy(xen_session *session, char **result, xen_vm vm);


/**
 * Get the HVM/boot_params field of the given VM.
 */
extern bool
xen_vm_get_hvm_boot_params(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the HVM/shadow_multiplier field of the given VM.
 */
extern bool
xen_vm_get_hvm_shadow_multiplier(xen_session *session, double *result, xen_vm vm);


/**
 * Get the platform field of the given VM.
 */
extern bool
xen_vm_get_platform(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the PCI_bus field of the given VM.
 */
extern bool
xen_vm_get_pci_bus(xen_session *session, char **result, xen_vm vm);


/**
 * Get the other_config field of the given VM.
 */
extern bool
xen_vm_get_other_config(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the domid field of the given VM.
 */
extern bool
xen_vm_get_domid(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the domarch field of the given VM.
 */
extern bool
xen_vm_get_domarch(xen_session *session, char **result, xen_vm vm);


/**
 * Get the last_boot_CPU_flags field of the given VM.
 */
extern bool
xen_vm_get_last_boot_cpu_flags(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the is_control_domain field of the given VM.
 */
extern bool
xen_vm_get_is_control_domain(xen_session *session, bool *result, xen_vm vm);


/**
 * Get the metrics field of the given VM.
 */
extern bool
xen_vm_get_metrics(xen_session *session, xen_vm_metrics *result, xen_vm vm);


/**
 * Get the guest_metrics field of the given VM.
 */
extern bool
xen_vm_get_guest_metrics(xen_session *session, xen_vm_guest_metrics *result, xen_vm vm);


/**
 * Get the last_booted_record field of the given VM.
 */
extern bool
xen_vm_get_last_booted_record(xen_session *session, char **result, xen_vm vm);


/**
 * Get the recommendations field of the given VM.
 */
extern bool
xen_vm_get_recommendations(xen_session *session, char **result, xen_vm vm);


/**
 * Get the xenstore_data field of the given VM.
 */
extern bool
xen_vm_get_xenstore_data(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the ha_always_run field of the given VM.
 */
extern bool
xen_vm_get_ha_always_run(xen_session *session, bool *result, xen_vm vm);


/**
 * Get the ha_restart_priority field of the given VM.
 */
extern bool
xen_vm_get_ha_restart_priority(xen_session *session, char **result, xen_vm vm);


/**
 * Get the is_a_snapshot field of the given VM.
 */
extern bool
xen_vm_get_is_a_snapshot(xen_session *session, bool *result, xen_vm vm);


/**
 * Get the snapshot_of field of the given VM.
 */
extern bool
xen_vm_get_snapshot_of(xen_session *session, xen_vm *result, xen_vm vm);


/**
 * Get the snapshots field of the given VM.
 */
extern bool
xen_vm_get_snapshots(xen_session *session, struct xen_vm_set **result, xen_vm vm);


/**
 * Get the snapshot_time field of the given VM.
 */
extern bool
xen_vm_get_snapshot_time(xen_session *session, time_t *result, xen_vm vm);


/**
 * Get the transportable_snapshot_id field of the given VM.
 */
extern bool
xen_vm_get_transportable_snapshot_id(xen_session *session, char **result, xen_vm vm);


/**
 * Get the blobs field of the given VM.
 */
extern bool
xen_vm_get_blobs(xen_session *session, xen_string_blob_map **result, xen_vm vm);


/**
 * Get the tags field of the given VM.
 */
extern bool
xen_vm_get_tags(xen_session *session, struct xen_string_set **result, xen_vm vm);


/**
 * Get the blocked_operations field of the given VM.
 */
extern bool
xen_vm_get_blocked_operations(xen_session *session, xen_vm_operations_string_map **result, xen_vm vm);


/**
 * Get the snapshot_info field of the given VM.
 */
extern bool
xen_vm_get_snapshot_info(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the snapshot_metadata field of the given VM.
 */
extern bool
xen_vm_get_snapshot_metadata(xen_session *session, char **result, xen_vm vm);


/**
 * Get the parent field of the given VM.
 */
extern bool
xen_vm_get_parent(xen_session *session, xen_vm *result, xen_vm vm);


/**
 * Get the children field of the given VM.
 */
extern bool
xen_vm_get_children(xen_session *session, struct xen_vm_set **result, xen_vm vm);


/**
 * Get the bios_strings field of the given VM.
 */
extern bool
xen_vm_get_bios_strings(xen_session *session, xen_string_string_map **result, xen_vm vm);


/**
 * Get the protection_policy field of the given VM.
 */
extern bool
xen_vm_get_protection_policy(xen_session *session, xen_vmpp *result, xen_vm vm);


/**
 * Get the is_snapshot_from_vmpp field of the given VM.
 */
extern bool
xen_vm_get_is_snapshot_from_vmpp(xen_session *session, bool *result, xen_vm vm);


/**
 * Get the appliance field of the given VM.
 */
extern bool
xen_vm_get_appliance(xen_session *session, xen_vm_appliance *result, xen_vm vm);


/**
 * Get the start_delay field of the given VM.
 */
extern bool
xen_vm_get_start_delay(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the shutdown_delay field of the given VM.
 */
extern bool
xen_vm_get_shutdown_delay(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the order field of the given VM.
 */
extern bool
xen_vm_get_order(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Get the VGPUs field of the given VM.
 */
extern bool
xen_vm_get_vgpus(xen_session *session, struct xen_vgpu_set **result, xen_vm vm);


/**
 * Get the attached_PCIs field of the given VM.
 */
extern bool
xen_vm_get_attached_pcis(xen_session *session, struct xen_pci_set **result, xen_vm vm);


/**
 * Get the suspend_SR field of the given VM.
 */
extern bool
xen_vm_get_suspend_sr(xen_session *session, xen_sr *result, xen_vm vm);


/**
 * Get the version field of the given VM.
 */
extern bool
xen_vm_get_version(xen_session *session, int64_t *result, xen_vm vm);


/**
 * Set the name/label field of the given VM.
 */
extern bool
xen_vm_set_name_label(xen_session *session, xen_vm vm, const char *label);


/**
 * Set the name/description field of the given VM.
 */
extern bool
xen_vm_set_name_description(xen_session *session, xen_vm vm, const char *description);


/**
 * Set the user_version field of the given VM.
 */
extern bool
xen_vm_set_user_version(xen_session *session, xen_vm vm, int64_t user_version);


/**
 * Set the is_a_template field of the given VM.
 */
extern bool
xen_vm_set_is_a_template(xen_session *session, xen_vm vm, bool is_a_template);


/**
 * Set the affinity field of the given VM.
 */
extern bool
xen_vm_set_affinity(xen_session *session, xen_vm vm, xen_host affinity);


/**
 * Set the VCPUs/params field of the given VM.
 */
extern bool
xen_vm_set_vcpus_params(xen_session *session, xen_vm vm, xen_string_string_map *params);


/**
 * Add the given key-value pair to the VCPUs/params field of the given
 * VM.
 */
extern bool
xen_vm_add_to_vcpus_params(xen_session *session, xen_vm vm, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * VCPUs/params field of the given VM.  If the key is not in that Map, then do
 * nothing.
 */
extern bool
xen_vm_remove_from_vcpus_params(xen_session *session, xen_vm vm, const char *key);


/**
 * Set the actions/after_shutdown field of the given VM.
 */
extern bool
xen_vm_set_actions_after_shutdown(xen_session *session, xen_vm vm, enum xen_on_normal_exit after_shutdown);


/**
 * Set the actions/after_reboot field of the given VM.
 */
extern bool
xen_vm_set_actions_after_reboot(xen_session *session, xen_vm vm, enum xen_on_normal_exit after_reboot);


/**
 * Set the actions/after_crash field of the given VM.
 */
extern bool
xen_vm_set_actions_after_crash(xen_session *session, xen_vm vm, enum xen_on_crash_behaviour after_crash);


/**
 * Set the PV/bootloader field of the given VM.
 */
extern bool
xen_vm_set_pv_bootloader(xen_session *session, xen_vm vm, const char *bootloader);


/**
 * Set the PV/kernel field of the given VM.
 */
extern bool
xen_vm_set_pv_kernel(xen_session *session, xen_vm vm, const char *kernel);


/**
 * Set the PV/ramdisk field of the given VM.
 */
extern bool
xen_vm_set_pv_ramdisk(xen_session *session, xen_vm vm, const char *ramdisk);


/**
 * Set the PV/args field of the given VM.
 */
extern bool
xen_vm_set_pv_args(xen_session *session, xen_vm vm, const char *args);


/**
 * Set the PV/bootloader_args field of the given VM.
 */
extern bool
xen_vm_set_pv_bootloader_args(xen_session *session, xen_vm vm, const char *bootloader_args);


/**
 * Set the PV/legacy_args field of the given VM.
 */
extern bool
xen_vm_set_pv_legacy_args(xen_session *session, xen_vm vm, const char *legacy_args);


/**
 * Set the HVM/boot_policy field of the given VM.
 */
extern bool
xen_vm_set_hvm_boot_policy(xen_session *session, xen_vm vm, const char *boot_policy);


/**
 * Set the HVM/boot_params field of the given VM.
 */
extern bool
xen_vm_set_hvm_boot_params(xen_session *session, xen_vm vm, xen_string_string_map *boot_params);


/**
 * Add the given key-value pair to the HVM/boot_params field of the
 * given VM.
 */
extern bool
xen_vm_add_to_hvm_boot_params(xen_session *session, xen_vm vm, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * HVM/boot_params field of the given VM.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_vm_remove_from_hvm_boot_params(xen_session *session, xen_vm vm, const char *key);


/**
 * Set the platform field of the given VM.
 */
extern bool
xen_vm_set_platform(xen_session *session, xen_vm vm, xen_string_string_map *platform);


/**
 * Add the given key-value pair to the platform field of the given VM.
 */
extern bool
xen_vm_add_to_platform(xen_session *session, xen_vm vm, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the platform
 * field of the given VM.  If the key is not in that Map, then do nothing.
 */
extern bool
xen_vm_remove_from_platform(xen_session *session, xen_vm vm, const char *key);


/**
 * Set the PCI_bus field of the given VM.
 */
extern bool
xen_vm_set_pci_bus(xen_session *session, xen_vm vm, const char *pci_bus);


/**
 * Set the other_config field of the given VM.
 */
extern bool
xen_vm_set_other_config(xen_session *session, xen_vm vm, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * VM.
 */
extern bool
xen_vm_add_to_other_config(xen_session *session, xen_vm vm, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given VM.  If the key is not in that Map, then do
 * nothing.
 */
extern bool
xen_vm_remove_from_other_config(xen_session *session, xen_vm vm, const char *key);


/**
 * Set the recommendations field of the given VM.
 */
extern bool
xen_vm_set_recommendations(xen_session *session, xen_vm vm, const char *recommendations);


/**
 * Set the xenstore_data field of the given VM.
 */
extern bool
xen_vm_set_xenstore_data(xen_session *session, xen_vm vm, xen_string_string_map *xenstore_data);


/**
 * Add the given key-value pair to the xenstore_data field of the given
 * VM.
 */
extern bool
xen_vm_add_to_xenstore_data(xen_session *session, xen_vm vm, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * xenstore_data field of the given VM.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_vm_remove_from_xenstore_data(xen_session *session, xen_vm vm, const char *key);


/**
 * Set the tags field of the given VM.
 */
extern bool
xen_vm_set_tags(xen_session *session, xen_vm vm, struct xen_string_set *tags);


/**
 * Add the given value to the tags field of the given VM.  If the value
 * is already in that Set, then do nothing.
 */
extern bool
xen_vm_add_tags(xen_session *session, xen_vm vm, const char *value);


/**
 * Remove the given value from the tags field of the given VM.  If the
 * value is not in that Set, then do nothing.
 */
extern bool
xen_vm_remove_tags(xen_session *session, xen_vm vm, const char *value);


/**
 * Set the blocked_operations field of the given VM.
 */
extern bool
xen_vm_set_blocked_operations(xen_session *session, xen_vm vm, xen_vm_operations_string_map *blocked_operations);


/**
 * Add the given key-value pair to the blocked_operations field of the
 * given VM.
 */
extern bool
xen_vm_add_to_blocked_operations(xen_session *session, xen_vm vm, enum xen_vm_operations key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * blocked_operations field of the given VM.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_vm_remove_from_blocked_operations(xen_session *session, xen_vm vm, enum xen_vm_operations key);


/**
 * Set the suspend_SR field of the given VM.
 */
extern bool
xen_vm_set_suspend_sr(xen_session *session, xen_vm vm, xen_sr suspend_sr);


/**
 * Snapshots the specified VM, making a new VM. Snapshot automatically
 * exploits the capabilities of the underlying storage repository in which the
 * VM's disk images are stored (e.g. Copy on Write).
 */
extern bool
xen_vm_snapshot(xen_session *session, xen_vm *result, xen_vm vm, const char *new_name);

/**
 * Snapshots the specified VM, making a new VM. Snapshot automatically
 * exploits the capabilities of the underlying storage repository in which the
 * VM's disk images are stored (e.g. Copy on Write).
 */
extern bool
xen_vm_snapshot_async(xen_session *session, xen_task *result, xen_vm vm, const char *new_name);


/**
 * Snapshots the specified VM with quiesce, making a new VM. Snapshot
 * automatically exploits the capabilities of the underlying storage
 * repository in which the VM's disk images are stored (e.g. Copy on Write).
 */
extern bool
xen_vm_snapshot_with_quiesce(xen_session *session, xen_vm *result, xen_vm vm, const char *new_name);

/**
 * Snapshots the specified VM with quiesce, making a new VM. Snapshot
 * automatically exploits the capabilities of the underlying storage
 * repository in which the VM's disk images are stored (e.g. Copy on Write).
 */
extern bool
xen_vm_snapshot_with_quiesce_async(xen_session *session, xen_task *result, xen_vm vm, const char *new_name);


/**
 * Clones the specified VM, making a new VM. Clone automatically
 * exploits the capabilities of the underlying storage repository in which the
 * VM's disk images are stored (e.g. Copy on Write).   This function can only
 * be called when the VM is in the Halted State.
 */
extern bool
xen_vm_clone(xen_session *session, xen_vm *result, xen_vm vm, const char *new_name);

/**
 * Clones the specified VM, making a new VM. Clone automatically
 * exploits the capabilities of the underlying storage repository in which the
 * VM's disk images are stored (e.g. Copy on Write).   This function can only
 * be called when the VM is in the Halted State.
 */
extern bool
xen_vm_clone_async(xen_session *session, xen_task *result, xen_vm vm, const char *new_name);


/**
 * Copied the specified VM, making a new VM. Unlike clone, copy does
 * not exploits the capabilities of the underlying storage repository in which
 * the VM's disk images are stored. Instead, copy guarantees that the disk
 * images of the newly created VM will be 'full disks' - i.e. not part of a
 * CoW chain.  This function can only be called when the VM is in the Halted
 * State.
 */
extern bool
xen_vm_copy(xen_session *session, xen_vm *result, xen_vm vm, const char *new_name, xen_sr sr);

/**
 * Copied the specified VM, making a new VM. Unlike clone, copy does
 * not exploits the capabilities of the underlying storage repository in which
 * the VM's disk images are stored. Instead, copy guarantees that the disk
 * images of the newly created VM will be 'full disks' - i.e. not part of a
 * CoW chain.  This function can only be called when the VM is in the Halted
 * State.
 */
extern bool
xen_vm_copy_async(xen_session *session, xen_task *result, xen_vm vm, const char *new_name, xen_sr sr);


/**
 * Reverts the specified VM to a previous state.
 */
extern bool
xen_vm_revert(xen_session *session, xen_vm snapshot);

/**
 * Reverts the specified VM to a previous state.
 */
extern bool
xen_vm_revert_async(xen_session *session, xen_task *result, xen_vm snapshot);


/**
 * Checkpoints the specified VM, making a new VM. Checkpoint
 * automatically exploits the capabilities of the underlying storage
 * repository in which the VM's disk images are stored (e.g. Copy on Write)
 * and saves the memory image as well.
 */
extern bool
xen_vm_checkpoint(xen_session *session, xen_vm *result, xen_vm vm, const char *new_name);

/**
 * Checkpoints the specified VM, making a new VM. Checkpoint
 * automatically exploits the capabilities of the underlying storage
 * repository in which the VM's disk images are stored (e.g. Copy on Write)
 * and saves the memory image as well.
 */
extern bool
xen_vm_checkpoint_async(xen_session *session, xen_task *result, xen_vm vm, const char *new_name);


/**
 * Inspects the disk configuration contained within the VM's
 * other_config, creates VDIs and VBDs and then executes any applicable
 * post-install script.
 */
extern bool
xen_vm_provision(xen_session *session, xen_vm vm);

/**
 * Inspects the disk configuration contained within the VM's
 * other_config, creates VDIs and VBDs and then executes any applicable
 * post-install script.
 */
extern bool
xen_vm_provision_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Start the specified VM.  This function can only be called with the
 * VM is in the Halted State.
 */
extern bool
xen_vm_start(xen_session *session, xen_vm vm, bool start_paused, bool force);

/**
 * Start the specified VM.  This function can only be called with the
 * VM is in the Halted State.
 */
extern bool
xen_vm_start_async(xen_session *session, xen_task *result, xen_vm vm, bool start_paused, bool force);


/**
 * Start the specified VM on a particular host.  This function can only
 * be called with the VM is in the Halted State.
 */
extern bool
xen_vm_start_on(xen_session *session, xen_vm vm, xen_host host, bool start_paused, bool force);

/**
 * Start the specified VM on a particular host.  This function can only
 * be called with the VM is in the Halted State.
 */
extern bool
xen_vm_start_on_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host, bool start_paused, bool force);


/**
 * Pause the specified VM. This can only be called when the specified
 * VM is in the Running state.
 */
extern bool
xen_vm_pause(xen_session *session, xen_vm vm);

/**
 * Pause the specified VM. This can only be called when the specified
 * VM is in the Running state.
 */
extern bool
xen_vm_pause_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Resume the specified VM. This can only be called when the specified
 * VM is in the Paused state.
 */
extern bool
xen_vm_unpause(xen_session *session, xen_vm vm);

/**
 * Resume the specified VM. This can only be called when the specified
 * VM is in the Paused state.
 */
extern bool
xen_vm_unpause_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Attempt to cleanly shutdown the specified VM. (Note: this may not be
 * supported---e.g. if a guest agent is not installed). This can only be
 * called when the specified VM is in the Running state.
 */
extern bool
xen_vm_clean_shutdown(xen_session *session, xen_vm vm);

/**
 * Attempt to cleanly shutdown the specified VM. (Note: this may not be
 * supported---e.g. if a guest agent is not installed). This can only be
 * called when the specified VM is in the Running state.
 */
extern bool
xen_vm_clean_shutdown_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Attempt to cleanly shutdown the specified VM (Note: this may not be
 * supported---e.g. if a guest agent is not installed). This can only be
 * called when the specified VM is in the Running state.
 */
extern bool
xen_vm_clean_reboot(xen_session *session, xen_vm vm);

/**
 * Attempt to cleanly shutdown the specified VM (Note: this may not be
 * supported---e.g. if a guest agent is not installed). This can only be
 * called when the specified VM is in the Running state.
 */
extern bool
xen_vm_clean_reboot_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Stop executing the specified VM without attempting a clean shutdown.
 */
extern bool
xen_vm_hard_shutdown(xen_session *session, xen_vm vm);

/**
 * Stop executing the specified VM without attempting a clean shutdown.
 */
extern bool
xen_vm_hard_shutdown_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Reset the power-state of the VM to halted in the database only.
 * (Used to recover from slave failures in pooling scenarios by resetting the
 * power-states of VMs running on dead slaves to halted.) This is a
 * potentially dangerous operation; use with care.
 */
extern bool
xen_vm_power_state_reset(xen_session *session, xen_vm vm);

/**
 * Reset the power-state of the VM to halted in the database only.
 * (Used to recover from slave failures in pooling scenarios by resetting the
 * power-states of VMs running on dead slaves to halted.) This is a
 * potentially dangerous operation; use with care.
 */
extern bool
xen_vm_power_state_reset_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Stop executing the specified VM without attempting a clean shutdown
 * and immediately restart the VM.
 */
extern bool
xen_vm_hard_reboot(xen_session *session, xen_vm vm);

/**
 * Stop executing the specified VM without attempting a clean shutdown
 * and immediately restart the VM.
 */
extern bool
xen_vm_hard_reboot_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Suspend the specified VM to disk.  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_suspend(xen_session *session, xen_vm vm);

/**
 * Suspend the specified VM to disk.  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_suspend_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Awaken the specified VM and resume it.  This can only be called when
 * the specified VM is in the Suspended state.
 */
extern bool
xen_vm_resume(xen_session *session, xen_vm vm, bool start_paused, bool force);

/**
 * Awaken the specified VM and resume it.  This can only be called when
 * the specified VM is in the Suspended state.
 */
extern bool
xen_vm_resume_async(xen_session *session, xen_task *result, xen_vm vm, bool start_paused, bool force);


/**
 * Awaken the specified VM and resume it on a particular Host.  This
 * can only be called when the specified VM is in the Suspended state.
 */
extern bool
xen_vm_resume_on(xen_session *session, xen_vm vm, xen_host host, bool start_paused, bool force);

/**
 * Awaken the specified VM and resume it on a particular Host.  This
 * can only be called when the specified VM is in the Suspended state.
 */
extern bool
xen_vm_resume_on_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host, bool start_paused, bool force);


/**
 * Migrate a VM to another Host. This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_pool_migrate(xen_session *session, xen_vm vm, xen_host host, xen_string_string_map *options);

/**
 * Migrate a VM to another Host. This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_pool_migrate_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host, xen_string_string_map *options);


/**
 * Set the number of VCPUs for a running VM.
 */
extern bool
xen_vm_set_vcpus_number_live(xen_session *session, xen_vm self, int64_t nvcpu);

/**
 * Set the number of VCPUs for a running VM.
 */
extern bool
xen_vm_set_vcpus_number_live_async(xen_session *session, xen_task *result, xen_vm self, int64_t nvcpu);


/**
 * Add the given key-value pair to VM.VCPUs_params, and apply that
 * value on the running VM.
 */
extern bool
xen_vm_add_to_vcpus_params_live(xen_session *session, xen_vm self, const char *key, const char *value);

/**
 * Add the given key-value pair to VM.VCPUs_params, and apply that
 * value on the running VM.
 */
extern bool
xen_vm_add_to_vcpus_params_live_async(xen_session *session, xen_task *result, xen_vm self, const char *key, const char *value);


/**
 * Set the value of the ha_restart_priority field.
 */
extern bool
xen_vm_set_ha_restart_priority(xen_session *session, xen_vm self, const char *value);


/**
 * Set the value of the ha_always_run.
 */
extern bool
xen_vm_set_ha_always_run(xen_session *session, xen_vm self, bool value);


/**
 * Computes the virtualization memory overhead of a VM.
 */
extern bool
xen_vm_compute_memory_overhead(xen_session *session, int64_t *result, xen_vm vm);

/**
 * Computes the virtualization memory overhead of a VM.
 */
extern bool
xen_vm_compute_memory_overhead_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Set the value of the memory_dynamic_max field.
 */
extern bool
xen_vm_set_memory_dynamic_max(xen_session *session, xen_vm self, int64_t value);


/**
 * Set the value of the memory_dynamic_min field.
 */
extern bool
xen_vm_set_memory_dynamic_min(xen_session *session, xen_vm self, int64_t value);


/**
 * Set the minimum and maximum amounts of physical memory the VM is
 * allowed to use.
 */
extern bool
xen_vm_set_memory_dynamic_range(xen_session *session, xen_vm self, int64_t min, int64_t max);

/**
 * Set the minimum and maximum amounts of physical memory the VM is
 * allowed to use.
 */
extern bool
xen_vm_set_memory_dynamic_range_async(xen_session *session, xen_task *result, xen_vm self, int64_t min, int64_t max);


/**
 * Set the value of the memory_static_max field.
 */
extern bool
xen_vm_set_memory_static_max(xen_session *session, xen_vm self, int64_t value);


/**
 * Set the value of the memory_static_min field.
 */
extern bool
xen_vm_set_memory_static_min(xen_session *session, xen_vm self, int64_t value);


/**
 * Set the static (ie boot-time) range of virtual memory that the VM is
 * allowed to use.
 */
extern bool
xen_vm_set_memory_static_range(xen_session *session, xen_vm self, int64_t min, int64_t max);

/**
 * Set the static (ie boot-time) range of virtual memory that the VM is
 * allowed to use.
 */
extern bool
xen_vm_set_memory_static_range_async(xen_session *session, xen_task *result, xen_vm self, int64_t min, int64_t max);


/**
 * Set the memory limits of this VM.
 */
extern bool
xen_vm_set_memory_limits(xen_session *session, xen_vm self, int64_t static_min, int64_t static_max, int64_t dynamic_min, int64_t dynamic_max);

/**
 * Set the memory limits of this VM.
 */
extern bool
xen_vm_set_memory_limits_async(xen_session *session, xen_task *result, xen_vm self, int64_t static_min, int64_t static_max, int64_t dynamic_min, int64_t dynamic_max);


/**
 * Set the memory target for a running VM.
 */
extern bool
xen_vm_set_memory_target_live(xen_session *session, xen_vm self, int64_t target);

/**
 * Set the memory target for a running VM.
 */
extern bool
xen_vm_set_memory_target_live_async(xen_session *session, xen_task *result, xen_vm self, int64_t target);


/**
 * Wait for a running VM to reach its current memory target.
 */
extern bool
xen_vm_wait_memory_target_live(xen_session *session, xen_vm self);

/**
 * Wait for a running VM to reach its current memory target.
 */
extern bool
xen_vm_wait_memory_target_live_async(xen_session *session, xen_task *result, xen_vm self);


/**
 * Return true if the VM is currently 'co-operative' i.e. is expected
 * to reach a balloon target and actually has done.
 */
extern bool
xen_vm_get_cooperative(xen_session *session, bool *result, xen_vm self);

/**
 * Return true if the VM is currently 'co-operative' i.e. is expected
 * to reach a balloon target and actually has done.
 */
extern bool
xen_vm_get_cooperative_async(xen_session *session, xen_task *result, xen_vm self);


/**
 * Set the shadow memory multiplier on a halted VM.
 */
extern bool
xen_vm_set_hvm_shadow_multiplier(xen_session *session, xen_vm self, double value);


/**
 * Set the shadow memory multiplier on a running VM.
 */
extern bool
xen_vm_set_shadow_multiplier_live(xen_session *session, xen_vm self, double multiplier);

/**
 * Set the shadow memory multiplier on a running VM.
 */
extern bool
xen_vm_set_shadow_multiplier_live_async(xen_session *session, xen_task *result, xen_vm self, double multiplier);


/**
 * Set the maximum number of VCPUs for a halted VM.
 */
extern bool
xen_vm_set_vcpus_max(xen_session *session, xen_vm self, int64_t value);


/**
 * Set the number of startup VCPUs for a halted VM.
 */
extern bool
xen_vm_set_vcpus_at_startup(xen_session *session, xen_vm self, int64_t value);


/**
 * Send the given key as a sysrq to this VM.  The key is specified as a
 * single character (a String of length 1).  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_send_sysrq(xen_session *session, xen_vm vm, const char *key);

/**
 * Send the given key as a sysrq to this VM.  The key is specified as a
 * single character (a String of length 1).  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_send_sysrq_async(xen_session *session, xen_task *result, xen_vm vm, const char *key);


/**
 * Send the named trigger to this VM.  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_send_trigger(xen_session *session, xen_vm vm, const char *trigger);

/**
 * Send the named trigger to this VM.  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_send_trigger_async(xen_session *session, xen_task *result, xen_vm vm, const char *trigger);


/**
 * Returns the maximum amount of guest memory which will fit, together
 * with overheads, in the supplied amount of physical memory. If 'exact' is
 * true then an exact calculation is performed using the VM's current
 * settings. If 'exact' is false then a more conservative approximation is
 * used.
 */
extern bool
xen_vm_maximise_memory(xen_session *session, int64_t *result, xen_vm self, int64_t total, bool approximate);

/**
 * Returns the maximum amount of guest memory which will fit, together
 * with overheads, in the supplied amount of physical memory. If 'exact' is
 * true then an exact calculation is performed using the VM's current
 * settings. If 'exact' is false then a more conservative approximation is
 * used.
 */
extern bool
xen_vm_maximise_memory_async(xen_session *session, xen_task *result, xen_vm self, int64_t total, bool approximate);


/**
 * Migrate the VM to another host.  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_migrate_send(xen_session *session, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options);

/**
 * Migrate the VM to another host.  This can only be called when the
 * specified VM is in the Running state.
 */
extern bool
xen_vm_migrate_send_async(xen_session *session, xen_task *result, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options);


/**
 * Assert whether a VM can be migrated to the specified destination.
 */
extern bool
xen_vm_assert_can_migrate(xen_session *session, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options);

/**
 * Assert whether a VM can be migrated to the specified destination.
 */
extern bool
xen_vm_assert_can_migrate_async(xen_session *session, xen_task *result, xen_vm vm, xen_string_string_map *dest, bool live, xen_vdi_sr_map *vdi_map, xen_vif_network_map *vif_map, xen_string_string_map *options);


/**
 * Returns a record describing the VM's dynamic state, initialised when
 * the VM boots and updated to reflect runtime configuration changes e.g. CPU
 * hotplug.
 */
extern bool
xen_vm_get_boot_record(xen_session *session, xen_vm_record **result, xen_vm self);


/**
 * Start recording the specified data source.
 */
extern bool
xen_vm_record_data_source(xen_session *session, xen_vm self, const char *data_source);


/**
 * Query the latest value of the specified data source.
 */
extern bool
xen_vm_query_data_source(xen_session *session, double *result, xen_vm self, const char *data_source);


/**
 * Forget the recorded statistics related to the specified data source.
 */
extern bool
xen_vm_forget_data_source_archives(xen_session *session, xen_vm self, const char *data_source);


/**
 * Check to see whether this operation is acceptable in the current
 * state of the system, raising an error if the operation is invalid for some
 * reason.
 */
extern bool
xen_vm_assert_operation_valid(xen_session *session, xen_vm self, enum xen_vm_operations op);

/**
 * Check to see whether this operation is acceptable in the current
 * state of the system, raising an error if the operation is invalid for some
 * reason.
 */
extern bool
xen_vm_assert_operation_valid_async(xen_session *session, xen_task *result, xen_vm self, enum xen_vm_operations op);


/**
 * Recomputes the list of acceptable operations.
 */
extern bool
xen_vm_update_allowed_operations(xen_session *session, xen_vm self);

/**
 * Recomputes the list of acceptable operations.
 */
extern bool
xen_vm_update_allowed_operations_async(xen_session *session, xen_task *result, xen_vm self);


/**
 * Returns a list of the allowed values that a VBD device field can
 * take.
 */
extern bool
xen_vm_get_allowed_vbd_devices(xen_session *session, struct xen_string_set **result, xen_vm vm);


/**
 * Returns a list of the allowed values that a VIF device field can
 * take.
 */
extern bool
xen_vm_get_allowed_vif_devices(xen_session *session, struct xen_string_set **result, xen_vm vm);


/**
 * Return the list of hosts on which this VM may run.
 */
extern bool
xen_vm_get_possible_hosts(xen_session *session, struct xen_host_set **result, xen_vm vm);

/**
 * Return the list of hosts on which this VM may run.
 */
extern bool
xen_vm_get_possible_hosts_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Returns an error if the VM could not boot on this host for some
 * reason.
 */
extern bool
xen_vm_assert_can_boot_here(xen_session *session, xen_vm self, xen_host host);

/**
 * Returns an error if the VM could not boot on this host for some
 * reason.
 */
extern bool
xen_vm_assert_can_boot_here_async(xen_session *session, xen_task *result, xen_vm self, xen_host host);


/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this VM.
 */
extern bool
xen_vm_create_new_blob(xen_session *session, xen_blob *result, xen_vm vm, const char *name, const char *mime_type, bool pubblic);

/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this VM.
 */
extern bool
xen_vm_create_new_blob_async(xen_session *session, xen_task *result, xen_vm vm, const char *name, const char *mime_type, bool pubblic);


/**
 * Returns an error if the VM is not considered agile e.g. because it
 * is tied to a resource local to a host.
 */
extern bool
xen_vm_assert_agile(xen_session *session, xen_vm self);

/**
 * Returns an error if the VM is not considered agile e.g. because it
 * is tied to a resource local to a host.
 */
extern bool
xen_vm_assert_agile_async(xen_session *session, xen_task *result, xen_vm self);


/**
 * Returns mapping of hosts to ratings, indicating the suitability of
 * starting the VM at that location according to wlb. Rating is replaced with
 * an error if the VM cannot boot there.
 */
extern bool
xen_vm_retrieve_wlb_recommendations(xen_session *session, xen_host_string_set_map **result, xen_vm vm);

/**
 * Returns mapping of hosts to ratings, indicating the suitability of
 * starting the VM at that location according to wlb. Rating is replaced with
 * an error if the VM cannot boot there.
 */
extern bool
xen_vm_retrieve_wlb_recommendations_async(xen_session *session, xen_task *result, xen_vm vm);


/**
 * Copy the BIOS strings from the given host to this VM.
 */
extern bool
xen_vm_copy_bios_strings(xen_session *session, xen_vm vm, xen_host host);

/**
 * Copy the BIOS strings from the given host to this VM.
 */
extern bool
xen_vm_copy_bios_strings_async(xen_session *session, xen_task *result, xen_vm vm, xen_host host);


/**
 * Set the value of the protection_policy field.
 */
extern bool
xen_vm_set_protection_policy(xen_session *session, xen_vm self, xen_vmpp value);


/**
 * Set this VM's start delay in seconds.
 */
extern bool
xen_vm_set_start_delay(xen_session *session, xen_vm self, int64_t value);

/**
 * Set this VM's start delay in seconds.
 */
extern bool
xen_vm_set_start_delay_async(xen_session *session, xen_task *result, xen_vm self, int64_t value);


/**
 * Set this VM's shutdown delay in seconds.
 */
extern bool
xen_vm_set_shutdown_delay(xen_session *session, xen_vm self, int64_t value);

/**
 * Set this VM's shutdown delay in seconds.
 */
extern bool
xen_vm_set_shutdown_delay_async(xen_session *session, xen_task *result, xen_vm self, int64_t value);


/**
 * Set this VM's boot order.
 */
extern bool
xen_vm_set_order(xen_session *session, xen_vm self, int64_t value);

/**
 * Set this VM's boot order.
 */
extern bool
xen_vm_set_order_async(xen_session *session, xen_task *result, xen_vm self, int64_t value);


/**
 * Set this VM's suspend VDI, which must be indentical to its current
 * one.
 */
extern bool
xen_vm_set_suspend_vdi(xen_session *session, xen_vm self, xen_vdi value);

/**
 * Set this VM's suspend VDI, which must be indentical to its current
 * one.
 */
extern bool
xen_vm_set_suspend_vdi_async(xen_session *session, xen_task *result, xen_vm self, xen_vdi value);


/**
 * Assert whether all SRs required to recover this VM are available.
 */
extern bool
xen_vm_assert_can_be_recovered(xen_session *session, xen_vm self, xen_session *session_to);

/**
 * Assert whether all SRs required to recover this VM are available.
 */
extern bool
xen_vm_assert_can_be_recovered_async(xen_session *session, xen_task *result, xen_vm self, xen_session *session_to);


/**
 * Recover the VM.
 */
extern bool
xen_vm_recover(xen_session *session, xen_vm self, xen_session *session_to, bool force);

/**
 * Recover the VM.
 */
extern bool
xen_vm_recover_async(xen_session *session, xen_task *result, xen_vm self, xen_session *session_to, bool force);


/**
 * Import using a conversion service.
 */
extern bool
xen_vm_import_convert(xen_session *session, const char *type, const char *username, const char *password, xen_sr sr, xen_string_string_map *remote_config);

/**
 * Import using a conversion service.
 */
extern bool
xen_vm_import_convert_async(xen_session *session, xen_task *result, const char *type, const char *username, const char *password, xen_sr sr, xen_string_string_map *remote_config);


/**
 * Assign this VM to an appliance.
 */
extern bool
xen_vm_set_appliance(xen_session *session, xen_vm self, xen_vm_appliance value);

/**
 * Assign this VM to an appliance.
 */
extern bool
xen_vm_set_appliance_async(xen_session *session, xen_task *result, xen_vm self, xen_vm_appliance value);


/**
 * Query the system services advertised by this VM and register them.
 * This can only be applied to a system domain.
 */
extern bool
xen_vm_query_services(xen_session *session, xen_string_string_map **result, xen_vm self);

/**
 * Query the system services advertised by this VM and register them.
 * This can only be applied to a system domain.
 */
extern bool
xen_vm_query_services_async(xen_session *session, xen_task *result, xen_vm self);


/**
 * Return a list of all the VMs known to the system.
 */
extern bool
xen_vm_get_all(xen_session *session, struct xen_vm_set **result);


/**
 * Return a map of VM references to VM records for all VMs known to the
 * system.
 */
extern bool
xen_vm_get_all_records(xen_session *session, xen_vm_xen_vm_record_map **result);


#endif
