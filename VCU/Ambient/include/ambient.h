#ifndef AMBIENT_H
#define AMBIENT_H

#include "ws2811.h"

//constant
#define WIDTH 144
#define HEIGHT 1
#define LED_COUNT (WIDTH * HEIGHT)
#define TARGET_FREQ WS2811_TARGET_FREQ
#define GPIO_PIN 18
#define DMA 10
#define STRIP_TYPE WS2811_STRIP_GBR

#define ARRAY_SIZE(stuff)       (sizeof(stuff) / sizeof(stuff[0]))

//global variables(extern)
extern ws2811_t ledstring;
extern ws2811_led_t *matrix;

//lde width 
extern int width;

//led height bar=1
extern int height;
extern int led_count;

//running flag
extern volatile int running;

//method
void setup_handlers(void);

void matrix_blinkingdots(void);

//welcome light
void matrix_bottom(void); 

//wave function
void matrix_wave(void);

//ping pong to side to side
void matrix_pingpong(void);

//color flow
void matrix_color_flow(void);

void matrix_fade_in_out_smooth(void);

//motion method selection based on motion_state by motion switch
void update_motion(void);

//method to update brightness based on brightness_state by brightness_switch
void update_brightness(void);

//update current matrix to led
void matrix_render(void);

//led clear method
void matrix_clear(void);

//led_handler matrix init
void matrix_initialize(void);

//led_handler matrix free
void matrix_finalize(void);

#endif