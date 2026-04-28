# Add `alloy-data-extractor` ETL Repo

## Why

Once `extract-alloy-devices-data-repo` lands, the data lives in a
separate repo but the **extraction logic** (parsing SVDs, ATDFs,
DTSs, MCUXpresso headers, datasheet PDFs) still lives inside
alloy-codegen as `src/alloy_codegen/sources/*.py`.  That's
backwards: the C++ generator shouldn't need to understand how to
parse PIC ATDF packs.

This change spins out a third repo, `alloy-data-extractor`, whose
sole job is "given vendor sources, write canonical YAMLs to
alloy-devices-yml".  Multi-source, multi-vendor, multi-architecture
ETL — the data side of the pipeline.

The architectural picture after this lands:

```
                     pull
[vendor packs] ───────────────► alloy-data-extractor (Python)
                                      │
                                      │ writes YAML
                                      ▼
                              alloy-devices-yml (data only)
                                      │
                  reads YAML  ────────┼────────  reads YAML
                              │       │       │
                              ▼       ▼       ▼
                    alloy-codegen   alloy-codegen-rust   alloy-codegen-docs
                      (C++)           (Rust PACs)           (Markdown)
```

## What Changes

- New repository `alloy-data-extractor` (separate from
  alloy-codegen + alloy-devices-yml) hosting:
  - `src/alloy_data_extractor/extractors/` — one module per
    vendor source:
    - `cmsis_svd.py` (ARM Cortex-M, ~5,000 chips via
      cmsis-svd-data + cmsis-pack-manager)
    - `atdf.py` (Microchip AVR + SAM + **PIC8/16/18/24/32 +
      dsPIC** via MPLAB X DFP packs — ~2,000 chips, the "no
      OSS framework covers PIC" gap)
    - `mcuxpresso.py` (NXP iMXRT/Kinetis/LPC/MCX, ~400 chips)
    - `esp_idf.py` (Espressif, ~15)
    - `zephyr_dts.py` (cross-vendor: Renesas/TI/Infineon/Ambiq/
      SiLabs/Nordic, ~1,000 chips)
    - `stm32_cubemx.py` (full STM32 Cube DB: pinmux + clock
      tree extraction)
    - `modm_data.py` (modm's PDF-extracted STM32 reference-
      manual data — augments where Cube is incomplete)
    - `pico_sdk.py` (RP2040/RP2350)
    - `silabs_studio.py` (EFR/EFM)
    - `ti_sysconfig.py` (MSP430 + Sitara + SimpleLink)
    - `datasheet_pdf.py` (last-resort PDF scrape, modm-data
      style)
  - `src/alloy_data_extractor/normalize/` — unified
    DeviceModel normalizer that consumes any extractor's
    output.
  - `src/alloy_data_extractor/emit/` — writes canonical YAML
    files into the alloy-devices-yml repo via a configurable
    output root.
  - CLI `alloy-data-extract --vendor <v> --family <f>` (and
    `--all` for the full sweep).
- The current `src/alloy_codegen/sources/*.py` adapters get
  **moved** into the new repo at the equivalent paths.
  alloy-codegen replaces them with a thin shim that calls the
  YAML consumer (already shipped by
  `extract-alloy-devices-data-repo`).
- A pinned cmsis-svd-data + cmsis-pack-manager + Microchip
  MPLAB X DFP set + Zephyr checkout SHA per extractor
  recorded in `data/source_pins.toml` (the same pinning model
  that already exists for modm-devices).
- CI in alloy-data-extractor:
  - Runs every extractor against pinned sources.
  - Round-trips through schema validation + IR equality.
  - Opens a PR against alloy-devices-yml when extractor
    output drifts (via `peter-evans/create-pull-request`).
- Documentation: `docs/data-extraction.md` covers how to add
  a new vendor extractor (cookbook with file paths +
  references to existing extractors).

## Impact

After this lands the architecture splits cleanly:

- **alloy-data-extractor** owns "where the data comes from".
  Adding a vendor = one PR with a new extractor.
- **alloy-devices-yml** owns "what the data looks like".
  Adding a chip = one YAML committed by the extractor (or by
  hand for one-offs).
- **alloy-codegen** owns "what we generate from the data".
  Doesn't care where the YAML came from — could even be
  hand-authored.

This is the same model that powered modm + Embassy to scale
to ~3500 chips each.  We extend it to cover PIC + MSP430 +
8051 — categories no OSS HAL framework currently has.

## What this DOES NOT do

- Does not bulk-extract 8000 MCUs in one go.  This change
  ships the framework + the existing extractors.  Bulk
  extraction is `bulk-admit-from-alloy-devices-yml`.
- Does not retire the legacy adapters in alloy-codegen
  immediately.  After the move, alloy-codegen keeps the YAML
  consumer; the legacy SVD+patch path is deleted in a
  follow-up cleanup change once parity is proven.
- Does not standardise IP-version naming across vendors.
  Each extractor preserves vendor-canonical names (e.g. NXP
  `lpuart-v1` stays `lpuart-v1`); cross-vendor equivalences
  remain a peripheral-trait-template-library concern.
