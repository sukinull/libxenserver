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


#ifndef XEN_HOST_CPU_H
#define XEN_HOST_CPU_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_host_cpu_decl.h>
#include <xen/api/xen_host_cpu_xen_host_cpu_record_map.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_string_string_map.h>


/*
 * The host_cpu class.
 * 
 * A physical CPU.
 */


/**
 * Free the given xen_host_cpu.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_host_cpu_free(xen_host_cpu host_cpu);


typedef struct xen_host_cpu_set
{
    size_t size;
    xen_host_cpu *contents[];
} xen_host_cpu_set;

/**
 * Allocate a xen_host_cpu_set of the given size.
 */
extern xen_host_cpu_set *
xen_host_cpu_set_alloc(size_t size);

/**
 * Free the given xen_host_cpu_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_host_cpu_set_free(xen_host_cpu_set *set);


typedef struct xen_host_cpu_record
{
    xen_host_cpu handle;
    char *uuid;
    struct xen_host_record_opt *host;
    int64_t number;
    char *vendor;
    int64_t speed;
    char *modelname;
    int64_t family;
    int64_t model;
    char *stepping;
    char *flags;
    char *features;
    double utilisation;
    xen_string_string_map *other_config;
} xen_host_cpu_record;

/**
 * Allocate a xen_host_cpu_record.
 */
extern xen_host_cpu_record *
xen_host_cpu_record_alloc(void);

/**
 * Free the given xen_host_cpu_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_host_cpu_record_free(xen_host_cpu_record *record);


typedef struct xen_host_cpu_record_opt
{
    bool is_record;
    union
    {
        xen_host_cpu handle;
        xen_host_cpu_record *record;
    } u;
} xen_host_cpu_record_opt;

/**
 * Allocate a xen_host_cpu_record_opt.
 */
extern xen_host_cpu_record_opt *
xen_host_cpu_record_opt_alloc(void);

/**
 * Free the given xen_host_cpu_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_host_cpu_record_opt_free(xen_host_cpu_record_opt *record_opt);


typedef struct xen_host_cpu_record_set
{
    size_t size;
    xen_host_cpu_record *contents[];
} xen_host_cpu_record_set;

/**
 * Allocate a xen_host_cpu_record_set of the given size.
 */
extern xen_host_cpu_record_set *
xen_host_cpu_record_set_alloc(size_t size);

/**
 * Free the given xen_host_cpu_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_host_cpu_record_set_free(xen_host_cpu_record_set *set);



typedef struct xen_host_cpu_record_opt_set
{
    size_t size;
    xen_host_cpu_record_opt *contents[];
} xen_host_cpu_record_opt_set;

/**
 * Allocate a xen_host_cpu_record_opt_set of the given size.
 */
extern xen_host_cpu_record_opt_set *
xen_host_cpu_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_host_cpu_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_host_cpu_record_opt_set_free(xen_host_cpu_record_opt_set *set);


/**
 * Get a record containing the current state of the given host_cpu.
 */
extern bool
xen_host_cpu_get_record(xen_session *session, xen_host_cpu_record **result, xen_host_cpu host_cpu);


/**
 * Get a reference to the host_cpu instance with the specified UUID.
 */
extern bool
xen_host_cpu_get_by_uuid(xen_session *session, xen_host_cpu *result, char *uuid);


/**
 * Get the uuid field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_uuid(xen_session *session, char **result, xen_host_cpu host_cpu);


/**
 * Get the host field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_host(xen_session *session, xen_host *result, xen_host_cpu host_cpu);


/**
 * Get the number field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_number(xen_session *session, int64_t *result, xen_host_cpu host_cpu);


/**
 * Get the vendor field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_vendor(xen_session *session, char **result, xen_host_cpu host_cpu);


/**
 * Get the speed field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_speed(xen_session *session, int64_t *result, xen_host_cpu host_cpu);


/**
 * Get the modelname field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_modelname(xen_session *session, char **result, xen_host_cpu host_cpu);


/**
 * Get the family field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_family(xen_session *session, int64_t *result, xen_host_cpu host_cpu);


/**
 * Get the model field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_model(xen_session *session, int64_t *result, xen_host_cpu host_cpu);


/**
 * Get the stepping field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_stepping(xen_session *session, char **result, xen_host_cpu host_cpu);


/**
 * Get the flags field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_flags(xen_session *session, char **result, xen_host_cpu host_cpu);


/**
 * Get the features field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_features(xen_session *session, char **result, xen_host_cpu host_cpu);


/**
 * Get the utilisation field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_utilisation(xen_session *session, double *result, xen_host_cpu host_cpu);


/**
 * Get the other_config field of the given host_cpu.
 */
extern bool
xen_host_cpu_get_other_config(xen_session *session, xen_string_string_map **result, xen_host_cpu host_cpu);


/**
 * Set the other_config field of the given host_cpu.
 */
extern bool
xen_host_cpu_set_other_config(xen_session *session, xen_host_cpu host_cpu, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * host_cpu.
 */
extern bool
xen_host_cpu_add_to_other_config(xen_session *session, xen_host_cpu host_cpu, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given host_cpu.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_host_cpu_remove_from_other_config(xen_session *session, xen_host_cpu host_cpu, char *key);


/**
 * Return a list of all the host_cpus known to the system.
 */
extern bool
xen_host_cpu_get_all(xen_session *session, struct xen_host_cpu_set **result);


/**
 * Return a map of host_cpu references to host_cpu records for all
 * host_cpus known to the system.
 */
extern bool
xen_host_cpu_get_all_records(xen_session *session, xen_host_cpu_xen_host_cpu_record_map **result);


#endif
