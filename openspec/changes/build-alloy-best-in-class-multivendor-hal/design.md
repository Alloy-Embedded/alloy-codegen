## Context

O valor do `alloy-codegen` não é só normalizar dados de silicon vendors. O valor real é
emitir artefatos suficientemente ricos para que o `alloy` nunca precise reconstruir
fatos por string matching, scans de tabela ou defaults implícitos.

Esta design note fixa a boundary deste repo:

- `alloy-codegen` emite artefatos tipados, sidecars e ferramentas de diagnóstico
- `alloy` consome esses artefatos e decide a API do HAL

Misturar os dois na mesma OpenSpec aqui só esconde dependências reais.

## Goals / Non-Goals

Goals:
- emitir o conjunto de artefatos que fecha linker, startup-facing layout, clock profiles,
  connector validation, interrupt stubs e capability reporting
- garantir que cada artefato tenha validação forte e provenance
- deixar o boundary claro o bastante para o `alloy` não precisar de heurística downstream

Non-Goals:
- definir APIs concretas do HAL em `alloy`
- decidir ownership model do consumidor
- decidir a função CMake final no repo `alloy`

## Decisions

### Decision 1: linker script é artefato do gerador

**Chosen**: emitir `device.ld` derivado de `MemoryRegion` e `startup_roles`.

**Rationale**: memória e layout já são fatos do IR. Manter linker manual no consumidor
desperdiça o melhor source-of-truth do sistema.

### Decision 2: clock config é profile-based e emitted ahead-of-time

**Chosen**: emitir:
- `clock_profiles.hpp` com ids dos profiles
- `clock_config.hpp` com sequências concretas de aplicação

**Rationale**: o gerador já conhece clock graph, selectors e resets. O consumidor não deve
resolver isso em runtime nem reconstruir equações.

### Decision 3: connector tables e interrupt stubs são parte do contrato público

**Chosen**:
- `connectors.hpp` fecha a validabilidade compile-time de pin/peripheral/signal
- `interrupt_stubs.hpp` fecha a superfície mínima de override por device

**Rationale**: ambos são fatos estáticos do device e devem sair do publish, não do HAL.

### Decision 4: capability data sai em dois formatos

**Chosen**:
- `capabilities.hpp` para compile-time checks
- `capabilities.json` para tooling, CMake e diff

**Rationale**: o mesmo fato precisa servir compilador e tooling sem duplicação de verdade.

### Decision 5: explainability é deliverable do gerador

**Chosen**: `alloy explain` e `alloy diff` pertencem ao `alloy-codegen`.

**Rationale**: provenance nasce e morre no gerador. O downstream só deveria consumir o resultado.

### Decision 6: paired-alloy work é dependency, não task local

**Chosen**: qualquer item que requeira editar drivers, APIs ou CMake do `alloy`
fica documentado como dependência externa e não como task executável nesta spec.

## Risks / Trade-offs

- capability manifests só são tão bons quanto a cobertura do IR
- connector tables com diagnósticos ricos podem inflar o código gerado se não houver cuidado
- clock profile coverage inicial pode ser incompleta
- o valor pleno desta spec depende de o repo `alloy` realmente consumir esses artefatos depois

## Migration Plan

1. emitir artefatos
2. validar publish e smoke
3. documentar a handoff surface para o `alloy`

## External Dependencies

O consumo destes artefatos no `alloy` deve ser tratado em OpenSpecs pareadas lá, incluindo:
- linker script wiring
- `board::init()` / clock application
- GPIO/UART/SPI/I2C/DMA/ADC/Timer/PWM drivers
- ownership model
- CMake user API
