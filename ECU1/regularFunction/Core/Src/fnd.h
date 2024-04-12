// header : fnd.h
// note : Collection of fnd related functions

#ifndef FND_H
#define FND_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"
/* HEADER END */

/* MACRO BEGIN */
#define A_PORT				GPIOC
#define B_PORT				GPIOC
#define C_PORT				GPIOC
#define D_PORT				GPIOC
#define E_PORT				GPIOC
#define F_PORT				GPIOC
#define G_PORT				GPIOC
#define SELECT_1_PORT		GPIOC
#define SELECT_2_PORT		GPIOC
#define SELECT_3_PORT		GPIOC

#define A_PIN				GPIO_PIN_0
#define B_PIN				GPIO_PIN_1
#define C_PIN				GPIO_PIN_2
#define D_PIN				GPIO_PIN_3
#define E_PIN				GPIO_PIN_4
#define F_PIN				GPIO_PIN_5
#define G_PIN				GPIO_PIN_6
#define SELECT_1_PIN		GPIO_PIN_7
#define SELECT_2_PIN		GPIO_PIN_8
#define SELECT_3_PIN		GPIO_PIN_9
/* MACRO END */

/* STRUCT & TYPE BEGIN */

/* STRUCT & TYPE END */

/* VARIABLES BEGIN */
//extern uint16_t num_port[7];
//extern uint16_t num_pin[7];
//extern uint16_t select_port[3];
//extern uint16_t select_pin[3];
extern uint16_t num[10];
/* VARIABLES END */

/* FUNCTION BEGIN */

/* FUNCTION END */

#endif
