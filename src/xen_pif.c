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
#include "xen_ip_configuration_mode_internal.h"
#include "xen_ipv6_configuration_mode_internal.h"
#include "xen_primary_address_type_internal.h"
#include <xen/api/xen_bond.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_host.h>
#include <xen/api/xen_network.h>
#include <xen/api/xen_pif.h>
#include <xen/api/xen_pif_metrics.h>
#include <xen/api/xen_pif_xen_pif_record_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_tunnel.h>
#include <xen/api/xen_vlan.h>


XEN_FREE(xen_pif)
XEN_SET_ALLOC_FREE(xen_pif)
XEN_ALLOC(xen_pif_record)
XEN_SET_ALLOC_FREE(xen_pif_record)
XEN_ALLOC(xen_pif_record_opt)
XEN_RECORD_OPT_FREE(xen_pif)
XEN_SET_ALLOC_FREE(xen_pif_record_opt)


static const struct_member xen_pif_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, uuid) },
        { .key = "device",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, device) },
        { .key = "network",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pif_record, network) },
        { .key = "host",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pif_record, host) },
        { .key = "MAC",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, mac) },
        { .key = "MTU",
          .type = &abstract_type_int,
          .offset = offsetof(xen_pif_record, mtu) },
        { .key = "VLAN",
          .type = &abstract_type_int,
          .offset = offsetof(xen_pif_record, vlan) },
        { .key = "metrics",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pif_record, metrics) },
        { .key = "physical",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_pif_record, physical) },
        { .key = "currently_attached",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_pif_record, currently_attached) },
        { .key = "ip_configuration_mode",
          .type = &xen_ip_configuration_mode_abstract_type_,
          .offset = offsetof(xen_pif_record, ip_configuration_mode) },
        { .key = "IP",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, ip) },
        { .key = "netmask",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, netmask) },
        { .key = "gateway",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, gateway) },
        { .key = "DNS",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, dns) },
        { .key = "bond_slave_of",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pif_record, bond_slave_of) },
        { .key = "bond_master_of",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_pif_record, bond_master_of) },
        { .key = "VLAN_master_of",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pif_record, vlan_master_of) },
        { .key = "VLAN_slave_of",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_pif_record, vlan_slave_of) },
        { .key = "management",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_pif_record, management) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_pif_record, other_config) },
        { .key = "disallow_unplug",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_pif_record, disallow_unplug) },
        { .key = "tunnel_access_PIF_of",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_pif_record, tunnel_access_pif_of) },
        { .key = "tunnel_transport_PIF_of",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_pif_record, tunnel_transport_pif_of) },
        { .key = "ipv6_configuration_mode",
          .type = &xen_ipv6_configuration_mode_abstract_type_,
          .offset = offsetof(xen_pif_record, ipv6_configuration_mode) },
        { .key = "IPv6",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_pif_record, ipv6) },
        { .key = "ipv6_gateway",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pif_record, ipv6_gateway) },
        { .key = "primary_address_type",
          .type = &xen_primary_address_type_abstract_type_,
          .offset = offsetof(xen_pif_record, primary_address_type) }
    };

const abstract_type xen_pif_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_pif_record),
       .member_count =
           sizeof(xen_pif_record_struct_members) / sizeof(struct_member),
       .members = xen_pif_record_struct_members
    };


static const struct struct_member xen_pif_xen_pif_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_pif_xen_pif_record_map_contents, key)
    },
    {
        .type = &xen_pif_record_abstract_type_,
        .offset = offsetof(xen_pif_xen_pif_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_pif_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_pif_xen_pif_record_map_contents),
    .members = xen_pif_xen_pif_record_members
};


void
xen_pif_record_free(xen_pif_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->device);
    xen_network_record_opt_free(record->network);
    xen_host_record_opt_free(record->host);
    free(record->mac);
    xen_pif_metrics_record_opt_free(record->metrics);
    free(record->ip);
    free(record->netmask);
    free(record->gateway);
    free(record->dns);
    xen_bond_record_opt_free(record->bond_slave_of);
    xen_bond_record_opt_set_free(record->bond_master_of);
    xen_vlan_record_opt_free(record->vlan_master_of);
    xen_vlan_record_opt_set_free(record->vlan_slave_of);
    xen_string_string_map_free(record->other_config);
    xen_tunnel_record_opt_set_free(record->tunnel_access_pif_of);
    xen_tunnel_record_opt_set_free(record->tunnel_transport_pif_of);
    xen_string_set_free(record->ipv6);
    free(record->ipv6_gateway);
    free(record);
}


