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
template<PeripheralId Id>
struct I2cSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFreqField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCcrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTriseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSbField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAddrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBtfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArloField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBusyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSaddField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRdWrnField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNbytesField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAutoendField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTcField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxdataField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxdataField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMsenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMsdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSvdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kIadrszField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMreadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDadrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kIadrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCldivField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kChdivField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCkdivField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kHoldField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxcompField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNackField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArblstField = kInvalidFieldRef;
};

inline constexpr std::array<PeripheralId, 0> kI2cSemanticPeripherals = {};

// fill-i2c-semantic-gaps: per-controller I2C / TWI HW facts.
enum class RuntimeI2cClockSource : std::uint8_t {
  None = 0,
  Pclk = 1,
  Hsi16 = 2,
  Sysclk = 3,
};

enum class RuntimeI2cCtrlId : std::uint8_t {
  None = 0,
  I2C0 = 1,
  I2C1 = 2,
};

template<RuntimeI2cCtrlId Id>
struct I2cPeripheralTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr RuntimeI2cClockSource kClockSource = RuntimeI2cClockSource::None;
  static constexpr std::uint8_t kDreqTx = 0u;
  static constexpr std::uint8_t kDreqRx = 0u;
  static constexpr std::array<PinId, 0> kValidSdaPins = {};
  static constexpr std::array<PinId, 0> kValidSclPins = {};
  static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kInSclSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSclSignal = 0xFFFFu;
  static constexpr bool kSupportsFastModePlus = false;
  static constexpr bool kPortmuxAlt = false;
};

template<>
struct I2cPeripheralTraits<RuntimeI2cCtrlId::I2C0> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40044000u;
  static constexpr RuntimeI2cClockSource kClockSource = RuntimeI2cClockSource::None;
  static constexpr std::uint8_t kDreqTx = 32u;
  static constexpr std::uint8_t kDreqRx = 33u;
  static constexpr std::array<PinId, 8> kValidSdaPins = {PinId::GP0, PinId::GP4, PinId::GP8, PinId::GP12, PinId::GP16, PinId::GP20, PinId::GP24, PinId::GP28};
  static constexpr std::array<PinId, 8> kValidSclPins = {PinId::GP1, PinId::GP5, PinId::GP9, PinId::GP13, PinId::GP17, PinId::GP21, PinId::GP25, PinId::GP29};
  static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kInSclSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSclSignal = 0xFFFFu;
  static constexpr bool kSupportsFastModePlus = false;
  static constexpr bool kPortmuxAlt = false;
};

template<>
struct I2cPeripheralTraits<RuntimeI2cCtrlId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40048000u;
  static constexpr RuntimeI2cClockSource kClockSource = RuntimeI2cClockSource::None;
  static constexpr std::uint8_t kDreqTx = 34u;
  static constexpr std::uint8_t kDreqRx = 35u;
  static constexpr std::array<PinId, 6> kValidSdaPins = {PinId::GP2, PinId::GP6, PinId::GP10, PinId::GP14, PinId::GP18, PinId::GP26};
  static constexpr std::array<PinId, 6> kValidSclPins = {PinId::GP3, PinId::GP7, PinId::GP11, PinId::GP15, PinId::GP19, PinId::GP27};
  static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kInSclSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSclSignal = 0xFFFFu;
  static constexpr bool kSupportsFastModePlus = false;
  static constexpr bool kPortmuxAlt = false;
};

}
}
}
}
}
}
}
