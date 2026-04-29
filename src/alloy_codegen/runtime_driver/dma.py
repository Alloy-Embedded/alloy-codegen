"""DMA controller driver-semantic emitter (cross-vendor).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR, PeripheralInstance
from alloy_codegen.reporting import EmittedArtifact

from ..emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _semantic_enum_ref,
    _std_array_lines,
)
from ..runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_dma_bindings,
    runtime_lite_peripheral_class_name,
)

from .common import (
    RuntimeIndexedFieldRef,
    _SemanticContext,
    _context,
    _enrich_with_dma_bindings,
    _generic_dma_bindings_for_peripheral,
    _indexed_field_ref,
    _indexed_field_ref_expr,
    _invalid_indexed_field_ref,
    _peripheral_has_dma_binding,
    _schema_ref_expr,
)

DMA_DRIVER_HEADER = "driver_semantics/dma.hpp"


@dataclass(frozen=True, slots=True)
class DmaSemanticRow:
    """DMA semantic trait payload keyed by binding peripheral/signal."""

    peripheral_name: str
    signal_name: str
    binding_id: str
    controller_name: str
    request_line: str
    route_id: str
    conflict_group: str | None
    controller_schema_id: str | None
    router_name: str | None
    router_schema_id: str | None
    channel_index: int | None
    request_value: int | None
    channel_selector: int | None
    route_selector_field: RuntimeIndexedFieldRef


# AdcInternalChannel → runtime_driver/adc.py


# AdcCalibrationDataPoint → runtime_driver/adc.py


# AdcCalibrationContext → runtime_driver/adc.py


# AdcResolutionOption → runtime_driver/adc.py


# AdcSampleTimeOption → runtime_driver/adc.py


# AdcOversamplingOption → runtime_driver/adc.py


# AdcExternalTrigger → runtime_driver/adc.py


# AdcDmaBindingRow → runtime_driver/adc.py


# AdcDmaModeOption → runtime_driver/adc.py


# AdcSemanticRow → runtime_driver/adc.py


def _resolve_dma_router_peripheral(context: _SemanticContext) -> PeripheralInstance | None:
    routers = tuple(
        peripheral
        for peripheral in sorted(context.peripheral_by_name.values(), key=lambda item: item.name)
        if runtime_lite_peripheral_class_name(peripheral.ip_name) == "dma-router"
    )
    if not routers:
        return None
    return routers[0]


def _build_dma_rows(context: _SemanticContext) -> tuple[DmaSemanticRow, ...]:
    runtime_peripheral_names = {
        peripheral.name
        for peripheral in context.peripheral_by_name.values()
        if runtime_lite_peripheral_class_name(peripheral.ip_name)
        in {
            "gpio",
            "uart",
            "i2c",
            "spi",
            "qspi",
            "sdmmc",
            "pwm",
            "adc",
            "dac",
            "dma",
            "dma-router",
        }
    }
    router = _resolve_dma_router_peripheral(context)
    rows: list[DmaSemanticRow] = []
    for binding in _runtime_lite_dma_bindings(context.device):
        if binding.peripheral not in runtime_peripheral_names or binding.signal is None:
            continue
        controller = context.peripheral_by_name.get(binding.controller)
        if controller is None:
            continue
        controller_schema_id = controller.backend_schema_id
        route_selector_field = _invalid_indexed_field_ref(controller.base_address)
        router_name: str | None = None
        router_schema_id: str | None = None
        if controller_schema_id == "alloy.dma.st-bdma-v1-0":
            if router is not None:
                router_name = router.name
                router_schema_id = router.backend_schema_id
                route_selector_field = _indexed_field_ref(
                    base_address=router.base_address,
                    base_offset_bytes=0x00,
                    stride_bytes=0x04,
                    bit_offset=0,
                    bit_width=8,
                )
        elif controller_schema_id == "alloy.dma.st-bdma-f4-v1-0":
            route_selector_field = _indexed_field_ref(
                base_address=controller.base_address,
                base_offset_bytes=0x10,
                stride_bytes=0x18,
                bit_offset=25,
                bit_width=3,
            )
        elif controller_schema_id == "alloy.dma.microchip-xdmac-k":
            route_selector_field = _indexed_field_ref(
                base_address=controller.base_address,
                base_offset_bytes=0x78,
                stride_bytes=0x40,
                bit_offset=24,
                bit_width=7,
            )
        rows.append(
            DmaSemanticRow(
                peripheral_name=binding.peripheral,
                signal_name=binding.signal,
                binding_id=binding.binding_id,
                controller_name=binding.controller,
                request_line=binding.request_line,
                route_id=binding.route_id,
                conflict_group=binding.conflict_group,
                controller_schema_id=controller_schema_id,
                router_name=router_name,
                router_schema_id=router_schema_id,
                channel_index=binding.channel_index,
                request_value=binding.request_value,
                channel_selector=binding.channel_selector,
                route_selector_field=route_selector_field,
            )
        )
    return tuple(rows)


# _peripheral_has_dma_binding → runtime_driver/common.py


# _enrich_with_dma_bindings → runtime_driver/common.py


# _generic_dma_bindings_for_peripheral → runtime_driver/common.py


# _uart_dma_bindings_for_peripheral → runtime_driver/uart.py


def _dma_controller_hw_traits_block(device: CanonicalDeviceIR) -> list[str]:
    lines = [
        "// complete-rp2040-semantics Phase D: per-controller DMA HW facts.",
        "enum class RuntimeDmaCtrlId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_dma_controller_hw, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeDmaCtrlId Id>",
            "struct DmaControllerHwTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kChannelCount = 0u;",
            "  static constexpr std::uint32_t kMaxTransferCount = 0u;",
            "  static constexpr bool kSupportsChaining = false;",
            "  static constexpr bool kSupportsByteSwap = false;",
            "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
            # fill-dma-controller-hw-traits: Tier 2/3/4 HW capabilities.
            "  static constexpr std::uint8_t kPriorityLevelCount = 0u;",
            "  static constexpr std::array<std::uint8_t, 0> kSupportedBurstSizes = {};",
            "  static constexpr std::array<std::uint8_t, 0> kSupportedDataWidths = {};",
            "  static constexpr bool kSupportsCircular = false;",
            "  static constexpr bool kSupportsDoubleBuffer = false;",
            "  static constexpr bool kSupportsMemToMem = false;",
            "  static constexpr bool kSupportsDescriptorChaining = false;",
            "  static constexpr bool kSupportsScatterGather = false;",
            "};",
            "",
        ]
    )

    def _u8_array(name: str, items: tuple[int, ...]) -> str:
        if not items:
            return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
        values = ", ".join(f"{v}u" for v in items)
        return (
            f"  static constexpr std::array<std::uint8_t, {len(items)}> {name} = {{{{{values}}}}};"
        )

    for ctrl in device.rp2040_dma_controller_hw:
        if ctrl.irq_numbers:
            irq_items = ", ".join(f"{n}u" for n in ctrl.irq_numbers)
            irq_line = (
                f"  static constexpr std::array<std::uint32_t, {len(ctrl.irq_numbers)}> "
                f"kIrqNumbers = {{{{{irq_items}}}}};"
            )
        else:
            irq_line = "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};"
        lines.extend(
            [
                "template<>",
                f"struct DmaControllerHwTraits<RuntimeDmaCtrlId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kChannelCount = {ctrl.channel_count}u;",
                f"  static constexpr std::uint32_t kMaxTransferCount = {ctrl.max_transfer_count:#010x}u;",
                f"  static constexpr bool kSupportsChaining = {'true' if ctrl.supports_chaining else 'false'};",
                f"  static constexpr bool kSupportsByteSwap = {'true' if ctrl.supports_byte_swap else 'false'};",
                irq_line,
                f"  static constexpr std::uint8_t kPriorityLevelCount = {ctrl.priority_level_count}u;",
                _u8_array("kSupportedBurstSizes", ctrl.supported_burst_sizes),
                _u8_array("kSupportedDataWidths", ctrl.supported_data_widths),
                f"  static constexpr bool kSupportsCircular = {'true' if ctrl.supports_circular else 'false'};",
                f"  static constexpr bool kSupportsDoubleBuffer = {'true' if ctrl.supports_double_buffer else 'false'};",
                f"  static constexpr bool kSupportsMemToMem = {'true' if ctrl.supports_mem_to_mem else 'false'};",
                f"  static constexpr bool kSupportsDescriptorChaining = {'true' if ctrl.supports_descriptor_chaining else 'false'};",
                f"  static constexpr bool kSupportsScatterGather = {'true' if ctrl.supports_scatter_gather else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def emit_runtime_driver_dma_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_dma_rows(context)
    trait_lines = [
        "template<PeripheralId Peripheral, SignalId Signal>",
        "struct DmaSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr DmaBindingId kBindingId = DmaBindingId::none;",
        "  static constexpr DmaControllerId kControllerId = DmaControllerId::none;",
        "  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::none;",
        "  static constexpr DmaRouteId kRouteId = DmaRouteId::none;",
        "  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;",
        "  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::none;",
        "  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;",
        "  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::none;",
        "  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;",
        "  static constexpr int kChannelIndex = -1;",
        "  static constexpr int kRequestValue = -1;",
        "  static constexpr int kChannelSelector = -1;",
        "  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;",
        "};",
        "",
    ]
    row_lines: list[str] = []
    for row in rows:
        signal_ref = _semantic_enum_ref(
            "SignalId",
            context.semantics_catalog["signal_enum_map"],
            row.signal_name,
        )
        trait_lines.extend(
            [
                "template<>",
                f"struct DmaSemanticTraits<PeripheralId::{_enum_identifier(row.peripheral_name)}, {signal_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr DmaBindingId kBindingId = DmaBindingId::{_enum_identifier(row.binding_id)};",
                f"  static constexpr DmaControllerId kControllerId = DmaControllerId::{_enum_identifier(row.controller_name)};",
                f"  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::{_enum_identifier(row.request_line)};",
                f"  static constexpr DmaRouteId kRouteId = DmaRouteId::{_enum_identifier(row.route_id)};",
                "  static constexpr DmaConflictGroupId kConflictGroupId = "
                + (
                    "DmaConflictGroupId::none"
                    if row.conflict_group is None
                    else f"DmaConflictGroupId::{_enum_identifier(row.conflict_group)}"
                )
                + ";",
                f"  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::{_enum_identifier(row.controller_name)};",
                "  static constexpr PeripheralId kRouterPeripheralId = "
                + (
                    "PeripheralId::none"
                    if row.router_name is None
                    else f"PeripheralId::{_enum_identifier(row.router_name)}"
                )
                + ";",
                "  static constexpr BackendSchemaId kControllerSchemaId = "
                + _schema_ref_expr(context, row.controller_schema_id)
                + ";",
                "  static constexpr BackendSchemaId kRouterSchemaId = "
                + _schema_ref_expr(context, row.router_schema_id)
                + ";",
                f"  static constexpr int kChannelIndex = {row.channel_index if row.channel_index is not None else -1};",
                f"  static constexpr int kRequestValue = {row.request_value if row.request_value is not None else -1};",
                f"  static constexpr int kChannelSelector = {row.channel_selector if row.channel_selector is not None else -1};",
                "  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = "
                + _indexed_field_ref_expr(row.route_selector_field)
                + ";",
                "};",
                "",
            ]
        )
        row_lines.append(f"  PeripheralId::{_enum_identifier(row.peripheral_name)},")

    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        "\n".join(
            [
                *trait_lines,
                *_std_array_lines(
                    type_name="PeripheralId",
                    variable_name="kDmaSemanticPeripherals",
                    row_lines=row_lines,
                ),
                "",
                *_dma_controller_hw_traits_block(device),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "common.hpp"',
            '#include "../dma_bindings.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            DMA_DRIVER_HEADER,
        ),
        content=content,
    )


# emit_runtime_driver_adc_semantics_header → runtime_driver/adc.py




__all__ = [
    "DMA_DRIVER_HEADER",
    "DmaSemanticRow",
    "emit_runtime_driver_dma_semantics_header",
]