bool
xen_pif_get_record(xen_session *session, xen_pif_record **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = xen_pif_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("PIF.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_pif_get_by_uuid(xen_session *session, xen_pif *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_by_uuid");
    return session->ok;
}


bool
xen_pif_get_device(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_device");
    return session->ok;
}


bool
xen_pif_get_network(xen_session *session, xen_network *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_network");
    return session->ok;
}


bool
xen_pif_get_host(xen_session *session, xen_host *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_host");
    return session->ok;
}


bool
xen_pif_get_mac(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_MAC");
    return session->ok;
}


bool
xen_pif_get_mtu(xen_session *session, int64_t *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("PIF.get_MTU");
    return session->ok;
}


bool
xen_pif_get_vlan(xen_session *session, int64_t *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("PIF.get_VLAN");
    return session->ok;
}


bool
xen_pif_get_metrics(xen_session *session, xen_pif_metrics *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_metrics");
    return session->ok;
}


bool
xen_pif_get_physical(xen_session *session, bool *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("PIF.get_physical");
    return session->ok;
}


bool
xen_pif_get_currently_attached(xen_session *session, bool *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("PIF.get_currently_attached");
    return session->ok;
}


bool
xen_pif_get_ip_configuration_mode(xen_session *session, enum xen_ip_configuration_mode *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = xen_ip_configuration_mode_abstract_type_;
    XEN_CALL_("PIF.get_ip_configuration_mode");
    return session->ok;
}


bool
xen_pif_get_ip(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_IP");
    return session->ok;
}


bool
xen_pif_get_netmask(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_netmask");
    return session->ok;
}


bool
xen_pif_get_gateway(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_gateway");
    return session->ok;
}


bool
xen_pif_get_dns(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_DNS");
    return session->ok;
}


bool
xen_pif_get_bond_slave_of(xen_session *session, xen_bond *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_bond_slave_of");
    return session->ok;
}


bool
xen_pif_get_bond_master_of(xen_session *session, struct xen_bond_set **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("PIF.get_bond_master_of");
    return session->ok;
}


bool
xen_pif_get_vlan_master_of(xen_session *session, xen_vlan *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_VLAN_master_of");
    return session->ok;
}


bool
xen_pif_get_vlan_slave_of(xen_session *session, struct xen_vlan_set **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("PIF.get_VLAN_slave_of");
    return session->ok;
}


bool
xen_pif_get_management(xen_session *session, bool *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("PIF.get_management");
    return session->ok;
}


bool
xen_pif_get_other_config(xen_session *session, xen_string_string_map **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("PIF.get_other_config");
    return session->ok;
}


bool
xen_pif_get_disallow_unplug(xen_session *session, bool *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("PIF.get_disallow_unplug");
    return session->ok;
}


bool
xen_pif_get_tunnel_access_pif_of(xen_session *session, struct xen_tunnel_set **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("PIF.get_tunnel_access_PIF_of");
    return session->ok;
}


bool
xen_pif_get_tunnel_transport_pif_of(xen_session *session, struct xen_tunnel_set **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("PIF.get_tunnel_transport_PIF_of");
    return session->ok;
}


bool
xen_pif_get_ipv6_configuration_mode(xen_session *session, enum xen_ipv6_configuration_mode *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = xen_ipv6_configuration_mode_abstract_type_;
    XEN_CALL_("PIF.get_ipv6_configuration_mode");
    return session->ok;
}


bool
xen_pif_get_ipv6(xen_session *session, struct xen_string_set **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("PIF.get_IPv6");
    return session->ok;
}


bool
xen_pif_get_ipv6_gateway(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_ipv6_gateway");
    return session->ok;
}


bool
xen_pif_get_primary_address_type(xen_session *session, enum xen_primary_address_type *result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = xen_primary_address_type_abstract_type_;
    XEN_CALL_("PIF.get_primary_address_type");
    return session->ok;
}


bool
xen_pif_set_other_config(xen_session *session, xen_pif pif, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "PIF.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pif_add_to_other_config(xen_session *session, xen_pif pif, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "PIF.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_pif_remove_from_other_config(xen_session *session, xen_pif pif, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "PIF.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pif_set_disallow_unplug(xen_session *session, xen_pif pif, bool disallow_unplug)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif },
            { .type = &abstract_type_bool,
              .u.bool_val = disallow_unplug }
        };

    xen_call_(session, "PIF.set_disallow_unplug", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pif_create_vlan(xen_session *session, xen_pif *result, char *device, xen_network network, xen_host host, int64_t vlan)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = device },
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_int,
              .u.int_val = vlan }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.create_VLAN");
    return session->ok;
}

