"""Microchip Device Family Pack source adapter for SAME70 bootstrap support."""

from __future__ import annotations

import hashlib
import re
import shutil
import urllib.request
import xml.etree.ElementTree as ET
import zipfile
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.patches import DevicePatch, DmaRequestPatch, MemoryPatch, PeripheralPatch
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.raw import (
    RawInterrupt,
    RawPackagePadEntry,
    RawPeripheral,
    RawPinAlternateFunction,
    RawPinDataDocument,
    RawPinDocumentEntry,
    RawRegister,
    RawRegisterField,
)

PACK_SOURCE_ID = "microchip-dfp-pack"
EXTRACT_SOURCE_ID = "microchip-dfp-extract"
MICROCHIP_PACK_REMOTE = "https://packs.download.microchip.com/"
GPIO_PAD_PATTERN = re.compile(r"^P(?P<port>[A-Z])(?P<number>\d+)$")
POSITION_PATTERN = re.compile(r"^(?P<row>[A-Z]+)(?P<column>\d+)$")
ALT_FUNCTION_PATTERN = re.compile(r"^[A-Z]$")
ALT_FUNCTION_EXT_PATTERN = re.compile(r"^X(?P<index>\d+)$")
DMA_PARAMETER_PATTERN = re.compile(r"^DMAC_ID_(?P<signal>[A-Z0-9_]+)$")


@dataclass(frozen=True, slots=True)
class PackConfig:
    """Pinned upstream pack configuration for one supported family."""

    archive_name: str
    archive_url: str


@dataclass(frozen=True, slots=True)
class SelectedDeviceFiles:
    """Selected file set for one Microchip device inside a DFP extract.

    ``svd_path`` is optional: AVR 8-bit families publish ATDF only, with
    register data carried inline in the ATDF (no CMSIS-SVD file is produced).
    Callers MUST check ``svd_path is not None`` before using it.
    """

    device_name: str
    pdsc_path: Path
    atdf_path: Path
    svd_path: Path | None


PACK_CONFIGS: dict[tuple[str, str], PackConfig] = {
    (
        "microchip",
        "same70",
    ): PackConfig(
        archive_name="Microchip.SAME70_DFP.4.13.292.atpack",
        archive_url="https://packs.download.microchip.com/Microchip.SAME70_DFP.4.13.292.atpack",
    ),
    # AVR-Dx DFP — covers AVR128DA/DB/DD parts.  AVR devices use ATDF only; no
    # CMSIS-SVD is published for them.  The adapter treats SVD as optional when
    # the family matches an ATDF-only architecture.
    (
        "microchip",
        "avr-da",
    ): PackConfig(
        archive_name="Microchip.AVR-Dx_DFP.2.4.286.atpack",
        archive_url="https://packs.download.microchip.com/Microchip.AVR-Dx_DFP.2.4.286.atpack",
    ),
}

# Families whose ATDF pack does not include an SVD file (typical for 8-bit AVR).
# The device-file selector treats missing SVD entries as a non-fatal condition
# for these families, deferring register-data resolution to the ATDF.
SVD_OPTIONAL_FAMILIES: frozenset[tuple[str, str]] = frozenset(
    {
        ("microchip", "avr-da"),
    }
)


def _config_for(vendor: str, family: str) -> PackConfig:
    key = (vendor.lower(), family.lower())
    if key not in PACK_CONFIGS:
        raise StageExecutionError(f"Unsupported Microchip DFP family: {vendor}/{family}")
    return PACK_CONFIGS[key]


def _hash_file(path: Path) -> str:
    digest = hashlib.sha256()
    digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


def _hash_tree(root: Path) -> str:
    digest = hashlib.sha256()
    for path in sorted(root.rglob("*")):
        if not path.is_file():
            continue
        digest.update(str(path.relative_to(root)).encode("utf-8"))
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


def _local_name(tag: str) -> str:
    return tag.rsplit("}", maxsplit=1)[-1]


def _iter_children(element: ET.Element, local_name: str) -> list[ET.Element]:
    return [child for child in list(element) if _local_name(child.tag) == local_name]


def _first_child(element: ET.Element, local_name: str) -> ET.Element | None:
    for child in list(element):
        if _local_name(child.tag) == local_name:
            return child
    return None


def _first_descendant(element: ET.Element, local_name: str) -> ET.Element | None:
    for node in element.iter():
        if _local_name(node.tag) == local_name:
            return node
    return None


