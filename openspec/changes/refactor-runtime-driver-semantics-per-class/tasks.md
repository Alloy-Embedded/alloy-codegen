# Tasks — refactor-runtime-driver-semantics-per-class

## Phase 1: Common substrate

- [ ] 1.1 Create `src/alloy_codegen/runtime_driver/__init__.py`.
- [ ] 1.2 Move `_SemanticContext`, `_enrich`, `_invalid_register_ref`,
      `_invalid_field_ref`, `_clock_register_lookup`,
      `_synthetic_register`, `_synthetic_field`, dataclass row
      types into `runtime_driver/common.py`.
- [ ] 1.3 Add `__all__` listing every public helper so
      per-class modules can import cleanly.

## Phase 2: Migrate full-tier classes (low risk, well-tested)

- [ ] 2.1 Migrate GPIO → `runtime_driver/gpio.py`.
- [ ] 2.2 Migrate UART → `runtime_driver/uart.py`.
- [ ] 2.3 Migrate SPI → `runtime_driver/spi.py`.
- [ ] 2.4 Migrate I2C → `runtime_driver/i2c.py`.
- [ ] 2.5 Migrate ADC → `runtime_driver/adc.py`.
- [ ] 2.6 Migrate DAC → `runtime_driver/dac.py`.
- [ ] 2.7 Migrate DMA → `runtime_driver/dma.py`.
- [ ] 2.8 Migrate Timer → `runtime_driver/timer.py`.
- [ ] 2.9 Migrate PWM → `runtime_driver/pwm.py`.
- [ ] 2.10 Migrate PIO → `runtime_driver/pio.py`.
- [ ] 2.11 Per migration: golden-byte-stability check (compare
      `tests/fixtures/emitted/` before/after).
- [ ] 2.12 Per migration: full test suite green
      (`pytest tests/`).

## Phase 3: Migrate stub-tier classes

- [ ] 3.1 Migrate CAN → `runtime_driver/can.py`.
- [ ] 3.2 Migrate USB → `runtime_driver/usb.py`.
- [ ] 3.3 Migrate ETH → `runtime_driver/eth.py`.
- [ ] 3.4 Migrate RTC → `runtime_driver/rtc.py`.
- [ ] 3.5 Migrate Watchdog → `runtime_driver/watchdog.py`.
- [ ] 3.6 Migrate QSPI → `runtime_driver/qspi.py`.
- [ ] 3.7 Migrate SDMMC → `runtime_driver/sdmmc.py`.
- [ ] 3.8 Per migration: golden-byte-stability + tests.

## Phase 4: Cleanup

- [ ] 4.1 Reduce `runtime_driver_semantics.py` to a thin
      re-export shim (~50 lines), preserving every public
      symbol for backwards compatibility.
- [ ] 4.2 Update `stages/emit.py` imports to use
      `runtime_driver.<class>` directly (cleaner imports).
- [ ] 4.3 Reorganise `tests/` — move per-class semantic
      coverage tests into `tests/runtime_driver/test_<class>.py`.
- [ ] 4.4 Resolve the 18 `type: ignore` suppressions
      that previously clustered in the monolith (now naturally
      isolated to their per-class modules).

## Phase 5: Validation gate + spec

- [ ] 5.1 MODIFIED `validation-and-gates` requirement: no
      emitter file > 5.000 lines (this refactor codifies the
      rule that prevents future monolith regrowth).
- [ ] 5.2 `openspec validate refactor-runtime-driver-semantics-per-class
      --strict` passes.
- [ ] 5.3 Golden-byte-stability gate: every artifact emitted
      pre-refactor matches byte-for-byte post-refactor.
- [ ] 5.4 `pytest tests/` green: same passed/failed count as
      pre-refactor (no regression).
- [ ] 5.5 `ruff check` + `pyright` clean (or equivalent
      noise-floor unchanged from pre-refactor).
