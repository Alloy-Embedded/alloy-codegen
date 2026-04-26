#pragma once

#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_adc_st_adc,
  schema_alloy_clock_st_rcc_g0_v1_0,
  schema_alloy_dac_st_dac,
  schema_alloy_dma_router_st_dmamux_v1_0,
  schema_alloy_dma_st_bdma_v1_0,
  schema_alloy_flash_st_flash,
  schema_alloy_gpio_st_stm32g07x_gpio_v1_0,
  schema_alloy_pinmux_stm32_af_v1,
  schema_alloy_rcc_st_rcc_g0_v1_0,
  schema_alloy_rtc_st_rtc,
  schema_alloy_spi_st_spi,
  schema_alloy_timer_st_tim,
  schema_alloy_uart_st_usart_v3_1,
  schema_alloy_watchdog_st_iwdg,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_adc,
  class_dac,
  class_device,
  class_dma,
  class_dma_router,
  class_flash,
  class_gpio,
  class_rcc,
  class_rtc,
  class_spi,
  class_timer,
  class_uart,
  class_watchdog,
};

enum class SignalId : std::uint16_t {
  none,
  signal_IN0,
  signal_IN1,
  signal_IN2,
  signal_IN3,
  signal_IN6,
  signal_IN7,
  signal_RX,
  signal_SCK,
  signal_TX,
  signal_gpio,
  signal_rx,
  signal_sck,
  signal_spi1_sck,
  signal_tx,
  signal_usart1_rx,
  signal_usart1_tx,
};

enum class PortId : std::uint16_t {
  none,
  port_A,
  port_B,
};

enum class AccessKindId : std::uint16_t {
  none,
  access_kind_read_only,
  access_kind_read_write,
  access_kind_rwx,
  access_kind_rx,
  access_kind_write_only,
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
  route_kind_alternate_function,
};

enum class OperationKindId : std::uint16_t {
  none,
  operation_kind_clear_bit,
  operation_kind_set_bit,
  operation_kind_write_selector,
};

enum class OperationSubjectKindId : std::uint16_t {
  none,
  operation_subject_peripheral,
  operation_subject_pin,
};

enum class ActiveLevelId : std::uint16_t {
  none,
  active_level_high,
};

}
}
}
}
