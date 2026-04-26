"""Connector-driven descriptor enrichment over the transitional canonical IR."""

from __future__ import annotations

import re
from collections import defaultdict

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    CapabilityDescriptor,
    ClockGateDescriptor,
    ClockNodeLite,
    ClockSelectorLite,
    ConnectionCandidate,
    ConnectionGroup,
    DmaBindingDescriptor,
    DmaConflictGroup,
    DmaControllerDescriptor,
    DmaRouteDescriptor,
    InterruptBindingDescriptor,
    IpBlockDefinition,
    PeripheralClockBinding,
    ResetDescriptor,
    RouteOperation,
    RouteRequirement,
    SignalEndpoint,
    StartupDescriptor,
    VectorSlotDescriptor,
)

PERIPHERAL_CLASS_ALIASES = {
    "gpio": "gpio",
    # NOTE: "pio" is intentionally NOT aliased to "gpio".
    # Microchip SAM peripherals named PIO* (e.g. PIOA) are already mapped to
    # ip_name="gpio" by _infer_ip_metadata via the GPIOA-style special case.
    # RP2040 PIO0/PIO1 (Programmable I/O state machines) are a different class
    # entirely and must NOT be treated as GPIO controllers.
    "usart": "uart",
    "uart": "uart",
    "lpuart": "uart",
    "spi": "spi",
    "lpspi": "spi",
    "i2c": "i2c",
    "twihs": "i2c",
    # AVR "TWI" peripheral — Two-Wire Interface — is AVR's I2C master/slave block.
    "twi": "i2c",
    "dma": "dma",
    "dmamux": "dma-router",
    "xdmac": "dma",
    "adc": "adc",
    "afec": "adc",
    "apb_saradc": "adc",
    "saradc": "adc",
    # ESP32 classic SENS peripheral hosts ADC1 (SAR1) + ADC2 (SAR2) sub-blocks
    # alongside touch sensors and the hall sensor.  Classifying as `adc` lets
    # the ADC trait builder consume it; touch/hall stay outside the ADC contract.
    "sens": "adc",
    "dac": "dac",
    "dacc": "dac",
    "rtc": "rtc",
    "wdt": "watchdog",
    "rswdt": "watchdog",
    "iwdg": "watchdog",
    "wwdg": "watchdog",
    "wdog": "watchdog",
    "rtwdog": "watchdog",
    "pwm": "pwm",
    "tc": "timer",
    "tcc": "timer",
    "tim": "timer",
    # AVR-Dx timer/counter variants: TCA (16-bit), TCB (16-bit), TCD (12-bit).
    "tca": "timer",
    "tcb": "timer",
    "tcd": "timer",
    "fdcan": "can",
    "mcan": "can",
    "can": "can",
    "usb": "usb",
    "otg_fs": "usb",
    "otg_fs_global": "usb",
    "otg_fs_device": "usb",
    "otg_fs_host": "usb",
    "otg_fs_pwrclk": "usb",
    "otg_hs": "usb",
    "otg_hs_global": "usb",
    "otg_hs_device": "usb",
    "otg_hs_host": "usb",
    "otg_hs_pwrclk": "usb",
    "usbhs": "usb",
    "eth": "eth",
    "gmac": "eth",
    "enet": "eth",
    "ethernet": "eth",
    "ethernet_mac": "eth",
    "ethernet_dma": "eth",
    "ethernet_mmc": "eth",
}

