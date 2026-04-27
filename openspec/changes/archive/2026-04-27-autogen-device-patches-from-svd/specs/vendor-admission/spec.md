## ADDED Requirements

### Requirement: Device patches MUST be generatable from SVD + CMSIS-Pack sources

The repository SHALL ship `scripts/autogen_device_patches.py`, a
deterministic CLI that emits a draft `patches/<vendor>/<family>/devices/<device>.json`
from a CMSIS-SVD file (and optionally a CMSIS-Pack PDSC) with
the mechanical 80% of fields populated: device identity, package
candidates, core, memory map, peripheral instance list, IRQ
vector table, basic RCC bindings discoverable from the SVD.
Fields the generator cannot derive SHALL be emitted as
`"// TODO review"` placeholders so a reviewer sees exactly what
is unfinished.  The generator MUST be deterministic — re-running
on the same inputs SHALL produce byte-identical output.

#### Scenario: Generator reproduces ≥80% of a hand-curated patch

- **WHEN** `python -m scripts.autogen_device_patches --vendor st
  --family stm32g0 --device stm32g071rb --svd <STM32G071xx.svd>`
  is run
- **THEN** the emitted JSON SHALL match the existing
  `patches/st/stm32g0/devices/stm32g071rb.json` for memory regions,
  peripheral instance names + base addresses, and the IRQ vector
  table
- **AND** any hand-curated override fields the generator cannot
  derive SHALL be emitted as `"// TODO review"` placeholders

#### Scenario: Generator output is deterministic

- **WHEN** the generator is run twice on the same inputs
- **THEN** both runs SHALL emit byte-identical output
- **AND** the field ordering SHALL be stable so diffs vs. the
  prior draft are minimal
