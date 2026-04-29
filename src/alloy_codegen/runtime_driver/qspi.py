"""QSPI / OctoSPI driver-semantic emitter.

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

QSPI_DRIVER_HEADER = "driver_semantics/qspi.hpp"


@dataclass(frozen=True, slots=True)
class QspiSemanticRow:
    """QSPI semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    supports_spi_mode: bool
    supports_memory_mode: bool
    has_scrambling: bool
    has_dma: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    serial_clock_reg: RuntimeRegisterRef
    instruction_address_reg: RuntimeRegisterRef
    instruction_code_reg: RuntimeRegisterRef
    instruction_frame_reg: RuntimeRegisterRef
    scrambling_mode_reg: RuntimeRegisterRef
    scrambling_key_reg: RuntimeRegisterRef
    receive_data_reg: RuntimeRegisterRef
    transmit_data_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    software_reset_field: RuntimeFieldRef
    last_transfer_field: RuntimeFieldRef
    enabled_status_field: RuntimeFieldRef
    serial_memory_mode_field: RuntimeFieldRef
    chip_select_mode_field: RuntimeFieldRef
    bits_per_transfer_field: RuntimeFieldRef
    receive_ready_field: RuntimeFieldRef
    transmit_ready_field: RuntimeFieldRef
    transmit_empty_field: RuntimeFieldRef
    receive_ready_interrupt_enable_field: RuntimeFieldRef
    transmit_ready_interrupt_enable_field: RuntimeFieldRef
    transmit_empty_interrupt_enable_field: RuntimeFieldRef
    serial_clock_baud_rate_field: RuntimeFieldRef
    instruction_field: RuntimeFieldRef
    address_field: RuntimeFieldRef
    width_field: RuntimeFieldRef
    instruction_enable_field: RuntimeFieldRef
    address_enable_field: RuntimeFieldRef
    option_enable_field: RuntimeFieldRef
    data_enable_field: RuntimeFieldRef
    transfer_type_field: RuntimeFieldRef
    continuous_read_mode_field: RuntimeFieldRef
    dummy_cycles_field: RuntimeFieldRef
    scrambling_enable_field: RuntimeFieldRef
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()
    # Kernel-clock traits (added by ``add-kernel-clock-traits``).
    # ``None`` field-refs render as ``kInvalidFieldRef``.
    kernel_clock_selector_field: RuntimeFieldRef | None = None
    kernel_clock_source_options: tuple[KernelClockSourceOption, ...] = ()
    max_clock_hz: int = 0
    clock_gate_field: RuntimeFieldRef | None = None


def _microchip_qspi_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> QspiSemanticRow:
    has_dma = any(
        binding.peripheral == peripheral_name and binding.signal in {"RX", "TX"}
        for binding in _runtime_lite_dma_bindings(context.device)
    )
    return QspiSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        supports_spi_mode=True,
        supports_memory_mode=True,
        has_scrambling=True,
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
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            fallback_offset=0x10,
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            fallback_offset=0x14,
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            fallback_offset=0x18,
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
            fallback_offset=0x1C,
        ),
        serial_clock_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCR",
            fallback_offset=0x20,
        ),
        instruction_address_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IAR",
            fallback_offset=0x30,
        ),
        instruction_code_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ICR",
            fallback_offset=0x34,
        ),
        instruction_frame_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            fallback_offset=0x38,
        ),
        scrambling_mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SMR",
            fallback_offset=0x40,
        ),
        scrambling_key_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SKR",
            fallback_offset=0x44,
        ),
        receive_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RDR",
            fallback_offset=0x08,
        ),
        transmit_data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TDR",
            fallback_offset=0x0C,
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("QSPIEN",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("QSPIDIS",),
            fallback_register_offset=0x00,
            fallback_bit_offset=1,
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
        last_transfer_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("LASTXFER",),
            fallback_register_offset=0x00,
            fallback_bit_offset=24,
            fallback_bit_width=1,
        ),
        enabled_status_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("QSPIENS",),
            fallback_register_offset=0x10,
            fallback_bit_offset=24,
            fallback_bit_width=1,
        ),
        serial_memory_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("SMM",),
            fallback_register_offset=0x04,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        chip_select_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("CSMODE",),
            fallback_register_offset=0x04,
            fallback_bit_offset=4,
            fallback_bit_width=2,
        ),
        bits_per_transfer_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("NBBITS",),
            fallback_register_offset=0x04,
            fallback_bit_offset=8,
            fallback_bit_width=4,
        ),
        receive_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("RDRF",),
            fallback_register_offset=0x10,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        transmit_ready_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TDRE",),
            fallback_register_offset=0x10,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        transmit_empty_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TXEMPTY",),
            fallback_register_offset=0x10,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        receive_ready_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("RDRF",),
            fallback_register_offset=0x14,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        transmit_ready_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TDRE",),
            fallback_register_offset=0x14,
            fallback_bit_offset=1,
            fallback_bit_width=1,
        ),
        transmit_empty_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TXEMPTY",),
            fallback_register_offset=0x14,
            fallback_bit_offset=2,
            fallback_bit_width=1,
        ),
        serial_clock_baud_rate_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCR",
            field_names=("SCBR",),
            fallback_register_offset=0x20,
            fallback_bit_offset=8,
            fallback_bit_width=8,
        ),
        instruction_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ICR",
            field_names=("INST",),
            fallback_register_offset=0x34,
            fallback_bit_offset=0,
            fallback_bit_width=8,
        ),
        address_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IAR",
            field_names=("ADDR",),
            fallback_register_offset=0x30,
            fallback_bit_offset=0,
            fallback_bit_width=32,
        ),
        width_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("WIDTH",),
            fallback_register_offset=0x38,
            fallback_bit_offset=0,
            fallback_bit_width=3,
        ),
        instruction_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("INSTEN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=4,
            fallback_bit_width=1,
        ),
        address_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("ADDREN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=5,
            fallback_bit_width=1,
        ),
        option_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("OPTEN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=6,
            fallback_bit_width=1,
        ),
        data_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("DATAEN",),
            fallback_register_offset=0x38,
            fallback_bit_offset=7,
            fallback_bit_width=1,
        ),
        transfer_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("TFRTYP",),
            fallback_register_offset=0x38,
            fallback_bit_offset=12,
            fallback_bit_width=2,
        ),
        continuous_read_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("CRM",),
            fallback_register_offset=0x38,
            fallback_bit_offset=14,
            fallback_bit_width=1,
        ),
        dummy_cycles_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IFR",
            field_names=("NBDUM",),
            fallback_register_offset=0x38,
            fallback_bit_offset=16,
            fallback_bit_width=5,
        ),
        scrambling_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SMR",
            field_names=("SCREN",),
            fallback_register_offset=0x40,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
    )


