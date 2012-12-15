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
#include <xen/api/xen_pbd.h>
#include <xen/api/xen_pbd_xen_pbd_record_map.h>
#include <xen/api/xen_sr.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_pbd)
XEN_SET_ALLOC_FREE(xen_pbd)
XEN_ALLOC(xen_pbd_record)
XEN_SET_ALLOC_FREE(xen_pbd_record)
XEN_ALLOC(xen_pbd_record_opt)
XEN_RECORD_OPT_FREE(xen_pbd)
XEN_SET_ALLOC_FREE(xen_pbd_record_opt)


static const struct_member xen_pbd_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_pbd_record, uuid) },
        { .key = "host",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pbd_record, host) },
        { .key = "SR",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_pbd_record, sr) },
        { .key = "device_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_pbd_record, device_config) },
        { .key = "currently_attached",
          .type = &abstract_type_bool,
          .offset = offsetof(xen_pbd_record, currently_attached) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_pbd_record, other_config) }
    };

const abstract_type xen_pbd_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_pbd_record),
       .member_count =
           sizeof(xen_pbd_record_struct_members) / sizeof(struct_member),
       .members = xen_pbd_record_struct_members
    };


static const struct struct_member xen_pbd_xen_pbd_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_pbd_xen_pbd_record_map_contents, key)
    },
    {
        .type = &xen_pbd_record_abstract_type_,
        .offset = offsetof(xen_pbd_xen_pbd_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_pbd_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_pbd_xen_pbd_record_map_contents),
    .members = xen_pbd_xen_pbd_record_members
};


void
xen_pbd_record_free(xen_pbd_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_host_record_opt_free(record->host);
    xen_sr_record_opt_free(record->sr);
    xen_string_string_map_free(record->device_config);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_pbd_get_record(xen_session *session, xen_pbd_record **result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = xen_pbd_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("PBD.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_pbd_get_by_uuid(xen_session *session, xen_pbd *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PBD.get_by_uuid");
    return session->ok;
}


bool
xen_pbd_create(xen_session *session, xen_pbd *result, xen_pbd_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_pbd_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PBD.create");
    return session->ok;
}

bool
xen_pbd_create_async(xen_session *session, xen_task *result, xen_pbd_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_pbd_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PBD.create");
    return session->ok;
}

bool
xen_pbd_destroy(xen_session *session, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    xen_call_(session, "PBD.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pbd_destroy_async(xen_session *session, xen_task *result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PBD.destroy");
    return session->ok;
}

bool
xen_pbd_get_host(xen_session *session, xen_host *result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PBD.get_host");
    return session->ok;
}


bool
xen_pbd_get_sr(xen_session *session, xen_sr *result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PBD.get_SR");
    return session->ok;
}


bool
xen_pbd_get_device_config(xen_session *session, xen_string_string_map **result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("PBD.get_device_config");
    return session->ok;
}


bool
xen_pbd_get_currently_attached(xen_session *session, bool *result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = abstract_type_bool;

    XEN_CALL_("PBD.get_currently_attached");
    return session->ok;
}


bool
xen_pbd_get_other_config(xen_session *session, xen_string_string_map **result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("PBD.get_other_config");
    return session->ok;
}


bool
xen_pbd_set_other_config(xen_session *session, xen_pbd pbd, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "PBD.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pbd_add_to_other_config(xen_session *session, xen_pbd pbd, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "PBD.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_pbd_remove_from_other_config(xen_session *session, xen_pbd pbd, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "PBD.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_pbd_plug(xen_session *session, xen_pbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "PBD.plug", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pbd_plug_async(xen_session *session, xen_task *result, xen_pbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PBD.plug");
    return session->ok;
}

bool
xen_pbd_unplug(xen_session *session, xen_pbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "PBD.unplug", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_pbd_unplug_async(xen_session *session, xen_task *result, xen_pbd self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PBD.unplug");
    return session->ok;
}

bool
xen_pbd_set_device_config(xen_session *session, xen_pbd self, xen_string_string_map *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)value }
        };

    xen_call_(session, "PBD.set_device_config", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_pbd_set_device_config_async(xen_session *session, xen_task *result, xen_pbd self, xen_string_string_map *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.PBD.set_device_config");
    return session->ok;
}

bool
xen_pbd_get_all(xen_session *session, struct xen_pbd_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "PBD.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pbd_get_all_records(xen_session *session, xen_pbd_xen_pbd_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_pbd_record_map;

    *result = NULL;
    xen_call_(session, "PBD.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_pbd_get_uuid(xen_session *session, char **result, xen_pbd pbd)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = pbd }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("PBD.get_uuid");
    return session->ok;
}

