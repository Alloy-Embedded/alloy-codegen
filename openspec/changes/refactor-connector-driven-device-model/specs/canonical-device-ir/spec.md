## ADDED Requirements

### Requirement: Canonical IR Separates IP Blocks from Peripheral Instances
The canonical IR SHALL model reusable IP block definitions separately from device-local
peripheral instances.

#### Scenario: A vendor family reuses the same IP version across multiple instances
- **WHEN** two or more devices expose peripherals with the same `ip_name` and `ip_version`
- **THEN** the canonical IR SHALL represent the shared capabilities and signal model in an
  `ip_block` definition
- **AND** each concrete peripheral instance SHALL reference that block rather than duplicating the
  capability facts inline

### Requirement: Canonical IR Uses a Route-Driven Connector Model
The canonical IR SHALL represent pin-to-peripheral connectivity as route candidates, route
requirements, route operations, and valid connection groups rather than as AF-centric pin facts
alone.

#### Scenario: Different vendors encode the same connection using different routing schemes
- **WHEN** one family expresses a UART TX route as an alternate function, another as a PIO matrix
  selection, and another as a mux-plus-daisy pair
- **THEN** the canonical IR SHALL normalize all three into the same abstract connector model
- **AND** the vendor-specific details SHALL remain represented as descriptor data and provenance,
  not hidden in emitter logic

### Requirement: Canonical IR Models Complete Package and Pin Topology
The canonical IR SHALL model package variants, physical package pads, bonded pins, and pin
constraints strongly enough to support package-aware connection validation.

#### Scenario: A device package omits or constrains a pin that exists in another variant
- **WHEN** a family has multiple package variants with different bonded pins or pad constraints
- **THEN** the canonical IR SHALL record package-local pad identity and bonding state
- **AND** it SHALL expose the associated pin constraints needed to reject invalid connections

### Requirement: Canonical IR Models System Descriptor Domains
The canonical IR SHALL model interrupts, vector slots, memory regions, startup descriptors,
clock/reset/enable descriptors, and DMA route descriptors as first-class domains.

#### Scenario: Startup behavior must be built from descriptors without handwritten device tables
- **WHEN** a published device artifact is consumed by Alloy for startup integration
- **THEN** the canonical IR SHALL already contain the vector, memory, and startup data needed for
  descriptor emission
- **AND** those facts SHALL remain separate from the runtime startup algorithm implemented in Alloy

### Requirement: Canonical IR Models Capability Descriptors
The canonical IR SHALL represent peripheral capability descriptors in a way that supports both
IP-version-wide facts and instance-specific overrides.

#### Scenario: A peripheral class supports a feature in one IP version but not another
- **WHEN** a capability such as FIFO support, CTS/RTS, DMAMUX routing, or channel count varies by
  IP version or instance binding
- **THEN** the canonical IR SHALL model that capability explicitly
- **AND** emitters and Alloy consumers SHALL be able to read it without inferring behavior from
  instance names alone
