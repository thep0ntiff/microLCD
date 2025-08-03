# microLCD

**microLCD** is a minimal I2C-based driver for character LCDs (such as 16x2 or 20x4) using an I2C backpack (PCF8574).  
It was developed for the **STM32F3** series and is intended to be lightweight and easy to integrate.

---

## Features

- Simple API for sending commands and data to an LCD over I2C
- Designed for STM32F3 microcontrollers
- Easily portable to other STM32 series
- Minimal dependencies (only requires your HAL)

---

## Getting Started

### 📦 Requirements

- STM32 HAL (tested with STM32F3)
- LCD module with I2C backpack (PCF8574 or compatible)
- I2C interface configured via HAL

---

### 🛠 Setup

1. Include `lcd.c` and `lcd.h` in your project.
2. Add the necessary `#include "stm32f3xx_hal.h"` or your STM32 HAL header.
3. Make sure I2C is initialized before calling any LCD functions.
4. Set the correct I2C address for your LCD module:

```c
#define LCD_ADDR 0x27 // Change this to match your hardware
