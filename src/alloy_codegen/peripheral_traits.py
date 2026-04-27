"""Peripheral trait template library.

Added by the OpenSpec change ``peripheral-trait-template-library``.

Maintains a per-``(peripheral_class, ip_version)`` library of Tier
2/3/4 trait defaults under ``data/peripheral_traits/<class>/<ip_version>.toml``.
The normalize stage joins every peripheral instance to its
matching template via ``(peripheral.ip_name, peripheral.ip_version)``
and applies the template values to the IR before device-patch
overrides — the merge order is

    baseline ← template ← family-patch ← device-patch

This module ships the **library plumbing**: schema-aware loaders,
the ``(ip_name, ip_version) → template`` lookup, and the merge
helper.  Per-peripheral migrations (drop the redundant fields out
of every device patch) land incrementally in follow-up changes,
gated by the ``invert-patch-as-diff`` redundancy check.

Templates are versioned: every ``.toml`` carries a top-level
``template_revision`` integer that bumps when a default changes,
so device patches can pin against a known revision and the
resolved IR's per-peripheral provenance records the exact value.
"""

from __future__ import annotations

import tomllib
from collections.abc import Iterable
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from alloy_codegen.errors import StageExecutionError

# Repository root resolution: this module lives at
# ``src/alloy_codegen/peripheral_traits.py``.
_REPO_ROOT = Path(__file__).resolve().parents[2]
TEMPLATES_DIR = _REPO_ROOT / "data" / "peripheral_traits"
SCHEMAS_DIR = _REPO_ROOT / "schemas" / "peripheral_traits"

# Supported peripheral classes — every directory under
# ``data/peripheral_traits/`` and every schema under
# ``schemas/peripheral_traits/`` MUST appear here.  Adding a new
# class is a one-line edit + a schema + a template directory.
SUPPORTED_CLASSES: tuple[str, ...] = ("uart", "spi", "i2c")


@dataclass(frozen=True, slots=True)
class PeripheralTemplate:
    """One ``(peripheral_class, ip_version)`` trait template."""

    peripheral_class: str
    ip_name: str
    ip_version: str
    template_revision: int
    values: dict[str, Any] = field(default_factory=dict)
    source_path: Path | None = None

    @property
    def key(self) -> tuple[str, str]:
        """Lookup key matching ``(PeripheralInstance.ip_name,
        PeripheralInstance.ip_version)``."""
        return (self.ip_name, self.ip_version)

    def merged_into(self, override_values: dict[str, Any]) -> dict[str, Any]:
        """Return a copy of the template values with ``override_values``
        applied on top.  Implements the ``template ← override`` step of
        the merge chain."""
        result: dict[str, Any] = {**self.values}
        for key, value in override_values.items():
            if value is None or value == [] or value == {}:
                # ``None``/empty leaves are interpreted as "no
                # override" so callers can omit a key without
                # nulling the template's value.
                continue
            result[key] = value
        return result


def _read_toml(path: Path) -> dict[str, Any]:
    return tomllib.loads(path.read_text(encoding="utf-8"))


def _validate_required_fields(payload: dict[str, Any], path: Path) -> None:
    for field_name in ("template_revision", "ip_name", "ip_version"):
        if field_name not in payload:
            raise StageExecutionError(
                f"peripheral_traits template {path} is missing required "
                f"field {field_name!r}"
            )
    if not isinstance(payload["template_revision"], int):
        raise StageExecutionError(
            f"peripheral_traits template {path} field 'template_revision' "
            f"must be an integer; got {type(payload['template_revision']).__name__}"
        )


def load_template(path: Path, *, peripheral_class: str) -> PeripheralTemplate:
    """Load a single template TOML file and return it as a
    :class:`PeripheralTemplate`."""
    payload = _read_toml(path)
    _validate_required_fields(payload, path)
    return PeripheralTemplate(
        peripheral_class=peripheral_class,
        ip_name=str(payload["ip_name"]),
        ip_version=str(payload["ip_version"]),
        template_revision=int(payload["template_revision"]),
        values={
            k: v
            for k, v in payload.items()
            if k not in {"template_revision", "ip_name", "ip_version"}
        },
        source_path=path,
    )


