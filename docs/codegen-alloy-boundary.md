# Codegen and Alloy Boundary

`alloy-codegen` and `alloy` split responsibilities on purpose.

The generator owns hardware facts. The runtime owns behavior.

## Codegen-Owned Outputs

Published `alloy-devices` trees may contain:

- family-root traceability:
  - `artifact-manifest.json`
- family metadata:
  - `metadata/family-index.json`
  - `metadata/family-connectivity.json`
  - `metadata/ip-blocks.json`
  - `metadata/capabilities.json`
  - `metadata/packages.json`
  - `metadata/connectors.json`
  - `metadata/system-descriptors.json`
  - `metadata/devices/<device>.json`
- generated descriptor headers and translation units:
  - `generated/runtime/types.hpp`
  - `generated/runtime/devices/<device>/peripheral_instances.hpp`
  - `generated/runtime/devices/<device>/pins.hpp`
  - `generated/runtime/devices/<device>/registers.hpp`
  - `generated/runtime/devices/<device>/register_fields.hpp`
  - `generated/runtime/devices/<device>/clock_bindings.hpp`
  - `generated/runtime/devices/<device>/dma_bindings.hpp`
  - `generated/runtime/devices/<device>/routes.hpp`
  - `generated/runtime/devices/<device>/connectors.hpp`
  - `generated/runtime/devices/<device>/systick.hpp`
  - `generated/runtime/devices/<device>/startup.hpp`
  - `generated/runtime/devices/<device>/system_clock.hpp`
  - `generated/runtime/devices/<device>/clock_profiles.hpp`
  - `generated/runtime/devices/<device>/clock_config.hpp`
  - `generated/runtime/devices/<device>/interrupts.hpp`
  - `generated/runtime/devices/<device>/interrupt_stubs.hpp`
  - `generated/runtime/devices/<device>/capabilities.json`
  - `generated/runtime/devices/<device>/resets.hpp`
  - `generated/runtime/devices/<device>/enable_domains.hpp`
  - `generated/runtime/devices/<device>/clock_graph.hpp`
  - `generated/runtime/devices/<device>/capabilities.hpp`
  - `generated/runtime/devices/<device>/system_sequences.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/common.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/gpio.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/uart.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/i2c.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/spi.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/dma.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/adc.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/dac.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/can.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/rtc.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/watchdog.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/timer.hpp`
    - compare/capture/encoder timer traits
  - `generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
  - `generated/devices/<device>/device.ld`
  - `generated/devices/<device>/startup.cpp`
  - `generated/devices/<device>/startup_vectors.cpp`
- reports:
  - `reports/validation-report.json`
  - `reports/validation-summary.json`
  - `reports/coverage.json`
  - `reports/runtime-provenance.json`
  - `reports/runtime-explainability.json`
  - `reports/publication-record.json`

Those files may describe:

- addresses
- typed peripheral, pin, register, route, DMA, startup, SysTick, interrupt, reset,
  clock-graph, capability, and bring-up sequence facts
- validation and publication status

The published C++ contract is runtime-first:

- headers under `generated/runtime/` are the only supported Alloy-facing C++ boundary
- driver semantic headers under
  `generated/runtime/devices/<device>/driver_semantics/` are the required hot-path layer for
  foundational drivers, including DMA, ADC, DAC, timer, and PWM
- `generated/runtime/devices/<device>/startup.hpp` carries the typed startup descriptor surface
  that Alloy consumes for startup metadata
- `generated/runtime/devices/<device>/interrupts.hpp` carries typed interrupt-to-peripheral
  bindings for the runtime contract
- `generated/runtime/devices/<device>/interrupt_stubs.hpp` carries the weak `extern "C"`
  interrupt declaration surface plus typed interrupt-stub descriptors
- `generated/runtime/devices/<device>/connectors.hpp` carries typed valid
  pin-peripheral-signal combinations so Alloy does not need connector scans or handwritten
  compatibility tables, and it now carries compile-time invalid-connector diagnostics with
  alternative pins plus provenance
- `generated/runtime/devices/<device>/clock_profiles.hpp` carries the stable, typed
  profile ids and default/safe/max-profile metadata derived from the canonical clock graph
- `generated/runtime/devices/<device>/clock_config.hpp` carries ready-to-call typed profile
  application helpers so Alloy does not need handwritten per-device clock bring-up wrappers
- `generated/runtime/devices/<device>/capabilities.json` carries the same runtime capability
  facts as the header contract, but in a tool-friendly sidecar for diff, CMake, and diagnostics
- `alloy-codegen explain --device <device> --fact <fact>` is the supported diagnostic entrypoint
  for tracing one emitted runtime fact back to provenance and explainability reports
- `alloy-codegen diff --from <device1> --to <device2>` is the supported diagnostic entrypoint
  for comparing per-device runtime capability deltas with provenance attached to each change
- `generated/runtime/devices/<device>/enable_domains.hpp` carries typed enable-domain facts
  derived from published runtime gate controls so Alloy does not need to reconstruct peripheral
  activation policy from low-level clock tables
- `generated/runtime/devices/<device>/system_sequences.hpp` carries typed default bring-up
  ordering metadata so Alloy can sequence startup descriptors, startup controls, and default
  clock profiles without reconstructing vendor policy from tables
- `generated/devices/<device>/device.ld` carries the linker-visible memory layout so Alloy does
  not need handwritten device linker scripts for supported devices
- `generated/devices/<device>/startup.cpp` and `startup_vectors.cpp` remain published as build
  inputs, not as a descriptor contract
- JSON metadata and reports remain available for tooling, validation, and inspection
- provenance and explainability reports remain JSON-only outputs; they are not a second public
  C++ contract

## Alloy-Owned Behavior

The Alloy runtime owns:

- typed `connect()` APIs
- compile-time and runtime connection selection behavior
- ownership and claims such as `take()`, `claim()`, or token models
- board initialization policy
- peripheral driver APIs such as `uart`, `spi`, `i2c`, `gpio`, `dma`, `adc`, `dac`, `timer`,
  or `pwm`
- board sequencing and high-level bring-up policy

`alloy-codegen` may emit the descriptor data needed by those behaviors, but it must not
implement them.

## Contract Rules

Generated artifacts must remain descriptor-oriented:

- no `namespace alloy`
- no `connect()` implementation
- no resource ownership primitives such as `take()` or `claim()`
- no board policy
- no public driver classes

If a new generated artifact needs behavior, that behavior belongs in `alloy`, not in
`alloy-codegen`.
