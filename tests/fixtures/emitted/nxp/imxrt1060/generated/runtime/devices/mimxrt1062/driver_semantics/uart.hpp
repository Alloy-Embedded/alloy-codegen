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
struct UartSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 0> kSupportedDataBits = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedParityRaw = {};
  static constexpr std::array<std::uint16_t, 0> kSupportedStopBitsQ8 = {};
  static constexpr std::array<std::uint8_t, 0> kBaudOversamplingOptions = {};
  static constexpr std::array<std::uint8_t, 0> kBaudClockSourceRaw = {};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {};
  static constexpr std::uint32_t kMaxBaudHz = 0u;
  static constexpr bool kSupportsLin = false;
  static constexpr bool kSupportsIrda = false;
  static constexpr bool kSupportsSmartcard = false;
  static constexpr bool kSupportsHalfDuplex = false;
  static constexpr bool kSupportsSynchronous = false;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = false;
  static constexpr std::uint8_t kDmaBindingCount = 0u;
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
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
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
};

template<>
struct UartSemanticTraits<PeripheralId::LPUART1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40184000u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 4> kSupportedDataBits = {{7u, 8u, 9u, 10u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{0u, 1u, 2u}};
  static constexpr std::array<std::uint16_t, 2> kSupportedStopBitsQ8 = {{256u, 512u}};
  static constexpr std::array<std::uint8_t, 2> kBaudOversamplingOptions = {{16u, 32u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 24000000u;
  static constexpr bool kSupportsLin = true;
  static constexpr bool kSupportsIrda = true;
  static constexpr bool kSupportsSmartcard = false;
  static constexpr bool kSupportsHalfDuplex = true;
  static constexpr bool kSupportsSynchronous = false;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = true;
  static constexpr std::uint8_t kDmaBindingCount = 0u;
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
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
  static constexpr RuntimeFieldRef kUeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_ctrl, 0x40184000u, 24u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kReField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_ctrl, 0x40184000u, 24u, true}, 18u, 1u, true};
  static constexpr RuntimeFieldRef kTeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_ctrl, 0x40184000u, 24u, true}, 19u, 1u, true};
  static constexpr RuntimeFieldRef kPceField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_ctrl, 0x40184000u, 24u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kPsField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_ctrl, 0x40184000u, 24u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kM0Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kM1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_ctrl, 0x40184000u, 24u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kStopField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_baud, 0x40184000u, 16u, true}, 13u, 1u, true};
  static constexpr RuntimeFieldRef kTdrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_data, 0x40184000u, 28u, true}, 0u, 10u, true};
  static constexpr RuntimeFieldRef kRdrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_data, 0x40184000u, 28u, true}, 0u, 10u, true};
  static constexpr RuntimeFieldRef kTxeIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_stat, 0x40184000u, 20u, true}, 23u, 1u, true};
  static constexpr RuntimeFieldRef kRxneIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_stat, 0x40184000u, 20u, true}, 21u, 1u, true};
  static constexpr RuntimeFieldRef kTcIsrField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_lpuart1_stat, 0x40184000u, 20u, true}, 22u, 1u, true};
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
  static constexpr RuntimeFieldRef kCdField = RuntimeFieldRef{FieldId::field_lpuart1_baud_sbr, RuntimeRegisterRef{RegisterId::register_lpuart1_baud, 0x40184000u, 16u, true}, 0u, 13u, true};
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
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{20u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_ccm_cscdr1, 0x400FC000u, 36u, true}, 0u, 1u, true};
  static constexpr std::array<KernelClockSourceOption, 2> kKernelClockSourceOptions = {{{KernelClockSource::none, 0u, true}, {KernelClockSource::none, 1u, true}}};
  static constexpr std::uint32_t kKernelMaxClockHz = 80000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_ccm_ccgr5_cg12, RuntimeRegisterRef{RegisterId::register_ccm_ccgr5, 0x400FC000u, 124u, true}, 24u, 2u, true};
};

inline constexpr std::array<PeripheralId, 1> kUartSemanticPeripherals = {{
  PeripheralId::LPUART1,
}};

// complete-rp2040-semantics Phase B: per-controller UART facts.
enum class RuntimeUartId : std::uint8_t {
  None = 0,
};

template<RuntimeUartId Id>
struct UartPeripheralTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kFifoDepth = 0u;
  static constexpr std::uint8_t kDreqTx = 0u;
  static constexpr std::uint8_t kDreqRx = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidTxPins = {};
  static constexpr std::array<std::uint8_t, 0> kValidRxPins = {};
  static constexpr std::array<std::uint8_t, 0> kValidCtsPins = {};
  static constexpr std::array<std::uint8_t, 0> kValidRtsPins = {};
};


// add-typed-peripheral-enums-everywhere: typed UartParityOf per peripheral.
template<PeripheralId Id>
struct UartParityOf {
  enum class type : std::uint8_t {};
};

template<>
struct UartParityOf<PeripheralId::LPUART1> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<PeripheralId Id>
using UartParity = typename UartParityOf<Id>::type;

// add-typed-peripheral-enums-everywhere: typed UartStopBitsOf per peripheral.
template<PeripheralId Id>
struct UartStopBitsOf {
  enum class type : std::uint8_t {};
};

template<>
struct UartStopBitsOf<PeripheralId::LPUART1> {
  enum class type : std::uint8_t {
    one = 0u,
    two = 1u,
  };
};

template<PeripheralId Id>
using UartStopBits = typename UartStopBitsOf<Id>::type;

// add-typed-peripheral-enums-everywhere: typed UartOversamplingOf per peripheral.
template<PeripheralId Id>
struct UartOversamplingOf {
  enum class type : std::uint8_t {};
};

template<>
struct UartOversamplingOf<PeripheralId::LPUART1> {
  enum class type : std::uint8_t {
    over_16x = 0u,
    over_32x = 1u,
  };
};

template<PeripheralId Id>
using UartOversampling = typename UartOversamplingOf<Id>::type;

// add-typed-peripheral-enums-everywhere: typed UartBaudClockSourceOf per peripheral.
template<PeripheralId Id>
struct UartBaudClockSourceOf {
  enum class type : std::uint8_t {};
};

template<>
struct UartBaudClockSourceOf<PeripheralId::LPUART1> {
  enum class type : std::uint8_t {
    lpuart_clk_root = 0u,
  };
};

template<PeripheralId Id>
using UartBaudClockSource = typename UartBaudClockSourceOf<Id>::type;

// add-typed-peripheral-enums-everywhere: typed UartDataBitsOf per peripheral.
template<PeripheralId Id>
struct UartDataBitsOf {
  enum class type : std::uint8_t {};
};

template<>
struct UartDataBitsOf<PeripheralId::LPUART1> {
  enum class type : std::uint8_t {
    bits_7 = 0u,
    bits_8 = 1u,
    bits_9 = 2u,
    bits_10 = 3u,
  };
};

template<PeripheralId Id>
using UartDataBits = typename UartDataBitsOf<Id>::type;

}
}
}
}
}
}
}
