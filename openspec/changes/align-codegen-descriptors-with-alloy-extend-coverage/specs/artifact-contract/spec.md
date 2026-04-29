## ADDED Requirements

### Requirement: All driver-semantics classes SHALL ship full trait specialisations on every admitted device that owns the peripheral

The codegen SHALL emit a fully-populated `<Class>SemanticTraits<P>`
specialisation (not a stub with `kHardwarePresent = false`)
for every `(device, peripheral)` pair where the device's
silicon owns a peripheral of class CAN, USB Host, Ethernet
MAC, QSPI / OctoSPI, SDMMC, RTC, or Watchdog.  Stub
specialisations remain acceptable only when the device has no
peripheral of that class — never when the silicon has the
peripheral but the descriptor data is missing.  Together with
the already-full classes (Gpio, Uart, Spi, I2c, Adc, Dac, Dma,
Timer, Pwm, Pio, Usb-Device), this brings the
driver-semantics coverage to FULL across every published
peripheral class.

#### Scenario: stm32f405rg ships a populated CAN trait

- **WHEN** the pipeline emits artifacts for stm32f405rg
- **THEN** `driver_semantics/can.hpp` SHALL contain a
  specialisation `struct CanSemanticTraits<PeripheralId::CAN1>`
  with `kHardwarePresent = true`
- **AND** the specialisation SHALL carry a non-zero
  `kTxMailboxCount`, the bxCAN-specific filter-bank fields,
  and the populated TX/RX pin ids drawn from the device's
  `connection_candidates`

#### Scenario: mimxrt1062 ships populated FlexSPI traits

- **WHEN** the pipeline emits artifacts for mimxrt1062
- **THEN** `driver_semantics/qspi.hpp` SHALL contain
  specialisations for `FLEXSPI1` and `FLEXSPI2` with
  `kControllerKind = QspiControllerKind::octospi` and
  `kDataLines = 8`
- **AND** the alloy `extend-qspi-coverage` HAL driver SHALL
  compile against the resulting headers without
  `if constexpr` fallback paths gating on
  `kHardwarePresent`

### Requirement: Trait promotion regressions SHALL be detected by paired regression tests

The test suite SHALL carry a regression test for every class
promoted from stub to full under this change, asserting the
published trait specialisation contains the fields the
matching alloy `extend-<class>-coverage` HAL driver expects.
The tests SHALL run on every PR that touches the affected
emitter, the affected IR descriptor, or the per-device YAML
data.

#### Scenario: Stub regression detection

- **WHEN** a contributor accidentally drops a populated CAN
  controller descriptor from a YAML on stm32f405rg and
  resubmits
- **THEN** `tests/test_can_semantic_coverage.py` SHALL fail
  with a clear message naming the dropped descriptor field
- **AND** the build SHALL block the merge until the YAML is
  restored or the regression is justified by a follow-up
  proposal removing the device's CAN admission
