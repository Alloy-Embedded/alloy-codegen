#pragma once

#include <cstdint>

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_adc_espressif_esp32s3_saradc_v1,
  schema_alloy_adc_espressif_sens,
  schema_alloy_aes_espressif_aes,
  schema_alloy_apb_ctrl_espressif_apb_ctrl,
  schema_alloy_assist_debug_espressif_assist_debug,
  schema_alloy_bb_espressif_bb,
  schema_alloy_clock_espressif_generic_clock_v1,
  schema_alloy_dma_espressif_esp32s3_gdma_v1,
  schema_alloy_ds_espressif_ds,
  schema_alloy_efuse_espressif_efuse,
  schema_alloy_extmem_espressif_extmem,
  schema_alloy_gpio_espressif_esp32s3_gpio_v1,
  schema_alloy_gpio_sd_espressif_gpio_sd,
  schema_alloy_hmac_espressif_hmac,
  schema_alloy_i2c_espressif_esp32s3_i2c_v1,
  schema_alloy_i2s_espressif_i2s,
  schema_alloy_interrupt_core0_espressif_esp32s3_interrupt_matrix_v1,
  schema_alloy_interrupt_core1_espressif_esp32s3_interrupt_matrix_v1,
  schema_alloy_io_mux_espressif_io_mux,
  schema_alloy_lcd_cam_espressif_lcd_cam,
  schema_alloy_ledc_espressif_ledc,
  schema_alloy_mcpwm_espressif_mcpwm,
  schema_alloy_pcnt_espressif_pcnt,
  schema_alloy_peri_backup_espressif_peri_backup,
  schema_alloy_pinmux_espressif_iomatrix_v1,
  schema_alloy_rmt_espressif_rmt,
  schema_alloy_rng_espressif_rng,
  schema_alloy_rsa_espressif_rsa,
  schema_alloy_rtc_cntl_espressif_rtc_cntl,
  schema_alloy_rtc_i2c_espressif_rtc_i2c,
  schema_alloy_rtc_io_espressif_rtc_io,
  schema_alloy_sdhost_espressif_sdhost,
  schema_alloy_sensitive_espressif_sensitive,
  schema_alloy_sha_espressif_sha,
  schema_alloy_spi_espressif_esp32s3_spi_v1,
  schema_alloy_spi_espressif_spi,
  schema_alloy_system_espressif_esp32s3_system_v1,
  schema_alloy_systimer_espressif_systimer,
  schema_alloy_timg_espressif_timg,
  schema_alloy_twai_espressif_twai,
  schema_alloy_uart_espressif_esp32s3_uart_v1,
  schema_alloy_uhci_espressif_uhci,
  schema_alloy_usb_espressif_usb,
  schema_alloy_usb_device_espressif_usb_device,
  schema_alloy_usb_wrap_espressif_usb_wrap,
  schema_alloy_wcl_espressif_wcl,
  schema_alloy_xts_aes_espressif_xts_aes,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_adc,
  class_aes,
  class_apb_ctrl,
  class_assist_debug,
  class_bb,
  class_device,
  class_dma,
  class_ds,
  class_efuse,
  class_extmem,
  class_gpio,
  class_gpio_sd,
  class_hmac,
  class_i2c,
  class_i2s,
  class_interrupt_core0,
  class_interrupt_core1,
  class_io_mux,
  class_lcd_cam,
  class_ledc,
  class_mcpwm,
  class_pcnt,
  class_peri_backup,
  class_rmt,
  class_rng,
  class_rsa,
  class_rtc_cntl,
  class_rtc_i2c,
  class_rtc_io,
  class_sdhost,
  class_sensitive,
  class_sha,
  class_spi,
  class_system,
  class_systimer,
  class_timg,
  class_twai,
  class_uart,
  class_uhci,
  class_usb,
  class_usb_device,
  class_usb_wrap,
  class_wcl,
  class_xts_aes,
};

enum class SignalId : std::uint16_t {
  none,
  signal_CS,
  signal_DATA,
  signal_MISO,
  signal_MOSI,
  signal_RX,
  signal_SCK,
  signal_SCL,
  signal_SDA,
  signal_TX,
  signal_cs,
  signal_i2c0_scl,
  signal_i2c0_sda,
  signal_miso,
  signal_mosi,
  signal_rx,
  signal_sck,
  signal_scl,
  signal_sda,
  signal_spi2_cs,
  signal_spi2_miso,
  signal_spi2_mosi,
  signal_spi2_sck,
  signal_tx,
  signal_uart0_rx,
  signal_uart0_tx,
  signal_uart2_rx,
  signal_uart2_tx,
};

enum class PortId : std::uint16_t {
  none,
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
  vector_kind_reset_handler,
};

enum class RouteKindId : std::uint16_t {
  none,
  route_kind_mux,
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
