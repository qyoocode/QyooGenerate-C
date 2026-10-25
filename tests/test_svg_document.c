/* The serializer must preserve geometry and finalize a document only once. */
#include <assert.h>
#include <string.h>
#include "../src/svg.h"

int main(void) {
    svg *image = svg_create(68, 35);
    assert(image);
    svg_circle(image, 23, 6, 1, "#123456");
    svg_rectangle(image, 34, 17, 17, 17, "#abcdef");
    svg_finalize(image);
    assert(!image->failed);
    const char *closing = strstr(image->svg, "</svg>");
    assert(closing);
    assert(strstr(image->svg, "cx='23' cy='6' r='1' fill='#123456'"));
    assert(strstr(image->svg, "x='34' y='17' width='17' height='17' fill='#abcdef'"));
    size_t length = strlen(image->svg);
    svg_finalize(image);
    assert(strlen(image->svg) == length);
    assert(strstr(closing + 6, "</svg>") == NULL);
    svg_free(image);
    image = svg_create(68, 35);
    assert(image);
    svg_circle(image, 23, 6, 1, "#fff'bad");
    assert(image->failed); /* The helper cannot emit attribute injection. */
    svg_free(image);
    svg_free(NULL);
    return 0;
}
