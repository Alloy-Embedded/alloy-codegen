# Tasks — extend-zephyr-dts-vendor-coverage

## Phase 1: Compatible maps

- [ ] 1.1 Add `RENESAS_COMPATIBLE_MAP` to
      `sources/zephyr_dts.py` covering UART/SPI/I2C/TIMER/RTC/PWM/
      ADC/GPIO for RA-series (`renesas,ra-*`).
- [ ] 1.2 Add `TI_COMPATIBLE_MAP` for CC13/CC26 + MSP432
      (`ti,cc13xx-uart`, `ti,cc13xx-spi`, …).
- [ ] 1.3 Add `INFINEON_COMPATIBLE_MAP` for XMC + PSoC
      (`infineon,xmc4xxx-uart`, `infineon,cat1-*`).
- [ ] 1.4 Add `AMBIQ_COMPATIBLE_MAP` for Apollo3/Apollo4
      (`ambiq,apollo3-*`).
- [ ] 1.5 Add `SILABS_COMPATIBLE_MAP` for EFR32/EFM32
      (`silabs,gecko-*`).

## Phase 2: Vendor registration

- [ ] 2.1 `_register_renesas_ra4.py` — pilot device `r7fa4m1ab`.
- [ ] 2.2 `_register_ti_cc13x2.py` — pilot device `cc1352r`.
- [ ] 2.3 `_register_infineon_xmc4xxx.py` — pilot device
      `xmc4700`.
- [ ] 2.4 `_register_ambiq_apollo3.py` — pilot device `apollo3p`.
- [ ] 2.5 `_register_silabs_efr32.py` — pilot device `efr32mg21`.
- [ ] 2.6 Wire all five into `vendors/__init__.py` side-effect
      imports.

## Phase 3: Patches + fixtures

- [ ] 3.1 Per-vendor `patches/<vendor>/<family>/family.json`
      (small — packages, peripherals, ip_versions).
- [ ] 3.2 Per-vendor `patches/<vendor>/<family>/devices/<device>.json`
      (~50 LOC each, mirroring nRF52840).
- [ ] 3.3 Per-vendor minimal DTS fixture under
      `tests/fixtures/zephyr-dts/<vendor>/<device>.dts`.

## Phase 4: Pipeline integration

- [ ] 4.1 `bootstrap.py:DEVICE_REGISTRY` + `SOURCE_BUNDLES`
      add the 5 entries.
- [ ] 4.2 `affected_families.py:static_core_map` add the 5
      `(vendor, family) -> core` entries.
- [ ] 4.3 `tests/test_known_devices_catalog.py:_NOT_IN_PROBE_RS`
      add allow-list entries for any pilots probe-rs doesn't
      cover yet.

## Phase 5: Tests

- [ ] 5.1 Per-vendor extension to `test_zephyr_dts.py`
      asserting registry resolution + end-to-end normalize.
- [ ] 5.2 `test_runtime_cpp_smoke.py` parametrisation picks
      up the new devices automatically.
- [ ] 5.3 Devices-README golden regen (5 new rows).

## Phase 6: Spec + final checks

- [ ] 6.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 6.2 `openspec validate extend-zephyr-dts-vendor-coverage
      --strict` passes.
- [ ] 6.3 `pytest -q` + `ruff check` clean.
