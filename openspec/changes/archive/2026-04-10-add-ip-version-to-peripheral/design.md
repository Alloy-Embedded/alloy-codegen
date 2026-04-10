## Context

The STM32_open_pin_data MCU XML contains one `<IP .../>` element per peripheral instance:

```xml
<IP InstanceName="USART1" Name="USART" Version="usart_v3_1"/>
<IP InstanceName="USART2" Name="USART" Version="usart_v3_1"/>
<IP InstanceName="SPI1"   Name="SPI"   Version="spi_v2_1"/>
<IP InstanceName="GPIO"   Name="GPIO"  Version="STM32G07x_gpio_v1_0"/>
```

We already parse this file for GPIO modes. The IP version table is a side product of reading
the same file.

## Goals / Non-Goals

Goals:
- Capture `ip_version` string per peripheral instance in the canonical IR.
- Keep the value as-is from the vendor source (no normalization yet).
- Minor schema version bump (1.1.0); no breaking changes.

Non-Goals:
- Defining a cross-vendor IP version registry or canonical naming.
- Implementing a separate `ip_blocks` definition table with register maps.
- Deduplicating IP definitions across families (future work).

## Decisions

**Decision: store the raw vendor version string, not a normalized one.**

The vendor string (e.g. `"usart_v3_1"`) is what the data source provides and what downstream
tools currently expect for matching. Normalizing to a vendor-agnostic form requires a mapping
table that doesn't exist yet. Storing the raw string now and normalizing later is lower risk
than speculating on a cross-vendor scheme.

Alternatives considered: structured `{name, version}` tuple — rejected because the `ip_name`
field already captures the name part; duplicating it would add noise.

**Decision: `ip_version` is nullable (`str | None`).**

Not all sources provide this information. SVD-only devices (e.g. SAME70 in future) may not
have an MCU XML. Requiring a non-null value would block those families from normalizing.

**Decision: look up by `InstanceName`, not by `Name`.**

The `InstanceName` in the XML (e.g. `"USART1"`) maps directly to the canonical peripheral
name in the IR after alias resolution. `Name` (e.g. `"USART"`) maps to `ip_name`, which we
already have. The lookup key must be the instance name.

## Risks / Trade-offs

- **Vendor string opacity**: `"usart_v3_1"` is meaningful to ST tools but opaque to generic
  consumers. Mitigation: document that this is a vendor-declared identifier, not a stable
  Alloy-owned key. Normalization is an explicit future task.
- **Fixture maintenance**: MCU XML fixtures must be extended with all IP entries. This adds a
  small maintenance burden when adding new fixtures.

## Migration Plan

1. Extend MCU XML fixtures with `<IP .../>` entries.
2. Add parser function in `stm32_open_pin_data.py`.
3. Update `normalize.py` to call the parser and populate `ip_version`.
4. Bump `IR_SCHEMA_VERSION` and update schema file.
5. Regenerate all golden fixtures.
6. Update `test_schema.py` pinned version assertion.

No migration needed for existing `alloy-devices` artifacts: the `ip_version` field is additive
and consumers that read `device.json` will simply find a new optional field.
