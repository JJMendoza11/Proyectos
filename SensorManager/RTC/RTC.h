/*
 * RTC.h
 *
 *  Created on: Jul 9, 2021
 *      Author: lucky
 */

#ifndef SRC_RTC_RTC_H_
#define SRC_RTC_RTC_H

#include "Prototype.h"

#include "RTC_pub.h"

/*
 * @fn MX_RTC_Init
 * @brief Contiene el codigo generado por el IDE para
 * haer funcionar el periferio de RTC.
 * @param void.
 * @return void.
 */
void MX_RTC_Init(void);

/*
 * @fn RTC_u32GetCalendarInfo
 * @brief Funcion que lee la fecha y hora del sistema y las pasa
 * a una estructura del tipo RTC_CalendarFormat.
 * @param stCalendar puntero a la estructura donde se desea guardad
 * la fecha y hora del sistema para su procesamiento.
 * @return Retorna 0 si se hizo una lectura correcta de la fecha y
 * hora del sistema y retorna 1 si alguna de estas dos no se pudo
 * obtener.
 */
uint32 RTC_u32GetCalendarInfo(RTC_CalendarFormat* stCalendar);

#endif /* SRC_RTC_RTC_H_ */
