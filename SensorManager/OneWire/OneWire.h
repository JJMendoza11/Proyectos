/*
 * @file OneWire.h
 *
 *  Created on: Jul 26, 2021
 * @Author: lucky
 */

#ifndef SRC_ONEWIRE_ONEWIRE_H_
#define SRC_ONEWIRE_ONEWIRE_H_

#include "main.h"

#include "Prototype.h"

#include "OneWire_pub.h"

/*
 * @fn OneWire_vInit
 * @brief Inicializa las variables estaticas en bases al pin y puerto que se desea usar.
 * @param GPIOx Parametro del tipo GPIO_TypeDef que indica el puero a utilizar.
 * @param pin Parametro que indica el pin a utilizar.
 * @return void.
 */
extern void OneWire_vInit(GPIO_TypeDef* GPIOx, uint16 pin);

/*
 * @fn OneWire_u8Reset
 * @brief Funcion que hace la rutina de 'Reset and Presence Pulse'.
 * @param void.
 * @return Retorna 0 si la respuesta del sensor fue correcta y 1 si no lo fue.
 */
extern uint8 OneWire_u8Reset(void);

/*
 * @fn OneWire_vWriteBit
 * @brief Establece en alto o en bajo el cable para que el sensor lo lea.
 * @param bit Valor del bit que se desea escribir en la linea (1 ó 0).
 * @return void.
 */
extern void OneWire_vWriteBit(uint8 bit);

/*
 * @fn OneWire_u8ReadBit
 * @brief Lee el valor de la linea.
 * @param void.+
 * @return retorna el valor de la linea, equivalente a un bit (1 ó 0).
 */
extern uint8 OneWire_u8ReadBit(void);

/*
 * @fn OneWire_vWrite
 * @brief Funcion para escribir un byte completo en la linea.
 * @param byte Valor a escribir en la linea.
 * @return void.
 */
extern void OneWire_vWrite(uint8 byte);

/*
 * @fn OneWire_vWriteBytes
 * @brief Escribe una serie de bytes en la linea.
 * @param bytes Apuntaodr al buffer que se quiere escribir.
 * @param len Tamaño del buffer.
 */
extern void OneWire_vWriteBytes(uint8* bytes, uint8 len);

/*
 * @fn OneWire_u8Read
 * @brief Lee un byte completo y retorna el valor que se leyo.
 * @param void.4
 * @return byte leido en el cable.
 */
extern uint8 OneWire_u8Read(void);

/*
 * @fn OneWire_u8ReadBytes
 * @brief Lee un determinado numero de bytes indicados por bufLen.
 * @param buf Apuntador al buffer donde se desea gaurdar los datos.
 * @param bufLen Numero de bytes a leer.
 * @return void.
 */
extern void OneWire_vReadBytes(uint8* buf, uint8 bufLen);

/*
 * @fn OneWire_vSelectSens
 * @brief Ejecuta el comando de ROM para hablarle a un sensor en especifico.
 * @param rom Apuntador a los 64bits de la ROM del sensor al que se le desea
 * hablar.
 * @return void.
 */
extern void OneWire_vSelectSens(uint8* rom);

/*
 * @fn OneWire_vSkip
 * @brief Ejecuta el comando de 'skip' para que todos los sensores atiendan a
 * al comando de RAM. Se recomienda utilizar esta funcion solo si se tiene un
 * sensor.
 * @param void.
 * @return void.
 */
extern void OneWire_vSkip(void);

/*
 * @fn OneWire_vResetSearch
 * @brief Reinicia la variables necesarias para encontrar todos los dispositovos
 * en la linea.
 * @param void.
 * @param void.
 */
extern void OneWire_vResetSearch(void);

/*
 * @fn OneWire_vSearch
 * @brief Realiza la rutina de busqueda en la linea. Encuentra todos los sensores
 * que se encuentran en la linea.
 * @param newAdrr Apuntador parra guardar los valores de la ROM del sensor encontrado.
 * @return void.
 */
extern uint8 OneWire_vSearch(uint8* newAdrr);

/*
 * @fn OneWire_u8CRC8
 * @brief Realiza el calculo del CRC del mensaje recibido para comprar que sea valido.
 * @param Buf Apuntador que contiene el mensaje a calcular el CRC.
 * @param len Tamaño del buffer.
 * @return Retorna el CRC calculado del mensaje recibido.
 */
extern uint8 OneWire_u8CRC8(uint8* Buf, uint8 len);

#endif /* SRC_ONEWIRE_ONEWIRE_H_ */
