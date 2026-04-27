# Tasks — add-vendor-adapter-registry

## Phase 1: Registry module

- [ ] 1.1 Create `src/alloy_codegen/vendors/registry.py` with
      `register_vendor_adapter`, `resolve_vendor_adapter`, and
      `list_registered_adapters`.
- [ ] 1.2 Define `VendorAdapter` Protocol describing the shape
      every adapter must satisfy (`fetch`, `normalize`).

## Phase 2: Migrate existing adapters

- [ ] 2.1 Annotate each `sources/*.py` adapter module with
      `@register_vendor_adapter(vendor, family)` at import time.
- [ ] 2.2 Replace the cascade in `stages/normalize.py:3207-3269`
      with a single `resolve_vendor_adapter(vendor, family)` call.
- [ ] 2.3 Replace any analogous cascade in `stages/fetch.py`.
- [ ] 2.4 Unknown adapters raise `StageExecutionError` listing
      the registered set.

## Phase 3: Tests

- [ ] 3.1 Unit test that every currently-admitted family resolves
      to a registered adapter.
- [ ] 3.2 Unit test that an unknown `(vendor, family)` raises
      `StageExecutionError` with a discoverable message.
- [ ] 3.3 Full `pytest -q` + `ruff check` clean.

## Phase 4: Spec + final checks

- [ ] 4.1 Spec delta in `specs/vendor-admission/spec.md`.
- [ ] 4.2 `openspec validate add-vendor-adapter-registry --strict`
      passes.
