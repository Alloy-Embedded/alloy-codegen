## Overview

This change moves low-level MCU bring-up closer to the published device contract.

The generated contract gains two new pieces:

1. a real startup translation unit:
   - `generated/devices/<device>/startup.cpp`
2. a runtime-lite system clock bring-up contract:
   - `generated/runtime/devices/<device>/system_clock.hpp`

The existing artifacts remain useful:

- `startup_descriptors.hpp` stays as the typed startup fact surface
- `clock_bindings.hpp` stays focused on peripheral gate/reset/selector bindings

The new artifacts cover the missing executable/system bring-up layer.

## Startup Contract

### Generated startup translation unit

Each device emits `generated/devices/<device>/startup.cpp`.

The translation unit must materialize:

- weak default handler
- weak interrupt/system exception aliases for all published vector slots except stack pointer
- generated vector table placed in the correct section
- generated `Reset_Handler`
- baseline reset flow:
  - initialize data
  - initialize BSS
  - call `SystemInit()`
  - call static constructors
  - enter `main`

The implementation may use the common linker symbol baseline already assumed by Alloy toolchains:

- `_sidata`
- `_sdata`
- `_edata`
- `_sbss`
- `_ebss`
- `__stack_top`
- `__init_array_start`
- `__init_array_end`

This is acceptable because the generated TU removes handwritten device startup code while staying
compatible with the existing linker model.

### Startup descriptors remain typed

`startup_descriptors.hpp` remains the metadata side of the contract and must stay aligned with the
generated startup translation unit.

`startup_vectors.cpp` is retired by this change. `startup.cpp` becomes the executable startup
artifact.

## System Clock Contract

### Canonical IR

Canonical IR gains `system_clock_profiles`.

Each profile is typed and device-scoped. At minimum it carries:

- `profile_id`
- `kind`
- `source_kind`
- `sysclk_hz`
- `hclk_hz`
- optional bus frequencies (`apb1_hz`, `apb2_hz`, `pclk_hz`)
- optional oscillator input frequency (`source_hz`)
- optional PLL parameters (`pll_m`, `pll_n`, `pll_p`, `pll_q`, `pll_r`)
- optional prescalers (`ahb_prescaler`, `apb1_prescaler`, `apb2_prescaler`)
- optional `flash_latency`

The intent is not to model every possible vendor clock tree in one generic algorithm. The intent
is to publish concrete, validated bring-up profiles that the generated C++ helper can execute.

### Runtime-lite artifact

Each foundational device emits:

- `generated/runtime/devices/<device>/system_clock.hpp`

This header publishes:

- `enum class SystemClockProfileId`
- `enum class SystemClockProfileKindId`
- `enum class SystemClockSourceKindId`
- `SystemClockProfileDescriptor`
- `SystemClockProfileTraits<SystemClockProfileId>`
- generated bring-up helpers for supported schemas

The bring-up helper surface is:

- `template<SystemClockProfileId Id> inline bool apply_system_clock_profile()`
- `inline bool apply_default_system_clock()`
- `inline bool apply_safe_system_clock()`

These helpers are generated in the device runtime namespace, not in `namespace alloy`.

### Foundational coverage

Initial foundational coverage must include:

- `stm32g071rb`: HSI16 + PLL default board profile
- `stm32f401re`: HSE + PLL default board profile
- `atsame70q21b`: safe internal RC profile

The design must allow later expansion to:

- external source fallback profiles
- additional PLL/external presets
- non-foundational families

## Boundary Change

This change deliberately adjusts the previous boundary rule that said startup algorithms belong
only in Alloy.

After this change:

- `alloy-codegen` may publish device-scoped bring-up code for startup and system clock
- `alloy` still owns higher-level board policy, sequencing, and API shape
- generated code must remain device-scoped and typed; it must not implement board selection,
  ownership, or user-facing HAL classes

## Validation and Gates

Foundational publication must fail when:

- `generated/devices/<device>/startup.cpp` is missing
- startup.cpp does not materialize `Reset_Handler`
- foundational devices lack `generated/runtime/devices/<device>/system_clock.hpp`
- foundational system clock headers do not publish typed profiles and default/safe helpers

Consumer smoke must compile both the startup source and the runtime-lite system clock header.
