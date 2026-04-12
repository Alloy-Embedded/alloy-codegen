#pragma once

#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_clock_st_rcc_g0_v1_0,
  schema_alloy_dma_router_st_dmamux_v1_0,
  schema_alloy_dma_st_bdma_v1_0,
  schema_alloy_gpio_st_stm32g07x_gpio_v1_0,
  schema_alloy_pinmux_stm32_af_v1,
  schema_alloy_rcc_st_rcc_g0_v1_0,
  schema_alloy_uart_st_usart_v3_1,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_dma,
  class_dma_router,
  class_gpio,
  class_rcc,
  class_uart,
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
  signal_TX,
  signal_gpio,
  signal_rx,
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
  access_kind_read_write,
  access_kind_rwx,
  access_kind_rx,
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
