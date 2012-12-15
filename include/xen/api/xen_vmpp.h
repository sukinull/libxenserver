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


#ifndef XEN_VMPP_H
#define XEN_VMPP_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_string_string_map.h>
#include <xen/api/xen_task_decl.h>
#include <xen/api/xen_vm_decl.h>
#include <xen/api/xen_vmpp_archive_frequency.h>
#include <xen/api/xen_vmpp_archive_target_type.h>
#include <xen/api/xen_vmpp_backup_frequency.h>
#include <xen/api/xen_vmpp_backup_type.h>
#include <xen/api/xen_vmpp_decl.h>
#include <xen/api/xen_vmpp_xen_vmpp_record_map.h>


/*
 * The VMPP class.
 * 
 * VM Protection Policy.
 */


/**
 * Free the given xen_vmpp.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_vmpp_free(xen_vmpp vmpp);


typedef struct xen_vmpp_set
{
    size_t size;
    xen_vmpp *contents[];
} xen_vmpp_set;

/**
 * Allocate a xen_vmpp_set of the given size.
 */
extern xen_vmpp_set *
xen_vmpp_set_alloc(size_t size);

/**
 * Free the given xen_vmpp_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_vmpp_set_free(xen_vmpp_set *set);


typedef struct xen_vmpp_record
{
    xen_vmpp handle;
    char *uuid;
    char *name_label;
    char *name_description;
    bool is_policy_enabled;
    enum xen_vmpp_backup_type backup_type;
    int64_t backup_retention_value;
    enum xen_vmpp_backup_frequency backup_frequency;
    xen_string_string_map *backup_schedule;
    bool is_backup_running;
    time_t backup_last_run_time;
    enum xen_vmpp_archive_target_type archive_target_type;
    xen_string_string_map *archive_target_config;
    enum xen_vmpp_archive_frequency archive_frequency;
    xen_string_string_map *archive_schedule;
    bool is_archive_running;
    time_t archive_last_run_time;
    struct xen_vm_record_opt_set *vms;
    bool is_alarm_enabled;
    xen_string_string_map *alarm_config;
    struct xen_string_set *recent_alerts;
} xen_vmpp_record;

/**
 * Allocate a xen_vmpp_record.
 */
extern xen_vmpp_record *
xen_vmpp_record_alloc(void);

/**
 * Free the given xen_vmpp_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_vmpp_record_free(xen_vmpp_record *record);


typedef struct xen_vmpp_record_opt
{
    bool is_record;
    union
    {
        xen_vmpp handle;
        xen_vmpp_record *record;
    } u;
} xen_vmpp_record_opt;

/**
 * Allocate a xen_vmpp_record_opt.
 */
extern xen_vmpp_record_opt *
xen_vmpp_record_opt_alloc(void);

/**
 * Free the given xen_vmpp_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_vmpp_record_opt_free(xen_vmpp_record_opt *record_opt);


typedef struct xen_vmpp_record_set
{
    size_t size;
    xen_vmpp_record *contents[];
} xen_vmpp_record_set;

/**
 * Allocate a xen_vmpp_record_set of the given size.
 */
extern xen_vmpp_record_set *
xen_vmpp_record_set_alloc(size_t size);

/**
 * Free the given xen_vmpp_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_vmpp_record_set_free(xen_vmpp_record_set *set);



typedef struct xen_vmpp_record_opt_set
{
    size_t size;
    xen_vmpp_record_opt *contents[];
} xen_vmpp_record_opt_set;

/**
 * Allocate a xen_vmpp_record_opt_set of the given size.
 */
extern xen_vmpp_record_opt_set *
xen_vmpp_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_vmpp_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_vmpp_record_opt_set_free(xen_vmpp_record_opt_set *set);


/**
 * Get a record containing the current state of the given VMPP.
 */
extern bool
xen_vmpp_get_record(xen_session *session, xen_vmpp_record **result, xen_vmpp vmpp);


/**
 * Get a reference to the VMPP instance with the specified UUID.
 */
extern bool
xen_vmpp_get_by_uuid(xen_session *session, xen_vmpp *result, char *uuid);


/**
 * Create a new VMPP instance, and return its handle.
 */
extern bool
xen_vmpp_create(xen_session *session, xen_vmpp *result, xen_vmpp_record *record);

/**
 * Create a new VMPP instance, and return its handle.
 */
extern bool
xen_vmpp_create_async(xen_session *session, xen_task *result, xen_vmpp_record *record);


