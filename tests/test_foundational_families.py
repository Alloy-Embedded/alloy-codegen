from __future__ import annotations

import json
import os
import shutil
from collections.abc import Iterable

import pytest

from alloy_codegen.artifact_contract import find_runtime_cpp_string_violations
from alloy_codegen.bootstrap import registered_device_names
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.publish import run as run_publish

# The foundational publish tests below loop ``run_publish`` over every
# admitted (vendor, family) — eight families × full validate → emit →
# publish → consumer-verify cycle.  On the developer machine this is
# already 30–45 minutes; on shared CI runners the same loop runs ~3×
# slower and consistently exceeds the GitHub-Actions per-job budget.
#
# The per-device matrix in ``.github/workflows/bootstrap-family.yml``
# already exercises the publish path for every admitted device with
# its own determinism gate, so the aggregate cycle here is redundant
# in CI.  Mark the two slow loops as ``slow`` and skip them when the
# ``ALLOY_SKIP_SLOW_TESTS`` env var is set (the workflow turns it on).
_skip_if_slow_disabled = pytest.mark.skipif(
    os.environ.get("ALLOY_SKIP_SLOW_TESTS", "").strip() in {"1", "true", "yes"},
    reason=(
        "ALLOY_SKIP_SLOW_TESTS is set — the per-device bootstrap-family "
        "matrix already gates the full publish path on every admitted "
        "device, so the aggregate loop is redundant on CI."
    ),
)


def _family_contexts(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
    rp2040_execution_context: ExecutionContext,
    espressif_execution_context: ExecutionContext,
    microchip_avr_da_execution_context: ExecutionContext,
) -> tuple[tuple[PipelineScope, ExecutionContext], ...]:
    return (
        (PipelineScope(vendor="st", family="stm32g0"), execution_context),
        (PipelineScope(vendor="st", family="stm32f4"), execution_context),
        (PipelineScope(vendor="microchip", family="same70"), microchip_execution_context),
        (
            PipelineScope(vendor="microchip", family="avr-da"),
            microchip_avr_da_execution_context,
        ),
        (PipelineScope(vendor="nxp", family="imxrt1060"), nxp_execution_context),
        (PipelineScope(vendor="raspberrypi", family="rp2040"), rp2040_execution_context),
        (PipelineScope(vendor="espressif", family="esp32c3"), espressif_execution_context),
        (PipelineScope(vendor="espressif", family="esp32s3"), espressif_execution_context),
        (PipelineScope(vendor="espressif", family="esp32"), espressif_execution_context),
    )


def _common_family_artifact_paths(family_dir: str) -> tuple[str, ...]:
    # ``prune-redundant-json-artifacts`` (archived 2026-04) removed 8 of the
    # historical family-scoped metadata / report JSONs in favour of the
    # canonical YAML at ``data/devices/.../<device>.yml``.  The artifacts
    # listed below are the ones that remain in the emit pipeline today.
    return (
        f"{family_dir}/artifact-manifest.json",
        f"{family_dir}/metadata/family-index.json",
        f"{family_dir}/reports/validation-report.json",
        f"{family_dir}/reports/validation-summary.json",
        f"{family_dir}/reports/coverage.json",
        f"{family_dir}/reports/runtime-provenance.json",
        f"{family_dir}/reports/runtime-explainability.json",
        f"{family_dir}/generated/runtime/types.hpp",
    )


def _device_artifact_paths(
    family_dir: str,
    device_names: Iterable[str],
) -> tuple[str, ...]:
    paths: list[str] = []
    for device_name in device_names:
        # ``prune-redundant-json-artifacts`` (archived 2026-04) removed the
        # per-device ``metadata/devices/<device>.json`` rollup; the canonical
        # YAML at ``data/devices/.../<device>.yml`` is now the single source
        # of truth for that information.
        paths.extend(
            (
                f"{family_dir}/generated/devices/{device_name}/device.ld",
                f"{family_dir}/generated/devices/{device_name}/startup.cpp",
                f"{family_dir}/generated/devices/{device_name}/startup_vectors.cpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/peripheral_instances.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/pins.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/registers.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/register_fields.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/clock_bindings.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/system_clock.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/clock_profiles.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/clock_config.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/low_power.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/dma_bindings.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/routes.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/connectors.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/startup.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/interrupts.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/interrupt_stubs.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/resets.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/enable_domains.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/clock_graph.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/capabilities.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/capabilities.json",
                f"{family_dir}/generated/runtime/devices/{device_name}/system_sequences.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/common.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/gpio.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/uart.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/i2c.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/spi.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/dma.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/adc.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/dac.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/can.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/eth.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/usb.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/qspi.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/sdmmc.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/rtc.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/watchdog.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/timer.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/pwm.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/driver_semantics/pio.hpp",
                f"{family_dir}/generated/runtime/devices/{device_name}/systick.hpp",
            )
        )
    return tuple(paths)


