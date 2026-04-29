"""SDMMC driver-semantic emitter (Microchip HSMCI).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from ..runtime_lite_emission import (
    _runtime_lite_dma_bindings,
)

from .common import (
    KernelClockSourceOption,
    RuntimeFieldRef,
    RuntimeRegisterRef,
    _SemanticContext,
    _context,
    _emit_peripheral_semantics_header,
    _enrich_with_dma_bindings,
    _field_ref_expr,
    _irq_numbers_lines,
    _kernel_clock_lines,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
)

SDMMC_DRIVER_HEADER = "driver_semantics/sdmmc.hpp"


@dataclass(frozen=True, slots=True)
class SdmmcSemanticRow:
    """SD/MMC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    supports_1bit: bool
    supports_4bit: bool
    supports_8bit: bool
    has_dma: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    data_timeout_reg: RuntimeRegisterRef
    sd_card_reg: RuntimeRegisterRef
    argument_reg: RuntimeRegisterRef
    command_reg: RuntimeRegisterRef
    block_reg: RuntimeRegisterRef
    completion_timeout_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    dma_reg: RuntimeRegisterRef
    config_reg: RuntimeRegisterRef
    read_data_reg: RuntimeRegisterRef
    write_data_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    power_save_enable_field: RuntimeFieldRef
    power_save_disable_field: RuntimeFieldRef
    software_reset_field: RuntimeFieldRef
    clock_divider_field: RuntimeFieldRef
    power_save_divider_field: RuntimeFieldRef
    read_proof_field: RuntimeFieldRef
    write_proof_field: RuntimeFieldRef
    slot_select_field: RuntimeFieldRef
    bus_width_field: RuntimeFieldRef
    argument_field: RuntimeFieldRef
    command_index_field: RuntimeFieldRef
    response_type_field: RuntimeFieldRef
    special_command_field: RuntimeFieldRef
    open_drain_field: RuntimeFieldRef
    max_latency_field: RuntimeFieldRef
    transfer_command_field: RuntimeFieldRef
    transfer_direction_field: RuntimeFieldRef
    transfer_type_field: RuntimeFieldRef
    sdio_interrupt_command_field: RuntimeFieldRef
    atacs_field: RuntimeFieldRef
    block_count_field: RuntimeFieldRef
    block_length_field: RuntimeFieldRef
    command_ready_field: RuntimeFieldRef
    rx_ready_field: RuntimeFieldRef
    tx_ready_field: RuntimeFieldRef
    transfer_done_field: RuntimeFieldRef
    not_busy_field: RuntimeFieldRef
    dma_enable_field: RuntimeFieldRef
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()
    # Kernel-clock traits (added by ``add-kernel-clock-traits``).
    # ``None`` field-refs render as ``kInvalidFieldRef``.
    kernel_clock_selector_field: RuntimeFieldRef | None = None
    kernel_clock_source_options: tuple[KernelClockSourceOption, ...] = ()
    max_clock_hz: int = 0
    clock_gate_field: RuntimeFieldRef | None = None


