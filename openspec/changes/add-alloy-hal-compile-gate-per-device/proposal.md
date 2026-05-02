# Add Alloy-HAL Compile Gate Per Admitted Device

## Why

The v2.1 codegen now emits a typed RCC trait surface
(``kBus``, ``kRccEnable``, ``kRccReset``, ``kKernelClockMux``, and
the upcoming ``kGateModel`` from
``complete-rcc-synthesis-cross-vendor``) on every peripheral.  The
golden tree proves the *emitted bytes* are stable.  Nothing in CI
proves those bytes **compile under a real C++ toolchain** against
the alloy HAL drivers — and history shows this gap matters:

* Tranche 1 RCC synthesis broke the F0/F1/F3 PLL emitter only
  because the goldens were stable; a HAL compile would have caught
  the missing ``HSI`` source enum at PR time.
* The H7 grouped-mux split (``i2c123src`` → ``i2c1/i2c2/i2c3``)
  silently produced an *invalid* trait line for STM32G0 (``tim15sel``
  → ``tim1`` / ``tim5``) until a manual goldens diff caught it.
* The ESP32 / iMXRT / SAMD21 RCC gaps that
  ``complete-rcc-synthesis-cross-vendor`` is closing aren't
  currently visible to CI at all — the goldens just look "small but
  consistent".

Manual review of golden diffs cannot scale to ~600 admitted devices.
We need an automated gate that catches every "the codegen emitted
something that doesn't compile" regression before it lands on
``main``.

The gate also provides the *contract proof* the alloy boundary
needs: every requirement on
``codegen-alloy-boundary/spec.md`` (e.g. "every peripheral SHALL
carry a ``kGateModel``") becomes self-checking once a HAL driver
actually consumes it.

## What Changes

### A. New ``alloy-codegen-compile-gate/`` test harness

A new top-level directory under ``tests/`` holds a single CMake
project that:

1. Lists every admitted device under
   ``tests/alloy-codegen-compile-gate/devices/<vendor>/<family>/<device>/``
   with a one-line ``CMakeLists.txt`` adding the device's emitted
   ``peripheral_traits.h`` / ``peripheral_id.hpp`` /
   ``rcc_traits.hpp`` / clock-tree headers as include paths.
2. Compiles a minimal *probe* translation unit per device that:
   * Includes every emitted header.
   * Instantiates ``RccTraits<P>::EnableClock()`` for every
     peripheral via a fold over ``PeripheralId``.
   * Instantiates the clock-tree backend's ``Configure(default)``.
   * Static-asserts ``kGateModel`` is one of the five enumerators.
3. Builds with ``-std=c++20 -Wall -Werror -Wundef -Wmissing-declarations``
   on host (``arm-none-eabi-g++``-equivalent flags via
   ``--target=armv7m-none-eabi`` Clang for cross-architecture
   discipline; CI uses Clang to keep one toolchain).

The probe TU lives at
``tests/alloy-codegen-compile-gate/probe.cpp`` and is shared
across devices via CMake's per-target include path.

### B. ``scripts/run_compile_gate.py`` driver

A Python wrapper that:

* Walks ``alloy_codegen.bootstrap.DEVICE_REGISTRY``.
* Regenerates each device's emitted tree to a temp dir (idempotent;
  reuses cached generation if the IR hash hasn't changed).
* Invokes CMake + Clang per device with ``-DDEVICE=<id>``.
* Collects pass/fail/skip per device and prints a coverage matrix
  matching the proposal's "Coverage matrix" tables.
* Exits non-zero on any compile failure.

Invocation: ``python scripts/run_compile_gate.py``.  CI runs
``--ci`` flag which sets ``-j$(nproc)`` and fails fast on the first
broken device.

### C. CI integration

A new GitHub Actions job ``compile-gate`` is added to the existing
``.github/workflows/ci.yml`` that:

* Runs after the existing goldens job (so the goldens-being-stale
  failure mode is reported first, before the compile-gate noise).
* Caches Clang and the regenerated device trees keyed on
  ``alloy_codegen/`` source hash.
* Annotates PRs with a "compile gate" check showing
  pass/fail per admitted device.

### D. Per-vendor smoke driver fixtures

For three representative devices per gate model, a *real* HAL smoke
driver is added to prove the trait surface plumbs through to a
working executable (not just a compile):

* ``stm32g0b1`` — ``per_peri_en_rst`` reference (LPUART1 EnableClock
  → trace via QEMU).
* ``rp2040`` — ``per_peri_en`` reference (UART0 EnableClock).
* ``mimxrt1062`` — ``index_based`` reference (LPUART1 EnableClock,
  parses ``ccm.ccgr5.cg12``).
* ``avr64da32`` — ``always_on`` reference (no-op short-circuit).
* ``esp32c3`` — ``per_peri_pcr`` reference (UART0 PCR path).

These fixtures run under simulator (QEMU for ARM, qemu-system-xtensa
for ESP32, simavr for AVR-Dx) and assert the expected register
write happens.

## Impact

**Affected capabilities**:

* `validation-and-gates` — adds the per-device compile-gate
  requirement.
* `codegen-alloy-boundary` — adds the requirement that every
  emitted peripheral trait surface SHALL be compile-clean against
  the alloy HAL probe TU.

**New dependencies (CI-only)**:

* ``clang-18`` (already in CI image).
* ``cmake>=3.25`` (already in CI image).
* ``qemu-system-arm``, ``qemu-system-xtensa``, ``simavr`` for the
  smoke fixtures.

**Affected admitted devices**: all ~600 devices in
``DEVICE_REGISTRY``.  Initial roll-out gates the 5 reference
fixtures hard; the remaining ~595 are gated as a *report-only*
matrix until the per-vendor synthesis from
``complete-rcc-synthesis-cross-vendor`` is in.  Once that proposal
lands, the report-only gate is flipped to hard-fail.

**Out of scope**:

* The HAL drivers themselves — they live in the alloy repo, not
  here.  This proposal only adds the *probe* TU that proves the
  trait surface is well-formed.
* Runtime correctness beyond the 5 smoke fixtures — proving
  ``EnableClock()`` wakes a peripheral on real silicon is the alloy
  HAL test suite's job, not ours.
* Multi-toolchain (GCC + IAR + ARMCC) coverage — Clang-only for v1.
