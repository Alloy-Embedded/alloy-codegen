## ADDED Requirements

### Requirement: gpio.hpp SHALL surface valid Tier 1 field references on STM32

The emitted `gpio.hpp` `GpioSemanticTraits<PinId>` specializations on STM32 families SHALL carry valid (non-`kInvalidFieldRef`) values for the four primary configuration fields `kModeField`, `kSpeedField`, `kOutputTypeField`, `kPullField`, each resolved per pin from `device.register_fields` (e.g. `GPIOA.MODER.MODE0`, `GPIOA.OSPEEDR.OSPEED0`). Other-vendor specializations (SAM, RP2040, ESP32) keep their existing behaviour.

#### Scenario: STM32G0 PA0 surfaces valid mode/speed/type/pull fields

- **WHEN** the pipeline emits `gpio.hpp` for STM32G0 stm32g071rb
- **THEN** `GpioSemanticTraits<PinId::PA0>::kModeField` SHALL
  resolve to a `FieldRef` whose register is `GPIOA.MODER` and
  whose bit offset / width matches MODE0
- **AND** `kSpeedField` SHALL resolve to `GPIOA.OSPEEDR.OSPEED0`
- **AND** `kOutputTypeField` SHALL resolve to `GPIOA.OTYPER.OT0`
- **AND** `kPullField` SHALL resolve to `GPIOA.PUPDR.PUPD0`
- **AND** none of the four SHALL equal `kInvalidFieldRef`

#### Scenario: SAM and RP2040 GPIO are unchanged

- **WHEN** the pipeline emits `gpio.hpp` for SAME70 atsame70q21b
  or RP2040 rp2040
- **THEN** every existing field reference in
  `GpioSemanticTraits<PinId>` SHALL remain byte-identical to the
  previous golden
