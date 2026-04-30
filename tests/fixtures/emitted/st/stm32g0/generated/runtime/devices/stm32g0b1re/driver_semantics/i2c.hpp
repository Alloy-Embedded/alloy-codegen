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
namespace stm32g0b1re {
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
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kSupportedSpeeds = {};
  static constexpr std::array<I2cTimingPreset, 0> kTimingPresets = {};
  static constexpr bool kSupportsSmbus = false;
  static constexpr bool kSupportsPmbus = false;
  static constexpr bool kSupportsSlave = false;
  static constexpr bool kSupportsDualAddress = false;
  static constexpr bool kSupportsGeneralCall = false;
  static constexpr bool kSupports7BitAddressing = false;
  static constexpr bool kSupports10BitAddressing = false;
};

template<>
struct I2cSemanticTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_st_i2c;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = RuntimeRegisterRef{RegisterId::none, 0x40005400u, 4u, true};
  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIcrRegister = RuntimeRegisterRef{RegisterId::none, 0x40005400u, 32u, true};
  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 4u, true}, 13u, 1u, true};
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
  static constexpr RuntimeFieldRef kSaddField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 4u, true}, 0u, 10u, true};
  static constexpr RuntimeFieldRef kRdWrnField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 4u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kNbytesField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 4u, true}, 16u, 8u, true};
  static constexpr RuntimeFieldRef kAutoendField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 4u, true}, 25u, 1u, true};
  static constexpr RuntimeFieldRef kTxisField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 28u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTcField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 28u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kStopfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 28u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTxdataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 40u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxdataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 36u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kNackfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 28u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kBerrIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 28u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kArloIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 28u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kStopcfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 32u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kNackcfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 32u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kBerrcfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 32u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kArlocfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005400u, 32u, true}, 9u, 1u, true};
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
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 3> kSupportedSpeeds = {{100000u, 400000u, 1000000u}};
  static constexpr std::array<I2cTimingPreset, 3> kTimingPresets = {{{100000u, 64000000u, 0x10707ebbu, true}, {400000u, 64000000u, 0x00602173u, true}, {1000000u, 64000000u, 0x00300619u, true}}};
  static constexpr bool kSupportsSmbus = true;
  static constexpr bool kSupportsPmbus = false;
  static constexpr bool kSupportsSlave = true;
  static constexpr bool kSupportsDualAddress = true;
  static constexpr bool kSupportsGeneralCall = true;
  static constexpr bool kSupports7BitAddressing = true;
  static constexpr bool kSupports10BitAddressing = true;
};

template<>
struct I2cSemanticTraits<PeripheralId::I2C2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_st_i2c;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = RuntimeRegisterRef{RegisterId::none, 0x40005800u, 4u, true};
  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIcrRegister = RuntimeRegisterRef{RegisterId::none, 0x40005800u, 32u, true};
  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 4u, true}, 13u, 1u, true};
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
  static constexpr RuntimeFieldRef kSaddField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 4u, true}, 0u, 10u, true};
  static constexpr RuntimeFieldRef kRdWrnField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 4u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kNbytesField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 4u, true}, 16u, 8u, true};
  static constexpr RuntimeFieldRef kAutoendField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 4u, true}, 25u, 1u, true};
  static constexpr RuntimeFieldRef kTxisField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 28u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTcField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 28u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kStopfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 28u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTxdataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 40u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxdataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 36u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kNackfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 28u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kBerrIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 28u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kArloIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 28u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kStopcfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 32u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kNackcfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 32u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kBerrcfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 32u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kArlocfField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005800u, 32u, true}, 9u, 1u, true};
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
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 3> kSupportedSpeeds = {{100000u, 400000u, 1000000u}};
  static constexpr std::array<I2cTimingPreset, 3> kTimingPresets = {{{100000u, 64000000u, 0x10707ebbu, true}, {400000u, 64000000u, 0x00602173u, true}, {1000000u, 64000000u, 0x00300619u, true}}};
  static constexpr bool kSupportsSmbus = true;
  static constexpr bool kSupportsPmbus = false;
  static constexpr bool kSupportsSlave = true;
  static constexpr bool kSupportsDualAddress = true;
  static constexpr bool kSupportsGeneralCall = true;
  static constexpr bool kSupports7BitAddressing = true;
  static constexpr bool kSupports10BitAddressing = true;
};

inline constexpr std::array<PeripheralId, 2> kI2cSemanticPeripherals = {{
  PeripheralId::I2C1,
  PeripheralId::I2C2,
}};

// fill-i2c-semantic-gaps: per-controller I2C / TWI HW facts.
enum class RuntimeI2cClockSource : std::uint8_t {
  None = 0,
  Pclk = 1,
  Hsi16 = 2,
  Sysclk = 3,
};

enum class RuntimeI2cCtrlId : std::uint8_t {
  None = 0,
  I2C1 = 1,
  I2C2 = 2,
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
struct I2cPeripheralTraits<RuntimeI2cCtrlId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40005400u;
  static constexpr RuntimeI2cClockSource kClockSource = RuntimeI2cClockSource::Pclk;
  static constexpr std::uint8_t kDreqTx = 0u;
  static constexpr std::uint8_t kDreqRx = 0u;
  static constexpr std::array<PinId, 0> kValidSdaPins = {};
  static constexpr std::array<PinId, 0> kValidSclPins = {};
  static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kInSclSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSclSignal = 0xFFFFu;
  static constexpr bool kSupportsFastModePlus = true;
  static constexpr bool kPortmuxAlt = false;
};

template<>
struct I2cPeripheralTraits<RuntimeI2cCtrlId::I2C2> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40005800u;
  static constexpr RuntimeI2cClockSource kClockSource = RuntimeI2cClockSource::Pclk;
  static constexpr std::uint8_t kDreqTx = 0u;
  static constexpr std::uint8_t kDreqRx = 0u;
  static constexpr std::array<PinId, 0> kValidSdaPins = {};
  static constexpr std::array<PinId, 0> kValidSclPins = {};
  static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kInSclSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSdaSignal = 0xFFFFu;
  static constexpr std::uint16_t kOutSclSignal = 0xFFFFu;
  static constexpr bool kSupportsFastModePlus = true;
  static constexpr bool kPortmuxAlt = false;
};


// add-typed-peripheral-enums-everywhere: typed I2cSpeedModeOf per peripheral.
template<PeripheralId Id>
struct I2cSpeedModeOf {
  enum class type : std::uint8_t {};
};

template<>
struct I2cSpeedModeOf<PeripheralId::I2C1> {
  enum class type : std::uint8_t {
    standard = 0u,
    fast = 1u,
    fast_plus = 2u,
  };
};

template<>
struct I2cSpeedModeOf<PeripheralId::I2C2> {
  enum class type : std::uint8_t {
    standard = 0u,
    fast = 1u,
    fast_plus = 2u,
  };
};

template<PeripheralId Id>
using I2cSpeedMode = typename I2cSpeedModeOf<Id>::type;

}
}
}
}
}
}
}
