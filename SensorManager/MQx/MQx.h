/*
 * @file MQ7.h
 *
 *  Created on: Aug 1, 2021
 * @Author: lucky
 */

#ifndef SRC_MQX_MQX_H_
#define SRC_MQX_MQX_H_

#include "MQx_pub.h"
#include "Prototype.h"


/*
 * @fn MQx_vInit
 * @brief Funcion que inicializa todos los sensores MQx. La
 * iniciliazacion consta de la calibracion de cada sensor y
 * comprueba que los valores de la macro MQx_TABLE_INIT sean
 * correctos. Si la inicialización falla no se podra hacer
 * la conversión a ppm de cada gas.
 * @param void.
 * @return void.
 */
extern void MQx_vInit(void);


/*
 * @fn MQx_u16GetRawVal
 * @brief Hace la lectura del sensor solicitado y retorna
 * su valor 'crudo'.
 * @param device Indica el sensor que se quiere leer.
 * Rango: [0, MQx_enTotalMQSensors).
 * @return Retorna el valor del ADC 'crudo'.
 */
extern uint16 MQx_u16GetRawVal(uint16 device);


/*
 * @fn MQx_fGetR0Value
 * @brief Retorna el valor calibrado para la resistencia R0.
 * del sensor correspondiente.
 * @param device Indica el sensor que se quiere leer el valor
 * de R0. Rango: [0, MQx_enTotalMQSensors).
 * @return Retorna el valor de R0.
 */
extern float MQx_fGetR0Value(uint16 device);

/*
 * @fn MQx_fGetppm
 * @brief hace la conversion de la lectura del ADC a ppm.
 * @brief device Inidca el sensor que se quiere obener las ppm.
 * Rango: [0, MQx_enTotalMQSensors).
 * @return Retorna las ppm del gas principal de cada sensor.
 */
extern float MQx_fGetppm(uint16 device);

/*
 * @fn MQX_vGetProperties
 * @brief Retorna los valores de la esctructura MQ_tstSensorProperties
 * del sensor solicitado.
 * @param device Indica el sensor que se quiere obtener sus propiedades.
 * Rango: [0, MQx_enTotalMQSensors).
 * @param *properties Apuntador para escribir los valores de la estructura
 * MQ_tstSensorProperties.
 * @return void.
 */
extern void MQX_vGetProperties(uint16 device, MQ_tstSensorProperties* properties);

/*
 * @fn MQx_u8GetResolution
 * @brief Funcion que retorna la resolucion actual o guardad del ADC.
 * @param device Indica el sensor que se quiere obtener su resolucion.
 * Rango: [0, MQx_enTotalMQSensors).
 * @param current Se indica si se solicita el valor guardado (0) o el que tiene
 * el sensor (1).
 * @return Los retornos validos son: {6, 8, 10, 12}.
 */
extern uint8 MQx_u8GetResolution(uint16 device, uint8 current);

#endif /* SRC_MQX_MQX_H_ */
