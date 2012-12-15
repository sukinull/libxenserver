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



#include <stddef.h>
#include <stdlib.h>

#include "xen_internal.h"
#include <xen/api/xen_auth.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_auth)
XEN_SET_ALLOC_FREE(xen_auth)
XEN_ALLOC(xen_auth_record)
XEN_SET_ALLOC_FREE(xen_auth_record)
XEN_ALLOC(xen_auth_record_opt)
XEN_RECORD_OPT_FREE(xen_auth)
XEN_SET_ALLOC_FREE(xen_auth_record_opt)


static const struct_member xen_auth_record_struct_members[] =
    {
        
    };

const abstract_type xen_auth_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_auth_record),
       .member_count =
           sizeof(xen_auth_record_struct_members) / sizeof(struct_member),
       .members = xen_auth_record_struct_members
    };


void
xen_auth_record_free(xen_auth_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    
    free(record);
}


bool
xen_auth_get_subject_identifier(xen_session *session, char **result, char *subject_name)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject_name }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("auth.get_subject_identifier");
    return session->ok;
}


bool
xen_auth_get_subject_information_from_identifier(xen_session *session, xen_string_string_map **result, char *subject_identifier)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject_identifier }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("auth.get_subject_information_from_identifier");
    return session->ok;
}


bool
xen_auth_get_group_membership(xen_session *session, struct xen_string_set **result, char *subject_identifier)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = subject_identifier }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("auth.get_group_membership");
    return session->ok;
}

