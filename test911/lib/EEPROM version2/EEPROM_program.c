/*
 * EEPROM_program.c
 *
 * Created: 3/24/2024 11:58:55 AM
 *  Author: Kareem Hussein
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TWI_interface.h"

/* HAL */
#include "EEPROM_interface.h"
#include "EEPROM_private.h"


void EEPROM_voidInit(void)
{
	TWI_voidInitMaster();
}


void EEPROM_voidWriteByte(u16 copy_u16WordAddress, u8 copy_u8Data)
{
	u8 local_u8DeviceAddress = (copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_voidSendStartCondition();
	
	// Send device address with write operation
	TWI_voidSendSlaveAddWithWrite(local_u8DeviceAddress);
	
	// Send word address
	TWI_voidTransmitMasterDataByte((u8)copy_u16WordAddress);
	
	// Send byte data
	TWI_voidTransmitMasterDataByte(copy_u8Data);
	
	// Send stop condition
	TWI_voidSendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);
}


void EEPROM_voidReadByte(u16 copy_u16WordAddress, u8* copy_pu8Data)
{
	if(copy_pu8Data!=NULL)
	{
		u8 local_u8DeviceAddress = (copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;
	
	    // Send start condition
	    TWI_voidSendStartCondition();
	    
		// Send device address with write operation
	    TWI_voidSendSlaveAddWithWrite(local_u8DeviceAddress);
	    
		// Send word address
	    TWI_voidTransmitMasterDataByte((u8)copy_u16WordAddress);
		
		// Send repeated start condition in order to switch i2c operation
		TWI_voidSendRepeatedStartCondition();
		
		// Send slave address with read operation
		TWI_voidSendSlaveAddWithRead(local_u8DeviceAddress);
		
		// Read byte data and respond with not ACK
		TWI_voidReceiveMasterDataByteWithNack(copy_pu8Data);
		
		// Send stop condition
		TWI_voidSendStopCondition();
		
		// Self-timed Write Cycle delay
	    _delay_ms(5);
	}
	else
	{
		//return Error State
	}
}


void EEPROM_voidWritePage(u16 copy_u16BaseAddress, u8* copy_pu8Data, u8 copy_u8DataSize)
{
	if((copy_pu8Data!=NULL)&&(copy_u8DataSize<=16))
	{
		u8 local_u8DeviceAddress = (copy_u16BaseAddress>>8)|EEPROM_FIXED_ADDRESS;
	
	    // Send start condition
	    TWI_voidSendStartCondition();
	    
	    // Send device address with write operation
	    TWI_voidSendSlaveAddWithWrite(local_u8DeviceAddress);
	    
	    // Send word address
	    TWI_voidTransmitMasterDataByte((u8)copy_u16BaseAddress);
		
		
		u8 local_u8DataCounter;
		for(local_u8DataCounter=0;local_u8DataCounter<copy_u8DataSize;local_u8DataCounter++)
		{
			// Send byte data
	        TWI_voidTransmitMasterDataByte(copy_pu8Data[local_u8DataCounter]);
		}
		
		// Send stop condition
		TWI_voidSendStopCondition();
		
		// Self-timed Write Cycle delay
	    _delay_ms(5);
	}
	else
	{
		//return Error State
	}
}


void EEPROM_voidReadPage(u16 copy_u16BaseAddress, u8* copy_pu8Data, u8 copy_u8DataSize)
{
	if((copy_pu8Data!=NULL)&&(copy_u8DataSize<=16))
	{
		u8 local_u8DeviceAddress = (copy_u16BaseAddress>>8)|EEPROM_FIXED_ADDRESS;
	
	    // Send start condition
	    TWI_voidSendStartCondition();
	    
		// Send device address with write operation
	    TWI_voidSendSlaveAddWithWrite(local_u8DeviceAddress);
	    
		// Send word address
	    TWI_voidTransmitMasterDataByte((u8)copy_u16BaseAddress);
		
		// Send repeated start condition in order to switch i2c operation
		TWI_voidSendRepeatedStartCondition();
		
		// Send slave address with read operation
		TWI_voidSendSlaveAddWithRead(local_u8DeviceAddress);
		
		u8 local_u8DataCounter;
		for(local_u8DataCounter=0;local_u8DataCounter<(copy_u8DataSize-1);local_u8DataCounter++)
		{
			// Read  byte data
			TWI_voidReceiveMasterDataByteWithAck(&copy_pu8Data[local_u8DataCounter]);
		}
		
		// Read last byte data
		TWI_voidReceiveMasterDataByteWithNack(&copy_pu8Data[local_u8DataCounter]);
		
		// Send stop condition
		TWI_voidSendStopCondition();
		
		// Self-timed Write Cycle delay
	    _delay_ms(5);
	}
	else
	{
		//return Error State
	}
}