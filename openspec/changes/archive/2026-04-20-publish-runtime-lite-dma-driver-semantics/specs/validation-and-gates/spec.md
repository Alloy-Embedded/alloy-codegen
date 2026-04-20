## MODIFIED Requirements

### Requirement: Publication SHALL Enforce Runtime Completeness
Families SHALL only publish as runtime-ready when the emitted hot-path contract is complete for
foundational driver classes.

#### Scenario: DMA bindings lack runtime-lite DMA semantics
- **WHEN** a device publishes DMA bindings but omits runtime-lite DMA bindings or DMA driver
  semantics
- **THEN** validation SHALL fail
- **AND** publish SHALL be blocked

#### Scenario: Foundational DMA semantics are complete
- **WHEN** every published DMA binding also has complete runtime-lite DMA semantics
- **THEN** validation MAY pass this gate
- **AND** publish MAY continue
