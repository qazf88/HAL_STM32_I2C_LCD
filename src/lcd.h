#ifndef __HAL_STM32_I2C_LCD_H__
#define __HAL_STM32_I2C_LCD_H__

#include <inttypes.h>
#include "stm32g0xx_hal.h"

HAL_StatusTypeDef init(I2C_HandleTypeDef *i2c, uint8_t lcd_addr);
HAL_StatusTypeDef init_custom(I2C_HandleTypeDef *_i2c, uint8_t lcd_addr, uint8_t column, uint8_t rows);
HAL_StatusTypeDef clear();
HAL_StatusTypeDef home();
HAL_StatusTypeDef set_pos(uint8_t column, uint8_t row);
HAL_StatusTypeDef backlight(uint8_t state);
HAL_StatusTypeDef cursor(uint8_t cursor);
HAL_StatusTypeDef blink(uint8_t blink);
HAL_StatusTypeDef LCD_off();
HAL_StatusTypeDef LCD_on();
HAL_StatusTypeDef write_str(char *str);
HAL_StatusTypeDef write_data(uint8_t *data, size_t size);

#endif /* __HAL_STM32_I2C_LCD_H__ */