## ADDED Requirements

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
