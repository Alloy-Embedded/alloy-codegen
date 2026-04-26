## ADDED Requirements

### Requirement: pwm.hpp SHALL emit family-shaped PWM trait specializations

Every emitted `driver_semantics/pwm.hpp` SHALL declare per-flavour `*PwmTraits<Runtime*Id>` templates alongside the existing register-level `PwmSemanticTraits<PeripheralId>`. Each template is keyed by a generated enum populated from the matching family-shape descriptor list on `Device`:

- `StmTimerPwmTraits<RuntimeStmTimerPwmId>` — populated for STM32G0 / STM32F4.
- `FlexPwmTraits<RuntimeFlexPwmId>` — populated for iMXRT1060.
- `McpwmTraits<RuntimeMcpwmId>` — populated for ESP32 classic + ESP32-S3 (empty on ESP32-C3).
- `LedcTraits<RuntimeLedcId>` — populated for every Espressif variant.
- `AvrDaTcaPwmTraits<RuntimeAvrDaTcaId>` — populated for AVR-DA.
- `Same70PwmTraits<RuntimeSame70PwmId>` — populated for SAME70.
- The existing `Rp2040PwmSliceHwTraits<std::uint8_t SliceIndex>` (already populated by `complete-rp2040-semantics` Phase D) is unchanged.

Pad arrays use the typed `PinId` enum from `../pins.hpp`. Empty arrays are the **AllGpios** sentinel only on Espressif IO-matrix paths (LEDC + MCPWM); other families always emit a non-empty pad set when the controller is present. String literals are forbidden in the emitted code (boundary-test gate); pin names are encoded via `PinId::*` and clock-source tokens via dedicated `Runtime*ClockSource` enums.

#### Scenario: Non-PWM-shape families keep zero-cost defaults

- **WHEN** a device whose normalizer hasn't been wired for a particular PWM shape (e.g. STM32G0 has no FlexPWM) is emitted
- **THEN** the corresponding trait template (`FlexPwmTraits` in this case) declares the primary template with `kPresent = false` and zero-valued defaults
- **AND** no specializations of that template are emitted

#### Scenario: STM32G071RB emits a populated TIM1 specialization

- **WHEN** the STM32G071RB device is emitted
- **THEN** `pwm.hpp` contains `StmTimerPwmTraits<RuntimeStmTimerPwmId::TIM1>` with `kPresent = true`, `kBaseAddress = 0x40012c00u`, `kKind == StmTimerKind::Advanced`, `kChannelCount = 4u`, `kCounterBits = 16u`, `kSupportsComplementary = true`, `kSupportsDeadtime = true`, and `kValidCh1Pins` carrying at least `PinId::PA8`

#### Scenario: iMXRT1062 emits four FlexPWM specializations

- **WHEN** the mimxrt1062 device is emitted
- **THEN** `pwm.hpp` declares `FlexPwmTraits<RuntimeFlexPwmId::PWM1>`, `<PWM2>`, `<PWM3>`, `<PWM4>` each with `kPresent = true`, `kSubmoduleCount = 4u`, `kPairedChannels = true`, `kSupportsComplementary = true`, `kSupportsForceInitialization = true`

#### Scenario: ESP32-C3 emits LEDC but no MCPWM specialization

- **WHEN** the ESP32-C3 device is emitted
- **THEN** `LedcTraits<RuntimeLedcId::LEDC>::kPresent` is `true` and `kMaxResolutionBits == 14u`
- **AND** the primary `McpwmTraits` template is present (with zero defaults) but no `McpwmTraits<RuntimeMcpwmId::*>` specializations are emitted
