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
#include "xen_on_boot_internal.h"
#include "xen_string_vdi_operations_map_internal.h"
#include "xen_vdi_operations_internal.h"
#include "xen_vdi_type_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_crashdump.h>
#include <xen/api/xen_pool.h>
#include <xen/api/xen_sr.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_vdi_operations_map.h>
#include <xen/api/xen_vbd.h>
#include <xen/api/xen_vdi.h>
#include <xen/api/xen_vdi_operations.h>
#include <xen/api/xen_vdi_xen_vdi_record_map.h>


XEN_FREE(xen_vdi)
XEN_SET_ALLOC_FREE(xen_vdi)
XEN_ALLOC(xen_vdi_record)
XEN_SET_ALLOC_FREE(xen_vdi_record)
XEN_ALLOC(xen_vdi_record_opt)
XEN_RECORD_OPT_FREE(xen_vdi)
XEN_SET_ALLOC_FREE(xen_vdi_record_opt)


static const struct_member xen_vdi_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vdi_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vdi_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vdi_record, name_description) },
        { .key = "allowed_operations",
          .type = &xen_vdi_operations_set_abstract_type_,
          .offset = offsetof(xen_vdi_record, allowed_operations) },
        { .key = "current_operations",
          .type = &string_vdi_operations_map_abstract_type_,
          .offset = offsetof(xen_vdi_record, current_operations) },
        { .key = "SR",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vdi_record, sr) },
        { .key = "VBDs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vdi_record, vbds) },
        { .key = "crash_dumps",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vdi_record, crash_dumps) },
        { .key = "virtual_size",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vdi_record, virtual_size) },
        { .key = "physical_utilisation",
          .type = &abstract_type_int,
          .offset = offsetof(xen_vdi_record, physical_utilisation) },
        { .key = "type",
          .type = &xen_vdi_type_abstract_type_,
          .offset = offsetof(xen_vdi_record, type) },
        { .key = "sharable",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, sharable) },
        { .key = "read_only",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, read_only) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vdi_record, other_config) },
        { .key = "storage_lock",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, storage_lock) },
        { .key = "location",
          .type = &abstract_type_string,
          .offset = offsetof(xen_vdi_record, location) },
        { .key = "managed",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, managed) },
        { .key = "missing",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, missing) },
        { .key = "parent",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vdi_record, parent) },
        { .key = "xenstore_data",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vdi_record, xenstore_data) },
        { .key = "sm_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_vdi_record, sm_config) },
        { .key = "is_a_snapshot",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, is_a_snapshot) },
        { .key = "snapshot_of",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vdi_record, snapshot_of) },
        { .key = "snapshots",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_vdi_record, snapshots) },
        { .key = "snapshot_time",
          .type = &abstract_type_datetime,
          .offset = offsetof(xen_vdi_record, snapshot_time) },
        { .key = "tags",
          .type = &abstract_type_string_set,
          .offset = offsetof(xen_vdi_record, tags) },
        { .key = "allow_caching",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, allow_caching) },
        { .key = "on_boot",
          .type = &xen_on_boot_abstract_type_,
          .offset = offsetof(xen_vdi_record, on_boot) },
        { .key = "metadata_of_pool",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_vdi_record, metadata_of_pool) },
        { .key = "metadata_latest",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_vdi_record, metadata_latest) }
    };

const abstract_type xen_vdi_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_vdi_record),
       .member_count =
           sizeof(xen_vdi_record_struct_members) / sizeof(struct_member),
       .members = xen_vdi_record_struct_members
    };


static const struct struct_member xen_vdi_xen_vdi_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_vdi_xen_vdi_record_map_contents, key)
    },
    {
        .type = &xen_vdi_record_abstract_type_,
        .offset = offsetof(xen_vdi_xen_vdi_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_vdi_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_vdi_xen_vdi_record_map_contents),
    .members = xen_vdi_xen_vdi_record_members
};


void
xen_vdi_record_free(xen_vdi_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_vdi_operations_set_free(record->allowed_operations);
    xen_string_vdi_operations_map_free(record->current_operations);
    xen_sr_record_opt_free(record->sr);
    xen_vbd_record_opt_set_free(record->vbds);
    xen_crashdump_record_opt_set_free(record->crash_dumps);
    xen_string_string_map_free(record->other_config);
    free(record->location);
    xen_vdi_record_opt_free(record->parent);
    xen_string_string_map_free(record->xenstore_data);
    xen_string_string_map_free(record->sm_config);
    xen_vdi_record_opt_free(record->snapshot_of);
    xen_vdi_record_opt_set_free(record->snapshots);
    xen_string_set_free(record->tags);
    xen_pool_record_opt_free(record->metadata_of_pool);
    free(record);
}


