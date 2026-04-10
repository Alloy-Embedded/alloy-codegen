## MODIFIED Requirements

### Requirement: Source Scope Control
The source stage SHALL support scoped execution by vendor, family, and device.
The system SHALL resolve the vendor and family for a given device name automatically
from the device registry when they are not provided explicitly.

#### Scenario: Restrict source fetch to one family
- **WHEN** the user requests source ingestion for a specific family
- **THEN** the system SHALL fetch only the sources needed for that family
- **AND** it SHALL NOT require a full multi-vendor fetch to bootstrap one family

#### Scenario: Auto-resolve family from device name
- **WHEN** the user specifies only a device name (e.g. `--device stm32f401re`)
- **THEN** the system SHALL resolve the vendor and family from the device registry
- **AND** it SHALL NOT require the user to also pass `--vendor` or `--family`

#### Scenario: Reject unknown devices
- **WHEN** the user specifies a device name that is not in any registered family
- **THEN** the system SHALL raise an `UnsupportedScopeError` listing all supported devices

## ADDED Requirements

### Requirement: Multi-Family Device Registry
The system SHALL maintain an explicit device registry that maps `(vendor, family)` pairs
to their supported device names.

#### Scenario: All registered families are accessible to the pipeline
- **WHEN** the pipeline scope is resolved for any registered `(vendor, family)` pair
- **THEN** `resolved_device_names()` SHALL return only the devices belonging to that family
- **AND** adding a new family to the registry SHALL not alter the resolved device set of
  any existing family

#### Scenario: Registry is the single source of truth for supported devices
- **WHEN** the scope validator checks whether a device is supported
- **THEN** it SHALL consult the device registry exclusively
- **AND** it SHALL NOT compare device names against hardcoded module-level constants
