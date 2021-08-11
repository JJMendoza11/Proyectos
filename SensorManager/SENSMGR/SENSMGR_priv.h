/*
 * @file SENSMGR_priv.h
 *
 *  Created on: Aug 3, 2021
 * @Author: lucky
 */

#ifndef SRC_SENSMGR_SENSMGR_PRIV_H_
#define SRC_SENSMGR_SENSMGR_PRIV_H_

#include "Prototype.h"
#include "CFG.h"

#include "Dallas.h"
#include "Dallas_pub.h"

#include "MQx.h"
#include "MQx_pub.h"

#include "SENSMGR_pub.h"

/* ------------------------------------------------------------------------------------------------------------------ */
/* Macros configurables para establecer el tiempo minimo entre una lectura y otra del mismo sensor.
 * Las siguientes 4 macros al final se sumaran dando el tiempo minimo en segundo que se tiene que esperar el uP
 * para hacer una lectura del mismo sensor. Cada sensor tendra su propio tiempo de muestreo pero todos tienen que
 * respetar el tiempo minimo entre lecturas.
 */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def SHORTEST_PERIOD_SEC
 * @brief El minimo de segundos que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define SHORTEST_PERIOD_SEC					(5U)

/*
 * @def SHORTEST_PERIOD_MIN
 * @brief El minimo de minutos que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define SHORTEST_PERIOD_MIN					(0U)

/*
 * @def SHORTEST_PERIOD_HRS
 * @brief El minimo de horas que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define SHORTEST_PERIOD_HRS					(0U)

/*
 * @def SHORTEST_PERIOD_DAY
 * @brief El minimo de dias que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define SHORTEST_PERIOD_DAY					(0U)



/* ------------------------------------------------------------------------------------------------------------------ */
/* Macros configurables para establecer el tiempo maximo entre una lectura y otra del mismo sensor.
 * Las siguientes 4 macros al final se sumaran dando el tiempo maximo en segundo que se tiene que se puede
 * esperar  el uP para hacer una lectura del mismo sensor. Cada sensor tendra su propio tiempo de muestreo
 * pero todos tienen que respetar el tiempo maximo entre lecturas.
 */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def LONGEST_PERIOD_SEC
 * @brief El maximo de segundos que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define LONGEST_PERIOD_SEC					(0U)

/*
 * @def LONGEST_PERIOD_MIN
 * @brief El maximo de minutos que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define LONGEST_PERIOD_MIN					(0U)

/*
 * @def LONGEST_PERIOD_HRS
 * @brief El maximo de horas que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define LONGEST_PERIOD_HRS					(0U)

/*
 * @def LONGEST_PERIOD_DAY
 * @brief El maximo de dias que se tiene que esperar entre una lectura y otra. Configurable.
 */
#define LONGEST_PERIOD_DAY					(3U)



/* ------------------------------------------------------------------------------------------------------------------ */
/* Macros No configurables necesarias para el funcionamiento adecuado del modulo SENSMGR */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def HRS_IN_ONE_DAY
 * @brief Macro que contiene el numero de horas que hay en un dia. No configurable.
 */
#define HRS_IN_ONE_DAY						(24U)

/*
 * @def SECS_IN_ONE_MIN
 * @brief Macro que contiene el numero de segundos que hay en un minuto. No configurable.
 */
#define SECS_IN_ONE_MIN						(60U)

/*
 * @def SECS_IN_ONE_HR
 * @brief Macro que contiene el numero de segundos que hay en una hora. No configurable.
 */
#define SECS_IN_ONE_HR						(3600U)

/*
 * @def SECS_IN_ONE_DAY
 * @brief Macro que emplea los valores de SECS_IN_ONE_HR y HRS_IN_ONE_DAY para establcer
 * el numero de segundos que hay en un dia. No configurable.
 */
#define SECS_IN_ONE_DAY						(SECS_IN_ONE_HR * HRS_IN_ONE_DAY)

/*
 * @def Min2Sec
 * @brief Macro que convierte cierto numero de minutos a segundos. No configurable.
 */
#define Min2Sec(min)						((uint32) (min * SECS_IN_ONE_MIN))

/*
 * @def Hrs2Sec
 * @brief Macro que convierte cierto numero de horas a segundos. No configurable.
 */
#define Hrs2Sec(hrs)						((uint32) (hrs * SECS_IN_ONE_HR))

/*
 * @def Days2Sec
 * @brief Macro que convierte cierto numero de dias a segundos. No configurable.
 */
#define Days2Sec(day)						((uint32) (day * SECS_IN_ONE_DAY))

/*
 * @def Time2Sec
 * @brief Macro que convierte la hora dada (hr : min : seg) en su equivalente en segundos.
 * No configurable.
 */
#define Time2Sec(hrs, min, sec)				((uint32)(Hrs2Sec(hrs) + Min2Sec(min) + sec))

/*
 * @def Sampling_in_sec
 * @brief Macro que convierte el nuevo periodo de muestreo de su formato
 * Dias : Hrs : Min : Seg a su equivalente en segundos. No configurable.
 */
#define Sampling_in_sec(d, h, m, s)			((uint32)(Days2Sec(d) + Hrs2Sec(h) + Min2Sec(m) + s))

/*
 * @def SHORTEST_PERIOD
 * @brief Convierte las macros SHORTEST_PERIOD_AAA (donde AAA corresponde DAY, HRS, Min y SEC) en su
 * equivalente en segundo. Lo que da como resultado el periodo más corto (en segundos)
 * que el uP puede leer un sensor en especifico. No configurable.
 */
