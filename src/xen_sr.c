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
#include "xen_storage_operations_internal.h"
#include "xen_string_storage_operations_map_internal.h"
#include <xen/api/xen_blob.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_dr_task.h>
#include <xen/api/xen_host.h>
#include <xen/api/xen_pbd.h>
#include <xen/api/xen_sr.h>
#include <xen/api/xen_sr_xen_sr_record_map.h>
#include <xen/api/xen_storage_operations.h>
#include <xen/api/xen_string_blob_map.h>
#include <xen/api/xen_string_storage_operations_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vdi.h>


XEN_FREE(xen_sr)
XEN_SET_ALLOC_FREE(xen_sr)
XEN_ALLOC(xen_sr_record)
XEN_SET_ALLOC_FREE(xen_sr_record)
XEN_ALLOC(xen_sr_record_opt)
XEN_RECORD_OPT_FREE(xen_sr)
XEN_SET_ALLOC_FREE(xen_sr_record_opt)


static const struct_member xen_sr_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sr_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sr_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sr_record, name_description) },
        { .key = "allowed_operations",
          .type = &xen_storage_operations_set_abstract_type_,
          .offset = offsetof(xen_sr_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_storage_operations_map_abstract_type_,
          .offset = offsetof(xen_sr_record, current_operations) },
        { .key = "VDIs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_sr_record, vdis) },
        { .key = "PBDs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_sr_record, pbds) },
        { .key = "virtual_allocation",
          .type = &abstract_type_int,
          .offset = offsetof(xen_sr_record, virtual_allocation) },
        { .key = "physical_utilisation",
          .type = &abstract_type_int,
          .offset = offsetof(xen_sr_record, physical_utilisation) },
        { .key = "physical_size",
          .type = &abstract_type_int,
          .offset = offsetof(xen_sr_record, physical_size) },
        { .key = "type",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sr_record, type) },
        { .key = "content_type",
          .type = &abstract_type_string,
          .offset = offsetof(xen_sr_record, content_type) },
        { .key = "shared",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_sr_record, shared) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_sr_record, other_config) },
        { .key = "tags",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_sr_record, tags) },
        { .key = "sm_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_sr_record, sm_config) },
        { .key = "blobs",
          .type = &abstract_type_string_ref_map,
          .offset = offsetof(xen_sr_record, blobs) },
        { .key = "local_cache_enabled",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_sr_record, local_cache_enabled) },
        { .key = "introduced_by",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_sr_record, introduced_by) }
    };

const abstract_type xen_sr_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_sr_record),
       .member_count =
           sizeof(xen_sr_record_struct_members) / sizeof(struct_member),
       .members = xen_sr_record_struct_members
    };


static const struct struct_member xen_sr_xen_sr_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_sr_xen_sr_record_map_contents, key)
    },
    {
        .type = &xen_sr_record_abstract_type_,
        .offset = offsetof(xen_sr_xen_sr_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_sr_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_sr_xen_sr_record_map_contents),
    .members = xen_sr_xen_sr_record_members
};


void
xen_sr_record_free(xen_sr_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_storage_operations_set_free(record->allowed_operations);
    xen_string_storage_operations_map_free(record->current_operations);
    xen_vdi_record_opt_set_free(record->vdis);
    xen_pbd_record_opt_set_free(record->pbds);
    free(record->type);
    free(record->content_type);
    xen_string_string_map_free(record->other_config);
    xen_string_set_free(record->tags);
    xen_string_string_map_free(record->sm_config);
    xen_string_blob_map_free(record->blobs);
    xen_dr_task_record_opt_free(record->introduced_by);
    free(record);
}


bool
xen_sr_get_record(xen_session *session, xen_sr_record **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = xen_sr_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("SR.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_opaque_strdup_(sr);
    }

    return session->ok;
}


bool
xen_sr_get_by_uuid(xen_session *session, xen_sr *result, const char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.get_by_uuid");
    return session->ok;
}


bool
xen_sr_get_by_name_label(xen_session *session, struct xen_sr_set **result, const char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("SR.get_by_name_label");
    return session->ok;
}


bool
xen_sr_get_name_label(xen_session *session, char **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.get_name_label");
    return session->ok;
}


bool
xen_sr_get_name_description(xen_session *session, char **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.get_name_description");
    return session->ok;
}


bool
xen_sr_get_allowed_operations(xen_session *session, struct xen_storage_operations_set **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = xen_storage_operations_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("SR.get_allowed_operations");
    return session->ok;
}


