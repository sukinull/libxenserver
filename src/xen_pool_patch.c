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

#include "xen_after_apply_guidance_internal.h"
#include "xen_internal.h"
#include <xen/api/xen_after_apply_guidance.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_host.h>
#include <xen/api/xen_host_patch.h>
#include <xen/api/xen_pool_patch.h>
#include <xen/api/xen_pool_patch_xen_pool_patch_record_map.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_pool_patch)
XEN_SET_ALLOC_FREE(xen_pool_patch)
XEN_ALLOC(xen_pool_patch_record)
XEN_SET_ALLOC_FREE(xen_pool_patch_record)
XEN_ALLOC(xen_pool_patch_record_opt)
XEN_RECORD_OPT_FREE(xen_pool_patch)
XEN_SET_ALLOC_FREE(xen_pool_patch_record_opt)


static const struct_member xen_pool_patch_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pool_patch_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pool_patch_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pool_patch_record, name_description) },
        { .key = "version",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pool_patch_record, version) },
        { .key = "size",
          .type = &abstract_type_int,
          .offset = offsetof(xen_pool_patch_record, size) },
        { .key = "pool_applied",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_pool_patch_record, pool_applied) },
        { .key = "host_patches",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_pool_patch_record, host_patches) },
        { .key = "after_apply_guidance",
          .type = &xen_after_apply_guidance_set_abstract_type_,
          .offset = offsetof(xen_pool_patch_record, after_apply_guidance) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_pool_patch_record, other_config) }
    };

const abstract_type xen_pool_patch_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_pool_patch_record),
       .member_count =
           sizeof(xen_pool_patch_record_struct_members) / sizeof(struct_member),
       .members = xen_pool_patch_record_struct_members
    };


static const struct struct_member xen_pool_patch_xen_pool_patch_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_pool_patch_xen_pool_patch_record_map_contents, key)
    },
    {
        .type = &xen_pool_patch_record_abstract_type_,
        .offset = offsetof(xen_pool_patch_xen_pool_patch_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_pool_patch_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_pool_patch_xen_pool_patch_record_map_contents),
    .members = xen_pool_patch_xen_pool_patch_record_members
};


void
xen_pool_patch_record_free(xen_pool_patch_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    free(record->version);
    xen_host_patch_record_opt_set_free(record->host_patches);
    xen_after_apply_guidance_set_free(record->after_apply_guidance);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_pool_patch_get_record(xen_session *session, xen_pool_patch_record **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = xen_pool_patch_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("pool_patch.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_pool_patch_get_by_uuid(xen_session *session, xen_pool_patch *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("pool_patch.get_by_uuid");
    return session->ok;
}


bool
xen_pool_patch_get_by_name_label(xen_session *session, struct xen_pool_patch_set **result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("pool_patch.get_by_name_label");
    return session->ok;
}


bool
xen_pool_patch_get_name_label(xen_session *session, char **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("pool_patch.get_name_label");
    return session->ok;
}


bool
xen_pool_patch_get_name_description(xen_session *session, char **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("pool_patch.get_name_description");
    return session->ok;
}


bool
xen_pool_patch_get_version(xen_session *session, char **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("pool_patch.get_version");
    return session->ok;
}


bool
xen_pool_patch_get_size(xen_session *session, int64_t *result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("pool_patch.get_size");
    return session->ok;
}


bool
xen_pool_patch_get_pool_applied(xen_session *session, bool *result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("pool_patch.get_pool_applied");
    return session->ok;
}


bool
xen_pool_patch_get_host_patches(xen_session *session, struct xen_host_patch_set **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("pool_patch.get_host_patches");
    return session->ok;
}


bool
xen_pool_patch_get_after_apply_guidance(xen_session *session, struct xen_after_apply_guidance_set **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = xen_after_apply_guidance_set_abstract_type_;

    *result = NULL;
    XEN_CALL_("pool_patch.get_after_apply_guidance");
    return session->ok;
}


bool
xen_pool_patch_get_other_config(xen_session *session, xen_string_string_map **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("pool_patch.get_other_config");
    return session->ok;
}


bool
xen_pool_patch_set_other_config(xen_session *session, xen_pool_patch pool_patch, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "pool_patch.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pool_patch_add_to_other_config(xen_session *session, xen_pool_patch pool_patch, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "pool_patch.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_pool_patch_remove_from_other_config(xen_session *session, xen_pool_patch pool_patch, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "pool_patch.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pool_patch_apply(xen_session *session, char **result, xen_pool_patch self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("pool_patch.apply");
    return session->ok;
}

bool
xen_pool_patch_apply_async(xen_session *session, xen_task *result, xen_pool_patch self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.pool_patch.apply");
    return session->ok;
}

bool
xen_pool_patch_pool_apply(xen_session *session, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "pool_patch.pool_apply", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pool_patch_pool_apply_async(xen_session *session, xen_task *result, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.pool_patch.pool_apply");
    return session->ok;
}

bool
xen_pool_patch_precheck(xen_session *session, char **result, xen_pool_patch self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("pool_patch.precheck");
    return session->ok;
}

bool
xen_pool_patch_precheck_async(xen_session *session, xen_task *result, xen_pool_patch self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.pool_patch.precheck");
    return session->ok;
}

bool
xen_pool_patch_clean(xen_session *session, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "pool_patch.clean", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pool_patch_clean_async(xen_session *session, xen_task *result, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.pool_patch.clean");
    return session->ok;
}

bool
xen_pool_patch_pool_clean(xen_session *session, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "pool_patch.pool_clean", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pool_patch_pool_clean_async(xen_session *session, xen_task *result, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.pool_patch.pool_clean");
    return session->ok;
}

bool
xen_pool_patch_destroy(xen_session *session, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "pool_patch.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pool_patch_destroy_async(xen_session *session, xen_task *result, xen_pool_patch self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.pool_patch.destroy");
    return session->ok;
}

bool
xen_pool_patch_clean_on_host(xen_session *session, xen_pool_patch self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "pool_patch.clean_on_host", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_pool_patch_clean_on_host_async(xen_session *session, xen_task *result, xen_pool_patch self, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.pool_patch.clean_on_host");
    return session->ok;
}

bool
xen_pool_patch_get_all(xen_session *session, struct xen_pool_patch_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "pool_patch.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pool_patch_get_all_records(xen_session *session, xen_pool_patch_xen_pool_patch_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_pool_patch_record_map;

    *result = NULL;
    xen_call_(session, "pool_patch.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pool_patch_get_uuid(xen_session *session, char **result, xen_pool_patch pool_patch)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pool_patch }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("pool_patch.get_uuid");
    return session->ok;
}

