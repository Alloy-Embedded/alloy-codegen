## ADDED Requirements

### Requirement: Device patches MUST be diffs over a source-derived baseline

The pipeline SHALL build a "source-derived baseline IR" for every
device from authoritative vendor sources (CMSIS-SVD, ATDF, Zephyr
DTS, modm-devices, etc.) before applying any patch.  The
`patches/<vendor>/<family>/devices/<device>.json` file SHALL
contain only the **diff** between that baseline and the desired
final IR — no field that matches the baseline value SHALL appear
in the patch.  The patch SHALL declare a top-level
`"$baseline-revision"` recording the source identifier the diff
was computed against, so the pipeline can detect when the vendor
source updates and the diff needs re-review.

#### Scenario: Patch contains only overrides, not redundant baseline data

- **WHEN** a device patch is loaded
- **AND** the validation gate compares each leaf value to the
  source-derived baseline
- **THEN** every leaf in the patch SHALL differ from the baseline
- **AND** any leaf that matches the baseline SHALL fail validation
  with a message identifying the redundant field

#### Scenario: Stale baseline revision blocks the load by default

- **WHEN** a patch's `$baseline-revision` does not match the
  current vendor-source identifier
- **THEN** the loader SHALL fail with a clear message identifying
  which source moved
- **AND** the failure SHALL be overridable with an explicit
  `--accept-stale-baselines` flag, so reviewers can opt in to
  using a stale diff while they re-derive it

#### Scenario: Resolved IR after diff merge is identical to today's full-patch IR

- **WHEN** a family migrates to the diff model
- **AND** `scripts/minify_device_patches.py` rewrites every
  device patch in place
- **THEN** the resolved in-memory IR after baseline + diff merge
  SHALL be byte-identical to the IR produced before the migration
- **AND** every emitted artifact SHALL be byte-identical to its
  pre-migration golden
