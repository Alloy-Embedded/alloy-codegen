"""Watchdog driver-semantic emitter.

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.

Covers ATSAM (WDT/RSWDT), STM32 (IWDG/WWDG) and NXP
(WDOG/RTWDOG) controllers.  Unknown schemas drop in as
``is_stub`` rows so the artifact contract still emits a
specialisation.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .common import (
    RuntimeFieldRef,
    RuntimeRegisterRef,
    _SemanticContext,
    _context,
    _emit_peripheral_semantics_header,
    _field_ref_expr,
    _invalid_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _register_ref_expr,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
)

WATCHDOG_DRIVER_HEADER = "driver_semantics/watchdog.hpp"


@dataclass(frozen=True, slots=True)
class WatchdogSemanticRow:
    """Watchdog semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    has_window: bool
    control_reg: RuntimeRegisterRef
    config_reg: RuntimeRegisterRef
    status_reg: RuntimeRegisterRef
    prescaler_reg: RuntimeRegisterRef
    reload_reg: RuntimeRegisterRef
    window_reg: RuntimeRegisterRef
    enable_field: RuntimeFieldRef
    disable_field: RuntimeFieldRef
    restart_field: RuntimeFieldRef
    key_field: RuntimeFieldRef
    timeout_field: RuntimeFieldRef
    window_field: RuntimeFieldRef
    prescaler_field: RuntimeFieldRef
    early_warning_interrupt_enable_field: RuntimeFieldRef
    reset_enable_field: RuntimeFieldRef
    status_prescaler_update_field: RuntimeFieldRef
    status_reload_update_field: RuntimeFieldRef
    status_window_update_field: RuntimeFieldRef
    status_timeout_field: RuntimeFieldRef
    status_error_field: RuntimeFieldRef
    required_config_field: RuntimeFieldRef
    required_config_value: int
    start_key_value: int
    refresh_key_value: int
    unlock_key_value: int
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()


def _microchip_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    is_reinforced = peripheral_name == "RSWDT"
    required_config_field = (
        _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("ALLONES",),
        )
        if is_reinforced
        else _invalid_field_ref()
    )
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=not is_reinforced,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        prescaler_reg=_invalid_register_ref(),
        reload_reg=_invalid_register_ref(),
        window_reg=_invalid_register_ref(),
        enable_field=_invalid_field_ref(),
        disable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDDIS",),
        ),
        restart_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("WDRSTT",),
        ),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("KEY",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDV",),
        ),
        window_field=(
            _resolve_field_ref(
                context,
                peripheral_name=peripheral_name,
                register_name="MR",
                field_names=("WDD",),
            )
            if not is_reinforced
            else _invalid_field_ref()
        ),
        prescaler_field=_invalid_field_ref(),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDFIEN",),
        ),
        reset_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="MR",
            field_names=("WDRSTEN",),
        ),
        status_prescaler_update_field=_invalid_field_ref(),
        status_reload_update_field=_invalid_field_ref(),
        status_window_update_field=_invalid_field_ref(),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("WDUNF",),
        ),
        status_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("WDERR",),
        ),
        required_config_field=required_config_field,
        required_config_value=0xFFF if is_reinforced else 0,
        start_key_value=0,
        refresh_key_value=0xC4 if is_reinforced else 0xA5,
        unlock_key_value=0,
    )


def _nxp_wdog_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WRSR",
        ),
        prescaler_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        reload_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WSR",
        ),
        window_reg=_invalid_register_ref(context.peripheral_by_name[peripheral_name].base_address),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("WDE",),
        ),
        disable_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        restart_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WSR",
            field_names=("WSR",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("WT",),
        ),
        window_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("WDW",),
        ),
        prescaler_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WICR",
            field_names=("WIE",),
        ),
        reset_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WCR",
            field_names=("SRS",),
        ),
        status_prescaler_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_reload_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_window_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WRSR",
            field_names=("TOUT",),
        ),
        status_error_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WRSR",
            field_names=("SFTW",),
        ),
        required_config_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        required_config_value=0,
        start_key_value=0,
        refresh_key_value=0x5555,
        unlock_key_value=0xC520,
    )


