# Public repository audit — C generator

Inspected public default branch: `c980898409db454a58c152c3e6d8d94f79538837`.
Prepared on `codex/public-repo-audit-20261018`; no main edits, push, deployment,
or production-source changes. Classification: **reference implementation**.
Release verdict: **conditional for a clearly labeled reference generator**;
maintainer provenance confirmation remains a publication blocker. It must not
be presented as an exact production renderer or a camera-qualified generator.

## Findings and remediation

Evidence below links to the inspected public commit when describing original
behavior; current local sources and tests contain the prepared remediation.
No CRITICAL issue was established. CLI faults below are verified defects, not
claims of a remotely exploitable service.

| Severity | Finding and evidence | Prepared disposition |
|---|---|---|
| HIGH | [Unchecked argument increments and decimal conversion](https://github.com/qyoocode/QyooGenerate-C/blob/c980898409db454a58c152c3e6d8d94f79538837/src/qyoo.c#L47) cause crashes on missing values and accept malformed/overflow IDs, silently keeping only low 36 bits. | Validate option values and strict unsigned decimal range before rendering; test missing arguments, invalid text, 2^36, ULL overflow, and boundaries. |
| HIGH | [SVG builder allocation](https://github.com/qyoocode/QyooGenerate-C/blob/c980898409db454a58c152c3e6d8d94f79538837/src/svg.c#L13) appends after failed realloc; initial buffer allocation is unchecked. | Sticky failure state, checked size arithmetic, checked initial allocation, checked save, allocation-failure injection test. |
| MEDIUM | [Unchecked dimensions and GD allocation](https://github.com/qyoocode/QyooGenerate-C/blob/c980898409db454a58c152c3e6d8d94f79538837/src/image_renderer.c#L10), and success exit status on output failure. | Strict dimensions 1–4096; check GD image creation and stdio write/close results; propagate CLI failure. Legacy void renderer/save entry points remain, with additive checked variants for CLI use. |
| MEDIUM | [SVG transparent fill truncation](https://github.com/qyoocode/QyooGenerate-C/blob/c980898409db454a58c152c3e6d8d94f79538837/src/svg_renderer.c#L23); arbitrary CLI colors are passed into SVG attributes. | Strict hex/transparent CLI color validation and skip transparent operations. This is input hardening, not evidence of a deployed injection vulnerability. |
| MEDIUM | Historical layout is different from current Qyoo-Web renderer. | Preserve geometry; document exact differences and reference status. No claim of current scanner conformance. |
| MEDIUM | [Standalone SVG helper](https://github.com/qyoocode/QyooGenerate-C/blob/c980898409db454a58c152c3e6d8d94f79538837/src/svg.c#L1) has no file-level provenance. | Preserve source and BSD license; require owner confirmation of authorship or upstream attribution/license. No evidence establishes infringement. |
| LOW | [Homebrew-specific build flags](https://github.com/qyoocode/QyooGenerate-C/blob/c980898409db454a58c152c3e6d8d94f79538837/src/Makefile#L3), inaccurate random-ID example and manual example scripts treated as tests. | pkg-config discovery and overrides; deterministic tests; concise corrected README; bounded random example and historical-script disclaimer. |
| LOW | No CI or output ignores. | Add Linux build/sanitizer workflow and ignore generated outputs. Workflow is prepared, not yet observed on GitHub. |

## Compatibility evidence

Read-only comparison: current local Qyoo-Web `4d2941c`,
`src/generator/qyoo-renderer.ts`, constants and `qyooBits`/`renderQyooSvg`.
Private source remains local and is not copied into this public repository.

- Decimal 0 through 68,719,476,735 is representable. Tests cover 0,1,2,32,2^35,
  alternating bits and maximum, plus binary equivalents.
- Both serialize 36 bits MSB first, in row-major order. Base36 is a URL-layer
  representation and is intentionally outside this CLI.
- C 512-unit export: circle center256, radius128; integer-truncated inner square
  size180, dot radius13; centers179,209,239,269,299,329.
- Web 256-unit export: circle center128, radius102; dots65,90,115,140,165,190,
  radius10. Web default uses black carrier on opaque white; C defaults to white
  carrier with black dots and transparent background. These are not geometrically
  identical at any uniform scale. No geometry change was made.
- PNG and SVG share C drawing operations; GD's inclusive rectangle edges and
  ellipse rasterization differ from analytic web PNG pixel-center rules.
- Detector round-trip and camera-image reliability: **NOT RUN**. This change does
  not qualify the generator against the shipping iOS scanner.
- Signature-cell/CRC-10, Manifest v1, resolver, native actions, AR and contracts
  are outside this generator; they are not claimed as implemented here.

## Exposure, licensing and history

Reviewed all tracked files and all three reachable commits (`git rev-list --all`,
`git ls-tree`, `git show`), including historical README and scripts. A local,
redacted scan checked credential-like names, private-key markers, AWS access-key
patterns, email/local-home paths, and copyright placeholders. No matches were
found. Manual review found no committed models, binaries, photographs, editor
state, or user-data fixtures. This is a bounded review of fetched reachable
history, not a guarantee about deleted remote refs, forks, or future commits.

`LICENSE` is complete BSD-3-Clause with existing 2024 Qyoo copyright preserved.
libgd is an external build dependency, not vendored. The installed validation
version was 2.3.3. Binary distributors must review libgd and transitive dependency
notices. SVG helper authorship is unresolved; no replacement license or assumed
attribution was invented. Trademark/patent rights require owner/legal review.

## Exact validation commands and results

Executed on macOS with existing Apple clang (`cc`), Python3 and installed libgd;
no dependency installation or large build was performed.

| Command | Result |
|---|---|
| `make -C src && python3 tests/test_cli.py` against original source plus new tests | FAIL: missing options caused SIGSEGV; malformed/range values, invalid dimensions, color and output-failure assertions failed; initial geometry expectation also needed correction from independently calculated integer layout. |
| `make -B -C src test` after fixes | PASS: 5 Python methods, including invalid-input subcases, numeric/binary geometry vectors, PNG header, transparency and write failure. |
| `make -B -C src test CFLAGS='-O1 -g -Wall -Wextra -Werror -std=c11 -fsanitize=address,undefined' LDFLAGS='-fsanitize=address,undefined'` | PASS after replacing deprecated sprintf and correcting allocation-test expectation for non-triggered injection points: 5 Python methods plus SVG allocator-failure sweep. No ASan/UBSan diagnostics. |
| `git diff --check` | PASS. |
| `pkg-config --cflags --libs gdlib` | PASS: installed libgd discovered. |
| GitHub Linux CI | NOT RUN: workflow prepared locally only. |
| Full real-camera/iOS detector round-trip | NOT RUN: no detector qualification within this repository's small CLI suite. |

The SVG builder's failed-allocation path is exercised without exhausting memory.
GD internal encoder fault injection and disk-full faults are NOT RUN; checks
cover real missing-output-directory errors for PNG and SVG. No claim of a
formal security audit or exhaustive fuzzing is made.

## Storage and handoff

Before work: 20,857,440 KiB available (19.89 GiB), below the 20 GiB floor.
Storage-heavy builds, installs, and ML work stayed paused. The explicitly bounded
C verification reused existing dependencies and one output tree; generated
outputs stayed below 1 MiB. Latest measured free space and final output sizes
are recorded in the coordinating audit; filesystem changes include other active
sessions and cannot be attributed solely to this task. No files were deleted
or quarantined. Ignored bin/obj, failed-case PNGs and small test SVG/PNG evidence
are retained for review; no dated build trees or dependency copies were created.

Owner/legal actions: confirm SVG helper provenance; review trademark/patent
language separately from software copyright; decide whether a separately
versioned production-geometry mode is worthwhile only after cross-generator
qualification. Do not advertise this historical geometry as current production.
