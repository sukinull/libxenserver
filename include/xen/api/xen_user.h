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


#ifndef XEN_USER_H
#define XEN_USER_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_user_decl.h>


/*
 * The user class.
 * 
 * A user of the system.
 */


/**
 * Free the given xen_user.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_user_free(xen_user user);


typedef struct xen_user_set
{
    size_t size;
    xen_user *contents[];
} xen_user_set;

/**
 * Allocate a xen_user_set of the given size.
 */
extern xen_user_set *
xen_user_set_alloc(size_t size);

/**
 * Free the given xen_user_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_user_set_free(xen_user_set *set);


typedef struct xen_user_record
{
    xen_user handle;
    char *uuid;
    char *short_name;
    char *fullname;
    xen_string_string_map *other_config;
} xen_user_record;

/**
 * Allocate a xen_user_record.
 */
extern xen_user_record *
xen_user_record_alloc(void);

/**
 * Free the given xen_user_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_user_record_free(xen_user_record *record);


typedef struct xen_user_record_opt
{
    bool is_record;
    union
    {
        xen_user handle;
        xen_user_record *record;
    } u;
} xen_user_record_opt;

/**
 * Allocate a xen_user_record_opt.
 */
extern xen_user_record_opt *
xen_user_record_opt_alloc(void);

/**
 * Free the given xen_user_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_user_record_opt_free(xen_user_record_opt *record_opt);


typedef struct xen_user_record_set
{
    size_t size;
    xen_user_record *contents[];
} xen_user_record_set;

/**
 * Allocate a xen_user_record_set of the given size.
 */
extern xen_user_record_set *
xen_user_record_set_alloc(size_t size);

/**
 * Free the given xen_user_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_user_record_set_free(xen_user_record_set *set);



typedef struct xen_user_record_opt_set
{
    size_t size;
    xen_user_record_opt *contents[];
} xen_user_record_opt_set;

/**
 * Allocate a xen_user_record_opt_set of the given size.
 */
extern xen_user_record_opt_set *
xen_user_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_user_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_user_record_opt_set_free(xen_user_record_opt_set *set);


/**
 * Get a record containing the current state of the given user.
 */
extern bool
xen_user_get_record(xen_session *session, xen_user_record **result, xen_user user);


/**
 * Get a reference to the user instance with the specified UUID.
 */
extern bool
xen_user_get_by_uuid(xen_session *session, xen_user *result, char *uuid);


/**
 * Create a new user instance, and return its handle.
 */
extern bool
xen_user_create(xen_session *session, xen_user *result, xen_user_record *record);

/**
 * Create a new user instance, and return its handle.
 */
extern bool
xen_user_create_async(xen_session *session, xen_task *result, xen_user_record *record);


/**
 * Destroy the specified user instance.
 */
extern bool
xen_user_destroy(xen_session *session, xen_user user);

/**
 * Destroy the specified user instance.
 */
extern bool
xen_user_destroy_async(xen_session *session, xen_task *result, xen_user user);


/**
 * Get the uuid field of the given user.
 */
extern bool
xen_user_get_uuid(xen_session *session, char **result, xen_user user);


/**
 * Get the short_name field of the given user.
 */
extern bool
xen_user_get_short_name(xen_session *session, char **result, xen_user user);


/**
 * Get the fullname field of the given user.
 */
extern bool
xen_user_get_fullname(xen_session *session, char **result, xen_user user);


/**
 * Get the other_config field of the given user.
 */
extern bool
xen_user_get_other_config(xen_session *session, xen_string_string_map **result, xen_user user);


/**
 * Set the fullname field of the given user.
 */
extern bool
xen_user_set_fullname(xen_session *session, xen_user user, char *fullname);


/**
 * Set the other_config field of the given user.
 */
extern bool
xen_user_set_other_config(xen_session *session, xen_user user, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * user.
 */
extern bool
xen_user_add_to_other_config(xen_session *session, xen_user user, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given user.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_user_remove_from_other_config(xen_session *session, xen_user user, char *key);


#endif
