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


#ifndef XEN_API_FAILURE_H
#define XEN_API_FAILURE_H


enum xen_api_failure
{
    /**
     * An activation key can only be applied when the edition is
     * set to 'free'.
     */
    XEN_API_FAILURE_ACTIVATION_WHILE_NOT_FREE,

    /**
     * External authentication for this host is already enabled.
     */
    XEN_API_FAILURE_AUTH_ALREADY_ENABLED,

    /**
     * The host failed to disable external authentication.
     */
    XEN_API_FAILURE_AUTH_DISABLE_FAILED,

    /**
     * The host failed to disable external authentication.
     */
    XEN_API_FAILURE_AUTH_DISABLE_FAILED_PERMISSION_DENIED,

    /**
     * The host failed to disable external authentication.
     */
    XEN_API_FAILURE_AUTH_DISABLE_FAILED_WRONG_CREDENTIALS,

    /**
     * The host failed to enable external authentication.
     */
    XEN_API_FAILURE_AUTH_ENABLE_FAILED,

    /**
     * The host failed to enable external authentication.
     */
    XEN_API_FAILURE_AUTH_ENABLE_FAILED_DOMAIN_LOOKUP_FAILED,

    /**
     * The host failed to enable external authentication.
     */
    XEN_API_FAILURE_AUTH_ENABLE_FAILED_PERMISSION_DENIED,

    /**
     * The host failed to enable external authentication.
     */
    XEN_API_FAILURE_AUTH_ENABLE_FAILED_UNAVAILABLE,

    /**
     * The host failed to enable external authentication.
     */
    XEN_API_FAILURE_AUTH_ENABLE_FAILED_WRONG_CREDENTIALS,

    /**
     * External authentication is disabled, unable to resolve
     * subject name.
     */
    XEN_API_FAILURE_AUTH_IS_DISABLED,

    /**
     * Error querying the external directory service.
     */
    XEN_API_FAILURE_AUTH_SERVICE_ERROR,

    /**
     * Unknown type of external authentication.
     */
    XEN_API_FAILURE_AUTH_UNKNOWN_TYPE,

    /**
     * The backup could not be performed because the backup script
     * failed.
     */
    XEN_API_FAILURE_BACKUP_SCRIPT_FAILED,

    /**
     * The bootloader returned an error
     */
    XEN_API_FAILURE_BOOTLOADER_FAILED,

    /**
     * This PIF is a bond slave and cannot have a tunnel on it.
     */
    XEN_API_FAILURE_CANNOT_ADD_TUNNEL_TO_BOND_SLAVE,

    /**
     * This PIF is a bond slave and cannot have a VLAN on it.
     */
    XEN_API_FAILURE_CANNOT_ADD_VLAN_TO_BOND_SLAVE,

    /**
     * Cannot forward messages because the host cannot be
     * contacted.  The host may be switched off or there may be network
     * connectivity problems.
     */
    XEN_API_FAILURE_CANNOT_CONTACT_HOST,

    /**
     * An HA statefile could not be created, perhaps because no SR
     * with the appropriate capability was found.
     */
    XEN_API_FAILURE_CANNOT_CREATE_STATE_FILE,

    /**
     * The disaster recovery task could not be cleanly destroyed.
     */
    XEN_API_FAILURE_CANNOT_DESTROY_DISASTER_RECOVERY_TASK,

    /**
     * You tried to destroy a system network: these cannot be
     * destroyed.
     */
    XEN_API_FAILURE_CANNOT_DESTROY_SYSTEM_NETWORK,

    /**
     * Could not enable redo log.
     */
    XEN_API_FAILURE_CANNOT_ENABLE_REDO_LOG,

    /**
     * This host cannot be evacuated.
     */
    XEN_API_FAILURE_CANNOT_EVACUATE_HOST,

    /**
     * The requested update could to be obtained from the master.
     */
    XEN_API_FAILURE_CANNOT_FETCH_PATCH,

    /**
     * The backup partition to stream the updat to cannot be found
     */
    XEN_API_FAILURE_CANNOT_FIND_OEM_BACKUP_PARTITION,

    /**
     * The requested update could not be found.  This can occur
     * when you designate a new master or xe patch-clean.  Please upload the
     * update again
     */
    XEN_API_FAILURE_CANNOT_FIND_PATCH,

    /**
     * This operation could not be performed because the state
     * partition could not be found
     */
    XEN_API_FAILURE_CANNOT_FIND_STATE_PARTITION,

    /**
     * This PIF is a bond slave and cannot be plugged.
     */
    XEN_API_FAILURE_CANNOT_PLUG_BOND_SLAVE,

    /**
     * Cannot plug VIF
     */
    XEN_API_FAILURE_CANNOT_PLUG_VIF,

    /**
     * The power-state of a control domain cannot be reset.
     */
    XEN_API_FAILURE_CANNOT_RESET_CONTROL_DOMAIN,

    /**
     * A certificate already exists with the specified name.
     */
    XEN_API_FAILURE_CERTIFICATE_ALREADY_EXISTS,

    /**
     * The specified certificate is corrupt or unreadable.
     */
    XEN_API_FAILURE_CERTIFICATE_CORRUPT,

    /**
     * The specified certificate does not exist.
     */
    XEN_API_FAILURE_CERTIFICATE_DOES_NOT_EXIST,

    /**
     * The certificate library is corrupt or unreadable.
     */
    XEN_API_FAILURE_CERTIFICATE_LIBRARY_CORRUPT,

    /**
     * The specified certificate name is invalid.
     */
    XEN_API_FAILURE_CERTIFICATE_NAME_INVALID,

    /**
     * The system rejected the password change request; perhaps the
     * new password was too short?
     */
    XEN_API_FAILURE_CHANGE_PASSWORD_REJECTED,

    /**
     * Could not find a network interface with the specified device
     * name and MAC address.
     */
    XEN_API_FAILURE_COULD_NOT_FIND_NETWORK_INTERFACE_WITH_SPECIFIED_DEVICE_NAME_AND_MAC_ADDRESS,

    /**
     * An error occurred while attempting to import a database from
     * a metadata VDI
     */
    XEN_API_FAILURE_COULD_NOT_IMPORT_DATABASE,

    /**
     * The CPU does not support masking of features.
     */
    XEN_API_FAILURE_CPU_FEATURE_MASKING_NOT_SUPPORTED,

    /**
     * A CRL already exists with the specified name.
     */
    XEN_API_FAILURE_CRL_ALREADY_EXISTS,

    /**
     * The specified CRL is corrupt or unreadable.
     */
    XEN_API_FAILURE_CRL_CORRUPT,

    /**
     * The specified CRL does not exist.
     */
    XEN_API_FAILURE_CRL_DOES_NOT_EXIST,

    /**
     * The specified CRL name is invalid.
     */
    XEN_API_FAILURE_CRL_NAME_INVALID,

    /**
     * You attempted an operation which would have resulted in
     * duplicate keys in the database.
     */
    XEN_API_FAILURE_DB_UNIQUENESS_CONSTRAINT_VIOLATION,

    /**
     * The default SR reference does not point to a valid SR
     */
    XEN_API_FAILURE_DEFAULT_SR_NOT_FOUND,

    /**
     * The device is already attached to a VM
     */
    XEN_API_FAILURE_DEVICE_ALREADY_ATTACHED,

