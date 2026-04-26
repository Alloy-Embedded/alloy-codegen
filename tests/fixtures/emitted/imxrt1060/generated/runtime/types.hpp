#pragma once

#include <cstdint>

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_adc_nxp_adc,
  schema_alloy_can_nxp_can,
  schema_alloy_ccm_nxp_ccm,
  schema_alloy_ccm_analog_nxp_ccm_analog,
  schema_alloy_clock_nxp_ccm,
  schema_alloy_dcdc_nxp_dcdc,
  schema_alloy_dma_router_nxp_dmamux,
  schema_alloy_dma_nxp_dma,
  schema_alloy_eth_nxp_enet,
  schema_alloy_gpio_nxp_imxrt_gpio_v1,
  schema_alloy_gpt_nxp_gpt,
  schema_alloy_iomuxc_nxp_iomuxc,
  schema_alloy_lpi2c_nxp_lpi2c_v1,
  schema_alloy_pinmux_imxrt_iomuxc_v1,
  schema_alloy_pit_nxp_pit,
  schema_alloy_pwm_nxp_pwm,
  schema_alloy_spi_nxp_lpspi_v1,
  schema_alloy_uart_nxp_lpuart_v1,
  schema_alloy_usb_nxp_usb,
  schema_alloy_watchdog_nxp_rtwdog,
  schema_alloy_watchdog_nxp_wdog,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_adc,
  class_can,
  class_ccm,
  class_ccm_analog,
  class_dcdc,
  class_device,
  class_dma,
  class_dma_router,
  class_eth,
  class_gpio,
  class_gpt,
  class_iomuxc,
  class_lpi2c,
  class_pit,
  class_pwm,
  class_spi,
  class_timer,
  class_uart,
  class_usb,
  class_watchdog,
};

enum class SignalId : std::uint16_t {
  none,
  signal_IO00,
  signal_IO01,
  signal_PCS0,
  signal_RX,
  signal_SCK,
  signal_SCL,
  signal_SDA,
  signal_TX,
  signal_cs,
  signal_gpio1_io00,
  signal_gpio1_io01,
  signal_gpio4_io00,
  signal_gpio4_io01,
  signal_io00,
  signal_io01,
  signal_lpi2c1_scl,
  signal_lpi2c1_sda,
  signal_lpspi1_pcs0,
  signal_lpspi1_sck,
  signal_lpuart1_rx,
  signal_lpuart1_tx,
  signal_pcs0,
  signal_rx,
  signal_sck,
  signal_scl,
  signal_sda,
  signal_tx,
};

enum class PortId : std::uint16_t {
  none,
};

enum class AccessKindId : std::uint16_t {
  none,
  access_kind_read_only,
  access_kind_read_write,
};

enum class StartupKindId : std::uint16_t {
  none,
  startup_kind_copy_source_region,
  startup_kind_copy_target_region,
  startup_kind_initial_stack_pointer,
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
  route_kind_iomuxc_mux,
};

enum class OperationKindId : std::uint16_t {
  none,
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
};

}
}
}
}
