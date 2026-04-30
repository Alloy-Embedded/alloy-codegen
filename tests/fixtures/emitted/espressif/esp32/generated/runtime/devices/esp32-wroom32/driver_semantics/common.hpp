#pragma once

#include <cstdint>
#include "../peripheral_instances.hpp"
#include "../registers.hpp"
#include "../register_fields.hpp"
#include "../dma_bindings.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
namespace driver_semantics {
struct RuntimeRegisterRef {
  RegisterId register_id = RegisterId::none;
  std::uintptr_t base_address = 0u;
  std::uint32_t offset_bytes = 0u;
  bool valid = false;
};

struct RuntimeFieldRef {
  FieldId field_id = FieldId::none;
  RuntimeRegisterRef reg{};
  std::uint16_t bit_offset = 0u;
  std::uint16_t bit_width = 0u;
  bool valid = false;
};

struct RuntimeIndexedFieldRef {
  std::uintptr_t base_address = 0u;
  std::uint32_t base_offset_bytes = 0u;
  std::uint32_t stride_bytes = 0u;
  std::uint16_t bit_offset = 0u;
  std::uint16_t bit_width = 0u;
  std::uint16_t bit_stride_bits = 0u;
  bool valid = false;
};

inline constexpr RuntimeRegisterRef kInvalidRegisterRef{};
inline constexpr RuntimeFieldRef kInvalidFieldRef{};
inline constexpr RuntimeIndexedFieldRef kInvalidIndexedFieldRef{};

// ADC trait support types (added by add-full-adc-coverage).
// Apps consuming the runtime use these to generate high-level helpers
// like readTemperature() / readVdd() with full compile-time validation.
enum class InternalAdcChannelKind : std::uint8_t {
  none,
  temperature_sensor,
  vrefint,
  vbat,
  opamp_output,
  dac_output,
};

enum class AdcCalibrationKind : std::uint8_t {
  none,
  vrefint_cal,
  ts_cal_low,
  ts_cal_high,
  sigrow_sref,
  sigrow_tempsense_low,
  sigrow_tempsense_high,
  efuse_init_code,
};

enum class AdcExternalTriggerSource : std::uint8_t {
  none,
  software,
  tim1_cc1,
  tim1_cc2,
  tim1_cc3,
  tim1_cc4,
  tim1_trgo,
  tim1_trgo2,
  tim2_trgo,
  tim3_trgo,
  tim4_trgo,
  tim6_trgo,
  tim7_trgo,
  tim15_trgo,
  tim16_trgo,
  exti11,
  exti15,
  gpt1_compare1,
  gpt2_compare1,
  xbar_in0,
  xbar_in1,
  pwm0_compare,
  pwm1_compare,
};

enum class AdcDmaMode : std::uint8_t {
  none,
  one_shot,
  circular,
};

struct InternalAdcChannel {
  InternalAdcChannelKind kind = InternalAdcChannelKind::none;
  std::uint32_t channel_index = 0u;
  bool valid = false;
};

struct CalibrationDataPoint {
  AdcCalibrationKind kind = AdcCalibrationKind::none;
  RuntimeRegisterRef location{};
  std::int32_t semantic_constant = 0;
  bool valid = false;
};

struct CalibrationContext {
  std::int16_t cal_temp_low_celsius = 0;
  std::int16_t cal_temp_high_celsius = 0;
  std::uint16_t cal_voltage_mv = 0u;
  std::uint16_t vrefint_nominal_mv = 0u;
  bool valid = false;
};

struct AdcResolutionOption {
  std::uint8_t bits = 0u;
  std::uint8_t field_value = 0u;
  bool valid = false;
};

struct AdcSampleTimeOption {
  // ``cycles_q8`` carries the cycle count in Q8.8 fixed-point so
  // fractional cycles (1.5, 7.5, ...) survive without floats.  Apps
  // do ``cycles_q8 / 256.0f`` to recover a float, or compare integers.
  // 32-bit holds up to 16.7M cycles which covers every documented
  // ADC sample time across admitted vendors (STM32F4 ADC sample 480
  // cycles → 122880 in Q8.8 fixed-point — exceeds uint16_t).
  std::uint32_t cycles_q8 = 0u;
  std::uint8_t field_value = 0u;
  bool valid = false;
};

struct AdcOversamplingOption {
  std::uint16_t ratio = 0u;
  std::uint8_t field_value = 0u;
  bool valid = false;
};

struct AdcExternalTrigger {
  AdcExternalTriggerSource source = AdcExternalTriggerSource::none;
  std::uint8_t extsel_value = 0u;
  std::uint8_t exten_polarity_default = 0u;
  bool valid = false;
};

struct AdcDmaBinding {
  // Source ADC peripheral name + DMA controller / route descriptor.
  // ``data_register`` mirrors the ADC trait's kDataRegister so DMA
  // configuration code can pull the source address without a second
  // lookup.  ``binding_id`` cross-references the existing
  // ``DmaSemanticTraits`` table when the consumer wants the full
  // DMA route/channel descriptor.
  PeripheralId controller_peripheral = PeripheralId::none;
  DmaControllerId controller_id = DmaControllerId::none;
  DmaBindingId binding_id = DmaBindingId::none;
  std::uint8_t request_value = 0u;
  RuntimeRegisterRef data_register{};
  std::uint8_t transfer_width_bits = 0u;
  bool valid = false;
};

enum class DmaBindingDirection : std::uint8_t {
  none,
  Tx,
  Rx,
};

struct DmaBindingRef {
  // Generic peripheral->DMA binding cross-reference (
  // add-peripheral-dma-cross-references).  ``binding_id``
  // and ``controller_id`` cross-reference the per-device
  // ``DmaSemanticTraits`` / ``BindingTraits`` enums emitted
  // in ``dma_bindings.hpp`` so consumer code can resolve the
  // full route descriptor without a textual scan.
  DmaControllerId controller_id = DmaControllerId::none;
  DmaBindingId binding_id = DmaBindingId::none;
  std::uint16_t request_value = 0u;
  DmaBindingDirection direction = DmaBindingDirection::none;
  std::uint8_t transfer_width_bits = 0u;
  bool valid = false;
};

struct AdcDmaModeOption {
  AdcDmaMode mode = AdcDmaMode::none;
  std::uint8_t field_value = 0u;
  bool valid = false;
};

// Kernel-clock source classifier (added by add-kernel-clock-traits).
// Maps RCC mux parent-options onto a small enum so HAL drivers can
// resolve the actual feeding clock (PCLK1, SYSCLK, HSI16, ...) from
// system_clock_profiles at compile time.
enum class KernelClockSource : std::uint8_t {
  none,
  pclk,
  pclk1,
  pclk2,
  hclk,
  sysclk,
  hsi,
  hsi16,
  hse,
  lsi,
  lse,
  xtal,
  apb,
  peri_clk,
  clk_per,
  lpuart_clk_root,
  rc_fast,
  ref_tick,
};

struct KernelClockSourceOption {
  KernelClockSource source = KernelClockSource::none;
  std::uint8_t field_value = 0u;
  bool valid = false;
};

// I2C trait support type (added by add-i2c-tier-2-3-4-data).
// Precomputed TIMINGR / CWGR value for one (peripheral, source
// clock, target speed) triple — lets the alloy HAL pick the right
// register value at compile time without a runtime calculator.
struct I2cTimingPreset {
  std::uint32_t speed_hz = 0u;
  std::uint32_t source_clock_hz = 0u;
  std::uint32_t timingr_value = 0u;
  bool valid = false;
};
}
}
}
}
}
}
}
