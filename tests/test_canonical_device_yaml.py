"""Tests for the canonical-device YAML serializer + emitter.

Added by ``define-canonical-device-yaml-schema``.
"""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.bootstrap import DEVICE_REGISTRY, registered_device_names  # noqa: E402
from alloy_codegen.canonical_device_yaml import (  # noqa: E402
    DEVICE_SCHEMA_PATH,
    parse_device,
    serialize_device,
    validate_device,
)
from alloy_codegen.canonical_device_yaml_emitter import (  # noqa: E402
    emit_canonical_device_yaml,
)
from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.errors import StageExecutionError  # noqa: E402
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.serialization import to_primitive  # noqa: E402
from alloy_codegen.stages.normalize import run as run_normalize  # noqa: E402

# Source-override map per (vendor, family) so the test can run
# the normalize stage against snapshotted fixtures, hermetic.
_FIXTURES = ROOT / "tests" / "fixtures"
_SOURCE_OVERRIDES: dict[tuple[str, str], dict[str, str]] = {
    ("st", "stm32g0"): {
        "cmsis-svd-data": str(_FIXTURES / "cmsis-svd-data"),
        "stm32-open-pin-data": str(_FIXTURES / "stm32-open-pin-data"),
    },
    ("st", "stm32f4"): {
        "cmsis-svd-data": str(_FIXTURES / "cmsis-svd-data"),
        "stm32-open-pin-data": str(_FIXTURES / "stm32-open-pin-data"),
    },
    ("microchip", "same70"): {
        "microchip-dfp-extract": str(_FIXTURES / "microchip-dfp-same70"),
    },
    ("microchip", "avr-da"): {
        "microchip-dfp-extract": str(_FIXTURES / "microchip-dfp-avr-da"),
    },
    ("nxp", "imxrt1060"): {
        "nxp-mcux-soc-svd": str(_FIXTURES / "nxp-mcux-imxrt1060" / "svd"),
        "nxp-mcux-sdk": str(_FIXTURES / "nxp-mcux-imxrt1060" / "sdk"),
    },
    ("raspberrypi", "rp2040"): {"pico-sdk": str(_FIXTURES / "pico-sdk")},
    ("espressif", "esp32"): {"espressif-svd": str(_FIXTURES / "espressif-svd")},
    ("espressif", "esp32c3"): {"espressif-svd": str(_FIXTURES / "espressif-svd")},
    ("espressif", "esp32s3"): {"espressif-svd": str(_FIXTURES / "espressif-svd")},
    ("nordic", "nrf52"): {"zephyr-dts": str(_FIXTURES / "zephyr-dts")},
}


def _admitted_triples() -> list[tuple[str, str, str]]:
    triples: list[tuple[str, str, str]] = []
    for (vendor, family), _devices in DEVICE_REGISTRY.items():
        for device in registered_device_names(vendor, family):
            triples.append((vendor, family, device))
    return sorted(triples)


def _build_ir(vendor: str, family: str, device: str, tmp_path: Path):
    overrides = _SOURCE_OVERRIDES.get((vendor, family), {})
    ctx = ExecutionContext.default().with_overrides(
        source_overrides=overrides,
        artifact_root=str(tmp_path / "a"),
        publication_root=str(tmp_path / "p"),
    )
    return run_normalize(PipelineScope(device=device), ctx).payload.devices[0]


# ---------------------------------------------------------------------------
# Schema presence + structure
# ---------------------------------------------------------------------------


def test_device_schema_file_ships() -> None:
    assert DEVICE_SCHEMA_PATH.exists(), (
        f"missing canonical-device JSON schema at {DEVICE_SCHEMA_PATH}"
    )


# ---------------------------------------------------------------------------
# Round-trip + determinism contract — parametrised across every
# admitted (vendor, family, device) triple.
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("triple", _admitted_triples())
def test_serialize_then_validate_passes_schema(
    triple: tuple[str, str, str], tmp_path: Path
) -> None:
    """Spec scenario: every admitted device's canonical YAML
    passes the JSON Schema."""
    vendor, family, device = triple
    ir = _build_ir(vendor, family, device, tmp_path)
    text = serialize_device(ir)
    validate_device(text)  # raises on schema failure


