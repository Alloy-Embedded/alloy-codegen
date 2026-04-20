## Why

O `alloy-codegen` já provou o boundary runtime-only e o contrato tipado multi-vendor.
O próximo passo para realmente transformar o Alloy na melhor stack multi-vendor não é
“mais metadata”; é publicar o conjunto de artefatos que um HAL excelente consegue consumir
sem heurística, sem lookup textual e sem código manual por device.

Esta OpenSpec fica **deliberadamente limitada ao que pertence ao `alloy-codegen`**.
O consumo desses artefatos no repo `alloy` é uma dependência externa e deve ser tratado
em OpenSpecs pareadas lá.

## What Changes

### Codegen-owned deliverables

- **Generated linker script**: `device.ld`
- **Generated clock configuration helpers**:
  - `clock_config.hpp`
  - `clock_profiles.hpp`
- **Generated connector tables**: `connectors.hpp`
- **Generated interrupt stubs**: `interrupt_stubs.hpp`
- **Generated capability sidecars**:
  - `capabilities.hpp`
  - `capabilities.json`
- **CLI diagnostics**:
  - `alloy explain`
  - `alloy diff`
- **Cross-vendor validation gates** for completeness, capability parity, and regression detection

### Out-of-scope for this repo

- GPIO/UART/SPI/I2C/DMA/ADC/Timer/PWM implementations in `alloy`
- ownership model (`take()`)
- CMake package integration in `alloy`
- user-facing driver APIs

Those remain explicit external dependencies for the downstream consumer.

## Impact

- Affected specs: `artifact-contract`, `canonical-device-ir`, `validation-and-gates`
- Affected repo: `alloy-codegen`
- Downstream dependency: `alloy` must later consume the emitted artifacts; that is not
  implemented by this change

## What This Is Not

- not an `alloy` HAL implementation spec
- not an RTOS or async runtime spec
- not a USB/Ethernet/Wi-Fi stack spec
- not a breadth-first device explosion plan

## Implementation Phases

| Phase | Deliverable |
|-------|-------------|
| 0 | Gap audit: emitted vs consumed artifacts; paired-alloy dependency list |
| 1 | Linker script + startup-facing memory contract |
| 2 | Connector tables + interrupt stubs |
| 3 | Clock configuration helpers and profiles |
| 4 | Capability sidecars + explain/diff CLI |
| 5 | Validation moat: full artifact smoke, completeness, parity gates |
| 6 | Docs + paired-alloy handoff |

## Success Criteria

This change is complete when:

1. every foundational device publishes `device.ld`, `clock_config.hpp`,
   `clock_profiles.hpp`, `connectors.hpp`, `interrupt_stubs.hpp`,
   `capabilities.hpp`, and `capabilities.json`
2. consumer verification can compile/link the complete generated set without handwritten
   bridge headers
3. capability regressions across publications are machine-detected
4. `alloy explain` can trace an emitted fact back to its canonical provenance
5. the downstream `alloy` repo has a clean artifact contract to consume, without asking the
   generator to infer at runtime what it could emit ahead of time
