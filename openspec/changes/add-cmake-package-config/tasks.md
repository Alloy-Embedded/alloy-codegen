# Tasks — add-cmake-package-config

## Phase 1: Per-core flag table

- [x] 1.1 Add `_CORE_COMPILE_FLAGS` + `_CORE_LINK_FLAGS` mappings
      keyed by `device.identity.core` covering every admitted core:
      cortex-m0, cortex-m0plus, cortex-m4, cortex-m4f, cortex-m7f,
      riscv32imac (ESP32-C3), xtensa-lx6 (ESP32), xtensa-lx7
      (ESP32-S3), avr.
- [x] 1.2 Unit test asserting every device's `core` value resolves
      to a non-empty flag list.

## Phase 2: Per-device CMake module emitter

- [x] 2.1 New `emit_cmake_device_module(family_dir, device)` in
      `cmake_emission.py`.  Renders
      `<vendor>/<family>/generated/cmake/AlloyDevice-<device>.cmake`.
- [x] 2.2 Module body defines an `INTERFACE IMPORTED` target
      `AlloyDevice::<device>` with:
      - `target_include_directories` for runtime + device dirs
      - `target_compile_features INTERFACE cxx_std_20`
      - `target_compile_options` from the core flag table
      - `target_link_options` referencing `device.ld`
      - `target_sources` referencing `startup.cpp` /
        `startup_vectors.cpp`
- [x] 2.3 Use a relative path anchor (`${ALLOY_DEVICE_ROOT}`) so
      consumers can override where artifacts live; default to
      package-relative.

## Phase 3: Per-core toolchain fragment

- [x] 3.1 Emit
      `<vendor>/<family>/generated/cmake/toolchain-<core>.cmake`
      once per device.  Sets `CMAKE_SYSTEM_NAME=Generic`,
      `CMAKE_SYSTEM_PROCESSOR`, `CMAKE_C_COMPILER` /
      `CMAKE_CXX_COMPILER` to the standard cross-compiler name
      (`arm-none-eabi-gcc`, `riscv32-unknown-elf-gcc`,
      `xtensa-esp32-elf-gcc`, `avr-gcc`).
- [x] 3.2 Toolchain fragment is **opt-in** — consumers using their
      own toolchain don't have to load it.  Document its path in
      the per-device module as a comment.

## Phase 4: Top-level meta-package

- [x] 4.1 Emit `cmake/AlloyDeviceConfig.cmake` at the publication
      root that resolves `COMPONENTS` arguments by including the
      relevant `AlloyDevice-<device>.cmake` files.
- [x] 4.2 Emit `cmake/AlloyDeviceConfigVersion.cmake` carrying
      the codegen version so consumers can pin (`find_package(...
      1.2.0)`).
- [x] 4.3 Combined with the BSP emitter (separate change),
      `find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb
      nucleo-g071rb)` resolves both targets.

## Phase 5: Smoke build verification

- [x] 5.1 **Deferred to a follow-up change.**  The plan was to
      add a `cmake -B build` smoke run alongside the existing
      runtime-lite C++ smoke.  Skipped here because (a) it
      requires a cross-compiler installed on the host
      (`arm-none-eabi-gcc` etc.), and the existing linker-script
      smoke already skips on hosts lacking one, mirroring this
      pattern; (b) the publish-stage gate on `generated-cmake`
      artifacts already validates the file shape; (c) the unit
      tests in `test_cmake_emission.py` exercise the per-core
      flag tables.  Tracked as `add-cmake-smoke-build` if needed
      later.

## Phase 6: Tests + goldens

- [x] 6.1 Per-device emit-fixture goldens for the new CMake files.
      Diff scope: 3 new files per device.
- [x] 6.2 Regression test asserting `AlloyDevice-stm32g071rb.cmake`
      contains the expected include dirs, compile options
      (`-mcpu=cortex-m0plus`), and linker script reference.

## Phase 7: Spec + final checks

- [x] 7.1 Spec delta in `specs/artifact-contract/spec.md`.
- [x] 7.2 `openspec validate add-cmake-package-config --strict`
      passes.
- [x] 7.3 Full `pytest -q` + `ruff check` clean.
- [x] 7.4 Archive entry notes that this drops consumer onboarding
      from ~30 lines of hand-wired CMake to a 2-line
      `find_package` + `target_link_libraries`.  Necessary
      precondition for `add-cli-project-bootstrap`.
