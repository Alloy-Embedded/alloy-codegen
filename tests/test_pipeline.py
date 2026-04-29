from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages import pipeline as pipeline_stage
from alloy_codegen.stages.common import StageResult


def test_pipeline_runs_all_stages(execution_context: ExecutionContext) -> None:
    result = pipeline_stage.run(PipelineScope(device="stm32g071rb"), execution_context)

    assert result.stage == "pipeline"
    # ``patch`` was removed by
    # consume-alloy-devices-yml-as-canonical-input Phase 3 — pipeline is
    # now fetch → normalize → validate → emit → publish.
    assert len(result.payload.results) == 5
    assert [stage.stage for stage in result.payload.results] == [
        "fetch",
        "normalize",
        "validate",
        "emit",
        "publish",
    ]


def test_pipeline_returns_failed_when_any_stage_fails(
    monkeypatch, execution_context: ExecutionContext
) -> None:
    scope = PipelineScope(vendor="st", family="stm32g0", device="stm32g071rb")

    def make_result(stage: str, status: str = "completed") -> StageResult:
        return StageResult(stage=stage, scope=scope, status=status, payload={"stage": stage})

    monkeypatch.setattr(pipeline_stage, "run_fetch", lambda _scope, _context: make_result("fetch"))
    monkeypatch.setattr(
        pipeline_stage, "run_normalize", lambda _scope, _context: make_result("normalize")
    )
    monkeypatch.setattr(
        pipeline_stage, "run_validate", lambda _scope, _context: make_result("validate", "failed")
    )
    monkeypatch.setattr(pipeline_stage, "run_emit", lambda _scope, _context: make_result("emit"))
    monkeypatch.setattr(
        pipeline_stage, "run_publish", lambda _scope, _context: make_result("publish", "failed")
    )

    result = pipeline_stage.run(PipelineScope(device="stm32g071rb"), execution_context)

    assert result.status == "failed"
    assert result.warnings == (
        "validate stage failed inside pipeline.",
        "publish stage failed inside pipeline.",
    )
    assert [stage.status for stage in result.payload.results] == [
        "completed",
        "completed",
        "failed",
        "completed",
        "failed",
    ]
