## MODIFIED Requirements

### Requirement: Codegen/Runtime Boundary
`alloy-codegen` SHALL publish the complete hardware contract required by the Alloy foundational
driver hot path. Alloy SHALL NOT be required to reconstruct schema semantics from raw register
inventories, reflection tables, or register-name conventions.

#### Scenario: Alloy consumes runtime-lite in the hot path
- **WHEN** Alloy configures a foundational driver instance
- **THEN** the required register, field, clock, reset, and route semantics SHALL already be
  published as typed runtime-lite facts or typed driver-semantic traits
- **AND** Alloy SHALL NOT need to scan reflection tables or infer semantic meaning from strings