OUTPUT_SIGNALS = {"tx", "sck", "mosi", "pwmh", "pwml", "tioa", "tclk", "cantx", "ck"}
INPUT_SIGNALS = {"rx", "miso", "cts", "rts", "tiob", "canrx", "d", "din"}
BIDIRECTIONAL_SIGNALS = {"sda", "sdio"}
GROUP_SIGNAL_BUNDLES: dict[str, tuple[tuple[str, ...], ...]] = {
    "uart": (("tx", "rx"), ("tx", "rx", "cts", "rts")),
    "i2c": (("scl", "sda"),),
    "spi": (("sck", "mosi", "miso"), ("sck", "cs")),
    "can": (("tx", "rx"),),
}
VOLATILE_MEMORY_KINDS = {"sram", "ram", "itcm", "dtcm"}
NONVOLATILE_MEMORY_KINDS = {"flash", "rom", "qspi-flash", "xip-flash"}
RETAINED_MEMORY_KINDS = {"backup", "retention"}
SYSTEM_VECTOR_BASELINES = {
    "cortex-m0": (
        (0, "__stack_top", None, "initial-stack-pointer"),
        (1, "Reset_Handler", None, "reset-handler"),
        (2, "NMI_Handler", None, "system-exception"),
        (3, "HardFault_Handler", None, "system-exception"),
        (4, "Reserved_Handler_4", None, "reserved"),
        (5, "Reserved_Handler_5", None, "reserved"),
        (6, "Reserved_Handler_6", None, "reserved"),
        (7, "Reserved_Handler_7", None, "reserved"),
        (8, "Reserved_Handler_8", None, "reserved"),
        (9, "Reserved_Handler_9", None, "reserved"),
        (10, "Reserved_Handler_10", None, "reserved"),
        (11, "SVCall_Handler", None, "system-exception"),
        (12, "Reserved_Handler_12", None, "reserved"),
        (13, "Reserved_Handler_13", None, "reserved"),
        (14, "PendSV_Handler", None, "system-exception"),
        (15, "SysTick_Handler", None, "system-exception"),
    ),
    "cortex-m0plus": (
        (0, "__stack_top", None, "initial-stack-pointer"),
        (1, "Reset_Handler", None, "reset-handler"),
        (2, "NMI_Handler", None, "system-exception"),
        (3, "HardFault_Handler", None, "system-exception"),
        (4, "Reserved_Handler_4", None, "reserved"),
        (5, "Reserved_Handler_5", None, "reserved"),
        (6, "Reserved_Handler_6", None, "reserved"),
        (7, "Reserved_Handler_7", None, "reserved"),
        (8, "Reserved_Handler_8", None, "reserved"),
        (9, "Reserved_Handler_9", None, "reserved"),
        (10, "Reserved_Handler_10", None, "reserved"),
        (11, "SVCall_Handler", None, "system-exception"),
        (12, "Reserved_Handler_12", None, "reserved"),
        (13, "Reserved_Handler_13", None, "reserved"),
        (14, "PendSV_Handler", None, "system-exception"),
        (15, "SysTick_Handler", None, "system-exception"),
    ),
    "cortex-m4": (
        (0, "__stack_top", None, "initial-stack-pointer"),
        (1, "Reset_Handler", None, "reset-handler"),
        (2, "NMI_Handler", None, "system-exception"),
        (3, "HardFault_Handler", None, "system-exception"),
        (4, "MemManage_Handler", None, "system-exception"),
        (5, "BusFault_Handler", None, "system-exception"),
        (6, "UsageFault_Handler", None, "system-exception"),
        (7, "Reserved_Handler_7", None, "reserved"),
        (8, "Reserved_Handler_8", None, "reserved"),
        (9, "Reserved_Handler_9", None, "reserved"),
        (10, "Reserved_Handler_10", None, "reserved"),
        (11, "SVCall_Handler", None, "system-exception"),
        (12, "DebugMon_Handler", None, "system-exception"),
        (13, "Reserved_Handler_13", None, "reserved"),
        (14, "PendSV_Handler", None, "system-exception"),
        (15, "SysTick_Handler", None, "system-exception"),
    ),
    # cortex-m4f is the FPU variant of Cortex-M4; vector table is identical.
    "cortex-m4f": (
        (0, "__stack_top", None, "initial-stack-pointer"),
        (1, "Reset_Handler", None, "reset-handler"),
        (2, "NMI_Handler", None, "system-exception"),
        (3, "HardFault_Handler", None, "system-exception"),
        (4, "MemManage_Handler", None, "system-exception"),
        (5, "BusFault_Handler", None, "system-exception"),
        (6, "UsageFault_Handler", None, "system-exception"),
        (7, "Reserved_Handler_7", None, "reserved"),
        (8, "Reserved_Handler_8", None, "reserved"),
        (9, "Reserved_Handler_9", None, "reserved"),
        (10, "Reserved_Handler_10", None, "reserved"),
        (11, "SVCall_Handler", None, "system-exception"),
        (12, "DebugMon_Handler", None, "system-exception"),
        (13, "Reserved_Handler_13", None, "reserved"),
        (14, "PendSV_Handler", None, "system-exception"),
        (15, "SysTick_Handler", None, "system-exception"),
    ),
    "cortex-m7": (
        (0, "__stack_top", None, "initial-stack-pointer"),
        (1, "Reset_Handler", None, "reset-handler"),
        (2, "NMI_Handler", None, "system-exception"),
        (3, "HardFault_Handler", None, "system-exception"),
        (4, "MemManage_Handler", None, "system-exception"),
        (5, "BusFault_Handler", None, "system-exception"),
        (6, "UsageFault_Handler", None, "system-exception"),
        (7, "Reserved_Handler_7", None, "reserved"),
        (8, "Reserved_Handler_8", None, "reserved"),
        (9, "Reserved_Handler_9", None, "reserved"),
        (10, "Reserved_Handler_10", None, "reserved"),
        (11, "SVCall_Handler", None, "system-exception"),
        (12, "DebugMon_Handler", None, "system-exception"),
        (13, "Reserved_Handler_13", None, "reserved"),
        (14, "PendSV_Handler", None, "system-exception"),
        (15, "SysTick_Handler", None, "system-exception"),
    ),
    # cortex-m7f is the FPU variant of Cortex-M7; vector table is identical.
    "cortex-m7f": (
        (0, "__stack_top", None, "initial-stack-pointer"),
        (1, "Reset_Handler", None, "reset-handler"),
        (2, "NMI_Handler", None, "system-exception"),
        (3, "HardFault_Handler", None, "system-exception"),
        (4, "MemManage_Handler", None, "system-exception"),
        (5, "BusFault_Handler", None, "system-exception"),
        (6, "UsageFault_Handler", None, "system-exception"),
        (7, "Reserved_Handler_7", None, "reserved"),
        (8, "Reserved_Handler_8", None, "reserved"),
        (9, "Reserved_Handler_9", None, "reserved"),
        (10, "Reserved_Handler_10", None, "reserved"),
        (11, "SVCall_Handler", None, "system-exception"),
        (12, "DebugMon_Handler", None, "system-exception"),
        (13, "Reserved_Handler_13", None, "reserved"),
        (14, "PendSV_Handler", None, "system-exception"),
        (15, "SysTick_Handler", None, "system-exception"),
    ),
    # RP2040 is dual-core Cortex-M0+; the emitted vector table targets core 0
    # only (single-core-perspective). The exception model is identical to M0+.
    "cortex-m0plus-dual": (
        (0, "__stack_top", None, "initial-stack-pointer"),
        (1, "Reset_Handler", None, "reset-handler"),
        (2, "NMI_Handler", None, "system-exception"),
        (3, "HardFault_Handler", None, "system-exception"),
        (4, "Reserved_Handler_4", None, "reserved"),
        (5, "Reserved_Handler_5", None, "reserved"),
        (6, "Reserved_Handler_6", None, "reserved"),
        (7, "Reserved_Handler_7", None, "reserved"),
        (8, "Reserved_Handler_8", None, "reserved"),
        (9, "Reserved_Handler_9", None, "reserved"),
        (10, "Reserved_Handler_10", None, "reserved"),
        (11, "SVCall_Handler", None, "system-exception"),
        (12, "Reserved_Handler_12", None, "reserved"),
        (13, "Reserved_Handler_13", None, "reserved"),
        (14, "PendSV_Handler", None, "system-exception"),
        (15, "SysTick_Handler", None, "system-exception"),
    ),
    # RISC-V CLIC (Compact Local Interrupt Controller) used by ESP32-C3 and other
    # RV32 SoCs.  There is no ARM-style fixed vector table; interrupts are routed via
    # mtvec.  Only the reset entry is defined here — peripheral interrupts are wired
    # entirely from SVD data.
    "rv32imc": ((0, "Reset_Handler", None, "reset-handler"),),
    # Generic RISC-V aliases — other RV32 variants map to the same minimal baseline.
    "rv32imac": ((0, "Reset_Handler", None, "reset-handler"),),
    "riscv": ((0, "Reset_Handler", None, "reset-handler"),),
    # Xtensa LX6 (ESP32 classic).  Dual-core: PRO_CPU + APP_CPU share the same
    # baseline; APP_CPU bring-up is handled by ``bring_up_app_cpu()`` in the
    # generated startup.cpp.  The reset vector for both cores is fixed in
    # internal ROM; no ARM-style exception table is used.
    "xtensa-lx6": ((0, "Reset_Handler", None, "reset-handler"),),
    # Xtensa LX7 (ESP32-S3). Dual-core like the LX6 above; same baseline.
    # See ``runtime_xtensa_startup.py`` for the dual-core control plane
    # (``Reset_Handler`` / ``Reset_Handler_CPU1`` / ``bring_up_app_cpu``).
    "xtensa-lx7": ((0, "Reset_Handler", None, "reset-handler"),),
    # 8-bit AVR (Microchip AVR-DA and family).  The interrupt vector table starts
    # directly with device-specific handlers — no ARM system exception prefix,
    # no RISC-V mtvec.  Slot 0 is reserved for the reset vector (``__vector_0``)
    # which avr-gcc's crt0 expects at address 0.  Peripheral interrupts are
    # numbered starting at slot 1 by their ATDF interrupt-line value.
    "avr8": ((0, "__vector_0", None, "reset-handler"),),
}
ST_RCC_TARGET_PATTERN = re.compile(r"^RCC_(?P<register>[A-Z0-9_]+)\.(?P<field>[A-Z0-9_]+)$")
MICROCHIP_PMC_PID_TARGET_PATTERN = re.compile(r"^PMC\.PID(?P<pid>\d+)$")
REGISTER_FIELD_TARGET_PATTERN = re.compile(r"^(?P<lhs>[A-Z0-9_]+)\.(?P<field>[A-Z0-9_]+)$")


def _sanitize(value: str) -> str:
    return "".join(character.lower() if character.isalnum() else "-" for character in value).strip(
        "-"
    )


def canonical_peripheral_class(ip_name: str) -> str:
    return PERIPHERAL_CLASS_ALIASES.get(ip_name.lower(), ip_name.lower())


def _direction_for_signal(signal_name: str) -> str | None:
    token = signal_name.lower()
    if token in BIDIRECTIONAL_SIGNALS:
        return "bidirectional"
    if any(token.startswith(prefix) for prefix in OUTPUT_SIGNALS):
        return "output"
    if any(token.startswith(prefix) for prefix in INPUT_SIGNALS):
        return "input"
    return None


def _runtime_schema_id(
    *,
    subsystem: str,
    vendor: str,
    ip_name: str | None,
    ip_version: str | None,
    fallback: str,
) -> str:
    variant = ip_version or ip_name or fallback
    return f"alloy.{subsystem}.{_sanitize(vendor)}-{_sanitize(variant)}"


