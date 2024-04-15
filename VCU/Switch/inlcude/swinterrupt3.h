// switchlib.h
#ifndef SWINTERRUPT3_H
#define SWINTERRUPT3_H

#include <wiringPi.h>



// pinnumber
#define COLORSW 27
#define BRIGHTSW 28
#define MOTIONSW 25

extern unsigned char color_state;  // 0~4
extern unsigned char brightness_state; // 0~4
extern unsigned char motion_state; //0~4

//switch interrupt init
void setupSwitches(void);

//isr
void colorisr(void);
void brightnessisr(void);
void motionisr(void);

#endif