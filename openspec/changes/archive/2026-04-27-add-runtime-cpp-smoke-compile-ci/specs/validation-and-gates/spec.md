## ADDED Requirements

### Requirement: Emitted runtime C++ headers MUST pass a freestanding smoke compile in CI

CI SHALL run a smoke-compile step over every device the pipeline
admits.  The step SHALL compile a per-device `smoke.cpp` that
includes the device's runtime headers and exercises at least one
`static_assert` per typed C++20 concept the headers declare
(e.g. `ValidPinAssignment<Pin, PeripheralSignal::...>`) using
`clang++ -std=c++20 -ffreestanding -nostdlib -c`.  The step SHALL
fail the build on any compile error, with a failure message that
identifies the device, the offending header, and the compiler
stderr.  Locally, the gate SHALL be skipped (not failed) when
`clang++` is not on PATH so contributors without a clang
toolchain are not blocked from running unrelated tests.

#### Scenario: Every admitted device passes a freestanding smoke compile

- **WHEN** CI runs `pytest --runtime-cpp-smoke -q`
- **THEN** every admitted device SHALL produce a per-device
  `smoke.cpp` that compiles cleanly with
  `clang++ -std=c++20 -ffreestanding -nostdlib -c`
- **AND** the smoke `.cpp` SHALL include every runtime header the
  pipeline emitted for that device

#### Scenario: A regression in template metaprogramming fails the gate

- **WHEN** an emitter change introduces a malformed
  specialization or a missing include
- **AND** the smoke compile is run
- **THEN** the gate SHALL fail with a message identifying the
  device, the header, and the compiler stderr — sufficient
  context for the reviewer to fix without reproducing locally

#### Scenario: Local pytest is not blocked when clang is absent

- **WHEN** a contributor runs `pytest -q` locally and `clang++`
  is not on PATH
- **THEN** smoke-compile tests SHALL be skipped (not failed)
- **AND** the rest of the test suite SHALL run normally
