"""CAN / FDCAN driver-semantic emitter.

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.

Covers ATSAM (MCAN), STM32 (bxCAN, FDCAN) and NXP (FlexCAN)
controllers.  Unknown schemas drop in as stub rows so the
artifact contract still emits a specialisation.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .common import (
    RuntimeFieldRef,
    RuntimeIndexedFieldRef,
    RuntimeRegisterRef,
    _SemanticContext,
    _context,
    _emit_peripheral_semantics_header,
    _field_ref_expr,
    _indexed_field_ref,
    _indexed_field_ref_expr,
    _invalid_field_ref,
    _invalid_indexed_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_field_ref_any,
    _resolve_register_ref,
    _resolve_register_ref_any,
    _schema_ref_expr,
)

CAN_DRIVER_HEADER = "driver_semantics/can.hpp"


@dataclass(frozen=True, slots=True)
class CanSemanticRow:
    """CAN/FDCAN semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    has_flexible_data_rate: bool
    control_reg: RuntimeRegisterRef
    nominal_timing_reg: RuntimeRegisterRef
    data_timing_reg: RuntimeRegisterRef
    test_reg: RuntimeRegisterRef
    error_counter_reg: RuntimeRegisterRef
    protocol_status_reg: RuntimeRegisterRef
    interrupt_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_line_select_reg: RuntimeRegisterRef
    interrupt_line_enable_reg: RuntimeRegisterRef
    global_filter_reg: RuntimeRegisterRef
    standard_filter_config_reg: RuntimeRegisterRef
    extended_filter_config_reg: RuntimeRegisterRef
    extended_id_mask_reg: RuntimeRegisterRef
    rx_fifo0_config_reg: RuntimeRegisterRef
    rx_fifo0_status_reg: RuntimeRegisterRef
    rx_fifo0_ack_reg: RuntimeRegisterRef
    tx_buffer_config_reg: RuntimeRegisterRef
    tx_fifo_queue_status_reg: RuntimeRegisterRef
    tx_buffer_add_request_reg: RuntimeRegisterRef
    tx_buffer_pending_reg: RuntimeRegisterRef
    tx_event_fifo_config_reg: RuntimeRegisterRef
    tx_event_fifo_status_reg: RuntimeRegisterRef
    tx_event_fifo_ack_reg: RuntimeRegisterRef
    init_field: RuntimeFieldRef
    config_enable_field: RuntimeFieldRef
    restricted_operation_field: RuntimeFieldRef
    restricted_operation_ack_field: RuntimeFieldRef
    bus_monitor_field: RuntimeFieldRef
    fd_operation_enable_field: RuntimeFieldRef
    bit_rate_switch_enable_field: RuntimeFieldRef
    nominal_prescaler_field: RuntimeFieldRef
    nominal_time_seg1_field: RuntimeFieldRef
    nominal_time_seg2_field: RuntimeFieldRef
    nominal_sync_jump_width_field: RuntimeFieldRef
    data_prescaler_field: RuntimeFieldRef
    data_time_seg1_field: RuntimeFieldRef
    data_time_seg2_field: RuntimeFieldRef
    data_sync_jump_width_field: RuntimeFieldRef
    rx_fifo0_new_interrupt_field: RuntimeFieldRef
    tx_complete_interrupt_field: RuntimeFieldRef
    tx_event_fifo_new_interrupt_field: RuntimeFieldRef
    rx_fifo0_new_interrupt_enable_field: RuntimeFieldRef
    tx_complete_interrupt_enable_field: RuntimeFieldRef
    tx_event_fifo_new_interrupt_enable_field: RuntimeFieldRef
    rx_fifo0_fill_level_field: RuntimeFieldRef
    rx_fifo0_get_index_field: RuntimeFieldRef
    rx_fifo0_message_lost_field: RuntimeFieldRef
    rx_fifo0_ack_index_field: RuntimeFieldRef
    tx_fifo_queue_put_index_field: RuntimeFieldRef
    tx_fifo_queue_free_level_field: RuntimeFieldRef
    tx_buffer_add_request_pattern: RuntimeIndexedFieldRef
    tx_buffer_pending_pattern: RuntimeIndexedFieldRef
    # NVIC vector lines (added by ``add-irq-vector-traits``).  CAN / FDCAN
    # commonly carries 2 lines (e.g. FDCAN1_IT0 + FDCAN1_IT1).
    irq_numbers: tuple[int, ...] = ()


