# Fill GPIO Tier 1 Fields for STM32

## Why

`fill-gpio-semantic-gaps` (archived 2026-04-26) added the alt-function
list per pin, but the **register-field references** in the GPIO trait
specialization are still `kInvalidFieldRef` for STM32 — `kModeField`,
`kPullField`, `kOutputTypeField`, `kSpeedField` all resolve to
invalid.  Other vendors (SAM, RP2040 PIO) do populate them.

Without these fields, the alloy GPIO HAL cannot generate compile-time
register writes for `Gpio<PA0>::set_output_speed<High>()` — the HAL
has to fall back to vendor headers, defeating the purpose of the
codegen layer.

This is a Tier-1 fix (register/field plumbing), not new silicon
facts.  Mirrors the GPIO build pattern that already works for SAM.

## What Changes

### Pipeline

- `_st_gpio_row` (in `runtime_driver_semantics.py`) currently
  ships invalid field refs.  Wire up the existing IR data:
  `device.register_fields` already carries
  `GPIOA.MODER.MODE0`, `OSPEEDR.OSPEED0`, `OTYPER.OT0`,
  `PUPDR.PUPD0` per pin index.  Resolve them per-pin into the row.
- Pin-index awareness: each pin has its own field names
  (`MODE0..MODE15`).  Cache the lookup so emit doesn't repeat
  the resolution 16 times per port.

### Trait surface

No new constexprs; just the existing field-ref slots populated
with valid `FieldRef` records instead of `kInvalidFieldRef`.

### Goldens

Regenerate every `gpio.hpp` golden for STM32G0 / STM32F4.  Diff
scope: 4 field-ref records per pin become non-invalid.

## Impact

Unblocks compile-time GPIO config in the alloy HAL.  Same-shape work
will be needed for ESP32 GPIO IOMUX, but defer until the alloy GPIO
HAL targets ESP32.
