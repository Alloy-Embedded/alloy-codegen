## ADDED Requirements

### Requirement: Expanded peripheral coverage follows the same validation standard

New peripheral families MUST not bypass the generator's semantic and validation moat.

#### Scenario: New runtime peripheral families require capability and verification coverage
- **WHEN** a new runtime peripheral family is added
- **THEN** publication requires formal capability coverage and consumer verification coverage
- **AND** the family is not considered complete with schema-only or parser-only support

