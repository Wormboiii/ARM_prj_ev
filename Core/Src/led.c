/*
 * led.c
 *
 *  Created on: Jun 12, 2025
 *      Author: wonhyeok
 */

#include "led.h"
#include "delay_us.h"

LED_CONTROL led[8] =
{
		{GPIOA, GPIO_PIN_5, 1, 0},
		{GPIOA, GPIO_PIN_6, 1, 0},
		{GPIOA, GPIO_PIN_7, 1, 0},
		{GPIOC, GPIO_PIN_7, 1, 0},
		{GPIOA, GPIO_PIN_9, 1, 0},
		{GPIOA, GPIO_PIN_8, 1, 0},
		{GPIOB, GPIO_PIN_10, 1, 0},
		{GPIOB, GPIO_PIN_4, 1, 0},
};

void ledOn(uint8_t num) {
	for(uint8_t i = 0; i <= num; i++) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
	}
}

void ledOff(uint8_t num) {
	for(uint8_t i = 0; i <= num; i++) {
			HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
		}
}

void ledToggle(uint8_t num) {

}


void ledLS(uint8_t num) {
	for(uint8_t i = 0; i <= num; i++) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
	}
	//	for(int i = num; i >= 0; i--) {
	//		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
	//		HAL_Delay(100);
	//	}
	for(uint8_t i = num; ; i--) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
		delay_us(65000);
		if(i == 0){
			break;
		}
	}
}
void ledRS(uint8_t num) {
	for(uint8_t i = 0; i <= num; i++) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
	}
	for(uint8_t i = 0; i <= num; i++) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
		delay_us(65000);
	}
}

//void ledSRS() {
//	HAL_GPIO_WritePin(led[0].port, led[0].pinNumber, led[0].offState);
//	HAL_GPIO_WritePin(led[1].port, led[1].pinNumber, led[1].offState);
//	HAL_GPIO_WritePin(led[2].port, led[2].pinNumber, led[2].offState);
//	HAL_GPIO_WritePin(led[3].port, led[3].pinNumber, led[3].offState);
//	HAL_GPIO_WritePin(led[4].port, led[4].pinNumber, led[4].offState);
//	HAL_GPIO_WritePin(led[5].port, led[5].pinNumber, led[5].offState);
//	HAL_GPIO_WritePin(led[6].port, led[6].pinNumber, led[6].offState);
//	HAL_GPIO_WritePin(led[7].port, led[7].pinNumber, led[7].onState);
//	delay_us(65000);
//	HAL_GPIO_WritePin(led[7].port, led[7].pinNumber, led[7].offState);
//
//}
//
//void ledSLS() {
//	HAL_GPIO_WritePin(led[0].port, led[0].pinNumber, led[0].offState);
//	HAL_GPIO_WritePin(led[3].port, led[3].pinNumber, led[3].onState);
//	delay_us(65000);
//	HAL_GPIO_WritePin(led[3].port, led[3].pinNumber, led[3].offState);
//	HAL_GPIO_WritePin(led[2].port, led[2].pinNumber, led[2].onState);
//	delay_us(65000);
//	HAL_GPIO_WritePin(led[2].port, led[2].pinNumber, led[2].offState);
//	HAL_GPIO_WritePin(led[1].port, led[1].pinNumber, led[1].onState);
//	delay_us(65000);
//	HAL_GPIO_WritePin(led[1].port, led[1].pinNumber, led[1].offState);
//	HAL_GPIO_WritePin(led[0].port, led[0].pinNumber, led[0].onState);
//	delay_us(65000);
//}

void ledEven(uint8_t num) {

}
void ledOdd(uint8_t num) {

}
