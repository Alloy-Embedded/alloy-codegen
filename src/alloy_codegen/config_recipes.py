"""Declarative runtime configuration recipe generation."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import AlloyCodegenError

from .config_diagnostics import diagnose_runtime_config


@dataclass(frozen=True, slots=True)
class RuntimeConfigRecipe:
    """One resolved recipe generated from a declarative config request."""

    scope: dict[str, object]
    request_path: str
    clock_profile: str | None
    recipe: dict[str, object]

    def to_dict(self) -> dict[str, object]:
        return {
            "command": "config-recipe",
            "scope": self.scope,
            "request_path": self.request_path,
            "clock_profile": self.clock_profile,
            "recipe": self.recipe,
        }


def generate_runtime_config_recipe(
    *,
    request_path: str,
    context: ExecutionContext,
) -> RuntimeConfigRecipe:
    diagnosis = diagnose_runtime_config(request_path=request_path, context=context)
    if not diagnosis.is_valid:
        raise AlloyCodegenError(
            "Configuration request is not valid; run config-diagnose first and resolve errors."
        )

    requests = []
    for entry in diagnosis.requests:
        requests.append(
            {
                "peripheral_class": entry["peripheral_class"],
                "peripheral": entry["resolved_peripheral"],
                "route_group": entry.get("resolved_route_group"),
                "pins": {
                    signal_name: pin_info["requested"]
                    for signal_name, pin_info in sorted(entry.get("pins", {}).items())
                },
                "dma": {
                    signal_name: signal_info["requested"]
                    for signal_name, signal_info in sorted(entry.get("dma", {}).items())
                    if signal_info["requested"]
                },
            }
        )

    clock_profile = diagnosis.clock_profile["requested"]
    scope_payload = diagnosis.scope.to_dict()
    recipe = {
        "schema_version": "runtime-config-recipe-v1",
        "device": scope_payload["device"],
        "vendor": scope_payload["vendor"],
        "family": scope_payload["family"],
        "clock_profile": clock_profile,
        "requests": requests,
    }
    return RuntimeConfigRecipe(
        scope=scope_payload,
        request_path=request_path,
        clock_profile=clock_profile,
        recipe=recipe,
    )


def format_runtime_config_recipe(result: RuntimeConfigRecipe) -> str:
    """Render a runtime recipe in plain text."""
    lines = [
        (
            "config recipe: "
            f"{result.scope['vendor']}/{result.scope['family']}/{result.scope['device']}"
        ),
        f"request: {result.request_path}",
        f"clock profile: {result.clock_profile}",
        "resolved requests:",
    ]
    for request in result.recipe["requests"]:
        lines.append(
            f"- {request['peripheral_class']} {request['peripheral']} "
            f"route_group={request['route_group'] or '<none>'}"
        )
    return "\n".join(lines)


__all__ = [
    "RuntimeConfigRecipe",
    "format_runtime_config_recipe",
    "generate_runtime_config_recipe",
]
