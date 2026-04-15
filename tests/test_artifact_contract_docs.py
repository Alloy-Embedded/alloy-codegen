from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _read_doc(name: str) -> str:
    return (ROOT / "docs" / name).read_text(encoding="utf-8")


def test_codegen_alloy_boundary_doc_matches_active_contract() -> None:
    content = _read_doc("codegen-alloy-boundary.md")

    required_tokens = (
        "generated/peripherals/*.hpp",
        "generated/ip/*.hpp",
        "generated/connector_tables.hpp",
        "generated/rcc_map.hpp",
        "generated/dma_map.hpp",
        "generated/interrupt_map.hpp",
        "generated/memory_map.hpp",
        "generated/package_map.hpp",
        "generated/clock_tree_lite.hpp",
        "generated/runtime/types.hpp",
        "generated/runtime/devices/<device>/peripheral_instances.hpp",
        "generated/runtime/devices/<device>/pins.hpp",
        "generated/runtime/devices/<device>/registers.hpp",
        "generated/runtime/devices/<device>/register_fields.hpp",
        "generated/runtime/devices/<device>/clock_bindings.hpp",
        "generated/runtime/devices/<device>/system_clock.hpp",
        "generated/runtime/devices/<device>/dma_bindings.hpp",
        "generated/runtime/devices/<device>/routes.hpp",
        "generated/runtime/devices/<device>/driver_semantics/common.hpp",
        "generated/runtime/devices/<device>/driver_semantics/gpio.hpp",
        "generated/runtime/devices/<device>/driver_semantics/uart.hpp",
        "generated/runtime/devices/<device>/driver_semantics/i2c.hpp",
        "generated/runtime/devices/<device>/driver_semantics/spi.hpp",
        "generated/runtime/devices/<device>/driver_semantics/dma.hpp",
        "generated/runtime/devices/<device>/driver_semantics/adc.hpp",
        "generated/runtime/devices/<device>/driver_semantics/dac.hpp",
        "generated/devices/<device>/device_descriptor.hpp",
        "generated/devices/<device>/pins.hpp",
        "generated/devices/<device>/peripheral_instances.hpp",
        "generated/devices/<device>/interrupt_bindings.hpp",
        "generated/devices/<device>/dma_bindings.hpp",
        "generated/devices/<device>/capability_overlays.hpp",
        "generated/devices/<device>/register_map.hpp",
        "generated/devices/<device>/register_fields.hpp",
        "generated/devices/<device>/startup_descriptors.hpp",
        "generated/devices/<device>/startup.cpp",
        "generated/devices/<device>/startup_vectors.cpp",
        "reports/validation-summary.json",
        "reports/coverage.json",
        "reports/publication-record.json",
    )
    forbidden_tokens = (
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
        "<vendor>/<family>/generated/peripherals/<peripheral>.hpp",
        "<vendor>/<family>/generated/ip/<ip-version>.hpp",
        "<vendor>/<family>/generated/connector_tables.hpp",
        "<vendor>/<family>/generated/rcc_map.hpp",
        "<vendor>/<family>/generated/dma_map.hpp",
        "<vendor>/<family>/generated/interrupt_map.hpp",
        "<vendor>/<family>/generated/memory_map.hpp",
        "<vendor>/<family>/generated/package_map.hpp",
        "<vendor>/<family>/generated/clock_tree_lite.hpp",
        "<vendor>/<family>/generated/runtime/types.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/peripheral_instances.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/pins.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/registers.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/register_fields.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/clock_bindings.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/system_clock.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/dma_bindings.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/routes.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/common.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/gpio.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/uart.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/i2c.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/spi.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dma.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/adc.hpp",
        "<vendor>/<family>/generated/runtime/devices/<device>/driver_semantics/dac.hpp",
        "<vendor>/<family>/generated/devices/<device>/device_descriptor.hpp",
        "<vendor>/<family>/generated/devices/<device>/pins.hpp",
        "<vendor>/<family>/generated/devices/<device>/peripheral_instances.hpp",
        "<vendor>/<family>/generated/devices/<device>/interrupt_bindings.hpp",
        "<vendor>/<family>/generated/devices/<device>/dma_bindings.hpp",
        "<vendor>/<family>/generated/devices/<device>/capability_overlays.hpp",
        "<vendor>/<family>/generated/devices/<device>/register_map.hpp",
        "<vendor>/<family>/generated/devices/<device>/register_fields.hpp",
        "<vendor>/<family>/generated/devices/<device>/startup_descriptors.hpp",
        "<vendor>/<family>/generated/devices/<device>/startup.cpp",
        "<vendor>/<family>/generated/devices/<device>/startup_vectors.cpp",
        "<vendor>/<family>/reports/validation-summary.json",
        "<vendor>/<family>/reports/coverage.json",
        "<vendor>/<family>/reports/publication-summary.json",
        "<vendor>/<family>/reports/publication-record.json",
    )
    forbidden_tokens = (
        "generated/signal_map.hpp",
        "generated/devices/<device>/pin_functions.hpp",
    )

    for token in required_tokens:
        assert token in content
    for token in forbidden_tokens:
        assert token not in content
