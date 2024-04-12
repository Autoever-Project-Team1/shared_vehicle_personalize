// header : fnd.h
// note : Collection of fnd related functions
// note : this func, only using Port_C

#ifndef FND_H
#define FND_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"
/* HEADER END */

/* MACRO BEGIN */
#define DIGIT_1		0x0080
#define DIGIT_2		0x0100
#define	DIGIT_3		0x0200
/* MACRO END */

/* STRUCT & TYPE BEGIN */

/* STRUCT & TYPE END */

/* VARIABLES BEGIN */
extern uint32_t num[10];
/* VARIABLES END */

/* FUNCTION BEGIN */
void ShowFND(uint32_t data);
void OffFND();
/* FUNCTION END */

#endif
