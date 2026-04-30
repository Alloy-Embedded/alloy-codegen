#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
enum class CapabilityId : std::uint16_t {
  none,
  runtime_support_adc,
  runtime_support_can,
  device_core_count,
  device_multicore_topology,
  runtime_support_dma,
  runtime_support_dma_router,
  runtime_support_eth,
  capability_gpio_imxrt_gpio_v1_io00,
  capability_gpio_imxrt_gpio_v1_io01,
  runtime_support_gpio,
  capability_instance_gpio1_bga196_io00,
  capability_instance_gpio1_bga196_io01,
  capability_instance_gpio4_bga196_io00,
  capability_instance_gpio4_bga196_io01,
  runtime_support_pwm,
  capability_lpspi_lpspi_v1_cs,
  capability_lpspi_lpspi_v1_sck,
  runtime_support_spi,
  capability_instance_lpspi1_bga196_cs,
  capability_instance_lpspi1_bga196_sck,
  runtime_support_timer,
  capability_lpuart_lpuart_v1_rx,
  capability_lpuart_lpuart_v1_tx,
  runtime_support_uart,
  capability_instance_lpuart1_bga196_rx,
  capability_instance_lpuart1_bga196_tx,
  runtime_support_usb,
  runtime_support_watchdog,
};

enum class CapabilityScopeId : std::uint16_t {
  none,
  device,
  instance_overlay,
  ip_block,
  runtime_contract,
};

enum class CapabilityNameId : std::uint16_t {
  none,
  available_signal,
  core_count,
  multicore_topology,
  runtime_supported,
  signal_role,
};

