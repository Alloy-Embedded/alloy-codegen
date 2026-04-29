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


@dataclass(frozen=True, slots=True)
class TimerSemanticRow:
    """Timer semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    counter_bits: int
    channel_count: int
    has_compare: bool
    has_capture: bool
    has_encoder: bool
    has_pwm: bool
    has_one_pulse: bool
    has_center_aligned: bool
    has_complementary_outputs: bool
    has_deadtime: bool
    has_break_input: bool
    control_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    event_reg: RuntimeRegisterRef
    counter_reg: RuntimeRegisterRef
    prescaler_reg: RuntimeRegisterRef
    period_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    module_disable_field: RuntimeFieldRef
    software_reset_field: RuntimeFieldRef
    start_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    update_interrupt_enable_field: RuntimeFieldRef
    update_flag_field: RuntimeFieldRef
    update_generation_field: RuntimeFieldRef
    prescaler_field: RuntimeFieldRef
    period_field: RuntimeFieldRef
    one_pulse_field: RuntimeFieldRef
    center_aligned_field: RuntimeFieldRef
    auto_reload_preload_field: RuntimeFieldRef
    clock_source_field: RuntimeFieldRef
    encoder_mode_field: RuntimeFieldRef
    encoder_enable_field: RuntimeFieldRef
    encoder_position_enable_field: RuntimeFieldRef
    encoder_speed_enable_field: RuntimeFieldRef
    encoder_phase_edge_field: RuntimeFieldRef
    direction_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # NVIC vector lines, split per advanced-timer convention (added by
    # ``add-irq-vector-traits``).  ``None`` when the chip doesn't surface
    # the vector; on chips with a single shared vector (e.g. STM32G0
    # ``TIM1_BRK_UP_TRG_COM``) all four fields point at the same line.
    update_irq_number: int | None = None
    capture_irq_number: int | None = None
    break_irq_number: int | None = None
    trigger_irq_number: int | None = None
    # DMA cross-references (add-peripheral-dma-cross-references).
    dma_bindings: tuple[UartDmaBindingRow, ...] = ()
    # Tier 2/3/4 facts (add-timer-tier-2-3-4-data).
    max_prescaler: int = 0
    max_auto_reload: int = 0
    trigger_sources: tuple[tuple[str, int], ...] = ()  # (source, field_value)
    master_outputs: tuple[tuple[str, int], ...] = ()  # (source, field_value)
    supports_dma_burst: bool = False
    supports_repetition_counter: bool = False
    supports_xor_input: bool = False


@dataclass(frozen=True, slots=True)
class TimerChannelSemanticRow:
    """Timer channel semantic trait payload keyed by peripheral/channel index."""

    peripheral_name: str
    channel_index: int
    supports_compare: bool
    supports_capture: bool
    supports_encoder_input: bool
    supports_pwm: bool
    supports_complementary_output: bool
    control_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    compare_reg: RuntimeRegisterRef
    secondary_compare_reg: RuntimeRegisterRef
    period_reg: RuntimeRegisterRef
    counter_reg: RuntimeRegisterRef
    capture_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    interrupt_enable_field: RuntimeFieldRef
    interrupt_flag_field: RuntimeFieldRef
    mode_field: RuntimeFieldRef
    preload_field: RuntimeFieldRef
    output_enable_field: RuntimeFieldRef
    output_polarity_field: RuntimeFieldRef
    complementary_output_enable_field: RuntimeFieldRef
    capture_select_field: RuntimeFieldRef


@dataclass(frozen=True, slots=True)
class PwmSemanticRow:
    """PWM semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    counter_bits: int
    channel_count: int
    has_complementary_outputs: bool
    has_deadtime: bool
    has_fault_input: bool
    has_center_aligned: bool
    has_synchronized_update: bool
    control_reg: RuntimeRegisterRef
    output_enable_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    clock_reg: RuntimeRegisterRef
    sync_reg: RuntimeRegisterRef
    master_output_enable_field: RuntimeFieldRef
    load_field: RuntimeFieldRef
    clear_load_field: RuntimeFieldRef
    clock_prescaler_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # Tier 2/3/4 facts (add-pwm-tier-2-3-4-data).
    max_prescaler: int = 0
    max_period: int = 0
    deadtime_options: tuple[
        tuple[int, int, int], ...
    ] = ()  # (prescaler_field_value, count_bits, max_ns)
    supported_alignments: tuple[tuple[str, int], ...] = ()  # (alignment, field_value)
    break_inputs: tuple[
        tuple[str, int, int], ...
    ] = ()  # (input_id, polarity_field_value, enable_field_value)
    supports_deadtime: bool = False
    supports_break_input: bool = False
    supports_complementary_outputs: bool = False
    supports_asymmetric_pwm: bool = False
    supports_combined_pwm: bool = False


@dataclass(frozen=True, slots=True)
class PwmChannelSemanticRow:
    """PWM channel semantic trait payload keyed by peripheral/channel index."""

    peripheral_name: str
    channel_index: int
    supports_complementary_output: bool
    supports_deadtime: bool
    control_reg: RuntimeRegisterRef
    compare_reg: RuntimeRegisterRef
    secondary_compare_reg: RuntimeRegisterRef
    period_reg: RuntimeRegisterRef
    deadtime_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    interrupt_enable_field: RuntimeFieldRef
    interrupt_flag_field: RuntimeFieldRef
    mode_field: RuntimeFieldRef
    polarity_field: RuntimeFieldRef
    complementary_output_enable_field: RuntimeFieldRef
    center_aligned_field: RuntimeFieldRef
    period_field: RuntimeFieldRef
    duty_field: RuntimeFieldRef
    deadtime_rise_field: RuntimeFieldRef
    deadtime_fall_field: RuntimeFieldRef


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


def _render_typed_option_enum_block(
    *,
    template_name: str,
    alias_name: str,
    peripheral_entries: tuple[tuple[str, tuple[tuple[str, int], ...]], ...],
    leading_comment: str | None = None,
) -> list[str]:
    """Render a per-peripheral typed-option ``enum class`` block.

    Mirrors the ``AdcChannelOf<P>`` pattern established by
    ``add-adc-channel-typed-enum`` and lifted out by
    ``add-typed-peripheral-enums-everywhere``: emits a primary
    template ``struct <template_name>`` carrying an empty ``enum
    class type : std::uint8_t {};``, plus one specialisation per
    populated peripheral with named ``(enumerator, field_value)``
    pairs.  Trails with a ``using <alias_name> = typename ...::type;``
    convenience alias.

    ``peripheral_entries`` is a tuple of
    ``(peripheral_id_enum, ((name, field_value), ...))`` pairs.
    Peripherals carrying no entries are skipped — consumers reach
    for the alias via ``if constexpr (kPresent)`` gates and the
    primary template's empty enum keeps that branch compilable.
    """
    lines: list[str] = []
    if leading_comment:
        lines.append(f"// {leading_comment}")
    lines.extend(
        [
            "template<PeripheralId Id>",
            f"struct {template_name} {{",
            "  enum class type : std::uint8_t {};",
            "};",
            "",
        ]
    )
    for peripheral_id, entries in peripheral_entries:
        if not entries:
            continue
        lines.extend(
            [
                "template<>",
                f"struct {template_name}<PeripheralId::{peripheral_id}> {{",
                "  enum class type : std::uint8_t {",
            ]
        )
        for name, field_value in entries:
            lines.append(f"    {name} = {field_value}u,")
        lines.extend(
            [
                "  };",
                "};",
                "",
            ]
        )
    lines.extend(
        [
            "template<PeripheralId Id>",
            f"using {alias_name} = typename {template_name}<Id>::type;",
            "",
        ]
    )
    return lines


# Note: a name-table helper was considered but dropped — runtime
# C++ artifacts must not carry string literals (publication gate),
# and the typed enums alone are the value-add.  Consumers needing
# stringification handle it host-side via switch statements over the
# typed enum values.


# _UART_PARITY_NAME → runtime_driver/uart.py


# _UART_PARITY_CANONICAL_ORDER → runtime_driver/uart.py


# _UART_STOP_BITS_NAME → runtime_driver/uart.py


# _UART_FIFO_TRIGGER_NAME → runtime_driver/uart.py


# _build_uart_typed_enum_blocks → runtime_driver/uart.py


def _build_timer_typed_enum_blocks(rows: tuple[TimerSemanticRow, ...]) -> list[str]:
    """Render TIMER typed-option enum blocks (trigger source / master
    output)."""
    trigger_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    master_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    for row in rows:
        if row.is_stub:
            continue
        peripheral_id = _enum_identifier(row.peripheral_name)
        triggers = tuple((str(src), idx) for idx, (src, _fv) in enumerate(row.trigger_sources))
        if triggers:
            trigger_entries.append((peripheral_id, triggers))
        masters = tuple((str(src), idx) for idx, (src, _fv) in enumerate(row.master_outputs))
        if masters:
            master_entries.append((peripheral_id, masters))

    lines: list[str] = []
    for spec in (
        ("TimerTriggerSourceOf", "TimerTriggerSource", trigger_entries),
        ("TimerMasterOutputOf", "TimerMasterOutput", master_entries),
    ):
        template_name, alias_name, entries = spec
        if not any(e for _, e in entries):
            continue
        lines.append(
            f"// add-typed-peripheral-enums-everywhere: typed {template_name} per peripheral."
        )
        lines.extend(
            _render_typed_option_enum_block(
                template_name=template_name,
                alias_name=alias_name,
                peripheral_entries=tuple(entries),
            )
        )
    return lines


def _build_pwm_typed_enum_blocks(rows: tuple[PwmSemanticRow, ...]) -> list[str]:
    """Render PWM typed-option enum blocks (alignment / break input)."""
    align_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    break_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    for row in rows:
        if row.is_stub:
            continue
        peripheral_id = _enum_identifier(row.peripheral_name)
        alignments = tuple(
            (str(name), idx) for idx, (name, _fv) in enumerate(row.supported_alignments)
        )
        if alignments:
            align_entries.append((peripheral_id, alignments))
        breaks = tuple(
            (str(input_id), idx) for idx, (input_id, _pol, _en) in enumerate(row.break_inputs)
        )
        if breaks:
            break_entries.append((peripheral_id, breaks))

    lines: list[str] = []
    for spec in (
        ("PwmAlignmentOf", "PwmAlignment", align_entries),
        ("PwmBreakInputOf", "PwmBreakInput", break_entries),
    ):
        template_name, alias_name, entries = spec
        if not any(e for _, e in entries):
            continue
        lines.append(
            f"// add-typed-peripheral-enums-everywhere: typed {template_name} per peripheral."
        )
        lines.extend(
            _render_typed_option_enum_block(
                template_name=template_name,
                alias_name=alias_name,
                peripheral_entries=tuple(entries),
            )
        )
    return lines


# _render_adc_channel_enum_block → runtime_driver/adc.py


# _adc_calibration_data_point_expr → runtime_driver/adc.py


# _adc_calibration_context_expr → runtime_driver/adc.py


# _adc_resolution_option_expr → runtime_driver/adc.py


# _adc_sample_time_option_expr → runtime_driver/adc.py


# _adc_oversampling_option_expr → runtime_driver/adc.py


# _adc_external_trigger_expr → runtime_driver/adc.py


# _adc_dma_binding_expr → runtime_driver/adc.py


# _adc_dma_mode_option_expr → runtime_driver/adc.py


def _render_array_lines(
    *,
    cpp_type: str,
    array_name: str,
    count_name: str,
    items: tuple[object, ...],
    expr_fn,  # type: ignore[no-untyped-def]
) -> list[str]:
    """Render a paired ``static constexpr std::uint32_t kCount`` +
    ``static constexpr std::array<T, N> kArray = { ... };`` declaration."""
    lines: list[str] = [
        f"  static constexpr std::uint32_t {count_name} = {len(items)}u;",
    ]
    if not items:
        lines.append(f"  static constexpr std::array<{cpp_type}, 0> {array_name} = {{}};")
        return lines
    item_lines = [f"    {expr_fn(item)}," for item in items]
    lines.append(f"  static constexpr std::array<{cpp_type}, {len(items)}> {array_name} = {{{{")
    lines.extend(item_lines)
    lines.append("  }};")
    return lines


def _timer_irq_lines(row: TimerSemanticRow) -> list[str]:
    """Render the four split TIMER vector scalars + the shared
    ``kIrqNumbers`` array.  Added by ``add-irq-vector-traits``.

    ``0xFFFFFFFFu`` sentinel for fields that aren't surfaced by the chip.
    The shared array unions all four lines de-duplicated, so consumers
    can either branch on the named scalar or iterate the array.
    """

    def _scalar(value: int | None) -> str:
        if value is None:
            return "0xFFFFFFFFu"
        return f"{value}u"

    union_lines: tuple[int, ...] = tuple(
        sorted(
            {
                v
                for v in (
                    row.update_irq_number,
                    row.capture_irq_number,
                    row.break_irq_number,
                    row.trigger_irq_number,
                )
                if v is not None
            }
        )
    )
    lines = [
        f"  static constexpr std::uint32_t kUpdateIrqNumber = {_scalar(row.update_irq_number)};",
        f"  static constexpr std::uint32_t kCaptureIrqNumber = {_scalar(row.capture_irq_number)};",
        f"  static constexpr std::uint32_t kBreakIrqNumber = {_scalar(row.break_irq_number)};",
        f"  static constexpr std::uint32_t kTriggerIrqNumber = {_scalar(row.trigger_irq_number)};",
    ]
    lines.extend(_irq_numbers_lines(union_lines))
    return lines


# _i2c_tier234_lines → runtime_driver/i2c.py


# _render_adc_tier_extension_lines → runtime_driver/adc.py


# _resolve_dma_router_peripheral → runtime_driver/dma.py


# _build_dma_rows → runtime_driver/dma.py


def _timer_irq_numbers_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> dict[str, int | None]:
    """Return the four split TIMER vector lines (UP/CC/BRK/TRG).

    STM32 advanced timers split IRQs across UP, CC, BRK, TRG vectors;
    smaller chips collapse them onto a single shared vector.  We classify
    each binding by its ``interrupt`` name suffix.  Returns a dict with
    keys ``update``, ``capture``, ``break_``, ``trigger`` mapping to the
    line index, or ``None`` when not surfaced.

    On chips where the four vectors collapse to one (e.g. STM32G0
    ``TIM1_BRK_UP_TRG_COM``), the same line populates all four slots that
    the binding name advertises, so the consumer can install one handler
    via any of the four constants.
    """
    update: int | None = None
    capture: int | None = None
    brk: int | None = None
    trigger: int | None = None
    for binding in context.device.interrupt_bindings:
        if binding.peripheral != peripheral_name:
            continue
        name = (binding.interrupt or "").upper()
        line = int(binding.line)
        # Order matters: classify on substrings so a shared
        # "TIM1_BRK_UP_TRG_COM" vector populates UP / BRK / TRG
        # simultaneously.
        if "UP" in name and update is None:
            update = line
        if (("CC" in name) or ("COM" in name)) and capture is None:
            capture = line
        if "BRK" in name and brk is None:
            brk = line
        if "TRG" in name and trigger is None:
            trigger = line
        # Unclassified single-vector chips: fall back to the only line.
        if update is None and capture is None and brk is None and trigger is None:
            update = line
            capture = line
    return {
        "update": update,
        "capture": capture,
        "break_": brk,
        "trigger": trigger,
    }


