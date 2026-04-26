# Tasks: Define PIO Semantic Struct Fields

## 1. Update PioSemanticTraits struct definition in alloy-codegen templates

- [x] 1.1 Replaced the stub-only emission in
      `src/alloy_codegen/runtime_driver_semantics.py` with a structured one.
      Primary template now declares `kPresent`, `kStateMachineCount`,
      `kInstructionMemoryDepth`, `kTxFifoDepth`, `kRxFifoDepth`, `kGpioBase`,
      `kGpioCount`, `kBaseAddress`, `kDreqTx`, `kDreqRx` (all zero-defaulted).
- [x] 1.2 Added the `StateMachineSemanticTraits<PioId, std::uint8_t Sm>`
      template (`kPresent=false`, zero DREQ defaults).
- [x] 1.3 All goldens regenerated; the new fields are zero defaults so
      non-PIO families remain zero-cost.

## 2. IR model

- [x] 2.1 Added `PioDescriptor` dataclass to `src/alloy_codegen/ir/model.py`
      (`pio_id`, `base_address`, `state_machine_count`,
      `instruction_memory_depth`, `tx_fifo_depth`, `rx_fifo_depth`,
      `gpio_base`, `gpio_count`, `dreq_tx_base`, `dreq_rx_base`,
      `provenance`).
- [x] 2.2 Added `Device.pio_blocks: tuple[PioDescriptor, ...]` (omit-if-empty).
- [x] 2.3 Updated JSON schema (`schemas/canonical-device-ir-v1.schema.json`)
      with `$defs/pio_descriptor` and `pio_blocks`; added omit-when-empty +
      populated round-trip tests in `tests/test_ir_model.py`.
- [x] 2.4 Carried `pio_blocks` through `connector_model.py`'s IR rebuild so
      the field survives `ensure_connector_descriptors`.

## 3. RP2040 PIO data overlay

- [x] 3.1 Created `patches/raspberrypi/rp2040/pio.json` with both PIO blocks
      (base addresses, FIFO/IMEM depths, DREQ bases) and source-note
      provenance.
- [x] 3.2 Extended the RP2040 normalize path
      (`_build_rp2040_device_ir` + `_load_rp2040_pio_blocks_overlay` in
      `stages/normalize.py`) to load `pio.json` and attach
      `Device.pio_blocks` with provenance referencing the overlay.

## 4. PIO semantic emitter for RP2040

- [x] 4.1 `emit_runtime_driver_pio_semantics_header` emits one
      `PioSemanticTraits<PioId::PioN>` specialization per `PioDescriptor`
      with all topology fields populated.
- [x] 4.2 The emitter produces one
      `StateMachineSemanticTraits<PioId::PioN, sm>` specialization for
      `sm in [0, state_machine_count)` with per-SM DREQs derived as
      `dreq_{tx,rx}_base + sm`.

## 5. Goldens and compile tests

- [x] 5.1 Regenerated `tests/fixtures/emitted/rp2040/.../driver_semantics/pio.hpp`
      (new fixture) and the existing `stm32g0` / `imxrt1060` ones. Added
      `tests/test_pio_semantic_traits.py` asserting:
      - non-PIO families emit only the primary template with zero defaults
      - RP2040 emits Pio0/Pio1 specializations with the documented field
        values
      - 8 state-machine specializations exist with correct per-SM DREQs
        (`Pio0,3 → kDreqTx=3`, `Pio1,2 → kDreqTx=10`, etc.)
      - the rp2040 `pio.hpp` matches the regenerated golden byte-for-byte
- [x] 5.2 C++ compile-time `static_assert` smoke landed alongside the
      `fill-gpio-semantic-gaps` Phase E compile-test infra:
      `tests/compile_tests/test_rp2040_pio_traits.cpp` is driven by
      `tests/test_compile_invariants.py` (skipped when no host C++20
      compiler is on PATH).  Asserts cover `kStateMachineCount`,
      `kInstructionMemoryDepth`, both block base addresses, and per-SM
      DREQ derivation (`Pio0,3 → kDreqTx=3`, `Pio1,2 → kDreqTx=10`,
      `Pio1,3 → kDreqRx=15`).
- [x] 5.3 Non-RP2040 family goldens (stm32g0, imxrt1060) keep
      `kStateMachineCount=0` on the primary template; verified via the
      regenerated fixtures and the new test.

## 6. Documentation

- [x] 6.1 `docs/COVERAGE_MATRIX.md` created with a `pio_traits` column —
      RP2040 marked ✓, every other admitted family N/A.  The doc also
      cross-references the live `<vendor>/<family>/reports/coverage.json`
      artifact and the openspec proposals that introduced each column.
- [x] 6.2 Inline docstring in `emit_runtime_driver_pio_semantics_header`
      documents that `PioSemanticTraits<PioId::PioN>::kDreqTx` is the SM0
      base; per-SM consumers can either index into
      `StateMachineSemanticTraits<...>` or do `kDreqTx + sm_index` at
      compile time.