    /**
     * The device is not currently attached
     */
    XEN_API_FAILURE_DEVICE_ALREADY_DETACHED,

    /**
     * A device with the name given already exists on the selected
     * VM
     */
    XEN_API_FAILURE_DEVICE_ALREADY_EXISTS,

    /**
     * A timeout happened while attempting to attach a device to a
     * VM.
     */
    XEN_API_FAILURE_DEVICE_ATTACH_TIMEOUT,

    /**
     * The VM rejected the attempt to detach the device.
     */
    XEN_API_FAILURE_DEVICE_DETACH_REJECTED,

    /**
     * A timeout happened while attempting to detach a device from
     * a VM.
     */
    XEN_API_FAILURE_DEVICE_DETACH_TIMEOUT,

    /**
     * The operation could not be performed because the VBD was not
     * connected to the VM.
     */
    XEN_API_FAILURE_DEVICE_NOT_ATTACHED,

    /**
     * All VBDs of type 'disk' must be read/write for HVM guests
     */
    XEN_API_FAILURE_DISK_VBD_MUST_BE_READWRITE_FOR_HVM,

    /**
     * An internal error generated by the domain builder.
     */
    XEN_API_FAILURE_DOMAIN_BUILDER_ERROR,

    /**
     * The operation could not be performed because a domain still
     * exists for the specified VM.
     */
    XEN_API_FAILURE_DOMAIN_EXISTS,

    /**
     * A PIF with this specified device name already exists.
     */
    XEN_API_FAILURE_DUPLICATE_PIF_DEVICE_NAME,

    /**
     * Cannot restore this VM because it would create a duplicate
     */
    XEN_API_FAILURE_DUPLICATE_VM,

    /**
     * Some events have been lost from the queue and cannot be
     * retrieved.
     */
    XEN_API_FAILURE_EVENTS_LOST,

    /**
     * The event.from token could not be parsed. Valid values
     * include: '', and a value returned from a previous event.from call.
     */
    XEN_API_FAILURE_EVENT_FROM_TOKEN_PARSE_FAILURE,

    /**
     * The server failed to parse your event subscription. Valid
     * values include: *, class-name, class-name/object-reference.
     */
    XEN_API_FAILURE_EVENT_SUBSCRIPTION_PARSE_FAILURE,

    /**
     * The VM is set up to use a feature that requires it to boot
     * as HVM.
     */
    XEN_API_FAILURE_FEATURE_REQUIRES_HVM,

    /**
     * The use of this feature is restricted.
     */
    XEN_API_FAILURE_FEATURE_RESTRICTED,

    /**
     * The value specified is of the wrong type
     */
    XEN_API_FAILURE_FIELD_TYPE_ERROR,

    /**
     * The GPU group contains active PGPUs and cannot be deleted.
     */
    XEN_API_FAILURE_GPU_GROUP_CONTAINS_PGPU,

    /**
     * The GPU group contains active VGPUs and cannot be deleted.
     */
    XEN_API_FAILURE_GPU_GROUP_CONTAINS_VGPU,

    /**
     * You gave an invalid object reference.  The object may have
     * recently been deleted.  The class parameter gives the type of reference
     * given, and the handle parameter echoes the bad value given.
     */
    XEN_API_FAILURE_HANDLE_INVALID,

    /**
     * This host cannot accept the proposed new master setting at
     * this time.
     */
    XEN_API_FAILURE_HA_ABORT_NEW_MASTER,

    /**
     * This operation cannot be performed because creating or
     * deleting a bond involving the management interface is not allowed while HA
     * is on. In order to do that, disable HA, create or delete the bond then
     * re-enable HA.
     */
    XEN_API_FAILURE_HA_CANNOT_CHANGE_BOND_STATUS_OF_MGMT_IFACE,

    /**
     * This operation cannot be performed because the referenced
     * network is not properly shared. The network must either be entirely virtual
     * or must be physically present via a currently_attached PIF on every host.
     */
    XEN_API_FAILURE_HA_CONSTRAINT_VIOLATION_NETWORK_NOT_SHARED,

    /**
     * This operation cannot be performed because the referenced SR
     * is not properly shared. The SR must both be marked as shared and a
     * currently_attached PBD must exist for each host.
     */
    XEN_API_FAILURE_HA_CONSTRAINT_VIOLATION_SR_NOT_SHARED,

    /**
     * HA could not be enabled on the Pool because a liveset could
     * not be formed: check storage and network heartbeat paths.
     */
    XEN_API_FAILURE_HA_FAILED_TO_FORM_LIVESET,

    /**
     * The host could not join the liveset because the HA daemon
     * failed to start.
     */
    XEN_API_FAILURE_HA_HEARTBEAT_DAEMON_STARTUP_FAILED,

    /**
     * The host could not join the liveset because the HA daemon
     * could not access the heartbeat disk.
     */
    XEN_API_FAILURE_HA_HOST_CANNOT_ACCESS_STATEFILE,

    /**
     * The operation failed because the HA software on the
     * specified host could not see a subset of other hosts. Check your network
     * connectivity.
     */
    XEN_API_FAILURE_HA_HOST_CANNOT_SEE_PEERS,

    /**
     * The operation could not be performed while the host is still
     * armed; it must be disarmed first
     */
    XEN_API_FAILURE_HA_HOST_IS_ARMED,

    /**
     * The operation could not be performed because HA is enabled
     * on the Pool
     */
    XEN_API_FAILURE_HA_IS_ENABLED,

    /**
     * This host lost access to the HA statefile.
     */
    XEN_API_FAILURE_HA_LOST_STATEFILE,

    /**
     * The operation could not be performed because HA is not
     * enabled on the Pool
     */
    XEN_API_FAILURE_HA_NOT_ENABLED,

    /**
     * The operation could not be performed because the HA software
     * is not installed on this host.
     */
    XEN_API_FAILURE_HA_NOT_INSTALLED,

    /**
     * Cannot find a plan for placement of VMs as there are no
     * other hosts available.
     */
    XEN_API_FAILURE_HA_NO_PLAN,

    /**
     * This operation cannot be performed because it would
     * invalidate VM failover planning such that the system would be unable to
     * guarantee to restart protected VMs after a Host failure.
     */
    XEN_API_FAILURE_HA_OPERATION_WOULD_BREAK_FAILOVER_PLAN,

    /**
     * This host cannot join the pool because the pool has HA
     * enabled but this host has HA disabled.
     */
    XEN_API_FAILURE_HA_POOL_IS_ENABLED_BUT_HOST_IS_DISABLED,

    /**
     * Host cannot rejoin pool because it should have fenced (it is
     * not in the master's partition)
     */
    XEN_API_FAILURE_HA_SHOULD_BE_FENCED,

    /**
     * HA can only be enabled for 2 hosts or more. Note that 2
     * hosts requires a pre-configured quorum tiebreak script.
     */
    XEN_API_FAILURE_HA_TOO_FEW_HOSTS,

    /**
     * The hosts in this pool are not compatible.
     */
    XEN_API_FAILURE_HOSTS_NOT_COMPATIBLE,

    /**
     * The hosts in this pool are not homogeneous.
     */
    XEN_API_FAILURE_HOSTS_NOT_HOMOGENEOUS,

    /**
     * This host failed in the middle of an automatic failover
     * operation and needs to retry the failover action
     */
    XEN_API_FAILURE_HOST_BROKEN,

