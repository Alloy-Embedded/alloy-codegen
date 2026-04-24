/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 * SPDX-License-Identifier: Apache-2.0
 *
 * Supplementary-source fixture for alloy-codegen Phase 2.2 IO Matrix parser
 * tests.  Carved out from esp-idf v5.2 at
 * ``components/soc/esp32c3/include/soc/gpio_sig_map.h``.  Only the signals
 * currently referenced by ``patches/espressif/esp32c3/family.json`` are
 * included — this is enough to assert that every ``af_number`` value in the
 * family patch matches the upstream IO Matrix index, which is all the parser
 * test needs to cover.
 *
 * To regenerate: diff the ESP32-C3 pin_signals entries against a full
 * gpio_sig_map.h from the pinned esp-idf tag and refresh this fixture so it
 * includes every signal name cited in the patches.
 */

#pragma once

/* UART0 console */
#define U0RXD_IN_IDX            6
#define U0TXD_OUT_IDX           6

/* UART1 secondary */
#define U1RXD_IN_IDX            9
#define U1TXD_OUT_IDX           9

/* I2C0 */
#define I2CEXT0_SCL_IN_IDX      14
#define I2CEXT0_SCL_OUT_IDX     14
#define I2CEXT0_SDA_IN_IDX      15
#define I2CEXT0_SDA_OUT_IDX     15

/* SPI2 (FSPI) */
#define FSPIQ_IN_IDX            63
#define FSPIQ_OUT_IDX           63
#define FSPICLK_OUT_IDX         63
#define FSPID_IN_IDX            64
#define FSPID_OUT_IDX           64
#define FSPICS0_OUT_IDX         68