def _mcan_register_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    fallback_offset: int,
) -> RuntimeRegisterRef:
    return _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        fallback_offset=fallback_offset,
    )


def _mcan_field_ref(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    register_name: str,
    field_names: tuple[str, ...],
) -> RuntimeFieldRef:
    return _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name=register_name,
        field_names=field_names,
    )


def _mcan_common_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return CanSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_flexible_data_rate=True,
        control_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            fallback_offset=0x18,
        ),
        nominal_timing_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            fallback_offset=0x1C,
        ),
        data_timing_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            fallback_offset=0x0C,
        ),
        test_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TEST",
            fallback_offset=0x10,
        ),
        error_counter_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ECR",
            fallback_offset=0x40,
        ),
        protocol_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PSR",
            fallback_offset=0x44,
        ),
        interrupt_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            fallback_offset=0x50,
        ),
        interrupt_enable_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            fallback_offset=0x54,
        ),
        interrupt_line_select_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ILS",
            fallback_offset=0x58,
        ),
        interrupt_line_enable_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ILE",
            fallback_offset=0x5C,
        ),
        global_filter_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GFC",
            fallback_offset=0x80,
        ),
        standard_filter_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SIDFC",
            fallback_offset=0x84,
        ),
        extended_filter_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="XIDFC",
            fallback_offset=0x88,
        ),
        extended_id_mask_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="XIDAM",
            fallback_offset=0x90,
        ),
        rx_fifo0_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0C",
            fallback_offset=0xA0,
        ),
        rx_fifo0_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            fallback_offset=0xA4,
        ),
        rx_fifo0_ack_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0A",
            fallback_offset=0xA8,
        ),
        tx_buffer_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXBC",
            fallback_offset=0xC0,
        ),
        tx_fifo_queue_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXFQS",
            fallback_offset=0xC4,
        ),
        tx_buffer_add_request_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXBAR",
            fallback_offset=0xD0,
        ),
        tx_buffer_pending_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXBRP",
            fallback_offset=0xCC,
        ),
        tx_event_fifo_config_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXEFC",
            fallback_offset=0xF0,
        ),
        tx_event_fifo_status_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXEFS",
            fallback_offset=0xF4,
        ),
        tx_event_fifo_ack_reg=_mcan_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXEFA",
            fallback_offset=0xF8,
        ),
        init_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("INIT",),
        ),
        config_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("CCE",),
        ),
        restricted_operation_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("CSR",),
        ),
        restricted_operation_ack_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("CSA",),
        ),
        bus_monitor_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("ASM",),
        ),
        fd_operation_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("FDOE",),
        ),
        bit_rate_switch_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CCCR",
            field_names=("BRSE",),
        ),
        nominal_prescaler_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NBRP",),
        ),
        nominal_time_seg1_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NTSEG1",),
        ),
        nominal_time_seg2_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NTSEG2",),
        ),
        nominal_sync_jump_width_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NBTP",
            field_names=("NSJW",),
        ),
        data_prescaler_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DBRP",),
        ),
        data_time_seg1_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DTSEG1",),
        ),
        data_time_seg2_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DTSEG2",),
        ),
        data_sync_jump_width_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DBTP",
            field_names=("DSJW",),
        ),
        rx_fifo0_new_interrupt_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            field_names=("RF0N",),
        ),
        tx_complete_interrupt_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            field_names=("TC",),
        ),
        tx_event_fifo_new_interrupt_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IR",
            field_names=("TFE",),
        ),
        rx_fifo0_new_interrupt_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            field_names=("RF0NE",),
        ),
        tx_complete_interrupt_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            field_names=("TCE",),
        ),
        tx_event_fifo_new_interrupt_enable_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IE",
            field_names=("TFEE", "TFEE0"),
        ),
        rx_fifo0_fill_level_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            field_names=("F0FL",),
        ),
        rx_fifo0_get_index_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            field_names=("F0GI",),
        ),
        rx_fifo0_message_lost_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0S",
            field_names=("RF0L",),
        ),
        rx_fifo0_ack_index_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXF0A",
            field_names=("F0AI",),
        ),
        tx_fifo_queue_put_index_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXFQS",
            field_names=("TFQPI",),
        ),
        tx_fifo_queue_free_level_field=_mcan_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TXFQS",
            field_names=("TFFL",),
        ),
        tx_buffer_add_request_pattern=_indexed_field_ref(
            base_address=peripheral.base_address,
            base_offset_bytes=0xD0,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        tx_buffer_pending_pattern=_indexed_field_ref(
            base_address=peripheral.base_address,
            base_offset_bytes=0xCC,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
    )


def _st_fdcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    return _mcan_common_can_row(
        context,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
    )


def _st_bxcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    return CanSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_flexible_data_rate=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        nominal_timing_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            fallback_offset=0x1C,
        ),
        data_timing_reg=_invalid_register_ref(peripheral.base_address),
        test_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            fallback_offset=0x1C,
        ),
        error_counter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ESR",
            fallback_offset=0x18,
        ),
        protocol_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MSR",
            fallback_offset=0x4,
        ),
        interrupt_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MSR",
            fallback_offset=0x4,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x14,
        ),
        interrupt_line_select_reg=_invalid_register_ref(peripheral.base_address),
        interrupt_line_enable_reg=_invalid_register_ref(peripheral.base_address),
        global_filter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FMR",
            fallback_offset=0x200,
        ),
        standard_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FM1R",
            fallback_offset=0x204,
        ),
        extended_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="FS1R",
            fallback_offset=0x20C,
        ),
        extended_id_mask_reg=_invalid_register_ref(peripheral.base_address),
        rx_fifo0_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            fallback_offset=0x0C,
        ),
        rx_fifo0_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            fallback_offset=0x0C,
        ),
        rx_fifo0_ack_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            fallback_offset=0x0C,
        ),
        tx_buffer_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            fallback_offset=0x08,
        ),
        tx_fifo_queue_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            fallback_offset=0x08,
        ),
        tx_buffer_add_request_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TI0R",
            fallback_offset=0x180,
        ),
        tx_buffer_pending_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_config_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_status_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_ack_reg=_invalid_register_ref(peripheral.base_address),
        init_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("INRQ",),
        ),
        config_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("INRQ",),
        ),
        restricted_operation_field=_invalid_field_ref(peripheral.base_address),
        restricted_operation_ack_field=_invalid_field_ref(peripheral.base_address),
        bus_monitor_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("SILM",),
        ),
        fd_operation_enable_field=_invalid_field_ref(peripheral.base_address),
        bit_rate_switch_enable_field=_invalid_field_ref(peripheral.base_address),
        nominal_prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("BRP",),
        ),
        nominal_time_seg1_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("TS1",),
        ),
        nominal_time_seg2_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("TS2",),
        ),
        nominal_sync_jump_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BTR",
            field_names=("SJW",),
        ),
        data_prescaler_field=_invalid_field_ref(peripheral.base_address),
        data_time_seg1_field=_invalid_field_ref(peripheral.base_address),
        data_time_seg2_field=_invalid_field_ref(peripheral.base_address),
        data_sync_jump_width_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_new_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("FMP0",),
        ),
        tx_complete_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            field_names=("TXOK0",),
        ),
        tx_event_fifo_new_interrupt_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_new_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("FMPIE0",),
        ),
        tx_complete_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TMEIE",),
        ),
        tx_event_fifo_new_interrupt_enable_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_fill_level_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("FMP0",),
        ),
        rx_fifo0_get_index_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_message_lost_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("FOVR0",),
        ),
        rx_fifo0_ack_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RF0R",
            field_names=("RFOM0",),
        ),
        tx_fifo_queue_put_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            field_names=("CODE",),
        ),
        tx_fifo_queue_free_level_field=_invalid_field_ref(peripheral.base_address),
        tx_buffer_add_request_pattern=_indexed_field_ref(
            base_address=peripheral.base_address,
            base_offset_bytes=0x180,
            stride_bytes=0x10,
            bit_offset=0,
            bit_width=1,
        ),
        tx_buffer_pending_pattern=_invalid_indexed_field_ref(peripheral.base_address),
    )