bool
xen_vdi_get_record(xen_session *session, xen_vdi_record **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = xen_vdi_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("VDI.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_opaque_strdup_(vdi);
    }

    return session->ok;
}


bool
xen_vdi_get_by_uuid(xen_session *session, xen_vdi *result, const char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_by_uuid");
    return session->ok;
}


bool
xen_vdi_create(xen_session *session, xen_vdi *result, const xen_vdi_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vdi_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.create");
    return session->ok;
}

bool
xen_vdi_create_async(xen_session *session, xen_task *result, const xen_vdi_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_vdi_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.create");
    return session->ok;
}

bool
xen_vdi_destroy(xen_session *session, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    xen_call_(session, "VDI.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_destroy_async(xen_session *session, xen_task *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.destroy");
    return session->ok;
}

bool
xen_vdi_get_by_name_label(xen_session *session, struct xen_vdi_set **result, const char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VDI.get_by_name_label");
    return session->ok;
}


bool
xen_vdi_get_name_label(xen_session *session, char **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_name_label");
    return session->ok;
}


bool
xen_vdi_get_name_description(xen_session *session, char **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_name_description");
    return session->ok;
}


bool
xen_vdi_get_allowed_operations(xen_session *session, struct xen_vdi_operations_set **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = xen_vdi_operations_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("VDI.get_allowed_operations");
    return session->ok;
}


bool
xen_vdi_get_current_operations(xen_session *session, xen_string_vdi_operations_map **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = string_vdi_operations_map_abstract_type_;

    *result = NULL;
    XEN_CALL_("VDI.get_current_operations");
    return session->ok;
}


bool
xen_vdi_get_sr(xen_session *session, xen_sr *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_SR");
    return session->ok;
}


bool
xen_vdi_get_vbds(xen_session *session, struct xen_vbd_set **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VDI.get_VBDs");
    return session->ok;
}


bool
xen_vdi_get_crash_dumps(xen_session *session, struct xen_crashdump_set **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VDI.get_crash_dumps");
    return session->ok;
}


bool
xen_vdi_get_virtual_size(xen_session *session, int64_t *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VDI.get_virtual_size");
    return session->ok;
}


bool
xen_vdi_get_physical_utilisation(xen_session *session, int64_t *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("VDI.get_physical_utilisation");
    return session->ok;
}


bool
xen_vdi_get_type(xen_session *session, enum xen_vdi_type *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = xen_vdi_type_abstract_type_;
    XEN_CALL_("VDI.get_type");
    return session->ok;
}


bool
xen_vdi_get_sharable(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_sharable");
    return session->ok;
}


bool
xen_vdi_get_read_only(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_read_only");
    return session->ok;
}


bool
xen_vdi_get_other_config(xen_session *session, xen_string_string_map **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VDI.get_other_config");
    return session->ok;
}


bool
xen_vdi_get_storage_lock(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_storage_lock");
    return session->ok;
}


bool
xen_vdi_get_location(xen_session *session, char **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_location");
    return session->ok;
}


bool
xen_vdi_get_managed(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_managed");
    return session->ok;
}


bool
xen_vdi_get_missing(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_missing");
    return session->ok;
}


bool
xen_vdi_get_parent(xen_session *session, xen_vdi *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_parent");
    return session->ok;
}


bool
xen_vdi_get_xenstore_data(xen_session *session, xen_string_string_map **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VDI.get_xenstore_data");
    return session->ok;
}


bool
xen_vdi_get_sm_config(xen_session *session, xen_string_string_map **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("VDI.get_sm_config");
    return session->ok;
}


bool
xen_vdi_get_is_a_snapshot(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_is_a_snapshot");
    return session->ok;
}


bool
xen_vdi_get_snapshot_of(xen_session *session, xen_vdi *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_snapshot_of");
    return session->ok;
}


bool
xen_vdi_get_snapshots(xen_session *session, struct xen_vdi_set **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VDI.get_snapshots");
    return session->ok;
}


bool
xen_vdi_get_snapshot_time(xen_session *session, time_t *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_datetime;

    XEN_CALL_("VDI.get_snapshot_time");
    return session->ok;
}


bool
xen_vdi_get_tags(xen_session *session, struct xen_string_set **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("VDI.get_tags");
    return session->ok;
}


bool
xen_vdi_get_allow_caching(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_allow_caching");
    return session->ok;
}


bool
xen_vdi_get_on_boot(xen_session *session, enum xen_on_boot *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = xen_on_boot_abstract_type_;
    XEN_CALL_("VDI.get_on_boot");
    return session->ok;
}


