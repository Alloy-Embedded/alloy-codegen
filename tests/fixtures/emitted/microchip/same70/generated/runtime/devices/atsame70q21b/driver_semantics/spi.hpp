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
struct SpiSemanticTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_microchip_spi_zm;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40008000u;
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
  static constexpr std::array<std::uint8_t, 9> kSupportedFrameSizes = {{8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u}};
  static constexpr std::array<std::uint8_t, 0> kFifoThresholdBits = {{}};
  static constexpr bool kSupportsCrc = false;
  static constexpr bool kSupportsTiFrame = false;
  static constexpr bool kSupportsMotorolaFrame = true;
  static constexpr bool kSupportsI2sSubmode = false;
  static constexpr bool kSupportsBidirectional3Wire = false;
  static constexpr bool kSupportsLsbFirst = false;
  static constexpr bool kSupportsNssHwManagement = true;
  static constexpr std::uint8_t kSpiDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_spi0_rx_xdmac_perid_2, 2u, DmaBindingDirection::Rx, 16u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_spi0_tx_xdmac_perid_1, 1u, DmaBindingDirection::Tx, 16u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = RuntimeRegisterRef{RegisterId::register_spi0_sr, 0x40008000u, 16u, true};
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_spi0_cr, 0x40008000u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::register_spi0_mr, 0x40008000u, 4u, true};
  static constexpr RuntimeRegisterRef kCsrRegister = RuntimeRegisterRef{RegisterId::register_spi0_csr__s, 0x40008000u, 48u, true};
  static constexpr RuntimeRegisterRef kTdrRegister = RuntimeRegisterRef{RegisterId::register_spi0_tdr, 0x40008000u, 12u, true};
  static constexpr RuntimeRegisterRef kRdrRegister = RuntimeRegisterRef{RegisterId::register_spi0_rdr, 0x40008000u, 8u, true};
  static constexpr RuntimeFieldRef kCphaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCpolField = RuntimeFieldRef{FieldId::field_spi0_csr__s_cpol, RuntimeRegisterRef{RegisterId::register_spi0_csr__s, 0x40008000u, 48u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kMstrField = RuntimeFieldRef{FieldId::field_spi0_mr_mstr, RuntimeRegisterRef{RegisterId::register_spi0_mr, 0x40008000u, 4u, true}, 0u, 1u, true};
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
  static constexpr RuntimeFieldRef kSpienField = RuntimeFieldRef{FieldId::field_spi0_cr_spien, RuntimeRegisterRef{RegisterId::register_spi0_cr, 0x40008000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kSpidisField = RuntimeFieldRef{FieldId::field_spi0_cr_spidis, RuntimeRegisterRef{RegisterId::register_spi0_cr, 0x40008000u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kSwrstField = RuntimeFieldRef{FieldId::field_spi0_cr_swrst, RuntimeRegisterRef{RegisterId::register_spi0_cr, 0x40008000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kPsField = RuntimeFieldRef{FieldId::field_spi0_mr_ps, RuntimeRegisterRef{RegisterId::register_spi0_mr, 0x40008000u, 4u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kPcsdecField = RuntimeFieldRef{FieldId::field_spi0_mr_pcsdec, RuntimeRegisterRef{RegisterId::register_spi0_mr, 0x40008000u, 4u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kModfdisField = RuntimeFieldRef{FieldId::field_spi0_mr_modfdis, RuntimeRegisterRef{RegisterId::register_spi0_mr, 0x40008000u, 4u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kPcsField = RuntimeFieldRef{FieldId::field_spi0_mr_pcs, RuntimeRegisterRef{RegisterId::register_spi0_mr, 0x40008000u, 4u, true}, 16u, 4u, true};
  static constexpr RuntimeFieldRef kDlybcsField = RuntimeFieldRef{FieldId::field_spi0_mr_dlybcs, RuntimeRegisterRef{RegisterId::register_spi0_mr, 0x40008000u, 4u, true}, 24u, 8u, true};
  static constexpr RuntimeFieldRef kNcphaField = RuntimeFieldRef{FieldId::field_spi0_csr__s_ncpha, RuntimeRegisterRef{RegisterId::register_spi0_csr__s, 0x40008000u, 48u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kBitsField = RuntimeFieldRef{FieldId::field_spi0_csr__s_bits, RuntimeRegisterRef{RegisterId::register_spi0_csr__s, 0x40008000u, 48u, true}, 4u, 4u, true};
  static constexpr RuntimeFieldRef kScbrField = RuntimeFieldRef{FieldId::field_spi0_csr__s_scbr, RuntimeRegisterRef{RegisterId::register_spi0_csr__s, 0x40008000u, 48u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kDlybsField = RuntimeFieldRef{FieldId::field_spi0_csr__s_dlybs, RuntimeRegisterRef{RegisterId::register_spi0_csr__s, 0x40008000u, 48u, true}, 16u, 8u, true};
  static constexpr RuntimeFieldRef kDlybctField = RuntimeFieldRef{FieldId::field_spi0_csr__s_dlybct, RuntimeRegisterRef{RegisterId::register_spi0_csr__s, 0x40008000u, 48u, true}, 24u, 8u, true};
  static constexpr RuntimeFieldRef kTdreField = RuntimeFieldRef{FieldId::field_spi0_sr_tdre, RuntimeRegisterRef{RegisterId::register_spi0_sr, 0x40008000u, 16u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRdrfField = RuntimeFieldRef{FieldId::field_spi0_sr_rdrf, RuntimeRegisterRef{RegisterId::register_spi0_sr, 0x40008000u, 16u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxemptyField = RuntimeFieldRef{FieldId::field_spi0_sr_txempty, RuntimeRegisterRef{RegisterId::register_spi0_sr, 0x40008000u, 16u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTdField = RuntimeFieldRef{FieldId::field_spi0_tdr_td, RuntimeRegisterRef{RegisterId::register_spi0_tdr, 0x40008000u, 12u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kTdrPcsField = RuntimeFieldRef{FieldId::field_spi0_tdr_pcs, RuntimeRegisterRef{RegisterId::register_spi0_tdr, 0x40008000u, 12u, true}, 16u, 4u, true};
  static constexpr RuntimeFieldRef kRdField = RuntimeFieldRef{FieldId::field_spi0_rdr_rd, RuntimeRegisterRef{RegisterId::register_spi0_rdr, 0x40008000u, 8u, true}, 0u, 16u, true};
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{21u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer0_pid21, RuntimeRegisterRef{RegisterId::register_pmc_pcer0, 0x400E0600u, 16u, true}, 21u, 1u, true};
};

template<>
struct SpiSemanticTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_microchip_spi_zm;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40058000u;
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
  static constexpr std::array<std::uint8_t, 9> kSupportedFrameSizes = {{8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u}};
  static constexpr std::array<std::uint8_t, 0> kFifoThresholdBits = {{}};
  static constexpr bool kSupportsCrc = false;
  static constexpr bool kSupportsTiFrame = false;
  static constexpr bool kSupportsMotorolaFrame = true;
  static constexpr bool kSupportsI2sSubmode = false;
  static constexpr bool kSupportsBidirectional3Wire = false;
  static constexpr bool kSupportsLsbFirst = false;
  static constexpr bool kSupportsNssHwManagement = true;
  static constexpr std::uint8_t kSpiDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_spi1_rx_xdmac_perid_4, 4u, DmaBindingDirection::Rx, 16u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_spi1_tx_xdmac_perid_3, 3u, DmaBindingDirection::Tx, 16u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = RuntimeRegisterRef{RegisterId::register_spi1_sr, 0x40058000u, 16u, true};
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_spi1_cr, 0x40058000u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::register_spi1_mr, 0x40058000u, 4u, true};
  static constexpr RuntimeRegisterRef kCsrRegister = RuntimeRegisterRef{RegisterId::register_spi1_csr__s, 0x40058000u, 48u, true};
  static constexpr RuntimeRegisterRef kTdrRegister = RuntimeRegisterRef{RegisterId::register_spi1_tdr, 0x40058000u, 12u, true};
  static constexpr RuntimeRegisterRef kRdrRegister = RuntimeRegisterRef{RegisterId::register_spi1_rdr, 0x40058000u, 8u, true};
  static constexpr RuntimeFieldRef kCphaField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCpolField = RuntimeFieldRef{FieldId::field_spi1_csr__s_cpol, RuntimeRegisterRef{RegisterId::register_spi1_csr__s, 0x40058000u, 48u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kMstrField = RuntimeFieldRef{FieldId::field_spi1_mr_mstr, RuntimeRegisterRef{RegisterId::register_spi1_mr, 0x40058000u, 4u, true}, 0u, 1u, true};
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
  static constexpr RuntimeFieldRef kSpienField = RuntimeFieldRef{FieldId::field_spi1_cr_spien, RuntimeRegisterRef{RegisterId::register_spi1_cr, 0x40058000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kSpidisField = RuntimeFieldRef{FieldId::field_spi1_cr_spidis, RuntimeRegisterRef{RegisterId::register_spi1_cr, 0x40058000u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kSwrstField = RuntimeFieldRef{FieldId::field_spi1_cr_swrst, RuntimeRegisterRef{RegisterId::register_spi1_cr, 0x40058000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kPsField = RuntimeFieldRef{FieldId::field_spi1_mr_ps, RuntimeRegisterRef{RegisterId::register_spi1_mr, 0x40058000u, 4u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kPcsdecField = RuntimeFieldRef{FieldId::field_spi1_mr_pcsdec, RuntimeRegisterRef{RegisterId::register_spi1_mr, 0x40058000u, 4u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kModfdisField = RuntimeFieldRef{FieldId::field_spi1_mr_modfdis, RuntimeRegisterRef{RegisterId::register_spi1_mr, 0x40058000u, 4u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kPcsField = RuntimeFieldRef{FieldId::field_spi1_mr_pcs, RuntimeRegisterRef{RegisterId::register_spi1_mr, 0x40058000u, 4u, true}, 16u, 4u, true};
  static constexpr RuntimeFieldRef kDlybcsField = RuntimeFieldRef{FieldId::field_spi1_mr_dlybcs, RuntimeRegisterRef{RegisterId::register_spi1_mr, 0x40058000u, 4u, true}, 24u, 8u, true};
  static constexpr RuntimeFieldRef kNcphaField = RuntimeFieldRef{FieldId::field_spi1_csr__s_ncpha, RuntimeRegisterRef{RegisterId::register_spi1_csr__s, 0x40058000u, 48u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kBitsField = RuntimeFieldRef{FieldId::field_spi1_csr__s_bits, RuntimeRegisterRef{RegisterId::register_spi1_csr__s, 0x40058000u, 48u, true}, 4u, 4u, true};
  static constexpr RuntimeFieldRef kScbrField = RuntimeFieldRef{FieldId::field_spi1_csr__s_scbr, RuntimeRegisterRef{RegisterId::register_spi1_csr__s, 0x40058000u, 48u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kDlybsField = RuntimeFieldRef{FieldId::field_spi1_csr__s_dlybs, RuntimeRegisterRef{RegisterId::register_spi1_csr__s, 0x40058000u, 48u, true}, 16u, 8u, true};
  static constexpr RuntimeFieldRef kDlybctField = RuntimeFieldRef{FieldId::field_spi1_csr__s_dlybct, RuntimeRegisterRef{RegisterId::register_spi1_csr__s, 0x40058000u, 48u, true}, 24u, 8u, true};
  static constexpr RuntimeFieldRef kTdreField = RuntimeFieldRef{FieldId::field_spi1_sr_tdre, RuntimeRegisterRef{RegisterId::register_spi1_sr, 0x40058000u, 16u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRdrfField = RuntimeFieldRef{FieldId::field_spi1_sr_rdrf, RuntimeRegisterRef{RegisterId::register_spi1_sr, 0x40058000u, 16u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxemptyField = RuntimeFieldRef{FieldId::field_spi1_sr_txempty, RuntimeRegisterRef{RegisterId::register_spi1_sr, 0x40058000u, 16u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTdField = RuntimeFieldRef{FieldId::field_spi1_tdr_td, RuntimeRegisterRef{RegisterId::register_spi1_tdr, 0x40058000u, 12u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kTdrPcsField = RuntimeFieldRef{FieldId::field_spi1_tdr_pcs, RuntimeRegisterRef{RegisterId::register_spi1_tdr, 0x40058000u, 12u, true}, 16u, 4u, true};
  static constexpr RuntimeFieldRef kRdField = RuntimeFieldRef{FieldId::field_spi1_rdr_rd, RuntimeRegisterRef{RegisterId::register_spi1_rdr, 0x40058000u, 8u, true}, 0u, 16u, true};
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{42u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer1_pid42, RuntimeRegisterRef{RegisterId::register_pmc_pcer1, 0x400E0600u, 256u, true}, 10u, 1u, true};
};

inline constexpr std::array<PeripheralId, 2> kSpiSemanticPeripherals = {{
  PeripheralId::SPI0,
  PeripheralId::SPI1,
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
struct SpiPrescalerOf<PeripheralId::SPI0> {
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

template<>
struct SpiPrescalerOf<PeripheralId::SPI1> {
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
struct SpiFrameSizeOf<PeripheralId::SPI0> {
  enum class type : std::uint8_t {
    bits_8 = 0u,
    bits_9 = 1u,
    bits_10 = 2u,
    bits_11 = 3u,
    bits_12 = 4u,
    bits_13 = 5u,
    bits_14 = 6u,
    bits_15 = 7u,
    bits_16 = 8u,
  };
};

template<>
struct SpiFrameSizeOf<PeripheralId::SPI1> {
  enum class type : std::uint8_t {
    bits_8 = 0u,
    bits_9 = 1u,
    bits_10 = 2u,
    bits_11 = 3u,
    bits_12 = 4u,
    bits_13 = 5u,
    bits_14 = 6u,
    bits_15 = 7u,
    bits_16 = 8u,
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