def _classify_kernel_clock_source(node_id: str) -> str:
    """Map a clock-tree node ID (e.g. ``clock-node:rcc-apbenr2``,
    ``clock-node:hsi16``) to a ``KernelClockSource`` enum identifier.

    Returns ``"none"`` for unrecognised IDs so the emitter still
    surfaces the option (with the positional field value) without
    crashing.
    """
    nid = node_id.lower()
    if nid.startswith("clock-node:"):
        nid = nid[len("clock-node:") :]
    # Order matters: more specific suffixes first.
    if "lse" in nid:
        return "lse"
    if "lsi" in nid:
        return "lsi"
    if "hsi16" in nid:
        return "hsi16"
    if nid == "hsi" or nid.endswith("-hsi"):
        return "hsi"
    if "hse" in nid:
        return "hse"
    if "sysclk" in nid:
        return "sysclk"
    if "pclk1" in nid or "rcc-apbenr1" in nid or "apb1" in nid:
        return "pclk1"
    if "pclk2" in nid or "rcc-apbenr2" in nid or "apb2" in nid:
        return "pclk2"
    if "pclk" in nid or "rcc-apbenr" in nid:
        return "pclk"
    if "hclk" in nid:
        return "hclk"
    if nid == "xtal" or "xtal" in nid:
        return "xtal"
    if "rc_fast" in nid or "rcfast" in nid:
        return "rc_fast"
    if "ref_tick" in nid or "reftick" in nid:
        return "ref_tick"
    if nid == "apb" or nid.endswith("-apb"):
        return "apb"
    if "peri" in nid:
        return "peri_clk"
    if "clk_per" in nid or nid == "clk_per":
        return "clk_per"
    if "lpuart_clk_root" in nid or "lpuartclk" in nid:
        return "lpuart_clk_root"
    return "none"


def _kernel_clock_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> dict[str, object]:
    """Return the kernel-clock kwargs for a UART/SPI/I2C/QSPI/SDMMC row.

    Walks ``device.peripheral_clock_bindings`` for the named peripheral,
    follows the ``selector_id`` (when present) into ``clock_selectors``
    to pull the parent-options list, and resolves the ``register_field_id``
    on both the selector and the gate to typed ``RuntimeFieldRef``
    records.  Empty options + ``kInvalidFieldRef`` when the IR doesn't
    surface the data (e.g. peripherals on SoCs whose clock-tree
    normalizer hasn't been wired yet).  Added by
    ``add-kernel-clock-traits``.
    """
    device = context.device
    invalid_field = _invalid_field_ref()
    selector_field = invalid_field
    gate_field = invalid_field
    options: tuple[KernelClockSourceOption, ...] = ()

    binding = next(
        (b for b in device.peripheral_clock_bindings if b.peripheral == peripheral_name),
        None,
    )
    if binding is not None:
        # Selector → kKernelClockSourceOptions.
        if binding.selector_id is not None:
            selector = next(
                (s for s in device.clock_selectors if s.selector_id == binding.selector_id),
                None,
            )
            if selector is not None:
                options = tuple(
                    KernelClockSourceOption(
                        source=_classify_kernel_clock_source(opt),
                        field_value=index,
                    )
                    for index, opt in enumerate(selector.parent_options)
                )
                selector_field = _resolve_field_ref_by_id(
                    context, field_id=selector.register_field_id
                )
        # Gate → kClockGateField.
        if binding.clock_gate_id is not None:
            gate = next(
                (g for g in device.clock_gates if g.gate_id == binding.clock_gate_id),
                None,
            )
            if gate is not None:
                gate_field = _resolve_field_ref_by_id(context, field_id=gate.register_field_id)

    return {
        "kernel_clock_selector_field": selector_field,
        "kernel_clock_source_options": options,
        "clock_gate_field": gate_field,
    }


# _resolve_field_ref_by_id moved to runtime_driver/common.py.


# _spi_dma_bindings_for_peripheral → runtime_driver/spi.py


# _adc_dma_bindings_for_peripheral → runtime_driver/adc.py


# _adc_extension_for_peripheral → runtime_driver/adc.py


# _st_adc_row → runtime_driver/adc.py


# _microchip_afec_row → runtime_driver/adc.py


# _nxp_adc_row → runtime_driver/adc.py


# _espressif_saradc_row → runtime_driver/adc.py


# _espressif_esp32_sens_row → runtime_driver/adc.py


# _microchip_avr_adc_row → runtime_driver/adc.py


# _raspberrypi_adc_row → runtime_driver/adc.py


# _build_adc_rows → runtime_driver/adc.py


def _st_timer_counter_bits(peripheral_name: str) -> int:
    return 32 if peripheral_name in {"TIM2", "TIM5"} else 16


def _st_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
    counter_bits = _st_timer_counter_bits(peripheral_name)
    advanced_timer = peripheral_name in {"TIM1", "TIM8"}

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    base = context.peripheral_by_name[peripheral_name].base_address
    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=counter_bits,
        channel_count=4,
        has_compare=True,
        has_capture=True,
        has_encoder=True,
        has_pwm=True,
        has_one_pulse=True,
        has_center_aligned=True,
        has_complementary_outputs=advanced_timer,
        has_deadtime=advanced_timer,
        has_break_input=advanced_timer,
        control_reg=reg("CR1", 0x00),
        status_reg=reg("SR", 0x10),
        event_reg=reg("EGR", 0x14),
        counter_reg=reg("CNT", 0x24),
        prescaler_reg=reg("PSC", 0x28),
        period_reg=reg("ARR", 0x2C),
        enable_field=field("CR1", ("CEN",), 0x00, 0),
        disable_field=_invalid_field_ref(base),
        module_disable_field=_invalid_field_ref(base),
        software_reset_field=_invalid_field_ref(base),
        start_field=_invalid_field_ref(base),
        stop_field=_invalid_field_ref(base),
        update_interrupt_enable_field=field("DIER", ("UIE",), 0x0C, 0),
        update_flag_field=field("SR", ("UIF",), 0x10, 0),
        update_generation_field=field("EGR", ("UG",), 0x14, 0),
        prescaler_field=field("PSC", ("PSC",), 0x28, 0, 16),
        period_field=field("ARR", ("ARR",), 0x2C, 0, counter_bits),
        one_pulse_field=field("CR1", ("OPM",), 0x00, 3),
        center_aligned_field=field("CR1", ("CMS",), 0x00, 5, 2),
        auto_reload_preload_field=field("CR1", ("ARPE",), 0x00, 7),
        clock_source_field=_invalid_field_ref(base),
        encoder_mode_field=field("SMCR", ("SMS",), 0x08, 0, 3),
        encoder_enable_field=_invalid_field_ref(base),
        encoder_position_enable_field=_invalid_field_ref(base),
        encoder_speed_enable_field=_invalid_field_ref(base),
        encoder_phase_edge_field=_invalid_field_ref(base),
        direction_field=field("CR1", ("DIR",), 0x00, 4),
    )


def _st_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
    advanced_timer = peripheral_name in {"TIM1", "TIM8"}
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    rows: list[TimerChannelSemanticRow] = []
    for channel_index in range(4):
        channel_number = channel_index + 1
        mode_register_name = "CCMR1_INPUT" if channel_index < 2 else "CCMR2_INPUT"
        mode_register_offset = 0x18 if channel_index < 2 else 0x1C
        slot_offset = 0 if channel_index % 2 == 0 else 8
        compare_offset = 0x34 + (channel_index * 0x04)
        rows.append(
            TimerChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_compare=True,
                supports_capture=True,
                supports_encoder_input=channel_index < 2,
                supports_pwm=True,
                supports_complementary_output=advanced_timer and channel_index < 3,
                control_reg=reg(mode_register_name, mode_register_offset),
                status_reg=reg("SR", 0x10),
                compare_reg=reg(f"CCR{channel_number}", compare_offset),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg("ARR", 0x2C),
                counter_reg=reg("CNT", 0x24),
                capture_reg=reg(f"CCR{channel_number}", compare_offset),
                enable_field=field("CCER", (f"CC{channel_number}E",), 0x20, channel_index * 4),
                interrupt_enable_field=field(
                    "DIER",
                    (f"CC{channel_number}IE",),
                    0x0C,
                    channel_number,
                ),
                interrupt_flag_field=field(
                    "SR",
                    (f"CC{channel_number}IF",),
                    0x10,
                    channel_number,
                ),
                mode_field=field(
                    mode_register_name,
                    (f"OC{channel_number}M",),
                    mode_register_offset,
                    4 + slot_offset,
                    3,
                ),
                preload_field=field(
                    mode_register_name,
                    (f"OC{channel_number}PE",),
                    mode_register_offset,
                    3 + slot_offset,
                ),
                output_enable_field=field(
                    "CCER",
                    (f"CC{channel_number}E",),
                    0x20,
                    channel_index * 4,
                ),
                output_polarity_field=field(
                    "CCER",
                    (f"CC{channel_number}P",),
                    0x20,
                    1 + (channel_index * 4),
                ),
                complementary_output_enable_field=(
                    field(
                        "CCER",
                        (f"CC{channel_number}NE",),
                        0x20,
                        2 + (channel_index * 4),
                    )
                    if advanced_timer and channel_index < 3
                    else _invalid_field_ref(base)
                ),
                capture_select_field=field(
                    mode_register_name,
                    (f"CC{channel_number}S",),
                    mode_register_offset,
                    slot_offset,
                    2,
                ),
            )
        )
    return tuple(rows)


def _microchip_tc_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=32,
        channel_count=3,
        has_compare=True,
        has_capture=True,
        has_encoder=True,
        has_pwm=True,
        has_one_pulse=False,
        has_center_aligned=False,
        has_complementary_outputs=False,
        has_deadtime=False,
        has_break_input=False,
        control_reg=reg("CCR0", 0x00),
        status_reg=reg("SR0", 0x20),
        event_reg=reg("CCR0", 0x00),
        counter_reg=reg("CV0", 0x10),
        prescaler_reg=_invalid_register_ref(base),
        period_reg=reg("RC0", 0x1C),
        enable_field=field("CCR0", ("CLKEN",), 0x00, 0),
        disable_field=field("CCR0", ("CLKDIS",), 0x00, 1),
        module_disable_field=_invalid_field_ref(base),
        software_reset_field=_invalid_field_ref(base),
        start_field=field("CCR0", ("SWTRG",), 0x00, 2),
        stop_field=field("CCR0", ("CLKDIS",), 0x00, 1),
        update_interrupt_enable_field=field("IER0", ("CPCS",), 0x24, 4),
        update_flag_field=field("SR0", ("CPCS",), 0x20, 4),
        update_generation_field=field("CCR0", ("SWTRG",), 0x00, 2),
        prescaler_field=_invalid_field_ref(base),
        period_field=field("RC0", ("RC",), 0x1C, 0, 32),
        one_pulse_field=_invalid_field_ref(base),
        center_aligned_field=_invalid_field_ref(base),
        auto_reload_preload_field=_invalid_field_ref(base),
        clock_source_field=field("CMR0", ("TCCLKS",), 0x04, 0, 3),
        encoder_mode_field=_invalid_field_ref(base),
        encoder_enable_field=field("BMR", ("QDEN",), 0xC4, 8),
        encoder_position_enable_field=field("BMR", ("POSEN",), 0xC4, 9),
        encoder_speed_enable_field=field("BMR", ("SPEEDEN",), 0xC4, 10),
        encoder_phase_edge_field=field("BMR", ("EDGPHA",), 0xC4, 12),
        direction_field=field("QISR", ("DIR",), 0xD4, 8),
    )


def _microchip_tc_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    rows: list[TimerChannelSemanticRow] = []
    for channel_index in range(3):
        stride = channel_index * 0x40
        register_suffix = str(channel_index)
        rows.append(
            TimerChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_compare=True,
                supports_capture=True,
                supports_encoder_input=False,
                supports_pwm=True,
                supports_complementary_output=False,
                control_reg=reg(f"CCR{register_suffix}", 0x00 + stride),
                status_reg=reg(f"SR{register_suffix}", 0x20 + stride),
                compare_reg=reg(f"RA{register_suffix}", 0x14 + stride),
                secondary_compare_reg=reg(f"RB{register_suffix}", 0x18 + stride),
                period_reg=reg(f"RC{register_suffix}", 0x1C + stride),
                counter_reg=reg(f"CV{register_suffix}", 0x10 + stride),
                capture_reg=reg(f"RA{register_suffix}", 0x14 + stride),
                enable_field=field(f"CCR{register_suffix}", ("CLKEN",), 0x00 + stride, 0),
                interrupt_enable_field=field(
                    f"IER{register_suffix}",
                    ("CPCS",),
                    0x24 + stride,
                    4,
                ),
                interrupt_flag_field=field(
                    f"SR{register_suffix}",
                    ("CPCS",),
                    0x20 + stride,
                    4,
                ),
                mode_field=field(f"CMR{register_suffix}", ("WAVE",), 0x04 + stride, 15),
                preload_field=_invalid_field_ref(base),
                output_enable_field=_invalid_field_ref(base),
                output_polarity_field=_invalid_field_ref(base),
                complementary_output_enable_field=_invalid_field_ref(base),
                capture_select_field=_invalid_field_ref(base),
            )
        )
    return tuple(rows)


def _nxp_gpt_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=32,
        channel_count=1,
        has_compare=True,
        has_capture=True,
        has_encoder=False,
        has_pwm=False,
        has_one_pulse=False,
        has_center_aligned=False,
        has_complementary_outputs=False,
        has_deadtime=False,
        has_break_input=False,
        control_reg=reg("CR", 0x00),
        status_reg=reg("SR", 0x08),
        event_reg=reg("IR", 0x0C),
        counter_reg=reg("CNT", 0x24),
        prescaler_reg=reg("PR", 0x04),
        period_reg=reg("OCR1", 0x10),
        enable_field=field("CR", ("EN",), 0x00, 0),
        disable_field=_invalid_field_ref(base),
        module_disable_field=_invalid_field_ref(base),
        software_reset_field=field("CR", ("SWR",), 0x00, 15),
        start_field=_invalid_field_ref(base),
        stop_field=_invalid_field_ref(base),
        update_interrupt_enable_field=field("IR", ("OF1IE",), 0x0C, 0),
        update_flag_field=field("SR", ("OF1",), 0x08, 0),
        update_generation_field=_invalid_field_ref(base),
        prescaler_field=field("PR", ("PRESCALER",), 0x04, 0, 12),
        period_field=field("OCR1", ("OCR1",), 0x10, 0, 32),
        one_pulse_field=_invalid_field_ref(base),
        center_aligned_field=_invalid_field_ref(base),
        auto_reload_preload_field=_invalid_field_ref(base),
        clock_source_field=field("CR", ("CLKSRC",), 0x00, 6, 3),
        encoder_mode_field=_invalid_field_ref(base),
        encoder_enable_field=_invalid_field_ref(base),
        encoder_position_enable_field=_invalid_field_ref(base),
        encoder_speed_enable_field=_invalid_field_ref(base),
        encoder_phase_edge_field=_invalid_field_ref(base),
        direction_field=_invalid_field_ref(base),
    )


def _nxp_gpt_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return (
        TimerChannelSemanticRow(
            peripheral_name=peripheral_name,
            channel_index=0,
            supports_compare=True,
            supports_capture=True,
            supports_encoder_input=False,
            supports_pwm=False,
            supports_complementary_output=False,
            control_reg=reg("CR", 0x00),
            status_reg=reg("SR", 0x08),
            compare_reg=reg("OCR1", 0x10),
            secondary_compare_reg=_invalid_register_ref(base),
            period_reg=reg("OCR1", 0x10),
            counter_reg=reg("CNT", 0x24),
            capture_reg=reg("ICR1", 0x1C),
            enable_field=field("CR", ("EN",), 0x00, 0),
            interrupt_enable_field=field("IR", ("OF1IE",), 0x0C, 0),
            interrupt_flag_field=field("SR", ("OF1",), 0x08, 0),
            mode_field=_invalid_field_ref(base),
            preload_field=_invalid_field_ref(base),
            output_enable_field=_invalid_field_ref(base),
            output_polarity_field=_invalid_field_ref(base),
            complementary_output_enable_field=_invalid_field_ref(base),
            capture_select_field=_invalid_field_ref(base),
        ),
    )