bool
xen_vdi_get_metadata_of_pool(xen_session *session, xen_pool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_metadata_of_pool");
    return session->ok;
}


bool
xen_vdi_get_metadata_latest(xen_session *session, bool *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("VDI.get_metadata_latest");
    return session->ok;
}


bool
xen_vdi_set_other_config(xen_session *session, xen_vdi vdi, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "VDI.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_add_to_other_config(xen_session *session, xen_vdi vdi, const char *key, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_remove_from_other_config(xen_session *session, xen_vdi vdi, const char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VDI.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_xenstore_data(xen_session *session, xen_vdi vdi, xen_string_string_map *xenstore_data)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)xenstore_data }
        };

    xen_call_(session, "VDI.set_xenstore_data", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_add_to_xenstore_data(xen_session *session, xen_vdi vdi, const char *key, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.add_to_xenstore_data", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_remove_from_xenstore_data(xen_session *session, xen_vdi vdi, const char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VDI.remove_from_xenstore_data", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_sm_config(xen_session *session, xen_vdi vdi, xen_string_string_map *sm_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config }
        };

    xen_call_(session, "VDI.set_sm_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_add_to_sm_config(xen_session *session, xen_vdi vdi, const char *key, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.add_to_sm_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_remove_from_sm_config(xen_session *session, xen_vdi vdi, const char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "VDI.remove_from_sm_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_tags(xen_session *session, xen_vdi vdi, struct xen_string_set *tags)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)tags }
        };

    xen_call_(session, "VDI.set_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_add_tags(xen_session *session, xen_vdi vdi, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.add_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_remove_tags(xen_session *session, xen_vdi vdi, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.remove_tags", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_snapshot(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_string_string_map *driver_params)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = vdi },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)driver_params }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("VDI.snapshot");
        return session->ok;
    }
    else
    {
        return xen_vdi_snapshot_1_1(session, result, vdi);
    }
}

bool
xen_vdi_snapshot_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_string_string_map *driver_params)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = vdi },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)driver_params }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("Async.VDI.snapshot");
        return session->ok;
    }
    else
    {
        return xen_vdi_snapshot_1_1_async(session, result, vdi);
    }
}


/**
 * VDI.snapshot for API version 1.1.
 */
bool
xen_vdi_snapshot_1_1(xen_session *session, xen_vdi *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.snapshot");
    return session->ok;
}


/**
 * VDI.snapshot for API version 1.1.
 */
bool
xen_vdi_snapshot_1_1_async(xen_session *session, xen_task *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.snapshot");
    return session->ok;
}


bool
xen_vdi_clone(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_string_string_map *driver_params)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = vdi },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)driver_params }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("VDI.clone");
        return session->ok;
    }
    else
    {
        return xen_vdi_clone_1_1(session, result, vdi);
    }
}

bool
xen_vdi_clone_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_string_string_map *driver_params)
{
    if (session->api_version == xen_api_version_1_2)
    {
        abstract_value param_values[] =
            {
                { .type = &abstract_type_string,
                  .u.string_val = vdi },
                { .type = &abstract_type_string_string_map,
                  .u.set_val = (arbitrary_set *)driver_params }
            };

        abstract_type result_type = abstract_type_string;

        *result = NULL;
        XEN_CALL_("Async.VDI.clone");
        return session->ok;
    }
    else
    {
        return xen_vdi_clone_1_1_async(session, result, vdi);
    }
}


bool
xen_vdi_clone_1_1(xen_session *session, xen_vdi *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.clone");
    return session->ok;
}


bool
xen_vdi_clone_1_1_async(xen_session *session, xen_task *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.clone");
    return session->ok;
}


bool
xen_vdi_resize(xen_session *session, xen_vdi vdi, int64_t size)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_int,
              .u.int_val = size }
        };

    xen_call_(session, "VDI.resize", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_resize_async(xen_session *session, xen_task *result, xen_vdi vdi, int64_t size)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_int,
              .u.int_val = size }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.resize");
    return session->ok;
}

bool
xen_vdi_resize_online(xen_session *session, xen_vdi vdi, int64_t size)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_int,
              .u.int_val = size }
        };

    xen_call_(session, "VDI.resize_online", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_resize_online_async(xen_session *session, xen_task *result, xen_vdi vdi, int64_t size)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_int,
              .u.int_val = size }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.resize_online");
    return session->ok;
}

