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


#ifndef XEN_POOL_H
#define XEN_POOL_H

#include <xen/api/xen_blob_decl.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_network_decl.h>
#include <xen/api/xen_pif_decl.h>
#include <xen/api/xen_pool_decl.h>
#include <xen/api/xen_pool_xen_pool_record_map.h>
#include <xen/api/xen_sr_decl.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vdi_decl.h>
#include <xen/api/xen_vm_decl.h>
#include <xen/api/xen_vm_string_map.h>
#include <xen/api/xen_vm_string_set_map.h>
#include <xen/api/xen_vm_string_string_map_map.h>


/*
 * The pool class.
 * 
 * Pool-wide information.
 */


/**
 * Free the given xen_pool.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_pool_free(xen_pool pool);


typedef struct xen_pool_set
{
    size_t size;
    xen_pool *contents[];
} xen_pool_set;

/**
 * Allocate a xen_pool_set of the given size.
 */
extern xen_pool_set *
xen_pool_set_alloc(size_t size);

/**
 * Free the given xen_pool_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_pool_set_free(xen_pool_set *set);


typedef struct xen_pool_record
{
    xen_pool handle;
    char *uuid;
    char *name_label;
    char *name_description;
    struct xen_host_record_opt *master;
    struct xen_sr_record_opt *default_sr;
    struct xen_sr_record_opt *suspend_image_sr;
    struct xen_sr_record_opt *crash_dump_sr;
    xen_string_string_map *other_config;
    bool ha_enabled;
    xen_string_string_map *ha_configuration;
    struct xen_string_set *ha_statefiles;
    int64_t ha_host_failures_to_tolerate;
    int64_t ha_plan_exists_for;
    bool ha_allow_overcommit;
    bool ha_overcommitted;
    xen_string_blob_map *blobs;
    struct xen_string_set *tags;
    xen_string_string_map *gui_config;
    char *wlb_url;
    char *wlb_username;
    bool wlb_enabled;
    bool wlb_verify_cert;
    bool redo_log_enabled;
    struct xen_vdi_record_opt *redo_log_vdi;
    char *vswitch_controller;
    xen_string_string_map *restrictions;
    struct xen_vdi_record_opt_set *metadata_vdis;
} xen_pool_record;

/**
 * Allocate a xen_pool_record.
 */
extern xen_pool_record *
xen_pool_record_alloc(void);

/**
 * Free the given xen_pool_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_pool_record_free(xen_pool_record *record);


typedef struct xen_pool_record_opt
{
    bool is_record;
    union
    {
        xen_pool handle;
        xen_pool_record *record;
    } u;
} xen_pool_record_opt;

/**
 * Allocate a xen_pool_record_opt.
 */
extern xen_pool_record_opt *
xen_pool_record_opt_alloc(void);

/**
 * Free the given xen_pool_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_pool_record_opt_free(xen_pool_record_opt *record_opt);


typedef struct xen_pool_record_set
{
    size_t size;
    xen_pool_record *contents[];
} xen_pool_record_set;

/**
 * Allocate a xen_pool_record_set of the given size.
 */
extern xen_pool_record_set *
xen_pool_record_set_alloc(size_t size);

/**
 * Free the given xen_pool_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_pool_record_set_free(xen_pool_record_set *set);



typedef struct xen_pool_record_opt_set
{
    size_t size;
    xen_pool_record_opt *contents[];
} xen_pool_record_opt_set;

/**
 * Allocate a xen_pool_record_opt_set of the given size.
 */
extern xen_pool_record_opt_set *
xen_pool_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_pool_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_pool_record_opt_set_free(xen_pool_record_opt_set *set);


/**
 * Get a record containing the current state of the given pool.
 */
extern bool
xen_pool_get_record(xen_session *session, xen_pool_record **result, xen_pool pool);


/**
 * Get a reference to the pool instance with the specified UUID.
 */
extern bool
xen_pool_get_by_uuid(xen_session *session, xen_pool *result, const char *uuid);


/**
 * Get the uuid field of the given pool.
 */
extern bool
xen_pool_get_uuid(xen_session *session, char **result, xen_pool pool);


/**
 * Get the name_label field of the given pool.
 */
extern bool
xen_pool_get_name_label(xen_session *session, char **result, xen_pool pool);


