#!/usr/bin/env python3
"""Regenerate one or more canonical YAMLs from the legacy
`_build_<vendor>_device_ir` path.

Used after a deliberate change to a legacy IR builder, when
the parity gate from `add-codegen-yaml-parity-gate` flags drift
that is *intentional*.  This script writes the freshly-built IR
back into alloy-devices-yml so the next parity-gate run is green.

NEVER auto-invoked by CI — always a deliberate, reviewed action.

Usage:
    python scripts/regen_canonical_yamls.py \\
        --vendor st --family stm32g0 --device stm32g071rb

    # Or regenerate every admitted device for a family:
    python scripts/regen_canonical_yamls.py --vendor st --family stm32g0

    # Or every admitted device:
    python scripts/regen_canonical_yamls.py --all
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.bootstrap import DEVICE_REGISTRY  # noqa: E402
from alloy_codegen.canonical_device_yaml import serialize_device  # noqa: E402
from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.sources.alloy_devices_yml import (  # noqa: E402
    DATA_REPO_ROOT,
    device_yaml_path,
)
from alloy_codegen.vendors import resolve_vendor_adapter  # noqa: E402


def _devices_in_scope(args: argparse.Namespace) -> list[tuple[str, str, str]]:
    if args.all:
        return [
            (v, f, d)
            for (v, f), ds in DEVICE_REGISTRY.items()
            for d in ds
        ]
    if not args.vendor or not args.family:
        raise SystemExit(
            "must pass --all, or both --vendor and --family (and optionally --device)."
        )
    devices = DEVICE_REGISTRY.get((args.vendor, args.family), ())
    if not devices:
        raise SystemExit(f"no admitted devices for {args.vendor}/{args.family}.")
    if args.device:
        if args.device not in devices:
            raise SystemExit(
                f"device {args.device} is not admitted under "
                f"{args.vendor}/{args.family}; admitted: {devices}."
            )
        return [(args.vendor, args.family, args.device)]
    return [(args.vendor, args.family, d) for d in devices]


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(prog="regen_canonical_yamls")
    parser.add_argument("--all", action="store_true", help="Regenerate every admitted device.")
    parser.add_argument("--vendor")
    parser.add_argument("--family")
    parser.add_argument("--device")
    args = parser.parse_args(argv)

    targets = _devices_in_scope(args)
    if not DATA_REPO_ROOT.exists():
        raise SystemExit(
            f"alloy-devices-yml submodule not initialised at {DATA_REPO_ROOT}.  "
            "Run `git submodule update --init data/devices` first."
        )

    execution_context = ExecutionContext.default()
    rewrites: list[Path] = []
    for vendor, family, device in targets:
        adapter = resolve_vendor_adapter(vendor, family)
        ir = adapter.normalize(
            execution_context=execution_context,
            device_name=device,
            vendor=vendor,
            family=family,
        )
        text = serialize_device(ir)
        out_path = device_yaml_path(vendor=vendor, family=family, device=device)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        out_path.write_text(text, encoding="utf-8")
        rewrites.append(out_path)
        print(f"wrote {out_path}")

    print(f"\nRegenerated {len(rewrites)} YAML(s).  Review the diff with:")
    print("  cd data/devices && git diff")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
