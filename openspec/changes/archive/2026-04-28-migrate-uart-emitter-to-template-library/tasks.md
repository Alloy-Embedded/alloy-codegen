# Tasks — migrate-uart-emitter-to-template-library

## Phase 1: Emitter integration

- [x] 1.1 In `runtime_driver_semantics.py` UART trait builder,
      load the catalog once via
      `peripheral_traits.load_all_templates()`.
- [x] 1.2 For each UART peripheral instance, resolve its
      template via
      `peripheral_traits.resolve_template(catalog,
      peripheral_class="uart", ip_name=peripheral.ip_name,
      ip_version=peripheral.ip_version)`.
- [x] 1.3 If the template exists, compute the effective trait
      values via
      `merge_chain(baseline, template.values, family_overrides,
      device_overrides)`.  Otherwise fall back to the existing
      device-patch-only path so back-compat stays intact.

## Phase 2: Provenance plumbing

- [x] 2.1 When a template applied, prepend a comment line in
      the emitted trait struct identifying the revision tag:
      `// peripheral_traits/uart/<ip_name>__<ip_version>@rev<N>`.
- [x] 2.2 The tag uses the existing
      `peripheral_traits.template_provenance_tag(template)`
      helper.

## Phase 3: Tests

- [x] 3.1 `tests/test_uart_template_inheritance.py`:
      - `test_two_usart_v2_instances_inherit_identical_defaults`
        — STM32G0 USART1 and STM32F4 USART2 produce identical
        merged trait dicts (the headline spec scenario).
      - `test_device_patch_overrides_template` — when a device
        patch explicitly sets `uart_max_baud_hz`, the emitted
        value matches the patch, not the template.
      - `test_unknown_ip_version_falls_back_to_patch_only` —
        no template registered means no behaviour change vs.
        today.
- [x] 3.2 Existing UART golden tests should stay green when
      the patch values match the template defaults.  Any drift
      is regenerated via `--update-goldens` and the diff
      reviewed.

## Phase 4: Spec + final checks

- [x] 4.1 Spec delta in `specs/canonical-device-ir/spec.md`.
- [x] 4.2 `openspec validate
      migrate-uart-emitter-to-template-library --strict`
      passes.
- [x] 4.3 `pytest -q` + `ruff check` clean.
- [x] 4.4 `pytest --runtime-cpp-smoke` stays green for every
      admitted device.
