"""I2C driver-semantic emitter (STM32 v1/v2 / Microchip / NXP).

Carved out from ``runtime_driver_semantics.py`` under
``refactor-runtime-driver-semantics-per-class`` Phase 2.
"""

# ruff: noqa: E501

from __future__ import annotations

from dataclasses import dataclass
from typing import Any

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from ..connector_model import (
    canonical_peripheral_class,
)
from ..emission import (
    _enum_identifier,
)
from .common import (
    KernelClockSourceOption,
    RuntimeFieldRef,
    RuntimeRegisterRef,
    _context,
    _emit_peripheral_semantics_header,
    _enrich_with_dma_bindings,
    _field_ref_expr,
    _invalid_field_ref,
    _invalid_register_ref,
    _irq_numbers_lines,
    _kernel_clock_lines,
    _register_ref_expr,
    _render_typed_option_enum_block,
    _resolve_field_ref,
    _resolve_register_ref,
    _schema_ref_expr,
    _SemanticContext,
)

I2C_DRIVER_HEADER = "driver_semantics/i2c.hpp"


@dataclass(frozen=True, slots=True)
class I2cSemanticRow:
    """I2C semantic trait payload keyed by peripheral."""

    peripheral_name: str
    schema_id: str
    cr1_reg: RuntimeRegisterRef
    cr2_reg: RuntimeRegisterRef
    ccr_reg: RuntimeRegisterRef
    trise_reg: RuntimeRegisterRef
    sr1_reg: RuntimeRegisterRef
    sr2_reg: RuntimeRegisterRef
    dr_reg: RuntimeRegisterRef
    icr_reg: RuntimeRegisterRef
    cr_reg: RuntimeRegisterRef
    mmr_reg: RuntimeRegisterRef
    iadr_reg: RuntimeRegisterRef
    cwgr_reg: RuntimeRegisterRef
    sr_reg: RuntimeRegisterRef
    rhr_reg: RuntimeRegisterRef
    thr_reg: RuntimeRegisterRef
    pe_field: RuntimeFieldRef
    ack_field: RuntimeFieldRef
    start_field: RuntimeFieldRef
    stop_field: RuntimeFieldRef
    freq_field: RuntimeFieldRef
    ccr_field: RuntimeFieldRef
    fs_field: RuntimeFieldRef
    duty_field: RuntimeFieldRef
    trise_field: RuntimeFieldRef
    sb_field: RuntimeFieldRef
    addr_field: RuntimeFieldRef
    txe_field: RuntimeFieldRef
    rxne_field: RuntimeFieldRef
    btf_field: RuntimeFieldRef
    af_field: RuntimeFieldRef
    berr_field: RuntimeFieldRef
    arlo_field: RuntimeFieldRef
    busy_field: RuntimeFieldRef
    dr_data_field: RuntimeFieldRef
    sadd_field: RuntimeFieldRef
    rd_wrn_field: RuntimeFieldRef
    nbytes_field: RuntimeFieldRef
    autoend_field: RuntimeFieldRef
    txis_field: RuntimeFieldRef
    tc_field: RuntimeFieldRef
    stopf_field: RuntimeFieldRef
    txdata_field: RuntimeFieldRef
    rxdata_field: RuntimeFieldRef
    nackf_field: RuntimeFieldRef
    berr_isr_field: RuntimeFieldRef
    arlo_isr_field: RuntimeFieldRef
    stopcf_field: RuntimeFieldRef
    nackcf_field: RuntimeFieldRef
    berrcf_field: RuntimeFieldRef
    arlocf_field: RuntimeFieldRef
    msen_field: RuntimeFieldRef
    msdis_field: RuntimeFieldRef
    svdis_field: RuntimeFieldRef
    swrst_field: RuntimeFieldRef
    iadrsz_field: RuntimeFieldRef
    mread_field: RuntimeFieldRef
    dadr_field: RuntimeFieldRef
    iadr_field: RuntimeFieldRef
    cldiv_field: RuntimeFieldRef
    chdiv_field: RuntimeFieldRef
    ckdiv_field: RuntimeFieldRef
    hold_field: RuntimeFieldRef
    txcomp_field: RuntimeFieldRef
    rxrdy_field: RuntimeFieldRef
    txrdy_field: RuntimeFieldRef
    nack_field: RuntimeFieldRef
    arblst_field: RuntimeFieldRef
    is_stub: bool = False  # True when peripheral exists but schema is not yet implemented
    # NVIC vector lines (added by ``add-irq-vector-traits``).
    irq_numbers: tuple[int, ...] = ()
    # Kernel-clock traits (added by ``add-kernel-clock-traits``).
    # ``None`` field-refs render as ``kInvalidFieldRef``.
    kernel_clock_selector_field: RuntimeFieldRef | None = None
    kernel_clock_source_options: tuple[KernelClockSourceOption, ...] = ()
    max_clock_hz: int = 0
    clock_gate_field: RuntimeFieldRef | None = None
    # I2C Tier 2/3/4 (added by ``add-i2c-tier-2-3-4-data``).  Default-empty
    # tuples / falsy mode-flags block; populated by per-family device patches.
    speed_options: tuple[I2cSpeedOption, ...] = ()
    timing_presets: tuple[I2cTimingPreset, ...] = ()
    mode_flags: I2cModeFlags | None = None


