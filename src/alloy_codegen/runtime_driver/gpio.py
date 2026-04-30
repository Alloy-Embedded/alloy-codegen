"""GPIO driver-semantic emitter (STM32 / Microchip / NXP).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR, GpioPinDescriptor
from alloy_codegen.reporting import EmittedArtifact

from ..emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _std_array_lines,
)
from ..runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)
from .common import (
    RuntimeFieldRef,
    _context,
    _field_ref_expr,
    _invalid_field_ref,
    _line_index_from_candidate,
    _peripheral_ref,
    _resolve_field_ref,
    _schema_ref_expr,
    _SemanticContext,
)

GPIO_DRIVER_HEADER = "driver_semantics/gpio.hpp"


@dataclass(frozen=True, slots=True)
class GpioSemanticRow:
    """GPIO semantic trait payload keyed by pin."""

    pin_name: str
    peripheral_name: str
    schema_id: str
    line_index: int
    mode_field: RuntimeFieldRef
    direction_field: RuntimeFieldRef
    output_type_field: RuntimeFieldRef
    pull_field: RuntimeFieldRef
    speed_field: RuntimeFieldRef
    input_field: RuntimeFieldRef
    output_value_field: RuntimeFieldRef
    output_set_field: RuntimeFieldRef
    output_reset_field: RuntimeFieldRef
    pio_enable_field: RuntimeFieldRef
    pio_output_enable_field: RuntimeFieldRef
    pio_output_disable_field: RuntimeFieldRef
    pio_set_field: RuntimeFieldRef
    pio_clear_field: RuntimeFieldRef
    pio_input_state_field: RuntimeFieldRef
    pio_drive_enable_field: RuntimeFieldRef
    pio_drive_disable_field: RuntimeFieldRef
    pio_pull_up_enable_field: RuntimeFieldRef
    pio_pull_up_disable_field: RuntimeFieldRef
    pio_pull_down_enable_field: RuntimeFieldRef
    pio_pull_down_disable_field: RuntimeFieldRef


def _st_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MODER",
            field_names=(f"MODE{line_index}", f"MODER{line_index}"),
            fallback_register_offset=0x00,
            fallback_bit_offset=line_index * 2,
            fallback_bit_width=2,
        ),
        direction_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        output_type_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="OTYPER",
            field_names=(f"OT{line_index}", f"OT_{line_index}", f"OT{line_index}"),
            fallback_register_offset=0x04,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        pull_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PUPDR",
            field_names=(f"PUPD{line_index}", f"PUPDR{line_index}"),
            fallback_register_offset=0x0C,
            fallback_bit_offset=line_index * 2,
            fallback_bit_width=2,
        ),
        speed_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="OSPEEDR",
            field_names=(f"OSPEED{line_index}", f"OSPEEDR{line_index}"),
            fallback_register_offset=0x08,
            fallback_bit_offset=line_index * 2,
            fallback_bit_width=2,
        ),
        input_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
            field_names=(f"IDR{line_index}", f"ID{line_index}"),
            fallback_register_offset=0x10,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_value_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ODR",
            field_names=(f"ODR{line_index}", f"OD{line_index}"),
            fallback_register_offset=0x14,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_set_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BSRR",
            field_names=(f"BS{line_index}",),
            fallback_register_offset=0x18,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_reset_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="BSRR",
            field_names=(f"BR{line_index}",),
            fallback_register_offset=0x18,
            fallback_bit_offset=16 + line_index,
            fallback_bit_width=1,
        ),
        pio_enable_field=_invalid_field_ref(),
        pio_output_enable_field=_invalid_field_ref(),
        pio_output_disable_field=_invalid_field_ref(),
        pio_set_field=_invalid_field_ref(),
        pio_clear_field=_invalid_field_ref(),
        pio_input_state_field=_invalid_field_ref(),
        pio_drive_enable_field=_invalid_field_ref(),
        pio_drive_disable_field=_invalid_field_ref(),
        pio_pull_up_enable_field=_invalid_field_ref(),
        pio_pull_up_disable_field=_invalid_field_ref(),
        pio_pull_down_enable_field=_invalid_field_ref(),
        pio_pull_down_disable_field=_invalid_field_ref(),
    )


def _microchip_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    field_name = f"P{line_index}"

    def pio(register_name: str, offset: int) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=offset,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        )

    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_invalid_field_ref(),
        direction_field=_invalid_field_ref(),
        output_type_field=_invalid_field_ref(),
        pull_field=_invalid_field_ref(),
        speed_field=_invalid_field_ref(),
        input_field=_invalid_field_ref(),
        output_value_field=_invalid_field_ref(),
        output_set_field=_invalid_field_ref(),
        output_reset_field=_invalid_field_ref(),
        pio_enable_field=pio("PER", 0x000),
        pio_output_enable_field=pio("OER", 0x010),
        pio_output_disable_field=pio("ODR", 0x014),
        pio_set_field=pio("SODR", 0x030),
        pio_clear_field=pio("CODR", 0x034),
        pio_input_state_field=pio("PDSR", 0x03C),
        pio_drive_enable_field=pio("MDER", 0x050),
        pio_drive_disable_field=pio("MDDR", 0x054),
        pio_pull_up_enable_field=pio("PUER", 0x064),
        pio_pull_up_disable_field=pio("PUDR", 0x060),
        pio_pull_down_enable_field=pio("PPDER", 0x094),
        pio_pull_down_disable_field=pio("PPDDR", 0x090),
    )


def _nxp_gpio_semantics(
    context: _SemanticContext,
    *,
    pin_name: str,
    peripheral_name: str,
    schema_id: str,
    line_index: int,
) -> GpioSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address
    return GpioSemanticRow(
        pin_name=pin_name,
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        line_index=line_index,
        mode_field=_invalid_field_ref(base),
        direction_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="GDIR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x04,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_type_field=_invalid_field_ref(base),
        pull_field=_invalid_field_ref(base),
        speed_field=_invalid_field_ref(base),
        input_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PSR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x08,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_value_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DR",
            field_names=("DATA", f"IO{line_index:02d}"),
            fallback_register_offset=0x00,
            fallback_bit_offset=line_index,
            fallback_bit_width=1,
        ),
        output_set_field=_invalid_field_ref(base),
        output_reset_field=_invalid_field_ref(base),
        pio_enable_field=_invalid_field_ref(base),
        pio_output_enable_field=_invalid_field_ref(base),
        pio_output_disable_field=_invalid_field_ref(base),
        pio_set_field=_invalid_field_ref(base),
        pio_clear_field=_invalid_field_ref(base),
        pio_input_state_field=_invalid_field_ref(base),
        pio_drive_enable_field=_invalid_field_ref(base),
        pio_drive_disable_field=_invalid_field_ref(base),
        pio_pull_up_enable_field=_invalid_field_ref(base),
        pio_pull_up_disable_field=_invalid_field_ref(base),
        pio_pull_down_enable_field=_invalid_field_ref(base),
        pio_pull_down_disable_field=_invalid_field_ref(base),
    )


def _build_gpio_rows(context: _SemanticContext) -> tuple[GpioSemanticRow, ...]:
    rows: list[GpioSemanticRow] = []
    for pin_name, candidate in sorted(context.gpio_candidate_by_pin.items()):
        peripheral = context.peripheral_by_name.get(candidate.peripheral)
        if peripheral is None or peripheral.backend_schema_id is None:
            continue
        line_index = _line_index_from_candidate(context, candidate)
        if line_index is None:
            continue
        schema_id = peripheral.backend_schema_id
        if schema_id in {
            "alloy.gpio.st-stm32g07x-gpio-v1-0",
            "alloy.gpio.st-stm32f4x-gpio-v1-0",
        }:
            rows.append(
                _st_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
        elif schema_id == "alloy.gpio.microchip-pio-v":
            rows.append(
                _microchip_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
        elif schema_id == "alloy.gpio.nxp-imxrt-gpio-v1":
            rows.append(
                _nxp_gpio_semantics(
                    context,
                    pin_name=pin_name,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    line_index=line_index,
                )
            )
    return tuple(rows)


def _emit_gpio_semantics_header(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    context = _context(device)
    rows = _build_gpio_rows(context)
    # Map from PinId enum identifier → AF descriptor list, for the pin-AF
    # specializations contributed by ``fill-gpio-semantic-gaps``.
    af_pins_by_id: dict[str, GpioPinDescriptor] = {
        _enum_identifier(pin.pin_id): pin for pin in device.gpio_pins
    }
    trait_lines = [
        "template<PinId Id>",
        "struct GpioSemanticTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr std::uint32_t kLineIndex = 0u;",
        "  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputTypeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPullField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInputField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputValueField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;",
        # Alternate-function topology (added by fill-gpio-semantic-gaps).
        "  static constexpr std::uint32_t kPortOffset = 0u;",
        "  static constexpr std::uint32_t kPinIndex = 0u;",
        "  static constexpr std::uint8_t kMaxAltFunction = 0u;",
        "  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};",
        "  static constexpr bool kIsInputOnly = false;",
        "};",
        "",
    ]

    def _af_lines(pin: GpioPinDescriptor | None) -> list[str]:
        if pin is None:
            return [
                "  static constexpr std::uint32_t kPortOffset = 0u;",
                "  static constexpr std::uint32_t kPinIndex = 0u;",
                "  static constexpr std::uint8_t kMaxAltFunction = 0u;",
                "  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};",
                "  static constexpr bool kIsInputOnly = false;",
            ]
        is_input_only = "true" if pin.is_input_only else "false"
        if not pin.alt_functions:
            return [
                f"  static constexpr std::uint32_t kPortOffset = {pin.port_offset:#010x}u;",
                f"  static constexpr std::uint32_t kPinIndex = {pin.pin_index}u;",
                "  static constexpr std::uint8_t kMaxAltFunction = 0u;",
                "  static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};",
                f"  static constexpr bool kIsInputOnly = {is_input_only};",
            ]
        af_numbers = sorted({af.af_number for af in pin.alt_functions})
        af_array = ", ".join(f"{n}u" for n in af_numbers)
        return [
            f"  static constexpr std::uint32_t kPortOffset = {pin.port_offset:#010x}u;",
            f"  static constexpr std::uint32_t kPinIndex = {pin.pin_index}u;",
            f"  static constexpr std::uint8_t kMaxAltFunction = {max(af_numbers)}u;",
            (
                f"  static constexpr std::array<std::uint8_t, {len(af_numbers)}> "
                f"kValidAltFunctions = {{{{{af_array}}}}};"
            ),
            f"  static constexpr bool kIsInputOnly = {is_input_only};",
        ]

    pin_rows: list[str] = []
    consumed_pin_ids: set[str] = set()
    for row in rows:
        pin_id = _enum_identifier(row.pin_name)
        consumed_pin_ids.add(pin_id)
        trait_lines.extend(
            [
                "template<>",
                f"struct GpioSemanticTraits<PinId::{pin_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr PeripheralId kPeripheralId = {_peripheral_ref(row.peripheral_name)};",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                f"  static constexpr std::uint32_t kLineIndex = {row.line_index}u;",
                f"  static constexpr RuntimeFieldRef kModeField = {_field_ref_expr(row.mode_field)};",
                f"  static constexpr RuntimeFieldRef kDirectionField = {_field_ref_expr(row.direction_field)};",
                f"  static constexpr RuntimeFieldRef kOutputTypeField = {_field_ref_expr(row.output_type_field)};",
                f"  static constexpr RuntimeFieldRef kPullField = {_field_ref_expr(row.pull_field)};",
                f"  static constexpr RuntimeFieldRef kSpeedField = {_field_ref_expr(row.speed_field)};",
                f"  static constexpr RuntimeFieldRef kInputField = {_field_ref_expr(row.input_field)};",
                f"  static constexpr RuntimeFieldRef kOutputValueField = {_field_ref_expr(row.output_value_field)};",
                f"  static constexpr RuntimeFieldRef kOutputSetField = {_field_ref_expr(row.output_set_field)};",
                f"  static constexpr RuntimeFieldRef kOutputResetField = {_field_ref_expr(row.output_reset_field)};",
                f"  static constexpr RuntimeFieldRef kPioEnableField = {_field_ref_expr(row.pio_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioOutputEnableField = {_field_ref_expr(row.pio_output_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioOutputDisableField = {_field_ref_expr(row.pio_output_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioSetField = {_field_ref_expr(row.pio_set_field)};",
                f"  static constexpr RuntimeFieldRef kPioClearField = {_field_ref_expr(row.pio_clear_field)};",
                f"  static constexpr RuntimeFieldRef kPioInputStateField = {_field_ref_expr(row.pio_input_state_field)};",
                f"  static constexpr RuntimeFieldRef kPioDriveEnableField = {_field_ref_expr(row.pio_drive_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioDriveDisableField = {_field_ref_expr(row.pio_drive_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullUpEnableField = {_field_ref_expr(row.pio_pull_up_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullUpDisableField = {_field_ref_expr(row.pio_pull_up_disable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullDownEnableField = {_field_ref_expr(row.pio_pull_down_enable_field)};",
                f"  static constexpr RuntimeFieldRef kPioPullDownDisableField = {_field_ref_expr(row.pio_pull_down_disable_field)};",
                *_af_lines(af_pins_by_id.get(pin_id)),
                "};",
                "",
            ]
        )
        pin_rows.append(f"  PinId::{pin_id},")

    # AF-only specializations: pins that have alt-function topology but no
    # register-level GPIO row.  On STM32 (where no GPIO connection_candidates
    # are produced today) we still resolve the four Tier-1 register fields —
    # ``MODER``/``OSPEEDR``/``OTYPER``/``PUPDR`` — by deriving the
    # peripheral name from the pin's port letter and looking up the field via
    # the standard fallbacks.  The ``fill-gpio-tier-1-fields`` change makes
    # those compile-time references valid on STM32 instead of
    # `kInvalidFieldRef`, so the alloy GPIO HAL can synthesise register
    # writes without falling back to vendor headers.
    def _stm32_tier1_fields(pin: GpioPinDescriptor) -> tuple[RuntimeFieldRef, ...]:
        port_letter = pin.pin_id[1:2] if len(pin.pin_id) >= 2 else ""
        peripheral_name = f"GPIO{port_letter}"
        peripheral = context.peripheral_by_name.get(peripheral_name)
        if peripheral is None or peripheral.backend_schema_id is None:
            return (
                _invalid_field_ref(),
                _invalid_field_ref(),
                _invalid_field_ref(),
                _invalid_field_ref(),
            )
        if not peripheral.backend_schema_id.startswith("alloy.gpio.st-"):
            return (
                _invalid_field_ref(peripheral.base_address),
                _invalid_field_ref(peripheral.base_address),
                _invalid_field_ref(peripheral.base_address),
                _invalid_field_ref(peripheral.base_address),
            )
        idx = pin.pin_index
        return (
            _resolve_field_ref(
                context,
                peripheral_name=peripheral_name,
                register_name="MODER",
                field_names=(f"MODE{idx}", f"MODER{idx}"),
                fallback_register_offset=0x00,
                fallback_bit_offset=idx * 2,
                fallback_bit_width=2,
            ),
            _resolve_field_ref(
                context,
                peripheral_name=peripheral_name,
                register_name="OSPEEDR",
                field_names=(f"OSPEED{idx}", f"OSPEEDR{idx}"),
                fallback_register_offset=0x08,
                fallback_bit_offset=idx * 2,
                fallback_bit_width=2,
            ),
            _resolve_field_ref(
                context,
                peripheral_name=peripheral_name,
                register_name="OTYPER",
                field_names=(f"OT{idx}", f"OT_{idx}"),
                fallback_register_offset=0x04,
                fallback_bit_offset=idx,
                fallback_bit_width=1,
            ),
            _resolve_field_ref(
                context,
                peripheral_name=peripheral_name,
                register_name="PUPDR",
                field_names=(f"PUPD{idx}", f"PUPDR{idx}"),
                fallback_register_offset=0x0C,
                fallback_bit_offset=idx * 2,
                fallback_bit_width=2,
            ),
        )

    for pin_id, pin in sorted(af_pins_by_id.items()):
        if pin_id in consumed_pin_ids:
            continue
        mode_f, speed_f, otype_f, pull_f = _stm32_tier1_fields(pin)
        trait_lines.extend(
            [
                "template<>",
                f"struct GpioSemanticTraits<PinId::{pin_id}> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
                "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
                "  static constexpr std::uint32_t kLineIndex = 0u;",
                f"  static constexpr RuntimeFieldRef kModeField = {_field_ref_expr(mode_f)};",
                "  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;",
                f"  static constexpr RuntimeFieldRef kOutputTypeField = {_field_ref_expr(otype_f)};",
                f"  static constexpr RuntimeFieldRef kPullField = {_field_ref_expr(pull_f)};",
                f"  static constexpr RuntimeFieldRef kSpeedField = {_field_ref_expr(speed_f)};",
                "  static constexpr RuntimeFieldRef kInputField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOutputValueField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOutputSetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kOutputResetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioOutputEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioOutputDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioSetField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioClearField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioInputStateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioDriveEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioDriveDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullUpEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullUpDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullDownEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPioPullDownDisableField = kInvalidFieldRef;",
                *_af_lines(pin),
                "};",
                "",
            ]
        )
        pin_rows.append(f"  PinId::{pin_id},")
    body = "\n".join(
        [
            *trait_lines,
            *_std_array_lines(
                type_name="PinId", variable_name="kGpioSemanticPins", row_lines=pin_rows
            ),
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
            "#include <cstdint>",
            '#include "common.hpp"',
            '#include "../pins.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, GPIO_DRIVER_HEADER),
        content=content,
    )


# _emit_peripheral_semantics_header moved to runtime_driver/common.py.


def emit_runtime_driver_gpio_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    return _emit_gpio_semantics_header(family_dir=family_dir, device=device)


__all__ = [
    "GPIO_DRIVER_HEADER",
    "GpioSemanticRow",
    "emit_runtime_driver_gpio_semantics_header",
]
