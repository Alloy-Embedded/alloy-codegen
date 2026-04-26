## ADDED Requirements

### Requirement: Emitted ADC Driver-Semantics Header SHALL Declare A Typed Per-Peripheral Channel Enum

Every emitted `<vendor>/<family>/.../driver_semantics/adc.hpp` MUST
declare `template <PeripheralId Id> struct AdcChannelOf` with an
empty-fallback `enum class type : std::uint8_t {};` and one
specialisation per ADC peripheral whose `AdcSemanticTraits<P>::kPresent`
is true. The specialisation's enum MUST list:

- one ordinal enumerator `CH<n>` per channel index in
  `0..kChannelCount-1`
- one named alias per `kInternalChannels` entry whose `kind` matches
  the closed name table
  (`temperature_sensor` → `TempSensor`,
  `vrefint` → `Vrefint`,
  `vbat` → `VBat`,
  `opamp_output` → `OpAmpOut`,
  `dac_output` → `DacOut`),
  with the underlying value equal to the descriptor's published
  `channel_index`.

After all specialisations, the file MUST emit a convenience alias
`template <PeripheralId Id> using AdcChannel = typename
AdcChannelOf<Id>::type;`.

#### Scenario: STM32G0 ADC1 declares a typed Channel enum with internal aliases

- **WHEN** the publication emits
  `st/stm32g0/.../stm32g071rb/.../driver_semantics/adc.hpp`
- **THEN** the file contains
  `template<> struct AdcChannelOf<PeripheralId::ADC1>` whose
  `enum class type : std::uint8_t` lists `CH0`..`CH18` plus
  `TempSensor = 12`, `Vrefint = 13`, `VBat = 14`
- **AND** the file ends with
  `template<PeripheralId Id> using AdcChannel = typename
  AdcChannelOf<Id>::type;`

#### Scenario: SAME70 AFEC0 / AFEC1 declare distinct Channel enums

- **WHEN** the publication emits the same70 ADC traits for
  `atsame70q21b`
- **THEN** both `AdcChannelOf<PeripheralId::AFEC0>` and
  `AdcChannelOf<PeripheralId::AFEC1>` are emitted as distinct
  specialisations, each with its own enum
- **AND** the type system rejects passing
  `AdcChannel<PeripheralId::AFEC0>::CH3` to a function expecting
  `AdcChannel<PeripheralId::AFEC1>` (validated by the C++ compile
  probe under `tests/compile_probes/adc_channel_enum.cpp`)

#### Scenario: Devices without ADC traits get the empty fallback

- **WHEN** the publication emits ADC traits for a device whose
  `AdcSemanticTraits<P>::kPresent` is false (today: ESP32 family,
  RP2040)
- **THEN** the file still contains the
  `template <PeripheralId Id> struct AdcChannelOf` primary template
  with an empty `enum class type : std::uint8_t {}`
- **AND** consumer code that compiles against those targets sees
  no missing-symbol error when it references `AdcChannel<...>`
  through guarded `if constexpr (kPresent)` blocks

### Requirement: Emitted ADC Channel Enum SHALL Detect Duplicate Enumerator Names At Emit Time

The emitter MUST fail the publication run if the channel manifest
derivation produces two enumerators sharing the same name on a
single ADC peripheral (e.g. two `temperature_sensor` internal
channels on some hypothetical future device). The emitter MUST
with a diagnostic naming the device, the duplicate enumerator name,
and the conflicting channel indices. The emitter MUST NOT silently
emit two members with the same name (which is ill-formed C++) and
MUST NOT silently drop one of them.

#### Scenario: Duplicate kind on a single peripheral fails fast

- **WHEN** a (hypothetical) device patch declares two internal
  channels with `kind = "temperature_sensor"` on the same ADC
  peripheral
- **THEN** the publication fails with a diagnostic of the form
  "AdcChannelOf: duplicate enumerator name 'TempSensor' on
  PeripheralId::<P> at indices <i>, <j>"
- **AND** no `adc.hpp` is written for the affected device

### Requirement: Goldens SHALL Cover Every Published ADC Device

The publication MUST regenerate every ADC driver-semantics golden
in `tests/fixtures/emitted/<family>/.../driver_semantics/adc.hpp`
as part of this change so every published ADC
peripheral's `AdcChannelOf<P>` specialisation is captured in the
golden, and every `kPresent=false` device's empty-fallback is
captured. The diff against the prior goldens MUST be additive only
— no reordering, no whitespace churn outside the new block.

#### Scenario: Every ST/Microchip/NXP ADC golden gains the typed enum block

- **WHEN** the goldens regenerate after this change lands
- **THEN** each of the following files gains a typed
  `AdcChannelOf<PeripheralId::<P>>` specialisation:
  `st/stm32g0/.../{stm32g030f6,stm32g071rb,stm32g0b1re}/...`,
  `st/stm32f4/.../{stm32f401re,stm32f405rg}/...`,
  `microchip/same70/.../{atsame70n21b,atsame70q21b}/...`,
  `microchip/avr-da/.../avr128da32/...`,
  `nxp/imxrt1060/.../{mimxrt1062,mimxrt1064}/...`
- **AND** each `kPresent=false` family
  (`espressif/esp32`, `esp32c3`, `esp32s3`, `raspberrypi/rp2040`)
  gains the empty-fallback `AdcChannelOf<…>` primary template only
