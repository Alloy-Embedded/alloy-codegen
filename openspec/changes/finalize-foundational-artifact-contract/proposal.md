## Why

`alloy-devices` already publishes most of the descriptor-first contract we want, but the last
gaps are important enough that we still should not call the pipeline "100% complete".

The remaining problems are not about adding more vendors or families. They are about closing the
contract for the foundational set we already admitted:

- the published C++ surface is still weaker than the published JSON surface, so the future Alloy
  runtime would still need to infer too much or parse metadata for some device-level questions
- publication can still succeed for a family whose own coverage report says that not every device
  is publishable
- the documented artifact contract still references bootstrap-era files that are no longer part of
  the intended end state
- the vendor-admission gate does not yet enforce "contract-complete" foundational families as
  strictly as it should

That means the repo is close, but not yet at the point where we can say:

- the generated contract is complete for the future Alloy architecture
- publication truth is consistent across validation, coverage, and publish outputs
- foundational vendor support is complete enough to serve as the generic base for vendor 4

This change closes those last gaps.

## What Changes

- **NEW** final artifact-contract requirements for the generated family tree, including
  device-scoped C++ descriptor entrypoints that Alloy can consume directly:
  - `generated/devices/<device>/device_descriptor.hpp`
  - `generated/devices/<device>/pins.hpp`
  - `generated/devices/<device>/peripheral_instances.hpp`
  - `generated/devices/<device>/capability_overlays.hpp`
- **NEW** publication-consistency rules so a family cannot be published when its own coverage or
  per-device readiness still says it is incomplete
- **NEW** documentation-synchronization requirements so the published contract docs cannot drift
  from the actual emitted tree
- **MODIFIED** vendor-admission rules so foundational families are considered truly complete only
  when they are contract-complete and publication-consistent on the hardened contract
- **FOUNDATIONAL COMPLETION** close remaining foundational-family holes that prevent "100%"
  readiness, including cases where a family is emitted and published but still reports one or more
  incomplete descriptor domains

## Impact

- Affected specs:
  - `artifact-contract`
  - `publication-consistency`
  - `vendor-admission`
- Affected code:
  - `src/alloy_codegen/emission.py`
  - `src/alloy_codegen/stages/emit.py`
  - `src/alloy_codegen/stages/publish.py`
  - `src/alloy_codegen/reporting.py`
  - `src/alloy_codegen/validation.py`
  - `docs/codegen-alloy-boundary.md`
  - `docs/artifact-layout.md`
  - smoke-consumer coverage and golden fixtures
  - foundational family normalization/patch data where domain completeness is still incomplete