def load_templates(
    *,
    peripheral_class: str,
    templates_dir: Path | None = None,
) -> tuple[PeripheralTemplate, ...]:
    """Load every template under
    ``<templates_dir>/<peripheral_class>/*.toml`` for one class."""
    if peripheral_class not in SUPPORTED_CLASSES:
        raise StageExecutionError(
            f"unsupported peripheral_class {peripheral_class!r}; "
            f"known classes: {SUPPORTED_CLASSES}"
        )
    base = (templates_dir or TEMPLATES_DIR) / peripheral_class
    if not base.exists():
        return ()
    files = sorted(base.glob("*.toml"))
    return tuple(load_template(p, peripheral_class=peripheral_class) for p in files)


def load_all_templates(
    *,
    templates_dir: Path | None = None,
) -> dict[str, dict[tuple[str, str], PeripheralTemplate]]:
    """Load every shipped template, returning a nested dict
    ``{peripheral_class: {(ip_name, ip_version): PeripheralTemplate}}``."""
    catalog: dict[str, dict[tuple[str, str], PeripheralTemplate]] = {}
    for peripheral_class in SUPPORTED_CLASSES:
        templates = load_templates(
            peripheral_class=peripheral_class, templates_dir=templates_dir
        )
        catalog[peripheral_class] = {tpl.key: tpl for tpl in templates}
    return catalog


def resolve_template(
    catalog: dict[str, dict[tuple[str, str], PeripheralTemplate]],
    *,
    peripheral_class: str,
    ip_name: str,
    ip_version: str | None,
) -> PeripheralTemplate | None:
    """Look up the matching template for a peripheral instance.

    Returns ``None`` when no template is registered for the
    ``(class, ip_name, ip_version)`` triple — callers fall back to
    raw patch values.  ``None`` ``ip_version`` never matches: a
    template MUST declare its version explicitly.
    """
    if ip_version is None:
        return None
    bucket = catalog.get(peripheral_class)
    if bucket is None:
        return None
    return bucket.get((ip_name, ip_version))


def template_provenance_tag(template: PeripheralTemplate) -> str:
    """Stable string for per-peripheral provenance recording.

    Format: ``peripheral_traits/<class>/<ip_name>__<ip_version>@rev<N>``.
    The ``rev<N>`` suffix is the spec-required visible bump
    indicator.
    """
    return (
        f"peripheral_traits/{template.peripheral_class}/"
        f"{template.ip_name}__{template.ip_version}@rev{template.template_revision}"
    )


# ---------------------------------------------------------------------------
# Merge helpers
# ---------------------------------------------------------------------------


def merge_chain(*layers: dict[str, Any] | None) -> dict[str, Any]:
    """Merge a chain of override layers in order ``layers[0] ← layers[1] ← …``.

    Empty / ``None`` leaves at any layer are treated as "no
    override", so callers can omit a key without nulling earlier
    values.  Used by normalize to apply
    ``baseline ← template ← family-patch ← device-patch``.
    """
    result: dict[str, Any] = {}
    for layer in layers:
        if not layer:
            continue
        for key, value in layer.items():
            if value is None or value == [] or value == {}:
                continue
            result[key] = value
    return result


def discover_template_files(
    templates_dir: Path | None = None,
) -> Iterable[Path]:
    """Yield every shipped template file.  Useful for tooling
    (extractor / linter) that wants to walk the library."""
    base = templates_dir or TEMPLATES_DIR
    for peripheral_class in SUPPORTED_CLASSES:
        class_dir = base / peripheral_class
        if class_dir.exists():
            yield from sorted(class_dir.glob("*.toml"))


__all__ = [
    "PeripheralTemplate",
    "SCHEMAS_DIR",
    "SUPPORTED_CLASSES",
    "TEMPLATES_DIR",
    "discover_template_files",
    "load_all_templates",
    "load_template",
    "load_templates",
    "merge_chain",
    "resolve_template",
    "template_provenance_tag",
]
