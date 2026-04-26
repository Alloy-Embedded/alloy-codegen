# Tasks: Add New Vendor Families

Tasks are in admission-priority order. Each family follows the same 6-step admission
pipeline. CI gate at end of each phase blocks the next phase.

## Phase 1 — High-priority families

### 1.1 STM32H7

- [ ] 1.1.1 Fetch and pin STM32H743ZI SVD from `ARM-software/CMSIS-SVD` at
       commit SHA. Record in `patches/st/stm32h7/SOURCE.lock`.
- [ ] 1.1.2 Fetch ST Open Pin Data for H743ZI (LQFP144). Pin to source commit.
- [ ] 1.1.3 Create `patches/st/stm32h7/family.json`: clock domains D1/D2/D3,
       dual-core topology `stm32-dual-core` (M7 primary, M4 secondary),
       flash dual-bank layout (1MB+1MB at `0x08000000` + `0x08100000`).
- [ ] 1.1.4 Extend `STM32Normalizer` to handle H7 clock domain split. H7 has
       AHB1/AHB2 in D2, AHB3 in D1. APB buses differ from G0/F4.
- [ ] 1.1.5 Add `MulticoreTopology.stm32_dual_core` to IR model. M7 = primary,
       M4 = secondary. Emit two artifact sets: `stm32h743zi-m7/` and `stm32h743zi-m4/`.
- [ ] 1.1.6 Golden tests for stm32h743zi-m7 and stm32h743zi-m4. Assert M7
       artifact has `device:core-count=2`, M4 artifact marks itself as secondary.
- [ ] 1.1.7 Publish to `alloy-devices/st/stm32h7/generated/`.

### 1.2 STM32L4

- [ ] 1.2.1 Fetch and pin STM32L476RG SVD + Open Pin Data (LQFP64).
- [ ] 1.2.2 Create `patches/st/stm32l4/family.json`. Single-core M4.
       Low-power peripherals: LPUART1 base address, LPTIM1/2 bases, LP modes.
- [ ] 1.2.3 Extend `STM32Normalizer` for L4 clock tree (MSI oscillator, LSE,
       RCC_CCIPR2 for additional peripherals).
- [ ] 1.2.4 Add LPUART1 and LPTIM to the semantic header emit list
       (`uart.hpp` gains `UartId::Lpuart1`; `timer.hpp` gains `TimerId::Lptim1/2`).
- [ ] 1.2.5 Golden tests. Publish to `alloy-devices/st/stm32l4/generated/`.

### 1.3 nRF52840

- [ ] 1.3.1 Fetch nRF52840 SVD from `zephyrproject-rtos/hal_nordic` at pinned
       tag. Record in `patches/nordic/nrf52840/SOURCE.lock`.
- [ ] 1.3.2 Implement `NordicNormalizer` in
       `src/alloy_codegen/sources/nordic_svd.py`. Parse nRF PSEL register schemas
       to extract UART/SPI/TWI pin routing flexibility (any GPIO, PSEL.TXD etc.).
- [ ] 1.3.3 Create `patches/nordic/nrf52840/family.json`: GPIOTE channel count=8,
       EasyDMA channel count, USBD base address, BLE radio capability flag.
- [ ] 1.3.4 Add `kHasGpiote=true`, `kGpioteChannel` to GPIO trait model.
- [ ] 1.3.5 Emit UARTE0/1 as `UartId::Uarte0/1` in `uart.hpp` with `kSupportsDma=true`.
       SPIM0/1/2/3 in `spi.hpp`. TWIM0/1 in `i2c.hpp`. USBD in `usb.hpp`.
- [ ] 1.3.6 Golden tests for nrf52840. Publish to `alloy-devices/nordic/nrf52840/generated/`.

### 1.4 RP2350

- [ ] 1.4.1 Fetch RP2350 SVD from `raspberrypi/pico-sdk` at pinned tag.
       Two SVD variants: RP2350A (30 GPIO), RP2350B (48 GPIO).
- [ ] 1.4.2 Extend `RP2040Normalizer` into `RP2350Normalizer`. Key differences:
       - 3 PIO blocks (vs. 2). Populate 3 `PioDescriptor`s.
       - 48 GPIOs on RP2350B.
       - 3 PIO blocks: PIO0 base=0x50200000, PIO1=0x50300000, PIO2=0x50400000.
       - SHA-256 accelerator, TRNG, OTP: add to `capabilities.json`.
       - Dual ISA: emit `rp2350-arm` (Cortex-M33) and `rp2350-riscv` (hazard3).
- [ ] 1.4.3 Add `MulticoreTopology.rp2350_dual_isa` to IR. Emit two separate
       artifact sets (arm + riscv). Each gets its own startup, vector table,
       and toolchain spec.
- [ ] 1.4.4 `patches/raspberrypi/rp2350/family.json`: ISA variants, PIO counts,
       TRNG/SHA capabilities.
