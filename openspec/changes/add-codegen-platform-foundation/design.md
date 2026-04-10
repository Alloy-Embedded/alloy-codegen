## Context

`alloy-codegen` is being started from zero specifically to avoid dragging generator debt
from the previous repository structure. The main requirement is architectural discipline:
the repository must be able to ingest inconsistent upstream sources, apply explicit fixes,
produce a canonical device model, validate that model, and only then emit artifacts.

The design is inspired by several strong ideas from existing ecosystems:
- `modm-data`: heavy upstream ingestion and provenance awareness
- `modm-devices`: separating device data from framework code
- `stm32-data`: normalized device metadata and IP-version-aware modeling
- `chiptool`: intermediate representation before emission
- `svdtools`: reproducible declarative patches

But Alloy must own the implementation, schema, and contracts.

## Goals / Non-Goals

- **Goals**:
  - Build a clean codegen architecture from scratch
  - Make normalized data the core product, not a side effect of header generation
  - Keep vendor-specific quirks isolated in adapters, patches, and normalizers
  - Publish stable, versioned artifacts to `alloy-devices`
  - Define objective gates that must pass before broadening scope
  - Reach strong single-family quality before multi-vendor expansion

- **Non-Goals**:
  - Porting old code mechanically from `alloy/tools/codegen`
  - Supporting many vendors from day one
  - Adding async/distributed processing complexity before correctness is proven
  - Copying external schemas or toolchains wholesale
  - Treating generated C++ as the only valuable output

## Proposed Architecture

### 1. Pipeline stages

The pipeline is explicitly stage-separated:

1. `fetch`
   - Acquire upstream raw data into a controlled source cache
   - Track source version, origin, and fetch manifest

2. `patch`
   - Apply declarative, reviewed corrections to broken upstream data
   - Preserve provenance and patch identity

3. `normalize`
   - Convert raw and patched vendor-specific data into a canonical IR
   - Collapse vendor naming differences into common concepts

4. `validate`
   - Run schema validation, semantic validation, and completeness validation
   - Produce structured reports and gate decisions

5. `emit`
   - Generate downstream artifacts from validated IR
   - Emit both machine-readable metadata and generated C++ outputs

6. `publish`
   - Publish only gated outputs to `alloy-devices`
   - Record manifests tying artifacts back to sources, patches, and generator revision

### 2. Canonical IR

The canonical IR is the system boundary between upstream chaos and downstream emission.
Emitters must consume IR, not raw vendor formats. The IR must model:
- device identity and family membership
- package and pinout information
- GPIO and alternate-function connectivity
- IP blocks and IP versions
- register blocks and fields
- interrupt descriptions
- DMA routing
- RCC/clock/reset relationships
- memory regions
- provenance for all normalized facts

### 3. Artifact model

`alloy-devices` should not be “just headers”. It should contain at least:
- generated C++ outputs
- canonical device metadata exports
- manifests with schema and generator versions
- validation reports or summarized publication reports

This ensures debugging, comparisons, docs, and future tooling can reuse the same pipeline
product instead of scraping emitted code.

### 4. Single-family-first strategy

The architecture will fail if breadth arrives before correctness. The first supported path
must be one carefully chosen family, likely STM32G0, used to prove:
- source ingestion
- patch mechanics
- canonical IR design
- pin/AF/RCC/DMA/IRQ semantics
- emission into `alloy-devices`
- consumption by Alloy

Only after that path is stable should the system expand to a second family.

## Repository Layout

The exact implementation may vary, but the architecture assumes a layout like:

```text
alloy-codegen/
  cli/
  src/alloy_codegen/
    sources/
    patches/
    schemas/
    ir/
    normalize/
    validate/
    emit/
    publish/
    reports/
  fixtures/
  tests/
  openspec/
```

Key principles:
- `sources/` contains vendor adapters and source manifests
- `patches/` contains reviewed, reproducible patch data
- `schemas/` versions the canonical contracts
- `emit/` contains downstream emitters and no vendor fixups

## CLI Model

The CLI should expose stage-specific commands and one full pipeline command:

- `alloy-codegen fetch`
- `alloy-codegen patch`
- `alloy-codegen normalize`
- `alloy-codegen validate`
- `alloy-codegen emit`
- `alloy-codegen publish`
- `alloy-codegen pipeline`

