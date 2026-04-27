## ADDED Requirements

### Requirement: Vendor adapters SHALL register themselves through a central registry

The pipeline SHALL resolve vendor/family adapters through a central
registry exposed by `alloy_codegen.vendors.registry` rather than
through hard-coded `if vendor == ...` cascades.  Each adapter module
SHALL register itself at import time using the
`@register_vendor_adapter(vendor, family)` decorator.  Pipeline
stages (`stages.fetch`, `stages.normalize`) SHALL call
`resolve_vendor_adapter(vendor, family)` to look up the adapter.

#### Scenario: All admitted families resolve to a registered adapter

- **WHEN** the pipeline runs for any currently admitted
  `(vendor, family)` (e.g. `("st", "stm32g0")`,
  `("microchip", "same70")`, `("espressif", "esp32c3")`)
- **THEN** `resolve_vendor_adapter(vendor, family)` SHALL return
  the registered adapter without touching `stages/normalize.py`
  source code

#### Scenario: Unknown vendor/family raises a discoverable error

- **WHEN** `resolve_vendor_adapter("foo", "bar")` is called and
  no adapter is registered for that pair
- **THEN** the call SHALL raise `StageExecutionError`
- **AND** the error message SHALL list the set of registered
  `(vendor, family)` pairs so a developer sees what is admitted
