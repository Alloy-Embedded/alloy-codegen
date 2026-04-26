## MODIFIED Requirements

### Requirement: Admitted families SHALL pass a GPIO-semantic coverage gate

Every admitted MCU family SHALL emit a `driver_semantics/gpio.hpp` that
contains at least one `GpioSemanticTraits<PinId::...>` specialization with
`kPresent = true` once this change is applied to the family in question.
A repository-level CI gate SHALL fail PRs that admit a new family without
populated GPIO semantics, or that regress an existing family back to a
zero-specialization state.

The gate is rolled out per-family alongside the implementation phase that
populates that family. The gate becomes mandatory for every admitted family
once the final implementation phase lands. **As of `complete-rp2040-semantics`
Phase A, the gate is mandatory for RP2040 — the previous `xfail` marker
on the RP2040 case is removed and the family is expected to emit at
least one populated `GpioSemanticTraits` specialization.**

#### Scenario: GPIO coverage gate accepts a populated family

- **WHEN** a family that has been wired through the GPIO-semantic emitter
  emits its `gpio.hpp`
- **THEN** the file contains at least one specialization where
  `kPresent = true`
- **AND** the coverage gate passes for that family

#### Scenario: GPIO coverage gate blocks a regression

- **WHEN** a family that previously emitted populated `GpioSemanticTraits`
  specializations is changed in a way that drops all specializations
- **THEN** the coverage gate flags the family as regressed and the CI job
  fails

#### Scenario: RP2040 is included in the mandatory gate

- **WHEN** `tests/test_gpio_semantic_coverage.py` runs
- **THEN** the rp2040 device emits at least one `GpioSemanticTraits`
  specialization with `kPresent = true`
- **AND** the test does NOT carry an `xfail` marker for RP2040
