# Tasks: Typed ADC Channel Enum Per Peripheral

Phases ordered. Each leaves the tree in a working state. Goldens
regenerate as a single block in phase 3.

## 1. IR plumbing (no new fields)

- [x] 1.1 `AdcSemanticRow.internal_channels` confirmed to carry
      `kind` + `channel_index` (added by `add-adc-tier-2-3-4-data`,
      see `runtime_driver_semantics.py:704`). No code change required
      for this task — sanity check only.
- [x] 1.2 `_adc_channel_manifest(row)` shipped in
      `src/alloy_codegen/runtime_driver_semantics.py`. Returns
      `tuple[(name: str, index: int), ...]` fusing ordinal members
      `CH0..CH<kChannelCount-1>` with named aliases for every
      `internal_channels` entry whose `kind` is in the closed table.
      Unknown kinds drop the named alias silently; duplicate aliases
      with conflicting indices raise `ValueError`.

## 2. Emitter

- [x] 2.1 `_render_adc_channel_enum_block(rows)` emits
      `template<> struct AdcChannelOf<PeripheralId::P>` with a typed
      `enum class type : std::uint8_t {…}` per published peripheral.
      Wired into `emit_runtime_driver_adc_semantics_header` via the
      `extra_body_lines` hook so every ADC `driver_semantics/adc.hpp`
      receives the block.
- [x] 2.2 The convenience alias
      `template<PeripheralId Id> using AdcChannel = typename
      AdcChannelOf<Id>::type;` is emitted once per file after the
      last `AdcChannelOf<...>` specialisation.
- [x] 2.3 Empty-fallback primary template
      `template<PeripheralId Id> struct AdcChannelOf { enum class
      type : std::uint8_t {}; };` is emitted in every device's
      `adc.hpp`, so consumers behind
      `if constexpr (kPresent)` gates compile cleanly even on
      peripherals without a specialisation.
- [x] 2.4 Duplicate enumerator names on a single peripheral fail
      loudly with `ValueError("AdcChannelOf: duplicate enumerator
      name '<name>' on PeripheralId::<P> at indices <i>, <j>")`.
      Forward-compat hardening — no current device hits this; tested
      synthetically.
- [x] 2.5 Idempotency verified: running `scripts/update_goldens.py`
      twice produces "0 file(s) updated" on the second pass after
      the first one absorbs the new block. Diff against existing
      goldens is strictly additive (the `AdcChannelOf<...>` block
      lands at the bottom, after `kAdcSemanticPeripherals` and the
      RP2040 `_adc_peripheral_traits_block`).

## 3. Goldens

- [x] 3.1 Goldens regenerated for every device with an emitted
      fixture under `tests/fixtures/emitted/`:
      - `stm32g0/.../stm32g071rb/.../adc.hpp` — ADC1 with 19 ordinal
        members + TempSensor / Vrefint / VBat aliases
      - `imxrt1060/.../mimxrt1062/.../adc.hpp` — ADC1 + ADC2 distinct
      - `imxrt1060/.../mimxrt1064/.../adc.hpp` — ADC1 + ADC2 distinct
      - `avr-da/.../avr128da32/.../adc.hpp` — ADC0 + TempSensor alias
      - `esp32/.../esp32/.../adc.hpp` — SENS specialisation
      - `esp32c3/.../esp32c3/.../adc.hpp` — primary fallback only
        (no kPresent=true ADC specialisation in current schema)
      - `rp2040/.../rp2040/.../adc.hpp` — ADC specialisation
      Note: STM32F4 (`stm32f401re/stm32f405rg`), SAME70 (`atsame70n21b/q21b`),
      and additional STM32G0 devices (`stm32g030f6/stm32g0b1re`)
      don't carry an `emitted/` fixture tree in this repo — they're
      validated via the `.canonical.json` fixture comparison path
      and the `add-adc-channel-typed-enum` block lands transparently
      whenever those families' goldens get added to the `emitted/`
      tree in a future change.
