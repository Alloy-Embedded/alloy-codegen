# Tasks — consume-alloy-devices-yml-as-canonical-input

## Phase 1: YAML becomes mandatory

- [x] 1.1 In `stages/normalize.py`, replace the
      "YAML-or-adapter" branch with "YAML required" — raise
      `StageExecutionError("device YAML missing in
      data/devices/...")` when `is_available` returns false.
- [x] 1.2 Drop the post-YAML re-application of device patches
      (the eight ADC tier helpers, the UART/SPI/I2C tier
      forwarding, etc.) when the device came from YAML.
- [x] 1.3 Run `pytest -q` + golden comparison; confirm every
      emit-side test stays byte-identical.

## Phase 2: Remove vendor parsers + adapters

- [x] 2.1 Delete `src/alloy_codegen/sources/cmsis_svd.py`,
      `esp_idf.py`, `microchip_dfp.py`, `modm_devices.py`,
      `nxp_mcux.py`, `pico_sdk.py`, `raw.py`,
      `stm32_open_pin_data.py`, `zephyr_dts.py`,
      `zephyr_pinctrl.py`.  Keep `alloy_devices_yml.py` and
      `__init__.py`.
- [x] 2.2 Delete every `src/alloy_codegen/vendors/_register_*.py`
      module.  Trim `vendors/__init__.py` to no longer
      side-effect-import them.
- [x] 2.3 Replace `resolve_vendor_adapter` with a stub that
      raises `StageExecutionError("vendor adapters were
      removed; commit YAML to alloy-devices-yml instead")`.
- [x] 2.4 Delete every `_build_*_device_ir` function in
      `stages/normalize.py` and the helper functions that exist
      only to support them (the file shrinks from 3,785 to
      ~70 LOC).
- [x] 2.5 Run `pytest -q` + ruff; expect failures only in the
      tests scheduled for deletion in Phase 4.

## Phase 3: Remove the patch system

- [x] 3.1 Delete `patches/` entirely.
- [x] 3.2 Delete `src/alloy_codegen/patches.py` and
      `stages/patch.py`.
- [x] 3.3 Update `pipeline.py` / `cli.py` so the pipeline
      definition becomes `fetch → normalize → validate → emit
      → publish`.  `cli.py patch` subcommand removed.
- [x] 3.4 Delete every patch-loading import / call site in
      `stages/normalize.py`.
- [x] 3.5 The patch manifest survives as a permanently-empty
      marker on the normalize bundle so downstream stages don't
      need to special-case its absence.

## Phase 4: Delete stale tests + fixtures

- [x] 4.1 Delete test files: `test_normalize.py`,
      `test_espressif.py`, `test_microchip_dfp.py`,
      `test_zephyr_dts.py`,
      `test_zephyr_dts_vendor_coverage.py`,
      `test_modm_devices_enrichment.py`,
      `test_modm_clock_tree_edges.py`, `test_patches.py`,
      `test_fetch.py`, `test_known_devices_catalog.py`,
      `test_zephyr_pinctrl.py`,
      `test_imxrt_gpio_pins.py`,
      `test_autogen_device_patches.py`,
      `test_board_support_package_emitter.py`,
      `test_vendor_adapter_registry.py`,
      `test_affected_families.py`, `test_nxp_mcux.py`.
- [x] 4.2 Delete fixtures: `tests/fixtures/cmsis-svd-data/`,
      `espressif-svd/`, `microchip-dfp-avr-da/`,
      `microchip-dfp-same70/`, `nxp-mcux-imxrt1060/`,
      `zephyr-dts/`, `esp-idf-gpio-sig-map/`,
      `stm32-open-pin-data/`, `modm-devices/`.
- [x] 4.3 Audit any surviving test that imports from
      `alloy_codegen.sources` or `alloy_codegen.vendors._register_`;
      delete or migrate to YAML-consumer style.
- [x] 4.4 Run `pytest -q`; **390 passed, 22 skipped, 0 failed**.

## Phase 5: Bootstrap + CLI tidy-up

- [x] 5.1 Replace `DEVICE_REGISTRY` + `SOURCE_BUNDLES` +
      `merged_device_registry()` with a single
      `device_registry()` that walks `data/devices/vendors/`.
- [x] 5.2 Update every caller in `cli.py`, `bulk_admit.py`,
      `affected_families.py`, `runtime_readme.py`, etc., to use
      `device_registry()`.  Backwards-compat aliases
      `DEVICE_REGISTRY` and `discovered_device_registry()` are
      kept so out-of-tree callers don't break.
- [x] 5.3 Auxiliary cleanup: `runtime_readme.py` reads from the
      canonical YAML directly; `affected_families.py` reduced
      to YAML-path-based scope detection; `validation.py`
      `expected_source_ids` hardcoded to `("alloy-devices-yml",)`.
- [x] 5.4 String-literal violations from the new validity-concept
      emitters (added by `add-additional-validity-concepts`)
      removed so the runtime-strings gate stays green.
- [x] 5.5 Run `pytest -q` + `ruff check src/ tests/` clean.
- [x] 5.6 `scripts/bake_tier_data_into_yaml.py` migrated tier
      2/3/4 patch data into `alloy-devices-yml`;
      `scripts/clean_orphan_yaml_references.py` removed
      residual data inconsistencies (orphan peripheral refs,
      duplicate dma_bindings, non-rooted clock_nodes).

## Phase 6: Spec + final checks

- [x] 6.1 Spec delta in `specs/vendor-admission/spec.md`
      documenting that admission is now YAML-only.
- [x] 6.2 `openspec validate
      consume-alloy-devices-yml-as-canonical-input --strict`
      passes.
- [x] 6.3 README is fine as-is — admission docs already point
      contributors at the alloy-devices-yml data repo (no edits
      needed in this change).
- [x] 6.4 Final `pytest -q` + `ruff check` clean.
