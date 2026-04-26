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
struct SpiSemanticTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_raspberrypi_rp2040_spi_v1;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x4003C000u;
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
  static constexpr std::array<std::uint16_t, 0> kBaudPrescalerDivisors = {{}};
  static constexpr std::array<std::uint8_t, 0> kSupportedFrameSizes = {{}};
  static constexpr std::array<std::uint8_t, 0> kFifoThresholdBits = {{}};
  static constexpr bool kSupportsCrc = false;
  static constexpr bool kSupportsTiFrame = false;
  static constexpr bool kSupportsMotorolaFrame = false;
  static constexpr bool kSupportsI2sSubmode = false;
  static constexpr bool kSupportsBidirectional3Wire = false;
  static constexpr bool kSupportsLsbFirst = false;
  static constexpr bool kSupportsNssHwManagement = false;
  static constexpr std::uint8_t kSpiDmaBindingCount = 0u;
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
struct SpiSemanticTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_raspberrypi_rp2040_spi_v1;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40040000u;
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
  static constexpr std::array<std::uint16_t, 0> kBaudPrescalerDivisors = {{}};
  static constexpr std::array<std::uint8_t, 0> kSupportedFrameSizes = {{}};
  static constexpr std::array<std::uint8_t, 0> kFifoThresholdBits = {{}};
  static constexpr bool kSupportsCrc = false;
  static constexpr bool kSupportsTiFrame = false;
  static constexpr bool kSupportsMotorolaFrame = false;
  static constexpr bool kSupportsI2sSubmode = false;
  static constexpr bool kSupportsBidirectional3Wire = false;
  static constexpr bool kSupportsLsbFirst = false;
  static constexpr bool kSupportsNssHwManagement = false;
  static constexpr std::uint8_t kSpiDmaBindingCount = 0u;
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

inline constexpr std::array<PeripheralId, 0> kSpiSemanticPeripherals = {};

// complete-rp2040-semantics Phase B: per-controller SPI facts.
enum class RuntimeSpiId : std::uint8_t {
  None = 0,
  SPI0 = 1,
  SPI1 = 2,
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

template<>
struct SpiPeripheralTraits<RuntimeSpiId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x4003c000u;
  static constexpr std::uint32_t kMaxClockHz = 62500000u;
  static constexpr std::uint8_t kDreqTx = 16u;
  static constexpr std::uint8_t kDreqRx = 17u;
  static constexpr std::array<std::uint8_t, 4> kValidMosiPins = {{3u, 7u, 19u, 23u}};
  static constexpr std::array<std::uint8_t, 4> kValidMisoPins = {{0u, 4u, 16u, 20u}};
  static constexpr std::array<std::uint8_t, 4> kValidClkPins = {{2u, 6u, 18u, 22u}};
  static constexpr std::array<std::uint8_t, 4> kValidCsPins = {{1u, 5u, 17u, 21u}};
};

template<>
struct SpiPeripheralTraits<RuntimeSpiId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40040000u;
  static constexpr std::uint32_t kMaxClockHz = 62500000u;
  static constexpr std::uint8_t kDreqTx = 18u;
  static constexpr std::uint8_t kDreqRx = 19u;
  static constexpr std::array<std::uint8_t, 2> kValidMosiPins = {{11u, 15u}};
  static constexpr std::array<std::uint8_t, 3> kValidMisoPins = {{8u, 12u, 24u}};
  static constexpr std::array<std::uint8_t, 2> kValidClkPins = {{10u, 14u}};
  static constexpr std::array<std::uint8_t, 3> kValidCsPins = {{9u, 13u, 25u}};
};

}
}
}
}
}
}
}
