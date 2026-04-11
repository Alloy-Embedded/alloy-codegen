## ADDED Requirements

### Requirement: Published family trees SHALL expose the full descriptor-first contract

The system SHALL publish each supported `(vendor, family)` under a descriptor-first family tree
that includes family metadata, generated descriptor artifacts, device-scoped descriptor entrypoints,
and validation reports.

#### Scenario: Foundational family publishes complete artifact roots
- **WHEN** the pipeline publishes a foundational family to `alloy-devices`
- **THEN** the family root SHALL contain `artifact-manifest.json`
- **AND** it SHALL contain `metadata/`, `generated/`, and `reports/` subtrees
- **AND** each subtree SHALL include the required artifact families defined by the active contract

### Requirement: Device-scoped C++ descriptor entrypoints SHALL exist

The system SHALL emit device-scoped generated C++ entrypoints that the Alloy runtime can include
directly without inferring publishability-critical device facts from JSON metadata.

Required device-scoped descriptors are:

- `generated/devices/<device>/device_descriptor.hpp`
- `generated/devices/<device>/pins.hpp`
- `generated/devices/<device>/peripheral_instances.hpp`
- `generated/devices/<device>/capability_overlays.hpp`
- `generated/devices/<device>/register_map.hpp`
- `generated/devices/<device>/startup_descriptors.hpp`
- `generated/devices/<device>/startup_vectors.cpp`

#### Scenario: Device-scoped descriptor entrypoints are emitted
- **WHEN** the pipeline emits artifacts for a supported device
- **THEN** all required device-scoped descriptor entrypoints SHALL be materialized under
  `generated/devices/<device>/`

### Requirement: Publishability-critical facts SHALL have generated C++ parity

The system SHALL make publishability-critical hardware facts consumable from the generated C++
contract, not only from machine-readable JSON metadata.

Publishability-critical facts include:

- selected package identity
- pin and bonding facts
- peripheral instance identity and base placement
- package- or instance-scoped capability overlays
- references into connector, interrupt, memory, clock/reset, and startup descriptor data

#### Scenario: Alloy consumes generated C++ without metadata parsing
- **WHEN** the Alloy smoke consumer is compiled against a published foundational family
- **THEN** it SHALL be able to include generated descriptor headers for publishability-critical
  facts
- **AND** it SHALL NOT require parsing metadata JSON to obtain those facts

### Requirement: Active contract documentation SHALL match emitted artifacts

The system SHALL keep the active artifact-contract documentation synchronized with the emitted
artifact tree.

Retired bootstrap-era artifact names SHALL NOT appear in active contract documentation once they
are no longer emitted.

#### Scenario: Documentation rejects retired artifact names
- **WHEN** active documentation is validated against the emitted contract
- **THEN** references to retired artifact names SHALL fail validation
- **AND** omission of required active artifact families SHALL fail validation
