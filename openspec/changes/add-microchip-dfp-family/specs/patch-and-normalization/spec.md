## ADDED Requirements

### Requirement: Composite ATDF and SVD Normalization
The normalize stage SHALL support Microchip families whose canonical device model requires
merging ATDF topology data with SVD register data.

#### Scenario: ATDF and SVD merge into one canonical device model
- **WHEN** a `microchip/same70` device is normalized
- **THEN** the normalizer SHALL derive package, pins, signals, peripheral topology, and device
  identity from ATDF where appropriate
- **AND** it SHALL derive register layout, peripheral base addresses, and interrupt metadata from
  SVD where appropriate
- **AND** it SHALL merge both sources into one canonical IR document for that device

#### Scenario: Vendor naming is normalized before emit
- **WHEN** Microchip-specific names such as `PIO`, `PMC`, or `XDMAC` are encountered during
  normalization
- **THEN** the normalizer SHALL map them into canonical concepts before validation and emission
- **AND** emitters SHALL NOT need to interpret raw vendor naming to recover semantics

### Requirement: Reviewed Corrections for DFP Families
The patch layer SHALL remain the only reviewed path for correcting missing or ambiguous
Microchip family semantics.

#### Scenario: Pack gaps are corrected through family or device patches
- **WHEN** the DFP leaves required canonical relationships incomplete or ambiguous
- **THEN** reviewed family or device patch data MAY supplement those relationships
- **AND** the patch manifest SHALL record that supplementation explicitly

#### Scenario: Publish is blocked when critical semantics are still unresolved
- **WHEN** connectivity-critical domains such as package pinout, clock ownership, or DMA routing
  remain unresolved after DFP data and reviewed patches are applied
- **THEN** normalization MAY still emit draft outputs
- **AND** publication SHALL remain blocked until validation closes those gaps
