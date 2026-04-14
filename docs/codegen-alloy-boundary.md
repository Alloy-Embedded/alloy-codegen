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
  - `generated/runtime/devices/<device>/system_clock.hpp`
  - `generated/runtime/devices/<device>/dma_bindings.hpp`
  - `generated/runtime/devices/<device>/routes.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/common.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/gpio.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/uart.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/i2c.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/spi.hpp`
  - `generated/runtime/devices/<device>/driver_semantics/dma.hpp`
  - `generated/peripherals/*.hpp`
  - `generated/ip/*.hpp`
  - `generated/connector_tables.hpp`
  - `generated/runtime_profiles.hpp`
  - `generated/rcc_map.hpp`
  - `generated/dma_map.hpp`
  - `generated/interrupt_map.hpp`
  - `generated/memory_map.hpp`
  - `generated/package_map.hpp`
  - `generated/clock_tree_lite.hpp`
  - `generated/devices/<device>/device_descriptor.hpp`
  - `generated/devices/<device>/pins.hpp`
  - `generated/devices/<device>/peripheral_instances.hpp`
  - `generated/devices/<device>/interrupt_bindings.hpp`
  - `generated/devices/<device>/dma_bindings.hpp`
  - `generated/devices/<device>/capability_overlays.hpp`
  - `generated/devices/<device>/register_map.hpp`
  - `generated/devices/<device>/register_fields.hpp`
  - `generated/devices/<device>/startup_descriptors.hpp`
  - `generated/devices/<device>/startup.cpp`
  - `generated/devices/<device>/startup_vectors.cpp`
- reports:
  - `reports/validation-report.json`
  - `reports/validation-summary.json`
  - `reports/coverage.json`
  - `reports/publication-record.json`

Those files may describe:

- addresses
- device descriptors, register maps, and IP versions
- pins, packages, and constraints
- connector candidates, groups, requirements, and operations
- interrupts, memories, startup descriptors, clocks, resets, and DMA routes
- validation and publication status

The published C++ contract is descriptor-first:

- runtime-lite headers under `generated/runtime/` are the preferred hot-path boundary for Alloy
- runtime-lite driver semantic headers under
  `generated/runtime/devices/<device>/driver_semantics/` are the required hot-path layer for
  foundational drivers, including DMA
- family-level headers describe shared hardware facts across the family
- device-level headers describe one target device without requiring JSON-side inference
- reflection headers under `generated/*.hpp` remain available for tooling, smoke, and inspection
- runtime profile headers describe schema/backend dispatch without family parsing in Alloy
- reports describe whether the emitted contract is complete enough for Alloy to consume directly

## Alloy-Owned Behavior

The Alloy runtime owns:

- typed `connect()` APIs
- compile-time and runtime connection selection behavior
- ownership and claims such as `take()`, `claim()`, or token models
- board initialization policy
- peripheral driver APIs such as `uart`, `spi`, `i2c`, `gpio`, or `dma`
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
