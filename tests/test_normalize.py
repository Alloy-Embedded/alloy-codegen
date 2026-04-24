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
from alloy_codegen.sources.raw import RawInterrupt, RawPeripheral
from alloy_codegen.sources.stm32_open_pin_data import parse_raw_pin_data_document
from alloy_codegen.stages.normalize import (
    _deduplicate_raw_peripherals,
    _derive_pin_constraints,
    _normalize_interrupts,
    run,
)

G0_FIXTURE_DIR = Path(__file__).parent / "fixtures" / BOOTSTRAP_FAMILY
F4_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "stm32f4"
SAME70_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "same70"
RP2040_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "rp2040"
ESP32C3_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "esp32c3"
AVR_DA_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "avr-da"


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
    assert device.schema_version == "1.2.0"


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
    assert device.schema_version == "1.2.0"


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


def test_normalize_preserves_explicit_clock_selectors_and_bindings(
    execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    st_device = run(PipelineScope(device="stm32g071rb"), execution_context).payload.devices[0]
    nxp_device = run(PipelineScope(device="mimxrt1062"), nxp_execution_context).payload.devices[0]

    st_selectors = {selector.selector_id for selector in st_device.clock_selectors}
    st_bindings = {
        binding.peripheral: binding.selector_id for binding in st_device.peripheral_clock_bindings
    }
    assert "selector:usart1-kernel" in st_selectors
    assert st_bindings["USART1"] == "selector:usart1-kernel"
    if "LPUART1" in st_bindings:
        assert st_bindings["LPUART1"] == "selector:lpuart1-kernel"

    nxp_selectors = {selector.selector_id for selector in nxp_device.clock_selectors}
    nxp_binding_map = {
        binding.peripheral: binding for binding in nxp_device.peripheral_clock_bindings
    }
    nxp_gate_map = {gate.gate_id: gate.parent_node for gate in nxp_device.clock_gates}
    assert "selector:lpuart-root" in nxp_selectors
    assert nxp_binding_map["LPUART1"].selector_id == "selector:lpuart-root"
    assert nxp_gate_map["gate:lpuart1"] == "clock-node:lpuart-root"


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
        pad.bonded_pin == "PA0" and pad.position_label == "17" for pad in st_device.package_pads
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
        pad.pad_id == "GPIO_AD_B0_00" and pad.pad_kind == "io" for pad in nxp_device.package_pads
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


def test_parse_st_pin_data_collapses_duplicate_package_positions(tmp_path: Path) -> None:
    mcu_path = tmp_path / "device.xml"
    gpio_modes_path = tmp_path / "gpio.xml"
    mcu_path.write_text(
        """\
<Mcu xmlns="http://dummy.com" RefName="stm32demo" Package="tssop20">
  <IP Name="GPIO" Version="v1"/>
  <Pin Name="PB7" Position="1" Type="I/O" />
  <Pin Name="PB8" Position="1" Type="I/O" />
  <Pin Name="PA11 [PA9]" Position="16" Type="I/O" />
  <Pin Name="PA9 [PA11]" Position="16" Type="I/O" Variant="PINREMAP" />
</Mcu>
""",
        encoding="utf-8",
    )
    gpio_modes_path.write_text(
        """\
<Modes xmlns="http://dummy.com">
  <GPIO_Pin Name="PB7" />
  <GPIO_Pin Name="PA11" />
</Modes>
""",
        encoding="utf-8",
    )

    raw = parse_raw_pin_data_document(mcu_path=mcu_path, gpio_modes_path=gpio_modes_path)

    assert [pad.position_label for pad in raw.package_pads] == ["1", "16"]
    assert [pad.bonded_pin for pad in raw.package_pads] == ["PB7", "PA11"]


def test_normalize_interrupts_merges_same_line_aliases() -> None:
    provenance = Provenance(source_id="test", source_path="raw.svd", patch_ids=("test",))
    interrupts = _normalize_interrupts(
        (
            RawInterrupt(name="TIM6_DAC_LPTIM1", line=33, peripheral="TIM6"),
            RawInterrupt(name="TIM6_DAC", line=33, peripheral="DAC"),
            RawInterrupt(name="SPI1", line=51, peripheral="SPI1"),
            RawInterrupt(name="SPI1", line=51, peripheral="SPI1"),
        ),
        provenance=provenance,
    )

    assert len(interrupts) == 2
    assert interrupts[0].name == "TIM6_DAC_LPTIM1"
    assert interrupts[0].alias_names == ("TIM6_DAC",)
    assert interrupts[1].name == "SPI1"
    assert interrupts[1].alias_names == ()


def test_deduplicate_raw_peripherals_tracks_alias_mapping() -> None:
    peripherals, aliases = _deduplicate_raw_peripherals(
        (
            RawPeripheral(name="CCM_ANALOG", base_address=0x400D8000),
            RawPeripheral(name="PMU", base_address=0x400D8000),
            RawPeripheral(name="TEMPMON", base_address=0x400D8000),
            RawPeripheral(name="GPIO1", base_address=0x401B8000),
        ),
        preferred_names={"PMU", "TEMPMON", "GPIO1"},
    )

    assert [peripheral.name for peripheral in peripherals] == ["PMU", "GPIO1"]
    assert aliases["CCM_ANALOG"] == "PMU"
    assert aliases["PMU"] == "PMU"
    assert aliases["TEMPMON"] == "PMU"


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


@pytest.mark.parametrize("device_name", registered_device_names("raspberrypi", "rp2040"))
def test_normalize_matches_rp2040_fixture(
    device_name: str,
    rp2040_execution_context: ExecutionContext,
) -> None:
    fixture_path = RP2040_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), rp2040_execution_context)

    assert result.payload.devices[0].to_dict() == expected


