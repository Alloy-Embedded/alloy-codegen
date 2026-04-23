"""pico-sdk source adapter for the Raspberry Pi RP2040 bootstrap path.

The Raspberry Pi pico-sdk ships the official RP2040 CMSIS-SVD file at
``src/rp2040/hardware_regs/rp2040.svd``.  This adapter performs a sparse git
clone of that subtree (or accepts a pre-cloned local root via the
``ALLOY_CODEGEN_SOURCE_PICO_SDK_ROOT`` environment variable / ``pico-sdk``
source override) and re-uses the standard CMSIS-SVD parser because the file is
a fully conformant SVD document.

License note: pico-sdk is released under the BSD-3-Clause licence.  The SVD
file itself carries the same licence.  Provenance is tracked via the git
revision of the upstream pico-sdk repository.
"""

from __future__ import annotations

import hashlib
import subprocess
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.patches import load_device_patch
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import parse_raw_device_document  # noqa: F401 (re-export)
from alloy_codegen.sources.raw import RawDeviceDocument

PICO_SDK_REMOTE = "https://github.com/raspberrypi/pico-sdk.git"
RP2040_SVD_SUBTREE = "src/rp2040/hardware_regs"
SOURCE_ID = "pico-sdk"


# ---------------------------------------------------------------------------
# Source root management
# ---------------------------------------------------------------------------


def ensure_source_root(context: ExecutionContext) -> Path:
    """Resolve a usable pico-sdk root, cloning sparsely if needed."""
    configured_root = context.source_root_for(SOURCE_ID)
    if configured_root is not None:
        svd_dir = configured_root / RP2040_SVD_SUBTREE
        if not svd_dir.exists():
            raise StageExecutionError(
                f"Configured pico-sdk source root does not contain '{RP2040_SVD_SUBTREE}': "
                f"{configured_root}"
            )
        return configured_root

    source_root = context.source_cache_dir / "pico-sdk"
    if (source_root / RP2040_SVD_SUBTREE).exists():
        return source_root

    source_root.parent.mkdir(parents=True, exist_ok=True)
    clone_cmd = [
        "git",
        "clone",
        "--depth",
        "1",
        "--filter=blob:none",
        "--sparse",
        PICO_SDK_REMOTE,
        str(source_root),
    ]
    sparse_cmd = [
        "git",
        "-C",
        str(source_root),
        "sparse-checkout",
        "set",
        RP2040_SVD_SUBTREE,
    ]

    for command in (clone_cmd, sparse_cmd):
        completed = subprocess.run(command, capture_output=True, text=True)
        if completed.returncode != 0:
            raise StageExecutionError(
                f"Failed to prepare pico-sdk source root with command {' '.join(command)}: "
                f"{completed.stderr.strip()}"
            )

    return source_root


def source_revision(source_root: Path) -> str:
    """Return the current git HEAD SHA or a content-hash fallback."""
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

    # Fallback: content hash of the SVD subtree.
    digest = hashlib.sha256()
    subtree = source_root / RP2040_SVD_SUBTREE
    for path in sorted(subtree.rglob("*")):
        if not path.is_file():
            continue
        digest.update(str(path.relative_to(source_root)).encode("utf-8"))
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


# ---------------------------------------------------------------------------
# Path resolution
# ---------------------------------------------------------------------------


def resolve_svd_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the SVD path for one device."""
    patch = load_device_patch(context, device_name, vendor=vendor, family=family)
    source_root = ensure_source_root(context)
    svd_file = patch.svd_file
    if svd_file is None:
        raise StageExecutionError(f"Device patch for '{device_name}' does not declare a svd_file.")
    svd_dir = source_root / RP2040_SVD_SUBTREE
    svd_path = svd_dir / svd_file
    if not svd_path.exists():
        # The real pico-sdk ships 'RP2040.svd' (uppercase) while device patches
        # canonically reference 'rp2040.svd' (lowercase).  On case-sensitive
        # filesystems (Linux CI) we need a case-insensitive fallback.
        svd_lower = svd_file.lower()
        for candidate in svd_dir.iterdir():
            if candidate.name.lower() == svd_lower:
                svd_path = candidate
                break
        else:
            raise StageExecutionError(
                f"Missing SVD file '{svd_file}' for device '{device_name}' "
                f"under pico-sdk '{RP2040_SVD_SUBTREE}'."
            )
    return svd_path


# ---------------------------------------------------------------------------
# fetch_records — public entry point called by stages/fetch.py
# ---------------------------------------------------------------------------


def fetch_records(context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    """Resolve upstream pico-sdk SVD records for the requested scope."""
    validated_scope = scope.validate_supported()
    root = ensure_source_root(context)
    revision = source_revision(root)
    records: list[dict[str, str]] = []
    _vendor = validated_scope.resolved_vendor()
    _family = validated_scope.resolved_family()
    for device_name in validated_scope.resolved_device_names():
        local_path = resolve_svd_path(context, device_name, vendor=_vendor, family=_family)
        patch = load_device_patch(context, device_name, vendor=_vendor, family=_family)
        records.append(
            {
                "source_id": SOURCE_ID,
                "target_device": device_name,
                "origin_url": PICO_SDK_REMOTE,
                "revision": revision,
                "local_path": str(local_path),
                "upstream_path": f"{RP2040_SVD_SUBTREE}/{patch.svd_file}",
            }
        )
    return tuple(records)


# ---------------------------------------------------------------------------
# parse_raw_device_document — convenience re-export for tests
# ---------------------------------------------------------------------------


def parse_rp2040_document(svd_path: Path) -> RawDeviceDocument:
    """Parse the RP2040 SVD using the standard CMSIS-SVD parser."""
    return parse_raw_device_document(svd_path)