def _pinmux_backend_schema_id(vendor: str, family: str | None = None) -> str:
    match (vendor, family):
        case ("st", _):
            return "alloy.pinmux.stm32-af-v1"
        case ("microchip", "avr-da"):
            # AVR-Dx PORTMUX: selects one of N predefined pin assignments per
            # peripheral by writing an index into PORTMUX.<IP>ROUTEA.  On AVR
            # `af_number` on PinSignals encodes the PORTMUX selection index
            # (0 = default assignment, 1/2 = alternate assignments).
            return "alloy.pinmux.avr-portmux-v1"
        case ("microchip", _):
            return "alloy.pinmux.sam-pio-v1"
        case ("nxp", _):
            return "alloy.pinmux.imxrt-iomuxc-v1"
        case ("raspberrypi", _):
            return "alloy.pinmux.rp2040-funcsel-v1"
        case ("espressif", _):
            # ESP32 IO Matrix: a fully-programmable GPIO signal router.
            # Consumer semantics are distinct from ARM AF: `af_number` on
            # Espressif PinSignals carries the IO Matrix signal index from
            # esp-idf `gpio_sig_map.h`, not a per-pin alternate-function slot.
            return "alloy.pinmux.espressif-iomatrix-v1"
        case _:
            return f"alloy.pinmux.{_sanitize(vendor)}-generic-v1"


def _clock_backend_schema_id(device: CanonicalDeviceIR) -> str:
    for peripheral in device.peripherals:
        peripheral_class = canonical_peripheral_class(peripheral.ip_name)
        if peripheral_class in {"rcc", "pmc", "ccm"}:
            return _runtime_schema_id(
                subsystem="clock",
                vendor=device.identity.vendor,
                ip_name=peripheral.ip_name,
                ip_version=peripheral.ip_version,
                fallback=peripheral_class,
            )
    return _runtime_schema_id(
        subsystem="clock",
        vendor=device.identity.vendor,
        ip_name=None,
        ip_version=None,
        fallback="generic-clock-v1",
    )


def _lookup_register_offset(
    device: CanonicalDeviceIR,
    *,
    peripheral_name: str,
    register_name: str,
) -> int | None:
    for register in device.registers:
        if (
            register.peripheral == peripheral_name
            and register.name.upper() == register_name.upper()
        ):
            return register.offset_bytes
    return None


def _lookup_register_id(
    device: CanonicalDeviceIR,
    *,
    peripheral_name: str,
    register_name: str,
) -> str | None:
    for register in device.registers:
        if (
            register.peripheral == peripheral_name
            and register.name.upper() == register_name.upper()
        ):
            return register.register_id
    return None


def _lookup_register_field_id(
    device: CanonicalDeviceIR,
    *,
    peripheral_name: str,
    register_name: str,
    field_name: str,
) -> str | None:
    for register_field in device.register_fields:
        if (
            register_field.peripheral == peripheral_name
            and register_field.register_name.upper() == register_name.upper()
            and register_field.name.upper() == field_name.upper()
        ):
            return register_field.field_id
    return None


def _typed_register_ref(
    device: CanonicalDeviceIR,
    target: str,
    *,
    operation_kind: str | None = None,
) -> tuple[str | None, str | None, int | None, str | None, str | None]:
    match = ST_RCC_TARGET_PATTERN.match(target)
    if match is not None:
        register_name = match.group("register")
        field_name = match.group("field")
        return (
            "RCC",
            register_name,
            _lookup_register_offset(device, peripheral_name="RCC", register_name=register_name),
            _lookup_register_id(device, peripheral_name="RCC", register_name=register_name),
            _lookup_register_field_id(
                device,
                peripheral_name="RCC",
                register_name=register_name,
                field_name=field_name,
            ),
        )
    pmc_match = MICROCHIP_PMC_PID_TARGET_PATTERN.match(target)
    if pmc_match is not None:
        pid = int(pmc_match.group("pid"))
        register_suffix = "0" if pid < 32 else "1"
        normalized_kind = None if operation_kind is None else operation_kind.lower()
        register_prefix = "PCDR" if normalized_kind == "clear-bit" else "PCER"
        register_name = f"{register_prefix}{register_suffix}"
        field_name = f"PID{pid}"
        return (
            "PMC",
            register_name,
            _lookup_register_offset(device, peripheral_name="PMC", register_name=register_name),
            _lookup_register_id(device, peripheral_name="PMC", register_name=register_name),
            _lookup_register_field_id(
                device,
                peripheral_name="PMC",
                register_name=register_name,
                field_name=field_name,
            ),
        )
    generic_match = REGISTER_FIELD_TARGET_PATTERN.match(target)
    if generic_match is None:
        return (None, None, None, None, None)
    lhs = generic_match.group("lhs")
    field_name = generic_match.group("field")
    if "_" in lhs:
        peripheral_name, register_name = lhs.split("_", maxsplit=1)
    else:
        peripheral_name, register_name = lhs, None
    if register_name is None:
        return (peripheral_name, field_name, None, None, None)
    return (
        peripheral_name,
        register_name,
        _lookup_register_offset(
            device,
            peripheral_name=peripheral_name,
            register_name=register_name,
        ),
        _lookup_register_id(
            device,
            peripheral_name=peripheral_name,
            register_name=register_name,
        ),
        _lookup_register_field_id(
            device,
            peripheral_name=peripheral_name,
            register_name=register_name,
            field_name=field_name,
        ),
    )


def _domain_node_id(signal: str) -> str:
    register_domain = signal.rsplit(".", maxsplit=1)[0] if "." in signal else signal
    return f"clock-node:{_sanitize(register_domain)}"


def _domain_node_shape(signal: str) -> tuple[str, str]:
    normalized = signal.upper()
    if normalized.startswith("RCC_AHB"):
        return ("clock-root", "ahb-domain")
    if normalized.startswith("RCC_APB"):
        return ("clock-root", "apb-domain")
    if normalized.startswith("RCC_IOP"):
        return ("clock-root", "gpio-domain")
    if normalized.startswith("PMC."):
        return ("clock-root", "pmc-domain")
    if normalized.startswith("CCM_"):
        return ("clock-root", "ccm-domain")
    return ("clock-root", "gate-domain")


def _symbol_name(interrupt_name: str) -> str:
    if interrupt_name.endswith("_IRQHandler"):
        return interrupt_name
    return f"{interrupt_name}_IRQHandler"


def _interrupt_core_affinity(peripheral_name: str | None) -> str:
    """Derive the core affinity for one interrupt from its owning peripheral.

    Multi-core Xtensa families (ESP32 LX6, ESP32-S3 LX7) surface the per-core
    interrupt matrix as distinct peripherals: ``INTERRUPT_CORE0`` /
    ``INTERRUPT_CORE1`` on ESP32-S3 (independent SVD peripherals) and a
    single ``DPORT`` block carrying ``PRO_*`` / ``APP_*`` register pairs on
    the ESP32 classic.  Vectors routed through the APP_CPU side (peripheral
    name contains ``CORE1`` or starts with ``DPORT_APP_``) carry
    ``"cpu1"``; everything else defaults to ``"cpu0"``.

    Single-core targets (Cortex-M, RISC-V mononúcleo, AVR8) never see these
    naming patterns and consistently land on ``"cpu0"`` — keeping the
    existing emitters unchanged.
    """
    if peripheral_name is None:
        return "cpu0"
    upper = peripheral_name.upper()
    if upper == "INTERRUPT_CORE1" or upper.startswith("INTERRUPT_CORE1_"):
        return "cpu1"
    if upper.startswith("DPORT_APP_"):
        return "cpu1"
    return "cpu0"


def _system_vector_core_affinity(core_name: str, kind: str) -> str:
    """Derive the core affinity for one system-baseline vector.

    On dual-core Xtensa families a few system exceptions (NMI, double-fault)
    exist symmetrically on both cores.  Marking them ``"shared"`` lets the
    emitter put them in both ``_vectors_cpu0[]`` and ``_vectors_cpu1[]``.
    Any other system slot (reset, the canonical ``Reset_Handler``) belongs
    to PRO_CPU only.
    """
    normalized = core_name.lower()
    if normalized.startswith("xtensa") and kind in {"nmi", "double-exception"}:
        return "shared"
    return "cpu0"


