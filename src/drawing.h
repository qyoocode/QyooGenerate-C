// drawing.h

#ifndef DRAWING_H
#define DRAWING_H

// Type of drawing operation
typedef enum {
    RECTANGLE,
    CIRCLE,
    DOT
} DrawingType;

// Structure to represent a drawing operation
typedef struct {
    DrawingType type;
    int x, y;
    int width, height; // Used for rectangles
    int radius;        // Used for circles and dots
    char* fill_color;
} DrawingOp;

#endif // DRAWING_H

