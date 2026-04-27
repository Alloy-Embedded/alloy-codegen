"""Seed peripheral-trait templates from the resolved IR.

Added by ``peripheral-trait-template-library``.

For each ``(peripheral_class, ip_name, ip_version)`` group across
every admitted device, this tool computes the most-common value
of each Tier 2/3/4 field and prints a TOML draft suitable for
``data/peripheral_traits/<class>/<ip_version>.toml``.

The output is **most-common, not correct** — a reviewer checks
the seeded values against datasheets and fixes outliers before
committing.

CLI:

    python -m scripts.extract_peripheral_template \\
        --class uart --ip-version v2 \\
        [--out data/peripheral_traits/uart/usart_v2.toml]

Without ``--out`` the draft TOML goes to stdout.
"""

from __future__ import annotations

import argparse
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Any

_REPO_ROOT = Path(__file__).resolve().parents[1]
_SRC = _REPO_ROOT / "src"
if str(_SRC) not in sys.path:
    sys.path.insert(0, str(_SRC))

# Field surfaces per peripheral class.  Each entry maps a template
# field name to the patch-level field it samples from.  The
# extractor walks every admitted device's resolved patch, groups
# samples by ``(ip_name, ip_version)``, and emits the most common
# value (or sorted union for list-shaped fields).
_FIELD_SURFACES: dict[str, dict[str, tuple[str, str]]] = {
    "uart": {
        "max_baud_hz": ("uart_max_baud_hz", "scalar"),
        "data_bits_options": ("uart_data_bits_options", "list:int"),
        "parity_options": ("uart_parity_options", "list:str"),
        "stop_bits_options": ("uart_stop_bits_options", "list:str"),
        "oversampling_options": ("uart_baud_oversampling_options", "list:int"),
        "fifo_trigger_options": ("uart_fifo_trigger_options", "list:int"),
        "mode_flags": ("uart_mode_flags", "list:str"),
    },
    "spi": {
        "frame_size_options": ("spi_frame_size_options", "list:int"),
        "baud_prescaler_options": ("spi_baud_prescaler_options", "list:int"),
        "fifo_threshold_options": ("spi_fifo_threshold_options", "list:int"),
        "mode_flags": ("spi_mode_flags", "list:str"),
    },
    "i2c": {
        "speed_modes": ("i2c_speed_options", "list:str"),
        "mode_flags": ("i2c_mode_flags", "list:str"),
    },
}


@dataclass(frozen=True, slots=True)
class _Sample:
    """One peripheral instance's contribution to the extractor."""

    vendor: str
    family: str
    device: str
    peripheral: str
    ip_name: str
    ip_version: str
    fields: dict[str, Any]


def _walk_patch_field(payload: dict[str, Any], field_name: str) -> list[Any]:
    """Return the patch-level array for ``field_name``, or [] if absent.

    Scalar values are wrapped into a single-element list so the
    extractor can treat list / scalar fields uniformly upstream.
    """
    raw = payload.get(field_name)
    if raw is None:
        return []
    if isinstance(raw, list):
        return list(raw)
    # Scalar (int / str / etc.).  Wrap into a single-element list.
    return [raw]


def _peripheral_class_field_indexed(
    payload: dict[str, Any],
    *,
    field_name: str,
    peripheral_name: str,
    inner_value_key: str,
) -> Any:
    """Many Tier 2/3/4 patch arrays carry ``{peripheral, ...}`` entries.

    Filter by ``peripheral`` and return the inner field's value(s)."""
    rows = payload.get(field_name, ())
    if not isinstance(rows, list):
        return None
    matches = [
        row.get(inner_value_key)
        for row in rows
        if isinstance(row, dict) and row.get("peripheral") == peripheral_name
    ]
    return matches if matches else None


