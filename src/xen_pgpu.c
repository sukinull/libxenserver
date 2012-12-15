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
#include <xen/api/xen_gpu_group.h>
#include <xen/api/xen_host.h>
#include <xen/api/xen_pci.h>
#include <xen/api/xen_pgpu.h>
#include <xen/api/xen_pgpu_xen_pgpu_record_map.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_pgpu)
XEN_SET_ALLOC_FREE(xen_pgpu)
XEN_ALLOC(xen_pgpu_record)
XEN_SET_ALLOC_FREE(xen_pgpu_record)
XEN_ALLOC(xen_pgpu_record_opt)
XEN_RECORD_OPT_FREE(xen_pgpu)
XEN_SET_ALLOC_FREE(xen_pgpu_record_opt)


static const struct_member xen_pgpu_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pgpu_record, uuid) },
        { .key = "PCI",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pgpu_record, pci) },
        { .key = "GPU_group",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pgpu_record, gpu_group) },
        { .key = "host",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pgpu_record, host) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_pgpu_record, other_config) }
    };

const abstract_type xen_pgpu_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_pgpu_record),
       .member_count =
           sizeof(xen_pgpu_record_struct_members) / sizeof(struct_member),
       .members = xen_pgpu_record_struct_members
    };


static const struct struct_member xen_pgpu_xen_pgpu_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_pgpu_xen_pgpu_record_map_contents, key)
    },
    {
        .type = &xen_pgpu_record_abstract_type_,
        .offset = offsetof(xen_pgpu_xen_pgpu_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_pgpu_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_pgpu_xen_pgpu_record_map_contents),
    .members = xen_pgpu_xen_pgpu_record_members
};


void
xen_pgpu_record_free(xen_pgpu_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_pci_record_opt_free(record->pci);
    xen_gpu_group_record_opt_free(record->gpu_group);
    xen_host_record_opt_free(record->host);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_pgpu_get_record(xen_session *session, xen_pgpu_record **result, xen_pgpu pgpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu }
        };

    abstract_type result_type = xen_pgpu_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("PGPU.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_pgpu_get_by_uuid(xen_session *session, xen_pgpu *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PGPU.get_by_uuid");
    return session->ok;
}


bool
xen_pgpu_get_pci(xen_session *session, xen_pci *result, xen_pgpu pgpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PGPU.get_PCI");
    return session->ok;
}


bool
xen_pgpu_get_gpu_group(xen_session *session, xen_gpu_group *result, xen_pgpu pgpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PGPU.get_GPU_group");
    return session->ok;
}


bool
xen_pgpu_get_host(xen_session *session, xen_host *result, xen_pgpu pgpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PGPU.get_host");
    return session->ok;
}


bool
xen_pgpu_get_other_config(xen_session *session, xen_string_string_map **result, xen_pgpu pgpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("PGPU.get_other_config");
    return session->ok;
}


bool
xen_pgpu_set_other_config(xen_session *session, xen_pgpu pgpu, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "PGPU.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pgpu_add_to_other_config(xen_session *session, xen_pgpu pgpu, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "PGPU.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_pgpu_remove_from_other_config(xen_session *session, xen_pgpu pgpu, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "PGPU.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pgpu_get_all(xen_session *session, struct xen_pgpu_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "PGPU.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pgpu_get_all_records(xen_session *session, xen_pgpu_xen_pgpu_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_pgpu_record_map;

    *result = NULL;
    xen_call_(session, "PGPU.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pgpu_get_uuid(xen_session *session, char **result, xen_pgpu pgpu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pgpu }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PGPU.get_uuid");
    return session->ok;
}

