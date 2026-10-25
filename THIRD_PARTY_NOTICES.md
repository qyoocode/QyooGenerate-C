# Third-party notices

Qyoo is maintained by Pushplay LLC. Qyoo-owned code uses the repository’s
BSD-3-Clause license; historical copyright notices remain unchanged.

## libgd

PNG generation uses [libgd](https://libgd.github.io/), installed separately rather
than vendored here. Its author credits and permissive license are preserved in
[LICENSES/libgd-COPYING.txt](LICENSES/libgd-COPYING.txt), copied from libgd2.3.3’s
`COPYING` file. The [upstream2.3.3 notice](https://github.com/libgd/libgd/blob/gd-2.3.3/COPYING)
requires credit in user-accessible supporting documentation. Distributors of
linked binaries must also preserve notices for their actual libgd version and
its linked dependencies. This project does not relicense those dependencies.

## Historical SVG helper

The former `src/svg.c`/`src/svg.h` helper had no established applicable upstream
grant. Related code appears in section7.9 of the
[2018 Columbia SSOL report](https://www.cs.columbia.edu/~sedwards/classes/2018/4115-fall/reports/SSOL.pdf),
which establishes earlier related source, not a redistribution license or proof
of direct derivation. The current helper is a small original BSD-3-Clause
implementation written from the renderer’s required circle/rectangle interface.
The former implementation remains in Git history; this change does not rewrite
history or claim a license for historical third-party material.
