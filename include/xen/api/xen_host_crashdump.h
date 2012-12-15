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


#ifndef XEN_HOST_CRASHDUMP_H
#define XEN_HOST_CRASHDUMP_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_host_crashdump_decl.h>
#include <xen/api/xen_host_crashdump_xen_host_crashdump_record_map.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The host_crashdump class.
 * 
 * Represents a host crash dump.
 */


/**
 * Free the given xen_host_crashdump.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_host_crashdump_free(xen_host_crashdump host_crashdump);


typedef struct xen_host_crashdump_set
{
    size_t size;
    xen_host_crashdump *contents[];
} xen_host_crashdump_set;

/**
 * Allocate a xen_host_crashdump_set of the given size.
 */
extern xen_host_crashdump_set *
xen_host_crashdump_set_alloc(size_t size);

/**
 * Free the given xen_host_crashdump_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_host_crashdump_set_free(xen_host_crashdump_set *set);


typedef struct xen_host_crashdump_record
{
    xen_host_crashdump handle;
    char *uuid;
    struct xen_host_record_opt *host;
    time_t timestamp;
    int64_t size;
    xen_string_string_map *other_config;
} xen_host_crashdump_record;

/**
 * Allocate a xen_host_crashdump_record.
 */
extern xen_host_crashdump_record *
xen_host_crashdump_record_alloc(void);

/**
 * Free the given xen_host_crashdump_record, and all referenced values.
 *  The given record must have been allocated by this library.
 */
extern void
xen_host_crashdump_record_free(xen_host_crashdump_record *record);


typedef struct xen_host_crashdump_record_opt
{
    bool is_record;
    union
    {
        xen_host_crashdump handle;
        xen_host_crashdump_record *record;
    } u;
} xen_host_crashdump_record_opt;

/**
 * Allocate a xen_host_crashdump_record_opt.
 */
extern xen_host_crashdump_record_opt *
xen_host_crashdump_record_opt_alloc(void);

/**
 * Free the given xen_host_crashdump_record_opt, and all referenced
 * values.  The given record_opt must have been allocated by this library.
 */
extern void
xen_host_crashdump_record_opt_free(xen_host_crashdump_record_opt *record_opt);


typedef struct xen_host_crashdump_record_set
{
    size_t size;
    xen_host_crashdump_record *contents[];
} xen_host_crashdump_record_set;

/**
 * Allocate a xen_host_crashdump_record_set of the given size.
 */
extern xen_host_crashdump_record_set *
xen_host_crashdump_record_set_alloc(size_t size);

/**
 * Free the given xen_host_crashdump_record_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_host_crashdump_record_set_free(xen_host_crashdump_record_set *set);



typedef struct xen_host_crashdump_record_opt_set
{
    size_t size;
    xen_host_crashdump_record_opt *contents[];
} xen_host_crashdump_record_opt_set;

/**
 * Allocate a xen_host_crashdump_record_opt_set of the given size.
 */
extern xen_host_crashdump_record_opt_set *
xen_host_crashdump_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_host_crashdump_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_host_crashdump_record_opt_set_free(xen_host_crashdump_record_opt_set *set);


/**
 * Get a record containing the current state of the given
 * host_crashdump.
 */
extern bool
xen_host_crashdump_get_record(xen_session *session, xen_host_crashdump_record **result, xen_host_crashdump host_crashdump);


/**
 * Get a reference to the host_crashdump instance with the specified
 * UUID.
 */
extern bool
xen_host_crashdump_get_by_uuid(xen_session *session, xen_host_crashdump *result, char *uuid);


/**
 * Get the uuid field of the given host_crashdump.
 */
extern bool
xen_host_crashdump_get_uuid(xen_session *session, char **result, xen_host_crashdump host_crashdump);


/**
 * Get the host field of the given host_crashdump.
 */
extern bool
xen_host_crashdump_get_host(xen_session *session, xen_host *result, xen_host_crashdump host_crashdump);


/**
 * Get the timestamp field of the given host_crashdump.
 */
extern bool
xen_host_crashdump_get_timestamp(xen_session *session, time_t *result, xen_host_crashdump host_crashdump);


/**
 * Get the size field of the given host_crashdump.
 */
extern bool
xen_host_crashdump_get_size(xen_session *session, int64_t *result, xen_host_crashdump host_crashdump);


/**
 * Get the other_config field of the given host_crashdump.
 */
extern bool
xen_host_crashdump_get_other_config(xen_session *session, xen_string_string_map **result, xen_host_crashdump host_crashdump);


/**
 * Set the other_config field of the given host_crashdump.
 */
extern bool
xen_host_crashdump_set_other_config(xen_session *session, xen_host_crashdump host_crashdump, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * host_crashdump.
 */
extern bool
xen_host_crashdump_add_to_other_config(xen_session *session, xen_host_crashdump host_crashdump, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given host_crashdump.  If the key is not in that
 * Map, then do nothing.
 */
extern bool
xen_host_crashdump_remove_from_other_config(xen_session *session, xen_host_crashdump host_crashdump, char *key);


/**
 * Destroy specified host crash dump, removing it from the disk.
 */
extern bool
xen_host_crashdump_destroy(xen_session *session, xen_host_crashdump self);

/**
 * Destroy specified host crash dump, removing it from the disk.
 */
extern bool
xen_host_crashdump_destroy_async(xen_session *session, xen_task *result, xen_host_crashdump self);


/**
 * Upload the specified host crash dump to a specified URL.
 */
extern bool
xen_host_crashdump_upload(xen_session *session, xen_host_crashdump self, char *url, xen_string_string_map *options);

/**
 * Upload the specified host crash dump to a specified URL.
 */
extern bool
xen_host_crashdump_upload_async(xen_session *session, xen_task *result, xen_host_crashdump self, char *url, xen_string_string_map *options);


/**
 * Return a list of all the host_crashdumps known to the system.
 */
extern bool
xen_host_crashdump_get_all(xen_session *session, struct xen_host_crashdump_set **result);


/**
 * Return a map of host_crashdump references to host_crashdump records
 * for all host_crashdumps known to the system.
 */
extern bool
xen_host_crashdump_get_all_records(xen_session *session, xen_host_crashdump_xen_host_crashdump_record_map **result);


#endif
