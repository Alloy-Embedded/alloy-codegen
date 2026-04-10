"""STM32_open_pin_data source adapter for package, pin, and AF metadata."""

from __future__ import annotations

import hashlib
import re
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.patches import load_device_patch
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.raw import (
    RawPinAlternateFunction,
    RawPinDataDocument,
    RawPinDocumentEntry,
)

STM32_OPEN_PIN_DATA_REMOTE = "https://github.com/STMicroelectronics/STM32_open_pin_data.git"
MCU_SUBTREE = "mcu"
XML_NAMESPACE = {"st": "http://dummy.com"}
PIN_NAME_PATTERN = re.compile(r"\bP(?P<port>[A-Z])(?P<number>\d+)\b")
PACKAGE_PIN_COUNT_PATTERN = re.compile(r"(?P<count>\d+)$")
GPIO_AF_PATTERN = re.compile(r"GPIO_AF(?P<af>\d+)_")


def ensure_source_root(context: ExecutionContext) -> Path:
    """Resolve a usable STM32_open_pin_data root, cloning if needed."""
    if context.pin_source_root is not None:
        if not (context.pin_source_root / MCU_SUBTREE).exists():
            raise StageExecutionError(
                "Configured pin source root does not contain "
                f"'{MCU_SUBTREE}': {context.pin_source_root}"
            )
        return context.pin_source_root

    source_root = context.source_cache_dir / "STM32_open_pin_data"
    if (source_root / MCU_SUBTREE).exists():
        return source_root

    source_root.parent.mkdir(parents=True, exist_ok=True)
    clone_cmd = [
        "git",
        "clone",
        "--depth",
        "1",
        "--filter=blob:none",
        "--sparse",
        STM32_OPEN_PIN_DATA_REMOTE,
        str(source_root),
    ]
    sparse_cmd = ["git", "-C", str(source_root), "sparse-checkout", "set", MCU_SUBTREE]

    for command in (clone_cmd, sparse_cmd):
        completed = subprocess.run(command, capture_output=True, text=True)
        if completed.returncode != 0:
            raise StageExecutionError(
                "Failed to prepare STM32_open_pin_data source root with command "
                f"{' '.join(command)}: {completed.stderr.strip()}"
            )

    return source_root


def source_revision(source_root: Path) -> str:
    """Read the current source revision if the root is a git checkout."""
    completed = subprocess.run(
        ["git", "-C", str(source_root), "rev-parse", "--show-toplevel"],
        capture_output=True,
        text=True,
    )
    top_level = Path(completed.stdout.strip()).resolve() if completed.returncode == 0 else None
    if top_level == source_root.resolve():
        head = subprocess.run(
            ["git", "-C", str(source_root), "rev-parse", "HEAD"],
            capture_output=True,
            text=True,
        )
        if head.returncode == 0:
            return head.stdout.strip()

    digest = hashlib.sha256()
    subtree = source_root / MCU_SUBTREE
    for path in sorted(subtree.rglob("*")):
        if not path.is_file():
            continue
        digest.update(str(path.relative_to(source_root)).encode("utf-8"))
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


def resolve_mcu_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the MCU XML path for one device."""
    patch = load_device_patch(context, device_name, vendor=vendor, family=family)
    source_root = ensure_source_root(context)
    mcu_path = source_root / MCU_SUBTREE / patch.pin_data_file
    if not mcu_path.exists():
        raise StageExecutionError(
            f"Missing pin data file '{patch.pin_data_file}' for device '{device_name}'."
        )
    return mcu_path


def parse_ip_version_table(mcu_path: Path) -> dict[str, str]:
    """Return a mapping of peripheral instance name → vendor IP version string.

    Reads the ``<IP InstanceName="..." Version="..."/>`` elements from the MCU
    XML.  Only entries that carry both attributes are included.  The result is
    keyed by the *instance* name (e.g. ``"USART1"``) so the normalizer can look
    up the version by canonical peripheral name.
    """
    mcu_root = ET.parse(mcu_path).getroot()
    table: dict[str, str] = {}
    for ip_node in mcu_root.findall("st:IP", XML_NAMESPACE):
        instance_name = ip_node.get("InstanceName")
        version = ip_node.get("Version")
        if instance_name and version:
            table[instance_name] = version
    return table


def _parse_gpio_modes_file_name(mcu_root: ET.Element) -> str:
    for ip_node in mcu_root.findall("st:IP", XML_NAMESPACE):
        if ip_node.get("Name") != "GPIO":
            continue
        version = ip_node.get("Version")
        if version:
            return f"GPIO-{version}_Modes.xml"
    raise StageExecutionError("MCU XML does not declare a GPIO IP version.")


def resolve_gpio_modes_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the GPIO modes XML path for one device."""
    source_root = ensure_source_root(context)
    mcu_path = resolve_mcu_path(context, device_name, vendor=vendor, family=family)
    mcu_root = ET.parse(mcu_path).getroot()
    modes_file = _parse_gpio_modes_file_name(mcu_root)
    modes_path = source_root / MCU_SUBTREE / "IP" / modes_file
    if not modes_path.exists():
        raise StageExecutionError(
            f"Missing GPIO modes file '{modes_file}' for device '{device_name}'."
        )
    return modes_path


