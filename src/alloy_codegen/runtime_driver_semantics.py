# ruff: noqa: E501

"""Runtime-lite driver semantic emission helpers — backwards-compat shim.

Every per-peripheral-class emitter has moved to its own module under
``alloy_codegen/runtime_driver/`` (see
``refactor-runtime-driver-semantics-per-class``).  This module is now
a thin re-export shim so external consumers importing from
``alloy_codegen.runtime_driver_semantics`` keep working.

New code should import directly from the per-class module:

    from alloy_codegen.runtime_driver.uart import emit_runtime_driver_uart_semantics_header
    from alloy_codegen.runtime_driver.common import _SemanticContext, _resolve_field_ref
    from alloy_codegen.runtime_driver.common_header import emit_runtime_driver_semantics_common_header
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR

from .runtime_driver.adc import (  # noqa: F401
    ADC_DRIVER_HEADER,
    AdcCalibrationContext,
    AdcCalibrationDataPoint,
    AdcDmaBindingRow,
    AdcDmaModeOption,
    AdcExternalTrigger,
    AdcInternalChannel,
    AdcOversamplingOption,
    AdcResolutionOption,
    AdcSampleTimeOption,
    AdcSemanticRow,
    _ADC_INTERNAL_KIND_ENUMERATOR_NAME,
    emit_runtime_driver_adc_semantics_header,
)
from .runtime_driver.can import (  # noqa: F401
    CAN_DRIVER_HEADER,
    CanSemanticRow,
    emit_runtime_driver_can_semantics_header,
)

# Shared substrate (foundational dataclasses + resolve / expr helpers).
from .runtime_driver.common import (  # noqa: F401
    _IO_SIGNAL_PATTERN,
    KernelClockSourceOption,
    RuntimeFieldRef,
    RuntimeIndexedFieldRef,
    RuntimeRegisterRef,
    UartDmaBindingRow,
    _context,
    _dma_binding_direction_token,
    _dma_binding_ref_array_lines,
    _dma_binding_ref_expr,
    _emit_peripheral_semantics_header,
    _enrich_with_dma_bindings,
    _field_ref_expr,
    _generic_dma_bindings_for_peripheral,
    _indexed_field_ref,
    _indexed_field_ref_expr,
    _invalid_field_ref,
    _invalid_indexed_field_ref,
    _invalid_register_ref,
    _irq_numbers_for_peripheral,
    _irq_numbers_lines,
    _kernel_clock_lines,
    _line_index_from_candidate,
    _manual_field_ref,
    _peripheral_has_dma_binding,
    _peripheral_ref,
    _pin_ref,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_field_ref_any,
    _resolve_field_ref_by_id,
    _resolve_register_ref,
    _resolve_register_ref_any,
    _schema_ref_expr,
    _SemanticContext,
)
from .runtime_driver.common_header import (  # noqa: F401
    COMMON_DRIVER_HEADER,
    emit_runtime_driver_semantics_common_header,
)
from .runtime_driver.dac import (  # noqa: F401
    DAC_DRIVER_HEADER,
    DacChannelSemanticRow,
    DacSemanticRow,
    emit_runtime_driver_dac_semantics_header,
)
from .runtime_driver.dma import (  # noqa: F401
    DMA_DRIVER_HEADER,
    DmaSemanticRow,
    emit_runtime_driver_dma_semantics_header,
)
from .runtime_driver.eth import (  # noqa: F401
    ETH_DRIVER_HEADER,
    EthSemanticRow,
    emit_runtime_driver_eth_semantics_header,
)
from .runtime_driver.gpio import (  # noqa: F401
    GPIO_DRIVER_HEADER,
    GpioSemanticRow,
    emit_runtime_driver_gpio_semantics_header,
)
from .runtime_driver.i2c import (  # noqa: F401
    I2C_DRIVER_HEADER,
    I2cSemanticRow,
    emit_runtime_driver_i2c_semantics_header,
)
from .runtime_driver.pio import (  # noqa: F401
    PIO_DRIVER_HEADER,
    emit_runtime_driver_pio_semantics_header,
)
from .runtime_driver.pwm import (  # noqa: F401
    PWM_DRIVER_HEADER,
    PwmChannelSemanticRow,
    PwmSemanticRow,
    emit_runtime_driver_pwm_semantics_header,
)
from .runtime_driver.qspi import (  # noqa: F401
    QSPI_DRIVER_HEADER,
    QspiSemanticRow,
    emit_runtime_driver_qspi_semantics_header,
)
from .runtime_driver.rtc import (  # noqa: F401
    RTC_DRIVER_HEADER,
    RtcSemanticRow,
    emit_runtime_driver_rtc_semantics_header,
)
from .runtime_driver.sdmmc import (  # noqa: F401
    SDMMC_DRIVER_HEADER,
    SdmmcSemanticRow,
    emit_runtime_driver_sdmmc_semantics_header,
)
from .runtime_driver.spi import (  # noqa: F401
    SPI_DRIVER_HEADER,
    SpiDmaBindingRow,
    SpiSemanticRow,
    emit_runtime_driver_spi_semantics_header,
)
from .runtime_driver.timer import (  # noqa: F401
    TIMER_DRIVER_HEADER,
    TimerChannelSemanticRow,
    TimerSemanticRow,
    emit_runtime_driver_timer_semantics_header,
)
from .runtime_driver.uart import (  # noqa: F401
    UART_DRIVER_HEADER,
    UartBaudClockSource,
    UartBaudOversamplingOption,
    UartDataBitsOption,
    UartFifoTriggerOption,
    UartModeFlags,
    UartParityOption,
    UartSemanticRow,
    UartStopBitsOption,
    _uart_template_data_bits,
    emit_runtime_driver_uart_semantics_header,
)
from .runtime_driver.usb import (  # noqa: F401
    USB_DRIVER_HEADER,
    UsbSemanticRow,
    emit_runtime_driver_usb_semantics_header,
)
from .runtime_driver.watchdog import (  # noqa: F401
    WATCHDOG_DRIVER_HEADER,
    WatchdogSemanticRow,
    emit_runtime_driver_watchdog_semantics_header,
)
from .runtime_lite_emission import _device_runtime_generated_path


def _driver_semantics_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    """Collect every ``driver_semantics/*.hpp`` path the pipeline emits.

    Used by the artifact-manifest stage to enumerate expected outputs.
    """
    paths: list[str] = []
    for device in devices:
        device_name = device.identity.device
        paths.extend(
            (
                _device_runtime_generated_path(family_dir, device_name, COMMON_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, GPIO_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, UART_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, I2C_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, SPI_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, DMA_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, TIMER_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, PWM_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, ADC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, DAC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, RTC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, WATCHDOG_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, CAN_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, ETH_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, USB_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, QSPI_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, SDMMC_DRIVER_HEADER),
                _device_runtime_generated_path(family_dir, device_name, PIO_DRIVER_HEADER),
            )
        )
    return tuple(paths)


def runtime_driver_semantics_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    """Public entry point for the artifact-manifest enumerator."""
    return _driver_semantics_paths(family_dir=family_dir, devices=devices)


__all__ = [
    # Per-class header constants.
    "ADC_DRIVER_HEADER",
    "CAN_DRIVER_HEADER",
    "COMMON_DRIVER_HEADER",
    "DAC_DRIVER_HEADER",
    "DMA_DRIVER_HEADER",
    "ETH_DRIVER_HEADER",
    "GPIO_DRIVER_HEADER",
    "I2C_DRIVER_HEADER",
    "PIO_DRIVER_HEADER",
    "PWM_DRIVER_HEADER",
    "QSPI_DRIVER_HEADER",
    "RTC_DRIVER_HEADER",
    "SDMMC_DRIVER_HEADER",
    "SPI_DRIVER_HEADER",
    "TIMER_DRIVER_HEADER",
    "UART_DRIVER_HEADER",
    "USB_DRIVER_HEADER",
    "WATCHDOG_DRIVER_HEADER",
    # Per-class emitters.
    "emit_runtime_driver_adc_semantics_header",
    "emit_runtime_driver_can_semantics_header",
    "emit_runtime_driver_dac_semantics_header",
    "emit_runtime_driver_dma_semantics_header",
    "emit_runtime_driver_eth_semantics_header",
    "emit_runtime_driver_gpio_semantics_header",
    "emit_runtime_driver_i2c_semantics_header",
    "emit_runtime_driver_pio_semantics_header",
    "emit_runtime_driver_pwm_semantics_header",
    "emit_runtime_driver_qspi_semantics_header",
    "emit_runtime_driver_rtc_semantics_header",
    "emit_runtime_driver_sdmmc_semantics_header",
    "emit_runtime_driver_semantics_common_header",
    "emit_runtime_driver_spi_semantics_header",
    "emit_runtime_driver_timer_semantics_header",
    "emit_runtime_driver_uart_semantics_header",
    "emit_runtime_driver_usb_semantics_header",
    "emit_runtime_driver_watchdog_semantics_header",
    # Path collectors.
    "runtime_driver_semantics_required_paths",
]
