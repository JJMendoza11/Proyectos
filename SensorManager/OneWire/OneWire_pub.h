/*
 * @file OneWire_pub.h
 *
 *  Created on: 27 jul. 2021
 * @Author lucky
 */

#ifndef SRC_ONEWIRE_ONEWIRE_PUB_H_
#define SRC_ONEWIRE_ONEWIRE_PUB_H_

#include "Prototype.h"

/*
 * @def SENS_PRESENT
 * @brief Valor que indica que el sensor si respondio al pulso de 'reset'.
 * No configurable.
 */
#define SENS_PRESENT					0


/*
 * @def SENS_NOT_PRESENT
 * @brief Valor que indica que ningun sensor respondio al pulos de 'reset'.
 */
#define SENS_NOT_PRESENT				1

/*
 * @def ROM_SIZE_BYTES
 * @brief Tamaño en bytes de la memoria ROM del sensor.
 */
#define ROM_SIZE_BYTES					8U

/*
 * @typedef DeviceAddess
 * Tipo de dato para guarda el valor de la ROM de cada sensor.
 */
typedef uint8 DeviceAddess[ROM_SIZE_BYTES];

#endif /* SRC_ONEWIRE_ONEWIRE_PUB_H_ */
