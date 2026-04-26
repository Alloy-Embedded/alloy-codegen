# Add Board Support Package Emitter

## Why

modm's killer adoption feature is **"include one header, get blinky"**:
`#include <modm/board.hpp>` exposes `Board::Leds`, `Board::Button`,
`Board::initialize()` for every Nucleo / Discovery / Pico / Feather
they support.  alloy-codegen has device-level artifacts but **no
board layer** — every alloy consumer has to hand-wire pin names,
LED polarities, and clock profiles per dev board.  This is the
single biggest onboarding-friction gap vs modm.

The IR already has the data:
- `connection_candidates` and `connection_groups` describe every
  pin-to-peripheral mapping per package
- `pin_definitions` carry `port`, `number`, `package` membership
- `system_clock_profiles` carry the safe / default / performance
  bring-up presets

What's missing is a **board overlay** (one JSON per dev board
naming pins by their on-board function) and a **BSP emitter** that
turns it into a `bsp/<board>.hpp` header consumers can include.

## What Changes

### IR plumbing

Two new patch sources, both per-vendor under `patches/<vendor>/<family>/boards/`:

```
patches/st/stm32g0/boards/nucleo-g071rb.json
patches/st/stm32f4/boards/nucleo-f401re.json
patches/raspberrypi/rp2040/boards/pico.json
patches/microchip/avr-da/boards/curiosity-nano-128da48.json
```

Each board.json carries:

```json
{
  "board_id": "nucleo-g071rb",
  "device": "stm32g071rb",
  "package": "lqfp64",
  "summary": "ST Nucleo-64 board with STM32G071RB.",
  "named_pins": [
    {"name": "LED_GREEN", "pin": "PA5", "polarity": "active_high"},
    {"name": "BUTTON_USER", "pin": "PC13", "polarity": "active_low"},
    {"name": "UART_DBG_TX", "pin": "PA2", "peripheral": "USART2", "signal": "TX"},
    {"name": "UART_DBG_RX", "pin": "PA3", "peripheral": "USART2", "signal": "RX"}
  ],
  "default_clock_profile": "performance-pll-64mhz",
  "external_oscillators": [
    {"kind": "hse", "frequency_hz": 8000000, "source": "st-link-mco"}
  ]
}
```

New patch dataclasses + `BoardDescriptor` IR record.  The IR
validates `pin` against `connection_candidates` so a board file
that names a non-existent pin fails at normalize time.

### Trait surface

New emitted artifact per board:
`<vendor>/<family>/generated/runtime/boards/<board>/board.hpp`

```cpp
namespace st::stm32g0::generated::runtime::boards::nucleo_g071rb {

struct Leds {
  static constexpr PinId kGreen = PinId::PA5;
  static constexpr bool kGreenActiveHigh = true;
};

struct Buttons {
  static constexpr PinId kUser = PinId::PC13;
  static constexpr bool kUserActiveHigh = false;
};

struct DebugUart {
  static constexpr PeripheralId kPeripheral = PeripheralId::USART2;
  static constexpr PinId kTxPin = PinId::PA2;
  static constexpr PinId kRxPin = PinId::PA3;
};

inline constexpr ClockProfile kDefaultClockProfile =
    clock_profiles::kPerformancePll64Mhz;

}  // namespace
```

Compile-time validation: `static_assert(GpioSemanticTraits<Leds::kGreen>::kPresent)`
catches typos at `#include` time.

### Top-level convenience header

`<vendor>/<family>/generated/runtime/boards/<board>/board.hpp`
re-exports the device's `peripheral_instances.hpp` + `pins.hpp` so
**one include** is enough — matches modm's `<modm/board.hpp>`
ergonomics.

### Board catalog

New emitted manifest `metadata/boards.json` listing every admitted
board with its device + summary, so tooling (CLI, docs site, IDE
integrations) can enumerate them.

## Impact

This is the single highest-leverage adoption move per the
strategic analysis.  Combined with `add-cli-project-bootstrap`
(separate change), `alloy new --board nucleo-g071rb` writes a
buildable repo whose `main.cpp` imports `board.hpp` and lights an
LED — matching modm's onboarding without giving up the multi-language
IR moat.

The schema is intentionally tiny: ~5 board files (one per "obvious"
dev board for each admitted family) prove the pipeline.  Community
PRs add the rest.