def _nxp_pit_timer_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> TimerSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return TimerSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=32,
        channel_count=4,
        has_compare=False,
        has_capture=False,
        has_encoder=False,
        has_pwm=False,
        has_one_pulse=False,
        has_center_aligned=False,
        has_complementary_outputs=False,
        has_deadtime=False,
        has_break_input=False,
        control_reg=reg("TCTRL0", 0x108),
        status_reg=reg("TFLG0", 0x10C),
        event_reg=_invalid_register_ref(base),
        counter_reg=reg("CVAL0", 0x104),
        prescaler_reg=_invalid_register_ref(base),
        period_reg=reg("LDVAL0", 0x100),
        enable_field=field("TCTRL0", ("TEN",), 0x108, 0),
        disable_field=_invalid_field_ref(base),
        module_disable_field=field("MCR", ("MDIS",), 0x00, 1),
        software_reset_field=_invalid_field_ref(base),
        start_field=_invalid_field_ref(base),
        stop_field=_invalid_field_ref(base),
        update_interrupt_enable_field=field("TCTRL0", ("TIE",), 0x108, 1),
        update_flag_field=field("TFLG0", ("TIF",), 0x10C, 0),
        update_generation_field=_invalid_field_ref(base),
        prescaler_field=_invalid_field_ref(base),
        period_field=field("LDVAL0", ("TSV", "LDVAL"), 0x100, 0, 32),
        one_pulse_field=_invalid_field_ref(base),
        center_aligned_field=_invalid_field_ref(base),
        auto_reload_preload_field=_invalid_field_ref(base),
        clock_source_field=_invalid_field_ref(base),
        encoder_mode_field=_invalid_field_ref(base),
        encoder_enable_field=_invalid_field_ref(base),
        encoder_position_enable_field=_invalid_field_ref(base),
        encoder_speed_enable_field=_invalid_field_ref(base),
        encoder_phase_edge_field=_invalid_field_ref(base),
        direction_field=_invalid_field_ref(base),
    )


def _nxp_pit_timer_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[TimerChannelSemanticRow, ...]:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    rows: list[TimerChannelSemanticRow] = []
    for channel_index in range(4):
        base_offset = 0x100 + (channel_index * 0x10)
        rows.append(
            TimerChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_compare=False,
                supports_capture=False,
                supports_encoder_input=False,
                supports_pwm=False,
                supports_complementary_output=False,
                control_reg=reg(f"TCTRL{channel_index}", base_offset + 0x08),
                status_reg=reg(f"TFLG{channel_index}", base_offset + 0x0C),
                compare_reg=reg(f"LDVAL{channel_index}", base_offset + 0x00),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg(f"LDVAL{channel_index}", base_offset + 0x00),
                counter_reg=reg(f"CVAL{channel_index}", base_offset + 0x04),
                capture_reg=_invalid_register_ref(base),
                enable_field=field(
                    f"TCTRL{channel_index}",
                    ("TEN",),
                    base_offset + 0x08,
                    0,
                ),
                interrupt_enable_field=field(
                    f"TCTRL{channel_index}",
                    ("TIE",),
                    base_offset + 0x08,
                    1,
                ),
                interrupt_flag_field=field(
                    f"TFLG{channel_index}",
                    ("TIF",),
                    base_offset + 0x0C,
                    0,
                ),
                mode_field=_invalid_field_ref(base),
                preload_field=_invalid_field_ref(base),
                output_enable_field=_invalid_field_ref(base),
                output_polarity_field=_invalid_field_ref(base),
                complementary_output_enable_field=_invalid_field_ref(base),
                capture_select_field=_invalid_field_ref(base),
            )
        )
    return tuple(rows)


def _build_timer_rows(
    context: _SemanticContext,
) -> tuple[tuple[TimerSemanticRow, ...], tuple[TimerChannelSemanticRow, ...]]:
    timer_rows: list[TimerSemanticRow] = []
    channel_rows: list[TimerChannelSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("timer", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.timer.st-"):
            timer_rows.append(
                _st_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_st_timer_channel_rows(context, peripheral_name=peripheral.name))
        elif schema_id == "alloy.timer.microchip-tc-zl":
            timer_rows.append(
                _microchip_tc_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _microchip_tc_timer_channel_rows(
                    context,
                    peripheral_name=peripheral.name,
                )
            )
        elif schema_id == "alloy.gpt.nxp-gpt":
            timer_rows.append(
                _nxp_gpt_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _nxp_gpt_timer_channel_rows(context, peripheral_name=peripheral.name)
            )
        elif schema_id == "alloy.pit.nxp-pit":
            timer_rows.append(
                _nxp_pit_timer_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _nxp_pit_timer_channel_rows(context, peripheral_name=peripheral.name)
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (TimerSemanticTraits<PeripheralId::) is satisfied for devices whose
            # Timer IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            timer_rows.append(
                TimerSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    counter_bits=0,
                    channel_count=0,
                    has_compare=False,
                    has_capture=False,
                    has_encoder=False,
                    has_pwm=False,
                    has_one_pulse=False,
                    has_center_aligned=False,
                    has_complementary_outputs=False,
                    has_deadtime=False,
                    has_break_input=False,
                    control_reg=invalid_reg,
                    status_reg=invalid_reg,
                    event_reg=invalid_reg,
                    counter_reg=invalid_reg,
                    prescaler_reg=invalid_reg,
                    period_reg=invalid_reg,
                    enable_field=invalid_field,
                    disable_field=invalid_field,
                    module_disable_field=invalid_field,
                    software_reset_field=invalid_field,
                    start_field=invalid_field,
                    stop_field=invalid_field,
                    update_interrupt_enable_field=invalid_field,
                    update_flag_field=invalid_field,
                    update_generation_field=invalid_field,
                    prescaler_field=invalid_field,
                    period_field=invalid_field,
                    one_pulse_field=invalid_field,
                    center_aligned_field=invalid_field,
                    auto_reload_preload_field=invalid_field,
                    clock_source_field=invalid_field,
                    encoder_mode_field=invalid_field,
                    encoder_enable_field=invalid_field,
                    encoder_position_enable_field=invalid_field,
                    encoder_speed_enable_field=invalid_field,
                    encoder_phase_edge_field=invalid_field,
                    direction_field=invalid_field,
                    is_stub=True,
                )
            )
            # Add a single stub channel row so the artifact contract check for
            # TimerChannelSemanticTraits<PeripheralId:: is satisfied.
            channel_rows.append(
                TimerChannelSemanticRow(
                    peripheral_name=peripheral.name,
                    channel_index=0,
                    supports_compare=False,
                    supports_capture=False,
                    supports_encoder_input=False,
                    supports_pwm=False,
                    supports_complementary_output=False,
                    control_reg=invalid_reg,
                    status_reg=invalid_reg,
                    compare_reg=invalid_reg,
                    secondary_compare_reg=invalid_reg,
                    period_reg=invalid_reg,
                    counter_reg=invalid_reg,
                    capture_reg=invalid_reg,
                    enable_field=invalid_field,
                    interrupt_enable_field=invalid_field,
                    interrupt_flag_field=invalid_field,
                    mode_field=invalid_field,
                    preload_field=invalid_field,
                    output_enable_field=invalid_field,
                    output_polarity_field=invalid_field,
                    complementary_output_enable_field=invalid_field,
                    capture_select_field=invalid_field,
                )
            )
    enriched_timer_rows = _enrich_with_dma_bindings(
        context, tuple(timer_rows), transfer_width_bits=16
    )
    enriched_timer_rows = _enrich_timer_tier234(context, enriched_timer_rows)
    return tuple(enriched_timer_rows), tuple(channel_rows)  # type: ignore[return-value]


def _enrich_timer_tier234(
    context: _SemanticContext,
    rows: tuple[object, ...],
) -> tuple[object, ...]:
    """add-timer-tier-2-3-4-data: thread Tier 2/3/4 facts onto each
    timer row from the device patch's `timer_*` tuples."""
    import dataclasses as _dc

    device = context.device
    prescalers = {
        getattr(p, "peripheral", ""): p for p in getattr(device, "timer_prescaler_options", ())
    }
    flags = {getattr(f, "peripheral", ""): f for f in getattr(device, "timer_mode_flags", ())}
    triggers: dict[str, list[tuple[str, int]]] = {}
    for t in getattr(device, "timer_trigger_sources", ()):
        triggers.setdefault(getattr(t, "peripheral", ""), []).append(
            (getattr(t, "source", ""), int(getattr(t, "field_value", 0)))
        )
    masters: dict[str, list[tuple[str, int]]] = {}
    for m in getattr(device, "timer_master_outputs", ()):
        masters.setdefault(getattr(m, "peripheral", ""), []).append(
            (getattr(m, "source", ""), int(getattr(m, "field_value", 0)))
        )
    enriched: list[object] = []
    for row in rows:
        peripheral = getattr(row, "peripheral_name", None)
        if peripheral is None:
            enriched.append(row)
            continue
        psc = prescalers.get(peripheral)
        flg = flags.get(peripheral)
        kw: dict[str, object] = {}
        if psc is not None:
            kw["max_prescaler"] = int(getattr(psc, "max_prescaler", 0))
            ar = int(getattr(psc, "max_auto_reload", 0))
            kw["max_auto_reload"] = ar if ar else int(getattr(psc, "max_prescaler", 0))
        if flg is not None:
            kw["supports_dma_burst"] = bool(getattr(flg, "supports_dma_burst", False))
            kw["supports_repetition_counter"] = bool(
                getattr(flg, "supports_repetition_counter", False)
            )
            kw["supports_xor_input"] = bool(getattr(flg, "supports_xor_input", False))
        if peripheral in triggers:
            kw["trigger_sources"] = tuple(triggers[peripheral])
        if peripheral in masters:
            kw["master_outputs"] = tuple(masters[peripheral])
        if not kw:
            enriched.append(row)
            continue
        enriched.append(_dc.replace(row, **kw))
    return tuple(enriched)


def _st_pwm_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> PwmSemanticRow:
    advanced_timer = peripheral_name in {"TIM1", "TIM8"}
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return PwmSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=_st_timer_counter_bits(peripheral_name),
        channel_count=4,
        has_complementary_outputs=advanced_timer,
        has_deadtime=advanced_timer,
        has_fault_input=advanced_timer,
        has_center_aligned=True,
        has_synchronized_update=True,
        control_reg=reg("CR1", 0x00),
        output_enable_reg=reg("CCER", 0x20),
        status_reg=reg("SR", 0x10),
        clock_reg=reg("PSC", 0x28),
        sync_reg=reg("EGR", 0x14),
        master_output_enable_field=(
            field("BDTR", ("MOE",), 0x44, 15) if advanced_timer else _invalid_field_ref(base)
        ),
        load_field=field("EGR", ("UG",), 0x14, 0),
        clear_load_field=_invalid_field_ref(base),
        clock_prescaler_field=field("PSC", ("PSC",), 0x28, 0, 16),
    )


def _st_pwm_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[PwmChannelSemanticRow, ...]:
    advanced_timer = peripheral_name in {"TIM1", "TIM8"}
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    rows: list[PwmChannelSemanticRow] = []
    for channel_index in range(4):
        channel_number = channel_index + 1
        mode_register_name = "CCMR1_INPUT" if channel_index < 2 else "CCMR2_INPUT"
        mode_register_offset = 0x18 if channel_index < 2 else 0x1C
        slot_offset = 0 if channel_index % 2 == 0 else 8
        compare_offset = 0x34 + (channel_index * 0x04)
        rows.append(
            PwmChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_complementary_output=advanced_timer and channel_index < 3,
                supports_deadtime=advanced_timer,
                control_reg=reg(mode_register_name, mode_register_offset),
                compare_reg=reg(f"CCR{channel_number}", compare_offset),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg("ARR", 0x2C),
                deadtime_reg=reg("BDTR", 0x44) if advanced_timer else _invalid_register_ref(base),
                enable_field=field("CCER", (f"CC{channel_number}E",), 0x20, channel_index * 4),
                interrupt_enable_field=field(
                    "DIER",
                    (f"CC{channel_number}IE",),
                    0x0C,
                    channel_number,
                ),
                interrupt_flag_field=field(
                    "SR",
                    (f"CC{channel_number}IF",),
                    0x10,
                    channel_number,
                ),
                mode_field=field(
                    mode_register_name,
                    (f"OC{channel_number}M",),
                    mode_register_offset,
                    4 + slot_offset,
                    3,
                ),
                polarity_field=field(
                    "CCER",
                    (f"CC{channel_number}P",),
                    0x20,
                    1 + (channel_index * 4),
                ),
                complementary_output_enable_field=(
                    field(
                        "CCER",
                        (f"CC{channel_number}NE",),
                        0x20,
                        2 + (channel_index * 4),
                    )
                    if advanced_timer and channel_index < 3
                    else _invalid_field_ref(base)
                ),
                center_aligned_field=field("CR1", ("CMS",), 0x00, 5, 2),
                period_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="ARR",
                    register_offset=0x2C,
                    bit_offset=0,
                    bit_width=_st_timer_counter_bits(peripheral_name),
                ),
                duty_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"CCR{channel_number}",
                    register_offset=compare_offset,
                    bit_offset=0,
                    bit_width=_st_timer_counter_bits(peripheral_name),
                ),
                deadtime_rise_field=(
                    field("BDTR", ("DTG",), 0x44, 0, 8)
                    if advanced_timer
                    else _invalid_field_ref(base)
                ),
                deadtime_fall_field=(
                    field("BDTR", ("DTG",), 0x44, 0, 8)
                    if advanced_timer
                    else _invalid_field_ref(base)
                ),
            )
        )
    return tuple(rows)


def _microchip_pwm_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> PwmSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return PwmSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=24,
        channel_count=4,
        has_complementary_outputs=True,
        has_deadtime=True,
        has_fault_input=True,
        has_center_aligned=True,
        has_synchronized_update=True,
        control_reg=reg("CLK", 0x00),
        output_enable_reg=reg("ENA", 0x04),
        status_reg=reg("SR", 0x0C),
        clock_reg=reg("CLK", 0x00),
        sync_reg=reg("SCUC", 0x28),
        master_output_enable_field=_invalid_field_ref(base),
        load_field=field("SCUC", ("UPDULOCK",), 0x28, 0),
        clear_load_field=_invalid_field_ref(base),
        clock_prescaler_field=field("CLK", ("PREA",), 0x00, 8, 4),
    )


def _microchip_pwm_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[PwmChannelSemanticRow, ...]:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    rows: list[PwmChannelSemanticRow] = []
    for channel_index in range(4):
        stride = channel_index * 0x20
        rows.append(
            PwmChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_complementary_output=True,
                supports_deadtime=True,
                control_reg=reg(f"CMR{channel_index}", 0x200 + stride),
                compare_reg=reg(f"CDTY{channel_index}", 0x204 + stride),
                secondary_compare_reg=_invalid_register_ref(base),
                period_reg=reg(f"CPRD{channel_index}", 0x20C + stride),
                deadtime_reg=reg(f"DT{channel_index}", 0x218 + stride),
                enable_field=field("ENA", (f"CHID{channel_index}",), 0x04, channel_index),
                interrupt_enable_field=field(
                    "IER1",
                    (f"CHID{channel_index}",),
                    0x10,
                    channel_index,
                ),
                interrupt_flag_field=field(
                    "ISR1",
                    (f"CHID{channel_index}",),
                    0x1C,
                    channel_index,
                ),
                mode_field=field(
                    f"CMR{channel_index}",
                    ("CPRE",),
                    0x200 + stride,
                    0,
                    4,
                ),
                polarity_field=field(
                    f"CMR{channel_index}",
                    ("CPOL",),
                    0x200 + stride,
                    9,
                ),
                complementary_output_enable_field=_invalid_field_ref(base),
                center_aligned_field=field(
                    f"CMR{channel_index}",
                    ("CALG",),
                    0x200 + stride,
                    8,
                ),
                period_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"CPRD{channel_index}",
                    register_offset=0x20C + stride,
                    bit_offset=0,
                    bit_width=24,
                ),
                duty_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"CDTY{channel_index}",
                    register_offset=0x204 + stride,
                    bit_offset=0,
                    bit_width=24,
                ),
                deadtime_rise_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"DT{channel_index}",
                    register_offset=0x218 + stride,
                    bit_offset=16,
                    bit_width=16,
                ),
                deadtime_fall_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"DT{channel_index}",
                    register_offset=0x218 + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
            )
        )
    return tuple(rows)


