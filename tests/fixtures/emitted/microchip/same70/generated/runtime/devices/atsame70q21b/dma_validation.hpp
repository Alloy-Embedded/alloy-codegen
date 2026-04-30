#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
enum class DmaChannelId : std::uint16_t {
  none = 0u,
  XDMAC_PERID_0 = 1u,
  XDMAC_PERID_1 = 2u,
  XDMAC_PERID_10 = 3u,
  XDMAC_PERID_11 = 4u,
  XDMAC_PERID_12 = 5u,
  XDMAC_PERID_13 = 6u,
  XDMAC_PERID_14 = 7u,
  XDMAC_PERID_15 = 8u,
  XDMAC_PERID_16 = 9u,
  XDMAC_PERID_17 = 10u,
  XDMAC_PERID_18 = 11u,
  XDMAC_PERID_19 = 12u,
  XDMAC_PERID_2 = 13u,
  XDMAC_PERID_20 = 14u,
  XDMAC_PERID_21 = 15u,
  XDMAC_PERID_22 = 16u,
  XDMAC_PERID_23 = 17u,
  XDMAC_PERID_24 = 18u,
  XDMAC_PERID_25 = 19u,
  XDMAC_PERID_26 = 20u,
  XDMAC_PERID_27 = 21u,
  XDMAC_PERID_28 = 22u,
  XDMAC_PERID_29 = 23u,
  XDMAC_PERID_3 = 24u,
  XDMAC_PERID_30 = 25u,
  XDMAC_PERID_31 = 26u,
  XDMAC_PERID_34 = 27u,
  XDMAC_PERID_35 = 28u,
  XDMAC_PERID_36 = 29u,
  XDMAC_PERID_39 = 30u,
  XDMAC_PERID_4 = 31u,
  XDMAC_PERID_40 = 32u,
  XDMAC_PERID_41 = 33u,
  XDMAC_PERID_42 = 34u,
  XDMAC_PERID_43 = 35u,
  XDMAC_PERID_5 = 36u,
  XDMAC_PERID_6 = 37u,
  XDMAC_PERID_7 = 38u,
  XDMAC_PERID_8 = 39u,
  XDMAC_PERID_9 = 40u,
};

template<PeripheralId Peripheral, DmaChannelId Channel>
struct DmaBindingValid : std::false_type {};

template<>
struct DmaBindingValid<PeripheralId::AFEC0, DmaChannelId::XDMAC_PERID_35> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 35u;
};

template<>
struct DmaBindingValid<PeripheralId::AFEC1, DmaChannelId::XDMAC_PERID_36> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 36u;
};

template<>
struct DmaBindingValid<PeripheralId::DACC, DmaChannelId::XDMAC_PERID_30> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 30u;
};

template<>
struct DmaBindingValid<PeripheralId::DACC, DmaChannelId::XDMAC_PERID_31> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 31u;
};

template<>
struct DmaBindingValid<PeripheralId::GPIOA, DmaChannelId::XDMAC_PERID_34> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 34u;
};

template<>
struct DmaBindingValid<PeripheralId::HSMCI, DmaChannelId::XDMAC_PERID_0> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 0u;
};

template<>
struct DmaBindingValid<PeripheralId::PWM0, DmaChannelId::XDMAC_PERID_13> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 13u;
};

template<>
struct DmaBindingValid<PeripheralId::PWM1, DmaChannelId::XDMAC_PERID_39> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 39u;
};

template<>
struct DmaBindingValid<PeripheralId::QSPI, DmaChannelId::XDMAC_PERID_5> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 5u;
};

template<>
struct DmaBindingValid<PeripheralId::QSPI, DmaChannelId::XDMAC_PERID_6> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 6u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI0, DmaChannelId::XDMAC_PERID_1> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 1u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI0, DmaChannelId::XDMAC_PERID_2> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 2u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI1, DmaChannelId::XDMAC_PERID_3> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 3u;
};

template<>
struct DmaBindingValid<PeripheralId::SPI1, DmaChannelId::XDMAC_PERID_4> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 4u;
};

