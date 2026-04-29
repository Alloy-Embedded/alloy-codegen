"""Generated runtime capability contract."""

from __future__ import annotations

from collections import defaultdict
from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR, CapabilityDescriptor
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_rows,
    _std_array_lines,
    _text_artifact,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_dma_bindings,
    _runtime_lite_peripherals,
    runtime_lite_peripheral_class_name,
)

CAPABILITIES_HEADER = "capabilities.hpp"
CAPABILITIES_JSON = "capabilities.json"
_CPP_RESERVED_ENUM_IDENTIFIERS = frozenset(
    {
        "alignas",
        "alignof",
        "and",
        "and_eq",
        "asm",
        "auto",
        "bitand",
        "bitor",
        "bool",
        "break",
        "case",
        "catch",
        "char",
        "char8_t",
        "char16_t",
        "char32_t",
        "class",
        "compl",
        "concept",
        "const",
        "consteval",
        "constexpr",
        "constinit",
        "const_cast",
        "continue",
        "co_await",
        "co_return",
        "co_yield",
        "decltype",
        "default",
        "delete",
        "do",
        "double",
        "dynamic_cast",
        "else",
        "enum",
        "explicit",
        "export",
        "extern",
        "false",
        "float",
        "for",
        "friend",
        "goto",
        "if",
        "inline",
        "int",
        "long",
        "mutable",
        "namespace",
        "new",
        "noexcept",
        "not",
        "not_eq",
        "nullptr",
        "operator",
        "or",
        "or_eq",
        "private",
        "protected",
        "public",
        "register",
        "reinterpret_cast",
        "requires",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "static_assert",
        "static_cast",
        "struct",
        "switch",
        "template",
        "this",
        "thread_local",
        "throw",
        "true",
        "try",
        "typedef",
        "typeid",
        "typename",
        "union",
        "unsigned",
        "using",
        "virtual",
        "void",
        "volatile",
        "wchar_t",
        "while",
        "xor",
        "xor_eq",
    }
)


def _safe_enum_identifier(value: str) -> str:
    identifier = _enum_identifier(value)
    if identifier in _CPP_RESERVED_ENUM_IDENTIFIERS:
        return f"{identifier}_value"
    return identifier


@dataclass(frozen=True, slots=True)
class RuntimeCapabilityRow:
    """One device-scoped runtime capability fact."""

    capability_id: str
    scope: str
    peripheral_class: str
    name: str
    value: str
    peripheral: str | None


def _runtime_capability_scope_id(scope: str) -> str:
    return scope.replace("-", "_")


def _runtime_capability_class_name(capability: CapabilityDescriptor) -> str:
    source_name = capability.ip_name or capability.peripheral_class
    return runtime_lite_peripheral_class_name(source_name)


