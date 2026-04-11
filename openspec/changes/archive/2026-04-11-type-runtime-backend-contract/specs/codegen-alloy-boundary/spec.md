## ADDED Requirements

### Requirement: Runtime Boundary Avoids Family Parsing

The `alloy-devices` contract SHALL expose enough typed runtime descriptors that Alloy does not
need family-specific parsing of register targets, pinmux targets, or handwritten offsets for
foundational families.

#### Scenario: Alloy consumes runtime descriptors without family parsing

- **WHEN** Alloy consumes the foundational artifact contract
- **THEN** backend dispatch can be selected from generated schema descriptors
- **AND** register offsets required by runtime-owned subsystems are available in generated device descriptors