/**
 * Destroy the specified VMPP instance.
 */
extern bool
xen_vmpp_destroy(xen_session *session, xen_vmpp vmpp);

/**
 * Destroy the specified VMPP instance.
 */
extern bool
xen_vmpp_destroy_async(xen_session *session, xen_task *result, xen_vmpp vmpp);


/**
 * Get all the VMPP instances with the given label.
 */
extern bool
xen_vmpp_get_by_name_label(xen_session *session, struct xen_vmpp_set **result, char *label);


/**
 * Get the uuid field of the given VMPP.
 */
extern bool
xen_vmpp_get_uuid(xen_session *session, char **result, xen_vmpp vmpp);


/**
 * Get the name/label field of the given VMPP.
 */
extern bool
xen_vmpp_get_name_label(xen_session *session, char **result, xen_vmpp vmpp);


/**
 * Get the name/description field of the given VMPP.
 */
extern bool
xen_vmpp_get_name_description(xen_session *session, char **result, xen_vmpp vmpp);


/**
 * Get the is_policy_enabled field of the given VMPP.
 */
extern bool
xen_vmpp_get_is_policy_enabled(xen_session *session, bool *result, xen_vmpp vmpp);


/**
 * Get the backup_type field of the given VMPP.
 */
extern bool
xen_vmpp_get_backup_type(xen_session *session, enum xen_vmpp_backup_type *result, xen_vmpp vmpp);


/**
 * Get the backup_retention_value field of the given VMPP.
 */
extern bool
xen_vmpp_get_backup_retention_value(xen_session *session, int64_t *result, xen_vmpp vmpp);


/**
 * Get the backup_frequency field of the given VMPP.
 */
extern bool
xen_vmpp_get_backup_frequency(xen_session *session, enum xen_vmpp_backup_frequency *result, xen_vmpp vmpp);


/**
 * Get the backup_schedule field of the given VMPP.
 */
extern bool
xen_vmpp_get_backup_schedule(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp);


/**
 * Get the is_backup_running field of the given VMPP.
 */
extern bool
xen_vmpp_get_is_backup_running(xen_session *session, bool *result, xen_vmpp vmpp);


/**
 * Get the backup_last_run_time field of the given VMPP.
 */
extern bool
xen_vmpp_get_backup_last_run_time(xen_session *session, time_t *result, xen_vmpp vmpp);


/**
 * Get the archive_target_type field of the given VMPP.
 */
extern bool
xen_vmpp_get_archive_target_type(xen_session *session, enum xen_vmpp_archive_target_type *result, xen_vmpp vmpp);


/**
 * Get the archive_target_config field of the given VMPP.
 */
extern bool
xen_vmpp_get_archive_target_config(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp);


/**
 * Get the archive_frequency field of the given VMPP.
 */
extern bool
xen_vmpp_get_archive_frequency(xen_session *session, enum xen_vmpp_archive_frequency *result, xen_vmpp vmpp);


/**
 * Get the archive_schedule field of the given VMPP.
 */
extern bool
xen_vmpp_get_archive_schedule(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp);


/**
 * Get the is_archive_running field of the given VMPP.
 */
extern bool
xen_vmpp_get_is_archive_running(xen_session *session, bool *result, xen_vmpp vmpp);


/**
 * Get the archive_last_run_time field of the given VMPP.
 */
extern bool
xen_vmpp_get_archive_last_run_time(xen_session *session, time_t *result, xen_vmpp vmpp);


/**
 * Get the VMs field of the given VMPP.
 */
extern bool
xen_vmpp_get_vms(xen_session *session, struct xen_vm_set **result, xen_vmpp vmpp);


/**
 * Get the is_alarm_enabled field of the given VMPP.
 */
extern bool
xen_vmpp_get_is_alarm_enabled(xen_session *session, bool *result, xen_vmpp vmpp);


/**
 * Get the alarm_config field of the given VMPP.
 */
extern bool
xen_vmpp_get_alarm_config(xen_session *session, xen_string_string_map **result, xen_vmpp vmpp);


/**
 * Get the recent_alerts field of the given VMPP.
 */
extern bool
xen_vmpp_get_recent_alerts(xen_session *session, struct xen_string_set **result, xen_vmpp vmpp);


/**
 * Set the name/label field of the given VMPP.
 */
extern bool
xen_vmpp_set_name_label(xen_session *session, xen_vmpp vmpp, char *label);


/**
 * Set the name/description field of the given VMPP.
 */
