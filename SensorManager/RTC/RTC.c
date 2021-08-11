/*
 * RTC.c
 *
 *  Created on: Jul 9, 2021
 *      Author: lucky
 */

#include "main.h"

#include "Prototype.h"

#include "RTC_pub.h"
#include "RTC.h"

/* Private variables ---------------------------------------------------------*/
static RTC_HandleTypeDef hrtc;


/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 1;
  sTime.Minutes = 56;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_TUESDAY;
  sDate.Month = RTC_MONTH_AUGUST;
  sDate.Date = 8;
  sDate.Year = 21;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

uint32 RTC_u32GetCalendarInfo(RTC_CalendarFormat* stCalendar)
{
	uint32 u32Status = 0U;
	RTC_TimeTypeDef stTime;
	RTC_DateTypeDef stDate;

	u32Status = HAL_RTC_GetTime(&hrtc, &stTime, RTC_FORMAT_BIN);
	u32Status += HAL_RTC_GetDate(&hrtc, &stDate, RTC_FORMAT_BIN);

	stCalendar->stDate = stDate;

	stCalendar->stTime.u8Sec = stTime.Seconds;
	stCalendar->stTime.u8Min = stTime.Minutes;
	stCalendar->stTime.u8Hr = stTime.Hours;

	return u32Status;
}
