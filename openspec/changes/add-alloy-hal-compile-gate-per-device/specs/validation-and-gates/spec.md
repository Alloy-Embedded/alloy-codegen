## ADDED Requirements

### Requirement: Codegen output SHALL compile against the alloy HAL probe TU for every admitted device

Every device in ``alloy_codegen.bootstrap.DEVICE_REGISTRY`` SHALL produce an emitted artifact tree (``peripheral_traits.h``, ``peripheral_id.hpp``, ``rcc_traits.hpp``, and the clock-tree backend header) that compiles cleanly under the alloy HAL probe translation unit at ``tests/alloy-codegen-compile-gate/probe.cpp`` with flags ``-std=c++20 -Wall -Werror -Wundef -Wmissing-declarations -ffreestanding -nostdlib``.  The probe TU SHALL include every emitted header, instantiate ``RccTraits<P>`` for every ``PeripheralId`` enumerator, and static-assert that ``kGateModel`` is one of the five enumerators defined in the canonical-device-ir capability.

A single device's compile failure SHALL fail the ``compile-gate`` CI job and block PR merge.  The job SHALL print a coverage matrix listing pass / fail / skip per ``(vendor, family, device)`` triple so reviewers can see at a glance which devices are blocked.

#### Scenario: New peripheral lands without a `kGateModel` constexpr

- **WHEN** a contributor adds a new peripheral to a device YAML
  without populating its synthesised ``per_rcc_map`` entry
- **THEN** the codegen emitter SHALL omit the ``kGateModel`` line
  for that peripheral
- **AND** the probe TU's static-assert on ``kGateModel`` SHALL fail
  to compile
- **AND** the ``compile-gate`` CI job SHALL fail with a diagnostic
  pointing to the peripheral and the missing trait

#### Scenario: STM32 PLL emitter regression is caught at PR time

- **WHEN** a refactor of the STM32 clock-tree emitter accidentally
  drops the ``HSI`` source enumerator from
  ``ClockSourceConfig``
- **THEN** the goldens for every STM32 device SHALL change (and
  the goldens job either flags or accepts the regen)
- **AND** the ``compile-gate`` CI job SHALL fail because the probe
  TU's ``Configure(default)`` body references ``ClockSource::Hsi``
- **AND** the failure SHALL surface BEFORE manual goldens review,
  not after

#### Scenario: Report-only mode flips to hard-fail after RCC synthesis lands

- **WHEN** ``complete-rcc-synthesis-cross-vendor`` archives and
  every admitted device has either a populated ``en`` path or a
  ``gate_model`` marker
- **THEN** the ``compile-gate`` CI invocation SHALL drop the
  ``--report-only`` flag
- **AND** every device in ``DEVICE_REGISTRY`` SHALL be a hard-fail
  gate from that PR forward
- **AND** the report-only escape hatch SHALL be removed from
  ``scripts/run_compile_gate.py``
