# Tasks — add-additional-validity-concepts

## Phase 1: ValidDmaBinding

- [x] 1.1 New emitter `src/alloy_codegen/runtime_dma_validation.py`
      mirroring `runtime_pin_validation.py`'s shape.
- [x] 1.2 `dma_validation.hpp` per-device emits
      `template<PeripheralId, DmaChannelId> struct DmaBindingValid`
      + specialisations from `device.dma_bindings`.
- [x] 1.3 `concept ValidDmaBinding = DmaBindingValid<...>::value`.

## Phase 2: ValidClockSource

- [x] 2.1 New emitter
      `src/alloy_codegen/runtime_clock_validation.py`.
- [x] 2.2 `clock_validation.hpp` reads
      `peripheral_clock_bindings` and emits
      `ValidClockSource<Peripheral, Source>` with one
      specialisation per binding.

## Phase 3: ValidInterruptSlot

- [x] 3.1 Extend `runtime_interrupts.py` (or add a sibling
      `runtime_interrupt_validation.py`) to emit
      `ValidInterruptSlot<Peripheral, VectorSlot>` from
      `interrupt_bindings` + `vector_slots`.

## Phase 4: ValidI2cSpeed

- [x] 4.1 New emitter
      `src/alloy_codegen/runtime_i2c_speed_validation.py`.
- [x] 4.2 `i2c_speed_validation.hpp` defines a `consteval`
      predicate `is_valid_i2c_speed<Peripheral>(speed_hz)` that
      walks the configured `speed_modes` array and returns
      `true` when `speed_hz` fits within one mode's max.
- [x] 4.3 `template<PeripheralId P, std::uint32_t SpeedHz>
      concept ValidI2cSpeed = is_valid_i2c_speed<P>(SpeedHz);`.

## Phase 5: Pipeline wiring + tests

- [x] 5.1 `stages/emit.py` emits all four new headers per
      device when the underlying IR data exists.  No-op when
      the source tuples are empty (back-compat).
- [x] 5.2 Per-concept regression tests assert the emitted
      headers contain expected specialisations on stm32g071rb.
- [x] 5.3 `pytest --runtime-cpp-smoke` parametrisation picks
      up the new headers automatically; the synthesised
      `smoke.cpp` exercises a `static_assert(Valid<...>)` per
      concept where applicable.

## Phase 6: Spec + final checks

- [x] 6.1 Spec delta in `specs/artifact-contract/spec.md`.
- [x] 6.2 `openspec validate add-additional-validity-concepts
      --strict` passes.
- [x] 6.3 `pytest -q` + `ruff check` clean.
- [x] 6.4 `--runtime-cpp-smoke` green for every admitted
      device.
