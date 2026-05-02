## ADDED Requirements

### Requirement: Runtime-Lite Contract SHALL Expose Typed `PinId` And `route_for<>()` Accessor

The runtime-lite contract SHALL expose a typed `PinId` enumeration
per device and a `template <PeripheralId I, SignalId S, PinId P>
constexpr auto route_for() noexcept` accessor returning the
backend-typed pin route.  The accessor SHALL resolve at compile
time when all three template arguments are compile-time constants,
without scanning a runtime table.

#### Scenario: Alloy HAL routes USART2_TX onto PA2 at compile time

- **WHEN** alloy HAL on an STM32 G0 device calls
  `auto r = route_for<PeripheralId::USART2, SignalId::tx,
  PinId::pa2>();`
- **THEN** `r.code()` returns `7` at compile time (the AF7 number
  for USART2_TX on PA2)
- **AND** the call does not iterate `kRoutes` at runtime

#### Scenario: Routing an unsupported pin fails at compile time

- **WHEN** alloy HAL calls
  `route_for<PeripheralId::USART2, SignalId::tx, PinId::pa1>()`
  on an STM32 G0 device where PA1 cannot drive USART2_TX
- **THEN** the program fails to compile with a `static_assert`
  message identifying the missing route
- **AND** no runtime fallback is invoked

### Requirement: Runtime-Lite Contract SHALL Expose `PinConstraints` For Compile-Time Refusal

The runtime-lite contract SHALL expose
`template <PinId P> constexpr PinConstraints constraints_of() noexcept`
returning a typed flag set so HAL code can refuse routes onto
power, ground, or strapping pads at compile time.

#### Scenario: Routing onto a power pad refuses at compile time

- **WHEN** alloy HAL calls
  `route_for<PeripheralId::USART2, SignalId::tx, PinId::vdd>()`
- **THEN** the program fails to compile via `static_assert(
  !(constraints_of<P>() & PinConstraints::power))`
- **AND** the diagnostic names the offending pad

### Requirement: Runtime-Lite Contract SHALL Provide A Runtime Fallback For Alternate-Pin Annotations

The runtime-lite contract SHALL expose a runtime fallback
`PinRoute pin_route_lookup(PeripheralId, SignalId, PinId)` for
pin routes the canonical IR marks as runtime-resolvable
(e.g. STM32 `PA12 [PA10]` package-conditional alternate-pin
annotations).

#### Scenario: STM32 G0 PA12-aliased-as-PA10 route resolves at runtime

- **WHEN** alloy HAL on an STM32 G0 chip with PA12 aliased as PA10
  calls `pin_route_lookup(PeripheralId::USB, SignalId::dp,
  PinId::pa12)`
- **THEN** the call returns the alternate-pin route entry from
  `kAlternateRoutes`
- **AND** if no alternate exists, it returns an entry whose
  `valid()` is `false`
