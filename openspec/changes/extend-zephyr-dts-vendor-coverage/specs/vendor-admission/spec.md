## ADDED Requirements

### Requirement: The Zephyr DTS adapter SHALL cover Renesas, TI, Infineon, Ambiq, and SiLabs vendors

The repository SHALL ship per-vendor compatible-string maps under
`alloy_codegen.sources.zephyr_dts.COMPATIBLE_MAPS` for at least
the five vendors `renesas`, `ti`, `infineon`, `ambiq`, and
`silabs`, plus a registered vendor adapter (via the central
`@register_vendor_adapter(...)` registry) for one pilot family
per vendor: `renesas/ra4`, `ti/cc13x2`, `infineon/xmc4xxx`,
`ambiq/apollo3`, `silabs/efr32`.  Each pilot SHALL admit at least
one device through the standard normalize stage and pass the
runtime-cpp-smoke gate.

#### Scenario: Each new vendor pilot resolves through the registry

- **WHEN** the pipeline resolves
  `("renesas", "ra4")`, `("ti", "cc13x2")`, `("infineon", "xmc4xxx")`,
  `("ambiq", "apollo3")`, or `("silabs", "efr32")`
- **THEN** `resolve_vendor_adapter(...)` SHALL return a
  `VendorAdapter` whose `fetch` and `normalize` callables are
  registered through the central decorator
- **AND** no hard-coded `if vendor == ...` branch SHALL be
  required in pipeline modules

#### Scenario: Pilot devices produce a valid canonical IR via Zephyr DTS

- **WHEN** the pipeline normalizes a pilot device for any of the
  five new vendors
- **THEN** the resulting `CanonicalDeviceIR` SHALL declare the
  device's identity, memories, peripheral instances (extracted
  from the snapshotted DTS), and IRQ vector table
- **AND** `pytest --runtime-cpp-smoke` SHALL compile every
  pilot's emitted runtime headers cleanly with the same
  freestanding clang invocation used for already-admitted
  devices

#### Scenario: No bulk admission past the pilot

- **WHEN** a vendor's compatible map is added but only one
  pilot device is registered
- **THEN** other devices Zephyr supports for that vendor SHALL
  NOT be admitted by this change — bulk admission of the full
  catalog is gated by `add-bulk-admission-flow`
