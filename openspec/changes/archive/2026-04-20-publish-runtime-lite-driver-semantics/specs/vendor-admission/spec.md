## MODIFIED Requirements

### Requirement: Foundational Vendor Admission
A vendor/family SHALL NOT count as foundationally admitted unless its foundational runtime-owned
instances publish complete runtime-lite driver semantic traits for the supported foundational
driver classes.

#### Scenario: Vendor lacks foundational driver semantics
- **WHEN** a family publishes runtime-lite facts but omits required semantic traits for
  foundational drivers
- **THEN** the vendor admission gate SHALL remain incomplete

#### Scenario: Vendor satisfies foundational driver semantics
- **WHEN** the family publishes complete semantic trait packs for foundational drivers
- **THEN** the family MAY count toward foundational vendor admission