    /**
     * Host cannot attach network (in the case of NIC bonding, this
     * may be because attaching the network on this host would require other
     * networks [that are currently active] to be taken down).
     */
    XEN_API_FAILURE_HOST_CANNOT_ATTACH_NETWORK,

    /**
     * The pool master host cannot be removed.
     */
    XEN_API_FAILURE_HOST_CANNOT_DESTROY_SELF,

    /**
     * The metrics of this host could not be read.
     */
    XEN_API_FAILURE_HOST_CANNOT_READ_METRICS,

    /**
     * The host CDROM drive does not contain a valid CD
     */
    XEN_API_FAILURE_HOST_CD_DRIVE_EMPTY,

    /**
     * The specified host is disabled.
     */
    XEN_API_FAILURE_HOST_DISABLED,

    /**
     * The specified host is disabled and cannot be re-enabled
     * until after it has rebooted.
     */
    XEN_API_FAILURE_HOST_DISABLED_UNTIL_REBOOT,

    /**
     * The host failed to acquire an IP address on its management
     * interface and therefore cannot contact the master.
     */
    XEN_API_FAILURE_HOST_HAS_NO_MANAGEMENT_IP,

    /**
     * This host can not be forgotten because there are some user
     * VMs still running
     */
    XEN_API_FAILURE_HOST_HAS_RESIDENT_VMS,

    /**
     * Cannot perform operation as the host is running in emergency
     * mode.
     */
    XEN_API_FAILURE_HOST_IN_EMERGENCY_MODE,

    /**
     * This operation cannot be completed as the host is in use by
     * (at least) the object of type and ref echoed below.
     */
    XEN_API_FAILURE_HOST_IN_USE,

    /**
     * This operation cannot be completed as the host is still
     * live.
     */
    XEN_API_FAILURE_HOST_IS_LIVE,

    /**
     * You cannot make regular API calls directly on a slave.
     * Please pass API calls via the master host.
     */
    XEN_API_FAILURE_HOST_IS_SLAVE,

    /**
     * The host is its own slave. Please use
     * pool-emergency-transition-to-master or pool-emergency-reset-master.
     */
    XEN_API_FAILURE_HOST_ITS_OWN_SLAVE,

    /**
     * The master reports that it cannot talk back to the slave on
     * the supplied management IP address.
     */
    XEN_API_FAILURE_HOST_MASTER_CANNOT_TALK_BACK,

    /**
     * The host name is invalid.
     */
    XEN_API_FAILURE_HOST_NAME_INVALID,

    /**
     * This operation cannot be performed because the host is not
     * disabled. Please disable the host and then try again.
     */
    XEN_API_FAILURE_HOST_NOT_DISABLED,

    /**
     * Not enough host memory is available to perform this
     * operation
     */
    XEN_API_FAILURE_HOST_NOT_ENOUGH_FREE_MEMORY,

    /**
     * This operation cannot be completed as the host is not live.
     */
    XEN_API_FAILURE_HOST_NOT_LIVE,

    /**
     * You attempted an operation which involves a host which could
     * not be contacted.
     */
    XEN_API_FAILURE_HOST_OFFLINE,

    /**
     * This operation cannot be completed as the host power on mode
     * is disabled.
     */
    XEN_API_FAILURE_HOST_POWER_ON_MODE_DISABLED,

    /**
     * The host toolstack is still initialising. Please wait.
     */
    XEN_API_FAILURE_HOST_STILL_BOOTING,

    /**
     * The master says the host is not known to it. Perhaps the
     * Host was deleted from the master's database? Perhaps the slave is pointing
     * to the wrong master?
     */
    XEN_API_FAILURE_HOST_UNKNOWN_TO_MASTER,

    /**
     * The specified VBD device is not recognised: please use a
     * non-negative integer
     */
    XEN_API_FAILURE_ILLEGAL_VBD_DEVICE,

    /**
     * The VM could not be imported.
     */
    XEN_API_FAILURE_IMPORT_ERROR,

    /**
     * The VM could not be imported because attached disks could
     * not be found.
     */
    XEN_API_FAILURE_IMPORT_ERROR_ATTACHED_DISKS_NOT_FOUND,

    /**
     * Cannot import VM using chunked encoding.
     */
    XEN_API_FAILURE_IMPORT_ERROR_CANNOT_HANDLE_CHUNKED,

    /**
     * The VM could not be imported because a required object could
     * not be found.
     */
    XEN_API_FAILURE_IMPORT_ERROR_FAILED_TO_FIND_OBJECT,

    /**
     * The VM could not be imported; the end of the file was
     * reached prematurely.
     */
    XEN_API_FAILURE_IMPORT_ERROR_PREMATURE_EOF,

    /**
     * Some data checksums were incorrect; the VM may be corrupt.
     */
    XEN_API_FAILURE_IMPORT_ERROR_SOME_CHECKSUMS_FAILED,

    /**
     * The VM could not be imported because the XVA file is
     * invalid: an unexpected file was encountered.
     */
    XEN_API_FAILURE_IMPORT_ERROR_UNEXPECTED_FILE,

    /**
     * The import failed because this export has been created by a
     * different (incompatible) product version
     */
    XEN_API_FAILURE_IMPORT_INCOMPATIBLE_VERSION,

    /**
     * The specified interface cannot be used because it has no IP
     * address
     */
    XEN_API_FAILURE_INTERFACE_HAS_NO_IP,

    /**
     * The server failed to handle your request, due to an internal
     * error.  The given message may give details useful for debugging the
     * problem.
     */
    XEN_API_FAILURE_INTERNAL_ERROR,

    /**
     * The device name is invalid
     */
    XEN_API_FAILURE_INVALID_DEVICE,

    /**
     * The edition you supplied is invalid.
     */
    XEN_API_FAILURE_INVALID_EDITION,

    /**
     * The given feature string is not valid.
     */
    XEN_API_FAILURE_INVALID_FEATURE_STRING,

    /**
     * A required parameter contained an invalid IP address
     */
    XEN_API_FAILURE_INVALID_IP_ADDRESS_SPECIFIED,

    /**
     * The uploaded patch file is invalid
     */
    XEN_API_FAILURE_INVALID_PATCH,

    /**
     * The uploaded patch file is invalid.  See attached log for
     * more details.
     */
    XEN_API_FAILURE_INVALID_PATCH_WITH_LOG,

    /**
     * The value given is invalid
     */
    XEN_API_FAILURE_INVALID_VALUE,

    /**
     * You tried to create a VLAN or tunnel on top of a tunnel
     * access PIF - use the underlying transport PIF instead.
     */
    XEN_API_FAILURE_IS_TUNNEL_ACCESS_PIF,

    /**
     * The host joining the pool cannot already be a master of
     * another pool.
     */
    XEN_API_FAILURE_JOINING_HOST_CANNOT_BE_MASTER_OF_OTHER_HOSTS,

    /**
     * The host joining the pool cannot contain any shared storage.
     */
    XEN_API_FAILURE_JOINING_HOST_CANNOT_CONTAIN_SHARED_SRS,

    /**
     * The host joining the pool cannot have any running or
     * suspended VMs.
     */
    XEN_API_FAILURE_JOINING_HOST_CANNOT_HAVE_RUNNING_OR_SUSPENDED_VMS,

    /**
     * The host joining the pool cannot have any running VMs.
     */
    XEN_API_FAILURE_JOINING_HOST_CANNOT_HAVE_RUNNING_VMS,

