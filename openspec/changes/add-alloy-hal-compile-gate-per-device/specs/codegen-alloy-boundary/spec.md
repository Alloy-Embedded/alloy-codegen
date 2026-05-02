## ADDED Requirements

### Requirement: Emitted trait surface SHALL be compile-clean against the alloy HAL probe TU

Every emitted ``peripheral_traits.h`` MUST compile cleanly when included by the alloy HAL probe translation unit at ``tests/alloy-codegen-compile-gate/probe.cpp`` under ``-std=c++20 -Wall -Werror -Wundef -Wmissing-declarations`` with no ``#ifdef <vendor>`` / ``#if __has_include`` escape hatches.  This means: every typed ``constexpr`` line the emitter produces (``kBus``, ``kRccEnable``, ``kRccReset``, ``kKernelClockMux``, ``kGateModel``, plus the rich-metadata extensions from ``extend-peripheral-traits-with-rich-metadata``) MUST refer to enumerators / typed values that exist in headers the probe TU already pulls in via the canonical include order, and MUST NOT depend on hand-written HAL fall-back headers to fill in missing enums.

A trait line that compiles only because the alloy HAL hand-defines a "sentinel value" enum (e.g. ``ClockSource::Unknown``) for missing codegen output SHALL be considered a violation: the codegen surface MUST be self-sufficient.

#### Scenario: AVR-Dx peripheral compiles with no `kRccEnable` reference

- **WHEN** the probe TU includes the avr64da32 ``peripheral_traits.h``
- **THEN** every peripheral's ``kGateModel`` SHALL be
  ``GateModel::always_on``
- **AND** the probe TU's ``RccTraits<P>::EnableClock()`` body SHALL
  short-circuit to a no-op via the ``constexpr if`` on
  ``kGateModel``
- **AND** the probe TU SHALL NOT reference ``kRccEnable`` /
  ``kRccReset`` on any AVR-Dx peripheral path — even though those
  symbols may not exist on the AVR-Dx trait surface, the code path
  is unreachable via ``constexpr if``

#### Scenario: iMXRT peripheral compiles with `index_based` MMIO write

- **WHEN** the probe TU includes the mimxrt1062 ``peripheral_traits.h``
- **THEN** ``lpuart1::kGateModel`` SHALL be
  ``GateModel::index_based``
- **AND** the probe TU's ``RccTraits<lpuart1>::EnableClock()`` SHALL
  parse ``kRccEnable`` (``"ccm.ccgr5.cg12"``) verbatim through the
  shared register-path parser
- **AND** the parser MUST resolve to a typed
  ``RegisterFieldRef{ccm, ccgr5, cg12}`` at compile time without
  any per-peripheral specialisation

#### Scenario: New trait field doesn't break the probe TU

- **WHEN** a future change adds a new ``kFooBar`` constexpr line to
  ``peripheral_traits.h``
- **THEN** the change SHALL also extend the probe TU to reference
  ``kFooBar`` (so the new surface is exercised, not just emitted)
- **AND** the ``compile-gate`` CI job SHALL fail until the probe
  TU is extended — preventing "emit-only" surfaces that no consumer
  ever touches
