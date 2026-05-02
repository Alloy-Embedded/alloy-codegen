# alloy-codegen compile gate

Per-device compile gate that proves the emitted trait surface
(``peripheral_traits.h``, ``peripheral_id.hpp``, ``rcc_traits.hpp``,
``rcc_enable.hpp``) is well-formed C++ for **every admitted device**.

## What this catches

The byte-stable golden tests catch *regressions* on already-emitted
devices.  This compile gate catches the inverse failure mode: an
emitter change that produces output that **doesn't compile**, but
the goldens were never green for that device in the first place
(or are out-of-date and the regen would have surfaced the issue
later).

Concretely, the gate has caught (or would have caught) these issues
during the v2.1 RCC synthesis work:

* Missing ``HSI`` enumerator in ``ClockSourceConfig`` after a
  refactor — the probe TU references the clock-tree backend.
* H7 grouped-mux split (``i2c123src`` → ``i2c1/i2c2/i2c3``) silently
  producing an *invalid* trait line for STM32G0 (``tim15sel`` →
  ``tim1`` + ``tim5``) — the probe TU's ``constexpr`` reference
  to ``tim15::kKernelClockMux`` would have failed to resolve.
* Missing ``kGateModel`` line on a peripheral after the synthesiser
  failed to derive a gate-model enumerator — the probe TU's
  ``static_assert`` chain catches this directly.

## How it runs

Invoked via:

    python scripts/run_compile_gate.py [--device <id>] [--ci]

The driver:

1. Walks ``alloy_codegen.bootstrap.DEVICE_REGISTRY``.
2. For each ``(vendor, family, device)`` triple:
   * Generates a fresh emitted artifact tree under
     ``.cache/compile-gate/<ir-hash>/<device>/``.
   * Generates a probe TU at
     ``.cache/compile-gate/<ir-hash>/<device>/probe.cpp`` that
     references every peripheral's ``kBaseAddress`` and (where
     present) ``kGateModel``.
   * Invokes ``clang++`` with ``-std=c++20 -Wall -Werror -Wundef``
     against the probe TU.
3. Reports ✅ / ❌ / ⏭ per device.

No CMake, no link step, no embedded toolchain — the emitted headers
are pure ``constexpr``, so host clang validates them in milliseconds.

## CI integration

The ``compile-gate`` job in ``.github/workflows/tests.yml`` runs on
every PR.  Initial roll-out hard-fails on five reference fixtures
(one per ``GateModel`` enumerator):

| Fixture        | GateModel branch        |
|---------------|-------------------------|
| stm32g0b1cbtx  | ``per_peri_en_rst``      |
| rp2040         | ``per_peri_en``          |
| mimxrt1062     | ``index_based``          |
| avr64da32      | ``always_on``            |
| esp32c3        | ``per_peri_pcr``         |

The remaining ~600 admitted devices are gated as a *report-only*
matrix until ``complete-rcc-synthesis-cross-vendor`` archives.
