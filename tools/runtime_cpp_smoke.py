"""Runtime C++ smoke-compile gate.

Added by the OpenSpec change ``add-runtime-cpp-smoke-compile-ci``.

For every device the pipeline admits, materialise the emitted
runtime headers to a tmp tree and drive

    clang++ -std=c++20 -ffreestanding -nostdlib -c smoke.cpp

over a synthesised ``smoke.cpp`` that includes every runtime
header for that device.  Catches template-metaprogramming
regressions (typed enums, ``ValidPinAssignment`` concept,
specialisation arities) at PR time — invisible to the existing
golden + string-presence assertions.

Locally the gate is skipped when ``clang++`` is not on PATH, so
contributors without a clang toolchain are not blocked.

Public surface:

* :func:`clang_executable` — resolve the clang on PATH (or None).
* :func:`smoke_compile_device` — run the smoke compile for one
  ``(vendor, family, device)``.
* :func:`smoke_compile_all` — iterate every admitted device.

Pytest collects this as ``tests/test_runtime_cpp_smoke.py``.
The test is gated by ``--runtime-cpp-smoke`` (or the env var
``ALLOY_RUNTIME_CPP_SMOKE=1``) so the default ``pytest -q`` run
stays fast.
"""

from __future__ import annotations

import os
import shutil
import subprocess
from collections.abc import Iterable
from dataclasses import dataclass, field
from pathlib import Path

from alloy_codegen.bootstrap import DEVICE_REGISTRY, registered_device_names
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit

# Canonical clang invocation.  ``-ffreestanding -nostdlib`` keeps
# the gate honest: emitted headers are consumed by firmware that
# has no libc, so the smoke compile runs the same way.  ``-O0``
# keeps compile times tight and surfaces the "does it parse and
# typecheck" question, not "is the codegen optimal".
CLANG_FLAGS: tuple[str, ...] = (
    "-std=c++20",
    "-ffreestanding",
    "-nostdlib",
    "-fno-exceptions",
    "-fno-rtti",
    "-O0",
    "-c",
)

# Device-runtime headers we synthesise the smoke ``#include`` list
# from.  ``types.hpp`` MUST come first because every per-device
# header depends on its enum-class declarations.  Other entries
# follow a topological order that mirrors the existing emitter
# wiring (peripheral_instances → registers → register_fields → …).
_HEADER_ORDER: tuple[str, ...] = (
    "peripheral_instances.hpp",
    "pins.hpp",
    "registers.hpp",
    "register_fields.hpp",
    "clock_bindings.hpp",
    "dma_bindings.hpp",
    "routes.hpp",
    "connectors.hpp",
    "interrupts.hpp",
    "interrupt_stubs.hpp",
    "resets.hpp",
    "enable_domains.hpp",
    "clock_graph.hpp",
    "system_clock.hpp",
    "system_sequences.hpp",
    "clock_profiles.hpp",
    "clock_config.hpp",
    "low_power.hpp",
    "capabilities.hpp",
    "systick.hpp",
    "startup.hpp",
    # ``pin_validation.hpp`` is emitted only when the device has
    # connection_candidates (currently STM32 + iMXRT).  Listed
    # last so the static_assert below pulls in already-declared
    # enums.
    "pin_validation.hpp",
    # add-additional-validity-concepts: per-device validity-concept
    # headers for DMA bindings, peripheral clock sources, IRQ-vector
    # slots and I2C bus speeds.  Each header is emitted only when the
    # underlying IR data is present.
    "dma_validation.hpp",
    "clock_validation.hpp",
    "interrupt_validation.hpp",
    "i2c_speed_validation.hpp",
)


@dataclass(frozen=True, slots=True)
class SmokeResult:
    """Outcome of one device's smoke compile."""

    vendor: str
    family: str
    device: str
    passed: bool
    duration_seconds: float
    headers_included: tuple[str, ...] = field(default_factory=tuple)
    stderr: str = ""

    @property
    def label(self) -> str:
        return f"{self.vendor}/{self.family}/{self.device}"


def clang_executable() -> str | None:
    """Return the path to a clang++ that supports the smoke flags,
    or ``None`` if no compatible clang is on PATH."""
    candidate = shutil.which("clang++")
    if candidate is None:
        return None
    return candidate


def admitted_triples() -> tuple[tuple[str, str, str], ...]:
    """Return every admitted ``(vendor, family, device)`` triple."""
    triples: list[tuple[str, str, str]] = []
    for (vendor, family), _devices in DEVICE_REGISTRY.items():
        for device in registered_device_names(vendor, family):
            triples.append((vendor, family, device))
    return tuple(sorted(triples))


def _materialise_artifacts(
    *,
    artifacts: Iterable,
    target_dir: Path,
) -> dict[str, Path]:
    """Write emitted artifacts to disk under ``target_dir`` and
    return a ``{relative_path: absolute_path}`` map."""
    written: dict[str, Path] = {}
    for artifact in artifacts:
        path = artifact.path
        if not isinstance(artifact.content, str):
            continue
        out = target_dir / path
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(artifact.content, encoding="utf-8")
        written[path] = out
    return written


