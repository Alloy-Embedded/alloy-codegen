"""Greedy per-key minifier for device patches (invert-patch-as-diff).

For every ``patches/<vendor>/<family>/devices/<device>.json`` the
minifier:

1. Loads the patch JSON.
2. Runs the alloy normalize stage with the patch as-is and snapshots
   the resulting ``device.to_dict()`` — the **reference IR**.
3. For each top-level optional key in the patch, drops it, re-runs
   normalize, and compares the resulting IR to the reference.  If
   the IR is byte-identical, the key is redundant — the value
   matches what the pipeline derives from sources alone — and stays
   dropped.  If the IR differs, the key is restored.
4. Stamps a ``$baseline-revision`` matching the SHA-256 (truncated
   to 16 hex chars) of the rewritten patch contents, so the loader
   can detect future drift.
5. Writes the minified JSON back in place.

Reversibility (``--explode``) re-merges the original patch from a
backup snapshot stored at ``<patch>.full.json`` so reviewers can
inspect the dropped fields.

Required-by-schema fields (``patch_id``, ``device``, ``svd_file``,
``pin_data_file``, ``package``, ``core``, ``summary``) are never
dropped — the loader rejects patches missing them.

Usage::

    python -m scripts.minify_device_patches \\
        --vendor st --family stm32g0 --device stm32g071rb [--explode]
    python -m scripts.minify_device_patches --all   # every admitted patch

Idempotent: re-running on an already-minified patch is a no-op.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import shutil
import sys
import tempfile
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(REPO / "src"))

from alloy_codegen.bootstrap import DEVICE_REGISTRY  # noqa: E402
from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.scope import PipelineScope  # noqa: E402
from alloy_codegen.stages.normalize import run as run_normalize  # noqa: E402

# Top-level keys the schema requires to construct a valid DevicePatch.
# These are NEVER dropped by the minifier — even if their values
# happen to coincide with what raw sources expose, the patch loader
# requires them to be present.
_REQUIRED_KEYS: frozenset[str] = frozenset(
    {
        "patch_id",
        "device",
        "svd_file",
        "pin_data_file",
        "package",
        "pin_count",
        "core",
        "summary",
        "peripherals",  # listed for safety; some normalize paths require an
        # explicit admit list.  Conservative: keep, even if matching.
    }
)

# Top-level keys the loader treats as optional and the minifier may
# attempt to drop (in order — leftmost first).  Driven from the
# DevicePatch dataclass, but listed explicitly so the minifier order
# is stable across versions.
_OPTIONAL_KEYS: tuple[str, ...] = (
    "memories",
    "registers",
    "register_fields",
    "pins",
    "clock_nodes",
    "clock_selectors",
    "clock_gates",
    "resets",
    "peripheral_clock_bindings",
    "interrupts",
    "system_clock_profiles",
    "dma_controllers",
    "dma_request_refs",
    "adc_internal_channels",
    "adc_calibration_data_points",
    "adc_calibration_context",
    "adc_resolution_options",
    "adc_sample_time_options",
    "adc_oversampling_options",
    "adc_external_triggers",
    "adc_max_clock_hz",
    "uart_baud_clock_sources",
    "uart_baud_oversampling_options",
    "uart_fifo_trigger_options",
    "uart_data_bits_options",
    "uart_parity_options",
    "uart_stop_bits_options",
    "uart_mode_flags",
    "uart_max_baud_hz",
    "spi_baud_prescaler_options",
    "spi_frame_size_options",
    "spi_fifo_threshold_options",
    "spi_mode_flags",
    "timer_prescaler_options",
    "timer_trigger_sources",
    "timer_master_outputs",
    "timer_mode_flags",
    "pwm_deadtime_options",
    "pwm_alignment_options",
    "pwm_break_inputs",
    "pwm_mode_flags",
    "peripheral_max_clock_hz",
    "i2c_speed_options",
    "i2c_timing_presets",
    "i2c_mode_flags",
)


def _device_patch_path(vendor: str, family: str, device: str) -> Path:
    return REPO / "patches" / vendor / family / "devices" / f"{device}.json"


def _execution_context_for(vendor: str, family: str) -> ExecutionContext:
    """Build an ExecutionContext with fixture sources so the minifier
    can run the pipeline offline.  Falls back to the default context
    if no test fixture exists for the family — the user's own
    workstation typically has the real source overrides set."""
    base = ExecutionContext.default()
    fixture_overrides = {
        ("st", "stm32g0"): {
            "cmsis-svd-data": str(REPO / "tests/fixtures/cmsis-svd-data"),
            "stm32-open-pin-data": str(REPO / "tests/fixtures/stm32-open-pin-data"),
        },
        ("st", "stm32f4"): {
            "cmsis-svd-data": str(REPO / "tests/fixtures/cmsis-svd-data"),
            "stm32-open-pin-data": str(REPO / "tests/fixtures/stm32-open-pin-data"),
        },
        ("microchip", "same70"): {
            "microchip-dfp-extract": str(REPO / "tests/fixtures/microchip-dfp-same70"),
        },
        ("microchip", "avr-da"): {
            "microchip-dfp-extract": str(REPO / "tests/fixtures/microchip-dfp-avr-da"),
        },
        ("nxp", "imxrt1060"): {
            "nxp-mcux-soc-svd": str(REPO / "tests/fixtures/nxp-mcux-imxrt1060/svd"),
            "nxp-mcux-sdk": str(REPO / "tests/fixtures/nxp-mcux-imxrt1060/sdk"),
        },
        ("raspberrypi", "rp2040"): {
            "pico-sdk": str(REPO / "tests/fixtures/pico-sdk"),
        },
        ("espressif", "esp32"): {
            "espressif-svd": str(REPO / "tests/fixtures/espressif-svd"),
        },
        ("espressif", "esp32c3"): {
            "espressif-svd": str(REPO / "tests/fixtures/espressif-svd"),
        },
        ("espressif", "esp32s3"): {
            "espressif-svd": str(REPO / "tests/fixtures/espressif-svd"),
        },
    }.get((vendor, family))
    if fixture_overrides is None:
        return base
    with tempfile.TemporaryDirectory() as tmp:
        return base.with_overrides(
            source_overrides=fixture_overrides,
            artifact_root=str(Path(tmp) / "artifacts"),
            publication_root=str(Path(tmp) / "publication"),
        )


def _normalized_ir(vendor: str, family: str, device: str) -> dict:
    """Run the pipeline once and return ``device.to_dict()`` for the
    given device.  Re-creates the context per call so the temporary
    artifact root doesn't leak across calls."""
    base = ExecutionContext.default()
    fixture_map = {
        ("st", "stm32g0"): {
            "cmsis-svd-data": str(REPO / "tests/fixtures/cmsis-svd-data"),
            "stm32-open-pin-data": str(REPO / "tests/fixtures/stm32-open-pin-data"),
        },
        ("st", "stm32f4"): {
            "cmsis-svd-data": str(REPO / "tests/fixtures/cmsis-svd-data"),
            "stm32-open-pin-data": str(REPO / "tests/fixtures/stm32-open-pin-data"),
        },
        ("microchip", "same70"): {
            "microchip-dfp-extract": str(REPO / "tests/fixtures/microchip-dfp-same70"),
        },
        ("microchip", "avr-da"): {
            "microchip-dfp-extract": str(REPO / "tests/fixtures/microchip-dfp-avr-da"),
        },
        ("nxp", "imxrt1060"): {
            "nxp-mcux-soc-svd": str(REPO / "tests/fixtures/nxp-mcux-imxrt1060/svd"),
            "nxp-mcux-sdk": str(REPO / "tests/fixtures/nxp-mcux-imxrt1060/sdk"),
        },
        ("raspberrypi", "rp2040"): {
            "pico-sdk": str(REPO / "tests/fixtures/pico-sdk"),
        },
        ("espressif", "esp32"): {
            "espressif-svd": str(REPO / "tests/fixtures/espressif-svd"),
        },
        ("espressif", "esp32c3"): {
            "espressif-svd": str(REPO / "tests/fixtures/espressif-svd"),
        },
        ("espressif", "esp32s3"): {
            "espressif-svd": str(REPO / "tests/fixtures/espressif-svd"),
        },
    }
    overrides = fixture_map.get((vendor, family))
    if overrides is None:
        ctx = base
    else:
        ctx = base.with_overrides(
            source_overrides=overrides,
            artifact_root="/tmp/_alloy_minify_artifacts",
            publication_root="/tmp/_alloy_minify_publication",
        )
    result = run_normalize(PipelineScope(device=device), ctx)
    return result.payload.devices[0].to_dict()


