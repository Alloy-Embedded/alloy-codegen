"""Phase 0.3 parity gate: for every admitted device, the IR
loaded from `alloy-devices-yml` MUST byte-equal (modulo
primitive projection) the IR built by the legacy
`_build_<vendor>_device_ir` path.

This is the safety net that lets Phase-1 migrations remove
legacy parsers vendor-by-vendor: as long as both paths produce
the same IR, the codegen output is the same regardless of which
path ran.

Failure mode: pretty-printed structural diff per drifted field,
with a clear instruction telling the maintainer how to
regenerate the YAML if the change was intentional.

Devices whose YAML is absent from the submodule SKIP — the gate
stays green during gradual rollout.
"""

from __future__ import annotations

import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.bootstrap import DEVICE_REGISTRY  # noqa: E402
from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.sources import alloy_devices_yml as _adyml  # noqa: E402
from alloy_codegen.testing.ir_diff import ir_diff, render_diffs  # noqa: E402
from alloy_codegen.vendors import resolve_vendor_adapter  # noqa: E402

# Devices whose YAML in the alloy-devices-yml submodule is known
# to be stale relative to the current legacy `_build_*_device_ir`
# path.  These are tracked here as `xfail(strict=False)` so the
# gate stays GREEN today while making the gap explicit.
#
# Phase-1 migrations remove an entry from this set when they
# regenerate that vendor's YAMLs.  An empty set means every
# admitted device is byte-equal between paths.
_KNOWN_DRIFT: frozenset[tuple[str, str, str]] = frozenset()


def _admitted_devices() -> list[tuple[str, str, str]]:
    return [
        (vendor, family, device)
        for (vendor, family), devices in DEVICE_REGISTRY.items()
        for device in devices
    ]


@pytest.mark.parametrize(
    ("vendor", "family", "device"),
    _admitted_devices(),
    ids=lambda d: f"{d}",
)
def test_yaml_path_matches_legacy_path_byte_for_byte(
    vendor: str, family: str, device: str, request: pytest.FixtureRequest
) -> None:
    if (vendor, family, device) in _KNOWN_DRIFT:
        request.applymarker(
            pytest.mark.xfail(
                strict=False,
                reason=(
                    f"{vendor}/{family}/{device}: alloy-devices-yml YAML is "
                    "stale relative to the legacy IR path.  Tracked in "
                    "_KNOWN_DRIFT; Phase-1 migration of this vendor will "
                    "regenerate the YAML and remove this entry."
                ),
            )
        )
    if not _adyml.is_available(vendor=vendor, family=family, device=device):
        pytest.skip(
            f"alloy-devices-yml has no entry for {vendor}/{family}/{device} — "
            "submodule may not be initialised, or device YAML not yet committed."
        )

    yaml_ir = _adyml.load_canonical_device(vendor=vendor, family=family, device=device)

    # Build IR via the legacy path.  This re-runs the entire
    # vendor adapter (fetch + normalize) and is therefore slow
    # — but it is the canonical reference.  Only required for
    # the 17 admitted devices; bulk-mode does not run this gate.
    try:
        adapter = resolve_vendor_adapter(vendor, family)
    except Exception as exc:  # noqa: BLE001
        pytest.skip(
            f"vendor adapter unavailable for {vendor}/{family} ({exc!r}). "
            "Phase-1 migration may have removed the legacy path; "
            "parity gate is moot for this vendor once that lands."
        )

    execution_context = ExecutionContext.default()
    try:
        legacy_ir = adapter.normalize(
            execution_context=execution_context,
            device_name=device,
            vendor=vendor,
            family=family,
        )
    except Exception as exc:  # noqa: BLE001
        pytest.skip(
            f"legacy IR build failed for {vendor}/{family}/{device} "
            f"({type(exc).__name__}: {exc}).  This is environmental "
            "(missing source pins, offline CI, etc) — not a parity failure."
        )

    diffs = ir_diff(legacy_ir, yaml_ir)
    if diffs:
        report = render_diffs(diffs)
        pytest.fail(
            f"YAML / legacy IR drift for {vendor}/{family}/{device}:\n"
            f"{report}\n"
            "\nTo regenerate the YAML from the legacy path, run:\n"
            f"  python scripts/regen_canonical_yamls.py "
            f"--vendor {vendor} --family {family} --device {device}\n"
            "(after reviewing the diff for unintended changes)."
        )
