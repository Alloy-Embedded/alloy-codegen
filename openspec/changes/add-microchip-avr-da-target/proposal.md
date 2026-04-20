## Why

AVR-DA é o melhor próximo passo para provar que o pipeline aguenta uma arquitetura Harvard
real sem virar um fork por vendor. É o primeiro caso em que o IR precisa distinguir espaços
de memória de verdade (`prog`, `data`, `eeprom`) e o primeiro 8-bit com clock, pinmux e DMA
suficientemente ricos para validar o modelo.

O bootstrap correto é `AVR128DA32`, não ATmega clássico. Ele é complexo o bastante para
provar o boundary, mas ainda cabe no contrato runtime atual.

## What Changes

- **IR model change**: `MemoryRegion` ganha `address_space: str | None`
- **Schema bump**: `IR_SCHEMA_VERSION` sobe para `1.2.0`
- **Unified-address-space devices stay clean**:
  - ARM / RISC-V / Xtensa continuam com `address_space` ausente
  - SAME70 `address_space="base"` do ATDF é normalizado para `None`
- **New memory kind**: `"eeprom"`
- **Source adapter extension**: `microchip_dfp.py` passa a consumir múltiplos address spaces
- **New family**: `("microchip", "avr-da")` em `PACK_CONFIGS`
- **New vector baseline**: `avr8`
- **No silent ARM fallback**: core desconhecido falha explicitamente
- **New pinmux schema**: `alloy.pinmux.avr-portmux-v1`
- **New startup emitter**: `runtime_avr_startup.py`
- **Validation hardening**: o startup AVR precisa ser validado por compile/disassembly,
  não só por shape textual

## Impact

- Affected specs: `vendor-admission`, `canonical-device-ir`, `artifact-contract`
- Affected code:
  - `ir/model.py`
  - `bootstrap.py`
  - `sources/microchip_dfp.py`
  - `stages/fetch.py`
  - `connector_model.py`
  - `stages/emit.py`
  - `runtime_avr_startup.py`
  - `patches/microchip/avr-da/`
  - `tests/fixtures/`
  - `.github/workflows/publish-alloy-devices.yml`

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 0 | Bootstrap & source adapter | AVR-Dx DFP parses with multi-space memory support |
| 1 | IR schema | `address_space` lands and existing unified-space fixtures stay semantically unchanged |
| 2 | IR ingestion | Valid `CanonicalDeviceIR` for `avr128da32` |
| 3 | PORTMUX routing | `avr-portmux-v1` pin routing published |
| 4 | Runtime emission | AVR runtime headers + AVR startup pass artifact contract and codegen validation |
| 5 | CI & publication | `microchip/avr-da` publishes without regressing `same70` |
| 6 | Fixtures & docs | Goldens, docs, and license notes updated |

## Non-Goals

- classic ATmega
- XMEGA
- ATtiny
- EEPROM driver semantics
- analog comparator modeling in this change
