# Tasks — add-espressif-esp32-classic-target

## Phase 0: Bootstrap & Source Manifest

- [x] 0.1 Add `("espressif", "esp32")` to `DEVICE_REGISTRY` in `src/alloy_codegen/bootstrap.py`,
      registering `esp32` (QFN48) and `esp32-wroom32` (module) as the two admitted devices
- [x] 0.2 Add `("espressif", "esp32")` to `SOURCE_BUNDLES`, reusing the existing
      `espressif-svd` bundle (no new source adapter needed)
- [x] 0.3 Verify `espressif-svd` resolves `esp32.svd` for the family via existing
      `resolve_esp_svd_path`; confirm with a fetch dry-run
- [x] 0.4 Add a SOURCE_BUNDLES test case asserting the bundle composition is
      `(espressif-svd,)` for `("espressif", "esp32")` (mirror the esp32c3/esp32s3 test)

## Phase 1: Xtensa dual-core runtime contract

- [x] 1.1 Add `core_affinity: Literal["cpu0", "cpu1", "shared"] = "cpu0"` to
      `VectorSlotDescriptor` in `src/alloy_codegen/connector_model.py`
- [x] 1.2 Update the `vector_slots` builder in `connector_model.py` to derive
      `core_affinity` from the owning peripheral name: vectors whose interrupt's
      peripheral is `INTERRUPT_CORE1` (S3) or `DPORT_APP_INTR_*` (classic) get
      `"cpu1"`; all others default to `"cpu0"`
- [x] 1.3 Remove the `INTERRUPT_CORE1` filtering shim in `_build_esp32_device_ir`
      in `src/alloy_codegen/stages/normalize.py` (the comment block already documents
      that filtering — replace with the new dual-core posture)
- [x] 1.4 Rewrite `src/alloy_codegen/runtime_xtensa_startup.py` to emit:
        - `_vectors_cpu0[]` and `_vectors_cpu1[]` partitioned by `core_affinity`
        - `Reset_Handler` (PRO_CPU: BSS/data init + ctors + `main()`)
        - `Reset_Handler_CPU1` (APP_CPU: skip static init, call optional
          `app_main_cpu1()` weak symbol, then default-handler loop)
        - `bring_up_app_cpu()` function that touches the per-device CPU-1 control
          registers; the body is parameterised on whether the device's IR carries
          `DPORT.APPCPU_CTRL_B` (classic) or `SYSTEM.CORE_1_CONTROL_*` (S3)
        - Updated module docstring removing the single-core-perspective claim
- [x] 1.5 Remove the "Single-core-perspective: core 1 is not started" comment block
      from `src/alloy_codegen/emission.py` for Xtensa (line 4387 today); replace with
      a comment that points at `bring_up_app_cpu()`
- [x] 1.6 Update `patches/espressif/esp32s3/family.json` to admit `INTERRUPT_CORE1`
      in the peripheral allowlist (currently filtered)
- [x] 1.7 Add manual `register_fields` to `patches/espressif/esp32s3/devices/esp32s3.json`
      for `SYSTEM.CORE_1_CONTROL_0.CONTROL_CORE_1_CLKGATE_EN` and
      `SYSTEM.CORE_1_CONTROL_1.CONTROL_CORE_1_RUNSTALL`, used by
      `bring_up_app_cpu()`
- [x] 1.8 Regenerate the ESP32-S3 emitted goldens under
      `tests/fixtures/emitted/espressif/esp32s3/` to include the new
      dual-core artefacts; pin the diff explicitly in the test
- [x] 1.9 Add `tests/test_espressif.py::test_esp32s3_emits_dual_core_startup`
      asserting both vector tables, both Reset_Handlers, and `bring_up_app_cpu()`
      are present in the emitted `startup.cpp`

## Phase 2: ESP32 clássico — Family Catalog

- [x] 2.1 Scaffold `patches/espressif/esp32/family.json` with `family_patch_id` =
      `espressif-esp32-family-bootstrap-v1`
- [x] 2.2 Declare the peripheral allowlist (UART0/1/2, SPI2/3, I2C0/1, TIMG0/1, GPIO,
      LEDC, RMT, ADC1, DPORT) with canonical `peripheral_class` mappings
- [x] 2.3 Populate the pin catalog GPIO0–GPIO39 (40 entries); flag GPIO34–39 as
      input-only per Espressif TRM §4.10
- [x] 2.4 Add the system clock profiles: `XTAL_40MHZ`, `PLL_240MHZ`, `RTC_8M5`
- [x] 2.5 Leave `pin_signals` empty in this phase (IO Matrix ingestion is a follow-on,
      same posture as ESP32-S3 took initially)

## Phase 3: ESP32 clássico — Device Patches

