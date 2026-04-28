# vendor-admission Specification

## Purpose

Define the policy that governs when a vendor or family is admitted into the supported
multi-vendor publication set.
## Requirements
### Requirement: Foundational vendor set is explicit

The admitted foundational vendor/family set MUST be explicitly documented.

#### Scenario: Foundational vendors are listed

- **WHEN** maintainers review current admission status
- **THEN** the admitted vendor/family set is explicit and includes: ST/stm32g0, ST/stm32f4,
  Microchip/same70, Microchip/avr-da, NXP/imxrt1060, Espressif/esp32c3, Espressif/esp32s3,
  and Espressif/esp32
- **AND** the source pattern used by each foundational family is documented
- **AND** the ISA family (Cortex-M, RISC-V, Xtensa LX6, Xtensa LX7, AVR8) and memory
  model (unified vs Harvard) are documented alongside each entry
- **AND** the multi-core posture (single-core vs dual-core control plane) is
  documented for every multi-core family

### Requirement: New vendor admission is gated

A new vendor beyond the admitted foundational set MUST NOT enter active implementation until
readiness gates are closed and an admission proposal exists.

#### Scenario: Admission checks bootstrap readiness

- **WHEN** a new vendor or family is considered publishable
- **THEN** Gates T7, T8, and T9 are closed
- **AND** no foundational family requires final-stage emitter or publish exceptions
- **AND** a completed vendor-admission proposal exists in `openspec/changes/`

### Requirement: CI enforces the admitted vendor set

The CI workflow MUST fail if unadmitted vendor directories appear in `patches/`.

#### Scenario: Unadmitted vendor directories are blocked

- **WHEN** the quality workflow scans `patches/`
- **THEN** any vendor directory outside the admitted set fails the build

### Requirement: Vendor admission proposals are complete

A proposal to admit a new vendor MUST answer the bootstrap and source questions needed to make
the vendor publishable and maintainable.

#### Scenario: Admission proposal covers the full checklist

- **WHEN** a new vendor-admission proposal is reviewed
- **THEN** it identifies vendor key, bootstrap family, source pattern, bootstrap devices,
  fixture plan, licensing notes, and gate plan

### Requirement: Additional families from admitted vendors are still gated

Admitted vendors MUST satisfy bootstrap stability and proposal requirements before adding new
families.

#### Scenario: Existing vendor expands to a new family

- **WHEN** an already admitted vendor adds another family
- **THEN** the bootstrap family has completed at least two stable publication cycles
- **AND** no outstanding CI exceptions exist for that vendor
- **AND** a proposal exists naming the new family, its devices, and its fixture plan

### Requirement: New vendor admission requires semantic and provenance readiness

Vendor/family admission MUST not be judged only by parser success or low-level artifact emission.

#### Scenario: Admission checks semantic readiness

- **WHEN** a new vendor or family is considered publishable
- **THEN** admission evaluates system-control coverage, capability coverage, and provenance quality
- **AND** the family is not considered foundational-ready if those remain heuristic or opaque

### Requirement: Vendor Admission SHALL Require Zero-String Runtime Reuse

A new family or vendor SHALL only be admitted when it reuses or extends the fully typed
zero-string runtime contract.

#### Scenario: New family reuses existing typed schemas
- **WHEN** a new family maps onto existing fully typed runtime schemas
- **THEN** vendor admission succeeds without requiring semantic string fields in runtime C++

#### Scenario: New family needs semantic labels in runtime C++
- **WHEN** a candidate family can only be represented by adding schema names, signal names,
  route kinds, or similar semantic strings to runtime-facing headers
- **THEN** vendor admission fails until those semantics are modeled as typed ids or refs

### Requirement: Vendor Admission SHALL Depend On Runtime-Lite Reuse

A new vendor or family SHALL NOT be considered admission-ready unless it reuses the runtime-lite
contract expected by foundational drivers, without requiring a new reflection-table hot path in
`alloy`.

#### Scenario: New family needs custom table-walk runtime glue

- **WHEN** a new family can only be consumed through handwritten reflection-table lookup in the
  runtime
- **THEN** vendor admission fails until codegen emits a compatible runtime-lite contract

### Requirement: Vendor breadth is staged by quality, not just count

Coverage expansion MUST prioritize quality-complete vendor support over raw vendor-count growth.

