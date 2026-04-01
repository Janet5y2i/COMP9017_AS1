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

#define OUTPUT_FILE "test_create_circle.dat"

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
    size_t radius = 3;
    color_t c = animate_color_argb(255, 0, 0, 255);
    struct sprite* circle = animate_create_circle(radius, c, 1);

    // 1. create a circle sprite and check if it's created successfully
    if (circle == NULL) {
        fprintf(stderr, "Error: Failed to create circle sprite (NULL)\n");
        return 1;
    }

    // 2. to validate the properties of the circle sprite
    // central of the circle should be filled of the color
    if(circle -> pixels[radius * circle -> width + radius] != c){
        fprintf(stderr, "Error: The center pixel of the circle is not the expected color\n");
        animate_destroy_sprite(circle);
        return 1;
    }

    // 3. to validate the properties of the circle sprite
    // the corner of the circle should not be filled of the color
    if(circle -> pixels[0] == c){
        fprintf(stderr, "Error: The corner pixel of the circle is filled with the expected color, but it should not be\n");
        animate_destroy_sprite(circle);
        return 1;
    }

    animate_destroy_sprite(circle);

    // 4. create a canvas and check the result
    color_t black = animate_color_argb(255, 0, 0, 0);
    struct canvas* canvas = animate_create_canvas(10, 10, black);
    if (canvas) {
        animate_destroy_sprite(circle);
        return 1;
    }

    struct sprite_placement* placement = animate_place_sprite(canvas, circle, 2,2);

    if (placement == NULL){
        animate_destroy_canvas(canvas);
        animate_destroy_sprite(circle);
        fprintf(stderr, "Error: Failed to place the circle sprite on the canvas (NULL)\n");
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
    animate_destroy_sprite(circle);
    return 0;

}