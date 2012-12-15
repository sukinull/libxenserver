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
	fprintf(stderr, "Usage:\n"
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

	xen_console_set *console_set;
	bool d = xen_console_get_all(session, &console_set);
	if (d) {
		size_t i = 0;
		for (; i < console_set->size; ++i) {
			xen_console_record *console_record;
			xen_console_get_record(session, &console_record,
					console_set->contents[i]);
			char *handle = (char*) console_record->handle;
			char *opaque = (char*) console_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_console_record_free(console_record);
		}
	} else {
		print_error(session);
	}
	xen_console_set_free(console_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testCrashdumps(xen_session *session) {
	printf("\nGet all the  Crashdump Records\n");

	xen_crashdump_set *crashdump_set;
	bool d = xen_crashdump_get_all(session, &crashdump_set);
	if (d) {
		size_t i = 0;
		for (; i < crashdump_set->size; ++i) {
			xen_crashdump_record *crashdump_record;
			xen_crashdump_get_record(session, &crashdump_record,
					crashdump_set->contents[i]);
			char *handle = (char*) crashdump_record->handle;
			char *opaque = (char*) crashdump_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_crashdump_record_free(crashdump_record);
		}
	} else {
		print_error(session);
	}
	xen_crashdump_set_free(crashdump_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHosts(xen_session *session) {
	printf("\nGet all the  Host Records\n");

	xen_host_set *host_set;
	bool d = xen_host_get_all(session, &host_set);
	if (d) {
		size_t i = 0;
		for (; i < host_set->size; ++i) {
			xen_host_record *host_record;
			xen_host_get_record(session, &host_record, host_set->contents[i]);
			char *handle = (char*) host_record->handle;
			char *opaque = (char*) host_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_host_record_free(host_record);
		}
	} else {
		print_error(session);
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
	xen_host_set_free(host_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostCpus(xen_session *session) {
	printf("\nGet all the  HostCpu Records\n");

	xen_host_cpu_set *host_cpu_set;
	bool d = xen_host_cpu_get_all(session, &host_cpu_set);
	if (d) {
		size_t i = 0;
		for (; i < host_cpu_set->size; ++i) {
			xen_host_cpu_record *host_cpu_record;
			xen_host_cpu_get_record(session, &host_cpu_record,
					host_cpu_set->contents[i]);
			char *handle = (char*) host_cpu_record->handle;
			char *opaque = (char*) host_cpu_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_host_cpu_record_free(host_cpu_record);
		}
	} else {
		print_error(session);
	}
	xen_host_cpu_set_free(host_cpu_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostCrashdumps(xen_session *session) {
	printf("\nGet all the  HostCrashdump Records\n");

	xen_host_crashdump_set *host_crashdump_set;
	bool d = xen_host_crashdump_get_all(session, &host_crashdump_set);
	if (d) {
		size_t i = 0;
		for (; i < host_crashdump_set->size; ++i) {
			xen_host_crashdump_record *host_crashdump_record;
			xen_host_crashdump_get_record(session, &host_crashdump_record,
					host_crashdump_set->contents[i]);
			char *handle = (char*) host_crashdump_record->handle;
			char *opaque = (char*) host_crashdump_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_host_crashdump_record_free(host_crashdump_record);
		}
	} else {
		print_error(session);
	}
	xen_host_crashdump_set_free(host_crashdump_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostMetricss(xen_session *session) {
	printf("\nGet all the  HostMetrics Records\n");

	xen_host_metrics_set *host_metrics_set;
	bool d = xen_host_metrics_get_all(session, &host_metrics_set);
	if (d) {
		size_t i = 0;
		for (; i < host_metrics_set->size; ++i) {
			xen_host_metrics_record *host_metrics_record;
			xen_host_metrics_get_record(session, &host_metrics_record,
					host_metrics_set->contents[i]);
			char *handle = (char*) host_metrics_record->handle;
			char *opaque = (char*) host_metrics_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_host_metrics_record_free(host_metrics_record);
		}
	} else {
		print_error(session);
	}
	xen_host_metrics_set_free(host_metrics_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testHostPatchs(xen_session *session) {
	printf("\nGet all the  HostPatch Records\n");

	xen_host_patch_set *host_patch_set;
	bool d = xen_host_patch_get_all(session, &host_patch_set);
	if (d) {
		size_t i = 0;
		for (; i < host_patch_set->size; ++i) {
			xen_host_patch_record *host_patch_record;
			xen_host_patch_get_record(session, &host_patch_record,
					host_patch_set->contents[i]);
			char *handle = (char*) host_patch_record->handle;
			char *opaque = (char*) host_patch_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_host_patch_record_free(host_patch_record);
		}
	} else {
		print_error(session);
	}
	xen_host_patch_set_free(host_patch_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testNetworks(xen_session *session) {
	printf("\nGet all the  Network Records\n");

	xen_network_set *network_set;
	bool d = xen_network_get_all(session, &network_set);
	if (d) {
		size_t i = 0;
		for (; i < network_set->size; ++i) {
			xen_network_record *network_record;
			xen_network_get_record(session, &network_record,
					network_set->contents[i]);
			char *handle = (char*) network_record->handle;
			char *opaque = (char*) network_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_network_record_free(network_record);
		}
	} else {
		print_error(session);
	}
	xen_network_set_free(network_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPBDs(xen_session *session) {
	printf("\nGet all the  PBD Records\n");

	xen_pbd_set *pbd_set;
	bool d = xen_pbd_get_all(session, &pbd_set);
	if (d) {
		size_t i = 0;
		for (; i < pbd_set->size; ++i) {
			xen_pbd_record *pbd_record;
			xen_pbd_get_record(session, &pbd_record, pbd_set->contents[i]);
			char *handle = (char*) pbd_record->handle;
			char *opaque = (char*) pbd_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_pbd_record_free(pbd_record);
		}
	} else {
		print_error(session);
	}
	xen_pbd_set_free(pbd_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPIFs(xen_session *session) {
	printf("\nGet all the  PIF Records\n");

	xen_pif_set *pif_set;
	bool d = xen_pif_get_all(session, &pif_set);
	if (d) {
		size_t i = 0;
		for (; i < pif_set->size; ++i) {
			xen_pif_record *pif_record;
			xen_pif_get_record(session, &pif_record, pif_set->contents[i]);
			char *handle = (char*) pif_record->handle;
			char *opaque = (char*) pif_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_pif_record_free(pif_record);
		}
	} else {
		print_error(session);
	}
	xen_pif_set_free(pif_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPIFMetricss(xen_session *session) {
	printf("\nGet all the  PIFMetrics Records\n");

	xen_pif_metrics_set *pif_metrics_set;
	bool d = xen_pif_metrics_get_all(session, &pif_metrics_set);
	if (d) {
		size_t i = 0;
		for (; i < pif_metrics_set->size; ++i) {
			xen_pif_metrics_record *pif_metrics_record;
			xen_pif_metrics_get_record(session, &pif_metrics_record,
					pif_metrics_set->contents[i]);
			char *handle = (char*) pif_metrics_record->handle;
			char *opaque = (char*) pif_metrics_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_pif_metrics_record_free(pif_metrics_record);
		}
	} else {
		print_error(session);
	}
	xen_pif_metrics_set_free(pif_metrics_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPools(xen_session *session) {
	printf("\nGet all the  Pool Records\n");

	xen_pool_set *pool_set;
	bool d = xen_pool_get_all(session, &pool_set);
	if (d) {
		size_t i = 0;
		for (; i < pool_set->size; ++i) {
			xen_pool_record *pool_record;
			xen_pool_get_record(session, &pool_record, pool_set->contents[i]);
			char *handle = (char*) pool_record->handle;
			char *opaque = (char*) pool_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_pool_record_free(pool_record);
		}
	} else {
		print_error(session);
	}
	xen_pool_set_free(pool_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testSMs(xen_session *session) {
	printf("\nGet all the  SM Records\n");

	xen_sm_set *sm_set;
	bool d = xen_sm_get_all(session, &sm_set);
	if (d) {
		size_t i = 0;
		for (; i < sm_set->size; ++i) {
			xen_sm_record *sm_record;
			xen_sm_get_record(session, &sm_record, sm_set->contents[i]);
			char *handle = (char*) sm_record->handle;
			char *opaque = (char*) sm_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_sm_record_free(sm_record);
		}
	} else {
		print_error(session);
	}
	xen_sm_set_free(sm_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testSRs(xen_session *session) {
	printf("\nGet all the  SR Records\n");

	xen_sr_set *sr_set;
	bool d = xen_sr_get_all(session, &sr_set);
	if (d) {
		size_t i = 0;
		for (; i < sr_set->size; ++i) {
			xen_sr_record *sr_record;
			xen_sr_get_record(session, &sr_record, sr_set->contents[i]);
			char *handle = (char*) sr_record->handle;
			char *opaque = (char*) sr_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_sr_record_free(sr_record);
		}
	} else {
		print_error(session);
	}
	xen_sr_set_free(sr_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testTasks(xen_session *session) {
	printf("\nGet all the  Task Records\n");

	xen_task_set *task_set;
	bool d = xen_task_get_all(session, &task_set);
	if (d) {
		size_t i = 0;
		for (; i < task_set->size; ++i) {
			xen_task_record *task_record;
			xen_task_get_record(session, &task_record, task_set->contents[i]);
			char *handle = (char*) task_record->handle;
			char *opaque = (char*) task_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_task_record_free(task_record);
		}
	} else {
		print_error(session);
	}
	xen_task_set_free(task_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVBDs(xen_session *session) {
	printf("\nGet all the  VBD Records\n");

	xen_vbd_set *vbd_set;
	bool d = xen_vbd_get_all(session, &vbd_set);
	if (d) {
		size_t i = 0;
		for (; i < vbd_set->size; ++i) {
			xen_vbd_record *vbd_record;
			xen_vbd_get_record(session, &vbd_record, vbd_set->contents[i]);
			char *handle = (char*) vbd_record->handle;
			char *opaque = (char*) vbd_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vbd_record_free(vbd_record);
		}
	} else {
		print_error(session);
	}
	xen_vbd_set_free(vbd_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVBDMetricss(xen_session *session) {
	printf("\nGet all the  VBDMetrics Records\n");

	xen_vbd_metrics_set *vbd_metrics_set;
	bool d = xen_vbd_metrics_get_all(session, &vbd_metrics_set);
	if (d) {
		size_t i = 0;
		for (; i < vbd_metrics_set->size; ++i) {
			xen_vbd_metrics_record *vbd_metrics_record;
			xen_vbd_metrics_get_record(session, &vbd_metrics_record,
					vbd_metrics_set->contents[i]);
			char *handle = (char*) vbd_metrics_record->handle;
			char *opaque = (char*) vbd_metrics_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vbd_metrics_record_free(vbd_metrics_record);
		}
	} else {
		print_error(session);
	}
	xen_vbd_metrics_set_free(vbd_metrics_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVDIs(xen_session *session) {
	printf("\nGet all the  VDI Records\n");

	xen_vdi_set *vdi_set;
	bool d = xen_vdi_get_all(session, &vdi_set);
	if (d) {
		size_t i = 0;
		for (; i < vdi_set->size; ++i) {
			xen_vdi_record *vdi_record;
			xen_vdi_get_record(session, &vdi_record, vdi_set->contents[i]);
			char *handle = (char*) vdi_record->handle;
			char *opaque = (char*) vdi_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vdi_record_free(vdi_record);
		}
	} else {
		print_error(session);
	}
	xen_vdi_set_free(vdi_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVIFs(xen_session *session) {
	printf("\nGet all the  VIF Records\n");

	xen_vif_set *vif_set;
	bool d = xen_vif_get_all(session, &vif_set);
	if (d) {
		size_t i = 0;
		for (; i < vif_set->size; ++i) {
			xen_vif_record *vif_record;
			xen_vif_get_record(session, &vif_record, vif_set->contents[i]);
			char *handle = (char*) vif_record->handle;
			char *opaque = (char*) vif_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vif_record_free(vif_record);
		}
	} else {
		print_error(session);
	}
	xen_vif_set_free(vif_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVIFMetricss(xen_session *session) {
	printf("\nGet all the  VIFMetrics Records\n");

	xen_vif_metrics_set *vif_metrics_set;
	bool d = xen_vif_metrics_get_all(session, &vif_metrics_set);
	if (d) {
		size_t i = 0;
		for (; i < vif_metrics_set->size; ++i) {
			xen_vif_metrics_record *vif_metrics_record;
			xen_vif_metrics_get_record(session, &vif_metrics_record,
					vif_metrics_set->contents[i]);
			char *handle = (char*) vif_metrics_record->handle;
			char *opaque = (char*) vif_metrics_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vif_metrics_record_free(vif_metrics_record);
		}
	} else {
		print_error(session);
	}
	xen_vif_metrics_set_free(vif_metrics_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVMs(xen_session *session) {
	printf("\nGet all the  VM Records\n");

	xen_vm_set *vm_set;
	bool d = xen_vm_get_all(session, &vm_set);
	if (d) {
		size_t i = 0;
		for (; i < vm_set->size; ++i) {
			xen_vm_record *vm_record;
			xen_vm_get_record(session, &vm_record, vm_set->contents[i]);
			char *handle = (char*) vm_record->handle;
			char *opaque = (char*) vm_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vm_record_free(vm_record);
		}
	} else {
		print_error(session);
	}
	xen_vm_set_free(vm_set);

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

	xen_vm_guest_metrics_set *vm_guest_metrics_set;
	bool d = xen_vm_guest_metrics_get_all(session, &vm_guest_metrics_set);
	if (d) {
		size_t i = 0;
		for (; i < vm_guest_metrics_set->size; ++i) {
			xen_vm_guest_metrics_record *vm_guest_metrics_record;
			xen_vm_guest_metrics_get_record(session, &vm_guest_metrics_record,
					vm_guest_metrics_set->contents[i]);
			char *handle = (char*) vm_guest_metrics_record->handle;
			char *opaque = (char*) vm_guest_metrics_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vm_guest_metrics_record_free(vm_guest_metrics_record);
		}
	} else {
		print_error(session);
	}
	xen_vm_guest_metrics_set_free(vm_guest_metrics_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVMMetricss(xen_session *session) {
	printf("\nGet all the  VMMetrics Records\n");

	xen_vm_metrics_set *vm_metrics_set;
	bool d = xen_vm_metrics_get_all(session, &vm_metrics_set);
	if (d) {
		size_t i = 0;
		for (; i < vm_metrics_set->size; ++i) {
			xen_vm_metrics_record *vm_metrics_record;
			xen_vm_metrics_get_record(session, &vm_metrics_record,
					vm_metrics_set->contents[i]);
			char *handle = (char*) vm_metrics_record->handle;
			char *opaque = (char*) vm_metrics_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vm_metrics_record_free(vm_metrics_record);
		}
	} else {
		print_error(session);
	}
	xen_vm_metrics_set_free(vm_metrics_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testBonds(xen_session *session) {
	printf("\nGet all the  Bond Records\n");

	xen_bond_set *bond_set;
	bool d = xen_bond_get_all(session, &bond_set);
	if (d) {
		size_t i = 0;
		for (; i < bond_set->size; ++i) {
			xen_bond_record *bond_record;
			xen_bond_get_record(session, &bond_record, bond_set->contents[i]);
			char *handle = (char*) bond_record->handle;
			char *opaque = (char*) bond_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_bond_record_free(bond_record);
		}
	} else {
		print_error(session);
	}
	xen_bond_set_free(bond_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testPoolPatchs(xen_session *session) {
	printf("\nGet all the  PoolPatch Records\n");

	xen_pool_patch_set *pool_patch_set;
	bool d = xen_pool_patch_get_all(session, &pool_patch_set);
	if (d) {
		size_t i = 0;
		for (; i < pool_patch_set->size; ++i) {
			xen_pool_patch_record *pool_patch_record;
			xen_pool_patch_get_record(session, &pool_patch_record,
					pool_patch_set->contents[i]);
			char *handle = (char*) pool_patch_record->handle;
			char *opaque = (char*) pool_patch_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_pool_patch_record_free(pool_patch_record);
		}
	} else {
		print_error(session);
	}
	xen_pool_patch_set_free(pool_patch_set);

	printf("\n==============================================\n\n");
}

// automatically generated. Do not modify
static void testVLANs(xen_session *session) {
	printf("\nGet all the  VLAN Records\n");

	xen_vlan_set *vlan_set;
	bool d = xen_vlan_get_all(session, &vlan_set);
	if (d) {
		size_t i = 0;
		for (; i < vlan_set->size; ++i) {
			xen_vlan_record *vlan_record;
			xen_vlan_get_record(session, &vlan_record, vlan_set->contents[i]);
			char *handle = (char*) vlan_record->handle;
			char *opaque = (char*) vlan_set->contents[i];
			if (strcmp(handle, opaque) == 0)
				printf("identical: %s\n", opaque);
			else
				printf("record->handle[%s] v.s. set->contents[%d][%s]\n",
						opaque, i, handle);
			xen_vlan_record_free(vlan_record);
		}
	} else {
		print_error(session);
	}
	xen_vlan_set_free(vlan_set);

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
	testHosts(session);
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

	printf("\n\n");

	CLEANUP;

	return 0;
}
