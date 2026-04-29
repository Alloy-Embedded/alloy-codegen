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


# _build_timer_typed_enum_blocks → runtime_driver/timer.py


# _build_pwm_typed_enum_blocks → runtime_driver/pwm.py


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


# _timer_irq_lines → runtime_driver/timer.py


# _timer_irq_numbers_for_peripheral → runtime_driver/timer.py


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


# _st_timer_counter_bits → runtime_driver/timer.py


# _st_timer_row → runtime_driver/timer.py


# _st_timer_channel_rows → runtime_driver/timer.py


# _microchip_tc_timer_row → runtime_driver/timer.py


# _microchip_tc_timer_channel_rows → runtime_driver/timer.py


# _nxp_gpt_timer_row → runtime_driver/timer.py


# _nxp_gpt_timer_channel_rows → runtime_driver/timer.py


# _nxp_pit_timer_row → runtime_driver/timer.py


# _nxp_pit_timer_channel_rows → runtime_driver/timer.py


# _build_timer_rows → runtime_driver/timer.py


# _enrich_timer_tier234 → runtime_driver/timer.py


# _st_pwm_row → runtime_driver/pwm.py


# _st_pwm_channel_rows → runtime_driver/pwm.py


# _microchip_pwm_row → runtime_driver/pwm.py


# _microchip_pwm_channel_rows → runtime_driver/pwm.py


# _nxp_pwm_row → runtime_driver/pwm.py


# _nxp_pwm_channel_rows → runtime_driver/pwm.py


# _build_pwm_rows → runtime_driver/pwm.py


# _enrich_pwm_tier234 → runtime_driver/pwm.py


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


# _timer_specialization_builder → runtime_driver/timer.py


# _timer_tier234_lines → runtime_driver/timer.py


# _timer_channel_specialization_lines → runtime_driver/timer.py


# _pwm_specialization_builder → runtime_driver/pwm.py


# _timer_lut_struct_lines → runtime_driver/timer.py


# _timer_lut_table_lines → runtime_driver/timer.py


# _timer_traits_base_lines → runtime_driver/timer.py


# _timer_per_instance_array_lines → runtime_driver/timer.py


# _pwm_lut_struct_lines → runtime_driver/pwm.py


# _pwm_lut_table_lines → runtime_driver/pwm.py


# _pwm_traits_base_lines → runtime_driver/pwm.py


# _pwm_per_instance_array_lines → runtime_driver/pwm.py


# _pwm_tier234_lines → runtime_driver/pwm.py


# _pwm_channel_specialization_lines → runtime_driver/pwm.py


def emit_runtime_driver_semantics_common_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    return _emit_driver_semantics_common_header(family_dir=family_dir, device=device)


# emit_runtime_driver_gpio_semantics_header → runtime_driver/gpio.py


# _uart_peripheral_traits_block → runtime_driver/uart.py


# _dma_controller_hw_traits_block → runtime_driver/dma.py


# _timer_controller_hw_traits_block → runtime_driver/timer.py


# _pwm_slice_hw_traits_block → runtime_driver/pwm.py


# _flex_pwm_traits_block → runtime_driver/pwm.py


# _mcpwm_traits_block → runtime_driver/pwm.py


# _stm_timer_pwm_traits_block → runtime_driver/timer.py


# _avr_da_tca_pwm_traits_block → runtime_driver/pwm.py


# _same70_pwm_traits_block → runtime_driver/pwm.py


# emit_runtime_driver_timer_semantics_header → runtime_driver/timer.py


# emit_runtime_driver_pwm_semantics_header → runtime_driver/pwm.py


