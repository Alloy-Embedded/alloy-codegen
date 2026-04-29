# Reduce C++ Header Bloat via Shared Lookup Tables

## Why

The audit found three iMXRT1062 emitted headers that ship
heavy:

| File | Size | Pattern |
|---|---|---|
| `driver_semantics/pwm.hpp` | **52 KB** | 4 PWM blocks × 60 lines per-instance template specialisation |
| `driver_semantics/timer.hpp` | **31 KB** | 16 Timer instances × 50 lines per-instance |
| `driver_semantics/capabilities.hpp` | **31 KB** | Per-device capability enum duplicated across families |

The repetition is mechanical: every per-instance specialisation
hard-codes 40-60 fields that are *identical* across instances of
the same IP.  At 1000 admitted devices this becomes hundreds of
megabytes of redundant headers.

A shared `constexpr std::array<TraitsLut, N>` table indexed by
`PeripheralId` collapses the per-instance struct templates into
~3 lines per instance + one shared LUT.  Estimated savings:
**~30% per affected header on iMXRT, ~20% on STM32**.

## What Changes

- For each affected emitter (PWM, TIMER, CAPABILITIES, and any
  other where the audit shows >100 lines of per-instance
  repetition), refactor the emission to:
  1. Define a `<Class>HardwareLut` struct once at namespace
     scope carrying every Tier 2/3/4 field.
  2. Emit a single `inline constexpr std::array<<Class>HardwareLut,
     N>` table indexed by `PeripheralId`, with one row per
     instance.
  3. Replace per-instance specialisations with a thin alias:
     `template<> struct <Class>SemanticTraits<P> {
        static constexpr auto& kFacts =
        kHardwareLut[static_cast<size_t>(P)]; };`.
- The public `kFacts.<field>` API stays compile-time
  consteval-able; consumers see no behaviour change.
- The existing typed-enum + ValidPinAssignment-style
  specialisations are *unaffected* — they're already minimal.
- Per-emitter migration; one PR per emitter so we can validate
  each independently and roll back if anything trips the
  smoke-compile or footprint-budget gates.

## Impact

`pwm.hpp` on iMXRT1062 collapses from 52 KB → ~35 KB
(~30% drop).  Aggregate over all admitted devices: ~200-400 KB
of redundant output disappears.  Pairs with the
`artifact-footprint-budget` gate — the per-artifact byte ceiling
becomes more achievable as we eliminate redundancy rather than
just monitoring it.

Compile time also drops: parsing 52 KB of repeated template
specialisations is the slow part of the smoke compile on iMXRT
today (3.2 s for `atsame70q21b` per the runtime-cpp-smoke
report).

## What this DOES NOT do

- Does not change the emitted public API.  Consumers reading
  `<Class>SemanticTraits<P>::kField` continue to do so;
  internally the value comes from the LUT instead of an
  inline `static constexpr` member.
- Does not touch headers that are already minimal
  (`pin_validation.hpp`, `peripheral_instances.hpp`,
  `interrupts.hpp`).
- Does not introduce runtime overhead.  The LUT is
  `inline constexpr` and consumed at compile time; the linker
  may even discard the object if the consumer reads only
  scalar fields.