def _collect_samples(
    *,
    peripheral_class: str,
    ip_version: str | None,
    admitted_root: Path,
) -> list[_Sample]:
    """Walk every device patch under ``patches/`` and collect samples
    for the given peripheral class + optional ip_version filter."""
    import json

    surface = _FIELD_SURFACES[peripheral_class]
    samples: list[_Sample] = []

    for vendor_dir in sorted(admitted_root.iterdir()):
        if not vendor_dir.is_dir():
            continue
        for family_dir in sorted(vendor_dir.iterdir()):
            if not family_dir.is_dir():
                continue
            family_payload_path = family_dir / "family.json"
            if not family_payload_path.exists():
                continue
            family_payload = json.loads(family_payload_path.read_text(encoding="utf-8"))
            family_peripherals = {
                p["name"]: p
                for p in family_payload.get("peripherals", [])
                if isinstance(p, dict)
            }
            devices_dir = family_dir / "devices"
            if not devices_dir.exists():
                continue
            for device_path in sorted(devices_dir.glob("*.json")):
                payload = json.loads(device_path.read_text(encoding="utf-8"))
                device_peripherals = payload.get("peripherals", [])
                if not isinstance(device_peripherals, list):
                    continue
                for periph in device_peripherals:
                    name = periph if isinstance(periph, str) else periph.get("name")
                    if name is None:
                        continue
                    family_meta = family_peripherals.get(name, {})
                    ip_name = family_meta.get("ip_version", "").rsplit("-", 1)[0]
                    full_ip_version = family_meta.get("ip_version")
                    if ip_name == "" or full_ip_version is None:
                        continue
                    # We accept the family ip_version verbatim ("usart-v2") and
                    # also the trailing ``vN`` form so callers can pass either.
                    inferred_class = ip_name.lstrip("0123456789-_").split("-", 1)[0]
                    if inferred_class != _classify_ip_name(ip_name, peripheral_class):
                        continue
                    if ip_version is not None and ip_version not in full_ip_version:
                        continue
                    fields: dict[str, Any] = {}
                    for tmpl_field, (patch_field, kind) in surface.items():
                        rows = _walk_patch_field(payload, patch_field)
                        if not rows:
                            continue
                        if kind == "scalar":
                            fields[tmpl_field] = rows[0]
                        else:
                            # list:int / list:str — extract field values
                            # if rows are ``{peripheral, ...}`` records.
                            extracted = []
                            for entry in rows:
                                if isinstance(entry, dict):
                                    # Heuristic: take any leaf value
                                    # that's a primitive, prioritising
                                    # well-known names.
                                    for key in (
                                        "field_value",
                                        "kind",
                                        "value",
                                        "bits",
                                        "name",
                                    ):
                                        if key in entry:
                                            extracted.append(entry[key])
                                            break
                                else:
                                    extracted.append(entry)
                            if extracted:
                                fields[tmpl_field] = extracted
                    samples.append(
                        _Sample(
                            vendor=vendor_dir.name,
                            family=family_dir.name,
                            device=device_path.stem,
                            peripheral=name,
                            ip_name=ip_name,
                            ip_version=full_ip_version,
                            fields=fields,
                        )
                    )
    return samples


def _classify_ip_name(ip_name: str, peripheral_class: str) -> str:
    """Best-effort: which peripheral class does an ip_name belong to.

    Uses a small set of canonical roots; any unrecognised root
    falls back to its own value so callers can still group by it."""
    ip_lower = ip_name.lower()
    if peripheral_class == "uart" and (
        "usart" in ip_lower or "uart" in ip_lower or "lpuart" in ip_lower
    ):
        return ip_lower.split("-", 1)[0].split("_", 1)[0]
    if peripheral_class == "spi" and "spi" in ip_lower:
        return ip_lower.split("-", 1)[0].split("_", 1)[0]
    if peripheral_class == "i2c" and ("i2c" in ip_lower or "twi" in ip_lower):
        return ip_lower.split("-", 1)[0].split("_", 1)[0]
    return ip_lower.split("-", 1)[0].split("_", 1)[0]


