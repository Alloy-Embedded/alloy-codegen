# Tasks — add-alloy-data-extractor-repo

## Phase 1: New repo bootstrap

- [x] 1.1 Created `Alloy-Embedded/alloy-data-extractor` GitHub repo.
- [x] 1.2 Bootstrap content: `pyproject.toml` (deps: PyYAML,
      jsonschema, cmsis-pack-manager, devicetree, lxml),
      `README.md`, `LICENSE` (MIT), `.gitignore`,
      `.github/workflows/ci.yml`.
- [x] 1.3 Package layout shipped:
      `src/alloy_data_extractor/{extractors,normalize,emit}/`.

## Phase 2: First extractor (CMSIS-SVD)

- [x] 2.1 `extractors/cmsis_svd.py` — proof-of-life extractor
      that parses an SVD into the canonical-IR shape (identity,
      core via `<cpu>`, peripherals + interrupts).
- [x] 2.2 `emit/canonical_yaml.py` mirrors alloy-codegen's
      `_TOP_LEVEL_KEY_ORDER` + serializer contract — output
      loads cleanly via alloy-codegen's consumer.
- [x] 2.3 `pipeline.py` registers the extractor and orchestrates
      per-device runs, writing into the configured output root.

## Phase 3: CLI

- [x] 3.1 `alloy-data-extract --vendor X --family Y --device Z
      --extractor cmsis-svd --source Z=path.svd --output-root
      <data-repo>`.
- [x] 3.2 Auto-discovers the canonical-device JSON schema from
      `<output-root>/schema/canonical_device/device.schema.json`
      and validates output before writing.
- [x] 3.3 Per-device summary table printed to stdout:
      `<vendor>/<family>/<device>  <bytes>  -> <yaml-path>`.

## Phase 4: Source pinning manifest

- [x] 4.1 `data/source_pins.toml` lists every upstream the
      extractors plan to consume (cmsis-svd-data,
      stm32-open-pin-data, microchip MPLAB X DFP — covers
      ~2000 PIC/AVR/SAM chips, Zephyr, ESP-IDF, NXP MCUXpresso,
      modm-devices, Pico SDK).  Each entry records origin URL,
      revision pin, license note.

## Phase 5: Tests + CI

- [x] 5.1 `tests/test_cmsis_svd_extractor.py` — 6 tests covering
      core resolution, peripheral + interrupt extraction,
      top-level YAML key order, end-to-end pipeline write,
      registry discovery, unknown-extractor failure.  All
      pass.
- [x] 5.2 CI workflow (`ruff` + `pytest` + `ruff format
      --check`).
- [x] 5.3 CLI smoke against alloy-codegen's STM32G0 SVD fixture
      produces a schema-shaped YAML — proof the contract holds
      end-to-end.

## Phase 6: Other extractors — incremental migration

- [ ] 6.1 ATDF extractor (Microchip AVR + SAM + **PIC** —
      ~2000 chip moat).  **Deferred** to a per-vendor
      migration change (the existing alloy-codegen
      `microchip_dfp.py` is non-trivial and worth its own PR).
- [ ] 6.2 MCUXpresso extractor.  Deferred.
- [ ] 6.3 Zephyr DTS extractor.  Deferred.
- [ ] 6.4 ESP-IDF, modm-data, Pico SDK.  Deferred.

The legacy adapters remain in alloy-codegen during the
transition; the `extract-alloy-devices-data-repo` short-circuit
keeps the codegen working off the data repo regardless of which
side produced the YAMLs.

## Phase 7: alloy-codegen cleanup

- [ ] 7.1 Replace `src/alloy_codegen/sources/*.py` with shim
      modules — **deferred** until enough extractors have
      migrated that parity is provably complete.  Tracked in
      a follow-up `retire-legacy-source-adapters` change.
- [ ] 7.2 Drop dependencies the moved extractors used (lxml,
      cmsis-pack-manager) once the cleanup change lands.

## Phase 8: Spec + final checks

- [x] 8.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 8.2 `openspec validate add-alloy-data-extractor-repo
      --strict` passes.
- [x] 8.3 alloy-data-extractor pytest + ruff clean (its own
      CI runs on push).
