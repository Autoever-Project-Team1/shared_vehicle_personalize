#include <IO/LCD/lcd.h>
#include <IO/LCD/lcd_cfg.h>

extern I2C_HandleTypeDef hi2c2;

const I2C_LCD_CfgType I2C_LCD_CfgParam[I2C_LCD_MAX] =
{
	{   /*  Configuration Parameter For I2C_LCD Instance #1   */
		I2C_LCD_1,	/* Index of I2C_LCD Instance #1           */
		&hi2c2,		/* Hardware I2C Module's Handle           */
		0x27,		/* Hardware I2C_LCD Device Address        */
		16,			/* LCD Columns Count                      */
		3			/* LCD Rows Count                         */
	}
};
