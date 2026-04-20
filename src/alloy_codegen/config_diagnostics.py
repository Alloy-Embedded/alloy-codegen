"""Declarative runtime configuration diagnostics."""

from __future__ import annotations

import json
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import AlloyCodegenError
from alloy_codegen.runtime_lite_emission import (
    _runtime_lite_candidates,
    _runtime_lite_dma_bindings,
    _runtime_lite_peripherals,
    runtime_lite_peripheral_class_name,
)
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.validate import run as run_validate

from .config_cli import CONFIG_SCHEMA_VERSION


def _normalized_token(value: str | None) -> str:
    return (value or "").strip().lower().replace("_", "-")


def _load_config_request(request_path: str) -> dict[str, object]:
    payload = json.loads(Path(request_path).read_text(encoding="utf-8"))
    if not isinstance(payload, dict):
        raise AlloyCodegenError("Configuration request must be a JSON object.")
    return payload


def _validated_device(
    *,
    device_name: str,
    context: ExecutionContext,
):
    scope = PipelineScope(device=device_name)
    result = run_validate(scope, context)
    if result.status != "completed":
        raise AlloyCodegenError(f"Validation failed for device {device_name}.")
    return result.scope, result.payload.devices[0]


@dataclass(frozen=True, slots=True)
class RuntimeConfigDiagnosis:
    """Structured diagnostics for one declarative config request."""

    scope: PipelineScope
    request_path: str
    is_valid: bool
    clock_profile: dict[str, object]
    requests: tuple[dict[str, object], ...]

    def to_dict(self) -> dict[str, object]:
        return {
            "command": "config-diagnose",
            "scope": self.scope.to_dict(),
            "request_path": self.request_path,
            "schema": CONFIG_SCHEMA_VERSION,
            "is_valid": self.is_valid,
            "clock_profile": self.clock_profile,
            "requests": list(self.requests),
        }


def _device_runtime_classes(device) -> tuple[str, ...]:
    return tuple(
        sorted(
            {
                runtime_lite_peripheral_class_name(peripheral.ip_name)
                for peripheral in _runtime_lite_peripherals(device)
                if runtime_lite_peripheral_class_name(peripheral.ip_name) != "dma-router"
            }
        )
    )


def _peripherals_by_class(device) -> dict[str, tuple[str, ...]]:
    by_class: dict[str, set[str]] = {}
    for peripheral in _runtime_lite_peripherals(device):
        peripheral_class = runtime_lite_peripheral_class_name(peripheral.ip_name)
        if peripheral_class == "dma-router":
            continue
        by_class.setdefault(peripheral_class, set()).add(peripheral.name)
    return {key: tuple(sorted(value)) for key, value in by_class.items()}


def _available_signals_by_peripheral(device) -> dict[str, tuple[str, ...]]:
    by_peripheral: dict[str, set[str]] = {}
    for candidate in _runtime_lite_candidates(device):
        by_peripheral.setdefault(candidate.peripheral, set()).add(
            _normalized_token(candidate.signal)
        )
    return {key: tuple(sorted(value)) for key, value in by_peripheral.items()}


def _dma_signals_by_peripheral(device) -> dict[str, tuple[str, ...]]:
    by_peripheral: dict[str, set[str]] = {}
    for binding in _runtime_lite_dma_bindings(device):
        if binding.signal:
            by_peripheral.setdefault(binding.peripheral, set()).add(
                _normalized_token(binding.signal)
            )
    return {key: tuple(sorted(value)) for key, value in by_peripheral.items()}


def _group_alternatives(
    device, *, peripheral_name: str, signals: tuple[str, ...]
) -> tuple[dict[str, object], ...]:
    candidates_by_id = {
        candidate.candidate_id: candidate for candidate in _runtime_lite_candidates(device)
    }
    requested_signals = {_normalized_token(signal) for signal in signals}
    alternatives: list[dict[str, object]] = []
    for group in sorted(device.connection_groups, key=lambda item: item.group_id):
        if group.peripheral != peripheral_name:
            continue
        group_signals = {_normalized_token(signal) for signal in group.signals}
        if not requested_signals.issubset(group_signals):
            continue
        pins: dict[str, str] = {}
        for candidate_id in group.candidate_ids:
            candidate = candidates_by_id.get(candidate_id)
            if candidate is None:
                continue
            signal_name = _normalized_token(candidate.signal)
            if signal_name in requested_signals:
                pins[signal_name] = candidate.pin
        if requested_signals.issubset(pins.keys()):
            alternatives.append(
                {
                    "route_group": group.group_id,
                    "pins": {signal: pins[signal] for signal in sorted(requested_signals)},
                }
            )
    return tuple(alternatives)


