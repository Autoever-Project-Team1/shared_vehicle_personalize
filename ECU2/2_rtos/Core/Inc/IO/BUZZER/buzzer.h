#ifndef BUZZER_H
#define BUZZER_H

#define SOL_SHARP_L 415
#define RA_L        440
#define MI_L        659
#define RE_SHARP  622
#define FA_SHARP  740
#define DO_SHARP_H 1109
#define NOTHING 500000

#include "stm32f0xx_hal.h"

void buzzer_init(void);
void beep(uint32_t note, uint32_t duration);
void welcomesound(void);



#endif
