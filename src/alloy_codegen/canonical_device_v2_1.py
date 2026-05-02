"""Canonical device v2.1 reader / writer.

Public surface:

* :func:`parse_device(text)` — YAML text → :class:`CanonicalDevice`.
* :func:`parse_device_payload(payload)` — already-parsed dict →
  :class:`CanonicalDevice`.
* :func:`serialize_device(ir)` — :class:`CanonicalDevice` → YAML text.
* :func:`validate_device(text)` — schema-validate without parsing.
* :func:`validate_device_payload(payload)` — same on a parsed dict.
* :data:`SCHEMA_PATH` — absolute path to the bundled JSON-schema.

Determinism contract:

1. ``serialize_device`` emits keys in a fixed top-level order matching
   the v2.1 cheat-sheet
   (``schema → identity → provenance → memory → clock → templates →
   peripherals → pinout → interrupts → fuses → system_examples``).
2. Lists are not re-sorted — order is whatever the IR carried.
3. No YAML anchors / aliases.
4. UTF-8 output with a trailing newline.
5. The validator runs **before** the IR is constructed (schema-locked
   emission) and again on every re-serialised payload.
"""

from __future__ import annotations

import json
import re
from functools import cache
from pathlib import Path
from typing import Any

import yaml
from jsonschema import Draft202012Validator

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.v2_1 import (
    CANONICAL_SCHEMA,
    AdcCalibration,
    CalibrationDataPoint,
    CanonicalDevice,
    Clock,
    ClockDomain,
    ClockProfile,
    Core,
    ExternalTrigger,
    I2cTimingPreset,
    Identity,
    InterruptMatrix,
    InterruptPeripheralSource,
    InterruptVector,
    MemoryRegion,
    Multicore,
    MulticoreCore,
    Oscillator,
    PeripheralDma,
    PeripheralInstance,
    PeripheralIrq,
    PeripheralRcc,
    Pin,
    PinOptionFixed,
    PinOptionMatrix,
    PinOptionPsel,
    PLLConfig,
    Provenance,
    SelectRegister,
    SelectTask,
    Template,
    TemplateField,
    TemplateRegister,
)
from alloy_codegen.ir.v2_1.peripherals import PeripheralDmaChannel

# ---------------------------------------------------------------------------
# Schema location + lazy load
# ---------------------------------------------------------------------------

_REPO_ROOT = Path(__file__).resolve().parents[2]
SCHEMA_PATH: Path = _REPO_ROOT / "schema" / "canonical_device_v2_1" / "alloy-device-v2_1.schema.json"


@cache
def _validator() -> Draft202012Validator:
    """Cache the validator + parsed schema for the process lifetime.

    Reading + parsing the 21-KB schema JSON costs ~5 ms; we don't want
    to pay that on every YAML.
    """
    schema = json.loads(SCHEMA_PATH.read_text(encoding="utf-8"))
    Draft202012Validator.check_schema(schema)
    return Draft202012Validator(schema)


# ---------------------------------------------------------------------------
# YAML loader — fastest available SafeLoader, dates kept as strings.
# ---------------------------------------------------------------------------

try:
    from yaml import CSafeLoader as _BaseSafeLoader  # type: ignore[attr-defined]
except ImportError:  # pragma: no cover — only on no-libyaml installs
    from yaml import SafeLoader as _BaseSafeLoader  # type: ignore[no-redef]


class _StringDatesLoader(_BaseSafeLoader):
    """SafeLoader that keeps ISO-8601 dates and the YAML 1.1
    ``on/off/yes/no`` literals as plain strings.

    Why: JSON-schema validates against ``"type": "string"`` so dates
    must stay as strings; and ``select_task: { on: …, off: … }``
    needs ``on`` / ``off`` parsed as keys, not as booleans.  We keep
    ``true`` / ``false`` working — they're the only reasonable spelling
    for the boolean fields elsewhere in the schema.
    """


def _filter_implicit(entries: list[tuple[str, Any]]) -> list[tuple[str, Any]]:
    out = []
    for tag, regex in entries:
        if tag == "tag:yaml.org,2002:timestamp":
            continue
        # Drop the bool resolver entries that match on/off/yes/no.
        # The pattern always contains those four spellings; the
        # `true/false` resolver lives separately in PyYAML.
        if tag == "tag:yaml.org,2002:bool":
            pat = getattr(regex, "pattern", "")
            if any(word in pat for word in ("on", "off", "yes", "no")) and "true" not in pat.lower():
                continue
        out.append((tag, regex))
    return out


_StringDatesLoader.yaml_implicit_resolvers = {  # type: ignore[attr-defined]
    ch: _filter_implicit(entries)
    for ch, entries in _BaseSafeLoader.yaml_implicit_resolvers.items()  # type: ignore[attr-defined]
}


def _safe_load(text: str) -> Any:
    return yaml.load(text, Loader=_StringDatesLoader)


# ---------------------------------------------------------------------------
# YAML dumper — preserves dict insertion order, no anchors.
# ---------------------------------------------------------------------------


class _CanonicalDumper(yaml.SafeDumper):
    """SafeDumper that emits dicts in insertion order."""


def _represent_dict_preserve(dumper: _CanonicalDumper, data: dict) -> yaml.MappingNode:
    return dumper.represent_mapping("tag:yaml.org,2002:map", data.items())


