#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR (0x27 << 1)
#define LCD_DELAY_MS 5
#define BACKLIGHT (1 << 3)

HAL_StatusTypeDef LCD_SendCommand(uint8_t cmd)
{
    HAL_StatusTypeDef res;
    for (;;)
    {
        res = HAL_I2C_IsDeviceReady(&hi2c1, LCD_ADDR, 1,
                                    HAL_MAX_DELAY);
        if (res == HAL_OK)
            break;
    }
    // 4-bit mode, 2 lines, 5x7 format
    uint8_t data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C; // en=1, rs=0
    data_t[1] = data_u | 0x08; // en=0, rs=0
    data_t[2] = data_l | 0x0C; // en=1, rs=0
    data_t[3] = data_l | 0x08; // en=0, rs=0
     res = HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_t, 4, HAL_MAX_DELAY);
    HAL_Delay(LCD_DELAY_MS);
    return res;
}

HAL_StatusTypeDef LCD_Clear()
{
    return LCD_SendCommand(0b00000001);
}

HAL_StatusTypeDef LCD_off()
{
    return LCD_SendCommand(0x04);
}

HAL_StatusTypeDef LCD_on()
{
    HAL_StatusTypeDef LCD_Init();
}

HAL_StatusTypeDef LCD_SendData(uint8_t data)
{
    // 4-bit mode, 2 lines, 5x7 format
    uint8_t data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D; // en=1, rs=1
    data_t[1] = data_u | 0x09; // en=0, rs=1
    data_t[2] = data_l | 0x0D; // en=1, rs=1
    data_t[3] = data_l | 0x09; // en=0, rs=1
    HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_t, 4, HAL_MAX_DELAY);
    HAL_Delay(LCD_DELAY_MS);
    return res;
}

HAL_StatusTypeDef LCD_SetCursor(uint8_t row, uint8_t column)
{
    uint8_t pos = 0;
    if (row == 0)
    {
        pos = 0x80 + column;
    }
    else
    {
        pos = 0x80 + 0x40 + column;
    }
    return LCD_SendCommand(pos);
}

HAL_StatusTypeDef LCD_SendString(char *str)
{
    while (*str)
    {
        LCD_SendData((uint8_t)(*str));
        str++;
    }
    return HAL_OK;
}

HAL_StatusTypeDef LCD_Init()
{
    HAL_StatusTypeDef res;
    // 4-bit mode, 2 lines, 5x7 format
    res = LCD_SendCommand(0b00110000);
    // display & cursor home (keep this!)
    res = LCD_SendCommand(0b00000010);
    // display on, right shift, underline off, blink off
    res = LCD_SendCommand(0b00001100);
    // clear display (optional here)
    res = LCD_SendCommand(0b00000001);
    HAL_Delay(50);
    return res;
}
