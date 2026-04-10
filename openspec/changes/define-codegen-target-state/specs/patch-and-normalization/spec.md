## ADDED Requirements

### Requirement: Complete Hardware-Domain Normalization
The normalize stage SHALL produce a canonical model that covers every hardware domain required for
publishable Alloy device support.

#### Scenario: Foundational domains are normalized into canonical fields
- **WHEN** a publishable-candidate family is normalized successfully
- **THEN** the resulting canonical model SHALL cover at least IP blocks and versions, devices,
  packages, pins, connectivity, interrupts, memory, clocks, DMA, startup descriptors, and
  documentation references

#### Scenario: No publishability-critical domain remains opaque
- **WHEN** normalization completes for a family that is being considered publishable
- **THEN** no publishability-critical domain SHALL remain represented only as a vendor-specific
  opaque blob that downstream stages must reinterpret

### Requirement: IP-Version-First Peripheral Modeling
The normalize stage SHALL model peripherals in terms of both instance identity and IP-version
identity.

#### Scenario: Peripheral instances reference shared IP definitions
- **WHEN** two devices expose peripherals that share the same vendor IP version
- **THEN** the canonical model SHALL be able to represent that shared IP definition separately from
  the device-local peripheral instance

#### Scenario: Emitters do not infer IP versions ad hoc
- **WHEN** generated descriptors are emitted for a peripheral
- **THEN** the emitter SHALL read the canonical IP-version information directly
- **AND** it SHALL NOT infer version identity from family names or emitter-local heuristics

### Requirement: Explicit Multi-Source Merge Rules
The normalize stage SHALL merge multiple source products into one canonical model through explicit,
tested rules.

#### Scenario: Repository, pack, and SDK data merge deterministically
- **WHEN** normalization combines connectivity data, register data, and package data from multiple
  source products
- **THEN** the merge rules SHALL produce one deterministic canonical result
- **AND** provenance SHALL identify which source supplied each normalized fact
