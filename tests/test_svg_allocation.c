/* Exercise every SVG builder allocation failure without exhausting memory. */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
static int allocations, fail_at;
static void *test_malloc(size_t size) {
    return ++allocations == fail_at ? NULL : malloc(size);
}
static void *test_realloc(void *ptr, size_t size) {
    return ++allocations == fail_at ? NULL : realloc(ptr, size);
}
#define malloc test_malloc
#define realloc test_realloc
#include "../src/svg.c"
#undef malloc
#undef realloc
int main(void) {
    for (fail_at = 1; fail_at < 40; ++fail_at) {
        allocations = 0;
        svg *image = svg_create(512, 512);
        if (!image) continue;
        svg_circle(image, 256, 256, 128, "#ffffff");
        svg_rectangle(image, 256, 256, 128, 128, "#ffffff");
        svg_finalize(image);
        if (allocations >= fail_at) assert(image->failed);
        svg_free(image);
    }
    puts("SVG allocation failure checks passed");
    return 0;
}
