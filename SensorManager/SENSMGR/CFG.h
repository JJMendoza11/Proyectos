/*
 * @file CFG.h
 *
 *  Created on: Aug 3, 2021
 *  @Author: lucky
 */

#ifndef SRC_SENSMGR_CFG_H_
#define SRC_SENSMGR_CFG_H_

#include "Prototype.h"



/*
 * Archivo para la configuración del proyecto.
 * Este archio contien dos macros:
 *
 * 1. BASIC_REQUEST
 * 2. COMPLEX_REQUEST
 *
 * Estas macros gestionan el flujo del codigo ya que la macro BASIC_REQUEST
 * solo regresara las carateristicas basica de cada sensor, el valor crudo que se
 * obtiene del sensor, sin procesar y la resolucion que tiene el sensor.
 * Mientras que la configuracion COMPLEX_REQUEST además de obtener estas dos
 * proipiedades del sensor obtiene el valor procesado y ademas obtiene el SubId del
 * sensor. Con esto nos referimos al Id que tiene dentro de cada modulo Dallas o MQx,
 * segun sea el caso.
 * Esto sea hace con el fin de hacerlo lo más escalable que sea posible, ya que
 * la enumeracion SENSMGR_tenSensorList contiene el orden, en el cual serán
 * llamados los diversos sensores pero no necesariamente
 * corresponde al Id interno de cada modulo.
 * Por ejemplo, si se tuviera un sensor MQ2 (que es sensible al alcohol, tendria, en
 * la enumeracion SENSMGR_tenSensorList el valor de 2. Sin embargo, dentro del
 * modulo MQx, tendría el Id 1.
 * Por lo que quedaría asi la información correspondiente a este MQ2.
 * Id principal = 2, SubId = 1.
 * Algo semegante pasaría con los sensores Dallas.
 *
 * Para el correcto funcionamiento del proyecto es necesario que al menos una de las dos macros
 * no este comentada.
 * Si las dos macros estan descomentadas el programa tomara la configuracion de BASIC_REQUEST.
 * Esto porque a dicha macro se le tiene preferencia y por seguirdad del proyecto elimina
 * la definicion de la macro COMPLEX_REQUEST.
 * Si se llegara a tener las dos macros comentadas al compilar el proyecto marcaria varios
 * errores. Por lo cual se recomienda tener al menos una macro sin comentar.
 */


//#define BASIC_REQUEST

#define COMPLEX_REQUEST



/*
 * Rutina de seguridad para que solo se tenga definida la macro BASIC_REQUEST en el proyecto.
 */
#ifdef BASIC_REQUEST
#undef COMPLEX_REQUEST
#endif

/*
 * Rutina de seguridad para que solo se tenga definida la macro COMPLEX_REQUEST en el proyecto.
 */
#ifdef COMPLEX_REQUEST
#undef BASIC_REQUEST
#endif

#endif /* SRC_SENSMGR_CFG_H_ */
