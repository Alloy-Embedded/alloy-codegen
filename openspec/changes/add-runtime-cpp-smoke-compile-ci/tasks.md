# Tasks — add-runtime-cpp-smoke-compile-ci

## Phase 1: Harness

- [ ] 1.1 Create `tools/runtime_cpp_smoke.py`:
      - Iterates every emitted device.
      - Materialises emitted headers to a tmpdir.
      - Generates a `smoke.cpp` per device including all runtime
        headers and at least one `static_assert` per typed concept
        (e.g. `ValidPinAssignment<Pin, PeripheralSignal::*>`).
      - Invokes `clang++ -std=c++20 -ffreestanding -nostdlib -c`.
- [ ] 1.2 Failure mode reports device, header, and compiler stderr.

## Phase 2: Pytest integration

- [ ] 2.1 Pytest marker `@pytest.mark.runtime_cpp_smoke`.
- [ ] 2.2 `--runtime-cpp-smoke` CLI flag enables the marker.
- [ ] 2.3 The marker is **skipped** if `clang++` is not on PATH
      (so local devs without clang aren't blocked).

## Phase 3: CI wiring

- [ ] 3.1 GitHub Actions workflow runs
      `pytest --runtime-cpp-smoke -q` on every push.
- [ ] 3.2 The workflow uses the same clang the runtime-lite
      consumer-verification harness uses (no new toolchain
      dependency).

## Phase 4: Spec + final checks

- [ ] 4.1 Spec delta in `specs/validation-and-gates/spec.md`.
- [ ] 4.2 Document the gate in
      `docs/runtime-cpp-smoke-compile.md`.
- [ ] 4.3 `openspec validate add-runtime-cpp-smoke-compile-ci
      --strict` passes.
- [ ] 4.4 `pytest -q` clean (with and without the new flag).