#### Scenario: New coverage waves respect admission quality
- **WHEN** a peripheral class is expanded to additional vendors
- **THEN** each admitted vendor/family meets the same runtime-contract and validation expectations
- **AND** "partial but opaque" coverage is not treated as equivalent to complete support

### Requirement: Vendor Admission SHALL Depend on Typed Schema Reuse

Admission of a new family or vendor SHALL require either reuse of an already published typed
runtime backend schema or the introduction of a new localized schema contract that avoids
family-name parsing in Alloy.

#### Scenario: New family reuses an existing runtime schema
- **WHEN** a candidate family maps to already published runtime backend schemas
- **THEN** vendor admission succeeds without requiring Alloy runtime changes outside schema
  dispatch tables

#### Scenario: New family requires family-specific runtime parsing
- **WHEN** a candidate family can only be consumed by adding family-name checks or string
  parsing in Alloy
- **THEN** vendor admission fails until the contract is expressed as typed schema descriptors

### Requirement: Raspberry Pi RP2040 is admitted as a Cortex-M0+ target

The pipeline MUST support the Raspberry Pi RP2040 as a first-class vendor target using
the pico-sdk SVD as canonical source and `alloy.pinmux.rp2040-funcsel-v1` as pinmux schema.

#### Scenario: RP2040 is a supported bootstrap family

- **WHEN** the pipeline runs for vendor `raspberrypi`, family `rp2040`
- **THEN** it fetches device data from `github.com/raspberrypi/pico-sdk`
- **AND** it produces a valid `CanonicalDeviceIR` using Cortex-M0+ normalization paths
- **AND** it emits the full standard runtime C++ artifact set passing all contract gates

#### Scenario: RP2040 dual-core is documented as single-core-perspective

- **WHEN** the RP2040 device IR is normalized
- **THEN** `core` is recorded as `"cortex-m0plus-dual"` in device metadata
- **AND** the emitted `startup.cpp` contains an explicit generated comment stating that
  core 1 is not started in this first cut
- **AND** no CI gate fails due to the dual-core topology being partially modeled

#### Scenario: Raspberry Pi vendor is admitted in CI gate

- **WHEN** the CI admission check scans `patches/`
- **THEN** `patches/raspberrypi/` is recognized as admitted and does not fail the build

### Requirement: FUNCSEL pinmux routing is modeled as a named backend schema

The RP2040's FUNCSEL pin routing MUST be modeled as a distinct backend schema rather than
as a transparent extension of the ARM alternate-function model.

#### Scenario: FUNCSEL signals carry a distinguishing schema ID

- **WHEN** an RP2040 peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` is `alloy.pinmux.rp2040-funcsel-v1`
- **AND** pin signal `af_number` values represent FUNCSEL indices (0–9) from the RP2040
  datasheet GPIO function table
- **AND** consumers that check `backend_schema_id` before interpreting `af_number` see a
  distinct identifier and apply FUNCSEL routing logic instead of ARM AF logic

#### Scenario: Existing ARM backends are unaffected

- **WHEN** an ST or NXP peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` remains `alloy.pinmux.stm32-af-v1` or
  `alloy.pinmux.imxrt-iomuxc-v1` respectively
- **AND** no FUNCSEL logic is applied to those pin signal entries

### Requirement: Vendor Admission Requires Typed Runtime Contract Reuse
New foundational-family admission SHALL require reuse of the typed runtime-ref domains and
typed runtime header contract, unless a localized new schema is explicitly added and validated.

#### Scenario: New family attempts to publish with string glue
- **WHEN** a new family or vendor publishes foundational runtime artifacts
- **THEN** vendor admission fails if it depends on raw signal strings or CSV payloads as
  primary runtime contract

### Requirement: Espressif ESP32 families are admitted as non-ARM targets

The pipeline MUST support Espressif ESP32 families as first-class non-ARM vendor targets, starting
with ESP32-C3 (RISC-V RV32IMC) as the bootstrap family.

#### Scenario: ESP32-C3 is a supported bootstrap family

- **WHEN** the pipeline runs for vendor `espressif`, family `esp32c3`
- **THEN** it fetches device data from the Espressif SVD repository
- **AND** it produces a valid `CanonicalDeviceIR` without ARM-specific fallbacks
- **AND** it emits runtime C++ headers that pass the artifact contract checks

