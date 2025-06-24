/*
 * delay_us.c
 *
 *  Created on: Jun 18, 2025
 *      Author: wonhyeok
 */


#include "delay_us.h"

void delay_us(uint16_t us){
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	while((__HAL_TIM_GET_COUNTER(&htim11)) < us);
}


//void delay_us_secondary(uint16_t us){
//	__HAL_TIM_SET_COUNTER(&htim10, 0);
//	while((__HAL_TIM_GET_COUNTER(&htim10)) < us);
//}
