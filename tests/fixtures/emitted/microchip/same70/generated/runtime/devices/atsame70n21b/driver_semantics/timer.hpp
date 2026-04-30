#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "common.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
namespace driver_semantics {
template<PeripheralId Id>
struct TimerSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kCounterBits = 0u;
  static constexpr std::uint32_t kChannelCount = 0u;
  static constexpr bool kHasCompare = false;
  static constexpr bool kHasCapture = false;
  static constexpr bool kHasEncoder = false;
  static constexpr bool kHasPwm = false;
  static constexpr bool kHasOnePulse = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasBreakInput = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockSourceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr std::uint32_t kUpdateIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kCaptureIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kBreakIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kTriggerIrqNumber = 0xFFFFFFFFu;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
  static constexpr std::uint32_t kMaxPrescaler = 0u;
  static constexpr std::uint32_t kMaxAutoReload = 0u;
  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};
  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};
  static constexpr bool kSupportsDmaBurst = false;
  static constexpr bool kSupportsRepetitionCounter = false;
  static constexpr bool kSupportsXorInput = false;
};

struct TimerHardwareLut {
  BackendSchemaId schema_id;
  std::uint32_t counter_bits;
  std::uint32_t channel_count;
  bool has_compare;
  bool has_capture;
  bool has_encoder;
  bool has_pwm;
  bool has_one_pulse;
  bool has_center_aligned;
  bool has_complementary_outputs;
  bool has_deadtime;
  bool has_break_input;
  RuntimeRegisterRef control_register;
  RuntimeRegisterRef status_register;
  RuntimeRegisterRef event_register;
  RuntimeRegisterRef counter_register;
  RuntimeRegisterRef prescaler_register;
  RuntimeRegisterRef period_register;
  RuntimeFieldRef enable_field;
  RuntimeFieldRef disable_field;
  RuntimeFieldRef module_disable_field;
  RuntimeFieldRef software_reset_field;
  RuntimeFieldRef start_field;
  RuntimeFieldRef stop_field;
  RuntimeFieldRef update_interrupt_enable_field;
  RuntimeFieldRef update_flag_field;
  RuntimeFieldRef update_generation_field;
  RuntimeFieldRef prescaler_field;
  RuntimeFieldRef period_field;
  RuntimeFieldRef one_pulse_field;
  RuntimeFieldRef center_aligned_field;
  RuntimeFieldRef auto_reload_preload_field;
  RuntimeFieldRef clock_source_field;
  RuntimeFieldRef encoder_mode_field;
  RuntimeFieldRef encoder_enable_field;
  RuntimeFieldRef encoder_position_enable_field;
  RuntimeFieldRef encoder_speed_enable_field;
  RuntimeFieldRef encoder_phase_edge_field;
  RuntimeFieldRef direction_field;
  std::uint32_t update_irq_number;
  std::uint32_t capture_irq_number;
  std::uint32_t break_irq_number;
  std::uint32_t trigger_irq_number;
  std::uint32_t max_prescaler;
  std::uint32_t max_auto_reload;
  bool supports_dma_burst;
  bool supports_repetition_counter;
  bool supports_xor_input;
};

