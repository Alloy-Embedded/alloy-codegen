# Runtime C++ Smoke-Compile CI Gate

## Why

Emitted `.hpp` artifacts are validated today by string-presence
asserts and goldens — fast, but blind to compile-time errors that
only show up when a real compiler ingests the headers.  Recent
work (typed enums, `pin_validation.hpp` concepts) introduced
template-heavy C++20 code where a single missing include or
malformed specialization slips past the existing tests.

A minimal smoke-compile job that drives `clang++ -std=c++20
-ffreestanding -nostdlib -c` over each emitted runtime header
catches these regressions at PR time.  Cheap, decisive, scales
linearly with admitted devices because each compile is
independent.

## What Changes

- New harness `tools/runtime_cpp_smoke.py` that, for every device
  the pipeline emits, generates a tiny `smoke.cpp` including the
  device's runtime headers and instantiating one
  `static_assert(ValidPinAssignment<...>)` per registered concept
  (where applicable).
- Compiles with `clang++ -std=c++20 -ffreestanding -nostdlib -c`
  using a vendored libc++ headers subset (or the host toolchain's
  freestanding mode) — no link step, just compile.
- Pytest fixture `pytest --runtime-cpp-smoke` runs the harness for
  the whole admitted set; CI runs it on every push.
- Failure modes report the device, the offending header, and the
  compiler stderr as the test failure message.
- Job is **opt-in locally** (requires `clang++` on PATH) and
  **mandatory in CI** — the runtime-lite consumer-verification
  harness already requires a clang in CI, so the prerequisite is
  there.
- Artifacts unchanged — this is a new validation gate, not an
  emission change.

## Impact

Regressions in template metaprogramming or include hygiene
surface at PR time instead of in downstream alloy HAL builds.
Pairs with the existing publication gate (no string literals)
and the new `artifact-footprint-budget` change to form a
three-layer C++ quality bar: type-safety (smoke compile), zero
runtime overhead (no string literals), bounded footprint
(byte budgets per artifact).

## What this DOES NOT do

- Does not link.  Linking would require per-device startup files
  and is the runtime-lite consumer-verification harness's job.
- Does not run optimization passes.  Smoke compile is `-O0`; the
  goal is "does it parse and typecheck", not "is the codegen
  optimal".
