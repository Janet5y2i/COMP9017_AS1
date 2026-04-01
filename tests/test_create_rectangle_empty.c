/**
 * A simple test file to help you get started
 */

#include "animate.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define OUTPUT_FILE "test_create_rectangle_empty.dat"

struct sprite {
    // TODO
    size_t width;
    size_t height;
    color_t color;
    color_t *pixels;
    bool filled;
    int cnt;

};

int main(int argc, char** argv) {
    size_t height = 4;
    size_t width = 4;
    color_t c = animate_color_argb(255, 255, 255, 255);
    struct sprite* rectangle = animate_create_rectangle(width, height, c, 0);

    // 1. create a circle sprite and check if it's created successfully
    if (rectangle == NULL) {
        fprintf(stderr, "Error: Failed to create rectangle sprite (NULL)\n");
        return 1;
    }


    // 2. check the sprite_placement function and animate_create_circle
    // if the rectangle is right and can be place on the canvas
    color_t canvas_color = animate_color_argb(0, 0, 0, 0);
    struct canvas* canvas = animate_create_canvas(8, 8, canvas_color);
    if (canvas == NULL) {
        animate_destroy_sprite(rectangle);
        return 1;
    }

    struct sprite_placement* placement = animate_place_sprite(canvas, rectangle, 0,0);

    if (placement == NULL){
        animate_destroy_canvas(canvas);
        animate_destroy_sprite(rectangle);
        fprintf(stderr, "Error: Failed to place the cirectanglercle sprite on the canvas (NULL)\n");
        return 1;
    }

    
    size_t frame_size_bytes = animate_frame_size_bytes(canvas);
    void* data = malloc(frame_size_bytes);
    animate_generate_frame(canvas, 0, 1, data);

    FILE* fp = fopen(OUTPUT_FILE, "wb");
    fwrite(data, 1, frame_size_bytes, fp);
    fclose(fp);

    free(data);
    
    animate_destroy_canvas(canvas);
    animate_destroy_sprite(rectangle);
    return 0;

}