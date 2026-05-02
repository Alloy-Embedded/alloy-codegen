"""Emit ``runtime_init.c`` from a v2.1 :class:`CanonicalDevice` +
:class:`SynthesisedDevice`.

Produces a C source that brings the chip to the reset state plus
helper functions to switch to each named clock profile and to
enable / reset peripherals via the synthesised ``RouteOperation``
table.

Output layout::

    #include "peripheral_traits.h"
    #include <stdint.h>

    /* RouteOperation table — every clock-enable / reset pulse, in
     * source order, ready to consume by alloy_runtime_apply_op().
     */
    typedef struct AlloyRouteOperation {
        const char *operation_id;
        const char *kind;
        const char *register_id;
        const char *register_field_id;
        unsigned    value;
    } AlloyRouteOperation;

    static const AlloyRouteOperation kRouteOperations[] = {
        { "operation:clock-enable:gpioa", "set-bit",  "register:apb2enr:apb2enr", "field:apb2enr:apb2enr:iopaen", 1 },
        ...
    };

    /* Clock profiles — pick by name, set up dividers, return 0/-errno.
     */
    int alloy_clock_apply_post_reset(void);
    int alloy_clock_apply_pll_hse_72mhz(void);
    ...

The actual register writes live in vendor-specific implementation
shims (``alloy_runtime_apply_op``, ``alloy_clock_set_pll``); this
emitter produces only the data table + the dispatch shell.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import RouteOperation, SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice, ClockProfile


def _safe_c_id(value: str) -> str:
    """Sanitise an arbitrary string into a valid C identifier."""
    out = []
    for ch in value:
        if ch.isalnum() or ch == "_":
            out.append(ch)
        else:
            out.append("_")
    if not out or not out[0].isalpha():
        out.insert(0, "_")
    return "".join(out)


def _emit_route_op_row(op: RouteOperation) -> str:
    """One C struct initialiser for the ``kRouteOperations[]`` array."""
    parts = [
        f"\"{op.operation_id}\"",
        f"\"{op.kind}\"",
        f"\"{op.register_id or ''}\"",
        f"\"{op.register_field_id or ''}\"",
        f"{op.value_int if op.value_int is not None else 0}",
    ]
    return "    { " + ", ".join(parts) + " },"


def _emit_clock_profile(profile: ClockProfile, all_oscillators: dict[str, str]) -> list[str]:
    """One ``alloy_clock_apply_<id>()`` function per profile.

    The body is a stub — vendor shims fill it in.  We emit the
    constants the shim needs (target sysclk, source) so the function
    is self-contained.
    """
    fn = _safe_c_id("alloy_clock_apply_" + profile.id)
    lines = [
        "",
        f"/* Clock profile: {profile.id} ({profile.kind})",
        f" *   sysclk:        {profile.sysclk}",
        f" *   sysclk_source: {profile.sysclk_source}",
    ]
    for k, v in profile.extra.items():
        lines.append(f" *   {k}: {v}")
    lines.append(" */")
    lines.append(f"int {fn}(void);")
    return lines


def _emit_route_dispatch_decl() -> list[str]:
    """Forward decl + helper that walks ``kRouteOperations[]``."""
    return [
        "",
        "/* Walk every entry in kRouteOperations[] in declaration order,",
        " * dispatching each one to alloy_runtime_apply_op().  The default",
        " * implementation lives in a vendor-specific shim and is expected",
        " * to write `value` to (register_id, register_field_id) according",
        " * to `kind`.",
        " */",
        "extern int alloy_runtime_apply_op(const AlloyRouteOperation *op);",
        "",
        "static inline int alloy_runtime_init_peripherals(void) {",
        "    for (size_t i = 0; i < kRouteOperationCount; ++i) {",
        "        int rc = alloy_runtime_apply_op(&kRouteOperations[i]);",
        "        if (rc != 0) return rc;",
        "    }",
        "    return 0;",
        "}",
    ]


def emit_runtime_init(
    device: CanonicalDevice,
    synthesised: SynthesisedDevice,
) -> str:
    """Render the runtime-init C source for ``device``."""
    osc_freq = {k: v.freq for k, v in device.clock.oscillators.items()}

    lines: list[str] = [
        f"/* runtime_init.c",
        f" *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        f" *",
        f" * Provenance: {device.provenance.primary}",
        f" * Authored:   {device.provenance.authored}",
        f" *",
        f" * Generated artifacts:",
        f" *   * kRouteOperations[] — clock-enable + reset pulse table",
        f" *     (synthesised from peripherals[].rcc).",
        f" *   * alloy_clock_apply_<profile>() — one fn per",
        f" *     clock.profiles[] entry.",
        f" *",
        f" * Vendor shims provide:",
        f" *   * int alloy_runtime_apply_op(const AlloyRouteOperation *);",
        f" *   * int alloy_clock_set_<profile_id>_impl(void);",
        f" */",
        f"#include <stddef.h>",
        f"#include <stdint.h>",
        "",
        "typedef struct AlloyRouteOperation {",
        "    const char *operation_id;",
        "    const char *kind;",
        "    const char *register_id;",
        "    const char *register_field_id;",
        "    unsigned    value;",
        "} AlloyRouteOperation;",
        "",
    ]

    # Route operations table.
    if synthesised.route_operations:
        lines.append("static const AlloyRouteOperation kRouteOperations[] = {")
        for op in synthesised.route_operations:
            lines.append(_emit_route_op_row(op))
        lines.append("};")
        lines.append(
            f"static const size_t kRouteOperationCount = "
            f"sizeof(kRouteOperations) / sizeof(kRouteOperations[0]);"
        )
    else:
        lines.append("static const AlloyRouteOperation *kRouteOperations = NULL;")
        lines.append("static const size_t kRouteOperationCount = 0;")

    lines.extend(_emit_route_dispatch_decl())

    # Per-profile fn forward decls (the actual body lands in the
    # vendor shim).
    if device.clock.profiles:
        lines.append("")
        lines.append("/* ---- Clock profiles ---- */")
        for profile in device.clock.profiles:
            lines.extend(_emit_clock_profile(profile, osc_freq))

    # Reset state recap (a comment block — vendor shim consumes it).
    if device.clock.reset_state:
        lines.append("")
        lines.append("/* Reset state (post-power-on, pre-firmware):")
        for k, v in device.clock.reset_state.items():
            lines.append(f" *   {k}: {v}")
        lines.append(" */")

    lines.append("")
    return "\n".join(lines)
