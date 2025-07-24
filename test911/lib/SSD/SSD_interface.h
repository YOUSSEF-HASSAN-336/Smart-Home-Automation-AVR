/*
 *
 * @file SSD_interface.h
 * @author Kareem Hussein
 * @brief main header file contain public functions prototypes, types and macros for SSD
 * @date 24/08/2024      
 * @version 1.0
 *
 */

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_


#define SSD_ONE			0
#define SSD_TWO			1
#define SSD_THREE		2
#define SSD_FOUR	    3

              					/*************** APIS PROTO TYPES ***************/
								
void SSD_voidInit(void);
void SSD_voidDisplayOneDigitNumber(u8 copy_u8SSD_id, u8 copy_u8DesiredNumber);
void SSD_voidDisplayMultiDigitNumber(u16 copy_u16DesiredNumber);


#endif /* SSD_INTERFACE_H_ */
