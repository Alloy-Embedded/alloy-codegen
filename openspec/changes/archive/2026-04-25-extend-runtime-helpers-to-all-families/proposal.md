# Extend Runtime Helpers to All Admitted Families

## Why

`close-runtime-semantics-gaps` shipped `alloy::clock::enable/disable<>` and
`alloy::pinmux::route<>` but the per-route specializations only land for
SAM E70 (PMC + PIO). Other admitted families publish only the primary
template, which fires the dependent-false `static_assert` for any non-`none`
peripheral — i.e. the helpers are unusable today on STM32 / NXP / ESP32 /
RP2040 / AVR-DA.

For drivers and examples to stay portable across the families we already
admit, every family must specialize both helpers for its own clock and
pinmux subsystem.

## What Changes

Per-family runtime-lite emission gains the missing specializations:

- **st/stm32g0 + st/stm32f4**: `apply_route<>` writes
  `GPIOx_MODER` (alternate-function mode = 0b10) and
  `GPIOx_AFR[0|1]` (4-bit selector). `clock_enable` is already shipped.
- **nxp/imxrt1060**: `apply_route<>` writes
  `IOMUXC_SW_MUX_CTL_PAD_*` (`MUX_MODE` field). `clock_enable` already
  shipped.
- **espressif/esp32c3 + esp32s3**: `clock_enable<>` writes
  `SYSTEM_PERIP_CLK_EN*_REG` set-bit; `apply_route<>` writes the
  GPIO-matrix `GPIO_FUNCx_OUT_SEL_CFG` / `GPIO_FUNCx_IN_SEL_CFG`
  registers and the IO_MUX `IO_MUX_GPIOx_REG`'s `MCU_SEL` field.
- **raspberrypi/rp2040**: `clock_enable<>` writes `RESETS_RESET_CLR`
  (release-from-reset) for the peripheral; `apply_route<>` writes
  `IO_BANK0_GPIOx_CTRL.FUNCSEL`.
- **microchip/avr-da**: `clock_enable<>` is a no-op for peripherals
  with no per-instance clock gate (recorded as such in the device IR);
  `apply_route<>` writes the matching `PORTMUX.*ROUTE*` selector.

Each family change is independent — the codegen dispatch already has a
`family_dir.startswith(...)` ladder; we extend it.

## Impact

- **Affected specs**: `runtime-lite-contract` — primary template fallback
  is replaced by per-family specialization sets.
- **Affected code**:
  - `alloy_codegen/runtime_lite_emission.py` (`_emit_route_apply_helpers`,
    `_emit_clock_enable_disable_helpers`).
  - Generated `routes.hpp` and `clock_bindings.hpp` for every admitted
    family.
- **Republishes**: all admitted families need a fresh publish to land
  the new specializations in `alloy-devices`.
