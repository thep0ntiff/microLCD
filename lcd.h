/*
 * lcd.h
 *
 *  Created on: Aug 2, 2025
 *      Author: Vincent
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f3xx_hal.h"

#define LCD_ADDR        (0x27 << 1)

// Control bits
#define LCD_BACKLIGHT   0x08
#define LCD_EN          0x04
#define LCD_RW          0x02
#define LCD_RS          0x01

void LCD_Init(I2C_HandleTypeDef *hi2c);
void LCD_Send_Command(uint8_t cmd);
void LCD_Send_Data(uint8_t data);
void LCD_Send_String(char *str);
void LCD_Set_Cursor(uint8_t row, uint8_t col);

#endif
