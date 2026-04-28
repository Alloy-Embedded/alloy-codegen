## ADDED Requirements

### Requirement: STM32 normalize SHALL merge modm-devices clock-tree edges into the IR

The STM32 normalize builder SHALL load every clock-tree edge
parsed by `alloy_codegen.sources.modm_devices` for the device's
family and project them into the IR's `clock_nodes` and
`clock_selectors` tuples *before* applying family-patch and
device-patch overrides.  The merge order MUST be
`baseline ← modm-devices ← family-patch ← device-patch` so
hand-curated patches continue to override modm when they
disagree (today's contract is preserved).  Every node
contributed by modm SHALL carry
`provenance.source_id = "modm-devices"` so reviewers can audit
which edges flowed in automatically vs. which still require
hand work.

#### Scenario: STM32G0 stm32g071rb merges modm clock edges

- **WHEN** the pipeline normalizes stm32g071rb against the
  fixture modm-devices snapshot
- **THEN** the resulting IR's `clock_nodes` tuple SHALL contain
  at least 5 entries whose `provenance.source_id` is
  `"modm-devices"`
- **AND** the existing patch-derived nodes SHALL still be
  present (no loss of hand-curated data)

#### Scenario: Patches override modm on conflict

- **WHEN** a family patch declares a `clock_node` whose
  `(name, parent)` pair also appears in modm with a different
  divider value
- **THEN** the resolved IR SHALL carry the patch value, not
  modm's
- **AND** the per-node provenance SHALL identify
  `bootstrap-patch` as the contributing source

#### Scenario: Goldens stay byte-identical when patches cover the modm surface

- **WHEN** a device patch already declares every clock node
  modm would supply, with values that match
- **THEN** the resolved IR SHALL be byte-identical to today's
  patch-only output
- **AND** every emitted artifact SHALL match its existing
  golden fixture exactly
