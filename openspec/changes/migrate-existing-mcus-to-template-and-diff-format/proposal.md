# Migrate Existing MCUs to Template + Diff Format

## Why

The audit shows 14,129 LOC across 28 patch JSONs.  The new
infrastructure (`peripheral-trait-template-library`,
`invert-patch-as-diff`) lets us collapse this to **~3,500 LOC**
(75% reduction) by:

1. Moving Tier 2/3/4 arrays
   (`uart_*`, `spi_*`, `i2c_*`, `timer_*`, `pwm_*`, `adc_*`)
   from device patches to
   `data/peripheral_traits/<class>/<ip_version>.toml`.
2. Dropping fields the SVD/DTS already carries (peripherals,
   interrupts, base addresses, registers).
3. Keeping only true overrides (package, core, summary, RCC
   bindings, system_clock_profiles, calibration data).

This is a **migration**, not an architectural change.  All the
plumbing is in place; we now flip the existing devices over.

## What Changes

The change executes in waves to bound risk per PR.  Each wave
ships goldens regenerated via `auto-update-goldens` and
reviewed manually.

### Wave 1 — pilots (lowest risk, validates round-trip)

- `nordic/nrf52/nrf52840` — already 37 LOC, prove the round-trip.
- `raspberrypi/rp2040/{pico,rp2040}` — single IP version per
  peripheral; clean SVD; ideal pilot.
- `espressif/esp32c3/esp32c3` — single device; just landed.

### Wave 2 — STM32 (biggest single LOC win)

- `st/stm32g0/{stm32g030f6,stm32g071rb,stm32g0b1re}` — three
  devices share `usart_v2`, `spi_v2`, `i2c_v2` IPs.  Template
  pays off 3×.
- `st/stm32f4/{stm32f401re,stm32f405rg}` — two devices, shared
  STM32F4 IP versions.

### Wave 3 — Espressif

- `espressif/esp32/{esp32,esp32-wroom32}` — Xtensa LX6.
- `espressif/esp32s3/esp32s3` — Xtensa LX7.

### Wave 4 — iMXRT (biggest single device-patch win)

- `nxp/imxrt1060/{mimxrt1062,mimxrt1064}` — 1224 LOC each;
  ~1040 LOC moves to LPUART/LPSPI/LPI2C templates.

### Wave 5 — ATDF-only families (gated on a prerequisite)

- **Prerequisite:** `extend-autogen-to-atdf-and-mcuxpresso` —
  the autogen tool today only handles SVD; SAME70 + AVR-DA
  have no SVD baseline, so the diff invertor has nothing to
  subtract against.
- `microchip/same70/{atsame70n21b,atsame70q21b}`
- `microchip/avr-da/avr128da32`

## Impact

After Wave 4 (without Wave 5):
- Patches drop from ~14,129 → ~5,500 LOC (61% reduction).
- New STM32 / iMXRT / ESP32 / RP2040 / Nordic admissions cost
  10-30 LOC of override JSON (down from 180-1224 today).

After Wave 5 (with the ATDF prerequisite):
- Patches drop to ~3,500 LOC (75% reduction).
- All admitted families on the diff/template model.

## What this DOES NOT do

- Does not change the resolved IR.  The merged
  `baseline ← template ← family-patch ← device-patch` output
  matches today's patch-only IR byte-for-byte (validated by
  goldens staying green per wave).
- Does not introduce new templates.  The library only fills
  what `peripheral-trait-template-library` already seeded; new
  IP versions get added in their own changes.
- Does not auto-migrate.  Each wave is a reviewer-gated PR.
  The `--update-goldens` flag is the migration tool; the
  reviewer still inspects the diff.
