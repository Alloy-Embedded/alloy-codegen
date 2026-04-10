"""NXP MCUXpresso source adapters for imxrt1060 bootstrap support."""

from __future__ import annotations

import hashlib
import re
import subprocess
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.scope import PipelineScope

SVD_SOURCE_ID = "nxp-mcux-soc-svd"
SDK_SOURCE_ID = "nxp-mcux-sdk"

SVD_REMOTE = "https://github.com/nxp-mcuxpresso/mcux-soc-svd.git"
SDK_REMOTE = "https://github.com/nxp-mcuxpresso/mcux-sdk.git"
# Sparse-checkout paths sufficient for all imxrt1060 devices.
SVD_SPARSE_PATHS = ["MIMXRT1062", "MIMXRT1064"]
SDK_SPARSE_PATHS = ["devices/MIMXRT1062/drivers", "devices/MIMXRT1064/drivers"]

# Canonical (lower-case Alloy) device name → upstream NXP name.
DEVICE_UPSTREAM_NAMES: dict[str, str] = {
    "mimxrt1062": "MIMXRT1062",
    "mimxrt1064": "MIMXRT1064",
}

# Macro value token: hex address or decimal zero, optional U suffix.
_VALUE_TOKEN = r"(?:0x[0-9A-Fa-f]+|[0-9]+)U?"

# IOMUXC #define lines:
#   #define IOMUXC_<MACRO>   <muxReg>, <muxMode>, <inputReg>, <inputDaisy>, <cfgReg>
IOMUXC_DEFINE_PATTERN = re.compile(
    r"#define\s+IOMUXC_([A-Z0-9_]+)\s+"
    + rf"({_VALUE_TOKEN}),\s*"
    + rf"({_VALUE_TOKEN}),\s*"
    + rf"({_VALUE_TOKEN}),\s*"
    + rf"({_VALUE_TOKEN}),\s*"
    + rf"({_VALUE_TOKEN})"
)
IOMUXC_PAD_COMMENT_PATTERN = re.compile(r"/\*\s*(GPIO_[A-Z0-9_]+)\s*,\s*pad number\s*(\d+)\s*\*/")

# Known pad group prefixes for i.MX RT 1060 series.
# Format: IOMUXC_<PAD_NAME>_<SIGNAL_NAME>
# PAD_NAME examples: GPIO_EMC_00, GPIO_AD_B0_15, GPIO_B0_04, GPIO_SD_B1_10
NXP_PAD_PATTERN = re.compile(r"^(GPIO_(?:EMC|AD_B[01]|B[01]|SD_B[01])_\d{2})_(.+)$")

# Extract the trailing numeric index from a pad name.
PAD_NUMBER_PATTERN = re.compile(r"_(\d+)$")


@dataclass(frozen=True, slots=True)
class NxpIomuxcEntry:
    """One parsed IOMUXC mux option from an NXP SDK fsl_iomuxc.h header."""

    pad_name: str  # e.g. "GPIO_EMC_00"
    signal_name: str  # e.g. "LPSPI1_SCK"
    mux_mode: int  # 0–7, maps to AF number in canonical IR
    pad_number: int | None = None


def _upstream_name(device_name: str) -> str:
    name = DEVICE_UPSTREAM_NAMES.get(device_name.lower())
    if name is None:
        raise StageExecutionError(
            f"Unknown NXP device '{device_name}'. "
            f"Supported: {', '.join(sorted(DEVICE_UPSTREAM_NAMES))}."
        )
    return name


def _hash_tree(root: Path) -> str:
    digest = hashlib.sha256()
    for path in sorted(root.rglob("*")):
        if not path.is_file():
            continue
        digest.update(str(path.relative_to(root)).encode("utf-8"))
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


def _clone_sparse(remote: str, dest: Path, sparse_paths: list[str]) -> None:
    """Clone a remote repository with a sparse checkout of the given paths."""
    dest.parent.mkdir(parents=True, exist_ok=True)
    clone_cmd = [
        "git",
        "clone",
        "--depth",
        "1",
        "--filter=blob:none",
        "--sparse",
        remote,
        str(dest),
    ]
    sparse_cmd = ["git", "-C", str(dest), "sparse-checkout", "set"] + sparse_paths
    for command in (clone_cmd, sparse_cmd):
        completed = subprocess.run(command, capture_output=True, text=True)
        if completed.returncode != 0:
            raise StageExecutionError(
                f"Failed to prepare source with command {' '.join(command)}: "
                f"{completed.stderr.strip()}"
            )


def ensure_svd_root(context: ExecutionContext, *, vendor: str, family: str) -> Path:
    """Resolve the nxp-mcux-soc-svd root directory, cloning if needed."""
    configured = context.source_root_for(SVD_SOURCE_ID)
    if configured is not None:
        if not configured.exists():
            raise StageExecutionError(
                f"Configured {SVD_SOURCE_ID} override does not exist: {configured}"
            )
        return configured

    source_root = context.source_cache_dir / "nxp-mcux-soc-svd"
    if (source_root / SVD_SPARSE_PATHS[0]).exists():
        return source_root

    _clone_sparse(SVD_REMOTE, source_root, SVD_SPARSE_PATHS)
    return source_root


