#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
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
struct I2cSemanticTraits<PeripheralId::TWIHS0> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_microchip_twihs_z;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_twihs0_cr, 0x40018000u, 0u, true};
  static constexpr RuntimeRegisterRef kMmrRegister = RuntimeRegisterRef{RegisterId::register_twihs0_mmr, 0x40018000u, 4u, true};
  static constexpr RuntimeRegisterRef kIadrRegister = RuntimeRegisterRef{RegisterId::register_twihs0_iadr, 0x40018000u, 12u, true};
  static constexpr RuntimeRegisterRef kCwgrRegister = RuntimeRegisterRef{RegisterId::register_twihs0_cwgr, 0x40018000u, 16u, true};
  static constexpr RuntimeRegisterRef kSrRegister = RuntimeRegisterRef{RegisterId::register_twihs0_sr, 0x40018000u, 32u, true};
  static constexpr RuntimeRegisterRef kRhrRegister = RuntimeRegisterRef{RegisterId::register_twihs0_rhr, 0x40018000u, 48u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_twihs0_thr, 0x40018000u, 52u, true};
  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::field_twihs0_cr_start, RuntimeRegisterRef{RegisterId::register_twihs0_cr, 0x40018000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kStopField = RuntimeFieldRef{FieldId::field_twihs0_cr_stop, RuntimeRegisterRef{RegisterId::register_twihs0_cr, 0x40018000u, 0u, true}, 1u, 1u, true};
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
  static constexpr RuntimeFieldRef kTxdataField = RuntimeFieldRef{FieldId::field_twihs0_thr_txdata, RuntimeRegisterRef{RegisterId::register_twihs0_thr, 0x40018000u, 52u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxdataField = RuntimeFieldRef{FieldId::field_twihs0_rhr_rxdata, RuntimeRegisterRef{RegisterId::register_twihs0_rhr, 0x40018000u, 48u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMsenField = RuntimeFieldRef{FieldId::field_twihs0_cr_msen, RuntimeRegisterRef{RegisterId::register_twihs0_cr, 0x40018000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kMsdisField = RuntimeFieldRef{FieldId::field_twihs0_cr_msdis, RuntimeRegisterRef{RegisterId::register_twihs0_cr, 0x40018000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kSvdisField = RuntimeFieldRef{FieldId::field_twihs0_cr_svdis, RuntimeRegisterRef{RegisterId::register_twihs0_cr, 0x40018000u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kSwrstField = RuntimeFieldRef{FieldId::field_twihs0_cr_swrst, RuntimeRegisterRef{RegisterId::register_twihs0_cr, 0x40018000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kIadrszField = RuntimeFieldRef{FieldId::field_twihs0_mmr_iadrsz, RuntimeRegisterRef{RegisterId::register_twihs0_mmr, 0x40018000u, 4u, true}, 8u, 2u, true};
  static constexpr RuntimeFieldRef kMreadField = RuntimeFieldRef{FieldId::field_twihs0_mmr_mread, RuntimeRegisterRef{RegisterId::register_twihs0_mmr, 0x40018000u, 4u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kDadrField = RuntimeFieldRef{FieldId::field_twihs0_mmr_dadr, RuntimeRegisterRef{RegisterId::register_twihs0_mmr, 0x40018000u, 4u, true}, 16u, 7u, true};
  static constexpr RuntimeFieldRef kIadrField = RuntimeFieldRef{FieldId::field_twihs0_iadr_iadr, RuntimeRegisterRef{RegisterId::register_twihs0_iadr, 0x40018000u, 12u, true}, 0u, 24u, true};
  static constexpr RuntimeFieldRef kCldivField = RuntimeFieldRef{FieldId::field_twihs0_cwgr_cldiv, RuntimeRegisterRef{RegisterId::register_twihs0_cwgr, 0x40018000u, 16u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kChdivField = RuntimeFieldRef{FieldId::field_twihs0_cwgr_chdiv, RuntimeRegisterRef{RegisterId::register_twihs0_cwgr, 0x40018000u, 16u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kCkdivField = RuntimeFieldRef{FieldId::field_twihs0_cwgr_ckdiv, RuntimeRegisterRef{RegisterId::register_twihs0_cwgr, 0x40018000u, 16u, true}, 16u, 3u, true};
  static constexpr RuntimeFieldRef kHoldField = RuntimeFieldRef{FieldId::field_twihs0_cwgr_hold, RuntimeRegisterRef{RegisterId::register_twihs0_cwgr, 0x40018000u, 16u, true}, 24u, 6u, true};
  static constexpr RuntimeFieldRef kTxcompField = RuntimeFieldRef{FieldId::field_twihs0_sr_txcomp, RuntimeRegisterRef{RegisterId::register_twihs0_sr, 0x40018000u, 32u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_twihs0_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_twihs0_sr, 0x40018000u, 32u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_twihs0_sr_txrdy, RuntimeRegisterRef{RegisterId::register_twihs0_sr, 0x40018000u, 32u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kNackField = RuntimeFieldRef{FieldId::field_twihs0_sr_nack, RuntimeRegisterRef{RegisterId::register_twihs0_sr, 0x40018000u, 32u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kArblstField = RuntimeFieldRef{FieldId::field_twihs0_sr_arblst, RuntimeRegisterRef{RegisterId::register_twihs0_sr, 0x40018000u, 32u, true}, 9u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kSupportedSpeeds = {};
  static constexpr std::array<I2cTimingPreset, 0> kTimingPresets = {};
  static constexpr bool kSupportsSmbus = false;
  static constexpr bool kSupportsPmbus = false;
  static constexpr bool kSupportsSlave = true;
  static constexpr bool kSupportsDualAddress = false;
  static constexpr bool kSupportsGeneralCall = false;
  static constexpr bool kSupports7BitAddressing = true;
  static constexpr bool kSupports10BitAddressing = false;
};

template<>
struct I2cSemanticTraits<PeripheralId::TWIHS1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_microchip_twihs_z;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_twihs1_cr, 0x4001C000u, 0u, true};
  static constexpr RuntimeRegisterRef kMmrRegister = RuntimeRegisterRef{RegisterId::register_twihs1_mmr, 0x4001C000u, 4u, true};
  static constexpr RuntimeRegisterRef kIadrRegister = RuntimeRegisterRef{RegisterId::register_twihs1_iadr, 0x4001C000u, 12u, true};
  static constexpr RuntimeRegisterRef kCwgrRegister = RuntimeRegisterRef{RegisterId::register_twihs1_cwgr, 0x4001C000u, 16u, true};
  static constexpr RuntimeRegisterRef kSrRegister = RuntimeRegisterRef{RegisterId::register_twihs1_sr, 0x4001C000u, 32u, true};
  static constexpr RuntimeRegisterRef kRhrRegister = RuntimeRegisterRef{RegisterId::register_twihs1_rhr, 0x4001C000u, 48u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_twihs1_thr, 0x4001C000u, 52u, true};
  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::field_twihs1_cr_start, RuntimeRegisterRef{RegisterId::register_twihs1_cr, 0x4001C000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kStopField = RuntimeFieldRef{FieldId::field_twihs1_cr_stop, RuntimeRegisterRef{RegisterId::register_twihs1_cr, 0x4001C000u, 0u, true}, 1u, 1u, true};
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
  static constexpr RuntimeFieldRef kTxdataField = RuntimeFieldRef{FieldId::field_twihs1_thr_txdata, RuntimeRegisterRef{RegisterId::register_twihs1_thr, 0x4001C000u, 52u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxdataField = RuntimeFieldRef{FieldId::field_twihs1_rhr_rxdata, RuntimeRegisterRef{RegisterId::register_twihs1_rhr, 0x4001C000u, 48u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMsenField = RuntimeFieldRef{FieldId::field_twihs1_cr_msen, RuntimeRegisterRef{RegisterId::register_twihs1_cr, 0x4001C000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kMsdisField = RuntimeFieldRef{FieldId::field_twihs1_cr_msdis, RuntimeRegisterRef{RegisterId::register_twihs1_cr, 0x4001C000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kSvdisField = RuntimeFieldRef{FieldId::field_twihs1_cr_svdis, RuntimeRegisterRef{RegisterId::register_twihs1_cr, 0x4001C000u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kSwrstField = RuntimeFieldRef{FieldId::field_twihs1_cr_swrst, RuntimeRegisterRef{RegisterId::register_twihs1_cr, 0x4001C000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kIadrszField = RuntimeFieldRef{FieldId::field_twihs1_mmr_iadrsz, RuntimeRegisterRef{RegisterId::register_twihs1_mmr, 0x4001C000u, 4u, true}, 8u, 2u, true};
  static constexpr RuntimeFieldRef kMreadField = RuntimeFieldRef{FieldId::field_twihs1_mmr_mread, RuntimeRegisterRef{RegisterId::register_twihs1_mmr, 0x4001C000u, 4u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kDadrField = RuntimeFieldRef{FieldId::field_twihs1_mmr_dadr, RuntimeRegisterRef{RegisterId::register_twihs1_mmr, 0x4001C000u, 4u, true}, 16u, 7u, true};
  static constexpr RuntimeFieldRef kIadrField = RuntimeFieldRef{FieldId::field_twihs1_iadr_iadr, RuntimeRegisterRef{RegisterId::register_twihs1_iadr, 0x4001C000u, 12u, true}, 0u, 24u, true};
  static constexpr RuntimeFieldRef kCldivField = RuntimeFieldRef{FieldId::field_twihs1_cwgr_cldiv, RuntimeRegisterRef{RegisterId::register_twihs1_cwgr, 0x4001C000u, 16u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kChdivField = RuntimeFieldRef{FieldId::field_twihs1_cwgr_chdiv, RuntimeRegisterRef{RegisterId::register_twihs1_cwgr, 0x4001C000u, 16u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kCkdivField = RuntimeFieldRef{FieldId::field_twihs1_cwgr_ckdiv, RuntimeRegisterRef{RegisterId::register_twihs1_cwgr, 0x4001C000u, 16u, true}, 16u, 3u, true};
  static constexpr RuntimeFieldRef kHoldField = RuntimeFieldRef{FieldId::field_twihs1_cwgr_hold, RuntimeRegisterRef{RegisterId::register_twihs1_cwgr, 0x4001C000u, 16u, true}, 24u, 6u, true};
  static constexpr RuntimeFieldRef kTxcompField = RuntimeFieldRef{FieldId::field_twihs1_sr_txcomp, RuntimeRegisterRef{RegisterId::register_twihs1_sr, 0x4001C000u, 32u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_twihs1_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_twihs1_sr, 0x4001C000u, 32u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_twihs1_sr_txrdy, RuntimeRegisterRef{RegisterId::register_twihs1_sr, 0x4001C000u, 32u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kNackField = RuntimeFieldRef{FieldId::field_twihs1_sr_nack, RuntimeRegisterRef{RegisterId::register_twihs1_sr, 0x4001C000u, 32u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kArblstField = RuntimeFieldRef{FieldId::field_twihs1_sr_arblst, RuntimeRegisterRef{RegisterId::register_twihs1_sr, 0x4001C000u, 32u, true}, 9u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kSupportedSpeeds = {};
  static constexpr std::array<I2cTimingPreset, 0> kTimingPresets = {};
  static constexpr bool kSupportsSmbus = false;
  static constexpr bool kSupportsPmbus = false;
  static constexpr bool kSupportsSlave = true;
  static constexpr bool kSupportsDualAddress = false;
  static constexpr bool kSupportsGeneralCall = false;
  static constexpr bool kSupports7BitAddressing = true;
  static constexpr bool kSupports10BitAddressing = false;
};

template<>
struct I2cSemanticTraits<PeripheralId::TWIHS2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_microchip_twihs_z;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_twihs2_cr, 0x40060000u, 0u, true};
  static constexpr RuntimeRegisterRef kMmrRegister = RuntimeRegisterRef{RegisterId::register_twihs2_mmr, 0x40060000u, 4u, true};
  static constexpr RuntimeRegisterRef kIadrRegister = RuntimeRegisterRef{RegisterId::register_twihs2_iadr, 0x40060000u, 12u, true};
  static constexpr RuntimeRegisterRef kCwgrRegister = RuntimeRegisterRef{RegisterId::register_twihs2_cwgr, 0x40060000u, 16u, true};
  static constexpr RuntimeRegisterRef kSrRegister = RuntimeRegisterRef{RegisterId::register_twihs2_sr, 0x40060000u, 32u, true};
  static constexpr RuntimeRegisterRef kRhrRegister = RuntimeRegisterRef{RegisterId::register_twihs2_rhr, 0x40060000u, 48u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_twihs2_thr, 0x40060000u, 52u, true};
  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::field_twihs2_cr_start, RuntimeRegisterRef{RegisterId::register_twihs2_cr, 0x40060000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kStopField = RuntimeFieldRef{FieldId::field_twihs2_cr_stop, RuntimeRegisterRef{RegisterId::register_twihs2_cr, 0x40060000u, 0u, true}, 1u, 1u, true};
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
  static constexpr RuntimeFieldRef kTxdataField = RuntimeFieldRef{FieldId::field_twihs2_thr_txdata, RuntimeRegisterRef{RegisterId::register_twihs2_thr, 0x40060000u, 52u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxdataField = RuntimeFieldRef{FieldId::field_twihs2_rhr_rxdata, RuntimeRegisterRef{RegisterId::register_twihs2_rhr, 0x40060000u, 48u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMsenField = RuntimeFieldRef{FieldId::field_twihs2_cr_msen, RuntimeRegisterRef{RegisterId::register_twihs2_cr, 0x40060000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kMsdisField = RuntimeFieldRef{FieldId::field_twihs2_cr_msdis, RuntimeRegisterRef{RegisterId::register_twihs2_cr, 0x40060000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kSvdisField = RuntimeFieldRef{FieldId::field_twihs2_cr_svdis, RuntimeRegisterRef{RegisterId::register_twihs2_cr, 0x40060000u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kSwrstField = RuntimeFieldRef{FieldId::field_twihs2_cr_swrst, RuntimeRegisterRef{RegisterId::register_twihs2_cr, 0x40060000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kIadrszField = RuntimeFieldRef{FieldId::field_twihs2_mmr_iadrsz, RuntimeRegisterRef{RegisterId::register_twihs2_mmr, 0x40060000u, 4u, true}, 8u, 2u, true};
  static constexpr RuntimeFieldRef kMreadField = RuntimeFieldRef{FieldId::field_twihs2_mmr_mread, RuntimeRegisterRef{RegisterId::register_twihs2_mmr, 0x40060000u, 4u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kDadrField = RuntimeFieldRef{FieldId::field_twihs2_mmr_dadr, RuntimeRegisterRef{RegisterId::register_twihs2_mmr, 0x40060000u, 4u, true}, 16u, 7u, true};
  static constexpr RuntimeFieldRef kIadrField = RuntimeFieldRef{FieldId::field_twihs2_iadr_iadr, RuntimeRegisterRef{RegisterId::register_twihs2_iadr, 0x40060000u, 12u, true}, 0u, 24u, true};
  static constexpr RuntimeFieldRef kCldivField = RuntimeFieldRef{FieldId::field_twihs2_cwgr_cldiv, RuntimeRegisterRef{RegisterId::register_twihs2_cwgr, 0x40060000u, 16u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kChdivField = RuntimeFieldRef{FieldId::field_twihs2_cwgr_chdiv, RuntimeRegisterRef{RegisterId::register_twihs2_cwgr, 0x40060000u, 16u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kCkdivField = RuntimeFieldRef{FieldId::field_twihs2_cwgr_ckdiv, RuntimeRegisterRef{RegisterId::register_twihs2_cwgr, 0x40060000u, 16u, true}, 16u, 3u, true};
  static constexpr RuntimeFieldRef kHoldField = RuntimeFieldRef{FieldId::field_twihs2_cwgr_hold, RuntimeRegisterRef{RegisterId::register_twihs2_cwgr, 0x40060000u, 16u, true}, 24u, 6u, true};
  static constexpr RuntimeFieldRef kTxcompField = RuntimeFieldRef{FieldId::field_twihs2_sr_txcomp, RuntimeRegisterRef{RegisterId::register_twihs2_sr, 0x40060000u, 32u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_twihs2_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_twihs2_sr, 0x40060000u, 32u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_twihs2_sr_txrdy, RuntimeRegisterRef{RegisterId::register_twihs2_sr, 0x40060000u, 32u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kNackField = RuntimeFieldRef{FieldId::field_twihs2_sr_nack, RuntimeRegisterRef{RegisterId::register_twihs2_sr, 0x40060000u, 32u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kArblstField = RuntimeFieldRef{FieldId::field_twihs2_sr_arblst, RuntimeRegisterRef{RegisterId::register_twihs2_sr, 0x40060000u, 32u, true}, 9u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kSupportedSpeeds = {};
  static constexpr std::array<I2cTimingPreset, 0> kTimingPresets = {};
  static constexpr bool kSupportsSmbus = false;
  static constexpr bool kSupportsPmbus = false;
  static constexpr bool kSupportsSlave = true;
  static constexpr bool kSupportsDualAddress = false;
  static constexpr bool kSupportsGeneralCall = false;
  static constexpr bool kSupports7BitAddressing = true;
  static constexpr bool kSupports10BitAddressing = false;
};

inline constexpr std::array<PeripheralId, 3> kI2cSemanticPeripherals = {{
  PeripheralId::TWIHS0,
  PeripheralId::TWIHS1,
  PeripheralId::TWIHS2,
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

}
}
}
}
}
}
}