def runtime_capability_rows(device: CanonicalDeviceIR) -> tuple[RuntimeCapabilityRow, ...]:
    """Return typed runtime capability facts for one device."""

    runtime_peripherals = _runtime_lite_peripherals(device)
    runtime_peripheral_names = {peripheral.name for peripheral in runtime_peripherals}
    runtime_class_by_peripheral = {
        peripheral.name: runtime_lite_peripheral_class_name(peripheral.ip_name)
        for peripheral in runtime_peripherals
    }
    runtime_classes = set(runtime_class_by_peripheral.values())

    rows_by_id: dict[str, RuntimeCapabilityRow] = {}
    for capability in sorted(device.capabilities, key=lambda item: item.capability_id):
        class_name = _runtime_capability_class_name(capability)
        if class_name not in runtime_classes:
            continue
        peripheral_name: str | None = None
        if capability.scope == "instance-overlay":
            if capability.peripheral not in runtime_peripheral_names:
                continue
            if capability.package not in {None, device.identity.package}:
                continue
            peripheral_name = capability.peripheral
        elif capability.scope != "ip-block":
            continue
        rows_by_id[capability.capability_id] = RuntimeCapabilityRow(
            capability_id=capability.capability_id,
            scope=_runtime_capability_scope_id(capability.scope),
            peripheral_class=class_name,
            name=capability.name,
            value=capability.value,
            peripheral=peripheral_name,
        )

    for binding in _runtime_lite_dma_bindings(device):
        class_name = runtime_class_by_peripheral.get(binding.peripheral)
        if class_name is None or class_name in {"dma", "dma-router"}:
            continue
        signal_value = binding.signal or "peripheral"
        capability_id = (
            f"runtime-dma:{binding.peripheral}:{binding.controller}:"
            f"{binding.request_line}:{signal_value}"
        )
        rows_by_id.setdefault(
            capability_id,
            RuntimeCapabilityRow(
                capability_id=capability_id,
                scope="dma_binding",
                peripheral_class=class_name,
                name="dma-compatible-signal",
                value=signal_value,
                peripheral=binding.peripheral,
            ),
        )

    for class_name in sorted(runtime_classes):
        capability_id = f"runtime-support:{class_name}"
        rows_by_id.setdefault(
            capability_id,
            RuntimeCapabilityRow(
                capability_id=capability_id,
                scope="runtime_contract",
                peripheral_class=class_name,
                name="runtime-supported",
                value="true",
                peripheral=None,
            ),
        )

    # Device-level multicore facts (added by ``expose-xtensa-dual-core-facts``).
    # The two unconditional keys (`multicore-topology`, `core-count`) ride on
    # every device so consumers can branch on topology without a fallback.
    # `secondary-core-release-register` is emitted only for asymmetric Xtensa
    # devices where the IR carries an ``app_cpu_control_plane``.
    topology_value = {
        "single_core": "single-core",
        "symmetric_dual_core": "symmetric-dual-core",
        "xtensa_asymmetric_dual_core": "xtensa-dual-core",
    }.get(device.multicore_topology, "single-core")
    core_count = 1 if device.multicore_topology == "single_core" else 2
    rows_by_id["device:multicore-topology"] = RuntimeCapabilityRow(
        capability_id="device:multicore-topology",
        scope="device",
        peripheral_class="device",
        name="multicore-topology",
        value=topology_value,
        peripheral=None,
    )
    rows_by_id["device:core-count"] = RuntimeCapabilityRow(
        capability_id="device:core-count",
        scope="device",
        peripheral_class="device",
        name="core-count",
        value=str(core_count),
        peripheral=None,
    )
    plane = device.app_cpu_control_plane
    if plane is not None:
        if plane.release_register_secondary is not None:
            register_value = f"[{plane.release_register},{plane.release_register_secondary}]"
        else:
            register_value = plane.release_register
        rows_by_id["device:secondary-core-release-register"] = RuntimeCapabilityRow(
            capability_id="device:secondary-core-release-register",
            scope="device",
            peripheral_class="device",
            name="secondary-core-release-register",
            value=register_value,
            peripheral=None,
        )

    return tuple(
        sorted(
            rows_by_id.values(),
            key=lambda item: (
                item.peripheral_class,
                item.peripheral or "",
                item.scope,
                item.name,
                item.value,
                item.capability_id,
            ),
        )
    )


def runtime_capabilities_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    paths: list[str] = []
    for device in devices:
        if not _runtime_lite_peripherals(device):
            continue
        paths.append(
            _device_runtime_generated_path(family_dir, device.identity.device, CAPABILITIES_HEADER)
        )
        paths.append(
            _device_runtime_generated_path(family_dir, device.identity.device, CAPABILITIES_JSON)
        )
    return tuple(paths)


def emit_runtime_capabilities_json(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    rows = runtime_capability_rows(device)
    payload = {
        "schema_version": device.schema_version,
        "vendor": device.identity.vendor,
        "family": device.identity.family,
        "device": device.identity.device,
        "capabilities": [
            {
                "capability_id": row.capability_id,
                "scope": row.scope,
                "peripheral_class": row.peripheral_class,
                "name": row.name,
                "value": row.value,
                "peripheral": row.peripheral,
            }
            for row in rows
        ],
    }
    return _text_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, CAPABILITIES_JSON),
        artifact_kind="generated-runtime-metadata",
        payload=payload,
    )


