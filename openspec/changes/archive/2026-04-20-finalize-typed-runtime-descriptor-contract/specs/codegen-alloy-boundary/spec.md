## ADDED Requirements

### Requirement: Alloy Boundary SHALL Be Schema-Dispatched and Typed

The generated contract between `alloy-devices` and Alloy SHALL be consumable through backend
schema dispatch and typed descriptor execution, not through vendor or family name inference.

#### Scenario: Alloy adds a new family that reuses an existing schema
- **WHEN** a newly supported family reuses an already published runtime backend schema
- **THEN** Alloy can consume the generated descriptors without adding family-specific parsing
  or handwritten offsets

### Requirement: Generated Contract SHALL Be Sufficient for MMIO Addressing

The generated contract SHALL provide enough typed information for Alloy to resolve runtime
MMIO register and field addressing without handwritten offsets or bit definitions.

#### Scenario: Alloy backend performs a runtime-owned register write
- **WHEN** an Alloy backend needs to write a runtime-owned register field
- **THEN** it can obtain the register base, register offset, field offset, and width from the
  generated descriptors alone
- **AND** it does not need handwritten register or field constants
