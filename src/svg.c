/* SPDX-License-Identifier: BSD-3-Clause
 * Original Qyoo SVG serializer, 2026. No external SVG helper code is used.
 * Drawing coordinates and colors are supplied by the historical renderer.
 */
#include "svg.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Format one complete element, retaining a sticky allocation/write failure. */
static void emit(svg *image, const char *format, ...) {
    if (!image || image->failed || image->finalized) return;
    va_list args, measure;
    va_start(args, format);
    va_copy(measure, args);
    int count = vsnprintf(NULL, 0, format, measure);
    va_end(measure);
    if (count < 0 || (size_t)count > SIZE_MAX - image->length - 1) {
        image->failed = true;
        va_end(args);
        return;
    }
    size_t required = image->length + (size_t)count + 1;
    if (required > image->capacity) {
        size_t capacity = required > SIZE_MAX / 2 ? required : required * 2;
        char *buffer = realloc(image->svg, capacity);
        if (!buffer) {
            image->failed = true;
            va_end(args);
            return;
        }
        image->svg = buffer;
        image->capacity = capacity;
    }
    if (vsnprintf(image->svg + image->length, (size_t)count + 1,
                  format, args) != count) {
        image->failed = true;
    } else {
        image->length += (size_t)count;
    }
    va_end(args);
}

svg *svg_create(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;
    svg *image = malloc(sizeof(*image));
    if (!image) return NULL;
    *image = (svg){.width = width, .height = height};
    emit(image, "<svg xmlns='http://www.w3.org/2000/svg' width='%dpx' height='%dpx'>\n",
         width, height);
    return image;
}

/* The renderer supplies validated six-digit hex colors, never arbitrary XML. */
static bool valid_color(const char *color) {
    if (!color || *color++ != '#') return false;
    for (int i = 0; i < 6; ++i) {
        unsigned char c = (unsigned char)*color++;
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
              (c >= 'A' && c <= 'F'))) return false;
    }
    return *color == '\0';
}

void svg_circle(svg *image, int cx, int cy, int radius, char *fill) {
    if (!image) return;
    if (!valid_color(fill)) { image->failed = true; return; }
    emit(image, "  <circle cx='%d' cy='%d' r='%d' fill='%s'/>\n", cx, cy, radius, fill);
}

void svg_rectangle(svg *image, int x, int y, int width, int height, char *fill) {
    if (!image) return;
    if (!valid_color(fill)) { image->failed = true; return; }
    emit(image, "  <rect x='%d' y='%d' width='%d' height='%d' fill='%s'/>\n",
         x, y, width, height, fill);
}

void svg_fill(svg *image, char *fill) {
    if (image) svg_rectangle(image, 0, 0, image->width, image->height, fill);
}

void svg_finalize(svg *image) {
    if (!image || image->finalized) return;
    emit(image, "</svg>\n");
    image->finalized = true;
}

int svg_save_checked(svg *image, char *path) {
    if (!image || !path) return 0;
    svg_finalize(image);
    if (image->failed) return 0;
    FILE *output = fopen(path, "wb");
    if (!output) return 0;
    int success = fwrite(image->svg, 1, image->length, output) == image->length;
    if (fclose(output) != 0) success = 0;
    return success;
}

void svg_save(svg *image, char *path) { (void)svg_save_checked(image, path); }

void svg_print(svg *image) {
    if (!image) return;
    svg_finalize(image);
    if (!image->failed && fwrite(image->svg, 1, image->length, stdout) != image->length)
        image->failed = true;
}

void svg_free(svg *image) {
    if (!image) return;
    free(image->svg);
    free(image);
}
