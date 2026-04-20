# codegen-alloy-boundary Specification

## Purpose
TBD - created by archiving change eliminate-runtime-strings-from-cpp-contract. Update Purpose after archive.
## Requirements
### Requirement: Alloy Boundary SHALL Depend On Typed Runtime C++ Only

The contract between `alloy-devices` and Alloy SHALL allow the runtime to execute entirely
from typed generated C++ descriptors.

#### Scenario: Alloy backend executes a schema without string glue
- **WHEN** Alloy resolves pins, routes, clocks, resets, interrupts, DMA, memories, startup
  actions, or register-field operations
- **THEN** it can do so using generated typed C++ ids and refs alone
- **AND** no string comparison, string parsing, or handwritten semantic lookup is required

### Requirement: Human Labels SHALL Live Outside The Runtime C++ Boundary

Human-readable labels SHALL not be part of the runtime C++ boundary between `alloy-devices`
and Alloy.

#### Scenario: Developer wants diagnostics or inspection data
- **WHEN** generated artifacts need human-readable labels
- **THEN** those labels are published in JSON metadata or reports
- **AND** the runtime C++ contract remains fully typed

### Requirement: Alloy Runtime SHALL Target Runtime-Lite Artifacts

The documented boundary between `alloy-codegen` and `alloy` SHALL state that normal runtime
consumption targets the runtime-lite contract, while reflection artifacts remain available for
tooling, validation, smoke compilation, and debugging.

#### Scenario: Boundary doc describes runtime-lite as the hot-path contract

- **WHEN** the boundary documentation is updated for this change
- **THEN** it explicitly identifies runtime-lite artifacts as the intended hot-path contract for
  `alloy`
- **AND** it identifies reflection artifacts as non-hot-path support products

### Requirement: User-facing configuration layers build on the runtime contract

Any higher-level generator UX or configuration surface MUST build on the same typed runtime device
model used by Alloy.

#### Scenario: Recipes and configurator outputs do not create a second device model
- **WHEN** the generator emits configuration recipes, examples, or configurator outputs
- **THEN** those outputs are derived from the typed runtime contract
- **AND** they do not introduce a parallel handwritten or reflection-only device model

