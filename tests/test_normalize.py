from __future__ import annotations

import json
from pathlib import Path

import pytest

from alloy_codegen.bootstrap import (
    BOOTSTRAP_FAMILY,
    bootstrap_device_names,
    registered_device_names,
)
from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import PackagePad, PinDefinition, PinSignal, Provenance
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import _derive_pin_constraints, run

G0_FIXTURE_DIR = Path(__file__).parent / "fixtures" / BOOTSTRAP_FAMILY
F4_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "stm32f4"
SAME70_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "same70"


@pytest.mark.parametrize("device_name", bootstrap_device_names())
def test_normalize_matches_bootstrap_fixture(
    device_name: str,
    execution_context: ExecutionContext,
) -> None:
    fixture_path = G0_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), execution_context)

    assert result.payload.devices[0].to_dict() == expected


@pytest.mark.parametrize("device_name", registered_device_names("st", "stm32f4"))
def test_normalize_matches_stm32f4_fixture(
    device_name: str,
    execution_context: ExecutionContext,
) -> None:
    fixture_path = F4_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), execution_context)

    assert result.payload.devices[0].to_dict() == expected


def test_normalize_f4_uses_correct_family_identity(
    execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="stm32f401re"), execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "st"
    assert device.identity.family == "stm32f4"
    assert device.schema_version == "1.1.0"


def test_normalize_g0_and_f4_use_same_schema_version(
    execution_context: ExecutionContext,
) -> None:
    g0_result = run(PipelineScope(device="stm32g071rb"), execution_context)
    f4_result = run(PipelineScope(device="stm32f401re"), execution_context)

    g0_version = g0_result.payload.devices[0].schema_version
    f4_version = f4_result.payload.devices[0].schema_version
    assert g0_version == f4_version


@pytest.mark.parametrize("device_name", registered_device_names("microchip", "same70"))
def test_normalize_matches_same70_fixture(
    device_name: str,
    microchip_execution_context: ExecutionContext,
) -> None:
    fixture_path = SAME70_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), microchip_execution_context)

    assert result.payload.devices[0].to_dict() == expected


def test_normalize_same70_uses_correct_family_identity(
    microchip_execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="atsame70q21b"), microchip_execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "microchip"
    assert device.identity.family == "same70"
    assert device.schema_version == "1.1.0"


def test_normalize_g0_and_same70_use_same_schema_version(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
) -> None:
    g0_result = run(PipelineScope(device="stm32g071rb"), execution_context)
    same70_result = run(PipelineScope(device="atsame70q21b"), microchip_execution_context)

    g0_version = g0_result.payload.devices[0].schema_version
    same70_version = same70_result.payload.devices[0].schema_version
    assert g0_version == same70_version


