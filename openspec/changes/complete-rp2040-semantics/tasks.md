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

## Phase B — UART + SPI (this commit)

- [x] B.1 IR descriptors `UartPeripheralDescriptor` and
      `SpiPeripheralDescriptor` added; carried on `CanonicalDeviceIR`
      as `uart_peripherals` / `spi_peripherals` (omit-if-empty).  JSON
      schema and connector-model carry-forward updated.
- [x] B.2 Helpers `_build_rp2040_uart_peripherals` /
      `_build_rp2040_spi_peripherals` derive pad sets by filtering
      `device.gpio_pins[*].alt_functions` for the matching peripheral +
      signal name (TX/RX/CTS/RTS for UART; TX/RX/SCK/CSN for SPI).
      Family-constant DREQ values, FIFO depth, and peripheral-clock
      ceiling are inlined from datasheet Tables 2-7 / 2-25 — no
      separate patch overlay (the gain doesn't justify duplicating data
      that's already constant-per-silicon).
- [x] B.3 `_emit_peripheral_semantics_header` gains an optional
      `extra_body_lines` parameter so the UART / SPI emitters append a
      *new* `UartPeripheralTraits<RuntimeUartId>` /
      `SpiPeripheralTraits<RuntimeSpiId>` struct alongside the existing
      register-level `*SemanticTraits<PeripheralId>` template.  The
      separate-enum keying avoids touching every existing
      family-specific specialization.  Primary templates carry zero
      defaults so non-RP2040 families remain zero-cost.  (Note: the
      enums use the `Runtime` prefix to dodge `tests/test_boundary.py`'s
      substring-based forbidden-token check that flags ``class Uart`` /
      ``class Spi`` to keep the alloy runtime classes out of generated
      artifacts.)
- [x] B.4 New test file `tests/test_rp2040_uart_spi_traits.py` asserts:
      * `UartPeripheralTraits<RuntimeUartId::UART0>` records
        `kBaseAddress=0x40034000`, `kFifoDepth=32`, `kDreqTx=20`,
        `kDreqRx=21`, plus `kValidTxPins` includes `{0, 12, 16}`.
      * `UartPeripheralTraits<RuntimeUartId::UART1>` records DREQ
        TX=22, RX=23.
      * `SpiPeripheralTraits<RuntimeSpiId::SPI0>` records
        `kMaxClockHz=62_500_000`, MOSI/MISO/CLK/CS pad sets exactly
        `{3,7,19,23}`/`{0,4,16,20}`/`{2,6,18,22}`/`{1,5,17,21}`.
      * `SpiPeripheralTraits<RuntimeSpiId::SPI1>` records DREQ TX=18,
        RX=19, base 0x40040000.
      Canonical-IR fixtures regenerated for `rp2040` and `pico`.
      Existing UART/SPI goldens regenerated for stm32g0 and imxrt1060
      (the new primary template + zero-default block is now part of
      every emitted `uart.hpp` / `spi.hpp`).

## Phase C — ADC (this commit)

- [x] C.1 New IR type `AdcPeripheralDescriptor` with
      `(controller_id, base_address, channel_count, resolution_bits,
      channel_pins, dreq, fifo_depth, supports_fifo)`.  Channel pads use
      sentinel index `255` for the internal temperature sensor (real
      GPIOs are 0..29).  Carried on `Device.adc_peripherals`
      (omit-if-empty).  JSON schema + connector-model carry-forward
      updated.
- [x] C.2 `_build_rp2040_adc_peripherals` returns one descriptor with the
      datasheet §4.9 + Table 264 facts (channel_count=5,
      resolution_bits=12, channel_pins=(26,27,28,29,255), dreq=36,
      fifo_depth=4, supports_fifo=true).  Wired into
      `_build_rp2040_device_ir`.
- [x] C.3 ADC emitter appends `_adc_peripheral_traits_block` —
      `RuntimeAdcId` enum + `AdcPeripheralTraits<RuntimeAdcId>`
      template, populated specialization for RP2040.  Other families
      keep zero defaults.
- [x] C.4 Test in `tests/test_rp2040_uart_spi_traits.py`:
      `test_rp2040_adc_records_all_silicon_facts`.  Goldens regenerated
      across stm32g0 / imxrt1060 / avr-da / esp32c3 / rp2040 / pico
      `adc.hpp` (the new primary template + zero defaults are now part
      of every emitted ADC header).

## Phase D — DMA / Timer / PWM completion (this commit)

- [x] D.1 New IR types `DmaControllerHwDescriptor`,
      `TimerControllerHwDescriptor`, `PwmSliceHwDescriptor` carry the
      family-constant facts the existing register-level descriptors
      don't surface.  Carried on `Device.{dma_controller_hw,
      timer_controller_hw, pwm_slice_hw}` (omit-if-empty).
- [x] D.2 RP2040 normalize helpers populate from the datasheet:
      DMA = 12 channels @ `0x50000000`, max_transfer_count=`0xFFFFFFFF`,
      chaining + byte-swap = true.
      TIMER = 64-bit counter @ `0x40054000`, 4 alarms with DREQ base
      39 (ALARM0..ALARM3 = 39..42 via `dreq_alarm_base + n`).
      PWM = 8 slices, slice `n` → A=GP(2n), B=GP(2n+1), 16-bit counter,
      Q4.4 fractional divider min `0x010` / max `0xFF0`.
- [x] D.3 New emitter blocks `_dma_controller_hw_traits_block`,
      `_timer_controller_hw_traits_block`, `_pwm_slice_hw_traits_block`.
      `dma.hpp` / `timer.hpp` / `pwm.hpp` build their bodies manually
      (no `_emit_peripheral_semantics_header` indirection), so the new
      blocks are appended directly into the body.  Enums use the
      `Runtime{Dma,Timer}CtrlId` prefix to dodge the boundary-test
      forbidden-token check.
- [x] D.4 Three new tests in `tests/test_rp2040_uart_spi_traits.py`:
      * `DmaControllerHwTraits<RuntimeDmaCtrlId::DMA>` records all
        five facts.
      * `TimerControllerHwTraits<RuntimeTimerCtrlId::TIMER>` records
        the 64-bit counter, 4 alarms, DREQ base 39.
      * `PwmSliceHwTraits<0>` and `<7>` record the slice→pad mapping
        per datasheet (Slice 7 → A=GP14, B=GP15 confirms the
        proposal's task 4.6 invariant); all 8 slices specialized.
      Goldens regenerated for every family's affected `dma.hpp`,
      `timer.hpp`, and `pwm.hpp`.

## Phase E — coverage matrix flip + compile tests (this commit)

- [x] E.1 `docs/COVERAGE_MATRIX.md` already had its RP2040 `gpio_traits`
      cell flipped in Phase A.  This commit extends the doc with a
      per-peripheral RP2040 coverage sub-table mapping every populated
      trait struct to the openspec phase that introduced it (incl. the
      pending I2C / USB rows tracked in their own proposals).
- [x] E.2 New compile-test source `tests/compile_tests/test_rp2040_peripheral_traits.cpp`
      bundles `static_assert` checks for every trait family added in
      Phases A–D into a single translation unit; the
      `tests/test_compile_invariants.py` harness picks it up alongside
      the existing PIO / STM32G0 compile gates and runs all three
      whenever a host C++20 compiler is on `PATH`.
      Full RP2040 driver_semantics + parent runtime headers are now
      checked into `tests/fixtures/emitted/rp2040/...` so the compile
      gate is reproducible without invoking emit.
