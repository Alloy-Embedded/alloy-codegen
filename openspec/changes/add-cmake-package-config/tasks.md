# Tasks — add-cmake-package-config

## Phase 1: Per-core flag table

- [ ] 1.1 Add `_CORE_COMPILE_FLAGS` + `_CORE_LINK_FLAGS` mappings
      keyed by `device.identity.core` covering every admitted core:
      cortex-m0, cortex-m0plus, cortex-m4, cortex-m4f, cortex-m7f,
      riscv32imac (ESP32-C3), xtensa-lx6 (ESP32), xtensa-lx7
      (ESP32-S3), avr.
- [ ] 1.2 Unit test asserting every device's `core` value resolves
      to a non-empty flag list.

## Phase 2: Per-device CMake module emitter

- [ ] 2.1 New `emit_cmake_device_module(family_dir, device)` in
      `cmake_emission.py`.  Renders
      `<vendor>/<family>/generated/cmake/AlloyDevice-<device>.cmake`.
- [ ] 2.2 Module body defines an `INTERFACE IMPORTED` target
      `AlloyDevice::<device>` with:
      - `target_include_directories` for runtime + device dirs
      - `target_compile_features INTERFACE cxx_std_20`
      - `target_compile_options` from the core flag table
      - `target_link_options` referencing `device.ld`
      - `target_sources` referencing `startup.cpp` /
        `startup_vectors.cpp`
- [ ] 2.3 Use a relative path anchor (`${ALLOY_DEVICE_ROOT}`) so
      consumers can override where artifacts live; default to
      package-relative.

## Phase 3: Per-core toolchain fragment

- [ ] 3.1 Emit
      `<vendor>/<family>/generated/cmake/toolchain-<core>.cmake`
      once per device.  Sets `CMAKE_SYSTEM_NAME=Generic`,
      `CMAKE_SYSTEM_PROCESSOR`, `CMAKE_C_COMPILER` /
      `CMAKE_CXX_COMPILER` to the standard cross-compiler name
      (`arm-none-eabi-gcc`, `riscv32-unknown-elf-gcc`,
      `xtensa-esp32-elf-gcc`, `avr-gcc`).
- [ ] 3.2 Toolchain fragment is **opt-in** — consumers using their
      own toolchain don't have to load it.  Document its path in
      the per-device module as a comment.

## Phase 4: Top-level meta-package

- [ ] 4.1 Emit `cmake/AlloyDeviceConfig.cmake` at the publication
      root that resolves `COMPONENTS` arguments by including the
      relevant `AlloyDevice-<device>.cmake` files.
- [ ] 4.2 Emit `cmake/AlloyDeviceConfigVersion.cmake` carrying
      the codegen version so consumers can pin (`find_package(...
      1.2.0)`).
- [ ] 4.3 Combined with the BSP emitter (separate change),
      `find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb
      nucleo-g071rb)` resolves both targets.

## Phase 5: Smoke build verification

- [ ] 5.1 New consumer-verification stage step: in addition to
      the existing runtime-lite C++ smoke, run a `cmake -B build
      -S smoke_cmake_consumer/` against the generated package
      config and verify the configure step succeeds.  The smoke
      project is a 5-line `CMakeLists.txt` that does
      `find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb)`
      + `target_link_libraries`.  Non-blocking on hosts without a
      cross-compiler installed (skip with reason like the
      existing linker-script smoke).

## Phase 6: Tests + goldens

- [ ] 6.1 Per-device emit-fixture goldens for the new CMake files.
      Diff scope: 3 new files per device.
- [ ] 6.2 Regression test asserting `AlloyDevice-stm32g071rb.cmake`
      contains the expected include dirs, compile options
      (`-mcpu=cortex-m0plus`), and linker script reference.

## Phase 7: Spec + final checks

- [ ] 7.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 7.2 `openspec validate add-cmake-package-config --strict`
      passes.
- [ ] 7.3 Full `pytest -q` + `ruff check` clean.
- [ ] 7.4 Archive entry notes that this drops consumer onboarding
      from ~30 lines of hand-wired CMake to a 2-line
      `find_package` + `target_link_libraries`.  Necessary
      precondition for `add-cli-project-bootstrap`.