def test_foundational_families_emit_same_descriptor_contract(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
    rp2040_execution_context: ExecutionContext,
    espressif_execution_context: ExecutionContext,
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
        rp2040_execution_context,
        espressif_execution_context,
        microchip_avr_da_execution_context,
    ):
        result = run_emit(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        device_names = registered_device_names(scope.resolved_vendor(), scope.resolved_family())
        artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

        assert result.stage == "emit"
        assert result.status == "completed"
        for path in _common_family_artifact_paths(family_dir):
            assert path in artifacts, f"missing common family artifact: {path}"
        for path in _device_artifact_paths(family_dir, device_names):
            assert path in artifacts, f"missing device artifact: {path}"

        validation_summary = json.loads(
            artifacts[f"{family_dir}/reports/validation-summary.json"].content
        )
        coverage = json.loads(artifacts[f"{family_dir}/reports/coverage.json"].content)
        assert validation_summary["draft_system_descriptor_domains"] == []
        assert coverage["vendor"] == scope.resolved_vendor()
        assert coverage["family"] == scope.resolved_family()
        assert len(coverage["devices"]) == len(device_names)
        assert all("publishable" in device for device in coverage["devices"])
        assert all("domains" in device for device in coverage["devices"])
        assert all("counts" in device for device in coverage["devices"])
        assert coverage["all_devices_publishable"] == all(
            bool(device["publishable"]) for device in coverage["devices"]
        )
        assert find_runtime_cpp_string_violations(result.payload.artifacts) == ()


@_skip_if_slow_disabled
def test_foundational_families_publish_with_same_generic_workflow(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
    rp2040_execution_context: ExecutionContext,
    espressif_execution_context: ExecutionContext,
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
        rp2040_execution_context,
        espressif_execution_context,
        microchip_avr_da_execution_context,
    ):
        result = run_publish(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        device_names = registered_device_names(scope.resolved_vendor(), scope.resolved_family())

        assert result.stage == "publish"
        # Surface publish-stage warnings + consumer_verification details
        # into the pytest failure output so CI diagnostics explain why
        # publish blocked.  ConsumerVerification succeeded=False can come
        # from the compile step (captured in `stderr`) OR from the linker
        # script verification sub-step (captured separately in
        # `linker_script_verification.stderr`), so both paths are shown.
        failure_context = ""
        if result.status != "completed":
            failure_context = f"\nfamily={family_dir}\nwarnings={result.warnings!r}"
            cv = getattr(result.payload, "consumer_verification", None)
            if cv is not None and not cv.succeeded:
                failure_context += f"\nconsumer stderr:\n{cv.stderr[:2000]}"
                failure_context += f"\nconsumer command:\n{cv.command!r}"
                lsv = cv.linker_script_verification
                if lsv is not None:
                    failure_context += (
                        f"\nlinker script verification: attempted={lsv.attempted} "
                        f"succeeded={lsv.succeeded} skipped_reason={lsv.skipped_reason!r}"
                    )
                    if lsv.stderr:
                        failure_context += f"\nlinker stderr:\n{lsv.stderr[:2000]}"
                    if lsv.stdout:
                        failure_context += f"\nlinker stdout:\n{lsv.stdout[:500]}"
        assert result.status == "completed", failure_context
        assert result.payload.publication_mode == "published"
        assert result.payload.consumer_verification is not None
        assert result.payload.consumer_verification.succeeded is True
        assert result.payload.draft_system_descriptor_domains == ()

        publication_root = context.publication_root
        assert (publication_root / family_dir / "artifact-manifest.json").exists()
        assert (publication_root / family_dir / "reports" / "validation-report.json").exists()
        assert (publication_root / family_dir / "reports" / "validation-summary.json").exists()
        assert (publication_root / family_dir / "reports" / "coverage.json").exists()
        assert (publication_root / family_dir / "generated" / "runtime" / "types.hpp").exists()
        for device_name in device_names:
            assert (
                publication_root / family_dir / "generated" / "devices" / device_name / "device.ld"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "devices"
                / device_name
                / "startup.cpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "peripheral_instances.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "pins.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "registers.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "register_fields.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "clock_bindings.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "systick.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "system_clock.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "clock_profiles.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "clock_config.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "capabilities.json"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "dma_bindings.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "routes.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "connectors.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "startup.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "interrupt_stubs.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "driver_semantics"
                / "common.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "driver_semantics"
                / "gpio.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "driver_semantics"
                / "uart.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "driver_semantics"
                / "i2c.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "driver_semantics"
                / "spi.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "runtime"
                / "devices"
                / device_name
                / "driver_semantics"
                / "dma.hpp"
            ).exists()


@_skip_if_slow_disabled
def test_foundational_families_remain_complete_across_repeat_publish_cycles(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
    rp2040_execution_context: ExecutionContext,
    espressif_execution_context: ExecutionContext,
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
        rp2040_execution_context,
        espressif_execution_context,
        microchip_avr_da_execution_context,
    ):
        result_a = run_publish(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        coverage_a = json.loads(
            (context.publication_root / family_dir / "reports" / "coverage.json").read_text(
                encoding="utf-8"
            )
        )
        summary_a = json.loads(
            (
                context.publication_root / family_dir / "reports" / "validation-summary.json"
            ).read_text(encoding="utf-8")
        )

        shutil.rmtree(context.artifact_root)
        shutil.rmtree(context.publication_root)

        result_b = run_publish(scope, context)
        coverage_b = json.loads(
            (context.publication_root / family_dir / "reports" / "coverage.json").read_text(
                encoding="utf-8"
            )
        )
        summary_b = json.loads(
            (
                context.publication_root / family_dir / "reports" / "validation-summary.json"
            ).read_text(encoding="utf-8")
        )

        assert result_a.status == "completed"
        assert result_b.status == "completed"
        assert (
            result_a.payload.target_artifact_revision == result_b.payload.target_artifact_revision
        )
        assert (
            result_a.payload.publication_record.content_sha256
            == result_b.payload.publication_record.content_sha256
        )
        assert coverage_a == coverage_b
        assert summary_a == summary_b
        assert coverage_b["all_devices_publishable"] is True
        assert all(bool(device["publishable"]) for device in coverage_b["devices"])
        assert summary_b["draft_system_descriptor_domains"] == []


def test_rp2040_apply_route_emits_funcsel_and_resets_writes(
    rp2040_execution_context: ExecutionContext,
) -> None:
    """§4.3 — RP2040 apply_route<> writes RESETS_RESET and IO_BANK0_GPIOx_CTRL.FUNCSEL."""
    result = run_emit(PipelineScope(device="rp2040"), rp2040_execution_context)
    artifacts = {a.path: a for a in result.payload.artifacts}
    routes = artifacts["raspberrypi/rp2040/generated/runtime/devices/rp2040/routes.hpp"].content
    assert "apply_route<PinId::GP0, PeripheralId::UART0" in routes
    assert "& ~std::uint32_t{0x1F}" in routes  # FUNCSEL mask
    assert "0x40014004u" in routes  # IO_BANK0_GPIO0_CTRL address


def test_avr_da_apply_route_emits_portmux_writes(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """§5.3 — AVR-DA apply_route<> writes PORTMUX route registers via RMW."""
    result = run_emit(
        PipelineScope(vendor="microchip", family="avr-da", device="avr128da32"),
        microchip_avr_da_execution_context,
    )
    artifacts = {a.path: a for a in result.payload.artifacts}
    routes = artifacts["microchip/avr-da/generated/runtime/devices/avr128da32/routes.hpp"].content
    # USART0 TX on PA0 → PORTMUX.USARTROUTEA bits[1:0]
    assert "apply_route<PinId::PA0, PeripheralId::USART0, SignalId::signal_tx>" in routes
    assert "0x00000204u" in routes  # PORTMUX base + USARTROUTEA offset
    assert "std::uint32_t{0x3} << 0" in routes  # 2-bit mask at bit 0
    # USART1 TX on PC0 → PORTMUX.USARTROUTEA bits[3:2]
    assert "apply_route<PinId::PC0, PeripheralId::USART1, SignalId::signal_tx>" in routes
    assert "std::uint32_t{0x3} << 2" in routes  # 2-bit mask at bit 2
    # TWI0 → PORTMUX.TWIROUTEA
    assert "0x0000020Au" in routes  # TWIROUTEA address
    # SPI0 → PORTMUX.SPIROUTEA
    assert "0x00000208u" in routes  # SPIROUTEA address


def test_avr_da_clock_bindings_emits_noop_specializations(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """§5.1 — AVR-DA clock_enable/disable<> emit empty no-op specializations (no clock gate)."""
    result = run_emit(
        PipelineScope(vendor="microchip", family="avr-da", device="avr128da32"),
        microchip_avr_da_execution_context,
    )
    artifacts = {a.path: a for a in result.payload.artifacts}
    clock = artifacts[
        "microchip/avr-da/generated/runtime/devices/avr128da32/clock_bindings.hpp"
    ].content
    assert "clock_enable<PeripheralId::USART0>() noexcept -> void {}" in clock
    assert "clock_disable<PeripheralId::USART0>() noexcept -> void {}" in clock
    assert "clock_enable<PeripheralId::SPI0>() noexcept -> void {}" in clock
    assert "clock_enable<PeripheralId::TWI0>() noexcept -> void {}" in clock
