"""esp-idf / espressif-svd source adapter for the Espressif ESP32 bootstrap path.

Espressif publishes official CMSIS-SVD files for their SoCs in the dedicated
``espressif/svd`` GitHub repository.  This adapter performs a sparse git clone
of that repository (or accepts a pre-cloned local root via the
``ALLOY_CODEGEN_SOURCE_ESPRESSIF_SVD_ROOT`` environment variable / ``espressif-svd``
source override) and parses the SVD using the standard CMSIS-SVD parser.

Supplementary routing data (``gpio_sig_map.h``) is tracked as a separately
versioned supplementary source.  In this initial bootstrap phase the supplementary
source is registered in the fetch manifest so provenance is explicit, but full IO
Matrix pin signal parsing is deferred to Phase 2.

License note: ``espressif/svd`` and esp-idf are released under the Apache-2.0
licence.  Provenance (git revision) is recorded in the source manifest per fetch.
"""

from __future__ import annotations

import hashlib
import re
import subprocess
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.patches import load_device_patch
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import parse_raw_device_document  # noqa: F401
from alloy_codegen.sources.raw import RawDeviceDocument

ESPRESSIF_SVD_REMOTE = "https://github.com/espressif/svd.git"
SOURCE_ID = "espressif-svd"

# Supplementary-source ID for esp-idf `gpio_sig_map.h` ingestion (Phase 2.2).
GPIO_SIG_MAP_SOURCE_ID = "esp-idf-gpio-sig-map"

# Matches lines like ``#define U0RXD_IN_IDX           6`` in esp-idf's
# ``components/soc/esp32c3/include/soc/gpio_sig_map.h``.  The trailing
# ``_IDX`` suffix is stripped in the returned mapping so callers can look
# up signals by their canonical IO Matrix name (e.g. ``U0RXD_IN``).
_GPIO_SIG_MAP_PATTERN = re.compile(
    r"^\s*#define\s+(?P<name>[A-Z0-9_]+)_IDX\s+(?P<index>\d+)\b"
)


# ---------------------------------------------------------------------------
# Source root management
# ---------------------------------------------------------------------------


def ensure_source_root(context: ExecutionContext) -> Path:
    """Resolve a usable espressif-svd root, cloning sparsely if needed."""
    configured_root = context.source_root_for(SOURCE_ID)
    if configured_root is not None:
        if not configured_root.exists():
            raise StageExecutionError(
                f"Configured espressif-svd source root does not exist: {configured_root}"
            )
        return configured_root

    source_root = context.source_cache_dir / "espressif-svd"
    svd_subdir = source_root / "svd"
    if svd_subdir.exists() and any(svd_subdir.glob("*.svd")):
        return source_root

    source_root.parent.mkdir(parents=True, exist_ok=True)
    clone_cmd = [
        "git",
        "clone",
        "--depth",
        "1",
        "--filter=blob:none",
        "--no-checkout",
        ESPRESSIF_SVD_REMOTE,
        str(source_root),
    ]
    # In cone mode we list the directories we want checked out.
    # The espressif/svd repo stores all SVD files under svd/.
    sparse_set_cmd = [
        "git",
        "-C",
        str(source_root),
        "sparse-checkout",
        "set",
        "--cone",
        "svd",
    ]
    checkout_cmd = [
        "git",
        "-C",
        str(source_root),
        "checkout",
    ]

    for command in (clone_cmd, sparse_set_cmd, checkout_cmd):
        completed = subprocess.run(command, capture_output=True, text=True)
        if completed.returncode != 0:
            raise StageExecutionError(
                f"Failed to prepare espressif-svd source root with command "
                f"{' '.join(command)}: {completed.stderr.strip()}"
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

    # Fallback: content hash of the SVD files (under svd/ or root).
    digest = hashlib.sha256()
    svd_subdir = source_root / "svd"
    search_root = svd_subdir if svd_subdir.exists() else source_root
    for path in sorted(search_root.glob("*.svd")):
        digest.update(str(path.name).encode("utf-8"))
        digest.update(path.read_bytes())
    return f"content-sha256:{digest.hexdigest()}"


# ---------------------------------------------------------------------------
# Path resolution
# ---------------------------------------------------------------------------


def resolve_svd_path(
    context: ExecutionContext,
    device_name: str,
    *,
    vendor: str,
    family: str,
) -> Path:
    """Resolve the SVD path for one Espressif device."""
    patch = load_device_patch(context, device_name, vendor=vendor, family=family)
    source_root = ensure_source_root(context)
    svd_file = patch.svd_file
    if svd_file is None:
        raise StageExecutionError(
            f"Device patch for '{device_name}' does not declare a svd_file."
        )
    # SVD files live under svd/ in the espressif/svd repository.
    svd_subdir = source_root / "svd"
    svd_path = svd_subdir / svd_file
    if not svd_path.exists():
        # Case-insensitive fallback for case-sensitive filesystems.
        svd_lower = svd_file.lower()
        search_dirs = [svd_subdir, source_root]
        for search_dir in search_dirs:
            if not search_dir.exists():
                continue
            for candidate in search_dir.iterdir():
                if candidate.name.lower() == svd_lower:
                    svd_path = candidate
                    break
            else:
                continue
            break
        else:
            raise StageExecutionError(
                f"Missing SVD file '{svd_file}' for device '{device_name}' "
                f"in espressif-svd root '{source_root}'."
            )
    return svd_path


# ---------------------------------------------------------------------------
# fetch_records — public entry point called by stages/fetch.py
# ---------------------------------------------------------------------------


def fetch_records(
    context: ExecutionContext, scope: PipelineScope
) -> tuple[dict[str, str], ...]:
    """Resolve upstream espressif-svd records for the requested scope."""
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
                "origin_url": ESPRESSIF_SVD_REMOTE,
                "revision": revision,
                "local_path": str(local_path),
                "upstream_path": patch.svd_file or "",
            }
        )
    return tuple(records)


