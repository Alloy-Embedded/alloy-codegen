# Add Per-Peripheral Typed Channel Enum To AdcSemanticTraits

## Why

The published `AdcSemanticTraits<P>` already carries
`kChannelCount` and a `kInternalChannels` array of typed
`InternalAdcChannel{kind, channel_index}` records, plus four
indexed-field patterns for per-channel selection. That's enough for
the runtime to drive the peripheral, but it's NOT enough for the
runtime to expose a **typed** API — every consumer that wants to say
"sample channel 3 then VrefInt" still has to traffic in raw
`std::uint8_t` indices.

Downstream this surfaces as a real ergonomic + safety gap: the
alloy `extend-adc-coverage` proposal needs a `Channel` enum scoped
per peripheral so `ADC1::Channel::CH3` and `ADC2::Channel::CH3` are
**distinct types** that don't implicitly convert. modm publishes
exactly this surface and uses it everywhere; alloy can match the bar
because the data already exists in the IR — what's missing is the
emission.

This change emits, alongside each `AdcSemanticTraits<P>`
specialization, a typed `enum class AdcChannelOf<P> : std::uint8_t`
with named members for:

- ordinal channels `CH0`, `CH1`, …, `CH<kChannelCount-1>`
- the named internal channels declared by the descriptor
  (`Vrefint`, `VBat`, `TempSensor`, `OpAmpOut`, `DacOut`) at their
  published `channel_index`

Each specialization is distinct, so the type system rejects
cross-peripheral channel mixing. Backends that publish
`kPresent = false` get an empty fallback enum (no members), so the
HAL's `if constexpr (semantic_traits::kPresent)` gates continue to
work unchanged.

The IR already models the data (`device.adc_internal_channels` flows
through `AdcSemanticRow.internal_channels`); the proposal is purely
emission + a small naming policy.

## What Changes

### IR: typed `AdcChannelManifest` (no payload change, naming only)

`AdcSemanticRow` SHALL gain a typed `channel_manifest: AdcChannelManifest`
that fuses the ordinal + internal channel data the row already carries.
The manifest is a derivation, not a new source-of-truth field — its
constructor takes `channel_count` and the existing
`internal_channels` tuple and emits the channel-name list the C++
emitter consumes. This keeps the IR / patches authority unchanged.

### C++ emission: `AdcChannelOf<P>` enum per peripheral

Each emitted `<vendor>/<family>/.../driver_semantics/adc.hpp` SHALL
declare:

```cpp
template <PeripheralId Id>
struct AdcChannelOf {
    enum class type : std::uint8_t {};   // empty fallback
};

template <>
struct AdcChannelOf<PeripheralId::ADC1> {
    enum class type : std::uint8_t {
        CH0 = 0,
        CH1 = 1,
        // …
        CH18 = 18,
        TempSensor = 12,    // descriptor-published index, name from kind
        Vrefint    = 13,
        VBat       = 14,
    };
};

// Convenience alias for the HAL.
template <PeripheralId Id>
using AdcChannel = typename AdcChannelOf<Id>::type;
```

The duplicate-index case (e.g. STM32G0 ADC1 where TempSensor = CH12)
is intentional: the named enumerator is an alias for the ordinal
enumerator at the same underlying value, so application code can use
either spelling and the type is still distinct from another
peripheral's `Channel`.

### Naming policy

The `AdcInternalChannel.kind` is one of:
`temperature_sensor`, `vrefint`, `vbat`, `opamp_output`, `dac_output`.
Mapped to enumerator names as:

| `kind` | Enumerator name |
|---|---|
| `temperature_sensor` | `TempSensor` |
| `vrefint` | `Vrefint` |
| `vbat` | `VBat` |
| `opamp_output` | `OpAmpOut` |
| `dac_output` | `DacOut` |

If an internal channel's `kind` is unrecognised by this policy
(forward-compat for new families), the emitter MUST drop the named
alias and rely solely on the ordinal `CH<n>` form — never silently
invent a name.

### Goldens

Every published device's `driver_semantics/adc.hpp` golden gets the
new `AdcChannelOf<P>` specialisation. Devices whose ADC is not yet
modelled (ESP32, RP2040, AVR-DA today) get the empty-fallback only,
matching their `kPresent = false` posture.

### Documentation

`docs/SEMANTICS_GUIDE.md` (or the analogous doc for ADC) gets a new
"Channel enums" subsection that documents the naming policy and the
duplicate-index behaviour.

## What Does NOT Change

- `AdcSemanticTraits<P>` is unchanged. The new enum is a sibling
  specialisation, not a member.
- `kChannelCount` and `kInternalChannels` stay as-is — the new enum
  is derived from them at emit time.
- IR sources (vendor patches, SVD parsing) are unchanged. The
  manifest is a pure derivation in the IR builder.
- Publication contract: no new fields on capabilities.json, no new
  registers in registers.hpp, no new system-sequence steps.
- ESP32 / RP2040 / AVR-DA stay at `kPresent = false`. They get the
  empty-fallback enum specialisation today and a real one when
  their ADC schema is published (separate change per family).

## Out of Scope

- **Differential / negative-channel pairing.** Where supported (some
  STM32H7 ADCs), the channel is intrinsically a pair. Tracked as
  follow-up `add-adc-differential-channel-traits` once the descriptor
  publishes the pairing data.
- **Channel-to-pin mapping.** The descriptor's connection table
  already publishes which pin maps to which ADC channel; exposing
  this in a typed `AdcChannelPin<P, Channel>` table is a separate
  proposal.
- **Internal-channel calibration.** VrefInt has a flash-calibration
  pointer that the descriptor publishes via `AdcCalibrationDataPoint`;
  using that to compute mV directly from the raw sample lives in
  alloy's `add-adc-calibration` follow-up, not here.
- **Sample-time per channel as a typed field.** The runtime needs
  `set_sample_time(Channel, ticks)`; the per-channel sample-time
  register encoding is published, but we don't add a typed
  `SampleTime` enum here. The HAL accepts a raw tick count.

## Alternatives Considered

**Make the enum itself a non-member alias** (`using AdcChannel<P> =
…`). Rejected: requires a separate `template<P> struct
AdcChannelTable;` to host the values, which doubles the emitted code
volume for no clarity gain. The `AdcChannelOf<P>::type` shape is
identical to how modm scopes `Adc1::Channel`.

**Emit channel names from a pin-table lookup** (so e.g.
`Channel::PA0` etc.). Rejected: ties channel naming to package
layout, which differs across `<device>` variants of the same family.
The ordinal `CH<n>` plus internal-kind naming is package-independent
and stable across all variants.

**Skip the enum entirely; let alloy generate it from `kChannelCount`
+ `kInternalChannels` at runtime build time.** Rejected: the
descriptor is the source of truth for ADC facts; synthesising a
typed channel surface in alloy would put device facts back into the
runtime — exactly what the runtime/device boundary forbids. The
codegen owns this.
