## Why

The `alloy` HAL (Phase 2 of the roadmap) needs a compile-time way to validate that a
given pin actually carries a given peripheral signal before allowing a `Connector<>` or
`Uart<>` instantiation. The canonical IR already holds the full (peripheral, signal, pin,
af_number) mapping, but there is no C++ artifact that exposes this family-level lookup
table yet. Adding a `signal_map.hpp` emitter closes this gap and gives the HAL a single
stable include from which to derive template specialisations or `static_assert` checks.

## What Changes

- **New emitter function** `emit_signal_map_header()` in `emission.py`: aggregates all
  alternate-function signals across every device in the family scope into one
  `constexpr SignalDescriptor kSignalMap[]` table, deduplicated and sorted
- **`stages/emit.py`**: call the new emitter and include the artifact in the published set
- **Output artifact**: `{vendor}/{family}/generated/signal_map.hpp` — family-scoped,
  one file per family, all devices merged
- **Exclusions**: gpio-function signals (af_number is None) are excluded; only proper
  alternate-function entries are emitted
- **Tests**: golden fixture + `test_emit.py` assertion + `test_publish.py` count bump

## Impact

- Affected specs: `artifact-emission`
- Affected code: `emission.py`, `stages/emit.py`, `tests/test_emit.py`,
  `tests/test_publish.py`, golden fixtures
- No IR schema change; no new pipeline stages
- Artifact count increases by 1 per family (already guarded with `>= N` in publish test)
- Downstream `alloy` HAL can include `generated/signal_map.hpp` for compile-time AF
  validation in Connector/UART/SPI templates
