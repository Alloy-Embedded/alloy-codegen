## Phase 0: Bootstrap & Source Manifests

- [ ] 0.1 Add `("raspberrypi", "rp2040")` to `DEVICE_REGISTRY` and `SOURCE_BUNDLES`
      in `src/alloy_codegen/bootstrap.py` with source bundle `("pico-sdk",)`
- [ ] 0.2 Create `src/alloy_codegen/sources/pico_sdk.py` — source adapter that fetches
      `src/rp2040/hardware_regs/rp2040.svd` from `github.com/raspberrypi/pico-sdk`
- [ ] 0.3 Add Raspberry Pi fetch branch to `src/alloy_codegen/stages/fetch.py`
- [ ] 0.4 Add `pico-sdk` entry to the source manifest with revision pinning, provenance
      label `pico-sdk`, and BSD-3-Clause licensing note
- [ ] 0.5 Scaffold `patches/raspberrypi/rp2040/family.json` with packages (`qfn56`),
      pins (GP0–GP29), memories (SRAM 264KB + xip-flash window), clock nodes,
      and peripheral RCC-equivalent signals (RESETS register)
- [ ] 0.6 Scaffold `patches/raspberrypi/rp2040/devices/rp2040.json` with
      `core = "cortex-m0plus-dual"`, `svd_file`, memory regions, system clock profiles
      (safe-rosc-6mhz, default-pll-125mhz), and peripheral list
- [ ] 0.7 Add minimal stub SVD to `tests/fixtures/cmsis-svd-data/Raspberry Pi/rp2040.svd`
      covering RESETS, CLOCKS, IO_BANK0, and SIO
- [ ] 0.8 Verify fetch produces a non-empty `RawDeviceDocument` for `rp2040`

## Phase 1: IR Ingestion — RP2040

- [ ] 1.1 Add `alloy.pinmux.rp2040-funcsel-v1` to the known backend schema set in
      `connector_model.py`; document that `af_number` carries the FUNCSEL index (0–9)
- [ ] 1.2 Populate `patches/raspberrypi/rp2040/family.json` with full pin-signal data:
      UART0/1, SPI0/1, I2C0/1, PWM slices 0–7, ADC, USB, PIO0/PIO1 function indices
- [ ] 1.3 Populate clock nodes for ROSC, XOSC, PLL_SYS, PLL_USB, CLK_REF, CLK_SYS,
      CLK_PERI, CLK_USB, CLK_ADC in `family.json`; add fractional divider metadata
- [ ] 1.4 Add `kind = "xip-flash"` to `MemoryRegion` in `src/alloy_codegen/ir/model.py`
      and update the memory normalization path to recognize it from patches
- [ ] 1.5 Populate `patches/raspberrypi/rp2040/devices/rp2040.json` with clock enable/reset
      signals (RESETS.RESET_* bits), interrupt table, and DMA request lines
- [ ] 1.6 Add `core = "cortex-m0plus-dual"` to the known core set in normalizer;
      document single-core-perspective behavior explicitly in a generated comment
- [ ] 1.7 Write normalized golden fixture `tests/fixtures/rp2040/rp2040.canonical.json`
      and regression test in `tests/test_normalize.py`

## Phase 2: XIP Startup & Linker Script

- [ ] 2.1 Update `runtime_linker_script.py` to emit `BOOT2 (rx)` and `XIP_MAIN (rx)`
      sections when a `xip-flash` memory region is present
- [ ] 2.2 Emit `__boot2_start`, `__boot2_end`, and `__boot2_size` symbols in the linker
      script; emit `__xip_text_start` / `__xip_text_end` for the main flash text region
- [ ] 2.3 Update `startup.cpp` emitter (`stages/emit.py`) to include:
      - `.boot2` section placeholder (weak symbol, 256 bytes)
      - `xip_init()` call before the `.data` copy loop
      - Explicit single-core comment noting core 1 is not started in this first cut
- [ ] 2.4 Add linker script golden fixture `tests/fixtures/emitted/rp2040/.../device.ld`
      and startup golden fixture for `rp2040`
- [ ] 2.5 Update `artifact_contract.py` to accept `xip-flash` as a valid memory kind
      and verify `device.ld` contains at least one `xip-flash` region for RP2040

## Phase 3: Runtime Contract — RP2040

- [ ] 3.1 Emit full standard runtime header set for `rp2040` under
      `generated/runtime/devices/rp2040/`: peripheral_instances, pins, registers,
      register_fields, clock_bindings, clock_graph, clock_profiles, clock_config,
      system_clock, connectors, capabilities, routes, dma_bindings, systick,
      low_power, resets, enable_domains, interrupt_stubs, system_sequences
- [ ] 3.2 Emit all 17 driver semantics headers including `pio.hpp` as explicit stub
      (all refs = `kInvalidRef`, `kPresent = false`, `kPioSemanticPeripherals` is empty)
- [ ] 3.3 Verify consumer smoke compiles all RP2040 runtime headers without errors
- [ ] 3.4 Add emitted golden fixtures for at minimum:
      `peripheral_instances.hpp`, `clock_graph.hpp`, `connectors.hpp`,
      `capabilities.hpp`, `capabilities.json`, `driver_semantics/pio.hpp`
- [ ] 3.5 Add artifact-contract coverage proving runtime-only completeness for `rp2040`

## Phase 4: PIO Capability Stub

- [ ] 4.1 Ensure `capabilities.json` emits `runtime-support:pio` as a present capability
      with `present: true` and `schema_id: "alloy.pio.rp2040-v1-stub"`
- [ ] 4.2 Ensure `capabilities.hpp` emits a typed `CapabilityId::kPio` entry
- [ ] 4.3 Emit `driver_semantics/pio.hpp` with the standard stub pattern:
      `kPresent = false`, all register/field refs invalid, peripheral array empty
- [ ] 4.4 Add `runtime-support:pio` to the publication-gate capability regression list
      so it is tracked across publication cycles and not silently dropped
- [ ] 4.5 Add smoke test verifying `kPioSemanticPeripherals.size() == 0` compiles
      without errors on RP2040

## Phase 5: CI & Publication Gates

- [ ] 5.1 Add `raspberrypi/rp2040` to the publication matrix in
      `.github/workflows/publish-alloy-devices.yml`
- [ ] 5.2 Extend vendor-admission CI check to recognize `patches/raspberrypi/` as admitted
- [ ] 5.3 Add publish-time completeness check verifying all standard runtime headers are
      present for `rp2040`
- [ ] 5.4 Run full publication flow end-to-end for `rp2040` and confirm
      `publication_mode: published`
- [ ] 5.5 Add integration coverage confirming no capability regression between
      publication cycles for `rp2040`

## Phase 6: Fixtures & Docs

- [ ] 6.1 Regenerate all affected fixtures after all phases are complete
- [ ] 6.2 Update `openspec/project.md` with Raspberry Pi admission note, FUNCSEL schema
      documentation, and XIP memory kind note
- [ ] 6.3 Add explicit licensing/provenance note for pico-sdk SVD (BSD-3-Clause,
      `github.com/raspberrypi/pico-sdk`, pinned to a named release tag)
- [ ] 6.4 Archive this change
