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

#include "xen_console_protocol_internal.h"
#include "xen_internal.h"
#include <xen/api/xen_common.h>
#include <xen/api/xen_console.h>
#include <xen/api/xen_console_xen_console_record_map.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_vm.h>


XEN_FREE(xen_console)
XEN_SET_ALLOC_FREE(xen_console)
XEN_ALLOC(xen_console_record)
XEN_SET_ALLOC_FREE(xen_console_record)
XEN_ALLOC(xen_console_record_opt)
XEN_RECORD_OPT_FREE(xen_console)
XEN_SET_ALLOC_FREE(xen_console_record_opt)


static const struct_member xen_console_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_console_record, uuid) },
        { .key = "protocol",
          .type = &xen_console_protocol_abstract_type_,
          .offset = offsetof(xen_console_record, protocol) },
        { .key = "location",
          .type = &abstract_type_string,
          .offset = offsetof(xen_console_record, location) },
        { .key = "VM",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_console_record, vm) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_console_record, other_config) }
    };

const abstract_type xen_console_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_console_record),
       .member_count =
           sizeof(xen_console_record_struct_members) / sizeof(struct_member),
       .members = xen_console_record_struct_members
    };


static const struct struct_member xen_console_xen_console_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_console_xen_console_record_map_contents, key)
    },
    {
        .type = &xen_console_record_abstract_type_,
        .offset = offsetof(xen_console_xen_console_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_console_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_console_xen_console_record_map_contents),
    .members = xen_console_xen_console_record_members
};


void
xen_console_record_free(xen_console_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    free(record->location);
    xen_vm_record_opt_free(record->vm);
    xen_string_string_map_free(record->other_config);
    free(record);
}


bool
xen_console_get_record(xen_session *session, xen_console_record **result, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    abstract_type result_type = xen_console_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("console.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_console_get_by_uuid(xen_session *session, xen_console *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("console.get_by_uuid");
    return session->ok;
}


bool
xen_console_create(xen_session *session, xen_console *result, xen_console_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_console_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("console.create");
    return session->ok;
}

bool
xen_console_create_async(xen_session *session, xen_task *result, xen_console_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_console_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.console.create");
    return session->ok;
}

bool
xen_console_destroy(xen_session *session, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    xen_call_(session, "console.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_console_destroy_async(xen_session *session, xen_task *result, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.console.destroy");
    return session->ok;
}

bool
xen_console_get_protocol(xen_session *session, enum xen_console_protocol *result, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    abstract_type result_type = xen_console_protocol_abstract_type_;
    XEN_CALL_("console.get_protocol");
    return session->ok;
}


bool
xen_console_get_location(xen_session *session, char **result, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("console.get_location");
    return session->ok;
}


bool
xen_console_get_vm(xen_session *session, xen_vm *result, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("console.get_VM");
    return session->ok;
}


bool
xen_console_get_other_config(xen_session *session, xen_string_string_map **result, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("console.get_other_config");
    return session->ok;
}


bool
xen_console_set_other_config(xen_session *session, xen_console console, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "console.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_console_add_to_other_config(xen_session *session, xen_console console, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "console.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_console_remove_from_other_config(xen_session *session, xen_console console, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "console.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_console_get_all(xen_session *session, struct xen_console_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "console.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_console_get_all_records(xen_session *session, xen_console_xen_console_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_console_record_map;

    *result = NULL;
    xen_call_(session, "console.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_console_get_uuid(xen_session *session, char **result, xen_console console)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = console }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("console.get_uuid");
    return session->ok;
}

