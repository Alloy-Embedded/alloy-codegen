"""RTC (real-time clock) driver-semantic emitter.

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .common import (
    RuntimeFieldRef,
    RuntimeRegisterRef,
    _context,
    _emit_peripheral_semantics_header,
    _field_ref_expr,
    _invalid_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_field_ref_any,
    _resolve_register_ref,
    _resolve_register_ref_any,
    _schema_ref_expr,
    _SemanticContext,
)

RTC_DRIVER_HEADER = "driver_semantics/rtc.hpp"


@dataclass(frozen=True, slots=True)
class RtcSemanticRow:
    """RTC semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    has_calendar: bool
    has_alarm: bool
    has_write_protection: bool
    control_reg: RuntimeRegisterRef
    mode_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    time_reg: RuntimeRegisterRef
    date_reg: RuntimeRegisterRef
    alarm_time_reg: RuntimeRegisterRef
    alarm_date_reg: RuntimeRegisterRef
    interrupt_enable_reg: RuntimeRegisterRef
    interrupt_disable_reg: RuntimeRegisterRef
    interrupt_mask_reg: RuntimeRegisterRef
    clear_reg: RuntimeRegisterRef
    write_protect_reg: RuntimeRegisterRef
    prescaler_reg: RuntimeRegisterRef
    hour_mode_field: RuntimeFieldRef
    init_field: RuntimeFieldRef
    init_ready_field: RuntimeFieldRef
    shadow_bypass_field: RuntimeFieldRef
    update_time_field: RuntimeFieldRef
    update_calendar_field: RuntimeFieldRef
    update_ack_field: RuntimeFieldRef
    alarm_enable_field: RuntimeFieldRef
    alarm_interrupt_enable_field: RuntimeFieldRef
    second_interrupt_enable_field: RuntimeFieldRef
    time_event_interrupt_enable_field: RuntimeFieldRef
    calendar_event_interrupt_enable_field: RuntimeFieldRef
    status_alarm_field: RuntimeFieldRef
    status_second_field: RuntimeFieldRef
    status_time_event_field: RuntimeFieldRef
    status_calendar_event_field: RuntimeFieldRef
    status_tamper_error_field: RuntimeFieldRef
    clear_alarm_field: RuntimeFieldRef
    clear_second_field: RuntimeFieldRef
    clear_time_event_field: RuntimeFieldRef
    clear_calendar_event_field: RuntimeFieldRef
    clear_tamper_error_field: RuntimeFieldRef
    write_protect_key_field: RuntimeFieldRef
    write_protect_disable_key0: int
    write_protect_disable_key1: int
    write_protect_enable_key: int
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()


# WatchdogSemanticRow migrated to runtime_driver/watchdog.py
# (re-export at the bottom of this module).


# CanSemanticRow → runtime_driver/can.py


def _st_rtc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> RtcSemanticRow:
    status_register_names = ("ICSR", "ISR")
    clear_register_names = ("SCR",)
    return RtcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_calendar=True,
        has_alarm=True,
        has_write_protection=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        status_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
        ),
        time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TR",
        ),
        date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="DR",
        ),
        alarm_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ALRMAR",
        ),
        alarm_date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="ALRMBR",
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        interrupt_disable_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        interrupt_mask_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        clear_reg=_resolve_register_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
        ),
        write_protect_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WPR",
        ),
        prescaler_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PRER",
        ),
        hour_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("FMT",),
        ),
        init_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("INIT",),
        ),
        init_ready_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("INITF",),
        ),
        shadow_bypass_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("BYPSHAD",),
        ),
        update_time_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        update_calendar_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        update_ack_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        alarm_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("ALRAE",),
        ),
        alarm_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("ALRAIE",),
        ),
        second_interrupt_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        time_event_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("TSIE",),
        ),
        calendar_event_interrupt_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_alarm_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("ALRAF",),
        ),
        status_second_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_time_event_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("TSF",),
        ),
        status_calendar_event_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_tamper_error_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=status_register_names,
            field_names=("ITSF", "TAMP1F"),
        ),
        clear_alarm_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
            field_names=("CALRAF",),
        ),
        clear_second_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        clear_time_event_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
            field_names=("CTSF",),
        ),
        clear_calendar_event_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        clear_tamper_error_field=_resolve_field_ref_any(
            context,
            peripheral_name=peripheral_name,
            register_names=clear_register_names,
            field_names=("CITSF",),
        ),
        write_protect_key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WPR",
            field_names=("KEY",),
        ),
        write_protect_disable_key0=0xCA,
        write_protect_disable_key1=0x53,
        write_protect_enable_key=0xFF,
    )


