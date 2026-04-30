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
template<PeripheralId Id>
struct SpiSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint32_t kMaxClockHz = 0u;
  static constexpr std::int16_t kMosiOutSignal = -1;
  static constexpr std::int16_t kMisoInSignal = -1;
  static constexpr std::int16_t kClkOutSignal = -1;
  static constexpr std::int16_t kCsOutSignal = -1;
  static constexpr bool kHasIomuxFastPath = false;
  static constexpr std::int16_t kIomuxMosiPin = -1;
  static constexpr std::int16_t kIomuxMisoPin = -1;
  static constexpr std::int16_t kIomuxClkPin = -1;
  static constexpr std::int16_t kIomuxCsPin = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint16_t, 0> kBaudPrescalerDivisors = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedFrameSizes = {};
  static constexpr std::array<std::uint8_t, 0> kFifoThresholdBits = {};
  static constexpr bool kSupportsCrc = false;
  static constexpr bool kSupportsTiFrame = false;
  static constexpr bool kSupportsMotorolaFrame = false;
  static constexpr bool kSupportsI2sSubmode = false;
  static constexpr bool kSupportsBidirectional3Wire = false;
  static constexpr bool kSupportsLsbFirst = false;
  static constexpr bool kSupportsNssHwManagement = false;
  static constexpr std::uint8_t kSpiDmaBindingCount = 0u;
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
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
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
};

template<>
struct SpiSemanticTraits<PeripheralId::LPSPI1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_nxp_lpspi_v1;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40394000u;
  static constexpr std::uint32_t kMaxClockHz = 0u;
  static constexpr std::int16_t kMosiOutSignal = -1;
  static constexpr std::int16_t kMisoInSignal = -1;
  static constexpr std::int16_t kClkOutSignal = -1;
  static constexpr std::int16_t kCsOutSignal = -1;
  static constexpr bool kHasIomuxFastPath = false;
  static constexpr std::int16_t kIomuxMosiPin = -1;
  static constexpr std::int16_t kIomuxMisoPin = -1;
  static constexpr std::int16_t kIomuxClkPin = -1;
  static constexpr std::int16_t kIomuxCsPin = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint16_t, 8> kBaudPrescalerDivisors = {{1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u}};
  static constexpr std::array<std::uint8_t, 4> kSupportedFrameSizes = {{4u, 8u, 16u, 32u}};
  static constexpr std::array<std::uint8_t, 0> kFifoThresholdBits = {{}};
  static constexpr bool kSupportsCrc = false;
  static constexpr bool kSupportsTiFrame = false;
  static constexpr bool kSupportsMotorolaFrame = true;
  static constexpr bool kSupportsI2sSubmode = false;
  static constexpr bool kSupportsBidirectional3Wire = false;
  static constexpr bool kSupportsLsbFirst = true;
  static constexpr bool kSupportsNssHwManagement = true;
  static constexpr std::uint8_t kSpiDmaBindingCount = 0u;
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
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
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{32u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_ccm_cbcmr, 0x400FC000u, 24u, true}, 0u, 1u, true};
  static constexpr std::array<KernelClockSourceOption, 2> kKernelClockSourceOptions = {{{KernelClockSource::none, 0u, true}, {KernelClockSource::none, 1u, true}}};
  static constexpr std::uint32_t kKernelMaxClockHz = 60000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_ccm_ccgr1_cg0, RuntimeRegisterRef{RegisterId::register_ccm_ccgr1, 0x400FC000u, 108u, true}, 0u, 2u, true};
};

inline constexpr std::array<PeripheralId, 1> kSpiSemanticPeripherals = {{
  PeripheralId::LPSPI1,
}};

// complete-rp2040-semantics Phase B: per-controller SPI facts.
enum class RuntimeSpiId : std::uint8_t {
  None = 0,
};

template<RuntimeSpiId Id>
struct SpiPeripheralTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint32_t kMaxClockHz = 0u;
  static constexpr std::uint8_t kDreqTx = 0u;
  static constexpr std::uint8_t kDreqRx = 0u;
  static constexpr std::array<std::uint8_t, 0> kValidMosiPins = {};
  static constexpr std::array<std::uint8_t, 0> kValidMisoPins = {};
  static constexpr std::array<std::uint8_t, 0> kValidClkPins = {};
  static constexpr std::array<std::uint8_t, 0> kValidCsPins = {};
};


// add-typed-peripheral-enums-everywhere: typed SpiPrescalerOf per peripheral.
template<PeripheralId Id>
struct SpiPrescalerOf {
  enum class type : std::uint8_t {};
};

template<>
struct SpiPrescalerOf<PeripheralId::LPSPI1> {
  enum class type : std::uint8_t {
    div_1 = 0u,
    div_2 = 1u,
    div_4 = 2u,
    div_8 = 3u,
    div_16 = 4u,
    div_32 = 5u,
    div_64 = 6u,
    div_128 = 7u,
  };
};

template<PeripheralId Id>
using SpiPrescaler = typename SpiPrescalerOf<Id>::type;

// add-typed-peripheral-enums-everywhere: typed SpiFrameSizeOf per peripheral.
template<PeripheralId Id>
struct SpiFrameSizeOf {
  enum class type : std::uint8_t {};
};

template<>
struct SpiFrameSizeOf<PeripheralId::LPSPI1> {
  enum class type : std::uint8_t {
    bits_4 = 0u,
    bits_8 = 1u,
    bits_16 = 2u,
    bits_32 = 3u,
  };
};

template<PeripheralId Id>
using SpiFrameSize = typename SpiFrameSizeOf<Id>::type;

}
}
}
}
}
}
}
