"""Ethernet MAC driver-semantic emitter (Microchip GMAC).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .common import (
    RuntimeFieldRef,
    RuntimeRegisterRef,
    UartDmaBindingRow,
    _context,
    _emit_peripheral_semantics_header,
    _enrich_with_dma_bindings,
    _field_ref_expr,
    _invalid_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
    _SemanticContext,
)

ETH_DRIVER_HEADER = "driver_semantics/eth.hpp"


@dataclass(frozen=True, slots=True)
class EthSemanticRow:
    """Ethernet MAC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    supports_mii: bool
    supports_rmii: bool
    has_dma_engine: bool
    has_statistics_counters: bool
    control_reg: RuntimeRegisterRef
    config_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    user_io_reg: RuntimeRegisterRef
    dma_config_reg: RuntimeRegisterRef
    tx_status_reg: RuntimeRegisterRef
    rx_status_reg: RuntimeRegisterRef
    interrupt_status_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    rx_descriptor_base_reg: RuntimeRegisterRef
    tx_descriptor_base_reg: RuntimeRegisterRef
    rx_enable_field: RuntimeFieldRef
    tx_enable_field: RuntimeFieldRef
    management_port_enable_field: RuntimeFieldRef
    clear_statistics_field: RuntimeFieldRef
    write_enable_statistics_field: RuntimeFieldRef
    tx_start_field: RuntimeFieldRef
    speed_field: RuntimeFieldRef
    full_duplex_field: RuntimeFieldRef
    mdc_clock_divider_field: RuntimeFieldRef
    rmii_enable_field: RuntimeFieldRef
    management_done_field: RuntimeFieldRef
    rx_complete_interrupt_field: RuntimeFieldRef
    tx_complete_interrupt_field: RuntimeFieldRef
    rx_complete_interrupt_enable_field: RuntimeFieldRef
    tx_complete_interrupt_enable_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()
    # DMA cross-references (add-peripheral-dma-cross-references).
    dma_bindings: tuple[UartDmaBindingRow, ...] = ()


def _microchip_gmac_eth_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> EthSemanticRow:
    return EthSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_mii=True,
        supports_rmii=True,
        has_dma_engine=True,
        has_statistics_counters=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            fallback_offset=0x0000,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            fallback_offset=0x0004,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NSR",
            fallback_offset=0x0008,
        ),
        user_io_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="UR",
            fallback_offset=0x000C,
        ),
        dma_config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DCFGR",
            fallback_offset=0x0010,
        ),
        tx_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TSR",
            fallback_offset=0x0014,
        ),
        rx_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RSR",
            fallback_offset=0x0020,
        ),
        interrupt_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            fallback_offset=0x0024,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x0028,
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            fallback_offset=0x002C,
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
            fallback_offset=0x0030,
        ),
        rx_descriptor_base_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RBQB",
            fallback_offset=0x0018,
        ),
        tx_descriptor_base_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TBQB",
            fallback_offset=0x001C,
        ),
        rx_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("RXEN",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        tx_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("TXEN",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=3,
            fallback_bit_width=1,
        ),
        management_port_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("MPE",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=4,
            fallback_bit_width=1,
        ),
        clear_statistics_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("CLRSTAT",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=5,
            fallback_bit_width=1,
        ),
        write_enable_statistics_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("WESTAT",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        tx_start_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCR",
            field_names=("TSTART",),
            fallback_register_offset=0x0000,
            fallback_bit_offset=9,
            fallback_bit_width=1,
        ),
        speed_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            field_names=("SPD",),
            fallback_register_offset=0x0004,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        full_duplex_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            field_names=("FD",),
            fallback_register_offset=0x0004,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        mdc_clock_divider_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NCFGR",
            field_names=("CLK",),
            fallback_register_offset=0x0004,
            fallback_bit_offset=10,
            fallback_bit_width=3,
        ),
        rmii_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="UR",
            field_names=("RMII",),
            fallback_register_offset=0x000C,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        management_done_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="NSR",
            field_names=("IDLE",),
            fallback_register_offset=0x0008,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        rx_complete_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            field_names=("RCOMP",),
            fallback_register_offset=0x0024,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        tx_complete_interrupt_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ISR",
            field_names=("TCOMP",),
            fallback_register_offset=0x0024,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        rx_complete_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("RCOMP",),
            fallback_register_offset=0x0028,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        tx_complete_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TCOMP",),
            fallback_register_offset=0x0028,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
    )