    /**
     * The host joining the pool cannot have any VMs with active
     * tasks.
     */
    XEN_API_FAILURE_JOINING_HOST_CANNOT_HAVE_VMS_WITH_CURRENT_OPERATIONS,

    /**
     * There was an error connecting to the host while joining it
     * in the pool.
     */
    XEN_API_FAILURE_JOINING_HOST_CONNECTION_FAILED,

    /**
     * There was an error connecting to the host. the service
     * contacted didn't reply properly.
     */
    XEN_API_FAILURE_JOINING_HOST_SERVICE_FAILED,

    /**
     * This operation is not allowed under your license.  Please
     * contact your support representative.
     */
    XEN_API_FAILURE_LICENCE_RESTRICTION,

    /**
     * Cannot downgrade license while in pool. Please disband the
     * pool first, then downgrade licenses on hosts separately.
     */
    XEN_API_FAILURE_LICENSE_CANNOT_DOWNGRADE_WHILE_IN_POOL,

    /**
     * The license for the edition you requested is not available.
     */
    XEN_API_FAILURE_LICENSE_CHECKOUT_ERROR,

    /**
     * This host cannot join a pool because it's license does not
     * support pooling
     */
    XEN_API_FAILURE_LICENSE_DOES_NOT_SUPPORT_POOLING,

    /**
     * XHA cannot be enabled because this host's license does not
     * allow it
     */
    XEN_API_FAILURE_LICENSE_DOES_NOT_SUPPORT_XHA,

    /**
     * Your license has expired.  Please contact your support
     * representative.
     */
    XEN_API_FAILURE_LICENSE_EXPIRED,

    /**
     * This license file is no longer accepted. Please upgrade to
     * the new licensing system.
     */
    XEN_API_FAILURE_LICENSE_FILE_DEPRECATED,

    /**
     * There was an error processing your license.  Please contact
     * your support representative.
     */
    XEN_API_FAILURE_LICENSE_PROCESSING_ERROR,

    /**
     * A VDI with the specified location already exists within the
     * SR
     */
    XEN_API_FAILURE_LOCATION_NOT_UNIQUE,

    /**
     * The MAC address specified doesn't exist on this host.
     */
    XEN_API_FAILURE_MAC_DOES_NOT_EXIST,

    /**
     * The MAC address specified is not valid.
     */
    XEN_API_FAILURE_MAC_INVALID,

    /**
     * The MAC address specified still exists on this host.
     */
    XEN_API_FAILURE_MAC_STILL_EXISTS,

    /**
     * You tried to add a key-value pair to a map, but that key is
     * already there.
     */
    XEN_API_FAILURE_MAP_DUPLICATE_KEY,

    /**
     * This message has been deprecated.
     */
    XEN_API_FAILURE_MESSAGE_DEPRECATED,

    /**
     * You tried to call a method that does not exist.  The method
     * name that you used is echoed.
     */
    XEN_API_FAILURE_MESSAGE_METHOD_UNKNOWN,

    /**
     * You tried to call a method with the incorrect number of
     * parameters.  The fully-qualified method name that you used, and the number
     * of received and expected parameters are returned.
     */
    XEN_API_FAILURE_MESSAGE_PARAMETER_COUNT_MISMATCH,

    /**
     * The VDI mirroring cannot be performed
     */
    XEN_API_FAILURE_MIRROR_FAILED,

    /**
     * The license-server connection details (address or port) were
     * missing or incomplete.
     */
    XEN_API_FAILURE_MISSING_CONNECTION_DETAILS,

    /**
     * You tried to create a PIF, but the network you tried to
     * attach it to is already attached to some other PIF, and so the creation
     * failed.
     */
    XEN_API_FAILURE_NETWORK_ALREADY_CONNECTED,

    /**
     * The network contains active PIFs and cannot be deleted.
     */
    XEN_API_FAILURE_NETWORK_CONTAINS_PIF,

    /**
     * The network contains active VIFs and cannot be deleted.
     */
    XEN_API_FAILURE_NETWORK_CONTAINS_VIF,

    /**
     * This command is not allowed on the OEM edition.
     */
    XEN_API_FAILURE_NOT_ALLOWED_ON_OEM_EDITION,

    /**
     * The function is not implemented
     */
    XEN_API_FAILURE_NOT_IMPLEMENTED,

    /**
     * This pool is not in emergency mode.
     */
    XEN_API_FAILURE_NOT_IN_EMERGENCY_MODE,

    /**
     * This operation is not supported during an upgrade.
     */
    XEN_API_FAILURE_NOT_SUPPORTED_DURING_UPGRADE,

    /**
     * The given VM is not registered as a system domain. This
     * operation can only be performed on a registered system domain.
     */
    XEN_API_FAILURE_NOT_SYSTEM_DOMAIN,

    /**
     * There were no hosts available to complete the specified
     * operation.
     */
    XEN_API_FAILURE_NO_HOSTS_AVAILABLE,

    /**
     * The upper limit of active redo log instances was reached.
     */
    XEN_API_FAILURE_NO_MORE_REDO_LOGS_ALLOWED,

    /**
     * The specified object no longer exists.
     */
    XEN_API_FAILURE_OBJECT_NOLONGER_EXISTS,

    /**
     * This command is only allowed on the OEM edition.
     */
    XEN_API_FAILURE_ONLY_ALLOWED_ON_OEM_EDITION,

    /**
     * This operation needs the OpenVSwitch networking backend to
     * be enabled on all hosts in the pool.
     */
    XEN_API_FAILURE_OPENVSWITCH_NOT_ACTIVE,

    /**
     * You attempted an operation that was explicitly blocked (see
     * the blocked_operations field of the given object).
     */
    XEN_API_FAILURE_OPERATION_BLOCKED,

    /**
     * You attempted an operation that was not allowed.
     */
    XEN_API_FAILURE_OPERATION_NOT_ALLOWED,

    /**
     * Some VMs belonging to the appliance threw an exception while
     * carrying out the specified operation
     */
    XEN_API_FAILURE_OPERATION_PARTIALLY_FAILED,

    /**
     * Another operation involving the object is currently in
     * progress
     */
    XEN_API_FAILURE_OTHER_OPERATION_IN_PROGRESS,

    /**
     * There is not enough space to upload the update
     */
    XEN_API_FAILURE_OUT_OF_SPACE,

    /**
     * This patch has already been applied
     */
    XEN_API_FAILURE_PATCH_ALREADY_APPLIED,

    /**
     * The uploaded patch file already exists
     */
    XEN_API_FAILURE_PATCH_ALREADY_EXISTS,

    /**
     * The patch apply failed.  Please see attached output.
     */
    XEN_API_FAILURE_PATCH_APPLY_FAILED,

    /**
     * The specified patch is applied and cannot be destroyed.
     */
    XEN_API_FAILURE_PATCH_IS_APPLIED,

    /**
     * The patch precheck stage failed: prerequisite patches are
     * missing.
     */
    XEN_API_FAILURE_PATCH_PRECHECK_FAILED_PREREQUISITE_MISSING,

    /**
     * The patch precheck stage failed with an unknown error.  See
     * attached info for more details.
     */
    XEN_API_FAILURE_PATCH_PRECHECK_FAILED_UNKNOWN_ERROR,

