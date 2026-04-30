#pragma once

#include <cstdint>

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_adc_espressif_esp32_sens_v1,
  schema_alloy_aes_espressif_aes,
  schema_alloy_apb_ctrl_espressif_apb_ctrl,
  schema_alloy_bb_espressif_bb,
  schema_alloy_clock_espressif_generic_clock_v1,
  schema_alloy_dport_espressif_esp32_dport_v1,
  schema_alloy_efuse_espressif_efuse,
  schema_alloy_emac_dma_espressif_emac_dma,
  schema_alloy_emac_ext_espressif_emac_ext,
  schema_alloy_emac_mac_espressif_emac_mac,
  schema_alloy_flash_encryption_espressif_flash_encryption,
  schema_alloy_frc_timer_espressif_frc_timer,
  schema_alloy_gpio_espressif_esp32_gpio_v1,
  schema_alloy_gpio_sd_espressif_gpio_sd,
  schema_alloy_hinf_espressif_hinf,
  schema_alloy_i2c_espressif_esp32_i2c_v1,
  schema_alloy_i2c_espressif_i2c,
  schema_alloy_i2s_espressif_i2s,
  schema_alloy_io_mux_espressif_io_mux,
  schema_alloy_ledc_espressif_esp32_ledc_v1,
  schema_alloy_mcpwm_espressif_mcpwm,
  schema_alloy_nrx_espressif_nrx,
  schema_alloy_pcnt_espressif_pcnt,
  schema_alloy_pinmux_espressif_iomatrix_v1,
  schema_alloy_rmt_espressif_esp32_rmt_v1,
  schema_alloy_rng_espressif_rng,
  schema_alloy_rsa_espressif_rsa,
  schema_alloy_rtc_cntl_espressif_rtc_cntl,
  schema_alloy_rtc_i2c_espressif_rtc_i2c,
  schema_alloy_rtc_io_espressif_rtc_io,
  schema_alloy_sdhost_espressif_sdhost,
  schema_alloy_sha_espressif_sha,
  schema_alloy_slc_espressif_slc,
  schema_alloy_slchost_espressif_slchost,
  schema_alloy_spi_espressif_esp32_spi_v1,
  schema_alloy_spi_espressif_spi,
  schema_alloy_timg_espressif_esp32_timg_v1,
  schema_alloy_timg_espressif_timg,
  schema_alloy_twai_espressif_twai,
  schema_alloy_uart_espressif_esp32_uart_v1,
  schema_alloy_uart_espressif_uart,
  schema_alloy_uhci_espressif_uhci,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_adc,
  class_aes,
  class_apb_ctrl,
  class_bb,
  class_device,
  class_dport,
  class_efuse,
  class_emac_dma,
  class_emac_ext,
  class_emac_mac,
  class_flash_encryption,
  class_frc_timer,
  class_gpio,
  class_gpio_sd,
  class_hinf,
  class_i2c,
  class_i2s,
  class_io_mux,
  class_ledc,
  class_mcpwm,
  class_nrx,
  class_pcnt,
  class_rmt,
  class_rng,
  class_rsa,
  class_rtc_cntl,
  class_rtc_i2c,
  class_rtc_io,
  class_sdhost,
  class_sha,
  class_slc,
  class_slchost,
  class_spi,
  class_timg,
  class_twai,
  class_uart,
  class_uhci,
};

enum class SignalId : std::uint16_t {
  none,
  signal_RX,
  signal_TX,
  signal_rx,
  signal_tx,
  signal_uart0_rx,
  signal_uart0_tx,
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
