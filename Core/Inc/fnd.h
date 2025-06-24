/*
 * fnd.h
 *
 *  Created on: Jun 19, 2025
 *      Author: wonhyeok
 */

#ifndef INC_FND_H_
#define INC_FND_H_

#include "main.h"

#define FND_PORT_7	GPIOC				// FND와 MCU 연결한 핀 순서대로 나열함.
#define FND_PIN_7 	GPIO_PIN_9			// 본인 결선 순서대로 GPIOx, GPIO_PIN_x 수정 후 사용.

#define FND_PORT_6	GPIOB
#define FND_PIN_6	GPIO_PIN_9

#define FND_PORT_4	GPIOB
#define FND_PIN_4	GPIO_PIN_5

#define FND_PORT_2	GPIOB
#define FND_PIN_2	GPIO_PIN_3

#define FND_PORT_1	GPIOA
#define FND_PIN_1	GPIO_PIN_10

#define FND_PORT_9	GPIOA
#define FND_PIN_9	GPIO_PIN_12

#define FND_PORT_10	GPIOA
#define FND_PIN_10	GPIO_PIN_11

#define FND_PORT_5	GPIOB
#define FND_PIN_5	GPIO_PIN_12

void seg_number_CA(int number); // 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
void seg_number_CC(int number); // 캐소드 공통, 이상하게 나오면 애노드 공통 사용.
void seg_alph_CA(int alph);     // 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
void seg_alph_CC(int alph);     // 캐소드 공통, 이상하게 나오면 애노드 공통 사용.


#endif /* INC_FND_H_ */
