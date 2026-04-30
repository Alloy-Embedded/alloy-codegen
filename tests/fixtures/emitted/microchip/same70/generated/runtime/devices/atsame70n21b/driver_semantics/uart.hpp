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
namespace atsame70n21b {
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
struct UartSemanticTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x400E0800u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 1> kSupportedDataBits = {{8u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 1> kSupportedStopBitsQ8 = {{256u}};
  static constexpr std::array<std::uint8_t, 1> kBaudOversamplingOptions = {{16u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = false;
  static constexpr bool kSupportsIrda = false;
  static constexpr bool kSupportsSmartcard = false;
  static constexpr bool kSupportsHalfDuplex = false;
  static constexpr bool kSupportsSynchronous = false;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = false;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart0_rx_xdmac_perid_21, 21u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart0_tx_xdmac_perid_20, 20u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::register_uart0_mr, 0x400E0800u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_uart0_brgr, 0x400E0800u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_uart0_thr, 0x400E0800u, 28u, true};
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
  static constexpr RuntimeFieldRef kRstrxField = RuntimeFieldRef{FieldId::field_uart0_cr_rstrx, RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kRsttxField = RuntimeFieldRef{FieldId::field_uart0_cr_rsttx, RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kRxdisField = RuntimeFieldRef{FieldId::field_uart0_cr_rxdis, RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTxdisField = RuntimeFieldRef{FieldId::field_uart0_cr_txdis, RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kRststaField = RuntimeFieldRef{FieldId::field_uart0_cr_rststa, RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kParField = RuntimeFieldRef{FieldId::field_uart0_mr_par, RuntimeRegisterRef{RegisterId::register_uart0_mr, 0x400E0800u, 4u, true}, 9u, 3u, true};
  static constexpr RuntimeFieldRef kChmodeField = RuntimeFieldRef{FieldId::field_uart0_mr_chmode, RuntimeRegisterRef{RegisterId::register_uart0_mr, 0x400E0800u, 4u, true}, 14u, 2u, true};
  static constexpr RuntimeFieldRef kCdField = RuntimeFieldRef{FieldId::field_uart0_brgr_cd, RuntimeRegisterRef{RegisterId::register_uart0_brgr, 0x400E0800u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kRxenField = RuntimeFieldRef{FieldId::field_uart0_cr_rxen, RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kTxenField = RuntimeFieldRef{FieldId::field_uart0_cr_txen, RuntimeRegisterRef{RegisterId::register_uart0_cr, 0x400E0800u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_uart0_sr_txrdy, RuntimeRegisterRef{RegisterId::register_uart0_sr, 0x400E0800u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_uart0_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_uart0_sr, 0x400E0800u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxemptyField = RuntimeFieldRef{FieldId::field_uart0_sr_txempty, RuntimeRegisterRef{RegisterId::register_uart0_sr, 0x400E0800u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxchrField = RuntimeFieldRef{FieldId::field_uart0_thr_txchr, RuntimeRegisterRef{RegisterId::register_uart0_thr, 0x400E0800u, 28u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxchrField = RuntimeFieldRef{FieldId::field_uart0_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_uart0_rhr, 0x400E0800u, 24u, true}, 0u, 8u, true};
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
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{7u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer0_pid7, RuntimeRegisterRef{RegisterId::register_pmc_pcer0, 0x400E0600u, 16u, true}, 7u, 1u, true};
};

template<>
struct UartSemanticTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x400E0A00u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 1> kSupportedDataBits = {{8u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 1> kSupportedStopBitsQ8 = {{256u}};
  static constexpr std::array<std::uint8_t, 1> kBaudOversamplingOptions = {{16u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = false;
  static constexpr bool kSupportsIrda = false;
  static constexpr bool kSupportsSmartcard = false;
  static constexpr bool kSupportsHalfDuplex = false;
  static constexpr bool kSupportsSynchronous = false;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = false;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart1_rx_xdmac_perid_23, 23u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart1_tx_xdmac_perid_22, 22u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::register_uart1_mr, 0x400E0A00u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_uart1_brgr, 0x400E0A00u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_uart1_thr, 0x400E0A00u, 28u, true};
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
  static constexpr RuntimeFieldRef kRstrxField = RuntimeFieldRef{FieldId::field_uart1_cr_rstrx, RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kRsttxField = RuntimeFieldRef{FieldId::field_uart1_cr_rsttx, RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kRxdisField = RuntimeFieldRef{FieldId::field_uart1_cr_rxdis, RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTxdisField = RuntimeFieldRef{FieldId::field_uart1_cr_txdis, RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kRststaField = RuntimeFieldRef{FieldId::field_uart1_cr_rststa, RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kParField = RuntimeFieldRef{FieldId::field_uart1_mr_par, RuntimeRegisterRef{RegisterId::register_uart1_mr, 0x400E0A00u, 4u, true}, 9u, 3u, true};
  static constexpr RuntimeFieldRef kChmodeField = RuntimeFieldRef{FieldId::field_uart1_mr_chmode, RuntimeRegisterRef{RegisterId::register_uart1_mr, 0x400E0A00u, 4u, true}, 14u, 2u, true};
  static constexpr RuntimeFieldRef kCdField = RuntimeFieldRef{FieldId::field_uart1_brgr_cd, RuntimeRegisterRef{RegisterId::register_uart1_brgr, 0x400E0A00u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kRxenField = RuntimeFieldRef{FieldId::field_uart1_cr_rxen, RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kTxenField = RuntimeFieldRef{FieldId::field_uart1_cr_txen, RuntimeRegisterRef{RegisterId::register_uart1_cr, 0x400E0A00u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_uart1_sr_txrdy, RuntimeRegisterRef{RegisterId::register_uart1_sr, 0x400E0A00u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_uart1_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_uart1_sr, 0x400E0A00u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxemptyField = RuntimeFieldRef{FieldId::field_uart1_sr_txempty, RuntimeRegisterRef{RegisterId::register_uart1_sr, 0x400E0A00u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxchrField = RuntimeFieldRef{FieldId::field_uart1_thr_txchr, RuntimeRegisterRef{RegisterId::register_uart1_thr, 0x400E0A00u, 28u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxchrField = RuntimeFieldRef{FieldId::field_uart1_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_uart1_rhr, 0x400E0A00u, 24u, true}, 0u, 8u, true};
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
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{8u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer0_pid8, RuntimeRegisterRef{RegisterId::register_pmc_pcer0, 0x400E0600u, 16u, true}, 8u, 1u, true};
};

template<>
struct UartSemanticTraits<PeripheralId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1A00u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 1> kSupportedDataBits = {{8u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 1> kSupportedStopBitsQ8 = {{256u}};
  static constexpr std::array<std::uint8_t, 1> kBaudOversamplingOptions = {{16u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = false;
  static constexpr bool kSupportsIrda = false;
  static constexpr bool kSupportsSmartcard = false;
  static constexpr bool kSupportsHalfDuplex = false;
  static constexpr bool kSupportsSynchronous = false;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = false;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart2_rx_xdmac_perid_25, 25u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart2_tx_xdmac_perid_24, 24u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::register_uart2_mr, 0x400E1A00u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_uart2_brgr, 0x400E1A00u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_uart2_thr, 0x400E1A00u, 28u, true};
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
  static constexpr RuntimeFieldRef kRstrxField = RuntimeFieldRef{FieldId::field_uart2_cr_rstrx, RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kRsttxField = RuntimeFieldRef{FieldId::field_uart2_cr_rsttx, RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kRxdisField = RuntimeFieldRef{FieldId::field_uart2_cr_rxdis, RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTxdisField = RuntimeFieldRef{FieldId::field_uart2_cr_txdis, RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kRststaField = RuntimeFieldRef{FieldId::field_uart2_cr_rststa, RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kParField = RuntimeFieldRef{FieldId::field_uart2_mr_par, RuntimeRegisterRef{RegisterId::register_uart2_mr, 0x400E1A00u, 4u, true}, 9u, 3u, true};
  static constexpr RuntimeFieldRef kChmodeField = RuntimeFieldRef{FieldId::field_uart2_mr_chmode, RuntimeRegisterRef{RegisterId::register_uart2_mr, 0x400E1A00u, 4u, true}, 14u, 2u, true};
  static constexpr RuntimeFieldRef kCdField = RuntimeFieldRef{FieldId::field_uart2_brgr_cd, RuntimeRegisterRef{RegisterId::register_uart2_brgr, 0x400E1A00u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kRxenField = RuntimeFieldRef{FieldId::field_uart2_cr_rxen, RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kTxenField = RuntimeFieldRef{FieldId::field_uart2_cr_txen, RuntimeRegisterRef{RegisterId::register_uart2_cr, 0x400E1A00u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_uart2_sr_txrdy, RuntimeRegisterRef{RegisterId::register_uart2_sr, 0x400E1A00u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_uart2_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_uart2_sr, 0x400E1A00u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxemptyField = RuntimeFieldRef{FieldId::field_uart2_sr_txempty, RuntimeRegisterRef{RegisterId::register_uart2_sr, 0x400E1A00u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxchrField = RuntimeFieldRef{FieldId::field_uart2_thr_txchr, RuntimeRegisterRef{RegisterId::register_uart2_thr, 0x400E1A00u, 28u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxchrField = RuntimeFieldRef{FieldId::field_uart2_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_uart2_rhr, 0x400E1A00u, 24u, true}, 0u, 8u, true};
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
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{44u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer1_pid44, RuntimeRegisterRef{RegisterId::register_pmc_pcer1, 0x400E0600u, 256u, true}, 12u, 1u, true};
};

template<>
struct UartSemanticTraits<PeripheralId::UART3> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1C00u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 1> kSupportedDataBits = {{8u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 1> kSupportedStopBitsQ8 = {{256u}};
  static constexpr std::array<std::uint8_t, 1> kBaudOversamplingOptions = {{16u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = false;
  static constexpr bool kSupportsIrda = false;
  static constexpr bool kSupportsSmartcard = false;
  static constexpr bool kSupportsHalfDuplex = false;
  static constexpr bool kSupportsSynchronous = false;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = false;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart3_rx_xdmac_perid_27, 27u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart3_tx_xdmac_perid_26, 26u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::register_uart3_mr, 0x400E1C00u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_uart3_brgr, 0x400E1C00u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_uart3_thr, 0x400E1C00u, 28u, true};
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
  static constexpr RuntimeFieldRef kRstrxField = RuntimeFieldRef{FieldId::field_uart3_cr_rstrx, RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kRsttxField = RuntimeFieldRef{FieldId::field_uart3_cr_rsttx, RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kRxdisField = RuntimeFieldRef{FieldId::field_uart3_cr_rxdis, RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTxdisField = RuntimeFieldRef{FieldId::field_uart3_cr_txdis, RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kRststaField = RuntimeFieldRef{FieldId::field_uart3_cr_rststa, RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kParField = RuntimeFieldRef{FieldId::field_uart3_mr_par, RuntimeRegisterRef{RegisterId::register_uart3_mr, 0x400E1C00u, 4u, true}, 9u, 3u, true};
  static constexpr RuntimeFieldRef kChmodeField = RuntimeFieldRef{FieldId::field_uart3_mr_chmode, RuntimeRegisterRef{RegisterId::register_uart3_mr, 0x400E1C00u, 4u, true}, 14u, 2u, true};
  static constexpr RuntimeFieldRef kCdField = RuntimeFieldRef{FieldId::field_uart3_brgr_cd, RuntimeRegisterRef{RegisterId::register_uart3_brgr, 0x400E1C00u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kRxenField = RuntimeFieldRef{FieldId::field_uart3_cr_rxen, RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kTxenField = RuntimeFieldRef{FieldId::field_uart3_cr_txen, RuntimeRegisterRef{RegisterId::register_uart3_cr, 0x400E1C00u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_uart3_sr_txrdy, RuntimeRegisterRef{RegisterId::register_uart3_sr, 0x400E1C00u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_uart3_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_uart3_sr, 0x400E1C00u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxemptyField = RuntimeFieldRef{FieldId::field_uart3_sr_txempty, RuntimeRegisterRef{RegisterId::register_uart3_sr, 0x400E1C00u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxchrField = RuntimeFieldRef{FieldId::field_uart3_thr_txchr, RuntimeRegisterRef{RegisterId::register_uart3_thr, 0x400E1C00u, 28u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxchrField = RuntimeFieldRef{FieldId::field_uart3_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_uart3_rhr, 0x400E1C00u, 24u, true}, 0u, 8u, true};
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
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{45u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer1_pid45, RuntimeRegisterRef{RegisterId::register_pmc_pcer1, 0x400E0600u, 256u, true}, 13u, 1u, true};
};

template<>
struct UartSemanticTraits<PeripheralId::UART4> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1E00u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 1> kSupportedDataBits = {{8u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 1> kSupportedStopBitsQ8 = {{256u}};
  static constexpr std::array<std::uint8_t, 1> kBaudOversamplingOptions = {{16u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = false;
  static constexpr bool kSupportsIrda = false;
  static constexpr bool kSupportsSmartcard = false;
  static constexpr bool kSupportsHalfDuplex = false;
  static constexpr bool kSupportsSynchronous = false;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = false;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart4_rx_xdmac_perid_29, 29u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_uart4_tx_xdmac_perid_28, 28u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::register_uart4_mr, 0x400E1E00u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_uart4_brgr, 0x400E1E00u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_uart4_thr, 0x400E1E00u, 28u, true};
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
  static constexpr RuntimeFieldRef kRstrxField = RuntimeFieldRef{FieldId::field_uart4_cr_rstrx, RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kRsttxField = RuntimeFieldRef{FieldId::field_uart4_cr_rsttx, RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kRxdisField = RuntimeFieldRef{FieldId::field_uart4_cr_rxdis, RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kTxdisField = RuntimeFieldRef{FieldId::field_uart4_cr_txdis, RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kRststaField = RuntimeFieldRef{FieldId::field_uart4_cr_rststa, RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kParField = RuntimeFieldRef{FieldId::field_uart4_mr_par, RuntimeRegisterRef{RegisterId::register_uart4_mr, 0x400E1E00u, 4u, true}, 9u, 3u, true};
  static constexpr RuntimeFieldRef kChmodeField = RuntimeFieldRef{FieldId::field_uart4_mr_chmode, RuntimeRegisterRef{RegisterId::register_uart4_mr, 0x400E1E00u, 4u, true}, 14u, 2u, true};
  static constexpr RuntimeFieldRef kCdField = RuntimeFieldRef{FieldId::field_uart4_brgr_cd, RuntimeRegisterRef{RegisterId::register_uart4_brgr, 0x400E1E00u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kRxenField = RuntimeFieldRef{FieldId::field_uart4_cr_rxen, RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kTxenField = RuntimeFieldRef{FieldId::field_uart4_cr_txen, RuntimeRegisterRef{RegisterId::register_uart4_cr, 0x400E1E00u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kTxrdyField = RuntimeFieldRef{FieldId::field_uart4_sr_txrdy, RuntimeRegisterRef{RegisterId::register_uart4_sr, 0x400E1E00u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRxrdyField = RuntimeFieldRef{FieldId::field_uart4_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_uart4_sr, 0x400E1E00u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxemptyField = RuntimeFieldRef{FieldId::field_uart4_sr_txempty, RuntimeRegisterRef{RegisterId::register_uart4_sr, 0x400E1E00u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxchrField = RuntimeFieldRef{FieldId::field_uart4_thr_txchr, RuntimeRegisterRef{RegisterId::register_uart4_thr, 0x400E1E00u, 28u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kRxchrField = RuntimeFieldRef{FieldId::field_uart4_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_uart4_rhr, 0x400E1E00u, 24u, true}, 0u, 8u, true};
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
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{46u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer1_pid46, RuntimeRegisterRef{RegisterId::register_pmc_pcer1, 0x400E0600u, 256u, true}, 14u, 1u, true};
};

template<>
struct UartSemanticTraits<PeripheralId::USART0> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_usart_zw;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40024000u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 5> kSupportedDataBits = {{5u, 6u, 7u, 8u, 9u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 3> kSupportedStopBitsQ8 = {{256u, 384u, 512u}};
  static constexpr std::array<std::uint8_t, 2> kBaudOversamplingOptions = {{16u, 8u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = true;
  static constexpr bool kSupportsIrda = true;
  static constexpr bool kSupportsSmartcard = true;
  static constexpr bool kSupportsHalfDuplex = true;
  static constexpr bool kSupportsSynchronous = true;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = true;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_usart0_rx_xdmac_perid_8, 8u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_usart0_tx_xdmac_perid_7, 7u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::none, 0x40024000u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::none, 0x40024000u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_usart0_us_brgr, 0x40024000u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_usart0_us_thr, 0x40024000u, 28u, true};
  static constexpr RuntimeRegisterRef kUsCrRegister = RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true};
  static constexpr RuntimeRegisterRef kUsMrRegister = RuntimeRegisterRef{RegisterId::register_usart0_us_mr_spi_mode, 0x40024000u, 4u, true};
  static constexpr RuntimeRegisterRef kUsBrgrRegister = RuntimeRegisterRef{RegisterId::register_usart0_us_brgr, 0x40024000u, 32u, true};
  static constexpr RuntimeRegisterRef kUsThrRegister = RuntimeRegisterRef{RegisterId::register_usart0_us_thr, 0x40024000u, 28u, true};
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
  static constexpr RuntimeFieldRef kUsRstrxField = RuntimeFieldRef{FieldId::field_usart0_us_cr_lin_mode_rstrx, RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kUsRsttxField = RuntimeFieldRef{FieldId::field_usart0_us_cr_lin_mode_rsttx, RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kUsRxdisField = RuntimeFieldRef{FieldId::field_usart0_us_cr_lin_mode_rxdis, RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxdisField = RuntimeFieldRef{FieldId::field_usart0_us_cr_lin_mode_txdis, RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kUsRststaField = RuntimeFieldRef{FieldId::field_usart0_us_cr_lin_mode_rststa, RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kUsUsartModeField = RuntimeFieldRef{FieldId::field_usart0_us_mr_spi_mode_usart_mode, RuntimeRegisterRef{RegisterId::register_usart0_us_mr_spi_mode, 0x40024000u, 4u, true}, 0u, 4u, true};
  static constexpr RuntimeFieldRef kUsUsclksField = RuntimeFieldRef{FieldId::field_usart0_us_mr_spi_mode_usclks, RuntimeRegisterRef{RegisterId::register_usart0_us_mr_spi_mode, 0x40024000u, 4u, true}, 4u, 2u, true};
  static constexpr RuntimeFieldRef kUsChrlField = RuntimeFieldRef{FieldId::field_usart0_us_mr_spi_mode_chrl, RuntimeRegisterRef{RegisterId::register_usart0_us_mr_spi_mode, 0x40024000u, 4u, true}, 6u, 2u, true};
  static constexpr RuntimeFieldRef kUsCdField = RuntimeFieldRef{FieldId::field_usart0_us_brgr_cd, RuntimeRegisterRef{RegisterId::register_usart0_us_brgr, 0x40024000u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kUsRxenField = RuntimeFieldRef{FieldId::field_usart0_us_cr_lin_mode_rxen, RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxenField = RuntimeFieldRef{FieldId::field_usart0_us_cr_lin_mode_txen, RuntimeRegisterRef{RegisterId::register_usart0_us_cr_lin_mode, 0x40024000u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxrdyField = RuntimeFieldRef{FieldId::field_usart0_us_csr_lin_mode_txrdy, RuntimeRegisterRef{RegisterId::register_usart0_us_csr_lin_mode, 0x40024000u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kUsRxrdyField = RuntimeFieldRef{FieldId::field_usart0_us_csr_lin_mode_rxrdy, RuntimeRegisterRef{RegisterId::register_usart0_us_csr_lin_mode, 0x40024000u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxemptyField = RuntimeFieldRef{FieldId::field_usart0_us_csr_lin_mode_txempty, RuntimeRegisterRef{RegisterId::register_usart0_us_csr_lin_mode, 0x40024000u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxchrField = RuntimeFieldRef{FieldId::field_usart0_us_thr_txchr, RuntimeRegisterRef{RegisterId::register_usart0_us_thr, 0x40024000u, 28u, true}, 0u, 9u, true};
  static constexpr RuntimeFieldRef kUsRxchrField = RuntimeFieldRef{FieldId::field_usart0_us_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_usart0_us_rhr, 0x40024000u, 24u, true}, 0u, 9u, true};
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{13u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer0_pid13, RuntimeRegisterRef{RegisterId::register_pmc_pcer0, 0x400E0600u, 16u, true}, 13u, 1u, true};
};

template<>
struct UartSemanticTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_usart_zw;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x40028000u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 5> kSupportedDataBits = {{5u, 6u, 7u, 8u, 9u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 3> kSupportedStopBitsQ8 = {{256u, 384u, 512u}};
  static constexpr std::array<std::uint8_t, 2> kBaudOversamplingOptions = {{16u, 8u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = true;
  static constexpr bool kSupportsIrda = true;
  static constexpr bool kSupportsSmartcard = true;
  static constexpr bool kSupportsHalfDuplex = true;
  static constexpr bool kSupportsSynchronous = true;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = true;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_usart1_rx_xdmac_perid_10, 10u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_usart1_tx_xdmac_perid_9, 9u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::none, 0x40028000u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::none, 0x40028000u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_usart1_us_brgr, 0x40028000u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_usart1_us_thr, 0x40028000u, 28u, true};
  static constexpr RuntimeRegisterRef kUsCrRegister = RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true};
  static constexpr RuntimeRegisterRef kUsMrRegister = RuntimeRegisterRef{RegisterId::register_usart1_us_mr_spi_mode, 0x40028000u, 4u, true};
  static constexpr RuntimeRegisterRef kUsBrgrRegister = RuntimeRegisterRef{RegisterId::register_usart1_us_brgr, 0x40028000u, 32u, true};
  static constexpr RuntimeRegisterRef kUsThrRegister = RuntimeRegisterRef{RegisterId::register_usart1_us_thr, 0x40028000u, 28u, true};
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
  static constexpr RuntimeFieldRef kUsRstrxField = RuntimeFieldRef{FieldId::field_usart1_us_cr_lin_mode_rstrx, RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kUsRsttxField = RuntimeFieldRef{FieldId::field_usart1_us_cr_lin_mode_rsttx, RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kUsRxdisField = RuntimeFieldRef{FieldId::field_usart1_us_cr_lin_mode_rxdis, RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxdisField = RuntimeFieldRef{FieldId::field_usart1_us_cr_lin_mode_txdis, RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kUsRststaField = RuntimeFieldRef{FieldId::field_usart1_us_cr_lin_mode_rststa, RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kUsUsartModeField = RuntimeFieldRef{FieldId::field_usart1_us_mr_spi_mode_usart_mode, RuntimeRegisterRef{RegisterId::register_usart1_us_mr_spi_mode, 0x40028000u, 4u, true}, 0u, 4u, true};
  static constexpr RuntimeFieldRef kUsUsclksField = RuntimeFieldRef{FieldId::field_usart1_us_mr_spi_mode_usclks, RuntimeRegisterRef{RegisterId::register_usart1_us_mr_spi_mode, 0x40028000u, 4u, true}, 4u, 2u, true};
  static constexpr RuntimeFieldRef kUsChrlField = RuntimeFieldRef{FieldId::field_usart1_us_mr_spi_mode_chrl, RuntimeRegisterRef{RegisterId::register_usart1_us_mr_spi_mode, 0x40028000u, 4u, true}, 6u, 2u, true};
  static constexpr RuntimeFieldRef kUsCdField = RuntimeFieldRef{FieldId::field_usart1_us_brgr_cd, RuntimeRegisterRef{RegisterId::register_usart1_us_brgr, 0x40028000u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kUsRxenField = RuntimeFieldRef{FieldId::field_usart1_us_cr_lin_mode_rxen, RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxenField = RuntimeFieldRef{FieldId::field_usart1_us_cr_lin_mode_txen, RuntimeRegisterRef{RegisterId::register_usart1_us_cr_lin_mode, 0x40028000u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxrdyField = RuntimeFieldRef{FieldId::field_usart1_us_csr_lin_mode_txrdy, RuntimeRegisterRef{RegisterId::register_usart1_us_csr_lin_mode, 0x40028000u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kUsRxrdyField = RuntimeFieldRef{FieldId::field_usart1_us_csr_lin_mode_rxrdy, RuntimeRegisterRef{RegisterId::register_usart1_us_csr_lin_mode, 0x40028000u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxemptyField = RuntimeFieldRef{FieldId::field_usart1_us_csr_lin_mode_txempty, RuntimeRegisterRef{RegisterId::register_usart1_us_csr_lin_mode, 0x40028000u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxchrField = RuntimeFieldRef{FieldId::field_usart1_us_thr_txchr, RuntimeRegisterRef{RegisterId::register_usart1_us_thr, 0x40028000u, 28u, true}, 0u, 9u, true};
  static constexpr RuntimeFieldRef kUsRxchrField = RuntimeFieldRef{FieldId::field_usart1_us_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_usart1_us_rhr, 0x40028000u, 24u, true}, 0u, 9u, true};
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{14u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer0_pid14, RuntimeRegisterRef{RegisterId::register_pmc_pcer0, 0x400E0600u, 16u, true}, 14u, 1u, true};
};

template<>
struct UartSemanticTraits<PeripheralId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_usart_zw;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0x4002C000u;
  static constexpr std::uint16_t kFifoDepth = 0u;
  static constexpr std::int16_t kTxSignalIdx = -1;
  static constexpr std::int16_t kRxSignalIdx = -1;
  static constexpr bool kSupportsDma = false;
  static constexpr std::array<std::uint8_t, 5> kSupportedDataBits = {{5u, 6u, 7u, 8u, 9u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw = {{1u, 2u, 0u}};
  static constexpr std::array<std::uint16_t, 3> kSupportedStopBitsQ8 = {{256u, 384u, 512u}};
  static constexpr std::array<std::uint8_t, 2> kBaudOversamplingOptions = {{16u, 8u}};
  static constexpr std::array<std::uint8_t, 1> kBaudClockSourceRaw = {{0u}};
  static constexpr std::array<std::uint16_t, 0> kFifoTriggerFractionsQ8 = {{}};
  static constexpr std::uint32_t kMaxBaudHz = 8000000u;
  static constexpr bool kSupportsLin = true;
  static constexpr bool kSupportsIrda = true;
  static constexpr bool kSupportsSmartcard = true;
  static constexpr bool kSupportsHalfDuplex = true;
  static constexpr bool kSupportsSynchronous = true;
  static constexpr bool kSupportsAutoBaud = false;
  static constexpr bool kSupportsWakeFromStop = true;
  static constexpr std::uint8_t kDmaBindingCount = 2u;
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_usart2_rx_xdmac_perid_12, 12u, DmaBindingDirection::Rx, 8u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_usart2_tx_xdmac_perid_11, 11u, DmaBindingDirection::Tx, 8u, true},
  }};
  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBrrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kIsrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTdrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCrRegister = RuntimeRegisterRef{RegisterId::none, 0x4002C000u, 0u, true};
  static constexpr RuntimeRegisterRef kMrRegister = RuntimeRegisterRef{RegisterId::none, 0x4002C000u, 4u, true};
  static constexpr RuntimeRegisterRef kBrgrRegister = RuntimeRegisterRef{RegisterId::register_usart2_us_brgr, 0x4002C000u, 32u, true};
  static constexpr RuntimeRegisterRef kThrRegister = RuntimeRegisterRef{RegisterId::register_usart2_us_thr, 0x4002C000u, 28u, true};
  static constexpr RuntimeRegisterRef kUsCrRegister = RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true};
  static constexpr RuntimeRegisterRef kUsMrRegister = RuntimeRegisterRef{RegisterId::register_usart2_us_mr_spi_mode, 0x4002C000u, 4u, true};
  static constexpr RuntimeRegisterRef kUsBrgrRegister = RuntimeRegisterRef{RegisterId::register_usart2_us_brgr, 0x4002C000u, 32u, true};
  static constexpr RuntimeRegisterRef kUsThrRegister = RuntimeRegisterRef{RegisterId::register_usart2_us_thr, 0x4002C000u, 28u, true};
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
  static constexpr RuntimeFieldRef kUsRstrxField = RuntimeFieldRef{FieldId::field_usart2_us_cr_lin_mode_rstrx, RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kUsRsttxField = RuntimeFieldRef{FieldId::field_usart2_us_cr_lin_mode_rsttx, RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kUsRxdisField = RuntimeFieldRef{FieldId::field_usart2_us_cr_lin_mode_rxdis, RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxdisField = RuntimeFieldRef{FieldId::field_usart2_us_cr_lin_mode_txdis, RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kUsRststaField = RuntimeFieldRef{FieldId::field_usart2_us_cr_lin_mode_rststa, RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kUsUsartModeField = RuntimeFieldRef{FieldId::field_usart2_us_mr_spi_mode_usart_mode, RuntimeRegisterRef{RegisterId::register_usart2_us_mr_spi_mode, 0x4002C000u, 4u, true}, 0u, 4u, true};
  static constexpr RuntimeFieldRef kUsUsclksField = RuntimeFieldRef{FieldId::field_usart2_us_mr_spi_mode_usclks, RuntimeRegisterRef{RegisterId::register_usart2_us_mr_spi_mode, 0x4002C000u, 4u, true}, 4u, 2u, true};
  static constexpr RuntimeFieldRef kUsChrlField = RuntimeFieldRef{FieldId::field_usart2_us_mr_spi_mode_chrl, RuntimeRegisterRef{RegisterId::register_usart2_us_mr_spi_mode, 0x4002C000u, 4u, true}, 6u, 2u, true};
  static constexpr RuntimeFieldRef kUsCdField = RuntimeFieldRef{FieldId::field_usart2_us_brgr_cd, RuntimeRegisterRef{RegisterId::register_usart2_us_brgr, 0x4002C000u, 32u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kUsRxenField = RuntimeFieldRef{FieldId::field_usart2_us_cr_lin_mode_rxen, RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxenField = RuntimeFieldRef{FieldId::field_usart2_us_cr_lin_mode_txen, RuntimeRegisterRef{RegisterId::register_usart2_us_cr_lin_mode, 0x4002C000u, 0u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxrdyField = RuntimeFieldRef{FieldId::field_usart2_us_csr_lin_mode_txrdy, RuntimeRegisterRef{RegisterId::register_usart2_us_csr_lin_mode, 0x4002C000u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kUsRxrdyField = RuntimeFieldRef{FieldId::field_usart2_us_csr_lin_mode_rxrdy, RuntimeRegisterRef{RegisterId::register_usart2_us_csr_lin_mode, 0x4002C000u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxemptyField = RuntimeFieldRef{FieldId::field_usart2_us_csr_lin_mode_txempty, RuntimeRegisterRef{RegisterId::register_usart2_us_csr_lin_mode, 0x4002C000u, 20u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kUsTxchrField = RuntimeFieldRef{FieldId::field_usart2_us_thr_txchr, RuntimeRegisterRef{RegisterId::register_usart2_us_thr, 0x4002C000u, 28u, true}, 0u, 9u, true};
  static constexpr RuntimeFieldRef kUsRxchrField = RuntimeFieldRef{FieldId::field_usart2_us_rhr_rxchr, RuntimeRegisterRef{RegisterId::register_usart2_us_rhr, 0x4002C000u, 24u, true}, 0u, 9u, true};
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{15u}};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 150000000u;
  static constexpr RuntimeFieldRef kClockGateField = RuntimeFieldRef{FieldId::field_pmc_pcer0_pid15, RuntimeRegisterRef{RegisterId::register_pmc_pcer0, 0x400E0600u, 16u, true}, 15u, 1u, true};
};

inline constexpr std::array<PeripheralId, 8> kUartSemanticPeripherals = {{
  PeripheralId::UART0,
  PeripheralId::UART1,
  PeripheralId::UART2,
  PeripheralId::UART3,
  PeripheralId::UART4,
  PeripheralId::USART0,
  PeripheralId::USART1,
  PeripheralId::USART2,
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
struct UartParityOf<PeripheralId::UART0> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<>
struct UartParityOf<PeripheralId::UART1> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<>
struct UartParityOf<PeripheralId::UART2> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<>
struct UartParityOf<PeripheralId::UART3> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<>
struct UartParityOf<PeripheralId::UART4> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<>
struct UartParityOf<PeripheralId::USART0> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<>
struct UartParityOf<PeripheralId::USART1> {
  enum class type : std::uint8_t {
    none = 0u,
    even = 1u,
    odd = 2u,
  };
};

template<>
struct UartParityOf<PeripheralId::USART2> {
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
struct UartStopBitsOf<PeripheralId::UART0> {
  enum class type : std::uint8_t {
    one = 0u,
  };
};

template<>
struct UartStopBitsOf<PeripheralId::UART1> {
  enum class type : std::uint8_t {
    one = 0u,
  };
};

template<>
struct UartStopBitsOf<PeripheralId::UART2> {
  enum class type : std::uint8_t {
    one = 0u,
  };
};

template<>
struct UartStopBitsOf<PeripheralId::UART3> {
  enum class type : std::uint8_t {
    one = 0u,
  };
};

template<>
struct UartStopBitsOf<PeripheralId::UART4> {
  enum class type : std::uint8_t {
    one = 0u,
  };
};

template<>
struct UartStopBitsOf<PeripheralId::USART0> {
  enum class type : std::uint8_t {
    one = 0u,
    one_and_half = 1u,
    two = 2u,
  };
};

template<>
struct UartStopBitsOf<PeripheralId::USART1> {
  enum class type : std::uint8_t {
    one = 0u,
    one_and_half = 1u,
    two = 2u,
  };
};

template<>
struct UartStopBitsOf<PeripheralId::USART2> {
  enum class type : std::uint8_t {
    one = 0u,
    one_and_half = 1u,
    two = 2u,
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
struct UartOversamplingOf<PeripheralId::UART0> {
  enum class type : std::uint8_t {
    over_16x = 0u,
  };
};

template<>
struct UartOversamplingOf<PeripheralId::UART1> {
  enum class type : std::uint8_t {
    over_16x = 0u,
  };
};

template<>
struct UartOversamplingOf<PeripheralId::UART2> {
  enum class type : std::uint8_t {
    over_16x = 0u,
  };
};

template<>
struct UartOversamplingOf<PeripheralId::UART3> {
  enum class type : std::uint8_t {
    over_16x = 0u,
  };
};

template<>
struct UartOversamplingOf<PeripheralId::UART4> {
  enum class type : std::uint8_t {
    over_16x = 0u,
  };
};

template<>
struct UartOversamplingOf<PeripheralId::USART0> {
  enum class type : std::uint8_t {
    over_16x = 0u,
    over_8x = 1u,
  };
};

template<>
struct UartOversamplingOf<PeripheralId::USART1> {
  enum class type : std::uint8_t {
    over_16x = 0u,
    over_8x = 1u,
  };
};

template<>
struct UartOversamplingOf<PeripheralId::USART2> {
  enum class type : std::uint8_t {
    over_16x = 0u,
    over_8x = 1u,
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
struct UartBaudClockSourceOf<PeripheralId::UART0> {
  enum class type : std::uint8_t {
    mck = 0u,
  };
};

template<>
struct UartBaudClockSourceOf<PeripheralId::UART1> {
  enum class type : std::uint8_t {
    mck = 0u,
  };
};

template<>
struct UartBaudClockSourceOf<PeripheralId::UART2> {
  enum class type : std::uint8_t {
    mck = 0u,
  };
};

template<>
struct UartBaudClockSourceOf<PeripheralId::UART3> {
  enum class type : std::uint8_t {
    mck = 0u,
  };
};

template<>
struct UartBaudClockSourceOf<PeripheralId::UART4> {
  enum class type : std::uint8_t {
    mck = 0u,
  };
};

template<>
struct UartBaudClockSourceOf<PeripheralId::USART0> {
  enum class type : std::uint8_t {
    mck = 0u,
  };
};

template<>
struct UartBaudClockSourceOf<PeripheralId::USART1> {
  enum class type : std::uint8_t {
    mck = 0u,
  };
};

template<>
struct UartBaudClockSourceOf<PeripheralId::USART2> {
  enum class type : std::uint8_t {
    mck = 0u,
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
struct UartDataBitsOf<PeripheralId::UART0> {
  enum class type : std::uint8_t {
    bits_8 = 0u,
  };
};

template<>
struct UartDataBitsOf<PeripheralId::UART1> {
  enum class type : std::uint8_t {
    bits_8 = 0u,
  };
};

template<>
struct UartDataBitsOf<PeripheralId::UART2> {
  enum class type : std::uint8_t {
    bits_8 = 0u,
  };
};

template<>
struct UartDataBitsOf<PeripheralId::UART3> {
  enum class type : std::uint8_t {
    bits_8 = 0u,
  };
};

template<>
struct UartDataBitsOf<PeripheralId::UART4> {
  enum class type : std::uint8_t {
    bits_8 = 0u,
  };
};

template<>
struct UartDataBitsOf<PeripheralId::USART0> {
  enum class type : std::uint8_t {
    bits_5 = 0u,
    bits_6 = 1u,
    bits_7 = 2u,
    bits_8 = 3u,
    bits_9 = 4u,
  };
};

template<>
struct UartDataBitsOf<PeripheralId::USART1> {
  enum class type : std::uint8_t {
    bits_5 = 0u,
    bits_6 = 1u,
    bits_7 = 2u,
    bits_8 = 3u,
    bits_9 = 4u,
  };
};

template<>
struct UartDataBitsOf<PeripheralId::USART2> {
  enum class type : std::uint8_t {
    bits_5 = 0u,
    bits_6 = 1u,
    bits_7 = 2u,
    bits_8 = 3u,
    bits_9 = 4u,
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