/**
 * Get the name_description field of the given pool.
 */
extern bool
xen_pool_get_name_description(xen_session *session, char **result, xen_pool pool);


/**
 * Get the master field of the given pool.
 */
extern bool
xen_pool_get_master(xen_session *session, xen_host *result, xen_pool pool);


/**
 * Get the default_SR field of the given pool.
 */
extern bool
xen_pool_get_default_sr(xen_session *session, xen_sr *result, xen_pool pool);


/**
 * Get the suspend_image_SR field of the given pool.
 */
extern bool
xen_pool_get_suspend_image_sr(xen_session *session, xen_sr *result, xen_pool pool);


/**
 * Get the crash_dump_SR field of the given pool.
 */
extern bool
xen_pool_get_crash_dump_sr(xen_session *session, xen_sr *result, xen_pool pool);


/**
 * Get the other_config field of the given pool.
 */
extern bool
xen_pool_get_other_config(xen_session *session, xen_string_string_map **result, xen_pool pool);


/**
 * Get the ha_enabled field of the given pool.
 */
extern bool
xen_pool_get_ha_enabled(xen_session *session, bool *result, xen_pool pool);


/**
 * Get the ha_configuration field of the given pool.
 */
extern bool
xen_pool_get_ha_configuration(xen_session *session, xen_string_string_map **result, xen_pool pool);


/**
 * Get the ha_statefiles field of the given pool.
 */
extern bool
xen_pool_get_ha_statefiles(xen_session *session, struct xen_string_set **result, xen_pool pool);


/**
 * Get the ha_host_failures_to_tolerate field of the given pool.
 */
extern bool
xen_pool_get_ha_host_failures_to_tolerate(xen_session *session, int64_t *result, xen_pool pool);


/**
 * Get the ha_plan_exists_for field of the given pool.
 */
extern bool
xen_pool_get_ha_plan_exists_for(xen_session *session, int64_t *result, xen_pool pool);


/**
 * Get the ha_allow_overcommit field of the given pool.
 */
extern bool
xen_pool_get_ha_allow_overcommit(xen_session *session, bool *result, xen_pool pool);


/**
 * Get the ha_overcommitted field of the given pool.
 */
extern bool
xen_pool_get_ha_overcommitted(xen_session *session, bool *result, xen_pool pool);


/**
 * Get the blobs field of the given pool.
 */
extern bool
xen_pool_get_blobs(xen_session *session, xen_string_blob_map **result, xen_pool pool);


/**
 * Get the tags field of the given pool.
 */
extern bool
xen_pool_get_tags(xen_session *session, struct xen_string_set **result, xen_pool pool);


/**
 * Get the gui_config field of the given pool.
 */
extern bool
xen_pool_get_gui_config(xen_session *session, xen_string_string_map **result, xen_pool pool);


/**
 * Get the wlb_url field of the given pool.
 */
extern bool
xen_pool_get_wlb_url(xen_session *session, char **result, xen_pool pool);


/**
 * Get the wlb_username field of the given pool.
 */
extern bool
xen_pool_get_wlb_username(xen_session *session, char **result, xen_pool pool);


/**
 * Get the wlb_enabled field of the given pool.
 */
extern bool
xen_pool_get_wlb_enabled(xen_session *session, bool *result, xen_pool pool);


/**
 * Get the wlb_verify_cert field of the given pool.
 */
extern bool
xen_pool_get_wlb_verify_cert(xen_session *session, bool *result, xen_pool pool);


/**
 * Get the redo_log_enabled field of the given pool.
 */
extern bool
xen_pool_get_redo_log_enabled(xen_session *session, bool *result, xen_pool pool);


/**
 * Get the redo_log_vdi field of the given pool.
 */
extern bool
xen_pool_get_redo_log_vdi(xen_session *session, xen_vdi *result, xen_pool pool);


/**
 * Get the vswitch_controller field of the given pool.
 */
extern bool
xen_pool_get_vswitch_controller(xen_session *session, char **result, xen_pool pool);


/**
 * Get the restrictions field of the given pool.
 */
extern bool
xen_pool_get_restrictions(xen_session *session, xen_string_string_map **result, xen_pool pool);