@pytest.mark.parametrize("triple", _admitted_triples())
def test_round_trip_is_primitive_equivalent(triple: tuple[str, str, str], tmp_path: Path) -> None:
    """Spec scenario: parse_device(serialize_device(ir)) is
    equivalent to ir under the canonical-form (to_primitive)
    contract."""
    vendor, family, device = triple
    ir = _build_ir(vendor, family, device, tmp_path)
    text = serialize_device(ir)
    ir_back = parse_device(text)
    assert to_primitive(ir) == to_primitive(ir_back)


@pytest.mark.parametrize("triple", _admitted_triples())
def test_serialization_is_byte_stable(triple: tuple[str, str, str], tmp_path: Path) -> None:
    """Spec scenario: serialise → parse → re-serialise produces
    byte-identical output."""
    vendor, family, device = triple
    ir = _build_ir(vendor, family, device, tmp_path)
    text_a = serialize_device(ir)
    text_b = serialize_device(parse_device(text_a))
    assert text_a == text_b


# ---------------------------------------------------------------------------
# Determinism + key-order contract
# ---------------------------------------------------------------------------


def test_top_level_keys_emitted_in_canonical_order(tmp_path: Path) -> None:
    """schema_version always first, identity second, provenance third —
    contract from canonical_device_yaml._TOP_LEVEL_KEY_ORDER."""
    ir = _build_ir("st", "stm32g0", "stm32g071rb", tmp_path)
    text = serialize_device(ir)
    lines = [line for line in text.splitlines() if line and not line.startswith(" ")]
    # First three top-level keys (lines without leading space).
    first_three = [line.split(":", 1)[0] for line in lines[:3]]
    assert first_three == ["schema_version", "identity", "provenance"]


def test_double_serialize_on_same_ir_produces_identical_text(tmp_path: Path) -> None:
    ir = _build_ir("nordic", "nrf52", "nrf52840", tmp_path)
    text_a = serialize_device(ir)
    text_b = serialize_device(ir)
    assert text_a == text_b


# ---------------------------------------------------------------------------
# Schema validation failure modes
# ---------------------------------------------------------------------------


def test_validate_rejects_missing_required_fields() -> None:
    bad = "schema_version: '1.2.0'\n"  # missing identity
    with pytest.raises(StageExecutionError, match="schema validation"):
        validate_device(bad)


def test_validate_rejects_non_mapping_top_level() -> None:
    with pytest.raises(StageExecutionError, match="mapping"):
        parse_device("- foo\n- bar\n")


# ---------------------------------------------------------------------------
# Emitter integration
# ---------------------------------------------------------------------------


def test_emitter_produces_yaml_artifact_for_admitted_device(tmp_path: Path) -> None:
    ir = _build_ir("st", "stm32g0", "stm32g071rb", tmp_path)
    artifact = emit_canonical_device_yaml(family_dir="st/stm32g0", device=ir)
    assert artifact.path == "st/stm32g0/generated/devices/stm32g071rb.yml"
    assert artifact.artifact_kind == "generated-yaml"
    assert artifact.content.startswith("schema_version:")
    # Schema-valid by construction (emitter validates before returning).
    validate_device(artifact.content)


def test_pipeline_emit_includes_canonical_yaml_per_device(tmp_path: Path) -> None:
    """End-to-end: the emit stage produces one .yml per admitted
    device alongside the existing C++ headers."""
    from alloy_codegen.stages.emit import run as run_emit

    overrides = _SOURCE_OVERRIDES[("st", "stm32g0")]
    ctx = ExecutionContext.default().with_overrides(
        source_overrides=overrides,
        artifact_root=str(tmp_path / "a"),
        publication_root=str(tmp_path / "p"),
    )
    result = run_emit(PipelineScope(device="stm32g071rb"), ctx)
    yml_paths = [a.path for a in result.payload.artifacts if a.path.endswith(".yml")]
    assert "st/stm32g0/generated/devices/stm32g071rb.yml" in yml_paths
