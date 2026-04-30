# ruff: noqa: E501

"""Runtime-lite driver semantic emission helpers.

This layer sits above runtime-lite facts. It publishes schema-aware semantic
traits that Alloy drivers can consume directly without scanning reflection
tables or rediscovering register meanings in the runtime.
"""

from __future__ import annotations

import re
from dataclasses import dataclass

from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    ConnectionCandidate,
    GpioPinDescriptor,
    PeripheralInstance,
    PinDefinition,
    RegisterDescriptor,
    RegisterFieldDescriptor,
)
from alloy_codegen.peripheral_traits import (
    PeripheralTemplate,
    load_all_templates,
    resolve_template,
    template_provenance_tag,
)
from alloy_codegen.reporting import EmittedArtifact

from .connector_model import canonical_peripheral_class
from .emission import (
    _collect_runtime_semantics_catalog,
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _semantic_enum_ref,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_dma_bindings,
    runtime_lite_peripheral_class_name,
)

GPIO_DRIVER_HEADER = "driver_semantics/gpio.hpp"
I2C_DRIVER_HEADER = "driver_semantics/i2c.hpp"
SPI_DRIVER_HEADER = "driver_semantics/spi.hpp"
UART_DRIVER_HEADER = "driver_semantics/uart.hpp"
DMA_DRIVER_HEADER = "driver_semantics/dma.hpp"
TIMER_DRIVER_HEADER = "driver_semantics/timer.hpp"
PWM_DRIVER_HEADER = "driver_semantics/pwm.hpp"
ADC_DRIVER_HEADER = "driver_semantics/adc.hpp"
DAC_DRIVER_HEADER = "driver_semantics/dac.hpp"
RTC_DRIVER_HEADER = "driver_semantics/rtc.hpp"
WATCHDOG_DRIVER_HEADER = "driver_semantics/watchdog.hpp"
CAN_DRIVER_HEADER = "driver_semantics/can.hpp"
ETH_DRIVER_HEADER = "driver_semantics/eth.hpp"
USB_DRIVER_HEADER = "driver_semantics/usb.hpp"
QSPI_DRIVER_HEADER = "driver_semantics/qspi.hpp"
SDMMC_DRIVER_HEADER = "driver_semantics/sdmmc.hpp"
COMMON_DRIVER_HEADER = "driver_semantics/common.hpp"

# PIO migrated to ``runtime_driver/pio.py`` under
# ``refactor-runtime-driver-semantics-per-class``; re-exported below for
# backwards compatibility with consumers importing from the legacy module.
from .runtime_driver.pio import (  # noqa: E402, F401
    PIO_DRIVER_HEADER,
    emit_runtime_driver_pio_semantics_header,
)
from .runtime_driver.watchdog import (  # noqa: E402, F401
    WATCHDOG_DRIVER_HEADER,
    WatchdogSemanticRow,
    emit_runtime_driver_watchdog_semantics_header,
)
from .runtime_driver.can import (  # noqa: E402, F401
    CAN_DRIVER_HEADER,
    CanSemanticRow,
    emit_runtime_driver_can_semantics_header,
)
from .runtime_driver.dac import (  # noqa: E402, F401
    DAC_DRIVER_HEADER,
    DacChannelSemanticRow,
    DacSemanticRow,
    emit_runtime_driver_dac_semantics_header,
)
from .runtime_driver.eth import (  # noqa: E402, F401
    ETH_DRIVER_HEADER,
    EthSemanticRow,
    emit_runtime_driver_eth_semantics_header,
)
from .runtime_driver.qspi import (  # noqa: E402, F401
    QSPI_DRIVER_HEADER,
    QspiSemanticRow,
    emit_runtime_driver_qspi_semantics_header,
)
from .runtime_driver.rtc import (  # noqa: E402, F401
    RTC_DRIVER_HEADER,
    RtcSemanticRow,
    emit_runtime_driver_rtc_semantics_header,
)
from .runtime_driver.sdmmc import (  # noqa: E402, F401
    SDMMC_DRIVER_HEADER,
    SdmmcSemanticRow,
    emit_runtime_driver_sdmmc_semantics_header,
)
from .runtime_driver.usb import (  # noqa: E402, F401
    USB_DRIVER_HEADER,
    UsbSemanticRow,
    emit_runtime_driver_usb_semantics_header,
)
from .runtime_driver.gpio import (  # noqa: E402, F401
    GPIO_DRIVER_HEADER,
    GpioSemanticRow,
    emit_runtime_driver_gpio_semantics_header,
)
from .runtime_driver.spi import (  # noqa: E402, F401
    SPI_DRIVER_HEADER,
    SpiDmaBindingRow,
    SpiSemanticRow,
    emit_runtime_driver_spi_semantics_header,
)
from .runtime_driver.i2c import (  # noqa: E402, F401
    I2C_DRIVER_HEADER,
    I2cSemanticRow,
    emit_runtime_driver_i2c_semantics_header,
)
from .runtime_driver.uart import (  # noqa: E402, F401
    UART_DRIVER_HEADER,
    UartBaudClockSource,
    UartBaudOversamplingOption,
    UartDataBitsOption,
    UartFifoTriggerOption,
    UartModeFlags,
    UartParityOption,
    UartSemanticRow,
    UartStopBitsOption,
    emit_runtime_driver_uart_semantics_header,
)
from .runtime_driver.adc import (  # noqa: E402, F401
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
    emit_runtime_driver_adc_semantics_header,
)
from .runtime_driver.dma import (  # noqa: E402, F401
    DMA_DRIVER_HEADER,
    DmaSemanticRow,
    emit_runtime_driver_dma_semantics_header,
)
from .runtime_driver.timer import (  # noqa: E402, F401
    TIMER_DRIVER_HEADER,
    TimerChannelSemanticRow,
    TimerSemanticRow,
    emit_runtime_driver_timer_semantics_header,
)
from .runtime_driver.pwm import (  # noqa: E402, F401
    PWM_DRIVER_HEADER,
    PwmChannelSemanticRow,
    PwmSemanticRow,
    emit_runtime_driver_pwm_semantics_header,
)
from .runtime_driver.common_header import (  # noqa: E402, F401
    emit_runtime_driver_semantics_common_header,
)

