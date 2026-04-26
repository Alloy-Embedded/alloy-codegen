#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class CapabilityId : std::uint16_t {
  none,
  capability_adc_rp2040_adc_v1_ch0,
  capability_adc_rp2040_adc_v1_ch1,
  capability_adc_rp2040_adc_v1_ch2,
  capability_adc_rp2040_adc_v1_ch3,
  runtime_support_adc,
  runtime_dma_ADC_DMA_ADC_FIFO,
  capability_instance_adc_qfn56_ch0,
  capability_instance_adc_qfn56_ch1,
  capability_instance_adc_qfn56_ch2,
  capability_instance_adc_qfn56_ch3,
  device_core_count,
  device_multicore_topology,
  runtime_support_dma,
  runtime_support_pwm,
  runtime_support_rtc,
  capability_spi_rp2040_spi_v1_csn,
  capability_spi_rp2040_spi_v1_rx,
  capability_spi_rp2040_spi_v1_sck,
  capability_spi_rp2040_spi_v1_tx,
  runtime_support_spi,
  runtime_dma_SPI0_DMA_SPI0_RX_RX,
  runtime_dma_SPI0_DMA_SPI0_TX_TX,
  capability_instance_spi0_qfn56_csn,
  capability_instance_spi0_qfn56_rx,
  capability_instance_spi0_qfn56_sck,
  capability_instance_spi0_qfn56_tx,
  runtime_dma_SPI1_DMA_SPI1_RX_RX,
  runtime_dma_SPI1_DMA_SPI1_TX_TX,
  capability_instance_spi1_qfn56_csn,
  capability_instance_spi1_qfn56_rx,
  capability_instance_spi1_qfn56_sck,
  capability_instance_spi1_qfn56_tx,
  runtime_support_timer,
  capability_uart_rp2040_uart_v1_cts,
  capability_uart_rp2040_uart_v1_rts,
  capability_uart_rp2040_uart_v1_rx,
  capability_uart_rp2040_uart_v1_tx,
  runtime_support_uart,
  runtime_dma_UART0_DMA_UART0_RX_RX,
  runtime_dma_UART0_DMA_UART0_TX_TX,
  capability_instance_uart0_qfn56_cts,
  capability_instance_uart0_qfn56_rts,
  capability_instance_uart0_qfn56_rx,
  capability_instance_uart0_qfn56_tx,
  runtime_dma_UART1_DMA_UART1_RX_RX,
  runtime_dma_UART1_DMA_UART1_TX_TX,
  capability_instance_uart1_qfn56_cts,
  capability_instance_uart1_qfn56_rts,
  capability_instance_uart1_qfn56_rx,
  capability_instance_uart1_qfn56_tx,
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
  FIFO,
  RX,
  TX,
  ch0,
  ch1,
  ch2,
  ch3,
  csn,
  cts,
  rts,
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
inline constexpr std::array<CapabilityDescriptor, 51> kCapabilities = {{
  {CapabilityId::capability_adc_rp2040_adc_v1_ch0, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch0, PeripheralId::none},
  {CapabilityId::capability_adc_rp2040_adc_v1_ch1, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch1, PeripheralId::none},
  {CapabilityId::capability_adc_rp2040_adc_v1_ch2, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch2, PeripheralId::none},
  {CapabilityId::capability_adc_rp2040_adc_v1_ch3, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch3, PeripheralId::none},
  {CapabilityId::runtime_support_adc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO, CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::FIFO, PeripheralId::ADC},
  {CapabilityId::capability_instance_adc_qfn56_ch0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch0, PeripheralId::ADC},
  {CapabilityId::capability_instance_adc_qfn56_ch1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch1, PeripheralId::ADC},
  {CapabilityId::capability_instance_adc_qfn56_ch2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch2, PeripheralId::ADC},
  {CapabilityId::capability_instance_adc_qfn56_ch3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch3, PeripheralId::ADC},
  {CapabilityId::device_core_count, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityId::device_multicore_topology, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityId::runtime_support_dma, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_pwm, CapabilityScopeId::runtime_contract, PeripheralClassId::class_pwm, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_rtc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_rtc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_csn, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::csn, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_sck, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_SPI0_DMA_SPI0_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI0},
  {CapabilityId::runtime_dma_SPI0_DMA_SPI0_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_qfn56_csn, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::csn, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_qfn56_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_qfn56_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_qfn56_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::SPI0},
  {CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI1},
  {CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_qfn56_csn, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::csn, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_qfn56_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_qfn56_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_qfn56_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::SPI1},
  {CapabilityId::runtime_support_timer, CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_cts, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::cts, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_rts, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rts, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART0},
  {CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_qfn56_cts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_qfn56_rts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_qfn56_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_qfn56_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART0},
  {CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART1},
  {CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_qfn56_cts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_qfn56_rts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_qfn56_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_qfn56_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART1},
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

template<>
struct CapabilityTraits<CapabilityId::capability_adc_rp2040_adc_v1_ch0> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch0;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_adc_rp2040_adc_v1_ch1> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch1;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_adc_rp2040_adc_v1_ch2> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch2;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_adc_rp2040_adc_v1_ch3> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch3;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_adc> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::FIFO;
  static constexpr PeripheralId kPeripheralId = PeripheralId::ADC;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_adc_qfn56_ch0> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch0;
  static constexpr PeripheralId kPeripheralId = PeripheralId::ADC;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_adc_qfn56_ch1> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch1;
  static constexpr PeripheralId kPeripheralId = PeripheralId::ADC;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_adc_qfn56_ch2> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch2;
  static constexpr PeripheralId kPeripheralId = PeripheralId::ADC;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_adc_qfn56_ch3> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::ch3;
  static constexpr PeripheralId kPeripheralId = PeripheralId::ADC;
};

template<>
struct CapabilityTraits<CapabilityId::device_core_count> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::device;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_device;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::core_count;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::_1;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::device_multicore_topology> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::device;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_device;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::multicore_topology;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::single_core;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_dma> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_pwm> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_rtc> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_rtc;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_csn> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::csn;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_sck> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::sck;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_tx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::tx;
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
struct CapabilityTraits<CapabilityId::runtime_dma_SPI0_DMA_SPI0_RX_RX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::RX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_dma_SPI0_DMA_SPI0_TX_TX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::TX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi0_qfn56_csn> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::csn;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi0_qfn56_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi0_qfn56_sck> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::sck;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi0_qfn56_tx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::tx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::RX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::TX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi1_qfn56_csn> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::csn;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi1_qfn56_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi1_qfn56_sck> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::sck;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_spi1_qfn56_tx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::tx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_timer> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_cts> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::cts;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_rts> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rts;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::ip_block;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::signal_role;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<>
struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_tx> {
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
struct CapabilityTraits<CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::RX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::TX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn56_cts> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::cts;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn56_rts> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rts;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn56_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart0_qfn56_tx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::tx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::RX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::dma_binding;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::dma_compatible_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::TX;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart1_qfn56_cts> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::cts;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart1_qfn56_rts> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rts;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart1_qfn56_rx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::rx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
};

template<>
struct CapabilityTraits<CapabilityId::capability_instance_uart1_qfn56_tx> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::instance_overlay;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::available_signal;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::tx;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
};

