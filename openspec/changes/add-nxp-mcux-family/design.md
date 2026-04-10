## Context

NXP is the next practical vendor to support if Alloy wants both audience reach and usable open
upstream data. It is one of the largest MCU vendors in the current market, and its official
GitHub footprint is strong enough to bootstrap codegen:

- `nxp-mcuxpresso/mcux-soc-svd` publishes device SVDs as a dedicated repository
- `nxp-mcuxpresso/mcux-sdk` publishes SDK content, and for i.MX RT families it includes rich
  pin-function headers such as `devices/MIMXRT1062/drivers/fsl_iomuxc.h`

The important architectural twist is that the NXP pin source is not a dedicated metadata repo.
Instead, the useful connectivity data is delivered as structured C headers and SDK content.
This is exactly the kind of vendor shape the source-bundle model needs to support if Alloy is
going to scale past ST and Microchip.

## Goals / Non-Goals

Goals:
- Add `nxp` as a first-class vendor without changing the canonical IR or artifact contract
- Bootstrap NXP support on a family with a strong official structured pin source
- Prove that SDK-delivered pinmux headers can be normalized into the same canonical pin/signal
  model already used by ST
- Keep provenance explicit across SVD repo revision, SDK revision, selected header files, patches,
  and emitted artifacts
- Publish `nxp/imxrt1060` artifacts only after semantic closure and one real Alloy consumer path

Non-Goals:
- Supporting LPC, Kinetis, MCX, and i.MX RT all at once
- Depending on opaque IDE databases as the primary source of truth
- Introducing a new NXP-only IR branch or artifact shape
- Generalizing all header-derived pin sources in one step beyond what `imxrt1060` needs

## Proposed Architecture

### 1. Family choice: `imxrt1060`

The first NXP family should be chosen for source quality, not for breadth. `imxrt1060` is the
best bootstrap target because:

- the official SDK clearly ships `fsl_iomuxc.h` for devices such as `MIMXRT1062`
- the pin-function data is rich, explicit, and already structured as tuples of mux register,
  mux mode, input register, daisy value, and config register
- the SVD repo publishes matching device entries such as `MIMXRT1062` and `MIMXRT1064`

This proposal therefore uses:
- `vendor = "nxp"`
- `family = "imxrt1060"`
- bootstrap devices:
  - `mimxrt1062`
  - `mimxrt1064`

The canonical device IDs remain lower-case Alloy-style identifiers. Source provenance records
the official uppercase upstream names.

### 2. Source bundle model for NXP

The NXP source bundle is:

- `nxp-mcux-soc-svd`
  - authoritative source for register blocks and interrupt declarations

- `nxp-mcux-sdk`
  - authoritative source for pin-function tuples, mux registers, daisy selection, and
    device-local SDK metadata required to interpret IOMUX configuration

This is a useful contrast with Microchip:
- Microchip family support is pack-based (`.atpack` + extracted tree)
- NXP family support is repository-and-header based

The source-bundle model must treat both as first-class without changing the pipeline shape.

### 3. Header-derived pin-function normalization

For `imxrt1060`, the normalizer must parse structured pin-function macros from SDK headers such
as `fsl_iomuxc.h`. A typical macro encodes:

`<muxRegister, muxMode, inputRegister, inputDaisy, configRegister>`

The header parser must convert that SDK representation into canonical facts:
- pin identity
- peripheral identity
- signal identity
- AF or mux selection value
- input daisy information where present
- provenance back to the exact header and macro

The parser must not stop at text extraction. It must create a semantic bridge from header
macros into the same canonical pin/signal graph used by the rest of the pipeline.

### 4. SVD plus SDK merge

NXP normalization is a composite path:

- `mcux-soc-svd` provides:
  - register maps
  - base addresses
  - interrupts

- `mcux-sdk` provides:
  - pin-function tuples and mux selections
  - device-local SDK metadata
  - board/project templates useful for cross-checks, but not primary canonical data

The normalizer merges both into the existing canonical IR. Merge rules must be explicit:
- peripheral instance names must align across SVD and SDK pin-function headers
- pin names such as `GPIO_EMC_00` must map consistently into canonical pin identifiers
- signals such as `LPUART3_TX` and `LPSPI2_SCK` must become peripheral/signal tuples rather than
  emitter-specific strings

### 5. Patch strategy

NXP support keeps the same discipline as the rest of the system:
- reviewed data correction belongs in patches
- the SDK header parser does not silently repair semantic gaps
- the emitter does not own any NXP-specific business rules

Expected patch layout:
- `patches/nxp/imxrt1060/family.json`
- `patches/nxp/imxrt1060/devices/mimxrt1062.json`
- `patches/nxp/imxrt1060/devices/mimxrt1064.json`

