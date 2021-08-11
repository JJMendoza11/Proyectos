/*
 * @file Dallas.c
 *
 *  Created on: Jul 27, 2021
 * @Author: lucky
 */


#include "Prototype.h"

#include "OneWire.h"
#include "Timer.h"

#include "Dallas_priv.h"
#include "Dallas_pub.h"
#include "Dallas.h"

#define ROM_WITHOUT_CRC						(ROM_SIZE_BYTES - 1U)
#define SPAD_WITHOUT_CRC					(SCRATCHPAD_LEN - 1U)
#define TWOs_COMPLEMENT(x)					(((x ^ 0xFFFF) + 1) * -1)
#define IS_SIGNED(x)						((uint16)x & (uint16)0x8000)

typedef struct
{
	DeviceAddess Adrss;
	uint8 Resolution;
}Dallas_tstTempSensor;


static Dallas_tstTempSensor mySensors[TOTAL_DEVICES_EXP];
static uint8 myTotalDevices;
static uint8 myAutoSave;

uint8 __u8SaveScratch(uint16 device)
{
	uint8 status = N_OK;

	status = OneWire_u8Reset();
	if(status == SENS_PRESENT)
	{
		/* Se envia el comando de ROM con la dirección en especifico. */
		OneWire_vSelectSens(mySensors[device].Adrss);

		/* Se envia el comando de la RAM para guardar el scratch. */
		OneWire_vWrite(SAVE_SCRATCHPAD_CMD);

		/* Se espera a que el sensor guarde los datos en la EPROM. El tiempo
		 * para esta operación es entre 2ms y 10ms.
		 */
		Timer_vDelayUs(SAVE_TIME);

		status = OneWire_u8Reset();
	}

	return status;
}

uint8 __u8ValidAddress(uint16 devices)
{
	uint8 CalCRC;
	CalCRC = OneWire_u8CRC8(mySensors[devices].Adrss, ROM_WITHOUT_CRC);

	return !(CalCRC == mySensors[devices].Adrss[7]);
}

uint8 __u8ReadScratchPad(uint16 device, Dallas_tstScratchPad* Scratchpad)
{
	uint8 i;
	uint8 u8Status = N_OK;
	uint8* buf;

	u8Status = OneWire_u8Reset();
	if(u8Status == SENS_PRESENT)
	{
		/* Se envia el comando de ROM con la dirección en especifico. */
		OneWire_vSelectSens(mySensors[device].Adrss);

		/* Se envia el comando de la RAM para leer el scratch. */
		OneWire_vWrite(READ_SCRATCHPAD_CMD);

		buf = (uint8*)Scratchpad;
		for(i = 0; i < SCRATCHPAD_LEN; i++)
		{
			buf[i] = OneWire_u8Read();
		}

		u8Status = OneWire_u8Reset();

		/* Se comprueba que el mensaje sea valido. */
		if(u8Status == SENS_PRESENT)
		{
			u8Status = (Scratchpad->Crc == OneWire_u8CRC8(buf, SPAD_WITHOUT_CRC) ? OK: N_OK);
		}
	}

	return u8Status;
}

uint8 __u8WriteScratchPad(uint16 device, Dallas_tstScratchPad* Scratchpad)
{
	uint8 status = N_OK;

	status = OneWire_u8Reset();
	if(status == SENS_PRESENT)
	{
		/* Se envia el comando de ROM con la dirección en especifico. */
		OneWire_vSelectSens(mySensors[device].Adrss);

		/* Se envia el comando de la RAM para escribir el scratch. */
		OneWire_vWrite(WRITE_SCRATCHPAD_CMD);

		/* Se guardan los unicos registros que son de escritura en el
		 * sensor.
		 * */
		OneWire_vWrite(Scratchpad->AlarmTh);
		OneWire_vWrite(Scratchpad->AlarmTl);
		OneWire_vWrite(Scratchpad->Res);

		if(myAutoSave)
		{
			status = __u8SaveScratch(device);
		}
		else
		{
			status = OneWire_u8Reset();
		}
	}

	return status;
}

