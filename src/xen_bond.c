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

#include "xen_bond_mode_internal.h"
#include "xen_internal.h"
#include <xen/api/xen_bond.h>
#include <xen/api/xen_bond_xen_bond_record_map.h>
#include <xen/api/xen_common.h>
#include <xen/api/xen_network.h>
#include <xen/api/xen_pif.h>
#include <xen/api/xen_string_string_map.h>


XEN_FREE(xen_bond)
XEN_SET_ALLOC_FREE(xen_bond)
XEN_ALLOC(xen_bond_record)
XEN_SET_ALLOC_FREE(xen_bond_record)
XEN_ALLOC(xen_bond_record_opt)
XEN_RECORD_OPT_FREE(xen_bond)
XEN_SET_ALLOC_FREE(xen_bond_record_opt)


static const struct_member xen_bond_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_bond_record, uuid) },
        { .key = "master",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_bond_record, master) },
        { .key = "slaves",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_bond_record, slaves) },
        { .key = "other_config",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_bond_record, other_config) },
        { .key = "primary_slave",
          .type = &abstract_type_ref,
          .offset = offsetof(xen_bond_record, primary_slave) },
        { .key = "mode",
          .type = &xen_bond_mode_abstract_type_,
          .offset = offsetof(xen_bond_record, mode) },
        { .key = "properties",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_bond_record, properties) },
        { .key = "links_up",
          .type = &abstract_type_int,
          .offset = offsetof(xen_bond_record, links_up) }
    };

const abstract_type xen_bond_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_bond_record),
       .member_count =
           sizeof(xen_bond_record_struct_members) / sizeof(struct_member),
       .members = xen_bond_record_struct_members
    };


static const struct struct_member xen_bond_xen_bond_record_members[] =
{
    {
        .type = &abstract_type_string,
        .offset = offsetof(xen_bond_xen_bond_record_map_contents, key)
    },
    {
        .type = &xen_bond_record_abstract_type_,
        .offset = offsetof(xen_bond_xen_bond_record_map_contents, val)
    }
};

const abstract_type abstract_type_string_xen_bond_record_map =
{
    .typename = MAP,
    .struct_size = sizeof(xen_bond_xen_bond_record_map_contents),
    .members = xen_bond_xen_bond_record_members
};


void
xen_bond_record_free(xen_bond_record *record)
{
    if (record == NULL)
    {
        return;
    }
    free(record->handle);
    free(record->uuid);
    xen_pif_record_opt_free(record->master);
    xen_pif_record_opt_set_free(record->slaves);
    xen_string_string_map_free(record->other_config);
    xen_pif_record_opt_free(record->primary_slave);
    xen_string_string_map_free(record->properties);
    free(record);
}


bool
xen_bond_get_record(xen_session *session, xen_bond_record **result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = xen_bond_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("Bond.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_bond_get_by_uuid(xen_session *session, xen_bond *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Bond.get_by_uuid");
    return session->ok;
}


bool
xen_bond_get_master(xen_session *session, xen_pif *result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Bond.get_master");
    return session->ok;
}


bool
xen_bond_get_slaves(xen_session *session, struct xen_pif_set **result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("Bond.get_slaves");
    return session->ok;
}


bool
xen_bond_get_other_config(xen_session *session, xen_string_string_map **result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("Bond.get_other_config");
    return session->ok;
}


bool
xen_bond_get_primary_slave(xen_session *session, xen_pif *result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Bond.get_primary_slave");
    return session->ok;
}


bool
xen_bond_get_mode(xen_session *session, enum xen_bond_mode *result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = xen_bond_mode_abstract_type_;
    XEN_CALL_("Bond.get_mode");
    return session->ok;
}


bool
xen_bond_get_properties(xen_session *session, xen_string_string_map **result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("Bond.get_properties");
    return session->ok;
}


bool
xen_bond_get_links_up(xen_session *session, int64_t *result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = abstract_type_int;

    XEN_CALL_("Bond.get_links_up");
    return session->ok;
}


bool
xen_bond_set_other_config(xen_session *session, xen_bond bond, xen_string_string_map *other_config)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)other_config }
        };

    xen_call_(session, "Bond.set_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_bond_add_to_other_config(xen_session *session, xen_bond bond, char *key, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond },
            { .type = &abstract_type_string,
              .u.string_val = key },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "Bond.add_to_other_config", param_values, 3, NULL, NULL);
    return session->ok;
}


bool
xen_bond_remove_from_other_config(xen_session *session, xen_bond bond, char *key)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond },
            { .type = &abstract_type_string,
              .u.string_val = key }
        };

    xen_call_(session, "Bond.remove_from_other_config", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_bond_create(xen_session *session, xen_bond *result, xen_network network, struct xen_pif_set *members, char *mac, enum xen_bond_mode mode, xen_string_string_map *properties)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)members },
            { .type = &abstract_type_string,
              .u.string_val = mac },
            { .type = &xen_bond_mode_abstract_type_,
              .u.enum_val = mode },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)properties }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Bond.create");
    return session->ok;
}

bool
xen_bond_create_async(xen_session *session, xen_task *result, xen_network network, struct xen_pif_set *members, char *mac, enum xen_bond_mode mode, xen_string_string_map *properties)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = network },
            { .type = &abstract_type_string_set,
              .u.set_val = (arbitrary_set *)members },
            { .type = &abstract_type_string,
              .u.string_val = mac },
            { .type = &xen_bond_mode_abstract_type_,
              .u.enum_val = mode },
            { .type = &abstract_type_string_string_map,
              .u.set_val = (arbitrary_set *)properties }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.Bond.create");
    return session->ok;
}

bool
xen_bond_destroy(xen_session *session, xen_bond self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    xen_call_(session, "Bond.destroy", param_values, 1, NULL, NULL);
    return session->ok;
}

bool
xen_bond_destroy_async(xen_session *session, xen_task *result, xen_bond self)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.Bond.destroy");
    return session->ok;
}

bool
xen_bond_set_mode(xen_session *session, xen_bond self, enum xen_bond_mode value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_bond_mode_abstract_type_,
              .u.enum_val = value }
        };

    xen_call_(session, "Bond.set_mode", param_values, 2, NULL, NULL);
    return session->ok;
}

bool
xen_bond_set_mode_async(xen_session *session, xen_task *result, xen_bond self, enum xen_bond_mode value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &xen_bond_mode_abstract_type_,
              .u.enum_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.Bond.set_mode");
    return session->ok;
}

bool
xen_bond_set_property(xen_session *session, xen_bond self, char *name, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    xen_call_(session, "Bond.set_property", param_values, 3, NULL, NULL);
    return session->ok;
}

bool
xen_bond_set_property_async(xen_session *session, xen_task *result, xen_bond self, char *name, char *value)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = self },
            { .type = &abstract_type_string,
              .u.string_val = name },
            { .type = &abstract_type_string,
              .u.string_val = value }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Async.Bond.set_property");
    return session->ok;
}

bool
xen_bond_get_all(xen_session *session, struct xen_bond_set **result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "Bond.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_bond_get_all_records(xen_session *session, xen_bond_xen_bond_record_map **result)
{

    abstract_type result_type = abstract_type_string_xen_bond_record_map;

    *result = NULL;
    xen_call_(session, "Bond.get_all_records", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_bond_get_uuid(xen_session *session, char **result, xen_bond bond)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = bond }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("Bond.get_uuid");
    return session->ok;
}

