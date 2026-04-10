## 1. Source adapter

- [ ] 1.1 Add `parse_ip_version_table(mcu_path)` to `sources/stm32_open_pin_data.py`
      returning `dict[str, str]` (instance_name → version string)
- [ ] 1.2 Extend fixture MCU XML files with `<IP .../>` entries for all peripheral instances
      declared in the bootstrap device patches (stm32g030f6, stm32g071rb, stm32g0b1re)

## 2. IR model and schema

- [ ] 2.1 Add `ip_version: str | None` field to `PeripheralInstance` in `ir/model.py`
- [ ] 2.2 Add `ip_version` as optional nullable string property to peripheral objects in
      `schemas/canonical-device-ir-v1.schema.json`
- [ ] 2.3 Bump `IR_SCHEMA_VERSION` from `"1.0.0"` to `"1.1.0"` in `bootstrap.py`
- [ ] 2.4 Update `test_schema.py` pinned version assertion to `"1.1.0"`

## 3. Normalization

- [ ] 3.1 Call `parse_ip_version_table` in `stages/normalize.py` `build_canonical_ir`
- [ ] 3.2 Populate `ip_version` on each `PeripheralInstance` from the lookup table

## 4. Fixtures and golden tests

- [ ] 4.1 Regenerate canonical JSON fixtures for all 3 bootstrap devices
- [ ] 4.2 Regenerate emitted artifact fixtures (artifact-manifest SHA256 changes)
- [ ] 4.3 Confirm all existing tests pass with the new field present
