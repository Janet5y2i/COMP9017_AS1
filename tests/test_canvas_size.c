/**
 * Test case for animate_create_canvas function
 */
#include "animate.h"
#include <stdio.h>
#include <stdlib.h>

struct canvas {
    size_t height;
    size_t width;
    color_t background_color;
    void *head;
    void *tail;
};

int main(int argc, char** argv) {
    size_t h = 8;
    size_t w = 10;
    color_t bg = animate_color_argb(255, 0, 0, 0);

    // 1. create a canvas and check if it's created successfully
    struct canvas* canvas = animate_create_canvas(h, w, bg);
    if (canvas == NULL) {
        fprintf(stderr, "Error: Failed to create canvas (NULL)\n");
        return 1;
    }

    // 2. to validate the properties of the canvas
    // expected size = height * width * sizeof(color_t)
    size_t expected_size = h * w * sizeof(color_t);
    size_t frame_size_bytes = animate_frame_size_bytes(canvas);

    if (expected_size != frame_size_bytes) {
        return 1;
        animate_destroy_canvas(canvas);
    }

    animate_destroy_canvas(canvas);

    return 0;
}