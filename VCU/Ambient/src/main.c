/*
 * newtest.c
 *
 * Copyright (c) 2014 Jeremy Garff <jer @ jers.net>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     1.  Redistributions of source code must retain the above copyright notice, this list of
 *         conditions and the following disclaimer.
 *     2.  Redistributions in binary form must reproduce the above copyright notice, this list
 *         of conditions and the following disclaimer in the documentation and/or other materials
 *         provided with the distribution.
 *     3.  Neither the name of the owner nor the names of its contributors may be used to endorse
 *         or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


static char VERSION[] = "XX.YY.ZZ";

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>


// #include "clk.h"
// #include "gpio.h"
// #include "dma.h"
// #include "pwm.h"
// #include "version.h"

#include "ws2811.h"
#include "swinterrupt3.h"
// #include <wiringPi.h>

#define ARRAY_SIZE(stuff)       (sizeof(stuff) / sizeof(stuff[0]))

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define WIDTH                   144
#define HEIGHT                  1
#define LED_COUNT               (WIDTH * HEIGHT)

int width = WIDTH;
int height = HEIGHT;
int led_count = LED_COUNT;

int clear_on_exit = 1;

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

//brightness value

int brightness_values[5] = {
    30,     //0
    60,     //1
    100,    //2
    150,    //3
    255     //4
};

ws2811_led_t *matrix;

static uint8_t running = 1;

void AmbientLight_Render_Matrix(void)
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



void LED_Clear_Matrix(void)
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


void LED_Motion_BlinkDots(void) {
    for (int i = 0; i < width; ++i) {
        if (rand() % 2) { // 50% 확률로
            matrix[i] =  color_values[color_state];
        } else {
            matrix[i] = 0; // LED 끄기
        }
    }
}


void LED_Motion_Wave(void) 
{
    static int wave_position = 0; // 파동의 현재 위치
    matrix_clear(); // 초기화

    for (int i = 0; i < width; ++i) {
        // 파동 효과를 위해 각 LED의 밝기 계산
        int distance = abs(wave_position - i);
        if (distance < width / 4) {
            int brightness = (width / 4 - distance) * 255 / (width / 4); // 밝기 조절
            matrix[i] =  color_values[color_state];
        }
    }

    // 파동 위치 업데이트
    wave_position = (wave_position + 1) % width;
}

void LED_Motion_Pingpong(void) {
    static int direction = 1; // 1은 오른쪽으로, -1은 왼쪽으로 이동
    static int position = 0; // 현재 LED 위치
    matrix_clear(); // 모든 LED를 꺼서 초기화

    // 현재 위치에 LED를 켭니다.
    matrix[position] = color_values[color_state]; // 예를 들어 빨간색

    // 다음 위치 계산
    position += direction;
    if (position == width - 1 || position == 0) {
        direction *= -1; // 방향 전환
    }
}


void LED_Motion_Flow(void) {
    static int color_flow_position = 0; // 색상 흐름의 시작 위치

    // 모든 LED를 순회하며 색상 적용
    for (int i = 0; i < width; ++i) {
        int position = (i + color_flow_position) % width; // 순환적 색상 위치 계산
        if (position < width / 3) {
            // 첫 번째 1/3은 빨간색
            matrix[i] =  color_values[color_state]; // 빨간색
        } else if (position < (2 * width / 3)) {
            // 두 번째 1/3은 녹색
            matrix[i] =  color_values[(color_state+1)%5]; // 녹색
        } else {
            // 마지막 1/3은 파란색
            matrix[i] = color_values[(color_state+2)%5]; // 파란색
        }
    }

    // 색상 흐름 위치 업데이트
    color_flow_position = (color_flow_position + 1) % width;
}




float brightness = 0.0; // 밝기 초기값, 부동소수점으로 더 세밀한 조정 가능
float fading = 0.05; // 밝기 변경량, 매우 작은 값으로 부드러운 변화
int updatePeriod = 1; // 업데이트 주기, 매우 짧은 주기로 설정

void matrix_fade_in_out_smooth(void) {

    static float brightness = 0.0; // 밝기 초기값, 부동소수점으로 더 세밀한 조정 가능
    static float fading = 0.05; // 밝기 변경량, 매우 작은 값으로 부드러운 변화
    static int updatePeriod = 1; // 업데이트 주기, 매우 짧은 주기로 설정

    // 업데이트 주기를 매우 짧게 설정했기 때문에 카운터는 제거

    // 현재 밝기에 따라 모든 LED 색상 설정
    for (int i = 0; i < width; ++i) {
        // 밝기 조정을 위해 0~255 범위 대신, 0~100 범위를 사용한 후 실제 적용 시 스케일링
        int adjustedBrightness = (int)(brightness * 255.0 / 100.0); // 밝기 조정
        matrix[i] = (adjustedBrightness << 16) | (adjustedBrightness << 8) | adjustedBrightness; // 가정: 모든 LED를 동일한 색으로 설정
    }

    // 밝기 업데이트
    brightness += fading;
    if (brightness > 100.0) { // 최대 밝기를 초과하면
        brightness = 100.0; // 밝기를 최대로 설정하고
        fading = -fading; // 방향 전환 (어두워짐)
    } else if (brightness < 0.0) { // 최소 밝기보다 낮아지면
        brightness = 0.0; // 밝기를 최소로 설정하고
        fading = -fading; // 방향 전환 (밝아짐)
    }
}





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

void LED_Motion_Bottom(void)
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

void AmbientLight_Update_Motion(void) {
    switch (motion_state)
    {
    case 0:
        LED_Motion_Bottom();      
        break;
    case 1:
        LED_Motion_BlinkDots();
        break;
    case 2:
        LED_Motion_Wave();
        break;
    case 3:
        LED_Motion_Pingpong();
        break;  
    case 4:
        LED_Motion_Flow();
        break;
    default:
        break;
    }
}

void AmbientLight_Update_Color() {
    for (int i = 0; i < led_count; i++) {
        matrix[i] = color_values[color_state];
    }
}

void AmbientLight_Update_Brightness() {
    ledstring.channel[0].brightness = brightness_values[brightness_state];
}

static void ctrl_c_handler(int signum)
{
	(void)(signum);
    running = 0;
}

static void AmbientLight_Setup_Handlers(void)
{
    struct sigaction sa =
    {
        .sa_handler = ctrl_c_handler,
    };

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

int main(int argc, char *argv[])
{

	Setup_Switches();

    ws2811_return_t ret;

    matrix = malloc(sizeof(ws2811_led_t) * width * height);

    AmbientLight_Setup_Handlers();

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    while (running)
    {
		
		// color conversion switch
        AmbientLight_Update_Color();
		// brigthness conversion switch
		AmbientLight_Update_Brightness();
		// motion conversion switch
        AmbientLight_Update_Motion();
        //render
        AmbientLight_Render_Matrix();
        //rendering error handler
        if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
        {
            fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
            break;
        }

        // 15 frames /sec
        usleep(1000000 / 30);
		
    }

    if (clear_on_exit) {
	LED_Clear_Matrix();
	AmbientLight_Render_Matrix();
	ws2811_render(&ledstring);
    }

    ws2811_fini(&ledstring);

    printf ("\n");
    return ret;
}
