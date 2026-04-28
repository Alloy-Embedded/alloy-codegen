# Tasks — consume-alloy-devices-yml-as-canonical-input

## Phase 1: YAML becomes mandatory

- [ ] 1.1 In `stages/normalize.py`, replace the
      "YAML-or-adapter" branch with "YAML required" — raise
      `StageExecutionError("device YAML missing in
      data/devices/...")` when `is_available` returns false.
- [ ] 1.2 Drop the post-YAML re-application of device patches
      (the eight ADC tier helpers, the UART/SPI/I2C tier
      forwarding, etc.) when the device came from YAML.
- [ ] 1.3 Run `pytest -q` + golden comparison; confirm every
      emit-side test stays byte-identical.

## Phase 2: Remove vendor parsers + adapters

- [ ] 2.1 Delete `src/alloy_codegen/sources/cmsis_svd.py`,
      `esp_idf.py`, `microchip_dfp.py`, `modm_devices.py`,
      `nxp_mcux.py`, `pico_sdk.py`, `raw.py`,
      `stm32_open_pin_data.py`, `zephyr_dts.py`,
      `zephyr_pinctrl.py`.  Keep `alloy_devices_yml.py` and
      `__init__.py`.
- [ ] 2.2 Delete every `src/alloy_codegen/vendors/_register_*.py`
      module.  Trim `vendors/__init__.py` to no longer
      side-effect-import them.
- [ ] 2.3 Replace `resolve_vendor_adapter` with a stub that
      raises `StageExecutionError("vendor adapters were
      removed; commit YAML to alloy-devices-yml instead")`.
- [ ] 2.4 Delete every `_build_*_device_ir` function in
      `stages/normalize.py` and the helper functions that exist
      only to support them (the file shrinks from 3,794 to
      ~600 LOC).
- [ ] 2.5 Run `pytest -q` + ruff; expect failures only in the
      tests scheduled for deletion in Phase 4.

## Phase 3: Remove the patch system

- [ ] 3.1 Delete `patches/` entirely.
- [ ] 3.2 Delete `src/alloy_codegen/patches.py` and
      `stages/patch.py`.
- [ ] 3.3 Update `pipeline.py` / `cli.py` so the pipeline
      definition becomes `fetch → normalize → validate → emit
      → publish`.  `cli.py patch` subcommand removed.
- [ ] 3.4 Delete every patch-loading import / call site in
      `stages/normalize.py`.
- [ ] 3.5 Update the source-manifest schema to drop
      `patch_manifest`.

## Phase 4: Delete stale tests + fixtures

- [ ] 4.1 Delete test files: `test_normalize.py`,
      `test_espressif.py`, `test_microchip_dfp.py`,
      `test_zephyr_dts.py`,
      `test_zephyr_dts_vendor_coverage.py`,
      `test_modm_devices_enrichment.py`,
      `test_modm_clock_tree_edges.py`, `test_patches.py`,
      `test_fetch.py`, `test_known_devices_catalog.py`,
      `test_zephyr_pinctrl.py`,
      `test_imxrt_iomux_gpio.py` (and any other test that
      imports from `alloy_codegen.sources.*`).
- [ ] 4.2 Delete fixtures: `tests/fixtures/cmsis-svd-data/`,
      `espressif-svd/`, `microchip-dfp-avr-da/`,
      `microchip-dfp-same70/`, `nxp-mcux-imxrt1060/`,
      `zephyr-dts/`, `esp-idf-gpio-sig-map/`,
      `stm32-open-pin-data/`, `modm-devices/`.
- [ ] 4.3 Audit any surviving test that imports from
      `alloy_codegen.sources` or `alloy_codegen.vendors._register_`;
      delete or migrate to YAML-consumer style.
- [ ] 4.4 Run `pytest -q`; expect green.

## Phase 5: Bootstrap + CLI tidy-up

- [ ] 5.1 Replace `DEVICE_REGISTRY` + `SOURCE_BUNDLES` +
      `merged_device_registry()` with a single
      `device_registry()` that walks `data/devices/vendors/`.
- [ ] 5.2 Update every caller in `cli.py`, `bulk_admit.py`,
      `affected_families.py`, `runtime_readme.py`, etc., to use
      `device_registry()`.
- [ ] 5.3 Delete `data/known_devices.toml` +
      `data/known_devices.meta.toml` (now redundant).
- [ ] 5.4 Trim `cli.py`: remove `fetch` / `patch` subcommands;
      keep `targets` / `normalize` / `validate` / `emit` /
      `publish` / `pipeline` / `bulk-admit` /
      `config-*` / `affected` / `explain` / `diff`.
- [ ] 5.5 Run `pytest -q` + `ruff check src/ tests/` clean.
- [ ] 5.6 Run `bulk-admit` dry-run across all 9 admitted
      families; confirm every device produces a schema-valid
      IR and identical emit output vs. the pre-cleanup
      baseline.

## Phase 6: Spec + final checks

- [ ] 6.1 Spec delta in `specs/vendor-admission/spec.md`
      documenting that admission is now YAML-only.
- [ ] 6.2 `openspec validate
      consume-alloy-devices-yml-as-canonical-input --strict`
      passes.
- [ ] 6.3 Update `README.md` so contributors know admission is
      "commit YAML to alloy-devices-yml; this repo is
      consumer-only".
- [ ] 6.4 Final `pytest -q` + `ruff check` clean.
