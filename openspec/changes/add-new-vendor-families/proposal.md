# Add New Vendor Families

## Why

The alloy `expand-chip-coverage` openspec targets 20+ additional MCU families.
alloy-codegen must admit each family, generate the full artifact set, and
publish it to `alloy-devices` before alloy can compile for that target.

Current admitted families: SAME70, STM32G0, STM32F4, ESP32 classic, ESP32-C3,
ESP32-S3, RP2040, AVR-DA (8 = 9 in pipeline with LPC55S69 placeholder).

Families required by `expand-chip-coverage` (not yet admitted):

| Family          | Vendor      | Source format        | Priority |
|-----------------|-------------|----------------------|----------|
| STM32H7         | ST          | CMSIS-SVD + Open Pin Data | High |
| STM32L4         | ST          | CMSIS-SVD + Open Pin Data | High |
| STM32U5         | ST          | CMSIS-SVD + Open Pin Data | Medium |
| STM32WB55       | ST          | CMSIS-SVD + Open Pin Data | Medium |
| nRF52840        | Nordic Semi | CMSIS-SVD + SDK headers   | High |
| nRF5340         | Nordic Semi | CMSIS-SVD + SDK headers   | Medium |
| SAMD21          | Microchip   | ATDF                      | Medium |
| SAMD51/E5x      | Microchip   | ATDF                      | Medium |
| LPC55S69        | NXP         | MCUX SDK + SVD            | Medium |
| RP2350          | Raspberry Pi| pico-sdk SVD              | High |
| ESP32-H2        | Espressif   | SVD + gpio_sig_map        | Low    |
| ESP32-C6        | Espressif   | SVD + gpio_sig_map        | Low    |
| GD32F450        | GigaDevice  | CMSIS-SVD (clone)         | Low    |
| TM4C123         | TI          | CMSIS-SVD                 | Low    |
| CH32V307        | WCH         | CMSIS-SVD (RISC-V)        | Low    |
| IMXRT1062       | NXP         | MCUX SDK                  | Low    |

This openspec covers the admission pipeline: source fetch, normalizer adapter,
validation, and initial artifact generation (registers.hpp, startup, capabilities.json,
and the driver_semantics stubs). Full semantic trait population (GPIO/UART/SPI/…)
is deferred to follow-up openspecs per-family.

## What Changes

### Admission pipeline extension

The codegen's `vendor-admission` spec defines admission criteria:
1. Source data fetched and pinned (SVD/ATDF/SDK, specific version).
2. Normalizer adapter produces a valid `CanonicalDeviceIR`.
3. Generated artifacts pass schema validation.
4. Golden tests created.
5. `capabilities.json` emitted with correct family facts.
6. Artifact published to `alloy-devices` under the correct vendor/family path.

This openspec adds each new family through this pipeline.

### High-priority families (Phase 1)

**STM32H7** (H743, H750):
- Source: STM32H7 SVD from ARM CMSIS-SVD repo + ST Open Pin Data.
- Adapter: reuse `STM32Normalizer` with H7 clock tree (dual APB buses, D1/D2/D3 domains).
- Key trait: H7 has two Cortex-M7 + M4 cores; codegen marks M7 as primary.
  M4 core exposed via `multicore_topology = "stm32-dual-core"` (asymmetric,
  similar to Xtensa but Cortex-based). Publish two artifact sets: H7_M7, H7_M4.
- Partition layouts for `add-bootloader-integration`: dual-bank flash (1MB + 1MB).

**STM32L4** (L432KC, L476RG):
- Source: STM32L4 SVD + Open Pin Data.
- Low-power peripheral variants: LPUART1, LPTIM1/2 added to semantic headers.
- No dual-core; standard Cortex-M4.

