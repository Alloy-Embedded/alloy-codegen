"""Consumer-path verification against published alloy-devices artifacts."""

from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.reporting import ConsumerVerification
from alloy_codegen.scope import PipelineScope


def _smoke_device(scope: PipelineScope) -> str:
    return scope.device or "stm32g071rb"


def verify_alloy_smoke_consumer(
    *,
    scope: PipelineScope,
    alloy_root: Path | None,
    publication_root: Path,
    build_root: Path,
) -> ConsumerVerification:
    """Compile an Alloy smoke consumer against published artifacts."""
    if alloy_root is None:
        raise StageExecutionError("Alloy root is required for consumer verification.")

    compiler = shutil.which("c++")
    if compiler is None:
        raise StageExecutionError(
            "A C++ compiler named 'c++' is required for consumer verification."
        )

    consumer_id = "alloy-published-artifact-smoke"
    smoke_source = alloy_root / "tests" / "codegen" / "published_artifact_contract_smoke.cpp"
    if not smoke_source.exists():
        raise StageExecutionError(f"Smoke consumer source not found: {smoke_source}")

    device = _smoke_device(scope)
    startup_source = publication_root / "st" / "stm32g0" / device / "startup.cpp"
    if not startup_source.exists():
        raise StageExecutionError(f"Published startup source not found: {startup_source}")

    build_dir = build_root / consumer_id / device
    build_dir.mkdir(parents=True, exist_ok=True)
    executable_path = build_dir / "smoke-consumer"
    command = (
        compiler,
        "-std=c++23",
        "-Wall",
        "-Wextra",
        "-Werror",
        "-pedantic",
        f"-I{alloy_root / 'src'}",
        f"-I{publication_root}",
        '-DALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER="st/stm32g0/'
        f'{device}/register_map.hpp"',
        '-DALLOY_CODEGEN_SMOKE_PIN_FUNCTIONS_HEADER="st/stm32g0/'
        f'{device}/pin_functions.hpp"',
        '-DALLOY_CODEGEN_SMOKE_GPIO_HEADER="st/stm32g0/generated/peripherals/gpioa.hpp"',
        f"-DALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE=st::stm32g0::{device}",
        "-DALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE=st::stm32g0::generated::peripherals",
        str(smoke_source),
        str(startup_source),
        "-o",
        str(executable_path),
    )
    completed = subprocess.run(command, capture_output=True, text=True, check=False)
    return ConsumerVerification(
        consumer_id=consumer_id,
        compiler=compiler,
        source_file=str(smoke_source),
        startup_source=str(startup_source),
        build_dir=str(build_dir),
        executable_path=str(executable_path),
        command=command,
        succeeded=completed.returncode == 0,
        stdout=completed.stdout,
        stderr=completed.stderr,
    )