uint8 __u8GetResolution(uint8 device)
{
	uint8 resolution;
	Dallas_tstScratchPad Scratchpad;

	if(__u8ReadScratchPad(device, &Scratchpad) == OK)
	{
		switch(Scratchpad.Res)
		{
		case TEMP_9_BIT:
			resolution = 9;
			break;
		case TEMP_10_BIT:
			resolution = 10;
			break;
		case TEMP_11_BIT:
			resolution = 11;
			break;
		case TEMP_12_BIT:
			resolution = 12;
			break;
		default:
			resolution = N_OK;
			break;
		}
	}

	return resolution;
}

uint8 __u8IsConversionComplete(void)
{
	uint8 bit = OneWire_u8ReadBit();

	return (uint8)(bit == (uint8)CONVERSION_HAS_END);
}

uint8  __u8WaitForConversion(void)
{
	uint32 Counter = 0U;
	uint8 state = CONVERSION_IS_RUNNING;
	while((Counter < MAX_CONVERSION_TIMEOUT) && (state != CONVERSION_HAS_END))
	{
		Timer_vDelayUs((uint32)WAIT_FOR_1MS);

		state = __u8IsConversionComplete();

		Counter++;
	}

	if((Counter < MAX_CONVERSION_TIMEOUT) && (state == CONVERSION_HAS_END))
	{
		state = OK;
	}
	else
	{
		state = N_OK;
	}

	return state;
}

void Dallas_vBegin(void)
{
	uint8 devices = 0;

	myAutoSave = True;

	while((devices < TOTAL_DEVICES_EXP) && (!OneWire_vSearch(mySensors[devices].Adrss)))
	{
		if(__u8ValidAddress(devices) == OK)
		{
			mySensors[devices].Resolution = __u8GetResolution(devices);
			devices++;
		}
	}

	myTotalDevices = devices;
}

uint8 Dallas_u8GetResolution(uint16 device, uint8 current)
{
	uint8 resolution;

	if(current == True)
	{
		mySensors[device].Resolution = __u8GetResolution(device);
	}

	resolution = mySensors[device].Resolution;

	return resolution;
}

uint8 Dallas_u8SetResolution(uint16 device, uint8 resolution)
{
	Dallas_tstScratchPad Scratchpad;
	uint8 new_res;
	uint8 status = OK;

	switch(resolution)
	{
	case 9:
		new_res = (uint8)TEMP_9_BIT;
		break;
	case 10:
		new_res = (uint8)TEMP_10_BIT;
		break;
	case 11:
		new_res = (uint8)TEMP_11_BIT;
		break;
	case 12:
		new_res = (uint8)TEMP_12_BIT;
		break;
	default:
		status = (uint8)N_OK;
		break;
	}

	if(status == OK)
	{
		status = __u8ReadScratchPad(device, &Scratchpad);
		if(status == OK && Scratchpad.Res != new_res)
		{
			Scratchpad.Res = new_res;
			status = __u8WriteScratchPad(device, &Scratchpad);
			if(status == OK)
			{
				mySensors[device].Resolution = resolution;
			}
		}
	}

	return status;
}

void Dallas_vSetAutoSave(uint8 state)
{
	myAutoSave = state;
}


uint8 Dallas_u8RequestTemp(uint16 device)
{
	uint8 state = OK;

	state = OneWire_u8Reset();

	if(state == (uint8)OK)
	{
		OneWire_vSelectSens(mySensors[device].Adrss);
		OneWire_vWrite(CONVERT_TEMP_CMD);
		state = __u8WaitForConversion();
	}

	return state;
}

uint16 Dallas_u16GetRawVal(uint16 device)
{
	uint16 raw_temp = (uint16)INVALID_TEMP;
	Dallas_tstScratchPad Scratchpad;

	Dallas_u8RequestTemp(device);
	if(__u8ReadScratchPad(device, &Scratchpad) == (uint8)OK)
	{
		raw_temp = (Scratchpad.TempMsb << 8) + Scratchpad.TempLsb;
	}
	return raw_temp;
}

float Dallas_fGetTempC(uint16 device)
{
	float temp;
	uint16 raw_val;

	raw_val = Dallas_u16GetRawVal(device);

	if(raw_val != (uint16)INVALID_TEMP)
	{
		if(IS_SIGNED(raw_val))
		{
			raw_val = TWOs_COMPLEMENT(raw_val);
		}

		temp = raw_val / 16.0;
	}

	return temp;
}
