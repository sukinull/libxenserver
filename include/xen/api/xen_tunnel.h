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


#ifndef XEN_TUNNEL_H
#define XEN_TUNNEL_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_network_decl.h>
#include <xen/api/xen_pif_decl.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_tunnel_decl.h>
#include <xen/api/xen_tunnel_xen_tunnel_record_map.h>


/*
 * The tunnel class.
 * 
 * A tunnel for network traffic.
 */


/**
 * Free the given xen_tunnel.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_tunnel_free(xen_tunnel tunnel);


typedef struct xen_tunnel_set
{
    size_t size;
    xen_tunnel *contents[];
} xen_tunnel_set;

/**
 * Allocate a xen_tunnel_set of the given size.
 */
extern xen_tunnel_set *
xen_tunnel_set_alloc(size_t size);

/**
 * Free the given xen_tunnel_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_tunnel_set_free(xen_tunnel_set *set);


typedef struct xen_tunnel_record
{
    xen_tunnel handle;
    char *uuid;
    struct xen_pif_record_opt *access_pif;
    struct xen_pif_record_opt *transport_pif;
    xen_string_string_map *status;
    xen_string_string_map *other_config;
} xen_tunnel_record;

/**
 * Allocate a xen_tunnel_record.
 */
extern xen_tunnel_record *
xen_tunnel_record_alloc(void);

/**
 * Free the given xen_tunnel_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_tunnel_record_free(xen_tunnel_record *record);


typedef struct xen_tunnel_record_opt
{
    bool is_record;
    union
    {
        xen_tunnel handle;
        xen_tunnel_record *record;
    } u;
} xen_tunnel_record_opt;

/**
 * Allocate a xen_tunnel_record_opt.
 */
extern xen_tunnel_record_opt *
xen_tunnel_record_opt_alloc(void);

/**
 * Free the given xen_tunnel_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_tunnel_record_opt_free(xen_tunnel_record_opt *record_opt);


typedef struct xen_tunnel_record_set
{
    size_t size;
    xen_tunnel_record *contents[];
} xen_tunnel_record_set;

/**
 * Allocate a xen_tunnel_record_set of the given size.
 */
extern xen_tunnel_record_set *
xen_tunnel_record_set_alloc(size_t size);

/**
 * Free the given xen_tunnel_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_tunnel_record_set_free(xen_tunnel_record_set *set);



typedef struct xen_tunnel_record_opt_set
{
    size_t size;
    xen_tunnel_record_opt *contents[];
} xen_tunnel_record_opt_set;

/**
 * Allocate a xen_tunnel_record_opt_set of the given size.
 */
extern xen_tunnel_record_opt_set *
xen_tunnel_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_tunnel_record_opt_set, and all referenced values.
 *  The given set must have been allocated by this library.
 */
extern void
xen_tunnel_record_opt_set_free(xen_tunnel_record_opt_set *set);


/**
 * Get a record containing the current state of the given tunnel.
 */
extern bool
xen_tunnel_get_record(xen_session *session, xen_tunnel_record **result, xen_tunnel tunnel);


/**
 * Get a reference to the tunnel instance with the specified UUID.
 */
extern bool
xen_tunnel_get_by_uuid(xen_session *session, xen_tunnel *result, char *uuid);


/**
 * Get the uuid field of the given tunnel.
 */
extern bool
xen_tunnel_get_uuid(xen_session *session, char **result, xen_tunnel tunnel);


/**
 * Get the access_PIF field of the given tunnel.
 */
extern bool
xen_tunnel_get_access_pif(xen_session *session, xen_pif *result, xen_tunnel tunnel);


/**
 * Get the transport_PIF field of the given tunnel.
 */
extern bool
xen_tunnel_get_transport_pif(xen_session *session, xen_pif *result, xen_tunnel tunnel);


/**
 * Get the status field of the given tunnel.
 */
extern bool
xen_tunnel_get_status(xen_session *session, xen_string_string_map **result, xen_tunnel tunnel);


/**
 * Get the other_config field of the given tunnel.
 */
extern bool
xen_tunnel_get_other_config(xen_session *session, xen_string_string_map **result, xen_tunnel tunnel);


/**
 * Set the status field of the given tunnel.
 */
extern bool
xen_tunnel_set_status(xen_session *session, xen_tunnel tunnel, xen_string_string_map *status);


/**
 * Add the given key-value pair to the status field of the given
 * tunnel.
 */
extern bool
xen_tunnel_add_to_status(xen_session *session, xen_tunnel tunnel, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the status
 * field of the given tunnel.  If the key is not in that Map, then do nothing.
 */
extern bool
xen_tunnel_remove_from_status(xen_session *session, xen_tunnel tunnel, char *key);


/**
 * Set the other_config field of the given tunnel.
 */
extern bool
xen_tunnel_set_other_config(xen_session *session, xen_tunnel tunnel, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * tunnel.
 */
extern bool
xen_tunnel_add_to_other_config(xen_session *session, xen_tunnel tunnel, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given tunnel.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_tunnel_remove_from_other_config(xen_session *session, xen_tunnel tunnel, char *key);


/**
 * Create a tunnel.
 */
extern bool
xen_tunnel_create(xen_session *session, xen_tunnel *result, xen_pif transport_pif, xen_network network);

/**
 * Create a tunnel.
 */
extern bool
xen_tunnel_create_async(xen_session *session, xen_task *result, xen_pif transport_pif, xen_network network);


/**
 * Destroy a tunnel.
 */
extern bool
xen_tunnel_destroy(xen_session *session, xen_tunnel self);

/**
 * Destroy a tunnel.
 */
extern bool
xen_tunnel_destroy_async(xen_session *session, xen_task *result, xen_tunnel self);


/**
 * Return a list of all the tunnels known to the system.
 */
extern bool
xen_tunnel_get_all(xen_session *session, struct xen_tunnel_set **result);


/**
 * Return a map of tunnel references to tunnel records for all tunnels
 * known to the system.
 */
extern bool
xen_tunnel_get_all_records(xen_session *session, xen_tunnel_xen_tunnel_record_map **result);


#endif
