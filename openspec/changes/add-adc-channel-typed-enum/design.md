# Design: Typed ADC Channel Enum Per Peripheral

## Context

`AdcSemanticRow.internal_channels` already carries
`AdcInternalChannel(kind, channel_index)` for every device the
descriptor models. The `kInternalChannels` array surfaces those in
the emitted C++ traits. What's missing is the **typed enum** that
fuses the ordinal channels (`0..kChannelCount-1`) with the named
internal channels into a single per-peripheral type.

This is purely an emission concern. No new IR fields, no new SVD
parsing, no patch overlay changes. The IR has the data; the
emitter doesn't currently project it as an enum.

## Goals

1. Emit `AdcChannelOf<P>` per published ADC peripheral with named
   enumerators for both ordinal channels and named internal channels.
2. Distinct types per peripheral — `AdcChannelOf<ADC1>::type` and
   `AdcChannelOf<ADC2>::type` MUST NOT be implicitly convertible.
3. Empty fallback so backends with `kPresent = false` keep compiling
   under the existing `if constexpr (semantic_traits::kPresent)`
   gates downstream.
4. Forward-compat: an unrecognised `AdcInternalChannel.kind` does
   NOT break the emit; it's silently dropped from the named-alias
   set, the ordinal `CH<n>` member still exists at that index.

## Non-Goals

- New facts in the IR.
- Differential channels, channel-to-pin tables, or per-channel
  sample-time enums.
- Touching ESP32 / RP2040 / AVR-DA ADC support in this change. They
  ship `AdcChannelOf<…>::type` empty fallback today; their real
  channels arrive when their ADC schema is published.

## Key Decisions

### Decision 1: Specialise a struct, not a free template

Two shapes were considered:

**(A) Specialised struct hosting the enum:**
```cpp
template <PeripheralId Id>
struct AdcChannelOf {
    enum class type : std::uint8_t {};
};

template <>
struct AdcChannelOf<PeripheralId::ADC1> {
    enum class type : std::uint8_t { CH0 = 0, /* … */ };
};
```

**(B) Free template alias backed by a constexpr array:**
```cpp
template <PeripheralId Id>
struct AdcChannelTable;

template <>
struct AdcChannelTable<PeripheralId::ADC1> {
    static constexpr std::array<std::uint8_t, N> values = {…};
    enum class type : std::uint8_t { CH0 = 0, /* … */ };
};
```

Going with **(A)**. (B) duplicates the data (the array AND the enum)
without buying anything the enum can't already represent. The
`AdcChannelOf<P>::type` form is what modm ships for `Adc1::Channel`
and feels native in C++.

### Decision 2: Convenience alias `AdcChannel<P>`

After the struct, the emitter writes:
```cpp
template <PeripheralId Id>
using AdcChannel = typename AdcChannelOf<Id>::type;
```

So callers can spell `AdcChannel<PeripheralId::ADC1>::CH0` directly
instead of `AdcChannelOf<…>::type::CH0`. This mirrors the existing
`AdcSemanticTraits` access pattern.

### Decision 3: Duplicate enumerator values are intentional

When the descriptor publishes
`InternalAdcChannel{kind=vrefint, channel_index=13}` AND `kChannelCount=19`,
the emitter produces both `CH13 = 13` (ordinal) AND `Vrefint = 13`
(named alias). They're aliases of the same underlying value.

C++ allows duplicate enum values; the named member is just a
documented spelling. Application code may use either, and the type
system still rejects cross-peripheral mixing because the enum *type*
is distinct.

### Decision 4: Naming policy is a closed table

The `AdcInternalChannel.kind` enumeration is bounded today
(`temperature_sensor`, `vrefint`, `vbat`, `opamp_output`, `dac_output`).
The emitter carries a closed mapping from kind → enumerator name:

| kind | Enumerator |
|---|---|
| `temperature_sensor` | `TempSensor` |
| `vrefint` | `Vrefint` |
| `vbat` | `VBat` |
| `opamp_output` | `OpAmpOut` |
| `dac_output` | `DacOut` |

Unknown kinds (forward-compat for future families) drop the named
alias silently and the ordinal `CH<n>` member at that index is the
only spelling. No emitter heuristic invents names — the table is the
contract.

A new kind in the IR requires updating this table (and its row in
`docs/SEMANTICS_GUIDE.md`) in a sibling proposal; the codegen does
not auto-derive names from `kind` strings.

### Decision 5: Empty fallback for kPresent=false devices

Devices that publish `AdcSemanticTraits<P>::kPresent = false` get:
```cpp
template <>
struct AdcChannelOf<PeripheralId::ADC1> {
    enum class type : std::uint8_t {};   // empty
};
```

This keeps existing `if constexpr (semantic_traits::kPresent)`
gates working downstream; an enum with zero enumerators is valid C++
and consumers that try to spell `AdcChannel<…>::CH0` get a
"no member named 'CH0'" diagnostic that points at the descriptor
gap directly.

For ESP32 / RP2040 / AVR-DA today this is exactly the desired
posture.

### Decision 6: Underlying type fixed at `std::uint8_t`

Every published ADC peripheral has channel counts under 32 today.
`std::uint8_t` is enough for any plausible MCU ADC and matches the
width of `kChannelCount` indices. No template parameter for the
underlying type — this is a deliberate simplification.

## Risks

- **Silent name collision.** If a future device publishes two
  internal channels with the same `kind` (e.g. two temperature
  sensors), the emitter would emit two enumerators with the same
  name. Mitigation: the emitter MUST detect collisions at emit time
  and fail loudly with a diagnostic naming the device + the
  conflicting channel indices. Tracked as a small TODO in the impl
  task — there's no such device in the current set.
- **Descriptor evolution decoupling.** A future descriptor change
  that adds a new `kind` will silently drop the named alias until
  the closed table here is updated. Mitigation: add a CI step that
  fails if any `AdcInternalChannel.kind` value in the IR is missing
  from the emitter's name table. Tracked as task 4.

## Migration

### For alloy-devices consumers

No migration. The new struct is additive. Existing
`AdcSemanticTraits<P>::kInternalChannels` stays unchanged.

### For alloy

Once this change archives:
- `extend-adc-coverage` (alloy repo) drops its
  `std::uint8_t channel` transitional shim and consumes
  `AdcChannel<P>` directly.
- `tests/compile_tests/test_adc_api.cpp` updates to spell channel
  values via the typed enum; cross-peripheral compile-time
  rejection is now testable.

### For external consumers of alloy-devices

Anyone outside alloy who consumes the published headers directly
(rare; the contract names alloy as the primary consumer) sees one
new struct per ADC peripheral. No symbol renames, no header path
changes.
