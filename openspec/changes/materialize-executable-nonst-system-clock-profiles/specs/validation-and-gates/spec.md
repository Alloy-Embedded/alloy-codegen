## MODIFIED Requirements

### Requirement: Publication SHALL Enforce Runtime Completeness
Families SHALL only publish as runtime-ready when the emitted startup and system-clock contract is
 complete for foundational devices.

#### Scenario: SAME70 system-clock header falls back to metadata-only implementation
- **WHEN** a foundational SAME70 device publishes system-clock profiles
- **AND** `generated/runtime/devices/<device>/system_clock.hpp` emits only the generic
  metadata-only fallback implementation
- **THEN** validation SHALL fail
- **AND** publish SHALL be blocked
