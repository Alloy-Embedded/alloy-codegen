## ADDED Requirements

### Requirement: Full Canonical Hardware Model
The canonical IR SHALL be rich enough to answer future Alloy hardware-integration questions
without consulting raw vendor sources.

#### Scenario: Alloy-critical questions are answerable from IR
- **WHEN** Alloy needs device descriptors for pin compatibility, peripheral identity, startup
  vectors, interrupt routing, clock enable relationships, or DMA requests
- **THEN** the required facts SHALL be available in the canonical IR or directly emitted
  descriptors derived from it

#### Scenario: Packages and physical pins are represented explicitly
- **WHEN** a device has multiple package variants or package-specific pin exposure
- **THEN** the canonical IR SHALL model package identity, physical pin positions, and package-pin
  membership explicitly rather than collapsing them into one undifferentiated pin list

### Requirement: Complete Provenance
The canonical IR SHALL retain provenance for normalized hardware facts at a granularity useful for
validation and debugging.

#### Scenario: A normalized field is traceable to source and patch
- **WHEN** a user or tool inspects a normalized field that influences emitted artifacts
- **THEN** the system SHALL be able to identify which logical source input and which reviewed patch
  produced or modified that field

### Requirement: Cross-Vendor IR Reuse
The same IR schema family SHALL be reused across the foundational vendor set.

#### Scenario: Three vendor shapes share one schema family
- **WHEN** ST, Microchip, and NXP foundational families normalize successfully
- **THEN** they SHALL do so through the same IR schema family
- **AND** no vendor-specific schema fork SHALL be introduced just to admit a foundational vendor
