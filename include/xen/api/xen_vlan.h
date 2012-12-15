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


#ifndef XEN_VLAN_H
#define XEN_VLAN_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_network_decl.h>
#include <xen/api/xen_pif_decl.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vlan_decl.h>
#include <xen/api/xen_vlan_xen_vlan_record_map.h>


/*
 * The VLAN class.
 * 
 * A VLAN mux/demux.
 */


/**
 * Free the given xen_vlan.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_vlan_free(xen_vlan vlan);


typedef struct xen_vlan_set
{
    size_t size;
    xen_vlan *contents[];
} xen_vlan_set;

/**
 * Allocate a xen_vlan_set of the given size.
 */
extern xen_vlan_set *
xen_vlan_set_alloc(size_t size);

/**
 * Free the given xen_vlan_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_vlan_set_free(xen_vlan_set *set);


typedef struct xen_vlan_record
{
    xen_vlan handle;
    char *uuid;
    struct xen_pif_record_opt *tagged_pif;
    struct xen_pif_record_opt *untagged_pif;
    int64_t tag;
    xen_string_string_map *other_config;
} xen_vlan_record;

/**
 * Allocate a xen_vlan_record.
 */
extern xen_vlan_record *
xen_vlan_record_alloc(void);

/**
 * Free the given xen_vlan_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_vlan_record_free(xen_vlan_record *record);


typedef struct xen_vlan_record_opt
{
    bool is_record;
    union
    {
        xen_vlan handle;
        xen_vlan_record *record;
    } u;
} xen_vlan_record_opt;

/**
 * Allocate a xen_vlan_record_opt.
 */
extern xen_vlan_record_opt *
xen_vlan_record_opt_alloc(void);

/**
 * Free the given xen_vlan_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_vlan_record_opt_free(xen_vlan_record_opt *record_opt);


typedef struct xen_vlan_record_set
{
    size_t size;
    xen_vlan_record *contents[];
} xen_vlan_record_set;

/**
 * Allocate a xen_vlan_record_set of the given size.
 */
extern xen_vlan_record_set *
xen_vlan_record_set_alloc(size_t size);

/**
 * Free the given xen_vlan_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_vlan_record_set_free(xen_vlan_record_set *set);



typedef struct xen_vlan_record_opt_set
{
    size_t size;
    xen_vlan_record_opt *contents[];
} xen_vlan_record_opt_set;

/**
 * Allocate a xen_vlan_record_opt_set of the given size.
 */
extern xen_vlan_record_opt_set *
xen_vlan_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vlan_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_vlan_record_opt_set_free(xen_vlan_record_opt_set *set);


/**
 * Get a record containing the current state of the given VLAN.
 */
extern bool
xen_vlan_get_record(xen_session *session, xen_vlan_record **result, xen_vlan vlan);


/**
 * Get a reference to the VLAN instance with the specified UUID.
 */
extern bool
xen_vlan_get_by_uuid(xen_session *session, xen_vlan *result, char *uuid);


/**
 * Get the uuid field of the given VLAN.
 */
extern bool
xen_vlan_get_uuid(xen_session *session, char **result, xen_vlan vlan);


/**
 * Get the tagged_PIF field of the given VLAN.
 */
extern bool
xen_vlan_get_tagged_pif(xen_session *session, xen_pif *result, xen_vlan vlan);


/**
 * Get the untagged_PIF field of the given VLAN.
 */
extern bool
xen_vlan_get_untagged_pif(xen_session *session, xen_pif *result, xen_vlan vlan);


/**
 * Get the tag field of the given VLAN.
 */
extern bool
xen_vlan_get_tag(xen_session *session, int64_t *result, xen_vlan vlan);


/**
 * Get the other_config field of the given VLAN.
 */
extern bool
xen_vlan_get_other_config(xen_session *session, xen_string_string_map **result, xen_vlan vlan);


/**
 * Set the other_config field of the given VLAN.
 */
extern bool
xen_vlan_set_other_config(xen_session *session, xen_vlan vlan, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * VLAN.
 */
extern bool
xen_vlan_add_to_other_config(xen_session *session, xen_vlan vlan, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given VLAN.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_vlan_remove_from_other_config(xen_session *session, xen_vlan vlan, char *key);


/**
 * Create a VLAN mux/demuxer.
 */
extern bool
xen_vlan_create(xen_session *session, xen_vlan *result, xen_pif tagged_pif, int64_t tag, xen_network network);

/**
 * Create a VLAN mux/demuxer.
 */
extern bool
xen_vlan_create_async(xen_session *session, xen_task *result, xen_pif tagged_pif, int64_t tag, xen_network network);


/**
 * Destroy a VLAN mux/demuxer.
 */
extern bool
xen_vlan_destroy(xen_session *session, xen_vlan self);

/**
 * Destroy a VLAN mux/demuxer.
 */
extern bool
xen_vlan_destroy_async(xen_session *session, xen_task *result, xen_vlan self);


/**
 * Return a list of all the VLANs known to the system.
 */
extern bool
xen_vlan_get_all(xen_session *session, struct xen_vlan_set **result);


/**
 * Return a map of VLAN references to VLAN records for all VLANs known
 * to the system.
 */
extern bool
xen_vlan_get_all_records(xen_session *session, xen_vlan_xen_vlan_record_map **result);


#endif
