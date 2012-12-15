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


#ifndef XEN_DR_TASK_H
#define XEN_DR_TASK_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_dr_task_decl.h>
#include <xen/api/xen_dr_task_xen_dr_task_record_map.h>
#include <xen/api/xen_sr_decl.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The DR_task class.
 * 
 * DR task.
 */


/**
 * Free the given xen_dr_task.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_dr_task_free(xen_dr_task dr_task);


typedef struct xen_dr_task_set
{
    size_t size;
    xen_dr_task *contents[];
} xen_dr_task_set;

/**
 * Allocate a xen_dr_task_set of the given size.
 */
extern xen_dr_task_set *
xen_dr_task_set_alloc(size_t size);

/**
 * Free the given xen_dr_task_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_dr_task_set_free(xen_dr_task_set *set);


typedef struct xen_dr_task_record
{
    xen_dr_task handle;
    char *uuid;
    struct xen_sr_record_opt_set *introduced_srs;
} xen_dr_task_record;

/**
 * Allocate a xen_dr_task_record.
 */
extern xen_dr_task_record *
xen_dr_task_record_alloc(void);

/**
 * Free the given xen_dr_task_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_dr_task_record_free(xen_dr_task_record *record);


typedef struct xen_dr_task_record_opt
{
    bool is_record;
    union
    {
        xen_dr_task handle;
        xen_dr_task_record *record;
    } u;
} xen_dr_task_record_opt;

/**
 * Allocate a xen_dr_task_record_opt.
 */
extern xen_dr_task_record_opt *
xen_dr_task_record_opt_alloc(void);

/**
 * Free the given xen_dr_task_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_dr_task_record_opt_free(xen_dr_task_record_opt *record_opt);


typedef struct xen_dr_task_record_set
{
    size_t size;
    xen_dr_task_record *contents[];
} xen_dr_task_record_set;

/**
 * Allocate a xen_dr_task_record_set of the given size.
 */
extern xen_dr_task_record_set *
xen_dr_task_record_set_alloc(size_t size);

/**
 * Free the given xen_dr_task_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_dr_task_record_set_free(xen_dr_task_record_set *set);



typedef struct xen_dr_task_record_opt_set
{
    size_t size;
    xen_dr_task_record_opt *contents[];
} xen_dr_task_record_opt_set;

/**
 * Allocate a xen_dr_task_record_opt_set of the given size.
 */
extern xen_dr_task_record_opt_set *
xen_dr_task_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_dr_task_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_dr_task_record_opt_set_free(xen_dr_task_record_opt_set *set);


/**
 * Get a record containing the current state of the given DR_task.
 */
extern bool
xen_dr_task_get_record(xen_session *session, xen_dr_task_record **result, xen_dr_task dr_task);


/**
 * Get a reference to the DR_task instance with the specified UUID.
 */
extern bool
xen_dr_task_get_by_uuid(xen_session *session, xen_dr_task *result, char *uuid);


/**
 * Get the uuid field of the given DR_task.
 */
extern bool
xen_dr_task_get_uuid(xen_session *session, char **result, xen_dr_task dr_task);


/**
 * Get the introduced_SRs field of the given DR_task.
 */
extern bool
xen_dr_task_get_introduced_srs(xen_session *session, struct xen_sr_set **result, xen_dr_task dr_task);


/**
 * Create a disaster recovery task which will query the supplied list
 * of devices.
 */
extern bool
xen_dr_task_create(xen_session *session, xen_dr_task *result, char *type, xen_string_string_map *device_config, struct xen_string_set *whitelist);

/**
 * Create a disaster recovery task which will query the supplied list
 * of devices.
 */
extern bool
xen_dr_task_create_async(xen_session *session, xen_task *result, char *type, xen_string_string_map *device_config, struct xen_string_set *whitelist);


/**
 * Destroy the disaster recovery task, detaching and forgetting any SRs
 * introduced which are no longer required.
 */
extern bool
xen_dr_task_destroy(xen_session *session, xen_dr_task self);

/**
 * Destroy the disaster recovery task, detaching and forgetting any SRs
 * introduced which are no longer required.
 */
extern bool
xen_dr_task_destroy_async(xen_session *session, xen_task *result, xen_dr_task self);


/**
 * Return a list of all the DR_tasks known to the system.
 */
extern bool
xen_dr_task_get_all(xen_session *session, struct xen_dr_task_set **result);


/**
 * Return a map of DR_task references to DR_task records for all
 * DR_tasks known to the system.
 */
extern bool
xen_dr_task_get_all_records(xen_session *session, xen_dr_task_xen_dr_task_record_map **result);


#endif
