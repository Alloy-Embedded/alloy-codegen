"""Auto-generated README for the alloy-devices publication root.

Renders a markdown table of every admitted ``(vendor, family)`` pair plus the
devices, packages, and peripherals each one carries.  The emitter is a pure
function over ``DEVICE_REGISTRY`` and the family.json / device.json patches —
every parallel publish job produces byte-identical output, so the workflow's
publication-diff step trivially detects when the README really changed.

See ``add-publication-scale-features`` for the spec deltas (artifact-contract
gains the requirement that publication root carries this artifact).
"""

from __future__ import annotations

import hashlib
from dataclasses import dataclass

from alloy_codegen.bootstrap import DEVICE_REGISTRY
from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.patches import (
    DevicePatch,
    FamilyPatchCatalog,
    load_device_patch,
    load_family_patch_catalog,
)
from alloy_codegen.reporting import EmittedArtifact

# CMSIS / Cortex standard cores that ship in every ARM SVD.  Filtered out of the
# README peripheral list when we fall back to the canonical IR — these aren't
# user-facing peripherals, just the standard core debug/control blocks.
_CMSIS_STANDARD_PERIPHERALS: frozenset[str] = frozenset(
    {
        "CoreDebug",
        "DWT",
        "ETM",
        "FPB",
        "FPU",
        "ITM",
        "MPU",
        "NVIC",
        "SCB",
        "SCnSCB",
        "SysTick",
        "TPIU",
    }
)

README_PATH = "README.md"
README_ARTIFACT_KIND = "documentation"


# ---------------------------------------------------------------------------
# Internal data structures
# ---------------------------------------------------------------------------


@dataclass(frozen=True, slots=True)
class _FamilyRow:
    vendor: str
    family: str
    isa: str
    devices: tuple[str, ...]
    packages: tuple[str, ...]
    peripherals: tuple[str, ...]
    caveat: str | None


# ---------------------------------------------------------------------------
# ISA labels
# ---------------------------------------------------------------------------


# Friendly labels for `core` strings declared in device patches.  Multi-core
# nuance (single-core perspective vs dual-core) is added at render time.
_ISA_LABELS: dict[str, str] = {
    "cortex-m0plus": "Cortex-M0+",
    "cortex-m0plus-dual": "Cortex-M0+ (dual)",
    "cortex-m4": "Cortex-M4",
    "cortex-m4f": "Cortex-M4F",
    "cortex-m7": "Cortex-M7",
    "cortex-m7f": "Cortex-M7F",
    "rv32imc": "RISC-V RV32IMC",
    "rv32imac": "RISC-V RV32IMAC",
    "riscv": "RISC-V",
    "xtensa-lx6": "Xtensa LX6 (dual-core)",
    "xtensa-lx7": "Xtensa LX7 (dual-core)",
    "avr8": "AVR8",
}


def _isa_label(core: str) -> str:
    return _ISA_LABELS.get(core.lower(), core)


# ---------------------------------------------------------------------------
# Row construction
# ---------------------------------------------------------------------------


def _peripherals_from_canonical_ir(
    context: ExecutionContext, *, vendor: str, family: str, device: str
) -> tuple[str, ...]:
    """Fallback when family.json's peripheral list is empty.

    Some families (notably ``microchip/same70``) admit peripherals dynamically
    from the upstream SVD via the device-patch normalize path and never curate
    a ``peripherals`` array at the family level.  In that case the README
    would otherwise show ``—`` even though the published IR carries a full
    list.  We run normalize once and read the IR's peripheral set, filtering
    out the CMSIS-standard core blocks (``CoreDebug``, ``FPU``, etc.) that
    aren't user-facing.

    Imports happen lazily inside the function so the README emitter does not
    import the full normalize stack when the catalog already supplies the
    peripheral list (the common path).
    """
    from alloy_codegen.scope import PipelineScope
    from alloy_codegen.stages.normalize import run as run_normalize

    result = run_normalize(PipelineScope(vendor=vendor, family=family, device=device), context)
    if not result.payload.devices:
        return ()
    ir_device = result.payload.devices[0]
    return tuple(
        sorted(
            peripheral.name
            for peripheral in ir_device.peripherals
            if peripheral.name not in _CMSIS_STANDARD_PERIPHERALS
        )
    )


