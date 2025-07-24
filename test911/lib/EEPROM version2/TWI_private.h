/*
 * TWI_private.h
 *
 * Created: 3/15/2024 11:07:40 PM
 *  Author: Kareem Hussein
 */ 


#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_


#define TWI_STATUS_VALUE				 (TWSR_REG&0xF8)

#define TWI_START_CONDITION_ACK          0x08
#define TWI_REP_START_CONDITION_ACK      0x10
#define TWI_SLAVE_ADDRESS_WRITE_ACK      0x18
#define TWI_SLAVE_ADDRESS_READ_ACK       0x40
#define TWI_MASTER_DATA_TRANSMIT_ACK     0x28
#define TWI_MASTER_DATA_RECIEVE_ACK      0x50
#define TWI_MASTER_DATA_RECIEVE_NACK     0x58


#endif /* TWI_PRIVATE_H_ */