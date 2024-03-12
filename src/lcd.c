#include "lcd.h"

#include <inttypes.h>
#include "stdlib.h"

#define BACKLIGHT (1 << 3)
#define RS (1 << 0)
#define EN (1 << 2)
#define LCD_DELAY_MS 5

uint8_t _addr;
uint8_t _backlight = BACKLIGHT;

I2C_HandleTypeDef *i2c;

volatile uint32_t wite_time = 0;
volatile uint32_t last_send_time = 0;

HAL_StatusTypeDef send(uint8_t data, uint8_t cmd)
{
	HAL_StatusTypeDef res;

	while (HAL_GetTick() - last_send_time < wite_time)
	{
		HAL_Delay(1);
	}

	for (;;)
	{
		res = HAL_I2C_IsDeviceReady(&hi2c1, _addr, 1,
									HAL_MAX_DELAY);
		if (res == HAL_OK)
			break;
	}

	uint8_t up = data & 0xF0;
	uint8_t lo = (data << 4) & 0xF0;

	uint8_t data_arr[4];
	data_arr[0] = up | cmd | _backlight | En;
	data_arr[1] = up | cmd | _backlight;
	data_arr[2] = lo | cmd | _backlight | En;
	data_arr[3] = lo | cmd | _backlight;

	res = HAL_I2C_Master_Transmit(&hi2c1, _addr, data_arr,
								  sizeof(data_arr), HAL_MAX_DELAY);
	last_send_time = HAL_GetTick();
	return res;
}

void send_command(uint8_t cmd)
{
	send(cmd, 0);
	wite_time = 5;
}

void send_data(uint8_t data)
{
	send(data, Rs);
}

void init(I2C_HandleTypeDef *i2c, uint8_t lcd_addr)
{
	i2c = i2c;
	_addr = (lcd_addr << 1);
	// 4-bit mode, 2 lines, 5x7 format
	send_command(0b00110000);
	// display & cursor home (keep this!)
	send_command(0b00000010);
	// display on, right shift, underline off, blink off
	send_command(0b00001100);
	// clear display (optional here)
	send_command(0b00000001);
}

void write_str(char *str)
{
	while (*str)
	{
		send_data((uint8_t)(*str));
		str++;
	}
}

void write_data(uint8_t *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		send_data(data[i]);
	}
}

void set_cursor(uint8_t column, uint8_t row)
{
	column = (row == 0 ? column | 0x80 : column | 0xc0);
	send_command(column);
}

void clear()
{
	send_command(0x01);
}

 void backlight(uint8_t state){
	 if (state == 1)
	 {
		 _backlight = BACKLIGHT;
	 }
	 else
	 {
		 _backlight = LCD_NOBACKLIGHT;
	 }
	 send_command(0);
 }

 void home(){
	 send_command(0x02);
 }

 void LCD_off(){
	_backlight = LCD_NOBACKLIGHT;
	 send_command(0x08);
 }

 void LCD_on(){
	_backlight = BACKLIGHT;
	 send_command(0x0C);
 }
 
