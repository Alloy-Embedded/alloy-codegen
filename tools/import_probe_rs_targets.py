"""Import the ``probe-rs/probe-rs`` target catalog into a deterministic
``data/known_devices.toml`` known-devices index
(``ingest-probe-rs-target-catalog``).

probe-rs ships a community-maintained inventory of ~5000 chip
variants under ``targets/*.yaml``.  This tool clones (or syncs an
existing checkout of) probe-rs, parses every target YAML, and emits
two artifacts under ``data/``:

* ``known_devices.toml`` — flat table of canonical
  ``(vendor, family, device)`` triples plus the probe-rs target
  name, core, memory map, and flash-algo reference.
* ``known_devices.meta.toml`` — pinned probe-rs commit SHA + import
  timestamp + tool version.  The pipeline pins to this SHA so a
  re-run reproduces the same catalog byte-for-byte.

The catalog is **read-only** with respect to the pipeline.  Patches
remain the source of truth on conflict; the catalog is only for
discoverability + admission scaffolding (e.g. "what STM32G0 chips
exist that we don't admit yet?").

Usage
-----

::

    uv run --with pyyaml python -m tools.import_probe_rs_targets \\
        --probe-rs-root <path-to-probe-rs-checkout> \\
        [--output-dir data/]

Re-running on the same pinned SHA SHALL produce byte-identical
output.  PyYAML is required at runtime (the script runs offline,
not in the pipeline, so it is not added to the package's runtime
dependency closure).
"""

from __future__ import annotations

import argparse
import datetime
import json
import os
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

# Canonical alloy vendor IDs.  probe-rs uses long-form manufacturer
# names; we collapse them to the same lowercase identifiers the
# patches/ tree uses ("st", "microchip", "nxp", "espressif",
# "raspberrypi").  Anything not in this map is dropped from the
# catalog with a stderr warning so the developer notices unmapped
# vendors rather than silently shipping noise.
_VENDOR_MAP: dict[str, str] = {
    "stmicroelectronics": "st",
    "st": "st",
    "microchip": "microchip",
    "atmel": "microchip",
    "nxp": "nxp",
    "freescale": "nxp",
    "espressif": "espressif",
    "raspberrypi": "raspberrypi",
    "raspberry pi": "raspberrypi",
    "rp": "raspberrypi",
}


@dataclass(frozen=True, slots=True)
class _MemoryRegion:
    name: str
    kind: str  # "flash" | "ram" | "eeprom" | "other"
    start: int
    length: int
    access: str  # "rwx" | "rx" | "rw" | "r"


@dataclass(frozen=True, slots=True)
class _KnownDevice:
    vendor: str
    family: str
    device: str
    probe_rs_target: str
    core: str
    memory_regions: tuple[_MemoryRegion, ...] = ()
    flash_algorithm: str | None = None
    source_pack: str | None = None


def _slugify(value: str) -> str:
    """Reduce probe-rs identifiers to lowercase alloy device IDs.

    Strips packaging suffixes (Tx, Px) and known marketing tokens to
    leave a part-number stem.  Conservative on purpose: when in
    doubt we lowercase + replace ``-``/``_``/whitespace with ``-``."""
    s = value.strip().lower()
    # Drop common ST package suffixes ("Tx" / "Px" / "Yx" / ...).
    s = re.sub(r"([0-9])[a-z]{1,2}x$", r"\1", s)
    # Squash run-of-non-alnum into a single dash.
    s = re.sub(r"[^a-z0-9]+", "-", s).strip("-")
    return s


def _classify_region_kind(name: str | None, access: str) -> str:
    if name:
        lower = name.lower()
        if any(token in lower for token in ("flash", "nvm", "rom", "boot")):
            return "flash"
        if any(token in lower for token in ("ram", "sram", "dtcm", "itcm", "ocram")):
            return "ram"
        if "eeprom" in lower:
            return "eeprom"
    if "x" in access and "w" not in access:
        return "flash"
    if "w" in access:
        return "ram"
    return "other"


