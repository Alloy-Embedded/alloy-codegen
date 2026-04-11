## ADDED Requirements

### Requirement: Header-Sourced Connectivity Fits the Existing IR
The canonical IR SHALL represent connectivity extracted from NXP SDK headers without introducing
an NXP-specific schema fork.

#### Scenario: IMXRT1060 connectivity normalizes into the existing schema
- **WHEN** `nxp/imxrt1060` devices are normalized from SDK headers and SVDs
- **THEN** the resulting canonical documents SHALL conform to the same IR schema family used by
  existing ST and Microchip support
- **AND** no NXP-only structural branch SHALL be required just to represent SDK-derived pinmux
  data
