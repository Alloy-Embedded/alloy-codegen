## ADDED Requirements

### Requirement: alloy-codegen SHALL ship as a public PyPI package with a versioned CLI

The alloy-codegen project SHALL publish to PyPI under the
package name `alloy-codegen` on tagged commits.  The package
SHALL expose a `[project.scripts]` entry installing an
`alloy-codegen` CLI binary on the user's PATH.  The CLI
SHALL respond to `--version` with a string matching the
project's pinned `IR_SCHEMA_VERSION`.  Releases SHALL follow
semantic versioning, with breaking schema changes tied to
major-version bumps.

#### Scenario: Fresh contributor installs and verifies

- **WHEN** a fresh contributor runs `pip install alloy-codegen`
  followed by `alloy-codegen --version`
- **THEN** the version string SHALL match the IR schema
  version pinned by the released package
- **AND** the CLI SHALL be discoverable via `alloy-codegen --help`
  without further setup steps

### Requirement: alloy-codegen SHALL expose a documented contributor workflow for new chip admission

The repository SHALL ship a top-level
`CONTRIBUTING_DEVICES.md` document that walks a contributor
from "I want to add a new chip" to "PR open" in under 30
minutes.  The doc SHALL cover sourcing vendor data, running
the alloy-data-extractor to produce canonical YAML, running
`alloy-codegen generate` and `alloy-codegen validate`, and
opening the resulting PR against the right repository
(alloy-codegen for codegen changes, alloy-devices-yml for
data changes).  A separate `docs/overlay-schema.md` SHALL
document every patchable IR field with type, default,
example, and source-data origin.

#### Scenario: Contributor admits a new chip end-to-end

- **WHEN** a fresh contributor follows
  `CONTRIBUTING_DEVICES.md` to admit a new chip not currently
  in the catalog
- **THEN** the contributor SHALL produce a passing YAML in
  alloy-devices-yml and a green
  `alloy-codegen validate` run within 30 minutes
- **AND** the doc SHALL link the overlay-schema reference at
  every step where a patchable IR field is mentioned

### Requirement: alloy-codegen SHALL expose a unified CLI front door

The CLI SHALL consolidate the existing patchwork of
`python -m alloy_codegen.*` entry points into a single
`alloy-codegen <subcommand>` interface with at least three
subcommands: `generate` (run the full pipeline against a
device or family selection and emit artifacts), `validate`
(run the artifact contract and golden gates against existing
artifacts), and `doctor` (diagnose installation, schema
version, admitted-device count, missing goldens).  Each
subcommand SHALL respond to `--help` with one-line
descriptions for every flag, so a new contributor sees the
relevant surface area on first use.

#### Scenario: Help-driven discovery

- **WHEN** a contributor types `alloy-codegen` with no
  arguments or `alloy-codegen --help`
- **THEN** the CLI SHALL list its three primary subcommands
  with one-line descriptions
- **AND** each subcommand SHALL respond to its own `--help`
  with a self-contained walkthrough of its flags
