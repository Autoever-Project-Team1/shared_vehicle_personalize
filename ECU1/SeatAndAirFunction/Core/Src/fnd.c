// header : fnd.h
// note : Collection of fnd related functions

#include "fnd.h"

/* VARIABLES BEGIN */

//uint32_t num[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
uint32_t num[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x58, 0x00, 0x10};
/* VARIABLES END */

void ShowFND(uint32_t data)
{
	if((data/100) == 0 && ((data%100)/10) == 0)
	{
		GPIOC -> ODR = (num[(data%10)] | DIGIT_1);
	}
	else if((data/100) == 0)
	{
		GPIOC -> ODR = (num[(data%10)] | DIGIT_1);
		GPIOC -> ODR = (num[((data%100)/10)] | DIGIT_2);
	}
	else
	{
		GPIOC -> ODR = (num[(data%10)] | DIGIT_1);
		GPIOC -> ODR = (num[((data%100)/10)] | DIGIT_2);
		GPIOC -> ODR = (num[(data/100)] | DIGIT_3);
	}
	//GPIOC -> ODR = (num[(data%10)] | DIGIT_1);
	//GPIOC -> ODR = (num[((data%100)/10)] | DIGIT_2);
	//GPIOC -> ODR = (num[(data/100)] | DIGIT_3);
}

void OffFND()
{
	GPIOC -> ODR = 0x0000;
}




