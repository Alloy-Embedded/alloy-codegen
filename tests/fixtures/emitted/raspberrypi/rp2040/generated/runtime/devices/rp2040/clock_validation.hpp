#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
template<PeripheralId Peripheral, ClockGateId Source>
struct ClockSourceValid : std::false_type {};

template<>
struct ClockSourceValid<PeripheralId::ADC, ClockGateId::gate_adc> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::DMA, ClockGateId::gate_dma> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::I2C0, ClockGateId::gate_i2c0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::I2C1, ClockGateId::gate_i2c1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::SPI0, ClockGateId::gate_spi0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::SPI1, ClockGateId::gate_spi1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::UART0, ClockGateId::gate_uart0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::UART1, ClockGateId::gate_uart1> : std::true_type {
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

inline constexpr std::array<ClockSourceEntry, 8> kClockSources = {{
  {PeripheralId::ADC, ClockGateId::gate_adc, ClockSelectorId::none},
  {PeripheralId::DMA, ClockGateId::gate_dma, ClockSelectorId::none},
  {PeripheralId::I2C0, ClockGateId::gate_i2c0, ClockSelectorId::none},
  {PeripheralId::I2C1, ClockGateId::gate_i2c1, ClockSelectorId::none},
  {PeripheralId::SPI0, ClockGateId::gate_spi0, ClockSelectorId::none},
  {PeripheralId::SPI1, ClockGateId::gate_spi1, ClockSelectorId::none},
  {PeripheralId::UART0, ClockGateId::gate_uart0, ClockSelectorId::none},
  {PeripheralId::UART1, ClockGateId::gate_uart1, ClockSelectorId::none},
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
