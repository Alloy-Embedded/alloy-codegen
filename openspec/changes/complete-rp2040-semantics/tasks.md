# Tasks: Complete RP2040 Semantic Trait Coverage

Implementation note: the proposal's per-peripheral
`patches/raspberrypi/rp2040/{gpio_functions,uart_pins,spi_pins,adc,timer,pwm}.json`
overlays are **not** introduced for the GPIO surface — the FUNCSEL table
that the proposal sources from datasheet Table 2-3 is already encoded in
`patches/raspberrypi/rp2040/family.json` (each pin signal carries its
FUNCSEL `af_number` 1..9).  Phase A leverages that data directly through
`device.pins[*].signals[*].af_number`.  The dedicated overlays are still
useful for **non-GPIO** peripheral facts (DMA base addresses, PWM
slice/channel mapping, ADC FIFO depth, timer alarm count) — those land
in their respective phases below.

Depends on: `define-pio-semantic-struct` (archived) — done.  USB and I2C
are independent and currently active openspecs; this proposal does not
block on them.

## Phase A — RP2040 GPIO (this commit)

- [x] A.1 RP2040 normalize pipeline (`_build_rp2040_device_ir`) reuses
      `_build_espressif_gpio_pins` to populate `device.gpio_pins` from
      the existing FUNCSEL table on `device.pins[*].signals[*]`.
      `port = "GPIO"`, `port_offset = 0`, `is_input_only = false` for
      every pad.
- [x] A.2 Spec deltas added under
      `openspec/changes/complete-rp2040-semantics/specs/{canonical-device-ir,
      runtime-lite-contract, validation-and-gates}`. The
      `validation-and-gates` delta MODIFIES the GPIO coverage-gate
      requirement to include RP2040 mandatorily.
- [x] A.3 Coverage gate (`tests/test_gpio_semantic_coverage.py`):
      `test_gpio_coverage_gate_rp2040` no longer carries `pytest.xfail` —
      it is now a hard assertion.
- [x] A.4 Trait tests (`tests/test_gpio_semantic_traits.py`):
      * `test_rp2040_gp0_records_funcsel_alt_functions` — GP0 records
        the SPI0_RX / UART0_TX / I2C0_SDA FUNCSEL entries
        (kValidAltFunctions == {1, 2, 3}).
      * `test_rp2040_gp26_records_pad_topology` — GP26 surfaces as
        `kPresent = true` with empty `kValidAltFunctions`; the ADC
        binding lands in `adc.hpp` in Phase C.
      * `test_rp2040_emits_30_populated_specializations` — the QFN56
        package emits exactly 30 `kPresent = true` entries.
- [x] A.5 Canonical-IR fixtures regenerated:
      `tests/fixtures/rp2040/{rp2040,pico}.canonical.json`.

## Phase B — UART + SPI (pending)

- [ ] B.1 Add IR descriptors `UartPeripheralDescriptor` and
      `SpiPeripheralDescriptor` carrying `(controller_id, base_address,
      valid_pin_sets, dreq_tx, dreq_rx, max_clock_hz)`.
- [ ] B.2 Derive valid-pin sets by filtering `device.gpio_pins` for
      `peripheral in {UART0, UART1}` / `{SPI0, SPI1}` and the
      appropriate signal name (`TX`, `RX`, `MOSI`, `MISO`, …).
- [ ] B.3 Extend `runtime_driver_semantics.uart` and `.spi` emitters to
      populate the new pin-array fields on RP2040 specializations.
- [ ] B.4 Tests + golden regen.

## Phase C — ADC (pending)

- [ ] C.1 Add `AdcChannelDescriptor` to the IR carrying the channel ↔
      pad mapping (`{26, 27, 28, 29}` external + `255` for the internal
      temperature sensor).
- [ ] C.2 Wire the RP2040 normalizer to populate the ADC channel list
      (FIFO depth = 4, DREQ = 36 from datasheet §4.9 Table 264).
- [ ] C.3 Extend the ADC emitter to surface `kChannelPins`,
      `kFifoDepth`, `kDreq`.
- [ ] C.4 Tests + golden regen.

## Phase D — DMA / Timer / PWM completion (pending)

- [ ] D.1 Fill missing `DmaSemanticTraits` fields (`kBaseAddress`,
      `kChannelCount = 12`, `kMaxTransferCount`,
      `kSupportsChaining = true`, `kSupportsByteSwap = true`).
- [ ] D.2 Fill missing `TimerSemanticTraits` fields (`kBits = 64`,
      `kAlarmCount = 4`, per-alarm DREQs 39..42).
- [ ] D.3 Fill missing `PwmSemanticTraits` fields (`kSliceIndex`,
      `kChannelA_Pin`, `kChannelB_Pin`, `kClockDivMin/Max`).
- [ ] D.4 Tests + golden regen.

## Phase E — coverage matrix flip (pending)

- [ ] E.1 Update `docs/COVERAGE_MATRIX.md`: RP2040 row's `gpio_traits`
      cell switches from "⏳ pending (`complete-rp2040-semantics`)" to
      "✓ FUNCSEL".  Other RP2040 columns flip per phase.
- [ ] E.2 Add per-peripheral compile tests under
      `tests/compile_tests/test_rp2040_*.cpp` mirroring the GPIO and PIO
      patterns.
