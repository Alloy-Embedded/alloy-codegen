## ADDED Requirements

### Requirement: Emitters Publish Connector and IP-Version Descriptors
The emit stage SHALL publish connector tables, route descriptors, capability descriptors, and
IP-version descriptor artifacts from the validated canonical IR.

#### Scenario: Alloy consumes published descriptors to resolve a peripheral connection
- **WHEN** Alloy needs to decide whether a requested set of pins can realize a peripheral signal
  configuration
- **THEN** the published artifacts SHALL already expose the connector candidates, connection
  groups, requirements, and route operations needed for that decision
- **AND** the same family publication SHALL expose the referenced IP-version capability descriptors

### Requirement: Emitters Publish Complete System Descriptors
The emit stage SHALL publish interrupt, memory, package, DMA, clock/reset, and startup descriptor
artifacts for each publishable family.

#### Scenario: Startup data is published without startup behavior
- **WHEN** a device family is emitted for publication
- **THEN** the emitted artifact set SHALL contain startup vectors and startup descriptors as data
  artifacts
- **AND** it SHALL NOT embed the runtime startup algorithm that belongs in Alloy

### Requirement: Artifact Layout Is Descriptor-First and Self-Describing
The published artifact layout SHALL organize descriptor artifacts under `metadata/`, `generated/`,
and `reports/`, plus a family-root manifest.

#### Scenario: A consumer reads the published tree without access to the source checkout
- **WHEN** Alloy or a tooling consumer receives a published family tree from `alloy-devices`
- **THEN** the tree SHALL contain the metadata, generated descriptors, reports, and manifest
  needed to understand what was published
- **AND** the consumer SHALL NOT need raw vendor sources to interpret the artifact categories
