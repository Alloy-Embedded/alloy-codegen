from alloy_codegen.bootstrap import bootstrap_device_names
from alloy_codegen.patches import load_device_patch, load_family_patch_catalog


def test_all_bootstrap_devices_have_patch_documents(execution_context) -> None:
    family_catalog = load_family_patch_catalog(execution_context)

    assert family_catalog.patch_id == "st-stm32g0-family-bootstrap-v1"
    assert {package.name for package in family_catalog.packages} == {"tssop20", "lqfp64"}
    assert {pin.name for pin in family_catalog.pins} >= {"PA0", "PA2", "PA3", "PB6"}
    assert {signal.signal_id for signal in family_catalog.pin_signals} >= {
        "pa2-usart2-tx",
        "pa0-usart1-tx",
        "pa11-fdcan1-rx",
    }
    assert {request.request_id for request in family_catalog.dma_requests} >= {
        "dma1-usart2-tx",
        "dma1-usart1-rx",
    }
    assert family_catalog.peripherals

    for device_name in bootstrap_device_names():
        patch = load_device_patch(execution_context, device_name)
        assert patch.device == device_name
        assert patch.family_patch_id == family_catalog.patch_id
        assert patch.svd_file.endswith(".svd")
        assert patch.pins
        assert all(pin.signals for pin in patch.pins)
        assert all(peripheral.rcc_enable_signal for peripheral in patch.peripherals)


def test_device_patch_synthesizes_default_gpio_signal(execution_context) -> None:
    patch = load_device_patch(execution_context, "stm32g071rb")
    pa0 = next(pin for pin in patch.pins if pin.name == "PA0")

    assert patch.pin_count == 64
    assert pa0.signals[0].function == "gpio"
    assert pa0.signals[0].peripheral == "GPIOA"
    assert pa0.signals[0].signal == "IN0"
    assert pa0.signals[1].function == "usart1_tx"


def test_device_patch_derives_pin_metadata_from_family_catalog(execution_context) -> None:
    patch = load_device_patch(execution_context, "stm32g030f6")
    pa2 = next(pin for pin in patch.pins if pin.name == "PA2")

    assert patch.package == "tssop20"
    assert patch.pin_count == 20
    assert pa2.port == "A"
    assert pa2.number == 2
    assert pa2.signals[1].function == "usart2_tx"


def test_device_patch_resolves_dma_requests_from_family_catalog(execution_context) -> None:
    patch = load_device_patch(execution_context, "stm32g071rb")

    assert [request.request_line for request in patch.dma_requests] == ["DMA1_CH1", "DMA1_CH2"]
    assert [request.signal for request in patch.dma_requests] == ["RX", "TX"]