def fetch_records(context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    """Resolve upstream pin-data records for the requested scope."""
    validated_scope = scope.validate_supported()
    root = ensure_source_root(context)
    revision = source_revision(root)
    records: list[dict[str, str]] = []
    _vendor = validated_scope.resolved_vendor()
    _family = validated_scope.resolved_family()
    for device_name in validated_scope.resolved_device_names():
        mcu_path = resolve_mcu_path(context, device_name, vendor=_vendor, family=_family)
        modes_path = resolve_gpio_modes_path(context, device_name, vendor=_vendor, family=_family)
        for local_path in (mcu_path, modes_path):
            records.append(
                {
                    "source_id": "stm32-open-pin-data",
                    "target_device": device_name,
                    "origin_url": STM32_OPEN_PIN_DATA_REMOTE,
                    "revision": revision,
                    "local_path": str(local_path),
                    "upstream_path": str(local_path.relative_to(root)).replace("\\", "/"),
                }
            )
    return tuple(records)


def _extract_pin_identity(raw_name: str) -> tuple[str, str, int] | None:
    match = PIN_NAME_PATTERN.search(raw_name)
    if match is None:
        return None
    port = match.group("port")
    number = int(match.group("number"))
    return (f"P{port}{number}", port, number)


def _extract_package_pin_count(package_name: str) -> int | None:
    match = PACKAGE_PIN_COUNT_PATTERN.search(package_name)
    if match is None:
        return None
    return int(match.group("count"))


def _parse_af_number(pin_signal: ET.Element) -> int | None:
    for parameter in pin_signal.findall("st:SpecificParameter", XML_NAMESPACE):
        if parameter.get("Name") != "GPIO_AF":
            continue
        possible = parameter.find("st:PossibleValue", XML_NAMESPACE)
        if possible is None or possible.text is None:
            continue
        match = GPIO_AF_PATTERN.search(possible.text)
        if match is not None:
            return int(match.group("af"))
    return None


def _parse_gpio_modes(modes_path: Path) -> dict[str, dict[str, int]]:
    modes_root = ET.parse(modes_path).getroot()
    signals_by_pin: dict[str, dict[str, int]] = {}
    for gpio_pin in modes_root.findall(".//st:GPIO_Pin", XML_NAMESPACE):
        pin_name = gpio_pin.get("Name")
        if not pin_name:
            continue
        pin_signals: dict[str, int] = {}
        for pin_signal in gpio_pin.findall("st:PinSignal", XML_NAMESPACE):
            signal_name = pin_signal.get("Name")
            af_number = _parse_af_number(pin_signal)
            if signal_name and af_number is not None:
                pin_signals[signal_name] = af_number
        signals_by_pin[pin_name] = pin_signals
    return signals_by_pin


def _resolve_af_number(signal_name: str, available_signals: dict[str, int]) -> int | None:
    exact = available_signals.get(signal_name)
    if exact is not None:
        return exact

    prefix_matches = {
        af_number
        for candidate, af_number in available_signals.items()
        if signal_name.startswith(candidate) or candidate.startswith(signal_name)
    }
    if len(prefix_matches) == 1:
        return next(iter(prefix_matches))
    return None


def parse_raw_pin_data_document(
    *,
    mcu_path: Path,
    gpio_modes_path: Path,
) -> RawPinDataDocument:
    """Parse a minimal raw pin data document from STM32_open_pin_data XML sources."""
    mcu_root = ET.parse(mcu_path).getroot()
    available_signals = _parse_gpio_modes(gpio_modes_path)
    package_name = (mcu_root.get("Package") or "").lower()
    pins_by_position: dict[int, RawPinDocumentEntry] = {}
    pins_without_position: list[RawPinDocumentEntry] = []

    for pin_node in mcu_root.findall("st:Pin", XML_NAMESPACE):
        raw_name = pin_node.get("Name") or ""
        identity = _extract_pin_identity(raw_name)
        if identity is None:
            continue

        pin_name, port, number = identity
        af_signals: list[RawPinAlternateFunction] = []
        available_by_signal = available_signals.get(pin_name, {})
        for signal_node in pin_node.findall("st:Signal", XML_NAMESPACE):
            signal_name = signal_node.get("Name")
            if signal_name is None or signal_name == "GPIO":
                continue
            af_number = _resolve_af_number(signal_name, available_by_signal)
            if af_number is None:
                continue
            af_signals.append(
                RawPinAlternateFunction(
                    signal_name=signal_name,
                    af_number=af_number,
                )
            )

        entry = RawPinDocumentEntry(
            name=pin_name,
            port=port,
            number=number,
            signals=tuple(
                sorted(
                    af_signals,
                    key=lambda item: (item.af_number, item.signal_name),
                )
            ),
        )
        position_text = pin_node.get("Position")
        if position_text is not None and position_text.isdigit():
            pins_by_position.setdefault(int(position_text), entry)
        else:
            pins_without_position.append(entry)

    return RawPinDataDocument(
        device_name=(mcu_root.get("RefName") or mcu_path.stem).lower(),
        package_name=package_name,
        package_pin_count=_extract_package_pin_count(package_name),
        pins=tuple(
            [
                pins_by_position[position]
                for position in sorted(pins_by_position)
            ]
            + sorted(pins_without_position, key=lambda item: (item.port, item.number, item.name))
        ),
        gpio_modes_file=gpio_modes_path.name,
    )
