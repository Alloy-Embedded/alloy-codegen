"""DAC driver-semantic emitter (STM32 / Microchip).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from ..emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _std_array_lines,
)
from ..runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)
from .common import (
    RuntimeFieldRef,
    RuntimeIndexedFieldRef,
    RuntimeRegisterRef,
    UartDmaBindingRow,
    _context,
    _dma_binding_ref_array_lines,
    _enrich_with_dma_bindings,
    _field_ref_expr,
    _indexed_field_ref,
    _indexed_field_ref_expr,
    _invalid_field_ref,
    _invalid_indexed_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _peripheral_has_dma_binding,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
    _SemanticContext,
)

DAC_DRIVER_HEADER = "driver_semantics/dac.hpp"


@dataclass(frozen=True, slots=True)
class DacSemanticRow:
    """DAC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    channel_count: int
    has_hardware_trigger: bool
    has_dma: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    trigger_reg: RuntimeRegisterRef
    channel_enable_reg: RuntimeRegisterRef
    channel_disable_reg: RuntimeRegisterRef
    channel_status_reg: RuntimeRegisterRef
    data_reg: RuntimeRegisterRef
    software_reset_field: RuntimeFieldRef
    word_mode_field: RuntimeFieldRef
    prescaler_field: RuntimeFieldRef
    channel_enable_pattern: RuntimeIndexedFieldRef
    channel_disable_pattern: RuntimeIndexedFieldRef
    channel_ready_pattern: RuntimeIndexedFieldRef
    trigger_enable_pattern: RuntimeIndexedFieldRef
    trigger_select_pattern: RuntimeIndexedFieldRef
    data_pattern: RuntimeIndexedFieldRef
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()
    # DMA cross-references (add-peripheral-dma-cross-references).
    dma_bindings: tuple[UartDmaBindingRow, ...] = ()


@dataclass(frozen=True, slots=True)
class DacChannelSemanticRow:
    """DAC channel semantic trait payload keyed by peripheral/channel index."""

    peripheral_name: str
    channel_index: int
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    ready_field: RuntimeFieldRef
    trigger_enable_field: RuntimeFieldRef
    trigger_select_field: RuntimeFieldRef
    data_field: RuntimeFieldRef


def _st_dac_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> DacSemanticRow:
    base_address = context.peripheral_by_name[peripheral_name].base_address
    prefixed_registers = (peripheral_name, "DAC_CR") in context.register_by_key
    register_prefix = "DAC_" if prefixed_registers else ""
    control_register_name = f"{register_prefix}CR"
    trigger_register_name = f"{register_prefix}SWTRGR"
    dual_data_register_name = f"{register_prefix}DHR12RD"
    data_register_name = dual_data_register_name
    dual_channel = (
        peripheral_name,
        dual_data_register_name.upper(),
    ) in context.register_by_key or (
        peripheral_name,
        f"{register_prefix}DHR12R2".upper(),
    ) in context.register_by_key
    channel_count = 2 if dual_channel else 1
    trigger_bit_offset = 1 if prefixed_registers else 2
    trigger_select_bit_offset = 2 if prefixed_registers else 3
    trigger_select_width = 4 if prefixed_registers else 3
    mode_register = (
        _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=f"{register_prefix}MCR",
            fallback_offset=0x3C,
        )
        if prefixed_registers
        else _invalid_register_ref(base_address)
    )
    return DacSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=channel_count,
        has_hardware_trigger=True,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            fallback_offset=0x00,
        ),
        mode_reg=mode_register,
        trigger_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=trigger_register_name,
            fallback_offset=0x04,
        ),
        channel_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            fallback_offset=0x00,
        ),
        channel_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=control_register_name,
            fallback_offset=0x00,
        ),
        channel_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=f"{register_prefix}SR",
            fallback_offset=0x34,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=data_register_name,
            fallback_offset=0x20 if dual_channel else 0x08,
        ),
        software_reset_field=_invalid_field_ref(base_address),
        word_mode_field=_invalid_field_ref(base_address),
        prescaler_field=_invalid_field_ref(base_address),
        channel_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=16,
        ),
        channel_disable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=16,
        ),
        channel_ready_pattern=_invalid_indexed_field_ref(base_address),
        trigger_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=trigger_bit_offset,
            bit_width=1,
            bit_stride_bits=16,
        ),
        trigger_select_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x00,
            stride_bytes=0,
            bit_offset=trigger_select_bit_offset,
            bit_width=trigger_select_width,
            bit_stride_bits=16,
        ),
        data_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x20 if dual_channel else 0x08,
            stride_bytes=0,
            bit_offset=0,
            bit_width=12,
            bit_stride_bits=16 if dual_channel else 0,
        ),
    )


