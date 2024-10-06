#ifndef IMAGE_RENDERER_H
#define IMAGE_RENDERER_H

#include "drawing.h"

void render_image(DrawingOp *ops, int op_count, int width, int height, char *output_filename, int verbose);

#endif

