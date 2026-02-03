/*
 * Copyright (c) 2026, Texas Instruments Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FWL_H
#define FWL_H

#include <stdint.h>
#include <lib/utils_def.h>

/* Addresses of regions for firewalling */
#define DDR_BASE		0x80000000
#define DDR_SIZE		0x7FFFFFFF
#define ATF_BASE		DDR_BASE + BL31_BASE
#define ATF_SIZE		ATF_BASE + BL31_SIZE
/* BL32 region addresses are specified in board.mk */

#define TFA_HOST_ID		10U
#define A53_PRIV_ID		4U
#define FW_BACKGROUND_BIT	8U

/* Firewall IDs */
#define DDR_FWL_ID		1U
#define OSPI_FWL_ID		97U
#define ADC_MCASP_FWL_ID	160U

/* Number of firewall regions */
#define OSPI_FWL_NUM_REGIONS		8U
#define ADC_MCASP_FWL_NUM_REGIONS	16U

/* Firewall Regions */
#define DDR_BG_REGION		0U
#define DDR_BL31_REGION		1U
#define DDR_BL32_REGION		2U

/* Firewall Control Register Values */
#define FWL_CTRL_EN		0xA
#define FWL_CTRL_EN_BG		FWL_CTRL_EN | (1 << FW_BACKGROUND_BIT)

/* Firewall permission values */
#define FWL_PERM_ALL_RW		0xC3BBBB /* RW access to ALL hosts */
#define FWL_PERM_SEC_RW		0x400BB /* RW access to only secure hosts */

enum k3_fwl_region_type {
	K3_FWL_REGION_FOREGROUND = 0,
	K3_FWL_REGION_BACKGROUND = BIT(FW_BACKGROUND_BIT),
};

struct fwl_data {
	uint16_t fwl_id;
	uint8_t num_regions;
};

/*
 * Updates firewall configurations by disabling ROM-configured firewalls.
 * This function should be called during boot initialization and after
 * resume from low power mode to ensure firewall regions that were
 * configured by ROM for the boot phase are properly disabled.
 */
void update_fwl_configs(void);

#endif /* FWL_H */
