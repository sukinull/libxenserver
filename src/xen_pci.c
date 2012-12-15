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
#include <xen/api/xen_host.h>
#include <xen/api/xen_pci.h>
#include <xen/api/xen_pci_xen_pci_record_map.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_pci)
XEN_SET_ALLOC_FREE(xen_pci)
XEN_ALLOC(xen_pci_record)
XEN_SET_ALLOC_FREE(xen_pci_record)
XEN_ALLOC(xen_pci_record_opt)
XEN_RECORD_OPT_FREE(xen_pci)
XEN_SET_ALLOC_FREE(xen_pci_record_opt)


static const struct_member xen_pci_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pci_record, uuid) },
        { .key = "class_name",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pci_record, class_name) },
        { .key = "vendor_name",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pci_record, vendor_name) },
        { .key = "device_name",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pci_record, device_name) },
        { .key = "host",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pci_record, host) },
        { .key = "pci_id",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pci_record, pci_id) },
        { .key = "dependencies",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_pci_record, dependencies) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_pci_record, other_config) }
    };

const abstract_type xen_pci_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_pci_record),
       .member_count =
           sizeof(xen_pci_record_struct_members) / sizeof(struct_member),
       .members = xen_pci_record_struct_members
    };


static const struct struct_member xen_pci_xen_pci_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_pci_xen_pci_record_map_contents, key)
    },
    {
        .type = &xen_pci_record_abstract_type_,
        .offset = offsetof(xen_pci_xen_pci_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_pci_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_pci_xen_pci_record_map_contents),
    .members = xen_pci_xen_pci_record_members
};


void
xen_pci_record_free(xen_pci_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->class_name);
    free(record->vendor_name);
    free(record->device_name);
    xen_host_record_opt_free(record->host);
    free(record->pci_id);
    xen_pci_record_opt_set_free(record->dependencies);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_pci_get_record(xen_session *session, xen_pci_record **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = xen_pci_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("PCI.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_pci_get_by_uuid(xen_session *session, xen_pci *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PCI.get_by_uuid");
    return session->ok;
}


bool
xen_pci_get_class_name(xen_session *session, char **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PCI.get_class_name");
    return session->ok;
}


bool
xen_pci_get_vendor_name(xen_session *session, char **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PCI.get_vendor_name");
    return session->ok;
}


bool
xen_pci_get_device_name(xen_session *session, char **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PCI.get_device_name");
    return session->ok;
}


bool
xen_pci_get_host(xen_session *session, xen_host *result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PCI.get_host");
    return session->ok;
}


bool
xen_pci_get_pci_id(xen_session *session, char **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PCI.get_pci_id");
    return session->ok;
}


bool
xen_pci_get_dependencies(xen_session *session, struct xen_pci_set **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("PCI.get_dependencies");
    return session->ok;
}


bool
xen_pci_get_other_config(xen_session *session, xen_string_string_map **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("PCI.get_other_config");
    return session->ok;
}


bool
xen_pci_set_other_config(xen_session *session, xen_pci pci, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "PCI.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pci_add_to_other_config(xen_session *session, xen_pci pci, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "PCI.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_pci_remove_from_other_config(xen_session *session, xen_pci pci, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "PCI.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pci_get_all(xen_session *session, struct xen_pci_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "PCI.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pci_get_all_records(xen_session *session, xen_pci_xen_pci_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_pci_record_map;

    *result = NULL;
    xen_call_(session, "PCI.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pci_get_uuid(xen_session *session, char **result, xen_pci pci)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pci }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PCI.get_uuid");
    return session->ok;
}

