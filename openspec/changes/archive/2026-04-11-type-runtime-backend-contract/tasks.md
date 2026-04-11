## 1. OpenSpec

- [x] 1.1 Add canonical IR deltas for backend schemas, register descriptors, and typed route operations
- [x] 1.2 Add artifact contract deltas for runtime profiles, peripheral instances, and enriched register maps
- [x] 1.3 Add validation deltas for foundational-family publication gates

## 2. Source and IR

- [x] 2.1 Extend raw source models to carry normalized register descriptors
- [x] 2.2 Parse register offsets from CMSIS-SVD based sources
- [x] 2.3 Preserve Microchip and NXP coverage through the same raw register path
- [x] 2.4 Extend canonical IR and schema with backend schema IDs and register descriptors

## 3. Normalization

- [x] 3.1 Derive backend schema IDs for foundational peripheral classes
- [x] 3.2 Populate canonical register descriptors from raw source data
- [x] 3.3 Replace string-only route operations with typed runtime operation fields

## 4. Emission

- [x] 4.1 Emit `generated/runtime_profiles.hpp`
- [x] 4.2 Emit `generated/devices/<device>/peripheral_instances.hpp`
- [x] 4.3 Enrich `generated/devices/<device>/register_map.hpp` with per-register offsets
- [x] 4.4 Emit typed route operation descriptors in `generated/connector_tables.hpp`

## 5. Validation and Publication

- [x] 5.1 Add validation rules for backend schema coverage
- [x] 5.2 Add validation rules for typed route operations
- [x] 5.3 Add validation rules for foundational register descriptor coverage
- [x] 5.4 Block publication when foundational runtime descriptors are incomplete

## 6. Regression Coverage

- [x] 6.1 Update canonical golden fixtures
- [x] 6.2 Update emitted artifact golden fixtures
- [x] 6.3 Add targeted tests for typed route ops and register offsets
- [x] 6.4 Validate the change with `openspec validate ... --strict`, `ruff`, and `pytest`
