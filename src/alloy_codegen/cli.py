"""Command-line interface for alloy-codegen."""

from __future__ import annotations

import argparse
import json
import sys
from collections.abc import Sequence

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import AlloyCodegenError
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages import STAGE_RUNNERS
from alloy_codegen.stages.common import StageResult


def build_parser() -> argparse.ArgumentParser:
    """Create the top-level CLI parser."""
    parser = argparse.ArgumentParser(prog="alloy-codegen", description="Alloy codegen pipeline.")
    subparsers = parser.add_subparsers(dest="stage", required=True)

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
            "--source-root",
            default=None,
            help="Optional local cmsis-svd-data checkout to use instead of the cache clone.",
        )
        stage_parser.add_argument(
            "--pin-source-root",
            default=None,
            help=(
                "Optional local STM32_open_pin_data checkout to use instead of the cache clone."
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


def main(argv: Sequence[str] | None = None) -> int:
    """CLI entrypoint."""
    parser = build_parser()
    args = parser.parse_args(list(argv) if argv is not None else None)
    scope = PipelineScope(vendor=args.vendor, family=args.family, device=args.device)
    context = ExecutionContext.default().with_overrides(
        source_root=args.source_root,
        pin_source_root=args.pin_source_root,
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
