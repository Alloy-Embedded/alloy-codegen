## Vendor Admission

### Foundational vendor set

The following vendors are admitted and their families may be published without further approval:

| Vendor      | Admitted families | Source pattern                              |
|-------------|-------------------|---------------------------------------------|
| `st`        | `stm32g0`, `stm32f4` | repository + structured metadata companion |
| `microchip` | `same70`          | pack archive + deterministic extracted tree |
| `nxp`       | `imxrt1060`       | repository + SDK-delivered structured headers |

### Admission gate

A new vendor (vendor 4 or beyond) may NOT enter active implementation until all of the
following are true:

- Gates T7, T8, and T9 are closed:
  - T7: `st/stm32f4` is publishable and has completed two stable publication cycles
  - T8: `microchip/same70` is publishable and has completed two stable publication cycles
  - T9: `nxp/imxrt1060` is publishable and has completed two stable publication cycles
- No foundational family requires final-stage emitter or publish exceptions
- A completed vendor-admission proposal exists in `openspec/changes/` declaring all of the
  items in the checklist below

### CI enforcement

The `quality` job in `bootstrap-family.yml` contains a `Vendor admission gate` step that
scans `patches/` and fails the build if any vendor directory other than the admitted set is
present. Removing a vendor from the admitted list or adding a new one requires updating that
step as part of the same admission proposal.

### Vendor admission checklist (J.2)

A proposal to admit a new vendor MUST answer all of the following before merging:

1. **Vendor identity** — canonical lower-case vendor key and rationale for adding it
2. **Family** — at least one representative family to be admitted as the bootstrap family
3. **Source pattern** — which of the three proven source patterns the vendor uses:
   - `repository + metadata companion` (ST model)
   - `pack archive + extracted tree` (Microchip DFP model)
   - `repository + SDK-delivered headers` (NXP SDK model)
   If the vendor requires a new fourth source pattern, the proposal must explain why the
   existing generic source-bundle model cannot accommodate it and what pipeline changes
   would be needed. (J.3)
4. **Two bootstrap devices** — at least two representative devices that will serve as CI
   fixtures and golden-fixture baselines
5. **Fixture plan** — how the source fixtures will be kept minimal, deterministic, and
   checked into the repository
6. **Licensing notes** — upstream license for the vendor data and any publication constraints
7. **Gate plan** — proposed gate IDs (following the N1/N4, M1/M4 numbering convention) and
   what each gate requires before publication is allowed

### Additional families from admitted vendors

An admitted vendor may add new families beyond their bootstrap family only after:
- The bootstrap family has completed at least two stable publication cycles
- No outstanding CI exceptions exist for that vendor's existing families
- A lightweight proposal (may skip design.md) exists naming the new family, its devices,
  and its source fixture plan
