## ADDED Requirements

### Requirement: No String Glue in Foundational Runtime Headers
Validation SHALL fail for a foundational family when its runtime-facing headers still depend on
CSV payloads or textual signal fields as primary executable contract.

#### Scenario: Foundational family still emits CSV payload
- **WHEN** a foundational family emits CSV capability or interrupt payloads in a primary
  runtime struct
- **THEN** validation fails
- **AND** publish is blocked

### Requirement: No Text Parsing Required for Runtime Route Execution
Validation SHALL fail when a foundational route requirement or route operation still requires
text parsing to determine target or value semantics.

#### Scenario: Route operation only identifies its target textually
- **WHEN** a route operation lacks sufficient typed ids or typed refs
- **THEN** validation fails
- **AND** the family is not publishable
