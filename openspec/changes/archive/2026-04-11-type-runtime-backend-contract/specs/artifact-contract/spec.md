## ADDED Requirements

### Requirement: Runtime Profiles Header

The generated artifact contract SHALL publish family-scoped runtime backend profile descriptors.

#### Scenario: Family artifacts expose runtime profiles

- **WHEN** `emit` runs for a publishable family
- **THEN** the family tree includes `generated/runtime_profiles.hpp`
- **AND** the header enumerates backend schema identifiers required by the runtime

### Requirement: Peripheral Instance Runtime Header

The generated artifact contract SHALL publish device-scoped peripheral instance descriptors for
runtime consumption.

#### Scenario: Device artifacts expose peripheral instances

- **WHEN** `emit` runs for a publishable device
- **THEN** the device tree includes `generated/devices/<device>/peripheral_instances.hpp`
- **AND** each runtime-owned peripheral instance exposes base address, IP identity, and backend schema

### Requirement: Register Map Offsets

The generated artifact contract SHALL publish per-register offsets in the device-scoped register
map header.

#### Scenario: Register map includes normalized register offsets

- **WHEN** `emit` generates `generated/devices/<device>/register_map.hpp`
- **THEN** the header includes typed register descriptors
- **AND** each descriptor includes the peripheral owner and byte offset

### Requirement: Typed Connector Operations

The generated artifact contract SHALL publish route operations with typed runtime fields.

#### Scenario: Connector tables avoid free-form runtime parsing

- **WHEN** `emit` generates `generated/connector_tables.hpp`
- **THEN** route operations include typed schema and subject fields
- **AND** the runtime no longer depends on parsing target strings such as register paths
