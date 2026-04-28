## ADDED Requirements

### Requirement: alloy-codegen SHALL admit devices from alloy-devices-yml without per-device bootstrap entries

The pipeline SHALL discover admittable devices by walking
`data/devices/vendors/<vendor>/<family>/devices/*.yml` and SHALL
treat every schema-valid YAML as an admitted device without
requiring a hand-curated entry in
`bootstrap.DEVICE_REGISTRY`.  The legacy hand-curated registry
SHALL remain as a fallback only for devices whose YAMLs have
not yet been generated; on conflict the data-repo entry wins.
A `bulk-admit` CLI SHALL run the full pipeline against every
device in a requested `(vendor, family)` scope and produce a
machine-readable per-device pass/fail report.

#### Scenario: New chips appear in the registry the moment a YAML is committed

- **WHEN** a new YAML for `gigadevice/gd32f407vet6` is
  committed to alloy-devices-yml
- **AND** alloy-codegen bumps its submodule pin
- **THEN** `bootstrap.DEVICE_REGISTRY[("gigadevice", "gd32f4")]`
  SHALL include `gd32f407vet6` without any edit to
  `src/alloy_codegen/bootstrap.py`
- **AND** `alloy-codegen bulk-admit --vendor gigadevice
  --family gd32f4` SHALL produce C++ artifacts for the new
  device

#### Scenario: bulk-admit summary identifies failure modes per device

- **WHEN** `alloy-codegen bulk-admit --vendor st
  --family stm32g0` is run
- **THEN** the CLI SHALL emit a Markdown summary listing each
  device with one of the statuses: PASS, SCHEMA_INVALID,
  IR_BUILD_FAILED, EMIT_FAILED, SMOKE_COMPILE_FAILED,
  FOOTPRINT_EXCEEDED
- **AND** a machine-readable
  `reports/bulk-admit-<timestamp>.json` SHALL carry the same
  data plus per-device timing

#### Scenario: 8000-device sharded CI run completes within 30 minutes

- **WHEN** the data repo holds 8,000 devices and CI shards the
  bulk admission across 8 parallel jobs (1,000 devices each)
- **THEN** the wall clock for the full bulk run SHALL be
  under 30 minutes
- **AND** the per-shard variance SHALL be at most 20% (no
  shard takes >36 min while another finishes in <20)