def _st_dac_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[DacChannelSemanticRow, ...]:
    prefixed_registers = (peripheral_name, "DAC_CR") in context.register_by_key
    register_prefix = "DAC_" if prefixed_registers else ""
    channel_count = (
        2
        if (peripheral_name, f"{register_prefix}DHR12R2".upper()) in context.register_by_key
        else 1
    )
    trigger_select_width = 4 if prefixed_registers else 3
    rows: list[DacChannelSemanticRow] = []
    for channel_index in range(channel_count):
        channel_number = channel_index + 1
        register_offset = 0x08 + (channel_index * 0x0C)
        enable_field = _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=f"{register_prefix}CR",
            field_names=(f"EN{channel_number}",),
            fallback_register_offset=0x00,
            fallback_bit_offset=channel_index * 16,
            fallback_bit_width=1,
        )
        rows.append(
            DacChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                enable_field=enable_field,
                disable_field=enable_field,
                ready_field=_invalid_field_ref(
                    context.peripheral_by_name[peripheral_name].base_address
                ),
                trigger_enable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"{register_prefix}CR",
                    field_names=(f"TEN{channel_number}",),
                    fallback_register_offset=0x00,
                    fallback_bit_offset=(1 if prefixed_registers else 2) + (channel_index * 16),
                    fallback_bit_width=1,
                ),
                trigger_select_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"{register_prefix}CR",
                    field_names=(f"TSEL{channel_number}",),
                    fallback_register_offset=0x00,
                    fallback_bit_offset=(2 if prefixed_registers else 3) + (channel_index * 16),
                    fallback_bit_width=trigger_select_width,
                ),
                data_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"{register_prefix}DHR12R{channel_number}",
                    field_names=(f"DACC{channel_number}DHR",),
                    fallback_register_offset=register_offset,
                    fallback_bit_offset=0,
                    fallback_bit_width=12,
                ),
            )
        )
    return tuple(rows)


def _microchip_dac_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> DacSemanticRow:
    base_address = context.peripheral_by_name[peripheral_name].base_address
    return DacSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        channel_count=2,
        has_hardware_trigger=True,
        has_dma=_peripheral_has_dma_binding(context, peripheral_name),
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
        trigger_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TRIGR",
            fallback_offset=0x08,
        ),
        channel_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CHER",
            fallback_offset=0x10,
        ),
        channel_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CHDR",
            fallback_offset=0x14,
        ),
        channel_status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CHSR",
            fallback_offset=0x18,
        ),
        data_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CDR[%s]",
            fallback_offset=0x1C,
        ),
        software_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("SWRST",),
            fallback_register_offset=0x00,
            fallback_bit_offset=0,
            fallback_bit_width=1,
        ),
        word_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WORD",),
            fallback_register_offset=0x04,
            fallback_bit_offset=4,
            fallback_bit_width=1,
        ),
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("PRESCALER",),
            fallback_register_offset=0x04,
            fallback_bit_offset=24,
            fallback_bit_width=4,
        ),
        channel_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x10,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        channel_disable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x14,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        channel_ready_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x18,
            stride_bytes=0,
            bit_offset=16,
            bit_width=1,
            bit_stride_bits=1,
        ),
        trigger_enable_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x08,
            stride_bytes=0,
            bit_offset=0,
            bit_width=1,
            bit_stride_bits=1,
        ),
        trigger_select_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x08,
            stride_bytes=0,
            bit_offset=4,
            bit_width=3,
            bit_stride_bits=4,
        ),
        data_pattern=_indexed_field_ref(
            base_address=base_address,
            base_offset_bytes=0x1C,
            stride_bytes=0,
            bit_offset=0,
            bit_width=16,
            bit_stride_bits=16,
        ),
    )


def _microchip_dac_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[DacChannelSemanticRow, ...]:
    rows: list[DacChannelSemanticRow] = []
    for channel_index in range(2):
        rows.append(
            DacChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                enable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CHER",
                    field_names=(f"CH{channel_index}",),
                    fallback_register_offset=0x10,
                    fallback_bit_offset=channel_index,
                    fallback_bit_width=1,
                ),
                disable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CHDR",
                    field_names=(f"CH{channel_index}",),
                    fallback_register_offset=0x14,
                    fallback_bit_offset=channel_index,
                    fallback_bit_width=1,
                ),
                ready_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CHSR",
                    field_names=(f"DACRDY{channel_index}",),
                    fallback_register_offset=0x18,
                    fallback_bit_offset=16 + channel_index,
                    fallback_bit_width=1,
                ),
                trigger_enable_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="TRIGR",
                    field_names=(f"TRGEN{channel_index}",),
                    fallback_register_offset=0x08,
                    fallback_bit_offset=channel_index,
                    fallback_bit_width=1,
                ),
                trigger_select_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="TRIGR",
                    field_names=(f"TRGSEL{channel_index}",),
                    fallback_register_offset=0x08,
                    fallback_bit_offset=4 + (channel_index * 4),
                    fallback_bit_width=3,
                ),
                data_field=_resolve_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="CDR[%s]",
                    field_names=(f"DATA{channel_index}",),
                    fallback_register_offset=0x1C,
                    fallback_bit_offset=channel_index * 16,
                    fallback_bit_width=16,
                ),
            )
        )
    return tuple(rows)


