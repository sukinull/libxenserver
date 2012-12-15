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


#ifndef XEN_ROLE_H
#define XEN_ROLE_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_role_decl.h>
#include <xen/api/xen_role_xen_role_record_map.h>
#include <xen/api/xen_string_set.h>


/*
 * The role class.
 * 
 * A set of permissions associated with a subject.
 */


/**
 * Free the given xen_role.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_role_free(xen_role role);


typedef struct xen_role_set
{
    size_t size;
    xen_role *contents[];
} xen_role_set;

/**
 * Allocate a xen_role_set of the given size.
 */
extern xen_role_set *
xen_role_set_alloc(size_t size);

/**
 * Free the given xen_role_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_role_set_free(xen_role_set *set);


typedef struct xen_role_record
{
    xen_role handle;
    char *uuid;
    char *name_label;
    char *name_description;
    struct xen_role_record_opt_set *subroles;
} xen_role_record;

/**
 * Allocate a xen_role_record.
 */
extern xen_role_record *
xen_role_record_alloc(void);

/**
 * Free the given xen_role_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_role_record_free(xen_role_record *record);


typedef struct xen_role_record_opt
{
    bool is_record;
    union
    {
        xen_role handle;
        xen_role_record *record;
    } u;
} xen_role_record_opt;

/**
 * Allocate a xen_role_record_opt.
 */
extern xen_role_record_opt *
xen_role_record_opt_alloc(void);

/**
 * Free the given xen_role_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_role_record_opt_free(xen_role_record_opt *record_opt);


typedef struct xen_role_record_set
{
    size_t size;
    xen_role_record *contents[];
} xen_role_record_set;

/**
 * Allocate a xen_role_record_set of the given size.
 */
extern xen_role_record_set *
xen_role_record_set_alloc(size_t size);

/**
 * Free the given xen_role_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_role_record_set_free(xen_role_record_set *set);



typedef struct xen_role_record_opt_set
{
    size_t size;
    xen_role_record_opt *contents[];
} xen_role_record_opt_set;

/**
 * Allocate a xen_role_record_opt_set of the given size.
 */
extern xen_role_record_opt_set *
xen_role_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_role_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_role_record_opt_set_free(xen_role_record_opt_set *set);


/**
 * Get a record containing the current state of the given role.
 */
extern bool
xen_role_get_record(xen_session *session, xen_role_record **result, xen_role role);


/**
 * Get a reference to the role instance with the specified UUID.
 */
extern bool
xen_role_get_by_uuid(xen_session *session, xen_role *result, char *uuid);


/**
 * Get all the role instances with the given label.
 */
extern bool
xen_role_get_by_name_label(xen_session *session, struct xen_role_set **result, char *label);


/**
 * Get the uuid field of the given role.
 */
extern bool
xen_role_get_uuid(xen_session *session, char **result, xen_role role);


/**
 * Get the name/label field of the given role.
 */
extern bool
xen_role_get_name_label(xen_session *session, char **result, xen_role role);


/**
 * Get the name/description field of the given role.
 */
extern bool
xen_role_get_name_description(xen_session *session, char **result, xen_role role);


/**
 * Get the subroles field of the given role.
 */
extern bool
xen_role_get_subroles(xen_session *session, struct xen_role_set **result, xen_role role);


/**
 * This call returns a list of permissions given a role.
 */
extern bool
xen_role_get_permissions(xen_session *session, struct xen_role_set **result, xen_role self);


/**
 * This call returns a list of permission names given a role.
 */
extern bool
xen_role_get_permissions_name_label(xen_session *session, struct xen_string_set **result, xen_role self);


/**
 * This call returns a list of roles given a permission.
 */
extern bool
xen_role_get_by_permission(xen_session *session, struct xen_role_set **result, xen_role permission);


/**
 * This call returns a list of roles given a permission name.
 */
extern bool
xen_role_get_by_permission_name_label(xen_session *session, struct xen_role_set **result, char *label);


/**
 * Return a list of all the roles known to the system.
 */
extern bool
xen_role_get_all(xen_session *session, struct xen_role_set **result);


/**
 * Return a map of role references to role records for all roles known
 * to the system.
 */
extern bool
xen_role_get_all_records(xen_session *session, xen_role_xen_role_record_map **result);


#endif
