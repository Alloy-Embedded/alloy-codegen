#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
namespace driver_semantics {
template<PeripheralId Id>
struct SpiSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kCphaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCpolField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMstrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLsbfirstField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSsiField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSsmField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDffField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFrxthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBsyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpienField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpidisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPcsdecField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModfdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPcsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDlybcsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNcphaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBitsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kScbrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDlybsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDlybctField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTdreField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRdrfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTdField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTdrPcsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRdField = kInvalidFieldRef;
};

template<>
struct SpiSemanticTraits<PeripheralId::LPSPI1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_nxp_lpspi_v1;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = RuntimeRegisterRef{RegisterId::none, 0x40394000u, 20u, true};
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::none, 0x40394000u, 16u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::none, 0x40394000u, 36u, true};
  static constexpr RuntimeRegisterRef kCsrRegister = RuntimeRegisterRef{RegisterId::none, 0x40394000u, 64u, true};
  static constexpr RuntimeRegisterRef kTdrRegister = RuntimeRegisterRef{RegisterId::none, 0x40394000u, 100u, true};
  static constexpr RuntimeRegisterRef kRdrRegister = RuntimeRegisterRef{RegisterId::none, 0x40394000u, 116u, true};
  static constexpr RuntimeFieldRef kCphaField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 96u, true}, 30u, 1u, true};
  static constexpr RuntimeFieldRef kCpolField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 96u, true}, 31u, 1u, true};
  static constexpr RuntimeFieldRef kMstrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 36u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kBrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 96u, true}, 27u, 3u, true};
  static constexpr RuntimeFieldRef kSpeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 16u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kLsbfirstField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 96u, true}, 23u, 1u, true};
  static constexpr RuntimeFieldRef kSsiField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSsmField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDffField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDsField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 96u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kFrxthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kRxneField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kBsyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 20u, true}, 24u, 1u, true};
  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpienField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpidisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSwrstField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 16u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPcsdecField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModfdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPcsField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 96u, true}, 24u, 2u, true};
  static constexpr RuntimeFieldRef kDlybcsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNcphaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBitsField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 96u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kScbrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 64u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kDlybsField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 64u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kDlybctField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 64u, true}, 16u, 8u, true};
  static constexpr RuntimeFieldRef kTdreField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRdrfField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTdField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 100u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kTdrPcsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRdField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40394000u, 116u, true}, 0u, 32u, true};
};

inline constexpr std::array<PeripheralId, 1> kSpiSemanticPeripherals = {{
  PeripheralId::LPSPI1,
}};
}
}
}
}
}
}
}