enum class CapabilityValueId : std::uint16_t {
  none,
  _1,
  cs,
  io00,
  io01,
  rx,
  sck,
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
inline constexpr std::array<CapabilityDescriptor, 28> kCapabilities = {{
  {CapabilityId::runtime_support_adc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_can, CapabilityScopeId::runtime_contract, PeripheralClassId::class_can, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::device_core_count, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityId::device_multicore_topology, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityId::runtime_support_dma, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_dma_router, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma_router, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_eth, CapabilityScopeId::runtime_contract, PeripheralClassId::class_eth, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_gpio_imxrt_gpio_v1_io00, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::io00, PeripheralId::none},
  {CapabilityId::capability_gpio_imxrt_gpio_v1_io01, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::io01, PeripheralId::none},
  {CapabilityId::runtime_support_gpio, CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_gpio1_bga196_io00, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io00, PeripheralId::GPIO1},
  {CapabilityId::capability_instance_gpio1_bga196_io01, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io01, PeripheralId::GPIO1},
  {CapabilityId::capability_instance_gpio4_bga196_io00, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io00, PeripheralId::GPIO4},
  {CapabilityId::capability_instance_gpio4_bga196_io01, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io01, PeripheralId::GPIO4},
  {CapabilityId::runtime_support_pwm, CapabilityScopeId::runtime_contract, PeripheralClassId::class_pwm, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_lpspi_lpspi_v1_cs, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::cs, PeripheralId::none},
  {CapabilityId::capability_lpspi_lpspi_v1_sck, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_lpspi1_bga196_cs, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::cs, PeripheralId::LPSPI1},
  {CapabilityId::capability_instance_lpspi1_bga196_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::LPSPI1},
  {CapabilityId::runtime_support_timer, CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_lpuart_lpuart_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_lpuart_lpuart_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_lpuart1_bga196_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::LPUART1},
  {CapabilityId::capability_instance_lpuart1_bga196_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::LPUART1},
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

inline constexpr std::array<CapabilityHardwareLut, 28> kCapabilityHardwareLut = {{
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_can, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma_router, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_eth, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::io00, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::io01, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io00, PeripheralId::GPIO1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io01, PeripheralId::GPIO1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io00, PeripheralId::GPIO4},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io01, PeripheralId::GPIO4},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_pwm, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::cs, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::cs, PeripheralId::LPSPI1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::LPSPI1},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::LPUART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::LPUART1},
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
template<> struct CapabilityTraits<CapabilityId::runtime_support_can> : CapabilityTraitsBase<1> {};
template<> struct CapabilityTraits<CapabilityId::device_core_count> : CapabilityTraitsBase<2> {};
template<> struct CapabilityTraits<CapabilityId::device_multicore_topology> : CapabilityTraitsBase<3> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dma> : CapabilityTraitsBase<4> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dma_router> : CapabilityTraitsBase<5> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_eth> : CapabilityTraitsBase<6> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_imxrt_gpio_v1_io00> : CapabilityTraitsBase<7> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_imxrt_gpio_v1_io01> : CapabilityTraitsBase<8> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_gpio> : CapabilityTraitsBase<9> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpio1_bga196_io00> : CapabilityTraitsBase<10> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpio1_bga196_io01> : CapabilityTraitsBase<11> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpio4_bga196_io00> : CapabilityTraitsBase<12> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpio4_bga196_io01> : CapabilityTraitsBase<13> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_pwm> : CapabilityTraitsBase<14> {};
template<> struct CapabilityTraits<CapabilityId::capability_lpspi_lpspi_v1_cs> : CapabilityTraitsBase<15> {};
template<> struct CapabilityTraits<CapabilityId::capability_lpspi_lpspi_v1_sck> : CapabilityTraitsBase<16> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_spi> : CapabilityTraitsBase<17> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_lpspi1_bga196_cs> : CapabilityTraitsBase<18> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_lpspi1_bga196_sck> : CapabilityTraitsBase<19> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_timer> : CapabilityTraitsBase<20> {};
template<> struct CapabilityTraits<CapabilityId::capability_lpuart_lpuart_v1_rx> : CapabilityTraitsBase<21> {};
template<> struct CapabilityTraits<CapabilityId::capability_lpuart_lpuart_v1_tx> : CapabilityTraitsBase<22> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_uart> : CapabilityTraitsBase<23> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_lpuart1_bga196_rx> : CapabilityTraitsBase<24> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_lpuart1_bga196_tx> : CapabilityTraitsBase<25> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_usb> : CapabilityTraitsBase<26> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_watchdog> : CapabilityTraitsBase<27> {};

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
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_can,
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
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_eth> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_eth,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_gpio> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 7> kCapabilityIds = {{
    CapabilityId::capability_gpio_imxrt_gpio_v1_io00,
    CapabilityId::capability_gpio_imxrt_gpio_v1_io01,
    CapabilityId::runtime_support_gpio,
    CapabilityId::capability_instance_gpio1_bga196_io00,
    CapabilityId::capability_instance_gpio1_bga196_io01,
    CapabilityId::capability_instance_gpio4_bga196_io00,
    CapabilityId::capability_instance_gpio4_bga196_io01,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_pwm> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_pwm,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_spi> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::capability_lpspi_lpspi_v1_cs,
    CapabilityId::capability_lpspi_lpspi_v1_sck,
    CapabilityId::runtime_support_spi,
    CapabilityId::capability_instance_lpspi1_bga196_cs,
    CapabilityId::capability_instance_lpspi1_bga196_sck,
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
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::capability_lpuart_lpuart_v1_rx,
    CapabilityId::capability_lpuart_lpuart_v1_tx,
    CapabilityId::runtime_support_uart,
    CapabilityId::capability_instance_lpuart1_bga196_rx,
    CapabilityId::capability_instance_lpuart1_bga196_tx,
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
struct PeripheralCapabilityTraits<PeripheralId::ADC2> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::CAN1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::CAN2> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::CAN3> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DMA0> {
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
struct PeripheralCapabilityTraits<PeripheralId::ENET> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIO1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_gpio1_bga196_io00,
    CapabilityId::capability_instance_gpio1_bga196_io01,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIO4> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_gpio4_bga196_io00,
    CapabilityId::capability_instance_gpio4_bga196_io01,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPT1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPT2> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::LPSPI1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_lpspi1_bga196_cs,
    CapabilityId::capability_instance_lpspi1_bga196_sck,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::LPUART1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_lpuart1_bga196_rx,
    CapabilityId::capability_instance_lpuart1_bga196_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::LPUART3> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PIT> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PWM1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PWM2> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PWM3> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PWM4> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::RTWDOG> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::USB1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::WDOG1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::WDOG2> {
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