@dataclass(frozen=True, slots=True)
class I2cSpeedOption:
    """One supported I2C bus speed (added by ``add-i2c-tier-2-3-4-data``)."""

    speed_hz: int
    mode: str  # "standard" | "fast" | "fast_plus" | "high_speed"


@dataclass(frozen=True, slots=True)
class I2cTimingPreset:
    """Precomputed TIMINGR / CWGR value for a given source-clock + speed."""

    speed_hz: int
    source_clock_hz: int
    timingr_value: int


@dataclass(frozen=True, slots=True)
class I2cModeFlags:
    """Per-I2C capability flags; ``valid`` flips ``true`` once the patch
    populates the row."""

    supports_smbus: bool = False
    supports_pmbus: bool = False
    supports_dma: bool = False
    supports_slave: bool = True
    supports_dual_address: bool = False
    supports_general_call: bool = False
    supports_7bit_addressing: bool = True
    supports_10bit_addressing: bool = False
    valid: bool = False


# KernelClockSourceOption → runtime_driver/common.py


_I2C_SPEED_MODE_NAME: dict[str, str] = {
    "standard": "standard",
    "fast": "fast",
    "fast_plus": "fast_plus",
    "high_speed": "high_speed",
}


def _build_i2c_typed_enum_blocks(rows: tuple[I2cSemanticRow, ...]) -> list[str]:
    """Render I2C typed-option enum blocks (speed mode)."""
    mode_entries: list[tuple[str, tuple[tuple[str, int], ...]]] = []
    for row in rows:
        if row.is_stub:
            continue
        peripheral_id = _enum_identifier(row.peripheral_name)
        modes = tuple(
            (_I2C_SPEED_MODE_NAME[opt.mode], idx)
            for idx, opt in enumerate(row.speed_options)
            if opt.mode in _I2C_SPEED_MODE_NAME
        )
        if modes:
            mode_entries.append((peripheral_id, modes))

    if not any(e for _, e in mode_entries):
        return []
    lines: list[str] = [
        "// add-typed-peripheral-enums-everywhere: typed I2cSpeedModeOf per peripheral.",
    ]
    lines.extend(
        _render_typed_option_enum_block(
            template_name="I2cSpeedModeOf",
            alias_name="I2cSpeedMode",
            peripheral_entries=tuple(mode_entries),
        )
    )
    return lines


def _i2c_tier234_lines(row: I2cSemanticRow) -> list[str]:
    """Render the I2C Tier 2/3/4 constexprs for a peripheral
    specialisation.  Added by ``add-i2c-tier-2-3-4-data``.

    Empty arrays / falsy mode flags by default until per-family
    device patches populate the row's ``speed_options``,
    ``timing_presets``, and ``mode_flags`` fields.
    """
    speed_n = len(row.speed_options)
    if speed_n == 0:
        speeds_line = "  static constexpr std::array<std::uint32_t, 0> kSupportedSpeeds = {};"
    else:
        joined = ", ".join(f"{o.speed_hz}u" for o in row.speed_options)
        speeds_line = (
            f"  static constexpr std::array<std::uint32_t, {speed_n}> "
            f"kSupportedSpeeds = {{{{{joined}}}}};"
        )

    preset_n = len(row.timing_presets)
    if preset_n == 0:
        presets_line = "  static constexpr std::array<I2cTimingPreset, 0> kTimingPresets = {};"
    else:
        items = ", ".join(
            f"{{{p.speed_hz}u, {p.source_clock_hz}u, {p.timingr_value:#010x}u, true}}"
            for p in row.timing_presets
        )
        presets_line = (
            f"  static constexpr std::array<I2cTimingPreset, {preset_n}> "
            f"kTimingPresets = {{{{{items}}}}};"
        )

    flags = row.mode_flags
    return [
        speeds_line,
        presets_line,
        f"  static constexpr bool kSupportsSmbus = "
        f"{'true' if flags and flags.supports_smbus else 'false'};",
        f"  static constexpr bool kSupportsPmbus = "
        f"{'true' if flags and flags.supports_pmbus else 'false'};",
        f"  static constexpr bool kSupportsSlave = "
        f"{'true' if flags is None or flags.supports_slave else 'false'};",
        f"  static constexpr bool kSupportsDualAddress = "
        f"{'true' if flags and flags.supports_dual_address else 'false'};",
        f"  static constexpr bool kSupportsGeneralCall = "
        f"{'true' if flags and flags.supports_general_call else 'false'};",
        f"  static constexpr bool kSupports7BitAddressing = "
        f"{'true' if flags is None or flags.supports_7bit_addressing else 'false'};",
        f"  static constexpr bool kSupports10BitAddressing = "
        f"{'true' if flags and flags.supports_10bit_addressing else 'false'};",
    ]


# _kernel_clock_lines → runtime_driver/common.py


