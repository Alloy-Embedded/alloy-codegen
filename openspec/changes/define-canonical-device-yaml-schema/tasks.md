# Tasks — define-canonical-device-yaml-schema

## Phase 1: Schema authoring

- [ ] 1.1 Author `schema/canonical_device/device.schema.json`
      covering every public field of `CanonicalDeviceIR`.
- [ ] 1.2 Author `schema/canonical_device/family.schema.json`
      for the per-family catalog (packages, pins, IP-version
      registry).
- [ ] 1.3 Author `schema/canonical_device/vendor.schema.json`
      for vendor metadata + provenance source list.
- [ ] 1.4 Add `schema_version` integer to all three schemas;
      seed at 1.

## Phase 2: Serializer module

- [ ] 2.1 Create `src/alloy_codegen/canonical_device_yaml.py`:
      - `serialize_device(ir) -> str` (uses `ruamel.yaml` for
        comment-preservation + key-order stability).
      - `parse_device(text) -> CanonicalDeviceIR`.
      - `validate_device(text)` schema-validates via
        `jsonschema`.
- [ ] 2.2 Add `pyyaml` + `jsonschema` + `ruamel.yaml` to
      `pyproject.toml` dependencies.
- [ ] 2.3 Determinism contract: `serialize` emits keys in a
      fixed order, lists sorted, no anchor/alias usage, trailing
      newline.

## Phase 3: Round-trip integration

- [ ] 3.1 New emitter
      `src/alloy_codegen/canonical_device_yaml_emitter.py`
      writes one `<vendor>/<family>/devices/<device>.yml` per
      admitted device alongside today's runtime headers.
- [ ] 3.2 Wire into `stages/emit.py` per-device loop.
- [ ] 3.3 Add a per-device golden under
      `tests/fixtures/emitted/<family>/.../<device>.yml`.

## Phase 4: Validation tests

- [ ] 4.1 Round-trip test: for every admitted device,
      `parse_device(serialize_device(ir))` returns an IR
      equal to the input.
- [ ] 4.2 Byte-stability test: serialize twice → byte-identical
      output.
- [ ] 4.3 Schema validation: every emitted YAML passes
      `validate_device(...)` in CI.
- [ ] 4.4 Documentation `docs/canonical-device-yaml.md` walks
      through the schema + round-trip contract.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [ ] 5.2 `openspec validate define-canonical-device-yaml-schema
      --strict` passes.
- [ ] 5.3 `pytest -q` + `ruff check` clean.
- [ ] 5.4 `pytest --runtime-cpp-smoke` stays green.
