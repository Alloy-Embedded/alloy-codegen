"""Consumer-path verification against published alloy-devices artifacts."""

from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

from alloy_codegen.bootstrap import registered_device_names
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.reporting import ConsumerVerification, LinkerScriptVerification
from alloy_codegen.scope import PipelineScope


def _family_root(publication_root: Path, scope: PipelineScope) -> Path:
    return publication_root / scope.resolved_vendor() / scope.resolved_family()


def _published_device(scope: PipelineScope, family_root: Path) -> str:
    if scope.device is not None:
        return scope.device

    startup_sources = sorted(family_root.glob("generated/devices/*/startup.cpp"))
    if startup_sources:
        return startup_sources[0].parent.name

    vector_sources = sorted(family_root.glob("generated/devices/*/startup_vectors.cpp"))
    if vector_sources:
        return vector_sources[0].parent.name

    vendor = scope.resolved_vendor()
    family = scope.resolved_family()
    return registered_device_names(vendor, family)[0]


def _runtime_lite_smoke_source_path() -> Path:
    """Return the repository-local runtime-lite smoke consumer source."""
    return (
        Path(__file__).resolve().parents[2]
        / "tests"
        / "codegen"
        / "published_runtime_lite_contract_smoke.cpp"
    )


def _gnu_ld_compatible_driver(compiler: str) -> str | None:
    """Return the compiler driver when it can forward GNU-ld-compatible linker scripts."""
    completed = subprocess.run(
        (compiler, "-Wl,--version"),
        capture_output=True,
        text=True,
        check=False,
    )
    version_output = f"{completed.stdout}\n{completed.stderr}"
    if completed.returncode == 0 and (
        "GNU ld" in version_output or "LLD" in version_output or "GNU gold" in version_output
    ):
        return compiler
    return None


def _write_linker_smoke_source(path: Path) -> None:
    path.write_text(
        "\n".join(
            [
                'extern "C" void _start();',
                '[[gnu::section(".vectors"), gnu::used]] void* alloy_codegen_vectors[] = {',
                "    reinterpret_cast<void*>(&_start),",
                "};",
                "[[gnu::used]] int alloy_codegen_smoke_data = 7;",
                "[[gnu::used]] int alloy_codegen_smoke_bss;",
                'extern "C" [[gnu::used]] void _start() {',
                "    alloy_codegen_smoke_bss = alloy_codegen_smoke_data;",
                "    for (;;) {",
                "    }",
                "}",
                "",
            ]
        ),
        encoding="utf-8",
    )


def _verify_linker_script(
    *,
    compiler: str,
    build_dir: Path,
    linker_script: Path,
) -> LinkerScriptVerification:
    verifier = _gnu_ld_compatible_driver(compiler)
    source_path = build_dir / "device-ld-smoke.cpp"
    object_path = build_dir / "device-ld-smoke.o"
    output_path = build_dir / "device-ld-smoke.elf"
    map_path = build_dir / "device-ld-smoke.map"
    if verifier is None:
        return LinkerScriptVerification(
            attempted=False,
            succeeded=True,
            linker_script=str(linker_script),
            source_file=str(source_path),
            object_file=str(object_path),
            output_file=str(output_path),
            map_file=str(map_path),
            skipped_reason="GNU-ld-compatible linker driver is not available on this host.",
        )

    _write_linker_smoke_source(source_path)
    compile_command = (
        verifier,
        "-std=c++23",
        "-Wall",
        "-Wextra",
        "-Werror",
        "-c",
        str(source_path),
        "-o",
        str(object_path),
    )
    compile_result = subprocess.run(compile_command, capture_output=True, text=True, check=False)
    if compile_result.returncode != 0:
        return LinkerScriptVerification(
            attempted=True,
            succeeded=False,
            linker_script=str(linker_script),
            source_file=str(source_path),
            object_file=str(object_path),
            output_file=str(output_path),
            map_file=str(map_path),
            command=compile_command,
            stdout=compile_result.stdout,
            stderr=compile_result.stderr,
        )

    link_command = (
        verifier,
        str(object_path),
        "-nostdlib",
        f"-Wl,-T,{linker_script}",
        f"-Wl,-Map,{map_path}",
        "-Wl,-e,_start",
        "-o",
        str(output_path),
    )
    link_result = subprocess.run(link_command, capture_output=True, text=True, check=False)
    if link_result.returncode != 0:
        return LinkerScriptVerification(
            attempted=True,
            succeeded=False,
            linker_script=str(linker_script),
            source_file=str(source_path),
            object_file=str(object_path),
            output_file=str(output_path),
            map_file=str(map_path),
            command=link_command,
            stdout=link_result.stdout,
            stderr=link_result.stderr,
        )

    map_text = map_path.read_text(encoding="utf-8") if map_path.exists() else ""
    if "__stack_top" not in map_text:
        return LinkerScriptVerification(
            attempted=True,
            succeeded=False,
            linker_script=str(linker_script),
            source_file=str(source_path),
            object_file=str(object_path),
            output_file=str(output_path),
            map_file=str(map_path),
            command=link_command,
            stdout=link_result.stdout,
            stderr="linked output did not expose __stack_top in the map file",
        )
    if ".text" not in map_text or ".data" not in map_text or ".bss" not in map_text:
        return LinkerScriptVerification(
            attempted=True,
            succeeded=False,
            linker_script=str(linker_script),
            source_file=str(source_path),
            object_file=str(object_path),
            output_file=str(output_path),
            map_file=str(map_path),
            command=link_command,
            stdout=link_result.stdout,
            stderr="linked output map does not contain the expected .text/.data/.bss sections",
        )
    if "load address" not in map_text:
        return LinkerScriptVerification(
            attempted=True,
            succeeded=False,
            linker_script=str(linker_script),
            source_file=str(source_path),
            object_file=str(object_path),
            output_file=str(output_path),
            map_file=str(map_path),
            command=link_command,
            stdout=link_result.stdout,
            stderr="linked output map does not show a load address for initialized data",
        )
    return LinkerScriptVerification(
        attempted=True,
        succeeded=True,
        linker_script=str(linker_script),
        source_file=str(source_path),
        object_file=str(object_path),
        output_file=str(output_path),
        map_file=str(map_path),
        command=link_command,
        stdout=link_result.stdout,
        stderr=link_result.stderr,
    )


