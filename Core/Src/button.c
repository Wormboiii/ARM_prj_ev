/*
 * button.c
 *
 *  Created on: Jun 16, 2025
 *      Author: wonhyeok
 */

#include "button.h"

BUTTON_CONTROL button[3] = {
		{GPIOC, GPIO_PIN_13, 0},
		{GPIOC, GPIO_PIN_14, 0},
		{GPIOC, GPIO_PIN_15, 0}

};


//각 배열별로 디바운스 코드 입력
bool buttonGetPressed(uint8_t num) {
	static uint32_t prevTime[3] = {0xffffffff};

	if(prevTime[num] == 0xffffffff) {
		prevTime[num] = HAL_GetTick();
	}

	bool ret = false;

	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
		uint32_t currTime = HAL_GetTick();

		if(currTime - prevTime[num] > 30) {
			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
				ret = true;
			}
			prevTime[num] = currTime;
		}
	}
	return ret;
}



// delay 함수 사용해서 blocking code라 지양해야 하는 방법.
//bool buttongetPressed(uint8_t num) {
//	bool ret = false;
//
//	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
//		HAL_Delay(30);
//		if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
//			ret = true;
//		}
//	}
//	return ret;
//}



// 최초 1회 동작때는 디바운싱 안됨
//bool buttonGetPressed(uint8_t num) {
//	static uint32_t prevTime = 0;
//
//	bool ret = false;
//
//	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
//		uint32_t currTime = HAL_GetTick();
//
//		if(currTime - prevTime > 30) {
//			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
//				ret = true;
//			}
//			prevTime = currTime;
//		}
//	}
//	return ret;
//}



// 처음부터 디바운스 되게
//bool buttonGetPressed(uint8_t num) {
//	static uint32_t prevTime = 0xffffffff;
//
//	if(prevtime == 0xffffffff) {
//		prevTime = HAL_GetTick();
//	}
//
//	bool ret = false;
//
//	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
//		uint32_t currTime = HAL_GetTick();
//
//		if(currTime - prevTime > 30) {
//			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
//				ret = true;
//			}
//			prevTime = currTime;
//		}
//	}
//	return ret;
//}
