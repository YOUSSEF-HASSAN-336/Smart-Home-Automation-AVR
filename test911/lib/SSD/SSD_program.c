/*
 *
 * @file SSD_program.c
 * @author Kareem Hussein
 * @brief main source for SSD functions implementation
 * @date 24/08/2024      
 * @version 1.0
 *
 */


#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "SSD_interface.h"
#include "SSD_config.h"


void SSD_voidInit(void)
{
	/* Configure SSD pins as Output pins */
	DIO_voidSetPinDirection(SSD_D1_PORT, SSD_D1_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_D2_PORT, SSD_D2_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_D3_PORT, SSD_D3_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_D4_PORT, SSD_D4_PIN, DIO_PIN_OUTPUT);

	DIO_voidSetPinDirection(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_OUTPUT);
}


void SSD_voidDisplayOneDigitNumber(u8 copy_u8SSD_id, u8 copy_u8DesiredNumber)
{
	if(copy_u8DesiredNumber <= 9)
	{
		DIO_voidSetPinValue(SSD_D1_PORT, SSD_D1_PIN, (GET_BIT(copy_u8DesiredNumber, 0)));
		DIO_voidSetPinValue(SSD_D2_PORT, SSD_D2_PIN, (GET_BIT(copy_u8DesiredNumber, 1)));
		DIO_voidSetPinValue(SSD_D3_PORT, SSD_D3_PIN, (GET_BIT(copy_u8DesiredNumber, 2)));
		DIO_voidSetPinValue(SSD_D4_PORT, SSD_D4_PIN, (GET_BIT(copy_u8DesiredNumber, 3)));
		
		switch(copy_u8SSD_id)
		{
			case SSD_ONE:
			DIO_voidSetPinValue(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_LOW);
			DIO_voidSetPinValue(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_HIGH);
			break;
			
			case SSD_TWO:
			DIO_voidSetPinValue(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_LOW);
			DIO_voidSetPinValue(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_HIGH);
			break;
			
			case SSD_THREE:
			DIO_voidSetPinValue(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_LOW);
			DIO_voidSetPinValue(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_HIGH);
			break;
			
			case SSD_FOUR:
			DIO_voidSetPinValue(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_LOW);
			DIO_voidSetPinValue(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_HIGH);
			break;
		}
	}
	else
	{
		//return Error State
	}
}


void SSD_voidDisplayMultiDigitNumber(u16 copy_u16DesiredNumber)
{
	if(copy_u16DesiredNumber <= 9999)
	{
		u8 local_u8Tens      = copy_u16DesiredNumber/10;
		u8 local_u8Ones      = copy_u16DesiredNumber%10;
		u8 local_u8Hundreds;
		u8 local_u8Thousands;
		
		DIO_voidSetPinValue(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_HIGH);
		DIO_voidSetPinValue(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_HIGH);
		DIO_voidSetPinValue(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_HIGH);
		DIO_voidSetPinValue(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_HIGH);

		DIO_voidSetPinValue(SSD_D1_PORT, SSD_D1_PIN, GET_BIT(local_u8Ones, 0));
		DIO_voidSetPinValue(SSD_D2_PORT, SSD_D2_PIN, GET_BIT(local_u8Ones, 1));
		DIO_voidSetPinValue(SSD_D3_PORT, SSD_D3_PIN, GET_BIT(local_u8Ones, 2));
		DIO_voidSetPinValue(SSD_D4_PORT, SSD_D4_PIN, GET_BIT(local_u8Ones, 3));
		
		DIO_voidSetPinValue(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_LOW);
		_delay_ms(5);
		DIO_voidSetPinValue(SSD_COM1_PORT, SSD_COM1_PIN, DIO_PIN_HIGH);
		
		DIO_voidSetPinValue(SSD_D1_PORT, SSD_D1_PIN, GET_BIT(local_u8Tens, 0));
		DIO_voidSetPinValue(SSD_D2_PORT, SSD_D2_PIN, GET_BIT(local_u8Tens, 1));
		DIO_voidSetPinValue(SSD_D3_PORT, SSD_D3_PIN, GET_BIT(local_u8Tens, 2));
		DIO_voidSetPinValue(SSD_D4_PORT, SSD_D4_PIN, GET_BIT(local_u8Tens, 3));
		
		DIO_voidSetPinValue(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_LOW);
		_delay_ms(5);
		DIO_voidSetPinValue(SSD_COM2_PORT, SSD_COM2_PIN, DIO_PIN_HIGH);
		
		DIO_voidSetPinValue(SSD_D1_PORT, SSD_D1_PIN, GET_BIT(local_u8Hundreds, 0));
		DIO_voidSetPinValue(SSD_D2_PORT, SSD_D2_PIN, GET_BIT(local_u8Hundreds, 1));
		DIO_voidSetPinValue(SSD_D3_PORT, SSD_D3_PIN, GET_BIT(local_u8Hundreds, 2));
		DIO_voidSetPinValue(SSD_D4_PORT, SSD_D4_PIN, GET_BIT(local_u8Hundreds, 3));
		
		DIO_voidSetPinValue(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_LOW);
		_delay_ms(5);
		DIO_voidSetPinValue(SSD_COM3_PORT, SSD_COM3_PIN, DIO_PIN_HIGH);
		
		DIO_voidSetPinValue(SSD_D1_PORT, SSD_D1_PIN, GET_BIT(local_u8Thousands, 0));
		DIO_voidSetPinValue(SSD_D2_PORT, SSD_D2_PIN, GET_BIT(local_u8Thousands, 1));
		DIO_voidSetPinValue(SSD_D3_PORT, SSD_D3_PIN, GET_BIT(local_u8Thousands, 2));
		DIO_voidSetPinValue(SSD_D4_PORT, SSD_D4_PIN, GET_BIT(local_u8Thousands, 3));
		
		DIO_voidSetPinValue(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_LOW);
		_delay_ms(5);
		DIO_voidSetPinValue(SSD_COM4_PORT, SSD_COM4_PIN, DIO_PIN_HIGH);
	}
	else
	{
		//return Error State
	}
}