Likely patch use cases:
- canonicalizing naming mismatches between SVD and SDK
- package naming or package-variant refinement
- supplementing clock/enable semantics not explicit in pinmux headers
- refining DMA request mappings if they are not recoverable directly from the chosen source pair

### 6. Validation gates for NXP

#### Gate N1: source admission

Before normalization is considered real:
- the two `imxrt1060` bootstrap devices resolve reproducibly from `mcux-soc-svd` and `mcux-sdk`
- manifests record both repository revisions and the selected device-local source files
- repeated fetch/select runs with the same revisions are byte-stable

#### Gate N2: header-to-IR closure

Before draft artifact emission:
- the parser converts SDK pin-function macros into the canonical pin/signal model for both
  bootstrap devices
- no required connectivity facts remain trapped only inside vendor-specific raw header strings
- canonical fixtures for both devices are committed

#### Gate N3: semantic closure

Before publication:
- pin-function connectivity validates with zero critical conflicts
- peripheral naming between SDK and SVD validates with zero critical conflicts
- interrupt topology validates from SVD with zero critical conflicts
- clock/enable and DMA semantics required for publication are either closed from the chosen
  sources plus reviewed patches or publication remains blocked

#### Gate N4: publication readiness

Before `nxp/imxrt1060` is treated as supported:
- family artifacts publish into `alloy-devices` under `nxp/imxrt1060`
- at least one Alloy consumer path builds from published artifacts only
- two repeated publication runs are byte-stable and no-op when unchanged

### 7. Why not LPC or Renesas first?

`LPC55Sxx` is a plausible future NXP family, but the most clearly reusable structured pin source
I found in the official NXP repos is on the i.MX RT path through `fsl_iomuxc.h`. That makes
`imxrt1060` the safer first NXP bootstrap.

Renesas is also a major MCU vendor, but from a codegen-input perspective the openly published
source picture is weaker than NXP's official `mcux-soc-svd + mcux-sdk` combination. It should
stay on the roadmap, but NXP is the better next implementation target.

## Decisions

### Decision 1: choose NXP as the next vendor

Why:
- it is one of the largest missing MCU vendors in the current market
- its official source footprint is strong enough for codegen without inventing a closed tooling
  dependency

Alternative considered:
- Renesas
  Rejected for now because the open structured source path for pin/package/function data looks
  weaker and less direct than NXP's official SVD-plus-SDK combination.

### Decision 2: bootstrap on `imxrt1060`

Why:
- the SDK pin-function source is explicit and structured
- the family is widely used and visible
- the source pair is clean enough to test the architecture rather than fight the inputs

Alternative considered:
- `lpc55s6x`
  Rejected for first implementation because the openly visible pin-function source is less
  obviously canonical than the i.MX RT IOMUXC headers.

### Decision 3: SDK headers are valid structured inputs

Why:
- the `fsl_iomuxc.h` macros are already structured and semantically meaningful
- treating them as second-class because they are C headers would be artificial

Alternative considered:
- wait for a perfect XML or pack source
  Rejected because the official SDK already contains usable structured metadata.

## Risks / Trade-offs

- **Risk: header formats differ across NXP families**
  Mitigation: keep `imxrt1060` parser logic family-scoped and do not assume all NXP lines look
  the same

- **Risk: SDK headers encode pin functions but not full package topology**
  Mitigation: use family patches and selected SDK metadata to close the gaps, and block
  publication until validation says the family is semantically complete enough

- **Risk: source bundle now needs to support repository revision pairs**
  Mitigation: this is a natural extension of the existing named-source model and should be
  visible in manifests rather than hidden in code

- **Risk: Alloy consumer path for NXP is not ready yet**
  Mitigation: treat publication readiness as blocked until one consumer path is proven

## Migration Plan

### Phase 0: vendor admission
- register `nxp/imxrt1060` in the device registry
- bind the family to the `nxp-mcux-soc-svd + nxp-mcux-sdk` source bundle

### Phase 1: source bootstrap
- implement source selection from both official repositories
- record manifest data and selected file provenance
- close Gate N1

### Phase 2: header-derived normalization
- parse SDK pin-function headers
- merge pin/function facts with SVD peripheral and interrupt data
- add patches and golden fixtures
- close Gate N2

### Phase 3: semantic validation
- validate pin/peripheral/interrupt/clock/DMA semantics
- keep publication blocked until the family closes Gate N3

### Phase 4: publishable family
- emit and publish `nxp/imxrt1060`
- prove one Alloy consumer path
- close Gate N4

## Open Questions

- Should the first implementation parse only `fsl_iomuxc.h`, or should it also consume generated
  board `pin_mux.c/h` as a secondary validation oracle?
- If package topology is not fully reconstructable from the chosen SDK sources, should the second
  reviewed source be a curated Alloy-owned metadata file or another official NXP repository?