def emit_runtime_capabilities_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    rows = runtime_capability_rows(device)
    runtime_peripherals = _runtime_lite_peripherals(device)
    runtime_class_by_peripheral = {
        peripheral.name: runtime_lite_peripheral_class_name(peripheral.ip_name)
        for peripheral in runtime_peripherals
    }
    runtime_classes = sorted(set(runtime_class_by_peripheral.values()))

    capability_id_enum_map = {
        row.capability_id: _safe_enum_identifier(row.capability_id) for row in rows
    }
    capability_scope_enum_map = {
        scope: _safe_enum_identifier(scope) for scope in sorted({row.scope for row in rows})
    }
    capability_name_enum_map = {
        name: _safe_enum_identifier(name) for name in sorted({row.name for row in rows})
    }
    capability_value_enum_map = {
        value: _safe_enum_identifier(value) for value in sorted({row.value for row in rows})
    }

    def _capability_id_ref(capability_id: str) -> str:
        return f"CapabilityId::{capability_id_enum_map[capability_id]}"

    def _scope_ref(scope: str) -> str:
        return f"CapabilityScopeId::{capability_scope_enum_map[scope]}"

    def _name_ref(name: str) -> str:
        return f"CapabilityNameId::{capability_name_enum_map[name]}"

    def _value_ref(value: str) -> str:
        return f"CapabilityValueId::{capability_value_enum_map[value]}"

    def _class_ref(class_name: str) -> str:
        return f"PeripheralClassId::{_enum_identifier(f'class_{class_name}')}"

    def _peripheral_ref(peripheral_name: str | None) -> str:
        if peripheral_name is None:
            return "PeripheralId::none"
        return f"PeripheralId::{_enum_identifier(peripheral_name)}"

    capability_descriptor_rows = [
        "  {"
        f"{_capability_id_ref(row.capability_id)}, "
        f"{_scope_ref(row.scope)}, "
        f"{_class_ref(row.peripheral_class)}, "
        f"{_name_ref(row.name)}, "
        f"{_value_ref(row.value)}, "
        f"{_peripheral_ref(row.peripheral)}"
        "},"
        for row in rows
    ]

    capability_trait_lines: list[str] = [
        "template<CapabilityId Id>",
        "struct CapabilityTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::none;",
        "  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::none;",
        "  static constexpr CapabilityNameId kNameId = CapabilityNameId::none;",
        "  static constexpr CapabilityValueId kValueId = CapabilityValueId::none;",
        "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
        "};",
        "",
    ]
    if rows:
        # ``reduce-cpp-header-bloat-via-shared-luts``: every
        # ``CapabilityTraits<...>`` specialisation has the same
        # six fixed-size scalar fields.  Pull them into a single
        # ``inline constexpr std::array<CapabilityHardwareLut, N>``
        # at namespace scope and project per-id specialisations as
        # a one-line inheritance from a shared
        # ``CapabilityTraitsBase<Index>``.
        capability_trait_lines.extend(
            [
                "struct CapabilityHardwareLut {",
                "  CapabilityScopeId scope_id;",
                "  PeripheralClassId peripheral_class_id;",
                "  CapabilityNameId name_id;",
                "  CapabilityValueId value_id;",
                "  PeripheralId peripheral_id;",
                "};",
                "",
                f"inline constexpr std::array<CapabilityHardwareLut, {len(rows)}> "
                "kCapabilityHardwareLut = {{",
            ]
        )
        for row in rows:
            capability_trait_lines.append(
                "  {"
                f"{_scope_ref(row.scope)}, "
                f"{_class_ref(row.peripheral_class)}, "
                f"{_name_ref(row.name)}, "
                f"{_value_ref(row.value)}, "
                f"{_peripheral_ref(row.peripheral)}"
                "},"
            )
        capability_trait_lines.append("}};")
        capability_trait_lines.append("")
        capability_trait_lines.extend(
            [
                "template<std::size_t Index>",
                "struct CapabilityTraitsBase {",
                "  static constexpr auto& kFacts = kCapabilityHardwareLut[Index];",
                "  static constexpr bool kPresent = true;",
                "  static constexpr CapabilityScopeId kScopeId = kFacts.scope_id;",
                "  static constexpr PeripheralClassId kPeripheralClassId = kFacts.peripheral_class_id;",
                "  static constexpr CapabilityNameId kNameId = kFacts.name_id;",
                "  static constexpr CapabilityValueId kValueId = kFacts.value_id;",
                "  static constexpr PeripheralId kPeripheralId = kFacts.peripheral_id;",
                "};",
                "",
            ]
        )
        for index, row in enumerate(rows):
            capability_trait_lines.append(
                f"template<> struct CapabilityTraits<{_capability_id_ref(row.capability_id)}> "
                f": CapabilityTraitsBase<{index}> {{}};"
            )
        capability_trait_lines.append("")

    class_rows: dict[str, list[RuntimeCapabilityRow]] = defaultdict(list)
    peripheral_rows: dict[str, list[RuntimeCapabilityRow]] = defaultdict(list)
    for row in rows:
        class_rows[row.peripheral_class].append(row)
        if row.peripheral is not None:
            peripheral_rows[row.peripheral].append(row)

    capability_trait_lines.extend(
        [
            "template<PeripheralClassId Id>",
            "struct PeripheralClassCapabilityTraits {",
            "  static constexpr bool kPresent = false;",
            "  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};",
            "};",
            "",
        ]
    )
    for class_name in runtime_classes:
        row_group = class_rows.get(class_name, [])
        capability_trait_lines.extend(
            [
                "template<>",
                f"struct PeripheralClassCapabilityTraits<{_class_ref(class_name)}> {{",
                f"  static constexpr bool kPresent = {'true' if row_group else 'false'};",
                "  inline static constexpr std::array<CapabilityId, "
                f"{len(row_group)}> kCapabilityIds = {{{{",
                *[f"    {_capability_id_ref(row.capability_id)}," for row in row_group],
                "  }};",
                "};",
                "",
            ]
        )

    capability_trait_lines.extend(
        [
            "template<PeripheralId Id>",
            "struct PeripheralCapabilityTraits {",
            "  static constexpr bool kPresent = false;",
            "  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};",
            "};",
            "",
        ]
    )
    for peripheral in runtime_peripherals:
        row_group = peripheral_rows.get(peripheral.name, [])
        capability_trait_lines.extend(
            [
                "template<>",
                "struct PeripheralCapabilityTraits<"
                f"PeripheralId::{_enum_identifier(peripheral.name)}> {{",
                f"  static constexpr bool kPresent = {'true' if row_group else 'false'};",
                "  inline static constexpr std::array<CapabilityId, "
                f"{len(row_group)}> kCapabilityIds = {{{{",
                *[f"    {_capability_id_ref(row.capability_id)}," for row in row_group],
                "  }};",
                "};",
                "",
            ]
        )

    body = "\n".join(
        [
            "enum class CapabilityId : std::uint16_t {",
            "  none,",
            *_enum_rows(capability_id_enum_map, empty_identifier=None),
            "};",
            "",
            "enum class CapabilityScopeId : std::uint16_t {",
            "  none,",
            *_enum_rows(capability_scope_enum_map, empty_identifier=None),
            "};",
            "",
            "enum class CapabilityNameId : std::uint16_t {",
            "  none,",
            *_enum_rows(capability_name_enum_map, empty_identifier=None),
            "};",
            "",
            "enum class CapabilityValueId : std::uint16_t {",
            "  none,",
            *_enum_rows(capability_value_enum_map, empty_identifier=None),
            "};",
            "",
            "struct CapabilityDescriptor {",
            "  CapabilityId capability_id;",
            "  CapabilityScopeId scope_id;",
            "  PeripheralClassId peripheral_class_id;",
            "  CapabilityNameId name_id;",
            "  CapabilityValueId value_id;",
            "  PeripheralId peripheral_id;",
            "};",
            *_std_array_lines(
                type_name="CapabilityDescriptor",
                variable_name="kCapabilities",
                row_lines=capability_descriptor_rows,
            ),
            "",
            *capability_trait_lines,
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "peripheral_instances.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            CAPABILITIES_HEADER,
        ),
        content=content,
    )
