// header : fnd.h
// note : Collection of fnd related functions

#include "fnd.h"

/* VARIABLES BEGIN */
//uint16_t num_port[7] = {A_PORT, B_PORT, C_PORT, D_PORT, E_PORT, F_PORT, G_PORT};
//uint16_t num_pin[7] = {A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, F_PIN, G_PIN};
//uint16_t select_port[3] = {SELECT_1_PORT, SELECT_2_PORT, SELECT_3_PORT};
//uint16_t select_pin[3] = {SELECT_1_PIN, SELECT_2_PIN, SELECT_3_PIN};
uint16_t num[10] = {0x003f, 0x0006, 0x005b, 0x004f, 0x0066, 0x006d, 0x007d, 0x0027, 0x007f, 0x006f};
/* VARIABLES END */

//void FND_Posision_Show_Num(uint8_t posision, uint8_t number)
//{
//	uint8_t i = 0;
//	for(i = 0; i < 3; i++)
//	{
//		if(posision-1 == i)
//		{
//			HAL_GPIO_WritePin(select_port[i], select_pin[i], 0);
//		}
//		else
//		{
//			HAL_GPIO_WritePin(select_port[i], select_pin[i], 1);
//		}
//	}
//
//	for(i = 0; i < 7; i++)
//	{
//		uint8_t segment = (num[number] & (0x01 << i)) >> i;
//		if(segment == 1)
//		{
//			HAL_GPIO_WritePin(num_port[6 - i], num_pin[7 - i], 1);
//		}
//		else
//		{
//			HAL_GPIO_WritePin(num_port[6 - i], num_pin[7 - i], 0);
//		}
//	}
//}





