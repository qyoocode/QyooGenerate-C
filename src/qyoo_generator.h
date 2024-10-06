#ifndef QYOO_GENERATOR_H
#define QYOO_GENERATOR_H

#include "drawing.h"

void generate_qyoo(DrawingOp *ops, int *op_count, int width, int height, char *fg_color, char *dot_color, char *bg_color, char *binary_string, int verbose);

int is_binary_string(const char *input);
void number_to_binary_string(unsigned long long number, char *binary_string, int size);
unsigned long long binary_string_to_number(const char *binary_string);

#endif

