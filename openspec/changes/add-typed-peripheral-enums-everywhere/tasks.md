# Tasks — add-typed-peripheral-enums-everywhere

## Phase 1: Shared typed-enum renderer

- [ ] 1.1 Lift the ADC channel-enum renderer (added by
      `add-adc-channel-typed-enum`) into a generic helper
      `_render_typed_option_enum(*, peripheral_name, type_alias,
      entries)` that emits the
      `template<> struct <Name>Of<PeripheralId::P> { enum class type
      : std::uint8_t {...}; };` block + the closed name-table.
- [ ] 1.2 Refactor the ADC emitter to use the new shared renderer
      (no behaviour change; goldens stay byte-stable).

## Phase 2: UART typed enums

- [ ] 2.1 Emit `UartParityOf<P>::type` with entries `none`, `even`,
      `odd`, `mark`, `space` filtered by the peripheral's
      `parity_options`.
- [ ] 2.2 Emit `UartStopBitsOf<P>::type` with entries `half`,
      `one`, `one_and_half`, `two` keyed by `stop_bits_q8`.
- [ ] 2.3 Emit `UartOversamplingOf<P>::type` with `over_8x`,
      `over_16x`.
- [ ] 2.4 Emit `UartBaudClockSourceOf<P>::type` with entries
      derived from the source-classifier (`pclk`, `sysclk`,
      `hsi16`, `lse`, `xtal`, `apb`, `peri_clk`, `clk_per`,
      `lpuart_clk_root`, `rc_fast`, `ref_tick`).
- [ ] 2.5 Emit `UartDataBitsOf<P>::type` with named entries `bits_5`
      … `bits_10`.
- [ ] 2.6 Emit `UartFifoTriggerOf<P>::type` with named entries for
      the populated `fraction_q8` values (`one_eighth`, `quarter`,
      `half`, `three_quarters`, `seven_eighths`, `full`).
- [ ] 2.7 Pair every typed enum with a typed `std::array<...Of<P>::type, N>`
      constexpr alongside the existing raw `_Raw` arrays.  Keep the
      raw arrays one cycle for back-compat.

## Phase 3: SPI typed enums

- [ ] 3.1 `SpiPrescalerOf<P>::type` with entries `div_2`, `div_4`,
      …, `div_256` filtered by populated divisors.
- [ ] 3.2 `SpiFrameSizeOf<P>::type` with `bits_4` … `bits_32` filtered
      by populated frame sizes.
- [ ] 3.3 `SpiFifoThresholdOf<P>::type` with the populated
      `threshold_bits` named entries.

## Phase 4: I2C typed enums

- [ ] 4.1 `I2cSpeedModeOf<P>::type` with `standard`, `fast`,
      `fast_plus`, `high_speed` filtered by populated speed_options.

## Phase 5: TIMER typed enums

- [ ] 5.1 `TimerTriggerSourceOf<P>::type` with the union of source
      strings populated in `timer_trigger_sources` (`itr0`..`itr3`,
      `etr`, `ti1f_ed`, etc.).
- [ ] 5.2 `TimerMasterOutputOf<P>::type` with the union of master-output
      sources (`reset`, `enable`, `update`, `compare_pulse`,
      `oc1ref`..`oc4ref`).

## Phase 6: PWM typed enums

- [ ] 6.1 `PwmAlignmentOf<P>::type` with `edge`, `center_up`,
      `center_down`, `center_up_down` filtered by populated
      alignment_options.
- [ ] 6.2 `PwmBreakInputOf<P>::type` with the union of break-input
      IDs (`bkin`, `bkin2`, `fault0`..`fault3`).

## Phase 7: Tests + goldens

- [ ] 7.1 Per-peripheral regression tests asserting the typed enum
      exists and contains the expected named entries on a populated
      device (USART1 on STM32G0, SPI1, I2C1, TIM1).
- [ ] 7.2 Compile-time round-trip test: `to_string(parity::even) ==
      "even"`.
- [ ] 7.3 Negative test: applying a peripheral that doesn't support
      a given option (e.g. STM32F4 USART without FIFO triggers)
      yields an enum with zero entries — consumer code branching on
      `kSupportedFifoTriggers.empty()` still compiles.
- [ ] 7.4 Regenerate emit-fixture goldens.  Diff scope: ~20 new
      typed enum blocks per device with admitted Tier 2/3/4 data
      (UART/SPI/I2C/TIMER/PWM coverage).

## Phase 8: Spec + final checks

- [ ] 8.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 8.2 `openspec validate add-typed-peripheral-enums-everywhere
      --strict` passes.
- [ ] 8.3 Full `pytest -q` + `ruff check` clean.
- [ ] 8.4 Archive entry notes that this closes the ergonomics gap
      with modm and unblocks the Rust emitter to inherit the same
      typed enums (free win on multi-language thesis).

## Phase 9: Deprecation note (next cycle)

- [ ] 9.1 Add a docs/migration note that the `_Raw` `std::uint8_t`
      arrays are retained for one release cycle and SHALL be
      removed in a follow-up `cleanup-typed-enum-raw-arrays` change.
      Don't remove them in this change — too many existing
      consumer references.
