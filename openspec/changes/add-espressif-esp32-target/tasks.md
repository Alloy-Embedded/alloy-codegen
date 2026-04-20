## Phase 0: Bootstrap & Source Manifests

- [ ] 0.1 Add `("espressif", "esp32c3")` to `DEVICE_REGISTRY` and `SOURCE_BUNDLES`
      in `src/alloy_codegen/bootstrap.py`
- [ ] 0.2 Create `src/alloy_codegen/sources/esp_idf.py` for Espressif SVD ingestion
- [ ] 0.3 Add Espressif fetch branch to `src/alloy_codegen/stages/fetch.py`
- [ ] 0.4 Formalize supplementary-source ingestion for `gpio_sig_map.h`:
      source manifest entry, revision pinning, provenance label, and licensing note
- [ ] 0.5 Scaffold `patches/espressif/esp32c3/family.json` and
      `patches/espressif/esp32c3/devices/esp32c3.json`
- [ ] 0.6 Verify fetch produces a non-empty `RawDeviceDocument` for `esp32c3`

## Phase 1: IR Ingestion — ESP32-C3

- [ ] 1.1 Add explicit `riscv` baseline to `SYSTEM_VECTOR_BASELINES`
- [ ] 1.2 Remove the fallback-to-`cortex-m4` behavior for unknown cores
- [ ] 1.3 Extend `_typed_register_ref` for ESP32-C3 PCR clock/reset references
- [ ] 1.4 Populate `patches/espressif/esp32c3/family.json` with memory, clocks, packages,
      DMA, and startup-relevant controls
- [ ] 1.5 Populate `patches/espressif/esp32c3/devices/esp32c3.json` with peripheral
      enable/reset/interrupt enrichments
- [ ] 1.6 Write normalized golden fixture and regression tests for `esp32c3`

## Phase 2: IO Matrix Routing

- [ ] 2.1 Add `alloy.pinmux.espressif-iomatrix-v1` to the known backend schema set
- [ ] 2.2 Create supplementary parser for `gpio_sig_map.h`
- [ ] 2.3 Populate pin-signal data for UART, SPI, I2C, ADC bootstrap coverage
- [ ] 2.4 Ensure emitted runtime data carries IO Matrix signal-index provenance
- [ ] 2.5 Add emitted goldens proving the IO Matrix schema and comments are correct

## Phase 3: Runtime Contract — ESP32-C3

- [ ] 3.1 Update `artifact_contract.py` so architecture-scoped artifacts are explicit:
      `systick.hpp` required only for Cortex-M; startup validated per architecture
- [ ] 3.2 Add `runtime_riscv_startup.py` and wire RISC-V startup emission in `stages/emit.py`
- [ ] 3.3 Ensure consumer smoke compiles ESP32-C3 runtime headers without ARM-specific glue
- [ ] 3.4 Add emitted runtime goldens for `interrupts.hpp`, `clock_graph.hpp`,
      `peripheral_instances.hpp`, and startup output
- [ ] 3.5 Add publish/contract tests proving runtime-only completeness for `esp32c3`

## Phase 4: Xtensa Follow-On — ESP32-S3

- [ ] 4.1 Add `("espressif", "esp32s3")` to registry/bootstrap
- [ ] 4.2 Add explicit `xtensa-lx7` vector baseline
- [ ] 4.3 Extend Espressif adapter to load `esp32s3`
- [ ] 4.4 Document and enforce single-core control-plane perspective for this first cut
- [ ] 4.5 Add Xtensa startup emitter branch
- [ ] 4.6 Add normalized and emitted goldens for `esp32s3`
- [ ] 4.7 Add consumer smoke and artifact-contract coverage for `esp32s3`

## Phase 5: CI & Publication Gates

- [ ] 5.1 Add `espressif/esp32c3` to the publication matrix
- [ ] 5.2 Extend vendor-admission checks to include `espressif`
- [ ] 5.3 Add publish-time completeness checks for non-Cortex runtime-only devices
- [ ] 5.4 Run full publication flow for `esp32c3`
- [ ] 5.5 Add integration coverage for Espressif runtime-only publication

## Phase 6: Fixtures & Docs

- [ ] 6.1 Regenerate all affected fixtures
- [ ] 6.2 Update `openspec/project.md` with Espressif admission, architecture notes,
      and IO Matrix source provenance
- [ ] 6.3 Add explicit licensing/provenance note for Espressif supplementary sources
- [ ] 6.4 Archive this change
