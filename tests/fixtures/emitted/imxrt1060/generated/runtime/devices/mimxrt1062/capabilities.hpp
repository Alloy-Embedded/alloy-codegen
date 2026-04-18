#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
enum class CapabilityId : std::uint16_t {
  none,
  capability_gpio_imxrt_gpio_v1_io00,
  capability_gpio_imxrt_gpio_v1_io01,
  runtime_support_gpio,
  capability_instance_gpio1_bga196_io00,
  capability_instance_gpio1_bga196_io01,
  capability_instance_gpio4_bga196_io00,
  capability_instance_gpio4_bga196_io01,
  capability_lpspi_lpspi_v1_cs,
  capability_lpspi_lpspi_v1_sck,
  runtime_support_spi,
  capability_instance_lpspi1_bga196_cs,
  capability_instance_lpspi1_bga196_sck,
  capability_lpuart_lpuart_v1_rx,
  capability_lpuart_lpuart_v1_tx,
  runtime_support_uart,
  capability_instance_lpuart1_bga196_rx,
  capability_instance_lpuart1_bga196_tx,
};

enum class CapabilityScopeId : std::uint16_t {
  none,
  instance_overlay,
  ip_block,
  runtime_contract,
};

enum class CapabilityNameId : std::uint16_t {
  none,
  available_signal,
  runtime_supported,
  signal_role,
};

enum class CapabilityValueId : std::uint16_t {
  none,
  cs,
  io00,
  io01,
  rx,
  sck,
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
inline constexpr std::array<CapabilityDescriptor, 17> kCapabilities = {{
  {CapabilityId::capability_gpio_imxrt_gpio_v1_io00, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::io00, PeripheralId::none},
  {CapabilityId::capability_gpio_imxrt_gpio_v1_io01, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::io01, PeripheralId::none},
  {CapabilityId::runtime_support_gpio, CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_gpio1_bga196_io00, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io00, PeripheralId::GPIO1},
  {CapabilityId::capability_instance_gpio1_bga196_io01, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io01, PeripheralId::GPIO1},
  {CapabilityId::capability_instance_gpio4_bga196_io00, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io00, PeripheralId::GPIO4},
  {CapabilityId::capability_instance_gpio4_bga196_io01, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::io01, PeripheralId::GPIO4},
  {CapabilityId::capability_lpspi_lpspi_v1_cs, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::cs, PeripheralId::none},
  {CapabilityId::capability_lpspi_lpspi_v1_sck, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_lpspi1_bga196_cs, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::cs, PeripheralId::LPSPI1},
  {CapabilityId::capability_instance_lpspi1_bga196_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::LPSPI1},
  {CapabilityId::capability_lpuart_lpuart_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_lpuart_lpuart_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_lpuart1_bga196_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::LPUART1},
  {CapabilityId::capability_instance_lpuart1_bga196_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::LPUART1},
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

template<>
struct CapabilityTraits<CapabilityId::capability_gpio_imxrt_gpio_v1_io00> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::io00;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_gpio_imxrt_gpio_v1_io01> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::io01;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_gpio> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_gpio1_bga196_io00> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::io00;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_gpio1_bga196_io01> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::io01;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_gpio4_bga196_io00> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::io00;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO4;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_gpio4_bga196_io01> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::io01;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO4;
};

template<>
struct CapabilityTraits<CapabilityId::capability_lpspi_lpspi_v1_cs> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::cs;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_lpspi_lpspi_v1_sck> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::sck;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_spi> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_lpspi1_bga196_cs> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::cs;
  static constexpr PeripheralId kPeripheralId = PeripheralId::LPSPI1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_lpspi1_bga196_sck> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::sck;
  static constexpr PeripheralId kPeripheralId = PeripheralId::LPSPI1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_lpuart_lpuart_v1_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_lpuart_lpuart_v1_tx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::tx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_uart> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_lpuart1_bga196_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::LPUART1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_lpuart1_bga196_tx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::tx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::LPUART1;
};

template<PeripheralClassId Id>
struct PeripheralClassCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
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

template<PeripheralId Id>
struct PeripheralCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
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

}
}
}
}
}
}
