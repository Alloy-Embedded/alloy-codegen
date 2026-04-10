## Why

`PeripheralInstance` in the canonical IR identifies a peripheral by its IP name (e.g.
`"usart"`) and instance number (e.g. `1`), but carries no information about which *version*
of that IP block the peripheral implements.

This matters because:

- **STM32G0 and STM32F4 both have USART peripherals**, but they may implement different IP
  versions with different register layouts. Without an `ip_version` field, alloy cannot select
  the right register struct or HAL driver for a given peripheral instance — it can only guess
  from the family name.
- **Cross-device deduplication is impossible.** The `family-connectivity.json` can deduplicate
  peripheral *names* but cannot tell consumers "USART1 on G071 and USART1 on G030 share the
  same IP version and therefore the same register layout."
- **Phase 2 of the alloy HAL roadmap** (typed connect/signal tables, compile-time pin
  validation) requires knowing IP versions to select the correct generated policy type. Without
  this field, the connector generator would need a separate out-of-band lookup.

The STM32_open_pin_data MCU XML files already declare IP versions for all peripheral instances
via `<IP Name="USART" InstanceName="USART1" Version="usart_v3_1"/>`. The data is already in
the source; it is just not being extracted.

## What Changes

- **MODIFIED** `PeripheralInstance` in the canonical IR: adds `ip_version: str | None` field
  holding the raw vendor-declared IP version string (e.g. `"usart_v3_1"`).
- **NEW** `parse_ip_version_table` function in `sources/stm32_open_pin_data.py` that reads the
  `<IP .../>` table from the MCU XML and returns a `dict[instance_name, version_string]`.
- **MODIFIED** `stages/normalize.py`: `build_canonical_ir` looks up `ip_version` for each
  peripheral from the parsed IP version table.
- **MODIFIED** `schemas/canonical-device-ir-v1.schema.json`: `ip_version` added as an
  optional, nullable string property to the peripheral object.
- **MODIFIED** `bootstrap.py`: `IR_SCHEMA_VERSION` bumped from `"1.0.0"` to `"1.1.0"` to
  signal the additive schema change.
- **MODIFIED** fixture MCU XML files: extended with `<IP .../>` entries for all peripheral
  instances present in the bootstrap device patches.
- **MODIFIED** all golden fixtures: canonical JSON, emitted artifact-manifest SHA256 updated.

## Impact

- Affected specs: `canonical-device-ir`
- Affected code:
  - `src/alloy_codegen/ir/model.py`
  - `src/alloy_codegen/sources/stm32_open_pin_data.py`
  - `src/alloy_codegen/stages/normalize.py`
  - `src/alloy_codegen/bootstrap.py`
  - `schemas/canonical-device-ir-v1.schema.json`
  - `tests/fixtures/stm32-open-pin-data/mcu/*.xml`
  - `tests/fixtures/stm32g0/*.canonical.json`
  - `tests/fixtures/emitted/stm32g0/stm32g071rb/artifact-manifest.json`
- No breaking change to downstream consumers: `ip_version` is nullable and was absent before.
  Consumers that ignore unknown fields are unaffected. Consumers that validate against the
  schema need to accept the new `"1.1.0"` version.
