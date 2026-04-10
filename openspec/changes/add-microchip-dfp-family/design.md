## Context

`alloy-codegen` already proved that the architecture works for ST by combining
`cmsis-svd-data` with `STM32_open_pin_data`. That path is valuable, but it is also a warning:
the CLI and source layer now know about ST-specific auxiliary inputs explicitly. If we keep
adding vendor-specific source knobs, the pipeline will slowly turn into a list of exceptions.

Microchip families come through a different upstream packaging model:
- a Device Family Pack (`.atpack`) is the official upstream bundle
- the pack contains or references ATDF device descriptions
- the pack contains SVD register descriptions
- pack metadata defines family/version identity

This is the right moment to generalize source composition before adding a second vendor with a
different upstream shape.

The existing Alloy codebase also gives us a concrete consumer target: the `same70_xplained`
board and the existing `same70` handwritten HAL. The new vendor path should therefore target a
family that already matters to Alloy rather than a random Microchip family selected only because
it is easy to parse.

## Goals / Non-Goals

Goals:
- Add a first-class DFP-backed vendor ingestion path without forking the pipeline architecture
- Make named source inputs generic so new vendors do not require ad hoc CLI flags
- Normalize Microchip `same70` into the same canonical IR schema used by ST families
- Keep provenance explicit across pack archive, extracted tree, selected ATDF/SVD files, patches,
  and emitted artifacts
- Publish `microchip/same70` artifacts into `alloy-devices` only after semantic closure
- Prove one real Alloy consumer path from published `same70` artifacts

Non-Goals:
- Supporting every Microchip family or every legacy Atmel family in this proposal
- Mining Harmony as a primary source of truth
- Parsing PDFs or hand-maintained pin tables as the first path
- Introducing vendor-specific IR forks
- Making publication succeed with partial connectivity data; draft artifacts are acceptable,
  publishable artifacts are not

## Proposed Architecture

### 1. Generic named-source model

The current source stage needs to evolve from "one primary source plus optional hardcoded
extra roots" into a generic named-source model.

Each supported `(vendor, family)` declares a source bundle made of one or more logical
source IDs. The source product may be a repository checkout, a pack archive plus extracted
tree, or an SDK-delivered metadata bundle. Examples:

- `st/stm32g0`
  - `cmsis-svd-data`
  - `stm32-open-pin-data`

- `microchip/same70`
  - `microchip-dfp-pack`
  - `microchip-dfp-extract`

- `nxp/imxrt1060`
  - `nxp-mcux-soc-svd`
  - `nxp-mcux-sdk`

The pipeline context and CLI must allow users and CI to override source paths by logical
source ID rather than by vendor-specific flags. The exact surface can be CLI flags, config
file, or both, but the contract is:

- source overrides are named
- the names are stable and manifest-visible
- adding a new vendor source does not require adding a new top-level CLI flag

This keeps source composition explicit while preventing CLI sprawl.

### 2. Microchip DFP ingestion

The `microchip_dfp` adapter is responsible for:

1. resolving a DFP input
   - local `.atpack`
   - local extracted pack tree
   - future remote download support through a pack URL or index reference

2. materializing a deterministic extracted tree
   - same pack bytes produce byte-stable extracted content layout
   - manifests record pack identity, revision/hash, extraction output, and selected files

3. selecting device-specific inputs
   - one ATDF for device/package/peripheral topology
   - one SVD for register blocks and interrupt/vector data

The adapter must treat the pack as a real source product, not as a convenience archive. That
means the manifests must record:
- pack identity and version
- source origin
- archive content hash
- extracted tree hash or revision
- selected ATDF and SVD paths for the requested device

### 3. Composite normalization: ATDF + SVD

Microchip support is not "ATDF instead of SVD". It is a composite normalization path:

- ATDF contributes:
  - device identity
  - package variants
  - pins and signals
  - peripheral instances
  - memory regions where present
  - clock/peripheral relationships where present