def _build_eth_rows(context: _SemanticContext) -> tuple[EthSemanticRow, ...]:
    rows: list[EthSemanticRow] = []
    handled: set[str] = set()
    for peripheral in context.runtime_peripherals_by_class.get("eth", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.gmac.microchip-") or schema_id.startswith(
            "alloy.eth.microchip-"
        ):
            rows.append(
                _microchip_gmac_eth_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            handled.add(peripheral.name)

    # Emit stub rows for ETH peripherals whose schema is not yet implemented so
    # the artifact contract (`EthSemanticTraits<PeripheralId::`) is satisfied.
    for peripheral in context.runtime_peripherals_by_class.get("eth", ()):
        if peripheral.name in handled:
            continue
        base = context.peripheral_by_name[peripheral.name].base_address
        invalid_reg = _invalid_register_ref(base)
        invalid_field = _invalid_field_ref(base)
        rows.append(
            EthSemanticRow(
                peripheral_name=peripheral.name,
                schema_id=peripheral.backend_schema_id or "",
                supports_mii=False,
                supports_rmii=False,
                has_dma_engine=False,
                has_statistics_counters=False,
                control_reg=invalid_reg,
                config_reg=invalid_reg,
                status_reg=invalid_reg,
                user_io_reg=invalid_reg,
                dma_config_reg=invalid_reg,
                tx_status_reg=invalid_reg,
                rx_status_reg=invalid_reg,
                interrupt_status_reg=invalid_reg,
                interrupt_enable_reg=invalid_reg,
                interrupt_disable_reg=invalid_reg,
                interrupt_mask_reg=invalid_reg,
                rx_descriptor_base_reg=invalid_reg,
                tx_descriptor_base_reg=invalid_reg,
                rx_enable_field=invalid_field,
                tx_enable_field=invalid_field,
                management_port_enable_field=invalid_field,
                clear_statistics_field=invalid_field,
                write_enable_statistics_field=invalid_field,
                tx_start_field=invalid_field,
                speed_field=invalid_field,
                full_duplex_field=invalid_field,
                mdc_clock_divider_field=invalid_field,
                rmii_enable_field=invalid_field,
                management_done_field=invalid_field,
                rx_complete_interrupt_field=invalid_field,
                tx_complete_interrupt_field=invalid_field,
                rx_complete_interrupt_enable_field=invalid_field,
                tx_complete_interrupt_enable_field=invalid_field,
                is_stub=True,
            )
        )
    return _enrich_with_dma_bindings(context, tuple(rows), transfer_width_bits=32)  # type: ignore[return-value]


def _eth_specialization_builder(context: _SemanticContext):
    def _build(row: EthSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
                "  static constexpr bool kSupportsMii = false;",
                "  static constexpr bool kSupportsRmii = false;",
                "  static constexpr bool kHasDmaEngine = false;",
                "  static constexpr bool kHasStatisticsCounters = false;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kUserIoRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDmaConfigRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTxStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRxStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRxDescriptorBaseRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTxDescriptorBaseRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kRxEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kManagementPortEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearStatisticsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kWriteEnableStatisticsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxStartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kFullDuplexField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMdcClockDividerField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRmiiEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kManagementDoneField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxCompleteInterruptField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxCompleteInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;",
                *_irq_numbers_lines(row.irq_numbers),
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kConfigRegister": row.config_reg,
            "kStatusRegister": row.status_reg,
            "kUserIoRegister": row.user_io_reg,
            "kDmaConfigRegister": row.dma_config_reg,
            "kTxStatusRegister": row.tx_status_reg,
            "kRxStatusRegister": row.rx_status_reg,
            "kInterruptStatusRegister": row.interrupt_status_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kRxDescriptorBaseRegister": row.rx_descriptor_base_reg,
            "kTxDescriptorBaseRegister": row.tx_descriptor_base_reg,
        }
        field_members = {
            "kRxEnableField": row.rx_enable_field,
            "kTxEnableField": row.tx_enable_field,
            "kManagementPortEnableField": row.management_port_enable_field,
            "kClearStatisticsField": row.clear_statistics_field,
            "kWriteEnableStatisticsField": row.write_enable_statistics_field,
            "kTxStartField": row.tx_start_field,
            "kSpeedField": row.speed_field,
            "kFullDuplexField": row.full_duplex_field,
            "kMdcClockDividerField": row.mdc_clock_divider_field,
            "kRmiiEnableField": row.rmii_enable_field,
            "kManagementDoneField": row.management_done_field,
            "kRxCompleteInterruptField": row.rx_complete_interrupt_field,
            "kTxCompleteInterruptField": row.tx_complete_interrupt_field,
            "kRxCompleteInterruptEnableField": row.rx_complete_interrupt_enable_field,
            "kTxCompleteInterruptEnableField": row.tx_complete_interrupt_enable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kSupportsMii = {'true' if row.supports_mii else 'false'};",
            f"  static constexpr bool kSupportsRmii = {'true' if row.supports_rmii else 'false'};",
            f"  static constexpr bool kHasDmaEngine = {'true' if row.has_dma_engine else 'false'};",
            "  static constexpr bool kHasStatisticsCounters = "
            + ("true" if row.has_statistics_counters else "false")
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
        lines.extend(_irq_numbers_lines(row.irq_numbers))
        return lines

    return _build


def emit_runtime_driver_eth_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_eth_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupportsMii = false;",
        "  static constexpr bool kSupportsRmii = false;",
        "  static constexpr bool kHasDmaEngine = false;",
        "  static constexpr bool kHasStatisticsCounters = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kUserIoRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDmaConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRxDescriptorBaseRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTxDescriptorBaseRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kRxEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kManagementPortEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearStatisticsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWriteEnableStatisticsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFullDuplexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMdcClockDividerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRmiiEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kManagementDoneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxCompleteInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxCompleteInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        # DMA cross-references (add-peripheral-dma-cross-references).
        "  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=ETH_DRIVER_HEADER,
        trait_name="EthSemanticTraits",
        array_name="kEthSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_eth_specialization_builder(context),
    )




__all__ = [
    "ETH_DRIVER_HEADER",
    "EthSemanticRow",
    "emit_runtime_driver_eth_semantics_header",
]
