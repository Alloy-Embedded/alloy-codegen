# Tasks — extend-zephyr-dts-vendor-coverage

## Phase 1: Shared scaffolding

- [x] 1.1 Promote cross-vendor compatibles (`mmio-sram`,
      `soc-nv-flash`, `arm,armv7m-nvic`, `arm,armv8m-nvic`,
      `zephyr,memory-region`, `fixed-partitions`) into a module-level
      `_GENERIC_COMPATIBLE_MAP`.  Memory-handling already lives in
      the parser; this map is for *peripheral-class* generics
      (interrupt controllers) that every vendor inherits.
- [x] 1.2 Add a small helper (or inline `dict | dict` merge) so
      `compatible_map_for_vendor` returns the union of the
      generic map and the vendor-specific map.

## Phase 2: Per-vendor compatible maps

For each vendor below, hand-curate the compatible→ip-name table
covering at minimum: `uart`, `spi`, `i2c`, `adc`, `pwm` (or the
closest equivalent), `timer`, `gpio`, `wdt`, plus any vendor-
distinctive peripheral classes the source tree carries.

- [x] 2.1 `RENESAS_RA_COMPATIBLE_MAP` — Renesas RA family.
      `renesas,ra-sci-uart`, `renesas,ra-sci-i2c`,
      `renesas,ra-spi`, `renesas,ra-adc`, `renesas,ra-gpt-pwm`,
      `renesas,ra-agt-timer`, `renesas,ra-ioport` (gpio),
      `renesas,ra-wdt`, `renesas,ra-iwdt`.
- [x] 2.2 `TI_COMPATIBLE_MAP` — TI tiva-c and CC13xx/CC26xx.
      `ti,cc13xx-cc26xx-uart`, `ti,cc13xx-cc26xx-spi`,
      `ti,cc13xx-cc26xx-i2c`, `ti,cc13xx-cc26xx-adc`,
      `ti,cc13xx-cc26xx-timer`, `ti,cc13xx-cc26xx-gpio`,
      `ti,cc13xx-cc26xx-watchdog`, `ti,cc13xx-cc26xx-pinctrl`.
- [x] 2.3 `ATMEL_COMPATIBLE_MAP` — Atmel SAMD/SAML series.
      `atmel,sam0-uart`, `atmel,sam0-spi`, `atmel,sam0-i2c`,
      `atmel,sam0-adc`, `atmel,sam0-tcc-pwm`, `atmel,sam0-tc32`,
      `atmel,sam0-gpio`, `atmel,sam0-wdt`.
- [x] 2.4 `AMBIQ_COMPATIBLE_MAP` — Ambiq Apollo series.
      `ambiq,uart`, `ambiq,iom` (combined SPI/I2C controller),
      `ambiq,adc`, `ambiq,ctimer`, `ambiq,gpio`, `ambiq,wdt`,
      `ambiq,stimer`.
- [x] 2.5 `INFINEON_COMPATIBLE_MAP` — Infineon XMC and PSoC6.
      `infineon,xmc4xxx-uart`, `infineon,xmc4xxx-spi`,
      `infineon,xmc4xxx-i2c`, `infineon,xmc4xxx-vadc`,
      `infineon,xmc4xxx-ccu4-pwm`, `infineon,xmc4xxx-gpio`,
      `infineon,cat1-uart`, `infineon,cat1-i2c`,
      `infineon,cat1-spi`, `infineon,cat1-adc`,
      `infineon,cat1-counter`, `infineon,cat1-gpio`.
- [x] 2.6 `SILABS_COMPATIBLE_MAP` — SiLabs gecko series.
      `silabs,gecko-usart`, `silabs,gecko-leuart`,
      `silabs,gecko-i2c`, `silabs,gecko-spi`,
      `silabs,gecko-iadc`, `silabs,gecko-timer`,
      `silabs,gecko-letimer`, `silabs,gecko-gpio`,
      `silabs,gecko-wdog`.
- [x] 2.7 `ESPRESSIF_COMPATIBLE_MAP` — ESP32 series.
      `espressif,esp32-uart`, `espressif,esp32-spi`,
      `espressif,esp32-i2c`, `espressif,esp32-adc`,
      `espressif,esp32-mcpwm`, `espressif,esp32-ledc` (pwm),
      `espressif,esp32-timer`, `espressif,esp32-gpio`,
      `espressif,esp32-watchdog`, `espressif,esp32-rtc-timer`.

## Phase 3: Wire the maps into `COMPATIBLE_MAPS`

- [x] 3.1 Append all seven new vendor entries to
      `COMPATIBLE_MAPS` (the dict that `compatible_map_for_vendor`
      indexes).
- [x] 3.2 Update the module docstring to list the now-supported
      vendor keys.
- [x] 3.3 Extend `__all__` with the new public map symbols.

## Phase 4: Tests

- [x] 4.1 Per-vendor map test: parametrised case asserting each
      new vendor map exposes at minimum `uart`/`spi`/`i2c`/`gpio`
      and that every entry maps to a non-empty IP-name string.
- [x] 4.2 Generic-map merge test: `compatible_map_for_vendor`
      returns a map containing both vendor-specific compatibles
      AND the shared generic compatibles.
- [x] 4.3 Unmapped-compatible regression test: a synthetic DTS
      with an unknown vendor compatible string SHALL be skipped
      (recorded in `skipped_compatibles`), not raised.
- [x] 4.4 Existing Nordic test still passes unchanged (no
      regressions to the Nordic map shape or values).

## Phase 5: Validate, archive, push

- [x] 5.1 `openspec validate extend-zephyr-dts-vendor-coverage --strict`
- [x] 5.2 `pytest tests/test_zephyr_dts*.py -q` (subset) and full
      `pytest -q`
- [x] 5.3 `ruff check src/alloy_codegen/sources/zephyr_dts.py
      tests/test_zephyr_dts*.py`
- [x] 5.4 Archive the change with `openspec archive`, commit, push.
