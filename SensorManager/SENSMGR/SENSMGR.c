/*
 * @file SENSMGR.c
 *
 *  Created on: Aug 3, 2021
 * @Author: lucky
 */

#include "Prototype.h"

#include "RTC.h"

#include "CFG.h"

#include "OneWire.h"
#include "OneWire_pub.h"

#include "SENSMGR_pub.h"
#include "SENSMGR_priv.h"
#include "SENSMGR.h"

#define DEFAULT_TIME_IN_SEC							10U

static uint32 SENSMGR_au32SampleRate[Total_enSensors];
static uint32 SENSMGR_au32PrevTimeInSec[Total_enSensors];
static uint16 SENSMGR_au16SensorsId[Total_enSensors] = ID_TABLE;
static uint8 SENSMGR_au8SensInit[Total_enSensors];
static SENSMGR_tstptr2functions SENSMGR_stFunctios[Total_enSensors] = POINTERS_TO_FUNC_TABLE;

#ifdef BASIC_REQUEST
static void __vBasicReques(uint16 u16SensorId, SENSMGR_tstMessageBody* pstLidarMsg)
{
	pstLidarMsg->u16SensorValue = SENSMGR_stFunctios[u16SensorId].p2fnReqRawVal(SENSMGR_au16SensorsId[u16SensorId]);
	pstLidarMsg->u32ADCResolution = SENSMGR_stFunctios[u16SensorId].p2fnReqRes(SENSMGR_au16SensorsId[u16SensorId], False);
}
#endif

#ifdef COMPLEX_REQUEST
static void __vComplexReques(uint16 u16SensorId, SENSMGR_tstMessageBody* pstLidarMsg)
{
	pstLidarMsg->fConvertedValue = SENSMGR_stFunctios[u16SensorId].p2fnGetProcessedVal(SENSMGR_au16SensorsId[u16SensorId]);
	pstLidarMsg->u16SensorValue = SENSMGR_stFunctios[u16SensorId].p2fnReqRawVal(SENSMGR_au16SensorsId[u16SensorId]);
	pstLidarMsg->u32ADCResolution = SENSMGR_stFunctios[u16SensorId].p2fnReqRes(SENSMGR_au16SensorsId[u16SensorId], False);
	pstLidarMsg->u16SubId = SENSMGR_au16SensorsId[u16SensorId];
}
#endif

static uint32 __u32UpdateFreq(SENSMGR_SamplingRate* pstSampleRate, uint32* pu32NewSampleRate)
{
	uint32 u32State = N_OK;
	uint32 u32Period = 0U;

	u32Period = Sampling_in_sec(pstSampleRate->u8Days, pstSampleRate->u8Hrs, pstSampleRate->u8Mins, pstSampleRate->u8Secs);

	if((u32Period <= (uint32)LONGEST_PERIOD) && (u32Period >= (uint32)SHORTEST_PERIOD))
	{
		u32State = OK;
		*pu32NewSampleRate = u32Period;
	}

	return u32State;
}

static uint32 __u32GetTimeDiff(uint16 u16SensorId, RTC_tstTimeFormat* stTime, uint32* pu32CurrTimeInSec)
{
	uint32 u32DeltaTime = 0U;

	*pu32CurrTimeInSec = Time2Sec(stTime->u8Hr, stTime->u8Min, stTime->u8Sec);

	if(*pu32CurrTimeInSec < SENSMGR_au32PrevTimeInSec[u16SensorId])
	{
		u32DeltaTime = (SECS_IN_ONE_DAY - 1U) - SENSMGR_au32PrevTimeInSec[u16SensorId];
		u32DeltaTime += *pu32CurrTimeInSec;
	}
	else
	{
		u32DeltaTime = *pu32CurrTimeInSec - SENSMGR_au32PrevTimeInSec[u16SensorId];
	}

	return u32DeltaTime;
}

static void __CheckInitSampleRate(uint16 u16SensorId)
{
	uint32 u32NewSampleRate;
	uint32 u32State = OK;
	RTC_CalendarFormat stPresCal;
	SENSMGR_SamplingRate stInitSampleRate[Total_enSensors] = INIT_SAMPLERATE_TABLE;

	(void)RTC_u32GetCalendarInfo(&stPresCal);
	SENSMGR_au32PrevTimeInSec[u16SensorId] =
			Time2Sec(stPresCal.stTime.u8Hr, stPresCal.stTime.u8Min, stPresCal.stTime.u8Sec);

	u32State = __u32UpdateFreq(&stInitSampleRate[u16SensorId], &u32NewSampleRate);

	if(u32State == OK)
	{
		SENSMGR_au32SampleRate[u16SensorId] = u32NewSampleRate;
	}
	else
	{
		SENSMGR_au32SampleRate[u16SensorId] = (uint32)DEFAULT_TIME_IN_SEC;
	}

	SENSMGR_au8SensInit[u16SensorId] = (uint8)True;

}

uint32 SENSMGR_u32UpdateSampleRate(uint16 u16SensorId, SENSMGR_SamplingRate* pstNewSampleRate)
{
	uint32 u32State = N_OK;
	uint32 u32NewSampleRate = 0U;
	if(u16SensorId < (uint16)Total_enSensors)
	{
		u32State = __u32UpdateFreq(pstNewSampleRate, &u32NewSampleRate);
		if(u32State == OK)
			SENSMGR_au32SampleRate[u16SensorId] = u32NewSampleRate;
	}
	return u32State;
}

uint32 SENSMGR_u32ReadSensor(uint16 u16SensorId, SENSMGR_tstMessageBody* pstLidarMsg)
{
	RTC_CalendarFormat stPresCal;
	uint32 u32CurrTimeInSec = 0U;
	uint32 u32DeltaTime = 0U;
	uint32 u32RtrnState = N_OK;

	if((u16SensorId >= (uint16)Total_enSensors) || SENSMGR_au8SensInit[u16SensorId] != (uint8)True)
		return u32RtrnState;

	RTC_u32GetCalendarInfo(&stPresCal);

	u32DeltaTime = __u32GetTimeDiff(u16SensorId, &stPresCal.stTime, &u32CurrTimeInSec);

	if(u32DeltaTime >= SENSMGR_au32SampleRate[u16SensorId])
	{
		/*Leer el sensor. */
		SENSMGR_au32PrevTimeInSec[u16SensorId] = u32CurrTimeInSec;

#ifdef BASIC_REQUEST
		__vBasicReques(u16SensorId, pstLidarMsg);
#endif
#ifdef COMPLEX_REQUEST
		__vComplexReques(u16SensorId, pstLidarMsg);
#endif
		pstLidarMsg->stCal = stPresCal;
		u32RtrnState = (uint32)OK;
	}

	return u32RtrnState;
}

void SENSMGR_vInitAllSensors(GPIO_TypeDef* GPIOx, uint16 pin)
{
	uint16 i;
	uint16 LimitIdValue[Total_enSensors] = MAX_ID_TABLE;
	uint8 status = (uint8)OK;

	/*
	 * Se comprueba que todos los Id's de los sensores
	 * esten dentro de los limites de cada uno de sus
	 * respectivos componentes.
	 */
	for(i = 0; i < Total_enSensors; i++)
	{
		if(SENSMGR_au16SensorsId[i] >= LimitIdValue[i])
		{
			status = (uint8)N_OK;
			break;
		}
		__CheckInitSampleRate(i);
	}

	if(status == (uint8)OK)
	{
		/*
		 * Se inicializan todos los componentes correspondientes.
		 */
		OneWire_vInit(GPIOx, pin);
		Dallas_vBegin();
		MQx_vInit();
	}
}
