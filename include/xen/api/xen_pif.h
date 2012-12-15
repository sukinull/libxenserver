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


#ifndef XEN_PIF_H
#define XEN_PIF_H

#include <xen/api/xen_bond_decl.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_ip_configuration_mode.h>
#include <xen/api/xen_ipv6_configuration_mode.h>
#include <xen/api/xen_network_decl.h>
#include <xen/api/xen_pif_decl.h>
#include <xen/api/xen_pif_metrics_decl.h>
#include <xen/api/xen_pif_xen_pif_record_map.h>
#include <xen/api/xen_primary_address_type.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_tunnel_decl.h>
#include <xen/api/xen_vlan_decl.h>


/*
 * The PIF class.
 * 
 * A physical network interface (note separate VLANs are represented as
 * several PIFs).
 */


/**
 * Free the given xen_pif.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_pif_free(xen_pif pif);


typedef struct xen_pif_set
{
    size_t size;
    xen_pif *contents[];
} xen_pif_set;

/**
 * Allocate a xen_pif_set of the given size.
 */
extern xen_pif_set *
xen_pif_set_alloc(size_t size);

/**
 * Free the given xen_pif_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_pif_set_free(xen_pif_set *set);


typedef struct xen_pif_record
{
    xen_pif handle;
    char *uuid;
    char *device;
    struct xen_network_record_opt *network;
    struct xen_host_record_opt *host;
    char *mac;
    int64_t mtu;
    int64_t vlan;
    struct xen_pif_metrics_record_opt *metrics;
    bool physical;
    bool currently_attached;
    enum xen_ip_configuration_mode ip_configuration_mode;
    char *ip;
    char *netmask;
    char *gateway;
    char *dns;
    struct xen_bond_record_opt *bond_slave_of;
    struct xen_bond_record_opt_set *bond_master_of;
    struct xen_vlan_record_opt *vlan_master_of;
    struct xen_vlan_record_opt_set *vlan_slave_of;
    bool management;
    xen_string_string_map *other_config;
    bool disallow_unplug;
    struct xen_tunnel_record_opt_set *tunnel_access_pif_of;
    struct xen_tunnel_record_opt_set *tunnel_transport_pif_of;
    enum xen_ipv6_configuration_mode ipv6_configuration_mode;
    struct xen_string_set *ipv6;
    char *ipv6_gateway;
    enum xen_primary_address_type primary_address_type;
} xen_pif_record;

/**
 * Allocate a xen_pif_record.
 */
extern xen_pif_record *
xen_pif_record_alloc(void);

/**
 * Free the given xen_pif_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_pif_record_free(xen_pif_record *record);


typedef struct xen_pif_record_opt
{
    bool is_record;
    union
    {
        xen_pif handle;
        xen_pif_record *record;
    } u;
} xen_pif_record_opt;

/**
 * Allocate a xen_pif_record_opt.
 */
extern xen_pif_record_opt *
xen_pif_record_opt_alloc(void);

/**
 * Free the given xen_pif_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_pif_record_opt_free(xen_pif_record_opt *record_opt);


typedef struct xen_pif_record_set
{
    size_t size;
    xen_pif_record *contents[];
} xen_pif_record_set;

/**
 * Allocate a xen_pif_record_set of the given size.
 */
extern xen_pif_record_set *
xen_pif_record_set_alloc(size_t size);

/**
 * Free the given xen_pif_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_pif_record_set_free(xen_pif_record_set *set);



typedef struct xen_pif_record_opt_set
{
    size_t size;
    xen_pif_record_opt *contents[];
} xen_pif_record_opt_set;

/**
 * Allocate a xen_pif_record_opt_set of the given size.
 */
extern xen_pif_record_opt_set *
xen_pif_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_pif_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_pif_record_opt_set_free(xen_pif_record_opt_set *set);


/**
 * Get a record containing the current state of the given PIF.
 */
