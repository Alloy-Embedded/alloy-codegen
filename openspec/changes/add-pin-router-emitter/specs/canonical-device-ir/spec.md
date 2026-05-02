## ADDED Requirements

### Requirement: Canonical IR SHALL Materialise Pin Routes Synthesised From `pin_options`

The synthesised IR (`SynthesisedDevice`) SHALL carry a deterministic
`pin_routes: tuple[PinRoute, ...]` field materialised from
`device.peripherals[*].pin_options` payloads.  Each `PinRoute`
SHALL carry typed refs (`peripheral_id`, `signal_id`, `pin_id`),
the family's pinmux backend schema id, and the backend-specific
encoded routing cell.

#### Scenario: STM32 G0 USART2_TX route on PA2 lowers to AF7

- **WHEN** alloy-codegen synthesises the IR for `st/stm32g0/stm32g071rb`
- **THEN** `synthesised.pin_routes` contains an entry with
  `peripheral_id="usart2"`, `signal_id="tx"`, `pin_id="pa2"`,
  `backend_schema_id="alloy.pinmux.stm32-af-v1"`, and an encoded
  cell value `7` (the AF7 number for USART2_TX on PA2)

#### Scenario: SAM E70 USART1_TXD route on PA22 lowers to PIO matrix function A

- **WHEN** alloy-codegen synthesises the IR for `microchip/same70/atsame70q21b`
- **THEN** `synthesised.pin_routes` contains an entry with
  `peripheral_id="usart1"`, `signal_id="txd"`, `pin_id="pa22"`,
  `backend_schema_id="alloy.pinmux.sam-pio-v1"`, and an encoded
  cell whose `payload.matrix_function` equals `"A"`

#### Scenario: Pin route ordering is deterministic

- **WHEN** the same IR is synthesised twice on the same machine
- **THEN** `synthesised.pin_routes` is byte-identical, ordered by
  `(peripheral_id, signal_id, pin_id)` ascending

### Requirement: Canonical IR SHALL Bind Pinmux Backend Schema IDs To Vendor Families

Every admitted vendor/family SHALL declare exactly one
`pinmux_backend_schema_id` matching one of the registered backend
adapters.  The synthesiser SHALL refuse to lower `pin_options` for
any family whose schema id is not registered.

#### Scenario: Unknown backend schema raises a typed error

- **WHEN** alloy-codegen tries to synthesise pin routes for a family
  whose `pinmux_backend_schema_id` is `alloy.pinmux.unknown-v9`
- **THEN** synthesis raises `StageExecutionError` with a message
  naming the offending family, the missing schema id, and the
  list of registered backend ids

### Requirement: Canonical IR SHALL Surface Pin Constraints For Compile-Time Refusal

The synthesised IR SHALL surface the per-pad constraint set
(`power`, `ground`, `strapping`, `analog_only`, `input_only`,
`boot`) from `device.pinout[*].constraints` as a typed
`PinConstraints` flag set keyed by `pin_id`.  Pads carrying the
`power` or `ground` constraint SHALL NOT appear in `PinId`.

#### Scenario: STM32 G0 VDD/VBAT pads are not in PinId

- **WHEN** alloy-codegen synthesises `st/stm32g0/stm32g071rb`
- **THEN** `synthesised.pin_ids` does not contain `vdd`, `vss`,
  `vbat`, `vref+`, or any other pad whose `Pin.constraints`
  includes `power` or `ground`
- **AND** `synthesised.pin_constraints["vdd"]` carries the
  `PinConstraints.power` flag

## MODIFIED Requirements

### Requirement: Canonical IR SHALL Model Every Runtime Semantic Domain As Typed IDs

The canonical device IR SHALL model every semantic domain consumed by the Alloy runtime as
typed ids, enums, or typed refs rather than human-readable labels.  This SHALL include
**pin identity, peripheral signal identity, and pinmux backend schema id**, in addition to
the previously required domains.

#### Scenario: Foundational device is normalized

- **WHEN** a foundational device is normalized into the canonical IR
- **THEN** backend schema, peripheral class, signal, signal role, route kind, requirement
  kind, operation kind, operation subject kind, memory kind, startup kind, package pad kind,
  active level, **pin id, peripheral signal id, and pinmux backend schema id** are
  represented by typed ids
- **AND** the runtime does not need semantic strings to understand those domains

#### Scenario: Pin route is expressible without pad-name strings

- **WHEN** an emitter materialises a `PinRoute` from the canonical IR
- **THEN** the route is fully described by `PeripheralId`,
  `SignalId`, `PinId`, `PinmuxBackendSchemaId`, and an integer cell
  value
- **AND** no `const char*` pad name is required to drive the route at runtime
