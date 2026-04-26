#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
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
struct GpioSemanticTraits<PinId::GP0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP10> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 10u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP11> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 11u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP12> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 12u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP13> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 13u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP14> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 14u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP15> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 15u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP16> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 16u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP17> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 17u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP18> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 18u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP19> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 19u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP20> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 20u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP21> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 21u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP22> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 22u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP23> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 23u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP24> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 24u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP25> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 25u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP26> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 26u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP27> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 27u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP28> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 28u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP29> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 29u;
  static constexpr std::uint8_t kMaxAltFunction = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP4> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 4u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP5> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP6> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 6u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP7> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 7u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP8> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 8u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

template<>
struct GpioSemanticTraits<PinId::GP9> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kLineIndex = 0u;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;
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
  static constexpr std::uint32_t kPinIndex = 9u;
  static constexpr std::uint8_t kMaxAltFunction = 3u;
  static constexpr std::array<std::uint8_t, 3> kValidAltFunctions = {{1u, 2u, 3u}};
  static constexpr bool kIsInputOnly = false;
};

inline constexpr std::array<PinId, 30> kGpioSemanticPins = {{
  PinId::GP0,
  PinId::GP1,
  PinId::GP10,
  PinId::GP11,
  PinId::GP12,
  PinId::GP13,
  PinId::GP14,
  PinId::GP15,
  PinId::GP16,
  PinId::GP17,
  PinId::GP18,
  PinId::GP19,
  PinId::GP2,
  PinId::GP20,
  PinId::GP21,
  PinId::GP22,
  PinId::GP23,
  PinId::GP24,
  PinId::GP25,
  PinId::GP26,
  PinId::GP27,
  PinId::GP28,
  PinId::GP29,
  PinId::GP3,
  PinId::GP4,
  PinId::GP5,
  PinId::GP6,
  PinId::GP7,
  PinId::GP8,
  PinId::GP9,
}};
}
}
}
}
}
}
}
