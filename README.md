`HAL_STM32_I2C_LCD`

## Description
This library is a driver for the I2C LCD display based on the PCF8574 I2C I/O expander. It is designed to work with the STM32 HAL libraries.

## Usage
[Read this](https://qazf.com.ua/lcd1602-i2c-stm32/)

Copy the `lcd.c` and `lcd.h` files to your project and include the `lcd.h` file in your code.

Or you can use STMCubeMX project in PlatformIO [STM32CubeMX PlatformIO and VSCode](https://qazf.com.ua/stm32-cubemx-platformio/).
And add to `platformio.ini`:

```
lib_deps = qazf/HAL_STM32_I2C_LCD@^1
```
or
```
lib_deps = git@github.com:qazf88/HAL_STM32_I2C_LCD.git
```