template<>
struct DmaBindingValid<PeripheralId::TC0, DmaChannelId::XDMAC_PERID_40> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 40u;
};

template<>
struct DmaBindingValid<PeripheralId::TC1, DmaChannelId::XDMAC_PERID_41> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 41u;
};

template<>
struct DmaBindingValid<PeripheralId::TC2, DmaChannelId::XDMAC_PERID_42> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 42u;
};

template<>
struct DmaBindingValid<PeripheralId::TC3, DmaChannelId::XDMAC_PERID_43> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 43u;
};

template<>
struct DmaBindingValid<PeripheralId::TWIHS0, DmaChannelId::XDMAC_PERID_14> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 14u;
};

template<>
struct DmaBindingValid<PeripheralId::TWIHS0, DmaChannelId::XDMAC_PERID_15> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 15u;
};

template<>
struct DmaBindingValid<PeripheralId::TWIHS1, DmaChannelId::XDMAC_PERID_16> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 16u;
};

template<>
struct DmaBindingValid<PeripheralId::TWIHS1, DmaChannelId::XDMAC_PERID_17> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 17u;
};

template<>
struct DmaBindingValid<PeripheralId::TWIHS2, DmaChannelId::XDMAC_PERID_18> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 18u;
};

template<>
struct DmaBindingValid<PeripheralId::TWIHS2, DmaChannelId::XDMAC_PERID_19> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 19u;
};

template<>
struct DmaBindingValid<PeripheralId::UART0, DmaChannelId::XDMAC_PERID_20> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 20u;
};

template<>
struct DmaBindingValid<PeripheralId::UART0, DmaChannelId::XDMAC_PERID_21> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 21u;
};

template<>
struct DmaBindingValid<PeripheralId::UART1, DmaChannelId::XDMAC_PERID_22> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 22u;
};

template<>
struct DmaBindingValid<PeripheralId::UART1, DmaChannelId::XDMAC_PERID_23> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 23u;
};

template<>
struct DmaBindingValid<PeripheralId::UART2, DmaChannelId::XDMAC_PERID_24> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 24u;
};

template<>
struct DmaBindingValid<PeripheralId::UART2, DmaChannelId::XDMAC_PERID_25> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 25u;
};

template<>
struct DmaBindingValid<PeripheralId::UART3, DmaChannelId::XDMAC_PERID_26> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 26u;
};

template<>
struct DmaBindingValid<PeripheralId::UART3, DmaChannelId::XDMAC_PERID_27> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 27u;
};

template<>
struct DmaBindingValid<PeripheralId::UART4, DmaChannelId::XDMAC_PERID_28> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 28u;
};

template<>
struct DmaBindingValid<PeripheralId::UART4, DmaChannelId::XDMAC_PERID_29> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 29u;
};

template<>
struct DmaBindingValid<PeripheralId::USART0, DmaChannelId::XDMAC_PERID_7> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 7u;
};

template<>
struct DmaBindingValid<PeripheralId::USART0, DmaChannelId::XDMAC_PERID_8> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 8u;
};

template<>
struct DmaBindingValid<PeripheralId::USART1, DmaChannelId::XDMAC_PERID_10> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 10u;
};

template<>
struct DmaBindingValid<PeripheralId::USART1, DmaChannelId::XDMAC_PERID_9> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 9u;
};

template<>
struct DmaBindingValid<PeripheralId::USART2, DmaChannelId::XDMAC_PERID_11> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 11u;
};

