"""Tests for the alloy-devices-yml submodule consumer.

Added by ``extract-alloy-devices-data-repo``.
"""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.bootstrap import DEVICE_REGISTRY, registered_device_names  # noqa: E402
from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.sources import alloy_devices_yml as adyml  # noqa: E402
from alloy_codegen.stages.normalize import run as run_normalize  # noqa: E402

_DATA_REPO_AVAILABLE = (adyml.DATA_REPO_ROOT / "schema").exists()


def _admitted_triples() -> list[tuple[str, str, str]]:
    triples: list[tuple[str, str, str]] = []
    for (vendor, family), _ in DEVICE_REGISTRY.items():
        for device in registered_device_names(vendor, family):
            triples.append((vendor, family, device))
    return sorted(triples)


@pytest.mark.skipif(
    not _DATA_REPO_AVAILABLE,
    reason="alloy-devices-yml submodule not initialised (run `git submodule update --init`)",
)
class TestAlloyDevicesYmlConsumer:
    def test_data_repo_root_resolves(self) -> None:
        """The submodule root must point inside this checkout."""
        assert adyml.DATA_REPO_ROOT == ROOT / "data" / "devices"
        assert adyml.DATA_REPO_ROOT.exists()

    def test_submodule_revision_returns_sha(self) -> None:
        sha = adyml.submodule_revision()
        # SHA-1 is 40 hex chars when fully resolved.
        assert sha is None or (len(sha) == 40 and all(c in "0123456789abcdef" for c in sha))

    @pytest.mark.parametrize("triple", _admitted_triples())
    def test_every_admitted_device_has_a_yaml(self, triple: tuple[str, str, str]) -> None:
        """Spec scenario: every device alloy-codegen admits today
        resolves to a YAML in the data repo."""
        vendor, family, device = triple
        assert adyml.is_available(vendor=vendor, family=family, device=device), (
            f"missing YAML for {vendor}/{family}/{device}; expected at "
            f"{adyml.device_yaml_path(vendor=vendor, family=family, device=device)}"
        )

    def test_load_canonical_device_returns_valid_ir(self) -> None:
        ir = adyml.load_canonical_device(vendor="nordic", family="nrf52", device="nrf52840")
        assert ir.identity.vendor == "nordic"
        assert ir.identity.family == "nrf52"
        assert ir.identity.device == "nrf52840"
        # Schema-validated loaders preserve the IR shape — peripherals
        # must round-trip non-empty for the Nordic admission.
        assert len(ir.peripherals) > 0

    def test_load_canonical_device_unknown_raises(self) -> None:
        from alloy_codegen.errors import StageExecutionError

        with pytest.raises(StageExecutionError, match="no entry for"):
            adyml.load_canonical_device(vendor="acme", family="bogus", device="zzz")

    def test_normalize_short_circuits_through_yaml(self, tmp_path: Path) -> None:
        """Spec scenario: when YAML is present, the normalize stage
        loads the IR directly without consulting upstream sources."""
        # No source overrides — if the short-circuit doesn't kick in,
        # the legacy fetch path will fail because no source root is
        # configured.
        ctx = ExecutionContext.default().with_overrides(
            source_overrides={},
            artifact_root=str(tmp_path / "a"),
            publication_root=str(tmp_path / "p"),
        )
        result = run_normalize(PipelineScope(device="nrf52840"), ctx)
        assert len(result.payload.devices) == 1
        ir = result.payload.devices[0]
        assert ir.identity.device == "nrf52840"

    def test_fetch_synthesises_alloy_devices_yml_record(self, tmp_path: Path) -> None:
        """Spec scenario: fetch records identify alloy-devices-yml
        as the source when YAML is present."""
        from alloy_codegen.stages.fetch import run as run_fetch

        ctx = ExecutionContext.default().with_overrides(
            source_overrides={},
            artifact_root=str(tmp_path / "a"),
            publication_root=str(tmp_path / "p"),
        )
        result = run_fetch(PipelineScope(device="nrf52840"), ctx)
        sources = result.payload.source_manifest.sources
        assert any(s.source_id == "alloy-devices-yml" for s in sources)
        record = next(s for s in sources if s.source_id == "alloy-devices-yml")
        assert record.target_device == "nrf52840"
        assert record.upstream_path.endswith("nrf52840.yml")