def ensure_sdk_root(context: ExecutionContext, *, vendor: str, family: str) -> Path:
    """Resolve the nxp-mcux-sdk root directory, cloning if needed."""
    configured = context.source_root_for(SDK_SOURCE_ID)
    if configured is not None:
        if not configured.exists():
            raise StageExecutionError(
                f"Configured {SDK_SOURCE_ID} override does not exist: {configured}"
            )
        return configured

    source_root = context.source_cache_dir / "nxp-mcux-sdk"
    if (source_root / "devices" / "MIMXRT1062").exists():
        return source_root

    _clone_sparse(SDK_REMOTE, source_root, SDK_SPARSE_PATHS)
    return source_root


def resolve_svd_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the SVD file path for one NXP device."""
    svd_root = ensure_svd_root(context, vendor=vendor, family=family)
    upstream = _upstream_name(device_name)
    candidate = svd_root / upstream / f"{upstream}.xml"
    if not candidate.exists():
        raise StageExecutionError(f"NXP SVD file not found for '{device_name}': {candidate}")
    return candidate


def resolve_iomuxc_header_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the fsl_iomuxc.h path for one NXP device in the SDK tree."""
    sdk_root = ensure_sdk_root(context, vendor=vendor, family=family)
    upstream = _upstream_name(device_name)
    candidate = sdk_root / "devices" / upstream / "drivers" / "fsl_iomuxc.h"
    if not candidate.exists():
        raise StageExecutionError(
            f"NXP SDK IOMUX header not found for '{device_name}': {candidate}"
        )
    return candidate


def fetch_records(context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    """Resolve upstream NXP MCUXpresso source records for the requested scope."""
    validated_scope = scope.validate_supported()
    vendor = validated_scope.resolved_vendor()
    family = validated_scope.resolved_family()
    svd_root = ensure_svd_root(context, vendor=vendor, family=family)
    sdk_root = ensure_sdk_root(context, vendor=vendor, family=family)
    svd_revision = _hash_tree(svd_root)
    sdk_revision = _hash_tree(sdk_root)

    records: list[dict[str, str]] = []
    for device_name in validated_scope.resolved_device_names():
        upstream = _upstream_name(device_name)
        svd_path = resolve_svd_path(context, device_name, vendor=vendor, family=family)
        iomuxc_path = resolve_iomuxc_header_path(context, device_name, vendor=vendor, family=family)
        records.append(
            {
                "source_id": SVD_SOURCE_ID,
                "target_device": device_name,
                "origin_url": "https://github.com/nxp-mcuxpresso/mcux-soc-svd",
                "revision": svd_revision,
                "local_path": str(svd_path),
                "upstream_path": f"{upstream}/{upstream}.xml",
            }
        )
        records.append(
            {
                "source_id": SDK_SOURCE_ID,
                "target_device": device_name,
                "origin_url": "https://github.com/nxp-mcuxpresso/mcux-sdk",
                "revision": sdk_revision,
                "local_path": str(iomuxc_path),
                "upstream_path": f"devices/{upstream}/drivers/fsl_iomuxc.h",
            }
        )
    return tuple(records)


def _parse_int_value(raw: str) -> int:
    """Parse a C integer literal (hex or decimal, optional U suffix)."""
    stripped = raw.rstrip("U").rstrip("u")
    if stripped.startswith("0x") or stripped.startswith("0X"):
        return int(stripped, 16)
    return int(stripped, 10)


def parse_iomuxc_entries(header_path: Path) -> tuple[NxpIomuxcEntry, ...]:
    """Parse fsl_iomuxc.h macros into structured NxpIomuxcEntry tuples."""
    content = header_path.read_text(encoding="utf-8")
    pad_numbers: dict[str, int] = {}
    for line in content.splitlines():
        comment_match = IOMUXC_PAD_COMMENT_PATTERN.search(line)
        if comment_match is None:
            continue
        pad_numbers.setdefault(comment_match.group(1), int(comment_match.group(2)))

    entries: list[NxpIomuxcEntry] = []
    for match in IOMUXC_DEFINE_PATTERN.finditer(content):
        macro_name = match.group(1)
        mux_mode_raw = match.group(3)  # group(1)=name, (2)=muxReg, (3)=muxMode
        pad_match = NXP_PAD_PATTERN.match(macro_name)
        if pad_match is None:
            continue
        pad_name = pad_match.group(1)
        signal_name = pad_match.group(2)
        mux_mode = _parse_int_value(mux_mode_raw)
        entries.append(
            NxpIomuxcEntry(
                pad_name=pad_name,
                signal_name=signal_name,
                mux_mode=mux_mode,
                pad_number=pad_numbers.get(pad_name),
            )
        )
    return tuple(entries)
