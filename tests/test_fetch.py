import json

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.fetch import run as run_fetch
from alloy_codegen.stages.patch import run as run_patch


def test_fetch_uses_fixture_source_root(execution_context: ExecutionContext) -> None:
    result = run_fetch(PipelineScope(device="stm32g071rb"), execution_context)
    sources = result.payload.source_manifest.sources

    assert result.stage == "fetch"
    assert {source.source_id for source in sources} == {"cmsis-svd-data", "stm32-open-pin-data"}
    assert any(
        source.source_id == "cmsis-svd-data"
        and source.local_path.endswith("STM32G071.svd")
        and source.upstream_path == "data/STMicro/STM32G071.svd"
        and source.revision.startswith("content-sha256:")
        for source in sources
    )
    assert any(
        source.source_id == "stm32-open-pin-data"
        and source.local_path.endswith("STM32G071R(6-8-B)Tx.xml")
        and source.upstream_path == "mcu/STM32G071R(6-8-B)Tx.xml"
        and source.revision.startswith("content-sha256:")
        for source in sources
    )
    assert any(
        source.source_id == "stm32-open-pin-data"
        and source.local_path.endswith("GPIO-STM32G07x_gpio_v1_0_Modes.xml")
        and source.upstream_path == "mcu/IP/GPIO-STM32G07x_gpio_v1_0_Modes.xml"
        and source.revision.startswith("content-sha256:")
        for source in sources
    )


def test_fetch_and_patch_are_byte_stable(execution_context: ExecutionContext) -> None:
    scope = PipelineScope()

    fetch_a = json.dumps(run_fetch(scope, execution_context).to_dict(), sort_keys=True)
    fetch_b = json.dumps(run_fetch(scope, execution_context).to_dict(), sort_keys=True)
    patch_a = json.dumps(run_patch(scope, execution_context).to_dict(), sort_keys=True)
    patch_b = json.dumps(run_patch(scope, execution_context).to_dict(), sort_keys=True)

    assert fetch_a == fetch_b
    assert patch_a == patch_b
