/*
 * @file MQ7_pub.h
 *
 *  Created on: Aug 1, 2021
 * @Author: lucky
 */

#ifndef SRC_MQX_MQX_PUB_H_
#define SRC_MQX_MQX_PUB_H_

/*
 * @enum MQx_tenValidSensIds
 * @brief Corresponde a los Ids de los senosres MQx.
 */
typedef enum
{
	MQx_enMQ7 = 0,
	MQx_enTotalMQSensors
}MQx_tenValidSensIds;


/*
 * @struct MQ_tstSensorProperties
 * Varaibles necesarias para hacer una correcta calibración y lectura en ppm
 * para cada sensor. El valor que puede tomar cada variable esta más desglozada
 * en la macro MQx_TABLE_INIT que se encuentra en el archivo "MQx_priv.h".
 */
typedef struct
{
	uint32 RL;
	float R0;
	float R0InCleanAir;
	float A;
	float Pot;
	uint16 SensorId;
}MQ_tstSensorProperties;

#endif /* SRC_MQX_MQX_PUB_H_ */
