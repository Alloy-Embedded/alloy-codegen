## Phase 0: Bootstrap & Source Manifests

- [x] 0.1 Add `("raspberrypi", "rp2040")` to `DEVICE_REGISTRY` and `SOURCE_BUNDLES`
      in `src/alloy_codegen/bootstrap.py` with source bundle `("pico-sdk",)`
- [x] 0.2 Create `src/alloy_codegen/sources/pico_sdk.py` — source adapter that fetches
      `src/rp2040/hardware_regs/rp2040.svd` from `github.com/raspberrypi/pico-sdk`
- [x] 0.3 Add Raspberry Pi fetch branch to `src/alloy_codegen/stages/fetch.py`
- [x] 0.4 Add `pico-sdk` entry to the source manifest with revision pinning, provenance
      label `pico-sdk`, and BSD-3-Clause licensing note
- [x] 0.5 Scaffold `patches/raspberrypi/rp2040/family.json` with packages (`qfn56`),
      pins (GP0–GP29), memories (SRAM 264KB + xip-flash window), clock nodes,
      and peripheral RCC-equivalent signals (RESETS register)
- [x] 0.6 Scaffold `patches/raspberrypi/rp2040/devices/rp2040.json` with
      `core = "cortex-m0plus-dual"`, `svd_file`, memory regions, system clock profiles
      (safe-rosc-6mhz, default-pll-125mhz), and peripheral list
- [x] 0.7 Add minimal stub SVD to `tests/fixtures/pico-sdk/src/rp2040/hardware_regs/rp2040.svd`
      covering RESETS, CLOCKS, IO_BANK0, SIO, UART0/1, SPI0/1, I2C0/1, ADC, PWM, etc.
- [x] 0.8 Verify fetch produces a non-empty `RawDeviceDocument` for `rp2040`

## Phase 1: IR Ingestion — RP2040

- [x] 1.1 Add `alloy.pinmux.rp2040-funcsel-v1` to the known backend schema set in
      `connector_model.py`; document that `af_number` carries the FUNCSEL index (0–9)
- [x] 1.2 Populate `patches/raspberrypi/rp2040/family.json` with full pin-signal data:
      UART0/1, SPI0/1, I2C0/1, PWM slices 0–7, ADC, USB, PIO0/PIO1 function indices
- [x] 1.3 Populate clock nodes for ROSC, XOSC, PLL_SYS, PLL_USB, CLK_REF, CLK_SYS,
      CLK_PERI, CLK_USB, CLK_ADC in `family.json`; add fractional divider metadata
- [x] 1.4 Add `kind = "xip-flash"` to `MemoryRegion` in `src/alloy_codegen/ir/model.py`
      and update the memory normalization path to recognize it from patches
- [x] 1.5 Populate `patches/raspberrypi/rp2040/devices/rp2040.json` with clock enable/reset
      signals (RESETS.RESET_* bits), interrupt table, and DMA request lines
- [x] 1.6 Add `core = "cortex-m0plus-dual"` to the known core set in normalizer;
      document single-core-perspective behavior explicitly in a generated comment
- [x] 1.7 Write normalized golden fixtures `tests/fixtures/rp2040/rp2040.canonical.json`
      and `tests/fixtures/rp2040/pico.canonical.json`; add regression tests in
      `tests/test_normalize.py` for both devices

## Phase 2: XIP Startup & Linker Script

- [x] 2.1 Update `runtime_linker_script.py` to emit `BOOT2 (rx)` and `XIP_MAIN (rx)`
      sections when a `xip-flash` memory region is present
- [x] 2.2 Emit `__boot2_start`, `__boot2_end`, and `__boot2_size` symbols in the linker
      script; emit `__xip_text_start` / `__xip_text_end` for the main flash text region
- [x] 2.3 Update startup.cpp emitter (`emission.py`) to include:
      - `.boot2` section placeholder (256 bytes, ARM-only `#if defined(__arm__) || defined(__thumb__)` guard)
      - `xip_init()` weak declaration and call before the `.data` copy loop
      - Explicit single-core comment noting core 1 is not started in this first cut
- [x] 2.4 Add linker script and startup artifacts emitted for both `rp2040` and `pico` devices
- [x] 2.5 Update `artifact_contract.py` to accept `xip-flash` as a valid memory kind
      and verify `device.ld` contains at least one `xip-flash` region for RP2040

## Phase 3: Runtime Contract — RP2040

- [x] 3.1 Emit full standard runtime header set for `rp2040` and `pico` devices under
      `generated/runtime/devices/{device}/`: peripheral_instances, pins, registers,
      register_fields, clock_bindings, clock_graph, clock_profiles, clock_config,
      system_clock, connectors, capabilities, routes, dma_bindings, systick,
      low_power, resets, enable_domains, interrupt_stubs, system_sequences
- [x] 3.2 Emit all 17 driver semantics headers including `pio.hpp` as explicit stub
      (all refs = `kInvalidRef`, `kPresent = false`, `kPioSemanticPeripherals` is empty);
      stub peripheral IDs excluded from `k*SemanticPeripherals` arrays for all protocol types
- [x] 3.3 Verify consumer smoke compiles all RP2040/pico runtime headers without errors
      (validated via `test_foundational_families_publish_with_same_generic_workflow`)
- [x] 3.4 Emitted artifacts verified across `test_foundational_families_emit_same_descriptor_contract`
- [x] 3.5 Artifact-contract coverage passing for both `rp2040` and `pico` devices

## Phase 4: PIO Capability Stub

- [x] 4.1 `capabilities.json` emits `runtime-support:pio` as a present capability
      with `present: true` and appropriate schema_id
- [x] 4.2 `capabilities.hpp` emits a typed `CapabilityId::kPio` entry
- [x] 4.3 `driver_semantics/pio.hpp` emits standard stub pattern:
      `kPresent = false`, all register/field refs invalid, peripheral array empty
- [x] 4.4 PIO tracked in publication-gate capability regression across publish cycles
- [x] 4.5 Consumer smoke compiles `driver_semantics/pio.hpp` without errors

## Phase 5: CI & Publication Gates

- [x] 5.1 Added `raspberrypi/rp2040` to `test_foundational_families.py` publication matrix
      (`_family_contexts` and both publish tests)
- [x] 5.2 `patches/raspberrypi/` directory structure established and recognized
- [x] 5.3 All standard runtime headers verified present for both `rp2040` and `pico`
      via `_device_artifact_paths` in foundational family tests
- [x] 5.4 Full publication flow end-to-end for rp2040 family confirms
      `publication_mode: published` and `consumer_verification.succeeded: True`
- [x] 5.5 `test_foundational_families_remain_complete_across_repeat_publish_cycles`
      confirms no capability regression between publication cycles

## Phase 6: Fixtures & Docs

- [x] 6.1 All affected fixtures regenerated: `rp2040.canonical.json` and `pico.canonical.json`
      updated after ip_version additions, pin package filtering, and stub fixes
- [x] 6.2 Pi Pico board added as `pico` device in `raspberrypi/rp2040` family:
      27 exposed GPIO pins (GP0-GP22, GP25, GP26-GP28), 2MB QSPI flash,
      onboard LED on GP25; `patches/raspberrypi/rp2040/devices/pico.json` created
- [x] 6.3 SVD fixture updated with register field descriptors for UART0/UART1 DATA fields;
      BSD-3-Clause provenance for pico-sdk SVD documented in source manifest
- [x] 6.4 Archive this change
