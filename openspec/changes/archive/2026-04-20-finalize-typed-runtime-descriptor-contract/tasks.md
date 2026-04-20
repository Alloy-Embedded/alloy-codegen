## 1. OpenSpec

- [x] 1.1 Add canonical IR deltas for typed register-field descriptors and typed system bindings
- [x] 1.2 Add artifact contract deltas for structured runtime headers and non-CSV bindings
- [x] 1.3 Add validation and vendor-admission deltas for fully typed foundational runtime schemas

## 2. Raw Source and Canonical IR

- [x] 2.1 Extend raw-source extraction to capture register fields where upstream data provides them
- [x] 2.2 Add canonical descriptors for register fields, interrupt bindings, DMA bindings, and typed target references
- [x] 2.3 Add typed IDs for clock gate, reset, selector, register, field, interrupt, and DMA domains

## 3. Normalization and Enrichment

- [x] 3.1 Populate field descriptors for foundational runtime-owned schemas
- [x] 3.2 Replace textual route target interpretation with typed target-reference modeling
- [x] 3.3 Populate typed interrupt, DMA, clock, reset, and selector bindings per peripheral instance
- [x] 3.4 Remove CSV-only runtime payloads from enriched device descriptors

## 4. Emission

- [x] 4.1 Enrich `peripheral_instances.hpp` with typed binding IDs and structured references
- [x] 4.2 Enrich `register_map.hpp` with typed register IDs
- [x] 4.3 Emit `register_fields.hpp`
- [x] 4.4 Emit `interrupt_bindings.hpp`
- [x] 4.5 Emit `dma_bindings.hpp`
- [x] 4.6 Replace CSV payloads in `connector_tables.hpp` and `clock_tree_lite.hpp` with structured arrays
- [x] 4.7 Keep human-readable strings only as secondary diagnostics, not primary runtime fields

## 5. Validation and Publication

- [x] 5.1 Validate that foundational runtime-owned schemas have register and field descriptors
- [x] 5.2 Validate that route operations are executable from typed references alone
- [x] 5.3 Validate that interrupt and DMA bindings are typed and complete for foundational families
- [x] 5.4 Block publication when a foundational family still requires runtime string parsing
- [x] 5.5 Update vendor admission so new families must reuse schemas or add localized schema support only

## 6. Regression Coverage

- [x] 6.1 Update canonical fixtures for foundational families
- [x] 6.2 Update emitted artifact fixtures for foundational families
- [x] 6.3 Add tests covering typed field descriptors and typed binding headers
- [x] 6.4 Validate with `openspec validate finalize-typed-runtime-descriptor-contract --strict`
- [x] 6.5 Validate with `python3 -m ruff check src tests` and `python3 -m pytest tests -q`
