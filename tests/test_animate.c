#include "animate.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


struct sprite {
    // TODO
    size_t width;
    size_t height;
    color_t color;
    color_t *pixels;
    bool filled;
    int cnt;

};

// varified the move ove the sprite
int main(int argc, char** argv) {
    // create a sprite 10*10
    color_t c = animate_color_argb(255, 255, 255, 255);
    struct sprite* rectangle = animate_create_rectangle(3, 3, c, true);

    // create a canvas
    struct canvas* canvas = animate_create_canvas(12, 12, animate_color_argb(0, 0, 0, 0));
    
    // place the sprite at 0,0
    // set the param: yx = 10 , ay = 0
    struct sprite_placement* placement = animate_place_sprite(canvas, rectangle, 0, 0);
    animate_set_animation_params(placement, 0, 10, 0, 0);

    size_t frame_size = animate_frame_size_bytes(canvas);
    void* data = malloc(frame_size);

    // first test t = 0, should be at (0,0)
    animate_generate_frame(canvas, 0, 25, data);
    FILE* fp1 = fopen("test_animate_t0.dat", "wb");
    fwrite(data, 1, frame_size, fp1);
    fclose(fp1);

    // second test t = 1 frame = 25
    // x = 0 + 10*1 + 0 = 10 (10, 0)
    animate_generate_frame(canvas, 25, 25, data);
    FILE* fp2 = fopen("test_animate_t1.dat", "wb");
    fwrite(data, 1, frame_size, fp2);
    fclose(fp2);


    free(data);
    animate_destroy_canvas(canvas);
    animate_destroy_sprite(rectangle);

    return 0;
}