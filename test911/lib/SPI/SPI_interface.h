/*
 * SPI_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


#define SPI_MASTER_MODE			1
#define SPI_SLAVE_MODE			2

 
void SPI_voidInit      (void);
void SPI_voidTransceive(u8 copy_u8TxData, u8* copy_pu8RxData);


#endif /* SPI_INTERFACE_H_ */
