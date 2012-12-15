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


#ifndef XEN_AUTH_H
#define XEN_AUTH_H

#include <xen/api/xen_auth_decl.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>


/*
 * The auth class.
 * 
 * Management of remote authentication services.
 */


/**
 * Free the given xen_auth.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_auth_free(xen_auth auth);


typedef struct xen_auth_set
{
    size_t size;
    xen_auth *contents[];
} xen_auth_set;

/**
 * Allocate a xen_auth_set of the given size.
 */
extern xen_auth_set *
xen_auth_set_alloc(size_t size);

/**
 * Free the given xen_auth_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_auth_set_free(xen_auth_set *set);


typedef struct xen_auth_record
{
    xen_auth handle;
    
} xen_auth_record;

/**
 * Allocate a xen_auth_record.
 */
extern xen_auth_record *
xen_auth_record_alloc(void);

/**
 * Free the given xen_auth_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_auth_record_free(xen_auth_record *record);


typedef struct xen_auth_record_opt
{
    bool is_record;
    union
    {
        xen_auth handle;
        xen_auth_record *record;
    } u;
} xen_auth_record_opt;

/**
 * Allocate a xen_auth_record_opt.
 */
extern xen_auth_record_opt *
xen_auth_record_opt_alloc(void);

/**
 * Free the given xen_auth_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_auth_record_opt_free(xen_auth_record_opt *record_opt);


typedef struct xen_auth_record_set
{
    size_t size;
    xen_auth_record *contents[];
} xen_auth_record_set;

/**
 * Allocate a xen_auth_record_set of the given size.
 */
extern xen_auth_record_set *
xen_auth_record_set_alloc(size_t size);

/**
 * Free the given xen_auth_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_auth_record_set_free(xen_auth_record_set *set);



typedef struct xen_auth_record_opt_set
{
    size_t size;
    xen_auth_record_opt *contents[];
} xen_auth_record_opt_set;

/**
 * Allocate a xen_auth_record_opt_set of the given size.
 */
extern xen_auth_record_opt_set *
xen_auth_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_auth_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_auth_record_opt_set_free(xen_auth_record_opt_set *set);


/**
 * This call queries the external directory service to obtain the
 * subject_identifier as a string from the human-readable subject_name.
 */
extern bool
xen_auth_get_subject_identifier(xen_session *session, char **result, char *subject_name);


/**
 * This call queries the external directory service to obtain the user
 * information (e.g. username, organization etc) from the specified
 * subject_identifier.
 */
extern bool
xen_auth_get_subject_information_from_identifier(xen_session *session, xen_string_string_map **result, char *subject_identifier);


/**
 * This calls queries the external directory service to obtain the
 * transitively-closed set of groups that the the subject_identifier is member
 * of.
 */
extern bool
xen_auth_get_group_membership(xen_session *session, struct xen_string_set **result, char *subject_identifier);


#endif
