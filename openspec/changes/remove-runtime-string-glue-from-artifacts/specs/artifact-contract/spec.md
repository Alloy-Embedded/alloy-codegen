## ADDED Requirements

### Requirement: Typed Peripheral Instance Contract
The emitted `generated/devices/<device>/peripheral_instances.hpp` SHALL expose only typed
primary runtime fields for bindings, clock/reset references, and capability coverage.

#### Scenario: Peripheral instance header avoids CSV/runtime strings
- **WHEN** a device is emitted
- **THEN** each peripheral instance descriptor exposes typed offsets/counts and typed binding
  references
- **AND** it does not require CSV strings or RCC signal strings for runtime execution

### Requirement: Typed Connector Runtime Contract
The emitted `generated/connector_tables.hpp` SHALL expose route requirements and route
operations with typed domains and ids as the primary runtime contract.

#### Scenario: Connector tables are executable without parsing strings
- **WHEN** Alloy consumes route requirements or operations
- **THEN** it can execute them from typed ids, domains, and numeric values alone
- **AND** any human-readable strings are clearly secondary diagnostics

### Requirement: Typed Clock Reset Contract
The emitted family-level clock/reset contract SHALL publish typed gate/reset bindings rather
than raw textual signals as the primary runtime API.

#### Scenario: Family clock header is typed
- **WHEN** a foundational family is emitted
- **THEN** its clock/reset header publishes typed references to gates and resets
- **AND** the runtime does not need to parse an RCC/PMC signal string to enable or reset a
  peripheral
