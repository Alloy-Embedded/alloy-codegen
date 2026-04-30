#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class DmaChannelId : std::uint16_t {
  none = 0u,
  DMA_ADC = 1u,
  DMA_SPI2_RX = 2u,
  DMA_SPI2_TX = 3u,
  DMA_UART0_RX = 4u,
  DMA_UART0_TX = 5u,
};

template<PeripheralId Peripheral, DmaChannelId Channel>
struct DmaBindingValid : std::false_type {};

template<>
struct DmaBindingValid<PeripheralId::APB_SARADC, DmaChannelId::DMA_ADC> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 13u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI2, DmaChannelId::DMA_SPI2_RX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 2u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI2, DmaChannelId::DMA_SPI2_TX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 3u;
};

template<>
struct DmaBindingValid<PeripheralId::UART0, DmaChannelId::DMA_UART0_RX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 0u;
};

template<>
struct DmaBindingValid<PeripheralId::UART0, DmaChannelId::DMA_UART0_TX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 1u;
};

template<PeripheralId Peripheral, DmaChannelId Channel>
concept ValidDmaBinding = DmaBindingValid<Peripheral, Channel>::value;

namespace detail {
template<PeripheralId Peripheral, DmaChannelId Channel>
inline constexpr bool kInvalidDmaBinding = false;
}  // namespace detail

struct DmaBindingEntry {
  PeripheralId peripheral;
  DmaChannelId channel;
  std::uint8_t channel_index;
  std::uint16_t request_value;
};

inline constexpr std::array<DmaBindingEntry, 5> kDmaBindingEntries = {{
  {PeripheralId::APB_SARADC, DmaChannelId::DMA_ADC, 0u, 13u},
  {PeripheralId::SPI2, DmaChannelId::DMA_SPI2_RX, 0u, 2u},
  {PeripheralId::SPI2, DmaChannelId::DMA_SPI2_TX, 0u, 3u},
  {PeripheralId::UART0, DmaChannelId::DMA_UART0_RX, 0u, 0u},
  {PeripheralId::UART0, DmaChannelId::DMA_UART0_TX, 0u, 1u},
}};

constexpr bool is_valid_dma_binding(PeripheralId peripheral, DmaChannelId channel) noexcept {
  for (auto const& entry : kDmaBindingEntries) {
    if (entry.peripheral == peripheral && entry.channel == channel) {
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
