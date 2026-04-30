#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
namespace driver_semantics {
template<PinId Id>
struct GpioSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInputField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputValueField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;
  static constexpr std::uint32_t kPortOffset = 0u;
  static constexpr std::uint32_t kPinIndex = 0u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GPIO_AD_B0_00> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO1;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio1_gdir, 0x401B8000u, 4u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInputField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio1_psr, 0x401B8000u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kOutputValueField = RuntimeFieldRef{FieldId::field_gpio1_dr_data, RuntimeRegisterRef{RegisterId::register_gpio1_dr, 0x401B8000u, 0u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;
  static constexpr std::uint32_t kPortOffset = 0x00000000u;
  static constexpr std::uint32_t kPinIndex = 0u;
  static constexpr std::uint8_t kMaxAltFunction = 2u;
  static constexpr std::array<std::uint8_t, 2> kValidAltFunctions = {{0u, 2u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GPIO_AD_B0_01> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO1;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1;
  static constexpr std::uint32_t kLineIndex = 1u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio1_gdir, 0x401B8000u, 4u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInputField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio1_psr, 0x401B8000u, 8u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kOutputValueField = RuntimeFieldRef{FieldId::field_gpio1_dr_data, RuntimeRegisterRef{RegisterId::register_gpio1_dr, 0x401B8000u, 0u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;
  static constexpr std::uint32_t kPortOffset = 0x00000000u;
  static constexpr std::uint32_t kPinIndex = 1u;
  static constexpr std::uint8_t kMaxAltFunction = 2u;
  static constexpr std::array<std::uint8_t, 2> kValidAltFunctions = {{0u, 2u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GPIO_EMC_00> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO4;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio4_gdir, 0x401C4000u, 4u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInputField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio4_psr, 0x401C4000u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kOutputValueField = RuntimeFieldRef{FieldId::field_gpio4_dr_data, RuntimeRegisterRef{RegisterId::register_gpio4_dr, 0x401C4000u, 0u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;
  static constexpr std::uint32_t kPortOffset = 0x0000c000u;
  static constexpr std::uint32_t kPinIndex = 0u;
  static constexpr std::uint8_t kMaxAltFunction = 2u;
  static constexpr std::array<std::uint8_t, 1> kValidAltFunctions = {{2u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GPIO_EMC_01> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIO4;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1;
  static constexpr std::uint32_t kLineIndex = 1u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio4_gdir, 0x401C4000u, 4u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInputField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpio4_psr, 0x401C4000u, 8u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kOutputValueField = RuntimeFieldRef{FieldId::field_gpio4_dr_data, RuntimeRegisterRef{RegisterId::register_gpio4_dr, 0x401C4000u, 0u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;
  static constexpr std::uint32_t kPortOffset = 0x0000c000u;
  static constexpr std::uint32_t kPinIndex = 1u;
  static constexpr std::uint8_t kMaxAltFunction = 2u;
  static constexpr std::array<std::uint8_t, 1> kValidAltFunctions = {{2u}};
  static constexpr bool kIsInputOnly = false;
};

inline constexpr std::array<PinId, 4> kGpioSemanticPins = {{
  PinId::GPIO_AD_B0_00,
  PinId::GPIO_AD_B0_01,
  PinId::GPIO_EMC_00,
  PinId::GPIO_EMC_01,
}};
}
}
}
}
}
}
}
