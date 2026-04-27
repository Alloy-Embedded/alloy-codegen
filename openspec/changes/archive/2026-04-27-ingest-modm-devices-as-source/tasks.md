# Tasks — ingest-modm-devices-as-source

## Phase 1: Adapter

- [x] 1.1 Create `src/alloy_codegen/sources/modm_devices.py`.
- [x] 1.2 Parse `modm-devices/devices/stm32/<family>/<part>.xml`
      using `lxml`.
- [x] 1.3 Map modm's XML schema into our intermediate objects
      (peripherals, interrupts, dma_requests, connection_candidates,
      clock graph edges).
- [x] 1.4 Register via
      `@register_vendor_adapter("st", "stm32g0")` (and other ST
      families) — the registry resolves to the modm adapter
      *alongside* the existing CMSIS-SVD adapter; merge order
      handles precedence.

## Phase 2: Merge precedence

- [x] 2.1 Document and implement the merge order:
      `cmsis-svd < stm32-open-pin-data < modm-devices <
      family-patch < device-patch`.
- [x] 2.2 Per-field provenance in the resolved IR records which
      source contributed each leaf — so reviewers can tell where
      data came from.

## Phase 3: Source pinning

- [x] 3.1 `data/source_pins.toml` records the modm-devices
      checkout SHA the integration was run against.  Bumping it
      is a reviewable diff.
- [x] 3.2 The fetch stage refuses to load modm data if the
      checkout SHA does not match the pin (overridable with
      `--accept-stale-sources`).

## Phase 4: Validation guard

- [x] 4.1 For every currently admitted STM32 device, assert the
      modm import produces a structurally compatible IR fragment
      — no field-type mismatches, no missing required keys.
- [x] 4.2 Snapshot a minimal modm-devices subset under
      `tests/fixtures/modm-devices/` for the test fixture.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/vendor-admission/spec.md`.
- [x] 5.2 `openspec validate ingest-modm-devices-as-source --strict`
      passes.
- [x] 5.3 `pytest -q` + `ruff check` clean.
