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
    int cnt;

};

struct sprite_placement {
    // TODO
    struct sprite *sprite;
    struct canvas *canvas;
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
    //initialize the head and tail as null
    cv -> head = NULL;
    cv -> tail = NULL;
    
    
    
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
                size_t index = y * acc -> width + x;
                ssize_t dx = (ssize_t) x - (ssize_t) radius;
                ssize_t dy = (ssize_t) y - (ssize_t) radius;
                if ( dx * dx + dy * dy <= (size_t) radius * radius){
                    
                    acc -> pixels[index] = c;
                }
                else {
                    acc -> pixels[index] = 0;
                }
            }
        }
    }
    return acc;
}

struct sprite* animate_create_rectangle(size_t width, size_t height,
                                        color_t c, bool filled){
    // TODO
    struct sprite* acr = malloc(sizeof(struct sprite));
    if (acr == NULL){
        printf("Memory allocate uncessefully");
        return NULL;
    }

    acr -> width = width;
    acr -> height = height;
    acr -> color = c;
    acr -> filled = filled;
    acr -> pixels = malloc(acr -> width * acr -> height *sizeof(color_t));
    if (acr -> pixels == NULL){
        printf("Memory allocate uncessefully");
        return NULL;
    }

    for(size_t y = 0; y < acr -> height; y++){
        for (size_t x = 0; x < acr -> width; x++){
            size_t index = y * width + x;
            if (filled == true){
                acr -> pixels[index] = acr -> color;
            } else {
                if (filled == false){
                    if ( x == 0 || x == (width-1) || y == 0 || y == (height-1)){
                        acr -> pixels[index] = c;
                    } else {
                        acr -> pixels[index] = 0;
                    }
                }
            }
        }
    }
    return acr;
}

bool animate_destroy_sprite(struct sprite* sprite) {
    // TODO

    if (sprite -> cnt > 0){
        return 0;
    }

    //free pixels first as we create a space for it when create a sprite (animate_create_rectangle/circle)
    free(sprite -> pixels);
    free(sprite);

    return 1;
}

struct sprite_placement* animate_place_sprite(struct canvas* canvas,
                                              struct sprite* sprite,
                                              ssize_t x, ssize_t y) {
    // TODO
    struct sprite_placement* aps = malloc(sizeof(struct sprite_placement));
    if (aps == NULL){
        printf("Memory allocate uncessefully");
        return NULL;
    }
    // if the sprite in use, break the 
    aps -> sprite = sprite;

    aps -> canvas = canvas;
    aps -> x = x;
    aps -> y = y;

    if (canvas -> head == 0) {
        canvas -> head = aps;
        canvas -> tail = aps;
        aps -> next = NULL;
        aps -> prev = NULL;
    } else {
        aps -> prev = canvas -> tail;
        canvas -> tail -> next = aps;
        canvas -> tail = aps;
        aps -> next = NULL;


    }
    sprite -> cnt += 1;
    return aps;
}

void animate_placement_up(struct sprite_placement* sprite_placement){
    // TODO COMP9017
}

void animate_placement_down(struct sprite_placement* sprite_placement){
    // TODO COMP9017
}

void animate_placement_top(struct sprite_placement* sprite_placement){
    // TODO
    if (sprite_placement == NULL || sprite_placement -> canvas -> tail == sprite_placement){
        return;
    } else if (sprite_placement -> canvas -> head == sprite_placement) {
        sprite_placement -> canvas -> head = sprite_placement -> next;
        sprite_placement -> next -> prev = NULL;
    } else {
        sprite_placement -> prev -> next = sprite_placement -> next;
        sprite_placement -> next -> prev = sprite_placement -> prev;
    }

    //place to the tail
    sprite_placement -> canvas -> tail -> next = sprite_placement;
    sprite_placement -> prev = sprite_placement -> canvas -> tail;
    sprite_placement -> canvas -> tail = sprite_placement;
    sprite_placement -> next = NULL;
    

}

