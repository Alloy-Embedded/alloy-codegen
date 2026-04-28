# Consume alloy-devices-yml as the Canonical Input

## Why

The architectural pivot split the project into three repos:

| Repo | Role |
|---|---|
| `alloy-data-extractor` | Python ETL — vendor source parsing → canonical YAML |
| `alloy-devices-yml` | Schema-validated canonical YAML data |
| `alloy-codegen` (this repo) | C++ code generator — consumes canonical YAML, emits `.hpp`/`.cpp` |

The pivot is ~80% done — the YAML consumer hook
(`sources/alloy_devices_yml.py`, 121 LOC) is already wired into
`stages/normalize.py:3530` and **all 9 admitted families already
have committed YAML** in `data/devices/`.

But this repo still carries everything that *used* to produce
that YAML, before the data-extractor existed:

- **`src/alloy_codegen/sources/`** — 11 vendor source parsers
  (CMSIS-SVD, Zephyr DTS, Microchip ATDF, Espressif esp_idf,
  modm-devices, NXP MCUX, pico-sdk, STM32 Open Pin Data, Zephyr
  pinctrl) totalling **~4,000 LOC**.  Every functional parser
  here has been mirrored into `alloy-data-extractor`.

- **`src/alloy_codegen/vendors/_register_*.py`** —
  family-specific `VendorAdapter`s registering raw-source
  builders (`_build_st_stm32_device_ir`, etc.).  **~2,500 LOC**
  of dead code now that every admitted device's IR comes from
  YAML.

- **`patches/`** — 29 device-correction JSONs (400 KB).  These
  corrections are baked into the canonical YAML at extraction
  time, so applying them again on top of YAML loads is at best
  a no-op and at worst a silent override that diverges from the
  data repo.

- **`tests/fixtures/`** — gigabytes of cached vendor source
  inputs (CMSIS-SVD, ATDF, ESP32 SVDs, Nordic DTS, NXP IOMUXC,
  STM32 Open Pin XML).  Only useful for the parsers that no
  longer live here.

- **`bootstrap.py:DEVICE_REGISTRY` + `SOURCE_BUNDLES`** —
  hand-curated tuples that duplicate what
  `discovered_device_registry()` already derives from
  `data/devices/`.

- **Tests** — `test_normalize.py` (654 LOC), `test_espressif.py`
  (875 LOC), `test_microchip_dfp.py` (150 LOC),
  `test_zephyr_dts.py` (248 LOC), `test_modm_*` (~600 LOC),
  `test_patches.py` (67 LOC), and a long tail that exercise raw
  parsing.  ~2,500 LOC total.

Estimated cleanup: **~9,200 LOC + ~26 MB raw data + ~400 KB
patches** — roughly 17% of `src/`.

## What Changes

This is a **destructive cleanup**, executed in five
back-compat-preserving phases.  Each phase is independently
verifiable: the gate is "every admitted device's emit output
must remain byte-identical".

### Phase 1: Make the YAML path mandatory

- Flip `stages/normalize.py` from "YAML when available, adapter
  fallback otherwise" to "YAML required; raise
  `StageExecutionError` if missing".
- Remove the post-YAML re-application of device patches (the
  YAML already has tier 2/3/4 / mode flags / DMA bindings
  baked in).
- Goldens stay byte-identical — every admitted family already
  has YAML, the adapter path is never hit today.

### Phase 2: Delete the vendor parsers + adapters

- `rm -rf src/alloy_codegen/sources/` except
  `alloy_devices_yml.py` (the consumer) and
  `__init__.py`.
- `rm -rf src/alloy_codegen/vendors/_register_*.py` and the
  `vendor_adapter` registry plumbing in `vendors/__init__.py`.
- `resolve_vendor_adapter` becomes a one-liner that always
  raises (the YAML path is mandatory after Phase 1).
- Remove every `_build_*_device_ir` function in
  `stages/normalize.py` (~3,000 of its 3,794 LOC).

### Phase 3: Delete the patch system

- `rm -rf patches/`.
- Remove `stages/patch.py`, `load_device_patch`, the patch
  manifest, and every adc/uart/spi/i2c/gpio "tier extension"
  helper that re-applies patches in `normalize.py`.
- The pipeline becomes `fetch → normalize → validate → emit →
  publish` (`patch` stage gone).

### Phase 4: Delete the stale tests + fixtures

- Test files: `test_normalize.py`, `test_espressif.py`,
  `test_microchip_dfp.py`, `test_zephyr_dts.py`,
  `test_zephyr_dts_vendor_coverage.py`,
  `test_modm_devices_enrichment.py`,
  `test_modm_clock_tree_edges.py`, `test_patches.py`,
  `test_fetch.py` (replaced by `test_alloy_devices_yml_consumer`),
  `test_known_devices_catalog.py` (replaced by
  `discovered_device_registry()` walks).
- Fixtures: `tests/fixtures/cmsis-svd-data/`,
  `tests/fixtures/espressif-svd/`,
  `tests/fixtures/microchip-dfp-*/`,
  `tests/fixtures/nxp-mcux-imxrt1060/`,
  `tests/fixtures/zephyr-dts/`,
  `tests/fixtures/esp-idf-gpio-sig-map/`,
  `tests/fixtures/stm32-open-pin-data/`,
  `tests/fixtures/modm-devices/`.
- `tests/fixtures/emitted/` (golden outputs) **stays** — that's
  the regression net for the C++ emitter.

### Phase 5: Simplify bootstrap + CLI

- Collapse `DEVICE_REGISTRY` + `SOURCE_BUNDLES` +
  `merged_device_registry()` into a single
  `device_registry()` that walks `data/devices/`.
- CLI `targets` reads from the walker.
- `cli.py` subcommands `fetch` / `patch` are removed; only
  `normalize` / `validate` / `emit` / `publish` / `pipeline` /
  `bulk-admit` survive.
- Pipeline cli wiring updated to skip the deleted stages.

## Impact

The repo becomes the C++ generator it was always meant to be:
canonical YAML in, C++ out.  Roughly **9,200 LOC + 26 MB +
400 KB** disappear without a single change to the emitted
artifacts.

Future work compounds:
- Adding a new device family is "commit a YAML in
  alloy-devices-yml" — no code edits here.
- Onboarding a new contributor reads ~30k LOC of clean emitter
  + IR code instead of fighting with 11 vendor-source parsers.
- CI on this repo runs faster (no SVD/DTS parsing in the
  test suite hot path).

## What this DOES NOT do

- Does not move parsers anywhere — they already live in
  `alloy-data-extractor`.  This change just deletes the local
  copies.
- Does not change the canonical IR shape, the emitted C++ ABI,
  or any goldens.  Phase boundaries are gated on byte-identical
  emit output.
- Does not touch the alloy-devices-yml schema or contents.
- Does not migrate `add-new-vendor-families` (the in-flight
  proposal that adds H7/L4/U5/RP2350/etc).  That one becomes
  data-only ("commit YAMLs to alloy-devices-yml") after this
  change lands.