#### Scenario: ESP32-S3 is admitted after ESP32-C3 stabilizes

- **WHEN** the ESP32-C3 bootstrap family has completed at least one stable publication cycle
- **THEN** `esp32s3` (Xtensa LX7) may be added to the registry
- **AND** a proposal exists naming the new family, its Xtensa-specific requirements, and its
  fixture plan
- **AND** the proposal documents whether the first admitted model is single-core-perspective
  only or full multi-core aware

#### Scenario: Espressif vendor is admitted in CI gate

- **WHEN** the CI admission check scans `patches/`
- **THEN** `patches/espressif/` is recognized as admitted and does not fail the build

### Requirement: IO Matrix routing is modeled as a documented vendor-specific backend schema

ESP32's fully-programmable GPIO IO Matrix MUST be modeled as a named backend schema rather than
as an extension of the ARM alternate-function model.

#### Scenario: IO Matrix signals carry a distinguishing schema ID

- **WHEN** an Espressif peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` is `alloy.pinmux.espressif-iomatrix-v1`
- **AND** pin signal `af_number` values represent IO Matrix signal indices from
  Espressif's `gpio_sig_map.h`
- **AND** consumers that check `backend_schema_id` before interpreting `af_number` see a
  distinct identifier and apply IO Matrix routing logic instead of ARM AF logic

#### Scenario: IO Matrix supplementary data is explicitly admitted

- **WHEN** Espressif IO Matrix routing is used in normalization
- **THEN** the admitted source set includes the supplementary routing data source
- **AND** maintainers can identify its upstream repository, revision, and license

#### Scenario: Existing ARM backends are unaffected

- **WHEN** an ST or NXP peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` remains `alloy.pinmux.stm32-af-v1` or
  `alloy.pinmux.imxrt-iomuxc-v1` respectively
- **AND** no IO Matrix logic is applied to ARM pin signal entries

### Requirement: Microchip AVR-DA family is admitted as an 8-bit Harvard target

The pipeline MUST support the Microchip AVR-DA family (`AVR128DA32` as bootstrap device)
as the first 8-bit Harvard architecture target.

#### Scenario: AVR128DA32 is a supported bootstrap device

- **WHEN** the pipeline runs for vendor `microchip`, family `avr-da`
- **THEN** it fetches device data from the Microchip AVR-Dx DFP pack via
  `packs.download.microchip.com`
- **AND** it produces a valid `CanonicalDeviceIR` with Harvard address space annotations
  on memory regions
- **AND** it emits runtime C++ headers that pass the artifact contract checks

#### Scenario: AVR-DA is recognized as an admitted Microchip family in CI

- **WHEN** the CI admission check scans `patches/`
- **THEN** `patches/microchip/avr-da/` is recognized as admitted and does not fail the build
- **AND** `patches/microchip/same70/` continues to pass unchanged

### Requirement: AVR PORTMUX routing is modeled as a documented vendor-specific backend schema

AVR-DA's `PORTMUX`-based alternate pin assignments MUST be modeled as a named backend schema
distinct from ARM alternate-function and ESP32 IO Matrix schemas.

#### Scenario: PORTMUX signals carry a distinguishing schema ID

- **WHEN** a Microchip AVR-DA peripheral instance is present in canonical IR
- **THEN** its `backend_schema_id` is `alloy.pinmux.avr-portmux-v1`
- **AND** pin signal `af_number` values encode the PORTMUX selection index:
  `0` for the default pin assignment, `1` for the first alternate, `2` for the second
- **AND** consumers that check `backend_schema_id` apply PORTMUX logic
  instead of ARM AF or ESP32 IO Matrix logic

#### Scenario: Existing ARM and ESP32 backends are unaffected

- **WHEN** an ST, NXP, or Espressif peripheral instance is processed
- **THEN** its `backend_schema_id` remains unchanged
- **AND** no PORTMUX logic is applied to non-AVR pin signal entries

### Requirement: Espressif ESP32 classic family is admitted as a dual-core LX6 target

The pipeline MUST support the Espressif ESP32 classic family (dual-core
Xtensa LX6) as a first-class target, sharing the existing `espressif-svd`
source adapter and the dual-core Xtensa runtime contract. ESP32 classic
admission MUST additionally surface the dual-core control plane facts
(topology, core count, secondary-core release register) in the published
artifacts so downstream consumers can reason about cores from data alone.