def _find_pdsc_path(extract_root: Path) -> Path:
    candidates = sorted(extract_root.glob("*.pdsc"))
    if len(candidates) != 1:
        raise StageExecutionError(
            f"Expected exactly one PDSC file in Microchip DFP extract root {extract_root}, "
            f"found {len(candidates)}."
        )
    return candidates[0]


def _download_pack_if_missing(target_path: Path, archive_url: str) -> None:
    target_path.parent.mkdir(parents=True, exist_ok=True)
    try:
        with urllib.request.urlopen(archive_url) as response, target_path.open("wb") as output:
            shutil.copyfileobj(response, output)
    except Exception as exc:  # pragma: no cover - network failures are environment-specific
        raise StageExecutionError(
            f"Failed to download Microchip DFP archive from {archive_url}: {exc}"
        ) from exc


def ensure_pack_path(context: ExecutionContext, *, vendor: str, family: str) -> Path | None:
    """Resolve a usable DFP archive path when available."""
    configured_root = context.source_root_for(PACK_SOURCE_ID)
    config = _config_for(vendor, family)
    if configured_root is not None:
        if configured_root.is_file():
            if configured_root.suffix != ".atpack":
                raise StageExecutionError(
                    f"Configured {PACK_SOURCE_ID} override is not an .atpack file: "
                    f"{configured_root}"
                )
            return configured_root
        candidate = configured_root / config.archive_name
        if candidate.exists():
            return candidate
        archives = sorted(configured_root.glob("*.atpack"))
        if len(archives) == 1:
            return archives[0]
        raise StageExecutionError(
            f"Configured {PACK_SOURCE_ID} override does not resolve a single .atpack archive: "
            f"{configured_root}"
        )

    target_path = context.source_cache_dir / "microchip-dfp" / config.archive_name
    if not target_path.exists():
        _download_pack_if_missing(target_path, config.archive_url)
    return target_path


def ensure_extract_root(context: ExecutionContext, *, vendor: str, family: str) -> Path:
    """Resolve a usable extracted DFP tree, extracting the archive when needed."""
    configured_root = context.source_root_for(EXTRACT_SOURCE_ID)
    if configured_root is not None:
        if not configured_root.exists():
            raise StageExecutionError(
                f"Configured {EXTRACT_SOURCE_ID} override does not exist: {configured_root}"
            )
        _find_pdsc_path(configured_root)
        return configured_root

    pack_path = ensure_pack_path(context, vendor=vendor, family=family)
    if pack_path is None:
        raise StageExecutionError(
            f"Cannot resolve {EXTRACT_SOURCE_ID} without either an extract override or a pack."
        )
    archive_hash = _hash_file(pack_path).split(":", maxsplit=1)[1]
    extract_root = context.source_cache_dir / "microchip-dfp" / f"{family}-{archive_hash[:16]}"
    pdsc_path = extract_root / f"Microchip.{family.upper()}_DFP.pdsc"
    if pdsc_path.exists():
        return extract_root

    extract_root.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(pack_path) as archive:
        archive.extractall(extract_root)
    _find_pdsc_path(extract_root)
    return extract_root


def _select_device_files_from_pdsc(
    pdsc_path: Path,
    device_name: str,
    *,
    svd_required: bool = True,
) -> SelectedDeviceFiles:
    root = ET.parse(pdsc_path).getroot()
    requested_name = device_name.upper()
    for node in root.iter():
        if _local_name(node.tag) != "device":
            continue
        if node.get("Dname") != requested_name:
            continue
        debug_node = _first_child(node, "debug")
        atdf_node = _first_descendant(node, "atdf")
        svd_relative_path = None if debug_node is None else debug_node.get("svd")
        atdf_relative_path = None if atdf_node is None else atdf_node.get("name")
        if atdf_relative_path is None:
            raise StageExecutionError(
                f"PDSC entry for {requested_name} does not declare an ATDF path."
            )
        if svd_required and svd_relative_path is None:
            raise StageExecutionError(
                f"PDSC entry for {requested_name} does not declare an SVD path."
            )
        return SelectedDeviceFiles(
            device_name=device_name.lower(),
            pdsc_path=pdsc_path,
            atdf_path=pdsc_path.parent / atdf_relative_path,
            svd_path=(
                None if svd_relative_path is None else pdsc_path.parent / svd_relative_path
            ),
        )
    raise StageExecutionError(f"Device {requested_name} is not present in {pdsc_path.name}.")


