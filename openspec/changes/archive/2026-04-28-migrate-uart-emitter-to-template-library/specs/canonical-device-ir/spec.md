## ADDED Requirements

### Requirement: The UART trait emitter SHALL consume the peripheral-trait template library

The UART trait emitter SHALL look up each
peripheral instance's template (via
`peripheral_traits.resolve_template(...)`) keyed on
`(peripheral.ip_name, peripheral.ip_version)` and apply
`merge_chain(baseline, template.values, family_overrides,
device_overrides)` to compute the effective Tier 2/3/4 trait
values that flow into `uart.hpp`.  When no template is
registered for an `(ip_name, ip_version)` pair, the emitter
SHALL fall back to today's device-patch-only path, preserving
the existing behaviour.  Every emitted UART trait struct that
inherited from a template SHALL include a comment header
identifying the template revision tag
(`peripheral_traits/uart/<ip_name>__<ip_version>@rev<N>`) so
reviewers can audit which revision the device pinned against.

#### Scenario: Two USART_v2 instances inherit identical merged defaults

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
  and STM32F4 stm32f401re — both peripherals are
  `(ip_name=usart, ip_version=v2)`
- **THEN** the resolved trait values for `parity_options`,
  `data_bits_options`, `stop_bits_options`, `oversampling_options`,
  `fifo_trigger_options`, and `mode_flags` SHALL be identical
  across the two devices, sourced from
  `data/peripheral_traits/uart/usart_v2.toml`
- **AND** both emitted headers SHALL carry the comment header
  `// peripheral_traits/uart/usart__v2@rev<N>`

#### Scenario: Device-patch fields override template values

- **WHEN** an STM32G0 device patch explicitly sets
  `uart_max_baud_hz` to a value that differs from the template
- **THEN** the emitted `kMaxBaudHz` constexpr SHALL match the
  device-patch value, not the template value
- **AND** other UART trait fields not overridden by the patch
  SHALL still come from the template

#### Scenario: Unmapped ip_version falls back to today's path

- **WHEN** the pipeline emits `uart.hpp` for a device whose
  UART instance carries an `ip_version` that has no matching
  template under `data/peripheral_traits/uart/`
- **THEN** the emitter SHALL produce the same output as before
  this change
- **AND** no provenance comment SHALL be emitted for that
  trait struct
