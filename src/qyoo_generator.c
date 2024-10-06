// qyoo_generator.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drawing.h"

void generate_qyoo(DrawingOp *ops, int *op_count, int width, int height, char *fg_color, char *dot_color, char *bg_color, char *binary_string, int verbose) {
    int radius = width / 4;
    int square_size = radius * 2 * 0.707;
    int center_x = width / 2;
    int center_y = height / 2;

    int op_index = 0;

    // Add background rectangle operation
    ops[op_index++] = (DrawingOp){RECTANGLE, 0, 0, width, height, 0, bg_color};

    // Add foreground circle operation
    ops[op_index++] = (DrawingOp){CIRCLE, center_x, center_y, 0, 0, radius, fg_color};

    // Add foreground square operation
    ops[op_index++] = (DrawingOp){RECTANGLE, center_x, center_y, radius, radius, 0, fg_color};

    // Add the 6x6 grid of dots based on the binary string
    int grid_size = 6;
    int dot_radius = square_size / (2 * grid_size);
    int binary_index = 0;

    // add a small bit of padding
    dot_radius = dot_radius - ((dot_radius + 9) / 10);

    for (int row = 0; row < grid_size; row++) {
        for (int col = 0; col < grid_size; col++) {
            int x = center_x - square_size / 2 + col * square_size / grid_size + dot_radius;
            int y = center_y - square_size / 2 + row * square_size / grid_size + dot_radius;

            if (binary_string[binary_index] == '1') {
                ops[op_index++] = (DrawingOp){DOT, x, y, 0, 0, dot_radius, dot_color};
            }
            binary_index++;
        }
    }

    *op_count = op_index; // Store the number of operations
}

// Function to check if the input is a 36-digit binary string
int is_binary_string(const char *input) {
    if (strlen(input) == 36) {
        for (int i = 0; i < 36; i++) {
            if (input[i] != '0' && input[i] != '1') {
                return 0;  // Not a binary string
            }
        }
        return 1;  // It's a valid binary string
    }
    return 0;  // Length isn't 36, so it's not a valid binary string
}

// Function to convert number to binary string
void number_to_binary_string(unsigned long long number, char *binary_string, int size) {
    for (int i = size - 1; i >= 0; i--) {
        binary_string[i] = (number & 1) ? '1' : '0';
        number >>= 1;
    }
    binary_string[size] = '\0';  // Null-terminate the string
}

// Function to convert binary string to a number
unsigned long long binary_string_to_number(const char *binary_string) {
    unsigned long long number = 0;
    for (int i = 0; i < 36; i++) {
        number <<= 1;  // Shift left by one
        if (binary_string[i] == '1') {
            number |= 1;  // Set the least significant bit if the character is '1'
        }
    }
    return number;
}