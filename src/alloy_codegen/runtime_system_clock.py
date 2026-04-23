# ruff: noqa: E501

"""Generated runtime-lite system clock bring-up helpers."""

from __future__ import annotations

from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_rows,
    _std_array_lines,
)
from .ir.model import CanonicalDeviceIR
from .runtime_driver_semantics import (
    _context,
    _field_ref_expr,
    _register_ref_expr,
    _resolve_field_ref,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)

_CPP_RESERVED_ENUM_IDENTIFIERS = frozenset(
    {
        "alignas",
        "alignof",
        "and",
        "and_eq",
        "asm",
        "auto",
        "bitand",
        "bitor",
        "bool",
        "break",
        "case",
        "catch",
        "char",
        "char8_t",
        "char16_t",
        "char32_t",
        "class",
        "compl",
        "concept",
        "const",
        "consteval",
        "constexpr",
        "constinit",
        "const_cast",
        "continue",
        "co_await",
        "co_return",
        "co_yield",
        "decltype",
        "default",
        "delete",
        "do",
        "double",
        "dynamic_cast",
        "else",
        "enum",
        "explicit",
        "export",
        "extern",
        "false",
        "float",
        "for",
        "friend",
        "goto",
        "if",
        "inline",
        "int",
        "long",
        "mutable",
        "namespace",
        "new",
        "noexcept",
        "not",
        "not_eq",
        "nullptr",
        "operator",
        "or",
        "or_eq",
        "private",
        "protected",
        "public",
        "register",
        "reinterpret_cast",
        "requires",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "static_assert",
        "static_cast",
        "struct",
        "switch",
        "template",
        "this",
        "thread_local",
        "throw",
        "true",
        "try",
        "typedef",
        "typeid",
        "typename",
        "union",
        "unsigned",
        "using",
        "virtual",
        "void",
        "volatile",
        "wchar_t",
        "while",
        "xor",
        "xor_eq",
    }
)


def _safe_enum_identifier(value: str) -> str:
    identifier = _enum_identifier(value)
    if identifier in _CPP_RESERVED_ENUM_IDENTIFIERS:
        return f"{identifier}_value"
    return identifier


def runtime_system_clock_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, "system_clock.hpp")
        for device in devices
    )


def _system_clock_header_path(family_dir: str, device: CanonicalDeviceIR) -> str:
    return _device_runtime_generated_path(family_dir, device.identity.device, "system_clock.hpp")


def _profile_kind_enum_map(device: CanonicalDeviceIR) -> dict[str, str]:
    return {
        value: _safe_enum_identifier(value)
        for value in sorted({profile.kind for profile in device.system_clock_profiles})
    }


def _source_kind_enum_map(device: CanonicalDeviceIR) -> dict[str, str]:
    return {
        value: _safe_enum_identifier(value)
        for value in sorted({profile.source_kind for profile in device.system_clock_profiles})
    }


def _stm32g0_pllsrc_value(source_kind: str) -> int:
    if source_kind == "pll-internal":
        return 0x2
    if source_kind == "pll-external":
        return 0x3
    return 0x0


