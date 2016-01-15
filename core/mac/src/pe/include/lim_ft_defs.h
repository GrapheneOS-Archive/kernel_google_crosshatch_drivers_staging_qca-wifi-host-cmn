/*
 * Copyright (c) 2013-2016 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

#if defined WLAN_FEATURE_VOWIFI_11R
/**=========================================================================

   Macros and Function prototypes FT and 802.11R purposes

   ========================================================================*/

#ifndef __LIMFTDEFS_H__
#define __LIMFTDEFS_H__

#include <cds_api.h>
#include "wma_if.h"

/*--------------------------------------------------------------------------
   Preprocessor definitions and constants
   ------------------------------------------------------------------------*/
#define MAX_FTIE_SIZE             384   /* Max size limited to 384, on acct. of IW custom events */

/*--------------------------------------------------------------------------
   Type declarations
   ------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------
   FT Pre Auth Req SME<->PE
   ------------------------------------------------------------------------*/
typedef struct sSirFTPreAuthReq {
	uint16_t messageType;   /* eWNI_SME_FT_PRE_AUTH_REQ */
	uint16_t length;
	/*
	 * Track if response is processed for this request
	 * We expect only one response per request.
	 */
	bool bPreAuthRspProcessed;
	uint8_t preAuthchannelNum;
	/* BSSID currently associated to suspend the link */
	tSirMacAddr currbssId;
	tSirMacAddr preAuthbssId;       /* BSSID to preauth to */
	uint16_t ft_ies_length;
	uint8_t ft_ies[MAX_FTIE_SIZE];
	tpSirBssDescription pbssDescription;
} tSirFTPreAuthReq, *tpSirFTPreAuthReq;

/*-------------------------------------------------------------------------
   FT Pre Auth Rsp PE<->SME
   ------------------------------------------------------------------------*/
typedef struct sSirFTPreAuthRsp {
	uint16_t messageType;   /* eWNI_SME_FT_PRE_AUTH_RSP */
	uint16_t length;
	uint8_t smeSessionId;
	tSirMacAddr preAuthbssId;       /* BSSID to preauth to */
	tSirRetStatus status;
	uint16_t ft_ies_length;
	uint8_t ft_ies[MAX_FTIE_SIZE];
	uint16_t ric_ies_length;
	uint8_t ric_ies[MAX_FTIE_SIZE];
} tSirFTPreAuthRsp, *tpSirFTPreAuthRsp;

/*--------------------------------------------------------------------------
   FT Pre Auth Rsp Key SME<->PE
   ------------------------------------------------------------------------*/
typedef struct sSirFTUpdateKeyInfo {
	uint16_t messageType;
	uint16_t length;
	uint32_t smeSessionId;
	struct cdf_mac_addr bssid;
	tSirKeyMaterial keyMaterial;
} tSirFTUpdateKeyInfo, *tpSirFTUpdateKeyInfo;

/*--------------------------------------------------------------------------
   FT Pre Auth Rsp Key SME<->PE
   ------------------------------------------------------------------------*/
typedef struct sSirFTPreAuthKeyInfo {
	uint8_t extSetStaKeyParamValid; /* Ext Bss Config Msg if set */
	/* SetStaKeyParams for ext bss msg */
	tLimMlmSetKeysReq extSetStaKeyParam;
} tSirFTPreAuthKeyInfo, *tpSirFTPreAuthKeyInfo;

/*-------------------------------------------------------------------------
   Global FT Information
   ------------------------------------------------------------------------*/
typedef struct sFTPEContext {
	tpSirFTPreAuthReq pFTPreAuthReq;        /* Saved FT Pre Auth Req */
	tSirRetStatus ftPreAuthStatus;
	uint16_t saved_auth_rsp_length;
	uint8_t saved_auth_rsp[MAX_FTIE_SIZE];
	tSirFTPreAuthKeyInfo PreAuthKeyInfo;
	/* Items created for the new FT, session */
	void *pAddBssReq;       /* Save add bss req */
	void *pAddStaReq;       /*Save add sta req  */
	uint32_t peSessionId;
	uint32_t smeSessionId;

	/* This flag is required to indicate on which session the preauth
	 * has taken place, since the auth reponse for preauth will come
	 * for a new BSSID for which there is no session yet. This flag
	 * will be used to extract the session from the session preauth
	 * has been initiated
	 */
	bool ftPreAuthSession;
} tftPEContext, *tpftPEContext;

#endif /* __LIMFTDEFS_H__ */

#endif /* WLAN_FEATURE_VOWIFI_11R */
