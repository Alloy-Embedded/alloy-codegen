## ADDED Requirements

### Requirement: Trait header SHALL emit `kGateModel` for every peripheral

Every peripheral instance entry in the emitted ``peripheral_traits.h`` SHALL carry a typed ``static constexpr GateModel kGateModel = …;`` line drawn from the closed set defined in the canonical-device-ir capability. The ``GateModel`` enum itself SHALL be emitted to a sibling header ``peripheral_id.hpp`` (or a new ``rcc_traits.hpp`` if the peripheral_id header proves overloaded) so HAL drivers consume it via:

```cpp
#include "rcc_traits.hpp"

using namespace alloy::nxp::imxrt1060::mimxrt1062;

template <PeripheralId Id>
struct LpuartDriver {
  static constexpr void EnableClock() {
    if constexpr (lpuart1::kGateModel == GateModel::always_on) {
      // no-op
    } else if constexpr (lpuart1::kGateModel == GateModel::index_based) {
      // write 1 to lpuart1::kRccEnable verbatim
      MmioWrite(parse_register_path(lpuart1::kRccEnable), …);
    } else {
      // per_peri_en / per_peri_en_rst — uniform path
      MmioWrite(parse_register_path(lpuart1::kRccEnable), …);
    }
  }
};
```

#### Scenario: AVR-Dx HAL driver compiles with `always_on` short-circuit

- **WHEN** the alloy HAL builds against an avr64da32 codegen
  output
- **THEN** every peripheral's ``kGateModel`` SHALL be
  ``GateModel::always_on``
- **AND** the HAL driver's ``constexpr if`` branch for
  ``always_on`` SHALL emit a no-op for the EnableClock path
- **AND** the HAL driver SHALL NOT reference ``kRccEnable`` /
  ``kRccReset`` in any code path reachable on the AVR-Dx target

#### Scenario: iMXRT HAL driver compiles with `index_based` path

- **WHEN** the alloy HAL builds against a mimxrt1062 codegen
  output
- **THEN** ``lpuart1::kGateModel`` SHALL be
  ``GateModel::index_based``
- **AND** the HAL driver's ``constexpr if`` branch for
  ``index_based`` SHALL parse the ``kRccEnable`` path
  (``"ccm.ccgr5.cg12"``) verbatim — without name-based dispatch
