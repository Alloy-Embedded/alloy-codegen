## Why

The generator is now strong on one rare axis: a typed, runtime-only, multi-vendor contract with
no reflection in the Alloy hot path.

That is necessary, but it is not sufficient to become best-in-class.

To beat vendor tooling consistently, the generator still needs a stronger moat in the places where
vendor tools are weakest:

- full system-control semantics instead of partial peripheral facts
- formal capability contracts instead of schema heuristics
- provenance and explainability for every generated decision
- validation and publish gates that prove correctness, determinism, and drift resistance

Without those, the contract stays efficient but not yet authoritative.

## What Changes

- extend canonical IR with a full system-control fabric model:
  - clock roots/domains/dependencies
  - reset controls and sequencing dependencies
  - interrupt slots/bindings/default routing facts
  - power and enable domains where applicable
- publish typed runtime contracts for those system-control domains
- add a formal peripheral capability model to the runtime contract
- add generated provenance and explainability artifacts that show why facts were emitted, inferred,
  patched, rejected, or left unsupported
- harden validation and publication gates around determinism, foundational coverage, capability
  completeness, and explainability coverage

## Impact

- Alloy and downstream users can reason about bring-up and peripheral support through a richer,
  typed contract instead of reconstructing intent from low-level facts
- vendor/source drift becomes easier to diagnose because emitted facts carry provenance and
  explanation
- publication quality becomes a real competitive advantage instead of just a codegen convenience