#### Scenario: ESP32 classic is a supported family

- **WHEN** the pipeline runs for vendor `espressif`, family `esp32`
- **THEN** it fetches `esp32.svd` via the existing `espressif-svd` adapter
  without requiring a new source adapter
- **AND** it produces a valid `CanonicalDeviceIR` for both `esp32` (QFN48)
  and `esp32-wroom32` (module) device variants
- **AND** the canonical IR has `multicore_topology =
  xtensa_asymmetric_dual_core`, `core_count = 2`, and a populated
  `app_cpu_control_plane`
- **AND** it emits runtime C++ headers that pass the architecture-scoped
  artifact contract

#### Scenario: ESP32 classic admission publishes multicore facts in artefacts

- **WHEN** the pipeline emits the published artefact bundle for an admitted
  ESP32 classic device
- **THEN** `capabilities.json` carries
  `device:multicore-topology = "xtensa-dual-core"`,
  `device:core-count = 2`, and
  `device:secondary-core-release-register = "register_dport_appcpu_ctrl_b"`
- **AND** `system_sequences.hpp` ends `default_bringup` with a
  `secondary_core_release` step referencing the typed release register
- **AND** `registers.hpp` emits `register_dport_appcpu_ctrl_b` with
  `role = secondary_core_release`
- **AND** these facts are sufficient for a descriptor-only consumer to
  decide that the device is dual-core and which register releases the
  secondary core

#### Scenario: ESP32 classic admits two packages sharing one family catalog

- **WHEN** the bootstrap registers `espressif/esp32`
- **THEN** the family catalog `patches/espressif/esp32/family.json` is
  shared by every device variant
- **AND** at least two device patches exist: `esp32.json` for QFN48 and
  `esp32-wroom32.json` for the WROOM-32 module
- **AND** the family catalog carries a `multicore_topology` block declaring
  `topology = "xtensa-asymmetric-dual-core"`, `core_count = 2`, and the
  `app_cpu_control_plane` register reference
- **AND** ESP32-PICO-D4 and ESP32-WROVER are explicitly NOT admitted in
  the original admission change (this change does not relax that)

#### Scenario: ESP32-S3 admission also publishes multicore facts

- **WHEN** the pipeline emits the published artefact bundle for an admitted
  ESP32-S3 device
- **THEN** `capabilities.json` carries
  `device:multicore-topology = "xtensa-dual-core"` and
  `device:core-count = 2`
- **AND** `device:secondary-core-release-register` references both
  `register_system_core_1_control_0` and
  `register_system_core_1_control_1`
- **AND** the artefacts otherwise match the ESP32 classic shape (step kind,
  register role tag)

### Requirement: Publish CI computes affected families per push

The publish workflow SHALL compute, before launching the per-family matrix,
the subset of admitted families whose inputs the current commit actually
affects.  Only those families' publish jobs run; the remaining families are
skipped without consuming CI compute.

The detection is path-based on the git diff between the workflow's "since"
ref and HEAD.  An override exists for forcing the full matrix.

#### Scenario: Single-family patch only re-publishes that family

- **WHEN** a commit touches **only** files under `patches/<vendor>/<family>/**`
  for one admitted pair
- **AND** the publish workflow runs (either via `workflow_run` from Bootstrap CI
  or `workflow_dispatch` without `force_all`)
- **THEN** the `detect-affected` job's matrix output contains exactly one entry
  `{vendor: <vendor>, family: <family>}`
- **AND** the publish job runs that single matrix job
- **AND** no other admitted family runs its publish job for this commit

#### Scenario: Source-adapter change scopes to that adapter's families

- **WHEN** a commit touches `src/alloy_codegen/sources/<basename>.py` and no
  other src files
- **THEN** the matrix output contains every `(vendor, family)` pair whose
  `SOURCE_BUNDLES` entry includes that adapter's source ID, and no others

#### Scenario: Architecture-specific runtime emitter scopes to that ISA

- **WHEN** a commit touches `src/alloy_codegen/runtime_xtensa_startup.py`
- **THEN** the matrix output is restricted to families whose `core` starts with
  `xtensa` (esp32, esp32s3) and excludes Cortex-M / RISC-V / AVR families