    /**
     * The patch precheck stage failed: there are one or more VMs
     * still running on the server.  All VMs must be suspended before the patch
     * can be applied.
     */
    XEN_API_FAILURE_PATCH_PRECHECK_FAILED_VM_RUNNING,

    /**
     * The patch precheck stage failed: the server is of an
     * incorrect build.
     */
    XEN_API_FAILURE_PATCH_PRECHECK_FAILED_WRONG_SERVER_BUILD,

    /**
     * The patch precheck stage failed: the server is of an
     * incorrect version.
     */
    XEN_API_FAILURE_PATCH_PRECHECK_FAILED_WRONG_SERVER_VERSION,

    /**
     * A PBD already exists connecting the SR to the host
     */
    XEN_API_FAILURE_PBD_EXISTS,

    /**
     * Caller not allowed to perform this operation.
     */
    XEN_API_FAILURE_PERMISSION_DENIED,

    /**
     * This operation cannot be performed because the pif is
     * bonded.
     */
    XEN_API_FAILURE_PIF_ALREADY_BONDED,

    /**
     * A bond must consist of at least two member interfaces
     */
    XEN_API_FAILURE_PIF_BOND_NEEDS_MORE_MEMBERS,

    /**
     * You cannot bond interfaces across different hosts.
     */
    XEN_API_FAILURE_PIF_CANNOT_BOND_CROSS_HOST,

    /**
     * An unknown error occurred while attempting to configure an
     * interface.
     */
    XEN_API_FAILURE_PIF_CONFIGURATION_ERROR,

    /**
     * The specified device was not found.
     */
    XEN_API_FAILURE_PIF_DEVICE_NOT_FOUND,

    /**
     * The operation you requested cannot be performed because the
     * specified PIF does not allow unplug.
     */
    XEN_API_FAILURE_PIF_DOES_NOT_ALLOW_UNPLUG,

    /**
     * PIF has no IP configuration (mode curently set to 'none')
     */
    XEN_API_FAILURE_PIF_HAS_NO_NETWORK_CONFIGURATION,

    /**
     * PIF has no IPv6 configuration (mode curently set to 'none')
     */
    XEN_API_FAILURE_PIF_HAS_NO_V6_NETWORK_CONFIGURATION,

    /**
     * The primary address types are not compatible
     */
    XEN_API_FAILURE_PIF_INCOMPATIBLE_PRIMARY_ADDRESS_TYPE,

    /**
     * The operation you requested cannot be performed because the
     * specified PIF is the management interface.
     */
    XEN_API_FAILURE_PIF_IS_MANAGEMENT_INTERFACE,

    /**
     * You tried to destroy a PIF, but it represents an aspect of
     * the physical host configuration, and so cannot be destroyed.  The parameter
     * echoes the PIF handle you gave.
     */
    XEN_API_FAILURE_PIF_IS_PHYSICAL,

    /**
     * You tried to create a VLAN on top of another VLAN - use the
     * underlying physical PIF/bond instead
     */
    XEN_API_FAILURE_PIF_IS_VLAN,

    /**
     * Operation cannot proceed while a tunnel exists on this
     * interface.
     */
    XEN_API_FAILURE_PIF_TUNNEL_STILL_EXISTS,

    /**
     * You tried to create a PIF, but it already exists.
     */
    XEN_API_FAILURE_PIF_VLAN_EXISTS,

    /**
     * Operation cannot proceed while a VLAN exists on this
     * interface.
     */
    XEN_API_FAILURE_PIF_VLAN_STILL_EXISTS,

    /**
     * External authentication in this pool is already enabled for
     * at least one host.
     */
    XEN_API_FAILURE_POOL_AUTH_ALREADY_ENABLED,

    /**
     * The pool failed to disable the external authentication of at
     * least one host.
     */
    XEN_API_FAILURE_POOL_AUTH_DISABLE_FAILED,

    /**
     * The pool failed to disable the external authentication of at
     * least one host.
     */
    XEN_API_FAILURE_POOL_AUTH_DISABLE_FAILED_PERMISSION_DENIED,

    /**
     * The pool failed to disable the external authentication of at
     * least one host.
     */
    XEN_API_FAILURE_POOL_AUTH_DISABLE_FAILED_WRONG_CREDENTIALS,

    /**
     * The pool failed to enable external authentication.
     */
    XEN_API_FAILURE_POOL_AUTH_ENABLE_FAILED,

    /**
     * The pool failed to enable external authentication.
     */
    XEN_API_FAILURE_POOL_AUTH_ENABLE_FAILED_DOMAIN_LOOKUP_FAILED,

    /**
     * The pool failed to enable external authentication.
     */
    XEN_API_FAILURE_POOL_AUTH_ENABLE_FAILED_DUPLICATE_HOSTNAME,

    /**
     * The pool failed to enable external authentication.
     */
    XEN_API_FAILURE_POOL_AUTH_ENABLE_FAILED_INVALID_OU,

    /**
     * The pool failed to enable external authentication.
     */
    XEN_API_FAILURE_POOL_AUTH_ENABLE_FAILED_PERMISSION_DENIED,

    /**
     * The pool failed to enable external authentication.
     */
    XEN_API_FAILURE_POOL_AUTH_ENABLE_FAILED_WRONG_CREDENTIALS,

    /**
     * Cannot join pool whose external authentication configuration
     * is different.
     */
    XEN_API_FAILURE_POOL_JOINING_EXTERNAL_AUTH_MISMATCH,

    /**
     * The host joining the pool must have a physical management
     * NIC (i.e. the management NIC must not be on a VLAN or bonded PIF).
     */
    XEN_API_FAILURE_POOL_JOINING_HOST_MUST_HAVE_PHYSICAL_MANAGEMENT_NIC,

    /**
     * The host joining the pool must have the same product version
     * as the pool master.
     */
    XEN_API_FAILURE_POOL_JOINING_HOST_MUST_HAVE_SAME_PRODUCT_VERSION,

    /**
     * The provision call failed because it ran out of space.
     */
    XEN_API_FAILURE_PROVISION_FAILED_OUT_OF_SPACE,

    /**
     * The provision call can only be invoked on templates, not
     * regular VMs.
     */
    XEN_API_FAILURE_PROVISION_ONLY_ALLOWED_ON_TEMPLATE,

    /**
     * RBAC permission denied.
     */
    XEN_API_FAILURE_RBAC_PERMISSION_DENIED,

    /**
     * The operation could not be performed because a redo log is
     * enabled on the Pool.
     */
    XEN_API_FAILURE_REDO_LOG_IS_ENABLED,

    /**
     * The restore could not be performed because this backup has
     * been created by a different (incompatible) product version
     */
    XEN_API_FAILURE_RESTORE_INCOMPATIBLE_VERSION,

    /**
     * The restore could not be performed because the restore
     * script failed.  Is the file corrupt?
     */
    XEN_API_FAILURE_RESTORE_SCRIPT_FAILED,

    /**
     * The restore could not be performed because the host's
     * current management interface is not in the backup. The interfaces mentioned
     * in the backup are:
     */
    XEN_API_FAILURE_RESTORE_TARGET_MGMT_IF_NOT_IN_BACKUP,

    /**
     * The restore could not be performed because a network
     * interface is missing
     */
    XEN_API_FAILURE_RESTORE_TARGET_MISSING_DEVICE,

    /**
     * Role already exists.
     */
    XEN_API_FAILURE_ROLE_ALREADY_EXISTS,

