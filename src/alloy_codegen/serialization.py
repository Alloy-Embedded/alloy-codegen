"""Helpers for deterministic, JSON-friendly serialization."""

from __future__ import annotations

import hashlib
import json
from dataclasses import fields, is_dataclass
from typing import Any


def to_primitive(value: Any) -> Any:
    """Convert dataclasses and tuples into JSON-friendly primitives."""
    if is_dataclass(value):
        return {field.name: to_primitive(getattr(value, field.name)) for field in fields(value)}
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