bool
xen_pif_create_vlan_async(xen_session *session, xen_task *result, char *device, xen_network network, xen_host host, int64_t vlan)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = device },
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_int,
              .u.int_val = vlan }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.create_VLAN");
    return session->ok;
}

bool
xen_pif_destroy(xen_session *session, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "PIF.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pif_destroy_async(xen_session *session, xen_task *result, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.destroy");
    return session->ok;
}

bool
xen_pif_reconfigure_ip(xen_session *session, xen_pif self, enum xen_ip_configuration_mode mode, char *ip, char *netmask, char *gateway, char *dns)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_ip_configuration_mode_abstract_type_,
              .u.enum_val = mode },
            { .type = &abstract_type_string,
              .u.string_val = ip },
            { .type = &abstract_type_string,
              .u.string_val = netmask },
            { .type = &abstract_type_string,
              .u.string_val = gateway },
            { .type = &abstract_type_string,
              .u.string_val = dns }
        };

    xen_call_(session, "PIF.reconfigure_ip", param_values, 6, NULL, NULL);
    return session->ok;
}

bool
xen_pif_reconfigure_ip_async(xen_session *session, xen_task *result, xen_pif self, enum xen_ip_configuration_mode mode, char *ip, char *netmask, char *gateway, char *dns)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_ip_configuration_mode_abstract_type_,
              .u.enum_val = mode },
            { .type = &abstract_type_string,
              .u.string_val = ip },
            { .type = &abstract_type_string,
              .u.string_val = netmask },
            { .type = &abstract_type_string,
              .u.string_val = gateway },
            { .type = &abstract_type_string,
              .u.string_val = dns }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.reconfigure_ip");
    return session->ok;
}

bool
xen_pif_reconfigure_ipv6(xen_session *session, xen_pif self, enum xen_ipv6_configuration_mode mode, char *ipv6, char *gateway, char *dns)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_ipv6_configuration_mode_abstract_type_,
              .u.enum_val = mode },
            { .type = &abstract_type_string,
              .u.string_val = ipv6 },
            { .type = &abstract_type_string,
              .u.string_val = gateway },
            { .type = &abstract_type_string,
              .u.string_val = dns }
        };

    xen_call_(session, "PIF.reconfigure_ipv6", param_values, 5, NULL, NULL);
    return session->ok;
}

bool
xen_pif_reconfigure_ipv6_async(xen_session *session, xen_task *result, xen_pif self, enum xen_ipv6_configuration_mode mode, char *ipv6, char *gateway, char *dns)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_ipv6_configuration_mode_abstract_type_,
              .u.enum_val = mode },
            { .type = &abstract_type_string,
              .u.string_val = ipv6 },
            { .type = &abstract_type_string,
              .u.string_val = gateway },
            { .type = &abstract_type_string,
              .u.string_val = dns }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.reconfigure_ipv6");
    return session->ok;
}

bool
xen_pif_set_primary_address_type(xen_session *session, xen_pif self, enum xen_primary_address_type primary_address_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_primary_address_type_abstract_type_,
              .u.enum_val = primary_address_type }
        };

    xen_call_(session, "PIF.set_primary_address_type", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_pif_set_primary_address_type_async(xen_session *session, xen_task *result, xen_pif self, enum xen_primary_address_type primary_address_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_primary_address_type_abstract_type_,
              .u.enum_val = primary_address_type }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.set_primary_address_type");
    return session->ok;
}

bool
xen_pif_scan(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "PIF.scan", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pif_scan_async(xen_session *session, xen_task *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.scan");
    return session->ok;
}

bool
xen_pif_introduce(xen_session *session, xen_pif *result, xen_host host, char *mac, char *device)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = mac },
            { .type = &abstract_type_string,
              .u.string_val = device }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.introduce");
    return session->ok;
}

bool
xen_pif_introduce_async(xen_session *session, xen_task *result, xen_host host, char *mac, char *device)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = mac },
            { .type = &abstract_type_string,
              .u.string_val = device }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.introduce");
    return session->ok;
}

