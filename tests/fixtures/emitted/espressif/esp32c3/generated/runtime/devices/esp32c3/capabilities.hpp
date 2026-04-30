#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class CapabilityId : std::uint16_t {
  none,
  runtime_support_adc,
  runtime_dma_APB_SARADC_DMA_ADC_DATA,
  device_core_count,
  device_multicore_topology,
  runtime_support_dma,
  runtime_support_gpio,
  capability_i2c_esp32c3_i2c_v1_scl,
  capability_i2c_esp32c3_i2c_v1_sda,
  runtime_support_i2c,
  capability_instance_i2c0_qfn32_scl,
  capability_instance_i2c0_qfn32_sda,
  capability_spi_esp32c3_spi_v1_cs,
  capability_spi_esp32c3_spi_v1_miso,
  capability_spi_esp32c3_spi_v1_mosi,
  capability_spi_esp32c3_spi_v1_sck,
  runtime_support_spi,
  runtime_dma_SPI2_DMA_SPI2_RX_RX,
  runtime_dma_SPI2_DMA_SPI2_TX_TX,
  capability_instance_spi2_qfn32_cs,
  capability_instance_spi2_qfn32_miso,
  capability_instance_spi2_qfn32_mosi,
  capability_instance_spi2_qfn32_sck,
  capability_uart_esp32c3_uart_v1_rx,
  capability_uart_esp32c3_uart_v1_tx,
  runtime_support_uart,
  runtime_dma_UART0_DMA_UART0_RX_RX,
  runtime_dma_UART0_DMA_UART0_TX_TX,
  capability_instance_uart0_qfn32_rx,
  capability_instance_uart0_qfn32_tx,
  capability_instance_uart1_qfn32_rx,
  capability_instance_uart1_qfn32_tx,
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
  DATA,
  RX,
  TX,
  cs,
  miso,
  mosi,
  rx,
  sck,
  scl,
  sda,
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
inline constexpr std::array<CapabilityDescriptor, 31> kCapabilities = {{
  {CapabilityId::runtime_support_adc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_APB_SARADC_DMA_ADC_DATA, CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::DATA, PeripheralId::APB_SARADC},
  {CapabilityId::device_core_count, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityId::device_multicore_topology, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityId::runtime_support_dma, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_gpio, CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_i2c_esp32c3_i2c_v1_scl, CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::scl, PeripheralId::none},
  {CapabilityId::capability_i2c_esp32c3_i2c_v1_sda, CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::sda, PeripheralId::none},
  {CapabilityId::runtime_support_i2c, CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_i2c0_qfn32_scl, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::I2C0},
  {CapabilityId::capability_instance_i2c0_qfn32_sda, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::I2C0},
  {CapabilityId::capability_spi_esp32c3_spi_v1_cs, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::cs, PeripheralId::none},
  {CapabilityId::capability_spi_esp32c3_spi_v1_miso, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::miso, PeripheralId::none},
  {CapabilityId::capability_spi_esp32c3_spi_v1_mosi, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::mosi, PeripheralId::none},
  {CapabilityId::capability_spi_esp32c3_spi_v1_sck, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_SPI2_DMA_SPI2_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI2},
  {CapabilityId::runtime_dma_SPI2_DMA_SPI2_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI2},
  {CapabilityId::capability_instance_spi2_qfn32_cs, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::cs, PeripheralId::SPI2},
  {CapabilityId::capability_instance_spi2_qfn32_miso, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::miso, PeripheralId::SPI2},
  {CapabilityId::capability_instance_spi2_qfn32_mosi, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::mosi, PeripheralId::SPI2},
  {CapabilityId::capability_instance_spi2_qfn32_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI2},
  {CapabilityId::capability_uart_esp32c3_uart_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_uart_esp32c3_uart_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART0},
  {CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_qfn32_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_qfn32_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart1_qfn32_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_qfn32_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART1},
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

inline constexpr std::array<CapabilityHardwareLut, 31> kCapabilityHardwareLut = {{
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::DATA, PeripheralId::APB_SARADC},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::scl, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::sda, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::I2C0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::I2C0},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::cs, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::miso, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::mosi, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI2},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::cs, PeripheralId::SPI2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::miso, PeripheralId::SPI2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::mosi, PeripheralId::SPI2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI2},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART1},
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
template<> struct CapabilityTraits<CapabilityId::runtime_dma_APB_SARADC_DMA_ADC_DATA> : CapabilityTraitsBase<1> {};
template<> struct CapabilityTraits<CapabilityId::device_core_count> : CapabilityTraitsBase<2> {};
template<> struct CapabilityTraits<CapabilityId::device_multicore_topology> : CapabilityTraitsBase<3> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dma> : CapabilityTraitsBase<4> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_gpio> : CapabilityTraitsBase<5> {};
template<> struct CapabilityTraits<CapabilityId::capability_i2c_esp32c3_i2c_v1_scl> : CapabilityTraitsBase<6> {};
template<> struct CapabilityTraits<CapabilityId::capability_i2c_esp32c3_i2c_v1_sda> : CapabilityTraitsBase<7> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_i2c> : CapabilityTraitsBase<8> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_i2c0_qfn32_scl> : CapabilityTraitsBase<9> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_i2c0_qfn32_sda> : CapabilityTraitsBase<10> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_esp32c3_spi_v1_cs> : CapabilityTraitsBase<11> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_esp32c3_spi_v1_miso> : CapabilityTraitsBase<12> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_esp32c3_spi_v1_mosi> : CapabilityTraitsBase<13> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_esp32c3_spi_v1_sck> : CapabilityTraitsBase<14> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_spi> : CapabilityTraitsBase<15> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI2_DMA_SPI2_RX_RX> : CapabilityTraitsBase<16> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI2_DMA_SPI2_TX_TX> : CapabilityTraitsBase<17> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi2_qfn32_cs> : CapabilityTraitsBase<18> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi2_qfn32_miso> : CapabilityTraitsBase<19> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi2_qfn32_mosi> : CapabilityTraitsBase<20> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi2_qfn32_sck> : CapabilityTraitsBase<21> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_esp32c3_uart_v1_rx> : CapabilityTraitsBase<22> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_esp32c3_uart_v1_tx> : CapabilityTraitsBase<23> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_uart> : CapabilityTraitsBase<24> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX> : CapabilityTraitsBase<25> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX> : CapabilityTraitsBase<26> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn32_rx> : CapabilityTraitsBase<27> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn32_tx> : CapabilityTraitsBase<28> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_qfn32_rx> : CapabilityTraitsBase<29> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_qfn32_tx> : CapabilityTraitsBase<30> {};

