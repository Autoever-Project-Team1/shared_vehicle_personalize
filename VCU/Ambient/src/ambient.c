#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "ambient.h"
#include "swinterrupt3.h"



int width = WIDTH;
int height = HEIGHT;
int led_count = LED_COUNT;

ws2811_led_t *matrix;

ws2811_t ledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .invert = 0,
            .count = LED_COUNT,
            .strip_type = STRIP_TYPE,
            .brightness = 255,
        },
        [1] =
        {
            .gpionum = 0,
            .invert = 0,
            .count = 0,
            .brightness = 0,
        },
    },
};


ws2811_led_t color_values[5] = {
    0x00200000, // 빨간색
    0x00002000, // 초록색
    0x00000020, // 파란색
    0x00202000, // 노란색
    0x00201010  // 보라색
};

int brightness_values[5] = {
    30,     //0
    60,     //1
    100,    //2
    150,    //3
    255     //4
};

int dotspos[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
ws2811_led_t dotcolors[] =
{
    0x00200000,  // red
    0x00201000,  // orange
    0x00202000,  // yellow
    0x00002000,  // green
    0x00002020,  // lightblue
    0x00000020,  // blue
    0x00100010,  // purple
    0x00200010,  // pink
};

ws2811_led_t dotcolors_rgbw[] =
{
    0x00200000,  // red
    0x10200000,  // red + W
    0x00002000,  // green
    0x10002000,  // green + W
    0x00000020,  // blue
    0x10000020,  // blue + W
    0x00101010,  // white
    0x10101010,  // white + W

};

ws2811_led_t *matrix;

volatile int running = 1;

static void sig_handler(int signo) 
{
    if (signo == SIGINT || signo == SIGTERM) {
        running = 0;
    }
}

void setup_handlers(void) 
{
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
}

//blinking light
void matrix_blinkingdots(void) 
{
    for (int i = 0; i < width; ++i) {
        if (rand() % 2) {
            matrix[i] =  color_values[color_state];
        } else {
            matrix[i] = 0;
        }
    }
}
//welcome light
void matrix_bottom(void)
{
    int i;

    for (i = 0; i < (int)(ARRAY_SIZE(dotspos)); i++)
    {
        dotspos[i]++;
        if (dotspos[i] > (width - 1))
        {
            dotspos[i] = 0;
        }

        if (ledstring.channel[0].strip_type == SK6812_STRIP_RGBW) {
            matrix[dotspos[i] + (height - 1) * width] = dotcolors_rgbw[i];
        } else {
            matrix[dotspos[i] + (height - 1) * width] = dotcolors[i];
        }
    }
}
//wave function
void matrix_wave(void) 
{
    static int wave_position = 0; // 파동의 현재 위치
    matrix_clear(); // 초기화

    for (int i = 0; i < width; ++i) {
        int distance = abs(wave_position - i);
        if (distance < width / 4) {
            int brightness = (width / 4 - distance) * 255 / (width / 4); // 밝기 조절
            matrix[i] =  color_values[color_state];
        }
    }
    wave_position = (wave_position + 1) % width;
}

//ping pong to side to side
void matrix_pingpong(void) 
{
    static int direction = 1; 
    static int position = 0; 
    matrix_clear();
    matrix[position] = color_values[color_state];

    position += direction;
    if (position == width - 1 || position == 0) 
    {
        direction *= -1; // 방향 전환
    }
}

//color flow
void matrix_color_flow(void) {
    static int color_flow_position = 0; //시작 위치

    // 모든 LED를 순회하며 색상 적용
    for (int i = 0; i < width; ++i) 
    {
        int position = (i + color_flow_position) % width; // 순환적 위치 계산
        //처음 1/3색상 설정
        if (position < width / 3) {
            matrix[i] =  color_values[color_state];
        } else if (position < (2 * width / 3)) 
        {
            matrix[i] =  color_values[(color_state+1)%5];
        }
        //마지막 1/3 색상 설정 
        else 
        {
            matrix[i] = color_values[(color_state+2)%5];
        }
    }

    color_flow_position = (color_flow_position + 1) % width;
}


//motion method selection based on motion_state by motion switch
void update_motion(void) {
    switch (motion_state)
    {
    case 0:
        matrix_bottom();      
        break;
    case 1:
        matrix_blinkingdots();
        break;
    case 2:
        matrix_wave();
        break;
    case 3:
        matrix_pingpong();
        break;  
    case 4:
        matrix_color_flow();
        break;
    default:
        break;
    }
}

//method to update brightness based on brightness_state by brightness_switch
void update_brightness() 
{
    ledstring.channel[0].brightness = brightness_values[brightness_state];
}

//update current matrix to led
void matrix_render(void)
{
    int x, y;

    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
            ledstring.channel[0].leds[(y * width) + x] = matrix[y * width + x];
        }
    }
}

//led clear method
void matrix_clear(void)
{
    int x, y;

    for (y = 0; y < (height ); y++)
    {
        for (x = 0; x < width; x++)
        {
            matrix[y * width + x] = 0;
        }
    }
}

//led_handler matrix init
void matrix_initialize(void) {
     ws2811_return_t ret;
    matrix = malloc(sizeof(ws2811_led_t) * width * height);
    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        
    }
}

//led_handler matrix free
void matrix_finalize(void) {
    free(matrix);
    ws2811_fini(&ledstring);
}