- **AND** analogous scoping holds for `runtime_riscv_startup.py`,
  `runtime_avr_startup.py`, and `runtime_startup.py` (Cortex-M)

#### Scenario: Docs-only and openspec-only changes skip the publish entirely

- **WHEN** a commit touches **only** files under `tests/**`, `openspec/**`,
  `*.md`, or `.github/workflows/bootstrap-family.yml`
- **THEN** the `detect-affected` job sets `should_publish=false` and the
  publish job does NOT run
- **AND** Bootstrap Family CI on the same commit still runs (those workflows
  are independent)

#### Scenario: Unknown-path changes fall back to the full matrix

- **WHEN** a commit touches a path the affected-families heuristic does not
  explicitly map (e.g., a new top-level config file, or a rename that the
  mapping has not yet learned)
- **THEN** the matrix output is the full admitted set
- **AND** the rationale "unknown path triggered conservative full-rebuild" is
  visible in the job log

#### Scenario: Manual `force_all` override bypasses detection

- **WHEN** the publish workflow is triggered via `workflow_dispatch` with
  `force_all: true`
- **THEN** `detect-affected` skips the git diff and emits the full matrix
- **AND** every admitted family runs its publish job regardless of what
  changed (or did not change) since the last commit

#### Scenario: Diff failure is treated as full matrix (safe default)

- **WHEN** the `git diff --name-only <since>...<head>` command fails (e.g.,
  shallow clone without enough history, missing ref)
- **THEN** the affected-families CLI returns `all_families: true` and a log
  line records the failure cause
- **AND** the matrix output is the full admitted set

### Requirement: Device patches MUST be generatable from SVD + CMSIS-Pack sources

The repository SHALL ship `scripts/autogen_device_patches.py`, a
deterministic CLI that emits a draft `patches/<vendor>/<family>/devices/<device>.json`
from a CMSIS-SVD file (and optionally a CMSIS-Pack PDSC) with
the mechanical 80% of fields populated: device identity, package
candidates, core, memory map, peripheral instance list, IRQ
vector table, basic RCC bindings discoverable from the SVD.
Fields the generator cannot derive SHALL be emitted as
`"// TODO review"` placeholders so a reviewer sees exactly what
is unfinished.  The generator MUST be deterministic — re-running
on the same inputs SHALL produce byte-identical output.

#### Scenario: Generator reproduces ≥80% of a hand-curated patch

- **WHEN** `python -m scripts.autogen_device_patches --vendor st
  --family stm32g0 --device stm32g071rb --svd <STM32G071xx.svd>`
  is run
- **THEN** the emitted JSON SHALL match the existing
  `patches/st/stm32g0/devices/stm32g071rb.json` for memory regions,
  peripheral instance names + base addresses, and the IRQ vector
  table
- **AND** any hand-curated override fields the generator cannot
  derive SHALL be emitted as `"// TODO review"` placeholders

#### Scenario: Generator output is deterministic

- **WHEN** the generator is run twice on the same inputs
- **THEN** both runs SHALL emit byte-identical output
- **AND** the field ordering SHALL be stable so diffs vs. the
  prior draft are minimal

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

### Requirement: The repository SHALL ship a known-devices index imported from probe-rs

The repository SHALL ship `data/known_devices.toml`, a
canonical catalog of admittable MCUs imported from the
`probe-rs/probe-rs` project's `targets/*.yaml`.  Each entry SHALL
record the canonical `(vendor, family, device)` identity, the
probe-rs target name, the core, the memory map, and a flash
algorithm reference.  The catalog SHALL be regenerated by
`tools/import_probe_rs_targets.py` from a probe-rs checkout
pinned to a specific commit SHA recorded in
`data/known_devices.meta.toml`.  The catalog is read-only with
respect to the pipeline — alloy patches MUST continue to be the
source of truth on conflict; the catalog provides discoverability
and admission scaffolding only.

#### Scenario: Every admitted device resolves to a known-devices entry

- **WHEN** the test suite enumerates every device the alloy
  pipeline admits today
- **THEN** every `(vendor, family, device)` triple SHALL resolve
  to an entry in `data/known_devices.toml`
- **AND** any deliberate exception SHALL be recorded in an
  explicit allow-list in the test, with a comment explaining why

#### Scenario: Importer output is byte-stable