- SVD contributes:
  - register block structure
  - base addresses
  - interrupt declarations and vector metadata

The normalizer merges these into the existing canonical IR. The merge rules must be explicit
and tested. In particular:

- instance identity must be stable across ATDF and SVD naming
- vendor-specific naming such as `PIOA`, `PMC`, and `XDMAC` must map into existing canonical
  concepts without leaking raw vendor terms into emitters
- every normalized fact keeps provenance back to source ID and source path

### 4. Vendor namespace and device registry

The canonical vendor key for this path SHALL be `microchip`.

`Atmel` remains important historically and appears in upstream file names and legacy SVD
trees, but it must not create a second vendor namespace in Alloy. The registry therefore uses:

- `vendor = "microchip"`
- `family = "same70"`

Provenance and alias mapping may record that upstream paths came from `Atmel/*` or legacy
tool naming, but publication and IR identity remain under `microchip/same70`.

### 5. Family bootstrap strategy

This proposal uses `same70` because it already matters to Alloy and has an existing board and
HAL surface. The bootstrap must include:

- one board-target `same70` device matching the current Alloy board support for
  `same70_xplained`
- one second `same70` package variant from the same DFP to prove package-sensitive
  normalization and validation

The exact two device names must be chosen from the DFP catalog during implementation and
committed to the device registry. One must be the Alloy board target; the second must differ
in package or package-related pin topology.

### 6. Patch strategy

Patches remain the only place for reviewed data correction. Microchip support must not hide
repairs in emitters or ad hoc normalizer branches.

Expected patch layers:
- `patches/microchip/same70/family.json`
- `patches/microchip/same70/devices/<device>.json`

Patches may:
- add missing semantic links when the DFP is incomplete
- canonicalize ambiguous vendor naming
- refine package identity or pin metadata
- supplement DMA/clock metadata if the DFP leaves gaps

Patches may not:
- replace the DFP as the primary source of truth
- silently override register layout data that belongs in SVD
- introduce emitter-only semantics

### 7. Validation and admission gates

Microchip support should not be admitted just because ATDF parses. The family needs its own
admission gates that sit on top of the generic foundation gates.

#### Gate M1: DFP source admission

Before normalization is considered real:
- at least two representative `same70` devices are fetched from a DFP input reproducibly
- the pack archive and extracted tree both produce deterministic manifests
- the adapter selects ATDF and SVD files deterministically for each device
- rerunning `fetch + extract` with the same pack revision produces byte-stable manifests

#### Gate M2: Composite IR closure

Before draft artifact emission:
- the selected `same70` devices normalize fully into the existing canonical IR schema
- no Microchip-specific opaque blobs remain for package, pins, signals, peripheral instances,
  memory, or interrupts
- the IR schema version is unchanged unless a true schema change is approved separately
- all normalized fields carry provenance to `microchip-dfp-pack` or `microchip-dfp-extract`

#### Gate M3: Semantic closure

Before publication:
- package and pin connectivity validate without critical conflicts
- peripheral instance ownership validates against family clock/enable data
- interrupt data from SVD and family topology data agree without critical conflicts
- DMA semantics are either fully modeled and validated for the publication scope, or
  publication remains blocked until a reviewed source or patch closes that gap
- the board-target `same70` device and one second package variant both pass the semantic suite

This gate is intentionally strict. If XDMAC or clock ownership cannot be closed from DFP plus
reviewed patches, `same70` remains a draft family and does not publish.

#### Gate M4: Publication readiness

Before `microchip/same70` is treated as a supported published family:
- the family emits the same artifact contract used by ST families
- artifacts publish into the real `alloy-devices` repository under `microchip/same70`
- at least one Alloy consumer path builds from published artifacts only
- two repeated publication runs are byte-stable and no-op when inputs do not change

### 8. Alloy consumer path

