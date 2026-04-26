## ADDED Requirements

### Requirement: Per-device CMake INTERFACE library SHALL be emitted

The pipeline SHALL emit a `<vendor>/<family>/generated/cmake/AlloyDevice-<device>.cmake` artifact per admitted device that declares an `INTERFACE IMPORTED` target named `AlloyDevice::<device>` carrying every flag the consumer needs to compile + link a firmware image: include directories, `cxx_std_20` compile feature, per-core compile options (`-mcpu=...`, `-mthumb`, `-mfloat-abi=...`), linker-script reference (`device.ld`), and the startup translation unit.  Path references SHALL anchor on `${ALLOY_DEVICE_ROOT}` so consumers can override the artifact root.

#### Scenario: STM32G071RB CMake module exposes Cortex-M0+ flags

- **WHEN** the pipeline emits CMake artifacts for STM32G071RB
- **THEN** `st/stm32g0/generated/cmake/AlloyDevice-stm32g071rb.cmake`
  SHALL declare `add_library(AlloyDevice::stm32g071rb INTERFACE IMPORTED)`
- **AND** SHALL call `target_compile_options` with `-mcpu=cortex-m0plus`,
  `-mthumb`, and `-mfloat-abi=soft`
- **AND** SHALL call `target_link_options` with a `-T` flag pointing
  at `device.ld` under `${ALLOY_DEVICE_ROOT}`
- **AND** SHALL call `target_sources` referencing the device's
  `startup.cpp` (or `startup_vectors.cpp` on cores that emit a
  separate vector file)
- **AND** SHALL call `target_compile_features` with `cxx_std_20`

### Requirement: Top-level CMake meta-package SHALL resolve COMPONENTS

The pipeline SHALL emit a top-level `cmake/AlloyDeviceConfig.cmake` + `cmake/AlloyDeviceConfigVersion.cmake` pair at the publication root that resolves `find_package(AlloyDevice REQUIRED COMPONENTS <id>...)` calls by including the per-device CMake modules.  The version file SHALL carry the codegen-published version so consumers can pin via `find_package(AlloyDevice 1.2.0 REQUIRED ...)`.

#### Scenario: Consumer find_package picks up requested device + board

- **WHEN** a consumer's CMakeLists calls
  `find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb nucleo-g071rb)`
- **THEN** the meta-package SHALL surface targets named
  `AlloyDevice::stm32g071rb` and `AlloyDevice::nucleo-g071rb`
- **AND** linking either target SHALL bring in the include paths,
  compile options, linker-script flag, and startup translation
  unit transitively

### Requirement: Per-core toolchain fragment SHALL be available as opt-in

The pipeline SHALL emit a `<vendor>/<family>/generated/cmake/toolchain-<core>.cmake` per device that, when loaded via `-DCMAKE_TOOLCHAIN_FILE=...`, sets `CMAKE_SYSTEM_NAME=Generic`, `CMAKE_SYSTEM_PROCESSOR`, and the standard cross-compiler triple for that core.  The fragment SHALL be opt-in — consumers with their own toolchain SHALL be able to use the per-device CMake module without loading the toolchain fragment.

#### Scenario: Cortex-M0+ toolchain fragment selects arm-none-eabi-gcc

- **WHEN** the pipeline emits CMake artifacts for any Cortex-M0+
  device
- **THEN** the corresponding `toolchain-cortex-m0plus.cmake` SHALL
  set `CMAKE_SYSTEM_NAME` to `Generic`
- **AND** SHALL set `CMAKE_SYSTEM_PROCESSOR` to `arm`
- **AND** SHALL set `CMAKE_C_COMPILER` to `arm-none-eabi-gcc`
- **AND** SHALL set `CMAKE_CXX_COMPILER` to `arm-none-eabi-g++`
