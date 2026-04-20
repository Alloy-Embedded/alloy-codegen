## Why

The published `runtime-lite` contract is now good enough to identify devices, pins, routes,
registers, fields, clocks, and resets without reflection-table lookups at runtime. That closed
the string and table-scan problem, but it did not close the driver-semantics problem.

The Alloy runtime still needs schema-specific semantic access points for foundational drivers such
as `gpio`, `uart`, `i2c`, and `spi`. Today those drivers need facts like:
- which register/field enables a UART
- which field selects GPIO mode for a given line
- which status field means TX-ready or RX-ready
- which control fields map to stop bits, parity, transfer enable, and so on

Those semantics are present only indirectly in raw register inventories and route operations. If
the runtime consumes the current `runtime-lite` contract directly, it still has to rebuild driver
knowledge in handwritten C++ using register-name conventions or hardcoded offsets. That recreates
the exact scaling and maintenance problem the architecture is supposed to eliminate.

## What Changes

- add schema-scoped driver semantic traits to the `runtime-lite` contract for foundational driver
  classes: `gpio`, `uart`, `i2c`, and `spi`
- emit typed per-instance semantic aliases that map an instance id to the exact `RegisterId`,
  `FieldId`, and operation refs needed by the driver hot path
- keep reflection artifacts available for tooling and validation, but explicitly exclude them from
  the normal driver path
- add publish and validation gates so a family cannot publish as runtime-ready unless foundational
  driver semantics are emitted for every publishable foundational instance
- update boundary documentation to define driver semantic traits as the required hot-path contract

## Impact

- Affected specs: `artifact-contract`, `validation-and-gates`, `codegen-alloy-boundary`,
  `vendor-admission`
- Affected code: IR-to-emitter path for runtime-lite, artifact validation, consumer smoke coverage,
  publish gating, artifact layout docs