    /**
     * Role cannot be found.
     */
    XEN_API_FAILURE_ROLE_NOT_FOUND,

    /**
     * The credentials given by the user are incorrect, so access
     * has been denied, and you have not been issued a session handle.
     */
    XEN_API_FAILURE_SESSION_AUTHENTICATION_FAILED,

    /**
     * You gave an invalid session reference.  It may have been
     * invalidated by a server restart, or timed out.  You should get a new
     * session handle, using one of the session.login_ calls.  This error does not
     * invalidate the current connection.  The handle parameter echoes the bad
     * value given.
     */
    XEN_API_FAILURE_SESSION_INVALID,

    /**
     * This session is not registered to receive events.  You must
     * call event.register before event.next.  The session handle you are using is
     * echoed.
     */
    XEN_API_FAILURE_SESSION_NOT_REGISTERED,

    /**
     * The management interface on a slave cannot be disabled
     * because the slave would enter emergency mode.
     */
    XEN_API_FAILURE_SLAVE_REQUIRES_MANAGEMENT_INTERFACE,

    /**
     * The SM plugin did not respond to a query.
     */
    XEN_API_FAILURE_SM_PLUGIN_COMMUNICATION_FAILURE,

    /**
     * Attaching this SR failed.
     */
    XEN_API_FAILURE_SR_ATTACH_FAILED,

    /**
     * There was an SR backend failure.
     */
    XEN_API_FAILURE_SR_BACKEND_FAILURE,

    /**
     * The SR operation cannot be performed because a device
     * underlying the SR is in use by the host.
     */
    XEN_API_FAILURE_SR_DEVICE_IN_USE,

    /**
     * The SR is full. Requested new size exceeds the maximum size
     */
    XEN_API_FAILURE_SR_FULL,

    /**
     * The SR.shared flag cannot be set to false while the SR
     * remains connected to multiple hosts
     */
    XEN_API_FAILURE_SR_HAS_MULTIPLE_PBDS,

    /**
     * The SR has no attached PBDs
     */
    XEN_API_FAILURE_SR_HAS_NO_PBDS,

    /**
     * The SR is still connected to a host via a PBD. It cannot be
     * destroyed or forgotten.
     */
    XEN_API_FAILURE_SR_HAS_PBD,

    /**
     * The SR could not be destroyed, as the 'indestructible' flag
     * was set on it.
     */
    XEN_API_FAILURE_SR_INDESTRUCTIBLE,

    /**
     * The SR operation cannot be performed because the SR is not
     * empty.
     */
    XEN_API_FAILURE_SR_NOT_EMPTY,

    /**
     * The PBD could not be plugged because the SR is in use by
     * another host and is not marked as sharable.
     */
    XEN_API_FAILURE_SR_NOT_SHARABLE,

    /**
     * The SR backend does not support the operation (check the
     * SR's allowed operations)
     */
    XEN_API_FAILURE_SR_OPERATION_NOT_SUPPORTED,

    /**
     * The operation cannot be performed until the SR has been
     * upgraded
     */
    XEN_API_FAILURE_SR_REQUIRES_UPGRADE,

    /**
     * The SR could not be connected because the driver was not
     * recognised.
     */
    XEN_API_FAILURE_SR_UNKNOWN_DRIVER,

    /**
     * An SR with that uuid already exists.
     */
    XEN_API_FAILURE_SR_UUID_EXISTS,

    /**
     * The operation could not proceed because necessary VDIs were
     * already locked at the storage level.
     */
    XEN_API_FAILURE_SR_VDI_LOCKING_FAILED,

    /**
     * The remote system's SSL certificate failed to verify against
     * our certificate library.
     */
    XEN_API_FAILURE_SSL_VERIFY_ERROR,

    /**
     * Subject already exists.
     */
    XEN_API_FAILURE_SUBJECT_ALREADY_EXISTS,

    /**
     * Subject cannot be resolved by the external directory
     * service.
     */
    XEN_API_FAILURE_SUBJECT_CANNOT_BE_RESOLVED,

    /**
     * You must use tar output to retrieve system status from an
     * OEM host.
     */
    XEN_API_FAILURE_SYSTEM_STATUS_MUST_USE_TAR_ON_OEM,

    /**
     * Retrieving system status from the host failed.  A diagnostic
     * reason suitable for support organisations is also returned.
     */
    XEN_API_FAILURE_SYSTEM_STATUS_RETRIEVAL_FAILED,

    /**
     * The request was asynchronously cancelled.
     */
    XEN_API_FAILURE_TASK_CANCELLED,

    /**
     * The request was rejected because the server is too busy.
     */
    XEN_API_FAILURE_TOO_BUSY,

    /**
     * The request was rejected because there are too many pending
     * tasks on the server.
     */
    XEN_API_FAILURE_TOO_MANY_PENDING_TASKS,

    /**
     * You reached the maximal number of concurrently migrating
     * VMs.
     */
    XEN_API_FAILURE_TOO_MANY_STORAGE_MIGRATES,

    /**
     * The tunnel transport PIF has no IP configuration set.
     */
    XEN_API_FAILURE_TRANSPORT_PIF_NOT_CONFIGURED,

    /**
     * The requested bootloader is unknown
     */
    XEN_API_FAILURE_UNKNOWN_BOOTLOADER,

    /**
     * Only the local superuser can execute this operation
     */
    XEN_API_FAILURE_USER_IS_NOT_LOCAL_SUPERUSER,

    /**
     * The uuid you supplied was invalid.
     */
    XEN_API_FAILURE_UUID_INVALID,

    /**
     * There was a problem with the license daemon (v6d). Is it
     * running?
     */
    XEN_API_FAILURE_V6D_FAILURE,

    /**
     * You attempted to set a value that is not supported by this
     * implementation.  The fully-qualified field name and the value that you
     * tried to set are returned.  Also returned is a developer-only diagnostic
     * reason.
     */
    XEN_API_FAILURE_VALUE_NOT_SUPPORTED,

    /**
     * Read/write CDs are not supported
     */
    XEN_API_FAILURE_VBD_CDS_MUST_BE_READONLY,

    /**
     * Operation could not be performed because the drive is empty
     */
    XEN_API_FAILURE_VBD_IS_EMPTY,

    /**
     * Operation could not be performed because the drive is not
     * empty
     */
    XEN_API_FAILURE_VBD_NOT_EMPTY,

    /**
     * Media could not be ejected because it is not removable
     */
    XEN_API_FAILURE_VBD_NOT_REMOVABLE_MEDIA,

    /**
     * Drive could not be hot-unplugged because it is not marked as
     * unpluggable
     */
    XEN_API_FAILURE_VBD_NOT_UNPLUGGABLE,

    /**
     * This VM has locked the DVD drive tray, so the disk cannot be
     * ejected
     */
    XEN_API_FAILURE_VBD_TRAY_LOCKED,

    /**
     * The VDI could not be opened for metadata recovery as it
     * contains the current pool's metadata.
     */
    XEN_API_FAILURE_VDI_CONTAINS_METADATA_OF_THIS_POOL,

    /**
     * This operation cannot be performed because the specified VDI
     * is of an incompatible type (eg: an HA statefile cannot be attached to a
     * guest)
     */
    XEN_API_FAILURE_VDI_INCOMPATIBLE_TYPE,

    /**
     * This operation cannot be performed because this VDI is in
     * use by some other operation
     */
    XEN_API_FAILURE_VDI_IN_USE,