_CanonicalDumper.add_representer(dict, _represent_dict_preserve)


# Top-level key order for emitted YAML.  Mirrors the v2.1 cheat-sheet.
_TOP_LEVEL_KEY_ORDER: tuple[str, ...] = (
    "schema",
    "identity",
    "provenance",
    "memory",
    "clock",
    "templates",
    "peripherals",
    "pinout",
    "interrupts",
    "fuses",
    "system_examples",
)


def _ordered_top_level(payload: dict[str, Any]) -> dict[str, Any]:
    ordered: dict[str, Any] = {}
    seen: set[str] = set()
    for key in _TOP_LEVEL_KEY_ORDER:
        if key in payload:
            ordered[key] = payload[key]
            seen.add(key)
    for key, value in payload.items():
        if key not in seen:
            ordered[key] = value
    return ordered


# ---------------------------------------------------------------------------
# Hex / int helper
# ---------------------------------------------------------------------------

_HEX_PATTERN = re.compile(r"^0x[0-9A-Fa-f]+$")


def _coerce_hex(value: Any) -> int:
    """Accept ``int`` or ``"0x..."`` and return the canonical int."""
    if isinstance(value, bool):
        raise StageExecutionError(f"unexpected bool where hex/int expected: {value!r}")
    if isinstance(value, int):
        return value
    if isinstance(value, str) and _HEX_PATTERN.match(value):
        return int(value, 16)
    raise StageExecutionError(
        f"expected integer or 0x-prefixed hex string, got {value!r}"
    )


def _format_hex_or_int(value: int | None) -> int | str | None:
    """Round-trip pretty-print: emit ints ≥ 0x100 in hex form for
    parity with hand-crafted YAMLs; smaller values stay decimal."""
    if value is None:
        return None
    if value >= 0x100:
        return f"0x{value:X}"
    return value


# ---------------------------------------------------------------------------
# Section parsers — payload dict → IR dataclass
# ---------------------------------------------------------------------------


def _parse_provenance(node: dict[str, Any]) -> Provenance:
    secondary = node.get("secondary") or ()
    return Provenance(
        primary=str(node["primary"]),
        authored=node.get("authored", "auto"),
        authored_on=node.get("authored_on"),
        secondary=tuple(str(x) for x in secondary),
        notes=node.get("notes"),
        extra={
            k: v for k, v in node.items()
            if k not in {"primary", "authored", "authored_on", "secondary", "notes"}
        },
    )


def _parse_multicore(node: dict[str, Any]) -> Multicore:
    cores = tuple(
        MulticoreCore(
            id=c["id"],
            role=c["role"],
            vector_base=_coerce_hex(c["vector_base"]) if "vector_base" in c else None,
            app_cpu=c.get("app_cpu"),
            release_register=c.get("release_register"),
            release_op=c.get("release_op"),
            start_vector_symbol=c.get("start_vector_symbol"),
        )
        for c in node["cores"]
    )
    return Multicore(topology=node["topology"], cores=cores)


def _parse_core(node: dict[str, Any]) -> Core:
    return Core(
        isa=node["isa"],
        name=node["name"],
        bits=int(node["bits"]),
        fpu=bool(node.get("fpu", False)),
        mpu=bool(node.get("mpu", False)),
        endianness=node.get("endianness", "little"),
        interrupt_lines=node.get("interrupt_lines"),
        nvic_priority_bits=node.get("nvic_priority_bits"),
        multicore=_parse_multicore(node["multicore"]) if node.get("multicore") else None,
    )