def _i2c_extension_for_peripheral(
    context: _SemanticContext,
    *,
    peripheral_name: str,
) -> dict[str, Any]:
    """Build the Tier 2/3/4 kwargs for ``I2cSemanticRow``.

    Reads the device IR's I2C patch tuples (forwarded by
    ``stages/normalize.run``) and returns a dict suitable for ``**``
    unpacking into the row constructor.  Mirrors the UART/SPI Tier
    2/3/4 helpers added by ``add-uart-spi-tier-2-3-4-data``.  Added by
    ``add-i2c-tier-2-3-4-data``.
    """
    device = context.device
    speed_options = tuple(
        I2cSpeedOption(speed_hz=p.speed_hz, mode=p.mode)
        for p in device.i2c_speed_options
        if getattr(p, "peripheral", None) == peripheral_name
    )
    timing_presets = tuple(
        I2cTimingPreset(
            speed_hz=p.speed_hz,
            source_clock_hz=p.source_clock_hz,
            timingr_value=p.timingr_value,
        )
        for p in device.i2c_timing_presets
        if getattr(p, "peripheral", None) == peripheral_name
    )
    flags_patch = next(
        (p for p in device.i2c_mode_flags if getattr(p, "peripheral", None) == peripheral_name),
        None,
    )
    if flags_patch is not None:
        mode_flags = I2cModeFlags(
            supports_smbus=flags_patch.supports_smbus,
            supports_pmbus=flags_patch.supports_pmbus,
            supports_dma=flags_patch.supports_dma,
            supports_slave=flags_patch.supports_slave,
            supports_dual_address=flags_patch.supports_dual_address,
            supports_general_call=flags_patch.supports_general_call,
            supports_7bit_addressing=flags_patch.supports_7bit_addressing,
            supports_10bit_addressing=flags_patch.supports_10bit_addressing,
            valid=True,
        )
    else:
        mode_flags = None
    return {
        "speed_options": speed_options,
        "timing_presets": timing_presets,
        "mode_flags": mode_flags,
    }


def _st_i2c_v1_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=reg("CR1", 0x00),
        cr2_reg=reg("CR2", 0x04),
        ccr_reg=reg("CCR", 0x1C),
        trise_reg=reg("TRISE", 0x20),
        sr1_reg=reg("SR1", 0x14),
        sr2_reg=reg("SR2", 0x18),
        dr_reg=reg("DR", 0x10),
        icr_reg=empty_reg,
        cr_reg=empty_reg,
        mmr_reg=empty_reg,
        iadr_reg=empty_reg,
        cwgr_reg=empty_reg,
        sr_reg=empty_reg,
        rhr_reg=empty_reg,
        thr_reg=empty_reg,
        pe_field=field("CR1", "PE", 0x00, 0),
        ack_field=field("CR1", "ACK", 0x00, 10),
        start_field=field("CR1", "START", 0x00, 8),
        stop_field=field("CR1", "STOP", 0x00, 9),
        freq_field=field("CR2", "FREQ", 0x04, 0, 6),
        ccr_field=field("CCR", "CCR", 0x1C, 0, 12),
        fs_field=field("CCR", "F_S", 0x1C, 15),
        duty_field=field("CCR", "DUTY", 0x1C, 14),
        trise_field=field("TRISE", "TRISE", 0x20, 0, 6),
        sb_field=field("SR1", "SB", 0x14, 0),
        addr_field=field("SR1", "ADDR", 0x14, 1),
        txe_field=field("SR1", "TxE", 0x14, 7),
        rxne_field=field("SR1", "RxNE", 0x14, 6),
        btf_field=field("SR1", "BTF", 0x14, 2),
        af_field=field("SR1", "AF", 0x14, 10),
        berr_field=field("SR1", "BERR", 0x14, 8),
        arlo_field=field("SR1", "ARLO", 0x14, 9),
        busy_field=field("SR2", "BUSY", 0x18, 1),
        dr_data_field=field("DR", "DR", 0x10, 0, 8),
        sadd_field=empty_field,
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=empty_field,
        tc_field=empty_field,
        stopf_field=empty_field,
        txdata_field=empty_field,
        rxdata_field=empty_field,
        nackf_field=empty_field,
        berr_isr_field=empty_field,
        arlo_isr_field=empty_field,
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=empty_field,
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=empty_field,
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=empty_field,
        chdiv_field=empty_field,
        ckdiv_field=empty_field,
        hold_field=empty_field,
        txcomp_field=empty_field,
        rxrdy_field=empty_field,
        txrdy_field=empty_field,
        nack_field=empty_field,
        arblst_field=empty_field,
        **_i2c_extension_for_peripheral(context, peripheral_name=peripheral_name),
    )


def _st_i2c_v2_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=reg("CR2", 0x04),
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=reg("ICR", 0x20),
        cr_reg=empty_reg,
        mmr_reg=empty_reg,
        iadr_reg=empty_reg,
        cwgr_reg=empty_reg,
        sr_reg=empty_reg,
        rhr_reg=empty_reg,
        thr_reg=empty_reg,
        pe_field=empty_field,
        ack_field=empty_field,
        start_field=field("CR2", ("START",), 0x04, 13),
        stop_field=empty_field,
        freq_field=empty_field,
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=empty_field,
        dr_data_field=empty_field,
        sadd_field=field("CR2", ("SADD",), 0x04, 0, 10),
        rd_wrn_field=field("CR2", ("RD_WRN",), 0x04, 10),
        nbytes_field=field("CR2", ("NBYTES",), 0x04, 16, 8),
        autoend_field=field("CR2", ("AUTOEND",), 0x04, 25),
        txis_field=field("ISR", ("TXIS",), 0x1C, 1),
        tc_field=field("ISR", ("TC",), 0x1C, 6),
        stopf_field=field("ISR", ("STOPF",), 0x1C, 5),
        txdata_field=field("TXDR", ("TXDATA",), 0x28, 0, 8),
        rxdata_field=field("RXDR", ("RXDATA",), 0x24, 0, 8),
        nackf_field=field("ISR", ("NACKF",), 0x1C, 4),
        berr_isr_field=field("ISR", ("BERR",), 0x1C, 8),
        arlo_isr_field=field("ISR", ("ARLO",), 0x1C, 9),
        stopcf_field=field("ICR", ("STOPCF",), 0x20, 5),
        nackcf_field=field("ICR", ("NACKCF",), 0x20, 4),
        berrcf_field=field("ICR", ("BERRCF",), 0x20, 8),
        arlocf_field=field("ICR", ("ARLOCF",), 0x20, 9),
        msen_field=empty_field,
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=empty_field,
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=empty_field,
        chdiv_field=empty_field,
        ckdiv_field=empty_field,
        hold_field=empty_field,
        txcomp_field=empty_field,
        rxrdy_field=empty_field,
        txrdy_field=empty_field,
        nack_field=empty_field,
        arblst_field=empty_field,
        **_i2c_extension_for_peripheral(context, peripheral_name=peripheral_name),
    )


