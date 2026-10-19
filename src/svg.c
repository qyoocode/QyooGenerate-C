#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"svg.h"
#include <stdint.h>

// --------------------------------------------------------
// STATIC FUNCTION appendstringtosvg
// --------------------------------------------------------
static void appendstringtosvg(svg* psvg, char* text)
{
    if (!psvg || psvg->failed) return;
    size_t current = strlen(psvg->svg), extra = strlen(text);
    if (extra > SIZE_MAX - current - 1) { psvg->failed = true; return; }
    char *p = realloc(psvg->svg, current + extra + 1);
    if (!p) { psvg->failed = true; return; }
    psvg->svg = p;
    memcpy(psvg->svg + current, text, extra + 1);
}

// --------------------------------------------------------
// STATIC FUNCTION appendnumbertosvg
// --------------------------------------------------------
static void appendnumbertosvg(svg* psvg, int n)
{
    char sn[16];

    snprintf(sn, sizeof(sn), "%d", n);

    appendstringtosvg(psvg, sn);
}

// --------------------------------------------------------
// FUNCTION svg_create
// --------------------------------------------------------
svg* svg_create(int width, int height)
{
    svg* psvg = malloc(sizeof(svg));

    if(psvg != NULL)
    {
        *psvg = (svg){.svg = NULL, .width = width, .height = height, .finalized = false};

        psvg->svg = malloc(1);

        if (!psvg->svg) { free(psvg); return NULL; }
        psvg->svg[0] = '\0';

        appendstringtosvg(psvg, "<svg width='");
        appendnumbertosvg(psvg, width);
        appendstringtosvg(psvg, "px' height='");
        appendnumbertosvg(psvg, height);
        appendstringtosvg(psvg, "px' xmlns='http://www.w3.org/2000/svg' version='1.1' xmlns:xlink='http://www.w3.org/1999/xlink'>\n");

        return psvg;
    }
    else
    {
        return NULL;
    }
}

// --------------------------------------------------------
// FUNCTION svg_finalize
// --------------------------------------------------------
void svg_finalize(svg* psvg)
{
    appendstringtosvg(psvg, "</svg>");

    psvg->finalized = true;
}

// --------------------------------------------------------
// FUNCTION svg_circle
// --------------------------------------------------------
void svg_circle(svg* psvg, int cx, int cy, int r, char* fill)
{
    appendstringtosvg(psvg, "    <circle cx='");
    appendnumbertosvg(psvg, cx);
    appendstringtosvg(psvg, "' cy='");
    appendnumbertosvg(psvg, cy);
    appendstringtosvg(psvg, "' r='");
    appendnumbertosvg(psvg, r);
    appendstringtosvg(psvg, "' fill='");
    appendstringtosvg(psvg, fill);
    appendstringtosvg(psvg, "' />\n");
}

// --------------------------------------------------------
// FUNCTION svg_rectangle
// --------------------------------------------------------
void svg_rectangle(svg* psvg, int x, int y, int width, int height, char* fill)
{
    appendstringtosvg(psvg, "    <rect x='");
    appendnumbertosvg(psvg, x);
    appendstringtosvg(psvg, "' y='");
    appendnumbertosvg(psvg, y);
    appendstringtosvg(psvg, "' width='");
    appendnumbertosvg(psvg, width);
    appendstringtosvg(psvg, "' height='");
    appendnumbertosvg(psvg, height);
    appendstringtosvg(psvg, "' fill='");
    appendstringtosvg(psvg, fill);
    appendstringtosvg(psvg, "' />\n");
}

// --------------------------------------------------------
// FUNCTION svg_save
// --------------------------------------------------------
int svg_save_checked(svg* psvg, char* filepath)
{
    if(!psvg->finalized)
    {
        svg_finalize(psvg);
    }

    if (psvg->failed) return 0;
    FILE *fp = fopen(filepath, "w");
    if (!fp) return 0;
    size_t length = strlen(psvg->svg);
    int ok = fwrite(psvg->svg, 1, length, fp) == length;
    if (fclose(fp) != 0) ok = 0;
    return ok;
}

// --------------------------------------------------------
// FUNCTION svg_free
// --------------------------------------------------------
void svg_free(svg* psvg)
{
    free(psvg->svg);
    free(psvg);
}


void svg_save(svg* psvg, char* filepath)
{
    (void)svg_save_checked(psvg, filepath);
}