inline constexpr std::array<TimerHardwareLut, 4> kTimerHardwareLut = {{
  {BackendSchemaId::schema_alloy_timer_microchip_tc_zl, 32u, 3u, true, true, true, true, false, false, false, false, false, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 16u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 28u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, 1u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, 2u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, 1u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, 2u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 28u, true}, 0u, 32u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 4u, true}, 0u, 3u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::field_tc0_bmr_qden, RuntimeRegisterRef{RegisterId::register_tc0_bmr, 0x4000C000u, 196u, true}, 8u, 1u, true}, RuntimeFieldRef{FieldId::field_tc0_bmr_posen, RuntimeRegisterRef{RegisterId::register_tc0_bmr, 0x4000C000u, 196u, true}, 9u, 1u, true}, RuntimeFieldRef{FieldId::field_tc0_bmr_speeden, RuntimeRegisterRef{RegisterId::register_tc0_bmr, 0x4000C000u, 196u, true}, 10u, 1u, true}, RuntimeFieldRef{FieldId::field_tc0_bmr_edgpha, RuntimeRegisterRef{RegisterId::register_tc0_bmr, 0x4000C000u, 196u, true}, 12u, 1u, true}, RuntimeFieldRef{FieldId::field_tc0_qisr_dir, RuntimeRegisterRef{RegisterId::register_tc0_qisr, 0x4000C000u, 212u, true}, 8u, 1u, true}, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0u, false, false, false},
  {BackendSchemaId::schema_alloy_timer_microchip_tc_zl, 32u, 3u, true, true, true, true, false, false, false, false, false, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 16u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 28u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, 1u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, 2u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, 1u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, 2u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 28u, true}, 0u, 32u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 4u, true}, 0u, 3u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::field_tc1_bmr_qden, RuntimeRegisterRef{RegisterId::register_tc1_bmr, 0x40010000u, 196u, true}, 8u, 1u, true}, RuntimeFieldRef{FieldId::field_tc1_bmr_posen, RuntimeRegisterRef{RegisterId::register_tc1_bmr, 0x40010000u, 196u, true}, 9u, 1u, true}, RuntimeFieldRef{FieldId::field_tc1_bmr_speeden, RuntimeRegisterRef{RegisterId::register_tc1_bmr, 0x40010000u, 196u, true}, 10u, 1u, true}, RuntimeFieldRef{FieldId::field_tc1_bmr_edgpha, RuntimeRegisterRef{RegisterId::register_tc1_bmr, 0x40010000u, 196u, true}, 12u, 1u, true}, RuntimeFieldRef{FieldId::field_tc1_qisr_dir, RuntimeRegisterRef{RegisterId::register_tc1_qisr, 0x40010000u, 212u, true}, 8u, 1u, true}, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0u, false, false, false},
  {BackendSchemaId::schema_alloy_timer_microchip_tc_zl, 32u, 3u, true, true, true, true, false, false, false, false, false, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 16u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 28u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, 1u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, 2u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, 1u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, 2u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 28u, true}, 0u, 32u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 4u, true}, 0u, 3u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::field_tc2_bmr_qden, RuntimeRegisterRef{RegisterId::register_tc2_bmr, 0x40014000u, 196u, true}, 8u, 1u, true}, RuntimeFieldRef{FieldId::field_tc2_bmr_posen, RuntimeRegisterRef{RegisterId::register_tc2_bmr, 0x40014000u, 196u, true}, 9u, 1u, true}, RuntimeFieldRef{FieldId::field_tc2_bmr_speeden, RuntimeRegisterRef{RegisterId::register_tc2_bmr, 0x40014000u, 196u, true}, 10u, 1u, true}, RuntimeFieldRef{FieldId::field_tc2_bmr_edgpha, RuntimeRegisterRef{RegisterId::register_tc2_bmr, 0x40014000u, 196u, true}, 12u, 1u, true}, RuntimeFieldRef{FieldId::field_tc2_qisr_dir, RuntimeRegisterRef{RegisterId::register_tc2_qisr, 0x40014000u, 212u, true}, 8u, 1u, true}, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0u, false, false, false},
  {BackendSchemaId::schema_alloy_timer_microchip_tc_zl, 32u, 3u, true, true, true, true, false, false, false, false, false, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 16u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 28u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, 1u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, 2u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, 1u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, 2u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 28u, true}, 0u, 32u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 4u, true}, 0u, 3u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::field_tc3_bmr_qden, RuntimeRegisterRef{RegisterId::register_tc3_bmr, 0x40054000u, 196u, true}, 8u, 1u, true}, RuntimeFieldRef{FieldId::field_tc3_bmr_posen, RuntimeRegisterRef{RegisterId::register_tc3_bmr, 0x40054000u, 196u, true}, 9u, 1u, true}, RuntimeFieldRef{FieldId::field_tc3_bmr_speeden, RuntimeRegisterRef{RegisterId::register_tc3_bmr, 0x40054000u, 196u, true}, 10u, 1u, true}, RuntimeFieldRef{FieldId::field_tc3_bmr_edgpha, RuntimeRegisterRef{RegisterId::register_tc3_bmr, 0x40054000u, 196u, true}, 12u, 1u, true}, RuntimeFieldRef{FieldId::field_tc3_qisr_dir, RuntimeRegisterRef{RegisterId::register_tc3_qisr, 0x40054000u, 212u, true}, 8u, 1u, true}, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0u, false, false, false},
}};

