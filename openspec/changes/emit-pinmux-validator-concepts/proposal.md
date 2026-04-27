# Emit Pinmux Validator Concepts

## Why

The IR already carries every valid `(pin, peripheral, signal)` route
admitted by the silicon (`device.connection_candidates`,
`device.connection_groups`).  modm hand-tabulates "valid pinmux"
in C++ source per family — we have it as data.

Surfacing this data as **C++20 concepts** lets the alloy HAL catch
invalid pin assignments at compile time:

```cpp
static_assert(ValidPinAssignment<PinId::PA1, PeripheralSignal::SPI1_SCK>);
// passes — IR admits this route

static_assert(ValidPinAssignment<PinId::PA1, PeripheralSignal::USART1_TX>);
// fails at compile time — IR has no candidate for that route
```

Or, more usefully, as a concept constraint:

```cpp
template<PinId Tx, PinId Rx>
  requires ValidPinAssignment<Tx, PeripheralSignal::USART1_TX>
        && ValidPinAssignment<Rx, PeripheralSignal::USART1_RX>
class UsartDriver { /* ... */ };

UsartDriver<PinId::PB6, PinId::PB7> ok;       // OK
UsartDriver<PinId::PA0, PinId::PA1> fails;    // template instantiation fails
```

**This is a structural moat over modm.**  modm's model is
string-based — they cannot enumerate per-pin-per-signal validity
at compile time without hand-writing each.  Our IR carries the
graph; the emitter just projects it into types.

The cost is tiny: one new emitted header, no IR changes, no patch
overlays.  The narrative payoff (compile-time pinmux correctness
proven from data) is the kind of demo that makes alloy-codegen
look qualitatively different.

## What Changes

### Emitted artifact

New per-device header:
`<vendor>/<family>/generated/runtime/devices/<device>/pin_validation.hpp`

Structure:

```cpp
#pragma once
#include "pins.hpp"
#include "peripheral_instances.hpp"

namespace st::stm32g0::generated::runtime::devices::stm32g071rb {

// Closed enum of every (peripheral, signal) pair with admitted
// connection candidates.  Names follow <PERIPHERAL>_<SIGNAL>
// canonicalised to upper snake-case.
enum class PeripheralSignal : std::uint16_t {
  SPI1_SCK = 0u,
  USART1_RX = 1u,
  USART1_TX = 2u,
  // ... one entry per admitted (peripheral, signal) pair
};

// Primary template — every (Pin, Signal) combo is invalid by default.
template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

// One specialisation per ConnectionCandidate in the IR.
template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::SPI1_SCK>
    : std::true_type {
  static constexpr std::string_view kRouteKind = "alternate-function";
  static constexpr std::uint8_t kAfNumber = 0u;
};

// C++20 concept — the consumer-friendly form.
template<PinId Pin, PeripheralSignal Signal>
concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;

// Closed-form constexpr lookup (handy for constexpr-evaluated config code).
constexpr bool is_valid_pin_assignment(PinId pin, PeripheralSignal sig) noexcept {
  // ... linear scan over a constexpr table
}

}  // namespace
```

The `kRouteKind` / `kAfNumber` / `kRouteSelector` constexprs on the
specialisation expose the per-route metadata the HAL needs to
**configure** the pinmux once it has been *validated* — so the
consumer driver doesn't need a second lookup into existing tables.

### Per-route specialisation: what gets emitted

Each `ConnectionCandidate` produces one specialisation with:

- `kRouteKind` — e.g. `"alternate-function"` (STM32), `"funcsel"` (RP2040), `"iomux"` (iMXRT), `"pio"` (SAM), `"io_matrix"` (ESP32).
- `kRouteSelector` — the selector index (AF0..AF15 for STM32, FUNCSEL for RP2040, etc.).
- `kRouteGroupId` — when the candidate is part of a connection group (some packages carry multi-pin "atomic" routings).

Note that **runtime C++ artifacts must not carry string literals**
(publication gate).  Each `kRouteKind` string lives in a closed
`enum class RouteKind` lifted into `pin_validation.hpp` and the
specialisation references the enum, not a `std::string_view`.

### Consumer ergonomics

Three usage patterns supported:

1. **Compile-time assertion** — `static_assert(ValidPinAssignment<PA1, SPI1_SCK>)` for sanity checks in driver setup.
2. **Concept-constrained templates** — `requires ValidPinAssignment<Tx, USART1_TX>` so passing a wrong pin yields a SFINAE error before instantiation.
3. **Constexpr lookup** — `is_valid_pin_assignment(pin, sig)` for code that branches on validity at runtime (rare in HAL-style drivers but useful for bootloaders).

### Coverage

Every device with a non-empty `device.connection_candidates`.  On
the 9 admitted families today, that's all of them — even when the
connection list is small (G0 fixture has 3 entries; the SAME70 +
iMXRT fixtures carry ~hundreds).

### What this DOES NOT do

- It does **not** validate pin **conflicts** (two drivers using the
  same pin in incompatible roles) — that's the
  `connection_groups` story, scope of a separate change
  (`emit-pinmux-conflict-checks`).
- It does **not** enforce package-aware filtering at compile time —
  the consumer is expected to pick pins admitted on the package
  they target.  Future change can fold `pin.packages` into the
  concept.

## Impact

**Strategic moat.**  modm structurally cannot project pin validity
into a typed concept set — their data model is hand-tabulated
strings.  alloy-codegen has the connection-graph as data, so this
emitter is a 200-LOC win that no competitor can replicate without
re-architecting their entire device model.

After this lands, the alloy HAL's `Spi::Master<Mosi, Miso, Sck, Cs>`
constructor can carry `requires ValidPinAssignment<Mosi,
PeripheralSignal::SPI1_MOSI>` etc. and refuse to instantiate when
the user tries to wire the wrong pin — at *compile time*, before
anything is flashed.

This is the flagship demo for "alloy proves at compile time what
modm proves at runtime (or never)".