def test_normalize_emits_connector_driven_domains_for_foundational_vendors(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    st_device = run(PipelineScope(device="stm32g071rb"), execution_context).payload.devices[0]
    microchip_device = run(
        PipelineScope(device="atsame70q21b"),
        microchip_execution_context,
    ).payload.devices[0]
    nxp_device = run(PipelineScope(device="mimxrt1062"), nxp_execution_context).payload.devices[0]

    for device in (st_device, microchip_device, nxp_device):
        assert device.signal_endpoints
        assert device.route_requirements
        assert any(requirement.kind == "source-select" for requirement in device.route_requirements)
        assert device.route_operations
        assert device.connection_candidates
        assert device.connection_groups
        assert any(len(group.signals) >= 2 for group in device.connection_groups)
        assert any(capability.scope == "instance-overlay" for capability in device.capabilities)
        assert device.vector_slots
        assert device.startup_descriptors


def test_normalize_emits_ip_block_and_instance_overlay_capabilities(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    devices = (
        run(PipelineScope(device="stm32g071rb"), execution_context).payload.devices[0],
        run(PipelineScope(device="atsame70q21b"), microchip_execution_context).payload.devices[0],
        run(PipelineScope(device="mimxrt1062"), nxp_execution_context).payload.devices[0],
    )

    for device in devices:
        assert any(capability.scope == "instance-overlay" for capability in device.capabilities)
        if any(peripheral.ip_version is not None for peripheral in device.peripherals):
            assert any(capability.scope == "ip-block" for capability in device.capabilities)


def test_foundational_devices_expose_multi_signal_groups(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    contexts = {
        ("st", "stm32g0"): execution_context,
        ("st", "stm32f4"): execution_context,
        ("microchip", "same70"): microchip_execution_context,
        ("nxp", "imxrt1060"): nxp_execution_context,
    }

    for (vendor, family), context in contexts.items():
        for device_name in registered_device_names(vendor, family):
            device = run(PipelineScope(device=device_name), context).payload.devices[0]
            assert any(len(group.signals) >= 2 for group in device.connection_groups)


def test_normalize_populates_package_pads_for_foundational_vendors(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    st_device = run(PipelineScope(device="stm32g071rb"), execution_context).payload.devices[0]
    microchip_device = run(
        PipelineScope(device="atsame70q21b"),
        microchip_execution_context,
    ).payload.devices[0]
    nxp_device = run(PipelineScope(device="mimxrt1062"), nxp_execution_context).payload.devices[0]

    assert st_device.package_pads
    assert any(
        pad.bonded_pin == "PA0" and pad.position_label == "17"
        for pad in st_device.package_pads
    )
    assert all(pad.package == "lqfp64" for pad in st_device.package_pads)

    assert microchip_device.package_pads
    assert any(
        pad.bonded_pin == "PA0" and pad.position_label == "102"
        for pad in microchip_device.package_pads
    )
    assert any(pad.bonding_state == "bonded" for pad in microchip_device.package_pads)
    assert any(pad.bonding_state == "dedicated" for pad in microchip_device.package_pads)
    assert any(pad.pad_kind in {"power", "ground"} for pad in microchip_device.package_pads)

    assert nxp_device.package_pads
    assert any(
        pad.pad_id == "GPIO_AD_B0_00" and pad.pad_kind == "io"
        for pad in nxp_device.package_pads
    )
    assert all(pad.bonding_state == "bonded" for pad in nxp_device.package_pads)


def test_normalize_same70_derives_wakeup_pin_constraints(
    microchip_execution_context: ExecutionContext,
) -> None:
    device = run(
        PipelineScope(device="atsame70q21b"),
        microchip_execution_context,
    ).payload.devices[0]

    wakeup_constraints = {
        (constraint.pin, constraint.kind, constraint.value) for constraint in device.pin_constraints
    }

    assert ("PA0", "wakeup-capable", "WKUP0") in wakeup_constraints
    assert ("PD28", "wakeup-capable", "WKUP5") in wakeup_constraints


def test_derive_pin_constraints_classifies_signal_semantics() -> None:
    provenance = Provenance(source_id="test", source_path=None, patch_ids=())
    pins = (
        PinDefinition(
            name="PA0",
            port="A",
            number=0,
            signals=(
                PinSignal(
                    function="gpio",
                    peripheral="GPIOA",
                    signal="IN0",
                    af_number=None,
                    provenance=provenance,
                ),
                PinSignal(
                    function="adc1_in0",
                    peripheral="ADC1",
                    signal="IN0",
                    af_number=0,
                    provenance=provenance,
                ),
                PinSignal(
                    function="supc_wkup0",
                    peripheral="SUPC",
                    signal="WKUP0",
                    af_number=1,
                    provenance=provenance,
                ),
            ),
            provenance=provenance,
        ),
        PinDefinition(
            name="PB4",
            port="B",
            number=4,
            signals=(
                PinSignal(
                    function="gpio",
                    peripheral="GPIOB",
                    signal="IN4",
                    af_number=None,
                    provenance=provenance,
                ),
                PinSignal(
                    function="dbg_tdi",
                    peripheral="DBG",
                    signal="TDI",
                    af_number=1,
                    provenance=provenance,
                ),
            ),
            provenance=provenance,
        ),
        PinDefinition(
            name="PB5",
            port="B",
            number=5,
            signals=(
                PinSignal(
                    function="gpio",
                    peripheral="GPIOB",
                    signal="IN5",
                    af_number=None,
                    provenance=provenance,
                ),
                PinSignal(
                    function="dbg_swdio",
                    peripheral="DBG",
                    signal="SWDIO",
                    af_number=1,
                    provenance=provenance,
                ),
                PinSignal(
                    function="usart1_tx",
                    peripheral="USART1",
                    signal="TX",
                    af_number=2,
                    provenance=provenance,
                ),
            ),
            provenance=provenance,
        ),
        PinDefinition(
            name="PC0",
            port="C",
            number=0,
            signals=(
                PinSignal(
                    function="gpio",
                    peripheral="GPIOC",
                    signal="IN0",
                    af_number=None,
                    provenance=provenance,
                ),
                PinSignal(
                    function="adc1_in10",
                    peripheral="ADC1",
                    signal="IN10",
                    af_number=0,
                    provenance=provenance,
                ),
            ),
            provenance=provenance,
        ),
    )
    package_pads = (
        PackagePad(
            pad_id="1",
            package="testpkg",
            position_label="1",
            physical_index=1,
            pad_kind="reset",
            bonded_pin="PB4",
            provenance=provenance,
        ),
    )

    constraints = {
        (constraint.pin, constraint.kind, constraint.value)
        for constraint in _derive_pin_constraints(
            package_pads=package_pads,
            pins=pins,
            provenance=provenance,
        )
    }

    assert ("PA0", "analog-capable", "in0") in constraints
    assert ("PA0", "wakeup-capable", "WKUP0") in constraints
    assert ("PB4", "reset", "1") in constraints
    assert ("PB4", "debug-only", "TDI") in constraints
    assert ("PB5", "debug-shared", "SWDIO") in constraints
    assert ("PC0", "analog-only", "in10") in constraints
