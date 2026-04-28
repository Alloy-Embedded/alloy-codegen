# Canonical Device YAML

Added by the OpenSpec change `define-canonical-device-yaml-schema`.

## What it is

A schema-validated YAML projection of `CanonicalDeviceIR`.  One
file per admitted MCU at:

```
<vendor>/<family>/generated/devices/<device>.yml
```

This is the foundation of the upcoming three-repo split:

```
alloy-data-extractor   → writes YAML
alloy-devices-yml      → owns the YAML files (data only)
alloy-codegen          → reads YAML, emits C++
alloy-codegen-rust     → future sibling, reads same YAML
```

## File layout

```yaml
schema_version: 1.2.0          # always first; matches IR_SCHEMA_VERSION
identity:                       # always second
  vendor: st
  family: stm32g0
  device: stm32g071rb
  package: lqfp64
  core: cortex-m0plus
  summary: …
provenance:                     # always third (where the data came from)
  source_id: stm32-open-pin-data
  source_path: …
  patch_ids: […]

memories: [...]
packages: [...]
peripherals: [...]
interrupts: [...]
registers: [...]
register_fields: [...]
clock_nodes: [...]
clock_selectors: [...]
peripheral_clock_bindings: [...]
connection_candidates: [...]
…  # see schema/canonical_device/device.schema.json for the full surface
```

## Determinism contract

The serialiser guarantees:

1. **Fixed top-level key order.**  `schema_version` → `identity` →
   `provenance` → memory + structure → behaviour.  Codified in
   `canonical_device_yaml._TOP_LEVEL_KEY_ORDER`.
2. **Insertion-order nested dicts.**  `to_primitive(...)` walks
   dataclass fields in declaration order; the YAML dumper preserves
   it (no `sort_keys=True`).
3. **No anchors / aliases.**  Every YAML node is a literal — no
   `&anchor` or `*alias` shortcuts.  Output is portable to any
   YAML parser.
4. **UTF-8 + trailing newline.**  Standard `text` artifact shape.
5. **Byte-stable double-emission.**  `serialize_device(ir)` twice
   produces identical bytes.
6. **Round-trip primitive equivalence.**
   `to_primitive(parse_device(serialize_device(ir))) == to_primitive(ir)`.

### What round-trip does NOT guarantee (today)

`ir == parse_device(serialize_device(ir))` is **not** strict IR
equality.  A small set of `CanonicalDeviceIR` fields are typed
`object` (intentional — avoids circular imports with
`patches.py`).  Those fields round-trip as `dict`, not as their
original Patch dataclass.  Primitive equivalence (the contract
above) still holds — and that's what `alloy-devices-yml`
consumers care about.  A follow-up change can tighten this when
the data-repo split makes the coupling viable.

## Schema validation

```python
from alloy_codegen.canonical_device_yaml import validate_device

text = open("st/stm32g0/generated/devices/stm32g071rb.yml").read()
validate_device(text)  # raises StageExecutionError on failure
```

The schemas live at `schema/canonical_device/{device,family,vendor}.schema.json`.
v1 is intentionally permissive at the leaf level (uses
`additionalProperties: true` on nested shapes) — it validates
top-level structure + required fields.  Tightening per-field
constraints is incremental work that lands in follow-up changes.

## Adding a new IR field

1. Add the field to `CanonicalDeviceIR` (`src/alloy_codegen/ir/model.py`).
2. If new field has a default → no schema bump needed (older
   YAMLs continue to validate).
3. If new field is required → bump `schema_version` and update
   `device.schema.json`'s `required` list.
4. Verify round-trip on every admitted device:
   `pytest tests/test_canonical_device_yaml.py -q`.

The top-level key-order list (`_TOP_LEVEL_KEY_ORDER`) auto-falls
back to "unknown keys appended in natural order" so a new field
emerges in YAML without manual ordering work.

## Comments

YAML comments survive load → write only when using
`ruamel.yaml` round-trip mode.  The current serializer uses
`PyYAML` (faster, simpler) and **drops** comments on read.

If contributors need to attach commentary to a device YAML
(silicon errata, datasheet rev pin, …), the canonical place is a
sibling Markdown file:
`<vendor>/<family>/generated/devices/<device>.notes.md`.