- **WHEN** `tools/import_probe_rs_targets.py` is run twice
  against the same pinned probe-rs commit SHA
- **THEN** both runs SHALL produce byte-identical
  `data/known_devices.toml`
- **AND** the entries SHALL be sorted by `(vendor, family, device)`

#### Scenario: Catalog does not override patches

- **WHEN** a device's hand-curated patch JSON disagrees with the
  catalog (e.g. on memory map)
- **THEN** the pipeline SHALL still use the patch value — the
  catalog SHALL NOT be loaded as a source of truth for emission

### Requirement: The pipeline SHALL ingest Zephyr DTS as a vendor source adapter

The pipeline SHALL ship `src/alloy_codegen/sources/zephyr_dts.py`,
a vendor source adapter that consumes a Zephyr checkout and
produces the same intermediate objects (peripherals, interrupts,
clocks, dma_requests, pins, signals, connection_candidates) that
existing adapters emit.  The adapter SHALL use Zephyr's own
`edtlib` to fully resolve `.dts` + `.dtsi` overlays rather than
parsing DTS by hand.  The adapter SHALL register itself through
the central vendor-adapter registry, not through a hard-coded
`if vendor == ...` branch in pipeline modules.

#### Scenario: nRF52 device admitted via Zephyr DTS produces a valid canonical IR

- **WHEN** the pipeline runs for a Nordic nRF52 device whose
  fixture points at a snapshotted Zephyr DTS tree
- **THEN** the adapter SHALL produce a canonical IR with
  peripheral instances, IRQ numbers, clock parents (best-effort),
  and pinctrl-derived connection candidates
- **AND** the IR SHALL pass the standard validation stage without
  vendor-specific exceptions

#### Scenario: Unsupported compatible strings do not crash the adapter

- **WHEN** the adapter encounters a DTS node whose `compatible`
  string is not in its vendor mapping table
- **THEN** the adapter SHALL log the skip and continue
- **AND** it SHALL NOT raise — DTS is intentionally permissive
  about new compatibles

#### Scenario: Adapter registers through the vendor registry

- **WHEN** the adapter module is imported
- **THEN** it SHALL register itself via
  `@register_vendor_adapter(vendor, family)` for each Zephyr
  family it covers
- **AND** the pipeline's normalize/fetch stages SHALL resolve the
  adapter through `resolve_vendor_adapter(...)` rather than a
  hard-coded branch

### Requirement: The pipeline SHALL ingest modm-devices XML as an enrichment source for STM32

The pipeline SHALL ship `src/alloy_codegen/sources/modm_devices.py`,
an adapter that consumes
`modm-devices/devices/stm32/<family>/<part>.xml` and produces the
same intermediate objects as the existing STM32 source pipeline
(peripherals, interrupts, dma_requests, connection_candidates,
clock graph edges).  The adapter SHALL register through the
central vendor-adapter registry alongside the existing CMSIS-SVD
adapter.  The pipeline SHALL apply merge precedence
`cmsis-svd < stm32-open-pin-data < modm-devices < family-patch <
device-patch` so modm fills gaps left by open sources but defers
to hand-curated overrides.  The integration SHALL pin against a
specific modm-devices checkout SHA recorded in
`data/source_pins.toml`.

#### Scenario: modm fills clock-tree edges absent from CMSIS-SVD

- **WHEN** the pipeline normalizes an STM32G0 device
- **AND** CMSIS-SVD does not carry clock-tree edges for the RCC
  controller
- **THEN** the resolved IR SHALL include the clock graph edges
  imported from `modm-devices/devices/stm32/g0/<part>.xml`
- **AND** the per-edge provenance SHALL identify modm-devices as
  the contributing source

#### Scenario: Hand-curated patch overrides modm data

- **WHEN** a device patch sets a field that modm also sets, with
  a different value
- **THEN** the resolved IR SHALL use the patch value
- **AND** the per-field provenance SHALL still record modm as the
  precedence-1 source so the override is auditable

#### Scenario: Stale modm-devices SHA blocks the load by default

- **WHEN** the modm-devices checkout SHA does not match the pin
  recorded in `data/source_pins.toml`
- **THEN** the fetch stage SHALL fail with a message identifying
  the drift
- **AND** the failure SHALL be overridable with an explicit
  `--accept-stale-sources` flag for review workflows

