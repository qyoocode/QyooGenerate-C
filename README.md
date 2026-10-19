# QyooGenerate-C

A C command-line reference generator for the historical Qyoo visual carrier.
It writes PNG (through libgd) and SVG images for a 36-bit payload. This is a
reference tool, not the production Qyoo 4.0 renderer, resolver, or scanner.

## Build and test

Requires a C11 compiler, Make, pkg-config, libgd development headers, and Python 3
for tests. For example, install `gd pkg-config` with Homebrew on macOS, or
`build-essential pkg-config libgd-dev python3` using your Linux package manager.

```sh
make -C src
make -C src test
```

The Makefile discovers libgd through `pkg-config gdlib`. For another installation,
pass `GD_CFLAGS` and `GD_LIBS` explicitly. `CC`, `CFLAGS`, `LDFLAGS`, `OBJDIR`, and
`EXEDIR` are overridable. Build outputs go to `obj/` and `bin/`; images default to
`output/`. There is no destructive cleanup target.

## Generate an image

Run these examples from `src/`, because the default output directory is relative
to the current working directory. An explicit `-o` works from any directory.

```sh
../bin/qyoo -id 12345 -o ../output/12345.png
../bin/qyoo -id 68719476735 -svg -o ../output/max.svg
../bin/qyoo -id 010101010101010101010101010101010101 -svg -o ../output/alternating.svg
../bin/qyoo -id 12345 -fg '#000000' -dot '#ffffff' -bg '#ffffff' -o ../output/black.png
```

`-id` accepts decimal **0 through 68,719,476,735**, or exactly 36 binary digits.
Exactly 36 binary digits always mean binary; shorter digit strings mean decimal.
Signs, spaces, trailing characters, and overflow are rejected. Base36 URL route
representations are not accepted by this generator and do not change visual bits.

Options: `-o FILE`, `-svg`, `-w WIDTH`, `-h HEIGHT`, `-fg COLOR`, `-dot COLOR`,
`-bg COLOR`, `-v`/`--verbose`, `--help`. Width and height default to 512 and are
limited to 1–4096 each, bounding raster memory (about 64 MiB of pixel storage at
the maximum, plus library overhead). Small or clipped images may be unreadable;
accepted dimensions do not guarantee scanner success. Colors must be six hex
digits, optionally prefixed with `#`, or `transparent`. Defaults preserve the
historical white carrier, black dots, and transparent background. Errors return
a nonzero exit status; a failed write can leave a partial output file.

A bounded random ID, using Python rather than shell integer-width assumptions:

```sh
ID=$(python3 -c 'import secrets; print(secrets.randbelow(1 << 36))')
../bin/qyoo -id "$ID" -o ../output/random.png
```

## Compatibility and limits

Serialization is 36 bits, most significant bit first, row by row from top left
through bottom right. This agrees with the current Qyoo 4.0 payload ordering.
The C generator's historical geometry differs from the current web renderer.
At 512×512 its carrier center is (256,256), radius 128; dot centers span
179–329 in steps of 30, with radius 13. The web renderer's 256-unit export uses a
carrier radius of 102 and dot centers 65–190 in steps of 25, radius 10, with an
opaque white quiet zone and black carrier. Scaling and color changes alone do
not make these layouts identical. PNG libgd rasterization also differs from the
web renderer's pixel-center tests. Existing C geometry is preserved here.

No scan-success rate or physical-camera compatibility is established by these
CLI tests. The generator does not implement signature-cell/CRC-10 proposals,
Manifest v1 experiences, ID allocation, Base36 routing, or Ethereum minting.

`tests/` checks parsing, numeric/binary equivalence, row-major placement, PNG
output, transparent SVG handling, allocation failure handling, and output errors.
`scripts/` contains historical image-generation examples, not an assertion-based
test suite; some need GNU `shuf`. Do not use them as evidence of scanner quality.

## Licensing and provenance

Repository code is distributed under [BSD-3-Clause](LICENSE). PNG generation
links against separately installed libgd; retain its applicable license and
third-party notices when redistributing linked binaries. This repository does
not vendor libgd. Software licensing does not establish trademark or patent
rights in the Qyoo symbol. Ownership/provenance of the standalone SVG helper
still requires maintainer confirmation; see [AUDIT.md](AUDIT.md).
