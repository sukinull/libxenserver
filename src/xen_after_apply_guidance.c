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


#include <string.h>

#include "xen_internal.h"
#include <xen/api/xen_after_apply_guidance.h>
#include "xen_after_apply_guidance_internal.h"


/*
 * Maintain this in the same order as the enum declaration!
 */
static const char *lookup_table[] =
{
    "restartHVM",
    "restartPV",
    "restartHost",
    "restartXAPI",
    "undefined"
};


extern xen_after_apply_guidance_set *
xen_after_apply_guidance_set_alloc(size_t size)
{
    return calloc(1, sizeof(xen_after_apply_guidance_set) +
                  size * sizeof(enum xen_after_apply_guidance));
}


extern void
xen_after_apply_guidance_set_free(xen_after_apply_guidance_set *set)
{
    free(set);
}


const char *
xen_after_apply_guidance_to_string(enum xen_after_apply_guidance val)
{
    return lookup_table[val];
}


extern enum xen_after_apply_guidance
xen_after_apply_guidance_from_string(xen_session *session, const char *str)
{
    (void)session;
    return ENUM_LOOKUP(str, lookup_table);
}


const abstract_type xen_after_apply_guidance_abstract_type_ =
    {
        .typename = ENUM,
        .enum_marshaller =
             (const char *(*)(int))&xen_after_apply_guidance_to_string,
        .enum_demarshaller =
             (int (*)(xen_session *, const char *))&xen_after_apply_guidance_from_string
    };


const abstract_type xen_after_apply_guidance_set_abstract_type_ =
    {
        .typename = SET,
        .child = &xen_after_apply_guidance_abstract_type_
    };


