## Phase 0: Gap Audit & Downstream Handoff

- [x] 0.1 Document which emitted artifacts already exist, which are missing, and which are
      currently consumed by `alloy`
- [x] 0.2 Record the paired-alloy dependencies explicitly so this spec stays codegen-only
- [x] 0.3 Identify every downstream heuristic that can be replaced by an emitted artifact

## Phase 1: Linker Script & Startup-Facing Layout

- [x] 1.1 Create `src/alloy_codegen/runtime_linker_script.py`
- [x] 1.2 Emit `generated/devices/<device>/device.ld` from `MemoryRegion` + startup roles
- [ ] 1.3 Support Harvard layouts where `address_space` is meaningful
- [x] 1.4 Add linker-script required paths/content checks in `artifact_contract.py`
- [ ] 1.5 Extend `consumer_verification.py` to validate or link against
      `generated/devices/<device>/device.ld` on toolchains that support GNU ld scripts
- [x] 1.6 Add emitted linker-script goldens for foundational families

## Phase 2: Connector Tables & Interrupt Stubs

- [x] 2.1 Emit `connectors.hpp` per device with typed valid combinations
- [ ] 2.2 Emit provenance-rich invalid-combination diagnostics in connector specializations
- [x] 2.3 Emit `interrupt_stubs.hpp` per device
- [x] 2.4 Add artifact-contract and smoke coverage for both headers
- [x] 2.5 Add goldens covering connector tables and interrupt stubs

## Phase 3: Clock Configuration Helpers

- [x] 3.1 Create `src/alloy_codegen/runtime_clock_config.py`
- [x] 3.2 Emit `clock_profiles.hpp` per device
- [x] 3.3 Emit `clock_config.hpp` with generated application sequences
- [x] 3.4 Add artifact-contract and smoke coverage for clock config artifacts
- [x] 3.5 Add foundational-family goldens for default and max-frequency profiles

## Phase 4: Capability Sidecars & Diagnostics CLI

- [x] 4.1 Emit `capabilities.hpp` per device
- [x] 4.2 Emit `capabilities.json` per device
- [x] 4.3 Ensure capability emission consumes `CapabilityDescriptor` directly from the IR
- [ ] 4.4 Implement `alloy explain --device <name> --fact <fact>`
- [ ] 4.5 Implement `alloy diff --from <device1> --to <device2>`
- [ ] 4.6 Add artifact-contract, smoke, and docs coverage for the new artifacts/CLI

## Phase 5: Validation Moat

- [ ] 5.1 Fail publish when any required codegen-owned artifact is missing
- [x] 5.2 Fail publish when runtime-supported peripherals have incomplete capability coverage
- [ ] 5.3 Add cross-publication capability regression detection
- [ ] 5.4 Add cross-device capability parity/diff tests
- [ ] 5.5 Ensure consumer verification compiles or links the complete generated set

## Phase 6: Docs & Downstream Handoff

- [x] 6.1 Update artifact layout docs with the final emitted set
- [x] 6.2 Document the downstream consumer contract expected from `alloy`
- [x] 6.3 Document known gaps that still require paired-alloy work
- [ ] 6.4 Archive this change once all codegen-owned work is complete
