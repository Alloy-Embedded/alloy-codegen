# Add Additional Validity Concepts

## Why

`emit-pinmux-validator-concepts` shipped
`ValidPinAssignment<Pin, Signal>` — the proof that the IR carries
enough data to drive compile-time validation of pinmux choices.
The audit identified four more constraint pairs whose data is
already in the IR but never projected into a concept:

| Concept | Source data |
|---|---|
| `ValidDmaBinding<Peripheral, Channel>` | `dma_routes`, `dma_bindings` |
| `ValidClockSource<Peripheral, Source>` | `clock_gates`, `peripheral_clock_bindings` |
| `ValidInterruptSlot<Peripheral, Vector>` | `interrupt_bindings`, `vector_slots` |
| `ValidI2cSpeed<Peripheral, SpeedHz>` | `i2c_peripherals.speed_modes`, `system_clock_profiles` |

Drivers that today say "trust the user; runtime check" can flip
to `requires Valid<...>` constraints — refusing to instantiate
when the user wires the wrong DMA channel or asks for an
unreachable I2C baud rate.

## What Changes

- Per-concept emission via `runtime_<concept>.hpp` headers
  alongside the existing `pin_validation.hpp`:
  - `dma_validation.hpp` — `ValidDmaBinding<Peripheral, Channel>`
    + a `kDmaBindings[]` constexpr table.
  - `clock_validation.hpp` — `ValidClockSource<Peripheral, Source>`.
  - `interrupt_validation.hpp` — `ValidInterruptSlot<Peripheral,
    Vector>` (or merged into the existing `interrupts.hpp`).
  - `i2c_speed_validation.hpp` — `ValidI2cSpeed<Peripheral,
    SpeedHz>` template.  Implemented as a `consteval` predicate
    over `(speed_mode_set, kernel_clock_max_hz)` so the user can
    write `requires ValidI2cSpeed<I2C1, 400'000>`.
- All four follow the same shape as the pinmux concept: a
  primary template `: std::false_type {}` plus per-candidate
  full specialisations.
- The `static_assert(detail::kInvalidConnector<Pin>, "Invalid
  connector for SPI1_sck...")` ergonomic pattern from
  `connectors.hpp` is replicated in every new header so failed
  constraints emit human-readable error messages with the list
  of valid alternatives.
- `runtime-cpp-smoke` smoke `.cpp` exercises one
  `static_assert(Valid<...>)` per new concept per device, so a
  malformed specialisation breaks CI immediately.
- `pyproject.toml` ruff config gains no new entries — these are
  pure emitter additions.

## Impact

The structural moat over modm grows from 1 concept to 5.  Every
alloy HAL driver class can constrain its template parameters
against compile-time-validated peripheral wiring — DMA channels,
clock sources, IRQ vectors, I2C speeds.  Wrong choice = template
instantiation failure with a discoverable message, not a
runtime print.

## What this DOES NOT do

- Does not add new IR fields.  All four concepts read fields
  the IR already carries.
- Does not rewrite existing trait headers.  The new concept
  headers are additive; consumers opt into them via
  `requires`.
- Does not validate cross-concept constraints (e.g. "a DMA
  channel + an IRQ slot together don't conflict").  That's a
  separate `emit-pinmux-conflict-checks`-shaped change.
