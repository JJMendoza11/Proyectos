/*
 * @file OneWire.c
 *
 *  Created on: Jul 26, 2021
 * @Author: lucky
 */

#include "main.h"

#include "Prototype.h"

#include "Timer.h"

#include "OneWire.h"
#include "OneWire_priv.h"
#include "OneWire_pub.h"

#define CFG_IO_PIN						3U
#define CFG_IO_OUT						1U
#define TOTAL_PINS						32U
#define LOW								GPIO_PIN_RESET
#define HIGH							GPIO_PIN_SET
#define Clear_bit(reg, bit, loc)		(reg &= ~(bit << loc))
#define Set_bit(reg, bit, loc)			(reg |= (bit << loc))
#define Set_input_mode					Clear_bit(gpio->MODER, CFG_IO_PIN, myPinBitMask)
#define Set_output_mode					Set_bit(gpio->MODER, CFG_IO_OUT, myPinBitMask)
#define Get_moder_loc(bit)				(bit * 2)

static GPIO_TypeDef* gpio;
static uint16 myPin;
static uint8 myPinBitMask;
static uint8 myROM[ROM_SIZE_BYTES];
static uint8 mySearchEnd = False;
static uint8 myLastConflictedBitLoc;

static uint8 __u8SearchAlgorithm(uint8* lastZero)
{
	uint8 bit_val    = 0U;
	uint8 bit_comp   = 0U;
	uint8 eco_resp   = 0U;
	uint8 bit_cnt	 = 0U;
	uint8 byte_pos	 = 0U;
	uint8 byte_mask  = 1U;
	uint8 search_result = (uint8)OK;


	/* Si se obtuvo el pulso de respuesta empezar con la busqueda de
	 * dispositivos.
	 */
	if(OneWire_u8Reset() == SENS_PRESENT)
	{
		/* Se escribe el comando para la busqueda. */
		OneWire_vWrite(SEARCH_ROM_CMD);

		do
		{
			bit_val = OneWire_u8ReadBit();
			bit_comp = OneWire_u8ReadBit();

			switch(bit_val + bit_comp)
			{
			case NO_ID_CONFLICT:
					eco_resp = bit_val;
				break;
			case ID_CONFLICT:
				/* Si el bit en conflicto no es el ultimo que se registro.
				 * Entonces toma el previamente guardado. Si es el úlitmo,
				 * entonces se evalua si es la primera o segunda vez que
				 * pasa por este punto.
				 */
				if(bit_cnt < myLastConflictedBitLoc)
				{
					eco_resp = myROM[byte_pos] & byte_mask;
				}
				else
				{
					/* Si es un bit nuevo en conflicto se escribe 0,
					 * si es la segunda vez que pasa por aqui se
					 * escribe un uno.
					 */
					eco_resp = (bit_cnt == myLastConflictedBitLoc);
				}

				/*Si el eco es un cero se guarda su posición, esto para
				 * poder regresar en el 'arbol' de forma correcta.
				 */
				if(eco_resp == LOW)
				{
					*lastZero = bit_cnt;
				}

				break;
			case NO_DIVECE_CONNECTED:
			default:
				search_result = (uint8)N_OK;
				break;
			}

			/* Se guarda el bit */
			if(eco_resp == HIGH)
			{
				myROM[byte_pos] |= byte_mask;
			}
			else
			{
				myROM[byte_pos] &= ~byte_mask;
			}

			/* Se envía el eco */
			OneWire_vWriteBit(eco_resp);

			/* Se actualizan las variables correspondientes */
			byte_mask <<= 1;
			bit_cnt++;

			/*Se resetea si es necesario. */
			if(byte_mask == False)
			{
				byte_mask = 1;
				byte_pos++;
			}


		}while((byte_pos < ROM_SIZE_BYTES) && (search_result == OK));
	}

		if(bit_cnt != ROM_SIZE_BITS)
		{
			search_result = N_OK;
		}

		return search_result;
}

static void __vFindBitMask(uint16 pin)
{
	uint8 i;
	uint16 bit_mask;
	for(i = 0; i < TOTAL_PINS; i++)
	{
		bit_mask = (uint16)(1 << i);
		if(bit_mask == pin)
		{
			/* Se multiplica por 2 por la configuración del registro
			 * MODER. Para más información ver el capi 9.4.1 del
			 * Ref Manual.
			 */
			myPinBitMask = Get_moder_loc(i);
			break;
		}
	}
}

void OneWire_vInit(GPIO_TypeDef* GPIOx, uint16 pin)
{
	gpio = GPIOx;
	myPin = pin;
	__vFindBitMask(pin);
}

