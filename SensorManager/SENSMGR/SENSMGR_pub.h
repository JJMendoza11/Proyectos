/*
 * @file SENSMGR_pub.h
 *
 *  Created on: Aug 3, 2021
 * @Author: lucky
 */

#ifndef SRC_SENSMGR_SENSMGR_PUB_H_
#define SRC_SENSMGR_SENSMGR_PUB_H_

#include "CFG.h"
#include "RTC_pub.h"

/*
 * @enum SENSMGR_tenSensorList
 * @brief Lista de todos los sensores que se tienen, tanto MQx, como los Dallas.
 * Esta lista puede ir en el orden que sea, solo tiene el orden de como se iran
 * leyendo los sensores. Sin embargo las tablas ID_TABLE, MAX_ID_TABLE, INIT_SAMPLERATE_TABLE
 * y POINTERS_TO_FUNC_TABLE tienen que respetar la configuración dada por esta enumeracion.
 */
typedef enum
{
	MQ7_enSensor = 0,
	Temp_enSensor,
	Total_enSensors
}SENSMGR_tenSensorList;

/*
 * @struct SENSMGR_SamplingRate
 * @brief Estructura que se emplea para establecer el nuevo period de muestreo
 * de cada uno de los sensores.
 */
typedef struct
{
	uint8 u8Secs;
	uint8 u8Mins;
	uint8 u8Hrs;
	uint8 u8Days;
}SENSMGR_SamplingRate;

#ifdef BASIC_REQUEST
/*
 * @struct SENSMGR_tstMessageBody
 * @brief Esta estructura corresponde a los datos que se enviaran por la
 * tecnologia LIADR en la configurarion del proyecto BASIC_REQUEST. Esta
 * parte corresponde al cuerpo del mensaje.
 */
	typedef struct
	{
		uint32 u32ADCResolution;
		uint16 u16SensorValue;
		RTC_CalendarFormat stCal;
	}SENSMGR_tstMessageBody;
#endif

#ifdef COMPLEX_REQUEST
/*
* @struct SENSMGR_tstMessageBody
* @brief Esta estructura corresponde a los datos que se enviaran por la
* tecnologia LIADR en la configurarion del proyecto COMPLEX_REQUEST. Esta
* parte corresponde al cuerpo del mensaje.
*/
	typedef struct
	{
		uint32 u32ADCResolution;
		uint16 u16SubId;
		uint16 u16SensorValue;
		float fConvertedValue;
		RTC_CalendarFormat stCal;
	}SENSMGR_tstMessageBody;
#endif

/*
 * @struct SENSMGR_tstMessageHeader
 * @brief Corresponde a la cabecera del mensaje. Dicha cabezara contiene
 * el Id que le corresponed a cada sensor, asi como un "padding" explicito.
 * Esto debido a que el cuerpo del mensaje empieza con una variable uint32.
 */
typedef struct
{
	uint16 u16SensorId;
	uint16 u16Padding;
}SENSMGR_tstMessageHeader;

/*
 * @struct SENSMGR_tstFullMessage
 * @brief Estructura completa del mensaje. Contiene la estrucutra de la cabecera
 * como la estrucutra del cuerpo del mensaje. Si se deseara agregar un 'cola' al
 * mensaje se tendría que agregar la estrucutra correspondiente de este apartado.
 */
typedef struct
{
	SENSMGR_tstMessageHeader stHeader;
	SENSMGR_tstMessageBody stBody;
}SENSMGR_tstFullMessage;

#endif /* SRC_SENSMGR_SENSMGR_PUB_H_ */
