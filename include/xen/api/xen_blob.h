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


#ifndef XEN_BLOB_H
#define XEN_BLOB_H

#include <xen/api/xen_blob_decl.h>
#include <xen/api/xen_blob_xen_blob_record_map.h>
#include <xen/api/xen_common.h>


/*
 * The blob class.
 * 
 * A placeholder for a binary blob.
 */


/**
 * Free the given xen_blob.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_blob_free(xen_blob blob);


typedef struct xen_blob_set
{
    size_t size;
    xen_blob *contents[];
} xen_blob_set;

/**
 * Allocate a xen_blob_set of the given size.
 */
extern xen_blob_set *
xen_blob_set_alloc(size_t size);

/**
 * Free the given xen_blob_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_blob_set_free(xen_blob_set *set);


typedef struct xen_blob_record
{
    xen_blob handle;
    char *uuid;
    char *name_label;
    char *name_description;
    int64_t size;
    bool pubblic;
    time_t last_updated;
    char *mime_type;
} xen_blob_record;

/**
 * Allocate a xen_blob_record.
 */
extern xen_blob_record *
xen_blob_record_alloc(void);

/**
 * Free the given xen_blob_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_blob_record_free(xen_blob_record *record);


typedef struct xen_blob_record_opt
{
    bool is_record;
    union
    {
        xen_blob handle;
        xen_blob_record *record;
    } u;
} xen_blob_record_opt;

/**
 * Allocate a xen_blob_record_opt.
 */
extern xen_blob_record_opt *
xen_blob_record_opt_alloc(void);

/**
 * Free the given xen_blob_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_blob_record_opt_free(xen_blob_record_opt *record_opt);


typedef struct xen_blob_record_set
{
    size_t size;
    xen_blob_record *contents[];
} xen_blob_record_set;

/**
 * Allocate a xen_blob_record_set of the given size.
 */
extern xen_blob_record_set *
xen_blob_record_set_alloc(size_t size);

/**
 * Free the given xen_blob_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_blob_record_set_free(xen_blob_record_set *set);



typedef struct xen_blob_record_opt_set
{
    size_t size;
    xen_blob_record_opt *contents[];
} xen_blob_record_opt_set;

/**
 * Allocate a xen_blob_record_opt_set of the given size.
 */
extern xen_blob_record_opt_set *
xen_blob_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_blob_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_blob_record_opt_set_free(xen_blob_record_opt_set *set);


/**
 * Get a record containing the current state of the given blob.
 */
extern bool
xen_blob_get_record(xen_session *session, xen_blob_record **result, xen_blob blob);


/**
 * Get a reference to the blob instance with the specified UUID.
 */
extern bool
xen_blob_get_by_uuid(xen_session *session, xen_blob *result, char *uuid);


/**
 * Get all the blob instances with the given label.
 */
extern bool
xen_blob_get_by_name_label(xen_session *session, struct xen_blob_set **result, char *label);


/**
 * Get the uuid field of the given blob.
 */
extern bool
xen_blob_get_uuid(xen_session *session, char **result, xen_blob blob);


/**
 * Get the name/label field of the given blob.
 */
extern bool
xen_blob_get_name_label(xen_session *session, char **result, xen_blob blob);


/**
 * Get the name/description field of the given blob.
 */
extern bool
xen_blob_get_name_description(xen_session *session, char **result, xen_blob blob);


/**
 * Get the size field of the given blob.
 */
extern bool
xen_blob_get_size(xen_session *session, int64_t *result, xen_blob blob);


/**
 * Get the public field of the given blob.
 */
extern bool
xen_blob_get_public(xen_session *session, bool *result, xen_blob blob);


/**
 * Get the last_updated field of the given blob.
 */
extern bool
xen_blob_get_last_updated(xen_session *session, time_t *result, xen_blob blob);


/**
 * Get the mime_type field of the given blob.
 */
extern bool
xen_blob_get_mime_type(xen_session *session, char **result, xen_blob blob);


/**
 * Set the name/label field of the given blob.
 */
extern bool
xen_blob_set_name_label(xen_session *session, xen_blob blob, char *label);


/**
 * Set the name/description field of the given blob.
 */
extern bool
xen_blob_set_name_description(xen_session *session, xen_blob blob, char *description);


/**
 * Set the public field of the given blob.
 */
extern bool
xen_blob_set_public(xen_session *session, xen_blob blob, bool pubblic);


/**
 * Create a placeholder for a binary blob.
 */
extern bool
xen_blob_create(xen_session *session, xen_blob *result, char *mime_type, bool pubblic);


/**
 * .
 */
extern bool
xen_blob_destroy(xen_session *session, xen_blob self);


/**
 * Return a list of all the blobs known to the system.
 */
extern bool
xen_blob_get_all(xen_session *session, struct xen_blob_set **result);


/**
 * Return a map of blob references to blob records for all blobs known
 * to the system.
 */
extern bool
xen_blob_get_all_records(xen_session *session, xen_blob_xen_blob_record_map **result);


#endif
