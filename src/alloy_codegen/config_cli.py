"""Declarative configuration schema and template helpers."""

from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.runtime_lite_emission import (
    _runtime_lite_peripherals,
    runtime_lite_peripheral_class_name,
)
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.validate import run as run_validate

CONFIG_SCHEMA_FILE = "runtime-config-request-v1.schema.json"
CONFIG_SCHEMA_VERSION = "runtime-config-request-v1"


def _schema_path() -> Path:
    return Path(__file__).resolve().parents[2] / "schemas" / CONFIG_SCHEMA_FILE


def load_runtime_config_schema() -> dict[str, object]:
    """Load the declarative runtime configuration request schema."""
    return json.loads(_schema_path().read_text(encoding="utf-8"))


def build_runtime_config_template(
    *,
    device_name: str,
    context: ExecutionContext,
) -> dict[str, object]:
    """Build a declarative configuration template for one validated device."""
    result = run_validate(PipelineScope(device=device_name), context)
    device = result.payload.devices[0]
    clock_profiles = [profile.profile_id for profile in device.system_clock_profiles]
    default_clock_profile = next(
        (
            profile.profile_id
            for profile in device.system_clock_profiles
            if profile.kind == "default"
        ),
        clock_profiles[0] if clock_profiles else None,
    )
    peripheral_classes = sorted(
        {
            runtime_lite_peripheral_class_name(peripheral.ip_name)
            for peripheral in _runtime_lite_peripherals(device)
            if runtime_lite_peripheral_class_name(peripheral.ip_name) != "dma-router"
        }
    )
    return {
        "command": "config-template",
        "scope": {
            "vendor": device.identity.vendor,
            "family": device.identity.family,
            "device": device.identity.device,
        },
        "schema": CONFIG_SCHEMA_VERSION,
        "template": {
            "schema_version": CONFIG_SCHEMA_VERSION,
            "device": device.identity.device,
            "vendor": device.identity.vendor,
            "family": device.identity.family,
            "clock_profile": default_clock_profile,
            "requests": [],
            "outputs": {
                "recipes": [],
                "examples": [],
            },
        },
        "available": {
            "clock_profiles": clock_profiles,
            "peripheral_classes": peripheral_classes,
        },
    }


def format_runtime_config_template(result: dict[str, object]) -> str:
    """Render a runtime configuration template payload in plain text."""
    scope = result["scope"]
    available = result["available"]
    template = result["template"]
    lines = [
        f"config template: {scope['vendor']}/{scope['family']}/{scope['device']}",
        f"schema: {result['schema']}",
        f"default clock profile: {template['clock_profile']}",
        "available clock profiles: " + ", ".join(available["clock_profiles"]),
        "available peripheral classes: " + ", ".join(available["peripheral_classes"]),
        "template:",
        json.dumps(template, indent=2, sort_keys=True),
    ]
    return "\n".join(lines)


__all__ = [
    "CONFIG_SCHEMA_FILE",
    "CONFIG_SCHEMA_VERSION",
    "build_runtime_config_template",
    "format_runtime_config_template",
    "load_runtime_config_schema",
]
