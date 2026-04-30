#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
enum class CapabilityId : std::uint16_t {
  none,
  runtime_support_adc,
  capability_fdcan_fdcan_v1_0_rx,
  capability_fdcan_fdcan_v1_0_tx,
  runtime_support_can,
  capability_instance_fdcan1_lqfp64_rx,
  capability_instance_fdcan1_lqfp64_tx,
  runtime_support_dac,
  device_core_count,
  device_multicore_topology,
  runtime_support_dma,
  runtime_support_dma_router,
  runtime_support_gpio,
  runtime_support_i2c,
  runtime_support_rtc,
  runtime_support_spi,
  runtime_support_timer,
  runtime_support_uart,
  runtime_dma_USART1_DMA1_DMA1_CH1_RX,
  runtime_dma_USART1_DMA1_DMA1_CH2_TX,
  runtime_support_usb,
  runtime_support_watchdog,
};

enum class CapabilityScopeId : std::uint16_t {
  none,
  device,
  dma_binding,
  instance_overlay,
  ip_block,
  runtime_contract,
};

enum class CapabilityNameId : std::uint16_t {
  none,
  available_signal,
  core_count,
  dma_compatible_signal,
  multicore_topology,
  runtime_supported,
  signal_role,
};

enum class CapabilityValueId : std::uint16_t {
  none,
  _1,
  RX,
  TX,
  rx,
  single_core,
  true_value,
  tx,
};

struct CapabilityDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityNameId name_id;
  CapabilityValueId value_id;
  PeripheralId peripheral_id;
};
inline constexpr std::array<CapabilityDescriptor, 21> kCapabilities = {{
  {CapabilityId::runtime_support_adc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_fdcan_fdcan_v1_0_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_fdcan_fdcan_v1_0_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_can, CapabilityScopeId::runtime_contract, PeripheralClassId::class_can, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_fdcan1_lqfp64_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::FDCAN1},
  {CapabilityId::capability_instance_fdcan1_lqfp64_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::FDCAN1},
  {CapabilityId::runtime_support_dac, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dac, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::device_core_count, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityId::device_multicore_topology, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityId::runtime_support_dma, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_dma_router, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma_router, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_gpio, CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_i2c, CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_rtc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_rtc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_timer, CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH1_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART1},
  {CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH2_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART1},
  {CapabilityId::runtime_support_usb, CapabilityScopeId::runtime_contract, PeripheralClassId::class_usb, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_watchdog, CapabilityScopeId::runtime_contract, PeripheralClassId::class_watchdog, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
}};

template<CapabilityId Id>
struct CapabilityTraits {
  static constexpr bool kPresent = false;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::none;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::none;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::none;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::none;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

struct CapabilityHardwareLut {
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityNameId name_id;
  CapabilityValueId value_id;
  PeripheralId peripheral_id;
};

inline constexpr std::array<CapabilityHardwareLut, 21> kCapabilityHardwareLut = {{
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_can, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::FDCAN1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::FDCAN1},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dac, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma_router, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_rtc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART1},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_usb, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_watchdog, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
}};

template<std::size_t Index>
struct CapabilityTraitsBase {
  static constexpr auto& kFacts = kCapabilityHardwareLut[Index];
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = kFacts.scope_id;
  static constexpr PeripheralClassId kPeripheralClassId = kFacts.peripheral_class_id;
  static constexpr CapabilityNameId kNameId = kFacts.name_id;
  static constexpr CapabilityValueId kValueId = kFacts.value_id;
  static constexpr PeripheralId kPeripheralId = kFacts.peripheral_id;
};

template<> struct CapabilityTraits<CapabilityId::runtime_support_adc> : CapabilityTraitsBase<0> {};
template<> struct CapabilityTraits<CapabilityId::capability_fdcan_fdcan_v1_0_rx> : CapabilityTraitsBase<1> {};
template<> struct CapabilityTraits<CapabilityId::capability_fdcan_fdcan_v1_0_tx> : CapabilityTraitsBase<2> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_can> : CapabilityTraitsBase<3> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_fdcan1_lqfp64_rx> : CapabilityTraitsBase<4> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_fdcan1_lqfp64_tx> : CapabilityTraitsBase<5> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dac> : CapabilityTraitsBase<6> {};
template<> struct CapabilityTraits<CapabilityId::device_core_count> : CapabilityTraitsBase<7> {};
template<> struct CapabilityTraits<CapabilityId::device_multicore_topology> : CapabilityTraitsBase<8> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dma> : CapabilityTraitsBase<9> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dma_router> : CapabilityTraitsBase<10> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_gpio> : CapabilityTraitsBase<11> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_i2c> : CapabilityTraitsBase<12> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_rtc> : CapabilityTraitsBase<13> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_spi> : CapabilityTraitsBase<14> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_timer> : CapabilityTraitsBase<15> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_uart> : CapabilityTraitsBase<16> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH1_RX> : CapabilityTraitsBase<17> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH2_TX> : CapabilityTraitsBase<18> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_usb> : CapabilityTraitsBase<19> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_watchdog> : CapabilityTraitsBase<20> {};

template<PeripheralClassId Id>
struct PeripheralClassCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_adc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_adc,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_can> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::capability_fdcan_fdcan_v1_0_rx,
    CapabilityId::capability_fdcan_fdcan_v1_0_tx,
    CapabilityId::runtime_support_can,
    CapabilityId::capability_instance_fdcan1_lqfp64_rx,
    CapabilityId::capability_instance_fdcan1_lqfp64_tx,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_dac> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_dac,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_dma> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_dma,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_dma_router> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_dma_router,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_gpio> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_gpio,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_i2c> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_i2c,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_rtc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_rtc,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_spi> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_spi,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_timer> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_timer,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_uart> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 3> kCapabilityIds = {{
    CapabilityId::runtime_support_uart,
    CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH1_RX,
    CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH2_TX,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_usb> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_usb,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_watchdog> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_watchdog,
  }};
};

template<PeripheralId Id>
struct PeripheralCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::ADC1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DAC> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DMA1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DMAMUX1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::FDCAN1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_fdcan1_lqfp64_rx,
    CapabilityId::capability_instance_fdcan1_lqfp64_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIOB> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::I2C2> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::IWDG> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TIM1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH1_RX,
    CapabilityId::runtime_dma_USART1_DMA1_DMA1_CH2_TX,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::USB> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

}
}
}
}
}
}