def _microchip_hsmci_sdmmc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> SdmmcSemanticRow:
    has_dma = any(
        binding.peripheral == peripheral_name and binding.signal in {"RX", "TX"}
        for binding in _runtime_lite_dma_bindings(context.device)
    )
    return SdmmcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_1bit=True,
        supports_4bit=True,
        supports_8bit=False,
        has_dma=has_dma,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            fallback_offset=0x00,
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            fallback_offset=0x04,
        ),
        data_timeout_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DTOR",
            fallback_offset=0x08,
        ),
        sd_card_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SDCR",
            fallback_offset=0x0C,
        ),
        argument_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ARGR",
            fallback_offset=0x10,
        ),
        command_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            fallback_offset=0x14,
        ),
        block_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BLKR",
            fallback_offset=0x18,
        ),
        completion_timeout_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CSTOR",
            fallback_offset=0x1C,
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            fallback_offset=0x40,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x44,
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            fallback_offset=0x48,
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
            fallback_offset=0x4C,
        ),
        dma_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DMA",
            fallback_offset=0x50,
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFG",
            fallback_offset=0x54,
        ),
        read_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RDR",
            fallback_offset=0x30,
        ),
        write_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TDR",
            fallback_offset=0x34,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("MCIEN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("MCIDIS",),
            fallback_register_offset=0x00,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        power_save_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("PWSEN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        power_save_disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("PWSDIS",),
            fallback_register_offset=0x00,
            fallback_bit_offset=3,
            fallback_bit_width=1,
        ),
        software_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("SWRST",),
            fallback_register_offset=0x00,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        clock_divider_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("CLKDIV",),
            fallback_register_offset=0x04,
            fallback_bit_offset=0,
            fallback_bit_width=8,
        ),
        power_save_divider_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("PWSDIV",),
            fallback_register_offset=0x04,
            fallback_bit_offset=8,
            fallback_bit_width=3,
        ),
        read_proof_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("RDPROOF",),
            fallback_register_offset=0x04,
            fallback_bit_offset=11,
            fallback_bit_width=1,
        ),
        write_proof_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WRPROOF",),
            fallback_register_offset=0x04,
            fallback_bit_offset=12,
            fallback_bit_width=1,
        ),
        slot_select_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SDCR",
            field_names=("SDCSEL",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        bus_width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SDCR",
            field_names=("SDCBUS",),
            fallback_register_offset=0x0C,
            fallback_bit_offset=6,
            fallback_bit_width=2,
        ),
        argument_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ARGR",
            field_names=("ARG",),
            fallback_register_offset=0x10,
            fallback_bit_offset=0,
            fallback_bit_width=32,
        ),
        command_index_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("CMDNB",),
            fallback_register_offset=0x14,
            fallback_bit_offset=0,
            fallback_bit_width=6,
        ),
        response_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("RSPTYP",),
            fallback_register_offset=0x14,
            fallback_bit_offset=6,
            fallback_bit_width=2,
        ),
        special_command_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("SPCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=8,
            fallback_bit_width=3,
        ),
        open_drain_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("OPDCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=11,
            fallback_bit_width=1,
        ),
        max_latency_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("MAXLAT",),
            fallback_register_offset=0x14,
            fallback_bit_offset=12,
            fallback_bit_width=1,
        ),
        transfer_command_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("TRCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=16,
            fallback_bit_width=2,
        ),
        transfer_direction_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("TRDIR",),
            fallback_register_offset=0x14,
            fallback_bit_offset=18,
            fallback_bit_width=1,
        ),
        transfer_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("TRTYP",),
            fallback_register_offset=0x14,
            fallback_bit_offset=19,
            fallback_bit_width=3,
        ),
        sdio_interrupt_command_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("IOSPCMD",),
            fallback_register_offset=0x14,
            fallback_bit_offset=24,
            fallback_bit_width=2,
        ),
        atacs_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CMDR",
            field_names=("ATACS",),
            fallback_register_offset=0x14,
            fallback_bit_offset=26,
            fallback_bit_width=1,
        ),
        block_count_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BLKR",
            field_names=("BCNT",),
            fallback_register_offset=0x18,
            fallback_bit_offset=0,
            fallback_bit_width=16,
        ),
        block_length_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BLKR",
            field_names=("BLKLEN",),
            fallback_register_offset=0x18,
            fallback_bit_offset=16,
            fallback_bit_width=16,
        ),
        command_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("CMDRDY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        rx_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("RXRDY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        tx_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TXRDY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        transfer_done_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("XFRDONE",),
            fallback_register_offset=0x40,
            fallback_bit_offset=27,
            fallback_bit_width=1,
        ),
        not_busy_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("NOTBUSY",),
            fallback_register_offset=0x40,
            fallback_bit_offset=5,
            fallback_bit_width=1,
        ),
        dma_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DMA",
            field_names=("DMAEN",),
            fallback_register_offset=0x50,
            fallback_bit_offset=8,
            fallback_bit_width=1,
        ),
    )


