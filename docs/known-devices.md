# Known-Devices Catalog

`data/known_devices.toml` is the canonical inventory of admittable
MCUs imported from
[`probe-rs/probe-rs`](https://github.com/probe-rs/probe-rs)'s
`targets/*.yaml` collection (~5,000 chip variants).  It answers the
question **"what MCUs exist?"** independent of which devices alloy
currently admits via its `patches/` tree.

This catalog is **read-only** with respect to the pipeline:

- Hand-curated `patches/<vendor>/<family>/devices/<device>.json`
  files remain the source of truth on conflict.
- The catalog is consulted only for **discoverability** (which
  STM32G0 variants exist that we don't admit yet?) and **admission
  scaffolding** (pair with `autogen-device-patches-from-svd` to
  batch-draft patches for unfamiliar parts).

## Files

| File | Purpose |
|------|---------|
| `data/known_devices.toml` | Sorted-by-`(vendor, family, device)` array of catalog entries.  Each carries the probe-rs target name, core, optional flash-algo reference, optional source-pack reference, and a memory-region table. |
| `data/known_devices.meta.toml` | Pinned probe-rs commit SHA + import timestamp + tool version.  Re-running the importer at the pinned SHA reproduces `known_devices.toml` byte-for-byte. |

## Importer

```bash
uv run --with pyyaml python -m tools.import_probe_rs_targets \
    --probe-rs-root <path-to-probe-rs-checkout> \
    [--output-dir data/]
```

PyYAML is required at runtime; it is not added to the package
dependency closure because the importer is a developer tool, not a
pipeline stage.

The importer is deterministic — re-running on the same probe-rs
SHA produces byte-identical output.  Sort order is
`(vendor, family, device)` so diffs against the prior draft are
minimal when probe-rs upstream lands new targets.

## Admitted-but-not-in-probe-rs allow-list

A small number of devices the alloy pipeline admits today are **not**
in the probe-rs catalog.  Each is recorded in
`tests/test_known_devices_catalog.py::_NOT_IN_PROBE_RS` with a
rationale:

| Device | Reason |
|--------|--------|
| `espressif/esp32/esp32-wroom32` | Marketing module name; probe-rs catalogs the silicon (`esp32`) only. |
| `microchip/avr-da/avr128da32` | probe-rs is ARM-only — AVR DFPs are not covered. |
| `raspberrypi/rp2040/pico` | Pico is a board, not a chip; the chip entry `rp2040` covers it. |

Adding a new admitted device that is not in probe-rs requires
either:

1. Adding the entry to `_NOT_IN_PROBE_RS` with a rationale, or
2. Re-importing from a probe-rs SHA that includes the device.

The test fails otherwise so the gap is visible at review time.

## Conflict resolution

If a hand-curated patch's memory map disagrees with the catalog's
memory map, the patch wins.  The catalog is informational for the
pipeline; only the patches drive emission.  If the disagreement is
because probe-rs has authoritative data the patch should adopt,
that is a manual decision recorded in a regular patch update — the
catalog does not auto-flow corrections into the patches tree.
