## ADDED Requirements

### Requirement: Cross-Vendor IR Compatibility
The canonical IR schema SHALL accommodate Microchip DFP-backed families without introducing a
vendor-specific schema fork.

#### Scenario: SAME70 normalizes into the existing canonical schema
- **WHEN** a `microchip/same70` device is normalized successfully
- **THEN** the output SHALL conform to the same `CanonicalDeviceIR` schema family used by ST
  devices
- **AND** adding Microchip support SHALL NOT require a Microchip-only IR document shape

#### Scenario: Vendor-specific terms remain data, not schema
- **WHEN** a normalized Microchip field depends on an upstream vendor term or alias
- **THEN** that vendor detail SHALL be carried through provenance, identifiers, or canonicalized
  field values
- **AND** the schema SHALL NOT grow vendor-specific structural branches solely to represent
  Microchip naming
