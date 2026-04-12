## ADDED Requirements

### Requirement: Vendor Admission Requires Typed Runtime Contract Reuse
New foundational-family admission SHALL require reuse of the typed runtime-ref domains and
typed runtime header contract, unless a localized new schema is explicitly added and validated.

#### Scenario: New family attempts to publish with string glue
- **WHEN** a new family or vendor publishes foundational runtime artifacts
- **THEN** vendor admission fails if it depends on raw signal strings or CSV payloads as
  primary runtime contract