def _nxp_pwm_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> PwmSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    def field(
        register_name: str,
        field_names: tuple[str, ...],
        register_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=field_names,
            fallback_register_offset=register_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    return PwmSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        counter_bits=16,
        channel_count=4,
        has_complementary_outputs=True,
        has_deadtime=True,
        has_fault_input=True,
        has_center_aligned=True,
        has_synchronized_update=True,
        control_reg=reg("MCTRL", 0x188),
        output_enable_reg=reg("OUTEN", 0x180),
        status_reg=reg("FSTS0", 0x18E),
        clock_reg=_invalid_register_ref(base),
        sync_reg=reg("MCTRL", 0x188),
        master_output_enable_field=_invalid_field_ref(base),
        load_field=field("MCTRL", ("LDOK",), 0x188, 0, 4),
        clear_load_field=field("MCTRL", ("CLDOK",), 0x188, 4, 4),
        clock_prescaler_field=_invalid_field_ref(base),
    )


def _nxp_pwm_channel_rows(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> tuple[PwmChannelSemanticRow, ...]:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=name,
            fallback_offset=offset,
        )

    rows: list[PwmChannelSemanticRow] = []
    for channel_index in range(4):
        stride = channel_index * 0x60
        rows.append(
            PwmChannelSemanticRow(
                peripheral_name=peripheral_name,
                channel_index=channel_index,
                supports_complementary_output=True,
                supports_deadtime=True,
                control_reg=reg(f"SM{channel_index}CTRL", 0x06 + stride),
                compare_reg=reg(f"SM{channel_index}VAL2", 0x10 + stride),
                secondary_compare_reg=reg(f"SM{channel_index}VAL3", 0x12 + stride),
                period_reg=reg(f"SM{channel_index}VAL1", 0x0C + stride),
                deadtime_reg=reg(f"SM{channel_index}DTCNT0", 0x28 + stride),
                enable_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="OUTEN",
                    register_offset=0x180,
                    bit_offset=8 + channel_index,
                ),
                interrupt_enable_field=_invalid_field_ref(base),
                interrupt_flag_field=_invalid_field_ref(base),
                mode_field=_invalid_field_ref(base),
                polarity_field=_invalid_field_ref(base),
                complementary_output_enable_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name="OUTEN",
                    register_offset=0x180,
                    bit_offset=4 + channel_index,
                ),
                center_aligned_field=_invalid_field_ref(base),
                period_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}VAL1",
                    register_offset=0x0C + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
                duty_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}VAL2",
                    register_offset=0x10 + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
                deadtime_rise_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}DTCNT0",
                    register_offset=0x28 + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
                deadtime_fall_field=_manual_field_ref(
                    context,
                    peripheral_name=peripheral_name,
                    register_name=f"SM{channel_index}DTCNT1",
                    register_offset=0x2A + stride,
                    bit_offset=0,
                    bit_width=16,
                ),
            )
        )
    return tuple(rows)


def _build_pwm_rows(
    context: _SemanticContext,
) -> tuple[tuple[PwmSemanticRow, ...], tuple[PwmChannelSemanticRow, ...]]:
    pwm_rows: list[PwmSemanticRow] = []
    channel_rows: list[PwmChannelSemanticRow] = []
    timer_candidates = context.runtime_peripherals_by_class.get("timer", ())
    dedicated_pwm_candidates = context.runtime_peripherals_by_class.get("pwm", ())

    for peripheral in timer_candidates:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.timer.st-"):
            pwm_rows.append(
                _st_pwm_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_st_pwm_channel_rows(context, peripheral_name=peripheral.name))
        # Non-ST timers (NXP GPT, RP2040 TIMER, etc.) are handled in their own
        # timer builder and should NOT emit PWM rows here.

    for peripheral in dedicated_pwm_candidates:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id == "alloy.pwm.microchip-pwm-y":
            pwm_rows.append(
                _microchip_pwm_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(
                _microchip_pwm_channel_rows(context, peripheral_name=peripheral.name)
            )
        elif schema_id == "alloy.pwm.nxp-pwm":
            pwm_rows.append(
                _nxp_pwm_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
            channel_rows.extend(_nxp_pwm_channel_rows(context, peripheral_name=peripheral.name))
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (PwmSemanticTraits<PeripheralId::) is satisfied for devices whose
            # dedicated PWM IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            pwm_rows.append(
                PwmSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    counter_bits=0,
                    channel_count=0,
                    has_complementary_outputs=False,
                    has_deadtime=False,
                    has_fault_input=False,
                    has_center_aligned=False,
                    has_synchronized_update=False,
                    control_reg=invalid_reg,
                    output_enable_reg=invalid_reg,
                    status_reg=invalid_reg,
                    clock_reg=invalid_reg,
                    sync_reg=invalid_reg,
                    master_output_enable_field=invalid_field,
                    load_field=invalid_field,
                    clear_load_field=invalid_field,
                    clock_prescaler_field=invalid_field,
                    is_stub=True,
                )
            )
            # Add a single stub channel row so the artifact contract check for
            # PwmChannelSemanticTraits<PeripheralId:: is satisfied.
            channel_rows.append(
                PwmChannelSemanticRow(
                    peripheral_name=peripheral.name,
                    channel_index=0,
                    supports_complementary_output=False,
                    supports_deadtime=False,
                    control_reg=invalid_reg,
                    compare_reg=invalid_reg,
                    secondary_compare_reg=invalid_reg,
                    period_reg=invalid_reg,
                    deadtime_reg=invalid_reg,
                    enable_field=invalid_field,
                    interrupt_enable_field=invalid_field,
                    interrupt_flag_field=invalid_field,
                    mode_field=invalid_field,
                    polarity_field=invalid_field,
                    complementary_output_enable_field=invalid_field,
                    center_aligned_field=invalid_field,
                    period_field=invalid_field,
                    duty_field=invalid_field,
                    deadtime_rise_field=invalid_field,
                    deadtime_fall_field=invalid_field,
                )
            )
    enriched_pwm_rows = _enrich_pwm_tier234(context, tuple(pwm_rows))
    return tuple(enriched_pwm_rows), tuple(channel_rows)  # type: ignore[return-value]


def _enrich_pwm_tier234(
    context: _SemanticContext,
    rows: tuple[object, ...],
) -> tuple[object, ...]:
    """add-pwm-tier-2-3-4-data: thread Tier 2/3/4 facts onto each PWM
    row from the device patch's `pwm_*` tuples + the matching
    `timer_prescaler_options` (PWM uses the same PSC range as its
    backing timer)."""
    import dataclasses as _dc

    device = context.device
    flags_by_peripheral = {
        getattr(p, "peripheral", ""): p for p in getattr(device, "pwm_mode_flags", ())
    }
    deadtime_by_peripheral: dict[str, list[tuple[int, int, int]]] = {}
    for d in getattr(device, "pwm_deadtime_options", ()):
        deadtime_by_peripheral.setdefault(getattr(d, "peripheral", ""), []).append(
            (
                int(getattr(d, "prescaler_field_value", 0)),
                int(getattr(d, "count_bits", 8)),
                int(getattr(d, "max_ns", 0)),
            )
        )
    alignments_by_peripheral: dict[str, list[tuple[str, int]]] = {}
    for a in getattr(device, "pwm_alignment_options", ()):
        alignments_by_peripheral.setdefault(getattr(a, "peripheral", ""), []).append(
            (getattr(a, "alignment", ""), int(getattr(a, "field_value", 0)))
        )
    breaks_by_peripheral: dict[str, list[tuple[str, int, int]]] = {}
    for b in getattr(device, "pwm_break_inputs", ()):
        breaks_by_peripheral.setdefault(getattr(b, "peripheral", ""), []).append(
            (
                getattr(b, "input_id", ""),
                int(getattr(b, "polarity_field_value", 0)),
                int(getattr(b, "enable_field_value", 1)),
            )
        )
    psc_by_peripheral = {
        getattr(p, "peripheral", ""): p for p in getattr(device, "timer_prescaler_options", ())
    }
    enriched: list[object] = []
    for row in rows:
        peripheral = getattr(row, "peripheral_name", None)
        if peripheral is None:
            enriched.append(row)
            continue
        kw: dict[str, object] = {}
        psc = psc_by_peripheral.get(peripheral)
        if psc is not None:
            kw["max_prescaler"] = int(getattr(psc, "max_prescaler", 0))
            ar = int(getattr(psc, "max_auto_reload", 0))
            kw["max_period"] = ar if ar else int(getattr(psc, "max_prescaler", 0))
        if peripheral in deadtime_by_peripheral:
            kw["deadtime_options"] = tuple(deadtime_by_peripheral[peripheral])
        if peripheral in alignments_by_peripheral:
            kw["supported_alignments"] = tuple(alignments_by_peripheral[peripheral])
        if peripheral in breaks_by_peripheral:
            kw["break_inputs"] = tuple(breaks_by_peripheral[peripheral])
        flg = flags_by_peripheral.get(peripheral)
        if flg is not None:
            kw["supports_deadtime"] = bool(getattr(flg, "supports_deadtime", False))
            kw["supports_break_input"] = bool(getattr(flg, "supports_break_input", False))
            kw["supports_complementary_outputs"] = bool(
                getattr(flg, "supports_complementary_outputs", False)
            )
            kw["supports_asymmetric_pwm"] = bool(getattr(flg, "supports_asymmetric_pwm", False))
            kw["supports_combined_pwm"] = bool(getattr(flg, "supports_combined_pwm", False))
        if not kw:
            enriched.append(row)
            continue
        enriched.append(_dc.replace(row, **kw))
    return tuple(enriched)


def _emit_driver_semantics_common_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    body = "\n".join(
        [
            "struct RuntimeRegisterRef {",
            "  RegisterId register_id = RegisterId::none;",
            "  std::uintptr_t base_address = 0u;",
            "  std::uint32_t offset_bytes = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct RuntimeFieldRef {",
            "  FieldId field_id = FieldId::none;",
            "  RuntimeRegisterRef reg{};",
            "  std::uint16_t bit_offset = 0u;",
            "  std::uint16_t bit_width = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct RuntimeIndexedFieldRef {",
            "  std::uintptr_t base_address = 0u;",
            "  std::uint32_t base_offset_bytes = 0u;",
            "  std::uint32_t stride_bytes = 0u;",
            "  std::uint16_t bit_offset = 0u;",
            "  std::uint16_t bit_width = 0u;",
            "  std::uint16_t bit_stride_bits = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "inline constexpr RuntimeRegisterRef kInvalidRegisterRef{};",
            "inline constexpr RuntimeFieldRef kInvalidFieldRef{};",
            "inline constexpr RuntimeIndexedFieldRef kInvalidIndexedFieldRef{};",
            "",
            "// ADC trait support types (added by add-full-adc-coverage).",
            "// Apps consuming the runtime use these to generate high-level helpers",
            "// like readTemperature() / readVdd() with full compile-time validation.",
            "enum class InternalAdcChannelKind : std::uint8_t {",
            "  none,",
            "  temperature_sensor,",
            "  vrefint,",
            "  vbat,",
            "  opamp_output,",
            "  dac_output,",
            "};",
            "",
            "enum class AdcCalibrationKind : std::uint8_t {",
            "  none,",
            "  vrefint_cal,",
            "  ts_cal_low,",
            "  ts_cal_high,",
            "  sigrow_sref,",
            "  sigrow_tempsense_low,",
            "  sigrow_tempsense_high,",
            "  efuse_init_code,",
            "};",
            "",
            "enum class AdcExternalTriggerSource : std::uint8_t {",
            "  none,",
            "  software,",
            "  tim1_cc1,",
            "  tim1_cc2,",
            "  tim1_cc3,",
            "  tim1_cc4,",
            "  tim1_trgo,",
            "  tim1_trgo2,",
            "  tim2_trgo,",
            "  tim3_trgo,",
            "  tim4_trgo,",
            "  tim6_trgo,",
            "  tim7_trgo,",
            "  tim15_trgo,",
            "  tim16_trgo,",
            "  exti11,",
            "  exti15,",
            "  gpt1_compare1,",
            "  gpt2_compare1,",
            "  xbar_in0,",
            "  xbar_in1,",
            "  pwm0_compare,",
            "  pwm1_compare,",
            "};",
            "",
            "enum class AdcDmaMode : std::uint8_t {",
            "  none,",
            "  one_shot,",
            "  circular,",
            "};",
            "",
            "struct InternalAdcChannel {",
            "  InternalAdcChannelKind kind = InternalAdcChannelKind::none;",
            "  std::uint32_t channel_index = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct CalibrationDataPoint {",
            "  AdcCalibrationKind kind = AdcCalibrationKind::none;",
            "  RuntimeRegisterRef location{};",
            "  std::int32_t semantic_constant = 0;",
            "  bool valid = false;",
            "};",
            "",
            "struct CalibrationContext {",
            "  std::int16_t cal_temp_low_celsius = 0;",
            "  std::int16_t cal_temp_high_celsius = 0;",
            "  std::uint16_t cal_voltage_mv = 0u;",
            "  std::uint16_t vrefint_nominal_mv = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcResolutionOption {",
            "  std::uint8_t bits = 0u;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcSampleTimeOption {",
            "  // ``cycles_q8`` carries the cycle count in Q8.8 fixed-point so",
            "  // fractional cycles (1.5, 7.5, ...) survive without floats.  Apps",
            "  // do ``cycles_q8 / 256.0f`` to recover a float, or compare integers.",
            "  // 32-bit holds up to 16.7M cycles which covers every documented",
            "  // ADC sample time across admitted vendors (STM32F4 ADC sample 480",
            "  // cycles → 122880 in Q8.8 fixed-point — exceeds uint16_t).",
            "  std::uint32_t cycles_q8 = 0u;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcOversamplingOption {",
            "  std::uint16_t ratio = 0u;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcExternalTrigger {",
            "  AdcExternalTriggerSource source = AdcExternalTriggerSource::none;",
            "  std::uint8_t extsel_value = 0u;",
            "  std::uint8_t exten_polarity_default = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcDmaBinding {",
            "  // Source ADC peripheral name + DMA controller / route descriptor.",
            "  // ``data_register`` mirrors the ADC trait's kDataRegister so DMA",
            "  // configuration code can pull the source address without a second",
            "  // lookup.  ``binding_id`` cross-references the existing",
            "  // ``DmaSemanticTraits`` table when the consumer wants the full",
            "  // DMA route/channel descriptor.",
            "  PeripheralId controller_peripheral = PeripheralId::none;",
            "  DmaControllerId controller_id = DmaControllerId::none;",
            "  DmaBindingId binding_id = DmaBindingId::none;",
            "  std::uint8_t request_value = 0u;",
            "  RuntimeRegisterRef data_register{};",
            "  std::uint8_t transfer_width_bits = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "enum class DmaBindingDirection : std::uint8_t {",
            "  none,",
            "  Tx,",
            "  Rx,",
            "};",
            "",
            "struct DmaBindingRef {",
            "  // Generic peripheral->DMA binding cross-reference (",
            "  // add-peripheral-dma-cross-references).  ``binding_id``",
            "  // and ``controller_id`` cross-reference the per-device",
            "  // ``DmaSemanticTraits`` / ``BindingTraits`` enums emitted",
            "  // in ``dma_bindings.hpp`` so consumer code can resolve the",
            "  // full route descriptor without a textual scan.",
            "  DmaControllerId controller_id = DmaControllerId::none;",
            "  DmaBindingId binding_id = DmaBindingId::none;",
            "  std::uint16_t request_value = 0u;",
            "  DmaBindingDirection direction = DmaBindingDirection::none;",
            "  std::uint8_t transfer_width_bits = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "struct AdcDmaModeOption {",
            "  AdcDmaMode mode = AdcDmaMode::none;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "// Kernel-clock source classifier (added by add-kernel-clock-traits).",
            "// Maps RCC mux parent-options onto a small enum so HAL drivers can",
            "// resolve the actual feeding clock (PCLK1, SYSCLK, HSI16, ...) from",
            "// system_clock_profiles at compile time.",
            "enum class KernelClockSource : std::uint8_t {",
            "  none,",
            "  pclk,",
            "  pclk1,",
            "  pclk2,",
            "  hclk,",
            "  sysclk,",
            "  hsi,",
            "  hsi16,",
            "  hse,",
            "  lsi,",
            "  lse,",
            "  xtal,",
            "  apb,",
            "  peri_clk,",
            "  clk_per,",
            "  lpuart_clk_root,",
            "  rc_fast,",
            "  ref_tick,",
            "};",
            "",
            "struct KernelClockSourceOption {",
            "  KernelClockSource source = KernelClockSource::none;",
            "  std::uint8_t field_value = 0u;",
            "  bool valid = false;",
            "};",
            "",
            "// I2C trait support type (added by add-i2c-tier-2-3-4-data).",
            "// Precomputed TIMINGR / CWGR value for one (peripheral, source",
            "// clock, target speed) triple — lets the alloy HAL pick the right",
            "// register value at compile time without a runtime calculator.",
            "struct I2cTimingPreset {",
            "  std::uint32_t speed_hz = 0u;",
            "  std::uint32_t source_clock_hz = 0u;",
            "  std::uint32_t timingr_value = 0u;",
            "  bool valid = false;",
            "};",
        ]
    )
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <cstdint>",
            '#include "../peripheral_instances.hpp"',
            '#include "../registers.hpp"',
            '#include "../register_fields.hpp"',
            '#include "../dma_bindings.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            COMMON_DRIVER_HEADER,
        ),
        content=content,
    )