bool
xen_pif_forget(xen_session *session, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "PIF.forget", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pif_forget_async(xen_session *session, xen_task *result, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.forget");
    return session->ok;
}

bool
xen_pif_unplug(xen_session *session, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "PIF.unplug", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pif_unplug_async(xen_session *session, xen_task *result, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.unplug");
    return session->ok;
}

bool
xen_pif_plug(xen_session *session, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "PIF.plug", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pif_plug_async(xen_session *session, xen_task *result, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.plug");
    return session->ok;
}

bool
xen_pif_db_introduce(xen_session *session, xen_pif *result, char *device, xen_network network, xen_host host, char *mac, int64_t mtu, int64_t vlan, bool physical, enum xen_ip_configuration_mode ip_configuration_mode, char *ip, char *netmask, char *gateway, char *dns, xen_bond bond_slave_of, xen_vlan vlan_master_of, bool management, xen_string_string_map *other_config, bool disallow_unplug, enum xen_ipv6_configuration_mode ipv6_configuration_mode, struct xen_string_set *ipv6, char *ipv6_gateway, enum xen_primary_address_type primary_address_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = device },
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = mac },
            { .type = &abstract_type_int,
              .u.int_val = mtu },
            { .type = &abstract_type_int,
              .u.int_val = vlan },
            { .type = &abstract_type_bool,
              .u.bool_val = physical },
            { .type = &xen_ip_configuration_mode_abstract_type_,
              .u.enum_val = ip_configuration_mode },
            { .type = &abstract_type_string,
              .u.string_val = ip },
            { .type = &abstract_type_string,
              .u.string_val = netmask },
            { .type = &abstract_type_string,
              .u.string_val = gateway },
            { .type = &abstract_type_string,
              .u.string_val = dns },
            { .type = &abstract_type_string,
              .u.string_val = bond_slave_of },
            { .type = &abstract_type_string,
              .u.string_val = vlan_master_of },
            { .type = &abstract_type_bool,
              .u.bool_val = management },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config },
            { .type = &abstract_type_bool,
              .u.bool_val = disallow_unplug },
            { .type = &xen_ipv6_configuration_mode_abstract_type_,
              .u.enum_val = ipv6_configuration_mode },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)ipv6 },
            { .type = &abstract_type_string,
              .u.string_val = ipv6_gateway },
            { .type = &xen_primary_address_type_abstract_type_,
              .u.enum_val = primary_address_type }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.db_introduce");
    return session->ok;
}

bool
xen_pif_db_introduce_async(xen_session *session, xen_task *result, char *device, xen_network network, xen_host host, char *mac, int64_t mtu, int64_t vlan, bool physical, enum xen_ip_configuration_mode ip_configuration_mode, char *ip, char *netmask, char *gateway, char *dns, xen_bond bond_slave_of, xen_vlan vlan_master_of, bool management, xen_string_string_map *other_config, bool disallow_unplug, enum xen_ipv6_configuration_mode ipv6_configuration_mode, struct xen_string_set *ipv6, char *ipv6_gateway, enum xen_primary_address_type primary_address_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = device },
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string,
              .u.string_val = mac },
            { .type = &abstract_type_int,
              .u.int_val = mtu },
            { .type = &abstract_type_int,
              .u.int_val = vlan },
            { .type = &abstract_type_bool,
              .u.bool_val = physical },
            { .type = &xen_ip_configuration_mode_abstract_type_,
              .u.enum_val = ip_configuration_mode },
            { .type = &abstract_type_string,
              .u.string_val = ip },
            { .type = &abstract_type_string,
              .u.string_val = netmask },
            { .type = &abstract_type_string,
              .u.string_val = gateway },
            { .type = &abstract_type_string,
              .u.string_val = dns },
            { .type = &abstract_type_string,
              .u.string_val = bond_slave_of },
            { .type = &abstract_type_string,
              .u.string_val = vlan_master_of },
            { .type = &abstract_type_bool,
              .u.bool_val = management },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config },
            { .type = &abstract_type_bool,
              .u.bool_val = disallow_unplug },
            { .type = &xen_ipv6_configuration_mode_abstract_type_,
              .u.enum_val = ipv6_configuration_mode },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)ipv6 },
            { .type = &abstract_type_string,
              .u.string_val = ipv6_gateway },
            { .type = &xen_primary_address_type_abstract_type_,
              .u.enum_val = primary_address_type }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.db_introduce");
    return session->ok;
}

bool
xen_pif_db_forget(xen_session *session, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "PIF.db_forget", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pif_db_forget_async(xen_session *session, xen_task *result, xen_pif self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PIF.db_forget");
    return session->ok;
}

bool
xen_pif_get_all(xen_session *session, struct xen_pif_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "PIF.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pif_get_all_records(xen_session *session, xen_pif_xen_pif_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_pif_record_map;

    *result = NULL;
    xen_call_(session, "PIF.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pif_get_uuid(xen_session *session, char **result, xen_pif pif)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pif }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PIF.get_uuid");
    return session->ok;
}

