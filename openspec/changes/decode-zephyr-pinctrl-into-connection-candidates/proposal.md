# Decode Zephyr Pinctrl Groups into Connection Candidates

## Why

`ingest-zephyr-dts-as-source` v1 admitted Nordic nRF52840 with
peripherals + interrupts + memories — but **no pinctrl**.  The
emitted `connection_candidates` tuple is empty, which means
`pin_validation.hpp` never gets emitted for nRF52, and any HAL
driver that wants `requires ValidPinAssignment<...>` falls back
to runtime checks.

Zephyr DTS *does* carry pinctrl groups in a structured form
(`pinctrl-0`, `pinctrl-names`, vendor-specific encoding macros
like `NRF_PSEL`, `STM32_PIN_*`).  Decoding them populates
`connection_candidates` so the existing
`emit-pinmux-validator-concepts` machinery emits compile-time
pinmux validation for every Zephyr-admitted device.

## What Changes

- New module `src/alloy_codegen/sources/zephyr_pinctrl.py` with
  per-vendor decoders:
  - **Nordic**: `NRF_PSEL(<func>, <port>, <pin>)` macro decoded
    via a small `(func_name → peripheral_signal)` table.
  - **STM32**: `<STM32_PINMUX 'PA9', AF7_USART1>` style cells
    (already structured by Zephyr's `stm32-pinctrl.yaml`).
  - **NXP**: `<NXP_MUX_*>` IOMUX cells (deferred to follow-up
    `nxp-zephyr-pinctrl-decoder` change — IOMUX is encoding-
    heavy enough to warrant its own pass).
- The decoder returns a tuple of `(pin_name, peripheral, signal,
  af_number)` records that flow into the existing
  `connection_candidates` field of the IR via
  `_build_zephyr_dts_device_ir`.
- A vendor-dispatch table `PINCTRL_DECODERS` mirrors the existing
  `COMPATIBLE_MAPS` shape so adding new-vendor pinctrl is a
  one-entry edit.
- Unsupported pinctrl encodings log + skip rather than fail —
  same defensive stance as the compatible-string handling.
- The Nordic nRF52840 fixture DTS gains a `pinctrl` subnode so
  the fixture exercises the decoder end-to-end.

## Impact

Nordic nRF52840 emits `pin_validation.hpp` with real
`ValidPinAssignment<PinId::P0_06, PeripheralSignal::UART0_TX>`
specialisations.  STM32 admissions via Zephyr DTS (when they
land — currently we use STM32-open-pin-data) get the same.

Cross-vendor compile-time pinmux validation extends from
"STM32 only" (today, via the bespoke STM32 pin-data adapter) to
"every Zephyr-covered vendor" — a moat over modm that no other
HAL can match.

## What this DOES NOT do

- Does not handle NXP IOMUX encoding.  iMXRT pinmux uses a
  completely different encoding (separate selector + daisy
  registers); follows in `nxp-zephyr-pinctrl-decoder`.
- Does not change the existing STM32 admission (which still
  consumes `stm32-open-pin-data`, not Zephyr pinctrl).  The
  Zephyr-pinctrl path is an *additional* source for vendors
  where it's our best option.
- Does not validate pin conflicts (two drivers on same pin in
  incompatible roles).  That's the connection_groups story
  (separate change `emit-pinmux-conflict-checks`).