def _microchip_i2c_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str, field_name: str, reg_offset: int, bit_offset: int, bit_width: int = 1
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=(field_name,),
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=empty_reg,
        cr_reg=reg("CR", 0x00),
        mmr_reg=reg("MMR", 0x04),
        iadr_reg=reg("IADR", 0x0C),
        cwgr_reg=reg("CWGR", 0x10),
        sr_reg=reg("SR", 0x20),
        rhr_reg=reg("RHR", 0x30),
        thr_reg=reg("THR", 0x34),
        pe_field=empty_field,
        ack_field=empty_field,
        # TWIHS CR is a write-only "action" register: writing START=1 issues
        # a START condition, writing STOP=1 issues a STOP, and the bits are
        # self-clearing. Expose them as bit-0/bit-1 single-bit fields so the
        # HAL backend can drive them through rt::write_register(cr, ...) /
        # rt::modify_field(start/stop, 1u) instead of typing raw masks.
        start_field=field("CR", "START", 0x00, 0),
        stop_field=field("CR", "STOP", 0x00, 1),
        freq_field=empty_field,
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=empty_field,
        dr_data_field=empty_field,
        sadd_field=empty_field,
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=empty_field,
        tc_field=empty_field,
        stopf_field=empty_field,
        txdata_field=field("THR", "TXDATA", 0x34, 0, 8),
        rxdata_field=field("RHR", "RXDATA", 0x30, 0, 8),
        nackf_field=empty_field,
        berr_isr_field=empty_field,
        arlo_isr_field=empty_field,
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=field("CR", "MSEN", 0x00, 2),
        msdis_field=field("CR", "MSDIS", 0x00, 3),
        svdis_field=field("CR", "SVDIS", 0x00, 5),
        swrst_field=field("CR", "SWRST", 0x00, 7),
        iadrsz_field=field("MMR", "IADRSZ", 0x04, 8, 2),
        mread_field=field("MMR", "MREAD", 0x04, 12),
        dadr_field=field("MMR", "DADR", 0x04, 16, 7),
        iadr_field=field("IADR", "IADR", 0x0C, 0, 24),
        cldiv_field=field("CWGR", "CLDIV", 0x10, 0, 8),
        chdiv_field=field("CWGR", "CHDIV", 0x10, 8, 8),
        ckdiv_field=field("CWGR", "CKDIV", 0x10, 16, 3),
        hold_field=field("CWGR", "HOLD", 0x10, 24, 5),
        txcomp_field=field("SR", "TXCOMP", 0x20, 0),
        rxrdy_field=field("SR", "RXRDY", 0x20, 1),
        txrdy_field=field("SR", "TXRDY", 0x20, 2),
        nack_field=field("SR", "NACK", 0x20, 8),
        arblst_field=field("SR", "ARBLST", 0x20, 9),
        **_i2c_extension_for_peripheral(context, peripheral_name=peripheral_name),
    )


