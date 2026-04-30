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
namespace stm32g071rb {
enum class DmaChannelId : std::uint16_t {
  none = 0u,
  DMA1_DMA1_CH1 = 1u,
  DMA1_DMA1_CH2 = 2u,
  DMA1_DMAMUX_REQ_016 = 3u,
  DMA1_DMAMUX_REQ_017 = 4u,
};

template<PeripheralId Peripheral, DmaChannelId Channel>
struct DmaBindingValid : std::false_type {};

template<>
struct DmaBindingValid<PeripheralId::SPI1, DmaChannelId::DMA1_DMAMUX_REQ_016> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 16u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI1, DmaChannelId::DMA1_DMAMUX_REQ_017> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 17u;
};

template<>
struct DmaBindingValid<PeripheralId::USART1, DmaChannelId::DMA1_DMA1_CH1> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 50u;
};

template<>
struct DmaBindingValid<PeripheralId::USART1, DmaChannelId::DMA1_DMA1_CH2> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 1u;
  static constexpr std::uint16_t kRequestValue = 51u;
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

inline constexpr std::array<DmaBindingEntry, 4> kDmaBindingEntries = {{
  {PeripheralId::SPI1, DmaChannelId::DMA1_DMAMUX_REQ_016, 0u, 16u},
  {PeripheralId::SPI1, DmaChannelId::DMA1_DMAMUX_REQ_017, 0u, 17u},
  {PeripheralId::USART1, DmaChannelId::DMA1_DMA1_CH1, 0u, 50u},
  {PeripheralId::USART1, DmaChannelId::DMA1_DMA1_CH2, 1u, 51u},
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
