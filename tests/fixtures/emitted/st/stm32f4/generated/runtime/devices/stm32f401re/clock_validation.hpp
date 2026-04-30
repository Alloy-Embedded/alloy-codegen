#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
template<PeripheralId Peripheral, ClockGateId Source>
struct ClockSourceValid : std::false_type {};

template<>
struct ClockSourceValid<PeripheralId::DMA1, ClockGateId::gate_dma1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::DMA2, ClockGateId::gate_dma2> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIOA, ClockGateId::gate_gpioa> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIOB, ClockGateId::gate_gpiob> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::OTG_FS, ClockGateId::gate_otg_fs> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::SPI1, ClockGateId::gate_spi1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TIM1, ClockGateId::gate_tim1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::USART1, ClockGateId::gate_usart1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::USART2, ClockGateId::gate_usart2> : std::true_type {
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

inline constexpr std::array<ClockSourceEntry, 9> kClockSources = {{
  {PeripheralId::DMA1, ClockGateId::gate_dma1, ClockSelectorId::none},
  {PeripheralId::DMA2, ClockGateId::gate_dma2, ClockSelectorId::none},
  {PeripheralId::GPIOA, ClockGateId::gate_gpioa, ClockSelectorId::none},
  {PeripheralId::GPIOB, ClockGateId::gate_gpiob, ClockSelectorId::none},
  {PeripheralId::OTG_FS, ClockGateId::gate_otg_fs, ClockSelectorId::none},
  {PeripheralId::SPI1, ClockGateId::gate_spi1, ClockSelectorId::none},
  {PeripheralId::TIM1, ClockGateId::gate_tim1, ClockSelectorId::none},
  {PeripheralId::USART1, ClockGateId::gate_usart1, ClockSelectorId::none},
  {PeripheralId::USART2, ClockGateId::gate_usart2, ClockSelectorId::none},
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
