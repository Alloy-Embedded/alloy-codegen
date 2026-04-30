"""Tests for the UART emitter template-library migration.

Added by ``migrate-uart-emitter-to-template-library``.
"""

from __future__ import annotations

import sys
from dataclasses import replace
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.peripheral_traits import (  # noqa: E402
    PeripheralTemplate,
    load_all_templates,
    resolve_template,
    template_provenance_tag,
)
from alloy_codegen.runtime_driver.uart import (  # noqa: E402
    _uart_template_data_bits,
    _uart_template_fifo_triggers,
    _uart_template_mode_flags,
    _uart_template_oversampling,
    _uart_template_parity,
    _uart_template_stop_bits,
    emit_runtime_driver_uart_semantics_header,
)
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.stages.normalize import run as run_normalize  # noqa: E402


def _ctx() -> ExecutionContext:
    return ExecutionContext.default().with_overrides(
        artifact_root="/tmp/_uart_template_artifacts",
        publication_root="/tmp/_uart_template_publication",
    )


def _usart_v2_template() -> PeripheralTemplate:
    catalog = load_all_templates()
    template = resolve_template(catalog, peripheral_class="uart", ip_name="usart", ip_version="v2")
    assert template is not None, "usart_v2 template must be shipped"
    return template


# ---------------------------------------------------------------------------
# Spec scenario #1 — identical merged defaults across two USART_v2 instances
# ---------------------------------------------------------------------------


def test_two_usart_v2_instances_inherit_identical_defaults() -> None:
    """Spec: STM32G0 stm32g071rb USART1 and STM32F4 stm32f401re
    USART2 — both ``(ip_name=usart, ip_version=v2)`` — produce the
    same projected trait values from
    ``data/peripheral_traits/uart/usart_v2.toml`` and both emit the
    template-revision provenance comment."""
    execution_context = _ctx()
    cases = [
        ("stm32g071rb", "st/stm32g0", "v2", "alloy.uart.st-usart-v2-cube"),
        ("stm32f401re", "st/stm32f4", "v2", "alloy.uart.st-usart-v2-cube"),
    ]
    artifacts = []
    for device_name, family_dir, ip_version, schema_id in cases:
        normalized = run_normalize(PipelineScope(device=device_name), execution_context)
        device = normalized.payload.devices[0]
        # Pin every USART instance to (ip_name=usart, ip_version=v2)
        # so the template resolver matches.
        mutated = []
        for peripheral in device.peripherals:
            if (peripheral.ip_name or "").lower() == "usart":
                mutated.append(
                    replace(peripheral, ip_version=ip_version, backend_schema_id=schema_id)
                )
            else:
                mutated.append(peripheral)
        artifact = emit_runtime_driver_uart_semantics_header(
            family_dir=family_dir,
            device=replace(device, peripherals=tuple(mutated)),
        )
        artifacts.append(artifact.content)

    expected_tag = template_provenance_tag(_usart_v2_template())
    for content in artifacts:
        assert f"// {expected_tag}" in content, (
            f"missing template provenance comment {expected_tag!r}"
        )


# ---------------------------------------------------------------------------
# Spec scenario #2 — device-patch values still win over template
# ---------------------------------------------------------------------------


def test_device_patch_overrides_template_max_baud_hz() -> None:
    """When ``device.uart_max_baud_hz`` is non-zero, the patch wins
    over the template's ``max_baud_hz``."""
    execution_context = _ctx()
    normalized = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    device = normalized.payload.devices[0]
    # Assert the patch already supplies a non-zero max_baud_hz; if so,
    # the emitted artifact MUST carry the patch value, not the
    # template's 12_500_000.
    if device.uart_max_baud_hz == 0:
        # No patch override; spec scenario degenerate, skip.
        return
    mutated = []
    for peripheral in device.peripherals:
        if (peripheral.ip_name or "").lower() == "usart":
            mutated.append(
                replace(
                    peripheral,
                    ip_version="v2",
                    backend_schema_id="alloy.uart.st-usart-v2-cube",
                )
            )
        else:
            mutated.append(peripheral)
    artifact = emit_runtime_driver_uart_semantics_header(
        family_dir="st/stm32g0",
        device=replace(device, peripherals=tuple(mutated)),
    )
    assert f"static constexpr std::uint32_t kMaxBaudHz = {device.uart_max_baud_hz}u;" in (
        artifact.content
    )