def test_normalize_rp2040_uses_correct_family_identity(
    rp2040_execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="rp2040"), rp2040_execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "raspberrypi"
    assert device.identity.family == "rp2040"
    assert device.schema_version == "1.2.0"


def test_normalize_rp2040_has_expected_memories(
    rp2040_execution_context: ExecutionContext,
) -> None:
    device = run(PipelineScope(device="rp2040"), rp2040_execution_context).payload.devices[0]

    memory_kinds = {mem.kind for mem in device.memories}
    assert "sram" in memory_kinds
    assert "xip-flash" in memory_kinds


def test_normalize_rp2040_has_dma_requests(
    rp2040_execution_context: ExecutionContext,
) -> None:
    device = run(PipelineScope(device="rp2040"), rp2040_execution_context).payload.devices[0]

    dma_request_lines = {req.request_line for req in device.dma_requests}
    assert "UART0_RX" in dma_request_lines
    assert "UART0_TX" in dma_request_lines
    assert "SPI0_RX" in dma_request_lines
    assert "ADC" in dma_request_lines


# ---------------------------------------------------------------------------
# ESP32-C3 (Espressif) normalize tests
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("device_name", registered_device_names("espressif", "esp32c3"))
def test_normalize_matches_esp32c3_fixture(
    device_name: str,
    espressif_execution_context: ExecutionContext,
) -> None:
    fixture_path = ESP32C3_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), espressif_execution_context)

    assert result.payload.devices[0].to_dict() == expected


def test_normalize_esp32c3_uses_correct_family_identity(
    espressif_execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="esp32c3"), espressif_execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "espressif"
    assert device.identity.family == "esp32c3"
    assert device.identity.core == "rv32imc"
    assert device.schema_version == "1.2.0"


def test_normalize_esp32c3_has_expected_memories(
    espressif_execution_context: ExecutionContext,
) -> None:
    device = run(PipelineScope(device="esp32c3"), espressif_execution_context).payload.devices[0]

    memory_kinds = {mem.kind for mem in device.memories}
    memory_names = {mem.name for mem in device.memories}
    assert "sram" in memory_kinds
    assert "rom" in memory_kinds
    assert "DRAM" in memory_names
    assert "IRAM" in memory_names
    assert "ROM" in memory_names