# _emit_gpio_semantics_header → runtime_driver/gpio.py


# _uart_specialization_builder → runtime_driver/uart.py


# _adc_specialization_builder → runtime_driver/adc.py


def _timer_specialization_builder(context: _SemanticContext):
    def _build(row: TimerSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr std::uint32_t kCounterBits = 0u;",
                "  static constexpr std::uint32_t kChannelCount = 0u;",
                "  static constexpr bool kHasCompare = false;",
                "  static constexpr bool kHasCapture = false;",
                "  static constexpr bool kHasEncoder = false;",
                "  static constexpr bool kHasPwm = false;",
                "  static constexpr bool kHasOnePulse = false;",
                "  static constexpr bool kHasCenterAligned = false;",
                "  static constexpr bool kHasComplementaryOutputs = false;",
                "  static constexpr bool kHasDeadtime = false;",
                "  static constexpr bool kHasBreakInput = false;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateFlagField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClockSourceField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderModeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
                *_timer_irq_lines(row),
                *_timer_tier234_lines(row),
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kStatusRegister": row.status_reg,
            "kEventRegister": row.event_reg,
            "kCounterRegister": row.counter_reg,
            "kPrescalerRegister": row.prescaler_reg,
            "kPeriodRegister": row.period_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kModuleDisableField": row.module_disable_field,
            "kSoftwareResetField": row.software_reset_field,
            "kStartField": row.start_field,
            "kStopField": row.stop_field,
            "kUpdateInterruptEnableField": row.update_interrupt_enable_field,
            "kUpdateFlagField": row.update_flag_field,
            "kUpdateGenerationField": row.update_generation_field,
            "kPrescalerField": row.prescaler_field,
            "kPeriodField": row.period_field,
            "kOnePulseField": row.one_pulse_field,
            "kCenterAlignedField": row.center_aligned_field,
            "kAutoReloadPreloadField": row.auto_reload_preload_field,
            "kClockSourceField": row.clock_source_field,
            "kEncoderModeField": row.encoder_mode_field,
            "kEncoderEnableField": row.encoder_enable_field,
            "kEncoderPositionEnableField": row.encoder_position_enable_field,
            "kEncoderSpeedEnableField": row.encoder_speed_enable_field,
            "kEncoderPhaseEdgeField": row.encoder_phase_edge_field,
            "kDirectionField": row.direction_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr std::uint32_t kCounterBits = {row.counter_bits}u;",
            f"  static constexpr std::uint32_t kChannelCount = {row.channel_count}u;",
            f"  static constexpr bool kHasCompare = {'true' if row.has_compare else 'false'};",
            f"  static constexpr bool kHasCapture = {'true' if row.has_capture else 'false'};",
            f"  static constexpr bool kHasEncoder = {'true' if row.has_encoder else 'false'};",
            f"  static constexpr bool kHasPwm = {'true' if row.has_pwm else 'false'};",
            f"  static constexpr bool kHasOnePulse = {'true' if row.has_one_pulse else 'false'};",
            "  static constexpr bool kHasCenterAligned = "
            + ("true" if row.has_center_aligned else "false")
            + ";",
            "  static constexpr bool kHasComplementaryOutputs = "
            + ("true" if row.has_complementary_outputs else "false")
            + ";",
            f"  static constexpr bool kHasDeadtime = {'true' if row.has_deadtime else 'false'};",
            "  static constexpr bool kHasBreakInput = "
            + ("true" if row.has_break_input else "false")
            + ";",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(_timer_irq_lines(row))
        lines.extend(_timer_tier234_lines(row))
        return lines

    return _build


def _timer_tier234_lines(row: TimerSemanticRow) -> list[str]:
    """add-timer-tier-2-3-4-data: max prescaler + trigger sources +
    master outputs + capability flags constexprs."""

    def _option_array(name: str, items: tuple[tuple[str, int], ...]) -> str:
        # The source label is informational; only ``field_value`` is needed
        # at compile time to drive the SMS / MMS register write.  The
        # boundary test forbids string literals in runtime C++, so we emit
        # a typed `std::array<std::uint8_t, N>` keyed by field_value.
        if not items:
            return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
        values = ", ".join(f"{val}u" for _, val in items)
        return (
            f"  static constexpr std::array<std::uint8_t, {len(items)}> {name} = {{{{{values}}}}};"
        )

    return [
        f"  static constexpr std::uint32_t kMaxPrescaler = {row.max_prescaler}u;",
        f"  static constexpr std::uint32_t kMaxAutoReload = {row.max_auto_reload}u;",
        _option_array("kTriggerSources", row.trigger_sources),
        _option_array("kMasterOutputModes", row.master_outputs),
        f"  static constexpr bool kSupportsDmaBurst = {'true' if row.supports_dma_burst else 'false'};",
        f"  static constexpr bool kSupportsRepetitionCounter = {'true' if row.supports_repetition_counter else 'false'};",
        f"  static constexpr bool kSupportsXorInput = {'true' if row.supports_xor_input else 'false'};",
    ]


def _timer_channel_specialization_lines(
    channel_rows: tuple[TimerChannelSemanticRow, ...],
) -> list[str]:
    lines = [
        "template<PeripheralId Id, std::size_t ChannelIndex>",
        "struct TimerChannelSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr bool kSupportsCompare = false;",
        "  static constexpr bool kSupportsCapture = false;",
        "  static constexpr bool kSupportsEncoderInput = false;",
        "  static constexpr bool kSupportsPwm = false;",
        "  static constexpr bool kSupportsComplementaryOutput = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;",
        "};",
        "",
    ]
    if not channel_rows:
        return lines

    lines.extend(
        [
            "struct TimerChannelHardwareLut {",
            "  bool supports_compare;",
            "  bool supports_capture;",
            "  bool supports_encoder_input;",
            "  bool supports_pwm;",
            "  bool supports_complementary_output;",
            "  RuntimeRegisterRef control_register;",
            "  RuntimeRegisterRef status_register;",
            "  RuntimeRegisterRef compare_register;",
            "  RuntimeRegisterRef secondary_compare_register;",
            "  RuntimeRegisterRef period_register;",
            "  RuntimeRegisterRef counter_register;",
            "  RuntimeRegisterRef capture_register;",
            "  RuntimeFieldRef enable_field;",
            "  RuntimeFieldRef interrupt_enable_field;",
            "  RuntimeFieldRef interrupt_flag_field;",
            "  RuntimeFieldRef mode_field;",
            "  RuntimeFieldRef preload_field;",
            "  RuntimeFieldRef output_enable_field;",
            "  RuntimeFieldRef output_polarity_field;",
            "  RuntimeFieldRef complementary_output_enable_field;",
            "  RuntimeFieldRef capture_select_field;",
            "};",
            "",
            f"inline constexpr std::array<TimerChannelHardwareLut, {len(channel_rows)}> "
            "kTimerChannelHardwareLut = {{",
        ]
    )
    for row in channel_rows:
        lines.append(
            "  {"
            f"{'true' if row.supports_compare else 'false'}, "
            f"{'true' if row.supports_capture else 'false'}, "
            f"{'true' if row.supports_encoder_input else 'false'}, "
            f"{'true' if row.supports_pwm else 'false'}, "
            f"{'true' if row.supports_complementary_output else 'false'}, "
            f"{_register_ref_expr(row.control_reg)}, "
            f"{_register_ref_expr(row.status_reg)}, "
            f"{_register_ref_expr(row.compare_reg)}, "
            f"{_register_ref_expr(row.secondary_compare_reg)}, "
            f"{_register_ref_expr(row.period_reg)}, "
            f"{_register_ref_expr(row.counter_reg)}, "
            f"{_register_ref_expr(row.capture_reg)}, "
            f"{_field_ref_expr(row.enable_field)}, "
            f"{_field_ref_expr(row.interrupt_enable_field)}, "
            f"{_field_ref_expr(row.interrupt_flag_field)}, "
            f"{_field_ref_expr(row.mode_field)}, "
            f"{_field_ref_expr(row.preload_field)}, "
            f"{_field_ref_expr(row.output_enable_field)}, "
            f"{_field_ref_expr(row.output_polarity_field)}, "
            f"{_field_ref_expr(row.complementary_output_enable_field)}, "
            f"{_field_ref_expr(row.capture_select_field)}"
            "},"
        )
    lines.append("}};")
    lines.append("")
    lines.extend(
        [
            "template<std::size_t Index>",
            "struct TimerChannelTraitsBase {",
            "  static constexpr auto& kFacts = kTimerChannelHardwareLut[Index];",
            "  static constexpr bool kPresent = true;",
            "  static constexpr bool kSupportsCompare = kFacts.supports_compare;",
            "  static constexpr bool kSupportsCapture = kFacts.supports_capture;",
            "  static constexpr bool kSupportsEncoderInput = kFacts.supports_encoder_input;",
            "  static constexpr bool kSupportsPwm = kFacts.supports_pwm;",
            "  static constexpr bool kSupportsComplementaryOutput = kFacts.supports_complementary_output;",
            "  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;",
            "  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;",
            "  static constexpr RuntimeRegisterRef kCompareRegister = kFacts.compare_register;",
            "  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kFacts.secondary_compare_register;",
            "  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;",
            "  static constexpr RuntimeRegisterRef kCounterRegister = kFacts.counter_register;",
            "  static constexpr RuntimeRegisterRef kCaptureRegister = kFacts.capture_register;",
            "  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;",
            "  static constexpr RuntimeFieldRef kInterruptEnableField = kFacts.interrupt_enable_field;",
            "  static constexpr RuntimeFieldRef kInterruptFlagField = kFacts.interrupt_flag_field;",
            "  static constexpr RuntimeFieldRef kModeField = kFacts.mode_field;",
            "  static constexpr RuntimeFieldRef kPreloadField = kFacts.preload_field;",
            "  static constexpr RuntimeFieldRef kOutputEnableField = kFacts.output_enable_field;",
            "  static constexpr RuntimeFieldRef kOutputPolarityField = kFacts.output_polarity_field;",
            "  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kFacts.complementary_output_enable_field;",
            "  static constexpr RuntimeFieldRef kCaptureSelectField = kFacts.capture_select_field;",
            "};",
            "",
        ]
    )
    for index, row in enumerate(channel_rows):
        peripheral_id = _enum_identifier(row.peripheral_name)
        lines.append(
            f"template<> struct TimerChannelSemanticTraits<PeripheralId::{peripheral_id}, "
            f"{row.channel_index}u> : TimerChannelTraitsBase<{index}> {{}};"
        )
    lines.append("")
    return lines


def _pwm_specialization_builder(context: _SemanticContext):
    def _build(row: PwmSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr std::uint32_t kCounterBits = 0u;",
                "  static constexpr std::uint32_t kChannelCount = 0u;",
                "  static constexpr bool kHasComplementaryOutputs = false;",
                "  static constexpr bool kHasDeadtime = false;",
                "  static constexpr bool kHasFaultInput = false;",
                "  static constexpr bool kHasCenterAligned = false;",
                "  static constexpr bool kHasSynchronizedUpdate = false;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kOutputEnableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSyncRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kLoadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearLoadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClockPrescalerField = kInvalidFieldRef;",
                *_pwm_tier234_lines(row),
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kOutputEnableRegister": row.output_enable_reg,
            "kStatusRegister": row.status_reg,
            "kClockRegister": row.clock_reg,
            "kSyncRegister": row.sync_reg,
        }
        field_members = {
            "kMasterOutputEnableField": row.master_output_enable_field,
            "kLoadField": row.load_field,
            "kClearLoadField": row.clear_load_field,
            "kClockPrescalerField": row.clock_prescaler_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr std::uint32_t kCounterBits = {row.counter_bits}u;",
            f"  static constexpr std::uint32_t kChannelCount = {row.channel_count}u;",
            "  static constexpr bool kHasComplementaryOutputs = "
            + ("true" if row.has_complementary_outputs else "false")
            + ";",
            f"  static constexpr bool kHasDeadtime = {'true' if row.has_deadtime else 'false'};",
            "  static constexpr bool kHasFaultInput = "
            + ("true" if row.has_fault_input else "false")
            + ";",
            "  static constexpr bool kHasCenterAligned = "
            + ("true" if row.has_center_aligned else "false")
            + ";",
            "  static constexpr bool kHasSynchronizedUpdate = "
            + ("true" if row.has_synchronized_update else "false")
            + ";",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(_pwm_tier234_lines(row))
        return lines

    return _build


def _timer_lut_struct_lines() -> list[str]:
    return [
        "struct TimerHardwareLut {",
        "  BackendSchemaId schema_id;",
        "  std::uint32_t counter_bits;",
        "  std::uint32_t channel_count;",
        "  bool has_compare;",
        "  bool has_capture;",
        "  bool has_encoder;",
        "  bool has_pwm;",
        "  bool has_one_pulse;",
        "  bool has_center_aligned;",
        "  bool has_complementary_outputs;",
        "  bool has_deadtime;",
        "  bool has_break_input;",
        "  RuntimeRegisterRef control_register;",
        "  RuntimeRegisterRef status_register;",
        "  RuntimeRegisterRef event_register;",
        "  RuntimeRegisterRef counter_register;",
        "  RuntimeRegisterRef prescaler_register;",
        "  RuntimeRegisterRef period_register;",
        "  RuntimeFieldRef enable_field;",
        "  RuntimeFieldRef disable_field;",
        "  RuntimeFieldRef module_disable_field;",
        "  RuntimeFieldRef software_reset_field;",
        "  RuntimeFieldRef start_field;",
        "  RuntimeFieldRef stop_field;",
        "  RuntimeFieldRef update_interrupt_enable_field;",
        "  RuntimeFieldRef update_flag_field;",
        "  RuntimeFieldRef update_generation_field;",
        "  RuntimeFieldRef prescaler_field;",
        "  RuntimeFieldRef period_field;",
        "  RuntimeFieldRef one_pulse_field;",
        "  RuntimeFieldRef center_aligned_field;",
        "  RuntimeFieldRef auto_reload_preload_field;",
        "  RuntimeFieldRef clock_source_field;",
        "  RuntimeFieldRef encoder_mode_field;",
        "  RuntimeFieldRef encoder_enable_field;",
        "  RuntimeFieldRef encoder_position_enable_field;",
        "  RuntimeFieldRef encoder_speed_enable_field;",
        "  RuntimeFieldRef encoder_phase_edge_field;",
        "  RuntimeFieldRef direction_field;",
        "  std::uint32_t update_irq_number;",
        "  std::uint32_t capture_irq_number;",
        "  std::uint32_t break_irq_number;",
        "  std::uint32_t trigger_irq_number;",
        "  std::uint32_t max_prescaler;",
        "  std::uint32_t max_auto_reload;",
        "  bool supports_dma_burst;",
        "  bool supports_repetition_counter;",
        "  bool supports_xor_input;",
        "};",
        "",
    ]


def _timer_lut_table_lines(
    context: _SemanticContext,
    rows: list[TimerSemanticRow],
) -> list[str]:
    def _opt_irq(value: int | None) -> str:
        return f"{value}u" if value is not None else "0xFFFFFFFFu"

    lines = [
        f"inline constexpr std::array<TimerHardwareLut, {len(rows)}> kTimerHardwareLut = {{{{",
    ]
    for row in rows:
        lines.append(
            "  {"
            f"{_schema_ref_expr(context, row.schema_id)}, "
            f"{row.counter_bits}u, {row.channel_count}u, "
            f"{'true' if row.has_compare else 'false'}, "
            f"{'true' if row.has_capture else 'false'}, "
            f"{'true' if row.has_encoder else 'false'}, "
            f"{'true' if row.has_pwm else 'false'}, "
            f"{'true' if row.has_one_pulse else 'false'}, "
            f"{'true' if row.has_center_aligned else 'false'}, "
            f"{'true' if row.has_complementary_outputs else 'false'}, "
            f"{'true' if row.has_deadtime else 'false'}, "
            f"{'true' if row.has_break_input else 'false'}, "
            f"{_register_ref_expr(row.control_reg)}, "
            f"{_register_ref_expr(row.status_reg)}, "
            f"{_register_ref_expr(row.event_reg)}, "
            f"{_register_ref_expr(row.counter_reg)}, "
            f"{_register_ref_expr(row.prescaler_reg)}, "
            f"{_register_ref_expr(row.period_reg)}, "
            f"{_field_ref_expr(row.enable_field)}, "
            f"{_field_ref_expr(row.disable_field)}, "
            f"{_field_ref_expr(row.module_disable_field)}, "
            f"{_field_ref_expr(row.software_reset_field)}, "
            f"{_field_ref_expr(row.start_field)}, "
            f"{_field_ref_expr(row.stop_field)}, "
            f"{_field_ref_expr(row.update_interrupt_enable_field)}, "
            f"{_field_ref_expr(row.update_flag_field)}, "
            f"{_field_ref_expr(row.update_generation_field)}, "
            f"{_field_ref_expr(row.prescaler_field)}, "
            f"{_field_ref_expr(row.period_field)}, "
            f"{_field_ref_expr(row.one_pulse_field)}, "
            f"{_field_ref_expr(row.center_aligned_field)}, "
            f"{_field_ref_expr(row.auto_reload_preload_field)}, "
            f"{_field_ref_expr(row.clock_source_field)}, "
            f"{_field_ref_expr(row.encoder_mode_field)}, "
            f"{_field_ref_expr(row.encoder_enable_field)}, "
            f"{_field_ref_expr(row.encoder_position_enable_field)}, "
            f"{_field_ref_expr(row.encoder_speed_enable_field)}, "
            f"{_field_ref_expr(row.encoder_phase_edge_field)}, "
            f"{_field_ref_expr(row.direction_field)}, "
            f"{_opt_irq(row.update_irq_number)}, "
            f"{_opt_irq(row.capture_irq_number)}, "
            f"{_opt_irq(row.break_irq_number)}, "
            f"{_opt_irq(row.trigger_irq_number)}, "
            f"{row.max_prescaler}u, {row.max_auto_reload}u, "
            f"{'true' if row.supports_dma_burst else 'false'}, "
            f"{'true' if row.supports_repetition_counter else 'false'}, "
            f"{'true' if row.supports_xor_input else 'false'}"
            "},"
        )
    lines.append("}};")
    lines.append("")
    return lines


def _timer_traits_base_lines() -> list[str]:
    return [
        "template<std::size_t Index>",
        "struct TimerTraitsBase {",
        "  static constexpr auto& kFacts = kTimerHardwareLut[Index];",
        "  static constexpr bool kPresent = true;",
        "  static constexpr BackendSchemaId kSchemaId = kFacts.schema_id;",
        "  static constexpr std::uint32_t kCounterBits = kFacts.counter_bits;",
        "  static constexpr std::uint32_t kChannelCount = kFacts.channel_count;",
        "  static constexpr bool kHasCompare = kFacts.has_compare;",
        "  static constexpr bool kHasCapture = kFacts.has_capture;",
        "  static constexpr bool kHasEncoder = kFacts.has_encoder;",
        "  static constexpr bool kHasPwm = kFacts.has_pwm;",
        "  static constexpr bool kHasOnePulse = kFacts.has_one_pulse;",
        "  static constexpr bool kHasCenterAligned = kFacts.has_center_aligned;",
        "  static constexpr bool kHasComplementaryOutputs = kFacts.has_complementary_outputs;",
        "  static constexpr bool kHasDeadtime = kFacts.has_deadtime;",
        "  static constexpr bool kHasBreakInput = kFacts.has_break_input;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;",
        "  static constexpr RuntimeRegisterRef kEventRegister = kFacts.event_register;",
        "  static constexpr RuntimeRegisterRef kCounterRegister = kFacts.counter_register;",
        "  static constexpr RuntimeRegisterRef kPrescalerRegister = kFacts.prescaler_register;",
        "  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;",
        "  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;",
        "  static constexpr RuntimeFieldRef kDisableField = kFacts.disable_field;",
        "  static constexpr RuntimeFieldRef kModuleDisableField = kFacts.module_disable_field;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kFacts.software_reset_field;",
        "  static constexpr RuntimeFieldRef kStartField = kFacts.start_field;",
        "  static constexpr RuntimeFieldRef kStopField = kFacts.stop_field;",
        "  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kFacts.update_interrupt_enable_field;",
        "  static constexpr RuntimeFieldRef kUpdateFlagField = kFacts.update_flag_field;",
        "  static constexpr RuntimeFieldRef kUpdateGenerationField = kFacts.update_generation_field;",
        "  static constexpr RuntimeFieldRef kPrescalerField = kFacts.prescaler_field;",
        "  static constexpr RuntimeFieldRef kPeriodField = kFacts.period_field;",
        "  static constexpr RuntimeFieldRef kOnePulseField = kFacts.one_pulse_field;",
        "  static constexpr RuntimeFieldRef kCenterAlignedField = kFacts.center_aligned_field;",
        "  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kFacts.auto_reload_preload_field;",
        "  static constexpr RuntimeFieldRef kClockSourceField = kFacts.clock_source_field;",
        "  static constexpr RuntimeFieldRef kEncoderModeField = kFacts.encoder_mode_field;",
        "  static constexpr RuntimeFieldRef kEncoderEnableField = kFacts.encoder_enable_field;",
        "  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kFacts.encoder_position_enable_field;",
        "  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kFacts.encoder_speed_enable_field;",
        "  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kFacts.encoder_phase_edge_field;",
        "  static constexpr RuntimeFieldRef kDirectionField = kFacts.direction_field;",
        "  static constexpr std::uint32_t kUpdateIrqNumber = kFacts.update_irq_number;",
        "  static constexpr std::uint32_t kCaptureIrqNumber = kFacts.capture_irq_number;",
        "  static constexpr std::uint32_t kBreakIrqNumber = kFacts.break_irq_number;",
        "  static constexpr std::uint32_t kTriggerIrqNumber = kFacts.trigger_irq_number;",
        "  static constexpr std::uint32_t kMaxPrescaler = kFacts.max_prescaler;",
        "  static constexpr std::uint32_t kMaxAutoReload = kFacts.max_auto_reload;",
        "  static constexpr bool kSupportsDmaBurst = kFacts.supports_dma_burst;",
        "  static constexpr bool kSupportsRepetitionCounter = kFacts.supports_repetition_counter;",
        "  static constexpr bool kSupportsXorInput = kFacts.supports_xor_input;",
        "};",
        "",
    ]


def _timer_per_instance_array_lines(row: TimerSemanticRow) -> list[str]:
    """Variable-length tier 2/3/4 + de-duplicated IRQ-union +
    DMA-binding arrays."""

    def _u8_array(name: str, items: tuple[int, ...]) -> str:
        if not items:
            return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
        values = ", ".join(f"{v}u" for v in items)
        return (
            f"  static constexpr std::array<std::uint8_t, {len(items)}> {name} = {{{{{values}}}}};"
        )

    trigger_vals = tuple(v for _name, v in row.trigger_sources)
    master_vals = tuple(v for _name, v in row.master_outputs)
    union_irqs: tuple[int, ...] = tuple(
        sorted(
            {
                v
                for v in (
                    row.update_irq_number,
                    row.capture_irq_number,
                    row.break_irq_number,
                    row.trigger_irq_number,
                )
                if v is not None
            }
        )
    )
    lines = [
        _u8_array("kTriggerSources", trigger_vals),
        _u8_array("kMasterOutputModes", master_vals),
    ]
    lines.extend(_irq_numbers_lines(union_irqs))
    lines.extend(_dma_binding_ref_array_lines(row.dma_bindings))
    return lines


def _pwm_lut_struct_lines() -> list[str]:
    """Per-class hardware-LUT struct.  Carries every scalar +
    register / field reference; variable-length tier 2/3/4 arrays
    stay on the per-instance specialisation."""
    return [
        "struct PwmHardwareLut {",
        "  BackendSchemaId schema_id;",
        "  std::uint32_t counter_bits;",
        "  std::uint32_t channel_count;",
        "  bool has_complementary_outputs;",
        "  bool has_deadtime;",
        "  bool has_fault_input;",
        "  bool has_center_aligned;",
        "  bool has_synchronized_update;",
        "  RuntimeRegisterRef control_register;",
        "  RuntimeRegisterRef output_enable_register;",
        "  RuntimeRegisterRef status_register;",
        "  RuntimeRegisterRef clock_register;",
        "  RuntimeRegisterRef sync_register;",
        "  RuntimeFieldRef master_output_enable_field;",
        "  RuntimeFieldRef load_field;",
        "  RuntimeFieldRef clear_load_field;",
        "  RuntimeFieldRef clock_prescaler_field;",
        "  std::uint32_t max_prescaler;",
        "  std::uint32_t max_period;",
        "  bool supports_deadtime;",
        "  bool supports_break_input;",
        "  bool supports_complementary_outputs;",
        "  bool supports_asymmetric_pwm;",
        "  bool supports_combined_pwm;",
        "};",
        "",
    ]


def _pwm_lut_table_lines(
    context: _SemanticContext,
    rows: list[PwmSemanticRow],
) -> list[str]:
    """Render the ``inline constexpr std::array<PwmHardwareLut, N>``
    table indexed by the same ordering as the per-instance
    specialisations."""
    lines: list[str] = [
        f"inline constexpr std::array<PwmHardwareLut, {len(rows)}> kPwmHardwareLut = {{{{",
    ]
    for row in rows:
        lines.append(
            "  {"
            f"{_schema_ref_expr(context, row.schema_id)}, "
            f"{row.counter_bits}u, "
            f"{row.channel_count}u, "
            f"{'true' if row.has_complementary_outputs else 'false'}, "
            f"{'true' if row.has_deadtime else 'false'}, "
            f"{'true' if row.has_fault_input else 'false'}, "
            f"{'true' if row.has_center_aligned else 'false'}, "
            f"{'true' if row.has_synchronized_update else 'false'}, "
            f"{_register_ref_expr(row.control_reg)}, "
            f"{_register_ref_expr(row.output_enable_reg)}, "
            f"{_register_ref_expr(row.status_reg)}, "
            f"{_register_ref_expr(row.clock_reg)}, "
            f"{_register_ref_expr(row.sync_reg)}, "
            f"{_field_ref_expr(row.master_output_enable_field)}, "
            f"{_field_ref_expr(row.load_field)}, "
            f"{_field_ref_expr(row.clear_load_field)}, "
            f"{_field_ref_expr(row.clock_prescaler_field)}, "
            f"{row.max_prescaler}u, "
            f"{row.max_period}u, "
            f"{'true' if row.supports_deadtime else 'false'}, "
            f"{'true' if row.supports_break_input else 'false'}, "
            f"{'true' if row.supports_complementary_outputs else 'false'}, "
            f"{'true' if row.supports_asymmetric_pwm else 'false'}, "
            f"{'true' if row.supports_combined_pwm else 'false'}"
            "},"
        )
    lines.append("}};")
    lines.append("")
    return lines


def _pwm_traits_base_lines(row_count: int) -> list[str]:
    """The shared base that pulls every fact from
    ``kPwmHardwareLut[Index]``.  Per-instance specialisations
    inherit from one of ``PwmTraitsBase<0..N-1>`` so consumers
    keep the existing ``PwmSemanticTraits<P>::kField`` reading
    surface."""
    del row_count  # Single template for every index — no fanout.
    return [
        "template<std::size_t Index>",
        "struct PwmTraitsBase {",
        "  static constexpr auto& kFacts = kPwmHardwareLut[Index];",
        "  static constexpr bool kPresent = true;",
        "  static constexpr BackendSchemaId kSchemaId = kFacts.schema_id;",
        "  static constexpr std::uint32_t kCounterBits = kFacts.counter_bits;",
        "  static constexpr std::uint32_t kChannelCount = kFacts.channel_count;",
        "  static constexpr bool kHasComplementaryOutputs = kFacts.has_complementary_outputs;",
        "  static constexpr bool kHasDeadtime = kFacts.has_deadtime;",
        "  static constexpr bool kHasFaultInput = kFacts.has_fault_input;",
        "  static constexpr bool kHasCenterAligned = kFacts.has_center_aligned;",
        "  static constexpr bool kHasSynchronizedUpdate = kFacts.has_synchronized_update;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;",
        "  static constexpr RuntimeRegisterRef kOutputEnableRegister = kFacts.output_enable_register;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;",
        "  static constexpr RuntimeRegisterRef kClockRegister = kFacts.clock_register;",
        "  static constexpr RuntimeRegisterRef kSyncRegister = kFacts.sync_register;",
        "  static constexpr RuntimeFieldRef kMasterOutputEnableField = kFacts.master_output_enable_field;",
        "  static constexpr RuntimeFieldRef kLoadField = kFacts.load_field;",
        "  static constexpr RuntimeFieldRef kClearLoadField = kFacts.clear_load_field;",
        "  static constexpr RuntimeFieldRef kClockPrescalerField = kFacts.clock_prescaler_field;",
        "  static constexpr std::uint32_t kMaxPrescaler = kFacts.max_prescaler;",
        "  static constexpr std::uint32_t kMaxPeriod = kFacts.max_period;",
        "  static constexpr bool kSupportsDeadtime = kFacts.supports_deadtime;",
        "  static constexpr bool kSupportsBreakInput = kFacts.supports_break_input;",
        "  static constexpr bool kSupportsComplementaryOutputs = kFacts.supports_complementary_outputs;",
        "  static constexpr bool kSupportsAsymmetricPwm = kFacts.supports_asymmetric_pwm;",
        "  static constexpr bool kSupportsCombinedPwm = kFacts.supports_combined_pwm;",
        "};",
        "",
    ]


def _pwm_per_instance_array_lines(row: PwmSemanticRow) -> list[str]:
    """Variable-length tier 2/3/4 arrays — these stay on the
    per-instance specialisation since their sizes differ across
    instances."""

    def _u8_array(name: str, items: tuple[int, ...]) -> str:
        if not items:
            return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
        values = ", ".join(f"{v}u" for v in items)
        return (
            f"  static constexpr std::array<std::uint8_t, {len(items)}> {name} = {{{{{values}}}}};"
        )

    deadtime_psc = tuple(p for p, _bits, _ns in row.deadtime_options)
    alignment_vals = tuple(v for _name, v in row.supported_alignments)
    break_polarity = tuple(p for _id, p, _e in row.break_inputs)
    return [
        _u8_array("kDeadtimeOptions", deadtime_psc),
        _u8_array("kSupportedAlignments", alignment_vals),
        _u8_array("kBreakInputs", break_polarity),
    ]


def _pwm_tier234_lines(row: PwmSemanticRow) -> list[str]:
    """add-pwm-tier-2-3-4-data: max prescaler/period + deadtime / alignment /
    break-input arrays + capability flag constexprs."""

    def _u8_array(name: str, items: tuple[int, ...]) -> str:
        if not items:
            return f"  static constexpr std::array<std::uint8_t, 0> {name} = {{}};"
        values = ", ".join(f"{v}u" for v in items)
        return (
            f"  static constexpr std::array<std::uint8_t, {len(items)}> {name} = {{{{{values}}}}};"
        )

    deadtime_psc = tuple(p for p, _bits, _ns in row.deadtime_options)
    alignment_vals = tuple(v for _name, v in row.supported_alignments)
    break_polarity = tuple(p for _id, p, _e in row.break_inputs)
    return [
        f"  static constexpr std::uint32_t kMaxPrescaler = {row.max_prescaler}u;",
        f"  static constexpr std::uint32_t kMaxPeriod = {row.max_period}u;",
        _u8_array("kDeadtimeOptions", deadtime_psc),
        _u8_array("kSupportedAlignments", alignment_vals),
        _u8_array("kBreakInputs", break_polarity),
        f"  static constexpr bool kSupportsDeadtime = {'true' if row.supports_deadtime else 'false'};",
        f"  static constexpr bool kSupportsBreakInput = {'true' if row.supports_break_input else 'false'};",
        f"  static constexpr bool kSupportsComplementaryOutputs = {'true' if row.supports_complementary_outputs else 'false'};",
        f"  static constexpr bool kSupportsAsymmetricPwm = {'true' if row.supports_asymmetric_pwm else 'false'};",
        f"  static constexpr bool kSupportsCombinedPwm = {'true' if row.supports_combined_pwm else 'false'};",
    ]


def _pwm_channel_specialization_lines(
    channel_rows: tuple[PwmChannelSemanticRow, ...],
) -> list[str]:
    """Emit per-channel trait specialisations using the shared-LUT
    pattern.  All channel facts are fixed-size scalars / register +
    field refs, so the entire row goes into the LUT and the
    per-channel specialisation collapses to a one-line inheritance.
    """
    lines = [
        "template<PeripheralId Id, std::size_t ChannelIndex>",
        "struct PwmChannelSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr bool kSupportsComplementaryOutput = false;",
        "  static constexpr bool kSupportsDeadtime = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDeadtimeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDeadtimeRiseField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDeadtimeFallField = kInvalidFieldRef;",
        "};",
        "",
    ]
    if not channel_rows:
        return lines

    # Per-class LUT struct.
    lines.extend(
        [
            "struct PwmChannelHardwareLut {",
            "  bool supports_complementary_output;",
            "  bool supports_deadtime;",
            "  RuntimeRegisterRef control_register;",
            "  RuntimeRegisterRef compare_register;",
            "  RuntimeRegisterRef secondary_compare_register;",
            "  RuntimeRegisterRef period_register;",
            "  RuntimeRegisterRef deadtime_register;",
            "  RuntimeFieldRef enable_field;",
            "  RuntimeFieldRef interrupt_enable_field;",
            "  RuntimeFieldRef interrupt_flag_field;",
            "  RuntimeFieldRef mode_field;",
            "  RuntimeFieldRef polarity_field;",
            "  RuntimeFieldRef complementary_output_enable_field;",
            "  RuntimeFieldRef center_aligned_field;",
            "  RuntimeFieldRef period_field;",
            "  RuntimeFieldRef duty_field;",
            "  RuntimeFieldRef deadtime_rise_field;",
            "  RuntimeFieldRef deadtime_fall_field;",
            "};",
            "",
            f"inline constexpr std::array<PwmChannelHardwareLut, {len(channel_rows)}> "
            "kPwmChannelHardwareLut = {{",
        ]
    )
    for row in channel_rows:
        lines.append(
            "  {"
            f"{'true' if row.supports_complementary_output else 'false'}, "
            f"{'true' if row.supports_deadtime else 'false'}, "
            f"{_register_ref_expr(row.control_reg)}, "
            f"{_register_ref_expr(row.compare_reg)}, "
            f"{_register_ref_expr(row.secondary_compare_reg)}, "
            f"{_register_ref_expr(row.period_reg)}, "
            f"{_register_ref_expr(row.deadtime_reg)}, "
            f"{_field_ref_expr(row.enable_field)}, "
            f"{_field_ref_expr(row.interrupt_enable_field)}, "
            f"{_field_ref_expr(row.interrupt_flag_field)}, "
            f"{_field_ref_expr(row.mode_field)}, "
            f"{_field_ref_expr(row.polarity_field)}, "
            f"{_field_ref_expr(row.complementary_output_enable_field)}, "
            f"{_field_ref_expr(row.center_aligned_field)}, "
            f"{_field_ref_expr(row.period_field)}, "
            f"{_field_ref_expr(row.duty_field)}, "
            f"{_field_ref_expr(row.deadtime_rise_field)}, "
            f"{_field_ref_expr(row.deadtime_fall_field)}"
            "},"
        )
    lines.append("}};")
    lines.append("")

    # Shared base — one template, every per-channel specialisation
    # inherits from one instance of it.
    lines.extend(
        [
            "template<std::size_t Index>",
            "struct PwmChannelTraitsBase {",
            "  static constexpr auto& kFacts = kPwmChannelHardwareLut[Index];",
            "  static constexpr bool kPresent = true;",
            "  static constexpr bool kSupportsComplementaryOutput = kFacts.supports_complementary_output;",
            "  static constexpr bool kSupportsDeadtime = kFacts.supports_deadtime;",
            "  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;",
            "  static constexpr RuntimeRegisterRef kCompareRegister = kFacts.compare_register;",
            "  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kFacts.secondary_compare_register;",
            "  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;",
            "  static constexpr RuntimeRegisterRef kDeadtimeRegister = kFacts.deadtime_register;",
            "  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;",
            "  static constexpr RuntimeFieldRef kInterruptEnableField = kFacts.interrupt_enable_field;",
            "  static constexpr RuntimeFieldRef kInterruptFlagField = kFacts.interrupt_flag_field;",
            "  static constexpr RuntimeFieldRef kModeField = kFacts.mode_field;",
            "  static constexpr RuntimeFieldRef kPolarityField = kFacts.polarity_field;",
            "  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kFacts.complementary_output_enable_field;",
            "  static constexpr RuntimeFieldRef kCenterAlignedField = kFacts.center_aligned_field;",
            "  static constexpr RuntimeFieldRef kPeriodField = kFacts.period_field;",
            "  static constexpr RuntimeFieldRef kDutyField = kFacts.duty_field;",
            "  static constexpr RuntimeFieldRef kDeadtimeRiseField = kFacts.deadtime_rise_field;",
            "  static constexpr RuntimeFieldRef kDeadtimeFallField = kFacts.deadtime_fall_field;",
            "};",
            "",
        ]
    )
    for index, row in enumerate(channel_rows):
        peripheral_id = _enum_identifier(row.peripheral_name)
        lines.append(
            f"template<> struct PwmChannelSemanticTraits<PeripheralId::{peripheral_id}, "
            f"{row.channel_index}u> : PwmChannelTraitsBase<{index}> {{}};"
        )
    lines.append("")
    return lines


def emit_runtime_driver_semantics_common_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    return _emit_driver_semantics_common_header(family_dir=family_dir, device=device)


# emit_runtime_driver_gpio_semantics_header → runtime_driver/gpio.py


# _uart_peripheral_traits_block → runtime_driver/uart.py


# _dma_controller_hw_traits_block → runtime_driver/dma.py


def _timer_controller_hw_traits_block(device: CanonicalDeviceIR) -> list[str]:
    lines = [
        "// complete-rp2040-semantics Phase D: per-controller timer HW facts.",
        "enum class RuntimeTimerCtrlId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.rp2040_timer_controller_hw, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeTimerCtrlId Id>",
            "struct TimerControllerHwTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kCounterBits = 0u;",
            "  static constexpr std::uint8_t kAlarmCount = 0u;",
            "  static constexpr std::uint8_t kDreqAlarmBase = 0u;",
            "};",
            "",
        ]
    )
    for ctrl in device.rp2040_timer_controller_hw:
        lines.extend(
            [
                "template<>",
                f"struct TimerControllerHwTraits<RuntimeTimerCtrlId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kCounterBits = {ctrl.counter_bits}u;",
                f"  static constexpr std::uint8_t kAlarmCount = {ctrl.alarm_count}u;",
                f"  static constexpr std::uint8_t kDreqAlarmBase = {ctrl.dreq_alarm_base}u;",
                "};",
                "",
            ]
        )
    return lines


def _pwm_slice_hw_traits_block(device: CanonicalDeviceIR) -> list[str]:
    if not device.rp2040_pwm_slice_hw:
        return [
            "// complete-rp2040-semantics Phase D: per-slice PWM HW facts.",
            "template<std::uint8_t SliceIndex>",
            "struct PwmSliceHwTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint8_t kChannelAPin = 0u;",
            "  static constexpr std::uint8_t kChannelBPin = 0u;",
            "  static constexpr std::uint8_t kCounterBits = 0u;",
            "  static constexpr std::uint16_t kClockDivMinQ4 = 0u;",
            "  static constexpr std::uint16_t kClockDivMaxQ4 = 0u;",
            "};",
            "",
        ]
    lines = [
        "// complete-rp2040-semantics Phase D: per-slice PWM HW facts.",
        "template<std::uint8_t SliceIndex>",
        "struct PwmSliceHwTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr std::uint8_t kChannelAPin = 0u;",
        "  static constexpr std::uint8_t kChannelBPin = 0u;",
        "  static constexpr std::uint8_t kCounterBits = 0u;",
        "  static constexpr std::uint16_t kClockDivMinQ4 = 0u;",
        "  static constexpr std::uint16_t kClockDivMaxQ4 = 0u;",
        "};",
        "",
    ]
    for ctrl in device.rp2040_pwm_slice_hw:
        lines.extend(
            [
                "template<>",
                f"struct PwmSliceHwTraits<{ctrl.slice_index}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint8_t kChannelAPin = {ctrl.channel_a_pin}u;",
                f"  static constexpr std::uint8_t kChannelBPin = {ctrl.channel_b_pin}u;",
                f"  static constexpr std::uint8_t kCounterBits = {ctrl.counter_bits}u;",
                f"  static constexpr std::uint16_t kClockDivMinQ4 = {ctrl.clock_div_min_q4}u;",
                f"  static constexpr std::uint16_t kClockDivMaxQ4 = {ctrl.clock_div_max_q4}u;",
                "};",
                "",
            ]
        )
    return lines


def _flex_pwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase C: NXP iMXRT FlexPWM trait struct.

    iMXRT1060 ships ``PWM1``..``PWM4`` (4 submodules, paired A/B
    channels, complementary outputs, dead-time, fault input,
    force-init).  Per-submodule pad arrays are Phase-C-deferred —
    initial emission carries empty pad tuples; consumer concept
    checks rely on the silicon-fixed flag fields.
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase C: NXP iMXRT FlexPWM facts.",
        "enum class RuntimeFlexPwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.flex_pwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeFlexPwmId Id>",
            "struct FlexPwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kSubmoduleCount = 0u;",
            "  static constexpr bool kPairedChannels = false;",
            "  static constexpr bool kSupportsComplementary = false;",
            "  static constexpr bool kSupportsDeadtime = false;",
            "  static constexpr bool kSupportsFaultInput = false;",
            "  static constexpr bool kSupportsForceInitialization = false;",
            "};",
            "",
        ]
    )
    for ctrl in device.flex_pwm_peripherals:
        lines.extend(
            [
                "template<>",
                f"struct FlexPwmTraits<RuntimeFlexPwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kSubmoduleCount = {ctrl.submodule_count}u;",
                f"  static constexpr bool kPairedChannels = {'true' if ctrl.paired_channels else 'false'};",
                f"  static constexpr bool kSupportsComplementary = {'true' if ctrl.supports_complementary else 'false'};",
                f"  static constexpr bool kSupportsDeadtime = {'true' if ctrl.supports_deadtime else 'false'};",
                f"  static constexpr bool kSupportsFaultInput = {'true' if ctrl.supports_fault_input else 'false'};",
                f"  static constexpr bool kSupportsForceInitialization = {'true' if ctrl.supports_force_initialization else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def _mcpwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase B: Espressif MCPWM trait struct.

    Emits a `RuntimeMcpwmId` enum + `McpwmTraits<RuntimeMcpwmId>`
    template populated from `device.mcpwm_peripherals`.  ESP32 classic
    + S3 ship two MCPWM peripherals each; ESP32-C3 ships none (the
    descriptor list is empty there and only the primary template
    fires).
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase B: Espressif MCPWM facts.",
        "enum class RuntimeMcpwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.mcpwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeMcpwmId Id>",
            "struct McpwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::uint8_t kTimerCount = 0u;",
            "  static constexpr std::uint8_t kOutputSignalCount = 0u;",
            "  static constexpr std::array<std::uint16_t, 0> kGpioMatrixSignals = {};",
            "  static constexpr std::array<std::uint16_t, 0> kCaptureSignals = {};",
            "  static constexpr bool kSupportsDeadtime = false;",
            "  static constexpr bool kSupportsCarrierModulation = false;",
            "  static constexpr bool kSupportsFaultInput = false;",
            "};",
            "",
        ]
    )

    def _signal_array(name: str, signals: tuple[int, ...]) -> str:
        if not signals:
            return f"  static constexpr std::array<std::uint16_t, 0> {name} = {{}};"
        items = ", ".join(f"{s}u" for s in signals)
        return f"  static constexpr std::array<std::uint16_t, {len(signals)}> {name} = {{{items}}};"

    for ctrl in device.mcpwm_peripherals:
        lines.extend(
            [
                "template<>",
                f"struct McpwmTraits<RuntimeMcpwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr std::uint8_t kTimerCount = {ctrl.timer_count}u;",
                f"  static constexpr std::uint8_t kOutputSignalCount = {ctrl.output_signal_count}u;",
                _signal_array("kGpioMatrixSignals", ctrl.gpio_matrix_signals),
                _signal_array("kCaptureSignals", ctrl.capture_signals),
                f"  static constexpr bool kSupportsDeadtime = {'true' if ctrl.supports_deadtime else 'false'};",
                f"  static constexpr bool kSupportsCarrierModulation = {'true' if ctrl.supports_carrier_modulation else 'false'};",
                f"  static constexpr bool kSupportsFaultInput = {'true' if ctrl.supports_fault_input else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def _stm_timer_pwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase A: STM32 TIMx PWM trait struct.

    Emits a `RuntimeStmTimerPwmId` enum + `StmTimerPwmTraits` template
    populated from `device.stm_timer_pwm_peripherals`.  Per-channel
    pad arrays use `std::array<PinId, N>` keyed off the typed PinId
    enum from `../pins.hpp`.  ``kind`` is encoded as a typed
    `RuntimeStmTimerKind` enum so no string literals leak into the
    runtime C++ output.
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase A: STM32 TIM PWM facts.",
        "enum class RuntimeStmTimerKind : std::uint8_t {",
        "  None = 0,",
        "  Advanced = 1,",
        "  General = 2,",
        "};",
        "",
        "enum class RuntimeStmTimerPwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.stm_timer_pwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeStmTimerPwmId Id>",
            "struct StmTimerPwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr RuntimeStmTimerKind kKind = RuntimeStmTimerKind::None;",
            "  static constexpr std::uint8_t kChannelCount = 0u;",
            "  static constexpr std::uint8_t kCounterBits = 0u;",
            "  static constexpr std::array<PinId, 0> kValidCh1Pins = {};",
            "  static constexpr std::array<PinId, 0> kValidCh2Pins = {};",
            "  static constexpr std::array<PinId, 0> kValidCh3Pins = {};",
            "  static constexpr std::array<PinId, 0> kValidCh4Pins = {};",
            "  static constexpr std::array<PinId, 0> kValidCh1NPins = {};",
            "  static constexpr std::array<PinId, 0> kValidCh2NPins = {};",
            "  static constexpr std::array<PinId, 0> kValidCh3NPins = {};",
            "  static constexpr bool kSupportsComplementary = false;",
            "  static constexpr bool kSupportsDeadtime = false;",
            "  static constexpr bool kSupportsBrake = false;",
            "  static constexpr bool kSupportsCenterAligned = false;",
            "  static constexpr std::uint32_t kMaxClockHz = 0u;",
            "};",
            "",
        ]
    )

    def _pad_array(name: str, pads: tuple[str, ...]) -> str:
        if not pads:
            return f"  static constexpr std::array<PinId, 0> {name} = {{}};"
        items = ", ".join(f"PinId::{_enum_identifier(p)}" for p in pads)
        return f"  static constexpr std::array<PinId, {len(pads)}> {name} = {{{items}}};"

    _kind_token = {
        "advanced": "RuntimeStmTimerKind::Advanced",
        "general": "RuntimeStmTimerKind::General",
    }

    for ctrl in device.stm_timer_pwm_peripherals:
        kind_enum = _kind_token.get(ctrl.kind, "RuntimeStmTimerKind::None")
        ch_pads = list(ctrl.valid_ch_pins_per_channel) + [()] * 4
        chn_pads = list(ctrl.valid_chn_pins_per_channel) + [()] * 3
        lines.extend(
            [
                "template<>",
                f"struct StmTimerPwmTraits<RuntimeStmTimerPwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr RuntimeStmTimerKind kKind = {kind_enum};",
                f"  static constexpr std::uint8_t kChannelCount = {ctrl.channel_count}u;",
                f"  static constexpr std::uint8_t kCounterBits = {ctrl.counter_bits}u;",
                _pad_array("kValidCh1Pins", ch_pads[0]),
                _pad_array("kValidCh2Pins", ch_pads[1]),
                _pad_array("kValidCh3Pins", ch_pads[2]),
                _pad_array("kValidCh4Pins", ch_pads[3]),
                _pad_array("kValidCh1NPins", chn_pads[0]),
                _pad_array("kValidCh2NPins", chn_pads[1]),
                _pad_array("kValidCh3NPins", chn_pads[2]),
                f"  static constexpr bool kSupportsComplementary = {'true' if ctrl.supports_complementary else 'false'};",
                f"  static constexpr bool kSupportsDeadtime = {'true' if ctrl.supports_deadtime else 'false'};",
                f"  static constexpr bool kSupportsBrake = {'true' if ctrl.supports_brake else 'false'};",
                f"  static constexpr bool kSupportsCenterAligned = {'true' if ctrl.supports_center_aligned else 'false'};",
                f"  static constexpr std::uint32_t kMaxClockHz = {ctrl.max_clock_hz}u;",
                "};",
                "",
            ]
        )
    return lines


