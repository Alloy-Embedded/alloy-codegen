"""Full pipeline execution."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.fetch import run as run_fetch
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.publish import run as run_publish
from alloy_codegen.stages.validate import run as run_validate


@dataclass(frozen=True, slots=True)
class PipelineRun:
    """Aggregate result for the full pipeline."""

    results: tuple[StageResult, ...]


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the full pipeline sequentially."""
    execution_context = context or ExecutionContext.default()
    results = (
        run_fetch(scope, execution_context),
        run_normalize(scope, execution_context),
        run_validate(scope, execution_context),
        run_emit(scope, execution_context),
        run_publish(scope, execution_context),
    )
    failed_stages = tuple(result.stage for result in results if result.is_failed)
    return StageResult(
        stage="pipeline",
        scope=results[-1].scope,
        status="completed" if not failed_stages else "failed",
        payload=PipelineRun(results=results),
        warnings=tuple(f"{stage} stage failed inside pipeline." for stage in failed_stages),
    )