### Requirement: alloy-codegen SHALL consume canonical device data from a separate alloy-devices-yml repository

The repository SHALL ship a git submodule at `data/devices/`
pointing at the standalone `alloy-devices-yml` repository at a
pinned SHA recorded in `.gitmodules`.  The pipeline SHALL
short-circuit the normalize stage when a device's canonical
YAML exists in the submodule: the YAML is parsed via
`alloy_codegen.sources.alloy_devices_yml.load_canonical_device(...)`
and the resulting `CanonicalDeviceIR` flows directly into
validation + emission, bypassing the legacy SVD + patch path.
When the YAML is absent the legacy path SHALL still run, so
families that have not yet been migrated continue working
unchanged.  The emitted artifacts MUST be byte-identical
regardless of which path produced the IR.

#### Scenario: Admitted devices resolve via the submodule when YAML is present

- **WHEN** the pipeline runs for any of the 17 admitted
  devices after this change lands
- **AND** `data/devices/vendors/<vendor>/<family>/devices/<device>.yml`
  exists in the submodule
- **THEN** the normalize stage SHALL load the IR from that
  file
- **AND** the emitted artifacts SHALL be byte-identical to
  the artifacts produced by the legacy SVD + patch path

#### Scenario: Devices without YAML fall through to the legacy path

- **WHEN** the pipeline runs for a device whose canonical
  YAML is not yet committed to the submodule
- **THEN** the legacy adapter (CMSIS-SVD, ATDF, Zephyr DTS,
  …) SHALL be used as today
- **AND** the resulting IR + artifacts SHALL be unchanged
  from before this change

#### Scenario: Submodule bumps run the parity gate

- **WHEN** `tools/bump_devices_yml.py` updates the submodule
  to a new SHA
- **THEN** the tool SHALL rerun `pytest -q` and
  `pytest --runtime-cpp-smoke`
- **AND** SHALL report any per-device IR drift between the
  pre-bump and post-bump emissions
- **AND** SHALL refuse to commit the bump if the drift would
  produce non-trivial C++ artifact changes without explicit
  reviewer override

### Requirement: Vendor extraction logic SHALL live in a separate alloy-data-extractor repository

The repository ecosystem SHALL split vendor source extraction
into a standalone `alloy-data-extractor` repository — every
vendor parser (CMSIS-SVD, ATDF, MCUXpresso, ESP-IDF, Zephyr
DTS, modm-data, Pico SDK, datasheet PDF scraping, …) lives
there rather than inside alloy-codegen.  alloy-codegen SHALL
consume the canonical YAML
output produced by the extractor (via `alloy-devices-yml`)
rather than parsing vendor sources directly.  Adding a new
vendor SHALL be a one-PR change in alloy-data-extractor — a
new extractor module under
`src/alloy_data_extractor/extractors/<vendor>.py` plus an
entry in the source-pins manifest — with no edits required to
alloy-codegen.  The two repos communicate exclusively through
the schema-validated YAML format defined by
`define-canonical-device-yaml-schema`.

#### Scenario: alloy-codegen no longer imports vendor-specific source parsers

- **WHEN** alloy-codegen is built and tested after this change
  lands
- **THEN** `src/alloy_codegen/sources/` SHALL no longer contain
  bespoke vendor parsers (cmsis-svd, atdf, mcuxpresso, …)
- **AND** the only `sources/` module SHALL be
  `alloy_devices_yml.py` (the YAML consumer)

#### Scenario: Adding a new vendor is a single-repo change

- **WHEN** a contributor adds support for a new vendor (e.g.
  GigaDevice GD32)
- **THEN** the contribution SHALL touch only
  alloy-data-extractor: one new
  `extractors/gd32.py` + a `data/source_pins.toml` entry
- **AND** the extractor's CI SHALL produce YAML files that
  alloy-codegen consumes without further changes
- **AND** alloy-codegen SHALL emit C++ artifacts for the new
  vendor as soon as it bumps its `alloy-devices-yml`
  submodule pin

#### Scenario: Cross-language consumers reuse the same data

- **WHEN** a future `alloy-codegen-rust` or similar
  language-specific generator is added
- **THEN** it SHALL consume the same alloy-devices-yml data
- **AND** SHALL NOT need to ship its own vendor extractors
- **AND** SHALL pin to the same alloy-devices-yml SHA model
  alloy-codegen uses