# ---------------------------------------------------------------------------
# parse_esp32c3_document — convenience helper for tests
# ---------------------------------------------------------------------------


def parse_esp32_document(svd_path: Path) -> RawDeviceDocument:
    """Parse an Espressif SVD using the standard CMSIS-SVD parser."""
    return parse_raw_device_document(svd_path)


# ---------------------------------------------------------------------------
# parse_gpio_sig_map — esp-idf IO Matrix supplementary-source parser (Phase 2.2)
# ---------------------------------------------------------------------------


def parse_gpio_sig_map(header_path: Path) -> dict[str, int]:
    """Parse esp-idf ``gpio_sig_map.h`` into a ``{signal_name: index}`` mapping.

    The ESP32 IO Matrix routes any peripheral signal to any GPIO pin by
    writing a numeric signal index into a GPIO pin-mux register.  esp-idf
    publishes the canonical index assignments in
    ``components/soc/<chip>/include/soc/gpio_sig_map.h`` as a series of
    ``#define <NAME>_IDX <number>`` macros.

    This parser extracts those indices so downstream code can reconcile the
    ``af_number`` field on Espressif pin signals against the upstream
    source-of-truth, providing the supplementary-source provenance required
    by the add-espressif-esp32-target spec.

    Lines that do not match the ``#define <NAME>_IDX <number>`` pattern are
    silently skipped.  The ``_IDX`` suffix is stripped in the returned
    mapping — use ``U0RXD_IN`` (not ``U0RXD_IN_IDX``) as the lookup key.

    Example::

        >>> mapping = parse_gpio_sig_map(Path("gpio_sig_map.h"))
        >>> mapping["U0RXD_IN"]
        6
        >>> mapping["FSPICLK_OUT"]
        63
    """
    if not header_path.exists():
        raise StageExecutionError(f"gpio_sig_map.h not found: {header_path}")
    mapping: dict[str, int] = {}
    content = header_path.read_text(encoding="utf-8")
    for line in content.splitlines():
        match = _GPIO_SIG_MAP_PATTERN.match(line)
        if match is None:
            continue
        name = match.group("name")
        index = int(match.group("index"))
        # If the same name appears twice with different values the later one wins
        # (matches C preprocessor semantics).  In practice every entry is unique.
        mapping[name] = index
    return mapping
