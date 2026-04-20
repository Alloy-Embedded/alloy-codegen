## MODIFIED Requirements

### Requirement: Codegen/Runtime Boundary
`alloy-codegen` SHALL publish the complete hardware contract required by the Alloy foundational
driver hot path. Alloy SHALL NOT be required to reconstruct schema semantics from raw register
inventories, reflection tables, or register-name conventions.

#### Scenario: Alloy consumes DMA through runtime-lite
- **WHEN** Alloy configures a DMA route for a published foundational device
- **THEN** the required controller slot, request selector, controller-local selector, and
  register/field semantics SHALL already be published by `alloy-codegen`
- **AND** Alloy SHALL NOT infer DMA mux or selector values from request-line names