template<>
struct CapabilityTraits<CapabilityId::runtime_support_watchdog> {
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::runtime_contract;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::runtime_supported;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::true_value;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

template<PeripheralClassId Id>
struct PeripheralClassCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_adc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 10> kCapabilityIds = {{
    CapabilityId::capability_adc_rp2040_adc_v1_ch0,
    CapabilityId::capability_adc_rp2040_adc_v1_ch1,
    CapabilityId::capability_adc_rp2040_adc_v1_ch2,
    CapabilityId::capability_adc_rp2040_adc_v1_ch3,
    CapabilityId::runtime_support_adc,
    CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO,
    CapabilityId::capability_instance_adc_qfn56_ch0,
    CapabilityId::capability_instance_adc_qfn56_ch1,
    CapabilityId::capability_instance_adc_qfn56_ch2,
    CapabilityId::capability_instance_adc_qfn56_ch3,
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
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_pwm> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_pwm,
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
  inline static constexpr std::array<CapabilityId, 17> kCapabilityIds = {{
    CapabilityId::capability_spi_rp2040_spi_v1_csn,
    CapabilityId::capability_spi_rp2040_spi_v1_rx,
    CapabilityId::capability_spi_rp2040_spi_v1_sck,
    CapabilityId::capability_spi_rp2040_spi_v1_tx,
    CapabilityId::runtime_support_spi,
    CapabilityId::runtime_dma_SPI0_DMA_SPI0_RX_RX,
    CapabilityId::runtime_dma_SPI0_DMA_SPI0_TX_TX,
    CapabilityId::capability_instance_spi0_qfn56_csn,
    CapabilityId::capability_instance_spi0_qfn56_rx,
    CapabilityId::capability_instance_spi0_qfn56_sck,
    CapabilityId::capability_instance_spi0_qfn56_tx,
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX,
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX,
    CapabilityId::capability_instance_spi1_qfn56_csn,
    CapabilityId::capability_instance_spi1_qfn56_rx,
    CapabilityId::capability_instance_spi1_qfn56_sck,
    CapabilityId::capability_instance_spi1_qfn56_tx,
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
  inline static constexpr std::array<CapabilityId, 17> kCapabilityIds = {{
    CapabilityId::capability_uart_rp2040_uart_v1_cts,
    CapabilityId::capability_uart_rp2040_uart_v1_rts,
    CapabilityId::capability_uart_rp2040_uart_v1_rx,
    CapabilityId::capability_uart_rp2040_uart_v1_tx,
    CapabilityId::runtime_support_uart,
    CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX,
    CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX,
    CapabilityId::capability_instance_uart0_qfn56_cts,
    CapabilityId::capability_instance_uart0_qfn56_rts,
    CapabilityId::capability_instance_uart0_qfn56_rx,
    CapabilityId::capability_instance_uart0_qfn56_tx,
    CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX,
    CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX,
    CapabilityId::capability_instance_uart1_qfn56_cts,
    CapabilityId::capability_instance_uart1_qfn56_rts,
    CapabilityId::capability_instance_uart1_qfn56_rx,
    CapabilityId::capability_instance_uart1_qfn56_tx,
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
struct PeripheralCapabilityTraits<PeripheralId::ADC> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO,
    CapabilityId::capability_instance_adc_qfn56_ch0,
    CapabilityId::capability_instance_adc_qfn56_ch1,
    CapabilityId::capability_instance_adc_qfn56_ch2,
    CapabilityId::capability_instance_adc_qfn56_ch3,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DMA> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PWM> {
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
struct PeripheralCapabilityTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_SPI0_DMA_SPI0_RX_RX,
    CapabilityId::runtime_dma_SPI0_DMA_SPI0_TX_TX,
    CapabilityId::capability_instance_spi0_qfn56_csn,
    CapabilityId::capability_instance_spi0_qfn56_rx,
    CapabilityId::capability_instance_spi0_qfn56_sck,
    CapabilityId::capability_instance_spi0_qfn56_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX,
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX,
    CapabilityId::capability_instance_spi1_qfn56_csn,
    CapabilityId::capability_instance_spi1_qfn56_rx,
    CapabilityId::capability_instance_spi1_qfn56_sck,
    CapabilityId::capability_instance_spi1_qfn56_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TIMER> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX,
    CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX,
    CapabilityId::capability_instance_uart0_qfn56_cts,
    CapabilityId::capability_instance_uart0_qfn56_rts,
    CapabilityId::capability_instance_uart0_qfn56_rx,
    CapabilityId::capability_instance_uart0_qfn56_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX,
    CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX,
    CapabilityId::capability_instance_uart1_qfn56_cts,
    CapabilityId::capability_instance_uart1_qfn56_rts,
    CapabilityId::capability_instance_uart1_qfn56_rx,
    CapabilityId::capability_instance_uart1_qfn56_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::WATCHDOG> {
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
