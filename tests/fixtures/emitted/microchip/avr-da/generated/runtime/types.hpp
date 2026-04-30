#pragma once

#include <cstdint>

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_adc_microchip_avr_da_adc_v1,
  schema_alloy_clkctrl_microchip_avr_da_clkctrl_v1,
  schema_alloy_i2c_microchip_avr_da_twi_v1,
  schema_alloy_pinmux_avr_portmux_v1,
  schema_alloy_porta_microchip_avr_da_port_v1,
  schema_alloy_portc_microchip_avr_da_port_v1,
  schema_alloy_portmux_microchip_avr_da_portmux_v1,
  schema_alloy_spi_microchip_avr_da_spi_v1,
  schema_alloy_timer_microchip_avr_da_tca_v1,
  schema_alloy_uart_microchip_avr_da_usart_v1,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_adc,
  class_clkctrl,
  class_device,
  class_i2c,
  class_porta,
  class_portc,
  class_portmux,
  class_spi,
  class_timer,
  class_uart,
};

enum class SignalId : std::uint16_t {
  none,
  signal_CS,
  signal_MISO,
  signal_MOSI,
  signal_RX,
  signal_SCK,
  signal_SCL,
  signal_SDA,
  signal_TX,
  signal_cs,
  signal_miso,
  signal_mosi,
  signal_rx,
  signal_sck,
  signal_scl,
  signal_sda,
  signal_spi0_miso,
  signal_spi0_mosi,
  signal_spi0_sck,
  signal_spi0_ss,
  signal_twi0_scl,
  signal_twi0_sda,
  signal_tx,
  signal_usart0_rxd,
  signal_usart0_txd,
  signal_usart1_rxd,
  signal_usart1_txd,
};

enum class PortId : std::uint16_t {
  none,
  port_A,
  port_C,
};

enum class AccessKindId : std::uint16_t {
  none,
  access_kind_r,
  access_kind_rw,
  access_kind_rwx,
  access_kind_rx,
};

enum class StartupKindId : std::uint16_t {
  none,
  startup_kind_copy_source_region,
  startup_kind_copy_target_region,
  startup_kind_initial_stack_pointer,
  startup_kind_vector_source_region,
  startup_kind_vector_table,
  startup_kind_zero_target_region,
};

enum class VectorKindId : std::uint16_t {
  none,
  vector_kind_external_interrupt,
  vector_kind_reset_handler,
};

enum class RouteKindId : std::uint16_t {
  none,
  route_kind_peripheral_mux,
};

enum class OperationKindId : std::uint16_t {
  none,
  operation_kind_write_selector,
};

enum class OperationSubjectKindId : std::uint16_t {
  none,
  operation_subject_pin,
};

enum class ActiveLevelId : std::uint16_t {
  none,
};

}
}
}
}
