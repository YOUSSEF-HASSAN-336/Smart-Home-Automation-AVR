/*
 * TMR0_config.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_


/* Options FOR TMR0 Mode:
1- TMR0_NORMAL_MODE
2- TMR0_CTC_MODE
*/

#define TMR0_MODE							TMR0_CTC_MODE


#define TMR0_PRELOAD_VALUE			        113 
#define TMR0_OVER_FLOW_COUNTER			    977 

#define TMR0_OUTPUT_COMPARE_VALUE			249
#define TMR0_CTC_COUNTER					12000


#endif /* TMR0_CONFIG_H_ */
