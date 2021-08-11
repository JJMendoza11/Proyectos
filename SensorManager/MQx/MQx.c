/*
 * @file MQ7.c
 *
 *  Created on: Aug 1, 2021
 * @Author: lucky
 */

#include "stm32l0xx_hal.h"

#include "math.h"
#include "Prototype.h"

#include "ADC.h"
#include "ADC_pub.h"

#include "MQx.h"
#include "MQx_priv.h"
#include "MQx_pub.h"

static uint8 myResolution = 0x00;
static uint16 myMaxAdcVal = 0x00;
static MQ_tstSensorProperties mySensorMq[MQx_enTotalMQSensors] = MQx_TABLE_INIT;

uint8 __u8ValidTable(void)
{
	uint8 state = OK;
	uint16 i;

	for(i = 0; i < MQx_enTotalMQSensors; i++)
	{
		if(mySensorMq[i].SensorId >= ADC_enTotalSensors)
		{
			state = N_OK;
			break;
		}
	}

	return state;
}

float __fResistanceCalculation(uint16 device)
{
	uint16 raw = MQx_u16GetRawVal(device);
	float r = (float)(mySensorMq[device].RL * (float)((myMaxAdcVal - raw) / raw));

	return r;
}

void __vCalibration(void)
{
	uint16 device;
	uint16 i;
	float r0 = 0;

	for(device = 0; device < (uint16)MQx_enTotalMQSensors; device++)
	{
		/*
		 * Se obtiene un promedio de varias muestras para hacerlo lo
		 * más preciso.
		 */

		for(i = 0; i < (uint16)NUMBER_OF_SAMPLES; i++)
		{
			r0 += __fResistanceCalculation(device);
			HAL_Delay(TIME_BETWEEN_SAMPLES);
		}

		r0 = r0 / NUMBER_OF_SAMPLES;

		/*
		 * Se divide por el valor de R0 en aire limpio.
		 */
		r0 = r0 / mySensorMq[device].R0InCleanAir;

		mySensorMq[device].R0 = r0;

		r0 = 0;
	}
}

void MQx_vInit(void)
{
	uint32 bit_resolution;

	if(__u8ValidTable() == (uint8)OK)
	{
		bit_resolution = ADC_u32GetResolution();

		switch(bit_resolution)
		{
		case (uint32)ADC_RESOLUTION_6BITS:
			myMaxAdcVal = (uint16)MAX_6BIT_VALUE;
			break;
		case (uint32)ADC_RESOLUTION_8BITS:
			myMaxAdcVal = (uint16)MAX_8BIT_VALUE;
			break;
		case (uint32)ADC_RESOLUTION_10BITS:
			myMaxAdcVal = (uint16)MAX_10BIT_VALUE;
			break;
		case (uint32)ADC_RESOLUTION_12BITS:
		default:
			myMaxAdcVal = (uint16)MAX_12BIT_VALUE;
			break;
		}

		myResolution = bit_resolution;
		__vCalibration();
	}
}

uint16 MQx_u16GetRawVal(uint16 device)
{
	return (uint16)ADC_u32ReadChannel(mySensorMq[device].SensorId);
}

float MQx_fGetR0Value(uint16 device)
{
	return mySensorMq[device].R0;
}

float MQx_fGetppm(uint16 device)
{
	float relation;
	float ppm;
	float rs = __fResistanceCalculation(device);

	relation = rs/mySensorMq[device].R0;

	ppm = pow(relation, mySensorMq[device].Pot);

	ppm = mySensorMq[device].A * ppm;

	return ppm;
}

void MQX_vGetProperties(uint16 device, MQ_tstSensorProperties* properties)
{
	properties->A = mySensorMq[device].A;
	properties->Pot = mySensorMq[device].Pot;
	properties->R0 = mySensorMq[device].R0;
	properties->R0InCleanAir = mySensorMq[device].R0InCleanAir;
	properties->RL = mySensorMq[device].RL;
	properties->SensorId = mySensorMq[device].SensorId;
}

uint8 MQx_u8GetResolution(uint16 device, uint8 current)
{
	uint8 resolution;

	if((current) && (device < MQx_enTotalMQSensors))
	{
		resolution = ADC_u32GetResolution();
	}
	else
	{
		resolution = myResolution;
	}

	return resolution;
}
