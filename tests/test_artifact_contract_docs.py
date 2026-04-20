from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _read_doc(name: str) -> str:
    return (ROOT / "docs" / name).read_text(encoding="utf-8")


def test_codegen_alloy_boundary_doc_matches_active_contract() -> None:
    content = _read_doc("codegen-alloy-boundary.md")

    required_tokens = (
        "generated/runtime/types.hpp",
        "generated/runtime/devices/<device>/peripheral_instances.hpp",
        "generated/runtime/devices/<device>/pins.hpp",
        "generated/runtime/devices/<device>/registers.hpp",
        "generated/runtime/devices/<device>/register_fields.hpp",
        "generated/runtime/devices/<device>/clock_bindings.hpp",
        "generated/runtime/devices/<device>/dma_bindings.hpp",
        "generated/runtime/devices/<device>/routes.hpp",
        "generated/runtime/devices/<device>/connectors.hpp",
        "generated/runtime/devices/<device>/systick.hpp",
        "generated/runtime/devices/<device>/startup.hpp",
        "generated/runtime/devices/<device>/interrupt_stubs.hpp",
        "generated/runtime/devices/<device>/capabilities.json",
        "generated/runtime/devices/<device>/system_clock.hpp",
        "generated/runtime/devices/<device>/enable_domains.hpp",
        "generated/runtime/devices/<device>/driver_semantics/common.hpp",
        "generated/runtime/devices/<device>/driver_semantics/gpio.hpp",
        "generated/runtime/devices/<device>/driver_semantics/uart.hpp",
        "generated/runtime/devices/<device>/driver_semantics/i2c.hpp",
        "generated/runtime/devices/<device>/driver_semantics/spi.hpp",
        "generated/runtime/devices/<device>/driver_semantics/dma.hpp",
        "generated/runtime/devices/<device>/driver_semantics/adc.hpp",
        "generated/runtime/devices/<device>/driver_semantics/dac.hpp",
        "generated/runtime/devices/<device>/driver_semantics/can.hpp",
        "generated/runtime/devices/<device>/driver_semantics/rtc.hpp",
        "generated/runtime/devices/<device>/driver_semantics/watchdog.hpp",
        "generated/runtime/devices/<device>/driver_semantics/timer.hpp",
        "generated/runtime/devices/<device>/driver_semantics/pwm.hpp",
        "generated/devices/<device>/device.ld",
        "generated/devices/<device>/startup.cpp",
        "generated/devices/<device>/startup_vectors.cpp",
        "reports/validation-summary.json",
        "reports/coverage.json",
        "reports/runtime-provenance.json",
        "reports/runtime-explainability.json",
        "reports/publication-record.json",
    )
    forbidden_tokens = (
        "generated/peripherals/*.hpp",
        "generated/ip/*.hpp",
        "generated/connector_tables.hpp",
        "generated/rcc_map.hpp",
        "generated/dma_map.hpp",
        "generated/interrupt_map.hpp",
        "generated/memory_map.hpp",
        "generated/package_map.hpp",
        "generated/clock_tree_lite.hpp",
        "generated/runtime_profiles.hpp",
        "generated/runtime_semantics.hpp",
        "generated/runtime_refs.hpp",
        "generated/devices/<device>/device_descriptor.hpp",
        "generated/devices/<device>/pins.hpp",
        "generated/devices/<device>/peripheral_instances.hpp",
        "generated/devices/<device>/interrupt_bindings.hpp",
        "generated/devices/<device>/dma_bindings.hpp",
        "generated/devices/<device>/capability_overlays.hpp",
        "generated/devices/<device>/register_map.hpp",
        "generated/devices/<device>/register_fields.hpp",
        "generated/devices/<device>/startup_descriptors.hpp",
        "generated/signal_map.hpp",
        "generated/devices/<device>/pin_functions.hpp",
        "reports/publication-summary.json",
    )

    for token in required_tokens:
        assert token in content
    for token in forbidden_tokens:
        assert token not in content


def test_artifact_layout_doc_matches_active_contract() -> None:
    content = _read_doc("artifact-layout.md")

    required_tokens = (
        "<vendor>/<family>/artifact-manifest.json",
        "<vendor>/<family>/metadata/family-index.json",
        "<vendor>/<family>/metadata/family-connectivity.json",
        "<vendor>/<family>/metadata/ip-blocks.json",
        "<vendor>/<family>/metadata/capabilities.json",
        "<vendor>/<family>/metadata/packages.json",
        "<vendor>/<family>/metadata/connectors.json",
        "<vendor>/<family>/metadata/system-descriptors.json",
        "<vendor>/<family>/metadata/devices/<device>.json",
        "<vendor>/<family>/generated/runtime/types.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/peripheral_instances.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/pins.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/registers.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/register_fields.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/clock_bindings.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/dma_bindings.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/routes.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/connectors.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/systick.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/startup.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/interrupt_stubs.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/capabilities.json",
        "<vendor>/<family>/generated/runtime/devices/<device>/system_clock.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/enable_domains.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/common.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/gpio.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/uart.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/i2c.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/spi.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dma.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/adc.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dac.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/can.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/rtc.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/watchdog.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/timer.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/pwm.hpp",
        "<vendor>/<family>/generated/devices/<device>/device.ld",
        "<vendor>/<family>/generated/devices/<device>/startup.cpp",
        "<vendor>/<family>/generated/devices/<device>/startup_vectors.cpp",
        "<vendor>/<family>/reports/validation-summary.json",
        "<vendor>/<family>/reports/coverage.json",
        "<vendor>/<family>/reports/runtime-provenance.json",
        "<vendor>/<family>/reports/runtime-explainability.json",
        "<vendor>/<family>/reports/publication-summary.json",
        "<vendor>/<family>/reports/publication-record.json",
    )
    forbidden_tokens = (
        "generated/peripherals/<peripheral>.hpp",
        "generated/ip/<ip-version>.hpp",
        "generated/connector_tables.hpp",
        "generated/rcc_map.hpp",
        "generated/dma_map.hpp",
        "generated/interrupt_map.hpp",
        "generated/memory_map.hpp",
        "generated/package_map.hpp",
        "generated/clock_tree_lite.hpp",
        "generated/runtime_profiles.hpp",
        "generated/runtime_semantics.hpp",
        "generated/runtime_refs.hpp",
        "generated/devices/<device>/device_descriptor.hpp",
        "generated/devices/<device>/pins.hpp",
        "generated/devices/<device>/peripheral_instances.hpp",
        "generated/devices/<device>/interrupt_bindings.hpp",
        "generated/devices/<device>/dma_bindings.hpp",
        "generated/devices/<device>/capability_overlays.hpp",
        "generated/devices/<device>/register_map.hpp",
        "generated/devices/<device>/register_fields.hpp",
        "generated/devices/<device>/startup_descriptors.hpp",
        "generated/signal_map.hpp",
        "generated/devices/<device>/pin_functions.hpp",
    )

    for token in required_tokens:
        assert token in content
    for token in forbidden_tokens:
        assert token not in content
