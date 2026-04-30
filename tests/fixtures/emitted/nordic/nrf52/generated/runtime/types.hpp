#pragma once

#include <cstdint>

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_gpio_nordic_nrf_gpio_v1,
  schema_alloy_i2c_nordic_nrf_twi_v1,
  schema_alloy_pinmux_nordic_generic_v1,
  schema_alloy_rtc_nordic_nrf_rtc_v1,
  schema_alloy_spi_nordic_nrf_spi_v1,
  schema_alloy_timer_nordic_nrf_timer_v1,
  schema_alloy_uart_nordic_nrf_uart_v1,
  schema_alloy_watchdog_nordic_nrf_wdt_v1,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_device,
  class_gpio,
  class_i2c,
  class_rtc,
  class_spi,
  class_timer,
  class_uart,
  class_watchdog,
};

enum class SignalId : std::uint16_t {
  none,
  signal_MISO,
  signal_MOSI,
  signal_RX,
  signal_SCK,
  signal_SCL,
  signal_SDA,
  signal_TX,
  signal_i2c0_scl,
  signal_i2c0_sda,
  signal_miso,
  signal_mosi,
  signal_rx,
  signal_sck,
  signal_scl,
  signal_sda,
  signal_spi0_miso,
  signal_spi0_mosi,
  signal_spi0_sck,
  signal_tx,
  signal_uart0_rx,
  signal_uart0_tx,
};

enum class PortId : std::uint16_t {
  none,
  port_0,
};

enum class AccessKindId : std::uint16_t {
  none,
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
  vector_kind_initial_stack_pointer,
  vector_kind_reserved,
  vector_kind_reset_handler,
  vector_kind_system_exception,
};

enum class RouteKindId : std::uint16_t {
  none,
  route_kind_mux,
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