Each command must support scoped execution by vendor/family/device where applicable and must
produce structured output that CI can consume.

## Maturity Gates

These are hard gates, not aspirational milestones.

### Gate A: Source Bootstrap
Before any emitter is treated as real:
- the bootstrap family SHALL be `stm32g0`
- at least two representative `stm32g0` devices can be fetched reproducibly
- source manifests are recorded for both raw and patched inputs
- patch application is deterministic
- two consecutive runs with identical upstream revisions produce byte-identical patched
  source outputs and identical source/patch manifests

### Gate B: Canonical IR Stability
Before multi-device generation inside a family:
- at least three representative `stm32g0` devices normalize fully into the IR
- the IR schema is versioned
- golden fixtures exist for normalized outputs
- no critical domains remain represented only as vendor-specific opaque blobs
- no required canonical fields in device, pin, AF, RCC, IRQ, DMA, or memory domains are
  populated with placeholder sentinel values

### Gate C: Semantic Correctness
Before publication to `alloy-devices`:
- pins and alternate functions validate against package/device data
- RCC/clock/reset data validates against peripheral ownership rules
- IRQ and DMA mappings validate without critical conflicts
- validation reports show zero critical errors for the targeted family
- published-scope devices have zero unresolved TODO placeholders in connectivity-critical
  domains
- at least one low-end and one higher-feature `stm32g0` device pass the full semantic suite

### Gate D: Artifact Contract
Before Alloy consumes generated outputs:
- emitted metadata and generated C++ are both produced from the same IR revision
- manifests include generator version, schema version, source manifest, and patch set
- artifact layout is stable and documented
- at least one end-to-end consumer path in Alloy builds from published artifacts on a clean
  checkout using only published `alloy-devices`
- repeated emission with unchanged validated inputs is byte-stable for both metadata and
  generated C++ artifacts

### Gate E: Family Expansion
Before adding a second major family:
- Gate D is passing in CI for the first family
- regression suites exist for previously supported families
- family-specific normalization logic is isolated and does not fork the overall pipeline
- publication remains deterministic across reruns
- the bootstrap family has at least two passing publication cycles without contract changes

## Decisions

### Decision 1: Start from zero, not from a mechanical migration
**Why**: The old generator encoded too many concerns in one place. A clean repository only
helps if the architecture is also clean.

### Decision 2: IR-first, emitter-second
**Why**: Good generated C++ is a downstream consequence of good normalized device data.

### Decision 3: Publish metadata and code together
**Why**: Artifact debugging and downstream tooling need more than headers.

### Decision 4: Use explicit gates
**Why**: Without hard stop criteria, breadth will outrun correctness.

### Decision 5: Single-family first
**Why**: Pinmux, DMA, RCC, and packaging semantics are where data platforms usually fail.
It is better to learn those lessons deeply in one family than shallowly in many.

## Risks / Trade-offs

- **Risk: IR becomes too abstract too early**
  Mitigation: bootstrap with one family and one concrete consumer path before generalizing

- **Risk: schemas freeze too late**
  Mitigation: version schemas early and use manifests plus golden tests

- **Risk: publication pressure encourages skipping validation**
  Mitigation: make publication depend on gate results, not just command success

- **Risk: vendor breadth is added before semantics are understood**
  Mitigation: enforce Gate E before admitting new major families

- **Risk: emitters reintroduce hidden fixups**
  Mitigation: forbid semantic corrections in emitters; require fixes in patch or normalize

## Migration Plan

### Phase 0: Architecture bootstrap
- define project context
- define specs and gates
- lock the stage-separated architecture

### Phase 1: Single-family bootstrap (`stm32g0`)
- implement source, patch, normalize, validate for one family
- prove Gate A and Gate B

### Phase 2: Semantic closure
- model pins, AF, RCC, IRQ, DMA semantics for the bootstrap family
- prove Gate C

### Phase 3: Artifact publication
- emit metadata, manifests, and C++ outputs
- publish to `alloy-devices`
- prove Gate D

### Phase 4: Expansion
- add next families only after Gate E passes

## Open Questions

- Should canonical metadata be JSON-only initially, or JSON plus YAML exports?
- How much of validation reporting should be published into `alloy-devices` versus retained
  only in CI artifacts?
