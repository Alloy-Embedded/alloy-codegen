"""Declarative runtime configuration example generation."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.context import ExecutionContext

from .config_recipes import generate_runtime_config_recipe


@dataclass(frozen=True, slots=True)
class RuntimeConfigExamples:
    """User-facing example-ready outputs derived from a resolved config recipe."""

    scope: dict[str, object]
    request_path: str
    examples: tuple[dict[str, object], ...]

    def to_dict(self) -> dict[str, object]:
        return {
            "command": "config-example",
            "scope": self.scope,
            "request_path": self.request_path,
            "examples": list(self.examples),
        }


def _runtime_headers_for_request(scope: dict[str, object], request: dict[str, object]) -> list[str]:
    vendor = scope["vendor"]
    family = scope["family"]
    device = scope["device"]
    peripheral_class = request["peripheral_class"]
    return [
        f"{vendor}/{family}/generated/runtime/devices/{device}/clock_config.hpp",
        f"{vendor}/{family}/generated/runtime/devices/{device}/connectors.hpp",
        (
            f"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/"
            f"{peripheral_class}.hpp"
        ),
    ]


def _snippet_for_request(recipe: dict[str, object], request: dict[str, object]) -> list[str]:
    lines = [
        f"// Device: {recipe['device']}",
        f"// Clock profile: {recipe['clock_profile']}",
        f"// Peripheral: {request['peripheral_class']} {request['peripheral']}",
    ]
    if request.get("route_group"):
        lines.append(f"// Route group: {request['route_group']}")
    if request.get("pins"):
        pin_summary = ", ".join(
            f"{signal_name}={pin_name}" for signal_name, pin_name in sorted(request["pins"].items())
        )
        lines.append(f"// Pins: {pin_summary}")
    if request.get("dma"):
        dma_summary = ", ".join(
            signal_name for signal_name, enabled in sorted(request["dma"].items()) if enabled
        )
        lines.append(f"// DMA: {dma_summary}")
    return lines


def generate_runtime_config_examples(
    *,
    request_path: str,
    context: ExecutionContext,
) -> RuntimeConfigExamples:
    recipe_result = generate_runtime_config_recipe(request_path=request_path, context=context)
    recipe = recipe_result.recipe
    examples = []
    for request in recipe["requests"]:
        example_id = f"{request['peripheral_class']}-{str(request['peripheral']).lower()}-basic"
        examples.append(
            {
                "example_id": example_id,
                "kind": "basic",
                "title": (f"{request['peripheral_class']} bring-up for {request['peripheral']}"),
                "clock_profile": recipe["clock_profile"],
                "peripheral_class": request["peripheral_class"],
                "peripheral": request["peripheral"],
                "route_group": request.get("route_group"),
                "pins": dict(sorted(request.get("pins", {}).items())),
                "dma": dict(sorted(request.get("dma", {}).items())),
                "runtime_headers": _runtime_headers_for_request(recipe_result.scope, request),
                "snippet": _snippet_for_request(recipe, request),
            }
        )
    return RuntimeConfigExamples(
        scope=recipe_result.scope,
        request_path=request_path,
        examples=tuple(examples),
    )


def format_runtime_config_examples(result: RuntimeConfigExamples) -> str:
    """Render example-ready outputs in plain text."""
    lines = [
        (
            "config example: "
            f"{result.scope['vendor']}/{result.scope['family']}/{result.scope['device']}"
        ),
        f"request: {result.request_path}",
    ]
    for example in result.examples:
        lines.append(f"- {example['example_id']}: {example['title']}")
    return "\n".join(lines)


__all__ = [
    "RuntimeConfigExamples",
    "format_runtime_config_examples",
    "generate_runtime_config_examples",
]
