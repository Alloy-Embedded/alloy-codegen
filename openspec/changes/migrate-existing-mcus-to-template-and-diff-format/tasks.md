# Tasks — migrate-existing-mcus-to-template-and-diff-format

## Wave 1: Pilots (lowest risk)

- [ ] 1.1 Migrate `patches/nordic/nrf52/devices/nrf52840.json`
      — already 37 LOC, drop `__source_notes` envelope and
      ensure `nrf-uart-v1` template inheritance kicks in.
      Goldens: byte-identical.
- [ ] 1.2 Migrate `patches/raspberrypi/rp2040/devices/{rp2040,pico}.json`
      — Tier 2/3/4 to templates (rp2040-uart-v1,
      rp2040-spi-v1, rp2040-i2c-v1).  Goldens: regen + review.
- [ ] 1.3 Migrate `patches/espressif/esp32c3/devices/esp32c3.json`
      — esp32c3-uart-v1 / esp32c3-spi-v1 / esp32c3-i2c-v1.

## Wave 2: STM32

- [ ] 2.1 Seed missing STM32 templates (usart-v3 if needed for
      G0; lpuart-v1; spi-v2; i2c-v2; tim-v3) — these may
      already exist from earlier work.
- [ ] 2.2 Migrate `patches/st/stm32g0/devices/*.json` (3
      devices).  Expected LOC drop: 878 avg → ~80.
- [ ] 2.3 Migrate `patches/st/stm32f4/devices/*.json` (2
      devices).  Expected LOC drop: 733 avg → ~90.

## Wave 3: Espressif

- [ ] 3.1 Migrate `patches/espressif/esp32/devices/*.json`.
- [ ] 3.2 Migrate `patches/espressif/esp32s3/devices/esp32s3.json`.

## Wave 4: iMXRT

- [ ] 4.1 Seed nxp-lpuart-v1 / nxp-lpspi-v1 / nxp-lpi2c-v1
      templates from existing iMXRT patches.
- [ ] 4.2 Migrate `patches/nxp/imxrt1060/devices/*.json` (2
      devices).  Expected LOC drop: 1224 avg → ~50.

## Wave 5: ATDF (gated on prereq)

- [ ] 5.1 PRE-REQ: ship `extend-autogen-to-atdf-and-mcuxpresso`
      so SAME70/AVR-DA have a baseline to diff against.
- [ ] 5.2 Migrate `patches/microchip/same70/devices/*.json`.
- [ ] 5.3 Migrate `patches/microchip/avr-da/devices/avr128da32.json`.

## Per-wave validation

- [ ] V.1 Each wave runs `--update-goldens` once; reviewer
      audits the diff to confirm only structural / template-
      sourced fields moved.
- [ ] V.2 Each wave runs `--runtime-cpp-smoke` to catch any
      template-merge bug that escapes goldens.
- [ ] V.3 Per-wave commit logs describe the LOC reduction
      achieved.

## Spec + final checks

- [ ] X.1 Spec delta in `specs/canonical-device-ir/spec.md`
      noting the migration is complete (no contract change;
      records the rollout milestone).
- [ ] X.2 `openspec validate
      migrate-existing-mcus-to-template-and-diff-format
      --strict` passes.
- [ ] X.3 Total `patches/**/*.json` LOC is at most 5,500
      after Wave 4, at most 3,500 after Wave 5.