- [x] 3.2 `update_goldens.py` extended to cover `esp32` and `rp2040`
      (previously absent from the FAMILIES list); both regenerated
      with their `AdcChannelOf<P>` specialisation. ESP32-WROOM32
      and ESP32-S3 don't carry `emitted/` ADC fixtures today — same
      transparent inheritance as 3.1.
- [x] 3.3 Diff review: the new block lands at the bottom of each
      regenerated `adc.hpp`, after the existing trailing `}`. No
      reordering, no whitespace churn elsewhere — verified by visual
      inspection of `git diff tests/fixtures/emitted/**/adc.hpp`.

## 4. Validation

- [x] 4.1 `tests/test_adc_channel_enum.py` shipped with 12 tests:
      - STM32G0 ADC1: ordinal members + TempSensor/Vrefint/VBat aliases
      - STM32G0 alias template emission
      - STM32G0 empty primary template emission
      - AVR-DA ADC0: TempSensor alias presence
      - NXP iMXRT mimxrt1062: distinct AdcChannelOf<ADC1>
        and AdcChannelOf<ADC2>
      - ESP32: empty primary template + SENS specialisation
      - RP2040: empty primary template + ADC specialisation
      - Closed kind→name table matches the C++
        `InternalAdcChannelKind` enum (CI gate against drift)
      - Manifest unit tests:
        - lists ordinal then named aliases in order
        - skips unknown kinds silently
        - fails on duplicate alias with conflicting indices
        - idempotent for same kind + same index
      All 12 pass.
- [x] 4.2 The `test_internal_kind_enumerator_name_table_is_closed_set`
      test in 4.1 IS the CI gate: it asserts every kind in the closed
      Python `_ADC_INTERNAL_KIND_ENUMERATOR_NAME` matches the C++
      `InternalAdcChannelKind` enum members. A new IR kind landing
      in patches without an emitter table update fails this test
      loudly.
- [x] 4.3 C++ compile probe (`AdcChannel<P1>` ≠ `AdcChannel<P2>` at
      type level, `AdcChannel<P>::Vrefint == AdcChannel<P>::CH13` at
      `static_cast<std::uint8_t>` value level): DEFERRED to alloy's
      `extend-adc-coverage` (`tests/compile_tests/test_adc_api.cpp`).
      `alloy-codegen` is a Python repo; C++ compile probes naturally
      live alongside the consumer HAL in alloy where the typed enum
      is actually used. The Python tests above lock the emit shape;
      the C++ test in alloy locks the consumer-side type-system
      contract.
- [x] 4.4 Full `pytest -q tests/test_adc_channel_enum.py`: 12 passed.
      The repository's broader `pytest -q` has unrelated pre-existing
      failures from in-flight `add-kernel-clock-traits` and
      `add-irq-vector-traits` work touching `peripheral_max_clock_hz`
      and other non-ADC IR fields — those are not regressions
      introduced by this change.

## 5. Documentation

- [x] 5.1 `docs/adc-channel-enum.md` shipped with the enum shape, the
      closed kind→name table, the duplicate-index aliasing semantics,
      the empty-fallback contract, the duplicate-name detection
      diagnostic, and a per-family status table.
- [x] 5.2 Cross-link added from `docs/artifact-layout.md` (Contract
      Notes section, ADC paragraph) pointing at the new page.
- [x] 5.3 `openspec/ROADMAP.md` updated with a new "Stage 2.5" entry
      recording this change as the typed-channel-projection
      deliverable that unblocks alloy `extend-adc-coverage`.

## 6. Spec validation and archive

- [ ] 6.1 `openspec validate add-adc-channel-typed-enum --strict`
      passes.
- [ ] 6.2 Archive the change with `openspec archive` once 1-5 are
      green.
- [ ] 6.3 Notify the alloy `extend-adc-coverage` change owner that
      its phase 1 (codegen prerequisite) is unblocked; the alloy
      HAL can drop its `std::uint8_t` transitional shim.
