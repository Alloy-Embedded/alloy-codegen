"""§1.3 of close-runtime-semantics-gaps: assert that every field a public HAL
backend reads off ``*SemanticTraits`` resolves to a real ``RuntimeFieldRef``
in the published runtime-lite contract — i.e. zero ``kInvalidFieldRef`` for
the curated HAL-referenced field set, per admitted (vendor, peripheral class,
schema) tuple.

The test parses the emitted ``driver_semantics/*.hpp`` artifacts produced by
the live pipeline (no fixtures), so it catches IR-side regressions as well
as emitter-side ones.
"""

from __future__ import annotations

import re

import pytest

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run

# Each entry is: schema-id substring → tuple of trait field names that the
# public HAL backend reads. A field is "HAL-referenced" when ``src/hal``
# accesses it without an ``if constexpr (X.valid)`` shortcut, OR when the
# guarded path is the only path the schema is supposed to drive.
_HAL_REQUIRED_FIELDS_BY_SCHEMA: dict[str, tuple[str, ...]] = {
    # --- Microchip ---
    "i2c_microchip_twihs": (
        "kStartField",
        "kStopField",
        "kMsenField",
        "kMsdisField",
        "kSvdisField",
        "kSwrstField",
        "kTxdataField",
        "kRxdataField",
        "kTxcompField",
        "kTxrdyField",
        "kRxrdyField",
        "kNackField",
    ),
    "uart_microchip_uart": (
        "kRstrxField",
        "kRsttxField",
        "kRxdisField",
        "kTxdisField",
        "kRststaField",
        "kParField",
        "kChmodeField",
        "kCdField",
        "kRxenField",
        "kTxenField",
        "kTxrdyField",
        "kRxrdyField",
        "kTxemptyField",
        "kTxchrField",
        "kRxchrField",
    ),
    "uart_microchip_usart": (
        "kUsRstrxField",
        "kUsRsttxField",
        "kUsRxdisField",
        "kUsTxdisField",
        "kUsRststaField",
        "kUsUsartModeField",
        "kUsUsclksField",
        "kUsChrlField",
        "kUsCdField",
        "kUsRxenField",
        "kUsTxenField",
        "kUsTxrdyField",
        "kUsRxrdyField",
        "kUsTxemptyField",
        "kUsTxchrField",
        "kUsRxchrField",
    ),
    "spi_microchip_spi": (
        "kSpienField",
        "kSpidisField",
        "kSwrstField",
        "kPsField",
        "kPcsdecField",
        "kModfdisField",
        "kPcsField",
        "kDlybcsField",
        "kNcphaField",
        "kCpolField",
        "kMstrField",
        "kBitsField",
        "kScbrField",
        "kDlybsField",
        "kDlybctField",
        "kTdreField",
        "kRdrfField",
        "kTxemptyField",
        "kTdField",
        "kRdField",
    ),
    "eth_microchip_gmac": (
        "kRxEnableField",
        "kTxEnableField",
        "kManagementPortEnableField",
        "kSpeedField",
        "kFullDuplexField",
    ),
    # --- ST (modern USART used by G0 / L4 / U5 / etc.) ---
    "uart_st_usart": (
        "kUeField",
        "kReField",
        "kTeField",
        "kPceField",
        "kPsField",
        "kStopField",
        "kM0Field",
        "kM1Field",
        "kTxeIsrField",
        "kRxneIsrField",
        "kTcIsrField",
        "kTdrField",
        "kRdrField",
    ),
    # --- ST F4-style legacy USART ---
    "uart_st_uart": (
        "kUeField",
        "kReField",
        "kTeField",
        "kPceField",
        "kPsField",
        "kStopField",
        "kMField",
        "kTxeSrField",
        "kRxneSrField",
        "kTcSrField",
        "kDrField",
    ),
    # --- NXP LPSPI (IMXRT) ---
    "spi_nxp_lpspi": (
        "kCphaField",
        "kCpolField",
        "kMstrField",
        "kBrField",
        "kSpeField",
        "kLsbfirstField",
        "kDsField",
        "kPcsField",
        "kBitsField",
        "kScbrField",
        "kDlybsField",
        "kDlybctField",
        "kSwrstField",
        "kTdField",
        "kRdField",
    ),
}

_SPEC_BLOCK_RE = re.compile(
    r"template<>\s*\nstruct\s+(\w+SemanticTraits)<PeripheralId::(\w+)>\s*\{(?P<body>.*?)\n\};",
    re.DOTALL,
)
_SCHEMA_RE = re.compile(r"BackendSchemaId::(?P<schema>\w+)")
_FAMILY_PATH_RE = re.compile(
    r"^(?P<family>[^/]+/[^/]+)/generated/runtime/devices/(?P<device>[^/]+)/driver_semantics/(?P<cls>\w+)\.hpp$"
)


def _required_fields(schema_enum: str) -> tuple[str, ...]:
    if schema_enum == "none":
        return ()
    for substring, fields in _HAL_REQUIRED_FIELDS_BY_SCHEMA.items():
        if substring in schema_enum:
            return fields
    return ()


def _audit(content: str, *, location: str) -> list[str]:
    failures: list[str] = []
    for match in _SPEC_BLOCK_RE.finditer(content):
        body = match.group("body")
        schema_match = _SCHEMA_RE.search(body)
        if not schema_match:
            continue
        schema_enum = schema_match.group("schema")
        required = _required_fields(schema_enum)
        if not required:
            continue
        peripheral = match.group(2)
        for field_name in required:
            invalid = re.search(rf"\b{field_name}\s*=\s*kInvalidFieldRef\b", body)
            if invalid:
                failures.append(
                    f"{location}: {peripheral} ({schema_enum}) {field_name} = kInvalidFieldRef"
                )
    return failures


def _pipeline_artifacts(scope: PipelineScope, ctx: ExecutionContext) -> dict[str, str]:
    result = run(scope, ctx)
    return {artifact.path: artifact.content for artifact in result.payload.artifacts}


@pytest.mark.parametrize(
    ("device", "ctx_fixture"),
    [
        ("atsame70q21b", "microchip_execution_context"),
        ("stm32g071rb", "execution_context"),
        ("mimxrt1062", "nxp_execution_context"),
    ],
)
def test_runtime_lite_hal_referenced_fields_have_no_invalid_field_refs(
    request: pytest.FixtureRequest,
    device: str,
    ctx_fixture: str,
) -> None:
    ctx = request.getfixturevalue(ctx_fixture)
    artifacts = _pipeline_artifacts(PipelineScope(device=device), ctx)
    failures: list[str] = []
    for path, content in artifacts.items():
        match = _FAMILY_PATH_RE.match(path)
        if match is None:
            continue
        if match.group("device") != device:
            continue
        failures.extend(_audit(content, location=path))
    assert not failures, "\n".join(failures)