def _microchip_rtc_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> RtcSemanticRow:
    return RtcSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_calendar=True,
        has_alarm=True,
        has_write_protection=False,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        mode_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TIMR",
        ),
        date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CALR",
        ),
        alarm_time_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TIMALR",
        ),
        alarm_date_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CALALR",
        ),
        interrupt_enable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
        ),
        interrupt_disable_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IDR",
        ),
        interrupt_mask_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IMR",
        ),
        clear_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
        ),
        write_protect_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        prescaler_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        hour_mode_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("HRMOD",),
        ),
        init_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        init_ready_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        shadow_bypass_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        update_time_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("UPDTIM",),
        ),
        update_calendar_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("UPDCAL",),
        ),
        update_ack_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("ACKUPD",),
        ),
        alarm_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        alarm_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("ALREN",),
        ),
        second_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("SECEN",),
        ),
        time_event_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("TIMEN",),
        ),
        calendar_event_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="IER",
            field_names=("CALEN",),
        ),
        status_alarm_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("ALARM",),
        ),
        status_second_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("SEC",),
        ),
        status_time_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TIMEV",),
        ),
        status_calendar_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("CALEV",),
        ),
        status_tamper_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("TDERR",),
        ),
        clear_alarm_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("ALRCLR",),
        ),
        clear_second_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("SECCLR",),
        ),
        clear_time_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("TIMCLR",),
        ),
        clear_calendar_event_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("CALCLR",),
        ),
        clear_tamper_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SCCR",
            field_names=("TDERRCLR",),
        ),
        write_protect_key_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        write_protect_disable_key0=0,
        write_protect_disable_key1=0,
        write_protect_enable_key=0,
    )


