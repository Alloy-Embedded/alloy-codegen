## Why

The Alloy ecosystem needs a real device-data platform, not just a collection of scripts that
turn SVD files into headers. The new `alloy-codegen` repository must start from first
principles with a clean architecture that separates raw source ingestion, reproducible
patching, canonical normalization, validation, emission, and publication.

If we skip that separation and carry over legacy assumptions from the old generator, we will
recreate the same problems in a new repository: weak data contracts, vendor quirks leaking
into templates, fragile examples, and no trustworthy path to scale across families.

## What Changes

- **NEW** canonical multi-stage pipeline:
  `fetch -> patch -> normalize -> validate -> emit -> publish`
- **NEW** canonical device IR as the single source of truth for downstream emitters
- **NEW** reproducible patch layer for correcting upstream data without hidden fixups
- **NEW** validation system with explicit maturity gates that block progression to later
  phases
- **NEW** artifact contract for `alloy-devices`, including metadata, manifests, and
  generated C++ output
- **NEW** CLI model for operating the pipeline stage by stage and end to end
- **NEW** publication contract that releases artifacts only from validated pipeline states
- **NEW** remote publication workflow that can commit validated outputs into the real
  `alloy-devices` repository without pushing drift when the published tree is unchanged
- **NON-GOAL** reusing modm, stm32-data, chiptool, or svdtools directly as product
  dependencies; they inform the design but Alloy owns the implementation

## Impact

- Affected specs:
  - `source-ingestion`
  - `patch-and-normalization`
  - `canonical-device-ir`
  - `validation-and-gates`
  - `artifact-emission`
  - `publication-workflow`
  - `codegen-pipeline-cli`
- Affected code:
  - initial `alloy-codegen` repository structure
  - future pipeline CLI and schemas
  - future emitters for `alloy-devices`
  - future CI publication workflow
  - remote release automation into `alloy-devices`