bool
xen_sr_get_current_operations(xen_session *session, xen_string_storage_operations_map **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = string_storage_operations_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("SR.get_current_operations");
    return session->ok;
}


bool
xen_sr_get_vdis(xen_session *session, struct xen_vdi_set **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("SR.get_VDIs");
    return session->ok;
}


bool
xen_sr_get_pbds(xen_session *session, struct xen_pbd_set **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("SR.get_PBDs");
    return session->ok;
}


bool
xen_sr_get_virtual_allocation(xen_session *session, int64_t *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("SR.get_virtual_allocation");
    return session->ok;
}


bool
xen_sr_get_physical_utilisation(xen_session *session, int64_t *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("SR.get_physical_utilisation");
    return session->ok;
}


bool
xen_sr_get_physical_size(xen_session *session, int64_t *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("SR.get_physical_size");
    return session->ok;
}


bool
xen_sr_get_type(xen_session *session, char **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.get_type");
    return session->ok;
}


bool
xen_sr_get_content_type(xen_session *session, char **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.get_content_type");
    return session->ok;
}


bool
xen_sr_get_shared(xen_session *session, bool *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("SR.get_shared");
    return session->ok;
}


bool
xen_sr_get_other_config(xen_session *session, xen_string_string_map **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("SR.get_other_config");
    return session->ok;
}


bool
xen_sr_get_tags(xen_session *session, struct xen_string_set **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("SR.get_tags");
    return session->ok;
}


bool
xen_sr_get_sm_config(xen_session *session, xen_string_string_map **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("SR.get_sm_config");
    return session->ok;
}


bool
xen_sr_get_blobs(xen_session *session, xen_string_blob_map **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("SR.get_blobs");
    return session->ok;
}


bool
xen_sr_get_local_cache_enabled(xen_session *session, bool *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("SR.get_local_cache_enabled");
    return session->ok;
}


bool
xen_sr_get_introduced_by(xen_session *session, xen_dr_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.get_introduced_by");
    return session->ok;
}


bool
xen_sr_set_other_config(xen_session *session, xen_sr sr, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "SR.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_add_to_other_config(xen_session *session, xen_sr sr, const char *key, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "SR.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_sr_remove_from_other_config(xen_session *session, xen_sr sr, const char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "SR.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_set_tags(xen_session *session, xen_sr sr, struct xen_string_set *tags)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)tags }
        };

    xen_call_(session, "SR.set_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_add_tags(xen_session *session, xen_sr sr, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "SR.add_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_remove_tags(xen_session *session, xen_sr sr, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "SR.remove_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_set_sm_config(xen_session *session, xen_sr sr, xen_string_string_map *sm_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config }
        };

    xen_call_(session, "SR.set_sm_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_add_to_sm_config(xen_session *session, xen_sr sr, const char *key, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "SR.add_to_sm_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_sr_remove_from_sm_config(xen_session *session, xen_sr sr, const char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "SR.remove_from_sm_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_create(xen_session *session, xen_sr *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared, xen_string_string_map *sm_config)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = host },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)device_config },
                { .type = &abstract_type_int,
                  .u.int_val = physical_size },
                { .type = &abstract_type_string,
                  .u.string_val = name_label },
                { .type = &abstract_type_string,
                  .u.string_val = name_description },
                { .type = &abstract_type_string,
                  .u.string_val = type },
                { .type = &abstract_type_string,
                  .u.string_val = content_type },
                { .type = &abstract_type_bool,
                  .u.bool_val = shared },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)sm_config }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("SR.create");
        return session->ok;
    }
    else
    {
        return xen_sr_create_1_1(session, result, host, device_config, physical_size, name_label, name_description, type, content_type, shared);
    }
}

bool
xen_sr_create_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared, xen_string_string_map *sm_config)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = host },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)device_config },
                { .type = &abstract_type_int,
                  .u.int_val = physical_size },
                { .type = &abstract_type_string,
                  .u.string_val = name_label },
                { .type = &abstract_type_string,
                  .u.string_val = name_description },
                { .type = &abstract_type_string,
                  .u.string_val = type },
                { .type = &abstract_type_string,
                  .u.string_val = content_type },
                { .type = &abstract_type_bool,
                  .u.bool_val = shared },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)sm_config }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("Async.SR.create");
        return session->ok;
    }
    else
    {
        return xen_sr_create_1_1_async(session, result, host, device_config, physical_size, name_label, name_description, type, content_type, shared);
    }
}