def _nxp_i2c_row(
    context: _SemanticContext, *, peripheral_name: str, schema_id: str
) -> I2cSemanticRow:
    base = context.peripheral_by_name[peripheral_name].base_address

    def reg(name: str, offset: int) -> RuntimeRegisterRef:
        return _resolve_register_ref(
            context, peripheral_name=peripheral_name, register_name=name, fallback_offset=offset
        )

    def field(
        register_name: str,
        names: tuple[str, ...],
        reg_offset: int,
        bit_offset: int,
        bit_width: int = 1,
    ) -> RuntimeFieldRef:
        return _resolve_field_ref(
            context,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_names=names,
            fallback_register_offset=reg_offset,
            fallback_bit_offset=bit_offset,
            fallback_bit_width=bit_width,
        )

    empty_reg = _invalid_register_ref(base)
    empty_field = _invalid_field_ref(base)
    return I2cSemanticRow(
        peripheral_name=peripheral_name,
        schema_id=schema_id,
        cr1_reg=empty_reg,
        cr2_reg=empty_reg,
        ccr_reg=empty_reg,
        trise_reg=empty_reg,
        sr1_reg=empty_reg,
        sr2_reg=empty_reg,
        dr_reg=empty_reg,
        icr_reg=empty_reg,
        cr_reg=reg("MCR", 0x10),
        mmr_reg=reg("MCFGR1", 0x24),
        iadr_reg=empty_reg,
        cwgr_reg=reg("MCCR0", 0x48),
        sr_reg=reg("MSR", 0x14),
        rhr_reg=reg("MRDR", 0x70),
        thr_reg=reg("MTDR", 0x60),
        pe_field=empty_field,
        ack_field=empty_field,
        start_field=field("MTDR", ("CMD",), 0x60, 8, 3),
        stop_field=field("MTDR", ("CMD",), 0x60, 8, 3),
        freq_field=field("MCFGR1", ("PRESCALE",), 0x24, 8, 3),
        ccr_field=empty_field,
        fs_field=empty_field,
        duty_field=empty_field,
        trise_field=empty_field,
        sb_field=empty_field,
        addr_field=empty_field,
        txe_field=empty_field,
        rxne_field=empty_field,
        btf_field=empty_field,
        af_field=empty_field,
        berr_field=empty_field,
        arlo_field=empty_field,
        busy_field=field("MSR", ("BBF",), 0x14, 25),
        dr_data_field=empty_field,
        sadd_field=field("MTDR", ("DATA",), 0x60, 0, 8),
        rd_wrn_field=empty_field,
        nbytes_field=empty_field,
        autoend_field=empty_field,
        txis_field=field("MSR", ("TDF",), 0x14, 0),
        tc_field=field("MSR", ("SDF",), 0x14, 9),
        stopf_field=field("MSR", ("SDF",), 0x14, 9),
        txdata_field=field("MTDR", ("DATA",), 0x60, 0, 8),
        rxdata_field=field("MRDR", ("DATA",), 0x70, 0, 8),
        nackf_field=field("MSR", ("NDF",), 0x14, 10),
        berr_isr_field=field("MSR", ("FEF",), 0x14, 12),
        arlo_isr_field=field("MSR", ("ALF",), 0x14, 11),
        stopcf_field=empty_field,
        nackcf_field=empty_field,
        berrcf_field=empty_field,
        arlocf_field=empty_field,
        msen_field=field("MCR", ("MEN",), 0x10, 0),
        msdis_field=empty_field,
        svdis_field=empty_field,
        swrst_field=field("MCR", ("RST",), 0x10, 1),
        iadrsz_field=empty_field,
        mread_field=empty_field,
        dadr_field=empty_field,
        iadr_field=empty_field,
        cldiv_field=field("MCCR0", ("CLKLO",), 0x48, 0, 6),
        chdiv_field=field("MCCR0", ("CLKHI",), 0x48, 8, 6),
        ckdiv_field=field("MCFGR1", ("PRESCALE",), 0x24, 8, 3),
        hold_field=field("MCCR0", ("SETHOLD",), 0x48, 16, 6),
        txcomp_field=field("MSR", ("SDF",), 0x14, 9),
        rxrdy_field=field("MSR", ("RDF",), 0x14, 1),
        txrdy_field=field("MSR", ("TDF",), 0x14, 0),
        nack_field=field("MSR", ("NDF",), 0x14, 10),
        arblst_field=field("MSR", ("ALF",), 0x14, 11),
        **_i2c_extension_for_peripheral(context, peripheral_name=peripheral_name),
    )