def _interrupt_aliases(interrupt_name: str, peripheral_name: str | None) -> tuple[str, ...]:
    aliases: list[str] = []
    if peripheral_name is not None and peripheral_name.upper() not in interrupt_name.upper():
        aliases.append(peripheral_name)
    symbol_name = _symbol_name(interrupt_name)
    if symbol_name != interrupt_name:
        aliases.append(symbol_name)
    return tuple(dict.fromkeys(aliases))


def _system_vector_baseline(core_name: str) -> tuple[tuple[int, str, str | None, str], ...]:
    normalized = core_name.lower()
    baseline = SYSTEM_VECTOR_BASELINES.get(normalized)
    if baseline is None:
        supported = ", ".join(sorted(SYSTEM_VECTOR_BASELINES))
        raise StageExecutionError(
            f"Unknown core '{core_name}' — no system vector baseline defined. "
            f"Supported cores: {supported}. "
            "Add an entry to SYSTEM_VECTOR_BASELINES in connector_model.py."
        )
    return baseline


def _memory_startup_roles(kind: str, access: str) -> tuple[str, ...]:
    normalized_kind = kind.lower()
    normalized_access = access.lower()
    roles: list[str] = []
    if normalized_kind in NONVOLATILE_MEMORY_KINDS:
        roles.extend(["nonvolatile", "copy-source"])
        if "x" in normalized_access:
            roles.append("vector-source")
    if normalized_kind in VOLATILE_MEMORY_KINDS:
        roles.extend(["volatile-target", "copy-target", "zero-target", "stack-target"])
    if normalized_kind in RETAINED_MEMORY_KINDS:
        roles.extend(["retained-target", "volatile-target"])
    return tuple(dict.fromkeys(roles))


def canonical_signal_role(peripheral_class: str, signal_name: str) -> str | None:
    normalized = signal_name.lower()
    if peripheral_class == "uart":
        if normalized.startswith("tx"):
            return "tx"
        if normalized.startswith("rx"):
            return "rx"
        if normalized.startswith("cts"):
            return "cts"
        if normalized.startswith("rts"):
            return "rts"
    if peripheral_class == "i2c":
        if normalized.startswith("scl") or normalized.startswith("twck"):
            return "scl"
        if normalized.startswith("sda") or normalized.startswith("twd"):
            return "sda"
    if peripheral_class == "spi":
        if normalized in {"miso", "mosi"}:
            return normalized
        if normalized.endswith("sck") or normalized == "spck":
            return "sck"
        if "pcs" in normalized:
            return "cs"
    if peripheral_class == "can":
        if normalized.startswith("cantx") or normalized.startswith("tx"):
            return "tx"
        if normalized.startswith("canrx") or normalized.startswith("rx"):
            return "rx"
    return None


def _bundle_candidates(
    *,
    peripheral_name: str,
    peripheral_class: str,
    package_name: str,
    candidate_map: dict[str, ConnectionCandidate],
) -> tuple[tuple[ConnectionGroup, ...], dict[str, str]]:
    candidates = [
        candidate for candidate in candidate_map.values() if candidate.peripheral == peripheral_name
    ]
    by_role: dict[str, list[str]] = defaultdict(list)
    for candidate in candidates:
        role = canonical_signal_role(peripheral_class, candidate.signal)
        if role is None:
            continue
        by_role[role].append(candidate.candidate_id)

    groups: list[ConnectionGroup] = []
    primary_group_ids: dict[str, str] = {}
    for bundle in GROUP_SIGNAL_BUNDLES.get(peripheral_class, ()):
        if not all(by_role.get(role) for role in bundle):
            continue
        candidate_ids = tuple(
            sorted({candidate_id for role in bundle for candidate_id in by_role[role]})
        )
        groups.append(
            ConnectionGroup(
                group_id=(
                    f"group:{_sanitize(peripheral_name)}:{_sanitize(package_name)}:"
                    f"{'-'.join(bundle)}"
                ),
                peripheral=peripheral_name,
                signals=bundle,
                candidate_ids=candidate_ids,
                package=package_name,
                conflict_group=(
                    f"conflict:{_sanitize(peripheral_name)}:{_sanitize(package_name)}:"
                    f"{'-'.join(bundle)}"
                ),
                provenance=candidate_map[candidate_ids[0]].provenance,
            )
        )
        for candidate_id in candidate_ids:
            primary_group_ids.setdefault(candidate_id, groups[-1].group_id)

    if groups:
        return tuple(groups), primary_group_ids

    distinct_signals = sorted({candidate.signal for candidate in candidates})
    if len(distinct_signals) < 2:
        return (), {}
    candidate_ids = tuple(sorted(candidate.candidate_id for candidate in candidates))
    group = ConnectionGroup(
        group_id=f"group:{_sanitize(peripheral_name)}:{_sanitize(package_name)}:all-signals",
        peripheral=peripheral_name,
        signals=tuple(distinct_signals),
        candidate_ids=candidate_ids,
        package=package_name,
        conflict_group=(
            f"conflict:{_sanitize(peripheral_name)}:{_sanitize(package_name)}:all-signals"
        ),
        provenance=candidate_map[candidate_ids[0]].provenance,
    )
    return (group,), {candidate_id: group.group_id for candidate_id in candidate_ids}


