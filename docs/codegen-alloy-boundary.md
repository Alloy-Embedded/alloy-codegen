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
  - `generated/runtime/devices/<device>/systick.hpp`
  - `generated/runtime/devices/<device>/startup.hpp`
  - `generated/runtime/devices/<device>/system_clock.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/common.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/gpio.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/uart.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/i2c.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/spi.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/dma.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/adc.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/dac.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/timer.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
  - `generated/devices/<device>/startup.cpp`
  - `generated/devices/<device>/startup_vectors.cpp`
- reports:
  - `reports/validation-report.json`
  - `reports/validation-summary.json`
  - `reports/coverage.json`
  - `reports/publication-record.json`

Those files may describe:

- addresses
- typed peripheral, pin, register, route, DMA, startup, SysTick, and clock facts
- validation and publication status

The published C++ contract is runtime-first:

- headers under `generated/runtime/` are the only supported Alloy-facing C++ boundary
- driver semantic headers under
  `generated/runtime/devices/<device>/driver_semantics/` are the required hot-path layer for
  foundational drivers, including DMA, ADC, DAC, timer, and PWM
- `generated/runtime/devices/<device>/startup.hpp` carries the typed startup descriptor surface
  that Alloy consumes for startup metadata
- `generated/devices/<device>/startup.cpp` and `startup_vectors.cpp` remain published as build
  inputs, not as a descriptor contract
- JSON metadata and reports remain available for tooling, validation, and inspection

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
