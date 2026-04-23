"""cmsis-svd-data source adapter for the bootstrap STM32G0 path."""

from __future__ import annotations

import hashlib
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.patches import load_device_patch
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.raw import (
    RawDeviceDocument,
    RawInterrupt,
    RawPeripheral,
    RawRegister,
    RawRegisterField,
)

CMSIS_SVD_REMOTE = "https://github.com/cmsis-svd/cmsis-svd-data.git"
STMICRO_SUBTREE = "data/STMicro"


def ensure_source_root(context: ExecutionContext) -> Path:
    """Resolve a usable cmsis-svd-data root, cloning if needed."""
    configured_root = context.source_root_for("cmsis-svd-data")
    if configured_root is not None:
        if not (configured_root / STMICRO_SUBTREE).exists():
            raise StageExecutionError(
                f"Configured source root does not contain '{STMICRO_SUBTREE}': {configured_root}"
            )
        return configured_root

    source_root = context.source_cache_dir / "cmsis-svd-data"
    if (source_root / STMICRO_SUBTREE).exists():
        return source_root

    source_root.parent.mkdir(parents=True, exist_ok=True)
    clone_cmd = [
        "git",
        "clone",
        "--depth",
        "1",
        "--filter=blob:none",
        "--sparse",
        CMSIS_SVD_REMOTE,
        str(source_root),
    ]
    sparse_cmd = ["git", "-C", str(source_root), "sparse-checkout", "set", STMICRO_SUBTREE]

    for command in (clone_cmd, sparse_cmd):
        completed = subprocess.run(command, capture_output=True, text=True)
        if completed.returncode != 0:
            raise StageExecutionError(
                f"Failed to prepare cmsis-svd-data source root with command {' '.join(command)}: "
                f"{completed.stderr.strip()}"
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
    subtree = source_root / STMICRO_SUBTREE
    for path in sorted(subtree.rglob("*")):
        if not path.is_file():
            continue
        digest.update(str(path.relative_to(source_root)).encode("utf-8"))
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


def resolve_svd_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the SVD path for one device."""
    patch = load_device_patch(context, device_name, vendor=vendor, family=family)
    source_root = ensure_source_root(context)
    svd_path = source_root / STMICRO_SUBTREE / patch.svd_file
    if not svd_path.exists():
        raise StageExecutionError(
            f"Missing SVD file '{patch.svd_file}' for device '{device_name}'."
        )
    return svd_path


def fetch_records(context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    """Resolve upstream SVD records for the requested scope."""
    validated_scope = scope.validate_supported()
    root = ensure_source_root(context)
    revision = source_revision(root)
    records: list[dict[str, str]] = []
    _vendor = validated_scope.resolved_vendor()
    _family = validated_scope.resolved_family()
    for device_name in validated_scope.resolved_device_names():
        patch = load_device_patch(context, device_name, vendor=_vendor, family=_family)
        local_path = resolve_svd_path(context, device_name, vendor=_vendor, family=_family)
        records.append(
            {
                "source_id": "cmsis-svd-data",
                "target_device": device_name,
                "origin_url": CMSIS_SVD_REMOTE,
                "revision": revision,
                "local_path": str(local_path),
                "upstream_path": f"{STMICRO_SUBTREE}/{patch.svd_file}",
            }
        )
    return tuple(records)


def parse_raw_device_document(svd_path: Path) -> RawDeviceDocument:
    """Parse a minimal raw device document from an SVD file."""
    root = ET.parse(svd_path).getroot()
    peripheral_nodes = root.find("peripherals")
    peripherals: list[RawPeripheral] = []
    interrupts: list[RawInterrupt] = []

    if peripheral_nodes is not None:
        peripheral_elements = tuple(peripheral_nodes.findall("peripheral"))
        peripheral_index = {
            name: peripheral
            for peripheral in peripheral_elements
            if (name := peripheral.findtext("name")) is not None
        }
        for peripheral in peripheral_elements:
            name = peripheral.findtext("name")
            base_address = peripheral.findtext("baseAddress")
            if name and base_address:
                registers = _parse_registers(peripheral, peripheral_index)
                peripherals.append(
                    RawPeripheral(
                        name=name,
                        base_address=int(base_address, 16),
                        registers=registers,
                    )
                )
            for interrupt in peripheral.findall("interrupt"):
                interrupt_name = interrupt.findtext("name")
                interrupt_line = interrupt.findtext("value")
                if interrupt_name and interrupt_line:
                    interrupts.append(
                        RawInterrupt(
                            name=interrupt_name,
                            line=int(interrupt_line, 10),
                            peripheral=name,
                        )
                    )

    return RawDeviceDocument(
        device_name=(root.findtext("name") or svd_path.stem).lower(),
        description=root.findtext("description") or "",
        svd_version=root.findtext("version"),
        peripherals=tuple(peripherals),
        interrupts=tuple(interrupts),
    )


def _parse_registers(
    peripheral_node: ET.Element,
    peripheral_index: dict[str, ET.Element],
    *,
    seen: frozenset[str] = frozenset(),
) -> tuple[RawRegister, ...]:
    """Parse top-level register descriptors from one SVD peripheral node."""
    registers_node = peripheral_node.find("registers")
    if registers_node is None:
        derived_from = peripheral_node.get("derivedFrom")
        if derived_from is None:
            return ()
        if derived_from in seen:
            raise StageExecutionError(
                f"Detected circular SVD derivedFrom register chain involving '{derived_from}'."
            )
        base_peripheral = peripheral_index.get(derived_from)
        if base_peripheral is None:
            return ()
        return _parse_registers(base_peripheral, peripheral_index, seen=seen | {derived_from})

    peripheral_default_access = peripheral_node.findtext("access")
    peripheral_default_size = peripheral_node.findtext("size")
    register_nodes = tuple(registers_node.findall("register"))
    register_index = {
        name: register_node
        for register_node in register_nodes
        if (name := register_node.findtext("name")) is not None
    }
    registers: list[RawRegister] = []
    for register_node in register_nodes:
        name = register_node.findtext("name")
        base_register = _resolve_derived_register(register_node, register_index)
        offset_text = register_node.findtext("addressOffset")
        if offset_text is None and base_register is not None:
            offset_text = base_register.findtext("addressOffset")
        if name is None or offset_text is None:
            continue
        access = register_node.findtext("access")
        if access is None and base_register is not None:
            access = base_register.findtext("access")
        if access is None:
            access = peripheral_default_access
        size_text = register_node.findtext("size")
        if size_text is None and base_register is not None:
            size_text = base_register.findtext("size")
        if size_text is None:
            size_text = peripheral_default_size
        registers.append(
            RawRegister(
                name=name,
                offset_bytes=int(offset_text, 0),
                access=access,
                size_bits=None if size_text is None else int(size_text, 0),
                fields=_parse_register_fields(
                    register_node,
                    register_index,
                    default_access=access,
                ),
            )
        )
    return tuple(registers)


def _resolve_derived_register(
    register_node: ET.Element,
    register_index: dict[str, ET.Element],
) -> ET.Element | None:
    derived_from = register_node.get("derivedFrom")
    if derived_from is None:
        return None
    return register_index.get(derived_from)


def _parse_register_fields(
    register_node: ET.Element,
    register_index: dict[str, ET.Element],
    *,
    default_access: str | None,
    seen: frozenset[str] = frozenset(),
) -> tuple[RawRegisterField, ...]:
    fields_node = register_node.find("fields")
    if fields_node is None:
        derived_from = register_node.get("derivedFrom")
        if derived_from is None:
            return ()
        if derived_from in seen:
            raise StageExecutionError(
                f"Detected circular SVD derivedFrom field chain involving '{derived_from}'."
            )
        base_register = register_index.get(derived_from)
        if base_register is None:
            return ()
        return _parse_register_fields(
            base_register,
            register_index,
            default_access=default_access,
            seen=seen | {derived_from},
        )

    fields: list[RawRegisterField] = []
    for field_node in fields_node.findall("field"):
        name = field_node.findtext("name")
        bit_offset_text = field_node.findtext("bitOffset") or field_node.findtext("lsb")
        bit_width_text = field_node.findtext("bitWidth")
        if bit_width_text is None:
            msb_text = field_node.findtext("msb")
            if bit_offset_text is not None and msb_text is not None:
                bit_width_text = str(int(msb_text, 0) - int(bit_offset_text, 0) + 1)
        # SVD bitRange format: "[msb:lsb]" — used by RP2040 and some other vendors.
        if bit_offset_text is None or bit_width_text is None:
            bit_range_text = field_node.findtext("bitRange")
            if bit_range_text is not None:
                bit_range_text = bit_range_text.strip().strip("[]")
                msb_str, lsb_str = bit_range_text.split(":")
                lsb = int(lsb_str.strip(), 0)
                msb = int(msb_str.strip(), 0)
                bit_offset_text = str(lsb)
                bit_width_text = str(msb - lsb + 1)
        if name is None or bit_offset_text is None or bit_width_text is None:
            continue
        fields.append(
            RawRegisterField(
                name=name,
                bit_offset=int(bit_offset_text, 0),
                bit_width=int(bit_width_text, 0),
                access=field_node.findtext("access") or default_access,
            )
        )
    return tuple(fields)
