## ADDED Requirements

### Requirement: Normalization Produces Generic Connector Graphs
Normalization SHALL convert vendor-specific pinmux and routing inputs into the canonical connector
graph model.

#### Scenario: ST, Microchip, and NXP expose different source encodings
- **WHEN** the pipeline ingests AF-oriented XML, pack-derived ATDF data, or SDK header macros
- **THEN** normalization SHALL emit the same connector graph abstractions for all of them
- **AND** no vendor-specific routing meaning SHALL remain available only in opaque raw-source
  strings

### Requirement: Normalization Resolves Canonical Signal Identity Explicitly
Normalization SHALL produce canonical peripheral signal identities and SHALL use reviewed patches
to resolve naming mismatches rather than emitter fixups.

#### Scenario: Source repositories disagree on signal naming
- **WHEN** SVD, pack metadata, or SDK pin headers refer to the same hardware signal using
  different names
- **THEN** normalization SHALL canonicalize those identities before emission
- **AND** the resolution SHALL remain traceable to source and patch provenance

### Requirement: Normalization Closes Descriptor Domains Before Emit
Normalization SHALL populate connector, capability, package, interrupt, memory, startup,
clock/reset, and DMA domains before emission.

#### Scenario: A family has incomplete clock or startup facts
- **WHEN** normalization cannot produce a publishability-critical descriptor domain from sources
  plus reviewed patches
- **THEN** the missing domain SHALL remain visible as a validation failure
- **AND** emitters SHALL NOT silently invent the missing facts
