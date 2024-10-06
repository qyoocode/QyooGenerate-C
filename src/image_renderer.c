// image_renderer.c

#include <gd.h>
#include "drawing.h"
#include <string.h>
#include <stdio.h>

void render_image(DrawingOp *ops, int op_count, int width, int height, char *output_filename, int verbose) {
    // Create the image (with true color and transparency support)
    gdImagePtr im = gdImageCreateTrueColor(width, height);
    gdImageAlphaBlending(im, 0);    // Disable alpha blending (to support transparency)
    gdImageSaveAlpha(im, 1);        // Enable saving the alpha channel

    // Render each operation
    for (int i = 0; i < op_count; i++) {
        DrawingOp op = ops[i];

        if (verbose == 1) {
            printf("Processing operation %d: Type=%d, x=%d, y=%d, width=%d, height=%d, radius=%d, fill_color=%s\n",
               i, op.type, op.x, op.y, op.width, op.height, op.radius, op.fill_color);
        }

        // Parse the color from the hex string
        int red = 0, green = 0, blue = 0;
        int fill_color;

        // Handle transparent color
        if (strcmp(op.fill_color, "transparent") == 0) {
            // Fully transparent color
            fill_color = gdImageColorAllocateAlpha(im, 0, 0, 0, 127);
        } else {

            // Check if the first character is '#'
            if (op.fill_color[0] == '#') {
                // Parse the hex color value, assuming format "#rrggbb"
                sscanf(op.fill_color + 1, "%2x%2x%2x", &red, &green, &blue);
            } else {
                // Parse the hex color value, assuming format "rrggbb" (no #)
                sscanf(op.fill_color, "%2x%2x%2x", &red, &green, &blue);
            }

            fill_color = gdImageColorAllocate(im, red, green, blue);
        }

        // Draw the shapes based on the operation type
        if (op.type == RECTANGLE) {
            gdImageFilledRectangle(im, op.x, op.y, op.x + op.width, op.y + op.height, fill_color);
        } else if (op.type == CIRCLE || op.type == DOT) {
            gdImageFilledEllipse(im, op.x, op.y, op.radius * 2, op.radius * 2, fill_color);
        }
    }

    // Save to file
    FILE *out = fopen(output_filename, "wb");
    if (out) {
        gdImagePng(im, out);
        fclose(out);
    } else {
        fprintf(stderr, "Error: Could not open output file %s for writing\n", output_filename);
    }

    // Cleanup
    gdImageDestroy(im);
}