extern bool
xen_vmpp_set_name_description(xen_session *session, xen_vmpp vmpp, char *description);


/**
 * Set the is_policy_enabled field of the given VMPP.
 */
extern bool
xen_vmpp_set_is_policy_enabled(xen_session *session, xen_vmpp vmpp, bool is_policy_enabled);


/**
 * Set the backup_type field of the given VMPP.
 */
extern bool
xen_vmpp_set_backup_type(xen_session *session, xen_vmpp vmpp, enum xen_vmpp_backup_type backup_type);


/**
 * This call executes the protection policy immediately.
 */
extern bool
xen_vmpp_protect_now(xen_session *session, char **result, xen_vmpp vmpp);


/**
 * This call archives the snapshot provided as a parameter.
 */
extern bool
xen_vmpp_archive_now(xen_session *session, char **result, xen_vm snapshot);


/**
 * This call fetches a history of alerts for a given protection policy.
 */
extern bool
xen_vmpp_get_alerts(xen_session *session, struct xen_string_set **result, xen_vmpp vmpp, int64_t hours_from_now);


/**
 * .
 */
extern bool
xen_vmpp_set_backup_retention_value(xen_session *session, xen_vmpp self, int64_t value);


/**
 * Set the value of the backup_frequency field.
 */
extern bool
xen_vmpp_set_backup_frequency(xen_session *session, xen_vmpp self, enum xen_vmpp_backup_frequency value);


/**
 * .
 */
extern bool
xen_vmpp_set_backup_schedule(xen_session *session, xen_vmpp self, xen_string_string_map *value);


/**
 * Set the value of the archive_frequency field.
 */
extern bool
xen_vmpp_set_archive_frequency(xen_session *session, xen_vmpp self, enum xen_vmpp_archive_frequency value);


/**
 * .
 */
extern bool
xen_vmpp_set_archive_schedule(xen_session *session, xen_vmpp self, xen_string_string_map *value);


/**
 * Set the value of the archive_target_config_type field.
 */
extern bool
xen_vmpp_set_archive_target_type(xen_session *session, xen_vmpp self, enum xen_vmpp_archive_target_type value);


/**
 * .
 */
extern bool
xen_vmpp_set_archive_target_config(xen_session *session, xen_vmpp self, xen_string_string_map *value);


/**
 * Set the value of the is_alarm_enabled field.
 */
extern bool
xen_vmpp_set_is_alarm_enabled(xen_session *session, xen_vmpp self, bool value);


/**
 * .
 */
extern bool
xen_vmpp_set_alarm_config(xen_session *session, xen_vmpp self, xen_string_string_map *value);


/**
 * .
 */
extern bool
xen_vmpp_add_to_backup_schedule(xen_session *session, xen_vmpp self, char *key, char *value);


/**
 * .
 */
extern bool
xen_vmpp_add_to_archive_target_config(xen_session *session, xen_vmpp self, char *key, char *value);


/**
 * .
 */
extern bool
xen_vmpp_add_to_archive_schedule(xen_session *session, xen_vmpp self, char *key, char *value);


/**
 * .
 */
extern bool
xen_vmpp_add_to_alarm_config(xen_session *session, xen_vmpp self, char *key, char *value);


/**
 * .
 */
extern bool
xen_vmpp_remove_from_backup_schedule(xen_session *session, xen_vmpp self, char *key);


/**
 * .
 */
extern bool
xen_vmpp_remove_from_archive_target_config(xen_session *session, xen_vmpp self, char *key);


/**
 * .
 */
extern bool
xen_vmpp_remove_from_archive_schedule(xen_session *session, xen_vmpp self, char *key);


/**
 * .
 */
extern bool
xen_vmpp_remove_from_alarm_config(xen_session *session, xen_vmpp self, char *key);


/**
 * .
 */
extern bool
xen_vmpp_set_backup_last_run_time(xen_session *session, xen_vmpp self, time_t value);


/**
 * .
 */
extern bool
xen_vmpp_set_archive_last_run_time(xen_session *session, xen_vmpp self, time_t value);


/**
 * Return a list of all the VMPPs known to the system.
 */
extern bool
xen_vmpp_get_all(xen_session *session, struct xen_vmpp_set **result);


/**
 * Return a map of VMPP references to VMPP records for all VMPPs known
 * to the system.
 */
extern bool
xen_vmpp_get_all_records(xen_session *session, xen_vmpp_xen_vmpp_record_map **result);


#endif
