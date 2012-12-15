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


#ifndef XEN_PCI_H
#define XEN_PCI_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_host_decl.h>
#include <xen/api/xen_pci_decl.h>
#include <xen/api/xen_pci_xen_pci_record_map.h>
#include <xen/api/xen_string_string_map.h>


/*
 * The PCI class.
 * 
 * A PCI device.
 */


/**
 * Free the given xen_pci.  The given handle must have been allocated
 * by this library.
 */
extern void
xen_pci_free(xen_pci pci);


typedef struct xen_pci_set
{
    size_t size;
    xen_pci *contents[];
} xen_pci_set;

/**
 * Allocate a xen_pci_set of the given size.
 */
extern xen_pci_set *
xen_pci_set_alloc(size_t size);

/**
 * Free the given xen_pci_set.  The given set must have been allocated
 * by this library.
 */
extern void
xen_pci_set_free(xen_pci_set *set);


typedef struct xen_pci_record
{
    xen_pci handle;
    char *uuid;
    char *class_name;
    char *vendor_name;
    char *device_name;
    struct xen_host_record_opt *host;
    char *pci_id;
    struct xen_pci_record_opt_set *dependencies;
    xen_string_string_map *other_config;
} xen_pci_record;

/**
 * Allocate a xen_pci_record.
 */
extern xen_pci_record *
xen_pci_record_alloc(void);

/**
 * Free the given xen_pci_record, and all referenced values.  The given
 * record must have been allocated by this library.
 */
extern void
xen_pci_record_free(xen_pci_record *record);


typedef struct xen_pci_record_opt
{
    bool is_record;
    union
    {
        xen_pci handle;
        xen_pci_record *record;
    } u;
} xen_pci_record_opt;

/**
 * Allocate a xen_pci_record_opt.
 */
extern xen_pci_record_opt *
xen_pci_record_opt_alloc(void);

/**
 * Free the given xen_pci_record_opt, and all referenced values.  The
 * given record_opt must have been allocated by this library.
 */
extern void
xen_pci_record_opt_free(xen_pci_record_opt *record_opt);


typedef struct xen_pci_record_set
{
    size_t size;
    xen_pci_record *contents[];
} xen_pci_record_set;

/**
 * Allocate a xen_pci_record_set of the given size.
 */
extern xen_pci_record_set *
xen_pci_record_set_alloc(size_t size);

/**
 * Free the given xen_pci_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_pci_record_set_free(xen_pci_record_set *set);



typedef struct xen_pci_record_opt_set
{
    size_t size;
    xen_pci_record_opt *contents[];
} xen_pci_record_opt_set;

/**
 * Allocate a xen_pci_record_opt_set of the given size.
 */
extern xen_pci_record_opt_set *
xen_pci_record_opt_set_alloc(size_t size);

/**
 * Free the given xen_pci_record_opt_set, and all referenced values. 
 * The given set must have been allocated by this library.
 */
extern void
xen_pci_record_opt_set_free(xen_pci_record_opt_set *set);


/**
 * Get a record containing the current state of the given PCI.
 */
extern bool
xen_pci_get_record(xen_session *session, xen_pci_record **result, xen_pci pci);


/**
 * Get a reference to the PCI instance with the specified UUID.
 */
extern bool
xen_pci_get_by_uuid(xen_session *session, xen_pci *result, char *uuid);


/**
 * Get the uuid field of the given PCI.
 */
extern bool
xen_pci_get_uuid(xen_session *session, char **result, xen_pci pci);


/**
 * Get the class_name field of the given PCI.
 */
extern bool
xen_pci_get_class_name(xen_session *session, char **result, xen_pci pci);


/**
 * Get the vendor_name field of the given PCI.
 */
extern bool
xen_pci_get_vendor_name(xen_session *session, char **result, xen_pci pci);


/**
 * Get the device_name field of the given PCI.
 */
extern bool
xen_pci_get_device_name(xen_session *session, char **result, xen_pci pci);


/**
 * Get the host field of the given PCI.
 */
extern bool
xen_pci_get_host(xen_session *session, xen_host *result, xen_pci pci);


/**
 * Get the pci_id field of the given PCI.
 */
extern bool
xen_pci_get_pci_id(xen_session *session, char **result, xen_pci pci);


/**
 * Get the dependencies field of the given PCI.
 */
extern bool
xen_pci_get_dependencies(xen_session *session, struct xen_pci_set **result, xen_pci pci);


/**
 * Get the other_config field of the given PCI.
 */
extern bool
xen_pci_get_other_config(xen_session *session, xen_string_string_map **result, xen_pci pci);


/**
 * Set the other_config field of the given PCI.
 */
extern bool
xen_pci_set_other_config(xen_session *session, xen_pci pci, xen_string_string_map *other_config);


/**
 * Add the given key-value pair to the other_config field of the given
 * PCI.
 */
extern bool
xen_pci_add_to_other_config(xen_session *session, xen_pci pci, char *key, char *value);


/**
 * Remove the given key and its corresponding value from the
 * other_config field of the given PCI.  If the key is not in that Map, then
 * do nothing.
 */
extern bool
xen_pci_remove_from_other_config(xen_session *session, xen_pci pci, char *key);


/**
 * Return a list of all the PCIs known to the system.
 */
extern bool
xen_pci_get_all(xen_session *session, struct xen_pci_set **result);


/**
 * Return a map of PCI references to PCI records for all PCIs known to
 * the system.
 */
extern bool
xen_pci_get_all_records(xen_session *session, xen_pci_xen_pci_record_map **result);


#endif