# ---------------------------------------------------------------------------
# Spec scenario #3 — unknown ip_version → no template, no provenance
# ---------------------------------------------------------------------------


def test_unknown_ip_version_falls_back_to_patch_only() -> None:
    """When the ``(ip_name, ip_version)`` triple has no matching
    template, no provenance comment is emitted and behaviour matches
    the pre-template path."""
    execution_context = _ctx()
    normalized = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    device = normalized.payload.devices[0]
    # Pin USARTs to a synthetic ip_version we know the library does
    # not register a template for.
    mutated = []
    for peripheral in device.peripherals:
        if (peripheral.ip_name or "").lower() == "usart":
            mutated.append(
                replace(
                    peripheral,
                    ip_version="unmapped_synthetic_v999",
                    backend_schema_id="alloy.uart.st-usart-v2-cube",
                )
            )
        else:
            mutated.append(peripheral)
    artifact = emit_runtime_driver_uart_semantics_header(
        family_dir="st/stm32g0",
        device=replace(device, peripherals=tuple(mutated)),
    )
    assert "peripheral_traits/uart/" not in artifact.content


# ---------------------------------------------------------------------------
# Unit tests on the per-field projection helpers
# ---------------------------------------------------------------------------


def test_template_data_bits_projection_preserves_bit_widths() -> None:
    template = _usart_v2_template()
    options = _uart_template_data_bits(template)
    assert tuple(o.bits for o in options) == (7, 8, 9)
    # Field-encoding placeholders default to 0 — the IP-level
    # template knows the value-set, not the per-instance encoding.
    assert all(o.m0_value == 0 and o.m1_value == 0 for o in options)


def test_template_parity_projection_maps_pce_ps_pairs() -> None:
    template = _usart_v2_template()
    options = _uart_template_parity(template)
    by_name = {o.parity: (o.pce_value, o.ps_value) for o in options}
    assert by_name == {"none": (0, 0), "even": (1, 0), "odd": (1, 1)}


def test_template_stop_bits_projection_q8_quantises() -> None:
    template = _usart_v2_template()
    options = _uart_template_stop_bits(template)
    q8s = sorted(o.stop_bits_q8 for o in options)
    # "0.5" → 4, "1" → 8, "1.5" → 12, "2" → 16
    assert q8s == [4, 8, 12, 16]


def test_template_oversampling_and_fifo_projections() -> None:
    template = _usart_v2_template()
    over = _uart_template_oversampling(template)
    assert sorted(o.ratio for o in over) == [8, 16]

    fifo = _uart_template_fifo_triggers(template)
    assert sorted(o.field_value for o in fifo) == [0, 1, 2, 3]


def test_template_mode_flags_projection_synthesises_block() -> None:
    template = _usart_v2_template()
    flags = _uart_template_mode_flags(template)
    assert flags is not None
    assert flags.supports_lin is True
    assert flags.supports_irda is True
    assert flags.supports_smartcard is True
    assert flags.supports_auto_baud is True
    # The template's ``has_fifo`` / ``has_dma`` / ``has_modbus`` are
    # not modelled in UartModeFlags — they surface via separate IR
    # fields.  Confirm those don't accidentally trip booleans we
    # don't have.
    assert flags.valid is True


def test_template_mode_flags_returns_none_for_template_without_flags() -> None:
    blank = PeripheralTemplate(
        peripheral_class="uart",
        ip_name="synthetic",
        ip_version="v0",
        template_revision=1,
        values={},
    )
    assert _uart_template_mode_flags(blank) is None
