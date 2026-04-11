## ADDED Requirements

### Requirement: Vendor Admission SHALL Depend on Typed Schema Reuse

Admission of a new family or vendor SHALL require either reuse of an already published typed
runtime backend schema or the introduction of a new localized schema contract that avoids
family-name parsing in Alloy.

#### Scenario: New family reuses an existing runtime schema
- **WHEN** a candidate family maps to already published runtime backend schemas
- **THEN** vendor admission succeeds without requiring Alloy runtime changes outside schema
  dispatch tables

#### Scenario: New family requires family-specific runtime parsing
- **WHEN** a candidate family can only be consumed by adding family-name checks or string
  parsing in Alloy
- **THEN** vendor admission fails until the contract is expressed as typed schema descriptors
