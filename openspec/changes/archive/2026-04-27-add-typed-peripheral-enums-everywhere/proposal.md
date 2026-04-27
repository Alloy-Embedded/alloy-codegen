# Add Typed Peripheral Enums Everywhere

## Why

ADC pioneered the typed-enum pattern in `add-adc-channel-typed-enum`:
each peripheral with channels gets a per-instance `enum class
AdcChannelOf<P>::type` with named entries (`temp`, `vrefint`, `vbat`)
instead of bare `std::uint8_t` field values.  Consumers go from:

```cpp
adc.read(12);  // what is 12? hope it's the temp sensor
```

to:

```cpp
adc.read(AdcChannelOf<ADC1>::type::temperature_sensor);
```

The compile-time error message when you pass the wrong channel
becomes a **typed mismatch** instead of "out-of-range integer".

UART / SPI / I2C / TIMER / PWM trait surfaces still leak
`std::uint8_t` field values for every option (data bits, parity,
stop bits, prescalers, frame sizes, alignment modes, trigger
sources).  The arrays are typed, but the *individual values* still
require the consumer to remember "parity 0 = none, 1 = even, 2 =
odd, …".  modm exposes `Uart::Parity::Even` as a typed enum across
every peripheral; alloy's surface is technically richer (we carry
the field-value mapping in the IR) but ergonomically rougher
because we never lift it into typed names.

## What Changes

### Per-peripheral typed enums

For every option-array currently emitted as `std::array<std::uint8_t, N>`,
emit a paired `enum class` alongside it with named entries.  Pattern
mirrors `AdcChannelOf<P>`:

```cpp
// Today (kept for back-compat):
static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{0u, 1u, 2u}};

// Added:
enum class UartParityOf<USART1>::type : std::uint8_t {
  none = 0,
  even = 1,
  odd  = 2,
};
static constexpr std::array<UartParityOf<USART1>::type, 3> kSupportedParity = {{
    UartParityOf<USART1>::type::none,
    UartParityOf<USART1>::type::even,
    UartParityOf<USART1>::type::odd,
}};
```

The raw `kSupportedParityRaw` arrays stay (one cycle of
back-compat) so existing consumers keep building.  Both the typed
and raw arrays come from the same patch data — no IR changes, only
emission.

### Coverage

In scope:

- **UART**: parity, stop bits, oversampling, baud-clock source,
  data bits, FIFO trigger fraction
- **SPI**: prescaler divisor, frame size, FIFO threshold
- **I2C**: speed mode (Standard / Fast / FastPlus / HighSpeed)
- **TIMER**: trigger source, master output, clock source
- **PWM**: alignment, break-input ID

Out of scope (separate work):

- **GPIO**: alt-function lift to typed `GpioAlt<USART1_TX>`-style
  signal aliases (mirrors the Pinmux-validator-concepts change).
- **DMA**: signal direction (already typed as `DmaBindingDirection`).
- **CAN / ETH / SDMMC / QSPI / RTC / Watchdog / DAC**: defer until
  their Tier 2/3/4 changes land (Stage 4 of the roadmap).

### Naming convention

Follow ADC's `AdcChannelOf<P>::type` pattern: `<Peripheral><Option>Of<P>::type`.
This:
- Scopes to a peripheral instance (so different USARTs can carry
  different option sets — important for chips with mixed
  USART-v2 / LPUART blocks).
- Avoids namespace collisions (every peripheral can have a `Mode`
  enum without clashing).
- Keeps type-deduction friendly: `using Parity = UartParityOf<USART1>::type;`

### Closed kind→name table

For each option type, ship a closed enum entry → field-value table
+ a name table so `to_string(UartParityOf<USART1>::type::even) ==
"even"` round-trips.  Mirrors the ADC channel-name table.

## Impact

Catches "wrong field value" bugs at compile time and makes the
generated headers self-documenting (`even`/`odd`/`none` instead of
`0`/`1`/`2`).  modm exposes typed enums across every peripheral
hand-curated; alloy generates them from the same patch data that
already drives the array surface.  This is pure ergonomics —
**the IR doesn't change** — but it's the difference between
"this header is for hand-rolling drivers" and "this header is for
shipping concept-checked HAL layers".

Closes the ergonomics gap with modm without giving up the
multi-language IR moat: the Rust emitter (separate change) gets
the same typed enums for free.