def _build_i2c_rows(context: _SemanticContext) -> tuple[I2cSemanticRow, ...]:
    rows: list[I2cSemanticRow] = []
    candidate_peripherals = list(context.candidate_peripherals_by_class.get("i2c", ()))
    candidate_names = {p.name for p in candidate_peripherals}
    # Also surface I2C peripherals admitted in the device patch but without
    # admitted pin candidates (e.g. STM32G0 fixtures lack I2C pin_signals).
    # The dispatch falls through to the stub branch when the schema isn't
    # recognised, so the alloy HAL still gets ``kPresent`` + ``kIrqNumbers``
    # + ``kDmaBindings`` + Tier 2/3/4 silicon facts.  Added by
    # ``add-i2c-tier-2-3-4-data``.
    for peripheral in sorted(context.device.peripherals, key=lambda item: item.name):
        peripheral_class = canonical_peripheral_class(peripheral.ip_name)
        if peripheral_class == "i2c" and peripheral.name not in candidate_names:
            candidate_peripherals.append(peripheral)
            candidate_names.add(peripheral.name)
    for peripheral in candidate_peripherals:
        schema_id = peripheral.backend_schema_id
        if schema_id is None:
            continue
        if schema_id.startswith("alloy.i2c.st-") and "v1-5" in schema_id:
            rows.append(
                _st_i2c_v1_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id.startswith("alloy.i2c.st-"):
            rows.append(
                _st_i2c_v2_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.i2c.microchip-twihs-z":
            rows.append(
                _microchip_i2c_row(context, peripheral_name=peripheral.name, schema_id=schema_id)
            )
        elif schema_id == "alloy.lpi2c1.nxp-lpi2c-v1":
            rows.append(_nxp_i2c_row(context, peripheral_name=peripheral.name, schema_id=schema_id))
        else:
            # Emit a fully-invalid stub row so that the artifact contract
            # (I2cSemanticTraits<PeripheralId::) is satisfied for devices whose
            # I2C IP schema is not yet implemented in alloy.
            base = context.peripheral_by_name[peripheral.name].base_address
            invalid_reg = _invalid_register_ref(base)
            invalid_field = _invalid_field_ref(base)
            rows.append(
                I2cSemanticRow(
                    peripheral_name=peripheral.name,
                    schema_id=schema_id,
                    cr1_reg=invalid_reg,
                    cr2_reg=invalid_reg,
                    ccr_reg=invalid_reg,
                    trise_reg=invalid_reg,
                    sr1_reg=invalid_reg,
                    sr2_reg=invalid_reg,
                    dr_reg=invalid_reg,
                    icr_reg=invalid_reg,
                    cr_reg=invalid_reg,
                    mmr_reg=invalid_reg,
                    iadr_reg=invalid_reg,
                    cwgr_reg=invalid_reg,
                    sr_reg=invalid_reg,
                    rhr_reg=invalid_reg,
                    thr_reg=invalid_reg,
                    pe_field=invalid_field,
                    ack_field=invalid_field,
                    start_field=invalid_field,
                    stop_field=invalid_field,
                    freq_field=invalid_field,
                    ccr_field=invalid_field,
                    fs_field=invalid_field,
                    duty_field=invalid_field,
                    trise_field=invalid_field,
                    sb_field=invalid_field,
                    addr_field=invalid_field,
                    txe_field=invalid_field,
                    rxne_field=invalid_field,
                    btf_field=invalid_field,
                    af_field=invalid_field,
                    berr_field=invalid_field,
                    arlo_field=invalid_field,
                    busy_field=invalid_field,
                    dr_data_field=invalid_field,
                    sadd_field=invalid_field,
                    rd_wrn_field=invalid_field,
                    nbytes_field=invalid_field,
                    autoend_field=invalid_field,
                    txis_field=invalid_field,
                    tc_field=invalid_field,
                    stopf_field=invalid_field,
                    txdata_field=invalid_field,
                    rxdata_field=invalid_field,
                    nackf_field=invalid_field,
                    berr_isr_field=invalid_field,
                    arlo_isr_field=invalid_field,
                    stopcf_field=invalid_field,
                    nackcf_field=invalid_field,
                    berrcf_field=invalid_field,
                    arlocf_field=invalid_field,
                    msen_field=invalid_field,
                    msdis_field=invalid_field,
                    svdis_field=invalid_field,
                    swrst_field=invalid_field,
                    iadrsz_field=invalid_field,
                    mread_field=invalid_field,
                    dadr_field=invalid_field,
                    iadr_field=invalid_field,
                    cldiv_field=invalid_field,
                    chdiv_field=invalid_field,
                    ckdiv_field=invalid_field,
                    hold_field=invalid_field,
                    txcomp_field=invalid_field,
                    rxrdy_field=invalid_field,
                    txrdy_field=invalid_field,
                    nack_field=invalid_field,
                    arblst_field=invalid_field,
                    is_stub=True,
                    **_i2c_extension_for_peripheral(context, peripheral_name=peripheral.name),
                )
            )
    return _enrich_with_dma_bindings(context, tuple(rows), transfer_width_bits=8)  # type: ignore[return-value]


def _i2c_specialization_builder(context: _SemanticContext):
    def _build(row: I2cSemanticRow) -> list[str]:
        if row.is_stub:
            # Peripheral is present on hardware but schema not yet implemented —
            # emit a kPresent=false specialization so the alloy HAL can detect it.
            return [
                "  static constexpr bool kPresent = false;",
                f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
                "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
                "  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kFreqField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCcrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kFsField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTriseField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSbField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAddrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBtfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBerrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArloField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBusyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSaddField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRdWrnField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNbytesField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kAutoendField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTcField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxdataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxdataField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMsenField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMsdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSvdisField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kIadrszField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kMreadField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kDadrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kIadrField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCldivField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kChdivField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kCkdivField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kHoldField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxcompField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kNackField = kInvalidFieldRef;",
                "  static constexpr RuntimeFieldRef kArblstField = kInvalidFieldRef;",
                *_irq_numbers_lines(row.irq_numbers),
                *_kernel_clock_lines(
                    selector_field=row.kernel_clock_selector_field,
                    options=row.kernel_clock_source_options,
                    max_clock_hz=row.max_clock_hz,
                    gate_field=row.clock_gate_field,
                ),
                *_i2c_tier234_lines(row),
            ]
        register_members = {
            "kCr1Register": row.cr1_reg,
            "kCr2Register": row.cr2_reg,
            "kCcrRegister": row.ccr_reg,
            "kTriseRegister": row.trise_reg,
            "kSr1Register": row.sr1_reg,
            "kSr2Register": row.sr2_reg,
            "kDrRegister": row.dr_reg,
            "kIcrRegister": row.icr_reg,
            "kCrRegister": row.cr_reg,
            "kMmrRegister": row.mmr_reg,
            "kIadrRegister": row.iadr_reg,
            "kCwgrRegister": row.cwgr_reg,
            "kSrRegister": row.sr_reg,
            "kRhrRegister": row.rhr_reg,
            "kThrRegister": row.thr_reg,
        }
        field_members = {
            "kPeField": row.pe_field,
            "kAckField": row.ack_field,
            "kStartField": row.start_field,
            "kStopField": row.stop_field,
            "kFreqField": row.freq_field,
            "kCcrField": row.ccr_field,
            "kFsField": row.fs_field,
            "kDutyField": row.duty_field,
            "kTriseField": row.trise_field,
            "kSbField": row.sb_field,
            "kAddrField": row.addr_field,
            "kTxeField": row.txe_field,
            "kRxneField": row.rxne_field,
            "kBtfField": row.btf_field,
            "kAfField": row.af_field,
            "kBerrField": row.berr_field,
            "kArloField": row.arlo_field,
            "kBusyField": row.busy_field,
            "kDrDataField": row.dr_data_field,
            "kSaddField": row.sadd_field,
            "kRdWrnField": row.rd_wrn_field,
            "kNbytesField": row.nbytes_field,
            "kAutoendField": row.autoend_field,
            "kTxisField": row.txis_field,
            "kTcField": row.tc_field,
            "kStopfField": row.stopf_field,
            "kTxdataField": row.txdata_field,
            "kRxdataField": row.rxdata_field,
            "kNackfField": row.nackf_field,
            "kBerrIsrField": row.berr_isr_field,
            "kArloIsrField": row.arlo_isr_field,
            "kStopcfField": row.stopcf_field,
            "kNackcfField": row.nackcf_field,
            "kBerrcfField": row.berrcf_field,
            "kArlocfField": row.arlocf_field,
            "kMsenField": row.msen_field,
            "kMsdisField": row.msdis_field,
            "kSvdisField": row.svdis_field,
            "kSwrstField": row.swrst_field,
            "kIadrszField": row.iadrsz_field,
            "kMreadField": row.mread_field,
            "kDadrField": row.dadr_field,
            "kIadrField": row.iadr_field,
            "kCldivField": row.cldiv_field,
            "kChdivField": row.chdiv_field,
            "kCkdivField": row.ckdiv_field,
            "kHoldField": row.hold_field,
            "kTxcompField": row.txcomp_field,
            "kRxrdyField": row.rxrdy_field,
            "kTxrdyField": row.txrdy_field,
            "kNackField": row.nack_field,
            "kArblstField": row.arblst_field,
        }
        lines = [
            "  static constexpr bool kPresent = true;",
            f"  static constexpr BackendSchemaId kSchemaId = {_schema_ref_expr(context, row.schema_id)};",
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
        lines.extend(
            _kernel_clock_lines(
                selector_field=row.kernel_clock_selector_field,
                options=row.kernel_clock_source_options,
                max_clock_hz=row.max_clock_hz,
                gate_field=row.clock_gate_field,
            )
        )
        lines.extend(_i2c_tier234_lines(row))
        return lines

    return _build


def _i2c_peripheral_traits_block(device: CanonicalDeviceIR) -> list[str]:
    """fill-i2c-semantic-gaps: per-controller I2C / TWI trait struct.

    Emits a `RuntimeI2cCtrlId` enum + `I2cPeripheralTraits<RuntimeI2cCtrlId>`
    template populated from `device.i2c_peripherals`.  Pad lists are
    string-keyed (canonical pin names like ``"PA10"``, ``"GP12"``);
    we serialize them as `std::array<std::string_view, N>` so consumer
    concept checks can string-compare without runtime parsing.
    """
    # Encode the I2C clock source as a typed enum so consumer concept
    # checks can branch on it without string parsing — string literals
    # are not allowed in runtime C++ output (boundary test gate).
    lines = [
        "// fill-i2c-semantic-gaps: per-controller I2C / TWI HW facts.",
        "enum class RuntimeI2cClockSource : std::uint8_t {",
        "  None = 0,",
        "  Pclk = 1,",
        "  Hsi16 = 2,",
        "  Sysclk = 3,",
        "};",
        "",
        "enum class RuntimeI2cCtrlId : std::uint8_t {",
        "  None = 0,",
    ]
    for index, ctrl in enumerate(device.i2c_peripherals, start=1):
        lines.append(f"  {ctrl.peripheral_id} = {index},")
    lines.extend(
        [
            "};",
            "",
            "template<RuntimeI2cCtrlId Id>",
            "struct I2cPeripheralTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint32_t kBaseAddress = 0u;",
            "  static constexpr RuntimeI2cClockSource kClockSource = RuntimeI2cClockSource::None;",
            "  static constexpr std::uint8_t kDreqTx = 0u;",
            "  static constexpr std::uint8_t kDreqRx = 0u;",
            # Pad arrays use the typed ``PinId`` enum already declared in
            # ``../pins.hpp``; the empty array is the AllGpios sentinel
            # (any pad is acceptable — Espressif IO matrix path).
            "  static constexpr std::array<PinId, 0> kValidSdaPins = {};",
            "  static constexpr std::array<PinId, 0> kValidSclPins = {};",
            "  static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;",
            "  static constexpr std::uint16_t kInSclSignal = 0xFFFFu;",
            "  static constexpr std::uint16_t kOutSdaSignal = 0xFFFFu;",
            "  static constexpr std::uint16_t kOutSclSignal = 0xFFFFu;",
            "  static constexpr bool kSupportsFastModePlus = false;",
            "  static constexpr bool kPortmuxAlt = false;",
            "};",
            "",
        ]
    )

    def _pad_array(name: str, pads: tuple[str, ...]) -> str:
        if not pads:
            return f"  static constexpr std::array<PinId, 0> {name} = {{}};"
        items = ", ".join(f"PinId::{_enum_identifier(p)}" for p in pads)
        # Use single-brace init so clang accepts std::array<PinId, N> (the
        # double-brace form trips on enum types under C++23 in some
        # toolchains because the inner aggregate has no default ctor for
        # the enum).
        return f"  static constexpr std::array<PinId, {len(pads)}> {name} = {{{items}}};"

    def _opt_signal(value: int | None) -> str:
        return "0xFFFFu" if value is None else f"{value}u"

    _clock_source_token = {
        None: "RuntimeI2cClockSource::None",
        "": "RuntimeI2cClockSource::None",
        "pclk": "RuntimeI2cClockSource::Pclk",
        "hsi16": "RuntimeI2cClockSource::Hsi16",
        "sysclk": "RuntimeI2cClockSource::Sysclk",
    }

    for ctrl in device.i2c_peripherals:
        clock_enum = _clock_source_token.get(ctrl.clock_source, "RuntimeI2cClockSource::None")
        lines.extend(
            [
                "template<>",
                f"struct I2cPeripheralTraits<RuntimeI2cCtrlId::{ctrl.peripheral_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uint32_t kBaseAddress = {ctrl.base_address:#010x}u;",
                f"  static constexpr RuntimeI2cClockSource kClockSource = {clock_enum};",
                f"  static constexpr std::uint8_t kDreqTx = {ctrl.dreq_tx or 0}u;",
                f"  static constexpr std::uint8_t kDreqRx = {ctrl.dreq_rx or 0}u;",
                _pad_array("kValidSdaPins", ctrl.valid_sda_pins),
                _pad_array("kValidSclPins", ctrl.valid_scl_pins),
                f"  static constexpr std::uint16_t kInSdaSignal = {_opt_signal(ctrl.gpio_matrix_in_sda_signal)};",
                f"  static constexpr std::uint16_t kInSclSignal = {_opt_signal(ctrl.gpio_matrix_in_scl_signal)};",
                f"  static constexpr std::uint16_t kOutSdaSignal = {_opt_signal(ctrl.gpio_matrix_out_sda_signal)};",
                f"  static constexpr std::uint16_t kOutSclSignal = {_opt_signal(ctrl.gpio_matrix_out_scl_signal)};",
                f"  static constexpr bool kSupportsFastModePlus = {'true' if ctrl.supports_fast_mode_plus else 'false'};",
                f"  static constexpr bool kPortmuxAlt = {'true' if ctrl.portmux_alt else 'false'};",
                "};",
                "",
            ]
        )
    return lines


def emit_runtime_driver_i2c_semantics_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    rows = _build_i2c_rows(context)
    default_lines = [
        "  static constexpr bool kPresent = false;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr RuntimeRegisterRef kCr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCcrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kTriseRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSr1Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSr2Register = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kDrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIcrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kMmrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kIadrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kCwgrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kSrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kRhrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeRegisterRef kThrRegister = kInvalidRegisterRef;",
        "  static constexpr RuntimeFieldRef kPeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAckField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFreqField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCcrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kFsField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTriseField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSbField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAddrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxeField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxneField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBtfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArloField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBusyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDrDataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSaddField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRdWrnField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNbytesField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kAutoendField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTcField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxdataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxdataField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArloIsrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kStopcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kBerrcfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArlocfField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMsenField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMsdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSvdisField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kSwrstField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kIadrszField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kMreadField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kDadrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kIadrField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCldivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kChdivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kCkdivField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kHoldField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxcompField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kRxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kTxrdyField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kNackField = kInvalidFieldRef;",
        "  static constexpr RuntimeFieldRef kArblstField = kInvalidFieldRef;",
        # NVIC vector lines (added by ``add-irq-vector-traits``).
        "  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};",
        # DMA cross-references (added by ``add-peripheral-dma-cross-references``).
        "  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};",
        # Kernel-clock defaults (added by ``add-kernel-clock-traits``).
        "  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;",
        "  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};",
        "  static constexpr std::uint32_t kKernelMaxClockHz = 0u;",
        "  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;",
        # I2C Tier 2/3/4 defaults (added by ``add-i2c-tier-2-3-4-data``).
        "  static constexpr std::array<std::uint32_t, 0> kSupportedSpeeds = {};",
        "  static constexpr std::array<I2cTimingPreset, 0> kTimingPresets = {};",
        "  static constexpr bool kSupportsSmbus = false;",
        "  static constexpr bool kSupportsPmbus = false;",
        "  static constexpr bool kSupportsSlave = false;",
        "  static constexpr bool kSupportsDualAddress = false;",
        "  static constexpr bool kSupportsGeneralCall = false;",
        "  static constexpr bool kSupports7BitAddressing = false;",
        "  static constexpr bool kSupports10BitAddressing = false;",
    ]
    return _emit_peripheral_semantics_header(
        family_dir=family_dir,
        device=device,
        header_name=I2C_DRIVER_HEADER,
        trait_name="I2cSemanticTraits",
        array_name="kI2cSemanticPeripherals",
        rows=rows,
        default_lines=default_lines,
        specialization_builder=_i2c_specialization_builder(context),
        extra_body_lines=_compose_i2c_extra_body(rows, device),
    )


def _compose_i2c_extra_body(
    rows: tuple[I2cSemanticRow, ...],
    device: CanonicalDeviceIR,
) -> list[str]:
    extra_body: list[str] = list(_i2c_peripheral_traits_block(device))
    typed_blocks = _build_i2c_typed_enum_blocks(rows)
    if typed_blocks:
        if extra_body:
            extra_body.append("")
        extra_body.extend(typed_blocks)
    return extra_body




__all__ = [
    "I2C_DRIVER_HEADER",
    "I2cSemanticRow",
    "emit_runtime_driver_i2c_semantics_header",
]
