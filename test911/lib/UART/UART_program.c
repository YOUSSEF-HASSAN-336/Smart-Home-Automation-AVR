/*
 * UART_program.c
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "UART_interface.h"
#include "UART_register.h" 


void UART_voidInit(void)
{
	// Set Buad Rate = 9600 (f(osc) = 16MHZ, Double speed off)
	UBRRL_REG = 103;
	CLR_BIT(UCSRA_REG, U2X);
	
	// Disable UART Interrupts
	CLR_BIT(UCSRB_REG, RXCIE);
	CLR_BIT(UCSRB_REG, TXCIE);
	CLR_BIT(UCSRB_REG, UDRIE);
	
	
	u8 local_u8UCSRC_Val = 0;
	
	// writing on UCSRC
	SET_BIT(local_u8UCSRC_Val, URSEL);
	
	// select UART MODE = Asynchronous
	CLR_BIT(local_u8UCSRC_Val, UMSEL);
	
	// configure no parity
	CLR_BIT(local_u8UCSRC_Val, UPM0);
	CLR_BIT(local_u8UCSRC_Val, UPM1);
	
	// configure stop bits = 1
	CLR_BIT(local_u8UCSRC_Val, USBS);
	
	// configure data bits = 8
	SET_BIT(local_u8UCSRC_Val, UCSZ0);
	SET_BIT(local_u8UCSRC_Val, UCSZ1);
	CLR_BIT(UCSRB_REG, UCSZ2);
	
	// configure no polarity 
	CLR_BIT(local_u8UCSRC_Val, UCPOL);
	
	/* Write Configuration Values on UCSRC_REG */
	UCSRC_REG = local_u8UCSRC_Val; // UCSRC_REG = 0b10000110;
	
	// Enable UART Rx
	SET_BIT(UCSRB_REG, RXEN);
	
	// Enable UART Tx
	SET_BIT(UCSRB_REG, TXEN);
}


void UART_voidTxChar(u8 copy_u8TxData)
{
	// Busy Wait on Data Register empty flag
	while(0 == GET_BIT(UCSRA_REG, UDRE));

	UDR_REG = copy_u8TxData;
}


void UART_voidRxChar(u8* copy_pu8RxData)
{
	if(copy_pu8RxData != NULL)
	{
		// Busy Wait on Receive Complete flag
		while(0 == GET_BIT(UCSRA_REG, RXC));
		
		*copy_pu8RxData = UDR_REG;
	}
	else
	{
		//return Error state
	}
}


void UART_voidTxString(u8* copy_pu8TxString)
{
	if(copy_pu8TxString != NULL)
	{
		u8 local_u8Counter = 0;
		while(copy_pu8TxString[local_u8Counter] != '\0')
		{
			UART_voidTxChar(copy_pu8TxString[local_u8Counter]);
			local_u8Counter++;
		}
	}
	else
	{
		//return Error state
	}
}


void UART_voidRxString(u8* copy_pu8RxString)
{
	if(copy_pu8RxString != NULL)
	{
		u8 local_u8Counter = 0;
		
		/* do
		{
			UART_voidRxChar(&copy_pu8RxString[local_u8Counter]);
			local_u8Counter++;
			
		}while(copy_pu8RxString[local_u8Counter-1] != '#');
		copy_pu8RxString[local_u8Counter-1] = '\0'; */
		
		while(1)
		{
			UART_voidRxChar(&copy_pu8RxString[local_u8Counter]);
			
			if(copy_pu8RxString[local_u8Counter] == '#')
			{
				break;
			}
			else
			{
				local_u8Counter++;
			}
		}
		
		copy_pu8RxString[local_u8Counter] = '\0';
	}
	else
	{
		//return Error state
	}
}