def _compile_smoke_source(
    *,
    scope: PipelineScope,
    publication_root: Path,
    build_root: Path,
    compiler: str,
    consumer_id: str,
    source_path: Path,
    startup_source: Path,
    command: tuple[str, ...],
    linker_script_verification: LinkerScriptVerification | None = None,
) -> ConsumerVerification:
    family_root = _family_root(publication_root, scope)
    device = _published_device(scope, family_root)
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
        succeeded=completed.returncode == 0
        and (linker_script_verification is None or linker_script_verification.succeeded),
        stdout=completed.stdout,
        stderr=completed.stderr,
        linker_script_verification=linker_script_verification,
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
    startup_source = family_root / "generated" / "devices" / device / "startup.cpp"
    if not startup_source.exists():
        startup_source = family_root / "generated" / "devices" / device / "startup_vectors.cpp"
    linker_script = family_root / "generated" / "devices" / device / "device.ld"
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
        "-DALLOY_CODEGEN_HOST_SMOKE=1",
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
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CONNECTORS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/connectors.hpp"'
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
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ADC_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/adc.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_DAC_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/dac.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CAN_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/can.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ETH_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/eth.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_USB_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/usb.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_QSPI_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/qspi.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SDMMC_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/sdmmc.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_RTC_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/rtc.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_WATCHDOG_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/watchdog.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_TIMER_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/timer.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_PWM_SEMANTICS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/driver_semantics/pwm.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTICK_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/systick.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTEM_CLOCK_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/system_clock.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CLOCK_PROFILES_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/clock_profiles.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CLOCK_CONFIG_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/clock_config.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_LOW_POWER_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/low_power.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_STARTUP_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/startup.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_INTERRUPTS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/interrupts.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_INTERRUPT_STUBS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/interrupt_stubs.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_RESETS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/resets.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_ENABLE_DOMAINS_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/enable_domains.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CLOCK_GRAPH_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/clock_graph.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_CAPABILITIES_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/capabilities.hpp"'
        ),
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_SYSTEM_SEQUENCES_HEADER="
            f'"{vendor}/{family}/generated/runtime/devices/{device}/system_sequences.hpp"'
        ),
        f"-DALLOY_CODEGEN_SMOKE_RUNTIME_NAMESPACE={vendor}::{family}::generated::runtime",
        (
            f"-DALLOY_CODEGEN_SMOKE_RUNTIME_DEVICE_NAMESPACE="
            f"{vendor}::{family}::generated::runtime::devices::{device}"
        ),
        str(smoke_source),
        str(startup_source),
        "-o",
        str(executable_path),
    )
    linker_script_verification = _verify_linker_script(
        compiler=compiler,
        build_dir=build_dir,
        linker_script=linker_script,
    )
    return _compile_smoke_source(
        scope=scope,
        publication_root=publication_root,
        build_root=build_root,
        compiler=compiler,
        consumer_id=consumer_id,
        source_path=smoke_source,
        startup_source=startup_source,
        command=command,
        linker_script_verification=linker_script_verification,
    )