bool
xen_vdi_introduce(xen_session *session, xen_vdi *result, const char *uuid, const char *name_label, const char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, const char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of)
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
              .u.string_val = sr },
            { .type = &xen_vdi_type_abstract_type_,
              .u.enum_val = type },
            { .type = &abstract_type_bool,
              .u.bool_val = sharable },
            { .type = &abstract_type_bool,
              .u.bool_val = read_only },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config },
            { .type = &abstract_type_string,
              .u.string_val = location },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)xenstore_data },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config },
            { .type = &abstract_type_bool,
              .u.bool_val = managed },
            { .type = &abstract_type_int,
              .u.int_val = virtual_size },
            { .type = &abstract_type_int,
              .u.int_val = physical_utilisation },
            { .type = &abstract_type_string,
              .u.string_val = metadata_of_pool },
            { .type = &abstract_type_bool,
              .u.bool_val = is_a_snapshot },
            { .type = &abstract_type_datetime,
              .u.datetime_val = snapshot_time },
            { .type = &abstract_type_string,
              .u.string_val = snapshot_of }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.introduce");
    return session->ok;
}

bool
xen_vdi_introduce_async(xen_session *session, xen_task *result, const char *uuid, const char *name_label, const char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, const char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of)
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
              .u.string_val = sr },
            { .type = &xen_vdi_type_abstract_type_,
              .u.enum_val = type },
            { .type = &abstract_type_bool,
              .u.bool_val = sharable },
            { .type = &abstract_type_bool,
              .u.bool_val = read_only },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config },
            { .type = &abstract_type_string,
              .u.string_val = location },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)xenstore_data },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config },
            { .type = &abstract_type_bool,
              .u.bool_val = managed },
            { .type = &abstract_type_int,
              .u.int_val = virtual_size },
            { .type = &abstract_type_int,
              .u.int_val = physical_utilisation },
            { .type = &abstract_type_string,
              .u.string_val = metadata_of_pool },
            { .type = &abstract_type_bool,
              .u.bool_val = is_a_snapshot },
            { .type = &abstract_type_datetime,
              .u.datetime_val = snapshot_time },
            { .type = &abstract_type_string,
              .u.string_val = snapshot_of }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.introduce");
    return session->ok;
}

bool
xen_vdi_db_introduce(xen_session *session, xen_vdi *result, const char *uuid, const char *name_label, const char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, const char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of)
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
              .u.string_val = sr },
            { .type = &xen_vdi_type_abstract_type_,
              .u.enum_val = type },
            { .type = &abstract_type_bool,
              .u.bool_val = sharable },
            { .type = &abstract_type_bool,
              .u.bool_val = read_only },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config },
            { .type = &abstract_type_string,
              .u.string_val = location },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)xenstore_data },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config },
            { .type = &abstract_type_bool,
              .u.bool_val = managed },
            { .type = &abstract_type_int,
              .u.int_val = virtual_size },
            { .type = &abstract_type_int,
              .u.int_val = physical_utilisation },
            { .type = &abstract_type_string,
              .u.string_val = metadata_of_pool },
            { .type = &abstract_type_bool,
              .u.bool_val = is_a_snapshot },
            { .type = &abstract_type_datetime,
              .u.datetime_val = snapshot_time },
            { .type = &abstract_type_string,
              .u.string_val = snapshot_of }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.db_introduce");
    return session->ok;
}

bool
xen_vdi_db_introduce_async(xen_session *session, xen_task *result, const char *uuid, const char *name_label, const char *name_description, xen_sr sr, enum xen_vdi_type type, bool sharable, bool read_only, xen_string_string_map *other_config, const char *location, xen_string_string_map *xenstore_data, xen_string_string_map *sm_config, bool managed, int64_t virtual_size, int64_t physical_utilisation, xen_pool metadata_of_pool, bool is_a_snapshot, time_t snapshot_time, xen_vdi snapshot_of)
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
              .u.string_val = sr },
            { .type = &xen_vdi_type_abstract_type_,
              .u.enum_val = type },
            { .type = &abstract_type_bool,
              .u.bool_val = sharable },
            { .type = &abstract_type_bool,
              .u.bool_val = read_only },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config },
            { .type = &abstract_type_string,
              .u.string_val = location },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)xenstore_data },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)sm_config },
            { .type = &abstract_type_bool,
              .u.bool_val = managed },
            { .type = &abstract_type_int,
              .u.int_val = virtual_size },
            { .type = &abstract_type_int,
              .u.int_val = physical_utilisation },
            { .type = &abstract_type_string,
              .u.string_val = metadata_of_pool },
            { .type = &abstract_type_bool,
              .u.bool_val = is_a_snapshot },
            { .type = &abstract_type_datetime,
              .u.datetime_val = snapshot_time },
            { .type = &abstract_type_string,
              .u.string_val = snapshot_of }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.db_introduce");
    return session->ok;
}

