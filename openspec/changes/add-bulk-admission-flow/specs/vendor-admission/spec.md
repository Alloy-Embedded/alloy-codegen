## ADDED Requirements

### Requirement: The repository SHALL ship a bulk-admission CLI that combines the catalog, autogen, and Zephyr DTS

The repository SHALL ship `scripts/bulk_admit.py`, a CLI that
queries `data/known_devices.toml`, resolves each matching entry
to its input source (SVD or Zephyr DTS), runs the appropriate
autogen tool, and emits a draft device patch plus a registry
scaffold stub for review.  The CLI SHALL support a `--dry-run`
mode that prints every emission to stdout without touching disk
so reviewers can preview large batches before committing.  Every
emission SHALL be byte-deterministic — re-running with the same
inputs SHALL produce identical drafts.

#### Scenario: Bulk admit dry-run prints byte-deterministic drafts

- **WHEN** `python -m scripts.bulk_admit --vendor renesas
  --family ra4 --dry-run` is run twice against the same
  catalog + source tree
- **THEN** both runs SHALL print byte-identical output
- **AND** the output SHALL include one draft JSON patch per
  matched catalog entry, framed with a clear `=== <device>
  ===` separator

#### Scenario: Each admission emits both a patch draft and a registry scaffold

- **WHEN** `bulk_admit` admits a device that introduces a
  net-new `(vendor, family)` not yet registered
- **THEN** stdout SHALL print a copy-pastable stub for
  `vendors/_register_<vendor>_<family>.py`
- **AND** stdout SHALL print one-line `DEVICE_REGISTRY` and
  `SOURCE_BUNDLES` additions for `bootstrap.py`

#### Scenario: Unmatched catalog query fails with discoverable suggestions

- **WHEN** `bulk_admit --vendor acme --family bogus` is run
  and the catalog has no matching entries
- **THEN** the CLI SHALL exit non-zero with a message that
  lists the five closest `(vendor, family)` pairs in the
  catalog (Levenshtein distance), so the reviewer sees what
  they likely meant to type
