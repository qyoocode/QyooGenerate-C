#ifndef SVG_H
#define SVG_H

#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<math.h>

// --------------------------------------------------------
// STRUCT svg
// --------------------------------------------------------
typedef struct svg
{
    char* svg;
    int height;
    int width;
    bool finalized;
} svg;

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
svg* svg_create(int width, int height);
void svg_finalize(svg* psvg);
void svg_print(svg* psvg);
void svg_save(svg* psvg, char* filepath);
void svg_free(svg* psvg);
void svg_circle(svg* psvg, int cx, int cy, int r, char* fill);
void svg_rectangle(svg* psvg, int x, int y, int width, int height, char* fill);
void svg_fill(svg* psvg, char* fill);

#endif

