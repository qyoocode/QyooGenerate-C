#ifndef SVG_RENDERER_H
#define SVG_RENDERER_H

#include "drawing.h"

void render_svg(DrawingOp *ops, int op_count, int width, int height, char *output_filename, int verbose);

#endif

