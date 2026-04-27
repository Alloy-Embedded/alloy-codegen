# Tasks — add-runtime-cpp-smoke-compile-ci

## Phase 1: Harness

- [x] 1.1 Created `tools/runtime_cpp_smoke.py`:
      iterates every admitted device via
      `alloy_codegen.bootstrap.DEVICE_REGISTRY`, runs the emit
      pipeline, materialises every emitted runtime header to a
      tmp tree, generates a per-device `smoke_<v>_<f>_<d>.cpp`
      that includes them all in topological order, and invokes
      `clang++ -std=c++20 -ffreestanding -nostdlib
      -fno-exceptions -fno-rtti -O0 -c`.
- [x] 1.2 Failure mode: the pytest case fails with the device
      label, the full list of headers included, and the first
      60 lines of compiler stderr (see
      `tests/test_runtime_cpp_smoke.py::_format_failure`).

## Phase 2: Pytest integration

- [x] 2.1 Pytest marker `@pytest.mark.runtime_cpp_smoke` declared
      via `pytest_configure` in `tests/conftest.py`.
- [x] 2.2 `--runtime-cpp-smoke` CLI flag (and
      `ALLOY_RUNTIME_CPP_SMOKE=1` env var equivalent) registered
      via `pytest_addoption` + `pytest_collection_modifyitems` —
      tests with the marker are skipped unless either is set.
- [x] 2.3 The `clang_path` session fixture skips every parametrised
      case when `shutil.which("clang++")` returns `None`, so
      contributors without clang are not blocked.

## Phase 3: CI wiring

- [x] 3.1 `.github/workflows/bootstrap-family.yml` runs
      `ALLOY_RUNTIME_CPP_SMOKE=1 python -m pytest
      tests/test_runtime_cpp_smoke.py -q` after the standard
      pytest pass.
- [x] 3.2 The workflow installs `clang` alongside the existing
      `build-essential` apt package — no new pinned-version
      dependency.

## Phase 4: Spec + final checks

- [x] 4.1 Spec delta in `specs/validation-and-gates/spec.md`.
- [x] 4.2 Documented in `docs/runtime-cpp-smoke-compile.md`.
- [x] 4.3 `openspec validate add-runtime-cpp-smoke-compile-ci
      --strict` passes.
- [x] 4.4 `pytest -q` clean (with and without the new flag).
      All 17 admitted devices' runtime headers compile cleanly
      with the freestanding clang invocation in ~15 s wall clock.
