# Coverage Matrix

Per-family coverage of the populated runtime-lite trait surfaces emitted by
`alloy-codegen`.  Authoritative live data lives in
`<vendor>/<family>/reports/coverage.json` artifacts; this document is a
human-readable summary tracked alongside the openspec proposals that
introduce each column.

| Vendor      | Family    | Devices                              | gpio_traits | pio_traits |
|-------------|-----------|--------------------------------------|-------------|------------|
| st          | stm32g0   | stm32g030f6, stm32g071rb, stm32g0b1re | ✓ AF        | N/A        |
| st          | stm32f4   | stm32f401re, stm32f405rg              | ✓ AF        | N/A        |
| microchip   | same70    | atsame70n21b, atsame70q21b            | ✓ AF        | N/A        |
| microchip   | avr-da    | avr128da32                            | ✓ PORTMUX   | N/A        |
| nxp         | imxrt1060 | mimxrt1062, mimxrt1064                | ✓ register-level + AF zero-defaults | N/A |
| espressif   | esp32     | esp32, esp32-wroom32                  | ✓ IO matrix | N/A        |
| espressif   | esp32c3   | esp32c3                               | ✓ IO matrix | N/A        |
| espressif   | esp32s3   | esp32s3                               | ✓ IO matrix | N/A        |
| raspberrypi | rp2040    | rp2040, pico                          | ⏳ pending (`complete-rp2040-semantics`) | ✓ |

## Column meaning

- **gpio_traits** — populated `GpioSemanticTraits<PinId::*>` specializations
  with `kPresent = true`.  The annotation indicates how the alternate-function
  data was sourced:
  - **AF** — STM32 alternate-function table from ST Open Pin Data XML.
  - **PORTMUX** — AVR-DA PORTMUX channel index from the ATDF.
  - **IO matrix** — Espressif `gpio_sig_map.h` signal-index routing.
  - **register-level + AF zero-defaults** — NXP iMXRT exposes register-level
    GPIO traits (mode/direction/pull fields) and carries zero-defaulted AF
    fields until a follow-up wires NXP IOMUX data.
- **pio_traits** — populated `PioSemanticTraits<PioId::*>` and
  `StateMachineSemanticTraits<PioId, Sm>` specializations.  Only RP2040 has
  PIO hardware among the admitted families today.

## Source proposals

| Column | Introduced by | Specs touched |
|--------|---------------|---------------|
| `pio_traits` | `define-pio-semantic-struct` (archived) | `canonical-device-ir`, `runtime-lite-contract` |
| `gpio_traits` | `fill-gpio-semantic-gaps` (archived) | `canonical-device-ir`, `runtime-lite-contract`, `validation-and-gates` |

## Outstanding follow-ups

- **RP2040 GPIO traits** — tracked by `complete-rp2040-semantics`; the
  GPIO coverage gate's RP2040 case is `xfail`-marked until that change
  populates `device.gpio_pins` for RP2040.
- **`GpioMatrixSemanticTraits<SignalId>`** — signal-side trait split for
  Espressif's IO matrix.  Pin-side coverage is complete; the signal-side
  ergonomic gain is its own follow-up proposal.
- **NXP iMXRT IOMUX AF data** — currently the iMXRT specializations carry
  zero-defaulted `kPortOffset` / `kPinIndex` / `kValidAltFunctions`; a
  follow-up can wire IOMUX data through `_build_nxp_gpio_pins`.
