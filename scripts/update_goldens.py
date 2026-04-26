"""Re-emit each fixture-backed family and overwrite stale golden text artifacts.

Idempotent. After a true emitter regression, inspect `git diff
tests/fixtures/emitted/` before committing.
"""

from __future__ import annotations

import sys
import tempfile
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO_ROOT / "src"))

from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.stages.emit import run as run_emit  # noqa: E402


def _ctx(tmp: Path, overrides: dict[str, str]) -> ExecutionContext:
    return ExecutionContext.default().with_overrides(
        source_overrides=overrides,
        artifact_root=str(tmp / "artifacts"),
        publication_root=str(tmp / "publication"),
    )


_FX = REPO_ROOT / "tests" / "fixtures"

FAMILIES = [
    (
        "stm32g0",
        "st/stm32g0/",
        {"device": "stm32g071rb"},
        {
            "cmsis-svd-data": str(_FX / "cmsis-svd-data"),
            "stm32-open-pin-data": str(_FX / "stm32-open-pin-data"),
        },
    ),
    (
        "imxrt1060",
        "nxp/imxrt1060/",
        {"vendor": "nxp", "family": "imxrt1060"},
        {
            "nxp-mcux-soc-svd": str(_FX / "nxp-mcux-imxrt1060" / "svd"),
            "nxp-mcux-sdk": str(_FX / "nxp-mcux-imxrt1060" / "sdk"),
        },
    ),
    (
        "avr-da",
        "microchip/avr-da/",
        {"vendor": "microchip", "family": "avr-da", "device": "avr128da32"},
        {"microchip-dfp-extract": str(_FX / "microchip-dfp-avr-da")},
    ),
    (
        "esp32c3",
        "espressif/esp32c3/",
        {"vendor": "espressif", "family": "esp32c3", "device": "esp32c3"},
        {"espressif-svd": str(_FX / "espressif-svd")},
    ),
    (
        "esp32s3",
        "espressif/esp32s3/",
        {"vendor": "espressif", "family": "esp32s3", "device": "esp32s3"},
        {"espressif-svd": str(_FX / "espressif-svd")},
    ),
]


def _is_text(path: str) -> bool:
    return path.endswith((".hpp", ".cpp", ".ld", ".cmake", ".json", ".md"))


def _update_one(
    fixture_name: str, prefix: str, scope_kwargs: dict, overrides: dict[str, str], tmp: Path
) -> int:
    print(f"=== {fixture_name} ===")
    fixture_root = REPO_ROOT / "tests" / "fixtures" / "emitted" / fixture_name
    if not fixture_root.exists():
        print(f"  [skip] no fixture root at {fixture_root}")
        return 0
    ctx = _ctx(tmp, overrides)
    result = run_emit(PipelineScope(**scope_kwargs), ctx)
    updated = 0
    for artifact in result.payload.artifacts:
        path = artifact.path
        if not path.startswith(prefix) or not _is_text(path):
            continue
        relative = path[len(prefix) :]
        target = fixture_root / relative
        if not target.exists():
            continue
        existing = target.read_text(encoding="utf-8")
        if existing == artifact.content:
            continue
        target.write_text(artifact.content, encoding="utf-8")
        updated += 1
        print(f"  updated {relative}")
    print(f"  -> {updated} file(s) updated")
    return updated


def main() -> int:
    total = 0
    with tempfile.TemporaryDirectory() as tmp:
        for name, prefix, scope_kwargs, overrides in FAMILIES:
            total += _update_one(name, prefix, scope_kwargs, overrides, Path(tmp))
    print(f"\nTotal files updated: {total}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