uint8 OneWire_u8Reset(void)
{
	uint8 Resp = OK;
	uint8 Retries = 125;

	Set_input_mode;
	do
	{
		if(--Retries == 0)
		{
			Resp = N_OK;
			break;
		}
		Timer_vDelayUs(5);
	}while(HAL_GPIO_ReadPin(gpio, myPin) == LOW);

	if(Resp == OK)
	{
		HAL_GPIO_WritePin(gpio, myPin, LOW);
		Set_output_mode;
		Timer_vDelayUs(RESET_PULSE_T);
		Set_input_mode;
		Timer_vDelayUs(PRESENCE_PULSE_T);
		Resp = HAL_GPIO_ReadPin(gpio, myPin);
		Timer_vDelayUs(IDLE_PULSE_T);
	}

	return Resp;
}

void OneWire_vWriteBit(uint8 bit)
{
	if(bit == HIGH)
	{
		HAL_GPIO_WritePin(gpio, myPin, LOW);
		Set_output_mode;
		Timer_vDelayUs(WRITE_HIGH_T);
		HAL_GPIO_WritePin(gpio, myPin, HIGH);
		Timer_vDelayUs(IDLE_HIGH_T);
	}
	else
	{
		HAL_GPIO_WritePin(gpio, myPin, LOW);
		Set_output_mode;
		Timer_vDelayUs(WRITE_LOW_T);
		HAL_GPIO_WritePin(gpio, myPin, HIGH);
		Timer_vDelayUs(IDLE_LOW_T);
	}
}

uint8 OneWire_u8ReadBit(void)
{
	uint8 bit;

	Set_output_mode;
	HAL_GPIO_WritePin(gpio, myPin, LOW);
	Timer_vDelayUs(READ_TGR_T);
	Set_input_mode;
	Timer_vDelayUs(READ_SAMPLE_WAIT);
	bit = HAL_GPIO_ReadPin(gpio, myPin);
	Timer_vDelayUs(READ_IDLE_T);

	return bit;
}

void OneWire_vWrite(uint8 byte)
{
	uint8 bit_mask;
	for(bit_mask = 1; bit_mask; bit_mask <<= 1)
	{
		OneWire_vWriteBit((bit_mask & byte) ? HIGH: LOW);
	}

	Set_input_mode;
	HAL_GPIO_WritePin(gpio, myPin, LOW);
}

void OneWire_vWriteBytes(uint8* bytes, uint8 len)
{
	uint8 index;

	for(index = 0; index < len; index++)
	{
		OneWire_vWrite(bytes[index]);
	}
}

uint8 OneWire_u8Read(void)
{
	uint8 bit_mask;
	uint8 byte = 0U;

	for(bit_mask = 1; bit_mask; bit_mask <<= 1)
	{
		if(OneWire_u8ReadBit() == HIGH)
		{
			byte |= bit_mask;
		}
	}

	return byte;
}

void OneWire_vReadBytes(uint8* buf, uint8 bufLen)
{
	uint8 i;
	for(i = 0; i < bufLen; i++)
	{
		buf[i] = OneWire_u8Read();
	}
}

void OneWire_vSelectSens(uint8* rom)
{
	uint8 i;

	OneWire_vWrite(MATCH_ROM_CMD);

	for(i = 0; i < ROM_SIZE_BYTES; i++)
	{
		OneWire_vWrite(rom[i]);
	}
}

void OneWire_vSkip(void)
{
	OneWire_vWrite(SKIP_ROM_CMD);
}

void OneWire_vResetSearch(void)
{
	uint8 i;
	mySearchEnd = False;
	myLastConflictedBitLoc = False;

	for(i = 0; i < ROM_SIZE_BYTES; i++)
	{
		myROM[i] = 0U;
	}
}
uint8 OneWire_vSearch(uint8* newAdrr)
{
	uint8 lastZero = 0U;
	uint8 status = N_OK;
	uint8 i;

	if(mySearchEnd == False)
	{
		status = __u8SearchAlgorithm(&lastZero);
		if(status == OK)
		{
			myLastConflictedBitLoc = lastZero;
			if(myLastConflictedBitLoc == 0)
			{
				mySearchEnd = True;
			}

			for(i = 0; i < ROM_SIZE_BYTES; i++)
			{
				newAdrr[i] = myROM[i];
			}
		}
		else
		{
			OneWire_vResetSearch();
		}
	}

	return status;
}

uint8 OneWire_u8CRC8(uint8* buf, uint8 len)
{
	uint8_t crc = 0;

	while (len--) {
		uint8_t inbyte = *buf++;
		for (uint8_t i = 8; i; i--) {
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix) crc ^= 0x8C;
			inbyte >>= 1;
		}
	}
	return crc;
}
