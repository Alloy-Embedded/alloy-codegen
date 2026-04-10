## Phase 1: Emitter implementation

- [x]1.1 Add `emit_signal_map_header(*, family_dir, devices)` to `emission.py`:
      - collect all `PinSignal` entries where `af_number is not None` and `peripheral is not None`
      - deduplicate by `(peripheral, signal, pin_name, af_number)` across devices
      - sort by `(peripheral, signal, pin_name)` for determinism
      - emit `{family_dir}/generated/signal_map.hpp` with a `SignalDescriptor` struct and
        `kSignalMap[]` constexpr array inside the family C++ namespace
- [x]1.2 Call `emit_signal_map_header()` in `stages/emit.py` `run()` and include the
      result in the `artifacts` list

## Phase 2: Tests and golden fixtures

- [x]2.1 Generate and commit the golden fixture
      `tests/fixtures/emitted/stm32g0/generated/signal_map.hpp`
- [x]2.2 Add assertion in `test_emit.py` `test_emit_matches_golden_artifacts` verifying
      the `signal_map.hpp` content matches the fixture
- [x]2.3 Add a targeted test asserting `kSignalMap` content includes at least one known
      entry for the bootstrap family (e.g. USART2/TX/PA2)
- [x]2.4 Update `test_publish.py` artifact count guard if needed (already `>= N`)

## Phase 3: Gate check

- [x]3.1 Run `make test` (full suite) green with no ruff violations
- [x]3.2 Verify emitted `signal_map.hpp` compiles cleanly with a trivial C++ snippet
