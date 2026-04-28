## ADDED Requirements

### Requirement: Device admission SHALL be YAML-only

The `alloy-codegen` pipeline SHALL accept canonical
`CanonicalDeviceIR` data only via the `alloy-devices-yml`
submodule mounted at `data/devices/`.  The legacy paths —
in-repo vendor source parsing (`src/alloy_codegen/sources/*`),
the patch overlay system (`patches/*`), and the per-family
vendor adapters (`src/alloy_codegen/vendors/_register_*.py`)
— SHALL NOT exist after this change.  Devices that lack a
committed `data/devices/vendors/<vendor>/<family>/devices/<device>.yml`
SHALL fail admission with an explicit error directing the
contributor to the data repo.

#### Scenario: Admitted device loads from YAML and emits unchanged

- **WHEN** the pipeline processes any of the 9 admitted families
  (espressif, microchip, nordic, nxp, raspberrypi, st)
- **THEN** the normalize stage reads the IR from
  `data/devices/vendors/<vendor>/<family>/devices/<device>.yml`
  via `alloy_codegen.sources.alloy_devices_yml.load_canonical_device`
- **AND** the emitted artifacts under
  `tests/fixtures/emitted/` SHALL be byte-identical to the
  pre-cleanup baseline

#### Scenario: Missing YAML raises an actionable error

- **WHEN** the pipeline is asked to admit a device whose YAML
  is not present in `data/devices/vendors/<vendor>/<family>/devices/`
- **THEN** the normalize stage SHALL raise
  `StageExecutionError` with a message identifying the missing
  path and instructing the contributor to commit the YAML in
  the `alloy-devices-yml` repo

#### Scenario: Vendor source parsers and adapter registry no longer exist

- **WHEN** a contributor inspects the `alloy-codegen` source
  tree
- **THEN** there SHALL be no `src/alloy_codegen/sources/*.py`
  files other than `alloy_devices_yml.py` and `__init__.py`
- **AND** there SHALL be no
  `src/alloy_codegen/vendors/_register_*.py` modules
- **AND** there SHALL be no top-level `patches/` directory
- **AND** there SHALL be no `tests/fixtures/cmsis-svd-data/`,
  `espressif-svd/`, `microchip-dfp-*/`,
  `nxp-mcux-imxrt1060/`, `zephyr-dts/`,
  `esp-idf-gpio-sig-map/`, `stm32-open-pin-data/`, or
  `modm-devices/` fixture directories
