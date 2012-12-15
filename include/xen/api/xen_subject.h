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


#ifndef XEN_SUBJECT_H
#define XEN_SUBJECT_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_role_decl.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_subject_decl.h>
#include <xen/api/xen_subject_xen_subject_record_map.h>
#include <xen/api/xen_task_decl.h>


/*
 * The subject class.
 * 
 * A user or group that can log in xapi.
 */


/**
 * Free the given xen_subject.  The given handle must have been
 * allocated by this library.
 */
extern void
xen_subject_free(xen_subject subject);


typedef struct xen_subject_set
{
    size_t size;
    xen_subject *contents[];
} xen_subject_set;

/**
 * Allocate a xen_subject_set of the given size.
 */
extern xen_subject_set *
xen_subject_set_alloc(size_t size);

/**
 * Free the given xen_subject_set.  The given set must have been
 * allocated by this library.
 */
extern void
xen_subject_set_free(xen_subject_set *set);


typedef struct xen_subject_record
{
    xen_subject handle;
    char *uuid;
    char *subject_identifier;
    xen_string_string_map *other_config;
    struct xen_role_record_opt_set *roles;
} xen_subject_record;

/**
 * Allocate a xen_subject_record.
 */
extern xen_subject_record *
xen_subject_record_alloc(void);

/**
 * Free the given xen_subject_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_subject_record_free(xen_subject_record *record);


typedef struct xen_subject_record_opt
{
    bool is_record;
    union
    {
        xen_subject handle;
        xen_subject_record *record;
    } u;
} xen_subject_record_opt;

/**
 * Allocate a xen_subject_record_opt.
 */
extern xen_subject_record_opt *
xen_subject_record_opt_alloc(void);

/**
 * Free the given xen_subject_record_opt, and all referenced values. 
 * The given record_opt must have been allocated by this library.
 */
extern void
xen_subject_record_opt_free(xen_subject_record_opt *record_opt);


typedef struct xen_subject_record_set
{
    size_t size;
    xen_subject_record *contents[];
} xen_subject_record_set;

/**
 * Allocate a xen_subject_record_set of the given size.
 */
extern xen_subject_record_set *
xen_subject_record_set_alloc(size_t size);

/**
 * Free the given xen_subject_record_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_subject_record_set_free(xen_subject_record_set *set);



typedef struct xen_subject_record_opt_set
{
    size_t size;
    xen_subject_record_opt *contents[];
} xen_subject_record_opt_set;

/**
 * Allocate a xen_subject_record_opt_set of the given size.
 */
extern xen_subject_record_opt_set *
xen_subject_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_subject_record_opt_set, and all referenced
 * values.  The given set must have been allocated by this library.
 */
extern void
xen_subject_record_opt_set_free(xen_subject_record_opt_set *set);


/**
 * Get a record containing the current state of the given subject.
 */
extern bool
xen_subject_get_record(xen_session *session, xen_subject_record **result, xen_subject subject);


/**
 * Get a reference to the subject instance with the specified UUID.
 */
extern bool
xen_subject_get_by_uuid(xen_session *session, xen_subject *result, char *uuid);


/**
 * Create a new subject instance, and return its handle.
 */
extern bool
xen_subject_create(xen_session *session, xen_subject *result, xen_subject_record *record);

/**
 * Create a new subject instance, and return its handle.
 */
extern bool
xen_subject_create_async(xen_session *session, xen_task *result, xen_subject_record *record);


/**
 * Destroy the specified subject instance.
 */
extern bool
xen_subject_destroy(xen_session *session, xen_subject subject);

/**
 * Destroy the specified subject instance.
 */
extern bool
xen_subject_destroy_async(xen_session *session, xen_task *result, xen_subject subject);


/**
 * Get the uuid field of the given subject.
 */
extern bool
xen_subject_get_uuid(xen_session *session, char **result, xen_subject subject);


/**
 * Get the subject_identifier field of the given subject.
 */
extern bool
xen_subject_get_subject_identifier(xen_session *session, char **result, xen_subject subject);


/**
 * Get the other_config field of the given subject.
 */
extern bool
xen_subject_get_other_config(xen_session *session, xen_string_string_map **result, xen_subject subject);


/**
 * Get the roles field of the given subject.
 */
extern bool
xen_subject_get_roles(xen_session *session, struct xen_role_set **result, xen_subject subject);


/**
 * This call adds a new role to a subject.
 */
extern bool
xen_subject_add_to_roles(xen_session *session, xen_subject self, xen_role role);


/**
 * This call removes a role from a subject.
 */
extern bool
xen_subject_remove_from_roles(xen_session *session, xen_subject self, xen_role role);


/**
 * This call returns a list of permission names given a subject.
 */
extern bool
xen_subject_get_permissions_name_label(xen_session *session, struct xen_string_set **result, xen_subject self);


/**
 * Return a list of all the subjects known to the system.
 */
extern bool
xen_subject_get_all(xen_session *session, struct xen_subject_set **result);


/**
 * Return a map of subject references to subject records for all
 * subjects known to the system.
 */
extern bool
xen_subject_get_all_records(xen_session *session, xen_subject_xen_subject_record_map **result);


#endif
