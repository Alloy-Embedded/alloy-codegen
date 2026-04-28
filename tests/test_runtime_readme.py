"""Regression tests for the auto-generated alloy-devices README.

Covers the requirements introduced by `add-publication-scale-features`:
- every admitted (vendor, family) pair appears in the table
- `__readme_caveat` from family.json bubbles up to the caveats section
- families without `__readme_caveat` are absent from the caveats section
- regeneration is deterministic (byte-equal across calls)
"""

from __future__ import annotations

from alloy_codegen.bootstrap import DEVICE_REGISTRY
from alloy_codegen.context import ExecutionContext
from alloy_codegen.runtime_readme import (
    README_ARTIFACT_KIND,
    README_PATH,
    emit_devices_readme,
    render_devices_readme,
)


def test_devices_readme_lists_every_admitted_family() -> None:
    """Every (vendor, family) in DEVICE_REGISTRY shows up in the markdown table."""
    ctx = ExecutionContext.default()
    content = render_devices_readme(ctx, alloy_codegen_revision="test")
    for vendor, family in DEVICE_REGISTRY:
        # Each row contains the vendor and family in the leading two columns.
        marker = f"| {vendor} | {family} |"
        assert marker in content, f"missing table row for admitted family {vendor}/{family}"


def test_devices_readme_lists_every_device() -> None:
    """Every device name from DEVICE_REGISTRY appears in its family's row."""
    ctx = ExecutionContext.default()
    content = render_devices_readme(ctx, alloy_codegen_revision="test")
    for devices in DEVICE_REGISTRY.values():
        for device in devices:
            assert device in content, f"missing device entry: {device}"


def test_devices_readme_omits_caveats_section() -> None:
    """``consume-alloy-devices-yml-as-canonical-input`` removed the
    family-level ``__readme_caveat`` field — the README no longer
    carries a 'Coverage caveats' section."""
    ctx = ExecutionContext.default()
    content = render_devices_readme(ctx, alloy_codegen_revision="test")
    assert "## Coverage caveats" not in content


def test_devices_readme_emit_is_deterministic() -> None:
    """Two consecutive calls produce byte-identical content (idempotency)."""
    ctx = ExecutionContext.default()
    first = emit_devices_readme(ctx, alloy_codegen_revision="abc1234")
    second = emit_devices_readme(ctx, alloy_codegen_revision="abc1234")
    assert first.content == second.content
    assert first.content_sha256 == second.content_sha256


def test_devices_readme_has_required_metadata() -> None:
    """The artifact is shaped correctly for downstream materialization."""
    ctx = ExecutionContext.default()
    artifact = emit_devices_readme(ctx, alloy_codegen_revision=None)
    assert artifact.path == README_PATH == "README.md"
    assert artifact.artifact_kind == README_ARTIFACT_KIND == "documentation"
    assert artifact.content is not None and artifact.content.startswith("# alloy-devices")
    assert artifact.content_bytes == len(artifact.content.encode("utf-8"))


def test_devices_readme_revision_appears_in_header() -> None:
    """The supplied alloy-codegen revision is rendered into the header."""
    ctx = ExecutionContext.default()
    content = render_devices_readme(ctx, alloy_codegen_revision="deadbeef")
    assert "`deadbeef`" in content
    # And when revision is None, the placeholder shows up instead.
    none_content = render_devices_readme(ctx, alloy_codegen_revision=None)
    assert "(revision unknown)" in none_content


def test_devices_readme_matches_pinned_golden() -> None:
    """Drift detector: the rendered README must equal the pinned fixture
    when called with the same revision string.

    Update the fixture by running:
        uv run python -c "
        from alloy_codegen.context import ExecutionContext
        from alloy_codegen.runtime_readme import render_devices_readme
        ctx = ExecutionContext.default()
        open('tests/fixtures/emitted/devices-readme/README.md','w').write(
            render_devices_readme(ctx, alloy_codegen_revision='golden-fixture'))"
    """
    from pathlib import Path

    fixture = Path(__file__).parent / "fixtures" / "emitted" / "devices-readme" / "README.md"
    expected = fixture.read_text(encoding="utf-8")
    ctx = ExecutionContext.default()
    actual = render_devices_readme(ctx, alloy_codegen_revision="golden-fixture")
    assert actual == expected, (
        "Devices-README golden drifted; either the table content or the family "
        "caveats moved.  If intended, regenerate the fixture using the snippet "
        "in this test's docstring."
    )
