## ADDED Requirements

### Requirement: alloy-codegen SHALL consume canonical device data from a separate alloy-devices-yml repository

The repository SHALL ship a git submodule at `data/devices/`
pointing at the standalone `alloy-devices-yml` repository at a
pinned SHA recorded in `.gitmodules`.  The pipeline SHALL
short-circuit the normalize stage when a device's canonical
YAML exists in the submodule: the YAML is parsed via
`alloy_codegen.sources.alloy_devices_yml.load_canonical_device(...)`
and the resulting `CanonicalDeviceIR` flows directly into
validation + emission, bypassing the legacy SVD + patch path.
When the YAML is absent the legacy path SHALL still run, so
families that have not yet been migrated continue working
unchanged.  The emitted artifacts MUST be byte-identical
regardless of which path produced the IR.

#### Scenario: Admitted devices resolve via the submodule when YAML is present

- **WHEN** the pipeline runs for any of the 17 admitted
  devices after this change lands
- **AND** `data/devices/vendors/<vendor>/<family>/devices/<device>.yml`
  exists in the submodule
- **THEN** the normalize stage SHALL load the IR from that
  file
- **AND** the emitted artifacts SHALL be byte-identical to
  the artifacts produced by the legacy SVD + patch path

#### Scenario: Devices without YAML fall through to the legacy path

- **WHEN** the pipeline runs for a device whose canonical
  YAML is not yet committed to the submodule
- **THEN** the legacy adapter (CMSIS-SVD, ATDF, Zephyr DTS,
  …) SHALL be used as today
- **AND** the resulting IR + artifacts SHALL be unchanged
  from before this change

#### Scenario: Submodule bumps run the parity gate

- **WHEN** `tools/bump_devices_yml.py` updates the submodule
  to a new SHA
- **THEN** the tool SHALL rerun `pytest -q` and
  `pytest --runtime-cpp-smoke`
- **AND** SHALL report any per-device IR drift between the
  pre-bump and post-bump emissions
- **AND** SHALL refuse to commit the bump if the drift would
  produce non-trivial C++ artifact changes without explicit
  reviewer override
