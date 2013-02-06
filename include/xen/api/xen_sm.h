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


#ifndef XEN_SM_H
#define XEN_SM_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_sm_decl.h>
#include <xen/api/xen_sm_xen_sm_record_map.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>


/*
 * The SM class.
 * 
 * A storage manager plugin.
 */


/**
 * Free the given xen_sm.  The given handle must have been allocated by
 * this library.
 */
extern void
xen_sm_free(xen_sm sm);


typedef struct xen_sm_set
{
    size_t size;
    xen_sm *contents[];
} xen_sm_set;

/**
 * Allocate a xen_sm_set of the given size.
 */
extern xen_sm_set *
xen_sm_set_alloc(size_t size);

/**
 * Free the given xen_sm_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_sm_set_free(xen_sm_set *set);


typedef struct xen_sm_record
{
    xen_sm handle;
    char *uuid;
    char *name_label;
    char *name_description;
    char *type;
    char *vendor;
    char *copyright;
    char *version;
    char *required_api_version;
    xen_string_string_map *configuration;
    struct xen_string_set *capabilities;
    xen_string_string_map *other_config;
    char *driver_filename;
} xen_sm_record;

/**
 * Allocate a xen_sm_record.
 */
extern xen_sm_record *
xen_sm_record_alloc(void);

/**
 * Free the given xen_sm_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_sm_record_free(xen_sm_record *record);


typedef struct xen_sm_record_opt
{
    bool is_record;
    union
    {
        xen_sm handle;
        xen_sm_record *record;
    } u;
} xen_sm_record_opt;

/**
 * Allocate a xen_sm_record_opt.
 */
extern xen_sm_record_opt *
xen_sm_record_opt_alloc(void);

/**
 * Free the given xen_sm_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_sm_record_opt_free(xen_sm_record_opt *record_opt);


typedef struct xen_sm_record_set
{
    size_t size;
    xen_sm_record *contents[];
} xen_sm_record_set;

/**
 * Allocate a xen_sm_record_set of the given size.
 */
extern xen_sm_record_set *
xen_sm_record_set_alloc(size_t size);

/**
 * Free the given xen_sm_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_sm_record_set_free(xen_sm_record_set *set);



typedef struct xen_sm_record_opt_set
{
    size_t size;
    xen_sm_record_opt *contents[];
} xen_sm_record_opt_set;

/**
 * Allocate a xen_sm_record_opt_set of the given size.
 */
extern xen_sm_record_opt_set *
xen_sm_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_sm_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_sm_record_opt_set_free(xen_sm_record_opt_set *set);


/**
 * Get a record containing the current state of the given SM.
 */
extern bool
xen_sm_get_record(xen_session *session, xen_sm_record **result, xen_sm sm);


/**
 * Get a reference to the SM instance with the specified UUID.
 */
extern bool
xen_sm_get_by_uuid(xen_session *session, xen_sm *result, const char *uuid);


/**
 * Get all the SM instances with the given label.
 */
extern bool
xen_sm_get_by_name_label(xen_session *session, struct xen_sm_set **result, const char *label);


/**
 * Get the uuid field of the given SM.
 */
extern bool
xen_sm_get_uuid(xen_session *session, char **result, xen_sm sm);


/**
 * Get the name/label field of the given SM.
 */
extern bool
xen_sm_get_name_label(xen_session *session, char **result, xen_sm sm);


/**
 * Get the name/description field of the given SM.
 */
extern bool
xen_sm_get_name_description(xen_session *session, char **result, xen_sm sm);


/**
 * Get the type field of the given SM.
 */
extern bool
xen_sm_get_type(xen_session *session, char **result, xen_sm sm);


/**
 * Get the vendor field of the given SM.
 */
extern bool
xen_sm_get_vendor(xen_session *session, char **result, xen_sm sm);


/**
 * Get the copyright field of the given SM.
 */
extern bool
xen_sm_get_copyright(xen_session *session, char **result, xen_sm sm);


/**
 * Get the version field of the given SM.
 */
extern bool
xen_sm_get_version(xen_session *session, char **result, xen_sm sm);


/**
 * Get the required_api_version field of the given SM.
 */
extern bool
xen_sm_get_required_api_version(xen_session *session, char **result, xen_sm sm);


/**
 * Get the configuration field of the given SM.
 */
extern bool
xen_sm_get_configuration(xen_session *session, xen_string_string_map **result, xen_sm sm);


/**
 * Get the capabilities field of the given SM.
 */
extern bool
xen_sm_get_capabilities(xen_session *session, struct xen_string_set **result, xen_sm sm);


/**
 * Get the other_config field of the given SM.
 */
extern bool
xen_sm_get_other_config(xen_session *session, xen_string_string_map **result, xen_sm sm);


/**
 * Get the driver_filename field of the given SM.
 */
extern bool
xen_sm_get_driver_filename(xen_session *session, char **result, xen_sm sm);


/**
 * Set the other_config field of the given SM.
 */
extern bool
xen_sm_set_other_config(xen_session *session, xen_sm sm, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * SM.
 */
extern bool
xen_sm_add_to_other_config(xen_session *session, xen_sm sm, const char *key, const char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given SM.  If the key is not in that Map, then do
 * nothing.
 */
extern bool
xen_sm_remove_from_other_config(xen_session *session, xen_sm sm, const char *key);


/**
 * Return a list of all the SMs known to the system.
 */
extern bool
xen_sm_get_all(xen_session *session, struct xen_sm_set **result);


/**
 * Return a map of SM references to SM records for all SMs known to the
 * system.
 */
extern bool
xen_sm_get_all_records(xen_session *session, xen_sm_xen_sm_record_map **result);


#endif
