# Open alloy-codegen as a Public Contributor Tool

## Why

Alloy's `expand-chip-coverage` proposal explicitly identifies
the codegen visibility as the bottleneck for community-driven
chip admission: "Without a public code-generation tool, the
community cannot contribute new chips and the project will
never reach the coverage needed for broad adoption."

Today alloy-codegen lives at `github.com/Alloy-Embedded/alloy-codegen`
but is *not* yet a public tool in the sense that
`expand-chip-coverage` requires.  It has no PyPI release,
no `CONTRIBUTING_DEVICES.md` walkthrough, no documented overlay
schema, no `--version` discoverability, and no
`alloy-codegen generate / validate` CLI surface that a
contributor can pick up and use without reading the source.

The codegen also doesn't implement the `--svd <file> --overlay <yaml>
--out <dir>` workflow named in `expand-chip-coverage` Phase 1.1 —
today it consumes pre-normalized YAML from
`alloy-devices-yml`, not raw vendor SVD/ATDF/ESP-IDF headers.
That mismatch needs to be reconciled: either the codegen gains
a vendor-source ingestion path, or the contribution flow is
documented as "go via alloy-data-extractor first, then
alloy-codegen consumes the result."

This change closes the visibility gap so the codegen becomes
the documented, discoverable, contributable tool the alloy
ecosystem needs.

## What Changes

The codegen ships as a public, versioned, discoverable tool
with three deliverables.

First, a **PyPI release** under the `alloy-codegen` package
name with semantic versioning matched to `IR_SCHEMA_VERSION`,
a `[project.scripts]` entry exposing the `alloy-codegen` CLI,
and a `--version` flag confirming installation.  CI publishes
on tagged releases.

Second, a **`CONTRIBUTING_DEVICES.md`** walkthrough at the
repo root that takes a contributor from "I want to add a new
chip" to "PR open" in under 30 minutes.  The doc covers:
sourcing vendor SVD / ATDF / ESP-IDF headers; running
alloy-data-extractor to produce the canonical YAML; running
`alloy-codegen` against the YAML to produce artifacts;
validating with the smoke matrix; opening the PR.  An
**overlay-schema reference** documents every patchable IR
field (DMA request IDs, pin alternate function tables, clock
domain names, vendor-specific peripheral facts) with examples.

Third, a **`alloy-codegen` CLI surface** that exposes the
existing pipeline through three primary subcommands:
`generate` (run the full pipeline against a device list and
produce artifacts), `validate` (run the artifact contract +
golden gates against existing artifacts), and `doctor`
(diagnose installation, schema version, available admitted
devices).  The CLI replaces the patchwork of `python -m
alloy_codegen.*` entry points with a single, documented
front door.

## Impact

Affected specs: MODIFIED `codegen-alloy-boundary` adding the
public-tool admission requirements (PyPI, CLI, contributor
docs).  Affected code: `pyproject.toml` `[project.scripts]`
addition; new `CONTRIBUTING_DEVICES.md`; new
`docs/overlay-schema.md`; CLI refactor in `src/alloy_codegen/cli.py`
to consolidate subcommands; CI workflow gaining a
release-publish step on tagged commits.  Dependencies: this
change is the public-tool counterpart to alloy's
`expand-chip-coverage` Phase 1; ideally lands before alloy
ships its Phase 1, so that when alloy promises "anyone can
contribute a new chip" the tool is already available.  Out
of scope: actually admitting new chip families (separate
work in alloy/`expand-chip-coverage`); the
alloy-data-extractor public-tool story (separate repo,
separate proposal); GUI / web interface (alloy-configurator
already exists for that).
