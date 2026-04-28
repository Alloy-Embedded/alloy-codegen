"""Bake tier 2/3/4 patch data into the canonical YAML.

One-shot migration script for
``consume-alloy-devices-yml-as-canonical-input`` Phase 3.

Background: every admitted device's canonical YAML is committed
to the ``alloy-devices-yml`` data repo, but the YAMLs were
extracted from raw vendor sources (SVD, DTS, ATDF, etc.) —
without the hand-curated tier 2/3/4 fields that
``alloy-codegen``'s ``patches/`` system applies post-load.

This script walks every (vendor, family, device) admitted by the
data repo, runs ``stages.normalize.run`` (which applies the
``patches/`` overlay during enrichment), and re-serialises the
fully-enriched IR back to its YAML location.  After the script
runs and the resulting YAMLs are committed to
``alloy-devices-yml``, the patch system can be deleted without
losing any IR data.

Usage::

    .venv/bin/python scripts/bake_tier_data_into_yaml.py [--dry-run]

The ``--dry-run`` flag reports the per-device diff size without
writing anything.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.canonical_device_yaml import serialize_device  # noqa: E402
from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.sources.alloy_devices_yml import device_yaml_path  # noqa: E402
from alloy_codegen.stages.normalize import run as run_normalize  # noqa: E402


def _discover_admitted_devices() -> list[tuple[str, str, str]]:
    """Walk ``data/devices/vendors/<vendor>/<family>/devices/`` and
    return every ``(vendor, family, device)`` triple that has a
    committed YAML."""
    base = ROOT / "data" / "devices" / "vendors"
    triples: list[tuple[str, str, str]] = []
    for vendor_dir in sorted(base.iterdir()):
        if not vendor_dir.is_dir():
            continue
        for family_dir in sorted(vendor_dir.iterdir()):
            if not family_dir.is_dir():
                continue
            devices_dir = family_dir / "devices"
            if not devices_dir.exists():
                continue
            for yml in sorted(devices_dir.glob("*.yml")):
                triples.append((vendor_dir.name, family_dir.name, yml.stem))
    return triples


def _bake_one(
    vendor: str,
    family: str,
    device: str,
    *,
    dry_run: bool,
) -> tuple[int, int]:
    """Re-serialise one device's YAML with patches baked in.

    Returns ``(before_bytes, after_bytes)`` for diff reporting.
    """
    ctx = ExecutionContext.default()
    bundle = run_normalize(PipelineScope(device=device), ctx)
    ir = bundle.payload.devices[0]
    new_text = serialize_device(ir)
    target = device_yaml_path(vendor=vendor, family=family, device=device)
    before = target.read_text(encoding="utf-8") if target.exists() else ""
    after = new_text
    if not dry_run and after != before:
        target.write_text(after, encoding="utf-8")
    return len(before), len(after)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Report per-device byte deltas without writing anything.",
    )
    args = parser.parse_args()

    triples = _discover_admitted_devices()
    if not triples:
        print("No devices found under data/devices/vendors/.", file=sys.stderr)
        return 1

    total_before = 0
    total_after = 0
    print(f"{'vendor/family/device':50}  {'before':>8}  {'after':>8}  {'Δ':>8}")
    print("-" * 86)
    for vendor, family, device in triples:
        before, after = _bake_one(vendor, family, device, dry_run=args.dry_run)
        delta = after - before
        total_before += before
        total_after += after
        triple = f"{vendor}/{family}/{device}"
        print(f"{triple:50}  {before:>8}  {after:>8}  {delta:>+8}")
    print("-" * 86)
    delta_total = total_after - total_before
    print(f"{'TOTAL':50}  {total_before:>8}  {total_after:>8}  {delta_total:>+8}")
    if args.dry_run:
        print("\n(dry-run; nothing written)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
