## ADDED Requirements

### Requirement: CI SHALL enforce strict static typing on emitter and IR modules

The repository SHALL run `pyright` (or an equivalent strict
type checker) as part of CI.  The check SHALL run in strict
mode for the emitter and IR module trees
(`src/alloy_codegen/runtime_driver/**`,
`src/alloy_codegen/ir/**`,
`src/alloy_codegen/stages/**`) and in basic mode for the
remainder of `src/alloy_codegen/**` and all of `tests/**`.
Suppression comments SHALL carry a one-line justification of
the form `# pyright: ignore[<rule>]  # <reason>`.  Blank
suppressions (no rule, no reason) SHALL be rejected by CI.

#### Scenario: New PR introduces a strict-mode type error

- **WHEN** a contributor submits a PR that adds a function in
  `src/alloy_codegen/runtime_driver/uart.py` returning
  `str | None` and treating the result as `str` without
  narrowing
- **THEN** CI SHALL fail with the pyright error message
  pointing at the unnarrowed access
- **AND** the contributor SHALL fix the typing OR add a
  `# pyright: ignore[reportOptionalMemberAccess]` with a
  one-line justification

### Requirement: Every admitted device SHALL ship with full golden coverage

Every admitted device SHALL ship with a corresponding golden
artifact tree under `tests/fixtures/emitted/` covering every
file in
`data/devices/vendors/<v>/<f>/devices/*.yml`.  The coverage SHALL be exactly
100% on `main`.  The coverage dashboard
(`data/devices/coverage-dashboard.md`) SHALL surface the
ratio `golden_coverage = covered_devices / admitted_devices`
and CI SHALL fail any PR that drops the ratio below 100%.

#### Scenario: Admission of a new device requires goldens

- **WHEN** a contributor admits a new device (adds its YAML
  to `data/devices/vendors/<v>/<f>/devices/`)
- **THEN** CI SHALL fail until a corresponding golden tree
  is committed under `tests/fixtures/emitted/`
- **AND** the dashboard SHALL update to reflect the new
  device + its golden count

#### Scenario: Drift in an existing golden

- **WHEN** a code change accidentally drifts the emitted
  output for an existing device
- **THEN** the byte-stability gate SHALL fail the build
- **AND** the failure message SHALL show the device name,
  the affected artifact path, and a unified diff

### Requirement: Emitted artifacts and emitter Python SHALL avoid forbidden patterns

The codegen SHALL forbid patterns that compromise the
zero-overhead, exception-free, no-RTTI contract.  In any
emitted C++ file under `tests/fixtures/emitted/**` the
following are forbidden: `dynamic_cast`, `typeid`, raw `new`
and `delete`, and runtime string literals (already gated by
`find_runtime_cpp_string_violations`, extended here for
completeness).  In any emitter Python file under
`src/alloy_codegen/`, raising exceptions to communicate
emission failure is forbidden — emitters SHALL return
`EmittedArtifact | None` and surface failures through the
validation gates rather than via `raise`.

#### Scenario: Forbidden pattern surfaces in a generated artifact

- **WHEN** an emitter under modification accidentally writes
  a `dynamic_cast<…>` into a generated `.hpp`
- **THEN** the forbidden-pattern gate SHALL fail CI with the
  exact filename + line of the violation
- **AND** the failure message SHALL link to the pattern's
  rationale in `CONTRIBUTING.md`
