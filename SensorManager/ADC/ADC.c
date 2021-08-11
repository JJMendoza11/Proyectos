/*
 * @file ADC.c
 *
 *  Created on: Jul 9, 2021
 * @Author: lucky
 */


#include "main.h"

#include "Prototype.h"

#include "ADC_priv.h"
#include "ADC_pub.h"
#include "ADC.h"

/* Private variables ---------------------------------------------------------*/
static ADC_HandleTypeDef hadc;
static uint32 ADC_au32Channel[ADC_enTotalSensors] = ADC_CHANNEL_TABLE;


static void __Select_Channel(uint32 u32Channel)
{
	/** Configure for the selected ADC regular channel to be converted.
	*/
	ADC_ChannelConfTypeDef sConfig = {0};

	hadc.Instance->CHSELR = 0;
	sConfig.Channel = ADC_au32Channel[u32Channel];
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
	Error_Handler();
	}
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = ENABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

uint32 ADC_u32ReadChannel(uint16 channel)
{
	uint32 u32ADC_Val;

	__Select_Channel(channel);

	HAL_ADC_Start(&hadc);

	HAL_ADC_PollForConversion(&hadc, 1000);

	u32ADC_Val = HAL_ADC_GetValue(&hadc);

	HAL_ADC_Stop(&hadc);

	return u32ADC_Val;
}

uint32 ADC_u32GetResolution(void)
{
	uint32 resolution = 0U;
	switch(hadc.Init.Resolution)
	{
	case ADC_RESOLUTION_12B:
		resolution = (uint32)ADC_RESOLUTION_12BITS;
		break;
	case ADC_RESOLUTION_10B:
		resolution = (uint32)ADC_RESOLUTION_10BITS;
		break;

	case ADC_RESOLUTION_8B:
		resolution = (uint32)ADC_RESOLUTION_8BITS;
		break;

	case ADC_RESOLUTION_6B:
		resolution = (uint32)ADC_RESOLUTION_6BITS;
		break;
	}
	return resolution;
}
