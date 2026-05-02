"""Command-line entry point for alloy-codegen v2.1.

Usage::

    alloy-codegen <vendor>/<family>/<chip>           # all artifacts
    alloy-codegen <vendor>/<family>/<chip> --out DIR
    alloy-codegen <vendor>/<family>/<chip> --emit linker_script
    alloy-codegen --list                              # admitted devices

Produces an artifact tree under ``--out`` (default
``./out/<vendor>/<family>/<chip>/``)::

    out/<v>/<f>/<chip>/
    ├── peripheral_traits.h
    ├── runtime_init.c
    ├── linker.ld
    └── vector_table.c

The CLI is a thin shell — every emitter is a pure function
``(CanonicalDevice, SynthesisedDevice) -> str``.  Adding a new
emitter is just registering it in :data:`_EMITTERS`.
"""

from __future__ import annotations

import argparse
import sys
from collections.abc import Callable
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.bootstrap import DEVICE_REGISTRY, CANONICAL_SCHEMA
from alloy_codegen.emit_v2_1 import (
    emit_linker_script,
    emit_peripheral_traits,
    emit_runtime_init,
    emit_vector_table,
)
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.synthesised import SynthesisedDevice, build_synthesised
from alloy_codegen.ir.v2_1 import CanonicalDevice
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


@dataclass(frozen=True, slots=True)
class _EmitterEntry:
    name: str
    filename: str
    fn: Callable[[CanonicalDevice, SynthesisedDevice], str]
    description: str


_EMITTERS: tuple[_EmitterEntry, ...] = (
    _EmitterEntry(
        name="linker_script",
        filename="linker.ld",
        fn=lambda d, _s: emit_linker_script(d),
        description="GNU LD script — memory map + stack symbols.",
    ),
    _EmitterEntry(
        name="vector_table",
        filename="vector_table.c",
        fn=emit_vector_table,
        description="ISR vector table (or matrix-router stub).",
    ),
    _EmitterEntry(
        name="peripheral_traits",
        filename="peripheral_traits.h",
        fn=emit_peripheral_traits,
        description="C++ constexpr traits per peripheral + per-template fields.",
    ),
    _EmitterEntry(
        name="runtime_init",
        filename="runtime_init.c",
        fn=emit_runtime_init,
        description="RouteOperation table + clock-profile dispatch shells.",
    ),
)


def _emitter_by_name(name: str) -> _EmitterEntry:
    for e in _EMITTERS:
        if e.name == name:
            return e
    available = ", ".join(e.name for e in _EMITTERS)
    raise SystemExit(f"unknown emitter '{name}'.  Available: {available}")


def _parse_target(target: str) -> tuple[str, str, str]:
    """Accept ``<vendor>/<family>/<chip>`` or ``<vendor>/<chip>``
    (the latter resolves the family from the bootstrap registry).
    """
    parts = target.split("/")
    if len(parts) == 3:
        return parts[0], parts[1], parts[2]
    if len(parts) == 2:
        vendor, chip = parts
        # Look up the family by walking the registry.
        for (v, f), devices in DEVICE_REGISTRY.items():
            if v == vendor and chip in devices:
                return vendor, f, chip
        raise SystemExit(
            f"chip '{chip}' not found under vendor '{vendor}'.  "
            f"Use the explicit <vendor>/<family>/<chip> form, or "
            f"`alloy-codegen --list` to see admitted devices."
        )
    raise SystemExit(
        f"invalid target {target!r}.  Use <vendor>/<family>/<chip> "
        f"or <vendor>/<chip>."
    )


def _list_devices() -> int:
    print(f"# alloy-codegen — admitted devices ({CANONICAL_SCHEMA})")
    print()
    for (vendor, family), devices in sorted(DEVICE_REGISTRY.items()):
        print(f"## {vendor} / {family}")
        for d in devices:
            print(f"  - {vendor}/{family}/{d}")
        print()
    print(f"Total: {sum(len(v) for v in DEVICE_REGISTRY.values())} devices")
    return 0


def _run(target: str, out_root: Path, only: list[str] | None) -> int:
    vendor, family, device = _parse_target(target)
    try:
        canonical, synthesised = load_with_synthesis(
            vendor=vendor, family=family, device=device,
        )
    except StageExecutionError as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2

    out_dir = out_root / vendor / family / device
    out_dir.mkdir(parents=True, exist_ok=True)

    selected = _EMITTERS if not only else tuple(_emitter_by_name(n) for n in only)
    written = 0
    for emitter in selected:
        text = emitter.fn(canonical, synthesised)
        out_path = out_dir / emitter.filename
        out_path.write_text(text, encoding="utf-8")
        written += 1
        print(f"  wrote {out_path.relative_to(out_root.parent if out_root.parent.exists() else out_root)}"
              f"  ({len(text):>6} bytes, {text.count(chr(10)):>4} lines)")
    print(f"\n{written} artifact(s) emitted under {out_dir}")
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="alloy-codegen",
        description=__doc__,
    )
    parser.add_argument(
        "target",
        nargs="?",
        help="<vendor>/<family>/<chip> or <vendor>/<chip>",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=Path("out"),
        help="output root directory (default: ./out)",
    )
    parser.add_argument(
        "--emit",
        action="append",
        default=None,
        help=(
            "emit only the named artifact(s).  Repeat to emit several.  "
            "Available: " + ", ".join(e.name for e in _EMITTERS)
        ),
    )
    parser.add_argument(
        "--list",
        action="store_true",
        help="list every admitted device and exit",
    )
    args = parser.parse_args(argv)

    if args.list:
        return _list_devices()
    if not args.target:
        parser.error("missing <target> (use --list to see admitted devices)")
    return _run(args.target, args.out, args.emit)


if __name__ == "__main__":
    raise SystemExit(main())
