"""Generated runtime reset-control contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _collect_runtime_semantics_catalog,
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _semantic_enum_ref,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_peripherals,
    _runtime_lite_reset_ids,
)

RESETS_HEADER = "resets.hpp"


def runtime_resets_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, RESETS_HEADER)
        for device in devices
        if _runtime_lite_peripherals(device)
    )


def emit_runtime_resets_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    reset_ids = _runtime_lite_reset_ids(device)
    reset_by_id = {reset.reset_id: reset for reset in device.resets if reset.reset_id in reset_ids}

    def _reset_ref(reset_id: str) -> str:
        return f"ResetId::{_enum_identifier(reset_id)}"

    def _peripheral_ref(peripheral_name: str | None) -> str:
        if peripheral_name is None:
            return "PeripheralId::none"
        return f"PeripheralId::{_enum_identifier(peripheral_name)}"

    def _register_ref(register_id: str | None) -> str:
        if register_id is None:
            return "RegisterId::none"
        return f"RegisterId::{_enum_identifier(register_id)}"

    def _field_ref(field_id: str | None) -> str:
        if field_id is None:
            return "FieldId::none"
        return f"FieldId::{_enum_identifier(field_id)}"

    descriptor_rows: list[str] = []
    for reset_id, reset in sorted(reset_by_id.items()):
        active_level_ref = _semantic_enum_ref(
            "ActiveLevelId",
            semantics_catalog["active_level_enum_map"],
            reset.active_level,
        )
        descriptor_rows.append(
            "  {"
            f"{_reset_ref(reset_id)}, "
            f"{_peripheral_ref(reset.peripheral)}, "
            f"{_register_ref(reset.register_id)}, "
            f"{_field_ref(reset.register_field_id)}, "
            f"{active_level_ref}"
            "},"
        )

    body = "\n".join(
        [
            "struct ResetDescriptor {",
            "  ResetId reset_id;",
            "  PeripheralId peripheral_id;",
            "  RegisterId register_id;",
            "  FieldId field_id;",
            "  ActiveLevelId active_level_id;",
            "};",
            *_std_array_lines(
                type_name="ResetDescriptor",
                variable_name="kResetDescriptors",
                row_lines=descriptor_rows,
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
            '#include "clock_bindings.hpp"',
            '#include "peripheral_instances.hpp"',
            '#include "register_fields.hpp"',
            '#include "registers.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            RESETS_HEADER,
        ),
        content=content,
    )
