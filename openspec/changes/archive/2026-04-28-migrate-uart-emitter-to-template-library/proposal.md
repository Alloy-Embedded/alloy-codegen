# Migrate UART Emitter to Template Library

## Why

`peripheral-trait-template-library` shipped the inheritance
machinery (`load_all_templates`, `resolve_template`,
`merge_chain`) and seeded UART templates for `usart_v2`,
`lpuart_v1`, and `nrf-uart-v1` — but **no emitter consumes them
yet**.  Every device patch still carries the full Tier 2/3/4
arrays explicitly.

The UART emitter is the natural pilot: every admitted family
ships at least one UART instance, the IP-version space is small
(USART_v2 / LPUART_v1 / nrf-uart / esp32-uart), and the spec
scenario "two STM32 instances on the same USART_v2 IP receive
identical defaults" is *the* test of whether the template
library actually works end-to-end.

## What Changes

- `src/alloy_codegen/runtime_driver_semantics.py` (UART trait
  builder) gains a template-merge step:
  - Resolve the template via
    `(peripheral.ip_name, peripheral.ip_version)`.
  - Apply the merge chain
    `template ← family-patch ← device-patch` to compute the
    effective trait fields.
  - Use the merged values when emitting `uart.hpp` instead of
    reading raw patch fields directly.
- A per-peripheral provenance string
  `peripheral_traits/uart/<ip_name>__<ip_version>@rev<N>` is
  appended to the emitted trait struct's comment header so
  reviewers see at a glance which template revision a device
  pinned against (the spec-required visibility).
- Existing UART patches' Tier 2/3/4 arrays stay where they are
  — the merge order treats device-patch values as overrides on
  top of the template, so emitted artifacts stay byte-identical
  unless a patch genuinely *omits* a field that the template
  fills.
- A new test
  `tests/test_uart_template_inheritance.py::test_two_usart_v2_instances_inherit_identical_defaults`
  asserts the spec scenario directly: STM32G0 USART1 and STM32F4
  USART2 produce identical merged trait values pulled from the
  same `usart_v2.toml` template.
- Goldens that change MUST be regenerated via the
  `auto-update-goldens` flag — most should stay byte-identical
  because device patches still win.

## Impact

UART becomes the proof-of-life that the template library works
end-to-end.  Once green, follow-up changes
(`migrate-spi-emitter-to-template-library`,
`migrate-i2c-emitter-to-template-library`, etc.) become
mechanical: same pattern, different field surface.

Down the road this enables:
- Patches collapsing to diff-only (gated by
  `invert-patch-as-diff`).
- New peripherals on existing IPs landing as a single template
  edit instead of N device-patch edits.

## What this DOES NOT do

- Does not migrate any device patch.  Patches retain their
  Tier 2/3/4 arrays after this change — they still win in the
  merge chain.  Migration of patches per-family is the
  `migrate-<family>-patches-to-template-library` work.
- Does not flip SPI / I2C / TIMER / PWM / ADC emitters.  Each
  is its own follow-up change so we can validate one at a time
  and roll back if anything goes wrong.
- Does not add new template fields.  Templates already declared
  by `peripheral-trait-template-library` are the only source
  the UART emitter consults.