def _nxp_rtwdog_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
        ),
        prescaler_reg=_invalid_register_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        reload_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TOVAL",
        ),
        window_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WIN",
        ),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("EN",),
        ),
        disable_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        restart_field=_invalid_field_ref(context.peripheral_by_name[peripheral_name].base_address),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CNT",
            field_names=("CNTLOW",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="TOVAL",
            field_names=("TOVALLOW",),
        ),
        window_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WIN",
            field_names=("WINLOW",),
        ),
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("PRES",),
        ),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("INT",),
        ),
        reset_enable_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_prescaler_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_reload_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_window_update_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("FLG",),
        ),
        status_error_field=_invalid_field_ref(
            context.peripheral_by_name[peripheral_name].base_address
        ),
        required_config_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CS",
            field_names=("UPDATE",),
        ),
        required_config_value=1,
        start_key_value=0,
        refresh_key_value=0xA602,
        unlock_key_value=0xC520,
    )


def _st_iwdg_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    window_field = _resolve_field_ref(
        context,
        peripheral_name=peripheral_name,
        register_name="WINR",
        field_names=("WIN",),
    )
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=window_field.valid,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="KR",
        ),
        config_reg=_invalid_register_ref(),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        prescaler_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PR",
        ),
        reload_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RLR",
        ),
        window_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="WINR",
        ),
        enable_field=_invalid_field_ref(),
        disable_field=_invalid_field_ref(),
        restart_field=_invalid_field_ref(),
        key_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="KR",
            field_names=("KEY",),
        ),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="RLR",
            field_names=("RL",),
        ),
        window_field=window_field,
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="PR",
            field_names=("PR",),
        ),
        early_warning_interrupt_enable_field=_invalid_field_ref(),
        reset_enable_field=_invalid_field_ref(),
        status_prescaler_update_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("PVU",),
        ),
        status_reload_update_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("RVU",),
        ),
        status_window_update_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("WVU",),
        ),
        status_timeout_field=_invalid_field_ref(),
        status_error_field=_invalid_field_ref(),
        required_config_field=_invalid_field_ref(),
        required_config_value=0,
        start_key_value=0xCCCC,
        refresh_key_value=0xAAAA,
        unlock_key_value=0x5555,
    )


def _st_wwdg_watchdog_row(
    context: _SemanticContext,
    *,
    peripheral_name: str,
    schema_id: str,
) -> WatchdogSemanticRow:
    return WatchdogSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        has_window=True,
        control_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
        ),
        config_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
        ),
        status_reg=_resolve_register_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
        ),
        prescaler_reg=_invalid_register_ref(),
        reload_reg=_invalid_register_ref(),
        window_reg=_invalid_register_ref(),
        enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("WDGA",),
        ),
        disable_field=_invalid_field_ref(),
        restart_field=_invalid_field_ref(),
        key_field=_invalid_field_ref(),
        timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CR",
            field_names=("T",),
        ),
        window_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
            field_names=("W",),
        ),
        prescaler_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
            field_names=("WDGTB",),
            fallback_register_offset=0x04,
            fallback_bit_offset=7,
            fallback_bit_width=2,
        ),
        early_warning_interrupt_enable_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="CFR",
            field_names=("EWI",),
        ),
        reset_enable_field=_invalid_field_ref(),
        status_prescaler_update_field=_invalid_field_ref(),
        status_reload_update_field=_invalid_field_ref(),
        status_window_update_field=_invalid_field_ref(),
        status_timeout_field=_resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name="SR",
            field_names=("EWIF",),
        ),
        status_error_field=_invalid_field_ref(),
        required_config_field=_invalid_field_ref(),
        required_config_value=0,
        start_key_value=0,
        refresh_key_value=0,
        unlock_key_value=0,
    )


