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

from alloy_codegen.ir.synthesised import (
    ClockProgramStep,
    RouteOperation,
    SynthesisedDevice,
)
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


def _emit_clock_step(step: ClockProgramStep) -> list[str]:
    """Lower one :class:`ClockProgramStep` to one or more C lines.

    The C is intentionally raw read-modify-write through pointers —
    the runtime-lite contract says we don't depend on a vendor SDK
    header.  Where the IR carries a typed register address (it
    doesn't yet; ``register_addr`` is reserved for an enrichment
    pass), the lowering swaps the symbolic lookup for a literal.

    For now, ``register_id`` / ``field_id`` flow through as a
    comment so the regenerated source is auditable line-by-line
    against the reference manual; the *actual* writes route
    through small helper macros (``ALLOY_CLOCK_WF`` etc.) which
    a vendor shim resolves to concrete addresses.  This keeps
    the emitter byte-stable across runs even before the IR
    carries every typed register address.
    """
    out: list[str] = []
    if step.comment:
        out.append(f"    /* {step.comment} */")
    if step.kind == "barrier_dsb":
        out.append("    __DSB();")
    elif step.kind == "barrier_isb":
        out.append("    __ISB();")
    elif step.kind == "spin_until":
        # The body of the helper is provided by the runtime-lite
        # contract (``alloy_clock_spin_until``).  Until the helper
        # lands we surface the call shape as a documented stub.
        out.append(
            f"    if (alloy_clock_spin_until_field(\"{step.register_id or ''}\", "
            f"\"{step.field_id or ''}\", {step.expected if step.expected is not None else 0}u, "
            f"ALLOY_CLOCK_PLL_LOCK_TIMEOUT_US) != 0) {{ return -1; }}"
        )
    elif step.kind == "set_bits":
        out.append(
            f"    alloy_clock_set_field(\"{step.register_id or ''}\", "
            f"\"{step.field_id or ''}\");"
        )
    elif step.kind == "clear_bits":
        out.append(
            f"    alloy_clock_clear_field(\"{step.register_id or ''}\", "
            f"\"{step.field_id or ''}\");"
        )
    elif step.kind in ("write_field", "flash_latency"):
        out.append(
            f"    alloy_clock_write_field(\"{step.register_id or ''}\", "
            f"\"{step.field_id or ''}\", {step.value}u);"
        )
    elif step.kind == "write_register":
        out.append(
            f"    alloy_clock_write_register(\"{step.register_id or ''}\", "
            f"{step.value}u);"
        )
    else:  # pragma: no cover - exhaustively typed via ClockStepKind
        out.append(f"    /* unknown step kind: {step.kind} */")
    return out


def _emit_clock_profile(
    profile: ClockProfile,
    all_oscillators: dict[str, str],
    program: tuple[ClockProgramStep, ...] | None,
) -> list[str]:
    """One ``alloy_clock_enter_<id>()`` function per profile.

    When the synthesised IR carries a vendor-specific
    ``ClockProgramStep`` tuple for this profile, lower it inline.
    Otherwise emit a forward-declaration so vendor shims can plug
    in a body the legacy way.
    """
    fn = _safe_c_id("alloy_clock_enter_" + profile.id)
    lines = [
        "",
        f"/* Clock profile: {profile.id} ({profile.kind})",
        f" *   sysclk:        {profile.sysclk}",
        f" *   sysclk_source: {profile.sysclk_source}",
    ]
    if profile.hclk_hz is not None:
        lines.append(f" *   hclk_hz:       {profile.hclk_hz}")
    if profile.pclk_hz is not None:
        lines.append(f" *   pclk_hz:       {profile.pclk_hz}")
    for coef in ("m", "n", "r", "p", "q", "frac"):
        v = getattr(profile, f"pll_{coef}", None)
        if v is not None:
            lines.append(f" *   pll_{coef}:         {v}")
    for k, v in profile.extra.items():
        lines.append(f" *   {k}: {v}")
    lines.append(" */")
    if program is None or not program:
        # Legacy path: no body, no backend.
        lines.append(f"int {fn}(void);")
        return lines

    # Body lowered from the vendor backend's ClockProgramStep tuple.
    lines.append(f"int {fn}(void) {{")
    for step in program:
        lines.extend(_emit_clock_step(step))
    lines.append("    return 0;")
    lines.append("}")
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
        "/* runtime_init.c",
        " *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        " *",
        f" * Provenance: {device.provenance.primary}",
        f" * Authored:   {device.provenance.authored}",
        " *",
        " * Generated artifacts:",
        " *   * kRouteOperations[] — clock-enable + reset pulse table",
        " *     (synthesised from peripherals[].rcc).",
        " *   * alloy_clock_apply_<profile>() — one fn per",
        " *     clock.profiles[] entry.",
        " *",
        " * Vendor shims provide:",
        " *   * int alloy_runtime_apply_op(const AlloyRouteOperation *);",
        " *   * int alloy_clock_set_<profile_id>_impl(void);",
        " */",
        "#include <stddef.h>",
        "#include <stdint.h>",
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
            "static const size_t kRouteOperationCount = "
            "sizeof(kRouteOperations) / sizeof(kRouteOperations[0]);"
        )
    else:
        lines.append("static const AlloyRouteOperation *kRouteOperations = NULL;")
        lines.append("static const size_t kRouteOperationCount = 0;")

    lines.extend(_emit_route_dispatch_decl())

    # Per-profile bodies (when a ClockBackend lowered the profile)
    # or forward decls (when no backend is registered for the
    # vendor yet — caller's vendor shim fills them in).
    if device.clock.profiles:
        lines.append("")
        lines.append("/* ---- Clock profiles ---- */")
        # Helper-call forward decls only emitted once at the top of
        # the section so each profile body can call into them.
        if synthesised.clock_program_steps:
            lines.extend([
                "extern int alloy_clock_spin_until_field(const char *reg, const char *fld, unsigned expected, unsigned timeout_us);",
                "extern void alloy_clock_set_field(const char *reg, const char *fld);",
                "extern void alloy_clock_clear_field(const char *reg, const char *fld);",
                "extern void alloy_clock_write_field(const char *reg, const char *fld, unsigned value);",
                "extern void alloy_clock_write_register(const char *reg, unsigned value);",
                "#ifndef ALLOY_CLOCK_PLL_LOCK_TIMEOUT_US",
                "#define ALLOY_CLOCK_PLL_LOCK_TIMEOUT_US 10000u",
                "#endif",
                "#ifndef __DSB",
                "#define __DSB() __asm__ volatile (\"dsb\" ::: \"memory\")",
                "#endif",
                "#ifndef __ISB",
                "#define __ISB() __asm__ volatile (\"isb\" ::: \"memory\")",
                "#endif",
            ])
        for profile in device.clock.profiles:
            program = synthesised.clock_program_steps.get(profile.id)
            lines.extend(_emit_clock_profile(profile, osc_freq, program))

    # Reset state recap (a comment block — vendor shim consumes it).
    if device.clock.reset_state:
        lines.append("")
        lines.append("/* Reset state (post-power-on, pre-firmware):")
        for k, v in device.clock.reset_state.items():
            lines.append(f" *   {k}: {v}")
        lines.append(" */")

    lines.append("")
    return "\n".join(lines)
