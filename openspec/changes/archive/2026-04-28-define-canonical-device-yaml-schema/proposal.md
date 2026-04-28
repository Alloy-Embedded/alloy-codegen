# Define Canonical Device YAML Schema

## Why

The repo is heading toward a two/three-repo split: `alloy-data-extractor`
(ETL from vendor sources) → `alloy-devices-yml` (canonical data, no
code) → `alloy-codegen` (C++ emission, eventually multi-language).

Before splitting we need a **stable, schema-validated YAML
representation** of `CanonicalDeviceIR` so both sides of the future
boundary know what they're agreeing on.  Today the IR exists only as
Python dataclasses + JSON serialization that's coupled to internal
field names; we need a canonical text form that:

- Stays stable across pipeline refactors.
- Is human-reviewable (~150KB / chip; comments allowed).
- Validates via JSON Schema (mature tooling, VS Code integration).
- Round-trips: `IR → YAML → IR` produces byte-identical output.

This is foundational for everything downstream — the data-repo
split, multi-language consumers, and bulk admission of 8000+
chips all depend on this contract being precise.

## What Changes

- New schema directory `schema/canonical_device/` shipping:
  - `device.schema.json` — top-level per-MCU schema (identity,
    memories, peripherals, interrupts, registers, register fields,
    enumerated values, clock tree, pinmux, DMA, capabilities,
    Tier 2/3/4 facts, provenance).
  - `family.schema.json` — per-family catalog (packages, shared
    pin definitions, IP-version registry).
  - `vendor.schema.json` — per-vendor metadata + provenance source
    list.
- `alloy_codegen.canonical_device_yaml` module:
  - `serialize_device(ir: CanonicalDeviceIR) -> str` — emit the
    canonical YAML text.
  - `parse_device(text: str) -> CanonicalDeviceIR` — read it back.
  - `validate_device(text: str) -> None` — schema-validate without
    parsing into IR.
  - Round-trip contract: `parse(serialize(ir)) == ir`,
    `serialize(parse(yaml)) == yaml` (byte-stable).
- New per-device emitter that ships a `<vendor>/<family>/devices/<device>.yml`
  alongside today's other emitted artifacts.  Same publication
  gate: deterministic, schema-validated.
- Validation gate in CI: every emitted device YAML SHALL pass
  `validate_device(...)`.
- Cross-validation test: every admitted device runs
  `parse(serialize(ir))` and asserts byte-stable round-trip.
- Documentation `docs/canonical-device-yaml.md` describes the
  schema, the round-trip contract, and the comment conventions
  for documenting silicon quirks.

## Impact

Once this lands, the IR has a stable text form that can be
extracted into a separate repo without destabilising the codegen
side.  Every downstream consumer (current C++ emitter, future
Rust PAC, future docs generator) reads the same YAML —
schema-validated, round-trippable, comment-friendly.

This is the contract that unlocks the entire two-repo split.

## What this DOES NOT do

- Does not split the repo yet.  The YAML emission is just an
  additional artifact; the existing pipeline + patches stay
  exactly where they are.
- Does not change the resolved IR.  The serialization is a
  faithful projection of today's `CanonicalDeviceIR`; consumers
  see no behavioural change.
- Does not add new fields.  Every field in the YAML schema
  corresponds to an existing IR field.  Schema evolution lands in
  follow-up changes.
- Does not consume the YAML.  `extract-alloy-devices-data-repo`
  is the change that flips the codegen to read YAML as its
  primary input.
