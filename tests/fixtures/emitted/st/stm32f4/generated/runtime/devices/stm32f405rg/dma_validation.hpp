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
namespace stm32f405rg {
enum class DmaChannelId : std::uint16_t {
  none = 0u,
  DMA2_DMA2_STREAM2 = 1u,
  DMA2_DMA2_STREAM7 = 2u,
};

template<PeripheralId Peripheral, DmaChannelId Channel>
struct DmaBindingValid : std::false_type {};

template<>
struct DmaBindingValid<PeripheralId::USART1, DmaChannelId::DMA2_DMA2_STREAM2> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 2u;
  static constexpr std::uint16_t kRequestValue = 0u;
};

template<>
struct DmaBindingValid<PeripheralId::USART1, DmaChannelId::DMA2_DMA2_STREAM7> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 7u;
  static constexpr std::uint16_t kRequestValue = 0u;
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

inline constexpr std::array<DmaBindingEntry, 2> kDmaBindingEntries = {{
  {PeripheralId::USART1, DmaChannelId::DMA2_DMA2_STREAM2, 2u, 0u},
  {PeripheralId::USART1, DmaChannelId::DMA2_DMA2_STREAM7, 7u, 0u},
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
