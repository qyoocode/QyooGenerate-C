#include "drawing.h"
#include "svg.h"
#include <stdio.h>
#include <string.h>

void render_svg(DrawingOp *ops, int op_count, int width, int height, char *output_filename, int verbose) {
    // Create SVG
    svg* psvg = svg_create(width, height);

    // Render each operation
    for (int i = 0; i < op_count; i++) {
        DrawingOp op = ops[i];

        if (verbose == 1) {
            printf("Processing operation %d: Type=%d, x=%d, y=%d, width=%d, height=%d, radius=%d, fill_color=%s\n",
               i, op.type, op.x, op.y, op.width, op.height, op.radius, op.fill_color);
        }


        // Handle color formatting for SVG (prepend '#' if missing)
        char fill_color[8];  // Enough for "#rrggbb\0"
        if (op.fill_color[0] != '#') {
            snprintf(fill_color, sizeof(fill_color), "#%s", op.fill_color);
        } else {
            strncpy(fill_color, op.fill_color, sizeof(fill_color));
        }

        // Handle transparent case and valid operations
        if (op.type == RECTANGLE) {
            if (strcmp(op.fill_color, "transparent") != 0) {
                svg_rectangle(psvg, op.x, op.y, op.width, op.height, fill_color);
            } else {
                printf("Skipping transparent rectangle\n");
            }
        } else if (op.type == CIRCLE || op.type == DOT) {
            svg_circle(psvg, op.x, op.y, op.radius, fill_color);
        } else {
            printf("Skipping unknown operation type: %d\n", op.type);
        }
    }

    // Save the file
    printf("Saving SVG to: %s\n", output_filename);
    svg_save(psvg, output_filename);
    svg_free(psvg);
}
