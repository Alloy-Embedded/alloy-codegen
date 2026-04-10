## ADDED Requirements

### Requirement: Reproducible Patch Layer
The system SHALL correct upstream source defects through an explicit, reproducible patch
layer rather than hidden fixes in emitters or handwritten downstream code.

#### Scenario: Apply reviewed patches deterministically
- **WHEN** the patch stage runs on fetched source inputs
- **THEN** it SHALL apply only the declared patch set for the targeted scope
- **AND** it SHALL record which patches were applied in a patch manifest
- **AND** rerunning the patch stage with the same inputs and patch set SHALL produce
  byte-identical patched outputs

#### Scenario: Patch failures stop normalization
- **WHEN** a declared patch cannot be applied cleanly
- **THEN** the patch stage SHALL fail clearly
- **AND** the normalize stage SHALL NOT proceed on partially patched inputs

### Requirement: Vendor-Specific Normalization
The system SHALL normalize patched vendor-specific data into a common representation without
leaking vendor naming or raw format assumptions into downstream emitters.

#### Scenario: Normalize vendor-specific input into canonical concepts
- **WHEN** the normalize stage runs for a supported device
- **THEN** it SHALL map vendor-specific terms into canonical concepts for devices, pins,
  IP blocks, interrupts, DMA, RCC, and memory
- **AND** downstream stages SHALL consume canonical normalized data rather than raw vendor
  documents

#### Scenario: Preserve provenance during normalization
- **WHEN** a canonical field is derived from upstream source data
- **THEN** the normalized output SHALL retain provenance linking that field back to source
  origin and any applied patch identity
