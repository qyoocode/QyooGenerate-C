#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qyoo_generator.h"
#include "image_renderer.h"
#include "svg_renderer.h"
#include "drawing.h"

// Function to print help
void print_help() {
    printf("Usage: qyoo [options]\n");
    printf("Options:\n");
    printf("  -id [number]         Set the numeric ID (required)\n");
    printf("  -o [filename]        Output filename (default: [number].png or [number].svg)\n");
    printf("  -w [width]           Set the width of the image (default: 512)\n");
    printf("  -h [height]          Set the height of the image (default: 512)\n");
    printf("  -fg [color]          Set the foreground color (default: #ffffff)\n");
    printf("  -dot [color]         Set the dot color (default: #000000)\n");
    printf("  -bg [color]          Set the background color (default: transparent)\n");
    printf("  -svg                 Output the image as an .svg file\n");
    printf("  -verbose, -v         Verbose (print debug information)\n");
    printf("  --help, -h           Show this help message\n");
}

int main(int argc, char *argv[]) {
    // Default values
    char *output_filename = "";
    char binary_string[37] = {0};
    unsigned long long number = 0;  // Default number
    int width = 512, height = 512;
    int svg_output = 0;
    char *fg_color = "#ffffff"; // white
    char *dot_color = "#000000"; // black
    char *bg_color = "transparent"; // transparent background
    int verbose = 0;

    // Check for no parameters or help
    if (argc == 1 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            output_filename = argv[++i];
        } else if (strcmp(argv[i], "-w") == 0) {
            width = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-h") == 0) {
            height = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-fg") == 0) {
            fg_color = argv[++i];
        } else if (strcmp(argv[i], "-dot") == 0) {
            dot_color = argv[++i];
        } else if (strcmp(argv[i], "-bg") == 0) {
            bg_color = argv[++i];
        } else if (strcmp(argv[i], "-id") == 0) {
            // Check if the input is a binary string or a number
            if (is_binary_string(argv[++i])) {
                // If it's a valid binary string, use it directly
                strcpy(binary_string, argv[i]);
                number = binary_string_to_number(binary_string);
            } else {
                // Otherwise, treat it as a number and convert it
                number = strtoull(argv[i], NULL, 10);
                number_to_binary_string(number, binary_string, 36);
            }
        } else if (strcmp(argv[i], "-svg") == 0) {
	        svg_output = 1;
        } else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else {
            printf("Unknown argument: %s\n", argv[i]);
            return 1;
        }
    }

    // Check if a binary string or number was provided
    if (binary_string[0] == '\0') {
        printf("Please provide a valid number or 36-digit binary string using the -id option.\n");
        return 1;
    }

    // If no output filename, default to number-based name
    if (strcmp(output_filename, "") == 0) {
        if (svg_output) {
            asprintf(&output_filename, "../output/%llu.svg", number);
        } else {
            asprintf(&output_filename, "../output/%llu.png", number);
        }
    }

    // Auto-detect if the output should be SVG based on the file extension
    if (strstr(output_filename, ".svg") != NULL) {
        svg_output = 1;
    }

    // Generate Qyoo operations
    DrawingOp ops[100];
    int op_count;
    generate_qyoo(ops, &op_count, width, height, fg_color, dot_color, bg_color, binary_string, verbose);

    // Render to PNG or SVG
    if (svg_output) {
        render_svg(ops, op_count, width, height, output_filename, verbose);
    } else {
        render_image(ops, op_count, width, height, output_filename, verbose);
    }

    return 0;
}
