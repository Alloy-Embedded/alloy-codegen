"""Helpers for deterministic, JSON-friendly serialization."""

from __future__ import annotations

import hashlib
import json
import types as _types
from dataclasses import MISSING, fields, is_dataclass
from typing import Any, Literal, Union, get_args, get_origin, get_type_hints


def _is_empty_optional(value: Any) -> bool:
    if value is None:
        return True
    if isinstance(value, (tuple, list, dict, set, frozenset)):
        return len(value) == 0
    return False


def to_primitive(value: Any) -> Any:
    """Convert dataclasses and tuples into JSON-friendly primitives.

    Fields tagged with ``metadata={"omit_if_default": True}`` are dropped
    from the output when their current value equals the field's declared
    default.  This lets us add new IR fields with sensible defaults without
    invalidating goldens for every previously-admitted family.
    """
    if is_dataclass(value):
        payload: dict[str, Any] = {}
        for field in fields(value):
            item = getattr(value, field.name)
            if field.metadata.get("omit_if_empty") and _is_empty_optional(item):
                continue
            if field.metadata.get("omit_if_default"):
                if field.default is not MISSING and item == field.default:
                    continue
                if (
                    field.default_factory is not MISSING  # type: ignore[misc]
                    and item == field.default_factory()  # type: ignore[misc]
                ):
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


def _is_optional(annotation: Any) -> tuple[bool, Any]:
    """Return ``(is_optional, inner_type)`` for ``X | None`` / ``Optional[X]``.

    Returns ``(False, annotation)`` if not optional.
    """
    origin = get_origin(annotation)
    if origin is Union or origin is _types.UnionType:
        members = [a for a in get_args(annotation) if a is not type(None)]
        if len(members) == 1 and len(get_args(annotation)) == 2:
            return True, members[0]
    return False, annotation


def from_primitive(annotation: Any, value: Any) -> Any:
    """Inverse of :func:`to_primitive`.

    Reconstructs a value (possibly a dataclass tree) from a JSON-friendly
    primitive given its target type ``annotation``.  Supports the type
    surface used by :class:`alloy_codegen.ir.model.CanonicalDeviceIR`:

    * Frozen dataclasses (recursive).
    * ``tuple[X, ...]`` (variadic) — restored as a tuple.
    * ``X | None`` / ``Optional[X]`` — None passes through.
    * ``Literal[...]`` — value passed through unchanged.
    * Primitives (``str``, ``int``, ``float``, ``bool``, ``dict``).

    Fields absent from ``value`` fall back to the dataclass field's
    default / default_factory; this is the inverse of ``to_primitive``'s
    ``omit_if_empty`` / ``omit_if_default`` behaviour.
    """
    if value is None:
        return None

    is_opt, inner = _is_optional(annotation)
    if is_opt:
        return from_primitive(inner, value)

    origin = get_origin(annotation)
    args = get_args(annotation)

    # tuple[X, ...] — variadic typed tuple
    if origin is tuple:
        if len(args) == 2 and args[1] is Ellipsis:
            item_type = args[0]
            return tuple(from_primitive(item_type, item) for item in value)
        # Fixed-length tuple
        return tuple(from_primitive(t, v) for t, v in zip(args, value, strict=False))

    # list[X]
    if origin is list:
        item_type = args[0] if args else Any
        return [from_primitive(item_type, item) for item in value]

    # dict[K, V]
    if origin is dict:
        if not args:
            return dict(value)
        _key_type, val_type = args
        return {k: from_primitive(val_type, v) for k, v in value.items()}

    # Literal[...] — pass-through (the value is one of the literals).
    if origin is Literal:
        return value

    # Plain dataclass.
    if is_dataclass(annotation) and isinstance(annotation, type):
        if not isinstance(value, dict):
            raise TypeError(
                f"expected dict for dataclass {annotation.__name__}, got {type(value).__name__}"
            )
        hints = get_type_hints(annotation)
        kwargs: dict[str, Any] = {}
        for f in fields(annotation):
            field_type = hints.get(f.name, Any)
            if f.name in value:
                kwargs[f.name] = from_primitive(field_type, value[f.name])
                continue
            if f.default is not MISSING:
                kwargs[f.name] = f.default
            elif f.default_factory is not MISSING:  # type: ignore[misc]
                kwargs[f.name] = f.default_factory()  # type: ignore[misc]
            else:
                raise ValueError(
                    f"required field {annotation.__name__}.{f.name} missing from input"
                )
        return annotation(**kwargs)

    # Primitive types — dataclasses already use frozen ints/strs;
    # ``Any`` falls through here as well.
    return value


def canonical_json_text(value: Any) -> str:
    """Render a primitive payload as stable JSON text."""
    return json.dumps(to_primitive(value), indent=2, sort_keys=True) + "\n"


def canonical_json_sha256(value: Any) -> str:
    """Hash a payload using the canonical JSON representation."""
    return hashlib.sha256(canonical_json_text(value).encode("utf-8")).hexdigest()