def _short_sha(content: bytes) -> str:
    return hashlib.sha256(content).hexdigest()[:16]


def _stamp_baseline_revision(payload: dict) -> dict:
    """Set ``$baseline-revision`` to the SHA-16 of the JSON-serialised
    payload (with the field temporarily empty)."""
    payload = {k: v for k, v in payload.items() if k != "$baseline-revision"}
    serialised = json.dumps(payload, indent=2, sort_keys=False).encode("utf-8")
    revision = _short_sha(serialised)
    payload["$baseline-revision"] = revision
    return payload


def _minify_one(vendor: str, family: str, device: str) -> tuple[int, int]:
    """Greedy per-key minification.  Returns (kept_keys, dropped_keys)."""
    patch_path = _device_patch_path(vendor, family, device)
    if not patch_path.exists():
        raise SystemExit(f"missing patch: {patch_path}")
    original_text = patch_path.read_text()
    original_payload = json.loads(original_text)

    backup_path = patch_path.with_suffix(".full.json")
    if not backup_path.exists():
        backup_path.write_text(original_text)

    reference_ir = _normalized_ir(vendor, family, device)

    working = dict(original_payload)
    dropped: list[str] = []

    for key in _OPTIONAL_KEYS:
        if key not in working or key in _REQUIRED_KEYS:
            continue
        original_value = working.pop(key)
        # Persist the trial state and re-run normalize.
        patch_path.write_text(json.dumps(working, indent=2))
        try:
            trial_ir = _normalized_ir(vendor, family, device)
        except Exception:
            # Pipeline crash → restore and move on.
            working[key] = original_value
            patch_path.write_text(json.dumps(working, indent=2))
            continue
        if trial_ir == reference_ir:
            dropped.append(key)
        else:
            working[key] = original_value

    # Stamp baseline revision + write final JSON.
    final_payload = _stamp_baseline_revision(working)
    patch_path.write_text(json.dumps(final_payload, indent=2) + "\n")

    return len(working), len(dropped)


