/*
 * SPI_register.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_


                   /* SPI REGISTERS*/

// SPI Control Register
#define SPCR_REG            (*(volatile u8*)0x2D)
#define SPR0                0
#define SPR1                1
#define CPHA                2
#define CPOL                3
#define MSTR                4
#define DORD                5
#define SPE                 6
#define SPIE                7


// SPI Status Register
#define SPSR_REG             (*(volatile u8*)0x2E)
#define SPI2X                0
#define WCOL                 6
#define SPIF                 7


// SPI Data Register
#define SPDR_REG             (*(volatile u8*)0x2F)


#endif /* SPI_REGISTER_H_ */