template<std::size_t Index>
struct TimerTraitsBase {
  static constexpr auto& kFacts = kTimerHardwareLut[Index];
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = kFacts.schema_id;
  static constexpr std::uint32_t kCounterBits = kFacts.counter_bits;
  static constexpr std::uint32_t kChannelCount = kFacts.channel_count;
  static constexpr bool kHasCompare = kFacts.has_compare;
  static constexpr bool kHasCapture = kFacts.has_capture;
  static constexpr bool kHasEncoder = kFacts.has_encoder;
  static constexpr bool kHasPwm = kFacts.has_pwm;
  static constexpr bool kHasOnePulse = kFacts.has_one_pulse;
  static constexpr bool kHasCenterAligned = kFacts.has_center_aligned;
  static constexpr bool kHasComplementaryOutputs = kFacts.has_complementary_outputs;
  static constexpr bool kHasDeadtime = kFacts.has_deadtime;
  static constexpr bool kHasBreakInput = kFacts.has_break_input;
  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;
  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;
  static constexpr RuntimeRegisterRef kEventRegister = kFacts.event_register;
  static constexpr RuntimeRegisterRef kCounterRegister = kFacts.counter_register;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kFacts.prescaler_register;
  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;
  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;
  static constexpr RuntimeFieldRef kDisableField = kFacts.disable_field;
  static constexpr RuntimeFieldRef kModuleDisableField = kFacts.module_disable_field;
  static constexpr RuntimeFieldRef kSoftwareResetField = kFacts.software_reset_field;
  static constexpr RuntimeFieldRef kStartField = kFacts.start_field;
  static constexpr RuntimeFieldRef kStopField = kFacts.stop_field;
  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kFacts.update_interrupt_enable_field;
  static constexpr RuntimeFieldRef kUpdateFlagField = kFacts.update_flag_field;
  static constexpr RuntimeFieldRef kUpdateGenerationField = kFacts.update_generation_field;
  static constexpr RuntimeFieldRef kPrescalerField = kFacts.prescaler_field;
  static constexpr RuntimeFieldRef kPeriodField = kFacts.period_field;
  static constexpr RuntimeFieldRef kOnePulseField = kFacts.one_pulse_field;
  static constexpr RuntimeFieldRef kCenterAlignedField = kFacts.center_aligned_field;
  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kFacts.auto_reload_preload_field;
  static constexpr RuntimeFieldRef kClockSourceField = kFacts.clock_source_field;
  static constexpr RuntimeFieldRef kEncoderModeField = kFacts.encoder_mode_field;
  static constexpr RuntimeFieldRef kEncoderEnableField = kFacts.encoder_enable_field;
  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kFacts.encoder_position_enable_field;
  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kFacts.encoder_speed_enable_field;
  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kFacts.encoder_phase_edge_field;
  static constexpr RuntimeFieldRef kDirectionField = kFacts.direction_field;
  static constexpr std::uint32_t kUpdateIrqNumber = kFacts.update_irq_number;
  static constexpr std::uint32_t kCaptureIrqNumber = kFacts.capture_irq_number;
  static constexpr std::uint32_t kBreakIrqNumber = kFacts.break_irq_number;
  static constexpr std::uint32_t kTriggerIrqNumber = kFacts.trigger_irq_number;
  static constexpr std::uint32_t kMaxPrescaler = kFacts.max_prescaler;
  static constexpr std::uint32_t kMaxAutoReload = kFacts.max_auto_reload;
  static constexpr bool kSupportsDmaBurst = kFacts.supports_dma_burst;
  static constexpr bool kSupportsRepetitionCounter = kFacts.supports_repetition_counter;
  static constexpr bool kSupportsXorInput = kFacts.supports_xor_input;
};

template<>
struct TimerSemanticTraits<PeripheralId::TC0> : TimerTraitsBase<0> {
  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};
  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 1> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_tc0_rx_xdmac_perid_40, 40u, DmaBindingDirection::Rx, 16u, true},
  }};
};

template<>
struct TimerSemanticTraits<PeripheralId::TC1> : TimerTraitsBase<1> {
  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};
  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 1> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_tc1_rx_xdmac_perid_41, 41u, DmaBindingDirection::Rx, 16u, true},
  }};
};

template<>
struct TimerSemanticTraits<PeripheralId::TC2> : TimerTraitsBase<2> {
  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};
  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 1> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_tc2_rx_xdmac_perid_42, 42u, DmaBindingDirection::Rx, 16u, true},
  }};
};

template<>
struct TimerSemanticTraits<PeripheralId::TC3> : TimerTraitsBase<3> {
  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};
  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 1> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_tc3_rx_xdmac_perid_43, 43u, DmaBindingDirection::Rx, 16u, true},
  }};
};

template<PeripheralId Id, std::size_t ChannelIndex>
struct TimerChannelSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr bool kSupportsCompare = false;
  static constexpr bool kSupportsCapture = false;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

struct TimerChannelHardwareLut {
  bool supports_compare;
  bool supports_capture;
  bool supports_encoder_input;
  bool supports_pwm;
  bool supports_complementary_output;
  RuntimeRegisterRef control_register;
  RuntimeRegisterRef status_register;
  RuntimeRegisterRef compare_register;
  RuntimeRegisterRef secondary_compare_register;
  RuntimeRegisterRef period_register;
  RuntimeRegisterRef counter_register;
  RuntimeRegisterRef capture_register;
  RuntimeFieldRef enable_field;
  RuntimeFieldRef interrupt_enable_field;
  RuntimeFieldRef interrupt_flag_field;
  RuntimeFieldRef mode_field;
  RuntimeFieldRef preload_field;
  RuntimeFieldRef output_enable_field;
  RuntimeFieldRef output_polarity_field;
  RuntimeFieldRef complementary_output_enable_field;
  RuntimeFieldRef capture_select_field;
};

