## MODIFIED Requirements

### Requirement: Runtime-Lite C++ Contract
The published C++ artifact contract MUST separate reflection-oriented artifacts from hot-path
runtime artifacts. For foundational driver classes, the hot-path contract MUST include typed
driver-semantic traits in addition to runtime-lite facts.

#### Scenario: Foundational DMA semantics are published
- **WHEN** a family publishes DMA bindings for a device
- **THEN** the artifact tree SHALL include
  `generated/runtime/devices/<device>/dma_bindings.hpp`
- **AND** the artifact tree SHALL include
  `generated/runtime/devices/<device>/driver_semantics/dma.hpp`
- **AND** those headers SHALL publish typed ids, numeric route metadata, and typed register/field
  refs needed by the DMA hot path

