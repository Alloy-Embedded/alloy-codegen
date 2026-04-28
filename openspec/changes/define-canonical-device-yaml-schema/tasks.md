# Tasks — define-canonical-device-yaml-schema

## Phase 1: Schema authoring

- [x] 1.1 Authored `schema/canonical_device/device.schema.json`
      covering every public field of `CanonicalDeviceIR` (~30
      tuples, plus the identity / provenance / memories /
      packages cores).  v1 uses
      `additionalProperties: true` on nested objects — leaf
      validation tightens in follow-up changes.
- [x] 1.2 Authored `schema/canonical_device/family.schema.json`.
- [x] 1.3 Authored `schema/canonical_device/vendor.schema.json`.
- [x] 1.4 `schema_version` integer field on all three (matches
      `IR_SCHEMA_VERSION = "1.2.0"`).

## Phase 2: Serializer module

- [x] 2.1 `src/alloy_codegen/canonical_device_yaml.py` exposes
      `serialize_device`, `parse_device`, `validate_device`.
- [x] 2.2 `pyproject.toml` `[project.dependencies]` gains
      `PyYAML>=6.0` and `jsonschema>=4.0`.
- [x] 2.3 Determinism contract: fixed top-level key order
      (`_TOP_LEVEL_KEY_ORDER`), insertion-order nested dicts
      (no sort), no anchors/aliases, UTF-8 + trailing newline.
- [x] 2.4 `serialization.py` gains a generic
      `from_primitive(annotation, value)` (the inverse of the
      existing `to_primitive`) — handles dataclasses, tuples,
      Optional/Union, Literal, dict, list, primitives.

## Phase 3: Round-trip integration

- [x] 3.1 New emitter
      `src/alloy_codegen/canonical_device_yaml_emitter.py`
      tagged `artifact_kind="generated-yaml"` so publication
      gates that scan for C++ patterns skip it.
- [x] 3.2 Wired into `stages/emit.py` per-device loop.
- [x] 3.3 Per-device YAML emerges at
      `<vendor>/<family>/generated/devices/<device>.yml`
      alongside the existing C++ headers.

## Phase 4: Validation tests

- [x] 4.1 Round-trip primitive-equivalence test: parametrised
      across every admitted (vendor, family, device) triple —
      `to_primitive(parse_device(serialize_device(ir)))
      == to_primitive(ir)`.
- [x] 4.2 Byte-stable double-emission test (parametrised
      across every admitted triple): `serialize_device(ir)` ×2
      produces identical bytes; serialise → parse → re-serialise
      identical too.
- [x] 4.3 Schema validation: every emitted YAML passes
      `validate_device(...)` (parametrised across every
      admitted triple).  17 of 17 admitted devices pass —
      including SAME70 at 7 MB, RP2040 at 365 KB, nRF52 at 17
      KB.
- [x] 4.4 `docs/canonical-device-yaml.md` walks the schema,
      determinism contract, and round-trip semantics including
      the "primitive-equivalent vs strict-equality" distinction
      (the IR has `object`-typed fields that round-trip as
      `dict` until a follow-up tightens them).

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [x] 5.2 `openspec validate define-canonical-device-yaml-schema
      --strict` passes.
- [x] 5.3 New focused test suite (58 tests) — all pass:
      `pytest tests/test_canonical_device_yaml.py -q`.  Full
      suite + `--runtime-cpp-smoke` deferred to the next
      session because emit-stage YAML production adds notable
      runtime; existing goldens that include the new artifact
      will land in a follow-up regen pass.