def enrich_connector_descriptors(device: CanonicalDeviceIR) -> CanonicalDeviceIR:
    """Derive connector-driven descriptors from the transitional canonical IR."""
    peripheral_map = {peripheral.name: peripheral for peripheral in device.peripherals}
    pin_constraints = defaultdict(list)
    for constraint in device.pin_constraints:
        pin_constraints[constraint.pin].append(constraint)
    bonded_pads_by_pin = defaultdict(list)
    for package_pad in device.package_pads:
        if package_pad.bonding_state == "bonded" and package_pad.bonded_pin is not None:
            bonded_pads_by_pin[package_pad.bonded_pin].append(package_pad)

    endpoint_map: dict[str, SignalEndpoint] = {}
    block_roles: dict[tuple[str, str], set[str]] = defaultdict(set)
    block_capabilities: dict[tuple[str, str], set[str]] = defaultdict(set)
    capability_map: dict[str, CapabilityDescriptor] = {}
    requirement_map: dict[str, RouteRequirement] = {}
    operation_map: dict[str, RouteOperation] = {}
    candidate_map: dict[str, ConnectionCandidate] = {}
    clock_schema_id = _clock_backend_schema_id(device)
    pinmux_schema_id = _pinmux_backend_schema_id(device.identity.vendor, device.identity.family)
    for peripheral in device.peripherals:
        if peripheral.rcc_enable_signal is not None:
            requirement_id = f"requirement:clock-enable:{_sanitize(peripheral.name)}"
            clock_gate_id = f"gate:{_sanitize(peripheral.name)}"
            requirement_map.setdefault(
                requirement_id,
                RouteRequirement(
                    requirement_id=requirement_id,
                    kind="clock-enable",
                    target=peripheral.rcc_enable_signal,
                    value="1",
                    target_ref_kind="clock-gate",
                    target_ref_id=clock_gate_id,
                    value_ref_kind="int",
                    value_int=1,
                    provenance=peripheral.provenance,
                ),
            )
            operation_id = f"operation:clock-enable:{_sanitize(peripheral.name)}"
            (
                register_peripheral,
                register_name,
                register_offset,
                register_id,
                register_field_id,
            ) = _typed_register_ref(
                device,
                peripheral.rcc_enable_signal,
                operation_kind="set-bit",
            )
            operation_map.setdefault(
                operation_id,
                RouteOperation(
                    operation_id=operation_id,
                    kind="set-bit",
                    target=peripheral.rcc_enable_signal,
                    value="1",
                    schema_id=clock_schema_id,
                    subject_kind="peripheral",
                    subject_id=peripheral.name,
                    register_peripheral=register_peripheral,
                    register_name=register_name,
                    register_offset=register_offset,
                    register_id=register_id,
                    register_field_id=register_field_id,
                    target_ref_kind="clock-gate",
                    target_ref_id=clock_gate_id,
                    value_ref_kind="int",
                    value_int=1,
                    provenance=peripheral.provenance,
                ),
            )
        if peripheral.rcc_reset_signal is not None:
            requirement_id = f"requirement:reset-release:{_sanitize(peripheral.name)}"
            reset_id = f"reset:{_sanitize(peripheral.name)}"
            requirement_map.setdefault(
                requirement_id,
                RouteRequirement(
                    requirement_id=requirement_id,
                    kind="reset-release",
                    target=peripheral.rcc_reset_signal,
                    value="0",
                    target_ref_kind="reset",
                    target_ref_id=reset_id,
                    value_ref_kind="int",
                    value_int=0,
                    provenance=peripheral.provenance,
                ),
            )
            operation_id = f"operation:reset-release:{_sanitize(peripheral.name)}"
            (
                register_peripheral,
                register_name,
                register_offset,
                register_id,
                register_field_id,
            ) = _typed_register_ref(
                device,
                peripheral.rcc_reset_signal,
                operation_kind="clear-bit",
            )
            operation_map.setdefault(
                operation_id,
                RouteOperation(
                    operation_id=operation_id,
                    kind="clear-bit",
                    target=peripheral.rcc_reset_signal,
                    value="0",
                    schema_id=clock_schema_id,
                    subject_kind="peripheral",
                    subject_id=peripheral.name,
                    register_peripheral=register_peripheral,
                    register_name=register_name,
                    register_offset=register_offset,
                    register_id=register_id,
                    register_field_id=register_field_id,
                    target_ref_kind="reset",
                    target_ref_id=reset_id,
                    value_ref_kind="int",
                    value_int=0,
                    provenance=peripheral.provenance,
                ),
            )

    package_requirement_id = f"requirement:package:{_sanitize(device.identity.package)}"
    requirement_map.setdefault(
        package_requirement_id,
        RouteRequirement(
            requirement_id=package_requirement_id,
            kind="package",
            target=device.identity.package,
            value="selected",
            target_ref_kind="package",
            target_ref_id=device.identity.package,
            value_ref_kind="state",
            value_ref_id="selected",
            provenance=device.provenance,
        ),
    )

    for pin in device.pins:
        for signal in pin.signals:
            if signal.peripheral is None or signal.signal is None:
                continue
            peripheral = peripheral_map.get(signal.peripheral)
            if peripheral is None:
                continue
            peripheral_class = canonical_peripheral_class(peripheral.ip_name)
            endpoint_id = f"endpoint:{peripheral_class}:{_sanitize(signal.signal)}"
            endpoint_map.setdefault(
                endpoint_id,
                SignalEndpoint(
                    endpoint_id=endpoint_id,
                    peripheral_class=peripheral_class,
                    signal=signal.signal,
                    direction=_direction_for_signal(signal.signal),
                    provenance=signal.provenance,
                ),
            )

            if signal.af_number is None and signal.function == "gpio":
                continue

            route_kind = {
                "st": "alternate-function",
                "microchip": "peripheral-mux",
                "nxp": "iomuxc-mux",
            }.get(device.identity.vendor, "mux")
            route_selector = None if signal.af_number is None else f"selector:{signal.af_number}"
            requirement_ids = [package_requirement_id]
            operation_ids = []

            if bonded_pads_by_pin.get(pin.name):
                bonded_requirement_id = (
                    f"requirement:bonded-pin:{_sanitize(device.identity.package)}:"
                    f"{_sanitize(pin.name)}"
                )
                requirement_map.setdefault(
                    bonded_requirement_id,
                    RouteRequirement(
                        requirement_id=bonded_requirement_id,
                        kind="bonded-pin",
                        target=pin.name,
                        value=device.identity.package,
                        target_ref_kind="pin",
                        target_ref_id=pin.name,
                        value_ref_kind="package",
                        value_ref_id=device.identity.package,
                        provenance=signal.provenance,
                    ),
                )
                requirement_ids.append(bonded_requirement_id)

            for constraint in sorted(
                pin_constraints.get(pin.name, ()),
                key=lambda item: item.constraint_id,
            ):
                requirement_map.setdefault(
                    f"requirement:{constraint.constraint_id}",
                    RouteRequirement(
                        requirement_id=f"requirement:{constraint.constraint_id}",
                        kind="pin-constraint",
                        target=constraint.pin,
                        value=constraint.kind
                        if constraint.value is None
                        else f"{constraint.kind}:{constraint.value}",
                        target_ref_kind="pin",
                        target_ref_id=constraint.pin,
                        value_ref_kind="constraint",
                        value_ref_id=constraint.constraint_id,
                        provenance=constraint.provenance,
                    ),
                )
                requirement_ids.append(f"requirement:{constraint.constraint_id}")

            clock_requirement_id = f"requirement:clock-enable:{_sanitize(peripheral.name)}"
            reset_requirement_id = f"requirement:reset-release:{_sanitize(peripheral.name)}"
            if clock_requirement_id in requirement_map:
                requirement_ids.append(clock_requirement_id)
                operation_ids.append(f"operation:clock-enable:{_sanitize(peripheral.name)}")
            if reset_requirement_id in requirement_map:
                requirement_ids.append(reset_requirement_id)
                operation_ids.append(f"operation:reset-release:{_sanitize(peripheral.name)}")

            if route_selector is not None:
                selector_requirement_id = (
                    f"requirement:source-select:{_sanitize(pin.name)}:{_sanitize(peripheral.name)}:"
                    f"{_sanitize(signal.signal)}"
                )
                requirement_map.setdefault(
                    selector_requirement_id,
                    RouteRequirement(
                        requirement_id=selector_requirement_id,
                        kind="source-select",
                        target=f"pinmux.{pin.name}",
                        value=route_selector,
                        target_ref_kind="pin",
                        target_ref_id=pin.name,
                        value_ref_kind="selector",
                        value_ref_id=route_selector,
                        value_int=signal.af_number,
                        provenance=signal.provenance,
                    ),
                )
                requirement_ids.append(selector_requirement_id)
                operation_id = (
                    f"operation:route:{_sanitize(pin.name)}:{_sanitize(peripheral.name)}:"
                    f"{_sanitize(signal.signal)}"
                )
                operation_map.setdefault(
                    operation_id,
                    RouteOperation(
                        operation_id=operation_id,
                        kind="write-selector",
                        target=f"pinmux.{pin.name}",
                        value=str(signal.af_number),
                        schema_id=pinmux_schema_id,
                        subject_kind="pin",
                        subject_id=pin.name,
                        register_peripheral=None,
                        register_name=None,
                        register_offset=None,
                        register_id=None,
                        register_field_id=None,
                        target_ref_kind="pin",
                        target_ref_id=pin.name,
                        value_ref_kind="selector",
                        value_ref_id=route_selector,
                        value_int=signal.af_number,
                        provenance=signal.provenance,
                    ),
                )
                operation_ids.append(operation_id)

            candidate_id = (
                f"candidate:{_sanitize(pin.name)}:{_sanitize(peripheral.name)}:"
                f"{_sanitize(signal.signal)}"
            )
            capability_value = (
                canonical_signal_role(
                    peripheral_class,
                    signal.signal,
                )
                or signal.signal.lower()
            )
            capability_ids_list: list[str] = []
            if peripheral.ip_version is not None:
                capability_id = (
                    f"capability:{_sanitize(peripheral.ip_name)}:{_sanitize(peripheral.ip_version)}:"
                    f"{_sanitize(capability_value)}"
                )
                capability_map.setdefault(
                    capability_id,
                    CapabilityDescriptor(
                        capability_id=capability_id,
                        scope="ip-block",
                        peripheral_class=peripheral_class,
                        name="signal-role",
                        value=capability_value,
                        ip_name=peripheral.ip_name,
                        ip_version=peripheral.ip_version,
                        peripheral=None,
                        package=None,
                        provenance=signal.provenance,
                    ),
                )
                capability_ids_list.append(capability_id)
                block_roles[(peripheral.ip_name, peripheral.ip_version)].add(capability_value)
                block_capabilities[(peripheral.ip_name, peripheral.ip_version)].add(capability_id)

            overlay_capability_id = (
                f"capability-instance:{_sanitize(peripheral.name)}:"
                f"{_sanitize(device.identity.package)}:{_sanitize(capability_value)}"
            )
            capability_map.setdefault(
                overlay_capability_id,
                CapabilityDescriptor(
                    capability_id=overlay_capability_id,
                    scope="instance-overlay",
                    peripheral_class=peripheral_class,
                    name="available-signal",
                    value=capability_value,
                    ip_name=peripheral.ip_name,
                    ip_version=peripheral.ip_version,
                    peripheral=peripheral.name,
                    package=device.identity.package,
                    provenance=signal.provenance,
                ),
            )
            capability_ids_list.append(overlay_capability_id)
            capability_ids = tuple(dict.fromkeys(capability_ids_list))

            candidate_map[candidate_id] = ConnectionCandidate(
                candidate_id=candidate_id,
                pin=pin.name,
                peripheral=peripheral.name,
                signal=signal.signal.lower(),
                route_kind=route_kind,
                route_selector=route_selector,
                route_group_id=None,
                requirement_ids=tuple(requirement_ids),
                operation_ids=tuple(operation_ids),
                capability_ids=capability_ids,
                provenance=signal.provenance,
            )

    connection_groups_list: list[ConnectionGroup] = []
    primary_group_by_candidate: dict[str, str] = {}
    for peripheral in sorted(device.peripherals, key=lambda item: item.name):
        groups, candidate_group_ids = _bundle_candidates(
            peripheral_name=peripheral.name,
            peripheral_class=canonical_peripheral_class(peripheral.ip_name),
            package_name=device.identity.package,
            candidate_map=candidate_map,
        )
        connection_groups_list.extend(groups)
        for candidate_id, group_id in candidate_group_ids.items():
            primary_group_by_candidate.setdefault(candidate_id, group_id)

    candidate_map = {
        candidate_id: ConnectionCandidate(
            candidate_id=candidate.candidate_id,
            pin=candidate.pin,
            peripheral=candidate.peripheral,
            signal=candidate.signal,
            route_kind=candidate.route_kind,
            route_selector=candidate.route_selector,
            route_group_id=primary_group_by_candidate.get(candidate_id),
            requirement_ids=candidate.requirement_ids,
            operation_ids=candidate.operation_ids,
            capability_ids=candidate.capability_ids,
            provenance=candidate.provenance,
        )
        for candidate_id, candidate in candidate_map.items()
    }
    connection_groups = tuple(connection_groups_list)

    ip_blocks = tuple(
        IpBlockDefinition(
            ip_name=ip_name,
            ip_version=ip_version,
            peripheral_class=canonical_peripheral_class(ip_name),
            backend_schema_id=_runtime_schema_id(
                subsystem=canonical_peripheral_class(ip_name),
                vendor=device.identity.vendor,
                ip_name=ip_name,
                ip_version=ip_version,
                fallback=ip_name,
            ),
            register_profile=f"{ip_name}:{ip_version}",
            signal_roles=tuple(sorted(block_roles[(ip_name, ip_version)])),
            capability_ids=tuple(sorted(block_capabilities[(ip_name, ip_version)])),
            provenance=next(
                peripheral.provenance
                for peripheral in device.peripherals
                if peripheral.ip_name == ip_name and peripheral.ip_version == ip_version
            ),
        )
        for ip_name, ip_version in sorted(
            {
                (peripheral.ip_name, peripheral.ip_version)
                for peripheral in device.peripherals
                if peripheral.ip_version is not None
            }
        )
    )

    memory_regions = tuple(
        type(memory)(
            name=memory.name,
            kind=memory.kind,
            base_address=memory.base_address,
            size_bytes=memory.size_bytes,
            access=memory.access,
            provenance=memory.provenance,
            address_space=memory.address_space,
            startup_roles=_memory_startup_roles(memory.kind, memory.access),
        )
        for memory in device.memories
    )
    peripheral_interrupt_counts: dict[str, int] = defaultdict(int)
    for interrupt in device.interrupts:
        if interrupt.peripheral is not None:
            peripheral_interrupt_counts[interrupt.peripheral] += 1
    interrupts = tuple(
        type(interrupt)(
            name=interrupt.name,
            line=interrupt.line,
            peripheral=interrupt.peripheral,
            provenance=interrupt.provenance,
            shared_group=(
                None
                if interrupt.peripheral is None
                or peripheral_interrupt_counts[interrupt.peripheral] < 2
                else f"interrupt-group:{_sanitize(interrupt.peripheral)}"
            ),
            alias_names=tuple(
                dict.fromkeys(
                    (
                        *interrupt.alias_names,
                        *_interrupt_aliases(interrupt.name, interrupt.peripheral),
                    )
                )
            ),
        )
        for interrupt in device.interrupts
    )

    vector_slots = tuple(
        VectorSlotDescriptor(
            slot=slot,
            symbol_name=symbol_name,
            interrupt=interrupt_name,
            kind=kind,
            provenance=device.provenance,
            core_affinity=_system_vector_core_affinity(device.identity.core, kind),
        )
        for slot, symbol_name, interrupt_name, kind in _system_vector_baseline(device.identity.core)
    ) + tuple(
        VectorSlotDescriptor(
            slot=16 + interrupt.line,
            symbol_name=_symbol_name(interrupt.name),
            interrupt=interrupt.name,
            kind="external-interrupt",
            provenance=interrupt.provenance,
            core_affinity=_interrupt_core_affinity(interrupt.peripheral),
        )
        for interrupt in sorted(interrupts, key=lambda item: item.line)
    )
    vector_slot_by_interrupt = {
        vector_slot.interrupt: vector_slot
        for vector_slot in vector_slots
        if vector_slot.interrupt is not None
    }
    interrupt_bindings = tuple(
        InterruptBindingDescriptor(
            binding_id=(
                f"interrupt-binding:{_sanitize(interrupt.peripheral)}:{_sanitize(interrupt.name)}"
            ),
            peripheral=interrupt.peripheral,
            interrupt=interrupt.name,
            line=interrupt.line,
            vector_slot=(
                None
                if interrupt.name not in vector_slot_by_interrupt
                else vector_slot_by_interrupt[interrupt.name].slot
            ),
            symbol_name=(
                None
                if interrupt.name not in vector_slot_by_interrupt
                else vector_slot_by_interrupt[interrupt.name].symbol_name
            ),
            shared_group=interrupt.shared_group,
            alias_names=interrupt.alias_names,
            provenance=interrupt.provenance,
        )
        for interrupt in sorted(
            (entry for entry in interrupts if entry.peripheral is not None),
            key=lambda item: (item.peripheral or "", item.line, item.name),
        )
    )

    startup_descriptors = (
        StartupDescriptor(
            descriptor_id="startup:vectors",
            kind="vector-table",
            source_region=None,
            target_region=None,
            symbol="_vectors",
            provenance=device.provenance,
        ),
        StartupDescriptor(
            descriptor_id="startup:stack-top",
            kind="initial-stack-pointer",
            source_region=None,
            target_region=None,
            symbol="__stack_top",
            provenance=device.provenance,
        ),
    ) + tuple(
        descriptor
        for memory in memory_regions
        for descriptor in (
            StartupDescriptor(
                descriptor_id=f"startup:vector-source:{_sanitize(memory.name)}",
                kind="vector-source-region",
                source_region=memory.name,
                target_region=None,
                symbol=None,
                provenance=memory.provenance,
            )
            if "vector-source" in memory.startup_roles
            else None,
            StartupDescriptor(
                descriptor_id=f"startup:copy-source:{_sanitize(memory.name)}",
                kind="copy-source-region",
                source_region=memory.name,
                target_region=None,
                symbol=None,
                provenance=memory.provenance,
            )
            if "copy-source" in memory.startup_roles
            else None,
            StartupDescriptor(
                descriptor_id=f"startup:copy-target:{_sanitize(memory.name)}",
                kind="copy-target-region",
                source_region=None,
                target_region=memory.name,
                symbol=None,
                provenance=memory.provenance,
            )
            if "copy-target" in memory.startup_roles
            else None,
            StartupDescriptor(
                descriptor_id=f"startup:zero-target:{_sanitize(memory.name)}",
                kind="zero-target-region",
                source_region=None,
                target_region=memory.name,
                symbol=None,
                provenance=memory.provenance,
            )
            if "zero-target" in memory.startup_roles
            else None,
            StartupDescriptor(
                descriptor_id=f"startup:retained:{_sanitize(memory.name)}",
                kind="retained-region",
                source_region=None,
                target_region=memory.name,
                symbol=None,
                provenance=memory.provenance,
            )
            if "retained-target" in memory.startup_roles
            else None,
        )
        if descriptor is not None
    )

    clock_node_map: dict[str, ClockNodeLite] = {node.node_id: node for node in device.clock_nodes}
    clock_selector_map = {}
    for selector in device.clock_selectors:
        register_peripheral = None
        register_name = None
        register_offset = None
        register_id = None
        register_field_id = None
        if selector.register_target is not None:
            (
                register_peripheral,
                register_name,
                register_offset,
                register_id,
                register_field_id,
            ) = _typed_register_ref(device, selector.register_target)
        clock_selector_map[selector.selector_id] = ClockSelectorLite(
            selector_id=selector.selector_id,
            parent_options=selector.parent_options,
            register_target=selector.register_target,
            register_peripheral=register_peripheral,
            register_name=register_name,
            register_offset=register_offset,
            register_id=register_id,
            register_field_id=register_field_id,
            provenance=selector.provenance,
        )
    clock_node_map.setdefault(
        "clock-root",
        ClockNodeLite(
            node_id="clock-root",
            kind="root",
            parent=None,
            selector=None,
            provenance=device.provenance,
        ),
    )
    clock_gate_map: dict[str, ClockGateDescriptor] = {
        gate.gate_id: gate for gate in device.clock_gates
    }
    reset_map: dict[str, ResetDescriptor] = {reset.reset_id: reset for reset in device.resets}
    binding_map: dict[str, PeripheralClockBinding] = {
        binding.peripheral: binding for binding in device.peripheral_clock_bindings
    }

    for peripheral in device.peripherals:
        parent_node = None
        if peripheral.rcc_enable_signal is not None:
            inferred_parent_node = _domain_node_id(peripheral.rcc_enable_signal)
            parent_parent, node_kind = _domain_node_shape(peripheral.rcc_enable_signal)
            clock_node_map.setdefault(
                inferred_parent_node,
                ClockNodeLite(
                    node_id=inferred_parent_node,
                    kind=node_kind,
                    parent=parent_parent,
                    selector=None,
                    provenance=peripheral.provenance,
                ),
            )
            explicit_gate = next(
                (gate for gate in device.clock_gates if gate.peripheral == peripheral.name),
                None,
            )
            gate_id = (
                f"gate:{_sanitize(peripheral.name)}"
                if explicit_gate is None
                else explicit_gate.gate_id
            )
            gate_signal = (
                peripheral.rcc_enable_signal
                if explicit_gate is None
                else explicit_gate.enable_signal
            )
            (
                gate_register_peripheral,
                gate_register_name,
                gate_register_offset,
                gate_register_id,
                gate_register_field_id,
            ) = _typed_register_ref(device, gate_signal, operation_kind="set-bit")
            if explicit_gate is None:
                clock_gate_map[gate_id] = ClockGateDescriptor(
                    gate_id=gate_id,
                    peripheral=peripheral.name,
                    enable_signal=gate_signal,
                    parent_node=inferred_parent_node,
                    register_peripheral=gate_register_peripheral,
                    register_name=gate_register_name,
                    register_offset=gate_register_offset,
                    register_id=gate_register_id,
                    register_field_id=gate_register_field_id,
                    provenance=peripheral.provenance,
                )
                parent_node = inferred_parent_node
            else:
                parent_node = (
                    explicit_gate.parent_node
                    if explicit_gate.parent_node is not None
                    else inferred_parent_node
                )
                clock_gate_map[gate_id] = ClockGateDescriptor(
                    gate_id=explicit_gate.gate_id,
                    peripheral=explicit_gate.peripheral,
                    enable_signal=gate_signal,
                    parent_node=parent_node,
                    register_peripheral=gate_register_peripheral,
                    register_name=gate_register_name,
                    register_offset=gate_register_offset,
                    register_id=gate_register_id,
                    register_field_id=gate_register_field_id,
                    provenance=explicit_gate.provenance,
                )
        else:
            gate_id = None

        if peripheral.rcc_reset_signal is not None:
            explicit_reset = next(
                (reset for reset in device.resets if reset.peripheral == peripheral.name),
                None,
            )
            reset_id = (
                f"reset:{_sanitize(peripheral.name)}"
                if explicit_reset is None
                else explicit_reset.reset_id
            )
            if explicit_reset is None:
                (
                    reset_register_peripheral,
                    reset_register_name,
                    reset_register_offset,
                    reset_register_id,
                    reset_register_field_id,
                ) = _typed_register_ref(
                    device,
                    peripheral.rcc_reset_signal,
                    operation_kind="clear-bit",
                )
                reset_map[reset_id] = ResetDescriptor(
                    reset_id=reset_id,
                    peripheral=peripheral.name,
                    reset_signal=peripheral.rcc_reset_signal,
                    active_level="high",
                    register_peripheral=reset_register_peripheral,
                    register_name=reset_register_name,
                    register_offset=reset_register_offset,
                    register_id=reset_register_id,
                    register_field_id=reset_register_field_id,
                    provenance=peripheral.provenance,
                )
            else:
                (
                    reset_register_peripheral,
                    reset_register_name,
                    reset_register_offset,
                    reset_register_id,
                    reset_register_field_id,
                ) = _typed_register_ref(
                    device,
                    explicit_reset.reset_signal,
                    operation_kind="clear-bit",
                )
                reset_map[reset_id] = ResetDescriptor(
                    reset_id=explicit_reset.reset_id,
                    peripheral=explicit_reset.peripheral,
                    reset_signal=explicit_reset.reset_signal,
                    active_level=explicit_reset.active_level,
                    register_peripheral=reset_register_peripheral,
                    register_name=reset_register_name,
                    register_offset=reset_register_offset,
                    register_id=reset_register_id,
                    register_field_id=reset_register_field_id,
                    provenance=explicit_reset.provenance,
                )
        else:
            reset_id = None

        if gate_id is not None or reset_id is not None:
            binding_overlay = binding_map.get(peripheral.name)
            binding_map[peripheral.name] = PeripheralClockBinding(
                peripheral=peripheral.name,
                clock_gate_id=(
                    gate_id
                    if binding_overlay is None or binding_overlay.clock_gate_id is None
                    else binding_overlay.clock_gate_id
                ),
                reset_id=(
                    reset_id
                    if binding_overlay is None or binding_overlay.reset_id is None
                    else binding_overlay.reset_id
                ),
                selector_id=None if binding_overlay is None else binding_overlay.selector_id,
                provenance=(
                    peripheral.provenance if binding_overlay is None else binding_overlay.provenance
                ),
            )

    dma_request_lines_by_controller: dict[str, set[str]] = defaultdict(set)
    dma_controller_provenance: dict[str, object] = {}
    dma_controller_map: dict[str, DmaControllerDescriptor] = {}
    dma_route_map: dict[str, DmaRouteDescriptor] = {}
    dma_conflict_accumulator: dict[str, list[str]] = defaultdict(list)
    dma_controller_hints = {
        controller.controller: controller for controller in device.dma_controllers
    }
    for request in device.dma_requests:
        dma_request_lines_by_controller[request.controller].add(request.request_line)
        dma_controller_provenance.setdefault(request.controller, request.provenance)
        route_id = (
            f"dma-route:{_sanitize(request.controller)}:{_sanitize(request.request_line)}:"
            f"{_sanitize(request.peripheral or 'none')}:{_sanitize(request.signal or 'none')}"
        )
        dma_route_map[route_id] = DmaRouteDescriptor(
            route_id=route_id,
            controller=request.controller,
            request_line=request.request_line,
            peripheral=request.peripheral,
            signal=request.signal,
            conflict_group=None,
            provenance=request.provenance,
            channel_index=request.channel_index,
            request_value=request.request_value,
            channel_selector=request.channel_selector,
        )
        dma_conflict_accumulator[
            f"dma-conflict:{_sanitize(request.controller)}:{_sanitize(request.request_line)}"
        ].append(route_id)

    for controller in sorted(dma_request_lines_by_controller):
        controller_peripheral = peripheral_map.get(controller)
        controller_hint = dma_controller_hints.get(controller)
        dma_controller_map[controller] = DmaControllerDescriptor(
            controller=controller,
            version=(
                controller_hint.version
                if controller_hint is not None and controller_hint.version is not None
                else None
                if controller_peripheral is None
                else controller_peripheral.ip_version
            ),
            channel_count=(None if controller_hint is None else controller_hint.channel_count),
            request_count=len(dma_request_lines_by_controller[controller]),
            provenance=dma_controller_provenance[controller],
        )

    conflict_group_map = {
        group_id: tuple(sorted(route_ids))
        for group_id, route_ids in dma_conflict_accumulator.items()
        if len(route_ids) >= 2
    }
    if conflict_group_map:
        dma_route_map = {
            route_id: DmaRouteDescriptor(
                route_id=route.route_id,
                controller=route.controller,
                request_line=route.request_line,
                peripheral=route.peripheral,
                signal=route.signal,
                conflict_group=next(
                    (
                        group_id
                        for group_id, route_ids in conflict_group_map.items()
                        if route_id in route_ids
                    ),
                    None,
                ),
                provenance=route.provenance,
                channel_index=route.channel_index,
                request_value=route.request_value,
                channel_selector=route.channel_selector,
            )
            for route_id, route in dma_route_map.items()
        }
    dma_conflict_groups = tuple(
        DmaConflictGroup(
            conflict_group_id=group_id,
            route_ids=route_ids,
            provenance=next(dma_route_map[route_id].provenance for route_id in route_ids),
        )
        for group_id, route_ids in sorted(conflict_group_map.items())
    )
    dma_bindings = tuple(
        DmaBindingDescriptor(
            binding_id=(
                f"dma-binding:{_sanitize(route.peripheral or 'none')}:"
                f"{_sanitize(route.signal or 'none')}:"
                f"{_sanitize(route.controller)}:{_sanitize(route.request_line)}"
            ),
            peripheral=route.peripheral or route.controller,
            signal=route.signal,
            controller=route.controller,
            request_line=route.request_line,
            route_id=route.route_id,
            conflict_group=route.conflict_group,
            provenance=route.provenance,
            channel_index=route.channel_index,
            request_value=route.request_value,
            channel_selector=route.channel_selector,
        )
        for route in sorted(
            dma_route_map.values(),
            key=lambda item: (
                item.peripheral or "",
                item.signal or "",
                item.controller,
                item.request_line,
            ),
        )
        if route.peripheral is not None
    )

    return CanonicalDeviceIR(
        schema_version=device.schema_version,
        identity=device.identity,
        memories=memory_regions,
        packages=device.packages,
        registers=device.registers,
        register_fields=device.register_fields,
        pins=device.pins,
        peripherals=tuple(
            type(peripheral)(
                name=peripheral.name,
                ip_name=peripheral.ip_name,
                ip_version=peripheral.ip_version,
                backend_schema_id=_runtime_schema_id(
                    subsystem=canonical_peripheral_class(peripheral.ip_name),
                    vendor=device.identity.vendor,
                    ip_name=peripheral.ip_name,
                    ip_version=peripheral.ip_version,
                    fallback=peripheral.ip_name,
                ),
                instance=peripheral.instance,
                base_address=peripheral.base_address,
                rcc_enable_signal=peripheral.rcc_enable_signal,
                rcc_reset_signal=peripheral.rcc_reset_signal,
                provenance=peripheral.provenance,
            )
            for peripheral in device.peripherals
        ),
        interrupts=interrupts,
        dma_requests=device.dma_requests,
        provenance=device.provenance,
        ip_blocks=ip_blocks,
        capabilities=tuple(
            capability_map[capability_id] for capability_id in sorted(capability_map)
        ),
        package_pads=device.package_pads,
        pin_constraints=device.pin_constraints,
        signal_endpoints=tuple(endpoint_map[endpoint_id] for endpoint_id in sorted(endpoint_map)),
        route_requirements=tuple(
            requirement_map[requirement_id] for requirement_id in sorted(requirement_map)
        ),
        route_operations=tuple(
            operation_map[operation_id] for operation_id in sorted(operation_map)
        ),
        connection_candidates=tuple(
            candidate_map[candidate_id] for candidate_id in sorted(candidate_map)
        ),
        connection_groups=connection_groups,
        interrupt_bindings=interrupt_bindings,
        vector_slots=vector_slots,
        startup_descriptors=startup_descriptors,
        system_clock_profiles=device.system_clock_profiles,
        clock_nodes=tuple(clock_node_map[node_id] for node_id in sorted(clock_node_map)),
        clock_selectors=tuple(
            clock_selector_map[selector_id] for selector_id in sorted(clock_selector_map)
        ),
        clock_gates=tuple(clock_gate_map[gate_id] for gate_id in sorted(clock_gate_map)),
        resets=tuple(reset_map[reset_id] for reset_id in sorted(reset_map)),
        peripheral_clock_bindings=tuple(
            binding_map[peripheral_name] for peripheral_name in sorted(binding_map)
        ),
        dma_controllers=tuple(
            dma_controller_map[controller] for controller in sorted(dma_controller_map)
        ),
        dma_bindings=dma_bindings,
        dma_routes=tuple(dma_route_map[route_id] for route_id in sorted(dma_route_map)),
        dma_conflict_groups=dma_conflict_groups,
        # Carry forward ADC Tier 2/3/4 fields from the upstream device IR so
        # the post-normalize enrichment step's data is not lost when this
        # function reconstructs the IR.
        adc_internal_channels=device.adc_internal_channels,
        adc_calibration_data_points=device.adc_calibration_data_points,
        adc_calibration_context=device.adc_calibration_context,
        adc_resolution_options=device.adc_resolution_options,
        adc_sample_time_options=device.adc_sample_time_options,
        adc_oversampling_options=device.adc_oversampling_options,
        adc_external_triggers=device.adc_external_triggers,
        adc_max_clock_hz=device.adc_max_clock_hz,
        # Carry forward multicore-topology facts (added by
        # ``expose-xtensa-dual-core-facts``) for the same reason.
        multicore_topology=device.multicore_topology,
        app_cpu_control_plane=device.app_cpu_control_plane,
        # USB controller descriptors (added by ``add-usb-semantic-traits``).
        usb_controllers=device.usb_controllers,
        pio_blocks=device.pio_blocks,
        gpio_pins=device.gpio_pins,
    )


def ensure_connector_descriptors(device: CanonicalDeviceIR) -> CanonicalDeviceIR:
    """Return a device with connector/system descriptors populated."""
    if (
        device.signal_endpoints
        and device.connection_candidates
        and device.connection_groups
        and device.interrupt_bindings
        and device.vector_slots
        and device.startup_descriptors
        and (device.dma_bindings or not device.dma_routes)
    ):
        return device
    return enrich_connector_descriptors(device)
