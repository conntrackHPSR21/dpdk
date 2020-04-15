/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2014-2019 Broadcom
 * All rights reserved.
 */

#ifndef _ULP_FLOW_DB_H_
#define _ULP_FLOW_DB_H_

#include "bnxt_ulp.h"
#include "ulp_template_db.h"

#define BNXT_FLOW_DB_DEFAULT_NUM_FLOWS		128
#define BNXT_FLOW_DB_DEFAULT_NUM_RESOURCES	5

/* Structure for the flow database resource information. */
struct ulp_fdb_resource_info {
	/* Points to next resource in the chained list. */
	uint32_t	nxt_resource_idx;
	union {
		uint64_t	resource_em_handle;
		struct {
			uint32_t	resource_type;
			uint32_t	resource_hndl;
		};
	};
};

/* Structure for the flow database resource information. */
struct bnxt_ulp_flow_tbl {
	/* Flow tbl is the resource object list for each flow id. */
	struct ulp_fdb_resource_info	*flow_resources;

	/* Flow table stack to track free list of resources. */
	uint32_t	*flow_tbl_stack;
	uint32_t	head_index;
	uint32_t	tail_index;

	/* Table to track the active flows. */
	uint64_t	*active_flow_tbl;
	uint32_t	num_flows;
	uint32_t	num_resources;
};

/* Flow database supports two tables. */
enum bnxt_ulp_flow_db_tables {
	BNXT_ULP_REGULAR_FLOW_TABLE,
	BNXT_ULP_DEFAULT_FLOW_TABLE,
	BNXT_ULP_FLOW_TABLE_MAX
};

/* Structure for the flow database resource information. */
struct bnxt_ulp_flow_db {
	struct bnxt_ulp_flow_tbl	flow_tbl[BNXT_ULP_FLOW_TABLE_MAX];
};

/*
 * Initialize the flow database. Memory is allocated in this
 * call and assigned to the flow database.
 *
 * ulp_ctxt [in] Ptr to ulp context
 *
 * Returns 0 on success or negative number on failure.
 */
int32_t	ulp_flow_db_init(struct bnxt_ulp_context *ulp_ctxt);

/*
 * Deinitialize the flow database. Memory is deallocated in
 * this call and all flows should have been purged before this
 * call.
 *
 * ulp_ctxt [in] Ptr to ulp context
 *
 * Returns 0 on success.
 */
int32_t	ulp_flow_db_deinit(struct bnxt_ulp_context *ulp_ctxt);

#endif /* _ULP_FLOW_DB_H_ */