def _build_qspi_rows(context: _SemanticContext) -> tuple[QspiSemanticRow, ...]:
    rows: list[QspiSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("qspi", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.qspi.microchip-"):
            rows.append(
                _microchip_qspi_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
    return _enrich_with_dma_bindings(context, tuple(rows), transfer_width_bits=32)  # type: ignore[return-value]


def _qspi_specialization_builder(context: _SemanticContext):
    def _build(row: QspiSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kStatusRegister": row.status_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kSerialClockRegister": row.serial_clock_reg,
            "kInstructionAddressRegister": row.instruction_address_reg,
            "kInstructionCodeRegister": row.instruction_code_reg,
            "kInstructionFrameRegister": row.instruction_frame_reg,
            "kScramblingModeRegister": row.scrambling_mode_reg,
            "kScramblingKeyRegister": row.scrambling_key_reg,
            "kReceiveDataRegister": row.receive_data_reg,
            "kTransmitDataRegister": row.transmit_data_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kSoftwareResetField": row.software_reset_field,
            "kLastTransferField": row.last_transfer_field,
            "kEnabledStatusField": row.enabled_status_field,
            "kSerialMemoryModeField": row.serial_memory_mode_field,
            "kChipSelectModeField": row.chip_select_mode_field,
            "kBitsPerTransferField": row.bits_per_transfer_field,
            "kReceiveReadyField": row.receive_ready_field,
            "kTransmitReadyField": row.transmit_ready_field,
            "kTransmitEmptyField": row.transmit_empty_field,
            "kReceiveReadyInterruptEnableField": row.receive_ready_interrupt_enable_field,
            "kTransmitReadyInterruptEnableField": row.transmit_ready_interrupt_enable_field,
            "kTransmitEmptyInterruptEnableField": row.transmit_empty_interrupt_enable_field,
            "kSerialClockBaudRateField": row.serial_clock_baud_rate_field,
            "kInstructionField": row.instruction_field,
            "kAddressField": row.address_field,
            "kWidthField": row.width_field,
            "kInstructionEnableField": row.instruction_enable_field,
            "kAddressEnableField": row.address_enable_field,
            "kOptionEnableField": row.option_enable_field,
            "kDataEnableField": row.data_enable_field,
            "kTransferTypeField": row.transfer_type_field,
            "kContinuousReadModeField": row.continuous_read_mode_field,
            "kDummyCyclesField": row.dummy_cycles_field,
            "kScramblingEnableField": row.scrambling_enable_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            "  static constexpr bool kSupportsSpiMode = "
            + ("true" if row.supports_spi_mode else "false")
            + ";",
            "  static constexpr bool kSupportsMemoryMode = "
            + ("true" if row.supports_memory_mode else "false")
            + ";",
            f"  static constexpr bool kHasScrambling = {'true' if row.has_scrambling else 'false'};",
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


def emit_runtime_driver_qspi_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_qspi_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kSupportsSpiMode = false;",
        "  static constexpr bool kSupportsMemoryMode = false;",
        "  static constexpr bool kHasScrambling = false;",
        "  static constexpr bool kHasDma = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSerialClockRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInstructionAddressRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInstructionCodeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInstructionFrameRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kScramblingModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kScramblingKeyRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kReceiveDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTransmitDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kLastTransferField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEnabledStatusField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSerialMemoryModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChipSelectModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBitsPerTransferField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReceiveReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitEmptyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReceiveReadyInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitReadyInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransmitEmptyInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSerialClockBaudRateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInstructionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWidthField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInstructionEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddressEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOptionEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTransferTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kContinuousReadModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDummyCyclesField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kScramblingEnableField = kInvalidFieldRef;",
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
        header_name=QSPI_DRIVER_HEADER,
        trait_name="QspiSemanticTraits",
        array_name="kQspiSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_qspi_specialization_builder(context),
    )




__all__ = [
    "QSPI_DRIVER_HEADER",
    "QspiSemanticRow",
    "emit_runtime_driver_qspi_semantics_header",
]