/**
 * SR.create for API version 1.1.
 */
bool
xen_sr_create_1_1(xen_session *session, xen_sr *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_int,
              .u.int_val = physical_size },
            { .type = &abstract_type_string,
              .u.string_val = name_label },
            { .type = &abstract_type_string,
              .u.string_val = name_description },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = content_type },
            { .type = &abstract_type_bool,
              .u.bool_val = shared },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.create");
    return session->ok;
}


/**
 * SR.create for API version 1.1.
 */
bool
xen_sr_create_1_1_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_int,
              .u.int_val = physical_size },
            { .type = &abstract_type_string,
              .u.string_val = name_label },
            { .type = &abstract_type_string,
              .u.string_val = name_description },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = content_type },
            { .type = &abstract_type_bool,
              .u.bool_val = shared },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.create");
    return session->ok;
}


bool
xen_sr_introduce(xen_session *session, xen_sr *result, const char *uuid, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared, xen_string_string_map *sm_config)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = uuid },
                { .type = &abstract_type_string,
                  .u.string_val = name_label },
                { .type = &abstract_type_string,
                  .u.string_val = name_description },
                { .type = &abstract_type_string,
                  .u.string_val = type },
                { .type = &abstract_type_string,
                  .u.string_val = content_type },
                { .type = &abstract_type_bool,
                  .u.bool_val = shared },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)sm_config }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("SR.introduce");
        return session->ok;
    }
    else
    {
        return xen_sr_introduce_1_1(session, result, uuid, name_label, name_description, type, content_type, shared);
    }
}

bool
xen_sr_introduce_async(xen_session *session, xen_task *result, const char *uuid, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared, xen_string_string_map *sm_config)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = uuid },
                { .type = &abstract_type_string,
                  .u.string_val = name_label },
                { .type = &abstract_type_string,
                  .u.string_val = name_description },
                { .type = &abstract_type_string,
                  .u.string_val = type },
                { .type = &abstract_type_string,
                  .u.string_val = content_type },
                { .type = &abstract_type_bool,
                  .u.bool_val = shared },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)sm_config }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("Async.SR.introduce");
        return session->ok;
    }
    else
    {
        return xen_sr_introduce_1_1_async(session, result, uuid, name_label, name_description, type, content_type, shared);
    }
}


/**
 * SR.introduce for API version 1.1.
 */
bool
xen_sr_introduce_1_1(xen_session *session, xen_sr *result, const char *uuid, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid },
            { .type = &abstract_type_string,
              .u.string_val = name_label },
            { .type = &abstract_type_string,
              .u.string_val = name_description },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = content_type },
            { .type = &abstract_type_bool,
              .u.bool_val = shared },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.introduce");
    return session->ok;
}


/**
 * SR.introduce for API version 1.1.
 */
bool
xen_sr_introduce_1_1_async(xen_session *session, xen_task *result, const char *uuid, const char *name_label, const char *name_description, const char *type, const char *content_type, bool shared)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid },
            { .type = &abstract_type_string,
              .u.string_val = name_label },
            { .type = &abstract_type_string,
              .u.string_val = name_description },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = content_type },
            { .type = &abstract_type_bool,
              .u.bool_val = shared },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.introduce");
    return session->ok;
}


bool
xen_sr_make(xen_session *session, char **result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type, xen_string_string_map *sm_config)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = host },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)device_config },
                { .type = &abstract_type_int,
                  .u.int_val = physical_size },
                { .type = &abstract_type_string,
                  .u.string_val = name_label },
                { .type = &abstract_type_string,
                  .u.string_val = name_description },
                { .type = &abstract_type_string,
                  .u.string_val = type },
                { .type = &abstract_type_string,
                  .u.string_val = content_type },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)sm_config }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("SR.make");
        return session->ok;
    }
    else
    {
        return xen_sr_make_1_1(session, result, host, device_config, physical_size, name_label, name_description, type, content_type);
    }
}

bool
xen_sr_make_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type, xen_string_string_map *sm_config)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = host },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)device_config },
                { .type = &abstract_type_int,
                  .u.int_val = physical_size },
                { .type = &abstract_type_string,
                  .u.string_val = name_label },
                { .type = &abstract_type_string,
                  .u.string_val = name_description },
                { .type = &abstract_type_string,
                  .u.string_val = type },
                { .type = &abstract_type_string,
                  .u.string_val = content_type },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)sm_config }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("Async.SR.make");
        return session->ok;
    }
    else
    {
        return xen_sr_make_1_1_async(session, result, host, device_config, physical_size, name_label, name_description, type, content_type);
    }
}


