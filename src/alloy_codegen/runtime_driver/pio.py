"""PIO (Programmable I/O) driver-semantic emitter.

Currently RP2040-only.  Carved out from
``runtime_driver_semantics.py`` under the
``refactor-runtime-driver-semantics-per-class`` OpenSpec.
"""

# ruff: noqa: E501

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from ..emission import _cpp_artifact, _cpp_namespace_block, _std_array_lines
from ..runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)

PIO_DRIVER_HEADER = "driver_semantics/pio.hpp"

_PIO_TRAIT_FIELDS: tuple[tuple[str, str], ...] = (
    ("kStateMachineCount", "std::uint8_t"),
    ("kInstructionMemoryDepth", "std::uint8_t"),
    ("kTxFifoDepth", "std::uint8_t"),
    ("kRxFifoDepth", "std::uint8_t"),
    ("kGpioBase", "std::uint8_t"),
    ("kGpioCount", "std::uint8_t"),
    ("kBaseAddress", "std::uint32_t"),
    ("kDreqTx", "std::uint8_t"),
    ("kDreqRx", "std::uint8_t"),
)


def _pio_id_enum_lines(device: CanonicalDeviceIR) -> list[str]:
    if not device.pio_blocks:
        return [
            "enum class PioId : std::uint8_t {",
            "  None = 0,",
            "};",
            "",
        ]
    lines = ["enum class PioId : std::uint8_t {"]
    for index, block in enumerate(device.pio_blocks):
        lines.append(f"  {block.pio_id} = {index},")
    lines.append("};")
    lines.append("")
    return lines


def _pio_primary_trait_lines() -> list[str]:
    """Primary template: zero defaults so non-PIO families remain zero-cost."""
    body = [
        "template<PioId Id>",
        "struct PioSemanticTraits {",
        "  static constexpr bool kPresent = false;",
    ]
    for name, ctype in _PIO_TRAIT_FIELDS:
        body.append(f"  static constexpr {ctype} {name} = 0;")
    body.append("};")
    body.append("")
    return body


def _pio_specialization_lines(block) -> list[str]:
    return [
        "template<>",
        f"struct PioSemanticTraits<PioId::{block.pio_id}> {{",
        "  static constexpr bool kPresent = true;",
        f"  static constexpr std::uint8_t kStateMachineCount = {block.state_machine_count};",
        (
            f"  static constexpr std::uint8_t kInstructionMemoryDepth = "
            f"{block.instruction_memory_depth};"
        ),
        f"  static constexpr std::uint8_t kTxFifoDepth = {block.tx_fifo_depth};",
        f"  static constexpr std::uint8_t kRxFifoDepth = {block.rx_fifo_depth};",
        f"  static constexpr std::uint8_t kGpioBase = {block.gpio_base};",
        f"  static constexpr std::uint8_t kGpioCount = {block.gpio_count};",
        f"  static constexpr std::uint32_t kBaseAddress = {block.base_address:#010x}u;",
        f"  static constexpr std::uint8_t kDreqTx = {block.dreq_tx_base};",
        f"  static constexpr std::uint8_t kDreqRx = {block.dreq_rx_base};",
        "};",
        "",
    ]


def _state_machine_primary_trait_lines() -> list[str]:
    return [
        "template<PioId Pio, std::uint8_t Sm>",
        "struct StateMachineSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr std::uint8_t kDreqTx = 0;",
        "  static constexpr std::uint8_t kDreqRx = 0;",
        "};",
        "",
    ]


def _state_machine_specialization_lines(block) -> list[str]:
    # ``kDreqTx`` on the PIO trait is the SM0 base; per-SM consumers can also do
    # ``PioSemanticTraits<PioId::PioN>::kDreqTx + sm_index`` at compile time.
    lines: list[str] = []
    for sm in range(block.state_machine_count):
        lines.extend(
            [
                "template<>",
                f"struct StateMachineSemanticTraits<PioId::{block.pio_id}, {sm}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint8_t kDreqTx = {block.dreq_tx_base + sm};",
                f"  static constexpr std::uint8_t kDreqRx = {block.dreq_rx_base + sm};",
                "};",
                "",
            ]
        )
    return lines


def emit_runtime_driver_pio_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit ``driver_semantics/pio.hpp`` with structured PIO topology traits.

    The primary ``PioSemanticTraits<PioId>`` template carries zero-valued
    defaults so families without PIO hardware remain zero-cost.  Devices with
    populated ``device.pio_blocks`` (currently RP2040) get one specialization
    per block plus one ``StateMachineSemanticTraits<PioId, Sm>`` specialization
    per state machine, with per-SM DREQs derived as
    ``dreq_{tx,rx}_base + sm_index`` from the patch overlay.
    """
    body_lines: list[str] = []
    body_lines.extend(_pio_id_enum_lines(device))
    body_lines.extend(_pio_primary_trait_lines())
    for block in device.pio_blocks:
        body_lines.extend(_pio_specialization_lines(block))
    body_lines.extend(_state_machine_primary_trait_lines())
    for block in device.pio_blocks:
        body_lines.extend(_state_machine_specialization_lines(block))

    pio_id_rows = [f"  PioId::{block.pio_id}," for block in device.pio_blocks]
    body_lines.extend(
        _std_array_lines(
            type_name="PioId",
            variable_name="kPioSemanticPeripherals",
            row_lines=pio_id_rows,
        )
    )

    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "common.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, PIO_DRIVER_HEADER),
        content=content,
    )


__all__ = [
    "PIO_DRIVER_HEADER",
    "emit_runtime_driver_pio_semantics_header",
]
