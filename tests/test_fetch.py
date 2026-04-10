import json

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.fetch import run as run_fetch
from alloy_codegen.stages.patch import run as run_patch


def test_fetch_uses_fixture_source_root(execution_context: ExecutionContext) -> None:
    result = run_fetch(PipelineScope(device="stm32g071rb"), execution_context)
    source = result.payload.source_manifest.sources[0]

    assert result.stage == "fetch"
    assert source.local_path.endswith("STM32G071.svd")
    assert source.upstream_path == "data/STMicro/STM32G071.svd"
    assert source.revision.startswith("content-sha256:")


def test_fetch_and_patch_are_byte_stable(execution_context: ExecutionContext) -> None:
    scope = PipelineScope()

    fetch_a = json.dumps(run_fetch(scope, execution_context).to_dict(), sort_keys=True)
    fetch_b = json.dumps(run_fetch(scope, execution_context).to_dict(), sort_keys=True)
    patch_a = json.dumps(run_patch(scope, execution_context).to_dict(), sort_keys=True)
    patch_b = json.dumps(run_patch(scope, execution_context).to_dict(), sort_keys=True)

    assert fetch_a == fetch_b
    assert patch_a == patch_b
