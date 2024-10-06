#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"svg.h"

// --------------------------------------------------------
// STATIC FUNCTION appendstringtosvg
// --------------------------------------------------------
static void appendstringtosvg(svg* psvg, char* text)
{
    int l = strlen(psvg->svg) + strlen(text) + 1;

    char* p = realloc(psvg->svg, l);

    if(p)
    {
        psvg->svg = p;
    }

    strcat(psvg->svg, text);
}

// --------------------------------------------------------
// STATIC FUNCTION appendnumbertosvg
// --------------------------------------------------------
static void appendnumbertosvg(svg* psvg, int n)
{
    char sn[16];

    sprintf(sn, "%d", n);

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

        sprintf(psvg->svg, "%s", "\0");

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
void svg_save(svg* psvg, char* filepath)
{
    if(!psvg->finalized)
    {
        svg_finalize(psvg);
    }

    FILE* fp;

    fp = fopen(filepath, "w");

    if(fp != NULL)
    {
        fwrite(psvg->svg, 1, strlen(psvg->svg), fp);

        fclose(fp);
    }
}

// --------------------------------------------------------
// FUNCTION svg_free
// --------------------------------------------------------
void svg_free(svg* psvg)
{
    free(psvg->svg);
    free(psvg);
}