- [x] 3.1 Create `patches/espressif/esp32/devices/esp32.json` for the bare QFN48 chip:
        `core: "xtensa-lx6"`, `package: "qfn48"`, `revision: "v3"`,
        memories DRAM (0x3FFAE000, 320KiB), IRAM (0x40080000, 128KiB),
        RTC_FAST (0x3FF80000, 8KiB), RTC_SLOW (0x50000000, 8KiB)
- [x] 3.2 Add manual register declarations under `registers` for
        `DPORT.PERIP_CLK_EN` (offset 0x0C0, base 0x3FF00000),
        `DPORT.PERIP_RST_EN` (offset 0x0C4), and
        `DPORT.APPCPU_CTRL_B` (offset 0x030)
- [x] 3.3 Add `register_fields` under DPORT.PERIP_CLK_EN for every admitted peripheral's
        clock-enable bit per TRM §5.5 (UART_CLK_EN bit 2, UART1_CLK_EN bit 5,
        ..., GPIO_CLK_EN bit 7, SPI2_CLK_EN bit 6, etc.)
- [x] 3.4 Add corresponding `register_fields` under DPORT.PERIP_RST_EN per TRM §5.4
- [x] 3.5 Add `register_fields` under DPORT.APPCPU_CTRL_B for the single bit that
        unholds APP_CPU (bit 0); used by `bring_up_app_cpu()` emitter
- [x] 3.6 Wire `peripheral_clock_bindings` so each peripheral resolves its enable +
        reset signal via the manual DPORT register fields
- [x] 3.7 Add `interrupts` patch entries for system-level vectors that the SVD does not
        attribute to a peripheral (NMI, abort) — same approach as ESP32-S3
- [x] 3.8 Create `patches/espressif/esp32/devices/esp32-wroom32.json`: `family_patch_id`
        identical, `package: "wroom-32"`, with `package_pads` flagging GPIO6–GPIO11 as
        `bonding_state: "reserved-flash"` so they're carried but not exposed as IO

## Phase 4: Validation Green

- [x] 4.1 Run `uv run python -m alloy_codegen.cli validate --vendor espressif
        --family esp32 --json` for both devices and confirm `status=completed`,
        `draft_system_descriptor_domains=[]` (or document any draft domain explicitly,
        same posture as AVR-DA when DMA model is incomplete)
- [x] 4.2 Re-run `uv run python -m alloy_codegen.cli validate --vendor espressif
        --family esp32s3 --json` — must remain green after the dual-core retrofit
- [x] 4.3 Add `tests/test_espressif.py::test_esp32_classic_normalize_admits_both_cores`
        asserting both `INTERRUPT_CORE0` and `INTERRUPT_CORE1`-equivalent vectors are
        in the canonical IR
- [x] 4.4 Add `tests/test_espressif.py::test_esp32_classic_validate_no_draft_domains`
        to pin the publishability state
- [x] 4.5 Add a regression test asserting both QFN48 and WROOM-32 device variants
        produce IRs that differ only in `package_pads`

## Phase 5: Consumer Smoke + Publish Gate

- [x] 5.1 Add `esp32` and `esp32-wroom32` cases to `tests/test_foundational_families.py`
        so `test_foundational_families_publish_with_same_generic_workflow` covers them
- [x] 5.2 Confirm `esp32s3` consumer smoke still passes under the dual-core emitter
        (the test is parameterised by family; nothing extra to add)
- [x] 5.3 Run `uv run python -m alloy_codegen.cli publish --vendor espressif
        --family esp32 --artifact-root <tmp> --publication-root <tmp> --alloy-root <alloy>`
        locally and verify `consumer_verification.succeeded == True`
- [x] 5.4 Add `{vendor: espressif, family: esp32}` to the matrix in
        `.github/workflows/publish-alloy-devices.yml`
- [x] 5.5 Add the bootstrap-family job entries for `esp32` and `esp32-wroom32` in
        `.github/workflows/bootstrap-family.yml` (same shape as `esp32s3`)
- [x] 5.6 Push a commit triggering Bootstrap CI; confirm green for the new family AND
        for the retrofitted esp32s3; confirm the chained Publish workflow lands
        `espressif/esp32/` in `alloy-devices/` without erasing `esp32c3/` or `esp32s3/`
        (the publication.py fix from `0153d33` already handles this)

## Phase 6: Goldens & Docs

- [x] 6.1 Pin canonical emitted artifacts under
        `tests/fixtures/emitted/espressif/esp32/` for the new family and add a
        goldens-match regression following the ESP32-S3 pattern
- [x] 6.2 Refresh `tests/fixtures/emitted/espressif/esp32s3/` with the new dual-core
        startup (already done in 1.8 but re-pinned end-to-end here)
- [x] 6.3 Update `README.md` (or the device matrix doc) to list `espressif/esp32`
        under admitted families and amend the ESP32-S3 row to note dual-core
- [x] 6.4 Update the foundational vendor table in vendor-admission spec (handled via
        the spec delta below)
- [x] 6.5 Run `openspec validate add-espressif-esp32-classic-target --strict` and
        resolve any issues
