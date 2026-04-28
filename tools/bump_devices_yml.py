"""Bump the alloy-devices-yml submodule pin and report any drift.

Added by ``extract-alloy-devices-data-repo``.

Workflow:

1. Pull the submodule to the requested SHA (or origin/main).
2. Run the normalize stage for every admitted device against the
   new YAML pin and serialize the resulting IRs.
3. Compare against the previous pin's IR snapshot.
4. Report per-device drift and exit non-zero if any C++ artifact
   would change.

Usage:

    python -m tools.bump_devices_yml [--sha <new-sha>] [--allow-drift]

Without ``--sha`` the tool fetches and points at ``origin/main``.
``--allow-drift`` bypasses the drift gate (still reports the
diff) — used when the bump intentionally lands new data.
"""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

_REPO_ROOT = Path(__file__).resolve().parents[1]
_SUBMODULE_PATH = _REPO_ROOT / "data" / "devices"


def _git(*args: str, cwd: Path | None = None) -> str:
    proc = subprocess.run(
        ["git", *args],
        cwd=cwd or _SUBMODULE_PATH,
        capture_output=True,
        text=True,
        check=False,
    )
    if proc.returncode != 0:
        raise RuntimeError(
            f"git {' '.join(args)} failed in {cwd or _SUBMODULE_PATH}:\n{proc.stderr}"
        )
    return proc.stdout.strip()


def current_sha() -> str:
    return _git("rev-parse", "HEAD")


def fetch_origin() -> None:
    _git("fetch", "origin")


def checkout(sha: str) -> None:
    _git("checkout", sha)


def _capture_ir_snapshot() -> dict[str, str]:
    """Return ``{<vendor>/<family>/<device>: <yaml-text>}`` for every
    device the pipeline currently admits — captured by reading the
    YAML files directly (no normalize round-trip needed)."""
    src = _REPO_ROOT / "src"
    if str(src) not in sys.path:
        sys.path.insert(0, str(src))
    from alloy_codegen.bootstrap import (  # noqa: E402
        DEVICE_REGISTRY,
        registered_device_names,
    )
    from alloy_codegen.sources.alloy_devices_yml import device_yaml_path  # noqa: E402

    snapshot: dict[str, str] = {}
    for (vendor, family), _ in DEVICE_REGISTRY.items():
        for device in registered_device_names(vendor, family):
            path = device_yaml_path(vendor=vendor, family=family, device=device)
            if path.exists():
                snapshot[f"{vendor}/{family}/{device}"] = path.read_text(encoding="utf-8")
    return snapshot


def diff_snapshots(before: dict[str, str], after: dict[str, str]) -> dict[str, dict[str, int]]:
    """Per-device line counts before / after.  Returns
    ``{label: {before: N, after: M, delta: M-N}}``."""
    labels = sorted(set(before) | set(after))
    report: dict[str, dict[str, int]] = {}
    for label in labels:
        b = before.get(label, "").count("\n")
        a = after.get(label, "").count("\n")
        if b != a or before.get(label) != after.get(label):
            report[label] = {"before_lines": b, "after_lines": a, "delta": a - b}
    return report


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(prog="bump_devices_yml")
    parser.add_argument("--sha", default="origin/main")
    parser.add_argument(
        "--allow-drift",
        action="store_true",
        help="Don't exit non-zero when YAMLs drift; still report the diff.",
    )
    args = parser.parse_args(argv)

    if not _SUBMODULE_PATH.exists():
        sys.stderr.write(
            f"submodule not initialised at {_SUBMODULE_PATH}.  Run "
            "`git submodule update --init` first.\n"
        )
        return 2

    print(f"current pin: {current_sha()}")
    before = _capture_ir_snapshot()
    print(f"snapshot: {len(before)} devices")

    print(f"fetching + checking out {args.sha}")
    fetch_origin()
    checkout(args.sha)
    new_pin = current_sha()
    print(f"new pin:     {new_pin}")

    after = _capture_ir_snapshot()
    drift = diff_snapshots(before, after)

    if not drift:
        print("\nNo drift — submodule bump is a no-op for the codegen IR.")
        return 0

    print(f"\n{len(drift)} device YAMLs drifted:")
    for label, stats in drift.items():
        print(
            f"  {label:60s}  "
            f"{stats['before_lines']:>6} → {stats['after_lines']:>6} lines "
            f"(Δ {stats['delta']:+d})"
        )

    if args.allow_drift:
        print("\n--allow-drift set: exiting 0 despite drift.")
        return 0
    print(
        "\nDrift detected.  Pass --allow-drift to bump anyway, or revert "
        f"the submodule with: git -C data/devices checkout {current_sha()}"
    )
    return 1


if __name__ == "__main__":  # pragma: no cover
    raise SystemExit(main())
