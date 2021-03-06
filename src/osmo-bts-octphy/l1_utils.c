/* Layer 1 (PHY) Utilities of osmo-bts OCTPHY integration */

/* Copyright (c) 2014 Octasic Inc. All rights reserved.
 * Copyright (c) 2015 Harald Welte <laforge@gnumonks.org>
 *
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "l1_utils.h"
#include <octphy/octvc1/gsm/octvc1_gsm_api.h>
#include <octphy/octvc1/gsm/octvc1_gsm_id.h>
#include <octphy/octvc1/hw/octvc1_hw_api.h>

const struct value_string octphy_l1sapi_names[23] = 
{
	{ cOCTVC1_GSM_SAPI_ENUM_IDLE,	"IDLE" },
	{ cOCTVC1_GSM_SAPI_ENUM_FCCH,	"FCCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_SCH,	"SCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_SACCH,	"SACCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_SDCCH,	"SDCCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_BCCH,	"BCCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PCH_AGCH,"PCH_AGCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_CBCH,	"CBCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_RACH,	"RACH" },
	{ cOCTVC1_GSM_SAPI_ENUM_TCHF,	"TCH/F" },
	{ cOCTVC1_GSM_SAPI_ENUM_FACCHF,	"FACCH/F" },
	{ cOCTVC1_GSM_SAPI_ENUM_TCHH,	"TCH/H" },
	{ cOCTVC1_GSM_SAPI_ENUM_FACCHH,	"FACCH/H" },
	{ cOCTVC1_GSM_SAPI_ENUM_NCH,	"NCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PDTCH,	"PDTCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PACCH,	"PACCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PBCCH,	"PBCCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PAGCH,	"PAGCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PPCH,	"PPCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PNCH,	"PNCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PTCCH,	"PTCCH" },
	{ cOCTVC1_GSM_SAPI_ENUM_PRACH,	"PRACH" },
	{ 0, NULL }
};

const struct value_string octphy_dir_names[5] = 
{
	{ cOCTVC1_GSM_DIRECTION_ENUM_NONE,	"None" },
	{ cOCTVC1_GSM_DIRECTION_ENUM_TX_BTS_MS,	"TX_BTS_MS(DL)" },
	{ cOCTVC1_GSM_DIRECTION_ENUM_RX_BTS_MS,	"RX_BTS_MS(UL)" },
	{ cOCTVC1_GSM_DIRECTION_ENUM_TX_BTS_MS | cOCTVC1_GSM_DIRECTION_ENUM_RX_BTS_MS, "BOTH" },
	{ 0, NULL }
};

const struct value_string octphy_clkmgr_state_vals[8] = {
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_UNINITIALIZE, "UNINITIALIZED" },

/* Note: Octasic renamed cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_UNUSED to
 * cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_IDLE. The following ifdef
 * statement ensures that older headers still work. */
#ifdef cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_UNUSED
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_UNUSED,		"UNUSED" },
#else
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_IDLE,		"IDLE" },
#endif
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_NO_EXT_CLOCK, 	"NO_EXT_CLOCK" },
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_LOCKED,		"LOCKED" },
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_UNLOCKED,	"UNLOCKED" },
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_ERROR,		"ERROR" },
	{ cOCTVC1_HW_CLOCK_SYNC_MGR_STATE_ENUM_DISABLE,		"DISABLED" },
	{ 0, NULL }
};

