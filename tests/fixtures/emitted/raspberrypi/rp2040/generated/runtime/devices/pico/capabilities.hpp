#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
enum class CapabilityId : std::uint16_t {
  none,
  capability_adc_rp2040_adc_v1_ch0,
  capability_adc_rp2040_adc_v1_ch1,
  capability_adc_rp2040_adc_v1_ch2,
  runtime_support_adc,
  runtime_dma_ADC_DMA_ADC_FIFO,
  capability_instance_adc_pico_ch0,
  capability_instance_adc_pico_ch1,
  capability_instance_adc_pico_ch2,
  device_core_count,
  device_multicore_topology,
  runtime_support_dma,
  capability_i2c_rp2040_i2c_v1_scl,
  capability_i2c_rp2040_i2c_v1_sda,
  runtime_support_i2c,
  capability_instance_i2c0_pico_scl,
  capability_instance_i2c0_pico_sda,
  capability_instance_i2c1_pico_scl,
  capability_instance_i2c1_pico_sda,
  runtime_support_pwm,
  runtime_support_rtc,
  capability_spi_rp2040_spi_v1_csn,
  capability_spi_rp2040_spi_v1_rx,
  capability_spi_rp2040_spi_v1_sck,
  capability_spi_rp2040_spi_v1_tx,
  runtime_support_spi,
  runtime_dma_SPI0_DMA_SPI0_RX_RX,
  runtime_dma_SPI0_DMA_SPI0_TX_TX,
  capability_instance_spi0_pico_csn,
  capability_instance_spi0_pico_rx,
  capability_instance_spi0_pico_sck,
  capability_instance_spi0_pico_tx,
  runtime_dma_SPI1_DMA_SPI1_RX_RX,
  runtime_dma_SPI1_DMA_SPI1_TX_TX,
  capability_instance_spi1_pico_csn,
  capability_instance_spi1_pico_rx,
  capability_instance_spi1_pico_sck,
  capability_instance_spi1_pico_tx,
  runtime_support_timer,
  capability_uart_rp2040_uart_v1_cts,
  capability_uart_rp2040_uart_v1_rts,
  capability_uart_rp2040_uart_v1_rx,
  capability_uart_rp2040_uart_v1_tx,
  runtime_support_uart,
  runtime_dma_UART0_DMA_UART0_RX_RX,
  runtime_dma_UART0_DMA_UART0_TX_TX,
  capability_instance_uart0_pico_cts,
  capability_instance_uart0_pico_rts,
  capability_instance_uart0_pico_rx,
  capability_instance_uart0_pico_tx,
  runtime_dma_UART1_DMA_UART1_RX_RX,
  runtime_dma_UART1_DMA_UART1_TX_TX,
  capability_instance_uart1_pico_cts,
  capability_instance_uart1_pico_rts,
  capability_instance_uart1_pico_rx,
  capability_instance_uart1_pico_tx,
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
  csn,
  cts,
  rts,
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
inline constexpr std::array<CapabilityDescriptor, 56> kCapabilities = {{
  {CapabilityId::capability_adc_rp2040_adc_v1_ch0, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch0, PeripheralId::none},
  {CapabilityId::capability_adc_rp2040_adc_v1_ch1, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch1, PeripheralId::none},
  {CapabilityId::capability_adc_rp2040_adc_v1_ch2, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch2, PeripheralId::none},
  {CapabilityId::runtime_support_adc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO, CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::FIFO, PeripheralId::ADC},
  {CapabilityId::capability_instance_adc_pico_ch0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch0, PeripheralId::ADC},
  {CapabilityId::capability_instance_adc_pico_ch1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch1, PeripheralId::ADC},
  {CapabilityId::capability_instance_adc_pico_ch2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch2, PeripheralId::ADC},
  {CapabilityId::device_core_count, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityId::device_multicore_topology, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityId::runtime_support_dma, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_i2c_rp2040_i2c_v1_scl, CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::scl, PeripheralId::none},
  {CapabilityId::capability_i2c_rp2040_i2c_v1_sda, CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::sda, PeripheralId::none},
  {CapabilityId::runtime_support_i2c, CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_i2c0_pico_scl, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::I2C0},
  {CapabilityId::capability_instance_i2c0_pico_sda, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::I2C0},
  {CapabilityId::capability_instance_i2c1_pico_scl, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::I2C1},
  {CapabilityId::capability_instance_i2c1_pico_sda, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::I2C1},
  {CapabilityId::runtime_support_pwm, CapabilityScopeId::runtime_contract, PeripheralClassId::class_pwm, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_rtc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_rtc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_csn, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::csn, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_sck, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityId::capability_spi_rp2040_spi_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_SPI0_DMA_SPI0_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI0},
  {CapabilityId::runtime_dma_SPI0_DMA_SPI0_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_pico_csn, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::csn, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_pico_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_pico_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_pico_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::SPI0},
  {CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI1},
  {CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_pico_csn, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::csn, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_pico_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_pico_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI1},
  {CapabilityId::capability_instance_spi1_pico_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::SPI1},
  {CapabilityId::runtime_support_timer, CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_cts, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::cts, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_rts, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rts, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_uart_rp2040_uart_v1_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART0},
  {CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_pico_cts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_pico_rts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_pico_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_pico_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART0},
  {CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART1},
  {CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_pico_cts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_pico_rts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_pico_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_pico_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART1},
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

inline constexpr std::array<CapabilityHardwareLut, 56> kCapabilityHardwareLut = {{
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ch2, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::FIFO, PeripheralId::ADC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch0, PeripheralId::ADC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch1, PeripheralId::ADC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ch2, PeripheralId::ADC},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::scl, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::sda, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::I2C0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::I2C0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::I2C1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::I2C1},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_pwm, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_rtc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::csn, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::csn, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::SPI0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::csn, PeripheralId::SPI1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::SPI1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::SPI1},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::cts, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rts, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::UART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::UART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::UART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::UART1},
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

template<> struct CapabilityTraits<CapabilityId::capability_adc_rp2040_adc_v1_ch0> : CapabilityTraitsBase<0> {};
template<> struct CapabilityTraits<CapabilityId::capability_adc_rp2040_adc_v1_ch1> : CapabilityTraitsBase<1> {};
template<> struct CapabilityTraits<CapabilityId::capability_adc_rp2040_adc_v1_ch2> : CapabilityTraitsBase<2> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_adc> : CapabilityTraitsBase<3> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO> : CapabilityTraitsBase<4> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_adc_pico_ch0> : CapabilityTraitsBase<5> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_adc_pico_ch1> : CapabilityTraitsBase<6> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_adc_pico_ch2> : CapabilityTraitsBase<7> {};
template<> struct CapabilityTraits<CapabilityId::device_core_count> : CapabilityTraitsBase<8> {};
template<> struct CapabilityTraits<CapabilityId::device_multicore_topology> : CapabilityTraitsBase<9> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dma> : CapabilityTraitsBase<10> {};
template<> struct CapabilityTraits<CapabilityId::capability_i2c_rp2040_i2c_v1_scl> : CapabilityTraitsBase<11> {};
template<> struct CapabilityTraits<CapabilityId::capability_i2c_rp2040_i2c_v1_sda> : CapabilityTraitsBase<12> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_i2c> : CapabilityTraitsBase<13> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_i2c0_pico_scl> : CapabilityTraitsBase<14> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_i2c0_pico_sda> : CapabilityTraitsBase<15> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_i2c1_pico_scl> : CapabilityTraitsBase<16> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_i2c1_pico_sda> : CapabilityTraitsBase<17> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_pwm> : CapabilityTraitsBase<18> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_rtc> : CapabilityTraitsBase<19> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_csn> : CapabilityTraitsBase<20> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_rx> : CapabilityTraitsBase<21> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_sck> : CapabilityTraitsBase<22> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_rp2040_spi_v1_tx> : CapabilityTraitsBase<23> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_spi> : CapabilityTraitsBase<24> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI0_DMA_SPI0_RX_RX> : CapabilityTraitsBase<25> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI0_DMA_SPI0_TX_TX> : CapabilityTraitsBase<26> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_pico_csn> : CapabilityTraitsBase<27> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_pico_rx> : CapabilityTraitsBase<28> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_pico_sck> : CapabilityTraitsBase<29> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_pico_tx> : CapabilityTraitsBase<30> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX> : CapabilityTraitsBase<31> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX> : CapabilityTraitsBase<32> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi1_pico_csn> : CapabilityTraitsBase<33> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi1_pico_rx> : CapabilityTraitsBase<34> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi1_pico_sck> : CapabilityTraitsBase<35> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi1_pico_tx> : CapabilityTraitsBase<36> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_timer> : CapabilityTraitsBase<37> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_cts> : CapabilityTraitsBase<38> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_rts> : CapabilityTraitsBase<39> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_rx> : CapabilityTraitsBase<40> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_rp2040_uart_v1_tx> : CapabilityTraitsBase<41> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_uart> : CapabilityTraitsBase<42> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART0_DMA_UART0_RX_RX> : CapabilityTraitsBase<43> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART0_DMA_UART0_TX_TX> : CapabilityTraitsBase<44> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_pico_cts> : CapabilityTraitsBase<45> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_pico_rts> : CapabilityTraitsBase<46> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_pico_rx> : CapabilityTraitsBase<47> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_pico_tx> : CapabilityTraitsBase<48> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX> : CapabilityTraitsBase<49> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX> : CapabilityTraitsBase<50> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_pico_cts> : CapabilityTraitsBase<51> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_pico_rts> : CapabilityTraitsBase<52> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_pico_rx> : CapabilityTraitsBase<53> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_pico_tx> : CapabilityTraitsBase<54> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_watchdog> : CapabilityTraitsBase<55> {};

template<PeripheralClassId Id>
struct PeripheralClassCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_adc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 8> kCapabilityIds = {{
    CapabilityId::capability_adc_rp2040_adc_v1_ch0,
    CapabilityId::capability_adc_rp2040_adc_v1_ch1,
    CapabilityId::capability_adc_rp2040_adc_v1_ch2,
    CapabilityId::runtime_support_adc,
    CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO,
    CapabilityId::capability_instance_adc_pico_ch0,
    CapabilityId::capability_instance_adc_pico_ch1,
    CapabilityId::capability_instance_adc_pico_ch2,
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
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_i2c> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 7> kCapabilityIds = {{
    CapabilityId::capability_i2c_rp2040_i2c_v1_scl,
    CapabilityId::capability_i2c_rp2040_i2c_v1_sda,
    CapabilityId::runtime_support_i2c,
    CapabilityId::capability_instance_i2c0_pico_scl,
    CapabilityId::capability_instance_i2c0_pico_sda,
    CapabilityId::capability_instance_i2c1_pico_scl,
    CapabilityId::capability_instance_i2c1_pico_sda,
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
    CapabilityId::capability_instance_spi0_pico_csn,
    CapabilityId::capability_instance_spi0_pico_rx,
    CapabilityId::capability_instance_spi0_pico_sck,
    CapabilityId::capability_instance_spi0_pico_tx,
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX,
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX,
    CapabilityId::capability_instance_spi1_pico_csn,
    CapabilityId::capability_instance_spi1_pico_rx,
    CapabilityId::capability_instance_spi1_pico_sck,
    CapabilityId::capability_instance_spi1_pico_tx,
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
    CapabilityId::capability_instance_uart0_pico_cts,
    CapabilityId::capability_instance_uart0_pico_rts,
    CapabilityId::capability_instance_uart0_pico_rx,
    CapabilityId::capability_instance_uart0_pico_tx,
    CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX,
    CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX,
    CapabilityId::capability_instance_uart1_pico_cts,
    CapabilityId::capability_instance_uart1_pico_rts,
    CapabilityId::capability_instance_uart1_pico_rx,
    CapabilityId::capability_instance_uart1_pico_tx,
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
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_ADC_DMA_ADC_FIFO,
    CapabilityId::capability_instance_adc_pico_ch0,
    CapabilityId::capability_instance_adc_pico_ch1,
    CapabilityId::capability_instance_adc_pico_ch2,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DMA> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::I2C0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_i2c0_pico_scl,
    CapabilityId::capability_instance_i2c0_pico_sda,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_i2c1_pico_scl,
    CapabilityId::capability_instance_i2c1_pico_sda,
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
    CapabilityId::capability_instance_spi0_pico_csn,
    CapabilityId::capability_instance_spi0_pico_rx,
    CapabilityId::capability_instance_spi0_pico_sck,
    CapabilityId::capability_instance_spi0_pico_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_RX_RX,
    CapabilityId::runtime_dma_SPI1_DMA_SPI1_TX_TX,
    CapabilityId::capability_instance_spi1_pico_csn,
    CapabilityId::capability_instance_spi1_pico_rx,
    CapabilityId::capability_instance_spi1_pico_sck,
    CapabilityId::capability_instance_spi1_pico_tx,
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
    CapabilityId::capability_instance_uart0_pico_cts,
    CapabilityId::capability_instance_uart0_pico_rts,
    CapabilityId::capability_instance_uart0_pico_rx,
    CapabilityId::capability_instance_uart0_pico_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART1_DMA_UART1_RX_RX,
    CapabilityId::runtime_dma_UART1_DMA_UART1_TX_TX,
    CapabilityId::capability_instance_uart1_pico_cts,
    CapabilityId::capability_instance_uart1_pico_rts,
    CapabilityId::capability_instance_uart1_pico_rx,
    CapabilityId::capability_instance_uart1_pico_tx,
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
