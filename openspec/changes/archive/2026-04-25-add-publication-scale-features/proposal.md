## Why

Com 9 famílias admitidas e crescendo, dois problemas operacionais ficam evidentes:

1. **Falta visibilidade do que está suportado** — usuários do `alloy-devices` precisam
   ler 9 family.json + N device.json pra descobrir quais MCUs e periféricos rodam.
2. **Publish CI não escala** — todo push roda 9 jobs serializados mesmo quando só
   um patch de família mudou.  Com 1000 MCUs viraria ~16 horas de CI por commit.

Esta proposta adiciona duas features que atacam o eixo "publication ergonomics":

- **README auto-gerado** no root do `alloy-devices` — tabela do conjunto admitido
  reconstruída a cada publish, sempre em sync com `DEVICE_REGISTRY` + patches.
- **Affected-families detection** — o publish workflow detecta quais famílias o
  diff git afetou e roda só os jobs necessários, com override manual pra cache
  invalidation.

## What Changes

### Feature 1 — README auto-gerado

- **New emitter** `src/alloy_codegen/runtime_readme.py::emit_devices_readme()`
  rendendo markdown a partir de `DEVICE_REGISTRY` + family.json + device.json
- **Stages/publish.py** adiciona o artifact `README.md` no root da publication
  (`artifact_kind: "documentation"`)
- **Promotion**: `promote_staging_root` já cobre top-level non-vendor children
  (sem código novo)
- **Caveats opcionais**: campo novo `__readme_caveat` em
  `family.json::__source_notes` é coletado e exibido em seção dedicada
- **Determinismo**: cada job paralelo do publish workflow escreve o mesmo conteúdo
  (input idêntico) — `git status` no workflow não vê mudança e o commit só
  acontece quando algo realmente muda
- **Tabela**: lista completa de peripherals por família; GitHub renderiza horizontal
  scroll quando excede a largura

### Feature 2 — Affected-families detection

- **New CLI subcommand** `python -m alloy_codegen.cli affected-families
  --since <ref> [--json]` retornando o conjunto de `(vendor, family)` pares que
  precisam re-publicar
- **New module** `src/alloy_codegen/affected_families.py` com mapping
  path-pattern → famílias afetadas
- **Path heuristic**:
  - `patches/<vendor>/<family>/**` → só essa família
  - `src/alloy_codegen/sources/<source>.py` → famílias que usam aquele source
    (consulta `SOURCE_BUNDLES`)
  - `src/alloy_codegen/runtime_<arch>_startup.py` → famílias com aquele core
    (xtensa, riscv, avr; cortex-m via `runtime_startup.py`)
  - Outros `src/alloy_codegen/**` → **todas** (conservador)
  - `tests/**`, `openspec/**`, `*.md`, `.github/workflows/bootstrap-family.yml`
    → **nenhuma**
  - `.github/workflows/publish-alloy-devices.yml`, `pyproject.toml`, `uv.lock`
    → **todas**
  - Falha de diff (ref ausente) → **todas** (safe default)
- **Workflow integration**:
  - Novo job `detect-affected` (precondição do `publish`) computa o matrix dinâmico
  - `publish` consome via `strategy.matrix.include: ${{ fromJson(needs.detect.outputs.matrix) }}`
  - Skipa o publish inteiro quando o set é vazio
- **Manual override**: `workflow_dispatch` ganha input `force_all: boolean` que
  bypassa a detecção e força matrix completo

### Documentação

- O `README.md` do `alloy-codegen` (não confundir com o do `alloy-devices`) ganha
  uma seção "Published device matrix" linkando o `alloy-devices/README.md` e
  documentando como o auto-gen funciona

## Impact

- Affected specs: `artifact-contract`, `vendor-admission`
- Affected code:
  - `src/alloy_codegen/runtime_readme.py` (novo)
  - `src/alloy_codegen/affected_families.py` (novo)
  - `src/alloy_codegen/cli.py` (novo subcomando)
  - `src/alloy_codegen/stages/publish.py` (acrescenta README ao artifact list)
  - `src/alloy_codegen/patches.py` (parse de `__readme_caveat`)
  - `tests/test_runtime_readme.py` (novo)
  - `tests/test_affected_families.py` (novo)
  - `.github/workflows/publish-alloy-devices.yml` (detect-affected job + dynamic
    matrix + `force_all` input)
  - `README.md` (do alloy-codegen) — seção "Published device matrix"
- **Sem mudanças** em: emitters de runtime, normalize, validate, consumer
  verification, qualquer coisa upstream do publish stage

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 1 | README emitter | `runtime_readme.py` + `__readme_caveat` parser + tests; publish stage emite `README.md` |
| 2 | CLI `affected-families` | módulo `affected_families.py` com path mapping completo + subcomando CLI + JSON output |
| 3 | Workflow integration | `detect-affected` job + dynamic matrix + `force_all` workflow_dispatch input |
| 4 | Spec deltas + alloy-codegen README | `artifact-contract` ganha o root README; `vendor-admission` ganha affected-families requirement |
| 5 | Goldens + docs | README sample golden, regression de drift, alloy-codegen README atualizado |

## Non-Goals

- Detecção semântica baseada em AST do diff (path-only)
- Cache de artefatos compilados entre CI runs (Github Actions cache fica como
  follow-on se virar gargalo)
- Reescrever README histórico — primeira publish gera; sem retrofit
- Track per-família do SHA da última publicação (quem quer histórico usa `git log`)
- Truncar a coluna de peripherals — lista completa, GitHub faz scroll horizontal
- Tabela rodando localmente fora do publish stage (sem CLI dedicado pra preview;
  quem quer ver roda `python -m alloy_codegen.cli publish ... --dry-run` ou lê o
  arquivo gerado)
