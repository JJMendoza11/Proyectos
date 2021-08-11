/*
 * RTC_pub.h
 *
 *  Created on: 5 ago. 2021
 *      Author: lucky
 */

#ifndef SRC_RTC_RTC_PUB_H_
#define SRC_RTC_RTC_PUB_H_

#include "main.h"
#include "Prototype.h"

/*
 * @def RTC_tstDateFormat
 * @brief Macro que se utiliza para definir de otra forma la estructura
 * RTC_DateTypeDef. Esto con el unico fin de homogeneizar el formato
 * de la estrucuta RTC_CalendarFormat.
 */
#define RTC_tstDateFormat		RTC_DateTypeDef

/*
 * @struct RTC_tstTimeFormat
 * @brief Macro que solo mantiene las propiedades que le son utiles
 * al proyecto de la estructura RTC_TimeTypeDef.
 */
typedef struct
{
	uint8 u8Sec;
	uint8 u8Min;
	uint8 u8Hr;
}RTC_tstTimeFormat;

/*
 * @struct RTC_CalendarFormat
 * @brief Contiene fecha y hora a la cual se solicito la lectura
 * de algun sensor.
 */
typedef struct
{
	RTC_tstTimeFormat stTime;
	RTC_tstDateFormat stDate;
}RTC_CalendarFormat;

#endif /* SRC_RTC_RTC_PUB_H_ */
