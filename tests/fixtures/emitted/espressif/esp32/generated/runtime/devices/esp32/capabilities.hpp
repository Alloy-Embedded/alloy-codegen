#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32 {
enum class CapabilityId : std::uint16_t {
  none,
  runtime_support_adc,
  device_core_count,
  device_multicore_topology,
  device_secondary_core_release_register,
  runtime_support_gpio,
  runtime_support_i2c,
  runtime_support_spi,
  capability_uart_esp32_uart_v1_rx,
  capability_uart_esp32_uart_v1_tx,
  runtime_support_uart,
  capability_instance_uart0_qfn48_rx,
  capability_instance_uart0_qfn48_tx,
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
  secondary_core_release_register,
  signal_role,
};

enum class CapabilityValueId : std::uint16_t {
  none,
  _2,
  register_dport_appcpu_ctrl_b,
  rx,
  true_value,
  tx,
  xtensa_dual_core,
};

struct CapabilityDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityNameId name_id;
  CapabilityValueId value_id;
  PeripheralId peripheral_id;
};
inline constexpr std::array<CapabilityDescriptor, 12> kCapabilities = {{
  {CapabilityId::runtime_support_adc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::device_core_count, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_2, PeripheralId::none},
  {CapabilityId::device_multicore_topology, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::xtensa_dual_core, PeripheralId::none},
  {CapabilityId::device_secondary_core_release_register, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::secondary_core_release_register, CapabilityValueId::register_dport_appcpu_ctrl_b, PeripheralId::none},
  {CapabilityId::runtime_support_gpio, CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_i2c, CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_uart_esp32_uart_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_uart_esp32_uart_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_uart0_qfn48_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_qfn48_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART0},
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

inline constexpr std::array<CapabilityHardwareLut, 12> kCapabilityHardwareLut = {{
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_2, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::xtensa_dual_core, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::secondary_core_release_register, CapabilityValueId::register_dport_appcpu_ctrl_b, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART0},
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
template<> struct CapabilityTraits<CapabilityId::device_core_count> : CapabilityTraitsBase<1> {};
template<> struct CapabilityTraits<CapabilityId::device_multicore_topology> : CapabilityTraitsBase<2> {};
template<> struct CapabilityTraits<CapabilityId::device_secondary_core_release_register> : CapabilityTraitsBase<3> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_gpio> : CapabilityTraitsBase<4> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_i2c> : CapabilityTraitsBase<5> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_spi> : CapabilityTraitsBase<6> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_esp32_uart_v1_rx> : CapabilityTraitsBase<7> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_esp32_uart_v1_tx> : CapabilityTraitsBase<8> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_uart> : CapabilityTraitsBase<9> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn48_rx> : CapabilityTraitsBase<10> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn48_tx> : CapabilityTraitsBase<11> {};

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
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_spi> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_spi,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_uart> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::capability_uart_esp32_uart_v1_rx,
    CapabilityId::capability_uart_esp32_uart_v1_tx,
    CapabilityId::runtime_support_uart,
    CapabilityId::capability_instance_uart0_qfn48_rx,
    CapabilityId::capability_instance_uart0_qfn48_tx,
  }};
};

template<PeripheralId Id>
struct PeripheralCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIO> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::I2C0> {
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
struct PeripheralCapabilityTraits<PeripheralId::SENS> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::SPI0> {
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
struct PeripheralCapabilityTraits<PeripheralId::SPI2> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::SPI3> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_uart0_qfn48_rx,
    CapabilityId::capability_instance_uart0_qfn48_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART2> {
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