extern bool
xen_pif_get_record(xen_session *session, xen_pif_record **result, xen_pif pif);


/**
 * Get a reference to the PIF instance with the specified UUID.
 */
extern bool
xen_pif_get_by_uuid(xen_session *session, xen_pif *result, char *uuid);


/**
 * Get the uuid field of the given PIF.
 */
extern bool
xen_pif_get_uuid(xen_session *session, char **result, xen_pif pif);


/**
 * Get the device field of the given PIF.
 */
extern bool
xen_pif_get_device(xen_session *session, char **result, xen_pif pif);


/**
 * Get the network field of the given PIF.
 */
extern bool
xen_pif_get_network(xen_session *session, xen_network *result, xen_pif pif);


/**
 * Get the host field of the given PIF.
 */
extern bool
xen_pif_get_host(xen_session *session, xen_host *result, xen_pif pif);


/**
 * Get the MAC field of the given PIF.
 */
extern bool
xen_pif_get_mac(xen_session *session, char **result, xen_pif pif);


/**
 * Get the MTU field of the given PIF.
 */
extern bool
xen_pif_get_mtu(xen_session *session, int64_t *result, xen_pif pif);


/**
 * Get the VLAN field of the given PIF.
 */
extern bool
xen_pif_get_vlan(xen_session *session, int64_t *result, xen_pif pif);


/**
 * Get the metrics field of the given PIF.
 */
extern bool
xen_pif_get_metrics(xen_session *session, xen_pif_metrics *result, xen_pif pif);


/**
 * Get the physical field of the given PIF.
 */
extern bool
xen_pif_get_physical(xen_session *session, bool *result, xen_pif pif);


/**
 * Get the currently_attached field of the given PIF.
 */
extern bool
xen_pif_get_currently_attached(xen_session *session, bool *result, xen_pif pif);


/**
 * Get the ip_configuration_mode field of the given PIF.
 */
extern bool
xen_pif_get_ip_configuration_mode(xen_session *session, enum xen_ip_configuration_mode *result, xen_pif pif);


/**
 * Get the IP field of the given PIF.
 */
extern bool
xen_pif_get_ip(xen_session *session, char **result, xen_pif pif);


/**
 * Get the netmask field of the given PIF.
 */
extern bool
xen_pif_get_netmask(xen_session *session, char **result, xen_pif pif);


/**
 * Get the gateway field of the given PIF.
 */
extern bool
xen_pif_get_gateway(xen_session *session, char **result, xen_pif pif);


/**
 * Get the DNS field of the given PIF.
 */
extern bool
xen_pif_get_dns(xen_session *session, char **result, xen_pif pif);


/**
 * Get the bond_slave_of field of the given PIF.
 */
extern bool
xen_pif_get_bond_slave_of(xen_session *session, xen_bond *result, xen_pif pif);


/**
 * Get the bond_master_of field of the given PIF.
 */
extern bool
xen_pif_get_bond_master_of(xen_session *session, struct xen_bond_set **result, xen_pif pif);


/**
 * Get the VLAN_master_of field of the given PIF.
 */
extern bool
xen_pif_get_vlan_master_of(xen_session *session, xen_vlan *result, xen_pif pif);


/**
 * Get the VLAN_slave_of field of the given PIF.
 */
extern bool
xen_pif_get_vlan_slave_of(xen_session *session, struct xen_vlan_set **result, xen_pif pif);


/**
 * Get the management field of the given PIF.
 */
extern bool
xen_pif_get_management(xen_session *session, bool *result, xen_pif pif);


/**
 * Get the other_config field of the given PIF.
 */
extern bool
xen_pif_get_other_config(xen_session *session, xen_string_string_map **result, xen_pif pif);


/**
 * Get the disallow_unplug field of the given PIF.
 */
extern bool
xen_pif_get_disallow_unplug(xen_session *session, bool *result, xen_pif pif);


