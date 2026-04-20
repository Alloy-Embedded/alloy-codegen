## Context

We solved the "stringly typed" problem, but not the "table-shaped runtime" problem.

Today the generated outputs are still optimized around reflective completeness:

- family-wide connector tables
- family-wide clock tables
- device-wide register and field inventories
- typed ids and refs that still assume table lookup as the default usage pattern

That is useful for:

- validation
- report generation
- smoke consumers
- debugging and inspection
- future tooling

It is not the right shape for the final runtime path.

The runtime path should instead look like:

- compile-time selection of one peripheral instance
- compile-time selection of one legal route
- compile-time emission of a minimal sequence of register writes
- dead-stripping of everything not referenced by the chosen board / app

## Goals

- let `alloy` compile GPIO/UART/SPI/I2C bring-up down to code equivalent to direct register use
- preserve rich reflection outputs without forcing the runtime to include them
- keep foundational families (`st/stm32g0`, `st/stm32f4`, `microchip/same70`,
  `nxp/imxrt1060`) on one shared runtime-lite contract

## Non-Goals

- removing reflection tables from the repo entirely
- eliminating JSON metadata or validation reports
- forcing every possible query to become a template metaprogram

## Decision: Two Explicit Generated Contracts

`alloy-devices` SHALL publish two generated C++ products.

### Reflection Contract

Purpose:

- validation
- smoke compilation
- tooling
- debugging
- optional offline inspection

Examples:

- `generated/runtime_refs.hpp`
- `generated/runtime_semantics.hpp`
- `generated/connector_tables.hpp`
- `generated/clock_tree_lite.hpp`
- `generated/rcc_map.hpp`
- `generated/interrupt_map.hpp`
- `generated/dma_map.hpp`
- `generated/memory_map.hpp`
- `generated/package_map.hpp`

The reflection contract MAY remain table-oriented.

### Runtime-Lite Contract

Purpose:

- hot-path runtime consumption by `alloy`
- compile-time route resolution
- zero-overhead peripheral bring-up

The runtime-lite contract SHALL avoid family-wide scans as the expected usage model.

## Decision: Runtime-Lite Is Generated As Specializations And Packs

The runtime-lite contract SHALL favor:

- per-instance trait specializations
- per-route trait specializations
- `constexpr` packs of operations for one resolved route
- direct register and field refs
- compact enums and ids

It SHALL avoid requiring the runtime to iterate across family tables to rediscover:

- which peripheral is selected
- which register/field implements a route
- which clock gate/reset belongs to an instance
- which route ops apply to a chosen binding

## Decision: Hot Path Must Not Depend On Reflection Tables

The following runtime use cases SHALL be expressible using runtime-lite artifacts only:

- `gpio` instance enable / mode setup
- `uart` open on a chosen connector
- `spi` open on a chosen connector
- `i2c` open on a chosen connector
- direct peripheral base / register / field access used by foundational drivers

The reflection contract MAY still be compiled by smoke tests, but it SHALL NOT be required by
the production path of those drivers.

## Decision: Separate Generated Layout

The generated tree SHALL make the split obvious.

Target layout:

```text
generated/
  reflection/
    runtime_refs.hpp
    runtime_semantics.hpp
    connector_tables.hpp
    clock_tree_lite.hpp
    ...
  runtime/
    types.hpp
    clock_bindings.hpp
    routes/
      <peripheral-class>.hpp
    devices/<device>/
      peripheral_instances.hpp
      pins.hpp
      registers.hpp
      register_fields.hpp
      startup.hpp
```

The exact filenames may differ, but the contract split SHALL be explicit and stable.

## Decision: Route Lowering Produces Minimal Operation Packs

For each legal connector route, codegen SHALL emit a compact runtime-lite representation that
lets the runtime apply the route without searching the family graph at runtime.

Examples of acceptable runtime-lite shapes:

- `route_traits<PinId, PeripheralId, SignalId>`
- `connector_traits<Connector>`
- `constexpr std::array<RouteOp, N>` attached to one route specialization
- field-write helpers emitted as template aliases or typed `constexpr` descriptors local to the
  chosen route

The important rule is not the exact syntax; it is that the runtime SHALL not need a generic
"find candidate by scanning table" path for normal usage.

## Decision: Validation Must Enforce Zero-Overhead Shape

The publish gate SHALL reject foundational families if:

- runtime-owned drivers still require reflection headers in their hot path contract
- runtime-lite artifacts are missing for foundational peripheral classes
- runtime-lite artifacts still require family-wide scans to resolve one instance or route

## Migration Order

1. Define the contract split in OpenSpec
2. Emit runtime-lite headers for foundational families while keeping reflection outputs intact
3. Add validation gates proving runtime-lite completeness
4. Republish `alloy-devices`
5. Migrate `alloy` to runtime-lite consumption
6. Demote reflection headers to tooling / smoke / optional introspection only