def emit_runtime_system_clock_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    context = _context(device)
    profiles = tuple(sorted(device.system_clock_profiles, key=lambda item: item.profile_id))
    profile_enum_map = {
        profile.profile_id: _safe_enum_identifier(profile.profile_id) for profile in profiles
    }
    kind_enum_map = _profile_kind_enum_map(device)
    source_enum_map = _source_kind_enum_map(device)

    def field(
        peripheral_name: str,
        register_name: str,
        field_names: tuple[str, ...],
        *,
        reg_offset: int,
        bit_offset: int,
        bit_width: int,
    ) -> str:
        expr = _field_ref_expr(
            _resolve_field_ref(
                context,
                peripheral_name=peripheral_name,
                register_name=register_name,
                field_names=field_names,
                fallback_register_offset=reg_offset,
                fallback_bit_offset=bit_offset,
                fallback_bit_width=bit_width,
            )
        )
        if expr == "kInvalidFieldRef":
            return "driver_semantics::kInvalidFieldRef"
        return expr

    def register_ref(peripheral_name: str, register_name: str, *, reg_offset: int) -> str:
        from .runtime_driver_semantics import _resolve_register_ref

        expr = _register_ref_expr(
            _resolve_register_ref(
                context,
                peripheral_name=peripheral_name,
                register_name=register_name,
                fallback_offset=reg_offset,
            )
        )
        if expr == "kInvalidRegisterRef":
            return "driver_semantics::kInvalidRegisterRef"
        return expr

    family_key = (device.identity.vendor, device.identity.family)
    extra_trait_lines: list[str] = []
    apply_lines: list[str] = []

    if family_key == ("st", "stm32g0"):
        extra_trait_lines.extend(
            [
                f"inline constexpr auto kRccCrRegister = {register_ref('RCC', 'CR', reg_offset=0x00)};",
                f"inline constexpr auto kRccCfgrRegister = {register_ref('RCC', 'CFGR', reg_offset=0x08)};",
                f"inline constexpr auto kRccPllcfgrRegister = {register_ref('RCC', 'PLLCFGR', reg_offset=0x0C)};",
                f"inline constexpr auto kFlashAcrRegister = {register_ref('FLASH', 'ACR', reg_offset=0x00)};",
                f"inline constexpr auto kHsionField = {field('RCC', 'CR', ('HSION',), reg_offset=0x00, bit_offset=8, bit_width=1)};",
                f"inline constexpr auto kHsirdyField = {field('RCC', 'CR', ('HSIRDY',), reg_offset=0x00, bit_offset=10, bit_width=1)};",
                f"inline constexpr auto kPllonField = {field('RCC', 'CR', ('PLLON',), reg_offset=0x00, bit_offset=24, bit_width=1)};",
                f"inline constexpr auto kPllrdyField = {field('RCC', 'CR', ('PLLRDY',), reg_offset=0x00, bit_offset=25, bit_width=1)};",
                f"inline constexpr auto kSwField = {field('RCC', 'CFGR', ('SW',), reg_offset=0x08, bit_offset=0, bit_width=3)};",
                f"inline constexpr auto kSwsField = {field('RCC', 'CFGR', ('SWS',), reg_offset=0x08, bit_offset=3, bit_width=3)};",
                f"inline constexpr auto kPllsrcField = {field('RCC', 'PLLCFGR', ('PLLSRC',), reg_offset=0x0C, bit_offset=0, bit_width=2)};",
                f"inline constexpr auto kPllmField = {field('RCC', 'PLLCFGR', ('PLLM',), reg_offset=0x0C, bit_offset=4, bit_width=3)};",
                f"inline constexpr auto kPllnField = {field('RCC', 'PLLCFGR', ('PLLN',), reg_offset=0x0C, bit_offset=8, bit_width=7)};",
                f"inline constexpr auto kPllrenField = {field('RCC', 'PLLCFGR', ('PLLREN',), reg_offset=0x0C, bit_offset=24, bit_width=1)};",
                f"inline constexpr auto kPllrField = {field('RCC', 'PLLCFGR', ('PLLR',), reg_offset=0x0C, bit_offset=25, bit_width=2)};",
                f"inline constexpr auto kFlashLatencyField = {field('FLASH', 'ACR', ('LATENCY',), reg_offset=0x00, bit_offset=0, bit_width=3)};",
                "",
            ]
        )
        apply_lines.extend(
            [
                "template<SystemClockProfileId Id>",
                "inline bool apply_system_clock_profile() {",
                "  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {",
                "    return false;",
                "  } else if constexpr (Id == SystemClockProfileId::safe_hsi16) {",
                "    set_field_bits(kHsionField);",
                "    return wait_field_value(kHsirdyField, 1u);",
                "  } else if constexpr (Id == SystemClockProfileId::default_pll_64mhz) {",
                "    set_field_bits(kHsionField);",
                "    if (!wait_field_value(kHsirdyField, 1u)) {",
                "      return false;",
                "    }",
                "    write_field(kFlashLatencyField, SystemClockProfileTraits<Id>::kFlashLatency);",
                "    write_field(kPllsrcField, SystemClockProfileTraits<Id>::kPllSource);",
                "    write_field(kPllmField, SystemClockProfileTraits<Id>::kPllM);",
                "    write_field(kPllnField, SystemClockProfileTraits<Id>::kPllN);",
                "    write_field(kPllrField, SystemClockProfileTraits<Id>::kPllR);",
                "    set_field_bits(kPllrenField);",
                "    set_field_bits(kPllonField);",
                "    if (!wait_field_value(kPllrdyField, 1u)) {",
                "      return false;",
                "    }",
                "    write_field(kSwField, 0x2u);",
                "    return wait_field_value(kSwsField, 0x2u);",
                "  } else {",
                "    return false;",
                "  }",
                "}",
            ]
        )
    elif family_key == ("st", "stm32f4"):
        extra_trait_lines.extend(
            [
                f"inline constexpr auto kRccCrRegister = {register_ref('RCC', 'CR', reg_offset=0x00)};",
                f"inline constexpr auto kRccPllcfgrRegister = {register_ref('RCC', 'PLLCFGR', reg_offset=0x04)};",
                f"inline constexpr auto kRccCfgrRegister = {register_ref('RCC', 'CFGR', reg_offset=0x08)};",
                f"inline constexpr auto kFlashAcrRegister = {register_ref('FLASH', 'ACR', reg_offset=0x00)};",
                f"inline constexpr auto kHseonField = {field('RCC', 'CR', ('HSEON',), reg_offset=0x00, bit_offset=16, bit_width=1)};",
                f"inline constexpr auto kHserdyField = {field('RCC', 'CR', ('HSERDY',), reg_offset=0x00, bit_offset=17, bit_width=1)};",
                f"inline constexpr auto kPllonField = {field('RCC', 'CR', ('PLLON',), reg_offset=0x00, bit_offset=24, bit_width=1)};",
                f"inline constexpr auto kPllrdyField = {field('RCC', 'CR', ('PLLRDY',), reg_offset=0x00, bit_offset=25, bit_width=1)};",
                f"inline constexpr auto kPllmField = {field('RCC', 'PLLCFGR', ('PLLM',), reg_offset=0x04, bit_offset=0, bit_width=6)};",
                f"inline constexpr auto kPllnField = {field('RCC', 'PLLCFGR', ('PLLN',), reg_offset=0x04, bit_offset=6, bit_width=9)};",
                f"inline constexpr auto kPllpField = {field('RCC', 'PLLCFGR', ('PLLP',), reg_offset=0x04, bit_offset=16, bit_width=2)};",
                f"inline constexpr auto kPllsrcField = {field('RCC', 'PLLCFGR', ('PLLSRC',), reg_offset=0x04, bit_offset=22, bit_width=1)};",
                f"inline constexpr auto kPllqField = {field('RCC', 'PLLCFGR', ('PLLQ',), reg_offset=0x04, bit_offset=24, bit_width=4)};",
                f"inline constexpr auto kSwField = {field('RCC', 'CFGR', ('SW',), reg_offset=0x08, bit_offset=0, bit_width=2)};",
                f"inline constexpr auto kSwsField = {field('RCC', 'CFGR', ('SWS',), reg_offset=0x08, bit_offset=2, bit_width=2)};",
                f"inline constexpr auto kHpreField = {field('RCC', 'CFGR', ('HPRE',), reg_offset=0x08, bit_offset=4, bit_width=4)};",
                f"inline constexpr auto kPpre1Field = {field('RCC', 'CFGR', ('PPRE1',), reg_offset=0x08, bit_offset=10, bit_width=3)};",
                f"inline constexpr auto kPpre2Field = {field('RCC', 'CFGR', ('PPRE2',), reg_offset=0x08, bit_offset=13, bit_width=3)};",
                f"inline constexpr auto kFlashLatencyField = {field('FLASH', 'ACR', ('LATENCY',), reg_offset=0x00, bit_offset=0, bit_width=4)};",
                "",
            ]
        )
        apply_lines.extend(
            [
                "inline constexpr std::uint32_t encode_apb_prescaler(std::uint32_t divisor) {",
                "  return divisor == 1u ? 0u : divisor == 2u ? 4u : divisor == 4u ? 5u : divisor == 8u ? 6u : 7u;",
                "}",
                "",
                "template<SystemClockProfileId Id>",
                "inline bool apply_system_clock_profile() {",
                "  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {",
                "    return false;",
                "  } else if constexpr (Id == SystemClockProfileId::safe_reset_default) {",
                "    return true;",
                "  } else if constexpr (Id == SystemClockProfileId::default_hse_pll_84mhz) {",
                "    set_field_bits(kHseonField);",
                "    if (!wait_field_value(kHserdyField, 1u)) {",
                "      return false;",
                "    }",
                "    write_field(kFlashLatencyField, SystemClockProfileTraits<Id>::kFlashLatency);",
                "    write_field(kPllmField, SystemClockProfileTraits<Id>::kPllM);",
                "    write_field(kPllnField, SystemClockProfileTraits<Id>::kPllN);",
                "    write_field(kPllpField, (SystemClockProfileTraits<Id>::kPllP / 2u) - 1u);",
                "    write_field(kPllsrcField, 1u);",
                "    write_field(kPllqField, SystemClockProfileTraits<Id>::kPllQ);",
                "    set_field_bits(kPllonField);",
                "    if (!wait_field_value(kPllrdyField, 1u)) {",
                "      return false;",
                "    }",
                "    write_field(kHpreField, 0u);",
                "    write_field(kPpre1Field, encode_apb_prescaler(SystemClockProfileTraits<Id>::kApb1Prescaler));",
                "    write_field(kPpre2Field, encode_apb_prescaler(SystemClockProfileTraits<Id>::kApb2Prescaler));",
                "    write_field(kSwField, 0x2u);",
                "    return wait_field_value(kSwsField, 0x2u);",
                "  } else {",
                "    return false;",
                "  }",
                "}",
            ]
        )
    elif family_key == ("microchip", "same70"):
        extra_trait_lines.extend(
            [
                f"inline constexpr auto kPmcCkgrMorRegister = {register_ref('PMC', 'CKGR_MOR', reg_offset=0x20)};",
                f"inline constexpr auto kPmcCkgrPllarRegister = {register_ref('PMC', 'CKGR_PLLAR', reg_offset=0x28)};",
                f"inline constexpr auto kPmcMckrRegister = {register_ref('PMC', 'MCKR', reg_offset=0x30)};",
                f"inline constexpr auto kPmcSrRegister = {register_ref('PMC', 'SR', reg_offset=0x68)};",
                f"inline constexpr auto kEfcFmrRegister = {register_ref('EFC', 'EEFC_FMR', reg_offset=0x00)};",
                f"inline constexpr auto kMorMoscxtenField = {field('PMC', 'CKGR_MOR', ('MOSCXTEN',), reg_offset=0x20, bit_offset=0, bit_width=1)};",
                f"inline constexpr auto kMorMoscrcenField = {field('PMC', 'CKGR_MOR', ('MOSCRCEN',), reg_offset=0x20, bit_offset=3, bit_width=1)};",
                f"inline constexpr auto kMorMoscrcfField = {field('PMC', 'CKGR_MOR', ('MOSCRCF',), reg_offset=0x20, bit_offset=4, bit_width=3)};",
                f"inline constexpr auto kMorMoscxtstField = {field('PMC', 'CKGR_MOR', ('MOSCXTST',), reg_offset=0x20, bit_offset=8, bit_width=8)};",
                f"inline constexpr auto kMorKeyField = {field('PMC', 'CKGR_MOR', ('KEY',), reg_offset=0x20, bit_offset=16, bit_width=8)};",
                f"inline constexpr auto kMorMoscselField = {field('PMC', 'CKGR_MOR', ('MOSCSEL',), reg_offset=0x20, bit_offset=24, bit_width=1)};",
                f"inline constexpr auto kPllarDivaField = {field('PMC', 'CKGR_PLLAR', ('DIVA',), reg_offset=0x28, bit_offset=0, bit_width=8)};",
                f"inline constexpr auto kPllarPllacountField = {field('PMC', 'CKGR_PLLAR', ('PLLACOUNT',), reg_offset=0x28, bit_offset=8, bit_width=6)};",
                f"inline constexpr auto kPllarMulaField = {field('PMC', 'CKGR_PLLAR', ('MULA',), reg_offset=0x28, bit_offset=16, bit_width=11)};",
                f"inline constexpr auto kPllarOneField = {field('PMC', 'CKGR_PLLAR', ('ONE',), reg_offset=0x28, bit_offset=29, bit_width=1)};",
                f"inline constexpr auto kMckrCssField = {field('PMC', 'MCKR', ('CSS',), reg_offset=0x30, bit_offset=0, bit_width=2)};",
                f"inline constexpr auto kMckrPresField = {field('PMC', 'MCKR', ('PRES',), reg_offset=0x30, bit_offset=4, bit_width=3)};",
                f"inline constexpr auto kMckrMdivField = {field('PMC', 'MCKR', ('MDIV',), reg_offset=0x30, bit_offset=8, bit_width=2)};",
                f"inline constexpr auto kSrMoscxtsField = {field('PMC', 'SR', ('MOSCXTS',), reg_offset=0x68, bit_offset=0, bit_width=1)};",
                f"inline constexpr auto kSrLockaField = {field('PMC', 'SR', ('LOCKA',), reg_offset=0x68, bit_offset=1, bit_width=1)};",
                f"inline constexpr auto kSrMckrdyField = {field('PMC', 'SR', ('MCKRDY',), reg_offset=0x68, bit_offset=3, bit_width=1)};",
                f"inline constexpr auto kSrMoscselsField = {field('PMC', 'SR', ('MOSCSELS',), reg_offset=0x68, bit_offset=16, bit_width=1)};",
                f"inline constexpr auto kSrMoscrcsField = {field('PMC', 'SR', ('MOSCRCS',), reg_offset=0x68, bit_offset=17, bit_width=1)};",
                f"inline constexpr auto kEfcFwsField = {field('EFC', 'EEFC_FMR', ('FWS',), reg_offset=0x00, bit_offset=8, bit_width=4)};",
                "",
            ]
        )
        apply_lines.extend(
            [
                "inline constexpr std::uint32_t kPmcMorKeyPasswd = 0x37u;",
                "inline constexpr std::uint32_t kPmcMainRc12MHz = 0x2u;",
                "inline constexpr std::uint32_t kPmcMckCssMain = 0x1u;",
                "inline constexpr std::uint32_t kPmcMckCssPlla = 0x2u;",
                "inline constexpr std::uint32_t kPmcMckMdivEqPck = 0x0u;",
                "",
                "inline std::uint32_t encode_same70_mck_prescaler(std::uint32_t divisor) {",
                "  switch (divisor) {",
                "    case 1u: return 0x0u;",
                "    case 2u: return 0x1u;",
                "    case 4u: return 0x2u;",
                "    case 8u: return 0x3u;",
                "    case 16u: return 0x4u;",
                "    case 32u: return 0x5u;",
                "    case 64u: return 0x6u;",
                "    case 3u: return 0x7u;",
                "    default: return 0x0u;",
                "  }",
                "}",
                "",
                "inline std::uint32_t encode_field_value(driver_semantics::RuntimeFieldRef field, std::uint32_t value) {",
                "  return (value << field.bit_offset) & field_mask(field);",
                "}",
                "",
                "inline bool same70_wait_mck_ready() {",
                "  return wait_field_value(kSrMckrdyField, 1u);",
                "}",
                "",
                "inline void same70_write_main_oscillator(bool use_external, std::uint32_t startup_cycles) {",
                "  std::uint32_t mor = 0u;",
                "  mor |= encode_field_value(kMorKeyField, kPmcMorKeyPasswd);",
                "  mor |= encode_field_value(kMorMoscxtstField, startup_cycles);",
                "  mor |= encode_field_value(kMorMoscrcfField, kPmcMainRc12MHz);",
                "  mor |= encode_field_value(kMorMoscrcenField, 1u);",
                "  if (use_external) {",
                "    mor |= encode_field_value(kMorMoscxtenField, 1u);",
                "  }",
                "  write_register(kPmcCkgrMorRegister, mor);",
                "}",
                "",
                "inline bool same70_enable_internal_rc(std::uint32_t startup_cycles) {",
                "  same70_write_main_oscillator(false, startup_cycles);",
                "  return wait_field_value(kSrMoscrcsField, 1u);",
                "}",
                "",
                "inline bool same70_enable_external_crystal(std::uint32_t startup_cycles) {",
                "  same70_write_main_oscillator(true, startup_cycles);",
                "  if (!wait_field_value(kSrMoscxtsField, 1u)) {",
                "    return false;",
                "  }",
                "  std::uint32_t mor = 0u;",
                "  mor |= encode_field_value(kMorKeyField, kPmcMorKeyPasswd);",
                "  mor |= encode_field_value(kMorMoscxtstField, startup_cycles);",
                "  mor |= encode_field_value(kMorMoscrcfField, kPmcMainRc12MHz);",
                "  mor |= encode_field_value(kMorMoscrcenField, 1u);",
                "  mor |= encode_field_value(kMorMoscxtenField, 1u);",
                "  mor |= encode_field_value(kMorMoscselField, 1u);",
                "  write_register(kPmcCkgrMorRegister, mor);",
                "  return wait_field_value(kSrMoscselsField, 1u);",
                "}",
                "",
                "inline bool same70_switch_mck(std::uint32_t css_value, std::uint32_t prescaler_divisor) {",
                "  write_field(kMckrCssField, kPmcMckCssMain);",
                "  if (!same70_wait_mck_ready()) {",
                "    return false;",
                "  }",
                "  write_field(kMckrPresField, encode_same70_mck_prescaler(prescaler_divisor));",
                "  write_field(kMckrMdivField, kPmcMckMdivEqPck);",
                "  if (!same70_wait_mck_ready()) {",
                "    return false;",
                "  }",
                "  write_field(kMckrCssField, css_value);",
                "  return same70_wait_mck_ready();",
                "}",
                "",
                "template<SystemClockProfileId Id>",
                "inline bool apply_system_clock_profile() {",
                "  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {",
                "    return false;",
                "  } else if constexpr (",
                "      Id == SystemClockProfileId::safe_internal_12mhz ||",
                "      Id == SystemClockProfileId::default_safe_internal_12mhz) {",
                "    if (!same70_enable_internal_rc(SystemClockProfileTraits<Id>::kOscillatorStartupCycles)) {",
                "      return false;",
                "    }",
                "    return same70_switch_mck(kPmcMckCssMain, SystemClockProfileTraits<Id>::kMckPrescaler);",
                "  } else if constexpr (Id == SystemClockProfileId::crystal_12mhz) {",
                "    if (!same70_enable_external_crystal(SystemClockProfileTraits<Id>::kOscillatorStartupCycles)) {",
                "      return false;",
                "    }",
                "    return same70_switch_mck(kPmcMckCssMain, SystemClockProfileTraits<Id>::kMckPrescaler);",
                "  } else if constexpr (Id == SystemClockProfileId::plla_150mhz) {",
                "    if (!same70_enable_external_crystal(SystemClockProfileTraits<Id>::kOscillatorStartupCycles)) {",
                "      return false;",
                "    }",
                "    write_field(kEfcFwsField, SystemClockProfileTraits<Id>::kFlashLatency);",
                "    std::uint32_t pllar = 0u;",
                "    pllar |= encode_field_value(kPllarDivaField, SystemClockProfileTraits<Id>::kPllM);",
                "    pllar |= encode_field_value(kPllarPllacountField, 0x3Fu);",
                "    pllar |= encode_field_value(kPllarMulaField, SystemClockProfileTraits<Id>::kPllN);",
                "    pllar |= encode_field_value(kPllarOneField, 1u);",
                "    write_register(kPmcCkgrPllarRegister, pllar);",
                "    if (!wait_field_value(kSrLockaField, 1u)) {",
                "      return false;",
                "    }",
                "    return same70_switch_mck(kPmcMckCssPlla, SystemClockProfileTraits<Id>::kMckPrescaler);",
                "  } else {",
                "    return false;",
                "  }",
                "}",
            ]
        )
    elif family_key == ("nxp", "imxrt1060"):
        extra_trait_lines.extend(
            [
                f"inline constexpr auto kCcmCacrrRegister = {register_ref('CCM', 'CACRR', reg_offset=0x10)};",
                f"inline constexpr auto kCcmCbcdrRegister = {register_ref('CCM', 'CBCDR', reg_offset=0x14)};",
                f"inline constexpr auto kCcmCbcmrRegister = {register_ref('CCM', 'CBCMR', reg_offset=0x18)};",
                f"inline constexpr auto kCcmCdhiprRegister = {register_ref('CCM', 'CDHIPR', reg_offset=0x48)};",
                f"inline constexpr auto kCcmAnalogPllArmRegister = {register_ref('CCM_ANALOG', 'PLL_ARM', reg_offset=0x00)};",
                f"inline constexpr auto kDcdcReg0Register = {register_ref('DCDC', 'REG0', reg_offset=0x00)};",
                f"inline constexpr auto kDcdcReg3Register = {register_ref('DCDC', 'REG3', reg_offset=0x0C)};",
                f"inline constexpr auto kArmPodfField = {field('CCM', 'CACRR', ('ARM_PODF',), reg_offset=0x10, bit_offset=0, bit_width=3)};",
                f"inline constexpr auto kIpgPodfField = {field('CCM', 'CBCDR', ('IPG_PODF',), reg_offset=0x14, bit_offset=8, bit_width=2)};",
                f"inline constexpr auto kAhbPodfField = {field('CCM', 'CBCDR', ('AHB_PODF',), reg_offset=0x14, bit_offset=10, bit_width=3)};",
                f"inline constexpr auto kPeriphClockSelField = {field('CCM', 'CBCDR', ('PERIPH_CLK_SEL',), reg_offset=0x14, bit_offset=25, bit_width=1)};",
                f"inline constexpr auto kPeriphClock2PodfField = {field('CCM', 'CBCDR', ('PERIPH_CLK2_PODF',), reg_offset=0x14, bit_offset=27, bit_width=3)};",
                f"inline constexpr auto kPeriphClock2SelField = {field('CCM', 'CBCMR', ('PERIPH_CLK2_SEL',), reg_offset=0x18, bit_offset=12, bit_width=2)};",
                f"inline constexpr auto kPrePeriphClockSelField = {field('CCM', 'CBCMR', ('PRE_PERIPH_CLK_SEL',), reg_offset=0x18, bit_offset=18, bit_width=2)};",
                f"inline constexpr auto kAhbPodfBusyField = {field('CCM', 'CDHIPR', ('AHB_PODF_BUSY',), reg_offset=0x48, bit_offset=1, bit_width=1)};",
                f"inline constexpr auto kPeriph2ClockSelBusyField = {field('CCM', 'CDHIPR', ('PERIPH2_CLK_SEL_BUSY',), reg_offset=0x48, bit_offset=3, bit_width=1)};",
                f"inline constexpr auto kPeriphClockSelBusyField = {field('CCM', 'CDHIPR', ('PERIPH_CLK_SEL_BUSY',), reg_offset=0x48, bit_offset=5, bit_width=1)};",
                f"inline constexpr auto kArmPodfBusyField = {field('CCM', 'CDHIPR', ('ARM_PODF_BUSY',), reg_offset=0x48, bit_offset=16, bit_width=1)};",
                f"inline constexpr auto kPllArmDivSelectField = {field('CCM_ANALOG', 'PLL_ARM', ('DIV_SELECT',), reg_offset=0x00, bit_offset=0, bit_width=7)};",
                f"inline constexpr auto kPllArmPowerdownField = {field('CCM_ANALOG', 'PLL_ARM', ('POWERDOWN',), reg_offset=0x00, bit_offset=12, bit_width=1)};",
                f"inline constexpr auto kPllArmEnableField = {field('CCM_ANALOG', 'PLL_ARM', ('ENABLE',), reg_offset=0x00, bit_offset=13, bit_width=1)};",
                f"inline constexpr auto kPllArmBypassField = {field('CCM_ANALOG', 'PLL_ARM', ('BYPASS',), reg_offset=0x00, bit_offset=16, bit_width=1)};",
                f"inline constexpr auto kPllArmLockField = {field('CCM_ANALOG', 'PLL_ARM', ('LOCK',), reg_offset=0x00, bit_offset=31, bit_width=1)};",
                f"inline constexpr auto kDcdcStatusOkField = {field('DCDC', 'REG0', ('STS_DC_OK',), reg_offset=0x00, bit_offset=31, bit_width=1)};",
                f"inline constexpr auto kDcdcTargetVoltageField = {field('DCDC', 'REG3', ('TRG',), reg_offset=0x0C, bit_offset=0, bit_width=5)};",
                "",
            ]
        )
        apply_lines.extend(
            [
                "inline constexpr std::uint32_t kImxrtPeriphClockSelPrePeriph = 0u;",
                "inline constexpr std::uint32_t kImxrtPeriphClockSelPeriphClock2 = 1u;",
                "inline constexpr std::uint32_t kImxrtPeriphClock2SelOsc24M = 1u;",
                "inline constexpr std::uint32_t kImxrtPrePeriphClockSelPll1 = 0x3u;",
                "",
                "inline std::uint32_t encode_field_value(driver_semantics::RuntimeFieldRef field, std::uint32_t value) {",
                "  return (value << field.bit_offset) & field_mask(field);",
                "}",
                "",
                "inline bool imxrt_wait_transition_complete(driver_semantics::RuntimeFieldRef field) {",
                "  return wait_field_value(field, 0u);",
                "}",
                "",
                "inline std::uint32_t imxrt_target_voltage_mv(std::uint32_t sysclk_hz) {",
                "  return sysclk_hz > 528000000u ? 1250u : 1150u;",
                "}",
                "",
                "inline bool imxrt_set_core_voltage(std::uint32_t millivolts) {",
                "  const std::uint32_t target = (millivolts - 800u) / 25u;",
                "  write_field(kDcdcTargetVoltageField, target);",
                "  return wait_field_value(kDcdcStatusOkField, 1u);",
                "}",
                "",
                "inline bool imxrt_switch_to_periph_clk2_osc24m() {",
                "  write_field(kPeriphClock2PodfField, 0u);",
                "  write_field(kPeriphClock2SelField, kImxrtPeriphClock2SelOsc24M);",
                "  if (!imxrt_wait_transition_complete(kPeriph2ClockSelBusyField)) {",
                "    return false;",
                "  }",
                "  write_field(kPeriphClockSelField, kImxrtPeriphClockSelPeriphClock2);",
                "  return imxrt_wait_transition_complete(kPeriphClockSelBusyField);",
                "}",
                "",
                "inline bool imxrt_program_arm_pll(std::uint32_t div_select) {",
                "  write_register(",
                "      kCcmAnalogPllArmRegister,",
                "      encode_field_value(kPllArmPowerdownField, 1u));",
                "  std::uint32_t pll_arm = 0u;",
                "  pll_arm |= encode_field_value(kPllArmEnableField, 1u);",
                "  pll_arm |= encode_field_value(kPllArmDivSelectField, div_select);",
                "  write_register(kCcmAnalogPllArmRegister, pll_arm);",
                "  if (!wait_field_value(kPllArmLockField, 1u)) {",
                "    return false;",
                "  }",
                "  write_field(kPllArmBypassField, 0u);",
                "  return true;",
                "}",
                "",
                "inline bool imxrt_apply_prescalers(",
                "    std::uint32_t cpu_divisor,",
                "    std::uint32_t ahb_divisor,",
                "    std::uint32_t ipg_divisor) {",
                "  write_field(kArmPodfField, cpu_divisor - 1u);",
                "  if (!imxrt_wait_transition_complete(kArmPodfBusyField)) {",
                "    return false;",
                "  }",
                "  const auto current_cbcdr = read_register(kCcmCbcdrRegister);",
                "  const auto ahb_mask = field_mask(kAhbPodfField);",
                "  const auto ipg_mask = field_mask(kIpgPodfField);",
                "  std::uint32_t next_cbcdr = current_cbcdr & ~(ahb_mask | ipg_mask);",
                "  next_cbcdr |= encode_field_value(kAhbPodfField, ahb_divisor - 1u);",
                "  next_cbcdr |= encode_field_value(kIpgPodfField, ipg_divisor - 1u);",
                "  write_register(kCcmCbcdrRegister, next_cbcdr);",
                "  return imxrt_wait_transition_complete(kAhbPodfBusyField);",
                "}",
                "",
                "inline bool imxrt_switch_to_arm_pll_root() {",
                "  write_field(kPrePeriphClockSelField, kImxrtPrePeriphClockSelPll1);",
                "  write_field(kPeriphClockSelField, kImxrtPeriphClockSelPrePeriph);",
                "  return imxrt_wait_transition_complete(kPeriphClockSelBusyField);",
                "}",
                "",
                "template<SystemClockProfileId Id>",
                "inline bool apply_system_clock_profile() {",
                "  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {",
                "    return false;",
                "  } else if constexpr (Id == SystemClockProfileId::safe_osc24m) {",
                "    if (!imxrt_switch_to_periph_clk2_osc24m()) {",
                "      return false;",
                "    }",
                "    return imxrt_apply_prescalers(",
                "        SystemClockProfileTraits<Id>::kCpuPrescaler,",
                "        SystemClockProfileTraits<Id>::kAhbPrescaler,",
                "        SystemClockProfileTraits<Id>::kIpgPrescaler);",
                "  } else if constexpr (Id == SystemClockProfileId::default_arm_pll_600mhz) {",
                "    if (!imxrt_switch_to_periph_clk2_osc24m()) {",
                "      return false;",
                "    }",
                "    if (!imxrt_set_core_voltage(imxrt_target_voltage_mv(SystemClockProfileTraits<Id>::kSysclkHz))) {",
                "      return false;",
                "    }",
                "    if (!imxrt_program_arm_pll(SystemClockProfileTraits<Id>::kPllN)) {",
                "      return false;",
                "    }",
                "    if (!imxrt_apply_prescalers(",
                "            SystemClockProfileTraits<Id>::kCpuPrescaler,",
                "            SystemClockProfileTraits<Id>::kAhbPrescaler,",
                "            SystemClockProfileTraits<Id>::kIpgPrescaler)) {",
                "      return false;",
                "    }",
                "    return imxrt_switch_to_arm_pll_root();",
                "  } else {",
                "    return false;",
                "  }",
                "}",
            ]
        )
    else:
        apply_lines.extend(
            [
                "template<SystemClockProfileId Id>",
                "inline bool apply_system_clock_profile() {",
                "  return SystemClockProfileTraits<Id>::kPresent;",
                "}",
            ]
        )

    profile_rows: list[str] = []
    trait_lines: list[str] = [
        "template<SystemClockProfileId Id>",
        "struct SystemClockProfileTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::none;",
        "  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::none;",
        "  static constexpr std::uint32_t kSysclkHz = 0u;",
        "  static constexpr std::uint32_t kHclkHz = 0u;",
        "  static constexpr std::uint32_t kApb1Hz = 0u;",
        "  static constexpr std::uint32_t kApb2Hz = 0u;",
        "  static constexpr std::uint32_t kPclkHz = 0u;",
        "  static constexpr std::uint32_t kSourceHz = 0u;",
        "  static constexpr std::uint32_t kAhbPrescaler = 1u;",
        "  static constexpr std::uint32_t kApb1Prescaler = 1u;",
        "  static constexpr std::uint32_t kApb2Prescaler = 1u;",
        "  static constexpr std::uint32_t kOscillatorStartupCycles = 0u;",
        "  static constexpr std::uint32_t kMckPrescaler = 1u;",
        "  static constexpr std::uint32_t kCpuPrescaler = 1u;",
        "  static constexpr std::uint32_t kIpgPrescaler = 1u;",
        "  static constexpr std::uint32_t kPllM = 0u;",
        "  static constexpr std::uint32_t kPllN = 0u;",
        "  static constexpr std::uint32_t kPllP = 0u;",
        "  static constexpr std::uint32_t kPllQ = 0u;",
        "  static constexpr std::uint32_t kPllR = 0u;",
        "  static constexpr std::uint32_t kPllSource = 0u;",
        "  static constexpr std::uint32_t kFlashLatency = 0u;",
        "};",
        "",
    ]
    for profile in profiles:
        profile_id = profile_enum_map[profile.profile_id]
        trait_lines.extend(
            [
                "template<>",
                f"struct SystemClockProfileTraits<SystemClockProfileId::{profile_id}> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr SystemClockProfileKindId kKindId = "
                f"SystemClockProfileKindId::{kind_enum_map[profile.kind]};",
                "  static constexpr SystemClockSourceKindId kSourceKindId = "
                f"SystemClockSourceKindId::{source_enum_map[profile.source_kind]};",
                f"  static constexpr std::uint32_t kSysclkHz = {profile.sysclk_hz}u;",
                f"  static constexpr std::uint32_t kHclkHz = {profile.hclk_hz or 0}u;",
                f"  static constexpr std::uint32_t kApb1Hz = {profile.apb1_hz or 0}u;",
                f"  static constexpr std::uint32_t kApb2Hz = {profile.apb2_hz or 0}u;",
                f"  static constexpr std::uint32_t kPclkHz = {profile.pclk_hz or 0}u;",
                f"  static constexpr std::uint32_t kSourceHz = {profile.source_hz or 0}u;",
                f"  static constexpr std::uint32_t kAhbPrescaler = {profile.ahb_prescaler or 1}u;",
                f"  static constexpr std::uint32_t kApb1Prescaler = {profile.apb1_prescaler or 1}u;",
                f"  static constexpr std::uint32_t kApb2Prescaler = {profile.apb2_prescaler or 1}u;",
                "  static constexpr std::uint32_t kOscillatorStartupCycles = "
                f"{profile.oscillator_startup_cycles or 0}u;",
                f"  static constexpr std::uint32_t kMckPrescaler = {profile.mck_prescaler or 1}u;",
                f"  static constexpr std::uint32_t kCpuPrescaler = {profile.cpu_prescaler or 1}u;",
                f"  static constexpr std::uint32_t kIpgPrescaler = {profile.ipg_prescaler or 1}u;",
                f"  static constexpr std::uint32_t kPllM = {profile.pll_m or 0}u;",
                f"  static constexpr std::uint32_t kPllN = {profile.pll_n or 0}u;",
                f"  static constexpr std::uint32_t kPllP = {profile.pll_p or 0}u;",
                f"  static constexpr std::uint32_t kPllQ = {profile.pll_q or 0}u;",
                f"  static constexpr std::uint32_t kPllR = {profile.pll_r or 0}u;",
                "  static constexpr std::uint32_t kPllSource = "
                f"{(_stm32g0_pllsrc_value(profile.source_kind) if family_key == ('st', 'stm32g0') else 0)}u;",
                f"  static constexpr std::uint32_t kFlashLatency = {profile.flash_latency or 0}u;",
                "};",
                "",
            ]
        )
        profile_rows.append(
            "  {"
            f"SystemClockProfileId::{profile_id}, "
            f"SystemClockProfileKindId::{kind_enum_map[profile.kind]}, "
            f"SystemClockSourceKindId::{source_enum_map[profile.source_kind]}, "
            f"{profile.sysclk_hz}u, "
            f"{profile.hclk_hz or 0}u, "
            f"{profile.apb1_hz or 0}u, "
            f"{profile.apb2_hz or 0}u, "
            f"{profile.pclk_hz or 0}u"
            "},"
        )

    default_profile = next((profile for profile in profiles if profile.kind == "default"), None)
    safe_profile = next((profile for profile in profiles if profile.kind == "safe"), None)
    default_ref = (
        "SystemClockProfileId::none"
        if default_profile is None
        else f"SystemClockProfileId::{profile_enum_map[default_profile.profile_id]}"
    )
    safe_ref = (
        "SystemClockProfileId::none"
        if safe_profile is None
        else f"SystemClockProfileId::{profile_enum_map[safe_profile.profile_id]}"
    )

    body_lines = [
        "enum class SystemClockProfileId : std::uint16_t {",
        "  none,",
        *_enum_rows(profile_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class SystemClockProfileKindId : std::uint16_t {",
        "  none,",
        *_enum_rows(kind_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class SystemClockSourceKindId : std::uint16_t {",
        "  none,",
        *_enum_rows(source_enum_map, empty_identifier=None),
        "};",
        "",
        "struct SystemClockProfileDescriptor {",
        "  SystemClockProfileId profile_id;",
        "  SystemClockProfileKindId kind_id;",
        "  SystemClockSourceKindId source_kind_id;",
        "  std::uint32_t sysclk_hz;",
        "  std::uint32_t hclk_hz;",
        "  std::uint32_t apb1_hz;",
        "  std::uint32_t apb2_hz;",
        "  std::uint32_t pclk_hz;",
        "};",
        *_std_array_lines(
            type_name="SystemClockProfileDescriptor",
            variable_name="kSystemClockProfiles",
            row_lines=profile_rows,
        ),
        "",
        "using RuntimeRegisterRef = driver_semantics::RuntimeRegisterRef;",
        "using RuntimeFieldRef = driver_semantics::RuntimeFieldRef;",
        "",
        *trait_lines,
        "inline std::uint32_t read_register(driver_semantics::RuntimeRegisterRef reg) {",
        "  return *reinterpret_cast<volatile std::uint32_t*>(reg.base_address + reg.offset_bytes);",
        "}",
        "",
        "inline void write_register(driver_semantics::RuntimeRegisterRef reg, std::uint32_t value) {",
        "  *reinterpret_cast<volatile std::uint32_t*>(reg.base_address + reg.offset_bytes) = value;",
        "}",
        "",
        "inline std::uint32_t field_mask(driver_semantics::RuntimeFieldRef field) {",
        "  return ((field.bit_width >= 32u ? 0xFFFF'FFFFu : ((1u << field.bit_width) - 1u)) << field.bit_offset);",
        "}",
        "",
        "inline std::uint32_t read_field(driver_semantics::RuntimeFieldRef field) {",
        "  return (read_register(field.reg) & field_mask(field)) >> field.bit_offset;",
        "}",
        "",
        "inline void write_field(driver_semantics::RuntimeFieldRef field, std::uint32_t value) {",
        "  const auto current = read_register(field.reg);",
        "  const auto mask = field_mask(field);",
        "  write_register(field.reg, (current & ~mask) | ((value << field.bit_offset) & mask));",
        "}",
        "",
        "inline void set_field_bits(driver_semantics::RuntimeFieldRef field) {",
        "  write_field(field, (field.bit_width >= 32u ? 0xFFFF'FFFFu : ((1u << field.bit_width) - 1u)));",
        "}",
        "",
        "inline bool wait_field_value(",
        "    driver_semantics::RuntimeFieldRef field,",
        "    std::uint32_t expected,",
        "    std::uint32_t timeout = 100000u) {",
        "  while (timeout-- > 0u) {",
        "    if (read_field(field) == expected) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
        "",
        *extra_trait_lines,
        *apply_lines,
        "",
        "inline bool apply_default_system_clock() {",
        f"  return {('false' if default_profile is None else f'apply_system_clock_profile<{default_ref}>()')};",
        "}",
        "",
        "inline bool apply_safe_system_clock() {",
        f"  return {('false' if safe_profile is None else f'apply_system_clock_profile<{safe_ref}>()')};",
        "}",
    ]

    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "driver_semantics/common.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_system_clock_header_path(family_dir, device),
        content=content,
    )


__all__ = [
    "emit_runtime_system_clock_header",
    "runtime_system_clock_required_paths",
]