def _normalise_access(access_text: str) -> str:
    """probe-rs encodes access as comma-separated ``read,write,execute``
    flags.  Reduce to the typical ``rwx``/``rx``/``rw``/``r`` shorthand."""
    flags = {token.strip().lower() for token in access_text.split(",") if token.strip()}
    out = []
    if "read" in flags:
        out.append("r")
    if "write" in flags:
        out.append("w")
    if "execute" in flags:
        out.append("x")
    return "".join(out) or "r"


def _parse_memory_map(memory_map_blocks: list[object]) -> tuple[_MemoryRegion, ...]:
    regions: list[_MemoryRegion] = []
    for block in memory_map_blocks:
        if not isinstance(block, dict) or len(block) != 1:
            continue
        ((kind_key, body),) = block.items()
        if not isinstance(body, dict):
            continue
        rng = body.get("range") or {}
        if not isinstance(rng, dict):
            continue
        try:
            start = int(rng["start"])
            end = int(rng["end"])
        except (KeyError, TypeError, ValueError):
            continue
        access = _normalise_access(str(body.get("access", "")))
        name = str(body.get("name", "") or kind_key)
        regions.append(
            _MemoryRegion(
                name=name,
                kind=_classify_region_kind(name, access),
                start=start,
                length=end - start,
                access=access,
            )
        )
    return tuple(regions)


def _resolve_alloy_family(target_name: str, vendor_id: str) -> str:
    """Map a probe-rs target name to alloy's family identifier.

    probe-rs uses the chip's full part number as target name
    (``STM32G071RBTx``).  The alloy family is the silicon series
    stem (``stm32g0``).  Conservative heuristic: pull the first 6-7
    chars after the vendor's marketing prefix, lowercased.
    """
    s = target_name.lower()
    if vendor_id == "st" and s.startswith("stm32"):
        # STM32G071RBTx → stm32g0 (first 7 chars).
        return s[: 7] if len(s) >= 7 else s
    if vendor_id == "microchip":
        if s.startswith("atsame70"):
            return "same70"
        if s.startswith("avr"):
            return "avr-da"
        if s.startswith("atsam"):
            return "sam" + s[5:8]  # broad fallback
    if vendor_id == "nxp" and s.startswith(("mimxrt", "imxrt")):
        # MIMXRT1062DVL6A → imxrt1060 (collapsing the trailing
        # speed-grade digit).
        digits = re.match(r"m?imxrt(\d{3})", s)
        if digits:
            return f"imxrt{digits.group(1)}0"
    if vendor_id == "espressif":
        if s.startswith("esp32-c3") or s == "esp32c3":
            return "esp32c3"
        if s.startswith("esp32-s3") or s == "esp32s3":
            return "esp32s3"
        if s.startswith("esp32"):
            return "esp32"
    if vendor_id == "raspberrypi" and s.startswith("rp2040"):
        return "rp2040"
    return s.split("-")[0]