def _avr_da_tca_pwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase D: AVR-DA TCA PWM trait struct.

    Microchip AVR-DA exposes a single TCA0 routed via PORTMUX; emit a
    `RuntimeAvrDaTcaPwmId` enum + `AvrDaTcaPwmTraits` template.  Pad
    lists use the typed `PinId` enum so no string literals leak into
    the runtime C++ output.
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase D: Microchip AVR-DA TCA PWM facts.",
        "enum class RuntimeAvrDaTcaPwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.avr_da_tca_pwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeAvrDaTcaPwmId Id>",
            "struct AvrDaTcaPwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr std::array<PinId, 0> kDefaultChannelPins = {};",
            "  static constexpr std::uint8_t kSplitModeChannels = 0u;",
            "  static constexpr std::uint8_t kSingleModeChannels = 0u;",
            "  static constexpr std::uint8_t kCounterBits = 0u;",
            "  static constexpr bool kPortmuxAlt = false;",
            "};",
            "",
        ]
    )

    def _pad_array(name: str, pads: tuple[str, ...]) -> str:
        if not pads:
            return f"  static constexpr std::array<PinId, 0> {name} = {{}};"
        items = ", ".join(f"PinId::{_enum_identifier(p)}" for p in pads)
        return f"  static constexpr std::array<PinId, {len(pads)}> {name} = {{{items}}};"

    for ctrl in device.avr_da_tca_pwm_peripherals:
        lines.extend(
            [
                "template<>",
                f"struct AvrDaTcaPwmTraits<RuntimeAvrDaTcaPwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                _pad_array("kDefaultChannelPins", ctrl.default_channel_pins),
                f"  static constexpr std::uint8_t kSplitModeChannels = {ctrl.split_mode_channels}u;",
                f"  static constexpr std::uint8_t kSingleModeChannels = {ctrl.single_mode_channels}u;",
                f"  static constexpr std::uint8_t kCounterBits = {ctrl.counter_bits}u;",
                f"  static constexpr bool kPortmuxAlt = {'true' if ctrl.portmux_alt else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def _same70_pwm_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """extend-pwm-coverage-all-mcus Phase D: SAM E70 PWM + TC trait struct.

    Emits a `RuntimeSame70PwmKind` enum (Pwm / Tc) plus a
    `RuntimeSame70PwmId` enum + `Same70PwmTraits` template populated
    from `device.same70_pwm_peripherals`.  Per-channel pad mapping is
    Phase-D-deferred (left empty); silicon-fixed flag fields suffice
    for consumer concept checks in this pass.
    """
    lines = [
        "// extend-pwm-coverage-all-mcus Phase D: Microchip SAM E70 PWM/TC facts.",
        "enum class RuntimeSame70PwmKind : std::uint8_t {",
        "  None = 0,",
        "  Pwm = 1,",
        "  Tc = 2,",
        "};",
        "",
        "enum class RuntimeSame70PwmId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.same70_pwm_peripherals, start=1):
        lines.append(f"  {ctrl.controller_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeSame70PwmId Id>",
            "struct Same70PwmTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr RuntimeSame70PwmKind kKind = RuntimeSame70PwmKind::None;",
            "  static constexpr std::uint8_t kChannelCount = 0u;",
            "  static constexpr bool kSupportsDeadTime = false;",
            "  static constexpr bool kSupportsFaultInput = false;",
            "  static constexpr bool kSupportsDma = false;",
            "};",
            "",
        ]
    )

    _kind_token = {
        "pwm": "RuntimeSame70PwmKind::Pwm",
        "tc": "RuntimeSame70PwmKind::Tc",
    }

    for ctrl in device.same70_pwm_peripherals:
        kind_enum = _kind_token.get(ctrl.kind, "RuntimeSame70PwmKind::None")
        lines.extend(
            [
                "template<>",
                f"struct Same70PwmTraits<RuntimeSame70PwmId::{ctrl.controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr RuntimeSame70PwmKind kKind = {kind_enum};",
                f"  static constexpr std::uint8_t kChannelCount = {ctrl.channel_count}u;",
                f"  static constexpr bool kSupportsDeadTime = {'true' if ctrl.supports_dead_time else 'false'};",
                f"  static constexpr bool kSupportsFaultInput = {'true' if ctrl.supports_fault_input else 'false'};",
                f"  static constexpr bool kSupportsDma = {'true' if ctrl.supports_dma else 'false'};",
                "};",
                "",
            ]
        )
    return lines


# _i2c_peripheral_traits_block → runtime_driver/i2c.py


# _adc_peripheral_traits_block → runtime_driver/adc.py


# emit_runtime_driver_dma_semantics_header → runtime_driver/dma.py


def emit_runtime_driver_timer_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    timer_rows, channel_rows = _build_timer_rows(context)
    trait_lines = [
        "template<PeripheralId Id>",
        "struct TimerSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kCounterBits = 0u;",
        "  static constexpr std::uint32_t kChannelCount = 0u;",
        "  static constexpr bool kHasCompare = false;",
        "  static constexpr bool kHasCapture = false;",
        "  static constexpr bool kHasEncoder = false;",
        "  static constexpr bool kHasPwm = false;",
        "  static constexpr bool kHasOnePulse = false;",
        "  static constexpr bool kHasCenterAligned = false;",
        "  static constexpr bool kHasComplementaryOutputs = false;",
        "  static constexpr bool kHasDeadtime = false;",
        "  static constexpr bool kHasBreakInput = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateFlagField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockSourceField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).  TIMER
        # ships four split scalars (sentinel ``0xFFFFFFFFu``) plus the
        # de-duplicated union array.
        "  static constexpr std::uint32_t kUpdateIrqNumber = 0xFFFFFFFFu;",
        "  static constexpr std::uint32_t kCaptureIrqNumber = 0xFFFFFFFFu;",
        "  static constexpr std::uint32_t kBreakIrqNumber = 0xFFFFFFFFu;",
        "  static constexpr std::uint32_t kTriggerIrqNumber = 0xFFFFFFFFu;",
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        # DMA cross-references (add-peripheral-dma-cross-references).
        "  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};",
        # Tier 2/3/4 facts (add-timer-tier-2-3-4-data).
        "  static constexpr std::uint32_t kMaxPrescaler = 0u;",
        "  static constexpr std::uint32_t kMaxAutoReload = 0u;",
        "  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};",
        "  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};",
        "  static constexpr bool kSupportsDmaBurst = false;",
        "  static constexpr bool kSupportsRepetitionCounter = false;",
        "  static constexpr bool kSupportsXorInput = false;",
        "};",
        "",
    ]
    real_rows = [row for row in timer_rows if not row.is_stub]
    stub_rows = [row for row in timer_rows if row.is_stub]
    timer_peripheral_rows: list[str] = [
        f"  PeripheralId::{_enum_identifier(row.peripheral_name)},"
        for row in real_rows
    ]
    if real_rows:
        trait_lines.extend(_timer_lut_struct_lines())
        trait_lines.extend(_timer_lut_table_lines(context, real_rows))
        trait_lines.extend(_timer_traits_base_lines())
        for index, row in enumerate(real_rows):
            peripheral_id = _enum_identifier(row.peripheral_name)
            trait_lines.extend(
                [
                    "template<>",
                    f"struct TimerSemanticTraits<PeripheralId::{peripheral_id}> "
                    f": TimerTraitsBase<{index}> {{",
                    *_timer_per_instance_array_lines(row),
                    "};",
                    "",
                ]
            )
    specialization_builder = _timer_specialization_builder(context)
    for row in stub_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        row_lines = list(specialization_builder(row))
        bindings = getattr(row, "dma_bindings", None)
        if bindings is not None and not any("kDmaBindings = " in line for line in row_lines):
            row_lines.extend(_dma_binding_ref_array_lines(bindings))
        trait_lines.extend(
            [
                "template<>",
                f"struct TimerSemanticTraits<PeripheralId::{peripheral_id}> {{",
                *row_lines,
                "};",
                "",
            ]
        )
    typed_blocks = _build_timer_typed_enum_blocks(timer_rows)
    body = "\n".join(
        [
            *trait_lines,
            *_timer_channel_specialization_lines(channel_rows),
            *_std_array_lines(
                type_name="PeripheralId",
                variable_name="kTimerSemanticPeripherals",
                row_lines=timer_peripheral_rows,
            ),
            "",
            *_timer_controller_hw_traits_block(device),
            *(("",) if typed_blocks else ()),
            *typed_blocks,
        ]
    )
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstddef>",
            "#include <cstdint>",
            '#include "common.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            TIMER_DRIVER_HEADER,
        ),
        content=content,
    )


def emit_runtime_driver_pwm_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    """Emit ``pwm.hpp`` using the shared-LUT pattern introduced by
    ``reduce-cpp-header-bloat-via-shared-luts``.

    The per-instance trait specialisation now extends a shared
    ``PwmTraitsBase<N>`` template that pulls every scalar /
    register / field fact from a single
    ``inline constexpr std::array<PwmHardwareLut, N>`` table.
    The remaining per-instance body carries only the
    variable-length tier 2/3/4 arrays.  Public reading API
    (``PwmSemanticTraits<P>::kField``) stays byte-compatible
    with consumers thanks to template inheritance.
    """
    context = _context(device)
    pwm_rows, channel_rows = _build_pwm_rows(context)
    trait_lines = [
        "template<PeripheralId Id>",
        "struct PwmSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kCounterBits = 0u;",
        "  static constexpr std::uint32_t kChannelCount = 0u;",
        "  static constexpr bool kHasComplementaryOutputs = false;",
        "  static constexpr bool kHasDeadtime = false;",
        "  static constexpr bool kHasFaultInput = false;",
        "  static constexpr bool kHasCenterAligned = false;",
        "  static constexpr bool kHasSynchronizedUpdate = false;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kOutputEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSyncRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kLoadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearLoadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClockPrescalerField = kInvalidFieldRef;",
        # Tier 2/3/4 facts (add-pwm-tier-2-3-4-data).
        "  static constexpr std::uint32_t kMaxPrescaler = 0u;",
        "  static constexpr std::uint32_t kMaxPeriod = 0u;",
        "  static constexpr std::array<std::uint8_t, 0> kDeadtimeOptions = {};",
        "  static constexpr std::array<std::uint8_t, 0> kSupportedAlignments = {};",
        "  static constexpr std::array<std::uint8_t, 0> kBreakInputs = {};",
        "  static constexpr bool kSupportsDeadtime = false;",
        "  static constexpr bool kSupportsBreakInput = false;",
        "  static constexpr bool kSupportsComplementaryOutputs = false;",
        "  static constexpr bool kSupportsAsymmetricPwm = false;",
        "  static constexpr bool kSupportsCombinedPwm = false;",
        "};",
        "",
    ]
    # Real (non-stub) rows go through the LUT path; stubs keep
    # their bespoke kPresent=false specialisation since they
    # don't carry meaningful facts.
    real_rows = [row for row in pwm_rows if not row.is_stub]
    stub_rows = [row for row in pwm_rows if row.is_stub]
    pwm_peripheral_rows: list[str] = [
        f"  PeripheralId::{_enum_identifier(row.peripheral_name)},"
        for row in real_rows
    ]
    if real_rows:
        trait_lines.extend(_pwm_lut_struct_lines())
        trait_lines.extend(_pwm_lut_table_lines(context, real_rows))
        trait_lines.extend(_pwm_traits_base_lines(len(real_rows)))
        for index, row in enumerate(real_rows):
            peripheral_id = _enum_identifier(row.peripheral_name)
            trait_lines.extend(
                [
                    "template<>",
                    f"struct PwmSemanticTraits<PeripheralId::{peripheral_id}> "
                    f": PwmTraitsBase<{index}> {{",
                    *_pwm_per_instance_array_lines(row),
                    "};",
                    "",
                ]
            )
    specialization_builder = _pwm_specialization_builder(context)
    for row in stub_rows:
        peripheral_id = _enum_identifier(row.peripheral_name)
        trait_lines.extend(
            [
                "template<>",
                f"struct PwmSemanticTraits<PeripheralId::{peripheral_id}> {{",
                *specialization_builder(row),
                "};",
                "",
            ]
        )
    pwm_typed_blocks = _build_pwm_typed_enum_blocks(pwm_rows)
    body = "\n".join(
        [
            *trait_lines,
            *_pwm_channel_specialization_lines(channel_rows),
            *_std_array_lines(
                type_name="PeripheralId",
                variable_name="kPwmSemanticPeripherals",
                row_lines=pwm_peripheral_rows,
            ),
            "",
            *_pwm_slice_hw_traits_block(device),
            "",
            *_stm_timer_pwm_traits_block(device),
            "",
            *_mcpwm_traits_block(device),
            "",
            *_flex_pwm_traits_block(device),
            "",
            *_avr_da_tca_pwm_traits_block(device),
            "",
            *_same70_pwm_traits_block(device),
            *(("",) if pwm_typed_blocks else ()),
            *pwm_typed_blocks,
        ]
    )
    namespace_block = _cpp_namespace_block(
        (*_runtime_device_namespace_components(device), "driver_semantics"),
        body,
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstddef>",
            "#include <cstdint>",
            '#include "common.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            PWM_DRIVER_HEADER,
        ),
        content=content,
    )


# PIO emitter migrated to ``runtime_driver/pio.py`` —
# see top-of-file ``from .runtime_driver.pio import …`` re-export.

__all__ = [
    "emit_runtime_driver_adc_semantics_header",
    "emit_runtime_driver_can_semantics_header",
    "emit_runtime_driver_dac_semantics_header",
    "emit_runtime_driver_dma_semantics_header",
    "emit_runtime_driver_eth_semantics_header",
    "emit_runtime_driver_gpio_semantics_header",
    "emit_runtime_driver_i2c_semantics_header",
    "emit_runtime_driver_pio_semantics_header",
    "emit_runtime_driver_qspi_semantics_header",
    "emit_runtime_driver_sdmmc_semantics_header",
    "emit_runtime_driver_usb_semantics_header",
    "emit_runtime_driver_rtc_semantics_header",
    "emit_runtime_driver_semantics_common_header",
    "emit_runtime_driver_spi_semantics_header",
    "emit_runtime_driver_timer_semantics_header",
    "emit_runtime_driver_uart_semantics_header",
    "emit_runtime_driver_pwm_semantics_header",
    "emit_runtime_driver_watchdog_semantics_header",
    "runtime_driver_semantics_required_paths",
]