/**
 * SR.make for API version 1.1.
 */
bool
xen_sr_make_1_1(xen_session *session, char **result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_int,
              .u.int_val = physical_size },
            { .type = &abstract_type_string,
              .u.string_val = name_label },
            { .type = &abstract_type_string,
              .u.string_val = name_description },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = content_type },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.make");
    return session->ok;
}


/**
 * SR.make for API version 1.1.
 */
bool
xen_sr_make_1_1_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, int64_t physical_size, const char *name_label, const char *name_description, const char *type, const char *content_type)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_int,
              .u.int_val = physical_size },
            { .type = &abstract_type_string,
              .u.string_val = name_label },
            { .type = &abstract_type_string,
              .u.string_val = name_description },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string,
              .u.string_val = content_type },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.make");
    return session->ok;
}

bool
xen_sr_destroy(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_destroy_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.destroy");
    return session->ok;
}

bool
xen_sr_forget(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.forget", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_forget_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.forget");
    return session->ok;
}

bool
xen_sr_update(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.update", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_update_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.update");
    return session->ok;
}

bool
xen_sr_get_supported_types(xen_session *session, struct xen_string_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "SR.get_supported_types", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_sr_scan(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.scan", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_scan_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.scan");
    return session->ok;
}

bool
xen_sr_probe(xen_session *session, char **result, xen_host host, xen_string_string_map *device_config, const char *type, xen_string_string_map *sm_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.probe");
    return session->ok;
}

bool
xen_sr_probe_async(xen_session *session, xen_task *result, xen_host host, xen_string_string_map *device_config, const char *type, xen_string_string_map *sm_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)device_config },
            { .type = &abstract_type_string,
              .u.string_val = type },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.probe");
    return session->ok;
}

bool
xen_sr_set_shared(xen_session *session, xen_sr sr, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "SR.set_shared", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_sr_set_shared_async(xen_session *session, xen_task *result, xen_sr sr, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.set_shared");
    return session->ok;
}

bool
xen_sr_set_name_label(xen_session *session, xen_sr sr, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "SR.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_sr_set_name_label_async(xen_session *session, xen_task *result, xen_sr sr, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.set_name_label");
    return session->ok;
}

bool
xen_sr_set_name_description(xen_session *session, xen_sr sr, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "SR.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_sr_set_name_description_async(xen_session *session, xen_task *result, xen_sr sr, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.set_name_description");
    return session->ok;
}

bool
xen_sr_create_new_blob(xen_session *session, xen_blob *result, xen_sr sr, const char *name, const char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.create_new_blob");
    return session->ok;
}

bool
xen_sr_create_new_blob_async(xen_session *session, xen_task *result, xen_sr sr, const char *name, const char *mime_type, bool pubblic)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = mime_type },
            { .type = &abstract_type_bool,
              .u.bool_val = pubblic }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.create_new_blob");
    return session->ok;
}

bool
xen_sr_set_physical_size(xen_session *session, xen_sr self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "SR.set_physical_size", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_set_virtual_allocation(xen_session *session, xen_sr self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "SR.set_virtual_allocation", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_set_physical_utilisation(xen_session *session, xen_sr self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "SR.set_physical_utilisation", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_sr_assert_can_host_ha_statefile(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.assert_can_host_ha_statefile", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_assert_can_host_ha_statefile_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.assert_can_host_ha_statefile");
    return session->ok;
}

bool
xen_sr_assert_supports_database_replication(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.assert_supports_database_replication", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_assert_supports_database_replication_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.assert_supports_database_replication");
    return session->ok;
}

bool
xen_sr_enable_database_replication(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.enable_database_replication", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_enable_database_replication_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.enable_database_replication");
    return session->ok;
}

bool
xen_sr_disable_database_replication(xen_session *session, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    xen_call_(session, "SR.disable_database_replication", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_sr_disable_database_replication_async(xen_session *session, xen_task *result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.SR.disable_database_replication");
    return session->ok;
}

bool
xen_sr_get_all(xen_session *session, struct xen_sr_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "SR.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_sr_get_all_records(xen_session *session, xen_sr_xen_sr_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_sr_record_map;

    *result = NULL;
    xen_call_(session, "SR.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_sr_get_uuid(xen_session *session, char **result, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("SR.get_uuid");
    return session->ok;
}

