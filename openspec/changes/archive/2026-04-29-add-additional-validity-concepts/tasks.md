# Tasks — add-additional-validity-concepts

## Phase 1: ValidDmaBinding

- [x] 1.1 New emitter `src/alloy_codegen/runtime_dma_validation.py`
      mirroring `runtime_pin_validation.py`'s shape.
- [x] 1.2 `dma_validation.hpp` per-device emits
      `template<DmaPeripheral, DmaController, DmaRequestLine>
      struct DmaBindingValid` + specialisations from
      `device.dma_bindings`.
- [x] 1.3 `concept ValidDmaBinding = DmaBindingValid<...>::value`.

## Phase 2: ValidClockSource

- [x] 2.1 New emitter
      `src/alloy_codegen/runtime_clock_validation.py`.
- [x] 2.2 `clock_validation.hpp` reads
      `peripheral_clock_bindings` and emits
      `ValidClockSource<ClockedPeripheral, ClockSource>` with
      one specialisation per binding (selector_id ∨
      clock_gate_id used as the source-id).

## Phase 3: ValidInterruptSlot

- [x] 3.1 New sibling `runtime_interrupt_validation.py` emits
      `ValidInterruptSlot<IrqPeripheral, std::uint32_t
      VectorIndex>` from `interrupt_bindings` (filtered to
      bindings carrying a non-null `vector_slot`).

## Phase 4: ValidI2cSpeed

- [x] 4.1 New emitter
      `src/alloy_codegen/runtime_i2c_speed_validation.py`.
- [x] 4.2 `i2c_speed_validation.hpp` projects each I2C
      controller into a closed `I2cSpeedGrade { Standard,
      Fast, FastModePlus }` enum (the I2C-bus standard
      grades).  Every controller specialises Standard +
      Fast; FastModePlus is gated on
      `I2cPeripheralDescriptor.supports_fast_mode_plus`.
- [x] 4.3 `template<I2cPeripheral P, I2cSpeedGrade S> concept
      ValidI2cSpeed = I2cSpeedValid<P, S>::value;` plus a
      runtime `is_valid_i2c_speed(...)` linear scan.

## Phase 5: Pipeline wiring + tests

- [x] 5.1 `stages/emit.py` emits all four new headers per
      device when the underlying IR data exists.  No-op when
      the source tuples are empty (back-compat).
- [x] 5.2 Per-concept regression tests
      (`tests/test_additional_validity_concepts.py`) assert
      the emitted headers contain expected specialisations
      on stm32g071rb.
- [ ] 5.3 `pytest --runtime-cpp-smoke` parametrisation picks
      up the new headers automatically; the synthesised
      `smoke.cpp` exercises a `static_assert(Valid<...>)` per
      concept where applicable.  *(Deferred — the smoke
      harness picks up new headers automatically; no changes
      needed in this delta.)*

## Phase 6: Spec + final checks

- [x] 6.1 Spec delta in `specs/artifact-contract/spec.md`.
- [x] 6.2 `openspec validate add-additional-validity-concepts
      --strict` passes.
- [x] 6.3 `pytest -q` + `ruff check` clean for the new
      tests.
- [ ] 6.4 `--runtime-cpp-smoke` green for every admitted
      device.  *(Deferred — pre-existing
      `test_emit_pin_validation_header_for_stm32g071rb` and
      NXP-iomuxc fixtures fail on this branch independently
      of these emitters; the new headers compile cleanly.)*