This change should not stop at "the JSON looks good". The first published `same70` path must
prove consumption from Alloy.

Minimum acceptance:
- one clean consumer compile path in Alloy for the board-target `same70` device
- the build uses published `alloy-devices` artifacts only
- no local codegen fallback is required

This can be a smoke compile at first, but it must use the same published artifact layout that
future production builds will use.

## Decisions

### Decision 1: `microchip` is the canonical vendor key

Why:
- the official upstream packaging is now under Microchip
- `Atmel` still appears in historical source names and SVD trees, but keeping both as peer
  vendor keys would fork the namespace unnecessarily

Alternative considered:
- use `atmel` as vendor key for legacy continuity
  Rejected because it does not match the current official upstream and would make future
  Microchip families inconsistent.

### Decision 2: DFP is the primary source product

Why:
- it is the official structured source bundle that already contains ATDF and SVD
- it gives a better provenance boundary than scraping multiple unrelated repositories

Alternative considered:
- use Harmony as primary source and SVD as secondary
  Rejected because Harmony is better as cross-check or example material, not as the canonical
  device-data base.

### Decision 3: generic named-source overrides, not new special CLI flags

Why:
- the ST bootstrap already showed how quickly source-specific flags become design debt
- Microchip will not be the last vendor with composite sources

Alternative considered:
- add `--dfp-source-root` and keep `--pin-source-root`
  Rejected because it scales linearly with vendors and keeps source architecture implicit.

### Decision 4: publish only after DMA/clock closure

Why:
- incomplete connectivity-critical data is exactly how generated HALs become misleading
- draft normalization is useful, but published support claims must mean something

Alternative considered:
- publish with known TODOs for XDMAC or PMC semantics
  Rejected because it would lower the meaning of a published family.

## Risks / Trade-offs

- **Risk: DFP structure differs across Microchip families**
  Mitigation: keep `microchip_dfp` adapter generic at the pack layer and isolate
  `same70`-specific semantics to normalizers and patches

- **Risk: ATDF and SVD names do not align cleanly**
  Mitigation: make alias/canonicalization tables explicit, tested, and provenance-visible

- **Risk: DFP may not expose enough DMA or clock-routing semantics**
  Mitigation: treat missing semantics as a gate failure for publication, not as a silent
  approximation

- **Risk: generic source override refactor destabilizes ST flows**
  Mitigation: add regression coverage for existing ST families and allow a temporary
  deprecation bridge for old flags during migration

- **Risk: vendor namespace migration becomes confusing because legacy files say Atmel**
  Mitigation: record upstream vendor labels in provenance and manifests while keeping the
  canonical publication namespace fixed to `microchip`

## Migration Plan

### Phase 0: source model generalization
- define named source bundles and source override plumbing
- deprecate vendor-specific auxiliary source flags
- register `microchip/same70` in the device registry

### Phase 1: DFP source bootstrap
- implement `microchip_dfp` source adapter
- add deterministic extraction and manifests
- add fixture packs or extracted fixture subsets for two `same70` devices
- close Gate M1

### Phase 2: composite normalization
- parse ATDF + SVD into the canonical IR
- add family/device patch catalogs
- add canonical golden fixtures for two `same70` devices
- close Gate M2

### Phase 3: semantic closure
- validate pin/package/peripheral/clock/IRQ semantics
- model and validate DMA semantics required for publication
- close Gate M3

### Phase 4: artifact publication and Alloy consumption
- emit/publish `microchip/same70` artifacts
- prove one Alloy consumer path from published artifacts
- close Gate M4

## Open Questions

- Should `microchip_dfp` optionally accept a `.pdsc` index plus pack cache root in the first
  implementation, or should the first milestone support only direct `.atpack` and extracted
  tree inputs?
- If `same70` DFP data is insufficient for XDMAC closure, should the second approved source be
  a curated reviewed metadata file inside Alloy-owned patches, or a separate structured vendor
  source adapter?