def _summarise(samples: list[_Sample], surface: dict[str, tuple[str, str]]) -> dict[str, Any]:
    """Reduce a list of samples to one set of most-common values."""
    summary: dict[str, Any] = {}
    for tmpl_field, (_patch_field, kind) in surface.items():
        all_values = [
            sample.fields[tmpl_field]
            for sample in samples
            if tmpl_field in sample.fields
        ]
        if not all_values:
            continue
        if kind == "scalar":
            counts = Counter(all_values)
            summary[tmpl_field] = counts.most_common(1)[0][0]
        else:
            # Union the lists to a sorted unique sequence.
            unioned: list[Any] = []
            seen: set[Any] = set()
            for values in all_values:
                for value in values:
                    if value not in seen:
                        unioned.append(value)
                        seen.add(value)
            unioned.sort(key=lambda v: (str(type(v).__name__), v))
            summary[tmpl_field] = unioned
    return summary


def _emit_toml(
    *, peripheral_class: str, ip_name: str, ip_version: str, summary: dict[str, Any]
) -> str:
    """Render a draft TOML for one ``(class, ip_name, ip_version)``."""
    lines: list[str] = [
        "# Auto-seeded by scripts/extract_peripheral_template.py",
        "# Review the values below against datasheet truth before",
        "# committing — the extractor reports most-common, not correct.",
        "",
        "template_revision = 1",
        f'ip_name = "{ip_name}"',
        f'ip_version = "{ip_version}"',
        "",
    ]
    sub_tables: dict[str, dict[str, Any]] = {}
    for key, value in summary.items():
        if isinstance(value, dict):
            sub_tables[key] = value
            continue
        lines.append(f"{key} = {_format_toml_value(value)}")
    for table, entries in sub_tables.items():
        lines.append("")
        lines.append(f"[{table}]")
        for k, v in entries.items():
            lines.append(f"{k} = {_format_toml_value(v)}")
    return "\n".join(lines) + "\n"


def _format_toml_value(value: Any) -> str:
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, int):
        return str(value)
    if isinstance(value, float):
        return repr(value)
    if isinstance(value, str):
        escaped = value.replace('"', '\\"')
        return f'"{escaped}"'
    if isinstance(value, list):
        return "[" + ", ".join(_format_toml_value(v) for v in value) + "]"
    raise TypeError(f"unsupported TOML value: {value!r}")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="extract_peripheral_template",
        description=(
            "Seed a peripheral-trait template from admitted device patches."
        ),
    )
    parser.add_argument(
        "--class",
        dest="peripheral_class",
        required=True,
        choices=sorted(_FIELD_SURFACES),
    )
    parser.add_argument(
        "--ip-version",
        default=None,
        help="Filter samples to this ip_version substring (e.g. 'v2').",
    )
    parser.add_argument("--patches-root", type=Path, default=_REPO_ROOT / "patches")
    parser.add_argument("--out", type=Path, default=None)
    args = parser.parse_args(argv)

    samples = _collect_samples(
        peripheral_class=args.peripheral_class,
        ip_version=args.ip_version,
        admitted_root=args.patches_root,
    )
    if not samples:
        parser.error(
            f"No samples found for class={args.peripheral_class}, "
            f"ip_version={args.ip_version}.  Check --patches-root."
        )

    surface = _FIELD_SURFACES[args.peripheral_class]
    grouped: dict[tuple[str, str], list[_Sample]] = defaultdict(list)
    for sample in samples:
        grouped[(sample.ip_name, sample.ip_version)].append(sample)

    output_chunks: list[str] = []
    for (ip_name, ip_version), bucket in sorted(grouped.items()):
        summary = _summarise(bucket, surface)
        if not summary:
            continue
        output_chunks.append(
            _emit_toml(
                peripheral_class=args.peripheral_class,
                ip_name=ip_name,
                ip_version=ip_version,
                summary=summary,
            )
        )
        output_chunks.append("\n# ----------------------------------------\n\n")

    text = "".join(output_chunks).rstrip() + "\n"
    if args.out is None:
        sys.stdout.write(text)
    else:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text, encoding="utf-8")
    return 0


if __name__ == "__main__":  # pragma: no cover
    raise SystemExit(main())
