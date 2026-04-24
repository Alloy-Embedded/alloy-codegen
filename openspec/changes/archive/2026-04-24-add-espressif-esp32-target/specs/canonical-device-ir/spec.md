## ADDED Requirements

### Requirement: Canonical IR supports non-ARM system-vector topologies

The pipeline MUST produce correct interrupt and vector-slot metadata for non-ARM ISA families
(RISC-V, Xtensa) without applying ARM Cortex-M exception table assumptions.

#### Scenario: RISC-V devices receive a RISC-V vector baseline

- **WHEN** canonical IR is built for an ESP32-C3 (RISC-V RV32IMC) device
- **THEN** interrupt vector slots are derived from the RISC-V CLIC flat table
- **AND** no ARM-specific exception slots (NMI_Handler, HardFault_Handler, PendSV_Handler,
  SysTick_Handler) are inserted into the interrupt binding list
- **AND** `vector_slot` values reflect actual hardware interrupt IDs, not NVIC-offset numbers

#### Scenario: Xtensa devices receive an Xtensa vector baseline

- **WHEN** canonical IR is built for an ESP32-S3 (Xtensa LX7) device
- **THEN** interrupt vector slots are derived from the Xtensa 32-level interrupt model
- **AND** no Cortex-M exception slots appear in the interrupt binding list

#### Scenario: Unknown core fails explicitly rather than silently

- **WHEN** a device with an unrecognized `core` string is processed
- **THEN** the pipeline raises an explicit error identifying the unknown core
- **AND** it does not silently fall back to a Cortex-M4 baseline

### Requirement: Canonical IR models ESP32 clock/reset control signals

The pipeline MUST parse and normalize ESP32 PCR and DPORT clock/reset register references into
canonical clock-node and reset-control facts, consistent with the patterns used for ST RCC and
NXP CCM.

#### Scenario: ESP32-C3 PCR register references are resolved

- **WHEN** a peripheral patch declares `rcc_enable_signal: "PCR_UART0_CONF0_REG.UART0_CLK_EN"`
- **THEN** `connector_model` resolves the peripheral name (`PCR`), register name
  (`UART0_CONF0_REG`), and field name (`UART0_CLK_EN`) to a typed register reference
- **AND** a `clock-node:pcr-uart0-conf0-reg` clock node is inferred in the device clock graph

#### Scenario: ESP32 DPORT register references are resolved (ESP32 original / S3)

- **WHEN** a peripheral patch declares
  `rcc_enable_signal: "DPORT_PERIP_CLK_EN_REG.UART0_CLK_EN"`
- **THEN** `connector_model` resolves it to a typed register reference via the generic
  `REGISTER_FIELD_TARGET_PATTERN` fallback or a dedicated DPORT matcher
- **AND** a corresponding clock node is added to the device clock graph

### Requirement: Canonical IR tracks supplementary-source provenance for IO Matrix facts

The canonical IR MUST preserve the provenance of non-SVD Espressif routing data used to build
IO Matrix bindings.

#### Scenario: IO Matrix pin bindings cite the supplementary source

- **WHEN** canonical IR contains an Espressif pin-signal binding derived from `gpio_sig_map.h`
- **THEN** that binding's provenance identifies the supplementary source file and revision
- **AND** the provenance is distinct from the SVD provenance used for registers and interrupts