def select_device_files(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> SelectedDeviceFiles:
    """Select the ATDF and (optionally) SVD files for one device from the pack tree."""
    extract_root = ensure_extract_root(context, vendor=vendor, family=family)
    svd_required = (vendor.lower(), family.lower()) not in SVD_OPTIONAL_FAMILIES
    selected = _select_device_files_from_pdsc(
        _find_pdsc_path(extract_root), device_name, svd_required=svd_required
    )
    paths_to_check: list[Path] = [selected.atdf_path]
    if selected.svd_path is not None:
        paths_to_check.append(selected.svd_path)
    for path in paths_to_check:
        if not path.exists():
            raise StageExecutionError(f"Selected Microchip DFP source file is missing: {path}")
    return selected


def fetch_records(context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    """Resolve upstream Microchip DFP records for the requested scope."""
    validated_scope = scope.validate_supported()
    vendor = validated_scope.resolved_vendor()
    family = validated_scope.resolved_family()
    configured_pack_root = context.source_root_for(PACK_SOURCE_ID)
    configured_extract_root = context.source_root_for(EXTRACT_SOURCE_ID)
    pack_path = (
        ensure_pack_path(context, vendor=vendor, family=family)
        if configured_pack_root is not None or configured_extract_root is None
        else None
    )
    extract_root = ensure_extract_root(context, vendor=vendor, family=family)
    config = _config_for(vendor, family)
    pack_revision = _hash_file(pack_path) if pack_path is not None else None
    extract_revision = _hash_tree(extract_root)
    pdsc_path = _find_pdsc_path(extract_root)

    records: list[dict[str, str]] = []
    for device_name in validated_scope.resolved_device_names():
        selected = select_device_files(context, device_name, vendor=vendor, family=family)
        if pack_path is not None and pack_revision is not None:
            records.append(
                {
                    "source_id": PACK_SOURCE_ID,
                    "target_device": device_name,
                    "origin_url": config.archive_url,
                    "revision": pack_revision,
                    "local_path": str(pack_path),
                    "upstream_path": pack_path.name,
                }
            )
        records.append(
            {
                "source_id": EXTRACT_SOURCE_ID,
                "target_device": device_name,
                "origin_url": config.archive_url,
                "revision": extract_revision,
                "local_path": str(extract_root),
                "upstream_path": ".",
            }
        )
        extract_files: list[Path] = [pdsc_path, selected.atdf_path]
        if selected.svd_path is not None:
            extract_files.append(selected.svd_path)
        for local_path in extract_files:
            records.append(
                {
                    "source_id": EXTRACT_SOURCE_ID,
                    "target_device": device_name,
                    "origin_url": config.archive_url,
                    "revision": extract_revision,
                    "local_path": str(local_path),
                    "upstream_path": str(local_path.relative_to(extract_root)).replace("\\", "/"),
                }
            )
    return tuple(records)


def resolve_atdf_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the ATDF path for one device."""
    return select_device_files(context, device_name, vendor=vendor, family=family).atdf_path


def resolve_svd_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the SVD path for one device from the DFP extract.

    Raises ``StageExecutionError`` if the family does not publish an SVD file
    (the AVR 8-bit DFPs, for example, ship ATDF only).
    """
    selected = select_device_files(context, device_name, vendor=vendor, family=family)
    if selected.svd_path is None:
        raise StageExecutionError(
            f"Microchip family {vendor}/{family} does not publish an SVD file; use "
            "resolve_atdf_path() instead."
        )
    return selected.svd_path


def parse_ip_version_table(atdf_path: Path) -> dict[str, str]:
    """Return a mapping of canonical peripheral instance name to module version."""
    root = ET.parse(atdf_path).getroot()
    devices_node = root.find("devices")
    if devices_node is None:
        return {}
    device_node = devices_node.find("device")
    if device_node is None:
        return {}
    peripherals_node = device_node.find("peripherals")
    if peripherals_node is None:
        return {}

    table: dict[str, str] = {}
    for module_node in peripherals_node.findall("module"):
        module_name = str(module_node.get("name") or "").upper()
        version = str(module_node.get("version") or "").strip()
        for instance_node in module_node.findall("instance"):
            instance_name = str(instance_node.get("name") or "").upper()
            if not instance_name:
                continue
            table[_canonical_peripheral_name(instance_name)] = (
                f"{module_name.lower()}_{version.lower()}" if version else module_name.lower()
            )
    return table


def _parse_access(*, rw: str | None, executable: str | None) -> str:
    access = ""
    upper_rw = (rw or "").upper()
    if "R" in upper_rw:
        access += "r"
    if "W" in upper_rw:
        access += "w"
    if executable and executable.lower() == "true":
        access += "x"
    return access or "rw"


def _map_memory_kind(raw_kind: str) -> str:
    normalized = raw_kind.lower()
    return {
        "flash": "flash",
        "ram": "sram",
        "rom": "rom",
        "io": "io",
        "other": "memory",
    }.get(normalized, normalized)


def parse_memory_patches(atdf_path: Path) -> tuple[MemoryPatch, ...]:
    """Parse memory regions from the ATDF address-space description."""
    root = ET.parse(atdf_path).getroot()
    devices_node = root.find("devices")
    if devices_node is None:
        return ()
    device_node = devices_node.find("device")
    if device_node is None:
        return ()
    address_spaces = device_node.find("address-spaces")
    if address_spaces is None:
        return ()

    memories: list[MemoryPatch] = []
    for address_space in address_spaces.findall("address-space"):
        address_space_id = address_space.get("id")
        normalized_address_space = None
        if address_space_id not in {None, "", "base"}:
            normalized_address_space = str(address_space_id).lower()
        for segment in address_space.findall("memory-segment"):
            name = segment.get("name")
            start = segment.get("start")
            size = segment.get("size")
            if name is None or start is None or size is None:
                continue
            memories.append(
                MemoryPatch(
                    name=name.lower(),
                    kind=_map_memory_kind(str(segment.get("type") or "memory")),
                    base_address=int(start, 16),
                    size_bytes=int(size, 16),
                    access=_parse_access(
                        rw=segment.get("rw"),
                        executable=segment.get("exec"),
                    ),
                    address_space=normalized_address_space,
                )
            )
    return tuple(memories)


def _parameter_map(instance_node: ET.Element) -> dict[str, str]:
    parameters_node = instance_node.find("parameters")
    if parameters_node is None:
        return {}
    return {
        str(parameter.get("name")): str(parameter.get("value"))
        for parameter in parameters_node.findall("param")
        if parameter.get("name") is not None and parameter.get("value") is not None
    }


def _clock_id_for_instance(parameters: dict[str, str]) -> str | None:
    direct = parameters.get("CLOCK_ID") or parameters.get("INSTANCE_ID")
    if direct is not None:
        return direct
    for key in sorted(parameters):
        if key.startswith("CLOCK_ID_"):
            return parameters[key]
    for key in sorted(parameters):
        if key.startswith("INSTANCE_ID_"):
            return parameters[key]
    return None


def _canonical_peripheral_name(name: str) -> str:
    upper_name = name.upper()
    if upper_name.startswith("PIO") and len(upper_name) == 4:
        return f"GPIO{upper_name[-1]}"
    return upper_name


def parse_peripheral_patches(atdf_path: Path) -> tuple[PeripheralPatch, ...]:
    """Parse peripheral instance metadata and synthesize clock ownership strings."""
    root = ET.parse(atdf_path).getroot()
    devices_node = root.find("devices")
    if devices_node is None:
        return ()
    device_node = devices_node.find("device")
    if device_node is None:
        return ()
    peripherals_node = device_node.find("peripherals")
    if peripherals_node is None:
        return ()

    peripherals: dict[str, PeripheralPatch] = {}
    for module_node in peripherals_node.findall("module"):
        for instance_node in module_node.findall("instance"):
            instance_name = instance_node.get("name")
            if instance_name is None:
                continue
            register_group = instance_node.find("register-group")
            if register_group is None:
                continue
            parameters = _parameter_map(instance_node)
            clock_id = _clock_id_for_instance(parameters)
            canonical_name = _canonical_peripheral_name(instance_name)
            peripherals.setdefault(
                canonical_name,
                PeripheralPatch(
                    name=canonical_name,
                    rcc_enable_signal=None if clock_id is None else f"PMC.PID{clock_id}",
                    rcc_reset_signal=None,
                    ip_version=None,
                ),
            )
    return tuple(sorted(peripherals.values(), key=lambda peripheral: peripheral.name))


_AVR_INTERRUPT_PERIPHERAL_PATTERN = re.compile(
    r"^(?P<peripheral>[A-Z][A-Z0-9]*\d+)"
)


def parse_peripheral_base_addresses(atdf_path: Path) -> dict[str, int]:
    """Return ``{peripheral_name: register_group_offset}`` from an ATDF.

    AVR ATDFs use the ``<register-group offset="0x800" .../>`` attribute as
    the canonical per-instance register-file base address (in the AVR `data`
    address space).  For runtime-descriptor purposes those offsets act the
    same as an ARM peripheral `base_address`.  When the offset is missing or
    unparseable the peripheral is omitted from the result.
    """
    root = ET.parse(atdf_path).getroot()
    devices_node = root.find("devices")
    if devices_node is None:
        return {}
    device_node = devices_node.find("device")
    if device_node is None:
        return {}
    peripherals_node = device_node.find("peripherals")
    if peripherals_node is None:
        return {}
    offsets: dict[str, int] = {}
    for module_node in peripherals_node.findall("module"):
        for instance_node in module_node.findall("instance"):
            instance_name = instance_node.get("name")
            register_group = instance_node.find("register-group")
            if instance_name is None or register_group is None:
                continue
            offset_text = register_group.get("offset")
            if offset_text is None:
                continue
            try:
                offsets[_canonical_peripheral_name(instance_name)] = int(offset_text, 0)
            except ValueError:
                continue
    return offsets


def parse_interrupts_from_atdf(atdf_path: Path) -> tuple[RawInterrupt, ...]:
    """Parse ``<interrupts>`` from an ATDF into canonical RawInterrupt tuples.

    Microchip ATDFs publish ``<interrupt index="N" name="FOO_BAR" .../>``
    entries under the device node.  AVR 8-bit devices do not ship CMSIS-SVD,
    so this is the only source of truth for their vector table.

    The ``peripheral`` field on the returned `RawInterrupt` is inferred from
    the interrupt name prefix using a simple regex: everything up to the
    first underscore that matches a canonical instance identifier
    (``USART0``, ``TWI0``, ``SPI0``, etc.).  Interrupts whose name does not
    begin with a recognizable peripheral prefix (``RESET``, ``NMI``, …) get
    ``peripheral=None`` — the validation layer already allows system
    exceptions to carry no peripheral attribution.
    """
    root = ET.parse(atdf_path).getroot()
    devices_node = root.find("devices")
    if devices_node is None:
        return ()
    device_node = devices_node.find("device")
    if device_node is None:
        return ()
    interrupts_node = device_node.find("interrupts")
    if interrupts_node is None:
        return ()

    results: list[RawInterrupt] = []
    for interrupt_node in interrupts_node.findall("interrupt"):
        name = interrupt_node.get("name")
        index_text = interrupt_node.get("index")
        if name is None or index_text is None:
            continue
        try:
            line = int(index_text)
        except ValueError:
            continue
        peripheral: str | None = None
        head, _, _ = name.partition("_")
        if _AVR_INTERRUPT_PERIPHERAL_PATTERN.match(head):
            peripheral = head
        results.append(RawInterrupt(name=name, line=line, peripheral=peripheral))
    return tuple(results)


def _mask_to_bit_range(mask_text: str) -> tuple[int, int] | None:
    """Convert a hex ATDF bitfield mask like ``0x1E`` into ``(bit_offset, bit_width)``.

    Returns ``None`` if the mask cannot be parsed or is not a contiguous
    run of 1 bits (ATDF does publish non-contiguous masks for a few
    peripherals; those are skipped from the canonical IR for now).
    """
    try:
        mask = int(mask_text, 0)
    except ValueError:
        return None
    if mask <= 0:
        return None
    bit_offset = 0
    while mask & 0x1 == 0:
        mask >>= 1
        bit_offset += 1
    if mask & (mask + 1) != 0:  # mask is not a contiguous run of ones
        return None
    bit_width = mask.bit_length()
    return (bit_offset, bit_width)


def _parse_module_register_catalog(
    atdf_path: Path,
) -> dict[str, tuple[RawRegister, ...]]:
    """Parse ``<modules>`` from an ATDF into ``{module_name: (RawRegister, ...)}``.

    Each AVR ATDF publishes module-scope register definitions under a
    top-level ``<modules>`` element.  Device instances then reference
    those modules via ``<instance>/<register-group name-in-module="X"
    offset="N"/>``.  This catalog lets downstream code expand every
    admitted peripheral instance into concrete ``RawRegister`` entries
    at their runtime offsets (module-internal offset only — the
    instance-level register-group offset is added at the call site).

    Bitfields with a non-contiguous mask are dropped (cannot be expressed
    as a single ``(bit_offset, bit_width)`` pair); this is rare and only
    affects a few legacy AVR peripherals.
    """
    root = ET.parse(atdf_path).getroot()
    modules_node = root.find("modules")
    if modules_node is None:
        return {}
    catalog: dict[str, tuple[RawRegister, ...]] = {}
    for module_node in modules_node.findall("module"):
        module_name = module_node.get("name")
        if module_name is None:
            continue
        registers: list[RawRegister] = []
        # Most AVR-Dx modules expose exactly one top-level register-group
        # matching the module name.  Walk every register-group under the
        # module to be conservative.
        for group_node in module_node.findall("register-group"):
            for register_node in group_node.findall("register"):
                reg_name = register_node.get("name")
                reg_offset_text = register_node.get("offset")
                if reg_name is None or reg_offset_text is None:
                    continue
                try:
                    reg_offset = int(reg_offset_text, 0)
                except ValueError:
                    continue
                reg_size_text = register_node.get("size")
                reg_size_bits: int | None = None
                if reg_size_text is not None:
                    try:
                        reg_size_bits = int(reg_size_text, 0) * 8
                    except ValueError:
                        reg_size_bits = None
                reg_rw = register_node.get("rw")
                reg_access = _parse_access(rw=reg_rw, executable=None)
                fields: list[RawRegisterField] = []
                for bitfield_node in register_node.findall("bitfield"):
                    field_name = bitfield_node.get("name")
                    mask_text = bitfield_node.get("mask")
                    if field_name is None or mask_text is None:
                        continue
                    bit_range = _mask_to_bit_range(mask_text)
                    if bit_range is None:
                        continue
                    bit_offset, bit_width = bit_range
                    field_rw = bitfield_node.get("rw") or reg_rw
                    fields.append(
                        RawRegisterField(
                            name=field_name,
                            bit_offset=bit_offset,
                            bit_width=bit_width,
                            access=_parse_access(rw=field_rw, executable=None),
                        )
                    )
                registers.append(
                    RawRegister(
                        name=reg_name,
                        offset_bytes=reg_offset,
                        access=reg_access,
                        size_bits=reg_size_bits,
                        fields=tuple(fields),
                    )
                )
        catalog[module_name] = tuple(registers)
    return catalog


def parse_raw_peripherals_from_atdf(atdf_path: Path) -> tuple[RawPeripheral, ...]:
    """Build ``RawPeripheral`` entries from an ATDF by joining the per-device
    ``<instance>`` register-group offsets with the ``<modules>`` register catalog.

    Each admitted instance becomes one ``RawPeripheral`` whose
    ``base_address`` is the ``offset`` on its per-device register-group
    (absolute address in the AVR ``data`` address space).  The instance's
    ``registers`` tuple carries the module's register catalog with
    offsets retained unmodified — consumers of the IR treat those as the
    register's offset relative to the peripheral base.
    """
    catalog = _parse_module_register_catalog(atdf_path)
    root = ET.parse(atdf_path).getroot()
    devices_node = root.find("devices")
    if devices_node is None:
        return ()
    device_node = devices_node.find("device")
    if device_node is None:
        return ()
    peripherals_node = device_node.find("peripherals")
    if peripherals_node is None:
        return ()

    results: list[RawPeripheral] = []
    for module_node in peripherals_node.findall("module"):
        module_name = module_node.get("name") or ""
        module_registers = catalog.get(module_name, ())
        for instance_node in module_node.findall("instance"):
            instance_name = instance_node.get("name")
            register_group = instance_node.find("register-group")
            if instance_name is None or register_group is None:
                continue
            offset_text = register_group.get("offset")
            if offset_text is None:
                continue
            try:
                base = int(offset_text, 0)
            except ValueError:
                continue
            results.append(
                RawPeripheral(
                    name=_canonical_peripheral_name(instance_name),
                    base_address=base,
                    registers=module_registers,
                )
            )
    return tuple(results)


def _encode_af_number(function_name: str) -> int | None:
    if function_name == "default":
        return None
    if ALT_FUNCTION_PATTERN.match(function_name):
        return ord(function_name) - ord("A")
    match = ALT_FUNCTION_EXT_PATTERN.match(function_name)
    if match is not None:
        return 100 + int(match.group("index"))
    return None


def _signal_suffix(group: str, index: str | None) -> str:
    return f"{group}{index}" if index is not None else group


def _position_sort_key(position: str) -> tuple[tuple[int, ...], int, str]:
    match = POSITION_PATTERN.match(position)
    if match is None:
        return ((), 0, position)
    row = tuple(ord(char) - ord("A") for char in match.group("row"))
    column = int(match.group("column"))
    return (row, column, position)


def _microchip_pad_kind(pad: str) -> str:
    upper_pad = pad.upper()
    if upper_pad == "NC" or upper_pad.startswith("NC"):
        return "nc"
    if GPIO_PAD_PATTERN.match(upper_pad):
        return "io"
    if upper_pad.startswith(("VDD", "VSS", "VBAT", "VREF", "ADVREF", "VBG")):
        return "power"
    if upper_pad.startswith("GND"):
        return "ground"
    if upper_pad in {"NRST", "RESET"}:
        return "reset"
    if "JTAG" in upper_pad or upper_pad in {"TDI", "TDO", "TCK", "TMS"}:
        return "debug"
    if "BOOT" in upper_pad:
        return "boot"
    return "signal"


def parse_raw_pin_data_document(*, atdf_path: Path, package_name: str) -> RawPinDataDocument:
    """Parse GPIO-capable pin and alternate-function data from a Microchip ATDF."""
    root = ET.parse(atdf_path).getroot()
    variants_node = root.find("variants")
    if variants_node is None:
        raise StageExecutionError(f"ATDF does not declare variants: {atdf_path}")

    package_key = package_name.upper()
    selected_variant = next(
        (
            variant
            for variant in variants_node.findall("variant")
            if variant.get("package") == package_key
        ),
        None,
    )
    if selected_variant is None:
        raise StageExecutionError(f"ATDF {atdf_path.name} does not declare package {package_key}.")
    selected_pinout = selected_variant.get("pinout")
    if selected_pinout is None:
        raise StageExecutionError(f"ATDF variant for {package_key} does not declare a pinout name.")

    pinouts_node = root.find("pinouts")
    if pinouts_node is None:
        raise StageExecutionError(f"ATDF does not declare pinouts: {atdf_path}")

    pinout_node = next(
        (
            pinout
            for pinout in pinouts_node.findall("pinout")
            if pinout.get("name") == selected_pinout
        ),
        None,
    )
    if pinout_node is None:
        raise StageExecutionError(
            f"ATDF {atdf_path.name} does not define pinout {selected_pinout}."
        )

    signals_by_pad: dict[str, dict[tuple[str, int], RawPinAlternateFunction]] = {}
    devices_node = root.find("devices")
    if devices_node is None:
        raise StageExecutionError(f"ATDF does not declare devices: {atdf_path}")
    device_node = devices_node.find("device")
    if device_node is None:
        raise StageExecutionError(f"ATDF does not declare a device entry: {atdf_path}")
    peripherals_node = device_node.find("peripherals")
    if peripherals_node is None:
        raise StageExecutionError(f"ATDF does not declare peripherals: {atdf_path}")

    for module_node in peripherals_node.findall("module"):
        for instance_node in module_node.findall("instance"):
            instance_name = instance_node.get("name")
            if instance_name is None:
                continue
            canonical_instance = _canonical_peripheral_name(instance_name)
            signals_node = instance_node.find("signals")
            if signals_node is None:
                continue
            for signal_node in signals_node.findall("signal"):
                pad = signal_node.get("pad")
                function = signal_node.get("function")
                group = signal_node.get("group")
                if pad is None or function is None or group is None:
                    continue
                if canonical_instance.startswith("GPIO") and function == "default":
                    continue
                af_number = _encode_af_number(function)
                if af_number is None:
                    continue
                suffix = _signal_suffix(group, signal_node.get("index"))
                signal_name = f"{canonical_instance}_{suffix}"
                bucket = signals_by_pad.setdefault(pad, {})
                key = (signal_name, af_number)
                bucket.setdefault(
                    key,
                    RawPinAlternateFunction(signal_name=signal_name, af_number=af_number),
                )

    pins_by_position: dict[str, RawPinDocumentEntry] = {}
    package_pads: list[RawPackagePadEntry] = []
    for pin_node in pinout_node.findall("pin"):
        position = pin_node.get("position")
        pad = pin_node.get("pad")
        if position is None or pad is None:
            continue
        match = GPIO_PAD_PATTERN.match(pad)
        package_pads.append(
            RawPackagePadEntry(
                pad_id=position,
                position_label=position,
                physical_index=int(position) if position.isdigit() else None,
                pad_kind=_microchip_pad_kind(pad),
                bonded_pin=None if match is None else pad,
                bonding_state=(
                    "bonded"
                    if match is not None
                    else ("unbonded" if _microchip_pad_kind(pad) == "nc" else "dedicated")
                ),
            )
        )
        match = GPIO_PAD_PATTERN.match(pad)
        if match is None:
            continue
        signals = tuple(
            sorted(
                signals_by_pad.get(pad, {}).values(),
                key=lambda entry: (entry.af_number, entry.signal_name),
            )
        )
        pins_by_position[position] = RawPinDocumentEntry(
            name=pad,
            port=match.group("port"),
            number=int(match.group("number")),
            signals=signals,
        )

    return RawPinDataDocument(
        device_name=(device_node.get("name") or atdf_path.stem).lower(),
        package_name=package_name.lower(),
        package_pin_count=len(list(pinout_node.findall("pin"))),
        pins=tuple(
            pins_by_position[position]
            for position in sorted(pins_by_position, key=_position_sort_key)
        ),
        package_pads=tuple(
            sorted(
                package_pads,
                key=lambda item: (
                    item.physical_index is None,
                    -1 if item.physical_index is None else item.physical_index,
                    _position_sort_key(item.position_label),
                    item.pad_id,
                ),
            )
        ),
        gpio_modes_file=selected_pinout,
    )


def parse_dma_request_patches(atdf_path: Path) -> tuple[DmaRequestPatch, ...]:
    """Parse DMA request routing metadata from ATDF instance parameters."""
    root = ET.parse(atdf_path).getroot()
    devices_node = root.find("devices")
    if devices_node is None:
        return ()
    device_node = devices_node.find("device")
    if device_node is None:
        return ()
    peripherals_node = device_node.find("peripherals")
    if peripherals_node is None:
        return ()

    requests: dict[tuple[str, str], DmaRequestPatch] = {}
    for module_node in peripherals_node.findall("module"):
        for instance_node in module_node.findall("instance"):
            instance_name = instance_node.get("name")
            if instance_name is None:
                continue
            canonical_instance = _canonical_peripheral_name(instance_name)
            parameters = _parameter_map(instance_node)
            for parameter_name, value in parameters.items():
                match = DMA_PARAMETER_PATTERN.match(parameter_name)
                if match is None:
                    continue
                request = DmaRequestPatch(
                    controller="XDMAC",
                    request_line=f"PERID_{value}",
                    peripheral=canonical_instance,
                    signal=match.group("signal"),
                    request_value=int(value),
                )
                requests.setdefault((request.controller, request.request_line), request)
    return tuple(
        sorted(
            requests.values(),
            key=lambda request: (request.controller, request.request_line),
        )
    )


def merge_source_patch(
    patch: DevicePatch,
    *,
    selected: SelectedDeviceFiles,
    source_memories: tuple[MemoryPatch, ...],
    source_peripherals: tuple[PeripheralPatch, ...],
    source_dma_requests: tuple[DmaRequestPatch, ...],
    pin_count: int,
) -> DevicePatch:
    """Merge source-derived metadata into the lightweight device patch contract."""
    merged_peripherals = {peripheral.name: peripheral for peripheral in source_peripherals}
    merged_peripherals.update({peripheral.name: peripheral for peripheral in patch.peripherals})
    merged_dma_requests = {
        (request.controller, request.request_line): request for request in source_dma_requests
    }
    merged_dma_requests.update(
        {(request.controller, request.request_line): request for request in patch.dma_requests}
    )
    svd_file_relative = (
        None
        if selected.svd_path is None
        else str(selected.svd_path.relative_to(selected.pdsc_path.parent)).replace("\\", "/")
    )
    return DevicePatch(
        patch_id=patch.patch_id,
        family_patch_id=patch.family_patch_id,
        device=patch.device,
        svd_file=svd_file_relative,
        pin_data_file=str(selected.atdf_path.relative_to(selected.pdsc_path.parent)).replace(
            "\\", "/"
        ),
        package=patch.package,
        pin_count=pin_count,
        core=patch.core,
        summary=patch.summary,
        memories=source_memories if patch.memories == () else patch.memories,
        peripherals=tuple(
            sorted(merged_peripherals.values(), key=lambda peripheral: peripheral.name)
        ),
        registers=patch.registers,
        register_fields=patch.register_fields,
        pins=patch.pins,
        clock_nodes=patch.clock_nodes,
        clock_selectors=patch.clock_selectors,
        clock_gates=patch.clock_gates,
        resets=patch.resets,
        interrupts=patch.interrupts,
        system_clock_profiles=patch.system_clock_profiles,
        peripheral_clock_bindings=patch.peripheral_clock_bindings,
        dma_controllers=patch.dma_controllers,
        dma_requests=tuple(
            sorted(
                merged_dma_requests.values(),
                key=lambda request: (request.controller, request.request_line),
            )
        ),
    )