inline constexpr std::array<TimerChannelHardwareLut, 12> kTimerChannelHardwareLut = {{
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 20u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 24u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 28u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 20u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 4u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 64u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 96u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 84u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 88u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 92u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 80u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 84u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 64u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 100u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 96u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 68u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 128u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 160u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 148u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 152u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 156u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 144u, true}, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 148u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 128u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 164u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 160u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x4000C000u, 132u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 20u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 24u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 28u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 20u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 4u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 64u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 96u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 84u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 88u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 92u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 80u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 84u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 64u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 100u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 96u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 68u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 128u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 160u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 148u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 152u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 156u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 144u, true}, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 148u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 128u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 164u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 160u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40010000u, 132u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 20u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 24u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 28u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 20u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 4u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 64u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 96u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 84u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 88u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 92u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 80u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 84u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 64u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 100u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 96u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 68u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 128u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 160u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 148u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 152u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 156u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 144u, true}, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 148u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 128u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 164u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 160u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40014000u, 132u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 20u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 24u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 28u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 20u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 0u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 36u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 4u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 64u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 96u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 84u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 88u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 92u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 80u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 84u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 64u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 100u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 96u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 68u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
  {true, true, false, true, false, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 128u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 160u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 148u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 152u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 156u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 144u, true}, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 148u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 128u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 164u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 160u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40054000u, 132u, true}, 15u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
}};

template<std::size_t Index>
struct TimerChannelTraitsBase {
  static constexpr auto& kFacts = kTimerChannelHardwareLut[Index];
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = kFacts.supports_compare;
  static constexpr bool kSupportsCapture = kFacts.supports_capture;
  static constexpr bool kSupportsEncoderInput = kFacts.supports_encoder_input;
  static constexpr bool kSupportsPwm = kFacts.supports_pwm;
  static constexpr bool kSupportsComplementaryOutput = kFacts.supports_complementary_output;
  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;
  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;
  static constexpr RuntimeRegisterRef kCompareRegister = kFacts.compare_register;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kFacts.secondary_compare_register;
  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;
  static constexpr RuntimeRegisterRef kCounterRegister = kFacts.counter_register;
  static constexpr RuntimeRegisterRef kCaptureRegister = kFacts.capture_register;
  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;
  static constexpr RuntimeFieldRef kInterruptEnableField = kFacts.interrupt_enable_field;
  static constexpr RuntimeFieldRef kInterruptFlagField = kFacts.interrupt_flag_field;
  static constexpr RuntimeFieldRef kModeField = kFacts.mode_field;
  static constexpr RuntimeFieldRef kPreloadField = kFacts.preload_field;
  static constexpr RuntimeFieldRef kOutputEnableField = kFacts.output_enable_field;
  static constexpr RuntimeFieldRef kOutputPolarityField = kFacts.output_polarity_field;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kFacts.complementary_output_enable_field;
  static constexpr RuntimeFieldRef kCaptureSelectField = kFacts.capture_select_field;
};

template<> struct TimerChannelSemanticTraits<PeripheralId::TC0, 0u> : TimerChannelTraitsBase<0> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC0, 1u> : TimerChannelTraitsBase<1> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC0, 2u> : TimerChannelTraitsBase<2> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC1, 0u> : TimerChannelTraitsBase<3> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC1, 1u> : TimerChannelTraitsBase<4> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC1, 2u> : TimerChannelTraitsBase<5> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC2, 0u> : TimerChannelTraitsBase<6> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC2, 1u> : TimerChannelTraitsBase<7> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC2, 2u> : TimerChannelTraitsBase<8> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC3, 0u> : TimerChannelTraitsBase<9> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC3, 1u> : TimerChannelTraitsBase<10> {};
template<> struct TimerChannelSemanticTraits<PeripheralId::TC3, 2u> : TimerChannelTraitsBase<11> {};

inline constexpr std::array<PeripheralId, 4> kTimerSemanticPeripherals = {{
  PeripheralId::TC0,
  PeripheralId::TC1,
  PeripheralId::TC2,
  PeripheralId::TC3,
}};

// complete-rp2040-semantics Phase D: per-controller timer HW facts.
enum class RuntimeTimerCtrlId : std::uint8_t {
  None = 0,
};

template<RuntimeTimerCtrlId Id>
struct TimerControllerHwTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kCounterBits = 0u;
  static constexpr std::uint8_t kAlarmCount = 0u;
  static constexpr std::uint8_t kDreqAlarmBase = 0u;
};

}
}
}
}
}
}
}
