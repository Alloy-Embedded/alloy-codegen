"""Generated runtime connector contract."""

from __future__ import annotations

from collections import defaultdict
from itertools import chain

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_rows,
    _semantic_enum_ref,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_candidates,
)

CONNECTORS_HEADER = "connectors.hpp"


def _connector_diagnostic_message(
    *,
    peripheral_name: str,
    signal_name: str,
    pin_names: tuple[str, ...],
    source_ids: tuple[str, ...],
    patch_ids: tuple[str, ...],
) -> str:
    valid_pins = ", ".join(pin_names) if pin_names else "<none>"
    provenance_parts = list(source_ids)
    if patch_ids:
        provenance_parts.append(f"patches={', '.join(patch_ids)}")
    provenance = "; ".join(part for part in provenance_parts if part)
    if provenance:
        return (
            f"Invalid connector for {peripheral_name} {signal_name}. "
            f"Valid pins: {valid_pins}. Provenance: {provenance}."
        )
    return f"Invalid connector for {peripheral_name} {signal_name}. Valid pins: {valid_pins}."


def runtime_connectors_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, CONNECTORS_HEADER)
        for device in devices
        if _runtime_lite_candidates(device)
    )


def emit_runtime_connectors_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    from .runtime_lite_emission import _runtime_lite_semantics_catalog

    semantics_catalog = _runtime_lite_semantics_catalog((device,))
    runtime_candidates = _runtime_lite_candidates(device)
    all_pin_refs = tuple(
        f"PinId::{_enum_identifier(pin.name)}"
        for pin in sorted(device.pins, key=lambda item: item.name)
    )
    connector_enum_map = {
        candidate.candidate_id: _enum_identifier(candidate.candidate_id)
        for candidate in runtime_candidates
    }
    candidate_rows: list[str] = []
    connector_trait_lines: list[str] = [
        "enum class ConnectorId : std::uint16_t {",
        "  none,",
        *_enum_rows(connector_enum_map, empty_identifier=None),
        "};",
        "",
        "struct ConnectorDescriptor {",
        "  ConnectorId connector_id;",
        "  PinId pin_id;",
        "  PeripheralId peripheral_id;",
        "  SignalId signal_id;",
        "  RouteId route_id;",
        "  RouteKindId route_kind_id;",
        "  ConnectionGroupId group_id;",
        "};",
        "",
        "template<PinId Pin, PeripheralId Peripheral, SignalId Signal>",
        "struct ConnectorTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr ConnectorId kConnectorId = ConnectorId::none;",
        "  static constexpr RouteId kRouteId = RouteId::none;",
        "  static constexpr RouteKindId kRouteKindId = RouteKindId::none;",
        "  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;",
        "};",
        "",
        "namespace detail {",
        "template<auto Value>",
        "inline constexpr bool kInvalidConnector = false;",
        "}  // namespace detail",
        "",
        "template<PeripheralId Peripheral, SignalId Signal>",
        "struct ConnectorSignalTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr std::array<PinId, 0> kPins = {};",
        "  static constexpr std::array<ConnectorId, 0> kConnectors = {};",
        "};",
        "",
    ]

    candidates_by_endpoint: dict[tuple[str, str], list[object]] = defaultdict(list)
    for candidate in runtime_candidates:
        pin_ref = f"PinId::{_enum_identifier(candidate.pin)}"
        peripheral_ref = f"PeripheralId::{_enum_identifier(candidate.peripheral)}"
        signal_ref = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            candidate.signal,
        )
        route_id_ref = f"RouteId::{_enum_identifier(candidate.candidate_id)}"
        route_kind_ref = _semantic_enum_ref(
            "RouteKindId",
            semantics_catalog["route_kind_enum_map"],
            candidate.route_kind,
        )
        group_ref = (
            "ConnectionGroupId::none"
            if candidate.route_group_id is None
            else f"ConnectionGroupId::{_enum_identifier(candidate.route_group_id)}"
        )
        connector_id_ref = f"ConnectorId::{connector_enum_map[candidate.candidate_id]}"
        candidate_rows.append(
            "  {"
            f"{connector_id_ref}, "
            f"{pin_ref}, "
            f"{peripheral_ref}, "
            f"{signal_ref}, "
            f"{route_id_ref}, "
            f"{route_kind_ref}, "
            f"{group_ref}"
            "},"
        )
        connector_trait_lines.extend(
            [
                "template<>",
                f"struct ConnectorTraits<{pin_ref}, {peripheral_ref}, {signal_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr ConnectorId kConnectorId = {connector_id_ref};",
                f"  static constexpr RouteId kRouteId = {route_id_ref};",
                f"  static constexpr RouteKindId kRouteKindId = {route_kind_ref};",
                f"  static constexpr ConnectionGroupId kConnectionGroupId = {group_ref};",
                "};",
                "",
            ]
        )
        candidates_by_endpoint[(candidate.peripheral, candidate.signal)].append(candidate)

    for (peripheral_name, signal_name), endpoint_candidates in sorted(
        candidates_by_endpoint.items()
    ):
        peripheral_ref = f"PeripheralId::{_enum_identifier(peripheral_name)}"
        signal_ref = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            signal_name,
        )
        pin_rows = [
            f"    PinId::{_enum_identifier(candidate.pin)}," for candidate in endpoint_candidates
        ]
        connector_rows = [
            f"    ConnectorId::{connector_enum_map[candidate.candidate_id]},"
            for candidate in endpoint_candidates
        ]
        valid_pin_refs = {
            f"PinId::{_enum_identifier(candidate.pin)}" for candidate in endpoint_candidates
        }
        invalid_pin_refs = [pin_ref for pin_ref in all_pin_refs if pin_ref not in valid_pin_refs]
        source_ids = tuple(
            sorted(
                {
                    candidate.provenance.source_id
                    for candidate in endpoint_candidates
                    if candidate.provenance.source_id
                }
            )
        )
        patch_ids = tuple(
            sorted(
                {
                    patch_id
                    for patch_id in chain.from_iterable(
                        candidate.provenance.patch_ids for candidate in endpoint_candidates
                    )
                    if patch_id
                }
            )
        )
        diagnostic_message = _connector_diagnostic_message(
            peripheral_name=peripheral_name,
            signal_name=signal_name,
            pin_names=tuple(candidate.pin for candidate in endpoint_candidates),
            source_ids=source_ids,
            patch_ids=patch_ids,
        )
        connector_trait_lines.extend(
            [
                "template<>",
                f"struct ConnectorSignalTraits<{peripheral_ref}, {signal_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::array<PinId, {len(pin_rows)}> kPins = {{{{",
                *pin_rows,
                "  }};",
                f"  static constexpr std::array<ConnectorId, {len(connector_rows)}> "
                "kConnectors = {{",
                *connector_rows,
                "  }};",
                "};",
                "",
            ]
        )
        if invalid_pin_refs:
            connector_trait_lines.extend(
                [
                    "template<PinId Pin>",
                    f"struct ConnectorTraits<Pin, {peripheral_ref}, {signal_ref}> {{",
                    "  static constexpr bool kPresent = false;",
                    "  static constexpr ConnectorId kConnectorId = ConnectorId::none;",
                    "  static constexpr RouteId kRouteId = RouteId::none;",
                    ("  static constexpr RouteKindId kRouteKindId = RouteKindId::none;"),
                    (
                        "  static constexpr ConnectionGroupId kConnectionGroupId = "
                        "ConnectionGroupId::none;"
                    ),
                    f'  static_assert(detail::kInvalidConnector<Pin>, "{diagnostic_message}");',
                    "};",
                    "",
                ]
            )

    body = "\n".join(
        [
            *connector_trait_lines,
            *_std_array_lines(
                type_name="ConnectorDescriptor",
                variable_name="kConnectors",
                row_lines=candidate_rows,
            ),
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            '#include "routes.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, CONNECTORS_HEADER),
        content=content,
    )


__all__ = [
    "CONNECTORS_HEADER",
    "emit_runtime_connectors_header",
    "runtime_connectors_required_paths",
]
