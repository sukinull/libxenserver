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
#include "xen_network_default_locking_mode_internal.h"
#include "xen_network_operations_internal.h"
#include "xen_string_network_operations_map_internal.h"
#include <xen/api/xen_blob.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_network.h>
#include <xen/api/xen_network_operations.h>
#include <xen/api/xen_network_xen_network_record_map.h>
#include <xen/api/xen_pif.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_network_operations_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vif.h>


XEN_FREE(xen_network)
XEN_SET_ALLOC_FREE(xen_network)
XEN_ALLOC(xen_network_record)
XEN_SET_ALLOC_FREE(xen_network_record)
XEN_ALLOC(xen_network_record_opt)
XEN_RECORD_OPT_FREE(xen_network)
XEN_SET_ALLOC_FREE(xen_network_record_opt)


static const struct_member xen_network_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_network_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_network_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_network_record, name_description) },
        { .key = "allowed_operations",
          .type = &xen_network_operations_set_abstract_type_,
          .offset = offsetof(xen_network_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_network_operations_map_abstract_type_,
          .offset = offsetof(xen_network_record, current_operations) },
        { .key = "VIFs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_network_record, vifs) },
        { .key = "PIFs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_network_record, pifs) },
        { .key = "MTU",
          .type = &abstract_type_int,
          .offset = offsetof(xen_network_record, mtu) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_network_record, other_config) },
        { .key = "bridge",
          .type = &abstract_type_string,
          .offset = offsetof(xen_network_record, bridge) },
        { .key = "blobs",
          .type = &abstract_type_string_ref_map,
          .offset = offsetof(xen_network_record, blobs) },
        { .key = "tags",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_network_record, tags) },
        { .key = "default_locking_mode",
          .type = &xen_network_default_locking_mode_abstract_type_,
          .offset = offsetof(xen_network_record, default_locking_mode) }
    };

const abstract_type xen_network_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_network_record),
       .member_count =
           sizeof(xen_network_record_struct_members) / sizeof(struct_member),
       .members = xen_network_record_struct_members
    };


static const struct struct_member xen_network_xen_network_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_network_xen_network_record_map_contents, key)
    },
    {
        .type = &xen_network_record_abstract_type_,
        .offset = offsetof(xen_network_xen_network_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_network_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_network_xen_network_record_map_contents),
    .members = xen_network_xen_network_record_members
};


void
xen_network_record_free(xen_network_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_network_operations_set_free(record->allowed_operations);
    xen_string_network_operations_map_free(record->current_operations);
    xen_vif_record_opt_set_free(record->vifs);
    xen_pif_record_opt_set_free(record->pifs);
    xen_string_string_map_free(record->other_config);
    free(record->bridge);
    xen_string_blob_map_free(record->blobs);
    xen_string_set_free(record->tags);
    free(record);
}


bool
xen_network_get_record(xen_session *session, xen_network_record **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = xen_network_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("network.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_network_get_by_uuid(xen_session *session, xen_network *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("network.get_by_uuid");
    return session->ok;
}


bool
xen_network_create(xen_session *session, xen_network *result, xen_network_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_network_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("network.create");
    return session->ok;
}

bool
xen_network_create_async(xen_session *session, xen_task *result, xen_network_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_network_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.network.create");
    return session->ok;
}

bool
xen_network_destroy(xen_session *session, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    xen_call_(session, "network.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_network_destroy_async(xen_session *session, xen_task *result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.network.destroy");
    return session->ok;
}

bool
xen_network_get_by_name_label(xen_session *session, struct xen_network_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("network.get_by_name_label");
    return session->ok;
}


bool
xen_network_get_name_label(xen_session *session, char **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("network.get_name_label");
    return session->ok;
}


bool
xen_network_get_name_description(xen_session *session, char **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("network.get_name_description");
    return session->ok;
}


bool
xen_network_get_allowed_operations(xen_session *session, struct xen_network_operations_set **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = xen_network_operations_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("network.get_allowed_operations");
    return session->ok;
}


bool
xen_network_get_current_operations(xen_session *session, xen_string_network_operations_map **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = string_network_operations_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("network.get_current_operations");
    return session->ok;
}


bool
xen_network_get_vifs(xen_session *session, struct xen_vif_set **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("network.get_VIFs");
    return session->ok;
}


bool
xen_network_get_pifs(xen_session *session, struct xen_pif_set **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("network.get_PIFs");
    return session->ok;
}


bool
xen_network_get_mtu(xen_session *session, int64_t *result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("network.get_MTU");
    return session->ok;
}


bool
xen_network_get_other_config(xen_session *session, xen_string_string_map **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("network.get_other_config");
    return session->ok;
}


bool
xen_network_get_bridge(xen_session *session, char **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("network.get_bridge");
    return session->ok;
}


bool
xen_network_get_blobs(xen_session *session, xen_string_blob_map **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("network.get_blobs");
    return session->ok;
}


bool
xen_network_get_tags(xen_session *session, struct xen_string_set **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("network.get_tags");
    return session->ok;
}


bool
xen_network_get_default_locking_mode(xen_session *session, enum xen_network_default_locking_mode *result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = xen_network_default_locking_mode_abstract_type_;
    XEN_CALL_("network.get_default_locking_mode");
    return session->ok;
}


bool
xen_network_set_name_label(xen_session *session, xen_network network, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    xen_call_(session, "network.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_set_name_description(xen_session *session, xen_network network, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    xen_call_(session, "network.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_set_mtu(xen_session *session, xen_network network, int64_t mtu)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_int,
              .u.int_val = mtu }
        };

    xen_call_(session, "network.set_MTU", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_set_other_config(xen_session *session, xen_network network, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "network.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_add_to_other_config(xen_session *session, xen_network network, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "network.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_network_remove_from_other_config(xen_session *session, xen_network network, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "network.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_set_tags(xen_session *session, xen_network network, struct xen_string_set *tags)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)tags }
        };

    xen_call_(session, "network.set_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_add_tags(xen_session *session, xen_network network, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "network.add_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_remove_tags(xen_session *session, xen_network network, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "network.remove_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_network_create_new_blob(xen_session *session, xen_blob *result, xen_network network, char *name, char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("network.create_new_blob");
    return session->ok;
}

bool
xen_network_create_new_blob_async(xen_session *session, xen_task *result, xen_network network, char *name, char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.network.create_new_blob");
    return session->ok;
}

bool
xen_network_set_default_locking_mode(xen_session *session, xen_network network, enum xen_network_default_locking_mode value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &xen_network_default_locking_mode_abstract_type_,
              .u.enum_val = value }
        };

    xen_call_(session, "network.set_default_locking_mode", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_network_set_default_locking_mode_async(xen_session *session, xen_task *result, xen_network network, enum xen_network_default_locking_mode value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &xen_network_default_locking_mode_abstract_type_,
              .u.enum_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.network.set_default_locking_mode");
    return session->ok;
}

bool
xen_network_get_all(xen_session *session, struct xen_network_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "network.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_network_get_all_records(xen_session *session, xen_network_xen_network_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_network_record_map;

    *result = NULL;
    xen_call_(session, "network.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_network_get_uuid(xen_session *session, char **result, xen_network network)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("network.get_uuid");
    return session->ok;
}

