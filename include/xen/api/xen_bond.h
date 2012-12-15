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


#ifndef XEN_BOND_H
#define XEN_BOND_H

#include <xen/api/xen_bond_decl.h>
#include <xen/api/xen_bond_mode.h>
#include <xen/api/xen_bond_xen_bond_record_map.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_network_decl.h>
#include <xen/api/xen_pif_decl.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The Bond class.
 * 
 * .
 */


/**
 * Free the given xen_bond.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_bond_free(xen_bond bond);


typedef struct xen_bond_set
{
    size_t size;
    xen_bond *contents[];
} xen_bond_set;

/**
 * Allocate a xen_bond_set of the given size.
 */
extern xen_bond_set *
xen_bond_set_alloc(size_t size);

/**
 * Free the given xen_bond_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_bond_set_free(xen_bond_set *set);


typedef struct xen_bond_record
{
    xen_bond handle;
    char *uuid;
    struct xen_pif_record_opt *master;
    struct xen_pif_record_opt_set *slaves;
    xen_string_string_map *other_config;
    struct xen_pif_record_opt *primary_slave;
    enum xen_bond_mode mode;
    xen_string_string_map *properties;
    int64_t links_up;
} xen_bond_record;

/**
 * Allocate a xen_bond_record.
 */
extern xen_bond_record *
xen_bond_record_alloc(void);

/**
 * Free the given xen_bond_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_bond_record_free(xen_bond_record *record);


typedef struct xen_bond_record_opt
{
    bool is_record;
    union
    {
        xen_bond handle;
        xen_bond_record *record;
    } u;
} xen_bond_record_opt;

/**
 * Allocate a xen_bond_record_opt.
 */
extern xen_bond_record_opt *
xen_bond_record_opt_alloc(void);

/**
 * Free the given xen_bond_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_bond_record_opt_free(xen_bond_record_opt *record_opt);


typedef struct xen_bond_record_set
{
    size_t size;
    xen_bond_record *contents[];
} xen_bond_record_set;

/**
 * Allocate a xen_bond_record_set of the given size.
 */
extern xen_bond_record_set *
xen_bond_record_set_alloc(size_t size);

/**
 * Free the given xen_bond_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_bond_record_set_free(xen_bond_record_set *set);



typedef struct xen_bond_record_opt_set
{
    size_t size;
    xen_bond_record_opt *contents[];
} xen_bond_record_opt_set;

/**
 * Allocate a xen_bond_record_opt_set of the given size.
 */
extern xen_bond_record_opt_set *
xen_bond_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_bond_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_bond_record_opt_set_free(xen_bond_record_opt_set *set);


/**
 * Get a record containing the current state of the given Bond.
 */
extern bool
xen_bond_get_record(xen_session *session, xen_bond_record **result, xen_bond bond);


/**
 * Get a reference to the Bond instance with the specified UUID.
 */
extern bool
xen_bond_get_by_uuid(xen_session *session, xen_bond *result, char *uuid);


/**
 * Get the uuid field of the given Bond.
 */
extern bool
xen_bond_get_uuid(xen_session *session, char **result, xen_bond bond);


/**
 * Get the master field of the given Bond.
 */
extern bool
xen_bond_get_master(xen_session *session, xen_pif *result, xen_bond bond);


/**
 * Get the slaves field of the given Bond.
 */
extern bool
xen_bond_get_slaves(xen_session *session, struct xen_pif_set **result, xen_bond bond);


/**
 * Get the other_config field of the given Bond.
 */
extern bool
xen_bond_get_other_config(xen_session *session, xen_string_string_map **result, xen_bond bond);


/**
 * Get the primary_slave field of the given Bond.
 */
extern bool
xen_bond_get_primary_slave(xen_session *session, xen_pif *result, xen_bond bond);


/**
 * Get the mode field of the given Bond.
 */
extern bool
xen_bond_get_mode(xen_session *session, enum xen_bond_mode *result, xen_bond bond);


/**
 * Get the properties field of the given Bond.
 */
extern bool
xen_bond_get_properties(xen_session *session, xen_string_string_map **result, xen_bond bond);


/**
 * Get the links_up field of the given Bond.
 */
extern bool
xen_bond_get_links_up(xen_session *session, int64_t *result, xen_bond bond);


/**
 * Set the other_config field of the given Bond.
 */
extern bool
xen_bond_set_other_config(xen_session *session, xen_bond bond, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * Bond.
 */
extern bool
xen_bond_add_to_other_config(xen_session *session, xen_bond bond, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given Bond.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_bond_remove_from_other_config(xen_session *session, xen_bond bond, char *key);


/**
 * Create an interface bond.
 */
extern bool
xen_bond_create(xen_session *session, xen_bond *result, xen_network network, struct xen_pif_set *members, char *mac, enum xen_bond_mode mode, xen_string_string_map *properties);

/**
 * Create an interface bond.
 */
extern bool
xen_bond_create_async(xen_session *session, xen_task *result, xen_network network, struct xen_pif_set *members, char *mac, enum xen_bond_mode mode, xen_string_string_map *properties);


/**
 * Destroy an interface bond.
 */
extern bool
xen_bond_destroy(xen_session *session, xen_bond self);

/**
 * Destroy an interface bond.
 */
extern bool
xen_bond_destroy_async(xen_session *session, xen_task *result, xen_bond self);


/**
 * Change the bond mode.
 */
extern bool
xen_bond_set_mode(xen_session *session, xen_bond self, enum xen_bond_mode value);

/**
 * Change the bond mode.
 */
extern bool
xen_bond_set_mode_async(xen_session *session, xen_task *result, xen_bond self, enum xen_bond_mode value);


/**
 * Set the value of a property of the bond.
 */
extern bool
xen_bond_set_property(xen_session *session, xen_bond self, char *name, char *value);

/**
 * Set the value of a property of the bond.
 */
extern bool
xen_bond_set_property_async(xen_session *session, xen_task *result, xen_bond self, char *name, char *value);


/**
 * Return a list of all the Bonds known to the system.
 */
extern bool
xen_bond_get_all(xen_session *session, struct xen_bond_set **result);


/**
 * Return a map of Bond references to Bond records for all Bonds known
 * to the system.
 */
extern bool
xen_bond_get_all_records(xen_session *session, xen_bond_xen_bond_record_map **result);


#endif
