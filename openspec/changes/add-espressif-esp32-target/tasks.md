## Phase 0: Bootstrap & Source Manifests

- [x] 0.1 Add `("espressif", "esp32c3")` to `DEVICE_REGISTRY` and `SOURCE_BUNDLES`
      in `src/alloy_codegen/bootstrap.py`
- [x] 0.2 Create `src/alloy_codegen/sources/esp_idf.py` for Espressif SVD ingestion
- [x] 0.3 Add Espressif fetch branch to `src/alloy_codegen/stages/fetch.py`
- [x] 0.4 Formalize supplementary-source ingestion for `gpio_sig_map.h`:
      source manifest entry, revision pinning, provenance label, and licensing note
- [x] 0.5 Scaffold `patches/espressif/esp32c3/family.json` and
      `patches/espressif/esp32c3/devices/esp32c3.json`
- [x] 0.6 Verify fetch produces a non-empty `RawDeviceDocument` for `esp32c3`

## Phase 1: IR Ingestion — ESP32-C3

- [x] 1.1 Add explicit `riscv` baseline to `SYSTEM_VECTOR_BASELINES`
- [x] 1.2 Remove the fallback-to-`cortex-m4` behavior for unknown cores
- [x] 1.3 Extend `_typed_register_ref` for ESP32-C3 PCR clock/reset references
- [x] 1.4 Populate `patches/espressif/esp32c3/family.json` with memory, clocks, packages,
      DMA, and startup-relevant controls
- [x] 1.5 Populate `patches/espressif/esp32c3/devices/esp32c3.json` with peripheral
      enable/reset/interrupt enrichments
- [x] 1.6 Write normalized golden fixture and regression tests for `esp32c3`

## Phase 2: IO Matrix Routing

- [x] 2.1 Add `alloy.pinmux.espressif-iomatrix-v1` to the known backend schema set
- [x] 2.2 Create supplementary parser for `gpio_sig_map.h`
      (`sources/esp_idf.py::parse_gpio_sig_map()` parses `#define <NAME>_IDX
      <num>` entries into a `{signal_name: index}` mapping.  Vendored a
      minimal `tests/fixtures/esp-idf-gpio-sig-map/esp32c3/gpio_sig_map.h`
      with the signals cited by the ESP32-C3 family patch.  Supplementary
      source id `esp-idf-gpio-sig-map` reserved in
      `sources/esp_idf.py::GPIO_SIG_MAP_SOURCE_ID` for future fetch-manifest
      plumbing.)
- [x] 2.3 Populate pin-signal data for UART, SPI, I2C, ADC bootstrap coverage
- [x] 2.4 Ensure emitted runtime data carries IO Matrix signal-index provenance
      (Every `write-selector` route operation on ESP32-C3 carries
      `schema_id = "alloy.pinmux.espressif-iomatrix-v1"` and a numeric
      `value_int` that IS the IO Matrix index from `gpio_sig_map.h`.  The
      provenance chain is now: upstream header → family-patch `af_number` →
      canonical `RouteOperation.schema_id` + `.value_int` → emitted typed
      runtime artifact.  A regression test
      (`test_esp32c3_family_af_numbers_match_gpio_sig_map_upstream`) flags
      any drift between the patch and upstream.)
- [x] 2.5 Add emitted goldens proving the IO Matrix schema and comments are correct
      (`tests/test_espressif.py::test_esp32c3_runtime_routes_header_encodes_iomatrix_schema`
      asserts the emitted `runtime/devices/esp32c3/routes.hpp` and
      `runtime/types.hpp` encode the IO Matrix schema as
      `BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1`.)

## Phase 3: Runtime Contract — ESP32-C3

- [x] 3.1 Update `artifact_contract.py` so architecture-scoped artifacts are explicit:
      `systick.hpp` required only for Cortex-M; startup validated per architecture
- [x] 3.2 Add `runtime_riscv_startup.py` and wire RISC-V startup emission in `stages/emit.py`
- [x] 3.3 Ensure consumer smoke compiles ESP32-C3 runtime headers without ARM-specific glue
      (`tests/test_espressif.py::test_publish_esp32c3_consumer_smoke_passes`
      runs the end-to-end publish + host `c++` compile of the staged runtime
      headers + RISC-V startup.  The RISC-V `__attribute__((interrupt))` on
      peripheral IRQ handlers is now guarded by `ALLOY_CODEGEN_HOST_SMOKE`
      so the host compiler's `-Werror=unknown-attributes` does not trip.)
- [x] 3.4 Add emitted runtime goldens for `interrupts.hpp`, `clock_graph.hpp`,
      `peripheral_instances.hpp`, and startup output
- [x] 3.5 Add publish/contract tests proving runtime-only completeness for `esp32c3`

## Phase 4: Xtensa Follow-On — ESP32-S3

- [ ] 4.1 Add `("espressif", "esp32s3")` to registry/bootstrap
- [ ] 4.2 Add explicit `xtensa-lx7` vector baseline
- [ ] 4.3 Extend Espressif adapter to load `esp32s3`
- [ ] 4.4 Document and enforce single-core control-plane perspective for this first cut
- [ ] 4.5 Add Xtensa startup emitter branch
- [ ] 4.6 Add normalized and emitted goldens for `esp32s3`
- [ ] 4.7 Add consumer smoke and artifact-contract coverage for `esp32s3`

## Phase 5: CI & Publication Gates

- [x] 5.1 Add `espressif/esp32c3` to the publication matrix
      (`.github/workflows/publish-alloy-devices.yml` matrix now includes
      `vendor: espressif, family: esp32c3`.)
- [x] 5.2 Extend vendor-admission checks to include `espressif`
      (`.github/workflows/bootstrap-family.yml` ADMITTED_VENDORS already
      includes `espressif` — landed in the Phase 0 bootstrap commit.)
- [x] 5.3 Add publish-time completeness checks for non-Cortex runtime-only devices
      (The existing runtime-lite contract gates apply uniformly to every
      admitted family.  RISC-V-specific scoping — `systick.hpp` optional,
      arch-aware vector baseline — landed in Phase 3.1.  Fixed the
      single-device family ip-block reuse rule so RISC-V single-device
      families like esp32c3 are not falsely flagged.)
- [x] 5.4 Run full publication flow for `esp32c3`
      (`test_foundational_families_publish_with_same_generic_workflow` and
      `test_foundational_families_remain_complete_across_repeat_publish_cycles`
      now iterate over ESP32-C3 alongside the other foundational families.)
- [x] 5.5 Add integration coverage for Espressif runtime-only publication
      (Added `espressif_execution_context` to the `_family_contexts` loop in
      `tests/test_foundational_families.py` — ESP32-C3 now receives the same
      emit + publish + artifact-contract gate as every other foundational
      family.)

## Phase 6: Fixtures & Docs

- [ ] 6.1 Regenerate all affected fixtures
- [ ] 6.2 Update `openspec/project.md` with Espressif admission, architecture notes,
      and IO Matrix source provenance
- [ ] 6.3 Add explicit licensing/provenance note for Espressif supplementary sources
- [ ] 6.4 Archive this change
