"""Helpers for deterministic, JSON-friendly serialization."""

from __future__ import annotations

import hashlib
import json
from dataclasses import fields, is_dataclass
from typing import Any


def _is_empty_optional(value: Any) -> bool:
    if value is None:
        return True
    if isinstance(value, (tuple, list, dict, set, frozenset)):
        return len(value) == 0
    return False


def to_primitive(value: Any) -> Any:
    """Convert dataclasses and tuples into JSON-friendly primitives."""
    if is_dataclass(value):
        payload: dict[str, Any] = {}
        for field in fields(value):
            item = getattr(value, field.name)
            if field.metadata.get("omit_if_empty") and _is_empty_optional(item):
                continue
            payload[field.name] = to_primitive(item)
        return payload
    if isinstance(value, tuple):
        return [to_primitive(item) for item in value]
    if isinstance(value, list):
        return [to_primitive(item) for item in value]
    if isinstance(value, dict):
        return {str(key): to_primitive(item) for key, item in value.items()}
    return value


def canonical_json_text(value: Any) -> str:
    """Render a primitive payload as stable JSON text."""
    return json.dumps(to_primitive(value), indent=2, sort_keys=True) + "\n"


def canonical_json_sha256(value: Any) -> str:
    """Hash a payload using the canonical JSON representation."""
    return hashlib.sha256(canonical_json_text(value).encode("utf-8")).hexdigest()
