from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR, PeripheralInstance, PinDefinition
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.validate import run as run_validate
from alloy_codegen.validation import build_validation_report


def test_validate_reports_gate_statuses(execution_context: ExecutionContext) -> None:
    result = run_validate(PipelineScope(device="stm32g071rb"), execution_context)
    report = result.payload.report

    assert result.status == "completed"
    assert report.report_id == "bootstrap-validation-v1"
    assert report.gate_status("gate-a").passed is True
    assert report.gate_status("gate-b").passed is True
    assert report.gate_status("gate-c").passed is True


def test_validation_fails_gate_c_when_pin_gpio_mapping_is_invalid(
    execution_context: ExecutionContext,
) -> None:
    normalize_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = normalize_result.payload.devices[0]
    broken_pin = PinDefinition(
        name="PZ0",
        port="Z",
        number=0,
        signals=(),
        provenance=original_device.provenance,
    )
    broken_device = CanonicalDeviceIR(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=(broken_pin,),
        peripherals=original_device.peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
    )

    report = build_validation_report(
        scope=normalize_result.scope,
        source_manifest=normalize_result.payload.source_manifest,
        patch_manifest=normalize_result.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-pin-port-has-gpio-peripheral" in failing_rules


def test_validation_fails_gate_c_when_referenced_peripheral_lacks_rcc_enable(
    execution_context: ExecutionContext,
) -> None:
    normalize_result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    original_device = normalize_result.payload.devices[0]
    broken_peripherals = tuple(
        PeripheralInstance(
            name=peripheral.name,
            ip_name=peripheral.ip_name,
            instance=peripheral.instance,
            base_address=peripheral.base_address,
            rcc_enable_signal=None if peripheral.name == "USART1" else peripheral.rcc_enable_signal,
            rcc_reset_signal=peripheral.rcc_reset_signal,
            provenance=peripheral.provenance,
        )
        for peripheral in original_device.peripherals
    )
    broken_device = CanonicalDeviceIR(
        schema_version=original_device.schema_version,
        identity=original_device.identity,
        memories=original_device.memories,
        packages=original_device.packages,
        pins=original_device.pins,
        peripherals=broken_peripherals,
        interrupts=original_device.interrupts,
        dma_requests=original_device.dma_requests,
        provenance=original_device.provenance,
    )

    report = build_validation_report(
        scope=normalize_result.scope,
        source_manifest=normalize_result.payload.source_manifest,
        patch_manifest=normalize_result.payload.patch_manifest,
        devices=(broken_device,),
    )

    assert report.gate_status("gate-c").passed is False
    failing_rules = {result.rule_id for result in report.results if not result.passed}
    assert "stm32g071rb-referenced-peripherals-have-rcc-enable" in failing_rules