def _build_rtc_rows(context: _SemanticContext) -> tuple[RtcSemanticRow, ...]:
    rows: list[RtcSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("rtc", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.rtc.st-"):
            rows.append(
                _st_rtc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.rtc.microchip-"):
            rows.append(
                _microchip_rtc_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (RtcSemanticTraits<PeripheralId::) is satisfied for devices whose
            # RTC IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                RtcSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    has_calendar=False,
                    has_alarm=False,
                    has_write_protection=False,
                    control_reg=invalid_reg,
                    mode_reg=invalid_reg,
                    status_reg=invalid_reg,
                    time_reg=invalid_reg,
                    date_reg=invalid_reg,
                    alarm_time_reg=invalid_reg,
                    alarm_date_reg=invalid_reg,
                    interrupt_enable_reg=invalid_reg,
                    interrupt_disable_reg=invalid_reg,
                    interrupt_mask_reg=invalid_reg,
                    clear_reg=invalid_reg,
                    write_protect_reg=invalid_reg,
                    prescaler_reg=invalid_reg,
                    hour_mode_field=invalid_field,
                    init_field=invalid_field,
                    init_ready_field=invalid_field,
                    shadow_bypass_field=invalid_field,
                    update_time_field=invalid_field,
                    update_calendar_field=invalid_field,
                    update_ack_field=invalid_field,
                    alarm_enable_field=invalid_field,
                    alarm_interrupt_enable_field=invalid_field,
                    second_interrupt_enable_field=invalid_field,
                    time_event_interrupt_enable_field=invalid_field,
                    calendar_event_interrupt_enable_field=invalid_field,
                    status_alarm_field=invalid_field,
                    status_second_field=invalid_field,
                    status_time_event_field=invalid_field,
                    status_calendar_event_field=invalid_field,
                    status_tamper_error_field=invalid_field,
                    clear_alarm_field=invalid_field,
                    clear_second_field=invalid_field,
                    clear_time_event_field=invalid_field,
                    clear_calendar_event_field=invalid_field,
                    clear_tamper_error_field=invalid_field,
                    write_protect_key_field=invalid_field,
                    write_protect_disable_key0=0,
                    write_protect_disable_key1=0,
                    write_protect_enable_key=0,
                    is_stub=True,
                )
            )
    return tuple(rows)


# _mcan_register_ref → runtime_driver/can.py


# _mcan_field_ref → runtime_driver/can.py


# _mcan_common_can_row → runtime_driver/can.py


# _st_fdcan_can_row → runtime_driver/can.py


# _st_bxcan_can_row → runtime_driver/can.py


# _microchip_mcan_can_row → runtime_driver/can.py


# _nxp_flexcan_can_row → runtime_driver/can.py


# _build_can_rows → runtime_driver/can.py


def _rtc_specialization_builder(context: _SemanticContext):
    def _build(row: RtcSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr bool kHasCalendar = false;",
                "  static constexpr bool kHasAlarm = false;",
                "  static constexpr bool kHasWriteProtection = false;",
                "  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0u;",
                "  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0u;",
                "  static constexpr std::uint32_t kWriteProtectEnableKey = 0u;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTimeRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDateRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kAlarmTimeRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kAlarmDateRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kClearRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kWriteProtectRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kHourModeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kInitReadyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kShadowBypassField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateTimeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateCalendarField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kUpdateAckField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAlarmEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAlarmInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSecondInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTimeEventInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCalendarEventInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusAlarmField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusSecondField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusTimeEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusCalendarEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusTamperErrorField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearAlarmField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearSecondField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearTimeEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearCalendarEventField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kClearTamperErrorField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kWriteProtectKeyField = kInvalidFieldRef;",
                *_irq_numbers_lines(row.irq_numbers),
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kModeRegister": row.mode_reg,
            "kStatusRegister": row.status_reg,
            "kTimeRegister": row.time_reg,
            "kDateRegister": row.date_reg,
            "kAlarmTimeRegister": row.alarm_time_reg,
            "kAlarmDateRegister": row.alarm_date_reg,
            "kInterruptEnableRegister": row.interrupt_enable_reg,
            "kInterruptDisableRegister": row.interrupt_disable_reg,
            "kInterruptMaskRegister": row.interrupt_mask_reg,
            "kClearRegister": row.clear_reg,
            "kWriteProtectRegister": row.write_protect_reg,
            "kPrescalerRegister": row.prescaler_reg,
        }
        field_members = {
            "kHourModeField": row.hour_mode_field,
            "kInitField": row.init_field,
            "kInitReadyField": row.init_ready_field,
            "kShadowBypassField": row.shadow_bypass_field,
            "kUpdateTimeField": row.update_time_field,
            "kUpdateCalendarField": row.update_calendar_field,
            "kUpdateAckField": row.update_ack_field,
            "kAlarmEnableField": row.alarm_enable_field,
            "kAlarmInterruptEnableField": row.alarm_interrupt_enable_field,
            "kSecondInterruptEnableField": row.second_interrupt_enable_field,
            "kTimeEventInterruptEnableField": row.time_event_interrupt_enable_field,
            "kCalendarEventInterruptEnableField": row.calendar_event_interrupt_enable_field,
            "kStatusAlarmField": row.status_alarm_field,
            "kStatusSecondField": row.status_second_field,
            "kStatusTimeEventField": row.status_time_event_field,
            "kStatusCalendarEventField": row.status_calendar_event_field,
            "kStatusTamperErrorField": row.status_tamper_error_field,
            "kClearAlarmField": row.clear_alarm_field,
            "kClearSecondField": row.clear_second_field,
            "kClearTimeEventField": row.clear_time_event_field,
            "kClearCalendarEventField": row.clear_calendar_event_field,
            "kClearTamperErrorField": row.clear_tamper_error_field,
            "kWriteProtectKeyField": row.write_protect_key_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kHasCalendar = {'true' if row.has_calendar else 'false'};",
            f"  static constexpr bool kHasAlarm = {'true' if row.has_alarm else 'false'};",
            "  static constexpr bool kHasWriteProtection = "
            + ("true" if row.has_write_protection else "false")
            + ";",
            f"  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0x{row.write_protect_disable_key0:08X}u;",
            f"  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0x{row.write_protect_disable_key1:08X}u;",
            f"  static constexpr std::uint32_t kWriteProtectEnableKey = 0x{row.write_protect_enable_key:08X}u;",
        ]
        lines.extend(
            f"  static constexpr RuntimeRegisterRef {name} = {_register_ref_expr(value)};"
            for name, value in register_members.items()
        )
        lines.extend(
            f"  static constexpr RuntimeFieldRef {name} = {_field_ref_expr(value)};"
            for name, value in field_members.items()
        )
        lines.extend(_irq_numbers_lines(row.irq_numbers))
        return lines

    return _build


# _watchdog_specialization_builder → runtime_driver/watchdog.py


# _can_specialization_builder → runtime_driver/can.py


def emit_runtime_driver_rtc_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_rtc_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kHasCalendar = false;",
        "  static constexpr bool kHasAlarm = false;",
        "  static constexpr bool kHasWriteProtection = false;",
        "  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0u;",
        "  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0u;",
        "  static constexpr std::uint32_t kWriteProtectEnableKey = 0u;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTimeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDateRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kAlarmTimeRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kAlarmDateRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kClearRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kWriteProtectRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kHourModeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kInitReadyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kShadowBypassField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateTimeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateCalendarField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kUpdateAckField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAlarmEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAlarmInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSecondInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTimeEventInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCalendarEventInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusAlarmField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusSecondField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusTimeEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusCalendarEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusTamperErrorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearAlarmField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearSecondField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearTimeEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearCalendarEventField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kClearTamperErrorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWriteProtectKeyField = kInvalidFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=RTC_DRIVER_HEADER,
        trait_name="RtcSemanticTraits",
        array_name="kRtcSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_rtc_specialization_builder(context),
    )


# emit_runtime_driver_can_semantics_header → runtime_driver/can.py


__all__ = [
    "RTC_DRIVER_HEADER",
    "RtcSemanticRow",
    "emit_runtime_driver_rtc_semantics_header",
]
