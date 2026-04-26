# Add Kernel-Clock Traits to Peripheral Headers

## Why

modm computes baud / SCK / SCL frequencies via per-peripheral clock
graphs: `Spi1::Hz` resolves to whatever PCLK feeds SPI1 at the
selected RCC mux setting.  alloy-codegen surfaces the *value* the
peripheral expects (`kBaudClockSourceRaw`) but neither the
**RCC mux field** that selects the source nor the **maximum** input
frequency the peripheral can take.  Without those, an alloy HAL
driver cannot:

1. Validate that the chosen `pclk_hz` is below `kMaxClockHz`.
2. Generate a `Baudrate<f_pclk, 115200, 1_pct>` resolver that picks
   the right mux setting.
3. Cross-reference RCC clock-tree nodes admitted by
   `system_clock_profiles`.

UART/SPI/I2C/QSPI/SDMMC are the affected peripherals.  The IR
already tracks RCC `peripheral_clock_bindings` and `clock_selectors`;
this change wires those into the per-peripheral specialization.

## What Changes

### Trait surface

Each affected `<peripheral>.hpp` specialization gains:

- `kKernelClockSelectorField` — `FieldRef` pointing at the RCC mux
  bitfield that selects the kernel clock source for this peripheral
  (e.g. `RCC_CCIPR.USART1SEL`).  `kInvalidFieldRef` if the chip
  hard-wires the source.
- `kKernelClockSourceOptions` — `std::array<KernelClockSourceOption, N>`
  mapping the field value to a clock-tree node ID
  (`ClockTreeNodeId::Pclk1`, `Hsi16`, `Lse`, `Sysclk`, `XTAL`, ...).
- `kMaxClockHz` — the peripheral input clock ceiling per datasheet
  (e.g. `42'000'000u` for STM32F4 SPI1 on APB2).
- `kClockGateField` — RCC enable bit (`RCC_APB1ENR.USART2EN`).  Often
  already in `peripheral_instances.hpp`, but pulling it into the
  semantic header lets the HAL gate the clock without a second
  header.

### Pipeline

- New `_kernel_clock_for_peripheral(context, peripheral_name)` helper
  walking `device.peripheral_clock_bindings`.
- New row fields on UART / SPI / I2C / QSPI / SDMMC SemanticRows.
- Specialization builders emit the four new constexprs.

### Goldens

Regenerate every emit-fixture golden that touches an affected
peripheral.  Diff scope: 4 new constexprs per specialization on
chips with admitted clock bindings.

## Impact

Combined with `add-irq-vector-traits` and
`add-peripheral-dma-cross-references`, this completes the Stage 1
unblockers.  After the trio merges, the alloy async HAL drivers can
be written without any further codegen extension for these
peripherals.
