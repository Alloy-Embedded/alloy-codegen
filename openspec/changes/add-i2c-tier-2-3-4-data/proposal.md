# Add I2C Tier 2/3/4 Data Across Admitted Families

## Why

`I2cSemanticTraits` ships the Tier-1 register/field plumbing today
(`fill-i2c-semantic-gaps` archived 2026-04-26 added clock-mux + DREQ
+ pin lists), but two gaps block the alloy async I2C HAL:

1. **STM32G0 emission is broken** — `kI2cSemanticPeripherals = {}`
   on stm32g071rb despite the IR carrying I2C1.  No specialization
   fires, so the entire trait surface is unreachable from a
   consumer.  This is a bug, not a missing feature.
2. **No Tier 2/3/4 silicon facts** — supported speeds (100k / 400k /
   1M), addressing modes (7-bit / 10-bit / SMBus), max clock,
   addressing modes, TIMINGR presets per pclk.

modm exposes `I2c::Mode {Standard, Fast, FastPlus}` and
`Hertz<400000>` baud targets backed by precomputed timing tables.
alloy needs the same constexpr surface so
`I2cMaster<I2C1>::set_speed<400_kHz>()` resolves at compile time.

This change mirrors `add-uart-spi-tier-2-3-4-data` for I2C.

## What Changes

### IR plumbing

New patch dataclasses in `patches.py`:

- `I2cSpeedOptionPatch` — `{peripheral, speed_hz, field_value}`
- `I2cAddressingOptionPatch` — `{peripheral, mode (7|10|smbus), …}`
- `I2cTimingPresetPatch` — `{peripheral, speed_hz, source_clock_hz, timingr_value}`
- `I2cModeFlagsPatch` — `supports_smbus`, `supports_pmbus`,
  `supports_dma`, `supports_slave`, `supports_dual_address`,
  `supports_general_call`
- `i2c_max_clock_hz` scalar

`DevicePatch` and `CanonicalDeviceIR` extended with the new tuples.

### Trait surface

Each `I2cSemanticTraits` specialization gains:

- `kSupportedSpeeds` — `std::array<std::uint32_t, N>` (100'000,
  400'000, 1'000'000)
- `kSupports7BitAddressing`, `kSupports10BitAddressing`,
  `kSupportsSmbus`, `kSupportsPmbus`, `kSupportsSlave`,
  `kSupportsDualAddress`, `kSupportsGeneralCall`
- `kTimingPresets` — `std::array<TimingPreset, M>` of
  `{speed_hz, source_clock_hz, timingr_value}` so the HAL can
  pick the right TIMINGR at compile time
- `kMaxClockHz`
- `kSupportsDma`, `kDmaBindings` (via
  `add-peripheral-dma-cross-references`), `kIrqNumbers` (via
  `add-irq-vector-traits`)

### STM32G0 emission fix

Investigate why `kI2cSemanticPeripherals` is empty on G0.  Likely
the dispatch in `_build_i2c_rows` rejects schema-id matching, or
the I2C is missing a `backend_schema_id` in the canonical fixture.
Fix root cause, not symptoms.

### Per-family population

- STM32G0 / F4 — speeds 100k/400k/1M; TIMINGR presets for PCLK 64
  MHz and 84 MHz
- SAME70 — TWIHS speeds 100k/400k/1M; CWGR presets
- iMXRT1060 — LPI2C speeds 100k/400k/1M
- AVR-DA — TWI master speeds 100k/400k
- ESP32 family — speeds 100k/400k/800k; per-XTAL presets
- RP2040 — speeds 100k/400k/1M (DW_I2C)

### Goldens

Regenerate every `i2c.hpp` golden across all 9 admitted families.

## Impact

Unblocks the alloy `add-async-i2c-hal` driver.  Combined with the
Stage 1 cross-cutting changes, the alloy HAL can ship I2C support
without further codegen iteration.
