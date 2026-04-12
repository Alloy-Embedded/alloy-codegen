"""Command-line interface for alloy-codegen."""

from __future__ import annotations

import argparse
import json
import sys
from collections.abc import Sequence

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, BOOTSTRAP_VENDOR, supported_families
from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import AlloyCodegenError
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages import STAGE_RUNNERS
from alloy_codegen.stages.common import StageResult


def parse_source_overrides(items: Sequence[str]) -> dict[str, str]:
    """Parse repeated ``SOURCE_ID=PATH`` CLI arguments into a stable mapping."""
    overrides: dict[str, str] = {}
    for item in items:
        source_id, separator, source_path = item.partition("=")
        if separator != "=" or not source_id or not source_path:
            raise argparse.ArgumentTypeError(
                f"Invalid --source value {item!r}. Expected SOURCE_ID=PATH."
            )
        overrides[source_id.strip().lower()] = source_path.strip()
    return overrides


def build_parser() -> argparse.ArgumentParser:
    """Create the top-level CLI parser."""
    parser = argparse.ArgumentParser(prog="alloy-codegen", description="Alloy codegen pipeline.")
    subparsers = parser.add_subparsers(dest="stage", required=True)

    targets_parser = subparsers.add_parser(
        "targets",
        help="List supported vendor/family/device targets and their source bundles.",
    )
    targets_parser.add_argument("--vendor", default=None, help="Optional vendor filter.")
    targets_parser.add_argument("--family", default=None, help="Optional family filter.")
    targets_parser.add_argument(
        "--json",
        action="store_true",
        help="Emit machine-readable JSON instead of human-readable text.",
    )

    for stage_name in STAGE_RUNNERS:
        stage_parser = subparsers.add_parser(stage_name, help=f"Run the {stage_name} stage.")
        stage_parser.add_argument(
            "--vendor",
            default=None,
            help="Vendor scope. Defaults to bootstrap vendor.",
        )
        stage_parser.add_argument(
            "--family",
            default=None,
            help="Family scope. Defaults to bootstrap family.",
        )
        stage_parser.add_argument("--device", default=None, help="Optional device scope.")
        stage_parser.add_argument(
            "--source",
            action="append",
            default=[],
            metavar="SOURCE_ID=PATH",
            help=(
                "Optional logical source override. May be passed multiple times, "
                "for example --source cmsis-svd-data=/path/to/checkout."
            ),
        )
        stage_parser.add_argument(
            "--patch-root",
            default=None,
            help="Optional patch root override.",
        )
        stage_parser.add_argument(
            "--cache-dir",
            default=None,
            help="Optional source cache directory override.",
        )
        stage_parser.add_argument(
            "--artifact-root",
            default=None,
            help="Optional artifact output root override.",
        )
        stage_parser.add_argument(
            "--publication-root",
            default=None,
            help="Optional alloy-devices publication root override.",
        )
        stage_parser.add_argument(
            "--alloy-root",
            default=None,
            help="Optional Alloy checkout root used for consumer verification.",
        )
        stage_parser.add_argument(
            "--json",
            action="store_true",
            help="Emit machine-readable JSON instead of human-readable text.",
        )

    return parser


def build_targets_payload(
    *,
    vendor: str | None = None,
    family: str | None = None,
) -> dict[str, object]:
    """Return the supported target matrix as a stable payload."""
    entries = supported_families(vendor=vendor, family=family)
    return {
        "default_scope": {
            "vendor": BOOTSTRAP_VENDOR,
            "family": BOOTSTRAP_FAMILY,
        },
        "targets": [entry.to_dict() for entry in entries],
    }


def format_targets_payload(payload: dict[str, object]) -> str:
    """Render the supported target matrix in a readable plain-text form."""
    lines = [
        "default target: "
        f"{payload['default_scope']['vendor']}/{payload['default_scope']['family']}",
        "supported targets:",
    ]
    for entry in payload["targets"]:
        default_suffix = " (default)" if entry["is_default"] else ""
        devices = ", ".join(entry["devices"])
        sources = ", ".join(entry["source_bundles"])
        lines.append(
            f"- {entry['vendor']}/{entry['family']}{default_suffix}: "
            f"devices=[{devices}] sources=[{sources}]"
        )
    return "\n".join(lines)


def main(argv: Sequence[str] | None = None) -> int:
    """CLI entrypoint."""
    parser = build_parser()
    args = parser.parse_args(list(argv) if argv is not None else None)
    if args.stage == "targets":
        try:
            payload = build_targets_payload(vendor=args.vendor, family=args.family)
        except AlloyCodegenError as exc:
            if args.json:
                print(json.dumps({"error": str(exc)}, sort_keys=True))
            else:
                print(f"error: {exc}", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(payload, indent=2, sort_keys=True))
        else:
            print(format_targets_payload(payload))
        return 0

    scope = PipelineScope(vendor=args.vendor, family=args.family, device=args.device)
    source_overrides = parse_source_overrides(args.source)
    context = ExecutionContext.default().with_overrides(
        source_overrides=source_overrides,
        patch_root=args.patch_root,
        cache_dir=args.cache_dir,
        artifact_root=args.artifact_root,
        publication_root=args.publication_root,
        alloy_root=args.alloy_root,
    )

    try:
        result = STAGE_RUNNERS[args.stage](scope, context)
    except AlloyCodegenError as exc:
        if args.json:
            print(json.dumps({"error": str(exc)}, sort_keys=True))
        else:
            print(f"error: {exc}", file=sys.stderr)
        return 1

    if args.json:
        print(json.dumps(result.to_dict(), indent=2, sort_keys=True))
    else:
        print(f"{result.stage}: {result.status} [{result.scope.display_name()}]")
    return determine_exit_code(result)


def determine_exit_code(result: StageResult) -> int:
    """Map stage results to process exit codes for local and CI use."""
    return 0 if result.is_successful else 1


if __name__ == "__main__":
    raise SystemExit(main())
