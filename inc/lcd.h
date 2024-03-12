#ifndef __HAL_STM32_I2C_LCD_H__
#define __HAL_STM32_I2C_LCD_H__

#include <inttypes.h>
#include "stm32g0xx_hal.h"
#include "i2c.h"


#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100 // Enable bit
#define Rw 0b00000010 // Read/Write bit
#define Rs 0b00000001 // Register select bit

void init(I2C_HandleTypeDef *i2c, uint8_t lcd_addr);
void set_cursor(uint8_t column, uint8_t row);
void write_str(char *str);
void write_data(uint8_t *data, size_t size);
// void begin(uint8_t cols, uint8_t rows, uint8_t dotsize);
 void clear();
 void backlight(uint8_t state);
 void LCD_off();
 void home();
#endif /* __HAL_STM32_I2C_LCD_H__ */