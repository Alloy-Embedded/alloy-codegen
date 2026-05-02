# Tasks — add-alloy-hal-compile-gate-per-device

## Phase 1: Probe TU + minimal CMake harness

- [ ] 1.1 Create ``tests/alloy-codegen-compile-gate/probe.cpp``.
      Includes ``peripheral_traits.h``, ``peripheral_id.hpp``,
      ``rcc_traits.hpp`` (or whichever name lands from
      ``complete-rcc-synthesis-cross-vendor``), and the clock-tree
      backend header.  Body: a constexpr fold over every
      ``PeripheralId`` enumerator that touches ``kBus``,
      ``kRccEnable``, ``kRccReset``, ``kKernelClockMux``, and
      ``kGateModel``.  Static-asserts ``kGateModel`` is in the
      closed five-value set.
- [ ] 1.2 Create ``tests/alloy-codegen-compile-gate/CMakeLists.txt``
      with a ``add_compile_gate_device(<vendor> <family> <device>)``
      function that adds one library target per device with the
      device's emitted include directory and ``probe.cpp`` as the
      single TU.
- [ ] 1.3 Build flags: ``-std=c++20 -Wall -Werror -Wundef
      -Wmissing-declarations -ffreestanding -nostdlib`` so the probe
      doesn't accidentally pull in libc symbols that hide bugs.
- [ ] 1.4 Smoke-build for ``stm32g0b1`` locally to prove the harness
      works end-to-end before scaling.

## Phase 2: Per-device driver script

- [ ] 2.1 Create ``scripts/run_compile_gate.py``.  Walks
      ``alloy_codegen.bootstrap.DEVICE_REGISTRY``, regenerates each
      device's emitted tree under a temp dir keyed on the IR hash,
      and invokes the CMake harness once per device.
- [ ] 2.2 ``--report-matrix`` flag prints a vendor / family / device
      table with ✅ / ❌ / ⏭ per device, matching the format used in
      ``complete-rcc-synthesis-cross-vendor``'s coverage matrix.
- [ ] 2.3 ``--ci`` flag enables fail-fast and ``-j$(nproc)``;
      default mode runs serial and continues on failure to surface
      every broken device per run.
- [ ] 2.4 Cache the regenerated tree under
      ``.cache/compile-gate/<ir-hash>/`` so re-runs on the same IR
      skip codegen entirely.

## Phase 3: CI integration

- [ ] 3.1 Add a ``compile-gate`` job to ``.github/workflows/ci.yml``
      that depends on the existing ``goldens`` job.
- [ ] 3.2 Cache Clang + CMake + the regenerated device trees keyed
      on ``alloy_codegen/`` and ``device-registry`` content hashes.
- [ ] 3.3 Initial roll-out: hard-fail on the 5 reference fixtures
      (stm32g0b1, rp2040, mimxrt1062, avr64da32, esp32c3); report-
      only on the remaining devices.
- [ ] 3.4 After ``complete-rcc-synthesis-cross-vendor`` archives,
      flip the report-only gate to hard-fail by removing the
      ``--report-only`` flag from the CI invocation.

## Phase 4: Smoke driver fixtures (one per gate model)

- [ ] 4.1 ``tests/alloy-codegen-compile-gate/fixtures/stm32g0b1_lpuart1.cpp``
      — instantiates ``LpuartDriver<lpuart1>::EnableClock()``,
      asserts the expected ``rcc.apbenr1.lpuart1en`` MMIO write
      happens under QEMU.
- [ ] 4.2 ``rp2040_uart0.cpp`` — RP2040 ``per_peri_en`` smoke; asserts
      ``resets.reset.uart0`` is cleared.
- [ ] 4.3 ``mimxrt1062_lpuart1.cpp`` — iMXRT ``index_based`` smoke;
      asserts ``ccm.ccgr5.cg12`` is set to ``11`` (run-mode).
- [ ] 4.4 ``avr64da32_usart0.cpp`` — AVR-Dx ``always_on`` smoke;
      asserts ``EnableClock()`` is a no-op (zero MMIO writes).
- [ ] 4.5 ``esp32c3_uart0.cpp`` — ESP32-C3 ``per_peri_pcr`` smoke;
      asserts ``pcr.uart0_conf_reg.uart0_clk_en`` is set.
- [ ] 4.6 CI runs each fixture under its simulator
      (``qemu-system-arm`` for ARM, ``qemu-system-xtensa`` /
      ``qemu-system-riscv32`` for ESP32, ``simavr`` for AVR) and
      asserts the captured MMIO trace matches the expected pattern.

## Phase 5: Spec deltas + verification

- [ ] 5.1 ADDED ``validation-and-gates`` requirement: "Codegen
      output SHALL compile against the alloy HAL probe TU for every
      admitted device".
- [ ] 5.2 ADDED ``codegen-alloy-boundary`` requirement: "Every
      emitted ``peripheral_traits.h`` SHALL be compile-clean against
      the alloy HAL probe TU under ``-Wall -Werror -Wundef``".
- [ ] 5.3 Run ``openspec validate add-alloy-hal-compile-gate-per-device
      --strict`` clean.
- [ ] 5.4 Verify CI ``compile-gate`` job goes green on the 5
      reference fixtures and the report-only matrix matches
      expectation (every gate-model branch covered).
