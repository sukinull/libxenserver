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
#include <xen/api/xen_common.h>
#include <xen/api/xen_vm.h>
#include <xen/api/xen_vtpm.h>


XEN_FREE(xen_vtpm)
XEN_SET_ALLOC_FREE(xen_vtpm)
XEN_ALLOC(xen_vtpm_record)
XEN_SET_ALLOC_FREE(xen_vtpm_record)
XEN_ALLOC(xen_vtpm_record_opt)
XEN_RECORD_OPT_FREE(xen_vtpm)
XEN_SET_ALLOC_FREE(xen_vtpm_record_opt)


static const struct_member xen_vtpm_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vtpm_record, uuid) },
        { .key = "VM",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vtpm_record, vm) },
        { .key = "backend",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vtpm_record, backend) }
    };

const abstract_type xen_vtpm_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_vtpm_record),
       .member_count =
           sizeof(xen_vtpm_record_struct_members) / sizeof(struct_member),
       .members = xen_vtpm_record_struct_members
    };


void
xen_vtpm_record_free(xen_vtpm_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_vm_record_opt_free(record->vm);
    xen_vm_record_opt_free(record->backend);
    free(record);
}


bool
xen_vtpm_get_record(xen_session *session, xen_vtpm_record **result, xen_vtpm vtpm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vtpm }
        };

    abstract_type result_type = xen_vtpm_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VTPM.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_vtpm_get_by_uuid(xen_session *session, xen_vtpm *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VTPM.get_by_uuid");
    return session->ok;
}


bool
xen_vtpm_create(xen_session *session, xen_vtpm *result, xen_vtpm_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vtpm_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VTPM.create");
    return session->ok;
}

bool
xen_vtpm_create_async(xen_session *session, xen_task *result, xen_vtpm_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vtpm_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VTPM.create");
    return session->ok;
}

bool
xen_vtpm_destroy(xen_session *session, xen_vtpm vtpm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vtpm }
        };

    xen_call_(session, "VTPM.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vtpm_destroy_async(xen_session *session, xen_task *result, xen_vtpm vtpm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vtpm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VTPM.destroy");
    return session->ok;
}

bool
xen_vtpm_get_vm(xen_session *session, xen_vm *result, xen_vtpm vtpm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vtpm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VTPM.get_VM");
    return session->ok;
}


bool
xen_vtpm_get_backend(xen_session *session, xen_vm *result, xen_vtpm vtpm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vtpm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VTPM.get_backend");
    return session->ok;
}


bool
xen_vtpm_get_uuid(xen_session *session, char **result, xen_vtpm vtpm)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vtpm }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VTPM.get_uuid");
    return session->ok;
}