template<>
struct DmaBindingValid<PeripheralId::USART2, DmaChannelId::XDMAC_PERID_12> : std::true_type {
  static constexpr std::uint8_t kChannelIndex = 0u;
  static constexpr std::uint16_t kRequestValue = 12u;
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

inline constexpr std::array<DmaBindingEntry, 40> kDmaBindingEntries = {{
  {PeripheralId::AFEC0, DmaChannelId::XDMAC_PERID_35, 0u, 35u},
  {PeripheralId::AFEC1, DmaChannelId::XDMAC_PERID_36, 0u, 36u},
  {PeripheralId::DACC, DmaChannelId::XDMAC_PERID_30, 0u, 30u},
  {PeripheralId::DACC, DmaChannelId::XDMAC_PERID_31, 0u, 31u},
  {PeripheralId::GPIOA, DmaChannelId::XDMAC_PERID_34, 0u, 34u},
  {PeripheralId::HSMCI, DmaChannelId::XDMAC_PERID_0, 0u, 0u},
  {PeripheralId::PWM0, DmaChannelId::XDMAC_PERID_13, 0u, 13u},
  {PeripheralId::PWM1, DmaChannelId::XDMAC_PERID_39, 0u, 39u},
  {PeripheralId::QSPI, DmaChannelId::XDMAC_PERID_5, 0u, 5u},
  {PeripheralId::QSPI, DmaChannelId::XDMAC_PERID_6, 0u, 6u},
  {PeripheralId::SPI0, DmaChannelId::XDMAC_PERID_1, 0u, 1u},
  {PeripheralId::SPI0, DmaChannelId::XDMAC_PERID_2, 0u, 2u},
  {PeripheralId::SPI1, DmaChannelId::XDMAC_PERID_3, 0u, 3u},
  {PeripheralId::SPI1, DmaChannelId::XDMAC_PERID_4, 0u, 4u},
  {PeripheralId::TC0, DmaChannelId::XDMAC_PERID_40, 0u, 40u},
  {PeripheralId::TC1, DmaChannelId::XDMAC_PERID_41, 0u, 41u},
  {PeripheralId::TC2, DmaChannelId::XDMAC_PERID_42, 0u, 42u},
  {PeripheralId::TC3, DmaChannelId::XDMAC_PERID_43, 0u, 43u},
  {PeripheralId::TWIHS0, DmaChannelId::XDMAC_PERID_14, 0u, 14u},
  {PeripheralId::TWIHS0, DmaChannelId::XDMAC_PERID_15, 0u, 15u},
  {PeripheralId::TWIHS1, DmaChannelId::XDMAC_PERID_16, 0u, 16u},
  {PeripheralId::TWIHS1, DmaChannelId::XDMAC_PERID_17, 0u, 17u},
  {PeripheralId::TWIHS2, DmaChannelId::XDMAC_PERID_18, 0u, 18u},
  {PeripheralId::TWIHS2, DmaChannelId::XDMAC_PERID_19, 0u, 19u},
  {PeripheralId::UART0, DmaChannelId::XDMAC_PERID_20, 0u, 20u},
  {PeripheralId::UART0, DmaChannelId::XDMAC_PERID_21, 0u, 21u},
  {PeripheralId::UART1, DmaChannelId::XDMAC_PERID_22, 0u, 22u},
  {PeripheralId::UART1, DmaChannelId::XDMAC_PERID_23, 0u, 23u},
  {PeripheralId::UART2, DmaChannelId::XDMAC_PERID_24, 0u, 24u},
  {PeripheralId::UART2, DmaChannelId::XDMAC_PERID_25, 0u, 25u},
  {PeripheralId::UART3, DmaChannelId::XDMAC_PERID_26, 0u, 26u},
  {PeripheralId::UART3, DmaChannelId::XDMAC_PERID_27, 0u, 27u},
  {PeripheralId::UART4, DmaChannelId::XDMAC_PERID_28, 0u, 28u},
  {PeripheralId::UART4, DmaChannelId::XDMAC_PERID_29, 0u, 29u},
  {PeripheralId::USART0, DmaChannelId::XDMAC_PERID_7, 0u, 7u},
  {PeripheralId::USART0, DmaChannelId::XDMAC_PERID_8, 0u, 8u},
  {PeripheralId::USART1, DmaChannelId::XDMAC_PERID_10, 0u, 10u},
  {PeripheralId::USART1, DmaChannelId::XDMAC_PERID_9, 0u, 9u},
  {PeripheralId::USART2, DmaChannelId::XDMAC_PERID_11, 0u, 11u},
  {PeripheralId::USART2, DmaChannelId::XDMAC_PERID_12, 0u, 12u},
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
