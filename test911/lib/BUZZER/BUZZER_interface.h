/*
 * BUZZER_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef HAL_BUZZER_INC_BUZZER_INTERFACE_H_
#define HAL_BUZZER_INC_BUZZER_INTERFACE_H_


                  /*************** APIS PROTO TYPES ***************/

void BUZZER_voidInit  (u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);
void BUZZER_voidOn    (u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);
void BUZZER_voidOff   (u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);
void BUZZER_voidToggle(u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);


#endif /* HAL_BUZZER_INC_BUZZER_INTERFACE_H_ */