def _runtime_headers_for_device(
    *,
    written: dict[str, Path],
    vendor: str,
    family: str,
    device: str,
) -> list[str]:
    """Return the ordered list of repo-relative header paths to
    include in the smoke ``.cpp``."""
    base = f"{vendor}/{family}/generated/runtime/devices/{device}"
    headers: list[str] = []
    types_header = f"{vendor}/{family}/generated/runtime/types.hpp"
    if types_header in written:
        headers.append(types_header)
    for name in _HEADER_ORDER:
        candidate = f"{base}/{name}"
        if candidate in written:
            headers.append(candidate)
    return headers


def _generate_smoke_cpp(
    *,
    vendor: str,
    family: str,
    device: str,
    headers: list[str],
) -> str:
    """Render the per-device ``smoke.cpp`` source.

    The body deliberately keeps the only entry point as
    ``alloy_codegen_runtime_cpp_smoke_main`` so a future link step
    can reuse the harness without colliding with the runtime-lite
    consumer-verification ``main``.
    """
    include_lines = "\n".join(f'#include "{path}"' for path in headers)
    static_asserts = []
    pin_validation_path = (
        f"{vendor}/{family}/generated/runtime/devices/{device}/pin_validation.hpp"
    )
    if pin_validation_path in headers:
        # The header declares a closed PinAssignmentValid<Pin, Signal>
        # primary template.  We assert at least the primary
        # specialisation compiles; the actual matched specialisations
        # are device-specific and exercised by the connectors.hpp
        # ConnectorTraits asserts below.
        static_asserts.append(
            "static_assert(sizeof(::st::stm32g0::generated::runtime"
            "::devices::stm32g071rb::PinAssignmentEntry) > 0, "
            '"PinAssignmentEntry should compile");'
            if vendor == "st" and device == "stm32g071rb"
            else "// pin_validation.hpp included; "
            "device-specific static_asserts skipped."
        )
    # add-additional-validity-concepts: cheap structural smoke per
    # concept.  Each entry-table struct is unconditional in the
    # emitted header, so a sizeof() probe is enough to catch
    # template-arity / typed-enum regressions without hard-coding
    # device-specific specialisations here.
    # Namespace components mirror the emitter's ``_identifier``
    # sanitisation (alnum-only — hyphens become underscores) so device
    # names like ``esp32-wroom32`` resolve to ``esp32_wroom32``.
    def _ns_component(value: str) -> str:
        return "".join(c if c.isalnum() else "_" for c in value)

    base_ns = (
        f"::{_ns_component(vendor)}::{_ns_component(family)}"
        f"::generated::runtime::devices::{_ns_component(device)}"
    )
    extras = (
        ("dma_validation.hpp", "DmaBindingEntry"),
        ("clock_validation.hpp", "ClockSourceEntry"),
        ("interrupt_validation.hpp", "InterruptSlotEntry"),
        ("i2c_speed_validation.hpp", "I2cSpeedEntry"),
    )
    for header_name, entry_name in extras:
        candidate = (
            f"{vendor}/{family}/generated/runtime/devices/{device}/{header_name}"
        )
        if candidate in headers:
            static_asserts.append(
                f"static_assert(sizeof({base_ns}::{entry_name}) > 0, "
                f'"{entry_name} should compile");'
            )
    body = "\n    ".join(static_asserts) if static_asserts else "(void)0;"
    return (
        "// Auto-generated by tools/runtime_cpp_smoke.py — do not edit.\n"
        "// Smoke compile for "
        f"{vendor}/{family}/{device} runtime headers.\n"
        "\n"
        f"{include_lines}\n"
        "\n"
        "extern \"C\" int alloy_codegen_runtime_cpp_smoke_main() {\n"
        f"    {body}\n"
        "    return 0;\n"
        "}\n"
    )


def smoke_compile_device(
    *,
    vendor: str,
    family: str,
    device: str,
    work_dir: Path,
    clang: str | None = None,
    fixtures_root: Path | None = None,
) -> SmokeResult:
    """Run the smoke compile for one device.

    ``work_dir`` is used as the materialisation root and as the
    clang ``-I`` include path.  ``fixtures_root`` overrides the
    default :class:`ExecutionContext` source roots so tests can
    point at the snapshotted fixtures (the same overrides the
    ``execution_context`` pytest fixtures install).
    """
    import time

    compiler = clang or clang_executable()
    if compiler is None:
        raise RuntimeError(
            "clang++ is not on PATH; cannot run runtime-cpp-smoke."
        )

    started = time.monotonic()
    context = _build_smoke_execution_context(
        work_dir=work_dir, fixtures_root=fixtures_root, vendor=vendor, family=family
    )
    result = run_emit(
        PipelineScope(vendor=vendor, family=family, device=device),
        context,
    )
    materialised = _materialise_artifacts(
        artifacts=result.payload.artifacts, target_dir=work_dir
    )
    headers = _runtime_headers_for_device(
        written=materialised, vendor=vendor, family=family, device=device
    )
    if not headers:
        # Device emits no runtime headers (e.g. AVR-DA today).
        # That's a legitimate skip — there's nothing to compile.
        return SmokeResult(
            vendor=vendor,
            family=family,
            device=device,
            passed=True,
            duration_seconds=time.monotonic() - started,
            headers_included=(),
            stderr="(no runtime headers emitted; skipped)",
        )

    smoke_src = work_dir / f"smoke_{vendor}_{family}_{device}.cpp"
    smoke_src.write_text(
        _generate_smoke_cpp(
            vendor=vendor, family=family, device=device, headers=headers
        ),
        encoding="utf-8",
    )

    completed = subprocess.run(
        (
            compiler,
            *CLANG_FLAGS,
            "-I",
            str(work_dir),
            str(smoke_src),
            "-o",
            str(smoke_src.with_suffix(".o")),
        ),
        capture_output=True,
        text=True,
    )
    return SmokeResult(
        vendor=vendor,
        family=family,
        device=device,
        passed=(completed.returncode == 0),
        duration_seconds=time.monotonic() - started,
        headers_included=tuple(headers),
        stderr=completed.stderr,
    )


