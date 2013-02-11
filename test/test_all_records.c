/* Copyright (c) Citrix Systems, Inc.
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

/**
 *
 * Re-write by Yuh-Hung Liaw (sukinull AT gmail.com) 2012.
 */

/* PURPOSE:
 * ========
 *
 * Verify handles
 * Modified based on XenServerJava/samples/GetAllRecordsOfAllTypes.java
 *
 */

#define _GNU_SOURCE
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libxml/parser.h>
#include <curl/curl.h>

#include <xen/api/xen_all.h>

static char *url;

typedef struct {
	xen_result_func func;
	void *handle;
} xen_comms;

static void usage() {
	fprintf(stderr,
			"Usage:\n"
					"\n"
					"    test_records<url> <username> <password>\n"
					"\n"
					"where\n"
					"        <url>      is the server's URL, e.g. https://server.example.com\n"
					"        <username> is the username to use at the server; and\n"
					"        <password> is the password.\n");

	exit(EXIT_FAILURE);
}

static size_t write_func(void *ptr, size_t size, size_t nmemb, xen_comms *comms) {
	size_t n = size * nmemb;
#ifdef PRINT_XML
	printf("\n\n\n---Result from server -----------------------\n");
	printf("\n%s\n",((char*) ptr));
	fflush(stdout);
#endif
	return comms->func(ptr, n, comms->handle) ? n : 0;
}

static int call_func(const void *data, size_t len, void *user_handle,
		void *result_handle, xen_result_func result_func) {
	(void) user_handle;

#ifdef PRINT_XML
	printf("\n\n\n---Data to server: -----------------------\n");
	printf("\n%s\n",((char*) data));
	fflush(stdout);
#endif

	CURL *curl = curl_easy_init();
	if (!curl) {
		return -1;
	}

	xen_comms comms = { .func = result_func, .handle = result_handle };

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
#ifdef CURLOPT_MUTE
	curl_easy_setopt(curl, CURLOPT_MUTE, 1);
#endif
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_func);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &comms);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, len);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

	CURLcode result = curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	return result;
}

static void print_error(xen_session *session) {
	fprintf(stderr, "Error: %d", session->error_description_count);
	int i = 0;
	for (; i < session->error_description_count; i++) {
		fprintf(stderr, "%s ", session->error_description[i]);
	}
	fprintf(stderr, "\n");
}

