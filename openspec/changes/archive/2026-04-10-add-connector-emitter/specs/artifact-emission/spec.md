## ADDED Requirements

### Requirement: Family Signal Map Emission
The system SHALL emit a family-level C++ header that maps every alternate-function signal
in the family to the set of pins that carry it, together with the AF number.

#### Scenario: Signal map is generated for each family
- **WHEN** the emit stage runs for any registered vendor/family scope
- **THEN** the system SHALL produce a `generated/signal_map.hpp` artifact under the family
  output directory
- **AND** it SHALL contain a `constexpr SignalDescriptor kSignalMap[]` array with one row
  per unique `(peripheral, signal, pin_name, af_number)` combination across all devices in
  scope

#### Scenario: GPIO-function entries are excluded
- **WHEN** the signal map is built
- **THEN** it SHALL NOT include pin signals whose `af_number` is `None` (i.e. GPIO mode
  entries without an alternate-function number)
- **AND** it SHALL NOT include signals whose `peripheral` field is `None`

#### Scenario: Entries are deterministic and deduplicated
- **WHEN** the same `(peripheral, signal, pin_name, af_number)` tuple appears on more than
  one device in the family
- **THEN** it SHALL appear exactly once in the output
- **AND** rows SHALL be sorted by `(peripheral, signal, pin_name)` for stable output across
  repeated runs

#### Scenario: Output is in the family-scoped C++ namespace
- **WHEN** the signal map header is emitted
- **THEN** its namespace SHALL follow the same `{vendor}::{family}::generated` pattern used
  by all other family-level generated headers
