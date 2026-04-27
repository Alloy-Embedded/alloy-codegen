# Tasks — add-alloy-data-extractor-repo

## Phase 1: New repo bootstrap

- [ ] 1.1 Create `alloy-data-extractor` GitHub repo.
- [ ] 1.2 Bootstrap with `pyproject.toml`, `README.md`,
      `LICENSE` (MIT), `.github/workflows/ci.yml`.
- [ ] 1.3 Define the package layout under
      `src/alloy_data_extractor/{extractors,normalize,emit}`.

## Phase 2: Move existing adapters

- [ ] 2.1 Migrate `alloy_codegen.sources.cmsis_svd` →
      `alloy_data_extractor.extractors.cmsis_svd`.
- [ ] 2.2 Migrate `alloy_codegen.sources.microchip_dfp` →
      `alloy_data_extractor.extractors.atdf` (rename — ATDF is
      the canonical artifact, DFP is just the pack format).
- [ ] 2.3 Migrate `alloy_codegen.sources.nxp_mcux` →
      `alloy_data_extractor.extractors.mcuxpresso`.
- [ ] 2.4 Migrate `alloy_codegen.sources.esp_idf` →
      `alloy_data_extractor.extractors.esp_idf`.
- [ ] 2.5 Migrate `alloy_codegen.sources.zephyr_dts` →
      `alloy_data_extractor.extractors.zephyr_dts`.
- [ ] 2.6 Migrate `alloy_codegen.sources.stm32_open_pin_data` →
      `alloy_data_extractor.extractors.stm32_open_pin_data`.
- [ ] 2.7 Migrate `alloy_codegen.sources.modm_devices` →
      `alloy_data_extractor.extractors.modm_data`.
- [ ] 2.8 Migrate `alloy_codegen.sources.pico_sdk` →
      `alloy_data_extractor.extractors.pico_sdk`.

## Phase 3: Unified normalize + emit

- [ ] 3.1 `alloy_data_extractor.normalize.DeviceModel`
      consolidates the per-vendor `_build_*_device_ir`
      builders that lived in alloy-codegen normalize.py.
- [ ] 3.2 `alloy_data_extractor.emit.canonical_yaml` writes
      one `<vendor>/<family>/devices/<device>.yml` per
      device into the configured output root (defaults to a
      sibling `alloy-devices-yml/` checkout).
- [ ] 3.3 Reuses the schema + serializer from
      `define-canonical-device-yaml-schema` (vendored or
      depended-on as a small shared library).

## Phase 4: CLI

- [ ] 4.1 `alloy-data-extract --vendor st --family stm32g0`
      runs every applicable extractor for the requested scope.
- [ ] 4.2 `--all` walks every (vendor, family) registered.
- [ ] 4.3 `--output-root <path>` writes YAML output; default
      is `../alloy-devices-yml`.
- [ ] 4.4 `--diff` mode prints `git diff --stat` against the
      current alloy-devices-yml HEAD.

## Phase 5: Source pinning + CI

- [ ] 5.1 `data/source_pins.toml` records a pinned SHA / pack
      version per upstream source.
- [ ] 5.2 CI in alloy-data-extractor runs `--all` against the
      pins, validates output, and opens a PR against
      alloy-devices-yml when drift is detected.
- [ ] 5.3 Each PR carries a per-vendor breakdown of changed
      devices.

## Phase 6: alloy-codegen cleanup (this repo)

- [ ] 6.1 Replace `src/alloy_codegen/sources/*.py` with a
      thin shim that proxies to the YAML consumer (already
      shipped by `extract-alloy-devices-data-repo`).
- [ ] 6.2 Delete the legacy `_build_*_device_ir` cascades in
      `stages/normalize.py` once parity is proven (separate
      cleanup change `retire-legacy-source-adapters` —
      tracked but not blocking this change).
- [ ] 6.3 alloy-codegen's `pyproject.toml` drops dependencies
      that the moved extractors used (lxml, devicetree, …).

## Phase 7: Spec + final checks

- [ ] 7.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 7.2 `openspec validate add-alloy-data-extractor-repo
      --strict` passes.
- [ ] 7.3 alloy-codegen `pytest -q` stays green: every
      admitted device emits byte-identical artifacts via the
      YAML consumer path.
- [ ] 7.4 alloy-data-extractor CI: every extractor runs
      against pinned sources, output validates against the
      schema, parity test asserts round-trip equivalence.