def _microchip_mcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    return _mcan_common_can_row(
        context,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
    )


def _nxp_flexcan_can_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> CanSemanticRow:
    peripheral = context.peripheral_by_name[peripheral_name]
    fden_field = _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="MCR",
        field_names=("FDEN",),
    )
    data_timing_reg = _resolve_register_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="CBT",
    )
    bit_rate_switch_field = _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="CBT",
        field_names=("BTF",),
    )
    has_flexible_data_rate = fden_field.valid or data_timing_reg.valid
    return CanSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_flexible_data_rate=has_flexible_data_rate,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        nominal_timing_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            fallback_offset=0x4,
        ),
        data_timing_reg=data_timing_reg,
        test_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            fallback_offset=0x4,
        ),
        error_counter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ECR",
            fallback_offset=0x1C,
        ),
        protocol_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ESR1",
            fallback_offset=0x20,
        ),
        interrupt_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IFLAG1", "ESR1"),
            fallback_offset=0x30,
        ),
        interrupt_enable_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IMASK1", "CTRL1"),
            fallback_offset=0x28,
        ),
        interrupt_line_select_reg=_invalid_register_ref(peripheral.base_address),
        interrupt_line_enable_reg=_invalid_register_ref(peripheral.base_address),
        global_filter_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXFGMASK",
            fallback_offset=0x48,
        ),
        standard_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXMGMASK",
            fallback_offset=0x10,
        ),
        extended_filter_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RX14MASK",
            fallback_offset=0x14,
        ),
        extended_id_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RX15MASK",
            fallback_offset=0x18,
        ),
        rx_fifo0_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        rx_fifo0_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXFIR",
            fallback_offset=0x4C,
        ),
        rx_fifo0_ack_reg=_invalid_register_ref(peripheral.base_address),
        tx_buffer_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            fallback_offset=0x0,
        ),
        tx_fifo_queue_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFLAG1",
            fallback_offset=0x30,
        ),
        tx_buffer_add_request_reg=_invalid_register_ref(peripheral.base_address),
        tx_buffer_pending_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_config_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_status_reg=_invalid_register_ref(peripheral.base_address),
        tx_event_fifo_ack_reg=_invalid_register_ref(peripheral.base_address),
        init_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("HALT",),
        ),
        config_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("FRZ",),
        ),
        restricted_operation_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("LOM",),
        ),
        restricted_operation_ack_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MCR",
            field_names=("FRZACK",),
        ),
        bus_monitor_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("LOM",),
        ),
        fd_operation_enable_field=fden_field,
        bit_rate_switch_enable_field=bit_rate_switch_field,
        nominal_prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("PRESDIV",),
        ),
        nominal_time_seg1_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("PSEG1",),
        ),
        nominal_time_seg2_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("PSEG2",),
        ),
        nominal_sync_jump_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CTRL1",
            field_names=("RJW",),
        ),
        data_prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("EPRESDIV",),
        ),
        data_time_seg1_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("EPSEG1",),
        ),
        data_time_seg2_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("EPSEG2",),
        ),
        data_sync_jump_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CBT",
            field_names=("ERJW",),
        ),
        rx_fifo0_new_interrupt_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IFLAG1",),
            field_names=("BUF5I", "BUF4TO1I", "BUF4TO0I"),
        ),
        tx_complete_interrupt_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IFLAG1",),
            field_names=("BUF0I", "BUF4TO0I"),
        ),
        tx_event_fifo_new_interrupt_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_new_interrupt_enable_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IMASK1",),
            field_names=("BUF31TO0M", "BUFLM"),
        ),
        tx_complete_interrupt_enable_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=("IMASK1",),
            field_names=("BUF31TO0M", "BUFLM"),
        ),
        tx_event_fifo_new_interrupt_enable_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_fill_level_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_get_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RXFIR",
            field_names=("IDHIT",),
        ),
        rx_fifo0_message_lost_field=_invalid_field_ref(peripheral.base_address),
        rx_fifo0_ack_index_field=_invalid_field_ref(peripheral.base_address),
        tx_fifo_queue_put_index_field=_invalid_field_ref(peripheral.base_address),
        tx_fifo_queue_free_level_field=_invalid_field_ref(peripheral.base_address),
        tx_buffer_add_request_pattern=_invalid_indexed_field_ref(peripheral.base_address),
        tx_buffer_pending_pattern=_invalid_indexed_field_ref(peripheral.base_address),
    )


