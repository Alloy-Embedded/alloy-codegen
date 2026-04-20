## Context

AVR-DA é o primeiro device Harvard do pipeline. O ponto central aqui não é “suportar AVR”;
é provar que o IR consegue representar endereços repetidos em espaços diferentes sem colapsar
isso em um mapa unificado falso.

Essa proposta precisa mexer em uma coisa só no IR: `MemoryRegion.address_space`. O resto deve
ficar em adapters, emitters e validation.

## Goals / Non-Goals

Goals:
- modelar `prog`, `data` e `eeprom` corretamente
- manter unified-space devices sem ruído adicional
- validar startup AVR de forma observável, não só estrutural

Non-Goals:
- suportar ATmega clássico
- modelar analog comparator como se fosse ADC
- gerar driver de EEPROM

## Decisions

### Decision 1: `address_space` fica em `MemoryRegion`

**Chosen**: `MemoryRegion.address_space: str | None`.

**Rationale**: só memória precisa desse contexto. Isso mantém a mudança pequena e versionável.

### Decision 2: `address_space` só é serializado para espaços reais de Harvard

**Chosen**:
- `prog`, `data`, `eeprom` são serializados
- unified-address-space devices omitem o campo
- `base` vindo do ATDF de SAME70 é normalizado para `None`

**Rationale**: `base` é artefato do formato upstream, não semântica útil do IR.

### Decision 3: multi-space parsing continua em `microchip_dfp.py`

**Chosen**: refatorar o adapter existente.

**Rationale**: o formato é o mesmo; separar por family aqui só criaria drift interno.

### Decision 4: EEPROM é um memory kind próprio, sem startup roles

**Chosen**: `kind="eeprom"` e zero startup roles.

**Rationale**: EEPROM não é copy-source de startup nem stack target.

### Decision 5: PORTMUX usa schema próprio e `af_number` schema-local

**Chosen**: `alloy.pinmux.avr-portmux-v1`, com `af_number` codificando a seleção do PORTMUX.

### Decision 6: startup AVR começa em C, mas precisa ser comprovado por compile/disassembly

**Chosen**: o primeiro emitter gera startup em C compatível com avr-gcc.

**Rationale**: é o caminho mais simples de manter.

**Constraint**: isso só é aceito se a validação mostrar que o compilador/linker geram a tabela
de vetores e o reset flow corretos. Se a lowering não fechar, o emitter muda para asm sem
precisar refazer o IR.

## Risks / Trade-offs

- **schema bump**: precisa coordenação com `alloy-devices`
- **fixture churn**: todas as fixtures normalizadas passam pelo novo schema
- **startup lowering**: o maior risco real é o C startup não baixar para o formato correto

## Migration Plan

1. schema + normalization primeiro
2. AVR-DA depois
3. validação do startup antes de abrir o publish

## Open Questions

- o smoke consumer de AVR deve validar só compile ou também disassembly mínima do vetor/reset?
  Resposta provisória: os dois.
