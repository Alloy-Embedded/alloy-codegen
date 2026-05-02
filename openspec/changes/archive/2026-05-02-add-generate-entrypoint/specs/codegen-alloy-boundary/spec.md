## ADDED Requirements

### Requirement: alloy_codegen SHALL expose a top-level generate(config, out_dir) callable

`alloy_codegen.generate(config, out_dir)` SHALL be the stable
Python entrypoint downstream tools (alloy-cli, future agents,
LSPs) consume.  The function SHALL accept any object exposing
`chip.vendor / chip.family / chip.device` (or, when chip is
``None``, `board.id`), call `load_with_synthesis` to build the
canonical + synthesised IRs, run every registered emitter, and
write the artifacts directly under ``out_dir``.  The return
value SHALL be a sorted ``tuple[Path, ...]`` of the written
files so callers can log them or feed a cache.  Failures SHALL
raise a typed exception (``ConfigError`` for missing /
unresolvable target, ``StageExecutionError`` for parse +
synthesis errors).

#### Scenario: chip-driven config emits the four artifacts

- **WHEN** the caller passes a config with
  `chip.vendor="st"`, `chip.family="stm32g0"`,
  `chip.device="stm32g071rb"` and `out_dir=tmp_path`
- **THEN** ``generate`` SHALL write
  ``peripheral_traits.h``, ``runtime_init.c``,
  ``linker.ld``, and ``vector_table.c`` directly under
  ``tmp_path``
- **AND** the returned tuple SHALL list those four paths in
  sorted order

#### Scenario: board-driven config without resolved chip raises ConfigError

- **WHEN** the config has `chip=None` and
  `board.id="nucleo_g071rb"`
- **THEN** ``generate`` SHALL raise ``ConfigError`` because
  alloy-codegen does NOT host a board catalogue
- **AND** the message SHALL tell the caller to resolve the
  board to a `(vendor, family, device)` triple in their own
  layer before re-invoking

#### Scenario: a config without chip or board raises ConfigError

- **WHEN** the config exposes both `chip=None` and
  `board=None`
- **THEN** ``generate`` SHALL raise
  ``alloy_codegen.errors.ConfigError`` with a message
  naming the missing field

#### Scenario: unknown device raises ConfigError

- **WHEN** the config points at a chip that isn't in
  ``DEVICE_REGISTRY``
- **THEN** ``generate`` SHALL raise ``ConfigError`` listing
  the closest known vendor / family triple