/**
 * Get the tunnel_access_PIF_of field of the given PIF.
 */
extern bool
xen_pif_get_tunnel_access_pif_of(xen_session *session, struct xen_tunnel_set **result, xen_pif pif);


/**
 * Get the tunnel_transport_PIF_of field of the given PIF.
 */
extern bool
xen_pif_get_tunnel_transport_pif_of(xen_session *session, struct xen_tunnel_set **result, xen_pif pif);


/**
 * Get the ipv6_configuration_mode field of the given PIF.
 */
extern bool
xen_pif_get_ipv6_configuration_mode(xen_session *session, enum xen_ipv6_configuration_mode *result, xen_pif pif);


/**
 * Get the IPv6 field of the given PIF.
 */
extern bool
xen_pif_get_ipv6(xen_session *session, struct xen_string_set **result, xen_pif pif);


/**
 * Get the ipv6_gateway field of the given PIF.
 */
extern bool
xen_pif_get_ipv6_gateway(xen_session *session, char **result, xen_pif pif);


/**
 * Get the primary_address_type field of the given PIF.
 */
extern bool
xen_pif_get_primary_address_type(xen_session *session, enum xen_primary_address_type *result, xen_pif pif);


/**
 * Set the other_config field of the given PIF.
 */
extern bool
xen_pif_set_other_config(xen_session *session, xen_pif pif, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * PIF.
 */
extern bool
xen_pif_add_to_other_config(xen_session *session, xen_pif pif, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given PIF.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_pif_remove_from_other_config(xen_session *session, xen_pif pif, char *key);


/**
 * Set the disallow_unplug field of the given PIF.
 */
extern bool
xen_pif_set_disallow_unplug(xen_session *session, xen_pif pif, bool disallow_unplug);


/**
 * Create a VLAN interface from an existing physical interface. This
 * call is deprecated: use VLAN.create instead.
 */
extern bool
xen_pif_create_vlan(xen_session *session, xen_pif *result, char *device, xen_network network, xen_host host, int64_t vlan);

/**
 * Create a VLAN interface from an existing physical interface. This
 * call is deprecated: use VLAN.create instead.
 */
extern bool
xen_pif_create_vlan_async(xen_session *session, xen_task *result, char *device, xen_network network, xen_host host, int64_t vlan);


/**
 * Destroy the PIF object (provided it is a VLAN interface). This call
 * is deprecated: use VLAN.destroy or Bond.destroy instead.
 */
extern bool
xen_pif_destroy(xen_session *session, xen_pif self);

/**
 * Destroy the PIF object (provided it is a VLAN interface). This call
 * is deprecated: use VLAN.destroy or Bond.destroy instead.
 */
extern bool
xen_pif_destroy_async(xen_session *session, xen_task *result, xen_pif self);


/**
 * Reconfigure the IP address settings for this interface.
 */
extern bool
xen_pif_reconfigure_ip(xen_session *session, xen_pif self, enum xen_ip_configuration_mode mode, char *ip, char *netmask, char *gateway, char *dns);

/**
 * Reconfigure the IP address settings for this interface.
 */
extern bool
xen_pif_reconfigure_ip_async(xen_session *session, xen_task *result, xen_pif self, enum xen_ip_configuration_mode mode, char *ip, char *netmask, char *gateway, char *dns);


/**
 * Reconfigure the IPv6 address settings for this interface.
 */
extern bool
xen_pif_reconfigure_ipv6(xen_session *session, xen_pif self, enum xen_ipv6_configuration_mode mode, char *ipv6, char *gateway, char *dns);

/**
 * Reconfigure the IPv6 address settings for this interface.
 */
extern bool
xen_pif_reconfigure_ipv6_async(xen_session *session, xen_task *result, xen_pif self, enum xen_ipv6_configuration_mode mode, char *ipv6, char *gateway, char *dns);


/**
 * Change the primary address type used by this PIF.
 */
extern bool
xen_pif_set_primary_address_type(xen_session *session, xen_pif self, enum xen_primary_address_type primary_address_type);

/**
 * Change the primary address type used by this PIF.
 */
extern bool
xen_pif_set_primary_address_type_async(xen_session *session, xen_task *result, xen_pif self, enum xen_primary_address_type primary_address_type);


/**
 * Scan for physical interfaces on a host and create PIF objects to
 * represent them.
 */
extern bool
xen_pif_scan(xen_session *session, xen_host host);

/**
 * Scan for physical interfaces on a host and create PIF objects to
 * represent them.
 */
extern bool
xen_pif_scan_async(xen_session *session, xen_task *result, xen_host host);


/**
 * Create a PIF object matching a particular network interface.
 */
extern bool
xen_pif_introduce(xen_session *session, xen_pif *result, xen_host host, char *mac, char *device);

/**
 * Create a PIF object matching a particular network interface.
 */
extern bool
xen_pif_introduce_async(xen_session *session, xen_task *result, xen_host host, char *mac, char *device);


/**
 * Destroy the PIF object matching a particular network interface.
 */
extern bool
xen_pif_forget(xen_session *session, xen_pif self);

/**
 * Destroy the PIF object matching a particular network interface.
 */
extern bool
xen_pif_forget_async(xen_session *session, xen_task *result, xen_pif self);


/**
 * Attempt to bring down a physical interface.
 */
extern bool
xen_pif_unplug(xen_session *session, xen_pif self);

/**
 * Attempt to bring down a physical interface.
 */
extern bool
xen_pif_unplug_async(xen_session *session, xen_task *result, xen_pif self);


/**
 * Attempt to bring up a physical interface.
 */
extern bool
xen_pif_plug(xen_session *session, xen_pif self);

/**
 * Attempt to bring up a physical interface.
 */
extern bool
xen_pif_plug_async(xen_session *session, xen_task *result, xen_pif self);


/**
 * Create a new PIF record in the database only.
 */
extern bool
xen_pif_db_introduce(xen_session *session, xen_pif *result, char *device, xen_network network, xen_host host, char *mac, int64_t mtu, int64_t vlan, bool physical, enum xen_ip_configuration_mode ip_configuration_mode, char *ip, char *netmask, char *gateway, char *dns, xen_bond bond_slave_of, xen_vlan vlan_master_of, bool management, xen_string_string_map *other_config, bool disallow_unplug, enum xen_ipv6_configuration_mode ipv6_configuration_mode, struct xen_string_set *ipv6, char *ipv6_gateway, enum xen_primary_address_type primary_address_type);

/**
 * Create a new PIF record in the database only.
 */
extern bool
xen_pif_db_introduce_async(xen_session *session, xen_task *result, char *device, xen_network network, xen_host host, char *mac, int64_t mtu, int64_t vlan, bool physical, enum xen_ip_configuration_mode ip_configuration_mode, char *ip, char *netmask, char *gateway, char *dns, xen_bond bond_slave_of, xen_vlan vlan_master_of, bool management, xen_string_string_map *other_config, bool disallow_unplug, enum xen_ipv6_configuration_mode ipv6_configuration_mode, struct xen_string_set *ipv6, char *ipv6_gateway, enum xen_primary_address_type primary_address_type);


/**
 * Destroy a PIF database record.
 */
extern bool
xen_pif_db_forget(xen_session *session, xen_pif self);

/**
 * Destroy a PIF database record.
 */
extern bool
xen_pif_db_forget_async(xen_session *session, xen_task *result, xen_pif self);


/**
 * Return a list of all the PIFs known to the system.
 */
extern bool
xen_pif_get_all(xen_session *session, struct xen_pif_set **result);


/**
 * Return a map of PIF references to PIF records for all PIFs known to
 * the system.
 */
extern bool
xen_pif_get_all_records(xen_session *session, xen_pif_xen_pif_record_map **result);


#endif
