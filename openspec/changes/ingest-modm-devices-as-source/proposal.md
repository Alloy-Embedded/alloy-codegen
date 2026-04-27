# Ingest modm-devices for STM32 Pin/AF/Clock Data

## Why

modm-io's `modm-devices` repository carries already-normalized AF
tables, clock-tree topology, DMA matrices, and signal mappings
for ~3,500 STM32 variants — extracted from CubeMX XML and ST
reference manual PDFs by a mature pipeline (`modm-data`).
BSD-3 / MPL-2.0 licensed.

We currently re-extract a subset of this from CMSIS-SVD +
STM32-open-pin-data, which gives us less than modm has.  Importing
modm's already-normalized output as an *additional* source
(layered behind our existing patch overrides) gives us deeper
STM32 coverage without re-doing the PDF extraction work.

## What Changes

- New adapter `src/alloy_codegen/sources/modm_devices.py` that
  consumes `modm-devices/devices/stm32/<family>/<part>.xml` and
  produces the same intermediate objects as the existing STM32
  source pipeline.
- Adapter registers via the vendor-adapter registry decorator
  (Sprint 1 dependency).
- Initial integration is **enrichment**, not replacement: where
  modm has data the existing pipeline lacks (e.g. clock-tree
  edges, DMA request matrix), modm fills the gap.  Where the
  existing pipeline already has equivalent or better data
  (e.g. per-package pinout from STM32-open-pin-data), it wins.
- A merge precedence policy is documented:
  `cmsis-svd < stm32-open-pin-data < modm-devices < family-patch
  < device-patch` — modm sits between the open sources and the
  hand-curated patches.
- `data/source_pins.toml` records which checkout SHA of
  modm-devices the import was run against; bumping the SHA is a
  reviewable diff.
- A guard test asserts that for every currently-admitted STM32
  device, the modm import produces a structurally compatible IR
  fragment (no field-type mismatches, no missing required keys).

## Impact

STM32 clock-tree and DMA-matrix coverage jumps to modm's level
without us re-doing the PDF extraction.  Future STM32 admissions
inherit modm's coverage automatically — `autogen-device-patches`
+ modm-devices means most new STM32 variants come in with near-zero
manual work.

## What this DOES NOT do

- Does not affect non-STM32 vendors (modm covers some SAM and
  Nordic but Zephyr DTS already covers those better — see
  `ingest-zephyr-dts-as-source`).
- Does not bulk-admit the ~3,500 modm-known STM32 variants in
  this change.  That's a follow-up gated by the autogen flow.
