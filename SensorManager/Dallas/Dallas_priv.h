/*
 * @file Dallas_priv.h
 *
 *  Created on: Jul 27, 2021
 * @Author: lucky
 */

#ifndef SRC_DALLAS_DALLAS_PRIV_H_
#define SRC_DALLAS_DALLAS_PRIV_H_

/*@def SAVE_TIME
 * Tiempo que se tiene que esperar el uP para que el sensor escriba en la EPROM.
 * Rango segun el datasheet [2, 10]ms. El valor esta en us. Configurable.
 */
#define SAVE_TIME							10000U


/* ------------------------------------------------------------------------------------------------------------------ */
/* Tamaño de la RAM del sensor en bytes. */
/* ------------------------------------------------------------------------------------------------------------------ */


/*
 * @def SCRATCHPAD_LEN
 * @brief Tamaño del scratchpad de cada sensor contando el CRC que es el ultimo byte.
 * No configurable.
 */
#define SCRATCHPAD_LEN						9U

/*
 * @def CONVERSION_HAS_END
 * @brief Valor esperado justo cuando el sensor termine de realizar una conversion de
 * la temperatura. No configurable.
 */
#define CONVERSION_HAS_END					1U

/*
 * @def CONVERSION_IS_RUNNING
 * @brief Valor que indica que el sensor no a terminado de convertir la temperatura.
 * No configurable.
 */
#define CONVERSION_IS_RUNNING				0U

/*
 * @def MAX_CONVERSION_TIMEOUT
 * @brief Tiempo maximo en ms de espera para una conversion de temperatua en el sensor.
 * No configurable
 */
#define MAX_CONVERSION_TIMEOUT				750U

/*
 * @def WAIT_FOR_1MS
 * @brief Tiempo de espera en us. Es quivalente a 1ms. No configurable.
 */
#define WAIT_FOR_1MS						1000U

/* ------------------------------------------------------------------------------------------------------------------ */
/* Comandos para escribir en el Scratchpad del sensor. */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def WRITE_SCRATCHPAD_CMD
 * @brief Comando para escribir en el sensor las alarmas de TH, TL y la resolucion del sensor.
 * No configurable.
 */
#define WRITE_SCRATCHPAD_CMD				0x4E

/*
 * @def READ_SCRATCHPAD_CMD
 * @brief Comando para leer todo el scratchpad del sensor. No configurable.
 */
#define READ_SCRATCHPAD_CMD					0xBE

/*
 * @def SAVE_SCRATCHPAD_CMD
 * @brief Comando para que el sensor guarde los nuevos valores del scratchpad en su ROM. No
 * configurable.
 */
#define SAVE_SCRATCHPAD_CMD					0x48

/*
 * @def CONVERT_TEMP_CMD
 * @brief Comando para que el sensor inicie la conversion de temperatura. No configurable.
 */
#define CONVERT_TEMP_CMD					0x44

/*
 * @def RECALL_CMD
 * @brief Comando para que el sensor agarre los datos del scratchpad de la ROM y los pase
 * a la RAM. No configurable.
 */
#define RECALL_CMD							0xB8

/*
 * @def READ_PWR_MODE_CMD
 * @brief Comando para que el sensor nos indique si esta alimentado de forma paracita o no.
 * No configurable.
 */
#define READ_PWR_MODE_CMD 					0xB4

/* ------------------------------------------------------------------------------------------------------------------ */
/* Valores que puede tener el registro de configuracion del sensor. */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def TEMP_9_BIT
 * @brief Valor para establecer una resolucion de 9 bits en el sensor. No configurable.
 */
#define TEMP_9_BIT							0x1F

/*
 * @def TEMP_10_BIT
 * @brief Valor para establecer una resolucion de 10 bits en el sensor. No configurable.
 */
#define TEMP_10_BIT							0x3F

/*
 * @def TEMP_11_BIT
 * @brief Valor para establecer una resolucion de 11 bits en el sensor. No configurable.
 */
#define TEMP_11_BIT							0x5F

/*
 * @def TEMP_12_BIT
 * @brief Valor para establecer una resolucion de 12 bits en el sensor. No configurable.
 */
#define TEMP_12_BIT							0x7F

/*
 * @struct Dallas_tstScratchPad
 * @brief Estructura que contiene la representación de los bytes recibidos en el
 * Sratchpad del sensor.
 */
typedef struct
{
	uint8 TempLsb;
	uint8 TempMsb;
	uint8 AlarmTh;
	uint8 AlarmTl;
	uint8 Res;
	uint8 Reserver[3];
	uint8 Crc;
}Dallas_tstScratchPad;

#endif /* SRC_DALLAS_DALLAS_PRIV_H_ */