def _row_for_family(
    *,
    context: ExecutionContext,
    vendor: str,
    family: str,
    devices: tuple[str, ...],
) -> _FamilyRow:
    family_catalog: FamilyPatchCatalog = load_family_patch_catalog(
        context, vendor=vendor, family=family
    )
    device_patches: tuple[DevicePatch, ...] = tuple(
        load_device_patch(context, device, vendor=vendor, family=family) for device in devices
    )
    if not device_patches:
        raise StageExecutionError(
            f"DEVICE_REGISTRY lists no devices for {vendor}/{family}; cannot render README row."
        )
    isa = _isa_label(device_patches[0].core)
    packages = tuple(sorted({device.package for device in device_patches}))
    peripherals = tuple(peripheral.name for peripheral in family_catalog.peripherals)
    if not peripherals:
        # Fall back to the canonical IR — the family curates peripherals
        # dynamically from upstream SVD instead of declaring them in
        # family.json (e.g., microchip/same70).  The README is best-effort
        # documentation: if the lazy normalize fails (e.g., scoped test
        # fixtures don't have the source for OTHER families), degrade to
        # an empty list and keep the rest of the README intact.
        try:
            peripherals = _peripherals_from_canonical_ir(
                context, vendor=vendor, family=family, device=devices[0]
            )
        except StageExecutionError:
            peripherals = ()
    return _FamilyRow(
        vendor=vendor,
        family=family,
        isa=isa,
        devices=devices,
        packages=packages,
        peripherals=peripherals,
        caveat=family_catalog.readme_caveat,
    )


# ---------------------------------------------------------------------------
# Markdown rendering
# ---------------------------------------------------------------------------


def _render_header(alloy_codegen_revision: str | None) -> tuple[str, ...]:
    revision_text = alloy_codegen_revision or "(revision unknown)"
    return (
        "# alloy-devices",
        "",
        f"> Auto-generated by alloy-codegen `{revision_text}`. Do not edit manually — every"
        " publish run regenerates this file from `DEVICE_REGISTRY` and family patches.",
        "",
    )


def _render_table(rows: tuple[_FamilyRow, ...]) -> tuple[str, ...]:
    lines: list[str] = [
        "## Admitted families",
        "",
        "| Vendor | Family | ISA | Devices | Packages | Peripherals |",
        "|---|---|---|---|---|---|",
    ]
    for row in rows:
        lines.append(
            "| {vendor} | {family} | {isa} | {devices} | {packages} | {peripherals} |".format(
                vendor=row.vendor,
                family=row.family,
                isa=row.isa,
                devices=", ".join(row.devices),
                packages=", ".join(row.packages),
                peripherals=", ".join(row.peripherals) if row.peripherals else "—",
            )
        )
    lines.append("")
    return tuple(lines)


def _render_caveats(rows: tuple[_FamilyRow, ...]) -> tuple[str, ...]:
    caveat_rows = tuple(row for row in rows if row.caveat is not None)
    if not caveat_rows:
        return ()
    lines: list[str] = ["## Coverage caveats", ""]
    for row in caveat_rows:
        lines.append(f"- **{row.vendor}/{row.family}**: {row.caveat}")
    lines.append("")
    return tuple(lines)


def _render_markdown(rows: tuple[_FamilyRow, ...], *, alloy_codegen_revision: str | None) -> str:
    lines: list[str] = []
    lines.extend(_render_header(alloy_codegen_revision))
    lines.extend(_render_table(rows))
    lines.extend(_render_caveats(rows))
    # Ensure trailing newline.
    if not lines or lines[-1] != "":
        lines.append("")
    return "\n".join(lines)


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------


def render_devices_readme(
    context: ExecutionContext,
    *,
    alloy_codegen_revision: str | None = None,
) -> str:
    """Render the alloy-devices README markdown for the current admitted set."""
    rows = tuple(
        _row_for_family(context=context, vendor=vendor, family=family, devices=devices)
        for (vendor, family), devices in sorted(DEVICE_REGISTRY.items())
    )
    return _render_markdown(rows, alloy_codegen_revision=alloy_codegen_revision)


def emit_devices_readme(
    context: ExecutionContext,
    *,
    alloy_codegen_revision: str | None = None,
) -> EmittedArtifact:
    """Emit the alloy-devices root README artifact.

    The emitter is deterministic: identical inputs produce byte-identical
    output across parallel publish jobs.  ``alloy_codegen_revision`` is
    informational only — it appears in the auto-generated header but does
    NOT influence the table content (so README regeneration on a no-op
    revision bump still no-ops the publish-diff check).
    """
    content = render_devices_readme(context, alloy_codegen_revision=alloy_codegen_revision)
    return EmittedArtifact(
        path=README_PATH,
        artifact_kind=README_ARTIFACT_KIND,
        content=content,
        content_sha256=hashlib.sha256(content.encode("utf-8")).hexdigest(),
        content_bytes=len(content.encode("utf-8")),
    )
