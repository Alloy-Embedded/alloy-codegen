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
  - `generated/peripherals/*.hpp`
  - `generated/ip/*.hpp`
  - `generated/signal_map.hpp`
  - `generated/connector_tables.hpp`
  - `generated/rcc_map.hpp`
  - `generated/dma_map.hpp`
  - `generated/interrupt_map.hpp`
  - `generated/memory_map.hpp`
  - `generated/package_map.hpp`
  - `generated/clock_tree_lite.hpp`
  - `generated/devices/<device>/register_map.hpp`
  - `generated/devices/<device>/pin_functions.hpp`
  - `generated/devices/<device>/startup.cpp`
  - `generated/devices/<device>/startup_descriptors.hpp`
  - `generated/devices/<device>/startup_vectors.cpp`
- reports:
  - `reports/validation-report.json`
  - `reports/publication-record.json`
  - `reports/publication-summary.json`

Those files may describe:

- addresses
- registers and IP versions
- pins, packages, and constraints
- connector candidates, groups, requirements, and operations
- interrupts, memories, startup descriptors, clocks, resets, and DMA routes
- validation and publication status

## Alloy-Owned Behavior

The Alloy runtime owns:

- typed `connect()` APIs
- compile-time and runtime connection selection behavior
- ownership and claims such as `take()`, `claim()`, or token models
- board initialization policy
- peripheral driver APIs such as `uart`, `spi`, `i2c`, `gpio`, or `dma`
- reset-handler behavior and startup algorithms

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
