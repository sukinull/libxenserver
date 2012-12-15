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


#ifndef XEN_TASK_H
#define XEN_TASK_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_string_task_allowed_operations_map.h>
#include <xen/api/xen_task_allowed_operations.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_task_status_type.h>
#include <xen/api/xen_task_xen_task_record_map.h>


/*
 * The task class.
 * 
 * A long-running asynchronous task.
 */


/**
 * Free the given xen_task.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_task_free(xen_task task);


typedef struct xen_task_set
{
    size_t size;
    xen_task *contents[];
} xen_task_set;

/**
 * Allocate a xen_task_set of the given size.
 */
extern xen_task_set *
xen_task_set_alloc(size_t size);

/**
 * Free the given xen_task_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_task_set_free(xen_task_set *set);


typedef struct xen_task_record
{
    xen_task handle;
    char *uuid;
    char *name_label;
    char *name_description;
    struct xen_task_allowed_operations_set *allowed_operations;
    xen_string_task_allowed_operations_map *current_operations;
    time_t created;
    time_t finished;
    enum xen_task_status_type status;
    struct xen_host_record_opt *resident_on;
    double progress;
    char *type;
    char *result;
    struct xen_string_set *error_info;
    xen_string_string_map *other_config;
    struct xen_task_record_opt *subtask_of;
    struct xen_task_record_opt_set *subtasks;
} xen_task_record;

/**
 * Allocate a xen_task_record.
 */
extern xen_task_record *
xen_task_record_alloc(void);

/**
 * Free the given xen_task_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_task_record_free(xen_task_record *record);


typedef struct xen_task_record_opt
{
    bool is_record;
    union
    {
        xen_task handle;
        xen_task_record *record;
    } u;
} xen_task_record_opt;

/**
 * Allocate a xen_task_record_opt.
 */
extern xen_task_record_opt *
xen_task_record_opt_alloc(void);

/**
 * Free the given xen_task_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_task_record_opt_free(xen_task_record_opt *record_opt);


typedef struct xen_task_record_set
{
    size_t size;
    xen_task_record *contents[];
} xen_task_record_set;

/**
 * Allocate a xen_task_record_set of the given size.
 */
extern xen_task_record_set *
xen_task_record_set_alloc(size_t size);

/**
 * Free the given xen_task_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_task_record_set_free(xen_task_record_set *set);



typedef struct xen_task_record_opt_set
{
    size_t size;
    xen_task_record_opt *contents[];
} xen_task_record_opt_set;

/**
 * Allocate a xen_task_record_opt_set of the given size.
 */
extern xen_task_record_opt_set *
xen_task_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_task_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_task_record_opt_set_free(xen_task_record_opt_set *set);


/**
 * Get a record containing the current state of the given task.
 */
extern bool
xen_task_get_record(xen_session *session, xen_task_record **result, xen_task task);


/**
 * Get a reference to the task instance with the specified UUID.
 */
extern bool
xen_task_get_by_uuid(xen_session *session, xen_task *result, char *uuid);


/**
 * Get all the task instances with the given label.
 */
extern bool
xen_task_get_by_name_label(xen_session *session, struct xen_task_set **result, char *label);


/**
 * Get the uuid field of the given task.
 */
extern bool
xen_task_get_uuid(xen_session *session, char **result, xen_task task);


/**
 * Get the name/label field of the given task.
 */
extern bool
xen_task_get_name_label(xen_session *session, char **result, xen_task task);


/**
 * Get the name/description field of the given task.
 */
extern bool
xen_task_get_name_description(xen_session *session, char **result, xen_task task);


/**
 * Get the allowed_operations field of the given task.
 */
extern bool
xen_task_get_allowed_operations(xen_session *session, struct xen_task_allowed_operations_set **result, xen_task task);


/**
 * Get the current_operations field of the given task.
 */
extern bool
xen_task_get_current_operations(xen_session *session, xen_string_task_allowed_operations_map **result, xen_task task);


/**
 * Get the created field of the given task.
 */
extern bool
xen_task_get_created(xen_session *session, time_t *result, xen_task task);


/**
 * Get the finished field of the given task.
 */
extern bool
xen_task_get_finished(xen_session *session, time_t *result, xen_task task);


/**
 * Get the status field of the given task.
 */
extern bool
xen_task_get_status(xen_session *session, enum xen_task_status_type *result, xen_task task);


/**
 * Get the resident_on field of the given task.
 */
extern bool
xen_task_get_resident_on(xen_session *session, xen_host *result, xen_task task);


/**
 * Get the progress field of the given task.
 */
extern bool
xen_task_get_progress(xen_session *session, double *result, xen_task task);


/**
 * Get the type field of the given task.
 */
extern bool
xen_task_get_type(xen_session *session, char **result, xen_task task);


/**
 * Get the result field of the given task.
 */
extern bool
xen_task_get_result(xen_session *session, char **result, xen_task task);


/**
 * Get the error_info field of the given task.
 */
extern bool
xen_task_get_error_info(xen_session *session, struct xen_string_set **result, xen_task task);


/**
 * Get the other_config field of the given task.
 */
extern bool
xen_task_get_other_config(xen_session *session, xen_string_string_map **result, xen_task task);


/**
 * Get the subtask_of field of the given task.
 */
extern bool
xen_task_get_subtask_of(xen_session *session, xen_task *result, xen_task task);


/**
 * Get the subtasks field of the given task.
 */
extern bool
xen_task_get_subtasks(xen_session *session, struct xen_task_set **result, xen_task task);


/**
 * Set the other_config field of the given task.
 */
extern bool
xen_task_set_other_config(xen_session *session, xen_task task, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * task.
 */
extern bool
xen_task_add_to_other_config(xen_session *session, xen_task task, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given task.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_task_remove_from_other_config(xen_session *session, xen_task task, char *key);


/**
 * Create a new task object which must be manually destroyed.
 */
extern bool
xen_task_create(xen_session *session, xen_task *result, char *label, char *description);


/**
 * Destroy the task object.
 */
extern bool
xen_task_destroy(xen_session *session, xen_task self);


/**
 * Request that a task be cancelled. Note that a task may fail to be
 * cancelled and may complete or fail normally and note that, even when a task
 * does cancel, it might take an arbitrary amount of time.
 */
extern bool
xen_task_cancel(xen_session *session, xen_task task);

/**
 * Request that a task be cancelled. Note that a task may fail to be
 * cancelled and may complete or fail normally and note that, even when a task
 * does cancel, it might take an arbitrary amount of time.
 */
extern bool
xen_task_cancel_async(xen_session *session, xen_task *result, xen_task task);


/**
 * Return a list of all the tasks known to the system.
 */
extern bool
xen_task_get_all(xen_session *session, struct xen_task_set **result);


/**
 * Return a map of task references to task records for all tasks known
 * to the system.
 */
extern bool
xen_task_get_all_records(xen_session *session, xen_task_xen_task_record_map **result);


#endif
