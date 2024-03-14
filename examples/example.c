

// ...

/* USER CODE BEGIN Includes */
#include "lcd.h"
/* USER CODE END Includes */

// ...

 I2C_HandleTypeDef hi2c1;

// ...

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  // set I2C and disolay adress
  init(&hi2c1, 0x27);

  uint8_t data[] = "Hello, World!";
  write_str((char *)data);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  int counter = 0;
  uint32_t timer = 0;
  while (1)
  {

    if (HAL_GetTick() - timer >= 1000)
    {
      timer = HAL_GetTick();
      counter++;
      set_pos(0, 1);

      char num[10];
      sprintf(num, "%d", counter);

      write_str(num);
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

// ...