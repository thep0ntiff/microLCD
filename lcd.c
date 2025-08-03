/*
 * lcd.c
 *
 *  Created on: Aug 2, 2025
 *      Author: Vincent
 */
#include "lcd.h"

static I2C_HandleTypeDef *_lcd_i2c;

static void LCD_Send_Internal(uint8_t data, uint8_t flags) {
    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = up | flags | LCD_EN | LCD_BACKLIGHT;
    data_arr[1] = up | flags | LCD_BACKLIGHT;
    data_arr[2] = lo | flags | LCD_EN | LCD_BACKLIGHT;
    data_arr[3] = lo | flags | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(_lcd_i2c, LCD_ADDR, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
    HAL_Delay(1);
}

void LCD_Send_Command(uint8_t cmd) {
    LCD_Send_Internal(cmd, 0);
}

void LCD_Send_Data(uint8_t data) {
    LCD_Send_Internal(data, LCD_RS);
}

void LCD_Send_String(char *str) {
    while (*str) {
        LCD_Send_Data((uint8_t)(*str++));
    }
}

void LCD_Set_Cursor(uint8_t row, uint8_t col) {
    const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    LCD_Send_Command(0x80 | (col + row_offsets[row]));
}

void LCD_Init(I2C_HandleTypeDef *hi2c) {
    _lcd_i2c = hi2c;
    HAL_Delay(50);

    // Init sequence (send high nibbles only first)
    LCD_Send_Internal(0x30, 0); HAL_Delay(5);
    LCD_Send_Internal(0x30, 0); HAL_Delay(1);
    LCD_Send_Internal(0x30, 0); HAL_Delay(1);
    LCD_Send_Internal(0x20, 0); HAL_Delay(1); // 4-bit mode

    // Now configure
    LCD_Send_Command(0x28); // 4-bit, 2 line, 5x8 font
    LCD_Send_Command(0x08); // Display off
    LCD_Send_Command(0x01); // Clear display
    HAL_Delay(2);
    LCD_Send_Command(0x06); // Entry mode
    LCD_Send_Command(0x0C); // Display on, cursor off
}

