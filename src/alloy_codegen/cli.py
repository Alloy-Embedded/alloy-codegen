"""Command-line interface for alloy-codegen."""

from __future__ import annotations

import argparse
import json
import sys
from collections.abc import Sequence

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, BOOTSTRAP_VENDOR, supported_families
from alloy_codegen.config_cli import (
    build_runtime_config_template,
    format_runtime_config_template,
    load_runtime_config_schema,
)
from alloy_codegen.config_diagnostics import (
    diagnose_runtime_config,
    format_runtime_config_diagnosis,
)
from alloy_codegen.config_examples import (
    format_runtime_config_examples,
    generate_runtime_config_examples,
)
from alloy_codegen.config_recipes import (
    format_runtime_config_recipe,
    generate_runtime_config_recipe,
)
from alloy_codegen.context import ExecutionContext
from alloy_codegen.diagnostics_cli import (
    diff_runtime_capabilities,
    explain_runtime_fact,
    format_diff_result,
    format_explain_result,
)
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

    def add_context_args(stage_parser: argparse.ArgumentParser) -> None:
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
        add_context_args(stage_parser)

    explain_parser = subparsers.add_parser(
        "explain",
        help="Explain one emitted runtime fact for a device.",
    )
    explain_parser.add_argument("--device", required=True, help="Device to inspect.")
    explain_parser.add_argument("--fact", required=True, help="Fact or decision id to explain.")
    add_context_args(explain_parser)

    diff_parser = subparsers.add_parser(
        "diff",
        help="Compare runtime capability deltas between two devices.",
    )
    diff_parser.add_argument("--from", dest="from_device", required=True, help="Baseline device.")
    diff_parser.add_argument("--to", dest="to_device", required=True, help="Target device.")
    add_context_args(diff_parser)

    config_schema_parser = subparsers.add_parser(
        "config-schema",
        help="Print the declarative runtime configuration request schema.",
    )
    config_schema_parser.add_argument(
        "--json",
        action="store_true",
        help="Emit machine-readable JSON instead of human-readable text.",
    )

    config_template_parser = subparsers.add_parser(
        "config-template",
        help="Print a declarative runtime configuration template for one device.",
    )
    config_template_parser.add_argument("--device", required=True, help="Device to template.")
    add_context_args(config_template_parser)

    config_diagnose_parser = subparsers.add_parser(
        "config-diagnose",
        help="Diagnose one declarative runtime configuration request.",
    )
    config_diagnose_parser.add_argument(
        "--file",
        required=True,
        dest="request_file",
        help="Path to a runtime config request JSON file.",
    )
    add_context_args(config_diagnose_parser)

    config_recipe_parser = subparsers.add_parser(
        "config-recipe",
        help="Render a resolved runtime recipe from one declarative config request.",
    )
    config_recipe_parser.add_argument(
        "--file",
        required=True,
        dest="request_file",
        help="Path to a runtime config request JSON file.",
    )
    add_context_args(config_recipe_parser)

    config_example_parser = subparsers.add_parser(
        "config-example",
        help="Render example-ready outputs from one declarative config request.",
    )
    config_example_parser.add_argument(
        "--file",
        required=True,
        dest="request_file",
        help="Path to a runtime config request JSON file.",
    )
    add_context_args(config_example_parser)

    affected_parser = subparsers.add_parser(
        "affected-families",
        help=(
            "Compute the (vendor, family) set whose published artefacts a git diff "
            "affects.  Used by the publish workflow to scope its matrix dynamically."
        ),
    )
    affected_parser.add_argument(
        "--since",
        required=True,
        help="Git ref to diff against HEAD (e.g. HEAD~1, origin/main).",
    )
    affected_parser.add_argument(
        "--head",
        default="HEAD",
        help="Git ref representing the new tip (default: HEAD).",
    )
    affected_parser.add_argument(
        "--force-all",
        action="store_true",
        help="Bypass diff detection and return the full admitted set.",
    )
    affected_parser.add_argument(
        "--json",
        action="store_true",
        default=True,
        help="Emit machine-readable JSON (default).",
    )
    affected_parser.add_argument(
        "--plain",
        dest="json",
        action="store_false",
        help="Emit one '<vendor>/<family>' per line instead of JSON.",
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

    if args.stage == "config-schema":
        schema = load_runtime_config_schema()
        if args.json:
            print(json.dumps(schema, indent=2, sort_keys=True))
        else:
            print(f"{schema['title']} [{schema['$id']}]")
            print("required:", ", ".join(schema["required"]))
        return 0

    if args.stage == "affected-families":
        from alloy_codegen.affected_families import (
            compute_affected_from_git,
            serialize_affected_set,
        )

        affected = compute_affected_from_git(
            since=args.since,
            head=args.head,
            force_all=bool(args.force_all),
        )
        if args.json:
            payload = serialize_affected_set(affected, since=args.since, head=args.head)
            print(json.dumps(payload, indent=2, sort_keys=True))
        else:
            for vendor, family in affected.families:
                print(f"{vendor}/{family}")
        return 0

    source_overrides = parse_source_overrides(args.source)
    context = ExecutionContext.default().with_overrides(
        source_overrides=source_overrides,
        patch_root=args.patch_root,
        cache_dir=args.cache_dir,
        artifact_root=args.artifact_root,
        publication_root=args.publication_root,
        alloy_root=args.alloy_root,
    )

    if args.stage == "explain":
        try:
            result = explain_runtime_fact(
                device_name=args.device,
                fact=args.fact,
                context=context,
            )
        except AlloyCodegenError as exc:
            if args.json:
                print(json.dumps({"error": str(exc)}, sort_keys=True))
            else:
                print(f"error: {exc}", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(result.to_dict(), indent=2, sort_keys=True))
        else:
            print(format_explain_result(result))
        return 0

    if args.stage == "diff":
        try:
            result = diff_runtime_capabilities(
                from_device=args.from_device,
                to_device=args.to_device,
                context=context,
            )
        except AlloyCodegenError as exc:
            if args.json:
                print(json.dumps({"error": str(exc)}, sort_keys=True))
            else:
                print(f"error: {exc}", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(result.to_dict(), indent=2, sort_keys=True))
        else:
            print(format_diff_result(result))
        return 0

    if args.stage == "config-template":
        try:
            result = build_runtime_config_template(device_name=args.device, context=context)
        except AlloyCodegenError as exc:
            if args.json:
                print(json.dumps({"error": str(exc)}, sort_keys=True))
            else:
                print(f"error: {exc}", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(result, indent=2, sort_keys=True))
        else:
            print(format_runtime_config_template(result))
        return 0

    if args.stage == "config-diagnose":
        try:
            result = diagnose_runtime_config(request_path=args.request_file, context=context)
        except AlloyCodegenError as exc:
            if args.json:
                print(json.dumps({"error": str(exc)}, sort_keys=True))
            else:
                print(f"error: {exc}", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(result.to_dict(), indent=2, sort_keys=True))
        else:
            print(format_runtime_config_diagnosis(result))
        return 0 if result.is_valid else 1

    if args.stage == "config-recipe":
        try:
            result = generate_runtime_config_recipe(request_path=args.request_file, context=context)
        except AlloyCodegenError as exc:
            if args.json:
                print(json.dumps({"error": str(exc)}, sort_keys=True))
            else:
                print(f"error: {exc}", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(result.to_dict(), indent=2, sort_keys=True))
        else:
            print(format_runtime_config_recipe(result))
        return 0

    if args.stage == "config-example":
        try:
            result = generate_runtime_config_examples(
                request_path=args.request_file,
                context=context,
            )
        except AlloyCodegenError as exc:
            if args.json:
                print(json.dumps({"error": str(exc)}, sort_keys=True))
            else:
                print(f"error: {exc}", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(result.to_dict(), indent=2, sort_keys=True))
        else:
            print(format_runtime_config_examples(result))
        return 0

    scope = PipelineScope(vendor=args.vendor, family=args.family, device=args.device)

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