def _parse_identity(node: dict[str, Any]) -> Identity:
    known = {"vendor", "family", "device", "core", "package", "variant",
             "flash_size", "ram_size", "description"}
    return Identity(
        vendor=node["vendor"],
        family=node["family"],
        device=node["device"],
        core=_parse_core(node["core"]),
        package=node.get("package"),
        variant=node.get("variant"),
        flash_size=node.get("flash_size"),
        ram_size=node.get("ram_size"),
        description=node.get("description"),
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_memory_region(node: dict[str, Any]) -> MemoryRegion:
    known = {"id", "base", "size", "access", "alias", "address_space",
             "backing", "role", "banks", "default_use", "survives"}
    return MemoryRegion(
        id=node["id"],
        base=_coerce_hex(node["base"]),
        size=node["size"],
        access=node["access"],
        alias=node.get("alias"),
        address_space=node.get("address_space"),
        backing=node.get("backing"),
        role=node.get("role"),
        banks=tuple(node.get("banks") or ()),
        default_use=node.get("default_use"),
        survives=node.get("survives"),
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_oscillator(node: dict[str, Any]) -> Oscillator:
    rng = node.get("range")
    return Oscillator(
        freq=node["freq"],
        kind=node["kind"],
        tolerance=node.get("tolerance"),
        range=tuple(rng) if rng else None,  # type: ignore[arg-type]
        purpose=node.get("purpose"),
        optional=bool(node.get("optional", False)),
        source=node.get("source"),
    )


def _parse_pll_config(node: dict[str, Any]) -> PLLConfig:
    return PLLConfig(
        input_sources=tuple(node.get("input_sources") or ()),
        multiplier_range=tuple(node["multiplier_range"]) if node.get("multiplier_range") else None,  # type: ignore[arg-type]
        outputs=tuple(node.get("outputs") or ()),
        max_output=node.get("max_output"),
        vco_range=tuple(node["vco_range"]) if node.get("vco_range") else None,  # type: ignore[arg-type]
        vco_output_target=node.get("vco_output_target"),
        post_divs=tuple(node.get("post_divs") or ()),
        post_div_chain=tuple(node.get("post_div_chain") or ()),
        output=node.get("output"),
    )


def _parse_select_register(node: dict[str, Any] | None) -> SelectRegister | None:
    if not node:
        return None
    return SelectRegister(
        reg=node["reg"],
        field=node["field"],
        encoding=dict(node["encoding"]),
    )


def _parse_select_task(node: dict[str, Any] | None) -> SelectTask | None:
    if not node:
        return None
    # YAML's implicit type resolver converts ``on:`` and ``off:`` to
    # booleans True/False before our parser sees them.  Accept both
    # spellings so the on-disk YAML stays readable.
    on = node.get("on")
    if on is None:
        on = node.get(True)  # type: ignore[arg-type]
    off = node.get("off")
    if off is None:
        off = node.get(False)  # type: ignore[arg-type]
    if on is None:
        raise StageExecutionError("select_task requires `on:` (task to fire)")
    return SelectTask(on=on, off=off, status=node.get("status"))


def _parse_clock_domain(node: dict[str, Any]) -> ClockDomain:
    return ClockDomain(
        id=node["id"],
        source=node.get("source"),
        sources=tuple(node.get("sources") or ()),
        prescalers=tuple(float(x) for x in node.get("prescalers") or ()),
        max=node.get("max"),
        default=node.get("default"),
        target_freq=node.get("target_freq"),
        purpose=node.get("purpose"),
        notes=node.get("notes"),
        select_register=_parse_select_register(node.get("select_register")),
        auxsrc_register=_parse_select_register(node.get("auxsrc_register")),
        prescaler_register=_parse_select_register(node.get("prescaler_register")),
        select_task=_parse_select_task(node.get("select_task")),
    )


def _parse_clock_profile(node: dict[str, Any]) -> ClockProfile:
    known = {"id", "kind", "sysclk", "sysclk_source"}
    return ClockProfile(
        id=node["id"],
        kind=node["kind"],
        sysclk=node["sysclk"],
        sysclk_source=node["sysclk_source"],
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_clock(node: dict[str, Any]) -> Clock:
    return Clock(
        oscillators={k: _parse_oscillator(v) for k, v in (node.get("oscillators") or {}).items()},
        domains=tuple(_parse_clock_domain(d) for d in (node.get("domains") or [])),
        pll={k: _parse_pll_config(v) for k, v in (node.get("pll") or {}).items()},
        profiles=tuple(_parse_clock_profile(p) for p in (node.get("profiles") or [])),
        reset_state=dict(node.get("reset_state") or {}),
    )


def _parse_template_register(node: dict[str, Any]) -> TemplateRegister:
    return TemplateRegister(
        offset=_coerce_hex(node["offset"]),
        access=node.get("access"),
        stride=_coerce_hex(node["stride"]) if "stride" in node else None,
        count=node.get("count"),
        role=node.get("role"),
    )


def _parse_template_field(node: dict[str, Any]) -> TemplateField:
    bits_node = node.get("bits")
    return TemplateField(
        bit=node.get("bit"),
        bits=tuple(bits_node) if bits_node else None,  # type: ignore[arg-type]
        enum=dict(node.get("enum") or {}),
        access=node.get("access"),
    )


def _parse_template(node: dict[str, Any]) -> Template:
    known = {
        "extends", "capabilities", "capabilities_extra", "options",
        "registers", "registers_extra", "fields", "fields_extra",
        "max_clock", "max_baud", "pins_per_port", "speeds_mhz",
        "channels", "counter_bits", "counter_bits_options",
        "trigger_sources", "master_outputs", "waveform_modes",
        "deadtime_options", "break_inputs", "notes",
    }
    return Template(
        capabilities=tuple(node.get("capabilities") or ()),
        capabilities_extra=tuple(node.get("capabilities_extra") or ()),
        options=dict(node.get("options") or {}),
        registers={k: _parse_template_register(v) for k, v in (node.get("registers") or {}).items()},
        registers_extra={k: _parse_template_register(v) for k, v in (node.get("registers_extra") or {}).items()},
        fields={k: _parse_template_field(v) for k, v in (node.get("fields") or {}).items()},
        fields_extra={k: _parse_template_field(v) for k, v in (node.get("fields_extra") or {}).items()},
        extends=node.get("extends"),
        max_clock=node.get("max_clock"),
        max_baud=node.get("max_baud"),
        pins_per_port=node.get("pins_per_port"),
        speeds_mhz=tuple(node.get("speeds_mhz") or ()),
        channels=node.get("channels"),
        counter_bits=node.get("counter_bits"),
        counter_bits_options=tuple(node.get("counter_bits_options") or ()),
        trigger_sources=dict(node.get("trigger_sources") or {}),
        master_outputs=dict(node.get("master_outputs") or {}),
        waveform_modes=dict(node.get("waveform_modes") or {}),
        deadtime_options=tuple(node.get("deadtime_options") or ()),
        break_inputs=tuple(node.get("break_inputs") or ()),
        notes=node.get("notes"),
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_irq(node: Any) -> tuple[PeripheralIrq, ...]:
    if node is None:
        return ()
    if isinstance(node, dict):
        return (PeripheralIrq(num=int(node["num"]), name=node["name"]),)
    if isinstance(node, list):
        return tuple(PeripheralIrq(num=int(n["num"]), name=n["name"]) for n in node)
    raise StageExecutionError(f"irq must be object or list, got {type(node).__name__}")


def _parse_dma_channel(node: Any) -> PeripheralDmaChannel | None:
    if not isinstance(node, dict):
        return None
    known = {"ctrl", "channel", "dreq"}
    return PeripheralDmaChannel(
        ctrl=node.get("ctrl"),
        channel=node.get("channel"),
        dreq=node.get("dreq"),
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_dma(node: Any) -> PeripheralDma | None:
    if not isinstance(node, dict):
        return None
    known = {"tx", "rx", "shared"}
    return PeripheralDma(
        tx=_parse_dma_channel(node.get("tx")),
        rx=_parse_dma_channel(node.get("rx")),
        shared=node.get("shared"),
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_pin_options(node: Any) -> dict[str, object]:
    """Each `pin_options.<signal>` is one of three shapes per the
    schema's family-flag (matrix / psel / fixed-list)."""
    if not isinstance(node, dict):
        return {}
    out: dict[str, object] = {}
    for sig, opts in node.items():
        if isinstance(opts, dict):
            if opts.get("matrix") is True:
                out[sig] = PinOptionMatrix(
                    matrix=True,
                    default=opts.get("default"),
                    fast_path=opts.get("fast_path"),
                )
                continue
            if opts.get("psel") is True:
                out[sig] = PinOptionPsel(psel=True)
                continue
        if isinstance(opts, list):
            out[sig] = tuple(
                PinOptionFixed(
                    pin=o["pin"],
                    remap=o.get("remap"),
                    func=o.get("func"),
                    pinned=bool(o.get("pinned", True)),
                )
                for o in opts
            )
            continue
        out[sig] = opts
    return out


def _parse_calibration_data_point(node: dict[str, Any]) -> CalibrationDataPoint:
    return CalibrationDataPoint(
        rom_addr=_coerce_hex(node["rom_addr"]),
        size_bits=node.get("size_bits", 16),
        nominal_mv=node.get("nominal_mv"),
        temp_celsius=node.get("temp_celsius"),
        vdda_calibration=node.get("vdda_calibration"),
        description=node.get("description"),
    )


def _parse_calibration(node: Any) -> AdcCalibration | None:
    if not isinstance(node, dict):
        return None
    return AdcCalibration(
        vrefint=_parse_calibration_data_point(node["vrefint"]) if "vrefint" in node else None,
        ts_cal_low=_parse_calibration_data_point(node["ts_cal_low"]) if "ts_cal_low" in node else None,
        ts_cal_high=_parse_calibration_data_point(node["ts_cal_high"]) if "ts_cal_high" in node else None,
        ts_slope_uv_per_c=node.get("ts_slope_uv_per_c"),
    )


def _parse_external_triggers(node: Any) -> dict[str, tuple[ExternalTrigger, ...]]:
    if not isinstance(node, dict):
        return {}
    return {
        kind: tuple(
            ExternalTrigger(
                source=t["source"],
                extsel=t.get("extsel"),
                jextsel=t.get("jextsel"),
                polarity=t.get("polarity"),
            )
            for t in (rows or [])
        )
        for kind, rows in node.items()
    }


def _parse_timing_presets(node: Any) -> tuple[I2cTimingPreset, ...]:
    if not isinstance(node, list):
        return ()
    return tuple(
        I2cTimingPreset(
            speed=p["speed"],
            source_clock=p["source_clock"],
            timingr=_coerce_hex(p["timingr"]) if "timingr" in p else None,
            ccr=_coerce_hex(p["ccr"]) if "ccr" in p else None,
            trise=_coerce_hex(p["trise"]) if "trise" in p else None,
        )
        for p in node
    )


def _parse_peripheral(node: dict[str, Any]) -> PeripheralInstance:
    rcc_node = node.get("rcc")
    rcc = None
    if isinstance(rcc_node, dict):
        rcc = PeripheralRcc(
            en=rcc_node.get("en"),
            rst=rcc_node.get("rst"),
            extra={k: v for k, v in rcc_node.items() if k not in {"en", "rst"}},
        )

    known = {
        "id", "template", "ip_version", "alias", "base", "bus",
        "clock_source", "max_clock_override", "rcc", "irq", "dma",
        "pin_options", "pin_count", "pinned", "mutex_group",
        "power_reduction", "calibration", "external_triggers",
        "timing_presets", "trigger_source_peers", "channels",
        "counter_bits_default", "capabilities_extra", "conflicts_with",
        "notes",
    }
    return PeripheralInstance(
        id=node["id"],
        template=node["template"],
        ip_version=node.get("ip_version"),
        alias=node.get("alias"),
        base=_coerce_hex(node["base"]) if "base" in node else None,
        bus=node.get("bus"),
        clock_source=node.get("clock_source"),
        max_clock_override=node.get("max_clock_override"),
        rcc=rcc,
        irq=_parse_irq(node.get("irq")),
        dma=_parse_dma(node.get("dma")),
        pin_options=_parse_pin_options(node.get("pin_options")),
        pin_count=node.get("pin_count"),
        pinned=bool(node.get("pinned", True)),
        mutex_group=node.get("mutex_group"),
        power_reduction=node.get("power_reduction"),
        calibration=_parse_calibration(node.get("calibration")),
        external_triggers=_parse_external_triggers(node.get("external_triggers")),
        timing_presets=_parse_timing_presets(node.get("timing_presets")),
        trigger_source_peers=dict(node.get("trigger_source_peers") or {}),
        channels=dict(node.get("channels") or {}),
        counter_bits_default=node.get("counter_bits_default"),
        capabilities_extra=tuple(node.get("capabilities_extra") or ()),
        conflicts_with=tuple(node.get("conflicts_with") or ()),
        notes=node.get("notes"),
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_pin(node: dict[str, Any]) -> Pin:
    known = {
        "signal", "pin", "pad", "default_function", "ft", "rtc", "iomux",
        "saadc", "adc", "arduino", "pico", "voltage", "strapping_role",
        "input_only", "pinned", "constraints",
    }
    return Pin(
        signal=node["signal"],
        pin=node.get("pin"),
        pad=node.get("pad"),
        default_function=node.get("default_function"),
        ft=node.get("ft"),
        rtc=node.get("rtc"),
        iomux=node.get("iomux"),
        saadc=node.get("saadc"),
        adc=node.get("adc"),
        arduino=node.get("arduino"),
        pico=node.get("pico"),
        voltage=node.get("voltage"),
        strapping_role=node.get("strapping_role"),
        input_only=node.get("input_only"),
        pinned=bool(node.get("pinned", True)),
        constraints=tuple(node.get("constraints") or ()),
        extra={k: v for k, v in node.items() if k not in known},
    )


def _parse_interrupts(node: Any) -> tuple[InterruptVector, ...] | InterruptMatrix | None:
    if node is None:
        return None
    if isinstance(node, list):
        return tuple(
            InterruptVector(num=int(e["num"]), name=e["name"], role=e.get("role"))
            for e in node
        )
    if isinstance(node, dict) and node.get("matrix"):
        sources = node.get("peripheral_sources") or []
        return InterruptMatrix(
            matrix=True,
            internal_per_cpu=node.get("internal_per_cpu"),
            peripheral_sources=tuple(
                InterruptPeripheralSource(id=int(s["id"]), name=s["name"])
                for s in sources
            ),
        )
    raise StageExecutionError(f"unrecognised `interrupts` shape: {type(node).__name__}")


# ---------------------------------------------------------------------------
# Public entry points — parse / serialize / validate
# ---------------------------------------------------------------------------


def validate_device_payload(payload: Any) -> None:
    """Schema-validate ``payload`` against the bundled v2.1 schema.

    Raises :class:`StageExecutionError` listing every error in one
    message so reviewers see the full diagnosis at once.
    """
    validator = _validator()
    errors = sorted(validator.iter_errors(payload), key=lambda e: list(e.absolute_path))
    if errors:
        details = "\n".join(
            f"  • {'/'.join(str(p) for p in err.absolute_path) or '<root>'}: {err.message}"
            for err in errors
        )
        raise StageExecutionError(
            f"canonical device YAML failed v2.1 schema validation:\n{details}"
        )


def validate_device(text: str) -> None:
    """Schema-validate a YAML string."""
    validate_device_payload(_safe_load(text))


def parse_device_payload(payload: dict[str, Any]) -> CanonicalDevice:
    """Build a :class:`CanonicalDevice` from an already-parsed dict."""
    if not isinstance(payload, dict):
        raise StageExecutionError(
            f"canonical device YAML must be a mapping; got {type(payload).__name__}"
        )

    declared = payload.get("schema")
    if declared != CANONICAL_SCHEMA:
        raise StageExecutionError(
            f"canonical device YAML declares schema {declared!r}; "
            f"this codegen only consumes {CANONICAL_SCHEMA!r}.  "
            f"See the adopt-canonical-device-v2-1 migration note."
        )

    validate_device_payload(payload)

    return CanonicalDevice(
        identity=_parse_identity(payload["identity"]),
        provenance=_parse_provenance(payload["provenance"]),
        memory=tuple(_parse_memory_region(m) for m in payload["memory"]),
        clock=_parse_clock(payload["clock"]),
        peripherals=tuple(_parse_peripheral(p) for p in payload["peripherals"]),
        pinout=tuple(_parse_pin(p) for p in payload["pinout"]),
        templates={k: _parse_template(v) for k, v in (payload.get("templates") or {}).items()},
        interrupts=_parse_interrupts(payload.get("interrupts")),
        fuses=payload.get("fuses"),
        system_examples=payload.get("system_examples"),
    )


def parse_device(text: str) -> CanonicalDevice:
    """Parse YAML text into a :class:`CanonicalDevice`."""
    return parse_device_payload(_safe_load(text))


# ---------------------------------------------------------------------------
# Serializer — IR → primitive dict → YAML
# ---------------------------------------------------------------------------


def _drop_empty(d: dict[str, Any]) -> dict[str, Any]:
    """Strip ``None`` values + empty collections so re-serialised
    output looks like the hand-crafted YAMLs (no `field: null` lines)."""
    out: dict[str, Any] = {}
    for k, v in d.items():
        if v is None:
            continue
        if isinstance(v, (list, tuple)) and len(v) == 0:
            continue
        if isinstance(v, dict) and not v:
            continue
        out[k] = v
    return out


def _to_primitive(value: Any) -> Any:
    """Recursively convert v2.1 IR dataclasses to plain Python.

    Handles the ``extra`` field by inlining it at the same level, and
    the ``range`` 2-tuples by emitting them as 2-element lists.
    """
    if isinstance(value, CalibrationDataPoint):
        return _drop_empty({
            "rom_addr": _format_hex_or_int(value.rom_addr),
            "size_bits": value.size_bits,
            "nominal_mv": value.nominal_mv,
            "temp_celsius": value.temp_celsius,
            "vdda_calibration": value.vdda_calibration,
            "description": value.description,
        })
    if isinstance(value, AdcCalibration):
        return _drop_empty({
            "vrefint": _to_primitive(value.vrefint),
            "ts_cal_low": _to_primitive(value.ts_cal_low),
            "ts_cal_high": _to_primitive(value.ts_cal_high),
            "ts_slope_uv_per_c": value.ts_slope_uv_per_c,
        })
    if isinstance(value, ExternalTrigger):
        return _drop_empty({
            "source": value.source,
            "extsel": value.extsel,
            "jextsel": value.jextsel,
            "polarity": value.polarity,
        })
    if isinstance(value, I2cTimingPreset):
        return _drop_empty({
            "speed": value.speed,
            "source_clock": value.source_clock,
            "timingr": _format_hex_or_int(value.timingr),
            "ccr": _format_hex_or_int(value.ccr),
            "trise": _format_hex_or_int(value.trise),
        })
    if isinstance(value, PeripheralIrq):
        return {"num": value.num, "name": value.name}
    if isinstance(value, PeripheralRcc):
        out: dict[str, Any] = {}
        if value.en is not None: out["en"] = value.en
        if value.rst is not None: out["rst"] = value.rst
        out.update(value.extra)
        return out
    if isinstance(value, PeripheralDmaChannel):
        out = {}
        if value.ctrl is not None: out["ctrl"] = value.ctrl
        if value.channel is not None: out["channel"] = value.channel
        if value.dreq is not None: out["dreq"] = value.dreq
        out.update(value.extra)
        return out
    if isinstance(value, PeripheralDma):
        out = {}
        if value.tx is not None:    out["tx"] = _to_primitive(value.tx)
        if value.rx is not None:    out["rx"] = _to_primitive(value.rx)
        if value.shared is not None: out["shared"] = value.shared
        out.update(value.extra)
        return out
    if isinstance(value, PinOptionMatrix):
        out = {"matrix": True}
        if value.default is not None:   out["default"] = value.default
        if value.fast_path is not None: out["fast_path"] = value.fast_path
        return out
    if isinstance(value, PinOptionPsel):
        return {"psel": True}
    if isinstance(value, PinOptionFixed):
        out = {"pin": value.pin}
        if value.remap is not None: out["remap"] = value.remap
        if value.func is not None:  out["func"] = value.func
        if not value.pinned:        out["pinned"] = False
        return out
    if isinstance(value, SelectRegister):
        return {"reg": value.reg, "field": value.field, "encoding": dict(value.encoding)}
    if isinstance(value, SelectTask):
        out = {"on": value.on}
        if value.off is not None:    out["off"] = value.off
        if value.status is not None: out["status"] = value.status
        return out
    if isinstance(value, Oscillator):
        return _drop_empty({
            "freq": value.freq,
            "kind": value.kind,
            "tolerance": value.tolerance,
            "range": list(value.range) if value.range else None,
            "purpose": value.purpose,
            "optional": value.optional or None,
            "source": value.source,
        })
    if isinstance(value, PLLConfig):
        return _drop_empty({
            "input_sources": list(value.input_sources),
            "multiplier_range": list(value.multiplier_range) if value.multiplier_range else None,
            "outputs": list(value.outputs),
            "max_output": value.max_output,
            "vco_range": list(value.vco_range) if value.vco_range else None,
            "vco_output_target": value.vco_output_target,
            "post_divs": list(value.post_divs),
            "post_div_chain": list(value.post_div_chain),
            "output": value.output,
        })
    if isinstance(value, ClockDomain):
        out = {"id": value.id}
        if value.source is not None:           out["source"] = value.source
        if value.sources:                       out["sources"] = list(value.sources)
        if value.prescalers:
            out["prescalers"] = [int(x) if float(x).is_integer() else x for x in value.prescalers]
        if value.max is not None:               out["max"] = value.max
        if value.default is not None:           out["default"] = value.default
        if value.target_freq is not None:       out["target_freq"] = value.target_freq
        if value.purpose is not None:           out["purpose"] = value.purpose
        if value.notes is not None:             out["notes"] = value.notes
        if value.select_register is not None:   out["select_register"] = _to_primitive(value.select_register)
        if value.auxsrc_register is not None:   out["auxsrc_register"] = _to_primitive(value.auxsrc_register)
        if value.prescaler_register is not None:out["prescaler_register"] = _to_primitive(value.prescaler_register)
        if value.select_task is not None:       out["select_task"] = _to_primitive(value.select_task)
        return out
    if isinstance(value, ClockProfile):
        out = {"id": value.id, "kind": value.kind, "sysclk": value.sysclk,
               "sysclk_source": value.sysclk_source}
        out.update(value.extra)
        return out
    if isinstance(value, Clock):
        out = {
            "oscillators": {k: _to_primitive(v) for k, v in value.oscillators.items()},
            "domains": [_to_primitive(d) for d in value.domains],
        }
        if value.pll:
            out["pll"] = {k: _to_primitive(v) for k, v in value.pll.items()}
        if value.profiles:
            out["profiles"] = [_to_primitive(p) for p in value.profiles]
        if value.reset_state:
            out["reset_state"] = dict(value.reset_state)
        return out
    if isinstance(value, MulticoreCore):
        return _drop_empty({
            "id": value.id, "role": value.role,
            "vector_base": _format_hex_or_int(value.vector_base),
            "app_cpu": value.app_cpu,
            "release_register": value.release_register,
            "release_op": value.release_op,
            "start_vector_symbol": value.start_vector_symbol,
        })
    if isinstance(value, Multicore):
        return {"topology": value.topology, "cores": [_to_primitive(c) for c in value.cores]}
    if isinstance(value, Core):
        out = {"isa": value.isa, "name": value.name, "bits": value.bits}
        if value.fpu:                              out["fpu"] = True
        if value.mpu:                              out["mpu"] = True
        if value.endianness != "little":           out["endianness"] = value.endianness
        if value.interrupt_lines is not None:      out["interrupt_lines"] = value.interrupt_lines
        if value.nvic_priority_bits is not None:   out["nvic_priority_bits"] = value.nvic_priority_bits
        if value.multicore is not None:            out["multicore"] = _to_primitive(value.multicore)
        return out
    if isinstance(value, Identity):
        out = {
            "vendor": value.vendor, "family": value.family,
            "device": value.device, "core": _to_primitive(value.core),
        }
        for fld in ("variant", "package", "flash_size", "ram_size", "description"):
            v = getattr(value, fld)
            if v is not None: out[fld] = v
        out.update(value.extra)
        return out
    if isinstance(value, Provenance):
        out = {"primary": value.primary, "authored": value.authored}
        if value.authored_on is not None:   out["authored_on"] = str(value.authored_on)
        if value.secondary:                  out["secondary"] = list(value.secondary)
        if value.notes is not None:          out["notes"] = value.notes
        out.update(value.extra)
        return out
    if isinstance(value, MemoryRegion):
        out = {
            "id": value.id,
            "base": _format_hex_or_int(value.base),
            "size": value.size,
            "access": value.access,
        }
        for fld in ("alias", "address_space", "backing", "role",
                    "default_use", "survives"):
            v = getattr(value, fld)
            if v is not None: out[fld] = v
        if value.banks: out["banks"] = list(value.banks)
        out.update(value.extra)
        return out
    if isinstance(value, TemplateRegister):
        out: dict[str, Any] = {"offset": _format_hex_or_int(value.offset)}
        for fld in ("access", "stride", "count", "role"):
            v = getattr(value, fld)
            if v is not None:
                out[fld] = _format_hex_or_int(v) if fld == "stride" else v
        return out
    if isinstance(value, TemplateField):
        out = {}
        if value.bit is not None:    out["bit"] = value.bit
        if value.bits is not None:    out["bits"] = list(value.bits)
        if value.enum:                out["enum"] = dict(value.enum)
        if value.access is not None:  out["access"] = value.access
        return out
    if isinstance(value, Template):
        out = {}
        if value.extends is not None: out["extends"] = value.extends
        if value.capabilities:        out["capabilities"] = list(value.capabilities)
        if value.capabilities_extra:  out["capabilities_extra"] = list(value.capabilities_extra)
        if value.options:             out["options"] = dict(value.options)
        if value.max_clock is not None: out["max_clock"] = value.max_clock
        if value.max_baud is not None:  out["max_baud"] = value.max_baud
        if value.pins_per_port is not None: out["pins_per_port"] = value.pins_per_port
        if value.speeds_mhz:          out["speeds_mhz"] = list(value.speeds_mhz)
        if value.channels is not None: out["channels"] = value.channels
        if value.counter_bits is not None: out["counter_bits"] = value.counter_bits
        if value.counter_bits_options: out["counter_bits_options"] = list(value.counter_bits_options)
        if value.trigger_sources:     out["trigger_sources"] = dict(value.trigger_sources)
        if value.master_outputs:      out["master_outputs"] = dict(value.master_outputs)
        if value.waveform_modes:      out["waveform_modes"] = dict(value.waveform_modes)
        if value.deadtime_options:    out["deadtime_options"] = [dict(d) for d in value.deadtime_options]
        if value.break_inputs:        out["break_inputs"] = list(value.break_inputs)
        if value.registers:           out["registers"] = {k: _to_primitive(v) for k, v in value.registers.items()}
        if value.registers_extra:     out["registers_extra"] = {k: _to_primitive(v) for k, v in value.registers_extra.items()}
        if value.fields:              out["fields"] = {k: _to_primitive(v) for k, v in value.fields.items()}
        if value.fields_extra:        out["fields_extra"] = {k: _to_primitive(v) for k, v in value.fields_extra.items()}
        if value.notes is not None:   out["notes"] = value.notes
        out.update(value.extra)
        return out
    if isinstance(value, PeripheralInstance):
        out = {"id": value.id, "template": value.template}
        if value.ip_version is not None:  out["ip_version"] = value.ip_version
        if value.alias is not None:        out["alias"] = value.alias
        if value.base is not None:         out["base"] = _format_hex_or_int(value.base)
        if value.bus is not None:          out["bus"] = value.bus
        if value.clock_source is not None: out["clock_source"] = value.clock_source
        if value.max_clock_override is not None: out["max_clock_override"] = value.max_clock_override
        if value.rcc is not None:          out["rcc"] = _to_primitive(value.rcc)
        if value.irq:
            out["irq"] = (
                _to_primitive(value.irq[0]) if len(value.irq) == 1
                else [_to_primitive(i) for i in value.irq]
            )
        if value.dma is not None:          out["dma"] = _to_primitive(value.dma)
        if value.pin_options:
            out["pin_options"] = {
                k: (
                    [_to_primitive(item) for item in v] if isinstance(v, tuple)
                    else _to_primitive(v) if hasattr(v, '__dataclass_fields__')
                    else v
                )
                for k, v in value.pin_options.items()
            }
        if value.pin_count is not None:    out["pin_count"] = value.pin_count
        if not value.pinned:                out["pinned"] = False
        if value.mutex_group is not None:  out["mutex_group"] = value.mutex_group
        if value.power_reduction is not None: out["power_reduction"] = dict(value.power_reduction)
        if value.calibration is not None:  out["calibration"] = _to_primitive(value.calibration)
        if value.external_triggers:
            out["external_triggers"] = {
                kind: [_to_primitive(t) for t in trigs]
                for kind, trigs in value.external_triggers.items()
            }
        if value.timing_presets:
            out["timing_presets"] = [_to_primitive(p) for p in value.timing_presets]
        if value.trigger_source_peers:    out["trigger_source_peers"] = dict(value.trigger_source_peers)
        if value.channels:                out["channels"] = dict(value.channels)
        if value.counter_bits_default is not None: out["counter_bits_default"] = value.counter_bits_default
        if value.capabilities_extra:      out["capabilities_extra"] = list(value.capabilities_extra)
        if value.conflicts_with:          out["conflicts_with"] = list(value.conflicts_with)
        if value.notes is not None:        out["notes"] = value.notes
        out.update(value.extra)
        return out
    if isinstance(value, Pin):
        out = {"signal": value.signal}
        for fld in ("pin", "pad", "default_function", "ft", "rtc", "iomux",
                    "saadc", "adc", "arduino", "pico", "voltage",
                    "strapping_role", "input_only"):
            v = getattr(value, fld)
            if v is not None: out[fld] = v
        if not value.pinned:        out["pinned"] = False
        if value.constraints:        out["constraints"] = list(value.constraints)
        out.update(value.extra)
        return out
    if isinstance(value, InterruptVector):
        out = {"num": value.num, "name": value.name}
        if value.role is not None:  out["role"] = value.role
        return out
    if isinstance(value, InterruptPeripheralSource):
        return {"id": value.id, "name": value.name}
    if isinstance(value, InterruptMatrix):
        out = {"matrix": True}
        if value.internal_per_cpu is not None:
            out["internal_per_cpu"] = value.internal_per_cpu
        if value.peripheral_sources:
            out["peripheral_sources"] = [_to_primitive(s) for s in value.peripheral_sources]
        return out
    if isinstance(value, CanonicalDevice):
        out = {
            "schema": value.schema,
            "identity": _to_primitive(value.identity),
            "provenance": _to_primitive(value.provenance),
            "memory": [_to_primitive(m) for m in value.memory],
            "clock": _to_primitive(value.clock),
        }
        if value.templates:
            out["templates"] = {k: _to_primitive(v) for k, v in value.templates.items()}
        out["peripherals"] = [_to_primitive(p) for p in value.peripherals]
        out["pinout"]      = [_to_primitive(p) for p in value.pinout]
        if value.interrupts is not None:
            if isinstance(value.interrupts, tuple):
                out["interrupts"] = [_to_primitive(i) for i in value.interrupts]
            else:
                out["interrupts"] = _to_primitive(value.interrupts)
        if value.fuses is not None:           out["fuses"] = value.fuses
        if value.system_examples is not None: out["system_examples"] = value.system_examples
        return out
    # Plain primitives + already-primitive collections.
    if isinstance(value, (list, tuple)):
        return [_to_primitive(v) for v in value]
    if isinstance(value, dict):
        return {k: _to_primitive(v) for k, v in value.items()}
    return value


def serialize_device(ir: CanonicalDevice) -> str:
    """Render an IR to deterministic v2.1 YAML text."""
    payload = _to_primitive(ir)
    if not isinstance(payload, dict):
        raise StageExecutionError(
            f"_to_primitive must return a dict; got {type(payload).__name__}"
        )
    validate_device_payload(payload)  # belt-and-braces
    ordered = _ordered_top_level(payload)
    text = yaml.dump(
        ordered,
        Dumper=_CanonicalDumper,
        default_flow_style=False,
        sort_keys=False,
        allow_unicode=True,
        width=10_000,
    )
    if not text.endswith("\n"):
        text += "\n"
    return text


__all__ = [
    "CANONICAL_SCHEMA",
    "SCHEMA_PATH",
    "parse_device",
    "parse_device_payload",
    "serialize_device",
    "validate_device",
    "validate_device_payload",
]
