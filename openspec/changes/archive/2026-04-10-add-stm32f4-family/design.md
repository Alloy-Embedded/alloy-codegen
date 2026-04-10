## Context

The current pipeline treats `BOOTSTRAP_VENDOR = "st"` and `BOOTSTRAP_FAMILY = "stm32g0"` as
universal constants. They appear in five places: `bootstrap.py`, `scope.py`, `patches.py`,
`normalize.py`, and `emit.py`. Adding a second family requires these to become per-scope
values rather than module-level singletons.

Constraints:
- No new pipeline stages — same `fetch → patch → normalize → validate → emit → publish`
- Canonical IR schema must not fork per family — same `CanonicalDeviceIR` for all families
- Artifact layout (`{vendor}/{family}/...`) already encodes family identity; no format change
- `PipelineScope` already carries optional `vendor`/`family` fields — these just need to be
  populated from the registry when omitted

## Goals / Non-Goals

Goals:
- Enable any registered `(vendor, family)` to pass through the full pipeline
- `stm32f4` devices normalize and emit correct artifacts with the same quality bar as `stm32g0`
- Cross-family isolation: adding F4 data cannot regress G0 golden tests
- CLI scope resolution works: `--device stm32f401re` resolves vendor/family automatically

Non-Goals:
- Dynamic plugin loading of vendor adapters (out of scope — all families share the same
  STM32 adapter stack for now)
- Runtime vendor discovery from the filesystem
- Exposing multi-family to the publication workflow in this change (publication already uses
  `scope.resolved_vendor()/resolved_family()` paths, so it inherits multi-family for free)

## Decisions

**Decision: device-to-family registry in `bootstrap.py`**

Replace the single tuple `BOOTSTRAP_DEVICE_NAMES` with a dict:
```python
DEVICE_REGISTRY: dict[tuple[str, str], tuple[str, ...]] = {
    ("st", "stm32g0"): ("stm32g030f6", "stm32g071rb", "stm32g0b1re"),
    ("st", "stm32f4"): ("stm32f401re", "stm32f405rg"),
}
```
`bootstrap_device_names()` becomes `registered_device_names(vendor, family)`.
A new helper `resolve_device_family(device_name)` returns `(vendor, family)` for any
registered device.

Alternatives considered:
- Filesystem discovery: scan `patches/*/` at startup. Rejected — implicit, slow, non-hermetic.
- Per-family module: create `src/alloy_codegen/families/stm32f4.py`. Rejected — over-engineered
  for a data change; the adapter code is identical.

**Decision: scope auto-resolution from device name**

`PipelineScope.validate_supported()` calls `resolve_device_family(device_name)` when
`vendor`/`family` are not explicitly provided. This means `--device stm32f401re` works
without requiring `--vendor st --family stm32f4`.

**Decision: parameterise patch path helpers**

```python
def family_patch_file_path(context, *, vendor: str, family: str) -> Path: ...
def patch_file_path(context, device_name: str, *, vendor: str, family: str) -> Path: ...
```
All callers (`load_device_patch`, `load_family_patch_catalog`, `normalize.run`) pass
`scope.resolved_vendor()` / `scope.resolved_family()`. No default fall-through to constants.

**Decision: F4 device selection**

- `stm32f401re` — LQFP64, Cortex-M4F, 512 KB flash / 96 KB RAM. Minimal mid-range F4.
- `stm32f405rg` — LQFP64, Cortex-M4F, 1 MB flash / 192 KB RAM. Higher-feature F4 with USB OTG.

Both share the same package, enabling same-family cross-device comparison. SVD files are
available from cmsis-svd-data under `data/STMicro/`.

## Risks / Trade-offs

- **Risk**: F4 SVD quality may differ from G0 — peripheral aliases, interrupt naming.
  Mitigation: patch layer exists for exactly this; add F4 family.json corrections before
  shipping.
- **Risk**: `resolve_device_family` must be kept in sync with `DEVICE_REGISTRY`.
  Mitigation: derive it from the registry — no separate lookup table.

## Migration Plan

1. Update `bootstrap.py` registry and helpers (no breakage to callers yet)
2. Update `scope.py` to use registry
3. Update `patches.py` to accept vendor/family params
4. Update `normalize.py` and `emit.py` to forward scope fields
5. Add F4 patch JSON, SVD fixtures, MCU XML fixtures
6. Run full test suite; regenerate golden fixtures for F4 devices
7. Update `tasks.md` check-boxes as each step completes

Rollback: all changes are additive except the signature change to `patch_file_path` /
`family_patch_file_path`; those callers are all within the same repo and updated atomically.

## Open Questions

- None — architecture is settled.