def _explode_one(vendor: str, family: str, device: str) -> None:
    """Restore the original full patch from the ``<patch>.full.json``
    backup snapshot."""
    patch_path = _device_patch_path(vendor, family, device)
    backup_path = patch_path.with_suffix(".full.json")
    if not backup_path.exists():
        raise SystemExit(
            f"no backup found at {backup_path}; minify the patch first to create one"
        )
    shutil.copy(backup_path, patch_path)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--vendor", help="Vendor identifier (e.g. st)")
    parser.add_argument("--family", help="Family identifier (e.g. stm32g0)")
    parser.add_argument("--device", help="Device identifier (e.g. stm32g071rb)")
    parser.add_argument(
        "--all",
        action="store_true",
        help="Minify every device patch admitted by DEVICE_REGISTRY.",
    )
    parser.add_argument(
        "--explode",
        action="store_true",
        help="Restore the original full patch from the .full.json backup.",
    )
    args = parser.parse_args(argv)

    if args.all:
        targets = [
            (vendor, family, device)
            for (vendor, family), devices in DEVICE_REGISTRY.items()
            for device in devices
        ]
    elif args.vendor and args.family and args.device:
        targets = [(args.vendor, args.family, args.device)]
    else:
        parser.error("specify either --all or all of --vendor/--family/--device")
        return 2

    for vendor, family, device in targets:
        try:
            if args.explode:
                _explode_one(vendor, family, device)
                print(f"  exploded {vendor}/{family}/{device}")
            else:
                kept, dropped = _minify_one(vendor, family, device)
                print(
                    f"  {vendor}/{family}/{device}: kept {kept} keys, "
                    f"dropped {dropped} redundant"
                )
        except SystemExit as exc:
            print(f"  skip {vendor}/{family}/{device}: {exc}", file=sys.stderr)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
