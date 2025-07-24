/*
 * TMR0_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_


#define TMR0_NORMAL_OVER_FLOW			0
#define TMR0_CTC_COMPARE_MATCH			1


               /*************** APIS PROTOTYPES ***************/

void TMR0_voidInit                       (void);
void TMR0_voidStart                      (void);
void TMR0_voidStop                       (void);
void TMR0_voidSetDelay_msCompareMatchMode(u16 copy_u16Delay_ms);
void TMR0_voidSetCallBack                (void(*copy_pFunAction)(void), u8 copy_u8InterruptSource);


#endif /* TMR0_INTERFACE_H_ */
