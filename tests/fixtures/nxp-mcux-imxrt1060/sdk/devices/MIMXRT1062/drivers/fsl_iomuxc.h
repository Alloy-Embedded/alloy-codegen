/*
 * Copyright 2026 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Minimal fixture header for alloy-codegen NXP imxrt1060 bootstrap tests.
 * Represents a representative subset of fsl_iomuxc.h for MIMXRT1062.
 *
 * Macro format: IOMUXC_<PAD_NAME>_<SIGNAL_NAME>
 *   muxRegister, muxMode, inputRegister, inputDaisy, configRegister
 */

#ifndef _FSL_IOMUXC_H_
#define _FSL_IOMUXC_H_

/* GPIO_EMC_00, pad number 0 */
#define IOMUXC_GPIO_EMC_00_SEMC_DATA00          0x401F8014U, 0x0U, 0U, 0U, 0x401F8204U
#define IOMUXC_GPIO_EMC_00_LPSPI1_SCK           0x401F8014U, 0x2U, 0x401F8490U, 0x1U, 0x401F8204U
#define IOMUXC_GPIO_EMC_00_GPIO4_IO00           0x401F8014U, 0x5U, 0U, 0U, 0x401F8204U

/* GPIO_EMC_01, pad number 1 */
#define IOMUXC_GPIO_EMC_01_SEMC_DATA01          0x401F8018U, 0x0U, 0U, 0U, 0x401F8208U
#define IOMUXC_GPIO_EMC_01_LPSPI1_PCS0          0x401F8018U, 0x2U, 0x401F848CU, 0x1U, 0x401F8208U
#define IOMUXC_GPIO_EMC_01_GPIO4_IO01           0x401F8018U, 0x5U, 0U, 0U, 0x401F8208U

/* GPIO_AD_B0_00, pad number 0 */
#define IOMUXC_GPIO_AD_B0_00_LPI2C1_SCL         0x401F8024U, 0x0U, 0x401F841CU, 0x0U, 0x401F8214U
#define IOMUXC_GPIO_AD_B0_00_LPUART1_TX         0x401F8024U, 0x2U, 0U, 0U, 0x401F8214U
#define IOMUXC_GPIO_AD_B0_00_GPIO1_IO00         0x401F8024U, 0x5U, 0U, 0U, 0x401F8214U

/* GPIO_AD_B0_01, pad number 1 */
#define IOMUXC_GPIO_AD_B0_01_LPI2C1_SDA         0x401F8028U, 0x0U, 0x401F8420U, 0x0U, 0x401F8218U
#define IOMUXC_GPIO_AD_B0_01_LPUART1_RX         0x401F8028U, 0x2U, 0x401F853CU, 0x0U, 0x401F8218U
#define IOMUXC_GPIO_AD_B0_01_GPIO1_IO01         0x401F8028U, 0x5U, 0U, 0U, 0x401F8218U

#endif /* _FSL_IOMUXC_H_ */