**nRF52840** (Nordic):
- Source: nRF52840 CMSIS-SVD (from Nordic SDK `modules/hal/nordic`).
- Adapter: new `NordicNormalizer`. nRF peripherals use EasyDMA (`PSEL.*` registers
  for pin routing), UARTE (UART with EasyDMA), SPIM, TWIM (I2C master with DMA).
- Key trait: nRF52840 has a USBD (full-speed USB Device) peripheral and Bluetooth
  radio. Both exposed in `capabilities.json`. USB in `usb.hpp`.
- GPIOTE (GPIO Tasks and Events) is the nRF equivalent of RP2040 PIO for simple
  GPIO event routing. Exposed in `gpio.hpp` as `kHasGpiote=true`.

**RP2350** (Raspberry Pi):
- Source: pico-sdk SVD for RP2350 (RP2350A/B variants).
- Adapter: extend `RP2040Normalizer` for RP2350. New features:
  - Dual Cortex-M33 + RISC-V hazard3 cores (soft-selectable). Codegen
    generates two artifact variants: `rp2350-arm` (Cortex-M33) and
    `rp2350-riscv` (hazard3).
  - 8 KB OTP, SHA-256 hardware accelerator, TRNG — exposed in `capabilities.json`.
  - PIO: 3 PIO blocks (vs. 2 on RP2040). 12 DMA channels (vs. 12 on RP2040).
  - 48 GPIOs (vs. 30 on RP2040).

### Medium-priority families (Phase 2)

**STM32U5** (U575ZI): ultra-low-power, TrustZone, OCTOSPI. Standard Cortex-M33.
**STM32WB55**: Cortex-M4 + M0+ (BLE radio). Dual artifact (M4 and M0+).
**nRF5340**: Cortex-M33 × 2 (app core + net core). Dual artifact.
**SAMD21** (SAMD21G18): Microchip ATDF. Reuse `MicrochipAtdfNormalizer`.
  SERCOM peripherals (each SERCOM configures as UART/SPI/I2C). Key challenge:
  SERCOM mux tables must map SERCOM number + pin-mux letter to valid PADS.
**SAMD51/E5x**: ATDF. Faster Cortex-M4 variant of SAMD21. SERCOM + QSPI + CAN.
**LPC55S69**: NXP MCUX SDK. `NxpMcuxNormalizer` (partially implemented).
  FlexComm peripherals (each configures as UART/SPI/I2C). Trustzone-M.

### Low-priority families (Phase 3)

**ESP32-H2, ESP32-C6**: Espressif SVD + gpio_sig_map. Extend `EspressifNormalizer`.
**GD32F450**: STM32F4-compatible clone. GigaDevice SVD. Reuse `STM32Normalizer`
  with GD-specific overrides (different PLL, some extra peripherals).
**TM4C123**: TI CMSIS-SVD. New `TiNormalizer`. Standard Cortex-M4.
**CH32V307**: WCH CMSIS-SVD for RISC-V. New `WchNormalizer`. First non-ARM,
  non-Xtensa/RISC-V-exotic family — tests the toolchain-agnostic artifact contract.
**IMXRT1062**: NXP MCUX SDK. Extend `NxpMcuxNormalizer`. 600 MHz Cortex-M7.
  FlexSPI (external flash), eLCDIF (display), ENET (Ethernet) in capabilities.

### `vendor-admission` spec updates

The `vendor-admission` spec gains explicit admission scenarios for each new family,
including the multicore topology assertions (H7 M4 artifact, WB55 M0+, RP2350 dual
ISA) and a RISC-V admission scenario for CH32V307.

## What Does NOT Change

- Existing admitted families — adapters are extended, not replaced.
- The artifact contract — all new families produce the same artifact structure.
- Semantic trait population for new families — stubs with `kPresent=false` at
  admission; full population in follow-up per-family openspecs.

## Dependencies

- `expose-xtensa-dual-core-facts` (in-flight) — RP2350 and STM32H7 dual-core
  topology reuses the `MulticoreTopology` vocabulary introduced there.
