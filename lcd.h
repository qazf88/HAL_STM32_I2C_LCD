#ifndef __LCD_H__
#define __LCD_H__

#include "i2c.h"

HAL_StatusTypeDef LCD_Init();
HAL_StatusTypeDef LCD_Clear();
HAL_StatusTypeDef LCD_on();
HAL_StatusTypeDef LCD_off();
HAL_StatusTypeDef LCD_SendString(char *str);
HAL_StatusTypeDef LCD_SetCursor(uint8_t row, uint8_t column);
HAL_StatusTypeDef LCD_SendString(char *str);
HAL_StatusTypeDef LCD_SendData(uint8_t data);
HAL_StatusTypeDef LCD_SendCommand(uint8_t data);

#endif /* __LCD_H__ */