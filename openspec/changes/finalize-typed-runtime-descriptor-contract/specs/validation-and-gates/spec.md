## ADDED Requirements

### Requirement: Publication SHALL Require Fully Typed Foundational Runtime Schemas

Publication SHALL fail for a foundational family when any runtime-owned backend schema still
depends on string parsing or handwritten register-field knowledge in Alloy.

#### Scenario: Foundational family remains partially textual
- **WHEN** validation detects that a foundational runtime-owned schema lacks typed field
  descriptors or executable typed operation targets
- **THEN** the family fails validation
- **AND** publication is blocked

### Requirement: Validation SHALL Verify Typed Binding Completeness

Validation SHALL verify that interrupt, DMA, clock, reset, selector, register, and field
bindings are complete and internally consistent for foundational families.

#### Scenario: Peripheral binding is incomplete
- **WHEN** a foundational peripheral instance is missing a required typed binding or field
  descriptor for its runtime schema
- **THEN** validation reports the missing domain as an error
- **AND** the family is not publishable
