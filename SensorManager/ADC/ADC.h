/*
 * ADC.h
 *
 *  Created on: Jul 9, 2021
 *      Author: lucky
 */

#ifndef SRC_ADC_ADC_H_
#define SRC_ADC_ADC_H_

#include "Prototype.h"

/*
 * @fn MX_ADC_Init
 * @brief Funcion generado por IDE para inicializar el ADC.
 * @param void
 * @return void
 */
extern void MX_ADC_Init(void);


/*
 * @fn ADC_u32ReadChannel
 * @brief Funcion que lee la lectura del canal correspondiente
 * @param channel indica el canal que se desea leer.
 * Valor tiene que estar en el rango de [0, ADC_enTotalSensors).
 * @return Retorna el valor de la lectura del ADC.
 */
extern uint32 ADC_u32ReadChannel(uint16 channel);

/*
 * @fn ADC_u32GetResolution
 * @brief Funcion que retorna la resolucion del ADC segun el Handler.
 * @param void
 * @return resolucion {6, 8, 10, 12}.
 */
extern uint32 ADC_u32GetResolution(void);


#endif /* SRC_ADC_ADC_H_ */
