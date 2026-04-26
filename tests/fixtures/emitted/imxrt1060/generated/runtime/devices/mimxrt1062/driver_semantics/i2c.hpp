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
namespace mimxrt1062 {
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
}
}
}
}
}
}
}