def test_normalize_esp32c3_has_dma_requests(
    espressif_execution_context: ExecutionContext,
) -> None:
    device = run(PipelineScope(device="esp32c3"), espressif_execution_context).payload.devices[0]

    dma_request_lines = {req.request_line for req in device.dma_requests}
    assert "UART0_RX" in dma_request_lines
    assert "UART0_TX" in dma_request_lines
    assert "SPI2_RX" in dma_request_lines
    assert "SPI2_TX" in dma_request_lines
    assert "ADC" in dma_request_lines


def test_normalize_esp32c3_has_expected_clock_profiles(
    espressif_execution_context: ExecutionContext,
) -> None:
    device = run(PipelineScope(device="esp32c3"), espressif_execution_context).payload.devices[0]

    profile_ids = {prof.profile_id for prof in device.system_clock_profiles}
    assert "safe-rc-fast-8mhz" in profile_ids
    assert "default-pll-160mhz" in profile_ids

    safe = next(p for p in device.system_clock_profiles if p.profile_id == "safe-rc-fast-8mhz")
    default = next(p for p in device.system_clock_profiles if p.profile_id == "default-pll-160mhz")

    assert safe.sysclk_hz == 8_000_000
    assert default.sysclk_hz == 160_000_000


# ---------------------------------------------------------------------------
# AVR-DA (Microchip) normalize tests
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("device_name", registered_device_names("microchip", "avr-da"))
def test_normalize_matches_avr_da_fixture(
    device_name: str,
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    fixture_path = AVR_DA_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), microchip_avr_da_execution_context)

    assert result.payload.devices[0].to_dict() == expected


def test_normalize_avr_da_uses_correct_family_identity(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="avr128da32"), microchip_avr_da_execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "microchip"
    assert device.identity.family == "avr-da"
    assert device.identity.core == "avr8"
    assert device.schema_version == "1.2.0"


def test_normalize_avr_da_preserves_harvard_address_spaces(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 1.1/1.2: the Harvard address_space annotation survives the full
    normalize + connector_descriptor pipeline for AVR-DA.  All three memory
    regions (flash, sram, eeprom) must carry their distinct address_space."""
    device = run(
        PipelineScope(device="avr128da32"), microchip_avr_da_execution_context
    ).payload.devices[0]
    by_name = {memory.name: memory for memory in device.memories}
    assert by_name["APP_SECTION"].address_space == "prog"
    assert by_name["APP_SECTION"].kind == "flash"
    assert by_name["INTERNAL_SRAM"].address_space == "data"
    assert by_name["INTERNAL_SRAM"].kind == "sram"
    assert by_name["EEPROM"].address_space == "eeprom"
    assert by_name["EEPROM"].kind == "eeprom"
    # EEPROM must carry zero startup roles — it is never a copy-source or
    # volatile-target despite living in the "data" direction of hardware.
    assert by_name["EEPROM"].startup_roles == ()


def test_normalize_avr_da_has_avr8_vector_baseline(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """Phase 2.1/2.2: AVR vector slots start at slot 0 with ``__vector_0``
    (reset) — no ARM system-exception prefix."""
    device = run(
        PipelineScope(device="avr128da32"), microchip_avr_da_execution_context
    ).payload.devices[0]
    slots_by_index = {vector_slot.slot: vector_slot for vector_slot in device.vector_slots}
    assert 0 in slots_by_index
    assert slots_by_index[0].symbol_name == "__vector_0"
    assert slots_by_index[0].kind == "reset-handler"
    # No ARM fault handlers should appear.
    symbol_names = {vector_slot.symbol_name for vector_slot in device.vector_slots}
    assert "__stack_top" not in symbol_names
    assert "NMI_Handler" not in symbol_names
    assert "HardFault_Handler" not in symbol_names
    assert "SysTick_Handler" not in symbol_names


def test_normalize_avr_da_routes_usart_spi_twi_signals(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """PORTMUX bootstrap (Phase 0.5) must expose USART0/USART1/TWI0/SPI0
    signals so connection_candidates cover them."""
    device = run(
        PipelineScope(device="avr128da32"), microchip_avr_da_execution_context
    ).payload.devices[0]
    candidate_peripherals = {candidate.peripheral for candidate in device.connection_candidates}
    assert {"USART0", "USART1", "TWI0", "SPI0"} <= candidate_peripherals
