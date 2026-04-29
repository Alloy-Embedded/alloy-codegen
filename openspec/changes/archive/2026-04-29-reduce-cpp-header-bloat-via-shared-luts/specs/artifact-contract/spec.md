## ADDED Requirements

### Requirement: Per-instance trait headers SHALL share Tier 2/3/4 facts via a single constexpr lookup table per class

The pipeline SHALL emit, for peripheral classes whose emitted
trait header otherwise duplicates 40+ fields per instance
(PWM, TIMER, CAPABILITIES, and any future class with similar
shape),
one `inline constexpr std::array<<Class>HardwareLut, N>`
table at namespace scope and project per-instance trait
specialisations as thin template aliases that read from the
table.  The public reading API (`<Class>SemanticTraits<P>::k…`)
SHALL stay byte-compatible with consumers of the existing
shape.  The artifact size of the migrated headers SHALL
decrease by at least 20% versus the pre-migration baseline,
measured against the worst-case admitted device.

#### Scenario: iMXRT1062 pwm.hpp shrinks by ≥25%

- **WHEN** the pipeline emits `pwm.hpp` for mimxrt1062 after
  the migration
- **THEN** the artifact's UTF-8 byte size SHALL be at least
  25% smaller than its pre-migration value
- **AND** every consumer-visible
  `PwmSemanticTraits<P>::kField` access SHALL return the same
  compile-time value as before

#### Scenario: Public API stays byte-compatible

- **WHEN** a consumer reads `PwmSemanticTraits<PeripheralId::PWM1>::kPrescalerOptions`
  before and after the migration
- **THEN** the returned value SHALL be identical
- **AND** the existing runtime-cpp-smoke compile SHALL continue
  to pass without modification on the consumer side

#### Scenario: Footprint budget is tightened to lock in the win

- **WHEN** all three target emitters (PWM, TIMER, CAPABILITIES)
  have migrated
- **THEN** `data/artifact_footprint_budget.toml` SHALL be
  updated so each migrated artifact's `fail` budget is at most
  1.5× the new worst-case admitted size
- **AND** future regressions that re-bloat a header SHALL
  fail the publish stage
