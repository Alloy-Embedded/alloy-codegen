## MODIFIED Requirements

### Requirement: Published C++ artifacts expose only the supported runtime contract

The published `alloy-devices` C++ contract MUST expose only the typed runtime contract plus
required startup implementation units.

#### Scenario: Runtime is the only public generated C++ tree
- **WHEN** a foundational family is published
- **THEN** its supported public C++ headers live under `generated/runtime/**`
- **AND** any published startup implementation units are limited to `startup.cpp` and
  `startup_vectors.cpp`
- **AND** the publication does not require consumers to include reflection-oriented C++ headers
  under `generated/**`

#### Scenario: Reflection metadata remains non-C++ tooling output
- **WHEN** a foundational family is published
- **THEN** JSON metadata and validation reports remain published
- **AND** they do not reintroduce a second public C++ contract

## ADDED Requirements

### Requirement: Legacy reflection C++ artifacts are not part of the public publication contract

Reflection-oriented C++ artifacts MUST NOT remain part of the supported published contract once the
runtime-only boundary is enabled.

#### Scenario: Publish omits family-wide reflection tables
- **WHEN** a foundational family is published after this change
- **THEN** artifacts such as `connector_tables.hpp`, `clock_tree_lite.hpp`, `interrupt_map.hpp`,
  `memory_map.hpp`, and `package_map.hpp` are not part of the supported public C++ tree

#### Scenario: Publish omits device-scoped reflection headers
- **WHEN** a foundational family is published after this change
- **THEN** artifacts such as `register_map.hpp`, `register_fields.hpp`, `device_descriptor.hpp`,
  `pins.hpp`, and `startup_descriptors.hpp` are not part of the supported public C++ tree

### Requirement: Startup is published through the runtime contract

Startup facts needed by `alloy` MUST be published through a typed runtime startup header.

#### Scenario: Typed startup contract is present
- **WHEN** a foundational device is published
- **THEN** `generated/runtime/devices/<device>/startup.hpp` exists
- **AND** it exposes typed startup descriptors, vector slot facts, and startup ids needed by
  `alloy`
