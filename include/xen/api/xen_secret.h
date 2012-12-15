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


#ifndef XEN_SECRET_H
#define XEN_SECRET_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_secret_decl.h>
#include <xen/api/xen_secret_xen_secret_record_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The secret class.
 * 
 * A secret.
 */


/**
 * Free the given xen_secret.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_secret_free(xen_secret secret);


typedef struct xen_secret_set
{
    size_t size;
    xen_secret *contents[];
} xen_secret_set;

/**
 * Allocate a xen_secret_set of the given size.
 */
extern xen_secret_set *
xen_secret_set_alloc(size_t size);

/**
 * Free the given xen_secret_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_secret_set_free(xen_secret_set *set);


typedef struct xen_secret_record
{
    xen_secret handle;
    char *uuid;
    char *value;
    xen_string_string_map *other_config;
} xen_secret_record;

/**
 * Allocate a xen_secret_record.
 */
extern xen_secret_record *
xen_secret_record_alloc(void);

/**
 * Free the given xen_secret_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_secret_record_free(xen_secret_record *record);


typedef struct xen_secret_record_opt
{
    bool is_record;
    union
    {
        xen_secret handle;
        xen_secret_record *record;
    } u;
} xen_secret_record_opt;

/**
 * Allocate a xen_secret_record_opt.
 */
extern xen_secret_record_opt *
xen_secret_record_opt_alloc(void);

/**
 * Free the given xen_secret_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_secret_record_opt_free(xen_secret_record_opt *record_opt);


typedef struct xen_secret_record_set
{
    size_t size;
    xen_secret_record *contents[];
} xen_secret_record_set;

/**
 * Allocate a xen_secret_record_set of the given size.
 */
extern xen_secret_record_set *
xen_secret_record_set_alloc(size_t size);

/**
 * Free the given xen_secret_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_secret_record_set_free(xen_secret_record_set *set);



typedef struct xen_secret_record_opt_set
{
    size_t size;
    xen_secret_record_opt *contents[];
} xen_secret_record_opt_set;

/**
 * Allocate a xen_secret_record_opt_set of the given size.
 */
extern xen_secret_record_opt_set *
xen_secret_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_secret_record_opt_set, and all referenced values.
 *  The given set must have been allocated by this library.
 */
extern void
xen_secret_record_opt_set_free(xen_secret_record_opt_set *set);


/**
 * Get a record containing the current state of the given secret.
 */
extern bool
xen_secret_get_record(xen_session *session, xen_secret_record **result, xen_secret secret);


/**
 * Get a reference to the secret instance with the specified UUID.
 */
extern bool
xen_secret_get_by_uuid(xen_session *session, xen_secret *result, char *uuid);


/**
 * Create a new secret instance, and return its handle.
 */
extern bool
xen_secret_create(xen_session *session, xen_secret *result, xen_secret_record *record);

/**
 * Create a new secret instance, and return its handle.
 */
extern bool
xen_secret_create_async(xen_session *session, xen_task *result, xen_secret_record *record);


/**
 * Destroy the specified secret instance.
 */
extern bool
xen_secret_destroy(xen_session *session, xen_secret secret);

/**
 * Destroy the specified secret instance.
 */
extern bool
xen_secret_destroy_async(xen_session *session, xen_task *result, xen_secret secret);


/**
 * Get the uuid field of the given secret.
 */
extern bool
xen_secret_get_uuid(xen_session *session, char **result, xen_secret secret);


/**
 * Get the value field of the given secret.
 */
extern bool
xen_secret_get_value(xen_session *session, char **result, xen_secret secret);


/**
 * Get the other_config field of the given secret.
 */
extern bool
xen_secret_get_other_config(xen_session *session, xen_string_string_map **result, xen_secret secret);


/**
 * Set the value field of the given secret.
 */
extern bool
xen_secret_set_value(xen_session *session, xen_secret secret, char *value);


/**
 * Set the other_config field of the given secret.
 */
extern bool
xen_secret_set_other_config(xen_session *session, xen_secret secret, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * secret.
 */
extern bool
xen_secret_add_to_other_config(xen_session *session, xen_secret secret, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given secret.  If the key is not in that Map,
 * then do nothing.
 */
extern bool
xen_secret_remove_from_other_config(xen_session *session, xen_secret secret, char *key);


/**
 * Return a list of all the secrets known to the system.
 */
extern bool
xen_secret_get_all(xen_session *session, struct xen_secret_set **result);


/**
 * Return a map of secret references to secret records for all secrets
 * known to the system.
 */
extern bool
xen_secret_get_all_records(xen_session *session, xen_secret_xen_secret_record_map **result);


#endif
