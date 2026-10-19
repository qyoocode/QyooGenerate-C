#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "qyoo_generator.h"
#include "image_renderer.h"
#include "svg_renderer.h"

#define QYOO_MAX 68719476735ULL
#define MAX_DIMENSION 4096

static void print_help(void) {
    puts("Usage: qyoo -id ID [-o FILE] [-w WIDTH] [-h HEIGHT] [-svg]\n"
         "ID: decimal 0..68719476735, or exactly 36 binary digits.\n"
         "Dimensions: 1..4096 (default 512). Default output: ../output/ID.png\n"
         "Colors: -fg, -dot, -bg accept #rrggbb, rrggbb, or transparent.\n"
         "Defaults: white foreground, black dots, transparent background.\n"
         "Use --help for help; -v or --verbose for drawing operations.");
}

static int parse_decimal(const char *text, unsigned long long max, unsigned long long *value) {
    if (!text || !*text) return 0;
    for (const char *p = text; *p; ++p)
        if (*p < '0' || *p > '9') return 0;
    errno = 0;
    char *end;
    unsigned long long parsed = strtoull(text, &end, 10);
    if (errno == ERANGE || *end || parsed > max) return 0;
    *value = parsed;
    return 1;
}

static int valid_color(const char *color) {
    if (strcmp(color, "transparent") == 0) return 1;
    if (*color == '#') ++color;
    if (strlen(color) != 6) return 0;
    for (int i = 0; i < 6; ++i)
        if (!isxdigit((unsigned char)color[i])) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    char *output_filename = NULL;
    char default_filename[64];
    char binary_string[37] = {0};
    unsigned long long number = 0;
    int width = 512, height = 512, svg_output = 0, verbose = 0;
    char *fg_color = "#ffffff", *dot_color = "#000000", *bg_color = "transparent";
    if (argc == 1) { print_help(); return 1; }
    for (int i = 1; i < argc; ++i) {
        char *option = argv[i];
        if (!strcmp(option, "--help")) { print_help(); return 0; }
        if (!strcmp(option, "-svg")) { svg_output = 1; continue; }
        if (!strcmp(option, "-v") || !strcmp(option, "--verbose") || !strcmp(option, "-verbose")) {
            verbose = 1; continue;
        }
        if (strcmp(option, "-id") && strcmp(option, "-o") && strcmp(option, "-w") &&
            strcmp(option, "-h") && strcmp(option, "-fg") && strcmp(option, "-dot") && strcmp(option, "-bg")) {
            fprintf(stderr, "Unknown option: %s\n", option); return 1;
        }
        if (i + 1 >= argc) { fprintf(stderr, "Missing value for %s\n", option); return 1; }
        char *value = argv[++i];
        if (!strcmp(option, "-id")) {
            if (is_binary_string(value)) {
                memcpy(binary_string, value, sizeof(binary_string));
                number = binary_string_to_number(binary_string);
            } else {
                if (!parse_decimal(value, QYOO_MAX, &number)) {
                    fputs("Invalid ID: expected decimal 0..68719476735 or 36 binary digits\n", stderr); return 1;
                }
                number_to_binary_string(number, binary_string, 36);
            }
        } else if (!strcmp(option, "-o")) {
            if (!*value) { fputs("Empty output filename\n", stderr); return 1; }
            output_filename = value;
        } else if (!strcmp(option, "-w") || !strcmp(option, "-h")) {
            unsigned long long dimension;
            if (!parse_decimal(value, MAX_DIMENSION, &dimension) || dimension == 0) {
                fputs("Dimensions must be integers from 1 through 4096\n", stderr); return 1;
            }
            if (!strcmp(option, "-w")) width = (int)dimension; else height = (int)dimension;
        } else {
            if (!valid_color(value)) { fputs("Invalid color: expected rrggbb, #rrggbb, or transparent\n", stderr); return 1; }
            if (!strcmp(option, "-fg")) fg_color = value;
            else if (!strcmp(option, "-dot")) dot_color = value;
            else bg_color = value;
        }
    }
    if (!binary_string[0]) { fputs("The -id option is required\n", stderr); return 1; }
    if (!output_filename) {
        snprintf(default_filename, sizeof(default_filename), "../output/%llu.%s", number, svg_output ? "svg" : "png");
        output_filename = default_filename;
    }
    size_t len = strlen(output_filename);
    if (len >= 4 && !strcmp(output_filename + len - 4, ".svg")) svg_output = 1;
    DrawingOp ops[100];
    int op_count;
    generate_qyoo(ops, &op_count, width, height, fg_color, dot_color, bg_color, binary_string, verbose);
    int ok = svg_output ? render_svg_checked(ops, op_count, width, height, output_filename, verbose)
                        : render_image_checked(ops, op_count, width, height, output_filename, verbose);
    if (!ok) { fputs("Could not write output\n", stderr); return 1; }
    return 0;
}
