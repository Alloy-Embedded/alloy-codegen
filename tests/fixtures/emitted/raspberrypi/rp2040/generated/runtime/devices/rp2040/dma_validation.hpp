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
enum class DmaChannelId : std::uint16_t {
  none = 0u,
  DMA_ADC = 1u,
  DMA_SPI0_RX = 2u,
  DMA_SPI0_TX = 3u,
  DMA_SPI1_RX = 4u,
  DMA_SPI1_TX = 5u,
  DMA_UART0_RX = 6u,
  DMA_UART0_TX = 7u,
  DMA_UART1_RX = 8u,
  DMA_UART1_TX = 9u,
};

template<PeripheralId Peripheral, DmaChannelId Channel>
struct DmaBindingValid : std::false_type {};

template<>
struct DmaBindingValid<PeripheralId::ADC, DmaChannelId::DMA_ADC> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 36u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI0, DmaChannelId::DMA_SPI0_RX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 16u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI0, DmaChannelId::DMA_SPI0_TX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 17u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI1, DmaChannelId::DMA_SPI1_RX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 18u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI1, DmaChannelId::DMA_SPI1_TX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 19u;
};

template<>
struct DmaBindingValid<PeripheralId::UART0, DmaChannelId::DMA_UART0_RX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 21u;
};

template<>
struct DmaBindingValid<PeripheralId::UART0, DmaChannelId::DMA_UART0_TX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 20u;
};

template<>
struct DmaBindingValid<PeripheralId::UART1, DmaChannelId::DMA_UART1_RX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 23u;
};

template<>
struct DmaBindingValid<PeripheralId::UART1, DmaChannelId::DMA_UART1_TX> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 22u;
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

inline constexpr std::array<DmaBindingEntry, 9> kDmaBindingEntries = {{
  {PeripheralId::ADC, DmaChannelId::DMA_ADC, 0u, 36u},
  {PeripheralId::SPI0, DmaChannelId::DMA_SPI0_RX, 0u, 16u},
  {PeripheralId::SPI0, DmaChannelId::DMA_SPI0_TX, 0u, 17u},
  {PeripheralId::SPI1, DmaChannelId::DMA_SPI1_RX, 0u, 18u},
  {PeripheralId::SPI1, DmaChannelId::DMA_SPI1_TX, 0u, 19u},
  {PeripheralId::UART0, DmaChannelId::DMA_UART0_RX, 0u, 21u},
  {PeripheralId::UART0, DmaChannelId::DMA_UART0_TX, 0u, 20u},
  {PeripheralId::UART1, DmaChannelId::DMA_UART1_RX, 0u, 23u},
  {PeripheralId::UART1, DmaChannelId::DMA_UART1_TX, 0u, 22u},
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
