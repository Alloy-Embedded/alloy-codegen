from __future__ import annotations

from collections.abc import Iterable

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _family_contexts(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> tuple[tuple[PipelineScope, ExecutionContext], ...]:
    return (
        (PipelineScope(vendor="st", family="stm32g0"), execution_context),
        (PipelineScope(vendor="st", family="stm32f4"), execution_context),
        (PipelineScope(vendor="microchip", family="same70"), microchip_execution_context),
        (PipelineScope(vendor="nxp", family="imxrt1060"), nxp_execution_context),
    )


def _assert_descriptor_only_generated_artifacts(
    *,
    family_dir: str,
    generated_paths: Iterable[tuple[str, str]],
) -> None:
    forbidden_tokens = (
        "namespace alloy",
        "alloy::",
        "connect(",
        "claim(",
        "take(",
        "board::",
        "class Uart",
        "class Spi",
        "class I2c",
        "class Gpio",
        "ResourceToken",
        "Singleton",
    )
    for path, content in generated_paths:
        assert path.startswith(f"{family_dir}/generated/")
        for token in forbidden_tokens:
            assert token not in content, f"{path} leaked runtime token {token!r}"


def test_generated_artifacts_stay_descriptor_oriented(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
    ):
        result = run_emit(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        generated_artifacts = tuple(
            (artifact.path, artifact.content)
            for artifact in result.payload.artifacts
            if artifact.artifact_kind == "generated-cpp" and artifact.content is not None
        )

        assert generated_artifacts
        _assert_descriptor_only_generated_artifacts(
            family_dir=family_dir,
            generated_paths=generated_artifacts,
        )
