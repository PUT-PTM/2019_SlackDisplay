/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "displayer.h"
#include "i2c-lcd.h"
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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

uint8_t DataToSend[200]; // Tablica zawierajaca dane do wyslania
uint8_t MessageCounter = 0; // Licznik wyslanych wiadomosci
uint8_t MessageLength = 0; // Zawiera dlugosc wysylanej wiadomosci

uint8_t ReceivedData[200]; // Tablica przechowujaca odebrane dane
uint8_t ReceivedDataFlag = 0; // Flaga informujaca o odebraniu danych

uint8_t ReceivedText[180];
uint8_t ReceivedUser[50];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {



}

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
  MX_USB_DEVICE_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

    lcd_init();
    lcd_clear();
    lcd_send_string("qwerty");

    //lcd_send_string("KOT");
//    menu(MessageCounter);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
          HAL_Delay(100);
          if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
              ++MessageCounter;
              MessageLength = (uint8_t) sprintf(DataToSend, "Wiadomosc nr %d\n\r", MessageCounter);
              CDC_Transmit_FS(DataToSend, MessageLength);

          }
      }

      //down pin K7
      if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) != GPIO_PIN_SET) {
          HAL_Delay(100);
          if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) != GPIO_PIN_SET) {

              MessageLength = (uint8_t) sprintf(DataToSend, "cms_dn");
              CDC_Transmit_FS(DataToSend, MessageLength);

              while (ReceivedDataFlag != 1){
                  HAL_Delay(3);
              }

              //if (ReceivedDataFlag == 1) {
                  ReceivedDataFlag = 0;
                  // Wyczyszczenie tablicy nadawanych danych
                  uint8_t iter;
                  for (iter = 0; iter < 200; ++iter) {
                      DataToSend[iter] = 0;
                  }

                  for (iter = 0; iter < 50; ++iter) {
                  ReceivedUser[iter] = 0;
                 }
              for (iter = 0; iter < 180; ++iter) {
                  ReceivedText[iter] = 0;
              }


              int index = 0;

              //-----------------------------------------------------------------------------------
              while(ReceivedData[index]!='?'){
                  index++;
              }
              index++;
              int user_index = 0;
              while(ReceivedData[index]!='?'){
                  ReceivedUser[user_index]=ReceivedData[index];
                  user_index++;
                  index++;
              }
              index++;
              int text_index = 0;

              while(index<200){
                  ReceivedText[text_index]=ReceivedData[index];
                  text_index++;
                  index++;
              }

              //display
              lcd_clear();
              lcd_send_cmd(0x80);
              lcd_send_string("some user");
              lcd_send_cmd(0xc0);
              lcd_send_string(ReceivedText);


//                  MessageLength = (uint8_t) sprintf(DataToSend, "DRecieved: %s", ReceivedUser);
//                  CDC_Transmit_FS(DataToSend, MessageLength);
//              HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
             // }
//              HAL_Delay(20);
          }
      }


      //down pin K6
      if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) != GPIO_PIN_SET) {
          HAL_Delay(100);
          if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) != GPIO_PIN_SET) {

              MessageLength = (uint8_t) sprintf(DataToSend, "cch_dn");
              CDC_Transmit_FS(DataToSend, MessageLength);

              while (ReceivedDataFlag != 1){
                  HAL_Delay(3);
              }

              //if (ReceivedDataFlag == 1) {
              ReceivedDataFlag = 0;
              // Wyczyszczenie tablicy nadawanych danych
              uint8_t iter;
              for (iter = 0; iter < 200; ++iter) {
                  DataToSend[iter] = 0;
              }

              for (iter = 0; iter < 50; ++iter) {
                  ReceivedUser[iter] = 0;
              }
              for (iter = 0; iter < 180; ++iter) {
                  ReceivedText[iter] = 0;
              }

              int index = 0;

              //-----------------------------------------------------------------------------------
              while(ReceivedData[index]!='?'){
                  index++;
              }
              index++;
              int user_index = 0;
              while(ReceivedData[index]!='?'){
                  ReceivedUser[user_index]=ReceivedData[index];
                  user_index++;
                  index++;
              }
              index++;
              int text_index = 0;

              while(index<200){
                  ReceivedText[text_index]=ReceivedData[index];
                  text_index++;
                  index++;
              }

//display
                lcd_clear();
              lcd_send_cmd(0x80);
              lcd_send_string(ReceivedUser);
              lcd_send_cmd(0xc0);
              lcd_send_string(ReceivedText);

//              MessageLength = (uint8_t) sprintf(DataToSend, "DRecieved: %s", ReceivedText);
//              CDC_Transmit_FS(DataToSend, MessageLength);
              HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
              // }
//              HAL_Delay(20);

          }
      }


      //up pin K3
      if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) != GPIO_PIN_SET) {

          HAL_Delay(100);
          if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) != GPIO_PIN_SET) {

              MessageLength = (uint8_t) sprintf(DataToSend, "cms_up");
              CDC_Transmit_FS(DataToSend, MessageLength);

                  while (ReceivedDataFlag != 1){
                      HAL_Delay(3);
                  }
//                  if (ReceivedDataFlag == 1) {
                  ReceivedDataFlag = 0;

                  // Wyczyszczenie tablicy nadawanych danych
                  uint8_t iter;
                  for (iter = 0; iter < 200; ++iter) {
                      DataToSend[iter] = 0;
                  }


              for (iter = 0; iter < 50; ++iter) {
                  ReceivedUser[iter] = 0;
              }
              for (iter = 0; iter < 180; ++iter) {
                  ReceivedText[iter] = 0;
              }

              int index = 0;

                  //-----------------------------------------------------------------------------------
                  while(ReceivedData[index]!='?'){
                      index++;
                  }
                  index++;
                  int user_index = 0;
                  while(ReceivedData[index]!='?'){
                      ReceivedUser[user_index]=ReceivedData[index];
                      user_index++;
                      index++;
                  }
                  index++;
                    int text_index = 0;

              while(index<200){
                  ReceivedText[text_index]=ReceivedData[index];
                  text_index++;
                  index++;
              }


              //display
              lcd_clear();
              lcd_send_cmd(0x80);
              lcd_send_string(ReceivedUser);
              lcd_send_cmd(0xc0);
              lcd_send_string(ReceivedText);
//                  MessageLength = (uint8_t) sprintf(DataToSend, "URecieved: %s", ReceivedText);
//                  CDC_Transmit_FS(DataToSend, MessageLength);
//              HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
              HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
//                  }


//              HAL_Delay(20);
          }

      }

      //up pin K2
      if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) != GPIO_PIN_SET) {

          HAL_Delay(100);
          if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) != GPIO_PIN_SET) {

              MessageLength = (uint8_t) sprintf(DataToSend, "cch_up");
              CDC_Transmit_FS(DataToSend, MessageLength);

              while (ReceivedDataFlag != 1){
                  HAL_Delay(3);
              }
//                  if (ReceivedDataFlag == 1) {
              ReceivedDataFlag = 0;

              // Wyczyszczenie tablicy nadawanych danych
              uint8_t iter;
              for (iter = 0; iter < 200; ++iter) {
                  DataToSend[iter] = 0;
              }


              for (iter = 0; iter < 50; ++iter) {
                  ReceivedUser[iter] = 0;
              }
              for (iter = 0; iter < 180; ++iter) {
                  ReceivedText[iter] = 0;
              }

              int index = 0;

              //-----------------------------------------------------------------------------------
              while(ReceivedData[index]!='?'){
                  index++;
              }
              index++;
              int user_index = 0;
              while(ReceivedData[index]!='?'){
                  ReceivedUser[user_index]=ReceivedData[index];
                  user_index++;
                  index++;
              }
              index++;
              int text_index = 0;

              while(index<200){
                  ReceivedText[text_index]=ReceivedData[index];
                  text_index++;
                  index++;
              }

//display
              lcd_clear();
              lcd_send_cmd(0x80);
              lcd_send_string(ReceivedUser);
              lcd_send_cmd(0xc0);
              lcd_send_string(ReceivedText);
//              MessageLength = (uint8_t) sprintf(DataToSend, "URecieved: %s", ReceivedText);
//              CDC_Transmit_FS(DataToSend, MessageLength);
//              HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
              HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
//                  }


//              HAL_Delay(20);
          }

      }

      if (ReceivedDataFlag == 1) {

          ReceivedDataFlag = 0;



          // Wyczyszczenie tablicy nadawanych danych
          uint8_t iter;
          for (iter = 0; iter < 200; ++iter) {
              DataToSend[iter] = 0;
          }

         for (iter = 0; iter < 50; ++iter) {
                  ReceivedUser[iter] = 0;
                 }
              for (iter = 0; iter < 180; ++iter) {
                  ReceivedText[iter] = 0;
              }
          int index = 0;

          //-----------------------------------------------------------------------------------
          while(ReceivedData[index]!='?'){
              index++;
          }
          ++index;
          int user_index = 0;
          while(ReceivedData[index]!='?'){
              ReceivedUser[user_index]=ReceivedData[index];
              ++user_index;
              ++index;
          }
          index++;
          int text_index = 0;

          while(index<200){
              ReceivedText[text_index]=ReceivedData[index];
              text_index++;
              index++;
          }

          //display
          lcd_clear();
          lcd_send_cmd(0x80);
          lcd_send_string(ReceivedUser);
          lcd_send_cmd(0xc0);
          lcd_send_string(ReceivedText);

//          MessageLength = (uint8_t) sprintf(DataToSend, "Odebrano: %s", ReceivedText);



          CDC_Transmit_FS(DataToSend, MessageLength);
      }
      asm("nop");

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

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 400;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