template<PeripheralClassId Id>
struct PeripheralClassCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_adc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::runtime_support_adc,
    CapabilityId::runtime_dma_APB_SARADC_DMA_ADC_DATA,
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
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_gpio> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_gpio,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_i2c> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::capability_i2c_esp32c3_i2c_v1_scl,
    CapabilityId::capability_i2c_esp32c3_i2c_v1_sda,
    CapabilityId::runtime_support_i2c,
    CapabilityId::capability_instance_i2c0_qfn32_scl,
    CapabilityId::capability_instance_i2c0_qfn32_sda,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_spi> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 11> kCapabilityIds = {{
    CapabilityId::capability_spi_esp32c3_spi_v1_cs,
    CapabilityId::capability_spi_esp32c3_spi_v1_miso,
    CapabilityId::capability_spi_esp32c3_spi_v1_mosi,
    CapabilityId::capability_spi_esp32c3_spi_v1_sck,
    CapabilityId::runtime_support_spi,
    CapabilityId::runtime_dma_SPI2_DMA_SPI2_RX_RX,
    CapabilityId::runtime_dma_SPI2_DMA_SPI2_TX_TX,
    CapabilityId::capability_instance_spi2_qfn32_cs,
    CapabilityId::capability_instance_spi2_qfn32_miso,
    CapabilityId::capability_instance_spi2_qfn32_mosi,
    CapabilityId::capability_instance_spi2_qfn32_sck,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_uart> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 9> kCapabilityIds = {{
    CapabilityId::capability_uart_esp32c3_uart_v1_rx,
    CapabilityId::capability_uart_esp32c3_uart_v1_tx,
    CapabilityId::runtime_support_uart,
    CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX,
    CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX,
    CapabilityId::capability_instance_uart0_qfn32_rx,
    CapabilityId::capability_instance_uart0_qfn32_tx,
    CapabilityId::capability_instance_uart1_qfn32_rx,
    CapabilityId::capability_instance_uart1_qfn32_tx,
  }};
};

template<PeripheralId Id>
struct PeripheralCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::APB_SARADC> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_dma_APB_SARADC_DMA_ADC_DATA,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DMA> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIO> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::I2C0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_i2c0_qfn32_scl,
    CapabilityId::capability_instance_i2c0_qfn32_sda,
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
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_SPI2_DMA_SPI2_RX_RX,
    CapabilityId::runtime_dma_SPI2_DMA_SPI2_TX_TX,
    CapabilityId::capability_instance_spi2_qfn32_cs,
    CapabilityId::capability_instance_spi2_qfn32_miso,
    CapabilityId::capability_instance_spi2_qfn32_mosi,
    CapabilityId::capability_instance_spi2_qfn32_sck,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX,
    CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX,
    CapabilityId::capability_instance_uart0_qfn32_rx,
    CapabilityId::capability_instance_uart0_qfn32_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_uart1_qfn32_rx,
    CapabilityId::capability_instance_uart1_qfn32_tx,
  }};
};

}
}
}
}
}
}