- [ ] 1.4.5 Golden tests for rp2350-arm and rp2350-riscv. Assert 3 PIO blocks
       in rp2350-arm artifact.
- [ ] 1.4.6 Publish to `alloy-devices/raspberrypi/rp2350/generated/`.

## Phase 2 — Medium-priority families

### 2.1 STM32U5

- [ ] 2.1.1 Fetch STM32U575ZI SVD + Open Pin Data. Pin sources.
- [ ] 2.1.2 Extend `STM32Normalizer` for U5 clock tree (MSIS/MSIK, LP peripherals).
       TrustZone: emit non-secure artifact only (secure image is application concern).
- [ ] 2.1.3 OCTOSPI peripheral in capabilities: add `kSupportsOctospi=true`.
- [ ] 2.1.4 Golden + publish to `alloy-devices/st/stm32u5/generated/`.

### 2.2 STM32WB55

- [ ] 2.2.1 Fetch STM32WB55 SVD. Dual-core (M4 + M0+).
- [ ] 2.2.2 Emit dual artifact (M4 + M0+) reusing `stm32-dual-core` topology.
       M0+ runs BLE stack; M4 runs application.
- [ ] 2.2.3 BLE radio capability in `capabilities.json`.
- [ ] 2.2.4 Golden + publish to `alloy-devices/st/stm32wb/generated/`.

### 2.3 nRF5340

- [ ] 2.3.1 Fetch nRF5340 SVD. App core (M33) + Net core (M33).
- [ ] 2.3.2 Add `MulticoreTopology.nordic_dual_m33` to IR. Emit two artifacts.
- [ ] 2.3.3 Golden + publish to `alloy-devices/nordic/nrf5340/generated/`.

### 2.4 SAMD21

- [ ] 2.4.1 Fetch SAMD21G18 ATDF from Microchip DFP. Pin to version.
- [ ] 2.4.2 Extend `MicrochipAtdfNormalizer` for SERCOM multiplex table.
       SERCOM0–5: each configures as UART/SPI/I2C. Pin MUX C/D selects PAD routing.
- [ ] 2.4.3 `SercomSemanticTraits<SercomId::Sercom{N}>`: `kMode` enum (Uart/Spi/I2c)
       determined at compile time by config — emit all modes as valid.
- [ ] 2.4.4 Golden + publish to `alloy-devices/microchip/samd21/generated/`.

### 2.5 SAMD51 / SAM E5x

- [ ] 2.5.1 Fetch SAMD51J20A ATDF. Extend normalizer (12 SERCOMs, QSPI, CAN0/1).
- [ ] 2.5.2 QSPI in `capabilities.json`: `kSupportsQspi=true`.
- [ ] 2.5.3 Golden + publish to `alloy-devices/microchip/samd51/generated/`.

### 2.6 LPC55S69

- [ ] 2.6.1 Complete `NxpMcuxNormalizer` for LPC55S69 (placeholder exists).
       FlexComm0–8: multiplex as UART/SPI/I2C/I2S.
- [ ] 2.6.2 TrustZone-M: non-secure artifact only.
- [ ] 2.6.3 Golden + publish to `alloy-devices/nxp/lpc55s6x/generated/`.

## Phase 3 — Low-priority families

- [ ] 3.1 ESP32-H2: extend `EspressifNormalizer`. Zigbee/Thread radio capability.
       Publish to `alloy-devices/espressif/esp32h2/generated/`.
- [ ] 3.2 ESP32-C6: extend `EspressifNormalizer`. Wi-Fi 6, Zigbee/Thread.
       Publish to `alloy-devices/espressif/esp32c6/generated/`.
- [ ] 3.3 GD32F450: new `GigaDeviceNormalizer` extending STM32 SVD logic.
       Publish to `alloy-devices/gigadevice/gd32f4/generated/`.
- [ ] 3.4 TM4C123: new `TexasInstrumentsNormalizer`. Publish to
       `alloy-devices/ti/tm4c123/generated/`.
- [ ] 3.5 CH32V307: new `WchNormalizer` (RISC-V). First RISC-V admission.
       Verify artifact contract works with RISC-V ISA. Publish to
       `alloy-devices/wch/ch32v3/generated/`.
- [ ] 3.6 IMXRT1062: extend `NxpMcuxNormalizer`. FlexSPI, ENET in capabilities.
       Publish to `alloy-devices/nxp/imxrt10xx/generated/`.

## CI gates

- [ ] P1-gate: all Phase 1 families admitted, goldens pass, artifacts published.
       Blocks Phase 2 start. Verify `alloy-devices` publish CI job green.
- [ ] P2-gate: all Phase 2 families admitted.
- [ ] P3-gate: all Phase 3 families admitted.
- [ ] Coverage report: update `docs/COVERAGE_MATRIX.md` after each phase gate.
