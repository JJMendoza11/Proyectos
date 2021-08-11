/*
 * @file Dallas.h
 *
 *  Created on: Jul 27, 2021
 * @Author: lucky
 */

#ifndef SRC_DALLAS_DALLAS_H_
#define SRC_DALLAS_DALLAS_H_

#include "Prototype.h"

/*
 * @fn Dallas_vBegin
 * @brief Inicia la rutina para encontrar todos los sensores en la linea.
 * Los sensores que vaya a ser encontrados tambien depende de la macro
 * TOTAL_DEVICES_EXP. Si hay más sensores que el valor de la macro serán
 * ignorados los sensores n - TOTAL_DEVICES_EXP.
 * @param void.
 * @return void.
 */
extern void Dallas_vBegin(void);

/*
 * @fn Dallas_u8GetResolution
 * @brief Se obtiene la resolucion del sensor solicitado. Se puede solicitar
 * la resolucion que se tiene guardada en el modulo o directamente la que
 * tiene el sensor.
 * @param device Es el sensor solicitado. Tiene que ser menor a la macro
 * TOTAL_DEVICES_EXP.
 * @param current Se indica si se solicita el valor guardado (0) o el que tiene
 * el sensor (1).
 * @return Retorna la resolcuion del sensor solicitado.
 */
extern uint8 Dallas_u8GetResolution(uint16 device, uint8 current);

/*
 * @fn Dallas_u8SetResolution
 * @brief Se establece en el sensor la resolucion solicitada.
 * Además guarda la resolucion para futuras peticiones.
 * @param device Es el sensor solicitado. Tiene que ser menor a la macro
 * TOTAL_DEVICES_EXP.
 * @param resolution Indica la resolucion a establecer en el sensor.
 * Valores validos: [9, 10, 11, 12].
 * @return OK (0U) Si se establecio de forma correcta de lo contrario
 * retorna un N_OK (255U).
 */
extern uint8 Dallas_u8SetResolution(uint16 device, uint8 resolution);

/*
 * @fn Dallas_vSetAutoSave
 * @brief Se indica que si se desea guardar el valor en la ROM del sensor
 * cada vez que se le haga una escritura al scratchpad.
 * @param state Si se activa el autoguardado (1) ó no (0).
 * @return void.
 */
extern void Dallas_vSetAutoSave(uint8 state);

/*
 * @fn Dallas_u8RequestTemp
 * @brief Funcion que solicita al sensor que realice la conversion de la temperatura.
 * Esta funcion va esperar hasta que el sensor termine de hacer la conversion.
 * @param device Es el sensor solicitado. Tiene que ser menor a la macro
 * TOTAL_DEVICES_EXP.
 * @return Retorna OK si la conversion fue excitosa N_OK si no.
 */
extern uint8 Dallas_u8RequestTemp(uint16 device);

/*
 * @fn Dallas_u16GetRawTemp
 * @brief Retorna el valor de la temperatura de forma cruda.
 * @param device Es el sensor solicitado. Tiene que ser menor a la macro
 * TOTAL_DEVICES_EXP.
 * @return Regresa la temperatura cruda.
 */
extern uint16 Dallas_u16GetRawVal(uint16 device);

/*
 * @Dfn allas_fGetTempC
 * @brief Retorna la temperatura en grados Centrigrados del sensor solicitado.
 * @param device Es el sensor solicitado. Tiene que ser menor a la macro
 * TOTAL_DEVICES_EXP.
 * @return Retorna la temperatura del sensor.
 */
extern float Dallas_fGetTempC(uint16 device);

#endif /* SRC_DALLAS_DALLAS_H_ */
