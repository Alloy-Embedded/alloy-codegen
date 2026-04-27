# Extend Zephyr DTS Adapter Coverage to Renesas / TI / Infineon / Ambiq / SiLabs

## Why

`ingest-zephyr-dts-as-source` shipped the cross-vendor spine and
admitted Nordic nRF52 as the proof-of-life.  The proposal said
"one integration unlocks ~10 vendors that each would otherwise
require a bespoke 200-1000 LOC adapter" — but each of those
vendors still needs its own
`COMPATIBLE_MAPS["<vendor>"]` table populated and a
`_register_<vendor>_<family>.py` module wired in.

This change cashes the destrava: add five vendor compatible-maps
+ vendor-registry decorators so the adapter actually covers what
Zephyr already provides.

## What Changes

- `src/alloy_codegen/sources/zephyr_dts.py:COMPATIBLE_MAPS`
  gains five vendor entries:
  - `"renesas"` — RA / RX / Synergy peripherals
    (`renesas,ra-uart-sci`, `renesas,ra-spi`,
    `renesas,ra-iic`, …).
  - `"ti"` — MSP432 / SimpleLink / TI Sitara
    (`ti,cc13xx-uart`, `ti,msp432-uart`, …).
  - `"infineon"` — XMC / PSoC / TLE
    (`infineon,xmc4xxx-uart`, `infineon,cat1-spi`, …).
  - `"ambiq"` — Apollo3 / Apollo4 SoCs
    (`ambiq,apollo3-uart`, `ambiq,apollo3-spi`, …).
  - `"silabs"` — EFR32 / EFM32
    (`silabs,gecko-usart`, …).
- One new `_register_<vendor>_<family>.py` per pilot family per
  vendor.  Pilots: `renesas/ra4`, `ti/cc13x2`, `infineon/xmc4xxx`,
  `ambiq/apollo3`, `silabs/efr32`.
- `bootstrap.py:DEVICE_REGISTRY` + `SOURCE_BUNDLES` extended with
  one device per pilot family.
- Per-pilot minimal `family.json` + `devices/<device>.json`
  patches following the Nordic nRF52840 pattern (~50 LOC each).
- One snapshotted DTS per pilot device under
  `tests/fixtures/zephyr-dts/<vendor>/<device>.dts`.
- `affected_families.py` static-core-map gets the five new
  entries so the per-arch ISA classifier scopes correctly.
- Test parity for every new vendor: registry resolution +
  end-to-end normalize + IR shape sanity, mirroring
  `tests/test_zephyr_dts.py`.

## Impact

Admitted vendors goes from 6 to 11.  Each admission costs
~500 LOC (compatible map + registration + minimal patches +
one fixture DTS) — vs. ~2000-5000 LOC for a bespoke adapter.

After this lands, ~30 additional MCU families are *trivially*
admittable (each existing Zephyr soc directory is a single
new entry).  Bulk admission of those is the
`add-bulk-admission-flow` change's job.

## What this DOES NOT do

- Does not bulk-admit every chip Zephyr supports per vendor.
  Each vendor contributes one pilot device for plumbing
  validation; bulk admission follows in `add-bulk-admission-flow`.
- Does not fill pinctrl groups, clock-tree edges, or DMA
  matrices.  Those are
  `decode-zephyr-pinctrl-into-connection-candidates` +
  follow-up clock/DMA changes.
- Does not change the existing Nordic admission.
