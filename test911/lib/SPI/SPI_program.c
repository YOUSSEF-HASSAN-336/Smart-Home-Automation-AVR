/*
 * SPI_program.c
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_register.h"


void SPI_voidInit(void)
{
	// Disable SPI interrupt
	CLR_BIT(SPCR_REG, SPIE);
	
	// Select Data Order LSB transmitted first
	SET_BIT(SPCR_REG, DORD);
	
#if SPI_OPERATION_MODE == SPI_MASTER_MODE

    // select Master Mode
    SET_BIT(SPCR_REG, MSTR);
	
	// select CLK Rate = FCPU/128 (125 KHZ)
	SET_BIT(SPCR_REG, SPR0);
	SET_BIT(SPCR_REG, SPR1);
	CLR_BIT(SPSR_REG, SPI2X);

#elif SPI_OPERATION_MODE == SPI_SLAVE_MODE

    // select Slave Mode
    CLR_BIT(SPCR_REG, MSTR);	
	
#endif
	
	// Select CLK Polarity Falling => Rising
	SET_BIT(SPCR_REG, CPOL);
	
	// Select CLK Phase Setup => Sample
	SET_BIT(SPCR_REG, CPHA); 
	
	// Enable SPI
	SET_BIT(SPCR_REG, SPE);
}


void SPI_voidTransceive(u8 copy_u8TxData, u8* copy_pu8RxData)
{
	if(copy_pu8RxData != NULL)
	{
		SPDR_REG = copy_u8TxData;
		
		//Busy Wait on SPI int flag
		while(0 == GET_BIT(SPSR_REG , SPIF));
		
		*copy_pu8RxData = SPDR_REG;
	}
	else
	{
		//return Error State
	}
}