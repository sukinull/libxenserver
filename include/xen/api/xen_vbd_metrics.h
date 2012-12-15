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


#ifndef XEN_VBD_METRICS_H
#define XEN_VBD_METRICS_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vbd_metrics_decl.h>
#include <xen/api/xen_vbd_metrics_xen_vbd_metrics_record_map.h>


/*
 * The VBD_metrics class.
 * 
 * The metrics associated with a virtual block device.
 */


/**
 * Free the given xen_vbd_metrics.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_vbd_metrics_free(xen_vbd_metrics vbd_metrics);


typedef struct xen_vbd_metrics_set
{
    size_t size;
    xen_vbd_metrics *contents[];
} xen_vbd_metrics_set;

/**
 * Allocate a xen_vbd_metrics_set of the given size.
 */
extern xen_vbd_metrics_set *
xen_vbd_metrics_set_alloc(size_t size);

/**
 * Free the given xen_vbd_metrics_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_vbd_metrics_set_free(xen_vbd_metrics_set *set);


typedef struct xen_vbd_metrics_record
{
    xen_vbd_metrics handle;
    char *uuid;
    double io_read_kbs;
    double io_write_kbs;
    time_t last_updated;
    xen_string_string_map *other_config;
} xen_vbd_metrics_record;

/**
 * Allocate a xen_vbd_metrics_record.
 */
extern xen_vbd_metrics_record *
xen_vbd_metrics_record_alloc(void);

/**
 * Free the given xen_vbd_metrics_record, and all referenced values. 
 * The given record must have been allocated by this library.
 */
extern void
xen_vbd_metrics_record_free(xen_vbd_metrics_record *record);


typedef struct xen_vbd_metrics_record_opt
{
    bool is_record;
    union
    {
        xen_vbd_metrics handle;
        xen_vbd_metrics_record *record;
    } u;
} xen_vbd_metrics_record_opt;

/**
 * Allocate a xen_vbd_metrics_record_opt.
 */
extern xen_vbd_metrics_record_opt *
xen_vbd_metrics_record_opt_alloc(void);

/**
 * Free the given xen_vbd_metrics_record_opt, and all referenced
 * values.  The given record_opt must have been allocated by this library.
 */
extern void
xen_vbd_metrics_record_opt_free(xen_vbd_metrics_record_opt *record_opt);


typedef struct xen_vbd_metrics_record_set
{
    size_t size;
    xen_vbd_metrics_record *contents[];
} xen_vbd_metrics_record_set;

/**
 * Allocate a xen_vbd_metrics_record_set of the given size.
 */
extern xen_vbd_metrics_record_set *
xen_vbd_metrics_record_set_alloc(size_t size);

/**
 * Free the given xen_vbd_metrics_record_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_vbd_metrics_record_set_free(xen_vbd_metrics_record_set *set);



typedef struct xen_vbd_metrics_record_opt_set
{
    size_t size;
    xen_vbd_metrics_record_opt *contents[];
} xen_vbd_metrics_record_opt_set;

/**
 * Allocate a xen_vbd_metrics_record_opt_set of the given size.
 */
extern xen_vbd_metrics_record_opt_set *
xen_vbd_metrics_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vbd_metrics_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_vbd_metrics_record_opt_set_free(xen_vbd_metrics_record_opt_set *set);


/**
 * Get a record containing the current state of the given VBD_metrics.
 */
extern bool
xen_vbd_metrics_get_record(xen_session *session, xen_vbd_metrics_record **result, xen_vbd_metrics vbd_metrics);


/**
 * Get a reference to the VBD_metrics instance with the specified UUID.
 */
extern bool
xen_vbd_metrics_get_by_uuid(xen_session *session, xen_vbd_metrics *result, char *uuid);


/**
 * Get the uuid field of the given VBD_metrics.
 */
extern bool
xen_vbd_metrics_get_uuid(xen_session *session, char **result, xen_vbd_metrics vbd_metrics);


/**
 * Get the io/read_kbs field of the given VBD_metrics.
 */
extern bool
xen_vbd_metrics_get_io_read_kbs(xen_session *session, double *result, xen_vbd_metrics vbd_metrics);


/**
 * Get the io/write_kbs field of the given VBD_metrics.
 */
extern bool
xen_vbd_metrics_get_io_write_kbs(xen_session *session, double *result, xen_vbd_metrics vbd_metrics);


/**
 * Get the last_updated field of the given VBD_metrics.
 */
extern bool
xen_vbd_metrics_get_last_updated(xen_session *session, time_t *result, xen_vbd_metrics vbd_metrics);


/**
 * Get the other_config field of the given VBD_metrics.
 */
extern bool
xen_vbd_metrics_get_other_config(xen_session *session, xen_string_string_map **result, xen_vbd_metrics vbd_metrics);


/**
 * Set the other_config field of the given VBD_metrics.
 */
extern bool
xen_vbd_metrics_set_other_config(xen_session *session, xen_vbd_metrics vbd_metrics, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * VBD_metrics.
 */
extern bool
xen_vbd_metrics_add_to_other_config(xen_session *session, xen_vbd_metrics vbd_metrics, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given VBD_metrics.  If the key is not in that
 * Map, then do nothing.
 */
extern bool
xen_vbd_metrics_remove_from_other_config(xen_session *session, xen_vbd_metrics vbd_metrics, char *key);


/**
 * Return a list of all the VBD_metrics instances known to the system.
 */
extern bool
xen_vbd_metrics_get_all(xen_session *session, struct xen_vbd_metrics_set **result);


/**
 * Return a map of VBD_metrics references to VBD_metrics records for
 * all VBD_metrics instances known to the system.
 */
extern bool
xen_vbd_metrics_get_all_records(xen_session *session, xen_vbd_metrics_xen_vbd_metrics_record_map **result);


#endif
