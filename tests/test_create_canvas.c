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

#define OUTPUT_FILE "simple.dat"

int main(int argc, char** argv) {
    struct canvas* canvas = animate_create_canvas(8, 8, animate_color_argb(0, 0, 0, 0));
    if (canvas == NULL){
        printf("Failed to create canvas\n");
        return -1;
    }

    if (canvas -> height != 8){
        printf("Canvas height is incorrect\n");
        return -1;
    }

    if (canvas -> width != 8){
        printf("Canvas width is incorrect\n");
        return -1;
    }

    if (canvas -> background_color != animate_color_argb(0, 0, 0, 0)){
        printf("Canvas background color is incorrect\n");
        return -1;
    }
}