def _select_peripheral(
    *,
    request: dict[str, object],
    peripherals_in_class: tuple[str, ...],
    device,
) -> tuple[str | None, list[dict[str, object]]]:
    diagnostics: list[dict[str, object]] = []
    requested_peripheral = request.get("peripheral")
    if isinstance(requested_peripheral, str) and requested_peripheral:
        if requested_peripheral in peripherals_in_class:
            return requested_peripheral, diagnostics
        diagnostics.append(
            {
                "severity": "error",
                "code": "invalid-peripheral",
                "message": (
                    f"Peripheral {requested_peripheral!r} is not available for class "
                    f"{request['peripheral_class']!r}."
                ),
                "alternatives": list(peripherals_in_class),
            }
        )
        return None, diagnostics

    requested_pins = request.get("pins", {})
    requested_signals = {
        _normalized_token(signal_name): str(pin_name)
        for signal_name, pin_name in requested_pins.items()
        if isinstance(signal_name, str) and isinstance(pin_name, str)
    }
    if not requested_signals:
        if len(peripherals_in_class) == 1:
            return peripherals_in_class[0], diagnostics
        diagnostics.append(
            {
                "severity": "error",
                "code": "ambiguous-peripheral",
                "message": (
                    f"Class {request['peripheral_class']!r} has multiple peripherals; "
                    "select one explicitly."
                ),
                "alternatives": list(peripherals_in_class),
            }
        )
        return None, diagnostics

    qualifying: list[str] = []
    for peripheral_name in peripherals_in_class:
        candidate_index = {
            (_normalized_token(candidate.signal), candidate.pin)
            for candidate in _runtime_lite_candidates(device)
            if candidate.peripheral == peripheral_name
        }
        if all(
            (signal_name, pin_name) in candidate_index
            for signal_name, pin_name in requested_signals.items()
        ):
            qualifying.append(peripheral_name)
    if len(qualifying) == 1:
        return qualifying[0], diagnostics
    if qualifying:
        diagnostics.append(
            {
                "severity": "error",
                "code": "ambiguous-peripheral",
                "message": (
                    f"Pins resolve to multiple {request['peripheral_class']!r} peripherals."
                ),
                "alternatives": qualifying,
            }
        )
        return None, diagnostics
    diagnostics.append(
        {
            "severity": "error",
            "code": "no-matching-peripheral",
            "message": (
                f"No {request['peripheral_class']!r} peripheral matches the requested pin map."
            ),
            "alternatives": list(peripherals_in_class),
        }
    )
    return None, diagnostics


