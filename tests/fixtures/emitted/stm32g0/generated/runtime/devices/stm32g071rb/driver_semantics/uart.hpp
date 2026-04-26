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
template<PeripheralId Id>
struct UartSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrgrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsMrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsBrgrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsThrRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kUeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kM0Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kM1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTdrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRdrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxeIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxneIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTcIsrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxeSrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxneSrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTcSrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRstrxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRsttxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRststaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kParField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kChmodeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCdField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxchrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxchrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRstrxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRsttxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRststaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsUsartModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsUsclksField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsChrlField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsCdField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxemptyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxchrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxchrField = kInvalidFieldRef;
};

template<>
struct UartSemanticTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_st_usart_v3_1;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40013800u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr RuntimeRegisterRef kCr1Register = RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true};
  static constexpr RuntimeRegisterRef kCr2Register = RuntimeRegisterRef{RegisterId::register_usart1_cr2, 0x40013800u, 4u, true};
  static constexpr RuntimeRegisterRef kBrrRegister = RuntimeRegisterRef{RegisterId::register_usart1_brr, 0x40013800u, 12u, true};
  static constexpr RuntimeRegisterRef kIsrRegister = RuntimeRegisterRef{RegisterId::register_usart1_isr, 0x40013800u, 28u, true};
  static constexpr RuntimeRegisterRef kRdrRegister = RuntimeRegisterRef{RegisterId::register_usart1_rdr, 0x40013800u, 36u, true};
  static constexpr RuntimeRegisterRef kTdrRegister = RuntimeRegisterRef{RegisterId::register_usart1_tdr, 0x40013800u, 40u, true};
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kMrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrgrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsCrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsMrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsBrgrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUsThrRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kUeField = RuntimeFieldRef{FieldId::field_usart1_cr1_ue, RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kReField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kTeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kPceField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kPsField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kM0Field = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kM1Field = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_cr1, 0x40013800u, 0u, true}, 28u, 1u, true};
  static constexpr RuntimeFieldRef kMField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_cr2, 0x40013800u, 4u, true}, 12u, 2u, true};
  static constexpr RuntimeFieldRef kTdrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_tdr, 0x40013800u, 40u, true}, 0u, 9u, true};
  static constexpr RuntimeFieldRef kRdrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_rdr, 0x40013800u, 36u, true}, 0u, 9u, true};
  static constexpr RuntimeFieldRef kTxeIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_isr, 0x40013800u, 28u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kRxneIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_isr, 0x40013800u, 28u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTcIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_usart1_isr, 0x40013800u, 28u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kTxeSrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxneSrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTcSrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRstrxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRsttxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRststaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kParField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kChmodeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCdField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxemptyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxchrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxchrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRstrxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRsttxField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxdisField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRststaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsUsartModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsUsclksField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsChrlField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsCdField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxenField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxrdyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxemptyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsTxchrField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUsRxchrField = kInvalidFieldRef;
};

inline constexpr std::array<PeripheralId, 1> kUartSemanticPeripherals = {{
  PeripheralId::USART1,
}};
}
}
}
}
}
}
}
