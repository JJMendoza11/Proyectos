/*
 * @file OneWire_priv.h
 *
 *  @brief Created on: Jul 26, 2021
 *  A pesar de que hay varias macros configurable se recomienda no cambiar su valor
 *  a no sé que los cambios esten fundamentados en el datasheet del sensor.
 *  @Author lucky
 */

#ifndef SRC_ONEWIRE_ONEWIRE_PRIV_H_
#define SRC_ONEWIRE_ONEWIRE_PRIV_H_

/* ------------------------------------------------------------------------------------------------------------------ */
/* Macros para el Reset del Sensor. */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def RESET_PULSE_T
 * @brief Tiempo minimo en us que tiene que establecerse en bajo para que el sensor
 * lo detecte como un pulso de "reset". Rango: [480, 960]. Configurable.
 */
#define RESET_PULSE_T					480


/*
 * @def PRESENCE_PULSE_T
 * @brief Tiempo en us para que el sensor baje la linea una vez que se inicio el proceso
 * de "Reset and Presence Pulse". Rango: [15, 70]. Configurable.
 */
#define PRESENCE_PULSE_T				70


/*
 * @def IDLE_PULSE_T
 * @brief Tiempo que dura la respuesta del sensor. El tiempo de respuesta del sensor
 * dura 480us. No configurable
 */
#define IDLE_PULSE_T					(480 - PRESENCE_PULSE_T)



/* ------------------------------------------------------------------------------------------------------------------ */
/* Macros para establecer un Uno Logico. */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def WRITE_HIGH_T
 * @brief Tiempo en us que necesita bajar la linea para indicar al sensor que se
 * escribio un uno. Rango: [1, 15]. Configurable.
 */
#define WRITE_HIGH_T					10


/*
 * @def IDLE_HIGH_T
 * @brief Tiempo en us que la linea se tiene que dejar en alto para que el
 * sensor lea el uno. No configurable.
 */
#define IDLE_HIGH_T						(65 - WRITE_HIGH_T)



/* Macros para establecer un Cero Logico. */

/*
 * @def WRITE_LOW_T
 * @brief Tiempo en us para escribir un 0 logico. No Configurable.
 */
#define WRITE_LOW_T						65

/*
 * @def IDLE_LOW_T
 * @brief Tiempo en us que se tiene que esperar el uP para
 * seguir escribiendo más bits. No configurable.
 */
#define IDLE_LOW_T						(70 - WRITE_LOW_T)



/* ------------------------------------------------------------------------------------------------------------------ */
/* Macros para poder leer de forma correcta el Sensor. */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def READ_TGR_T
 * @brief Tiempo en us una vez se bajo el cable para que el sensor escriba.
 * No Configurable
 */
#define READ_TGR_T						3


/*
 * @def READ_SAMPLE_WAIT
 * @brief Tiempo en us para hacer una correcta lectura del cable.
 * No configurable.
 */
#define READ_SAMPLE_WAIT				10


/*
 * @def READ_IDLE_T
 * Tiempo en us restante para poder realizar otra acción de lectura o escritura.
 */
#define READ_IDLE_T						(66 - (READ_TGR_T + READ_SAMPLE_WAIT))



/* ------------------------------------------------------------------------------------------------------------------ */
/* Macros para los comandos de ROM del sensor. */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def READ_ROM_CMD
 * @brief Comando para leer los 64 bits del sensor. No configurable.
 */
#define READ_ROM_CMD					0x33


/*
 * @def MATCH_ROM_CMD
 * @brief Comando para hablarle a un sensor en concreto. No configurable.
 */
#define MATCH_ROM_CMD					0x55


/*
 * @def SEARCH_ROM_CMD
 * @brief Comando para realizar el proceso de reconocimiento del cable.
 * Sirve para detectar todos los sensores conectados en el cable.
 * No configurable.
 */
#define SEARCH_ROM_CMD					0xF0


/*
 * @def ALARM_SEARCH_CMD
 * @brief Comando para ver que sensor ya excedio de las TL o TH.
 * No configurable.
 */
#define ALARM_SEARCH_CMD				0xEC


/*
 * @def SKIP_ROM_CMD
 * @brief Comando para escribir a todos los senosres. Solo usar si se
 * tiene un unico sensor. No configurable.
 */
#define SKIP_ROM_CMD					0xCC



/* ------------------------------------------------------------------------------------------------------------------ */
/* Posibles resultados al recibir el bit y su complemento a la hora de
 * buscar un dispositivo.
 */
/* ------------------------------------------------------------------------------------------------------------------ */

/*
 * @def ID_CONFLICT
 * @brief Se detecto un conflicto a la hora de leer el cable durante el
 * comando de SEARCH_ROM_CMD. No configurable.
 */
#define ID_CONFLICT						0U


/*
 * @def NO_ID_CONFLICT
 * @brief La lectura del bit y su complemento fue el correcto. No configurable.
 */
#define NO_ID_CONFLICT					1U


/*
 * @def NO_DIVECE_CONNECTED
 * @brief Valor que se espera a la hora de recibir el bit y su complemento
 * Al estar en alto significa que no hay sensores conectados en la red.
 * No configurable.
 */
#define NO_DIVECE_CONNECTED				2U



/* @def ROM_SIZE_BITS
 * @brief Tamaño de la ROM del sensor en bits.
 */
#define ROM_SIZE_BITS					64U

#endif /* SRC_ONEWIRE_ONEWIRE_PRIV_H_ */
