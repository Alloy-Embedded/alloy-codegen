## ADDED Requirements

### Requirement: Emitter modules SHALL stay under a maintainability size cap

No single emitter Python module SHALL exceed 5.000 lines of
code (LOC).  When a module crosses the threshold, the
contributor SHALL split it into a sub-package along the
natural boundary — per peripheral class, per artifact
category, or per vendor adapter family — whichever fits
the module's responsibility surface.  The rationale is to
prevent the change-blast-radius problems that monolithic
files create (any modification potentially touches dozens of
unrelated builders), to keep IDE navigation responsive, and
to localise type-checker and lint noise.  The cap is a
forcing function against future drift back into a monolith.

#### Scenario: CI rejects an oversized emitter module

- **WHEN** a contributor submits a PR that pushes any file
  under `src/alloy_codegen/runtime_*` or
  `src/alloy_codegen/runtime_driver/` past 5.000 LOC
- **THEN** CI SHALL fail with a message naming the
  offending file, its LOC count, and the suggested split
  boundary
- **AND** the PR SHALL be unmergeable until the file is
  split

#### Scenario: Refactor of runtime_driver_semantics.py validates the rule

- **WHEN** the `refactor-runtime-driver-semantics-per-class`
  change ships
- **THEN** `runtime_driver_semantics.py` SHALL shrink to a
  re-export shim around 50 lines and 17 per-class modules
  SHALL exist under `src/alloy_codegen/runtime_driver/`
- **AND** every emitted artifact SHALL be byte-identical to
  the pre-refactor output (golden-byte-stability gate)

### Requirement: Refactor changes SHALL preserve byte-stability of all emitted artifacts

Refactor changes SHALL pass a golden-byte-stability gate when
they are tagged in OpenSpec as a `refactor-*` (no intentional
behaviour change).  Every emitted artifact — every `.hpp`, `.cpp`, `.json`,
`.cmake`, and `.ld` file under `tests/fixtures/emitted/` —
SHALL match byte-for-byte before and after the refactor.  The
gate SHALL apply to all admitted devices, not just the ones
with golden fixtures today.  Devices without golden fixtures
SHALL get them generated as part of the refactor's CI prep,
so the byte-stability check covers the full admitted set
once the refactor lands.

#### Scenario: Byte-drift detection on a refactor PR

- **WHEN** a contributor submits a `refactor-*` PR that
  inadvertently introduces whitespace drift in one emitted
  header
- **THEN** the byte-stability gate SHALL flag the affected
  device + artifact
- **AND** CI SHALL block the merge with a diff snippet
  showing exactly which bytes drifted
- **AND** the contributor SHALL either fix the regression or
  re-tag the change as a non-refactor (which then requires
  a proposal explaining the behaviour change)