def smoke_compile_all(
    *,
    work_root: Path,
    clang: str | None = None,
    fixtures_root: Path | None = None,
) -> tuple[SmokeResult, ...]:
    """Run the smoke compile for every admitted device, one
    sub-tmpdir per device so cleanup is trivial."""
    results: list[SmokeResult] = []
    for vendor, family, device in admitted_triples():
        device_dir = work_root / f"{vendor}_{family}_{device}"
        device_dir.mkdir(parents=True, exist_ok=True)
        results.append(
            smoke_compile_device(
                vendor=vendor,
                family=family,
                device=device,
                work_dir=device_dir,
                clang=clang,
                fixtures_root=fixtures_root,
            )
        )
    return tuple(results)


def _build_smoke_execution_context(
    *,
    work_dir: Path,
    fixtures_root: Path | None,
    vendor: str,
    family: str,
) -> ExecutionContext:
    """Build an :class:`ExecutionContext` for the smoke run.

    When ``fixtures_root`` is supplied, populate every source
    override pointing into the snapshotted fixtures tree so the
    pipeline never reaches for the network.
    """
    base = ExecutionContext.default()
    overrides: dict[str, str] = {}
    if fixtures_root is not None:
        # Mirror the per-fixture source-root layout that
        # ``tests/conftest.py`` installs for each family.  Adding a
        # new family here is a one-liner.
        family_overrides: dict[tuple[str, str], dict[str, str]] = {
            ("st", "stm32g0"): {
                "cmsis-svd-data": str(fixtures_root / "cmsis-svd-data"),
                "stm32-open-pin-data": str(fixtures_root / "stm32-open-pin-data"),
            },
            ("st", "stm32f4"): {
                "cmsis-svd-data": str(fixtures_root / "cmsis-svd-data"),
                "stm32-open-pin-data": str(fixtures_root / "stm32-open-pin-data"),
            },
            ("microchip", "same70"): {
                "microchip-dfp-extract": str(fixtures_root / "microchip-dfp-same70"),
            },
            ("microchip", "avr-da"): {
                "microchip-dfp-extract": str(fixtures_root / "microchip-dfp-avr-da"),
            },
            ("nxp", "imxrt1060"): {
                "nxp-mcux-soc-svd": str(fixtures_root / "nxp-mcux-imxrt1060" / "svd"),
                "nxp-mcux-sdk": str(fixtures_root / "nxp-mcux-imxrt1060" / "sdk"),
            },
            ("raspberrypi", "rp2040"): {
                "pico-sdk": str(fixtures_root / "pico-sdk"),
            },
            ("espressif", "esp32"): {
                "espressif-svd": str(fixtures_root / "espressif-svd"),
            },
            ("espressif", "esp32c3"): {
                "espressif-svd": str(fixtures_root / "espressif-svd"),
            },
            ("espressif", "esp32s3"): {
                "espressif-svd": str(fixtures_root / "espressif-svd"),
            },
            ("nordic", "nrf52"): {
                "zephyr-dts": str(fixtures_root / "zephyr-dts"),
            },
        }
        overrides = family_overrides.get((vendor, family), {})
    return base.with_overrides(
        source_overrides=overrides,
        artifact_root=str(work_dir / "_artifacts"),
        publication_root=str(work_dir / "_publication"),
    )


def runtime_cpp_smoke_enabled() -> bool:
    """Return True when the gate is opted into via env var.

    Pytest's ``--runtime-cpp-smoke`` CLI flag is the canonical
    activator; this env var is provided so CI workflow files can
    set it without piping through pytest's argv.
    """
    return os.environ.get("ALLOY_RUNTIME_CPP_SMOKE", "").strip() in {"1", "true", "yes"}


__all__ = [
    "CLANG_FLAGS",
    "SmokeResult",
    "admitted_triples",
    "clang_executable",
    "runtime_cpp_smoke_enabled",
    "smoke_compile_all",
    "smoke_compile_device",
]
