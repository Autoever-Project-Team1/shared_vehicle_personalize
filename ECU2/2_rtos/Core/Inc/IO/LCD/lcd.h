#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "stdint.h"

#define I2C_LCD_MAX	1	// Maximum Number of I2C_LCD Modules in Your Project
#define I2C_LCD_1	0	// I2C_LCD Instance Number 1 (Add more if you need)

// GUIDELINE SEQUENCE
#define SEQ_0		0
#define SEQ_1		1
#define SEQ_2		2
#define SEQ_3		3

//-----[ Prototypes For All User External Functions ]-----

void I2C_LCD_Init(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Clear(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Home(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_SetCursor(uint8_t I2C_LCD_InstanceIndex, uint8_t Col, uint8_t Row);
void I2C_LCD_WriteChar(uint8_t I2C_LCD_InstanceIndex, char Ch);
void I2C_LCD_WriteString(uint8_t I2C_LCD_InstanceIndex, char* Str);

void I2C_LCD_ShiftLeft(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_ShiftRight(uint8_t I2C_LCD_InstanceIndex);

void I2C_LCD_Backlight(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoBacklight(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Display(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoDisplay(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Cursor(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoCursor(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_Blink(uint8_t I2C_LCD_InstanceIndex);
void I2C_LCD_NoBlink(uint8_t I2C_LCD_InstanceIndex);

void I2C_LCD_CreateCustomChar(uint8_t I2C_LCD_InstanceIndex, uint8_t CharIndex, const uint8_t* CharMap);
void I2C_LCD_PrintCustomChar(uint8_t I2C_LCD_InstanceIndex, uint8_t CharIndex);
void I2C_LCD_GUIDELINE(uint8_t now_seq);
#endif /* I2C_LCD_H_ */
