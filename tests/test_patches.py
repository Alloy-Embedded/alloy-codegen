from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, BOOTSTRAP_VENDOR, bootstrap_device_names
from alloy_codegen.patches import load_device_patch, load_family_patch_catalog


def test_all_bootstrap_devices_have_patch_documents(execution_context) -> None:
    family_catalog = load_family_patch_catalog(
        execution_context, vendor=BOOTSTRAP_VENDOR, family=BOOTSTRAP_FAMILY
    )

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
        patch = load_device_patch(
            execution_context, device_name, vendor=BOOTSTRAP_VENDOR, family=BOOTSTRAP_FAMILY
        )
        assert patch.device == device_name
        assert patch.family_patch_id == family_catalog.patch_id
        assert patch.svd_file.endswith(".svd")
        assert patch.pin_data_file.endswith(".xml")
        assert patch.pins == ()
        assert all(peripheral.rcc_enable_signal for peripheral in patch.peripherals)


def test_device_patch_declares_open_pin_data_source(execution_context) -> None:
    patch = load_device_patch(
        execution_context, "stm32g071rb", vendor=BOOTSTRAP_VENDOR, family=BOOTSTRAP_FAMILY
    )

    assert patch.pin_count == 64
    assert patch.package == "lqfp64"
    assert patch.pin_data_file == "STM32G071R(6-8-B)Tx.xml"


def test_device_patch_derives_package_metadata_from_family_catalog(execution_context) -> None:
    patch = load_device_patch(
        execution_context, "stm32g030f6", vendor=BOOTSTRAP_VENDOR, family=BOOTSTRAP_FAMILY
    )

    assert patch.package == "tssop20"
    assert patch.pin_count == 20
    assert patch.pin_data_file == "STM32G030F6Px.xml"


def test_device_patch_resolves_dma_requests_from_family_catalog(execution_context) -> None:
    patch = load_device_patch(
        execution_context, "stm32g071rb", vendor=BOOTSTRAP_VENDOR, family=BOOTSTRAP_FAMILY
    )

    assert [request.request_line for request in patch.dma_requests] == ["DMA1_CH1", "DMA1_CH2"]
    assert [request.signal for request in patch.dma_requests] == ["RX", "TX"]
    assert [request.channel_index for request in patch.dma_requests] == [0, 1]
    assert [request.request_value for request in patch.dma_requests] == [50, 51]