def _diagnose_request(
    *,
    request_index: int,
    request: dict[str, object],
    device,
    runtime_classes: tuple[str, ...],
    peripherals_by_class: dict[str, tuple[str, ...]],
    signals_by_peripheral: dict[str, tuple[str, ...]],
    dma_signals_by_peripheral: dict[str, tuple[str, ...]],
) -> dict[str, object]:
    diagnostics: list[dict[str, object]] = []
    peripheral_class = str(request.get("peripheral_class", ""))
    requested_signals = {
        _normalized_token(signal_name): str(pin_name)
        for signal_name, pin_name in request.get("pins", {}).items()
        if isinstance(signal_name, str) and isinstance(pin_name, str)
    }
    request_payload: dict[str, object] = {
        "index": request_index,
        "kind": request.get("kind"),
        "peripheral_class": peripheral_class,
        "requested_peripheral": request.get("peripheral"),
        "requested_route_group": request.get("route_group"),
        "requested_pins": dict(sorted(requested_signals.items())),
        "requested_dma": request.get("dma", {}),
        "diagnostics": diagnostics,
        "alternatives": [],
    }

    if peripheral_class not in runtime_classes:
        diagnostics.append(
            {
                "severity": "error",
                "code": "invalid-peripheral-class",
                "message": (
                    f"Peripheral class {peripheral_class!r} is not supported by this device."
                ),
                "alternatives": list(runtime_classes),
            }
        )
        request_payload["is_valid"] = False
        return request_payload

    peripherals_in_class = peripherals_by_class.get(peripheral_class, ())
    resolved_peripheral, selection_diagnostics = _select_peripheral(
        request=request,
        peripherals_in_class=peripherals_in_class,
        device=device,
    )
    diagnostics.extend(selection_diagnostics)
    request_payload["resolved_peripheral"] = resolved_peripheral
    request_payload["alternatives"] = list(peripherals_in_class)
    if resolved_peripheral is None:
        request_payload["is_valid"] = False
        return request_payload

    available_signals = signals_by_peripheral.get(resolved_peripheral, ())
    selected_candidates_by_signal: dict[str, tuple[object, ...]] = {}
    pin_diagnostics: dict[str, dict[str, object]] = {}

    for signal_name, pin_name in requested_signals.items():
        endpoint_candidates = tuple(
            candidate
            for candidate in _runtime_lite_candidates(device)
            if candidate.peripheral == resolved_peripheral
            and _normalized_token(candidate.signal) == signal_name
        )
        valid_pins = tuple(sorted({candidate.pin for candidate in endpoint_candidates}))
        pin_diagnostics[signal_name] = {
            "requested": pin_name,
            "valid_pins": list(valid_pins),
            "is_valid": pin_name in valid_pins,
        }
        if not endpoint_candidates:
            diagnostics.append(
                {
                    "severity": "error",
                    "code": "invalid-signal",
                    "message": (
                        f"Signal {signal_name!r} is not available on peripheral "
                        f"{resolved_peripheral!r}."
                    ),
                    "alternatives": list(available_signals),
                }
            )
            continue
        matching_candidates = tuple(
            candidate for candidate in endpoint_candidates if candidate.pin == pin_name
        )
        if not matching_candidates:
            diagnostics.append(
                {
                    "severity": "error",
                    "code": "invalid-pin",
                    "message": (
                        f"Pin {pin_name!r} does not route signal {signal_name!r} on "
                        f"{resolved_peripheral!r}."
                    ),
                    "alternatives": list(valid_pins),
                }
            )
            continue
        selected_candidates_by_signal[signal_name] = matching_candidates

    request_payload["pins"] = pin_diagnostics

    route_group = request.get("route_group")
    requested_signal_list = tuple(sorted(requested_signals))
    alternatives = _group_alternatives(
        device,
        peripheral_name=resolved_peripheral,
        signals=requested_signal_list,
    )
    if len(requested_signal_list) > 1:
        matching_alternatives = [
            alternative
            for alternative in alternatives
            if all(
                alternative["pins"].get(signal_name) == requested_signals[signal_name]
                for signal_name in requested_signal_list
            )
        ]
        if isinstance(route_group, str) and route_group:
            if not any(alternative["route_group"] == route_group for alternative in alternatives):
                diagnostics.append(
                    {
                        "severity": "error",
                        "code": "invalid-route-group",
                        "message": (
                            f"Route group {route_group!r} is not valid for {resolved_peripheral!r} "
                            f"signals {', '.join(requested_signal_list)}."
                        ),
                        "alternatives": [item["route_group"] for item in alternatives],
                    }
                )
            elif not any(
                alternative["route_group"] == route_group for alternative in matching_alternatives
            ):
                diagnostics.append(
                    {
                        "severity": "error",
                        "code": "route-group-pin-conflict",
                        "message": (
                            f"Pins do not match route group {route_group!r} for "
                            f"{resolved_peripheral!r}."
                        ),
                        "alternatives": list(alternatives),
                    }
                )
        elif requested_signals and not matching_alternatives:
            diagnostics.append(
                {
                    "severity": "error",
                    "code": "pin-conflict",
                    "message": (
                        f"Requested pins do not form a valid route group for "
                        f"{resolved_peripheral!r}."
                    ),
                    "alternatives": list(alternatives),
                }
            )
        if matching_alternatives:
            request_payload["resolved_route_group"] = matching_alternatives[0]["route_group"]
    elif isinstance(route_group, str) and route_group:
        valid_groups = sorted(
            {
                candidate.route_group_id
                for candidates in selected_candidates_by_signal.values()
                for candidate in candidates
                if candidate.route_group_id
            }
        )
        if route_group not in valid_groups:
            diagnostics.append(
                {
                    "severity": "error",
                    "code": "invalid-route-group",
                    "message": (
                        f"Route group {route_group!r} is not valid for {resolved_peripheral!r}."
                    ),
                    "alternatives": valid_groups,
                }
            )
        else:
            request_payload["resolved_route_group"] = route_group

    dma_request = request.get("dma", {})
    request_payload["dma"] = {}
    for signal_name in ("rx", "tx"):
        requested_dma = bool(dma_request.get(signal_name))
        if not requested_dma:
            continue
        valid_dma_signals = dma_signals_by_peripheral.get(resolved_peripheral, ())
        request_payload["dma"][signal_name] = {
            "requested": True,
            "is_valid": signal_name in valid_dma_signals,
            "valid_signals": list(valid_dma_signals),
        }
        if signal_name not in valid_dma_signals:
            diagnostics.append(
                {
                    "severity": "error",
                    "code": "dma-unavailable",
                    "message": (
                        f"DMA is not available for signal {signal_name!r} on "
                        f"{resolved_peripheral!r}."
                    ),
                    "alternatives": list(valid_dma_signals),
                }
            )

    request_payload["is_valid"] = not any(
        diagnostic["severity"] == "error" for diagnostic in diagnostics
    )
    return request_payload


