"""Consumer-path verification against published alloy-devices artifacts."""

from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

from alloy_codegen.bootstrap import registered_device_names
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.reporting import ConsumerVerification
from alloy_codegen.scope import PipelineScope


def _family_root(publication_root: Path, scope: PipelineScope) -> Path:
    return publication_root / scope.resolved_vendor() / scope.resolved_family()


def _published_device(scope: PipelineScope, family_root: Path) -> str:
    if scope.device is not None:
        return scope.device

    vector_sources = sorted(family_root.glob("generated/devices/*/startup_vectors.cpp"))
    if vector_sources:
        return vector_sources[0].parent.name

    vendor = scope.resolved_vendor()
    family = scope.resolved_family()
    return registered_device_names(vendor, family)[0]


def _first_generated_gpio_header(family_root: Path) -> Path:
    candidates = sorted((family_root / "generated" / "peripherals").glob("*.hpp"))
    if not candidates:
        generated_dir = family_root / "generated" / "peripherals"
        raise StageExecutionError(f"No generated peripheral headers found under {generated_dir}")
    return candidates[0]


def _first_generated_ip_header(family_root: Path) -> Path | None:
    candidates = sorted((family_root / "generated" / "ip").glob("*.hpp"))
    if not candidates:
        return None
    for candidate in candidates:
        content = candidate.read_text(encoding="utf-8")
        if "capability:" in content:
            return candidate
    return candidates[0]


def _smoke_source_path() -> Path:
    """Return the repository-local smoke consumer source."""
    return (
        Path(__file__).resolve().parents[2]
        / "tests"
        / "codegen"
        / "published_artifact_contract_smoke.cpp"
    )


def _runtime_lite_smoke_source_path() -> Path:
    """Return the repository-local runtime-lite smoke consumer source."""
    return (
        Path(__file__).resolve().parents[2]
        / "tests"
        / "codegen"
        / "published_runtime_lite_contract_smoke.cpp"
    )


def _compile_smoke_source(
    *,
    scope: PipelineScope,
    publication_root: Path,
    build_root: Path,
    compiler: str,
    consumer_id: str,
    source_path: Path,
    command: tuple[str, ...],
) -> ConsumerVerification:
    family_root = _family_root(publication_root, scope)
    device = _published_device(scope, family_root)
    startup_source = family_root / "generated" / "devices" / device / "startup_vectors.cpp"
    build_dir = build_root / consumer_id / device
    build_dir.mkdir(parents=True, exist_ok=True)
    executable_path = build_dir / "smoke-consumer"
    completed = subprocess.run(command, capture_output=True, text=True, check=False)
    return ConsumerVerification(
        consumer_id=consumer_id,
        compiler=compiler,
        source_file=str(source_path),
        startup_source=str(startup_source),
        build_dir=str(build_dir),
        executable_path=str(executable_path),
        command=command,
        succeeded=completed.returncode == 0,
        stdout=completed.stdout,
        stderr=completed.stderr,
    )


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
    smoke_source = _smoke_source_path()
    if not smoke_source.exists():
        raise StageExecutionError(f"Smoke consumer source not found: {smoke_source}")

    family_root = _family_root(publication_root, scope)
    device = _published_device(scope, family_root)
    startup_source = family_root / "generated" / "devices" / device / "startup_vectors.cpp"
    if not startup_source.exists():
        raise StageExecutionError(f"Published startup source not found: {startup_source}")
    gpio_header = _first_generated_gpio_header(family_root)
    ip_header = _first_generated_ip_header(family_root)
    gpio_header_include = str(gpio_header.relative_to(publication_root)).replace("\\", "/")
    vendor = scope.resolved_vendor()
    family = scope.resolved_family()

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
        (
            f"-DALLOY_CODEGEN_SMOKE_REGISTER_MAP_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/register_map.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_REGISTER_FIELDS_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/register_fields.hpp"'
        ),
        f'-DALLOY_CODEGEN_SMOKE_GPIO_HEADER="{gpio_header_include}"',
        f'-DALLOY_CODEGEN_SMOKE_CONNECTOR_TABLES_HEADER="{vendor}/{family}/generated/connector_tables.hpp"',
        f'-DALLOY_CODEGEN_SMOKE_INTERRUPT_MAP_HEADER="{vendor}/{family}/generated/interrupt_map.hpp"',
        f'-DALLOY_CODEGEN_SMOKE_MEMORY_MAP_HEADER="{vendor}/{family}/generated/memory_map.hpp"',
        f'-DALLOY_CODEGEN_SMOKE_PACKAGE_MAP_HEADER="{vendor}/{family}/generated/package_map.hpp"',
        f'-DALLOY_CODEGEN_SMOKE_CLOCK_TREE_HEADER="{vendor}/{family}/generated/clock_tree_lite.hpp"',
        f'-DALLOY_CODEGEN_SMOKE_RUNTIME_PROFILES_HEADER="{vendor}/{family}/generated/runtime_profiles.hpp"',
        (
            f"-DALLOY_CODEGEN_SMOKE_DEVICE_DESCRIPTOR_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/device_descriptor.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_PINS_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/pins.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_PERIPHERAL_INSTANCES_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/peripheral_instances.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_INTERRUPT_BINDINGS_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/interrupt_bindings.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_DMA_BINDINGS_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/dma_bindings.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_CAPABILITY_OVERLAYS_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/capability_overlays.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_STARTUP_DESCRIPTORS_HEADER="
            f'"{vendor}/{family}/generated/devices/{device}/startup_descriptors.hpp"'
        ),
        f"-DALLOY_CODEGEN_SMOKE_DEVICE_NAMESPACE={vendor}::{family}::generated::devices::{device}",
        f"-DALLOY_CODEGEN_SMOKE_GENERATED_NAMESPACE={vendor}::{family}::generated",
        f"-DALLOY_CODEGEN_SMOKE_GPIO_NAMESPACE={vendor}::{family}::generated::peripherals",
    )
    if ip_header is not None:
        ip_header_include = str(ip_header.relative_to(publication_root)).replace("\\", "/")
        command += (f'-DALLOY_CODEGEN_SMOKE_IP_HEADER="{ip_header_include}"',)
    command += (
        str(smoke_source),
        str(startup_source),
        "-o",
        str(executable_path),
    )
    return _compile_smoke_source(
        scope=scope,
        publication_root=publication_root,
        build_root=build_root,
        compiler=compiler,
        consumer_id=consumer_id,
        source_path=smoke_source,
        command=command,
    )


