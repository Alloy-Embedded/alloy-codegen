## Why

Two system bring-up domains are still under-published in `alloy-devices`:

- `startup` only emits descriptors plus a nearly-empty `startup_vectors.cpp`
- `clock-reset` only emits peripheral gate/reset/selector bindings, not system clock bring-up

That keeps `alloy` and end users responsible for handwritten reset handlers, vector tables, and
board-specific PLL/source/prescaler setup. Those are not optional details; they are part of the
minimum usable MCU bring-up contract.

## What Changes

- publish a generated `startup.cpp` per device with vector table materialization and a generated
  reset-handler baseline
- extend canonical IR and patches with typed system-clock profile metadata
- publish `generated/runtime/devices/<device>/system_clock.hpp` with typed profiles and generated
  bring-up helpers for foundational devices
- harden validation and publish gates so foundational families cannot ship without generated
  startup code and system clock bring-up coverage

## Impact

- users no longer need to handwrite startup translation units for supported devices
- Alloy can consume generated startup and system-clock contracts instead of board-local manual
  register recipes
- foundational families gain a publishable path for safe/default/high-performance clock profiles
  without runtime string parsing or handwritten per-board glue
