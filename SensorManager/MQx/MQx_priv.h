/*
 * @file MQ7_priv.h
 *
 *  Created on: Aug 1, 2021
 * @Author: lucky
 */

#ifndef SRC_MQX_MQX_PRIV_H_
#define SRC_MQX_MQX_PRIV_H_

#include "ADC_pub.h"

/* @def MAX_12BIT_VALUE
 * @brief Valor maximo que se puede conseguir con 12 bits de resolución.
 * Es del tipo uint16. No configurable.
 *
 */
#define MAX_12BIT_VALUE								4095U


/* @def MAX_10BIT_VALUE
 * @brief Valor maximo que se puede conseguir con 10 bits de resolución.
 * Es del tipo uint16. No configurable.
 */
#define MAX_10BIT_VALUE								1023U


/* @def MAX_8BIT_VALUE
 * @brief Valor maximo que se puede conseguir con 8 bits de resolución.
 * Es del tipo uint16. No configurable.
 */
#define MAX_8BIT_VALUE								255U


/* @def MAX_6BIT_VALUE
 * @brief Valor maximo que se puede conseguir con 6 bits de resolución.
 * Es del tipo uint16. No configurable.
 */
#define MAX_6BIT_VALUE								63U


/* @def NUMBER_OF_SAMPLES
 * @brief Numero de muestras para la calibracion de todos los sensores.
 * Configurable.
 * Min Val: 0x00
 * Max Val: 0xFFFF*/
#define NUMBER_OF_SAMPLES							50U

/* @def TIME_BETWEEN_SAMPLES
 * @brief Tiempo que se espera para tomar cada muestra de la calibracion.
 * El valor esta en milisegundos.
 * Configurable.
 * Min Val 0x00
 * Max Val 0xFFFFFFFF
 * */
#define TIME_BETWEEN_SAMPLES						500


/* @def MQx_TABLE_INIT
 * @brief Tabla de inicilización para los sensores MQx. La tabla tiene que corresponder al valor de:
 * MQx_enTotalMQSensors, dicho valor se encuentra en el archivo "MQx_pub.h".
 * Configurable.
 * 		- RL: Valor de la resistencia RL en Kohms. Este valor se puede leer en la placa del sensor.
 * 			Min Val 0x00
 * 			MAx Val 0xFFFFFFFF
 * 		- R0: El valor de esta variable es indiferente, ya que se sobre escribe en la rutina de
 * 			inicialización. El valor tiene que ser de tipo float.
 * 			Se recomienda establecer el valor de 0.0f.
 * 		- R0InCelanAir: Valor que tiene la resistencia R0 en aire limpi. Dicho valor se encuentra
 * 			en el datasheet de cada sensor. El valor tiene que ser de tipo float.
 * 		- A: Todos los sensores corresponden a una funcion del tipo exponencial Ax^B. Donde A y B
 * 			 se calculan mediante las graficas que vienen en el datasheet de cada sensor; 'x'
 * 			 corresponde a la lectura del sensor. El valor tiene que ser del tipo float.
 * 		- Pot: Corresponde al valor de B en la ecuacion Ax^B. El valor tiene que ser del tipo float.
 * 		- SensorId: Corresponde al canal correspondiente del ADC.
 * 					El valor tiene que estar en el rango [0, ADC_enTotalSensors).
 */
#define MQx_TABLE_INIT  																													\
/*RL,				R0,				R0InCleanAir,			A, 					Pot,			SensorId */ 								\
{{1,				0.0f,			25.7f,					9.4653f,			-1.522,			ADC_enMQ7_Sensor}}		/* MQx_enMQ7 */


#endif /* SRC_MQX_MQX_PRIV_H_ */