#define SHORTEST_PERIOD						Sampling_in_sec(SHORTEST_PERIOD_DAY, SHORTEST_PERIOD_HRS, SHORTEST_PERIOD_MIN, SHORTEST_PERIOD_SEC)

/*
 * @def LONGEST_PERIOD
 * @brief Convierte las macros LONGEST_PERIOD_BBB (donde BBB corresponde DAY, HRS, MIN y SEC) en su
 * equivalente en segundo. Lo que da como resultado el periodo más largo (en segundos)
 * que el uP puede esperarse para leer un sensor en especifico. No configurable.
 */
#define LONGEST_PERIOD						Sampling_in_sec(LONGEST_PERIOD_DAY, LONGEST_PERIOD_HRS, LONGEST_PERIOD_MIN, LONGEST_PERIOD_SEC)



/* ------------------------------------------------------------------------------------------------------------------ */
/* Tablas de configuracion para emparejar de forma correcta los Ids internos de cada modulo con el de estemudlo
 * que funge solo como un contedor.
 */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def ID_TABLE
 * @brief Esta tabla corresponde al Id de cada sensor que se tiene dentro de cada modulo (MQx o Dallas).
 * El orden tiene que ser correspondiente con la enumeracion SENSMGR_tenSensorList. Esto
 * porque esta tabla tiene los Ids de cada sensor dentro de cada modulo. Los valores de esta macro
 * tienen que respetar los limites dados por la enumeracion MQx_tenValidSensIds o la macro
 * TOTAL_DEVICES_EXP, segun sea el caso. Configurable.
 */
#define ID_TABLE							\
{MQx_enMQ7, 0}

/*
 * @def MAX_ID_TABLE
 * @brief Tabla que se usara en la inicializacion para comprobar que todos los Ids establecidos en la
 * macro ID_TABLE respetendo el numero maximo de sensores que se tienen en cada modulo (Dallas y MQx).
 */
#define MAX_ID_TABLE						\
/* MQ7_enSensor,		Temp_enSensor 	*/	\
{MQx_enTotalMQSensors,  TOTAL_DEVICES_EXP}

/*
 * @def INIT_SAMPLERATE_TABLE
 * @brief Tabla que contiene el periodo de muestreo de cada sensor de forma inicial. Estos
 * valores de muestreos se escribiran de forma correcta en el modulo siempre y cuando esten
 * dentro del rango: [SHORTEST_PERIOD, LONGEST_PERIOD]. De lo contrario se establcera un
 * valor predefinido por la macro DEFAULT_TIME_IN_SEC.
 */
#define INIT_SAMPLERATE_TABLE				\
/* Sec,					Min,				Hrs, 				Ds	*/ 					 \
{ {0,					1,					0,					0},		/*MQ7_enSensor */ \
  {0,					1,					0,					0}		 /*Temp_enSensor*/ \
}

#ifdef BASIC_REQUEST

/*
 * @def POINTERS_TO_FUNC_TABLE
 * @brief Tabla de punteros a funciones para la obtencion del valor crudo del sensor y de la
 * resolucion del sensor. Esta tabla contiene las funciones necesarias para cumplir con
 * la configuracion BASIC_REQUEST del proyecto.
 */
	#define POINTERS_TO_FUNC_TABLE															\
		/* GetRawVal,						GetResolution */ 								\
		{ {MQx_u32GetRawVal,				MQx_u8GetResolution},		/*MQ7_enSensor */ 	\
		  {Dallas_u16GetRawVal,				Dallas_u8GetResolution}		/*Temp_enSensor*/	\
		}
/*
 * @struct SENSMGR_tstptr2functions
 * @brief Estructura que cumplen con el prototipo de las funciones para ser invocadas de
 * forma correcta y tener los resolutados.Esta estrucuta contiene los punteros para cumplir
 * con la configuracion BASIC_REQUEST del proyecto.
 */
	typedef struct
	{
		uint16 (*p2fnReqRawVal)(uint16);
		uint8 (*p2fnReqRes)(uint16, uint8);
	}SENSMGR_tstptr2functions;

#endif

#ifdef COMPLEX_REQUEST
	/*
	 * @def POINTERS_TO_FUNC_TABLE
	 * @brief Tabla de punteros a funciones para la obtencion del valor crudo del sensor, la
	 * resolucion del sensor y su valor procesado. Esta tabla contiene las funciones necesarias
	 * para cumplir con la configuracion COMPLEX_REQUEST del proyecto.
	 */
#define POINTERS_TO_FUNC_TABLE																		\
	/* ProcessedVal,				GetRawVal,						GetResolution */ 				\
	{ {MQx_fGetppm, 				MQx_u16GetRawVal,				MQx_u8GetResolution},			\
	  {Dallas_fGetTempC,		Dallas_u16GetRawVal,			Dallas_u8GetResolution}				\
	}

/*
 * @struct SENSMGR_tstptr2functions
 * @brief Estructura que cumplen con el prototipo de las funciones para ser invocadas de
 * forma correcta y tener los resolutados.Esta estrucuta contiene los punteros para cumplir
 * con la configuracion COMPLEX_REQUEST del proyecto.
 */
	typedef struct
	{
		float (*p2fnGetProcessedVal)(uint16);
		uint16 (*p2fnReqRawVal)(uint16);
		uint8 (*p2fnReqRes)(uint16, uint8);
	}SENSMGR_tstptr2functions;

#endif

#endif /* SRC_SENSMGR_SENSMGR_PRIV_H_ */