def _build_sdmmc_rows(context: _SemanticContext) -> tuple[SdmmcSemanticRow, ...]:
    rows: list[SdmmcSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("sdmmc", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.hsmci.microchip-"):
            rows.append(
                _microchip_hsmci_sdmmc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
    return _enrich_with_dma_bindings(context, tuple(rows), transfer_width_bits=32)  # type: ignore[return-value]


# _microchip_watchdog_row → runtime_driver/watchdog.py


# _nxp_wdog_watchdog_row → runtime_driver/watchdog.py


# _nxp_rtwdog_watchdog_row → runtime_driver/watchdog.py


# _st_iwdg_watchdog_row → runtime_driver/watchdog.py


# _st_wwdg_watchdog_row → runtime_driver/watchdog.py


# _build_watchdog_rows → runtime_driver/watchdog.py


def _sdmmc_specialization_builder(context: _SemanticContext):
    def _build(row: SdmmcSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kDataTimeoutRegister": row.data_timeout_reg,
            "kSdCardRegister": row.sd_card_reg,
            "kArgumentRegister": row.argument_reg,
            "kCommandRegister": row.command_reg,
            "kBlockRegister": row.block_reg,
            "kCompletionTimeoutRegister": row.completion_timeout_reg,
            "kStatusRegister": row.status_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kDmaRegister": row.dma_reg,
            "kConfigRegister": row.config_reg,
            "kReadDataRegister": row.read_data_reg,
            "kWriteDataRegister": row.write_data_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kPowerSaveEnableField": row.power_save_enable_field,
            "kPowerSaveDisableField": row.power_save_disable_field,
            "kSoftwareResetField": row.software_reset_field,
            "kClockDividerField": row.clock_divider_field,
            "kPowerSaveDividerField": row.power_save_divider_field,
            "kReadProofField": row.read_proof_field,
            "kWriteProofField": row.write_proof_field,
            "kSlotSelectField": row.slot_select_field,
            "kBusWidthField": row.bus_width_field,
            "kArgumentField": row.argument_field,
            "kCommandIndexField": row.command_index_field,
            "kResponseTypeField": row.response_type_field,
            "kSpecialCommandField": row.special_command_field,
            "kOpenDrainField": row.open_drain_field,
            "kMaxLatencyField": row.max_latency_field,
            "kTransferCommandField": row.transfer_command_field,
            "kTransferDirectionField": row.transfer_direction_field,
            "kTransferTypeField": row.transfer_type_field,
            "kSdioInterruptCommandField": row.sdio_interrupt_command_field,
            "kAtacsField": row.atacs_field,
            "kBlockCountField": row.block_count_field,
            "kBlockLengthField": row.block_length_field,
            "kCommandReadyField": row.command_ready_field,
            "kRxReadyField": row.rx_ready_field,
            "kTxReadyField": row.tx_ready_field,
            "kTransferDoneField": row.transfer_done_field,
            "kNotBusyField": row.not_busy_field,
            "kDmaEnableField": row.dma_enable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kSupports1Bit = {'true' if row.supports_1bit else 'false'};",
            f"  static constexpr bool kSupports4Bit = {'true' if row.supports_4bit else 'false'};",
            f"  static constexpr bool kSupports8Bit = {'true' if row.supports_8bit else 'false'};",
            f"  static constexpr bool kHasDma = {'true' if row.has_dma else 'false'};",
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
        lines.extend(
            _kernel_clock_lines(
                selector_field=row.kernel_clock_selector_field,
                options=row.kernel_clock_source_options,
                max_clock_hz=row.max_clock_hz,
                gate_field=row.clock_gate_field,
            )
        )
        return lines

    return _build


def emit_runtime_driver_sdmmc_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_sdmmc_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupports1Bit = false;",
        "  static constexpr bool kSupports4Bit = false;",
        "  static constexpr bool kSupports8Bit = false;",
        "  static constexpr bool kHasDma = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDataTimeoutRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSdCardRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kArgumentRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCommandRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kBlockRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCompletionTimeoutRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDmaRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kReadDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kWriteDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPowerSaveEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPowerSaveDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockDividerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPowerSaveDividerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReadProofField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWriteProofField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSlotSelectField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBusWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArgumentField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCommandIndexField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kResponseTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpecialCommandField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOpenDrainField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMaxLatencyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferCommandField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferDirectionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSdioInterruptCommandField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAtacsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBlockCountField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBlockLengthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCommandReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferDoneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNotBusyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        # Kernel-clock defaults (added by ``add-kernel-clock-traits``).
        "  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;",
        "  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};",
        "  static constexpr std::uint32_t kKernelMaxClockHz = 0u;",
        "  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=SDMMC_DRIVER_HEADER,
        trait_name="SdmmcSemanticTraits",
        array_name="kSdmmcSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_sdmmc_specialization_builder(context),
    )


# emit_runtime_driver_watchdog_semantics_header → runtime_driver/watchdog.py




__all__ = [
    "SDMMC_DRIVER_HEADER",
    "SdmmcSemanticRow",
    "emit_runtime_driver_sdmmc_semantics_header",
]
