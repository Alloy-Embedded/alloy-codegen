# Tasks: Typed ADC Channel Enum Per Peripheral

Phases ordered. Each leaves the tree in a working state. Goldens
regenerate as a single block in phase 3.

## 1. IR plumbing (no new fields)

- [ ] 1.1 Confirm `AdcSemanticRow.internal_channels` carries the
      data the emitter needs (`kind`, `channel_index`). It does as
      of `add-adc-tier-2-3-4-data`; this task is a sanity check
      with no code change expected.
- [ ] 1.2 Add a derivation helper
      `runtime_driver_semantics.adc_channel_manifest(row)` returning
      a `tuple[ChannelEnumerator, ...]` where `ChannelEnumerator`
      is `(name: str, index: int)`. The helper computes ordinal
      members `CH0..CH<kChannelCount-1>` plus named aliases for
      every `internal_channels` entry whose `kind` matches the
      closed name table.

## 2. Emitter

- [ ] 2.1 Extend the ADC trait emitter so each
      `<vendor>/<family>/.../driver_semantics/adc.hpp` opens its
      `<>` specialisation with an `AdcChannelOf<PeripheralId::P>`
      specialisation hosting a typed
      `enum class type : std::uint8_t { … }`.
- [ ] 2.2 Emit the convenience alias
      `template <PeripheralId Id> using AdcChannel = typename
      AdcChannelOf<Id>::type;` once per file (after the last
      `AdcChannelOf<...>` specialisation).
- [ ] 2.3 Handle the empty fallback: every `AdcSemanticTraits<P>`
      with `kPresent = false` gets an `AdcChannelOf<P>` whose
      `enum class type` has no members.
- [ ] 2.4 Detect duplicate enumerator names at emit time and fail
      loudly with a diagnostic naming the device and the
      conflicting channel indices. (No such device exists today;
      this is forward-compat.)
- [ ] 2.5 Update the per-emitter idempotency / formatting
      consistency (header order, anonymous namespace placement) so
      the diff against the existing goldens is limited to the
      added enum + alias.

## 3. Goldens

- [ ] 3.1 Regenerate goldens for every device that currently
      publishes ADC traits:
      - `st/stm32g0/.../{stm32g030f6, stm32g071rb, stm32g0b1re}/.../adc.hpp`
      - `st/stm32f4/.../{stm32f401re, stm32f405rg}/.../adc.hpp`
      - `microchip/same70/.../{atsame70n21b, atsame70q21b}/.../adc.hpp`
      - `microchip/avr-da/.../avr128da32/.../adc.hpp`
      - `nxp/imxrt1060/.../{mimxrt1062, mimxrt1064}/.../adc.hpp`
- [ ] 3.2 Regenerate goldens for devices with `kPresent=false`
      (ESP32 / ESP32-WROOM32 / ESP32-C3 / ESP32-S3 / RP2040) — the
      empty-fallback `AdcChannelOf<P>` MUST appear in their
      `adc.hpp` so consumers don't see a missing-symbol when they
      compile against those targets.
- [ ] 3.3 Diff review: the change to each existing golden MUST be
      strictly additive (the new specialisation block + alias) —
      no reordering, no whitespace churn elsewhere.

## 4. Validation

- [ ] 4.1 Add a test in `tests/test_<family>.py` (each family that
      publishes ADC) asserting that the regenerated `adc.hpp`
      contains `AdcChannelOf<PeripheralId::<P>>::type` for every
      published ADC peripheral and at least the documented set of
      named aliases (TempSensor / Vrefint / VBat where the
      descriptor declares them).
- [ ] 4.2 Add a CI gate in the existing semantics-coverage check:
      every distinct `AdcInternalChannel.kind` value present in the
      IR for any published device MUST appear in the emitter's
      closed name table. A new kind that lands in patches without
      the emitter being updated MUST fail this gate with a
      diagnostic.
- [ ] 4.3 Add a tiny C++ compile probe under
      `tests/compile_probes/adc_channel_enum.cpp` (or extend the
      existing C++ probe set) that:
      - declares two ADC peripherals on the same device
      - confirms `AdcChannel<P1>` and `AdcChannel<P2>` are NOT
        implicitly convertible
      - confirms `AdcChannel<P>::Vrefint` and `AdcChannel<P>::CH13`
        compare equal under `static_cast<std::uint8_t>` (alias
        semantics)
- [ ] 4.4 The full `pytest -q` suite passes after goldens
      regenerate.

## 5. Documentation

- [ ] 5.1 Update `docs/SEMANTICS_GUIDE.md` (or the analogous doc
      that describes ADC traits) with a "Channel enums" subsection:
      - the enum shape
      - the closed name table for `kind` → enumerator
      - the duplicate-index aliasing semantics
      - guidance on what to do when a new `kind` appears (update
        the table and re-emit, do not invent a name in the
        emitter)
- [ ] 5.2 Cross-link from the `AdcSemanticTraits` reference in
      the same doc.
- [ ] 5.3 Update `openspec/ROADMAP.md` to record this change as a
      Stage 2 deliverable that unblocks alloy's `extend-adc-coverage`
      consumer change.

## 6. Spec validation and archive

- [ ] 6.1 `openspec validate add-adc-channel-typed-enum --strict`
      passes.
- [ ] 6.2 Archive the change with `openspec archive` once 1-5 are
      green.
- [ ] 6.3 Notify the alloy `extend-adc-coverage` change owner that
      its phase 1 (codegen prerequisite) is unblocked; the alloy
      HAL can drop its `std::uint8_t` transitional shim.
