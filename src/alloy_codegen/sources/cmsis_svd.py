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
from alloy_codegen.sources.raw import RawDeviceDocument, RawInterrupt, RawPeripheral

CMSIS_SVD_REMOTE = "https://github.com/cmsis-svd/cmsis-svd-data.git"
STMICRO_SUBTREE = "data/STMicro"


def ensure_source_root(context: ExecutionContext) -> Path:
    """Resolve a usable cmsis-svd-data root, cloning if needed."""
    if context.source_root is not None:
        if not (context.source_root / STMICRO_SUBTREE).exists():
            raise StageExecutionError(
                "Configured source root does not contain "
                f"'{STMICRO_SUBTREE}': {context.source_root}"
            )
        return context.source_root

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
        ["git", "-C", str(source_root), "rev-parse", "HEAD"],
        capture_output=True,
        text=True,
    )
    if completed.returncode == 0:
        return completed.stdout.strip()

    digest = hashlib.sha256()
    subtree = source_root / STMICRO_SUBTREE
    for path in sorted(subtree.rglob("*")):
        if not path.is_file():
            continue
        digest.update(str(path.relative_to(source_root)).encode("utf-8"))
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


def resolve_svd_path(context: ExecutionContext, device_name: str) -> Path:
    """Resolve the SVD path for one bootstrap device."""
    patch = load_device_patch(context, device_name)
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
    for device_name in validated_scope.resolved_device_names():
        patch = load_device_patch(context, device_name)
        local_path = resolve_svd_path(context, device_name)
        records.append(
            {
                "source_id": "cmsis-svd-data",
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
        for peripheral in peripheral_nodes.findall("peripheral"):
            name = peripheral.findtext("name")
            base_address = peripheral.findtext("baseAddress")
            if name and base_address:
                peripherals.append(
                    RawPeripheral(
                        name=name,
                        base_address=int(base_address, 16),
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
