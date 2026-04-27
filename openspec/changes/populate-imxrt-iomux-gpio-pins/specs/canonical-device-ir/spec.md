## ADDED Requirements

### Requirement: iMXRT IR SHALL include source-derived gpio_pins and connection_candidates

The pipeline SHALL parse the iMXRT MCUXpresso `fsl_iomuxc.h`
header to extract every IOMUXC pin/mode combination
(peripheral, signal, selector index, daisy register/value) and
project the records into the canonical IR's `gpio_pins` tuple
and `connection_candidates` tuple.  Every admitted iMXRT device
SHALL therefore emit a non-empty `pin_validation.hpp` carrying
real `PinAssignmentValid<...>` specialisations — the same
compile-time pinmux validation contract STM32 admits today.
The `route_kind` for every IOMUXC-derived candidate SHALL be
`"iomuxc-mux"` (already an admitted route-kind in the
pipeline).

#### Scenario: mimxrt1062 emits non-empty gpio_pins from IOMUX

- **WHEN** the pipeline normalizes mimxrt1062
- **THEN** the resulting IR's `gpio_pins` tuple SHALL be
  non-empty and SHALL include at least the pins
  `GPIO_AD_B0_03`, `GPIO_AD_B0_06`, `GPIO_AD_B0_07`
- **AND** every entry SHALL carry the alternate-function
  records sourced from `MIMXRT1062/drivers/fsl_iomuxc.h`

#### Scenario: pin_validation.hpp emitted with real specialisations

- **WHEN** the pipeline emits artifacts for mimxrt1062
- **THEN** `nxp/imxrt1060/generated/runtime/devices/mimxrt1062/pin_validation.hpp`
  SHALL exist
- **AND** it SHALL contain at least one
  `PinAssignmentValid<PinId::GPIO_AD_B0_06,
  PeripheralSignal::LPUART1_TX> : std::true_type`
  specialisation
- **AND** the `kRouteKind` member SHALL be
  `RouteKind::iomuxc_mux`

#### Scenario: Daisy chain register/value attached when present

- **WHEN** an IOMUXC entry carries a daisy register reference
  (e.g. `IOMUXC_LPUART1_RX_SELECT_INPUT`)
- **THEN** the corresponding `ConnectionCandidate` SHALL
  reference a `RouteOperation` that records the daisy register
  address and the value to write
- **AND** the runtime layer SHALL be able to consume it without
  consulting the source header