# Shared substrate moved to ``runtime_driver/common.py`` under
# ``refactor-runtime-driver-semantics-per-class`` Phase 1.2.  Re-exported
# below so the legacy module API stays stable.
from .runtime_driver.common import (  # noqa: E402, F401
    _IO_SIGNAL_PATTERN,
    KernelClockSourceOption,
    RuntimeFieldRef,
    RuntimeIndexedFieldRef,
    RuntimeRegisterRef,
    UartDmaBindingRow,
    _SemanticContext,
    _context,
    _dma_binding_direction_token,
    _dma_binding_ref_array_lines,
    _dma_binding_ref_expr,
    _emit_peripheral_semantics_header,
    _enrich_with_dma_bindings,
    _field_ref_expr,
    _generic_dma_bindings_for_peripheral,
    _irq_numbers_for_peripheral,
    _kernel_clock_lines,
    _peripheral_has_dma_binding,
    _indexed_field_ref,
    _indexed_field_ref_expr,
    _invalid_field_ref,
    _invalid_indexed_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _line_index_from_candidate,
    _manual_field_ref,
    _peripheral_ref,
    _pin_ref,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_field_ref_any,
    _resolve_field_ref_by_id,
    _resolve_register_ref,
    _resolve_register_ref_any,
    _schema_ref_expr,
)


# GpioSemanticRow → runtime_driver/gpio.py


# UartSemanticRow → runtime_driver/uart.py


# DmaSemanticRow → runtime_driver/dma.py


# TimerSemanticRow → runtime_driver/timer.py


# TimerChannelSemanticRow → runtime_driver/timer.py


# PwmSemanticRow → runtime_driver/pwm.py


# PwmChannelSemanticRow → runtime_driver/pwm.py


def _driver_semantics_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
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
    return _driver_semantics_paths(family_dir=family_dir, devices=devices)


# Resolution / refs / expr helpers moved to
# ``runtime_driver/common.py`` under
# ``refactor-runtime-driver-semantics-per-class`` Phase 1.2.
# Re-exported via the ``from .runtime_driver.common import …``
# block at the top of this module.


# ---------------------------------------------------------------------------
# ADC trait helpers (Tier 2/3/4 — added by add-full-adc-coverage)
# ---------------------------------------------------------------------------


# _adc_internal_channel_expr → runtime_driver/adc.py


# _ADC_INTERNAL_KIND_ENUMERATOR_NAME → runtime_driver/adc.py


# _render_typed_option_enum_block → runtime_driver/common.py (duplicate removed)


# _render_array_lines → runtime_driver/common.py (duplicate removed)


# _classify_kernel_clock_source → runtime_driver/common.py (duplicate removed)


# _kernel_clock_for_peripheral → runtime_driver/common.py (duplicate removed)


# _emit_driver_semantics_common_header → runtime_driver/common_header.py


# emit_runtime_driver_semantics_common_header → runtime_driver/common_header.py


