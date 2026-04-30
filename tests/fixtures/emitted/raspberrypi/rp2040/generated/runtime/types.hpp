#pragma once

#include <cstdint>

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_adc_raspberrypi_rp2040_adc_v1,
  schema_alloy_clock_raspberrypi_generic_clock_v1,
  schema_alloy_clocks_raspberrypi_clocks,
  schema_alloy_dma_raspberrypi_rp2040_dma_v1,
  schema_alloy_i2c_raspberrypi_rp2040_i2c_v1,
  schema_alloy_io_bank0_raspberrypi_io_bank0,
  schema_alloy_pads_bank0_raspberrypi_pads_bank0,
  schema_alloy_pinmux_rp2040_funcsel_v1,
  schema_alloy_pio_raspberrypi_rp2040_pio_v1,
  schema_alloy_pll_sys_raspberrypi_pll_sys,
  schema_alloy_pll_usb_raspberrypi_pll_usb,
  schema_alloy_pwm_raspberrypi_rp2040_pwm_v1,
  schema_alloy_resets_raspberrypi_resets,
  schema_alloy_rtc_raspberrypi_rp2040_rtc_v1,
  schema_alloy_sio_raspberrypi_rp2040_sio_v1,
  schema_alloy_spi_raspberrypi_rp2040_spi_v1,
  schema_alloy_timer_raspberrypi_rp2040_timer_v1,
  schema_alloy_uart_raspberrypi_rp2040_uart_v1,
  schema_alloy_usbctrl_regs_raspberrypi_rp2040_usb_v1,
  schema_alloy_watchdog_raspberrypi_rp2040_watchdog_v1,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_adc,
  class_clocks,
  class_device,
  class_dma,
  class_i2c,
  class_io_bank0,
  class_pads_bank0,
  class_pio,
  class_pll_sys,
  class_pll_usb,
  class_pwm,
  class_resets,
  class_rtc,
  class_sio,
  class_spi,
  class_timer,
  class_uart,
  class_usbctrl_regs,
  class_watchdog,
};

enum class SignalId : std::uint16_t {
  none,
  signal_CH0,
  signal_CH1,
  signal_CH2,
  signal_CSN,
  signal_CTS,
  signal_FIFO,
  signal_RTS,
  signal_RX,
  signal_SCK,
  signal_SCL,
  signal_SDA,
  signal_TX,
  signal_adc_ch0,
  signal_adc_ch1,
  signal_adc_ch2,
  signal_ch0,
  signal_ch1,
  signal_ch2,
  signal_csn,
  signal_cts,
  signal_i2c0_scl,
  signal_i2c0_sda,
  signal_i2c1_scl,
  signal_i2c1_sda,
  signal_rts,
  signal_rx,
  signal_sck,
  signal_scl,
  signal_sda,
  signal_spi0_csn,
  signal_spi0_rx,
  signal_spi0_sck,
  signal_spi0_tx,
  signal_spi1_csn,
  signal_spi1_rx,
  signal_spi1_sck,
  signal_spi1_tx,
  signal_tx,
  signal_uart0_cts,
  signal_uart0_rts,
  signal_uart0_rx,
  signal_uart0_tx,
  signal_uart1_cts,
  signal_uart1_rts,
  signal_uart1_rx,
  signal_uart1_tx,
};

enum class PortId : std::uint16_t {
  none,
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