bool
xen_vdi_db_forget(xen_session *session, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    xen_call_(session, "VDI.db_forget", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_db_forget_async(xen_session *session, xen_task *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.db_forget");
    return session->ok;
}

bool
xen_vdi_update(xen_session *session, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    xen_call_(session, "VDI.update", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_update_async(xen_session *session, xen_task *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.update");
    return session->ok;
}

bool
xen_vdi_copy(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.copy");
    return session->ok;
}

bool
xen_vdi_copy_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_sr sr)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = sr }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.copy");
    return session->ok;
}

bool
xen_vdi_set_managed(xen_session *session, xen_vdi self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VDI.set_managed", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_forget(xen_session *session, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    xen_call_(session, "VDI.forget", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_forget_async(xen_session *session, xen_task *result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.forget");
    return session->ok;
}

bool
xen_vdi_set_sharable(xen_session *session, xen_vdi self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VDI.set_sharable", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_read_only(xen_session *session, xen_vdi self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VDI.set_read_only", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_missing(xen_session *session, xen_vdi self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VDI.set_missing", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_virtual_size(xen_session *session, xen_vdi self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VDI.set_virtual_size", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_physical_utilisation(xen_session *session, xen_vdi self, int64_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_int,
              .u.int_val = value }
        };

    xen_call_(session, "VDI.set_physical_utilisation", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_is_a_snapshot(xen_session *session, xen_vdi self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VDI.set_is_a_snapshot", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_snapshot_of(xen_session *session, xen_vdi self, xen_vdi value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.set_snapshot_of", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_snapshot_time(xen_session *session, xen_vdi self, time_t value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_datetime,
              .u.datetime_val = value }
        };

    xen_call_(session, "VDI.set_snapshot_time", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_metadata_of_pool(xen_session *session, xen_vdi self, xen_pool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.set_metadata_of_pool", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_vdi_set_name_label(xen_session *session, xen_vdi self, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_set_name_label_async(xen_session *session, xen_task *result, xen_vdi self, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.set_name_label");
    return session->ok;
}

bool
xen_vdi_set_name_description(xen_session *session, xen_vdi self, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "VDI.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_set_name_description_async(xen_session *session, xen_task *result, xen_vdi self, const char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.set_name_description");
    return session->ok;
}

bool
xen_vdi_set_on_boot(xen_session *session, xen_vdi self, enum xen_on_boot value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_on_boot_abstract_type_,
              .u.enum_val = value }
        };

    xen_call_(session, "VDI.set_on_boot", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_set_on_boot_async(xen_session *session, xen_task *result, xen_vdi self, enum xen_on_boot value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_on_boot_abstract_type_,
              .u.enum_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.set_on_boot");
    return session->ok;
}

bool
xen_vdi_set_allow_caching(xen_session *session, xen_vdi self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    xen_call_(session, "VDI.set_allow_caching", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_vdi_set_allow_caching_async(xen_session *session, xen_task *result, xen_vdi self, bool value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_bool,
              .u.bool_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.set_allow_caching");
    return session->ok;
}

bool
xen_vdi_open_database(xen_session *session, xen_session **result, xen_vdi self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.open_database");
    return session->ok;
}

bool
xen_vdi_open_database_async(xen_session *session, xen_task *result, xen_vdi self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.open_database");
    return session->ok;
}

bool
xen_vdi_read_database_pool_uuid(xen_session *session, char **result, xen_vdi self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.read_database_pool_uuid");
    return session->ok;
}

bool
xen_vdi_read_database_pool_uuid_async(xen_session *session, xen_task *result, xen_vdi self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.read_database_pool_uuid");
    return session->ok;
}

bool
xen_vdi_pool_migrate(xen_session *session, xen_vdi *result, xen_vdi vdi, xen_sr sr, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.pool_migrate");
    return session->ok;
}

bool
xen_vdi_pool_migrate_async(xen_session *session, xen_task *result, xen_vdi vdi, xen_sr sr, xen_string_string_map *options)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi },
            { .type = &abstract_type_string,
              .u.string_val = sr },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)options }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.VDI.pool_migrate");
    return session->ok;
}

bool
xen_vdi_get_all(xen_session *session, struct xen_vdi_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "VDI.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vdi_get_all_records(xen_session *session, xen_vdi_xen_vdi_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_vdi_record_map;

    *result = NULL;
    xen_call_(session, "VDI.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_vdi_get_uuid(xen_session *session, char **result, xen_vdi vdi)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = vdi }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("VDI.get_uuid");
    return session->ok;
}

