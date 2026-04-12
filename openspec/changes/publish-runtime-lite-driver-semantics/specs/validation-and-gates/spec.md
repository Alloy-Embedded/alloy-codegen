## MODIFIED Requirements

### Requirement: Publication SHALL Enforce Runtime Completeness
Families SHALL only publish as runtime-ready when the emitted hot-path contract is complete for
foundational driver classes.

#### Scenario: Foundational semantics are missing
- **WHEN** a foundational runtime-owned peripheral instance lacks emitted driver semantic traits
- **THEN** validation SHALL fail
- **AND** publish SHALL be blocked

#### Scenario: Foundational semantics are complete
- **WHEN** every publishable foundational instance has the required semantic trait pack for its
  driver class
- **THEN** validation MAY pass this gate
- **AND** publish MAY continue
