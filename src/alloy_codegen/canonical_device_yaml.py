"""Canonical YAML representation of :class:`CanonicalDeviceIR`.

Added by ``define-canonical-device-yaml-schema`` — the foundational
contract for the future three-repo split (``alloy-data-extractor`` →
``alloy-devices-yml`` → ``alloy-codegen`` and siblings).

This module owns the conversion between :class:`CanonicalDeviceIR`
and a deterministic, schema-validated YAML form.  Public surface:

* :func:`serialize_device(ir)` — render the canonical YAML text.
* :func:`parse_device(text)` — read the YAML back into the IR.
* :func:`validate_device(text)` — schema-validate without parsing.

Determinism contract:

1. ``serialize_device`` emits keys in a fixed top-level order (see
   ``_TOP_LEVEL_KEY_ORDER``).  Nested dicts within use the same
   ordering ``to_primitive`` produced (which itself follows
   dataclass field order).
2. Lists are not re-sorted — order is whatever the IR had.
3. No YAML anchors / aliases (``allow_unicode=True``,
   ``default_flow_style=False``, ``sort_keys=False``).
4. UTF-8 output with a trailing newline.
5. Round-trip is **primitive-equivalent**:
   ``to_primitive(parse_device(serialize_device(ir))) ==
   to_primitive(ir)``.  This is byte-stable on the YAML side
   (re-serialising produces identical bytes) and semantically
   faithful on the IR side.  Strict ``ir == parse(serialize(ir))``
   equality is not guaranteed today because the IR holds a small
   set of fields typed ``object`` (intentional — avoids circular
   imports with ``patches.py``); those fields round-trip as
   ``dict`` rather than as their original Patch dataclass.  A
   follow-up change can tighten this when needed.
"""

from __future__ import annotations

import json
from pathlib import Path
from typing import Any

import yaml
from jsonschema import Draft202012Validator

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.serialization import from_primitive, to_primitive

# Resolve the schema directory shipped at repo-root ``schema/``.
_REPO_ROOT = Path(__file__).resolve().parents[2]
SCHEMA_DIR = _REPO_ROOT / "schema" / "canonical_device"
DEVICE_SCHEMA_PATH = SCHEMA_DIR / "device.schema.json"
FAMILY_SCHEMA_PATH = SCHEMA_DIR / "family.schema.json"
VENDOR_SCHEMA_PATH = SCHEMA_DIR / "vendor.schema.json"

# Top-level key order for emitted YAML.  Mirrors the conceptual
# layering "identity → memory + structure → behaviour" so a
# reviewer reading top-to-bottom builds intuition device-first.
_TOP_LEVEL_KEY_ORDER: tuple[str, ...] = (
    "schema_version",
    "identity",
    "provenance",
    "memories",
    "packages",
    "package_pads",
    "pin_constraints",
    "pins",
    "ip_blocks",
    "peripherals",
    "interrupts",
    "interrupt_bindings",
    "vector_slots",
    "registers",
    "register_fields",
    "capabilities",
    "signal_endpoints",
    "route_requirements",
    "route_operations",
    "connection_candidates",
    "connection_groups",
    "system_clock_profiles",
    "clock_nodes",
    "clock_selectors",
    "clock_gates",
    "resets",
    "peripheral_clock_bindings",
    "dma_controllers",
    "dma_requests",
    "dma_bindings",
    "dma_routes",
    "startup_descriptors",
)


# ---------------------------------------------------------------------------
# Custom YAML representer: dump dicts in insertion order, never sort.
# ---------------------------------------------------------------------------


class _CanonicalDumper(yaml.SafeDumper):
    """SafeDumper that emits dicts in insertion order with no sorting."""


def _represent_dict_preserve_order(dumper: _CanonicalDumper, data: dict) -> yaml.MappingNode:
    return dumper.represent_mapping("tag:yaml.org,2002:map", data.items())


_CanonicalDumper.add_representer(dict, _represent_dict_preserve_order)


def _ordered_top_level(payload: dict[str, Any]) -> dict[str, Any]:
    """Return ``payload`` with keys reordered to match
    :data:`_TOP_LEVEL_KEY_ORDER`.  Unknown keys (added by future IR
    additions) are appended in their natural order — the contract
    is "known keys first, in fixed order; new keys after".
    """
    ordered: dict[str, Any] = {}
    seen: set[str] = set()
    for key in _TOP_LEVEL_KEY_ORDER:
        if key in payload:
            ordered[key] = payload[key]
            seen.add(key)
    for key, value in payload.items():
        if key not in seen:
            ordered[key] = value
    return ordered


# ---------------------------------------------------------------------------
# Public surface
# ---------------------------------------------------------------------------


def serialize_device(ir: CanonicalDeviceIR) -> str:
    """Render ``ir`` as deterministic, canonical YAML text."""
    primitive = to_primitive(ir)
    if not isinstance(primitive, dict):
        raise StageExecutionError(
            f"to_primitive(CanonicalDeviceIR) must produce a dict; got {type(primitive).__name__}"
        )
    ordered = _ordered_top_level(primitive)
    text = yaml.dump(
        ordered,
        Dumper=_CanonicalDumper,
        default_flow_style=False,
        sort_keys=False,
        allow_unicode=True,
        width=10_000,  # don't auto-wrap long string fields
    )
    if not text.endswith("\n"):
        text += "\n"
    return text


def parse_device(text: str) -> CanonicalDeviceIR:
    """Parse YAML text back into a :class:`CanonicalDeviceIR`.

    See module docstring for the round-trip contract — fields the
    IR types as ``object`` round-trip as ``dict``, not as their
    original Patch dataclass instance.
    """
    payload = yaml.safe_load(text)
    if not isinstance(payload, dict):
        raise StageExecutionError(
            "Canonical device YAML must be a mapping at the top level; "
            f"got {type(payload).__name__}"
        )
    return from_primitive(CanonicalDeviceIR, payload)


def validate_device(text: str) -> None:
    """Schema-validate canonical device YAML text.

    Raises :class:`StageExecutionError` when validation fails,
    listing every error in one message so reviewers see the full
    diagnosis at once.
    """
    payload = yaml.safe_load(text)
    schema = json.loads(DEVICE_SCHEMA_PATH.read_text(encoding="utf-8"))
    validator = Draft202012Validator(schema)
    errors = sorted(validator.iter_errors(payload), key=lambda e: list(e.absolute_path))
    if errors:
        details = "\n".join(
            f"  • {'/'.join(str(p) for p in err.absolute_path) or '<root>'}: {err.message}"
            for err in errors
        )
        raise StageExecutionError(f"canonical device YAML failed schema validation:\n{details}")


__all__ = [
    "DEVICE_SCHEMA_PATH",
    "FAMILY_SCHEMA_PATH",
    "SCHEMA_DIR",
    "VENDOR_SCHEMA_PATH",
    "parse_device",
    "serialize_device",
    "validate_device",
]