def _build_can_rows(context: _SemanticContext) -> tuple[CanSemanticRow, ...]:
    rows: list[CanSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("can", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.fdcan.st-") or schema_id.startswith("alloy.can.st-fdcan"):
            rows.append(
                _st_fdcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.can.st-can" or schema_id.startswith("alloy.can.st-bxcan"):
            rows.append(
                _st_bxcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.can.microchip-mcan-"):
            rows.append(
                _microchip_mcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.can.nxp-can"):
            rows.append(
                _nxp_flexcan_can_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
    return tuple(rows)


def _can_specialization_builder(context: _SemanticContext):
    def _build(row: CanSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kNominalTimingRegister": row.nominal_timing_reg,
            "kDataTimingRegister": row.data_timing_reg,
            "kTestRegister": row.test_reg,
            "kErrorCounterRegister": row.error_counter_reg,
            "kProtocolStatusRegister": row.protocol_status_reg,
            "kInterruptRegister": row.interrupt_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptLineSelectRegister": row.interrupt_line_select_reg,
            "kInterruptLineEnableRegister": row.interrupt_line_enable_reg,
            "kGlobalFilterRegister": row.global_filter_reg,
            "kStandardFilterConfigRegister": row.standard_filter_config_reg,
            "kExtendedFilterConfigRegister": row.extended_filter_config_reg,
            "kExtendedIdMaskRegister": row.extended_id_mask_reg,
            "kRxFifo0ConfigRegister": row.rx_fifo0_config_reg,
            "kRxFifo0StatusRegister": row.rx_fifo0_status_reg,
            "kRxFifo0AckRegister": row.rx_fifo0_ack_reg,
            "kTxBufferConfigRegister": row.tx_buffer_config_reg,
            "kTxFifoQueueStatusRegister": row.tx_fifo_queue_status_reg,
            "kTxBufferAddRequestRegister": row.tx_buffer_add_request_reg,
            "kTxBufferPendingRegister": row.tx_buffer_pending_reg,
            "kTxEventFifoConfigRegister": row.tx_event_fifo_config_reg,
            "kTxEventFifoStatusRegister": row.tx_event_fifo_status_reg,
            "kTxEventFifoAckRegister": row.tx_event_fifo_ack_reg,
        }
        field_members = {
            "kInitField": row.init_field,
            "kConfigEnableField": row.config_enable_field,
            "kRestrictedOperationField": row.restricted_operation_field,
            "kRestrictedOperationAckField": row.restricted_operation_ack_field,
            "kBusMonitorField": row.bus_monitor_field,
            "kFdOperationEnableField": row.fd_operation_enable_field,
            "kBitRateSwitchEnableField": row.bit_rate_switch_enable_field,
            "kNominalPrescalerField": row.nominal_prescaler_field,
            "kNominalTimeSeg1Field": row.nominal_time_seg1_field,
            "kNominalTimeSeg2Field": row.nominal_time_seg2_field,
            "kNominalSyncJumpWidthField": row.nominal_sync_jump_width_field,
            "kDataPrescalerField": row.data_prescaler_field,
            "kDataTimeSeg1Field": row.data_time_seg1_field,
            "kDataTimeSeg2Field": row.data_time_seg2_field,
            "kDataSyncJumpWidthField": row.data_sync_jump_width_field,
            "kRxFifo0NewInterruptField": row.rx_fifo0_new_interrupt_field,
            "kTxCompleteInterruptField": row.tx_complete_interrupt_field,
            "kTxEventFifoNewInterruptField": row.tx_event_fifo_new_interrupt_field,
            "kRxFifo0NewInterruptEnableField": row.rx_fifo0_new_interrupt_enable_field,
            "kTxCompleteInterruptEnableField": row.tx_complete_interrupt_enable_field,
            "kTxEventFifoNewInterruptEnableField": row.tx_event_fifo_new_interrupt_enable_field,
            "kRxFifo0FillLevelField": row.rx_fifo0_fill_level_field,
            "kRxFifo0GetIndexField": row.rx_fifo0_get_index_field,
            "kRxFifo0MessageLostField": row.rx_fifo0_message_lost_field,
            "kRxFifo0AckIndexField": row.rx_fifo0_ack_index_field,
            "kTxFifoQueuePutIndexField": row.tx_fifo_queue_put_index_field,
            "kTxFifoQueueFreeLevelField": row.tx_fifo_queue_free_level_field,
        }
        indexed_field_members = {
            "kTxBufferAddRequestPattern": row.tx_buffer_add_request_pattern,
            "kTxBufferPendingPattern": row.tx_buffer_pending_pattern,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            "  static constexpr bool kHasFlexibleDataRate = "
            + ("true" if row.has_flexible_data_rate else "false")
            + ";",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeIndexedFieldRef {name} = {_indexed_field_ref_expr(value)};"
            for name, value in indexed_field_members.items()
        )
        lines.extend(_irq_numbers_lines(row.irq_numbers))
        return lines

    return _build


def emit_runtime_driver_can_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_can_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kHasFlexibleDataRate = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kNominalTimingRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDataTimingRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTestRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kErrorCounterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kProtocolStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kGlobalFilterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = "
        "kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxBufferAddRequestRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxBufferPendingRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxEventFifoConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxEventFifoStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxEventFifoAckRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kConfigEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRestrictedOperationField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRestrictedOperationAckField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBusMonitorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFdOperationEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBitRateSwitchEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalTimeSeg1Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalTimeSeg2Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNominalSyncJumpWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataTimeSeg1Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataTimeSeg2Field = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataSyncJumpWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0NewInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0NewInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptEnableField = "
        "kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0FillLevelField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0GetIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0MessageLostField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxFifo0AckIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxFifoQueuePutIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxFifoQueueFreeLevelField = kInvalidFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTxBufferAddRequestPattern = "
        "kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTxBufferPendingPattern = "
        "kInvalidIndexedFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=CAN_DRIVER_HEADER,
        trait_name="CanSemanticTraits",
        array_name="kCanSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_can_specialization_builder(context),
    )




__all__ = [
    "CAN_DRIVER_HEADER",
    "CanSemanticRow",
    "emit_runtime_driver_can_semantics_header",
]