    /**
     * The operation cannot be performed on physical device
     */
    XEN_API_FAILURE_VDI_IS_A_PHYSICAL_DEVICE,

    /**
     * This operation can only be performed on CD VDIs (iso files
     * or CDROM drives)
     */
    XEN_API_FAILURE_VDI_IS_NOT_ISO,

    /**
     * This operation cannot be performed because the specified VDI
     * could not be found in the specified SR
     */
    XEN_API_FAILURE_VDI_LOCATION_MISSING,

    /**
     * This operation cannot be performed because the specified VDI
     * could not be found on the storage substrate
     */
    XEN_API_FAILURE_VDI_MISSING,

    /**
     * You attempted to migrate a VDI which is not attached to a
     * runnning VM.
     */
    XEN_API_FAILURE_VDI_NEEDS_VM_FOR_MIGRATE,

    /**
     * This operation cannot be performed because this VDI could
     * not be properly attached to the VM.
     */
    XEN_API_FAILURE_VDI_NOT_AVAILABLE,

    /**
     * This VDI was not mapped to a destination SR in
     * VM.migrate_send operation
     */
    XEN_API_FAILURE_VDI_NOT_IN_MAP,

    /**
     * This operation cannot be performed because the system does
     * not manage this VDI
     */
    XEN_API_FAILURE_VDI_NOT_MANAGED,

    /**
     * The operation required write access but this VDI is
     * read-only
     */
    XEN_API_FAILURE_VDI_READONLY,

    /**
     * Network has active VIFs
     */
    XEN_API_FAILURE_VIF_IN_USE,

    /**
     * You tried to create a VLAN, but the tag you gave was invalid
     * -- it must be between 0 and 4094.  The parameter echoes the VLAN tag you
     * gave.
     */
    XEN_API_FAILURE_VLAN_TAG_INVALID,

    /**
     * Archive more frequent than backup.
     */
    XEN_API_FAILURE_VMPP_ARCHIVE_MORE_FREQUENT_THAN_BACKUP,

    /**
     * There is at least one VM assigned to this protection policy.
     */
    XEN_API_FAILURE_VMPP_HAS_VM,

    /**
     * The given VMs failed to release memory when instructed to do
     * so
     */
    XEN_API_FAILURE_VMS_FAILED_TO_COOPERATE,

    /**
     * This VM is assigned to a protection policy.
     */
    XEN_API_FAILURE_VM_ASSIGNED_TO_PROTECTION_POLICY,

    /**
     * You attempted to start a VM that's attached to more than one
     * VDI with a timeoffset marked as reset-on-boot.
     */
    XEN_API_FAILURE_VM_ATTACHED_TO_MORE_THAN_ONE_VDI_WITH_TIMEOFFSET_MARKED_AS_RESET_ON_BOOT,

    /**
     * You attempted an operation on a VM that was not in an
     * appropriate power state at the time; for example, you attempted to start a
     * VM that was already running.  The parameters returned are the VM's handle,
     * and the expected and actual VM state at the time of the call.
     */
    XEN_API_FAILURE_VM_BAD_POWER_STATE,

    /**
     * The BIOS strings for this VM have already been set and
     * cannot be changed anymore.
     */
    XEN_API_FAILURE_VM_BIOS_STRINGS_ALREADY_SET,

    /**
     * You cannot delete the specified default template.
     */
    XEN_API_FAILURE_VM_CANNOT_DELETE_DEFAULT_TEMPLATE,

    /**
     * An error occured while restoring the memory image of the
     * specified virtual machine
     */
    XEN_API_FAILURE_VM_CHECKPOINT_RESUME_FAILED,

    /**
     * An error occured while saving the memory image of the
     * specified virtual machine
     */
    XEN_API_FAILURE_VM_CHECKPOINT_SUSPEND_FAILED,

    /**
     * The VM crashed
     */
    XEN_API_FAILURE_VM_CRASHED,

    /**
     * The specified VM has a duplicate VBD device and cannot be
     * started.
     */
    XEN_API_FAILURE_VM_DUPLICATE_VBD_DEVICE,

    /**
     * VM didn't acknowledge the need to shutdown.
     */
    XEN_API_FAILURE_VM_FAILED_SHUTDOWN_ACKNOWLEDGMENT,

    /**
     * The VM unexpectedly halted
     */
    XEN_API_FAILURE_VM_HALTED,

    /**
     * You attempted to migrate a VM which has a checkpoint.
     */
    XEN_API_FAILURE_VM_HAS_CHECKPOINT,

    /**
     * This operation could not be performed, because the VM has
     * one or more PCI devices passed through.
     */
    XEN_API_FAILURE_VM_HAS_PCI_ATTACHED,

    /**
     * You attempted to migrate a VM with more than one snapshot.
     */
    XEN_API_FAILURE_VM_HAS_TOO_MANY_SNAPSHOTS,

    /**
     * This VM operation cannot be performed on an older-versioned
     * host during an upgrade.
     */
    XEN_API_FAILURE_VM_HOST_INCOMPATIBLE_VERSION,

    /**
     * HVM is required for this operation
     */
    XEN_API_FAILURE_VM_HVM_REQUIRED,

    /**
     * The VM is incompatible with the CPU features of this host.
     */
    XEN_API_FAILURE_VM_INCOMPATIBLE_WITH_THIS_HOST,

    /**
     * This operation is not allowed as the VM is part of an
     * appliance.
     */
    XEN_API_FAILURE_VM_IS_PART_OF_AN_APPLIANCE,

    /**
     * This operation cannot be performed because the specified VM
     * is protected by xHA
     */
    XEN_API_FAILURE_VM_IS_PROTECTED,

    /**
     * The operation attempted is not valid for a template VM
     */
    XEN_API_FAILURE_VM_IS_TEMPLATE,

    /**
     * The specified VM has too little memory to be started.
     */
    XEN_API_FAILURE_VM_MEMORY_SIZE_TOO_LOW,

    /**
     * An error occurred during the migration process.
     */
    XEN_API_FAILURE_VM_MIGRATE_FAILED,

    /**
     * You attempted an operation on a VM which requires PV drivers
     * to be installed but the drivers were not detected.
     */
    XEN_API_FAILURE_VM_MISSING_PV_DRIVERS,

    /**
     * The specified VM is not currently resident on the specified
     * host.
     */
    XEN_API_FAILURE_VM_NOT_RESIDENT_HERE,

    /**
     * This VM does not have a crashdump SR specified.
     */
    XEN_API_FAILURE_VM_NO_CRASHDUMP_SR,

    /**
     * This VM does not have a suspend SR specified.
     */
    XEN_API_FAILURE_VM_NO_SUSPEND_SR,

    /**
     * You need at least 1 VCPU to start a VM
     */
    XEN_API_FAILURE_VM_NO_VCPUS,

    /**
     * You attempted an operation on a VM which requires a more
     * recent version of the PV drivers. Please upgrade your PV drivers.
     */
    XEN_API_FAILURE_VM_OLD_PV_DRIVERS,

    /**
     * The VM unexpectedly rebooted
     */
    XEN_API_FAILURE_VM_REBOOTED,

    /**
     * You attempted to run a VM on a host which doesn't have a
     * pGPU available in the GPU group needed by the VM. The VM has a vGPU
     * attached to this GPU group.
     */
    XEN_API_FAILURE_VM_REQUIRES_GPU,

