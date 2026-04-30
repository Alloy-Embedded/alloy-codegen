#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
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
struct GpioSemanticTraits<PinId::PA0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpioa_moder, 0x50000000u, 0u, true}, 0u, 2u, true};
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 4u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kPullField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 12u, true}, 0u, 2u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 8u, true}, 0u, 2u, true};
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
  static constexpr std::uint32_t kPortOffset = 0x00000000u;
  static constexpr std::uint32_t kPinIndex = 0u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::PA1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpioa_moder, 0x50000000u, 0u, true}, 2u, 2u, true};
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 4u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kPullField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 12u, true}, 2u, 2u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 8u, true}, 2u, 2u, true};
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
  static constexpr std::uint32_t kPortOffset = 0x00000000u;
  static constexpr std::uint32_t kPinIndex = 1u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 1> kValidAltFunctions = {{0u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::PA2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::field_gpioa_moder_mode2, RuntimeRegisterRef{RegisterId::register_gpioa_moder, 0x50000000u, 0u, true}, 4u, 2u, true};
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 4u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kPullField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 12u, true}, 4u, 2u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 8u, true}, 4u, 2u, true};
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
  static constexpr std::uint32_t kPortOffset = 0x00000000u;
  static constexpr std::uint32_t kPinIndex = 2u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::PA3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpioa_moder, 0x50000000u, 0u, true}, 6u, 2u, true};
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 4u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kPullField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 12u, true}, 6u, 2u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 8u, true}, 6u, 2u, true};
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
  static constexpr std::uint32_t kPortOffset = 0x00000000u;
  static constexpr std::uint32_t kPinIndex = 3u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::PA5> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpioa_moder, 0x50000000u, 0u, true}, 10u, 2u, true};
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 4u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kPullField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 12u, true}, 10u, 2u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000000u, 8u, true}, 10u, 2u, true};
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
  static constexpr std::uint32_t kPortOffset = 0x00000000u;
  static constexpr std::uint32_t kPinIndex = 5u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::PB6> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::field_gpiob_moder_mode6, RuntimeRegisterRef{RegisterId::register_gpiob_moder, 0x50000400u, 0u, true}, 12u, 2u, true};
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000400u, 4u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kPullField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000400u, 12u, true}, 12u, 2u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000400u, 8u, true}, 12u, 2u, true};
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
  static constexpr std::uint32_t kPortOffset = 0x00000400u;
  static constexpr std::uint32_t kPinIndex = 6u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 1> kValidAltFunctions = {{0u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::PB7> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpiob_moder, 0x50000400u, 0u, true}, 14u, 2u, true};
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000400u, 4u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kPullField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000400u, 12u, true}, 14u, 2u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x50000400u, 8u, true}, 14u, 2u, true};
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
  static constexpr std::uint32_t kPortOffset = 0x00000400u;
  static constexpr std::uint32_t kPinIndex = 7u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 1> kValidAltFunctions = {{0u}};
  static constexpr bool kIsInputOnly = false;
};

inline constexpr std::array<PinId, 7> kGpioSemanticPins = {{
  PinId::PA0,
  PinId::PA1,
  PinId::PA2,
  PinId::PA3,
  PinId::PA5,
  PinId::PB6,
  PinId::PB7,
}};
}
}
}
}
}
}
}