/**
 * Get the metadata_VDIs field of the given pool.
 */
extern bool
xen_pool_get_metadata_vdis(xen_session *session, struct xen_vdi_set **result, xen_pool pool);


/**
 * Set the name_label field of the given pool.
 */
extern bool
xen_pool_set_name_label(xen_session *session, xen_pool pool, const char *name_label);


/**
 * Set the name_description field of the given pool.
 */
extern bool
xen_pool_set_name_description(xen_session *session, xen_pool pool, const char *name_description);


/**
 * Set the default_SR field of the given pool.
 */
extern bool
xen_pool_set_default_sr(xen_session *session, xen_pool pool, xen_sr default_sr);


/**
 * Set the suspend_image_SR field of the given pool.
 */
extern bool
xen_pool_set_suspend_image_sr(xen_session *session, xen_pool pool, xen_sr suspend_image_sr);


/**
 * Set the crash_dump_SR field of the given pool.
 */
extern bool
xen_pool_set_crash_dump_sr(xen_session *session, xen_pool pool, xen_sr crash_dump_sr);


/**
 * Set the other_config field of the given pool.
 */
extern bool
xen_pool_set_other_config(xen_session *session, xen_pool pool, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * pool.
 */
extern bool
xen_pool_add_to_other_config(xen_session *session, xen_pool pool, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given pool.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_pool_remove_from_other_config(xen_session *session, xen_pool pool, const char *key);


/**
 * Set the ha_allow_overcommit field of the given pool.
 */
extern bool
xen_pool_set_ha_allow_overcommit(xen_session *session, xen_pool pool, bool ha_allow_overcommit);


/**
 * Set the tags field of the given pool.
 */
extern bool
xen_pool_set_tags(xen_session *session, xen_pool pool, struct xen_string_set *tags);


/**
 * Add the given value to the tags field of the given pool.  If the
 * value is already in that Set, then do nothing.
 */
extern bool
xen_pool_add_tags(xen_session *session, xen_pool pool, const char *value);


/**
 * Remove the given value from the tags field of the given pool.  If
 * the value is not in that Set, then do nothing.
 */
extern bool
xen_pool_remove_tags(xen_session *session, xen_pool pool, const char *value);


/**
 * Set the gui_config field of the given pool.
 */
extern bool
xen_pool_set_gui_config(xen_session *session, xen_pool pool, xen_string_string_map *gui_config);


/**
 * Add the given key-value pair to the gui_config field of the given
 * pool.
 */
extern bool
xen_pool_add_to_gui_config(xen_session *session, xen_pool pool, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the gui_config
 * field of the given pool.  If the key is not in that Map, then do nothing.
 */
extern bool
xen_pool_remove_from_gui_config(xen_session *session, xen_pool pool, const char *key);


/**
 * Set the wlb_enabled field of the given pool.
 */
extern bool
xen_pool_set_wlb_enabled(xen_session *session, xen_pool pool, bool wlb_enabled);


/**
 * Set the wlb_verify_cert field of the given pool.
 */
extern bool
xen_pool_set_wlb_verify_cert(xen_session *session, xen_pool pool, bool wlb_verify_cert);


/**
 * Instruct host to join a new pool.
 */
extern bool
xen_pool_join(xen_session *session, const char *master_address, const char *master_username, const char *master_password);

/**
 * Instruct host to join a new pool.
 */
extern bool
xen_pool_join_async(xen_session *session, xen_task *result, const char *master_address, const char *master_username, const char *master_password);


/**
 * Instruct host to join a new pool.
 */
extern bool
xen_pool_join_force(xen_session *session, const char *master_address, const char *master_username, const char *master_password);

/**
 * Instruct host to join a new pool.
 */
extern bool
xen_pool_join_force_async(xen_session *session, xen_task *result, const char *master_address, const char *master_username, const char *master_password);


/**
 * Instruct a pool master to eject a host from the pool.
 */
extern bool
xen_pool_eject(xen_session *session, xen_host host);

/**
 * Instruct a pool master to eject a host from the pool.
 */
extern bool
xen_pool_eject_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Instruct host that's currently a slave to transition to being
 * master.
 */
extern bool
xen_pool_emergency_transition_to_master(xen_session *session);


/**
 * Instruct a slave already in a pool that the master has changed.
 */
extern bool
xen_pool_emergency_reset_master(xen_session *session, const char *master_address);


/**
 * Instruct a pool master, M, to try and contact its slaves and, if
 * slaves are in emergency mode, reset their master address to M.
 */
extern bool
xen_pool_recover_slaves(xen_session *session, struct xen_host_set **result);

/**
 * Instruct a pool master, M, to try and contact its slaves and, if
 * slaves are in emergency mode, reset their master address to M.
 */
extern bool
xen_pool_recover_slaves_async(xen_session *session, xen_task *result);


/**
 * Create PIFs, mapping a network to the same physical interface/VLAN
 * on each host. This call is deprecated: use Pool.create_VLAN_from_PIF
 * instead.
 */
extern bool
xen_pool_create_vlan(xen_session *session, struct xen_pif_set **result, const char *device, xen_network network, int64_t vlan);

/**
 * Create PIFs, mapping a network to the same physical interface/VLAN
 * on each host. This call is deprecated: use Pool.create_VLAN_from_PIF
 * instead.
 */
extern bool
xen_pool_create_vlan_async(xen_session *session, xen_task *result, const char *device, xen_network network, int64_t vlan);


/**
 * Create a pool-wide VLAN by taking the PIF.
 */
extern bool
xen_pool_create_vlan_from_pif(xen_session *session, struct xen_pif_set **result, xen_pif pif, xen_network network, int64_t vlan);

/**
 * Create a pool-wide VLAN by taking the PIF.
 */
extern bool
xen_pool_create_vlan_from_pif_async(xen_session *session, xen_task *result, xen_pif pif, xen_network network, int64_t vlan);


/**
 * Turn on High Availability mode.
 */
extern bool
xen_pool_enable_ha(xen_session *session, struct xen_sr_set *heartbeat_srs, xen_string_string_map *configuration);

/**
 * Turn on High Availability mode.
 */
extern bool
xen_pool_enable_ha_async(xen_session *session, xen_task *result, struct xen_sr_set *heartbeat_srs, xen_string_string_map *configuration);


/**
 * Turn off High Availability mode.
 */
extern bool
xen_pool_disable_ha(xen_session *session);

/**
 * Turn off High Availability mode.
 */
extern bool
xen_pool_disable_ha_async(xen_session *session, xen_task *result);


/**
 * Forcibly synchronise the database now.
 */
extern bool
xen_pool_sync_database(xen_session *session);

/**
 * Forcibly synchronise the database now.
 */
extern bool
xen_pool_sync_database_async(xen_session *session, xen_task *result);


/**
 * Perform an orderly handover of the role of master to the referenced
 * host.
 */
extern bool
xen_pool_designate_new_master(xen_session *session, xen_host host);

/**
 * Perform an orderly handover of the role of master to the referenced
 * host.
 */
extern bool
xen_pool_designate_new_master_async(xen_session *session, xen_task *result, xen_host host);


/**
 * When this call returns the VM restart logic will not run for the
 * requested number of seconds. If the argument is zero then the restart
 * thread is immediately unblocked.
 */
extern bool
xen_pool_ha_prevent_restarts_for(xen_session *session, int64_t seconds);


/**
 * Returns true if a VM failover plan exists for up to 'n' host
 * failures.
 */
extern bool
xen_pool_ha_failover_plan_exists(xen_session *session, bool *result, int64_t n);


/**
 * Returns the maximum number of host failures we could tolerate before
 * we would be unable to restart configured VMs.
 */
extern bool
xen_pool_ha_compute_max_host_failures_to_tolerate(xen_session *session, int64_t *result);


/**
 * Returns the maximum number of host failures we could tolerate before
 * we would be unable to restart the provided VMs.
 */
extern bool
xen_pool_ha_compute_hypothetical_max_host_failures_to_tolerate(xen_session *session, int64_t *result, xen_vm_string_map *configuration);


/**
 * Return a VM failover plan assuming a given subset of hosts fail.
 */
extern bool
xen_pool_ha_compute_vm_failover_plan(xen_session *session, xen_vm_string_string_map_map **result, struct xen_host_set *failed_hosts, struct xen_vm_set *failed_vms);


/**
 * Set the maximum number of host failures to consider in the HA VM
 * restart planner.
 */
extern bool
xen_pool_set_ha_host_failures_to_tolerate(xen_session *session, xen_pool self, int64_t value);

/**
 * Set the maximum number of host failures to consider in the HA VM
 * restart planner.
 */
extern bool
xen_pool_set_ha_host_failures_to_tolerate_async(xen_session *session, xen_task *result, xen_pool self, int64_t value);


/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this pool.
 */
extern bool
xen_pool_create_new_blob(xen_session *session, xen_blob *result, xen_pool pool, const char *name, const char *mime_type, bool pubblic);

/**
 * Create a placeholder for a named binary blob of data that is
 * associated with this pool.
 */
extern bool
xen_pool_create_new_blob_async(xen_session *session, xen_task *result, xen_pool pool, const char *name, const char *mime_type, bool pubblic);


/**
 * This call enables external authentication on all the hosts of the
 * pool.
 */
extern bool
xen_pool_enable_external_auth(xen_session *session, xen_pool pool, xen_string_string_map *config, const char *service_name, const char *auth_type);


/**
 * This call disables external authentication on all the hosts of the
 * pool.
 */
extern bool
xen_pool_disable_external_auth(xen_session *session, xen_pool pool, xen_string_string_map *config);


/**
 * This call asynchronously detects if the external authentication
 * configuration in any slave is different from that in the master and raises
 * appropriate alerts.
 */
extern bool
xen_pool_detect_nonhomogeneous_external_auth(xen_session *session, xen_pool pool);


/**
 * Initializes workload balancing monitoring on this pool with the
 * specified wlb server.
 */
extern bool
xen_pool_initialize_wlb(xen_session *session, const char *wlb_url, const char *wlb_username, const char *wlb_password, const char *xenserver_username, const char *xenserver_password);

/**
 * Initializes workload balancing monitoring on this pool with the
 * specified wlb server.
 */
extern bool
xen_pool_initialize_wlb_async(xen_session *session, xen_task *result, const char *wlb_url, const char *wlb_username, const char *wlb_password, const char *xenserver_username, const char *xenserver_password);


/**
 * Permanently deconfigures workload balancing monitoring on this pool.
 */
extern bool
xen_pool_deconfigure_wlb(xen_session *session);

/**
 * Permanently deconfigures workload balancing monitoring on this pool.
 */
extern bool
xen_pool_deconfigure_wlb_async(xen_session *session, xen_task *result);


/**
 * Sets the pool optimization criteria for the workload balancing
 * server.
 */
extern bool
xen_pool_send_wlb_configuration(xen_session *session, xen_string_string_map *config);

/**
 * Sets the pool optimization criteria for the workload balancing
 * server.
 */
extern bool
xen_pool_send_wlb_configuration_async(xen_session *session, xen_task *result, xen_string_string_map *config);


/**
 * Retrieves the pool optimization criteria from the workload balancing
 * server.
 */
extern bool
xen_pool_retrieve_wlb_configuration(xen_session *session, xen_string_string_map **result);

/**
 * Retrieves the pool optimization criteria from the workload balancing
 * server.
 */
extern bool
xen_pool_retrieve_wlb_configuration_async(xen_session *session, xen_task *result);


/**
 * Retrieves vm migrate recommendations for the pool from the workload
 * balancing server.
 */
extern bool
xen_pool_retrieve_wlb_recommendations(xen_session *session, xen_vm_string_set_map **result);

/**
 * Retrieves vm migrate recommendations for the pool from the workload
 * balancing server.
 */
extern bool
xen_pool_retrieve_wlb_recommendations_async(xen_session *session, xen_task *result);


/**
 * Send the given body to the given host and port, using HTTPS, and
 * print the response.  This is used for debugging the SSL layer.
 */
extern bool
xen_pool_send_test_post(xen_session *session, char **result, const char *host, int64_t port, const char *body);

/**
 * Send the given body to the given host and port, using HTTPS, and
 * print the response.  This is used for debugging the SSL layer.
 */
extern bool
xen_pool_send_test_post_async(xen_session *session, xen_task *result, const char *host, int64_t port, const char *body);


/**
 * Install an SSL certificate pool-wide.
 */
extern bool
xen_pool_certificate_install(xen_session *session, const char *name, const char *cert);

/**
 * Install an SSL certificate pool-wide.
 */
extern bool
xen_pool_certificate_install_async(xen_session *session, xen_task *result, const char *name, const char *cert);


/**
 * Remove an SSL certificate.
 */
extern bool
xen_pool_certificate_uninstall(xen_session *session, const char *name);

/**
 * Remove an SSL certificate.
 */
extern bool
xen_pool_certificate_uninstall_async(xen_session *session, xen_task *result, const char *name);


/**
 * List all installed SSL certificates.
 */
extern bool
xen_pool_certificate_list(xen_session *session, struct xen_string_set **result);

/**
 * List all installed SSL certificates.
 */
extern bool
xen_pool_certificate_list_async(xen_session *session, xen_task *result);


/**
 * Install an SSL certificate revocation list, pool-wide.
 */
extern bool
xen_pool_crl_install(xen_session *session, const char *name, const char *cert);

/**
 * Install an SSL certificate revocation list, pool-wide.
 */
extern bool
xen_pool_crl_install_async(xen_session *session, xen_task *result, const char *name, const char *cert);


/**
 * Remove an SSL certificate revocation list.
 */
extern bool
xen_pool_crl_uninstall(xen_session *session, const char *name);

/**
 * Remove an SSL certificate revocation list.
 */
extern bool
xen_pool_crl_uninstall_async(xen_session *session, xen_task *result, const char *name);


/**
 * List all installed SSL certificate revocation lists.
 */
extern bool
xen_pool_crl_list(xen_session *session, struct xen_string_set **result);

/**
 * List all installed SSL certificate revocation lists.
 */
extern bool
xen_pool_crl_list_async(xen_session *session, xen_task *result);


/**
 * Sync SSL certificates from master to slaves.
 */
extern bool
xen_pool_certificate_sync(xen_session *session);

/**
 * Sync SSL certificates from master to slaves.
 */
extern bool
xen_pool_certificate_sync_async(xen_session *session, xen_task *result);


/**
 * Enable the redo log on the given SR and start using it, unless HA is
 * enabled.
 */
extern bool
xen_pool_enable_redo_log(xen_session *session, xen_sr sr);

/**
 * Enable the redo log on the given SR and start using it, unless HA is
 * enabled.
 */
extern bool
xen_pool_enable_redo_log_async(xen_session *session, xen_task *result, xen_sr sr);


/**
 * Disable the redo log if in use, unless HA is enabled.
 */
extern bool
xen_pool_disable_redo_log(xen_session *session);

/**
 * Disable the redo log if in use, unless HA is enabled.
 */
extern bool
xen_pool_disable_redo_log_async(xen_session *session, xen_task *result);


/**
 * Set the IP address of the vswitch controller.
 */
extern bool
xen_pool_set_vswitch_controller(xen_session *session, const char *address);

/**
 * Set the IP address of the vswitch controller.
 */
extern bool
xen_pool_set_vswitch_controller_async(xen_session *session, xen_task *result, const char *address);


/**
 * This call tests if a location is valid.
 */
extern bool
xen_pool_test_archive_target(xen_session *session, char **result, xen_pool self, xen_string_string_map *config);


/**
 * This call attempts to enable pool-wide local storage caching.
 */
extern bool
xen_pool_enable_local_storage_caching(xen_session *session, xen_pool self);

/**
 * This call attempts to enable pool-wide local storage caching.
 */
extern bool
xen_pool_enable_local_storage_caching_async(xen_session *session, xen_task *result, xen_pool self);


/**
 * This call disables pool-wide local storage caching.
 */
extern bool
xen_pool_disable_local_storage_caching(xen_session *session, xen_pool self);

/**
 * This call disables pool-wide local storage caching.
 */
extern bool
xen_pool_disable_local_storage_caching_async(xen_session *session, xen_task *result, xen_pool self);


/**
 * Return a list of all the pools known to the system.
 */
extern bool
xen_pool_get_all(xen_session *session, struct xen_pool_set **result);


/**
 * Return a map of pool references to pool records for all pools known
 * to the system.
 */
extern bool
xen_pool_get_all_records(xen_session *session, xen_pool_xen_pool_record_map **result);


#endif