def verify_runtime_lite_smoke_consumer(
    *,
    scope: PipelineScope,
    alloy_root: Path | None,
    publication_root: Path,
    build_root: Path,
) -> ConsumerVerification:
    """Compile the runtime-lite smoke consumer against published artifacts."""
    if alloy_root is None:
        raise StageExecutionError("Alloy root is required for consumer verification.")

    compiler = shutil.which("c++")
    if compiler is None:
        raise StageExecutionError(
            "A C++ compiler named 'c++' is required for consumer verification."
        )

    consumer_id = "alloy-published-runtime-lite-smoke"
    smoke_source = _runtime_lite_smoke_source_path()
    if not smoke_source.exists():
        raise StageExecutionError(f"Smoke consumer source not found: {smoke_source}")

    family_root = _family_root(publication_root, scope)
    device = _published_device(scope, family_root)
    vendor = scope.resolved_vendor()
    family = scope.resolved_family()
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
        f'-DALLOY_CODEGEN_SMOKE_RUNTIME_TYPES_HEADER="{vendor}/{family}/generated/runtime/types.hpp"',
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PERIPHERALS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/peripheral_instances.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PINS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/pins.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTERS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/registers.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_REGISTER_FIELDS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/register_fields.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CLOCK_BINDINGS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/clock_bindings.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_BINDINGS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/dma_bindings.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ROUTES_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/routes.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_GPIO_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/gpio.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_UART_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/uart.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_I2C_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/i2c.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SPI_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/spi.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DMA_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/dma.hpp"'
        ),
        f"-DALLOY_CODEGEN_SMOKE_RUNTIME_NAMESPACE={vendor}::{family}::generated::runtime",
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_NAMESPACE="
            f"{vendor}::{family}::generated::runtime::devices::{device}"
        ),
        str(smoke_source),
        "-o",
        str(executable_path),
    )
    return _compile_smoke_source(
        scope=scope,
        publication_root=publication_root,
        build_root=build_root,
        compiler=compiler,
        consumer_id=consumer_id,
        source_path=smoke_source,
        command=command,
    )