    /**
     * You attempted to run a VM on a host which doesn't have I/O
     * virtualisation (IOMMU/VT-d) enabled, which is needed by the VM.
     */
    XEN_API_FAILURE_VM_REQUIRES_IOMMU,

    /**
     * You attempted to run a VM on a host which doesn't have a PIF
     * on a Network needed by the VM. The VM has at least one VIF attached to the
     * Network.
     */
    XEN_API_FAILURE_VM_REQUIRES_NETWORK,

    /**
     * You attempted to run a VM on a host which doesn't have
     * access to an SR needed by the VM. The VM has at least one VBD attached to a
     * VDI in the SR.
     */
    XEN_API_FAILURE_VM_REQUIRES_SR,

    /**
     * VM cannot be started because it requires a VDI which cannot
     * be attached
     */
    XEN_API_FAILURE_VM_REQUIRES_VDI,

    /**
     * An error occured while reverting the specified virtual
     * machine to the specified snapshot
     */
    XEN_API_FAILURE_VM_REVERT_FAILED,

    /**
     * VM failed to shutdown before the timeout expired
     */
    XEN_API_FAILURE_VM_SHUTDOWN_TIMEOUT,

    /**
     * The quiesced-snapshot operation failed for an unexpected
     * reason
     */
    XEN_API_FAILURE_VM_SNAPSHOT_WITH_QUIESCE_FAILED,

    /**
     * The VSS plug-in is not installed on this virtual machine
     */
    XEN_API_FAILURE_VM_SNAPSHOT_WITH_QUIESCE_NOT_SUPPORTED,

    /**
     * The VSS plug-in cannot be contacted
     */
    XEN_API_FAILURE_VM_SNAPSHOT_WITH_QUIESCE_PLUGIN_DEOS_NOT_RESPOND,

    /**
     * The VSS plug-in has timed out
     */
    XEN_API_FAILURE_VM_SNAPSHOT_WITH_QUIESCE_TIMEOUT,

    /**
     * Too many VCPUs to start this VM
     */
    XEN_API_FAILURE_VM_TOO_MANY_VCPUS,

    /**
     * The VM cannot be imported unforced because it is either the
     * same version or an older version of an existing VM.
     */
    XEN_API_FAILURE_VM_TO_IMPORT_IS_NOT_NEWER_VERSION,

    /**
     * You attempted an operation on a VM that was judged to be
     * unsafe by the server. This can happen if the VM would run on a CPU that has
     * a potentially incompatible set of feature flags to those the VM requires.
     * If you want to override this warning then use the 'force' option.
     */
    XEN_API_FAILURE_VM_UNSAFE_BOOT,

    /**
     * The WLB server rejected our configured authentication
     * details.
     */
    XEN_API_FAILURE_WLB_AUTHENTICATION_FAILED,

    /**
     * The WLB server refused a connection to XenServer.
     */
    XEN_API_FAILURE_WLB_CONNECTION_REFUSED,

    /**
     * The connection to the WLB server was reset.
     */
    XEN_API_FAILURE_WLB_CONNECTION_RESET,

    /**
     * This pool has wlb-enabled set to false.
     */
    XEN_API_FAILURE_WLB_DISABLED,

    /**
     * The WLB server reported an internal error.
     */
    XEN_API_FAILURE_WLB_INTERNAL_ERROR,

    /**
     * The WLB server rejected XenServer's request as malformed.
     */
    XEN_API_FAILURE_WLB_MALFORMED_REQUEST,

    /**
     * The WLB server said something that XenServer wasn't
     * expecting or didn't understand.  The method called on the WLB server, a
     * diagnostic reason, and the response from WLB are returned.
     */
    XEN_API_FAILURE_WLB_MALFORMED_RESPONSE,

    /**
     * No WLB connection is configured.
     */
    XEN_API_FAILURE_WLB_NOT_INITIALIZED,

    /**
     * The communication with the WLB server timed out.
     */
    XEN_API_FAILURE_WLB_TIMEOUT,

    /**
     * The configured WLB server name failed to resolve in DNS.
     */
    XEN_API_FAILURE_WLB_UNKNOWN_HOST,

    /**
     * The WLB URL is invalid. Ensure it is in format:
     * <ipaddress>:<port>.  The configured/given URL is returned.
     */
    XEN_API_FAILURE_WLB_URL_INVALID,

    /**
     * The WLB server reported that XenServer rejected its
     * configured authentication details.
     */
    XEN_API_FAILURE_WLB_XENSERVER_AUTHENTICATION_FAILED,

    /**
     * The WLB server reported that XenServer refused it a
     * connection (even though we're connecting perfectly fine in the other
     * direction).
     */
    XEN_API_FAILURE_WLB_XENSERVER_CONNECTION_REFUSED,

    /**
     * The WLB server reported that XenServer said something to it
     * that WLB wasn't expecting or didn't understand.
     */
    XEN_API_FAILURE_WLB_XENSERVER_MALFORMED_RESPONSE,

    /**
     * The WLB server reported that communication with XenServer
     * timed out.
     */
    XEN_API_FAILURE_WLB_XENSERVER_TIMEOUT,

    /**
     * The WLB server reported that its configured server name for
     * this XenServer instance failed to resolve in DNS.
     */
    XEN_API_FAILURE_WLB_XENSERVER_UNKNOWN_HOST,

    /**
     * 3rd party xapi hook failed
     */
    XEN_API_FAILURE_XAPI_HOOK_FAILED,

    /**
     * The requested plugin could not be found.
     */
    XEN_API_FAILURE_XENAPI_MISSING_PLUGIN,

    /**
     * There was a failure communicating with the plugin.
     */
    XEN_API_FAILURE_XENAPI_PLUGIN_FAILURE,

    /**
     * Some volumes to be snapshot could not be added to the VSS
     * snapshot set
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_ADDING_VOLUME_TO_SNAPSET_FAILED,

    /**
     * An attempt to create the snapshots failed
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_CREATING_SNAPSHOT,

    /**
     * Could not create the XML string generated by the
     * transportable snapshot
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_CREATING_SNAPSHOT_XML_STRING,

    /**
     * Initialization of the VSS requestor failed
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_INIT_FAILED,

    /**
     * Could not find any volumes supported by the Citrix XenServer
     * Vss Provider
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_NO_VOLUMES_SUPPORTED,

    /**
     * An attempt to prepare VSS writers for the snapshot failed
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_PREPARING_WRITERS,

    /**
     * The Citrix XenServer Vss Provider is not loaded
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_PROV_NOT_LOADED,

    /**
     * An attempt to start a new VSS snapshot failed
     */
    XEN_API_FAILURE_XEN_VSS_REQ_ERROR_START_SNAPSHOT_SET_FAILED,

    /**
     * The server failed to unmarshal the XMLRPC message; it was
     * expecting one element and received something else.
     */
    XEN_API_FAILURE_XMLRPC_UNMARSHAL_FAILURE,

    /**
     * Unknown to this version of the bindings.
     */
    XEN_API_FAILURE_UNDEFINED
};


/**
 * Return the name corresponding to the given code.  This string must
 * not be modified or freed.
 */
extern const char *
xen_api_failure_to_string(enum xen_api_failure val);


/**
 * Return the correct code for the given string, or UNDEFINED if the
 * given string does not match a known code.
 */
extern enum xen_api_failure
xen_api_failure_from_string(const char *str);


#endif
