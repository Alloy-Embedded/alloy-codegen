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
struct CanSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kHasFlexibleDataRate = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kNominalTimingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDataTimingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTestRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kErrorCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferAddRequestRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferPendingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxEventFifoConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxEventFifoStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxEventFifoAckRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kConfigEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRestrictedOperationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRestrictedOperationAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBusMonitorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFdOperationEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBitRateSwitchEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalTimeSeg1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalTimeSeg2Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalSyncJumpWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataTimeSeg1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataTimeSeg2Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataSyncJumpWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0FillLevelField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0GetIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0MessageLostField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0AckIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxFifoQueuePutIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxFifoQueueFreeLevelField = kInvalidFieldRef;
  static constexpr RuntimeIndexedFieldRef kTxBufferAddRequestPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kTxBufferPendingPattern = kInvalidIndexedFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct CanSemanticTraits<PeripheralId::MCAN0> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_microchip_mcan_n;
  static constexpr bool kHasFlexibleDataRate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true};
  static constexpr RuntimeRegisterRef kNominalTimingRegister = RuntimeRegisterRef{RegisterId::register_mcan0_nbtp, 0x40030000u, 28u, true};
  static constexpr RuntimeRegisterRef kDataTimingRegister = RuntimeRegisterRef{RegisterId::register_mcan0_dbtp, 0x40030000u, 12u, true};
  static constexpr RuntimeRegisterRef kTestRegister = RuntimeRegisterRef{RegisterId::register_mcan0_test, 0x40030000u, 16u, true};
  static constexpr RuntimeRegisterRef kErrorCounterRegister = RuntimeRegisterRef{RegisterId::register_mcan0_ecr, 0x40030000u, 64u, true};
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = RuntimeRegisterRef{RegisterId::register_mcan0_psr, 0x40030000u, 68u, true};
  static constexpr RuntimeRegisterRef kInterruptRegister = RuntimeRegisterRef{RegisterId::register_mcan0_ir, 0x40030000u, 80u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_mcan0_ie, 0x40030000u, 84u, true};
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = RuntimeRegisterRef{RegisterId::register_mcan0_ils, 0x40030000u, 88u, true};
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = RuntimeRegisterRef{RegisterId::register_mcan0_ile, 0x40030000u, 92u, true};
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = RuntimeRegisterRef{RegisterId::register_mcan0_gfc, 0x40030000u, 128u, true};
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan0_sidfc, 0x40030000u, 132u, true};
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan0_xidfc, 0x40030000u, 136u, true};
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = RuntimeRegisterRef{RegisterId::register_mcan0_xidam, 0x40030000u, 144u, true};
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan0_rxf0c, 0x40030000u, 160u, true};
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = RuntimeRegisterRef{RegisterId::register_mcan0_rxf0s, 0x40030000u, 164u, true};
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = RuntimeRegisterRef{RegisterId::register_mcan0_rxf0a, 0x40030000u, 168u, true};
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan0_txbc, 0x40030000u, 192u, true};
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = RuntimeRegisterRef{RegisterId::register_mcan0_txfqs, 0x40030000u, 196u, true};
  static constexpr RuntimeRegisterRef kTxBufferAddRequestRegister = RuntimeRegisterRef{RegisterId::register_mcan0_txbar, 0x40030000u, 208u, true};
  static constexpr RuntimeRegisterRef kTxBufferPendingRegister = RuntimeRegisterRef{RegisterId::register_mcan0_txbrp, 0x40030000u, 204u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan0_txefc, 0x40030000u, 240u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoStatusRegister = RuntimeRegisterRef{RegisterId::register_mcan0_txefs, 0x40030000u, 244u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoAckRegister = RuntimeRegisterRef{RegisterId::register_mcan0_txefa, 0x40030000u, 248u, true};
  static constexpr RuntimeFieldRef kInitField = RuntimeFieldRef{FieldId::field_mcan0_cccr_init, RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kConfigEnableField = RuntimeFieldRef{FieldId::field_mcan0_cccr_cce, RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRestrictedOperationField = RuntimeFieldRef{FieldId::field_mcan0_cccr_csr, RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kRestrictedOperationAckField = RuntimeFieldRef{FieldId::field_mcan0_cccr_csa, RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kBusMonitorField = RuntimeFieldRef{FieldId::field_mcan0_cccr_asm, RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kFdOperationEnableField = RuntimeFieldRef{FieldId::field_mcan0_cccr_fdoe, RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kBitRateSwitchEnableField = RuntimeFieldRef{FieldId::field_mcan0_cccr_brse, RuntimeRegisterRef{RegisterId::register_mcan0_cccr, 0x40030000u, 24u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kNominalPrescalerField = RuntimeFieldRef{FieldId::field_mcan0_nbtp_nbrp, RuntimeRegisterRef{RegisterId::register_mcan0_nbtp, 0x40030000u, 28u, true}, 16u, 9u, true};
  static constexpr RuntimeFieldRef kNominalTimeSeg1Field = RuntimeFieldRef{FieldId::field_mcan0_nbtp_ntseg1, RuntimeRegisterRef{RegisterId::register_mcan0_nbtp, 0x40030000u, 28u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kNominalTimeSeg2Field = RuntimeFieldRef{FieldId::field_mcan0_nbtp_ntseg2, RuntimeRegisterRef{RegisterId::register_mcan0_nbtp, 0x40030000u, 28u, true}, 0u, 7u, true};
  static constexpr RuntimeFieldRef kNominalSyncJumpWidthField = RuntimeFieldRef{FieldId::field_mcan0_nbtp_nsjw, RuntimeRegisterRef{RegisterId::register_mcan0_nbtp, 0x40030000u, 28u, true}, 25u, 7u, true};
  static constexpr RuntimeFieldRef kDataPrescalerField = RuntimeFieldRef{FieldId::field_mcan0_dbtp_dbrp, RuntimeRegisterRef{RegisterId::register_mcan0_dbtp, 0x40030000u, 12u, true}, 16u, 5u, true};
  static constexpr RuntimeFieldRef kDataTimeSeg1Field = RuntimeFieldRef{FieldId::field_mcan0_dbtp_dtseg1, RuntimeRegisterRef{RegisterId::register_mcan0_dbtp, 0x40030000u, 12u, true}, 8u, 5u, true};
  static constexpr RuntimeFieldRef kDataTimeSeg2Field = RuntimeFieldRef{FieldId::field_mcan0_dbtp_dtseg2, RuntimeRegisterRef{RegisterId::register_mcan0_dbtp, 0x40030000u, 12u, true}, 4u, 4u, true};
  static constexpr RuntimeFieldRef kDataSyncJumpWidthField = RuntimeFieldRef{FieldId::field_mcan0_dbtp_dsjw, RuntimeRegisterRef{RegisterId::register_mcan0_dbtp, 0x40030000u, 12u, true}, 0u, 3u, true};
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptField = RuntimeFieldRef{FieldId::field_mcan0_ir_rf0n, RuntimeRegisterRef{RegisterId::register_mcan0_ir, 0x40030000u, 80u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxCompleteInterruptField = RuntimeFieldRef{FieldId::field_mcan0_ir_tc, RuntimeRegisterRef{RegisterId::register_mcan0_ir, 0x40030000u, 80u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptField = RuntimeFieldRef{FieldId::field_mcan0_ir_tfe, RuntimeRegisterRef{RegisterId::register_mcan0_ir, 0x40030000u, 80u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptEnableField = RuntimeFieldRef{FieldId::field_mcan0_ie_rf0ne, RuntimeRegisterRef{RegisterId::register_mcan0_ie, 0x40030000u, 84u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = RuntimeFieldRef{FieldId::field_mcan0_ie_tce, RuntimeRegisterRef{RegisterId::register_mcan0_ie, 0x40030000u, 84u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptEnableField = RuntimeFieldRef{FieldId::field_mcan0_ie_tfee, RuntimeRegisterRef{RegisterId::register_mcan0_ie, 0x40030000u, 84u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kRxFifo0FillLevelField = RuntimeFieldRef{FieldId::field_mcan0_rxf0s_f0fl, RuntimeRegisterRef{RegisterId::register_mcan0_rxf0s, 0x40030000u, 164u, true}, 0u, 7u, true};
  static constexpr RuntimeFieldRef kRxFifo0GetIndexField = RuntimeFieldRef{FieldId::field_mcan0_rxf0s_f0gi, RuntimeRegisterRef{RegisterId::register_mcan0_rxf0s, 0x40030000u, 164u, true}, 8u, 6u, true};
  static constexpr RuntimeFieldRef kRxFifo0MessageLostField = RuntimeFieldRef{FieldId::field_mcan0_rxf0s_rf0l, RuntimeRegisterRef{RegisterId::register_mcan0_rxf0s, 0x40030000u, 164u, true}, 25u, 1u, true};
  static constexpr RuntimeFieldRef kRxFifo0AckIndexField = RuntimeFieldRef{FieldId::field_mcan0_rxf0a_f0ai, RuntimeRegisterRef{RegisterId::register_mcan0_rxf0a, 0x40030000u, 168u, true}, 0u, 6u, true};
  static constexpr RuntimeFieldRef kTxFifoQueuePutIndexField = RuntimeFieldRef{FieldId::field_mcan0_txfqs_tfqpi, RuntimeRegisterRef{RegisterId::register_mcan0_txfqs, 0x40030000u, 196u, true}, 16u, 5u, true};
  static constexpr RuntimeFieldRef kTxFifoQueueFreeLevelField = RuntimeFieldRef{FieldId::field_mcan0_txfqs_tffl, RuntimeRegisterRef{RegisterId::register_mcan0_txfqs, 0x40030000u, 196u, true}, 0u, 6u, true};
  static constexpr RuntimeIndexedFieldRef kTxBufferAddRequestPattern = RuntimeIndexedFieldRef{0x40030000u, 208u, 0u, 0u, 1u, 1u, true};
  static constexpr RuntimeIndexedFieldRef kTxBufferPendingPattern = RuntimeIndexedFieldRef{0x40030000u, 204u, 0u, 0u, 1u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct CanSemanticTraits<PeripheralId::MCAN1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_microchip_mcan_n;
  static constexpr bool kHasFlexibleDataRate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true};
  static constexpr RuntimeRegisterRef kNominalTimingRegister = RuntimeRegisterRef{RegisterId::register_mcan1_nbtp, 0x40034000u, 28u, true};
  static constexpr RuntimeRegisterRef kDataTimingRegister = RuntimeRegisterRef{RegisterId::register_mcan1_dbtp, 0x40034000u, 12u, true};
  static constexpr RuntimeRegisterRef kTestRegister = RuntimeRegisterRef{RegisterId::register_mcan1_test, 0x40034000u, 16u, true};
  static constexpr RuntimeRegisterRef kErrorCounterRegister = RuntimeRegisterRef{RegisterId::register_mcan1_ecr, 0x40034000u, 64u, true};
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = RuntimeRegisterRef{RegisterId::register_mcan1_psr, 0x40034000u, 68u, true};
  static constexpr RuntimeRegisterRef kInterruptRegister = RuntimeRegisterRef{RegisterId::register_mcan1_ir, 0x40034000u, 80u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_mcan1_ie, 0x40034000u, 84u, true};
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = RuntimeRegisterRef{RegisterId::register_mcan1_ils, 0x40034000u, 88u, true};
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = RuntimeRegisterRef{RegisterId::register_mcan1_ile, 0x40034000u, 92u, true};
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = RuntimeRegisterRef{RegisterId::register_mcan1_gfc, 0x40034000u, 128u, true};
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan1_sidfc, 0x40034000u, 132u, true};
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan1_xidfc, 0x40034000u, 136u, true};
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = RuntimeRegisterRef{RegisterId::register_mcan1_xidam, 0x40034000u, 144u, true};
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan1_rxf0c, 0x40034000u, 160u, true};
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = RuntimeRegisterRef{RegisterId::register_mcan1_rxf0s, 0x40034000u, 164u, true};
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = RuntimeRegisterRef{RegisterId::register_mcan1_rxf0a, 0x40034000u, 168u, true};
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan1_txbc, 0x40034000u, 192u, true};
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = RuntimeRegisterRef{RegisterId::register_mcan1_txfqs, 0x40034000u, 196u, true};
  static constexpr RuntimeRegisterRef kTxBufferAddRequestRegister = RuntimeRegisterRef{RegisterId::register_mcan1_txbar, 0x40034000u, 208u, true};
  static constexpr RuntimeRegisterRef kTxBufferPendingRegister = RuntimeRegisterRef{RegisterId::register_mcan1_txbrp, 0x40034000u, 204u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoConfigRegister = RuntimeRegisterRef{RegisterId::register_mcan1_txefc, 0x40034000u, 240u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoStatusRegister = RuntimeRegisterRef{RegisterId::register_mcan1_txefs, 0x40034000u, 244u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoAckRegister = RuntimeRegisterRef{RegisterId::register_mcan1_txefa, 0x40034000u, 248u, true};
  static constexpr RuntimeFieldRef kInitField = RuntimeFieldRef{FieldId::field_mcan1_cccr_init, RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kConfigEnableField = RuntimeFieldRef{FieldId::field_mcan1_cccr_cce, RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRestrictedOperationField = RuntimeFieldRef{FieldId::field_mcan1_cccr_csr, RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kRestrictedOperationAckField = RuntimeFieldRef{FieldId::field_mcan1_cccr_csa, RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kBusMonitorField = RuntimeFieldRef{FieldId::field_mcan1_cccr_asm, RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kFdOperationEnableField = RuntimeFieldRef{FieldId::field_mcan1_cccr_fdoe, RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kBitRateSwitchEnableField = RuntimeFieldRef{FieldId::field_mcan1_cccr_brse, RuntimeRegisterRef{RegisterId::register_mcan1_cccr, 0x40034000u, 24u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kNominalPrescalerField = RuntimeFieldRef{FieldId::field_mcan1_nbtp_nbrp, RuntimeRegisterRef{RegisterId::register_mcan1_nbtp, 0x40034000u, 28u, true}, 16u, 9u, true};
  static constexpr RuntimeFieldRef kNominalTimeSeg1Field = RuntimeFieldRef{FieldId::field_mcan1_nbtp_ntseg1, RuntimeRegisterRef{RegisterId::register_mcan1_nbtp, 0x40034000u, 28u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kNominalTimeSeg2Field = RuntimeFieldRef{FieldId::field_mcan1_nbtp_ntseg2, RuntimeRegisterRef{RegisterId::register_mcan1_nbtp, 0x40034000u, 28u, true}, 0u, 7u, true};
  static constexpr RuntimeFieldRef kNominalSyncJumpWidthField = RuntimeFieldRef{FieldId::field_mcan1_nbtp_nsjw, RuntimeRegisterRef{RegisterId::register_mcan1_nbtp, 0x40034000u, 28u, true}, 25u, 7u, true};
  static constexpr RuntimeFieldRef kDataPrescalerField = RuntimeFieldRef{FieldId::field_mcan1_dbtp_dbrp, RuntimeRegisterRef{RegisterId::register_mcan1_dbtp, 0x40034000u, 12u, true}, 16u, 5u, true};
  static constexpr RuntimeFieldRef kDataTimeSeg1Field = RuntimeFieldRef{FieldId::field_mcan1_dbtp_dtseg1, RuntimeRegisterRef{RegisterId::register_mcan1_dbtp, 0x40034000u, 12u, true}, 8u, 5u, true};
  static constexpr RuntimeFieldRef kDataTimeSeg2Field = RuntimeFieldRef{FieldId::field_mcan1_dbtp_dtseg2, RuntimeRegisterRef{RegisterId::register_mcan1_dbtp, 0x40034000u, 12u, true}, 4u, 4u, true};
  static constexpr RuntimeFieldRef kDataSyncJumpWidthField = RuntimeFieldRef{FieldId::field_mcan1_dbtp_dsjw, RuntimeRegisterRef{RegisterId::register_mcan1_dbtp, 0x40034000u, 12u, true}, 0u, 3u, true};
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptField = RuntimeFieldRef{FieldId::field_mcan1_ir_rf0n, RuntimeRegisterRef{RegisterId::register_mcan1_ir, 0x40034000u, 80u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxCompleteInterruptField = RuntimeFieldRef{FieldId::field_mcan1_ir_tc, RuntimeRegisterRef{RegisterId::register_mcan1_ir, 0x40034000u, 80u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptField = RuntimeFieldRef{FieldId::field_mcan1_ir_tfe, RuntimeRegisterRef{RegisterId::register_mcan1_ir, 0x40034000u, 80u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptEnableField = RuntimeFieldRef{FieldId::field_mcan1_ie_rf0ne, RuntimeRegisterRef{RegisterId::register_mcan1_ie, 0x40034000u, 84u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = RuntimeFieldRef{FieldId::field_mcan1_ie_tce, RuntimeRegisterRef{RegisterId::register_mcan1_ie, 0x40034000u, 84u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptEnableField = RuntimeFieldRef{FieldId::field_mcan1_ie_tfee, RuntimeRegisterRef{RegisterId::register_mcan1_ie, 0x40034000u, 84u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kRxFifo0FillLevelField = RuntimeFieldRef{FieldId::field_mcan1_rxf0s_f0fl, RuntimeRegisterRef{RegisterId::register_mcan1_rxf0s, 0x40034000u, 164u, true}, 0u, 7u, true};
  static constexpr RuntimeFieldRef kRxFifo0GetIndexField = RuntimeFieldRef{FieldId::field_mcan1_rxf0s_f0gi, RuntimeRegisterRef{RegisterId::register_mcan1_rxf0s, 0x40034000u, 164u, true}, 8u, 6u, true};
  static constexpr RuntimeFieldRef kRxFifo0MessageLostField = RuntimeFieldRef{FieldId::field_mcan1_rxf0s_rf0l, RuntimeRegisterRef{RegisterId::register_mcan1_rxf0s, 0x40034000u, 164u, true}, 25u, 1u, true};
  static constexpr RuntimeFieldRef kRxFifo0AckIndexField = RuntimeFieldRef{FieldId::field_mcan1_rxf0a_f0ai, RuntimeRegisterRef{RegisterId::register_mcan1_rxf0a, 0x40034000u, 168u, true}, 0u, 6u, true};
  static constexpr RuntimeFieldRef kTxFifoQueuePutIndexField = RuntimeFieldRef{FieldId::field_mcan1_txfqs_tfqpi, RuntimeRegisterRef{RegisterId::register_mcan1_txfqs, 0x40034000u, 196u, true}, 16u, 5u, true};
  static constexpr RuntimeFieldRef kTxFifoQueueFreeLevelField = RuntimeFieldRef{FieldId::field_mcan1_txfqs_tffl, RuntimeRegisterRef{RegisterId::register_mcan1_txfqs, 0x40034000u, 196u, true}, 0u, 6u, true};
  static constexpr RuntimeIndexedFieldRef kTxBufferAddRequestPattern = RuntimeIndexedFieldRef{0x40034000u, 208u, 0u, 0u, 1u, 1u, true};
  static constexpr RuntimeIndexedFieldRef kTxBufferPendingPattern = RuntimeIndexedFieldRef{0x40034000u, 204u, 0u, 0u, 1u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 2> kCanSemanticPeripherals = {{
  PeripheralId::MCAN0,
  PeripheralId::MCAN1,
}};
}
}
}
}
}
}
}
