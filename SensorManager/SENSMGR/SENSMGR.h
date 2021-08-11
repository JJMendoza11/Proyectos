/*
 * @file SENSMGR.h
 *
 *  Created on: Aug 3, 2021
 * @Author: lucky
 */

#ifndef SRC_SENSMGR_SENSMGR_H_
#define SRC_SENSMGR_SENSMGR_H_

#include "Prototype.h"

#include "SENSMGR_pub.h"

/*
 * @fn SENSMGR_u32UpdateSampleRate
 * @brief Actualiza el tiempo de muestreo de cada sensor de forma independiente. El
 * tiempo total de muestreo tiene que ser menor a LONGEST_PERIOD y mayor a SHORTEST_PERIOD
 * en su equivalente en segundos.
 * @param u16SensorId Es el sensor que se dese cambiar el tiempo de muestreo.
 * Rango: [0, Total_enSensors).
 * @param pstNewSampleRate Estrucutura que contiene el nuevo tiempo de muestreo, con el
 * formato de dias, horas, minutos y segundos.
 */
extern uint32 SENSMGR_u32UpdateSampleRate(uint16 u16SensorId, SENSMGR_SamplingRate* pstNewSampleRate);

/*
 * @fn SENSMGR_u32ReadSensor
 * @brief Se obtienen las lectura de los sensores para mandar atravez de la tecnologia
 * LIDAR.
 * @param u16SensorId Es el sensor que se desea obtener su lectura.
 * Rango: [0, Total_enSensors).
 * @param pstLidarMsg Apuntador al cuerpo del mensaje LIDAR. EL encabezado se debe
 * de llenar en la funcion que llama a esta.
 * @return Retorna un OK, si paso el tiempo de muestreo y retorna un N_OK si aun
 * falta tiempo para proceder hacer la lectura del sensor.
 */
extern uint32 SENSMGR_u32ReadSensor(uint16 u16SensorId, SENSMGR_tstMessageBody* pstLidarMsg);

/*
 * @fn SENSMGR_vInitAllSensors
 * @brief Funcion que lleva acabo todas las rutinas de inicializacion de los sensores, la
 * calibración de los sensores MQx y la detección de todos los sensores de temperatura de
 * la familia Dallas conectados en la linea.
 * @param GPIOx Puerto necesario para la comunicación de la libreria OneWire.
 * @param pin Igual que el parametro previo se necesita para la inicializacion de la
 * libreria de OneWire.
 * @return void.
 */
extern void SENSMGR_vInitAllSensors(GPIO_TypeDef* GPIOx, uint16 pin);

#endif /* SRC_SENSMGR_SENSMGR_H_ */
