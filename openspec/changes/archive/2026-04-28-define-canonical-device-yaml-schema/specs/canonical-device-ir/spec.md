## ADDED Requirements

### Requirement: The pipeline SHALL emit a canonical YAML representation per admitted device

The pipeline SHALL emit one schema-validated YAML file per
admitted device at
`<vendor>/<family>/generated/devices/<device>.yml` capturing
the full `CanonicalDeviceIR` (identity, memories, peripherals,
interrupts, registers, register fields, enumerated values,
clock tree, pinmux, DMA, capabilities, Tier 2/3/4 facts,
provenance).  The YAML MUST validate against the JSON Schema
shipped at `schema/canonical_device/device.schema.json` and
MUST round-trip back to a byte-identical IR via
`alloy_codegen.canonical_device_yaml.parse_device(...)`.
Serialisation MUST be deterministic — re-emitting on the same
IR produces byte-identical output.

#### Scenario: stm32g071rb emits a schema-validated canonical YAML

- **WHEN** the pipeline emits artifacts for stm32g071rb
- **THEN** the artifact set SHALL include
  `st/stm32g0/generated/devices/stm32g071rb.yml`
- **AND** that file SHALL pass
  `validate_device(...)` against
  `schema/canonical_device/device.schema.json`

#### Scenario: Round-trip preserves the IR exactly

- **WHEN** the canonical YAML for any admitted device is
  parsed back via `parse_device(text)`
- **THEN** the resulting `CanonicalDeviceIR` SHALL be equal
  (per dataclass `__eq__`) to the IR that produced the YAML
- **AND** re-serialising the parsed IR SHALL produce a string
  byte-identical to the input

#### Scenario: Determinism across runs

- **WHEN** the pipeline emits canonical YAML twice for the
  same device with the same source inputs
- **THEN** both emissions SHALL produce byte-identical text
- **AND** key order, list sorting, and whitespace SHALL match
  the contract documented in
  `docs/canonical-device-yaml.md`
