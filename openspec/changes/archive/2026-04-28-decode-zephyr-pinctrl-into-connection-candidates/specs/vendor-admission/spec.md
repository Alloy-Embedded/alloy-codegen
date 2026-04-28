## ADDED Requirements

### Requirement: The Zephyr DTS adapter SHALL decode pinctrl groups into connection_candidates

The Zephyr DTS adapter SHALL decode `pinctrl-0` / `pinctrl-names`
references on peripheral nodes and the corresponding pin-state
groups (`<vendor>,pinctrl` compatibles) into the IR's
`connection_candidates` tuple.  The adapter SHALL ship per-vendor
decoders for at least Nordic (`NRF_PSEL` macro encoding) and
STM32 (`STM32_PINMUX` cell encoding); other-vendor decoders MAY
be added in follow-up changes through a `PINCTRL_DECODERS`
registry that mirrors the existing `COMPATIBLE_MAPS` shape.

#### Scenario: Nordic nRF52840 admission emits pin_validation.hpp

- **WHEN** the pipeline normalizes the Nordic nRF52840 fixture
  whose DTS now carries a UART0 pinctrl group with
  `NRF_PSEL(UART_TX, 0, 6)`
- **THEN** the resulting IR SHALL have at least one
  `ConnectionCandidate(pin="P0_06", peripheral="UART0",
  signal="TX", route_kind="alternate-function", ...)` entry
- **AND** `emit-pinmux-validator-concepts` SHALL emit
  `pin_validation.hpp` containing a
  `PinAssignmentValid<PinId::P0_06,
  PeripheralSignal::UART0_TX> : std::true_type` specialisation
- **AND** the runtime-cpp-smoke gate SHALL still compile cleanly

#### Scenario: STM32 pinctrl cells decode to the same shape

- **WHEN** the decoder receives an `<STM32_PINMUX 'PA9',
  AF7_USART1>` cell
- **THEN** it SHALL emit
  `PinctrlAssignment(pin="PA9", peripheral="USART1",
  signal="TX", af_number=7,
  route_kind="alternate-function")`
- **AND** the same record shape SHALL be used regardless of
  vendor so the downstream
  `connection_candidates` projection is uniform

#### Scenario: Unsupported pinctrl encodings skip without crashing

- **WHEN** the decoder encounters a pinctrl group whose vendor
  is not in `PINCTRL_DECODERS` (e.g. NXP IOMUX cells before the
  follow-up change lands)
- **THEN** the decoder SHALL log the skip and return an empty
  tuple of assignments
- **AND** the rest of the IR construction (peripherals,
  interrupts, memories) SHALL proceed unaffected
