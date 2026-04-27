## ADDED Requirements

### Requirement: The pipeline SHALL ingest modm-devices XML as an enrichment source for STM32

The pipeline SHALL ship `src/alloy_codegen/sources/modm_devices.py`,
an adapter that consumes
`modm-devices/devices/stm32/<family>/<part>.xml` and produces the
same intermediate objects as the existing STM32 source pipeline
(peripherals, interrupts, dma_requests, connection_candidates,
clock graph edges).  The adapter SHALL register through the
central vendor-adapter registry alongside the existing CMSIS-SVD
adapter.  The pipeline SHALL apply merge precedence
`cmsis-svd < stm32-open-pin-data < modm-devices < family-patch <
device-patch` so modm fills gaps left by open sources but defers
to hand-curated overrides.  The integration SHALL pin against a
specific modm-devices checkout SHA recorded in
`data/source_pins.toml`.

#### Scenario: modm fills clock-tree edges absent from CMSIS-SVD

- **WHEN** the pipeline normalizes an STM32G0 device
- **AND** CMSIS-SVD does not carry clock-tree edges for the RCC
  controller
- **THEN** the resolved IR SHALL include the clock graph edges
  imported from `modm-devices/devices/stm32/g0/<part>.xml`
- **AND** the per-edge provenance SHALL identify modm-devices as
  the contributing source

#### Scenario: Hand-curated patch overrides modm data

- **WHEN** a device patch sets a field that modm also sets, with
  a different value
- **THEN** the resolved IR SHALL use the patch value
- **AND** the per-field provenance SHALL still record modm as the
  precedence-1 source so the override is auditable

#### Scenario: Stale modm-devices SHA blocks the load by default

- **WHEN** the modm-devices checkout SHA does not match the pin
  recorded in `data/source_pins.toml`
- **THEN** the fetch stage SHALL fail with a message identifying
  the drift
- **AND** the failure SHALL be overridable with an explicit
  `--accept-stale-sources` flag for review workflows
