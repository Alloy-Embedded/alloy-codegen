from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def test_generated_artifacts_stay_descriptor_oriented(
    execution_context: ExecutionContext,
) -> None:
    result = run_emit(PipelineScope(device="stm32g071rb"), execution_context)
    generated_artifacts = [
        artifact
        for artifact in result.payload.artifacts
        if artifact.artifact_kind == "generated-cpp" and artifact.content is not None
    ]
    forbidden_tokens = (
        "namespace alloy",
        "connect(",
        "claim(",
        "take(",
        "board::",
        "class Uart",
        "class Spi",
        "class I2c",
        "class Gpio",
    )

    assert generated_artifacts
    for artifact in generated_artifacts:
        assert artifact.path.startswith("st/stm32g0/generated/")
        for token in forbidden_tokens:
            assert token not in artifact.content, f"{artifact.path} leaked runtime token {token!r}"
