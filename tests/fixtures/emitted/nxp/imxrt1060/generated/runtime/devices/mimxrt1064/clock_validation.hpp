#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
template<PeripheralId Peripheral, ClockGateId Source>
struct ClockSourceValid : std::false_type {};

template<>
struct ClockSourceValid<PeripheralId::GPIO1, ClockGateId::gate_gpio1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIO4, ClockGateId::gate_gpio4> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::LPSPI1, ClockGateId::gate_lpspi1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::selector_lpspi_root;
};

template<>
struct ClockSourceValid<PeripheralId::LPUART1, ClockGateId::gate_lpuart1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::selector_lpuart_root;
};

template<>
struct ClockSourceValid<PeripheralId::LPUART3, ClockGateId::gate_lpuart3> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<PeripheralId Peripheral, ClockGateId Source>
concept ValidClockSource = ClockSourceValid<Peripheral, Source>::value;

namespace detail {
template<PeripheralId Peripheral, ClockGateId Source>
inline constexpr bool kInvalidClockSource = false;
}  // namespace detail

struct ClockSourceEntry {
  PeripheralId peripheral;
  ClockGateId source;
  ClockSelectorId selector;
};

inline constexpr std::array<ClockSourceEntry, 5> kClockSources = {{
  {PeripheralId::GPIO1, ClockGateId::gate_gpio1, ClockSelectorId::none},
  {PeripheralId::GPIO4, ClockGateId::gate_gpio4, ClockSelectorId::none},
  {PeripheralId::LPSPI1, ClockGateId::gate_lpspi1, ClockSelectorId::selector_lpspi_root},
  {PeripheralId::LPUART1, ClockGateId::gate_lpuart1, ClockSelectorId::selector_lpuart_root},
  {PeripheralId::LPUART3, ClockGateId::gate_lpuart3, ClockSelectorId::none},
}};

constexpr bool is_valid_clock_source(PeripheralId peripheral, ClockGateId source) noexcept {
  for (auto const& entry : kClockSources) {
    if (entry.peripheral == peripheral && entry.source == source) {
      return true;
    }
  }
  return false;
}
}
}
}
}
}
}
