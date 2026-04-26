# Fill I2C Semantic Gaps Across All Families

## Why

The alloy `complete-async-hal` openspec adds `async_i2c.hpp` and `I2cMaster<T>`
concept. The concept's compile-time validation requires `I2cSemanticTraits<PeripheralId>`
to be populated for each I2C peripheral on every family. Today:

| Family       | I2C traits populated? |
|--------------|-----------------------|
| SAME70       | Yes (TWI0/TWI1/TWIHS) |
| STM32G0      | Empty                 |
| STM32F4      | Empty                 |
| ESP32 classic| Empty                 |
| ESP32-C3     | Empty                 |
| ESP32-S3     | Empty                 |
| RP2040       | Empty                 |
| AVR-DA       | Empty                 |
| NXP LPC55S69 | Not yet admitted      |

8 of 9 families are entirely empty. The alloy I2C HAL concept check will silently
pass (concept constraints unevaluated) for any family without traits, meaning
misconfigured I2C peripheral IDs compile with no diagnostic.

## What Changes

### STM32G0 and STM32F4 I2C traits

STM32 I2C peripherals have:
- A fixed base address per peripheral (I2C1, I2C2, … from SVD).
- A clock source select in `RCC_CCIPR` (HSI16, SYSCLK, PCLK1 on G0).
- DMA request lines for TX and DMA for RX — indexed per peripheral.
- A set of valid SDA/SCL pins (from Open Pin Data AF table).

`I2cSemanticTraits<Id>` gains:
- `kPresent = true`
- `kBaseAddress` — peripheral base from SVD.
- `kClockSource` — `enum class I2cClockSource` (Pclk, Hsi16, Sysclk).
- `kDmaRequestTx`, `kDmaRequestRx` — DMA mux request line indices.
- `kValidSdaPins`, `kValidSclPins` — constexpr arrays of valid pin IDs.

### ESP32 I2C traits (classic, C3, S3)

ESP32 I2C is software-configurable: any GPIO can be routed to I2C SDA/SCL
via the GPIO matrix. There is no fixed pin assignment at hardware level.

`I2cSemanticTraits` for Espressif:
- `kPresent = true`
- `kPeripheralIndex` — 0 or 1 (I2C0/I2C1; C3 has only I2C0).
- `kBaseAddress` — from SVD.
- `kInSdaSignalIndex`, `kInSclSignalIndex` — GPIO matrix input signal indices.
- `kOutSdaSignalIndex`, `kOutSclSignalIndex` — GPIO matrix output signal indices.
- `kValidSdaPins = AllGpios{}` — sentinel indicating any GPIO may be used
  (not a fixed list). Alloy's I2c concept check accepts this sentinel.
- `kSupportsFastModePlus` — `true` on S3, `false` on classic/C3.

### RP2040 I2C traits

RP2040 has two I2C controllers (I2C0, I2C1). Pin assignment is constrained
but flexible (each controller has 2–3 possible SDA/SCL pin pairs).

`I2cSemanticTraits`:
- `kPresent = true`
- `kControllerIndex` — 0 or 1.
- `kBaseAddress` — from pico-sdk SVD.
- `kValidSdaPins`, `kValidSclPins` — constexpr arrays of the valid GPIO
  numbers that can be routed to this controller (from RP2040 datasheet
  Table 2-5).
- `kDreqTx`, `kDreqRx` — DMA DREQ values for this controller.

### AVR-DA I2C (TWI) traits

AVR-DA has TWI0 (optional TWI1 on larger packages). Pin mux via PORTMUX.

`I2cSemanticTraits`:
- `kPresent = true`
- `kTwiIndex` — 0 or 1.
- `kBaseAddress` — from ATDF.
- `kPortmuxAlt` — `true` if alternate pin placement selected via PORTMUX.
- `kSdaPort`, `kSdaPin`, `kSclPort`, `kSclPin` — default and alternate pin
  pairs.

## What Does NOT Change

- SAME70 I2C traits — already populated.
- The `I2cSemanticTraits` struct layout in alloy — codegen fills specializations.
- USB, SPI, UART semantic emission — separate openspecs.

## Alternatives Considered

**Single "fill-all-semantic-gaps" openspec:** Combining GPIO, I2C, SPI, UART into
one mega-PR creates an unreviable change. Splitting by peripheral type keeps each
PR focused and independently mergeable.
