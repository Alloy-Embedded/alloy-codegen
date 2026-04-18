"""Generated runtime clock dependency graph contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_rows,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)

CLOCK_GRAPH_HEADER = "clock_graph.hpp"


def runtime_clock_graph_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, CLOCK_GRAPH_HEADER)
        for device in devices
        if device.clock_nodes
    )


def emit_runtime_clock_graph_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    # Build ordered node list: clock-root first, then all others alphabetically
    all_node_ids: list[str] = []
    if any(node.node_id == "clock-root" for node in device.clock_nodes):
        all_node_ids.append("clock-root")
    all_node_ids.extend(
        node.node_id
        for node in sorted(device.clock_nodes, key=lambda item: item.node_id)
        if node.node_id != "clock-root"
    )

    node_enum_map = {node_id: _enum_identifier(node_id) for node_id in all_node_ids}

    def _node_ref(node_id: str | None) -> str:
        if node_id is None or node_id not in node_enum_map:
            return "ClockNodeId::none"
        return f"ClockNodeId::{node_enum_map[node_id]}"

    dependency_row_lines: list[str] = []
    for node in sorted(device.clock_nodes, key=lambda item: item.node_id):
        node_ref = _node_ref(node.node_id)
        parent_ref = _node_ref(node.parent)
        dependency_row_lines.append(f"  {{{node_ref}, {parent_ref}}},")

    body = "\n".join(
        [
            "enum class ClockNodeId : std::uint16_t {",
            "  none,",
            *_enum_rows(node_enum_map, empty_identifier=None),
            "};",
            "",
            "struct ClockDependencyDescriptor {",
            "  ClockNodeId node_id;",
            "  ClockNodeId parent_id;",
            "};",
            *_std_array_lines(
                type_name="ClockDependencyDescriptor",
                variable_name="kClockDependencies",
                row_lines=dependency_row_lines,
            ),
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, CLOCK_GRAPH_HEADER),
        content=content,
    )