const struct value_string octphy_cid_vals[35] = {
	{ cOCTVC1_GSM_MSG_TRX_OPEN_CID,			"TRX-OPEN" },
	{ cOCTVC1_GSM_MSG_TRX_CLOSE_CID,		"TRX-CLOSE" },
	{ cOCTVC1_GSM_MSG_TRX_STATUS_CID,		"TRX-STATUS" },
	{ cOCTVC1_GSM_MSG_TRX_INFO_CID,			"TRX-INFO" },
	{ cOCTVC1_GSM_MSG_TRX_RESET_CID,		"TRX-RESET" },
	{ cOCTVC1_GSM_MSG_TRX_MODIFY_CID,		"TRX-MODIFY" },
	{ cOCTVC1_GSM_MSG_TRX_LIST_CID,			"TRX-LIST" },
	{ cOCTVC1_GSM_MSG_TRX_CLOSE_ALL_CID,		"TRX-CLOSE-ALL" },
	{ cOCTVC1_GSM_MSG_TRX_START_RECORD_CID,		"RECORD-START" },
	{ cOCTVC1_GSM_MSG_TRX_STOP_RECORD_CID,		"RECORD-STOP" },
	{ cOCTVC1_GSM_MSG_TRX_ACTIVATE_LOGICAL_CHANNEL_CID, "LCHAN-ACT" },
	{ cOCTVC1_GSM_MSG_TRX_DEACTIVATE_LOGICAL_CHANNEL_CID, "LCHAN-DEACT" },
	{ cOCTVC1_GSM_MSG_TRX_STATUS_LOGICAL_CHANNEL_CID, "LCHAN-STATUS" },
	{ cOCTVC1_GSM_MSG_TRX_INFO_LOGICAL_CHANNEL_CID,	"LCHAN-INFO" },
	{ cOCTVC1_GSM_MSG_TRX_LIST_LOGICAL_CHANNEL_CID,	"LCHAN-LIST" },
	{ cOCTVC1_GSM_MSG_TRX_REQUEST_LOGICAL_CHANNEL_EMPTY_FRAME_CID,
							"LCHAN-EMPTY-FRAME" },
	{ cOCTVC1_GSM_MSG_TRX_REQUEST_LOGICAL_CHANNEL_DATA_CID,	"LCHAN-DATA" },
	{ cOCTVC1_GSM_MSG_TRX_ACTIVATE_PHYSICAL_CHANNEL_CID, "PCHAN-ACT" },
	{ cOCTVC1_GSM_MSG_TRX_DEACTIVATE_PHYSICAL_CHANNEL_CID, "PCHAN-DEACT" },
	{ cOCTVC1_GSM_MSG_TRX_STATUS_PHYSICAL_CHANNEL_CID, "PCHAN-STATUS" },
	{ cOCTVC1_GSM_MSG_TRX_RESET_PHYSICAL_CHANNEL_CID, "PCHAN-RESET" },
	{ cOCTVC1_GSM_MSG_TRX_LIST_PHYSICAL_CHANNEL_CID, "PCHAN-LIST" },
	{ cOCTVC1_GSM_MSG_TRX_INFO_PHYSICAL_CHANNEL_CID, "PCHAN-INFO" },
	{ cOCTVC1_GSM_MSG_TRX_MODIFY_PHYSICAL_CHANNEL_CIPHERING_CID,
							"PCHAN-CIPH-MODIFY" },
	{ cOCTVC1_GSM_MSG_TRX_INFO_PHYSICAL_CHANNEL_CIPHERING_CID,
							"PCHAN-CIPH-INFO" },
	{ cOCTVC1_GSM_MSG_TRX_INFO_PHYSICAL_CHANNEL_MEASUREMENT_CID,
							"PCHAN-MEASUREMENT" },
	{ cOCTVC1_GSM_MSG_TRX_INFO_RF_CID,		"RF-INFO" },
	{ cOCTVC1_GSM_MSG_TRX_MODIFY_RF_CID,		"RF-MODIFY" },
	{ cOCTVC1_GSM_MSG_TAP_FILTER_LIST_CID,		"TAP-FILTER-LIST" },
	{ cOCTVC1_GSM_MSG_TAP_FILTER_INFO_CID,		"TAP-FILTER-INFO" },
	{ cOCTVC1_GSM_MSG_TAP_FILTER_STATS_CID,		"TAP-FILTER-STATS" },
	{ cOCTVC1_GSM_MSG_TAP_FILTER_MODIFY_CID,	"TAP-FILTER-MODIFY" },
	{ cOCTVC1_GSM_MSG_TRX_START_LOGICAL_CHANNEL_RAW_DATA_INDICATIONS_CID,
							"LCHAN-RAW-DATA-START" },
	{ cOCTVC1_GSM_MSG_TRX_STOP_LOGICAL_CHANNEL_RAW_DATA_INDICATIONS_CID,
							"LCHAN-RAW-DATA-STOP" },
	{ 0, NULL }
};

const struct value_string octphy_eid_vals[7] = {
	{ cOCTVC1_GSM_MSG_TRX_TIME_INDICATION_EID,	"TIME.ind" },
	{ cOCTVC1_GSM_MSG_TRX_STATUS_CHANGE_EID,	"TRX-STATUS-CHG.ind" },
	{ cOCTVC1_GSM_MSG_TRX_LOGICAL_CHANNEL_DATA_INDICATION_EID,
							"LCHAN-DATA.ind" },
	{ cOCTVC1_GSM_MSG_TRX_LOGICAL_CHANNEL_READY_TO_SEND_INDICATION_EID,
							"LCHAN-RTS.ind" },
	{ cOCTVC1_GSM_MSG_TRX_LOGICAL_CHANNEL_RACH_INDICATION_EID,
							"LCHAN-RACH.ind" },
	{ cOCTVC1_GSM_MSG_TRX_LOGICAL_CHANNEL_RAW_DATA_INDICATION_EID,
							"LCHAN-RAW-DATA.ind" },
	{ 0, NULL }
};