static void testConsoles(xen_session *session) {
	printf("\nGet all the  Console Records\n");

	xen_console_xen_console_record_map *console_map;
	bool ok = xen_console_get_all_records(session, &console_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < console_map->size; ++i) {
		xen_console key = console_map->contents[i].key;
	}

	xen_console_xen_console_record_map_free(console_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testCrashdumps(xen_session *session) {
	printf("\nGet all the  Crashdump Records\n");

	xen_crashdump_xen_crashdump_record_map *crashdump_map;
	bool ok = xen_crashdump_get_all_records(session, &crashdump_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < crashdump_map->size; ++i) {
		xen_crashdump key = crashdump_map->contents[i].key;
	}

	xen_crashdump_xen_crashdump_record_map_free(crashdump_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHosts(xen_session *session) {
	printf("\nGet all the  Host Records\n");

	xen_host_xen_host_record_map *host_map;
	bool ok = xen_host_get_all_records(session, &host_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < host_map->size; ++i) {
		xen_host key = host_map->contents[i].key;
	}

#if 0
	printf("== Get All ============================\n\n");

	xen_host_xen_host_record_map *result;
	bool ok = xen_host_get_all_records(session, &result);
	if(!ok) {
		print_error(session);
	}
	size_t i=0;
	for(;i<result->size;++i) {
		xen_host key = result->contents[i].key;
		struct xen_host_record *val = result->contents[i].val;
		if(strcmp((char*)key, (char*)val->handle)==0) {

		} else {
			printf("%s v.s. %s", (char*)key, (char*)val->handle);
		}
		xen_host_record_free(val);
		xen_host_free(key);
	}
	free(result);
#endif
	xen_host_xen_host_record_map_free(host_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostCpus(xen_session *session) {
	printf("\nGet all the  HostCpu Records\n");

	xen_host_cpu_xen_host_cpu_record_map *host_cpu_map;
	bool ok = xen_host_cpu_get_all_records(session, &host_cpu_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < host_cpu_map->size; ++i) {
		xen_host_cpu key = host_cpu_map->contents[i].key;
	}

	xen_host_cpu_xen_host_cpu_record_map_free(host_cpu_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostCrashdumps(xen_session *session) {
	printf("\nGet all the  HostCrashdump Records\n");

	xen_host_crashdump_xen_host_crashdump_record_map *host_crashdump_map;
	bool ok = xen_host_crashdump_get_all_records(session, &host_crashdump_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < host_crashdump_map->size; ++i) {
		xen_host_crashdump key = host_crashdump_map->contents[i].key;
	}

	xen_host_crashdump_xen_host_crashdump_record_map_free(host_crashdump_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostMetricss(xen_session *session) {
	printf("\nGet all the  HostMetrics Records\n");

	xen_host_metrics_xen_host_metrics_record_map *host_metrics_map;
	bool ok = xen_host_metrics_get_all_records(session, &host_metrics_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < host_metrics_map->size; ++i) {
		xen_host_metrics key = host_metrics_map->contents[i].key;
	}

	xen_host_metrics_xen_host_metrics_record_map_free(host_metrics_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostPatchs(xen_session *session) {
	printf("\nGet all the  HostPatch Records\n");

	xen_host_patch_xen_host_patch_record_map *host_patch_map;
	bool ok = xen_host_patch_get_all_records(session, &host_patch_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < host_patch_map->size; ++i) {
		xen_host_patch key = host_patch_map->contents[i].key;
	}

	xen_host_patch_xen_host_patch_record_map_free(host_patch_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testNetworks(xen_session *session) {
	printf("\nGet all the  Network Records\n");

	xen_network_xen_network_record_map *network_map;
	bool ok = xen_network_get_all_records(session, &network_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < network_map->size; ++i) {
		xen_network key = network_map->contents[i].key;
	}

	xen_network_xen_network_record_map_free(network_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPBDs(xen_session *session) {
	printf("\nGet all the  PBD Records\n");

	xen_pbd_xen_pbd_record_map *pbd_map;
	bool ok = xen_pbd_get_all_records(session, &pbd_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < pbd_map->size; ++i) {
		xen_pbd key = pbd_map->contents[i].key;
	}

	xen_pbd_xen_pbd_record_map_free(pbd_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPIFs(xen_session *session) {
	printf("\nGet all the  PIF Records\n");

	xen_pif_xen_pif_record_map *pif_map;
	bool ok = xen_pif_get_all_records(session, &pif_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < pif_map->size; ++i) {
		xen_pif key = pif_map->contents[i].key;
	}

	xen_pif_xen_pif_record_map_free(pif_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPIFMetricss(xen_session *session) {
	printf("\nGet all the  PIFMetrics Records\n");

	xen_pif_metrics_xen_pif_metrics_record_map *pif_metrics_map;
	bool ok = xen_pif_metrics_get_all_records(session, &pif_metrics_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < pif_metrics_map->size; ++i) {
		xen_pif_metrics key = pif_metrics_map->contents[i].key;
	}

	xen_pif_metrics_xen_pif_metrics_record_map_free(pif_metrics_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPools(xen_session *session) {
	printf("\nGet all the  Pool Records\n");

	xen_pool_xen_pool_record_map *pool_map;
	bool ok = xen_pool_get_all_records(session, &pool_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < pool_map->size; ++i) {
		xen_pool key = pool_map->contents[i].key;
	}

	xen_pool_xen_pool_record_map_free(pool_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testSMs(xen_session *session) {
	printf("\nGet all the  SM Records\n");

	xen_sm_xen_sm_record_map *sm_map;
	bool ok = xen_sm_get_all_records(session, &sm_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < sm_map->size; ++i) {
		xen_sm key = sm_map->contents[i].key;
	}

	xen_sm_xen_sm_record_map_free(sm_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testSRs(xen_session *session) {
	printf("\nGet all the  SR Records\n");

	xen_sr_xen_sr_record_map *sr_map;
	bool ok = xen_sr_get_all_records(session, &sr_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < sr_map->size; ++i) {
		xen_sr key = sr_map->contents[i].key;
	}

	xen_sr_xen_sr_record_map_free(sr_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testTasks(xen_session *session) {
	printf("\nGet all the  Task Records\n");

	xen_task_xen_task_record_map *task_map;
	bool ok = xen_task_get_all_records(session, &task_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < task_map->size; ++i) {
		xen_task key = task_map->contents[i].key;
	}

	xen_task_xen_task_record_map_free(task_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVBDs(xen_session *session) {
	printf("\nGet all the  VBD Records\n");

	xen_vbd_xen_vbd_record_map *vbd_map;
	bool ok = xen_vbd_get_all_records(session, &vbd_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vbd_map->size; ++i) {
		xen_vbd key = vbd_map->contents[i].key;
	}

	xen_vbd_xen_vbd_record_map_free(vbd_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVBDMetricss(xen_session *session) {
	printf("\nGet all the  VBDMetrics Records\n");

	xen_vbd_metrics_xen_vbd_metrics_record_map *vbd_metrics_map;
	bool ok = xen_vbd_metrics_get_all_records(session, &vbd_metrics_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vbd_metrics_map->size; ++i) {
		xen_vbd_metrics key = vbd_metrics_map->contents[i].key;
	}

	xen_vbd_metrics_xen_vbd_metrics_record_map_free(vbd_metrics_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVDIs(xen_session *session) {
	printf("\nGet all the  VDI Records\n");

	xen_vdi_xen_vdi_record_map *vdi_map;
	bool ok = xen_vdi_get_all_records(session, &vdi_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vdi_map->size; ++i) {
		xen_vdi key = vdi_map->contents[i].key;
	}

	xen_vdi_xen_vdi_record_map_free(vdi_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVIFs(xen_session *session) {
	printf("\nGet all the  VIF Records\n");

	xen_vif_xen_vif_record_map *vif_map;
	bool ok = xen_vif_get_all_records(session, &vif_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vif_map->size; ++i) {
		xen_vif key = vif_map->contents[i].key;
	}

	xen_vif_xen_vif_record_map_free(vif_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVIFMetricss(xen_session *session) {
	printf("\nGet all the  VIFMetrics Records\n");

	xen_vif_metrics_xen_vif_metrics_record_map *vif_metrics_map;
	bool ok = xen_vif_metrics_get_all_records(session, &vif_metrics_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vif_metrics_map->size; ++i) {
		xen_vif_metrics key = vif_metrics_map->contents[i].key;
	}

	xen_vif_metrics_xen_vif_metrics_record_map_free(vif_metrics_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVMs(xen_session *session) {
	printf("\nGet all the  VM Records\n");

	xen_vm_xen_vm_record_map *vm_map;
	bool ok = xen_vm_get_all_records(session, &vm_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vm_map->size; ++i) {
		xen_vm key = vm_map->contents[i].key;
	}

	xen_vm_xen_vm_record_map_free(vm_map);

#if 0
	printf("== Get All VM Records ============================\n\n");

	xen_vm_xen_vm_record_map *result;
	bool ok = xen_vm_get_all_records(session, &result);
	if(!ok) {
		print_error(session);
	}
	size_t i=0;
	for(;i<result->size;++i) {
		xen_vm key = result->contents[i].key;
		struct xen_vm_record *val = result->contents[i].val;
		if(strcmp((char*)key, (char*)val->handle)==0) {

		} else {
			printf("%s v.s. %s", (char*)key, (char*)val->handle);
		}
		xen_vm_record_free(val);
		xen_vm_free(key);
	}
	free(result);
#endif

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVMGuestMetricss(xen_session *session) {
	printf("\nGet all the  VMGuestMetrics Records\n");

	xen_vm_guest_metrics_xen_vm_guest_metrics_record_map *vm_guest_metrics_map;
	bool ok = xen_vm_guest_metrics_get_all_records(session, &vm_guest_metrics_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vm_guest_metrics_map->size; ++i) {
		xen_vm_guest_metrics key = vm_guest_metrics_map->contents[i].key;
	}

	xen_vm_guest_metrics_xen_vm_guest_metrics_record_map_free(vm_guest_metrics_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVMMetricss(xen_session *session) {
	printf("\nGet all the  VMMetrics Records\n");

	xen_vm_metrics_xen_vm_metrics_record_map *vm_metrics_map;
	bool ok = xen_vm_metrics_get_all_records(session, &vm_metrics_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vm_metrics_map->size; ++i) {
		xen_vm_metrics key = vm_metrics_map->contents[i].key;
	}

	xen_vm_metrics_xen_vm_metrics_record_map_free(vm_metrics_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testBonds(xen_session *session) {
	printf("\nGet all the  Bond Records\n");

	xen_bond_xen_bond_record_map *bond_map;
	bool ok = xen_bond_get_all_records(session, &bond_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < bond_map->size; ++i) {
		xen_bond key = bond_map->contents[i].key;
	}

	xen_bond_xen_bond_record_map_free(bond_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPoolPatchs(xen_session *session) {
	printf("\nGet all the  PoolPatch Records\n");

	xen_pool_patch_xen_pool_patch_record_map *pool_patch_map;
	bool ok = xen_pool_patch_get_all_records(session, &pool_patch_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < pool_patch_map->size; ++i) {
		xen_pool_patch key = pool_patch_map->contents[i].key;
	}

	xen_pool_patch_xen_pool_patch_record_map_free(pool_patch_map);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVLANs(xen_session *session) {
	printf("\nGet all the  VLAN Records\n");

	xen_vlan_xen_vlan_record_map *vlan_map;
	bool ok = xen_vlan_get_all_records(session, &vlan_map);
	if (!ok) {
		print_error(session);
	}
	size_t i = 0;
	for (; i < vlan_map->size; ++i) {
		xen_vlan key = vlan_map->contents[i].key;
	}

	xen_vlan_xen_vlan_record_map_free(vlan_map);

	printf("\n==============================================\n\n");
}

int main(int argc, char **argv) {

	if (argc != 4) {
		usage();
	}

	url = argv[1];
	char *username = argv[2];
	char *password = argv[3];

	xmlInitParser();
	xmlKeepBlanksDefault(0);
	xen_init();
	curl_global_init(CURL_GLOBAL_ALL);

#define CLEANUP                                 \
    do {                                        \
        xen_session_logout(session);            \
        curl_global_cleanup();                  \
        xen_fini();                             \
        xmlCleanupParser();                     \
    } while(0)                                  \


	xen_session *session = xen_session_login_with_password(call_func, NULL,
			username, password, xen_api_latest_version);

	/* ---------------------------------------------------------------------
	 Read host, capabilities and API vsn
	 --------------------------------------------------------------------- */
	testConsoles(session);
	testCrashdumps(session);
	//testHosts(session);
	testHostCpus(session);
	testHostCrashdumps(session);
	testHostMetricss(session);
	testHostPatchs(session);
	testNetworks(session);
	testPBDs(session);
	testPIFs(session);
	testPIFMetricss(session);
	testPools(session);
	testSMs(session);
	testSRs(session);
	testTasks(session);
	testVBDs(session);
	testVBDMetricss(session);
	testVDIs(session);
	testVIFs(session);
	testVIFMetricss(session);
	testVMs(session);
	testVMGuestMetricss(session);
	testVMMetricss(session);

	if (session->api_version == xen_api_version_1_1) {
		printf(
				"Rio connection detected; skipping getting records on Bonds, Patches, and VLANs\n\n");
	} else {
		testBonds(session);
		testPoolPatchs(session);
		testVLANs(session);
	}

	printf("xen_xxx_record_map_free fix - replace xen_xxx_record_opt_free to xen_xxx_free");
	printf("\n\n");

	CLEANUP;

	return 0;
}
