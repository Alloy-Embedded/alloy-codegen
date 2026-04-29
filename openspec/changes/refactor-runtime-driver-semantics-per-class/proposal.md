# Refactor runtime_driver_semantics.py into Per-Class Modules

## Why

`src/alloy_codegen/runtime_driver_semantics.py` is **17.262 lines, 260 functions**, the single largest file in the repository.  It contains 18 peripheral-class builders (GPIO, UART, SPI, I2C, ADC, DAC, DMA, Timer, PWM, CAN, ETH, USB, RTC, Watchdog, QSPI, SDMMC, PIO, DAC) whose internal structure is virtually identical: each builds a tuple of `*SemanticRow` dataclasses, each emits a header via the same template flow.  Modifications cascade across the file unpredictably, golden regen takes forever, and adding a new peripheral class means navigating thousands of lines to find where to slot in.

Today the file is a maintenance bottleneck:
- The longest function is `_microchip_hsmci_sdmmc_row()` at **384 lines**.
- 18 `type: ignore` suppressions cluster here.
- New chip families (P3 OpenSpecs) will each touch this file in 5-8 places.
- `populate-tier1-stub-driver-semantics` (P1) needs to rewrite 4 of the 18 builders — currently each rewrite is a careful surgery to avoid clobbering siblings.

Splitting into per-class modules buys: 60% LOC reduction in the largest file, clear ownership per peripheral class, easier IDE navigation, isolated diff-blast-radius, and a natural place to mount per-class regression tests.

This refactor must land **before** P1 (stub elimination) and the P3 family-admission OpenSpecs, or those changes will continue to suffer from the monolithic file.

## What Changes

- Create new module sub-package `src/alloy_codegen/runtime_driver/`:
  ```
  src/alloy_codegen/runtime_driver/
    __init__.py
    common.py                  # _SemanticContext, _enrich helpers, shared dataclasses
    gpio.py
    uart.py
    spi.py
    i2c.py
    adc.py
    dac.py
    dma.py
    timer.py
    pwm.py
    can.py
    eth.py
    usb.py
    rtc.py
    watchdog.py
    qspi.py
    sdmmc.py
    pio.py
  ```
- Each per-class module exports `emit_runtime_driver_<class>_semantics_header(*, family_dir, device) -> EmittedArtifact` mirroring today's signature.
- Common helpers (`_SemanticContext`, `_enrich`, `_invalid_register_ref`, `_invalid_field_ref`, `_st_clock_register_lookup`, etc.) move to `runtime_driver/common.py`.
- `runtime_driver_semantics.py` becomes a thin re-export shim for backwards compatibility (existing imports keep working) — file shrinks from 17k to ~50 lines.
- Per-module unit tests under `tests/runtime_driver/test_<class>.py` (split from today's mixed `test_uart_spi_traits.py`, `test_can_semantic_coverage.py`, etc.).
- No behaviour change — pure structural refactor; goldens unchanged; smoke matrix unchanged.

## Impact

- **Affected specs**: MODIFIED `validation-and-gates` (codifies the maintainability rule: no single emitter file > 5.000 lines).
- **Affected code**: `runtime_driver_semantics.py` shrinks 17k → ~50 lines; 18 new per-class modules; `stages/emit.py` imports updated; `tests/` reorganised into per-class subdirectory.
- **Dependencies**: None — purely internal refactor; unblocks P1, P3a/b/c which all touch driver semantics.
- **Out of scope**: Changing emission output (artifacts must be byte-identical to pre-refactor); changing test assertions (tests should produce identical pass/fail set); changing the IR (no model changes).
- **Risk**: Refactor regression — golden hash drift if even one byte changes.  Mitigation: golden-byte-stability gate is the primary acceptance test.
