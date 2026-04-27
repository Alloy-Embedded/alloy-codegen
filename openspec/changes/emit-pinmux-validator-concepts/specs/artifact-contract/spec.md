## ADDED Requirements

### Requirement: Per-device pin_validation.hpp SHALL project IR connection candidates as C++20 concepts

The pipeline SHALL emit, for every device with a non-empty
`device.connection_candidates`, a per-device header at
`<vendor>/<family>/generated/runtime/devices/<device>/pin_validation.hpp`
that projects the IR's connection-candidate graph into the C++ type
system.  The header SHALL contain (1) a closed
`enum class PeripheralSignal : std::uint16_t` enumerating every
distinct `(peripheral, signal)` pair admitted by the IR, with names
canonicalised to `<PERIPHERAL>_<SIGNAL>` upper-snake-case and sorted
deterministically; (2) a closed `enum class RouteKind : std::uint8_t`
covering every distinct route-kind label appearing in the device's
connection candidates (canonicalised to lower-snake-case, e.g.
`alternate_function`, `iomuxc_mux`, `peripheral_mux`, `mux`); (3) a primary template
`template<PinId Pin, PeripheralSignal Signal> struct PinAssignmentValid
: std::false_type {};` plus one full specialisation per
`ConnectionCandidate` flipping it to `std::true_type` and carrying
`kRouteKind` (typed `RouteKind`) and `kRouteSelectorIndex`
(`std::uint8_t`) as `static constexpr` members; and (4) a
`template<PinId, PeripheralSignal> concept ValidPinAssignment =
PinAssignmentValid<...>::value;` convenience concept plus a
`constexpr bool is_valid_pin_assignment(PinId, PeripheralSignal)`
linear-scan lookup.

#### Scenario: STM32G0 stm32g071rb emits PinAssignmentValid for every connection candidate

- **WHEN** the pipeline emits artifacts for STM32G0 stm32g071rb
- **THEN** the output SHALL include
  `st/stm32g0/generated/runtime/devices/stm32g071rb/pin_validation.hpp`
- **AND** that file SHALL contain `enum class PeripheralSignal` with
  entries `SPI1_SCK`, `USART1_RX`, and `USART1_TX`
- **AND** SHALL contain a specialisation
  `template<> struct PinAssignmentValid<PinId::PA1,
  PeripheralSignal::SPI1_SCK> : std::true_type` carrying
  `static constexpr RouteKind kRouteKind = RouteKind::alternate_function`
  and `static constexpr std::uint8_t kRouteSelectorIndex = 0`
- **AND** SHALL declare `template<PinId Pin, PeripheralSignal Signal>
  concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;`

#### Scenario: Pin/signal pair NOT in IR yields the primary template (false_type)

- **WHEN** a `(pin, signal)` pair is absent from
  `device.connection_candidates` (for example
  `(PinId::PA1, PeripheralSignal::USART1_TX)` on stm32g071rb)
- **THEN** the emitted header SHALL NOT contain a specialisation for
  that pair
- **AND** the primary template's `std::false_type` base SHALL apply
- **AND** `static_assert(!ValidPinAssignment<PinId::PA1,
  PeripheralSignal::USART1_TX>)` SHALL hold at compile time for any
  consumer of the header

#### Scenario: Devices with empty connection_candidates emit no pin_validation.hpp

- **WHEN** a device's `connection_candidates` list is empty
- **THEN** the pipeline SHALL skip emission of
  `pin_validation.hpp` for that device
- **AND** no other artifact SHALL be affected

### Requirement: pin_validation.hpp SHALL NOT carry string literals for route-kind labels

Per the publication gate, runtime-generated C++ artifacts MUST NOT
contain string literals (firmware-image bloat).  Route-kind labels
SHALL therefore be projected as a closed `enum class RouteKind`,
and per-candidate specialisations SHALL reference the typed enum
(e.g. `RouteKind::alternate_function`) rather than a
`std::string_view`.  Unknown route-kind strings encountered in the
IR SHALL raise `StageExecutionError` so typos cannot ship as silent
runtime data.

#### Scenario: Emitted pin_validation.hpp carries no std::string_view for route kinds

- **WHEN** the pipeline emits `pin_validation.hpp` for any admitted
  device
- **THEN** the file SHALL NOT contain `std::string_view`
- **AND** every specialisation's `kRouteKind` member SHALL be typed
  `RouteKind` (the closed enum class declared in the same header)
