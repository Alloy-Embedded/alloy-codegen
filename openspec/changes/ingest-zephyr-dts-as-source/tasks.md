# Tasks — ingest-zephyr-dts-as-source

## Phase 1: Adapter scaffolding

- [ ] 1.1 Create `src/alloy_codegen/sources/zephyr_dts.py`.
- [ ] 1.2 Vendor `edtlib` (or depend on
      `python-devicetree>=0.0.2` from `pyproject.toml`).
- [ ] 1.3 Register the adapter via
      `@register_vendor_adapter("nordic", "nrf52")` (depends on
      `add-vendor-adapter-registry`).

## Phase 2: Resolve DTS into IR objects

- [ ] 2.1 Resolve a target's `.dts` + included `.dtsi` files via
      `edtlib.EDT(...)` and walk the resolved tree.
- [ ] 2.2 Extract peripheral instances from compatible-matching
      nodes (e.g. `nordic,nrf-twi`, `nordic,nrf-spi`).
- [ ] 2.3 Extract IRQ numbers from `interrupts` properties.
- [ ] 2.4 Extract clock parents from `clocks` properties (best-effort
      — clock graph is partial in DTS).
- [ ] 2.5 Extract DMA channels from `dmas` properties when present.
- [ ] 2.6 Extract pinctrl groups from `pinctrl-0` references and
      decode them into `connection_candidates`.

## Phase 3: ExecutionContext integration

- [ ] 3.1 Add `zephyr-root` source override to
      `ExecutionContext` so tests can pin a specific Zephyr
      checkout.
- [ ] 3.2 Wire fetch stage to call the new adapter when the
      registry resolves to it.

## Phase 4: Tests + fixture

- [ ] 4.1 Snapshot a minimal Zephyr DTS subset for an nRF52 part
      under `tests/fixtures/zephyr-dts/`.
- [ ] 4.2 Pipeline test that the adapter produces a valid
      canonical IR for the snapshotted device (peripherals,
      interrupts, basic clocks present).
- [ ] 4.3 Negative test: an unsupported `compatible` string does
      not crash the adapter — it logs and skips.
- [ ] 4.4 `pytest -q` + `ruff check` clean.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 5.2 `openspec validate ingest-zephyr-dts-as-source --strict`
      passes.