def diagnose_runtime_config(
    *,
    request_path: str,
    context: ExecutionContext,
) -> RuntimeConfigDiagnosis:
    payload = _load_config_request(request_path)
    schema_version = payload.get("schema_version")
    if schema_version != CONFIG_SCHEMA_VERSION:
        raise AlloyCodegenError(
            f"Unsupported config schema {schema_version!r}; expected {CONFIG_SCHEMA_VERSION!r}."
        )
    device_name = payload.get("device")
    if not isinstance(device_name, str) or not device_name:
        raise AlloyCodegenError("Configuration request must set a non-empty 'device'.")

    scope, device = _validated_device(device_name=device_name, context=context)
    if payload.get("vendor") not in {None, device.identity.vendor}:
        raise AlloyCodegenError(
            f"Request vendor {payload.get('vendor')!r} does not match device vendor "
            f"{device.identity.vendor!r}."
        )
    if payload.get("family") not in {None, device.identity.family}:
        raise AlloyCodegenError(
            f"Request family {payload.get('family')!r} does not match device family "
            f"{device.identity.family!r}."
        )

    runtime_classes = _device_runtime_classes(device)
    peripherals_by_class = _peripherals_by_class(device)
    signals_by_peripheral = _available_signals_by_peripheral(device)
    dma_signals_by_peripheral = _dma_signals_by_peripheral(device)
    clock_profiles = tuple(sorted(profile.profile_id for profile in device.system_clock_profiles))
    requested_clock_profile = payload.get("clock_profile")
    clock_profile_is_valid = requested_clock_profile in {None, *clock_profiles}
    clock_profile_payload = {
        "requested": requested_clock_profile,
        "is_valid": clock_profile_is_valid,
        "available": list(clock_profiles),
    }

    requests = payload.get("requests")
    if not isinstance(requests, list):
        raise AlloyCodegenError("Configuration request 'requests' must be a JSON array.")

    request_diagnostics = tuple(
        _diagnose_request(
            request_index=index,
            request=request,
            device=device,
            runtime_classes=runtime_classes,
            peripherals_by_class=peripherals_by_class,
            signals_by_peripheral=signals_by_peripheral,
            dma_signals_by_peripheral=dma_signals_by_peripheral,
        )
        for index, request in enumerate(requests)
        if isinstance(request, dict)
    )

    is_valid = clock_profile_is_valid and all(
        request_diagnostic["is_valid"] for request_diagnostic in request_diagnostics
    )
    return RuntimeConfigDiagnosis(
        scope=scope,
        request_path=request_path,
        is_valid=is_valid,
        clock_profile=clock_profile_payload,
        requests=request_diagnostics,
    )


def format_runtime_config_diagnosis(result: RuntimeConfigDiagnosis) -> str:
    """Render runtime config diagnostics in plain text."""
    lines = [
        f"config diagnose: {result.scope.display_name()}",
        f"request: {result.request_path}",
        f"valid: {'yes' if result.is_valid else 'no'}",
        (
            "clock profile: "
            f"{result.clock_profile['requested']} "
            f"({'ok' if result.clock_profile['is_valid'] else 'invalid'})"
        ),
    ]
    if not result.clock_profile["is_valid"]:
        lines.append("available clock profiles: " + ", ".join(result.clock_profile["available"]))
    for entry in result.requests:
        lines.append(
            f"- request[{entry['index']}] {entry['peripheral_class']} "
            f"resolved={entry.get('resolved_peripheral') or '<none>'} "
            f"valid={'yes' if entry['is_valid'] else 'no'}"
        )
        for diagnostic in entry["diagnostics"]:
            lines.append(f"  {diagnostic['severity']}: {diagnostic['message']}")
    return "\n".join(lines)


__all__ = [
    "RuntimeConfigDiagnosis",
    "diagnose_runtime_config",
    "format_runtime_config_diagnosis",
]