def _build_watchdog_rows(context: _SemanticContext) -> tuple[WatchdogSemanticRow, ...]:
    rows: list[WatchdogSemanticRow] = []
    for peripheral in context.runtime_peripherals_by_class.get("watchdog", ()):
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.watchdog.microchip-"):
            rows.append(
                _microchip_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.watchdog.st-iwdg"):
            rows.append(
                _st_iwdg_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id.startswith("alloy.watchdog.st-wwdg"):
            rows.append(
                _st_wwdg_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.watchdog.nxp-wdog":
            rows.append(
                _nxp_wdog_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        elif schema_id == "alloy.watchdog.nxp-rtwdog":
            rows.append(
                _nxp_rtwdog_watchdog_row(
                    context,
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                )
            )
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (WatchdogSemanticTraits<PeripheralId::) is satisfied for devices whose
            # Watchdog IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                WatchdogSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    has_window=False,
                    control_reg=invalid_reg,
                    config_reg=invalid_reg,
                    status_reg=invalid_reg,
                    prescaler_reg=invalid_reg,
                    reload_reg=invalid_reg,
                    window_reg=invalid_reg,
                    enable_field=invalid_field,
                    disable_field=invalid_field,
                    restart_field=invalid_field,
                    key_field=invalid_field,
                    timeout_field=invalid_field,
                    window_field=invalid_field,
                    prescaler_field=invalid_field,
                    early_warning_interrupt_enable_field=invalid_field,
                    reset_enable_field=invalid_field,
                    status_prescaler_update_field=invalid_field,
                    status_reload_update_field=invalid_field,
                    status_window_update_field=invalid_field,
                    status_timeout_field=invalid_field,
                    status_error_field=invalid_field,
                    required_config_field=invalid_field,
                    required_config_value=0,
                    start_key_value=0,
                    refresh_key_value=0,
                    unlock_key_value=0,
                    is_stub=True,
                )
            )
    return tuple(rows)


def _watchdog_specialization_builder(context: _SemanticContext):
    def _build(row: WatchdogSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr bool kHasWindow = false;",
                "  static constexpr std::uint32_t kRequiredConfigValue = 0u;",
                "  static constexpr std::uint32_t kStartKeyValue = 0u;",
                "  static constexpr std::uint32_t kRefreshKeyValue = 0u;",
                "  static constexpr std::uint32_t kUnlockKeyValue = 0u;",
                "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kReloadRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kWindowRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRestartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kKeyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTimeoutField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kWindowField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kEarlyWarningInterruptEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kResetEnableField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusPrescalerUpdateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusReloadUpdateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusWindowUpdateField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusTimeoutField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStatusErrorField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRequiredConfigField = kInvalidFieldRef;",
                *_irq_numbers_lines(row.irq_numbers),
            ]
        register_members = {
            "kControlRegister": row.control_reg,
            "kConfigRegister": row.config_reg,
            "kStatusRegister": row.status_reg,
            "kPrescalerRegister": row.prescaler_reg,
            "kReloadRegister": row.reload_reg,
            "kWindowRegister": row.window_reg,
        }
        field_members = {
            "kEnableField": row.enable_field,
            "kDisableField": row.disable_field,
            "kRestartField": row.restart_field,
            "kKeyField": row.key_field,
            "kTimeoutField": row.timeout_field,
            "kWindowField": row.window_field,
            "kPrescalerField": row.prescaler_field,
            "kEarlyWarningInterruptEnableField": row.early_warning_interrupt_enable_field,
            "kResetEnableField": row.reset_enable_field,
            "kStatusPrescalerUpdateField": row.status_prescaler_update_field,
            "kStatusReloadUpdateField": row.status_reload_update_field,
            "kStatusWindowUpdateField": row.status_window_update_field,
            "kStatusTimeoutField": row.status_timeout_field,
            "kStatusErrorField": row.status_error_field,
            "kRequiredConfigField": row.required_config_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
            f"  static constexpr bool kHasWindow = {'true' if row.has_window else 'false'};",
            f"  static constexpr std::uint32_t kRequiredConfigValue = 0x{row.required_config_value:08X}u;",
            f"  static constexpr std::uint32_t kStartKeyValue = 0x{row.start_key_value:08X}u;",
            f"  static constexpr std::uint32_t kRefreshKeyValue = 0x{row.refresh_key_value:08X}u;",
            f"  static constexpr std::uint32_t kUnlockKeyValue = 0x{row.unlock_key_value:08X}u;",
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


def emit_runtime_driver_watchdog_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_watchdog_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr bool kHasWindow = false;",
        "  static constexpr std::uint32_t kRequiredConfigValue = 0u;",
        "  static constexpr std::uint32_t kStartKeyValue = 0u;",
        "  static constexpr std::uint32_t kRefreshKeyValue = 0u;",
        "  static constexpr std::uint32_t kUnlockKeyValue = 0u;",
        "  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kReloadRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kWindowRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRestartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kKeyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTimeoutField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kWindowField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kEarlyWarningInterruptEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kResetEnableField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusPrescalerUpdateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusReloadUpdateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusWindowUpdateField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusTimeoutField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStatusErrorField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRequiredConfigField = kInvalidFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=WATCHDOG_DRIVER_HEADER,
        trait_name="WatchdogSemanticTraits",
        array_name="kWatchdogSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_watchdog_specialization_builder(context),
    )


__all__ = [
    "WATCHDOG_DRIVER_HEADER",
    "WatchdogSemanticRow",
    "emit_runtime_driver_watchdog_semantics_header",
]
