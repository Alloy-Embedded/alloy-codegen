# Extend Zephyr DTS Vendor Coverage

## Why

`ingest-zephyr-dts-as-source` (archived 2026-04-27) shipped the
Zephyr DTS adapter but only registered a single compatible-string
map: `NORDIC_COMPATIBLE_MAP`.  Every other vendor that Zephyr
covers — Renesas RA, TI tiva-c, Atmel SAMD/SAML, Ambiq Apollo3,
Infineon XMC/PSoC, SiLabs gecko, Espressif ESP32, STM32 — falls
into the "unmapped compatible → silently skipped" path and
produces a canonical IR with **zero peripherals**.

Without compatible-string maps for those vendors, the cross-vendor
spine the original proposal promised does not actually work for
anyone except Nordic.  Any contributor pointing the adapter at a
Zephyr checkout for a non-Nordic SoC sees an empty IR with no
diagnostic that the *adapter* (not their checkout) is the problem.

This change is **data-only**: extend `COMPATIBLE_MAPS` with
curated maps for the next tier of vendors, document the
conventions, and add tests asserting each map covers the
expected peripheral classes.

## What Changes

- Add seven new compatible-string maps to
  `src/alloy_codegen/sources/zephyr_dts.py::COMPATIBLE_MAPS`:
  - `renesas` (Renesas RA — `renesas,ra-sci-uart`, etc.)
  - `ti` (TI tiva-c / cc13xx — `ti,cc13xx-cc26xx-uart`, etc.)
  - `atmel` (Atmel SAMD/SAML — `atmel,sam0-uart`, etc.)
  - `ambiq` (Ambiq Apollo — `ambiq,uart`, `ambiq,iom`, etc.)
  - `infineon` (Infineon XMC/PSoC — `infineon,xmc4xxx-uart`, etc.)
  - `silabs` (SiLabs gecko — `silabs,gecko-usart`, etc.)
  - `espressif` (ESP32 — `espressif,esp32-uart`, etc.)
- Promote the cross-vendor families (`mmio-sram`, `soc-nv-flash`,
  ARM NVIC `arm,armv7m-nvic` / `arm,armv8m-nvic`) into a shared
  `_GENERIC_COMPATIBLE_MAP` that every vendor map merges with so
  memory + interrupt-controller nodes are recognised consistently.
- Add `compatible_map_for_vendor` lookups for each new vendor key.
- Tests: per-vendor map coverage tests + an "unmapped compatible
  is skipped, not raised" regression test for a synthetic vendor.

## Impact

- Affected code: `src/alloy_codegen/sources/zephyr_dts.py` (data
  table + module exports); `tests/test_zephyr_dts_*.py`.
- No new vendor adapters are registered.  Admitting a new family
  still requires its own `_register_<vendor>_<family>.py` shim and
  fixtures — this change just makes that follow-up cheap (no need
  to also extend the adapter's vocabulary).
- No IR/schema changes.  Downstream artifacts unchanged for
  currently admitted devices.

## What this does NOT do

- Does not admit any new device into `DEVICE_REGISTRY`.  Admission
  is gated on fixtures + goldens and lands in a separate
  `add-new-vendor-families` change (already open).
- Does not extend coverage to clocks, DMA channels, or pinctrl —
  those remain deferred (the original proposal's "best-effort and
  follow-up" carve-out still applies).
- Does not parse vendor-specific binding YAML.  We hand-curate the
  compatible→ip-name mapping; auto-derivation from `dts/bindings/`
  is a much larger effort and is out of scope here.