def _parse_target_yaml(path: Path) -> list[_KnownDevice]:
    """Parse one ``targets/*.yaml`` into one or more ``_KnownDevice``
    rows (probe-rs targets sometimes pack multiple variants)."""
    try:
        import yaml  # type: ignore[import-not-found]
    except ImportError as exc:  # pragma: no cover - tooling-time import
        raise SystemExit(
            "PyYAML is required: re-run with `uv run --with pyyaml`"
        ) from exc

    payload = yaml.safe_load(path.read_text())
    if not isinstance(payload, dict):
        return []

    target_name = str(payload.get("name", "")).strip()
    if not target_name:
        return []

    manufacturer_block = payload.get("manufacturer") or {}
    if isinstance(manufacturer_block, dict):
        manufacturer = str(manufacturer_block.get("name", "")).strip()
    else:
        manufacturer = str(manufacturer_block).strip()
    vendor_id = _VENDOR_MAP.get(manufacturer.lower().replace(" ", ""))
    if vendor_id is None:
        # Try with raw lowercased name (no whitespace strip).
        vendor_id = _VENDOR_MAP.get(manufacturer.lower())
    if vendor_id is None:
        sys.stderr.write(
            f"[probe-rs] skipping {path.name}: unmapped vendor {manufacturer!r}\n"
        )
        return []

    flash_algorithms = payload.get("flash_algorithms") or []
    flash_algorithm = (
        str(flash_algorithms[0]).strip() if flash_algorithms else None
    )
    source_pack = (
        str(payload.get("generated_from_pack", "")).strip() or None
    )

    rows: list[_KnownDevice] = []
    variants = payload.get("variants") or []
    if not isinstance(variants, list):
        variants = []

    for variant in variants:
        if not isinstance(variant, dict):
            continue
        variant_name = str(variant.get("name", "")).strip() or target_name
        cores_block = variant.get("cores") or []
        core_type = ""
        if isinstance(cores_block, list) and cores_block:
            first = cores_block[0]
            if isinstance(first, dict):
                core_type = str(first.get("type", "")).strip()
        memory_map = variant.get("memory_map") or []
        if not isinstance(memory_map, list):
            memory_map = []
        family = _resolve_alloy_family(variant_name, vendor_id)
        rows.append(
            _KnownDevice(
                vendor=vendor_id,
                family=family,
                device=_slugify(variant_name),
                probe_rs_target=variant_name,
                core=core_type,
                memory_regions=_parse_memory_map(memory_map),
                flash_algorithm=flash_algorithm,
                source_pack=source_pack,
            )
        )
    if not rows:
        # Fall back to a single row keyed by the top-level target name
        # when the YAML has no nested variants (older probe-rs schema).
        rows.append(
            _KnownDevice(
                vendor=vendor_id,
                family=_resolve_alloy_family(target_name, vendor_id),
                device=_slugify(target_name),
                probe_rs_target=target_name,
                core="",
                memory_regions=(),
                flash_algorithm=flash_algorithm,
                source_pack=source_pack,
            )
        )
    return rows


def _resolve_probe_rs_sha(probe_rs_root: Path) -> str:
    """Return the commit SHA the importer is pinned to (HEAD of the
    checkout).  Best-effort: returns ``"unknown"`` if git is missing
    or the path is not a git repo."""
    try:
        out = subprocess.run(
            ["git", "rev-parse", "HEAD"],
            cwd=probe_rs_root,
            capture_output=True,
            text=True,
            check=False,
        )
        if out.returncode == 0:
            return out.stdout.strip()
    except (FileNotFoundError, OSError):
        pass
    return "unknown"


def _toml_escape(value: str) -> str:
    """Quote a string for inclusion in a basic TOML scalar."""
    escaped = value.replace("\\", "\\\\").replace('"', '\\"')
    return f'"{escaped}"'


def _emit_known_devices_toml(devices: list[_KnownDevice], output_path: Path) -> None:
    """Render the catalog to ``data/known_devices.toml`` deterministically.

    The TOML uses an array-of-tables keyed by ``[[device]]`` so the
    file remains diffable.  Entries are sorted by
    ``(vendor, family, device)`` for byte-stable output.
    """
    sorted_devices = sorted(devices, key=lambda d: (d.vendor, d.family, d.device))
    lines: list[str] = [
        "# Known-devices catalog imported from probe-rs/probe-rs.",
        "# Regenerated by `tools/import_probe_rs_targets.py` — see",
        "# `docs/known-devices.md` for the workflow.",
        "# Sorted by (vendor, family, device).  Read-only with respect to",
        "# the pipeline; alloy patches remain source of truth on conflict.",
        "",
    ]
    for device in sorted_devices:
        lines.append("[[device]]")
        lines.append(f"vendor = {_toml_escape(device.vendor)}")
        lines.append(f"family = {_toml_escape(device.family)}")
        lines.append(f"device = {_toml_escape(device.device)}")
        lines.append(f"probe_rs_target = {_toml_escape(device.probe_rs_target)}")
        if device.core:
            lines.append(f"core = {_toml_escape(device.core)}")
        if device.flash_algorithm:
            lines.append(f"flash_algorithm = {_toml_escape(device.flash_algorithm)}")
        if device.source_pack:
            lines.append(f"source_pack = {_toml_escape(device.source_pack)}")
        for region in device.memory_regions:
            lines.append("")
            lines.append("    [[device.memory_region]]")
            lines.append(f"    name = {_toml_escape(region.name)}")
            lines.append(f"    kind = {_toml_escape(region.kind)}")
            lines.append(f"    start = {region.start}")
            lines.append(f"    length = {region.length}")
            lines.append(f"    access = {_toml_escape(region.access)}")
        lines.append("")
    output_path.write_text("\n".join(lines).rstrip() + "\n")


