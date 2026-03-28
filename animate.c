#include "animate.h"

#include <stdio.h>
#include <stdlib.h>


struct sprite {
    // TODO
    size_t width;
    size_t height;
    color_t color;
    color_t *pixels;
    bool filled;

};

struct sprite_placement {
    // TODO
    struct sprite *ptr_s;
    struct canvas *ptr_c;
    ssize_t x;
    ssize_t y;
    ssize_t vx;
    ssize_t vy;
    ssize_t ax;
    ssize_t ay;
    struct sprite_placement *prev;
    struct sprite_placement *next;
};

struct canvas {
    // TODO
    size_t height;
    size_t width;
    color_t background_color;
    struct sprite_placement *head;
    struct sprite_placement *tail;

};



/* This is the header structure that we can expect to find at position 0 in a bitmap file. */
struct bitmap_header {
    uint8_t  magic[2];          // Expect {'B', 'M'}
    uint32_t size_bytes;        // Size of the file in bytes
    uint16_t reserved[2];
    uint32_t pixel_offset;      // Starting address of pixel data
// Don't pad this struct for alignment
} __attribute__((packed));

/*
 * This header immediately follows bitmap_header in the file.
 * You may ignore all fields except bV5Width and bV5Height, unless you'd like to validate
 * the image format
 */
struct bitmapv5_header {
                               // Offset     Size Description
    uint32_t bV5Size         ; // 0x00          4 Size of this header (124 bytes)
    uint32_t bV5Width        ; // 0x04          4 Width of the bitmap in pixels
    uint32_t bV5Height       ; // 0x08          4 Height of the bitmap in pixels
    uint16_t bV5Planes       ; // 0x0C          2 Number of planes (must be 1)
    uint16_t bV5BitCount     ; // 0x0E          2 Bits per pixel (e.g., 32)
    uint32_t bV5Compression  ; // 0x10          4 BI_RGB (0), BI_BITFIELDS (3)
    uint32_t bV5SizeImage    ; // 0x14          4 Size of image data (0 if uncompressed)
    uint32_t bV5XPelsPerMeter; // 0x18          4 Horizontal pixels per meter
    uint32_t bV5YPelsPerMeter; // 0x1C          4 Vertical pixels per meter
    uint32_t bV5ClrUsed      ; // 0x20          4 Number of color indices used
    uint32_t bV5ClrImportant ; // 0x24          4 Number of important colors
    uint32_t bV5RedMask      ; // 0x28          4 Color mask for red component
    uint32_t bV5GreenMask    ; // 0x2C          4 Color mask for green component
    uint32_t bV5BlueMask     ; // 0x30          4 Color mask for blue component
    uint32_t bV5AlphaMask    ; // 0x34          4 Color mask for alpha channel
    uint32_t bV5CSType       ; // 0x38          4 Color space type (e.g., LCS_CALIBRATED_RGB)
    uint8_t  bV5Endpoints[36]; // 0x3C-0x5B    36 CIE XYZ color space endpoints
    uint32_t bV5GammaRed     ; // 0x5C          4 Gamma red component
    uint32_t bV5GammaGreen   ; // 0x60          4 Gamma green component
    uint32_t bV5GammaBlue    ; // 0x64          4 Gamma blue component
    uint32_t bV5Intent       ; // 0x68          4 Rendering intent
    uint32_t bV5ProfileData  ; // 0x6C          4 Offset to ICC profile data
    uint32_t bV5ProfileSize  ; // 0x70          4 Size of embedded profile data
    uint32_t bV5Reserved     ; // 0x74          4 Reserved (must be 0)
};


struct canvas* animate_create_canvas(size_t height, size_t width,
                                     color_t background_color){
    // TODO

    struct canvas* cv = malloc(sizeof(struct canvas));
    
    if ( cv == NULL){
        printf("Memory allocate uncessefully");
        return NULL;
    }

    cv -> height = height;
    cv -> width = width;
    cv -> background_color = background_color;
    
    
    
    return cv;
}

struct sprite* animate_create_sprite(const char* file) {
    // TODO
    return NULL;
}

//For circle, the width and height should be the same, which are equal to two times of radius
struct sprite* animate_create_circle(size_t radius, color_t c, bool filled) {
    // TODO
    struct sprite* acc = malloc(sizeof(struct sprite));
    
    if (acc == NULL){
        printf("Memory allocate uncessefully");
        return NULL;
    }
    acc -> width = radius * 2;
    acc -> height = radius * 2;
    acc -> color = c;
    acc -> filled = filled;
    acc -> pixels = malloc(acc->width * acc->height * sizeof(color_t));
    if (acc-> pixels == NULL){
        printf("Memory allocate uncessefully");
        return NULL;
    } else {
        for (size_t x = 0; x < acc -> width; x++){
            for(size_t y = 0 ; y < acc -> height; y++){
                ssize_t dx = (ssize_t) x - (ssize_t) radius;
                ssize_t dy = (ssize_t) y - (ssize_t) radius;
                if ( dx * dx + dy * dy <= (size_t) radius * radius){
                    
                    acc -> pixels[y * acc->width + x] = c;
                }
                else {
                    acc -> pixels[y * acc->width + x] = 0;
                }
            }
        }
    }
    return acc;
}

struct sprite* animate_create_rectangle(size_t width, size_t height,
                                        color_t c, bool filled){
    // TODO
    return NULL;
}

bool animate_destroy_sprite(struct sprite* sprite) {
    // TODO
    return 1;
}

struct sprite_placement* animate_place_sprite(struct canvas* canvas,
                                              struct sprite* sprite,
                                              ssize_t x, ssize_t y) {
    // TODO
    return NULL;
}

void animate_placement_up(struct sprite_placement* sprite_placement){
    // TODO COMP9017
}

void animate_placement_down(struct sprite_placement* sprite_placement){
    // TODO COMP9017
}

void animate_placement_top(struct sprite_placement* sprite_placement){
    // TODO
}

void animate_placement_bottom(struct sprite_placement* sprite_placement){
    // TODO
}

void animate_destroy_placement(struct sprite_placement* sprite_placement){
    // TODO
}

void animate_set_animation_params(struct sprite_placement* sprite_placement,
                                  ssize_t vx, ssize_t vy,
                                  ssize_t ax, ssize_t ay){
    // TODO
}

void animate_destroy_canvas(struct canvas* canvas){
    // TODO
}

size_t animate_frame_size_bytes(struct canvas* canvas){
    // TODO
    size_t height = canvas -> height;
    size_t width = canvas -> width;
    size_t size = height * width * sizeof(color_t);
    return size;
}

void animate_generate_frame(const struct canvas* canvas, size_t frame,
                            size_t frame_rate, void* buf) {
    // TODO
    //size_t *data = buf;
    color_t* loc = (color_t*)buf;
    size_t pixal = canvas -> height * canvas -> width;
    //for (buf; buf < size; buf++)
    //    *buf = canvas -> background_color;
    for (size_t i ; i < pixal; i++){
        loc[i] = canvas -> background_color;
    }
}

// Optional extension
void animate_set_animation_function(struct sprite_placement* sprite_placement,
                                    animate_fn, void* priv) {
}

