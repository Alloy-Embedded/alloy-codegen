## ADDED Requirements

### Requirement: Publish CI computes affected families per push

The publish workflow SHALL compute, before launching the per-family matrix,
the subset of admitted families whose inputs the current commit actually
affects.  Only those families' publish jobs run; the remaining families are
skipped without consuming CI compute.

The detection is path-based on the git diff between the workflow's "since"
ref and HEAD.  An override exists for forcing the full matrix.

#### Scenario: Single-family patch only re-publishes that family

- **WHEN** a commit touches **only** files under `patches/<vendor>/<family>/**`
  for one admitted pair
- **AND** the publish workflow runs (either via `workflow_run` from Bootstrap CI
  or `workflow_dispatch` without `force_all`)
- **THEN** the `detect-affected` job's matrix output contains exactly one entry
  `{vendor: <vendor>, family: <family>}`
- **AND** the publish job runs that single matrix job
- **AND** no other admitted family runs its publish job for this commit

#### Scenario: Source-adapter change scopes to that adapter's families

- **WHEN** a commit touches `src/alloy_codegen/sources/<basename>.py` and no
  other src files
- **THEN** the matrix output contains every `(vendor, family)` pair whose
  `SOURCE_BUNDLES` entry includes that adapter's source ID, and no others

#### Scenario: Architecture-specific runtime emitter scopes to that ISA

- **WHEN** a commit touches `src/alloy_codegen/runtime_xtensa_startup.py`
- **THEN** the matrix output is restricted to families whose `core` starts with
  `xtensa` (esp32, esp32s3) and excludes Cortex-M / RISC-V / AVR families
- **AND** analogous scoping holds for `runtime_riscv_startup.py`,
  `runtime_avr_startup.py`, and `runtime_startup.py` (Cortex-M)

#### Scenario: Docs-only and openspec-only changes skip the publish entirely

- **WHEN** a commit touches **only** files under `tests/**`, `openspec/**`,
  `*.md`, or `.github/workflows/bootstrap-family.yml`
- **THEN** the `detect-affected` job sets `should_publish=false` and the
  publish job does NOT run
- **AND** Bootstrap Family CI on the same commit still runs (those workflows
  are independent)

#### Scenario: Unknown-path changes fall back to the full matrix

- **WHEN** a commit touches a path the affected-families heuristic does not
  explicitly map (e.g., a new top-level config file, or a rename that the
  mapping has not yet learned)
- **THEN** the matrix output is the full admitted set
- **AND** the rationale "unknown path triggered conservative full-rebuild" is
  visible in the job log

#### Scenario: Manual `force_all` override bypasses detection

- **WHEN** the publish workflow is triggered via `workflow_dispatch` with
  `force_all: true`
- **THEN** `detect-affected` skips the git diff and emits the full matrix
- **AND** every admitted family runs its publish job regardless of what
  changed (or did not change) since the last commit

#### Scenario: Diff failure is treated as full matrix (safe default)

- **WHEN** the `git diff --name-only <since>...<head>` command fails (e.g.,
  shallow clone without enough history, missing ref)
- **THEN** the affected-families CLI returns `all_families: true` and a log
  line records the failure cause
- **AND** the matrix output is the full admitted set
