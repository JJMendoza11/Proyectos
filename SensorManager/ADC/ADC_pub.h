/*
 * @file ADC_pub.h
 *
 *  Created on: Aug 1, 2021
 * @Author: lucky
 */

#ifndef SRC_ADC_ADC_PUB_H_
#define SRC_ADC_ADC_PUB_H_

/*
 * @def ADC_RESOLUTION_12BITS
 * @brief Resolucion de 12 bits. No configurable
 */
#define ADC_RESOLUTION_12BITS		(12U)


/*
 * @def ADC_RESOLUTION_10BITS
 * @brief Resolucion de 10 bits. No configurable
 */
#define ADC_RESOLUTION_10BITS		(10U)

/*
 * @def ADC_RESOLUTION_8BITS
 * @brief Resolucion de 8 bits. No configurable
 */
#define ADC_RESOLUTION_8BITS		(8U)

/*
 * @def ADC_RESOLUTION_6BITS
 * @brief Resolucion de 6 bits. No configurable
 */
#define ADC_RESOLUTION_6BITS		(6U)

/*
 * @enum ADC_tenValidSensIds
 * @brief Cotiene el Id de todos los canales que estan habilitados en el ADC.
 * Configurable.
 */
typedef enum
{
	ADC_enMQ7_Sensor = 0,
	ADC_enTotalSensors
}ADC_tenValidSensIds;

#endif /* SRC_ADC_ADC_PUB_H_ */
