"""Regenerate `<device>.canonical.json` fixtures for families touched by
the UART/SPI Tier 2/3/4 patch population.  Idempotent."""

from __future__ import annotations

import json
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(REPO / "src"))

from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.stages.normalize import run as run_normalize  # noqa: E402

FIXTURES = REPO / "tests" / "fixtures"


def _ctx(overrides: dict[str, str]) -> ExecutionContext:
    return ExecutionContext.default().with_overrides(source_overrides=overrides)


ST = {
    "cmsis-svd-data": str(FIXTURES / "cmsis-svd-data"),
    "stm32-open-pin-data": str(FIXTURES / "stm32-open-pin-data"),
}
RP = {"pico-sdk": str(FIXTURES / "pico-sdk")}
ESP = {"espressif-svd": str(FIXTURES / "espressif-svd")}
AVR = {"microchip-dfp-extract": str(FIXTURES / "microchip-dfp-avr-da")}
NXP = {
    "nxp-mcux-soc-svd": str(FIXTURES / "nxp-mcux-imxrt1060" / "svd"),
    "nxp-mcux-sdk": str(FIXTURES / "nxp-mcux-imxrt1060" / "sdk"),
}
SAME70 = {"microchip-dfp-extract": str(FIXTURES / "microchip-dfp-same70")}

JOBS = [
    # (fixture-dir, device-name, source-overrides)
    ("stm32g0", "stm32g071rb", ST),
    ("stm32g0", "stm32g030f6", ST),
    ("stm32g0", "stm32g0b1re", ST),
    ("stm32f4", "stm32f401re", ST),
    ("stm32f4", "stm32f405rg", ST),
    ("rp2040", "rp2040", RP),
    ("rp2040", "pico", RP),
    ("esp32", "esp32", ESP),
    ("esp32c3", "esp32c3", ESP),
    ("esp32s3", "esp32s3", ESP),
    ("avr-da", "avr128da32", AVR),
    ("imxrt1060", "mimxrt1062", NXP),
    ("imxrt1060", "mimxrt1064", NXP),
    ("same70", "atsame70n21b", SAME70),
    ("same70", "atsame70q21b", SAME70),
]


def main() -> None:
    for fx_dir, device, overrides in JOBS:
        ctx = _ctx(overrides)
        result = run_normalize(PipelineScope(device=device), ctx)
        payload = result.payload.devices[0].to_dict()
        out = FIXTURES / fx_dir / f"{device}.canonical.json"
        out.write_text(json.dumps(payload, indent=2) + "\n")
        print(f"  regen {out.relative_to(REPO)}")


if __name__ == "__main__":
    main()