def _emit_meta_toml(
    *,
    output_path: Path,
    probe_rs_sha: str,
    target_count: int,
    device_count: int,
    tool_version: str,
) -> None:
    """Pin metadata (SHA + import timestamp + tool version)."""
    timestamp = (
        os.environ.get("KNOWN_DEVICES_FROZEN_TIMESTAMP")
        or datetime.datetime.now(datetime.UTC).strftime("%Y-%m-%dT%H:%M:%SZ")
    )
    lines = [
        "# Pinned metadata for `data/known_devices.toml`.",
        "# Regenerate by re-running `tools/import_probe_rs_targets.py`",
        "# against a probe-rs checkout at the SHA below.",
        "",
        f"probe_rs_sha = {_toml_escape(probe_rs_sha)}",
        f"imported_at_utc = {_toml_escape(timestamp)}",
        f"tool_version = {_toml_escape(tool_version)}",
        f"target_yaml_count = {target_count}",
        f"device_count = {device_count}",
        "",
    ]
    output_path.write_text("\n".join(lines))


def _walk_target_yamls(probe_rs_root: Path) -> list[Path]:
    targets_dir = probe_rs_root / "probe-rs" / "targets"
    if not targets_dir.exists():
        # Fallback: caller may have pointed at the targets dir directly.
        targets_dir = probe_rs_root / "targets"
    if not targets_dir.exists():
        targets_dir = probe_rs_root
    return sorted(targets_dir.rglob("*.yaml"))


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--probe-rs-root",
        type=Path,
        required=True,
        help="Path to a probe-rs/probe-rs checkout (we read targets/*.yaml).",
    )
    parser.add_argument(
        "--output-dir",
        type=Path,
        default=Path("data"),
        help="Directory to write known_devices.toml + known_devices.meta.toml.",
    )
    parser.add_argument(
        "--tool-version",
        default="ingest-probe-rs-target-catalog/v1",
        help="Version label recorded in known_devices.meta.toml.",
    )
    args = parser.parse_args(argv)

    probe_rs_root: Path = args.probe_rs_root.resolve()
    output_dir: Path = args.output_dir.resolve()
    output_dir.mkdir(parents=True, exist_ok=True)

    target_paths = _walk_target_yamls(probe_rs_root)
    if not target_paths:
        sys.stderr.write(
            f"[probe-rs] no targets/*.yaml found under {probe_rs_root}\n"
        )
        return 2

    devices: list[_KnownDevice] = []
    for path in target_paths:
        devices.extend(_parse_target_yaml(path))

    catalog_path = output_dir / "known_devices.toml"
    meta_path = output_dir / "known_devices.meta.toml"

    _emit_known_devices_toml(devices, catalog_path)
    _emit_meta_toml(
        output_path=meta_path,
        probe_rs_sha=_resolve_probe_rs_sha(probe_rs_root),
        target_count=len(target_paths),
        device_count=len(devices),
        tool_version=args.tool_version,
    )

    sys.stdout.write(
        json.dumps(
            {
                "target_yaml_count": len(target_paths),
                "device_count": len(devices),
                "catalog_path": str(catalog_path),
                "meta_path": str(meta_path),
            },
            indent=2,
        )
        + "\n"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