def _build_dac_rows(
    context: _SemanticContext,
) -> tuple[tuple[DacSemanticRow, ...], tuple[DacChannelSemanticRow, ...]]:
    rows: list[DacSemanticRow] = []
    channel_rows: list[DacChannelSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("dac", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.dac.st-"):
            rows.append(
                _st_dac_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_st_dac_channel_rows(context, peripheral_name=peripheral.name))
        elif schema_id == "alloy.dac.microchip-dacc-e":
            rows.append(
                _microchip_dac_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _microchip_dac_channel_rows(context, peripheral_name=peripheral.name)
            )
    enriched = _enrich_with_dma_bindings(context, tuple(rows), transfer_width_bits=16)
    return tuple(enriched), tuple(channel_rows)  # type: ignore[return-value]


def _dac_specialization_builder(context: _SemanticContext):
    def _build(row: DacSemanticRow) -> list[str]:
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kTriggerRegister": row.trigger_reg,
            "kChannelEnableRegister": row.channel_enable_reg,
            "kChannelDisableRegister": row.channel_disable_reg,
            "kChannelStatusRegister": row.channel_status_reg,
            "kDataRegister": row.data_reg,
        }
        field_members = {
            "kSoftwareResetField": row.software_reset_field,
            "kWordModeField": row.word_mode_field,
            "kPrescalerField": row.prescaler_field,
        }
        indexed_field_members = {
            "kChannelEnablePattern": row.channel_enable_pattern,
            "kChannelDisablePattern": row.channel_disable_pattern,
            "kChannelReadyPattern": row.channel_ready_pattern,
            "kTriggerEnablePattern": row.trigger_enable_pattern,
            "kTriggerSelectPattern": row.trigger_select_pattern,
            "kDataPattern": row.data_pattern,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr std::uint32_t kChannelCount = {row.channel_count}u;",
            "  static constexpr bool kHasHardwareTrigger = "
            + ("true" if row.has_hardware_trigger else "false")
            + ";",
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
        lines.extend(
            f"  static constexpr RuntimeIndexedFieldRef {name} = {_indexed_field_ref_expr(value)};"
            for name, value in indexed_field_members.items()
        )
        lines.extend(_irq_numbers_lines(row.irq_numbers))
        return lines

    return _build


def _dac_channel_specialization_lines(
    channel_rows: tuple[DacChannelSemanticRow, ...],
) -> list[str]:
    lines = [
        "template<PeripheralId Id, std::size_t ChannelIndex>",
        "struct DacChannelSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTriggerEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTriggerSelectField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDataField = kInvalidFieldRef;",
        "};",
        "",
    ]
    for row in channel_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kReadyField": row.ready_field,
            "kTriggerEnableField": row.trigger_enable_field,
            "kTriggerSelectField": row.trigger_select_field,
            "kDataField": row.data_field,
        }
        lines.extend(
            [
                "template<>",
                f"struct DacChannelSemanticTraits<PeripheralId::{peripheral_id}, {row.channel_index}u> {{",
                "  static constexpr bool kPresent = true;",
            ]
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(["};", ""])
    return lines


def emit_runtime_driver_dac_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    dac_rows, channel_rows = _build_dac_rows(context)
    trait_lines = [
        "template<PeripheralId Id>",
        "struct DacSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kChannelCount = 0u;",
        "  static constexpr bool kHasHardwareTrigger = false;",
        "  static constexpr bool kHasDma = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTriggerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kChannelEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kChannelDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kChannelStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDataRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWordModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kChannelReadyPattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTriggerEnablePattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kTriggerSelectPattern = kInvalidIndexedFieldRef;",
        "  static constexpr RuntimeIndexedFieldRef kDataPattern = kInvalidIndexedFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        # DMA cross-references (add-peripheral-dma-cross-references).
        "  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};",
        "};",
        "",
    ]
    dac_peripheral_rows: list[str] = []
    specialization_builder = _dac_specialization_builder(context)
    for row in dac_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        row_lines = list(specialization_builder(row))
        bindings = getattr(row, "dma_bindings", None)
        if bindings is not None and not any("kDmaBindings = " in line for line in row_lines):
            row_lines.extend(_dma_binding_ref_array_lines(bindings))
        trait_lines.extend(
            [
                "template<>",
                f"struct DacSemanticTraits<PeripheralId::{peripheral_id}> {{",
                *row_lines,
                "};",
                "",
            ]
        )
        if not getattr(row, "is_stub", False):
            dac_peripheral_rows.append(f"  PeripheralId::{peripheral_id},")
    body = "\n".join(
        [
            *trait_lines,
            *_dac_channel_specialization_lines(channel_rows),
            *_std_array_lines(
                type_name="PeripheralId",
                variable_name="kDacSemanticPeripherals",
                row_lines=dac_peripheral_rows,
            ),
        ]
    )
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstddef>",
            "#include <cstdint>",
            '#include "common.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            DAC_DRIVER_HEADER,
        ),
        content=content,
    )




__all__ = [
    "DAC_DRIVER_HEADER",
    "DacChannelSemanticRow",
    "DacSemanticRow",
    "emit_runtime_driver_dac_semantics_header",
]
