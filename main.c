/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int contador = 0;
int estado = 0;

/* Se establecen las variables para setear el debounce de los diferentes componentes */

uint32_t tiempoDebounce_suma = 0;
uint32_t tiempoDebounce_resta = 0;
uint32_t tiempoDebounce_estado = 0;

/* Se establecen las variables de estado previo para los diferentes botones */

GPIO_PinState antes_suma = 0;
GPIO_PinState antes_resta = 0;
GPIO_PinState antes_estado = 0;

/*Se establecen las variables del estado del botón actuañl*/

GPIO_PinState estado_suma = GPIO_PIN_RESET;
GPIO_PinState estado_resta = GPIO_PIN_RESET;
GPIO_PinState estado_cambio = GPIO_PIN_RESET;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

GPIO_PinState debounce_s(void);
GPIO_PinState debounce_r(void);
GPIO_PinState debounce_c(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  debounce_s();
	  debounce_r();
	  debounce_c();

	  int suma = HAL_GPIO_ReadPin(SUMA_GPIO_Port, SUMA_Pin);
	  int resta = HAL_GPIO_ReadPin(RESTA_GPIO_Port, RESTA_Pin);
	  int cambio = HAL_GPIO_ReadPin(CAMBIO_GPIO_Port, CAMBIO_Pin);

	  if(cambio == GPIO_PIN_SET){
		estado++;
		contador = 0;
		if(estado > 1){
			estado = 0;
		}
	  }

	  if(suma == GPIO_PIN_SET){
		contador++;
		if(contador > 15){
			contador = 0;
		}
	  }
	  else if(resta == GPIO_PIN_RESET){
		contador --;
		if(contador < 0){
			contador = 0;
		}
	  }
	  if(estado == 0){
		if(contador == 0){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 1){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 2){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 3){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 4){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 5){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 6){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 7){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 8){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(contador == 9){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(contador == 10){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(contador == 11){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(contador == 12){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(contador == 13){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(contador == 14){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
		else if(contador == 15){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
	  }
	  if(estado == 1){
		if(contador == 0){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 1){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 2){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 3){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
		else if(contador == 4){
			HAL_GPIO_WritePin(GPIOB,LED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,LED_4_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
		}
	 }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_1_Pin|LED_2_Pin|LED_3_Pin|LED_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USART_TX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(USART_TX_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_1_Pin LED_2_Pin LED_3_Pin LED_4_Pin */
  GPIO_InitStruct.Pin = LED_1_Pin|LED_2_Pin|LED_3_Pin|LED_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SUMA_Pin */
  GPIO_InitStruct.Pin = SUMA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(SUMA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RESTA_Pin */
  GPIO_InitStruct.Pin = RESTA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(RESTA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CAMBIO_Pin */
  GPIO_InitStruct.Pin = CAMBIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(CAMBIO_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
GPIO_PinState debounce_s(void){
	GPIO_PinState actual = HAL_GPIO_ReadPin(SUMA_GPIO_Port, SUMA_Pin);
	if(actual != antes_suma){
		tiempoDebounce_suma = HAL_GetTick();
	}

	if((HAL_GetTick() - tiempoDebounce_suma) > 50){
		if(actual != antes_suma){
			antes_suma = actual;
		}
	}
	return antes_suma;
}
GPIO_PinState debounce_r(void){
	GPIO_PinState actual = HAL_GPIO_ReadPin(RESTA_GPIO_Port, RESTA_Pin);
	if(actual != antes_resta){
		tiempoDebounce_resta = HAL_GetTick();
	}

	if((HAL_GetTick() - tiempoDebounce_resta) > 50){
		if(actual != antes_resta){
			antes_resta = actual;
		}
	}
	return antes_resta;
}
GPIO_PinState debounce_c(void){
	GPIO_PinState actual = HAL_GPIO_ReadPin(CAMBIO_GPIO_Port, CAMBIO_Pin);
	if(actual != antes_estado){
		tiempoDebounce_estado = HAL_GetTick();
	}

	if((HAL_GetTick() - tiempoDebounce_estado) > 200){
		if(actual != antes_estado){
			antes_estado = actual;
		}
	}
	return antes_estado;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
