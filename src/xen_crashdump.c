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
#include <xen/api/xen_crashdump.h>
#include <xen/api/xen_crashdump_xen_crashdump_record_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vdi.h>
#include <xen/api/xen_vm.h>


XEN_FREE(xen_crashdump)
XEN_SET_ALLOC_FREE(xen_crashdump)
XEN_ALLOC(xen_crashdump_record)
XEN_SET_ALLOC_FREE(xen_crashdump_record)
XEN_ALLOC(xen_crashdump_record_opt)
XEN_RECORD_OPT_FREE(xen_crashdump)
XEN_SET_ALLOC_FREE(xen_crashdump_record_opt)


static const struct_member xen_crashdump_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_crashdump_record, uuid) },
        { .key = "VM",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_crashdump_record, vm) },
        { .key = "VDI",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_crashdump_record, vdi) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_crashdump_record, other_config) }
    };

const abstract_type xen_crashdump_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_crashdump_record),
       .member_count =
           sizeof(xen_crashdump_record_struct_members) / sizeof(struct_member),
       .members = xen_crashdump_record_struct_members
    };


static const struct struct_member xen_crashdump_xen_crashdump_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_crashdump_xen_crashdump_record_map_contents, key)
    },
    {
        .type = &xen_crashdump_record_abstract_type_,
        .offset = offsetof(xen_crashdump_xen_crashdump_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_crashdump_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_crashdump_xen_crashdump_record_map_contents),
    .members = xen_crashdump_xen_crashdump_record_members
};


void
xen_crashdump_record_free(xen_crashdump_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_vm_record_opt_free(record->vm);
    xen_vdi_record_opt_free(record->vdi);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_crashdump_get_record(xen_session *session, xen_crashdump_record **result, xen_crashdump crashdump)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump }
        };

    abstract_type result_type = xen_crashdump_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("crashdump.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_crashdump_get_by_uuid(xen_session *session, xen_crashdump *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("crashdump.get_by_uuid");
    return session->ok;
}


bool
xen_crashdump_get_vm(xen_session *session, xen_vm *result, xen_crashdump crashdump)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("crashdump.get_VM");
    return session->ok;
}


bool
xen_crashdump_get_vdi(xen_session *session, xen_vdi *result, xen_crashdump crashdump)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("crashdump.get_VDI");
    return session->ok;
}


bool
xen_crashdump_get_other_config(xen_session *session, xen_string_string_map **result, xen_crashdump crashdump)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("crashdump.get_other_config");
    return session->ok;
}


bool
xen_crashdump_set_other_config(xen_session *session, xen_crashdump crashdump, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "crashdump.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_crashdump_add_to_other_config(xen_session *session, xen_crashdump crashdump, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "crashdump.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_crashdump_remove_from_other_config(xen_session *session, xen_crashdump crashdump, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "crashdump.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_crashdump_destroy(xen_session *session, xen_crashdump self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "crashdump.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_crashdump_destroy_async(xen_session *session, xen_task *result, xen_crashdump self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.crashdump.destroy");
    return session->ok;
}

bool
xen_crashdump_get_all(xen_session *session, struct xen_crashdump_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "crashdump.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_crashdump_get_all_records(xen_session *session, xen_crashdump_xen_crashdump_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_crashdump_record_map;

    *result = NULL;
    xen_call_(session, "crashdump.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_crashdump_get_uuid(xen_session *session, char **result, xen_crashdump crashdump)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = crashdump }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("crashdump.get_uuid");
    return session->ok;
}

