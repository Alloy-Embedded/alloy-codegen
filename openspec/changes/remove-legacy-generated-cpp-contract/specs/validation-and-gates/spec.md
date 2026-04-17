## MODIFIED Requirements

### Requirement: Consumer verification validates only the supported published C++ contract

Consumer verification MUST compile against the supported runtime contract, not against legacy
reflection-oriented C++ headers.

#### Scenario: Runtime smoke is the canonical published smoke
- **WHEN** consumer verification runs for a foundational family
- **THEN** it compiles the runtime contract smoke consumer
- **AND** it does not compile a legacy artifact smoke that depends on removed reflection C++
  headers

## ADDED Requirements

### Requirement: Publish fails if legacy public C++ artifacts remain

Publish MUST fail when a foundational family still exposes legacy reflection-oriented C++ headers
as part of its supported public publication.

#### Scenario: Legacy family-level reflection headers block publish
- **WHEN** a foundational family still emits supported public C++ headers such as
  `connector_tables.hpp` or `clock_tree_lite.hpp`
- **THEN** publish fails

#### Scenario: Legacy device-scoped reflection headers block publish
- **WHEN** a foundational family still emits supported public C++ headers such as
  `register_map.hpp`, `device_descriptor.hpp`, or `startup_descriptors.hpp`
- **THEN** publish fails

### Requirement: Publish fails if typed runtime startup contract is missing

Publish MUST fail when the runtime startup contract is absent or structurally incomplete.

#### Scenario: Missing runtime startup header blocks publish
- **WHEN** a foundational device is published without `generated/runtime/devices/<device>/startup.hpp`
- **THEN** publish fails

#### Scenario: Runtime smoke compiles startup through the runtime boundary
- **WHEN** runtime smoke runs against a foundational device
- **THEN** it includes the typed runtime startup header
- **AND** it does not include `generated/devices/<device>/startup_descriptors.hpp`
