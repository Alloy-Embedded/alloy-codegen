## ADDED Requirements

### Requirement: Publication SHALL be blocked for coverage-incomplete families

The system SHALL refuse publication for a requested scope whenever the corresponding coverage state
still says the family is not fully publishable.

That includes:

- `coverage.all_devices_publishable == false`
- any targeted device with `publishable == false`

#### Scenario: Family coverage blocks publish
- **WHEN** a family passes structural validation but `coverage.all_devices_publishable` is false
- **THEN** the publish stage SHALL fail
- **AND** no promoted `alloy-devices` artifact tree SHALL be produced for that family

#### Scenario: One incomplete device blocks family publish
- **WHEN** one device in the requested scope reports `publishable=false`
- **THEN** the publish stage SHALL fail for that scope
- **AND** the failure reason SHALL identify that the requested scope is not fully publishable

### Requirement: Publication reports SHALL agree on readiness state

The system SHALL keep validation, coverage, and publication outputs consistent about whether a
scope is publishable.

#### Scenario: Published family reports consistent readiness
- **WHEN** a family is published successfully
- **THEN** `validation-summary.json` SHALL indicate passing readiness
- **AND** `coverage.json` SHALL indicate `all_devices_publishable=true`
- **AND** `publication-record.json` SHALL describe a published scope that is fully ready under the
  same rules

### Requirement: Foundational release workflows SHALL reject partial publication

The system SHALL prevent CI release workflows from pushing or keeping a foundational family in
`alloy-devices` when the same run still reports that the family is incomplete.

#### Scenario: Partial foundational family cannot be pushed
- **WHEN** a foundational family release run ends with one or more incomplete publishability
  domains or devices
- **THEN** the workflow SHALL fail before push
- **AND** the remote `alloy-devices` tree SHALL remain unchanged for that scope
