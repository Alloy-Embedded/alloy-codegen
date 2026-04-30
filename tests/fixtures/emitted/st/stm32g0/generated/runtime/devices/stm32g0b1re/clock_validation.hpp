#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
template<PeripheralId Peripheral, ClockGateId Source>
struct ClockSourceValid : std::false_type {};

template<>
struct ClockSourceValid<PeripheralId::ADC1, ClockGateId::gate_adc1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::DMA1, ClockGateId::gate_dma1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::DMAMUX1, ClockGateId::gate_dmamux1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::FDCAN1, ClockGateId::gate_fdcan1> : std::true_type {
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
struct ClockSourceValid<PeripheralId::I2C1, ClockGateId::gate_i2c1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::I2C2, ClockGateId::gate_i2c2> : std::true_type {
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
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::selector_usart1_kernel;
};

template<>
struct ClockSourceValid<PeripheralId::USB, ClockGateId::gate_usb> : std::true_type {
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

inline constexpr std::array<ClockSourceEntry, 12> kClockSources = {{
  {PeripheralId::ADC1, ClockGateId::gate_adc1, ClockSelectorId::none},
  {PeripheralId::DMA1, ClockGateId::gate_dma1, ClockSelectorId::none},
  {PeripheralId::DMAMUX1, ClockGateId::gate_dmamux1, ClockSelectorId::none},
  {PeripheralId::FDCAN1, ClockGateId::gate_fdcan1, ClockSelectorId::none},
  {PeripheralId::GPIOA, ClockGateId::gate_gpioa, ClockSelectorId::none},
  {PeripheralId::GPIOB, ClockGateId::gate_gpiob, ClockSelectorId::none},
  {PeripheralId::I2C1, ClockGateId::gate_i2c1, ClockSelectorId::none},
  {PeripheralId::I2C2, ClockGateId::gate_i2c2, ClockSelectorId::none},
  {PeripheralId::SPI1, ClockGateId::gate_spi1, ClockSelectorId::none},
  {PeripheralId::TIM1, ClockGateId::gate_tim1, ClockSelectorId::none},
  {PeripheralId::USART1, ClockGateId::gate_usart1, ClockSelectorId::selector_usart1_kernel},
  {PeripheralId::USB, ClockGateId::gate_usb, ClockSelectorId::none},
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
