# Add CMake Package Config Emitter

## Why

CMake is the lingua franca of C++ embedded builds.  Today an
alloy-codegen consumer pulls the published artifacts (headers,
linker script, startup.cpp) and hand-wires:

- include paths (`generated/runtime/devices/<device>` etc.)
- the linker script path (`device.ld`)
- the startup translation unit (`startup.cpp`)
- the per-target compile flags (target triple, FPU, ABI)

This is at least 30 lines of boilerplate per project.  modm's
`lbuild` materialises a tailored CMakeLists, but it's a custom
build tool the user has to learn.  The de-facto standard for
"library that drops into any C++ build" is **CMake package config**
(`find_package(...)`).

This change ships, alongside the existing per-device artifacts, a
generated `<vendor>/<family>/<device>/cmake/AlloyDeviceConfig.cmake`
file that exposes the device as an INTERFACE library with all
include paths, compile-options, and the linker-script path baked
in, so a downstream `CMakeLists.txt` becomes:

```cmake
find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb)
target_link_libraries(my_app PRIVATE AlloyDevice::stm32g071rb)
```

That's it.  No header-search paths, no `-T` flag, no manual
startup wiring.

## What Changes

### Emitted artifacts

Per device:

```
<vendor>/<family>/generated/cmake/AlloyDeviceConfig.cmake
<vendor>/<family>/generated/cmake/AlloyDevice-<device>.cmake
<vendor>/<family>/generated/cmake/toolchain-<core>.cmake
```

`AlloyDeviceConfig.cmake` is the entry point — it includes one
`AlloyDevice-<device>.cmake` per admitted device based on the
requested `COMPONENTS`.

`AlloyDevice-<device>.cmake` defines:

```cmake
add_library(AlloyDevice::stm32g071rb INTERFACE IMPORTED)

target_include_directories(AlloyDevice::stm32g071rb INTERFACE
    "${ALLOY_DEVICE_ROOT}/st/stm32g0/generated/runtime"
    "${ALLOY_DEVICE_ROOT}/st/stm32g0/generated/runtime/devices/stm32g071rb"
)

target_compile_features(AlloyDevice::stm32g071rb INTERFACE cxx_std_20)

target_compile_options(AlloyDevice::stm32g071rb INTERFACE
    -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft
)

target_link_options(AlloyDevice::stm32g071rb INTERFACE
    -T"${ALLOY_DEVICE_ROOT}/st/stm32g0/generated/devices/stm32g071rb/device.ld"
    -nostartfiles
)

target_sources(AlloyDevice::stm32g071rb INTERFACE
    "${ALLOY_DEVICE_ROOT}/st/stm32g0/generated/devices/stm32g071rb/startup.cpp"
)
```

`toolchain-<core>.cmake` is an opt-in toolchain file fragment that
sets the cross-compiler triple, search-mode flags, etc. — emitted
once per ARM core variant (`cortex-m0`, `cortex-m0plus`,
`cortex-m4f`, `cortex-m7f`, `riscv32imac`, `xtensa-lx6`,
`xtensa-lx7`, `avr`).

### Compile-flags table

The compile / link options come from a per-core mapping in the IR:

```python
CORE_FLAGS = {
    "cortex-m0":     ["-mcpu=cortex-m0", "-mthumb", "-mfloat-abi=soft"],
    "cortex-m0plus": ["-mcpu=cortex-m0plus", "-mthumb", "-mfloat-abi=soft"],
    "cortex-m4":     ["-mcpu=cortex-m4", "-mthumb", "-mfloat-abi=soft"],
    "cortex-m4f":    ["-mcpu=cortex-m4", "-mthumb", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16"],
    "cortex-m7f":    ["-mcpu=cortex-m7", "-mthumb", "-mfloat-abi=hard", "-mfpu=fpv5-d16"],
    # ... etc.
}
```

This table lives in `runtime_lite_emission.py` (or a new
`cmake_emission.py` module).  Each device's `core` field selects
the right entry.

### Top-level meta-package

A single `cmake/AlloyDeviceConfig.cmake` at the publication root
delegates to the per-device file via `COMPONENTS` so:

```cmake
find_package(AlloyDevice REQUIRED COMPONENTS stm32g071rb nucleo-g071rb)
```

picks up both the device target and (combined with the BSP
emitter) the board target.

## Impact

Reduces consumer onboarding from 30 lines of CMake plumbing to 2.
This is the change that makes alloy-codegen feel like a "real"
library rather than a folder of headers.  Necessary precondition
for `add-cli-project-bootstrap` (`alloy new`) — that CLI's
generated CMakeLists will lean on `find_package(AlloyDevice)`.

modm has nothing equivalent in CMake; their integration story is
"use lbuild".  Shipping native CMake support is a moat for
embedded teams already invested in CMake/Ninja/CTest.
