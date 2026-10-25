/* SPDX-License-Identifier: BSD-3-Clause
 * Qyoo SVG serialization interface. Original replacement, 2026.
 */
#ifndef QYOO_SVG_H
#define QYOO_SVG_H

#include <stdbool.h>
#include <stddef.h>

typedef struct svg {
    char *svg;
    size_t length;
    size_t capacity;
    int width;
    int height;
    bool finalized;
    bool failed;
} svg;

svg *svg_create(int width, int height);
void svg_circle(svg *image, int cx, int cy, int radius, char *fill);
void svg_rectangle(svg *image, int x, int y, int width, int height, char *fill);
void svg_fill(svg *image, char *fill);
void svg_finalize(svg *image);
int svg_save_checked(svg *image, char *path);
void svg_save(svg *image, char *path);
void svg_print(svg *image);
void svg_free(svg *image);

#endif
