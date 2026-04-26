# ADC Channel Enums

Every emitted `<vendor>/<family>/.../driver_semantics/adc.hpp` declares,
alongside the per-peripheral `AdcSemanticTraits<P>` block, a typed
`AdcChannelOf<P>` struct hosting an `enum class type : std::uint8_t`.
The enum names the ADC channels (ordinals + descriptor-published
internal channels) so consumer HALs can plumb a strongly-typed channel
parameter end-to-end.

## Shape

```cpp
template <PeripheralId Id>
struct AdcChannelOf {
    enum class type : std::uint8_t {};   // empty fallback
};

template <>
struct AdcChannelOf<PeripheralId::ADC1> {
    enum class type : std::uint8_t {
        CH0 = 0u, CH1 = 1u, /* ... */ CH18 = 18u,
        TempSensor = 12u,   // alias for CH12
        Vrefint    = 13u,   // alias for CH13
        VBat       = 14u,   // alias for CH14
    };
};

template <PeripheralId Id>
using AdcChannel = typename AdcChannelOf<Id>::type;
```

Each specialisation is its own type — `AdcChannel<PeripheralId::ADC1>`
and `AdcChannel<PeripheralId::ADC2>` do not implicitly convert. The
type system catches "I passed an ADC2 channel into an ADC1 read" at
compile time.

## Closed kind → enumerator name table

The mapping from `AdcInternalChannel.kind` (Python IR field) to the
named enumerator in the emitted enum is closed. Adding a new kind to
the IR without updating the table here drops the named alias silently
— the ordinal `CH<n>` member at that index still exists, but no
spelling like `Vrefint` is produced.

| `kind` (IR) | Enumerator (emitted) |
| --- | --- |
| `temperature_sensor` | `TempSensor` |
| `vrefint` | `Vrefint` |
| `vbat` | `VBat` |
| `opamp_output` | `OpAmpOut` |
| `dac_output` | `DacOut` |

A CI test (`tests/test_adc_channel_enum.py::test_internal_kind_enumerator_name_table_is_closed_set`)
asserts this table matches the C++ `InternalAdcChannelKind` enum
emitted in `common.hpp`. If you add a new kind to the IR, you must
either:

1. Extend `_ADC_INTERNAL_KIND_ENUMERATOR_NAME` in
   `src/alloy_codegen/runtime_driver_semantics.py` with the
   appropriate enumerator name, **and** update the table here, **and**
   the `InternalAdcChannelKind` enum in `common.hpp`, OR
2. Land the kind without an alias and accept the ordinal `CH<n>`
   spelling only — usually a stop-gap.

## Duplicate-name detection

If the channel manifest derivation produces two enumerators with the
same name on a single peripheral (e.g. two `temperature_sensor`
internal channels on a hypothetical future device), the emitter fails
fast with a diagnostic of the form:

```
ValueError: AdcChannelOf: duplicate enumerator name 'TempSensor' on
PeripheralId::<P> at indices <i>, <j>
```

This is forward-compatibility hardening — no current device hits this
path. The duplicate detection itself is exercised by
`test_adc_channel_enum.py::test_manifest_fails_on_duplicate_alias`.

## Aliasing semantics

`CH13` and `Vrefint` are both members of the same enum and share
underlying value `13`. C++ allows this — they're co-equal spellings.
`static_cast<std::uint8_t>(AdcChannel<P>::CH13) ==
static_cast<std::uint8_t>(AdcChannel<P>::Vrefint)` holds. Application
code may use either spelling.

The same kind appearing twice with the **same** index (e.g. two
patches both declaring `vrefint` at index 13) is silently coalesced —
only one named alias is emitted. Different indices for the same kind
fail loudly per the duplicate-name rule above.

## Empty fallback

Any peripheral whose `AdcSemanticTraits<P>::kPresent` is false gets
the inherited empty `enum class type : std::uint8_t {}` from the
primary template. The empty primary template is always emitted in
every device's `adc.hpp`, so consumers gating with
`if constexpr (AdcSemanticTraits<P>::kPresent)` compile cleanly even
on devices without an ADC.

## Status across published families

| Family | Device(s) | ADC peripheral(s) |
| --- | --- | --- |
| `st/stm32g0` | `stm32g071rb` | `ADC1` (19 ch + TempSensor / Vrefint / VBat) |
| `st/stm32f4` | `stm32f401re`, `stm32f405rg` | `ADC1` |
| `microchip/same70` | `atsame70n21b`, `atsame70q21b` | `AFEC0`, `AFEC1` |
| `microchip/avr-da` | `avr128da32` | `ADC0` (TempSensor) |
| `nxp/imxrt1060` | `mimxrt1062`, `mimxrt1064` | `ADC1`, `ADC2` |
| `espressif/esp32` | `esp32`, `esp32-wroom32` | `SENS` |
| `espressif/esp32c3` | `esp32c3` | (kPresent=false today; primary fallback only) |
| `espressif/esp32s3` | `esp32s3` | (kPresent=false today; primary fallback only) |
| `raspberrypi/rp2040` | `rp2040` | `ADC` |
