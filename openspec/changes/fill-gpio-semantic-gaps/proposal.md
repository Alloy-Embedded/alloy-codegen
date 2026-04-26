# Fill GPIO Semantic Gaps Across All Families

## Why

The alloy `add-gpio-hal` and `expand-chip-coverage` openspecs require
`GpioSemanticTraits<PinId>` specializations to be populated for every supported
MCU family. Today the situation is:

| Family       | GPIO traits populated? |
|--------------|------------------------|
| SAME70       | Yes (reference impl)   |
| STM32G0      | Empty (`kPresent=false`)|
| STM32F4      | Empty                  |
| ESP32 classic| Empty                  |
| ESP32-C3     | Empty                  |
| ESP32-S3     | Empty                  |
| RP2040       | Partial (see `complete-rp2040-semantics`) |
| AVR-DA       | Empty                  |
| NXP LPC55S69 | Not yet admitted        |

Without populated GPIO traits, the alloy HAL's compile-time pin routing
validation (`gpio::pin<Id>()` concept check) cannot validate pin assignments
at compile time. Every consumer silently falls back to unchecked code.

## What Changes

### STM32G0 and STM32F4 GPIO traits

The STM32 SVD exposes `GPIO{A..F}.MODER`, `OSPEEDR`, `PUPDR`, `AFRL/AFRH`
and the ST Open Pin Data JSON records which alternate functions are valid for
each physical pin. The emitter gains a new `gpio_semantics` pass that:

1. Reads the pin-alternate-function table from the Open Pin Data overlay
   (`patches/st/stm32g0/pin_data.json`, `patches/st/stm32f4/pin_data.json`).
2. For each `PinId`, fills `GpioSemanticTraits`:
   - `kPresent = true`
   - `kPortOffset` — the GPIOX base address offset from `GPIOA_BASE`
   - `kPinIndex` — bit position within the port (0–15)
   - `kMaxAltFunction` — highest AF index the pin supports
   - `kValidAltFunctions` — `constexpr std::array<std::uint8_t, N>` of valid AF
     numbers for this pin (from Open Pin Data)
3. Emits the specializations into
   `generated/runtime/devices/<device>/driver_semantics/gpio.hpp`.

### ESP32 classic, ESP32-C3, ESP32-S3 GPIO traits

The Espressif `gpio_sig_map.h` provides the full matrix of GPIO ↔ peripheral
signal routing. The existing `esp_idf.py` adapter already reads this file to
populate IO_MUX facts. The `gpio_semantics` pass extends that to:

1. For each GPIO pad, populate:
   - `kPresent = true`
   - `kGpioNum` — pad number (0–39 classic, 0–21 C3, 0–47 S3)
   - `kIsInputOnly` — `true` for GPIO34–39 on classic, none on C3/S3
   - `kHasIoMuxFastPath` — `true` if the pad has a direct IO_MUX function
     (bypasses GPIO matrix for full-speed peripherals)
   - `kIoMuxFunctions` — constexpr list of signal names that route through
     IO_MUX without the GPIO matrix (up to 6 per pad)
2. Separate `GpioMatrixSemanticTraits<SignalId>` records the input/output
   signal index for every peripheral signal so consumers can compute
   `GPIO.func_in_sel_cfg` and `GPIO.func_out_sel_cfg` at compile time.

### AVR-DA GPIO traits

AVR-DA (ATmega-xDA) uses ATDF for register descriptions. The ATDF's
`<module name="PORT">` section lists all PORTs and pins. The `gpio_semantics`
pass for AVR:

1. For each `PINxn`, emits:
   - `kPresent = true`
   - `kPortIndex` — A=0, B=1, …, G=6
   - `kPinBit` — bit index within the port byte
   - `kHasPinCtrl` — always `true` for AVR-DA (each pin has `PINnCTRL`)
   - `kPmuxChannel` — PORTMUX channel index if the pin participates in
     peripheral mux (from ATDF `<signal>` elements on `<module name="PORTMUX">`)

## What Does NOT Change

- SAME70 GPIO traits — already populated, reference implementation preserved.
- RP2040 GPIO — handled in `complete-rp2040-semantics`.
- The `GpioSemanticTraits` struct layout — defined in alloy's
  `src/hal/gpio/detail/gpio_semantic_traits.hpp`; codegen fills specializations.
- Non-GPIO semantic headers — out of scope for this change.

## Alternatives Considered

**Manual hand-coding:** The ST Open Pin Data JSON has ~3000 pin entries per
device. Hand-coding is error-prone and unmaintainable. Codegen from authoritative
source is the only correct approach.

**Defer until `add-gpio-hal` lands in alloy:** The alloy openspec can proceed with
empty traits and a runtime fallback — but that undermines the zero-overhead
compile-time validation goal that distinguishes alloy from mbed OS. Traits must
be populated before the alloy gpio HAL ships.
