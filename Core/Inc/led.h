/*
 * led.h
 *
 *  Created on: Jun 12, 2025
 *      Author: wonhyeok
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

typedef struct {
	GPIO_TypeDef	*port;
	uint16_t 		pinNumber;
	GPIO_PinState onState;
	GPIO_PinState offState;
}LED_CONTROL;

void ledOn(uint8_t num);
void ledOff(uint8_t num);
void ledToggle(uint8_t num);

void ledLS(uint8_t num);
void ledRS(uint8_t num);
void ledEven(uint8_t num);
void ledOdd(uint8_t num);

//void ledSLS();
//void ledSRS();

#endif /* INC_LED_H_ */
