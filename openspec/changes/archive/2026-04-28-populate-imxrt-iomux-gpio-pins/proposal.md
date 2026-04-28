# Populate iMXRT IOMUX into gpio_pins

## Why

The IR-completeness audit revealed iMXRT1062 has **zero**
`gpio_pins`, **zero** `i2c_peripherals`, **zero**
`uart_peripherals` — the IOMUX tables that NXP ships in
`fsl_iomuxc.h` carry every pin's daisy-chain selectors and
alternate functions, but our `_build_imxrt1060_device_ir` never
extracts them.

Without `gpio_pins` populated, the alloy HAL on iMXRT cannot
issue `requires ValidPinAssignment<Pin, Signal>` constraints,
the connectors emitter falls back to runtime traits only, and
the family is structurally weaker than STM32 despite being more
capable silicon.

## What Changes

- New parser `src/alloy_codegen/sources/nxp_iomux.py` that
  reads `MIMXRT106*/drivers/fsl_iomuxc.h` and extracts the
  `IOMUXC_<PIN>_<MODE>(...)` macros into structured records:
  - `pin_name` (e.g. `GPIO_AD_B0_03`)
  - `peripheral` + `signal` (e.g. `LPUART1`, `TX`)
  - `selector_index` (the IOMUXC selector field value)
  - `daisy_register` + `daisy_value` (cross-bar input
    selection — needed for many iMXRT signals).
- The existing `nxp_mcux.py` adapter calls the new parser and
  surfaces the records as a tuple of `RawPinAlternateFunction`
  records that flow into the existing pin-builder pipeline.
- `_build_imxrt1060_device_ir` populates `gpio_pins` from the
  union of IOMUX pin set + family-catalog pin definitions.
- `connection_candidates` projects every `(pin, peripheral,
  signal)` triple into the IR with
  `route_kind="iomuxc-mux"` (already a known route_kind in the
  pipeline).
- `pin_validation.hpp` for iMXRT1062 + iMXRT1064 emits real
  `PinAssignmentValid<...>` specialisations for each admitted
  pin/signal pair (~hundreds, vs. zero today).

## Impact

iMXRT becomes a first-class structural target — every alloy HAL
driver gains the same `requires ValidPinAssignment<...>`
guarantee STM32 has today.  The "moat over modm" claim becomes
true on a non-STM32 vendor for the first time, on actual silicon
that ships in millions of products.

## What this DOES NOT do

- Does not handle `i2c_peripherals` / `uart_peripherals` / the
  vendor-specific peripheral-descriptor tuples on iMXRT.  Those
  are separate gaps documented in the audit and follow in
  per-class changes.
- Does not migrate iMXRT patches.  The `family.json` continues
  to declare peripherals manually; only `gpio_pins` +
  `connection_candidates` flip to source-derived.
- Does not parse the daisy-chain *selection logic* (when a pin
  needs both a selector + a daisy-register write).  We capture
  the daisy_register/daisy_value pair so the runtime layer can
  consume it, but composing them into a runtime pinmux helper
  is the alloy HAL's job, not the codegen's.
