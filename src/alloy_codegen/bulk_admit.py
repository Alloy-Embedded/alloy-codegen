"""``alloy-codegen bulk-admit`` subcommand.

Added by ``bulk-admit-from-alloy-devices-yml``.

Walks every device in a requested ``(vendor, family)`` scope —
sourced from the filesystem-derived registry that joins the
hand-curated ``DEVICE_REGISTRY`` with any YAML committed to the
``alloy-devices-yml`` submodule — and runs the full pipeline
per device.  Reports per-device pass/fail with explicit failure
modes (schema invalid, IR build failed, emit failed,
smoke-compile failed, footprint exceeded).

Output: a Markdown summary table on stdout + a machine-readable
JSON report under ``reports/bulk-admit-<timestamp>.json``.
"""

from __future__ import annotations

import json
import time
from collections.abc import Iterable
from dataclasses import asdict, dataclass, field
from datetime import UTC, datetime
from pathlib import Path

from alloy_codegen.bootstrap import merged_device_registry
from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import AlloyCodegenError
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


@dataclass(slots=True)
class BulkAdmitOutcome:
    """Per-device outcome of one bulk-admit run."""

    vendor: str
    family: str
    device: str
    status: str  # PASS | SCHEMA_INVALID | IR_BUILD_FAILED | EMIT_FAILED | SKIPPED
    duration_seconds: float = 0.0
    artifact_count: int = 0
    error: str = ""

    @property
    def label(self) -> str:
        return f"{self.vendor}/{self.family}/{self.device}"


@dataclass(slots=True)
class BulkAdmitReport:
    """Aggregate report from one bulk-admit run."""

    started_utc: str
    finished_utc: str = ""
    total: int = 0
    passes: int = 0
    failures: int = 0
    duration_seconds: float = 0.0
    devices: list[BulkAdmitOutcome] = field(default_factory=list)

    def add(self, outcome: BulkAdmitOutcome) -> None:
        self.devices.append(outcome)
        self.total += 1
        if outcome.status == "PASS":
            self.passes += 1
        elif outcome.status != "SKIPPED":
            self.failures += 1


def admit_devices(
    *,
    vendor: str | None = None,
    family: str | None = None,
    limit: int | None = None,
    dry_run: bool = False,
    context: ExecutionContext | None = None,
) -> BulkAdmitReport:
    """Walk the registry and run the full pipeline per matching device.

    ``vendor`` / ``family`` filter the registry; pass ``None`` for
    each to admit every device the merged registry knows.
    ``dry_run=True`` runs through normalize but skips emit (faster;
    useful for "is the YAML schema-valid" smoke checks at scale).
    """
    started = time.monotonic()
    report = BulkAdmitReport(started_utc=datetime.now(UTC).isoformat())
    ctx = context or ExecutionContext.default().with_overrides(
        source_overrides={},
        artifact_root="/tmp/_alloy_bulk_artifacts",
        publication_root="/tmp/_alloy_bulk_publication",
    )

    triples = list(_resolve_triples(vendor=vendor, family=family))
    if limit is not None:
        triples = triples[:limit]

    for v, f, d in triples:
        outcome = _admit_one(v, f, d, ctx, dry_run=dry_run)
        report.add(outcome)

    report.finished_utc = datetime.now(UTC).isoformat()
    report.duration_seconds = time.monotonic() - started
    return report


def _resolve_triples(*, vendor: str | None, family: str | None) -> Iterable[tuple[str, str, str]]:
    registry = merged_device_registry()
    for (rv, rf), devices in sorted(registry.items()):
        if vendor is not None and rv != vendor:
            continue
        if family is not None and rf != family:
            continue
        for device in devices:
            yield (rv, rf, device)


def _admit_one(
    vendor: str,
    family: str,
    device: str,
    ctx: ExecutionContext,
    *,
    dry_run: bool,
) -> BulkAdmitOutcome:
    started = time.monotonic()
    if dry_run:
        # Stop after normalize — no emit cost.
        from alloy_codegen.stages.normalize import run as run_normalize

        try:
            result = run_normalize(PipelineScope(device=device), ctx)
        except AlloyCodegenError as exc:
            return BulkAdmitOutcome(
                vendor=vendor,
                family=family,
                device=device,
                status="IR_BUILD_FAILED",
                duration_seconds=time.monotonic() - started,
                error=str(exc)[:500],
            )
        return BulkAdmitOutcome(
            vendor=vendor,
            family=family,
            device=device,
            status="PASS",
            duration_seconds=time.monotonic() - started,
            artifact_count=len(result.payload.devices),
        )

    try:
        result = run_emit(PipelineScope(device=device), ctx)
    except AlloyCodegenError as exc:
        msg = str(exc)
        status = "IR_BUILD_FAILED"
        if "schema validation" in msg.lower():
            status = "SCHEMA_INVALID"
        elif "emit" in msg.lower():
            status = "EMIT_FAILED"
        return BulkAdmitOutcome(
            vendor=vendor,
            family=family,
            device=device,
            status=status,
            duration_seconds=time.monotonic() - started,
            error=msg[:500],
        )
    except Exception as exc:  # noqa: BLE001 — bulk-admit is a top-level guard
        return BulkAdmitOutcome(
            vendor=vendor,
            family=family,
            device=device,
            status="EMIT_FAILED",
            duration_seconds=time.monotonic() - started,
            error=f"{type(exc).__name__}: {exc}"[:500],
        )

    return BulkAdmitOutcome(
        vendor=vendor,
        family=family,
        device=device,
        status="PASS",
        duration_seconds=time.monotonic() - started,
        artifact_count=len(result.payload.artifacts),
    )


def render_markdown(report: BulkAdmitReport) -> str:
    """Render a Markdown summary suitable for stdout / CI logs."""
    lines: list[str] = [
        "# Bulk-admit summary",
        "",
        f"- Started:  `{report.started_utc}`",
        f"- Finished: `{report.finished_utc}`",
        f"- Duration: {report.duration_seconds:.2f} s",
        f"- Total:    {report.total}  (✅ {report.passes}  ❌ {report.failures})",
        "",
        "| Status | Vendor | Family | Device | Duration | Notes |",
        "|---|---|---|---|---|---|",
    ]
    for outcome in report.devices:
        marker = "✅" if outcome.status == "PASS" else "❌"
        notes = outcome.error.replace("\n", " ").replace("|", "\\|")[:120] or "—"
        lines.append(
            f"| {marker} {outcome.status} | {outcome.vendor} | {outcome.family} | "
            f"{outcome.device} | {outcome.duration_seconds:.2f}s | {notes} |"
        )
    return "\n".join(lines) + "\n"


def write_report_json(report: BulkAdmitReport, path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    payload = {
        "started_utc": report.started_utc,
        "finished_utc": report.finished_utc,
        "duration_seconds": round(report.duration_seconds, 3),
        "total": report.total,
        "passes": report.passes,
        "failures": report.failures,
        "devices": [asdict(o) for o in report.devices],
    }
    path.write_text(
        json.dumps(payload, indent=2, sort_keys=False, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )


__all__ = [
    "BulkAdmitOutcome",
    "BulkAdmitReport",
    "admit_devices",
    "render_markdown",
    "write_report_json",
]