void animate_placement_bottom(struct sprite_placement* sprite_placement){
    // TODO
    //if it already is canvas's head => do nothing 
    if (sprite_placement == NULL || sprite_placement -> canvas -> head == sprite_placement){
        return;
    } else if (sprite_placement -> canvas -> tail == sprite_placement){
        //reset the tail
        sprite_placement -> canvas -> tail = sprite_placement -> prev;
        sprite_placement -> prev -> next = NULL;
    } else {
        sprite_placement -> prev -> next = sprite_placement -> next;
        sprite_placement -> next -> prev = sprite_placement -> prev;
    }
    
    sprite_placement -> next = sprite_placement -> canvas -> head;
    sprite_placement -> canvas -> head -> prev = sprite_placement;
    sprite_placement -> canvas -> head = sprite_placement;
    sprite_placement -> prev = NULL;

}

void animate_destroy_placement(struct sprite_placement* sprite_placement){
    // TODO
    //if no placement
    if( sprite_placement == NULL){
        return;
    } else if (sprite_placement -> canvas -> head == sprite_placement -> canvas -> tail) {
    //if the is only one placement
         sprite_placement -> canvas -> head = NULL;
         sprite_placement -> canvas -> tail = NULL;
    //when destroy the last one, set the prev's next as null
    } else if (sprite_placement -> next == NULL){
        sprite_placement -> prev -> next = NULL;
        sprite_placement -> canvas -> tail = sprite_placement -> prev ;
    } else if (sprite_placement -> prev == NULL){
    //when destroy the first one, set the next's prev as null
        sprite_placement -> next -> prev = NULL;
        sprite_placement -> canvas -> head = sprite_placement -> next ;
    } else {
        sprite_placement -> prev -> next = sprite_placement -> next ;
        sprite_placement -> next -> prev = sprite_placement -> prev ;
    }
    
    //update the sprite's using cnt
    sprite_placement -> sprite -> cnt--;

    //free the memory
    free(sprite_placement);


}

void animate_set_animation_params(struct sprite_placement* sprite_placement,
                                  ssize_t vx, ssize_t vy,
                                  ssize_t ax, ssize_t ay){
    // TODO
    //prevent a null sprite_placement destory the code
    if (sprite_placement == NULL){
        return;
    }
    sprite_placement -> vx = vx;
    sprite_placement -> vy = vy;
    sprite_placement -> ax = ax;
    sprite_placement -> ay = ay;
}

void animate_destroy_canvas(struct canvas* canvas){
    // TODO
    
    while (canvas -> head != NULL) {
        animate_destroy_placement(canvas -> head);
    }
    
    free(canvas);
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
    //a pointer buf point to the space create in main.c (void* data = malloc(frame_size_bytes);)
    color_t* loc = (color_t*)buf;
    //total pixal of the input canvas
    size_t pixal = canvas -> height * canvas -> width;
    //fill the background_color to all the space in buf(loc)
    for (size_t i = 0; i < pixal; i++){
        loc[i] = canvas -> background_color;
    }

    //calculate what is the time right now
    float t = (float)frame/frame_rate;
    struct sprite_placement* current = canvas -> head;
    while (current != NULL){
        ssize_t new_x = (current -> x) + (current -> vx) * t + (current -> ax) * t *t / 2;
        ssize_t new_y = (current -> y) + (current -> vy) * t + (current -> ay) * t *t / 2;

        //go through all pixal in the sprite
        for (size_t sy = 0; sy < current -> sprite -> height; sy++){
            for (size_t sx = 0; sx < current -> sprite -> width; sx++){
                
                //the location of the sprite right now
                size_t sprite_index = sy * current -> sprite -> width + sx;

                //color of this localtion
                color_t pixel_color = current -> sprite -> pixels[sprite_index];

                ////calculate the absolute location in the loc(buf)
                ssize_t abs_x = new_x + sx;
                ssize_t abs_y = new_y + sy;

                if(( (abs_x >= 0 && abs_x < canvas -> width) && (abs_y >= 0 && abs_y < canvas -> height))){
                    if((pixel_color >> 24) != 0){
                        size_t canvas_index = (size_t)abs_y * canvas -> width + (size_t)abs_x;
                        loc[canvas_index] = pixel_color | 0xFF000000;
                    }
                }
            }
        }
        current = current -> next;
    }
    



}

// Optional extension
void animate_set_animation_function(struct sprite_placement* sprite_placement,
                                    animate_fn, void* priv) {
}

