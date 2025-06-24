/*
 * fnd.c
 *
 *  Created on: Jun 19, 2025
 *      Author: wonhyeok
 */


#include "fnd.h"

uint8_t Seg_num[] = {														// 숫자 0~9까지를 캐소드 공통(Common Cathode) FND에 나타냈을 때를 16비트로 표시한 배열
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67
    };

uint8_t Seg_alph[] = {														// 알파벳 a~z를 캐소드 공통(Common Annode) FND에 나타냈을 때를 16비트로 표시한 배열
    0x5f, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, 0x76, 0x11, 0x0d, 0x75, 0x38, 0x55, 0x54, 0x5c, 0x73, 0x67, 0x50, 0x2d, 0x78, 0x1c, 0x2a, 0x6a, 0x14, 0x6e, 0x1b
};



void seg_number_CA(int number) {    										// 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
    HAL_GPIO_WritePin(FND_PORT_7, FND_PIN_7, (~Seg_num[number]&0x01));		// 함수를 호출 후 괄호 안에 0~9의 숫자를 넣으면 해당 숫자 FND에 출력.
    HAL_GPIO_WritePin(FND_PORT_6, FND_PIN_6, ((~Seg_num[number]&0x02)>>1));	// 위 배열에서 FND에 해당하는 핀 순서대로 비트를 추출하여 GPIO 출력으로 사용함.
    HAL_GPIO_WritePin(FND_PORT_4, FND_PIN_4, ((~Seg_num[number]&0x04)>>2));
    HAL_GPIO_WritePin(FND_PORT_2, FND_PIN_2, ((~Seg_num[number]&0x08)>>3));
    HAL_GPIO_WritePin(FND_PORT_1, FND_PIN_1, ((~Seg_num[number]&0x10)>>4));
    HAL_GPIO_WritePin(FND_PORT_9, FND_PIN_9, ((~Seg_num[number]&0x20)>>5));
    HAL_GPIO_WritePin(FND_PORT_10, FND_PIN_10, ((~Seg_num[number]&0x40)>>6));
    HAL_GPIO_WritePin(FND_PORT_5, FND_PIN_5, (~Seg_num[number]&0x80)>>7);
}

void seg_number_CC(int number) {   											// 캐소드 공통, 이상하게 나오면 애노드 공통 사용.
	HAL_GPIO_WritePin(FND_PORT_7, FND_PIN_7, (Seg_num[number]&0x01));		// 함수를 호출 후 괄호 안에 0~9의 숫자를 넣으면 해당 숫자 FND에 출력.
	HAL_GPIO_WritePin(FND_PORT_6, FND_PIN_6, ((Seg_num[number]&0x02)>>1));
	HAL_GPIO_WritePin(FND_PORT_4, FND_PIN_4, ((Seg_num[number]&0x04)>>2));
	HAL_GPIO_WritePin(FND_PORT_2, FND_PIN_2, ((Seg_num[number]&0x08)>>3));
	HAL_GPIO_WritePin(FND_PORT_1, FND_PIN_1, ((Seg_num[number]&0x10)>>4));
	HAL_GPIO_WritePin(FND_PORT_9, FND_PIN_9, ((Seg_num[number]&0x20)>>5));
	HAL_GPIO_WritePin(FND_PORT_10, FND_PIN_10, ((Seg_num[number]&0x40)>>6));
	HAL_GPIO_WritePin(FND_PORT_5, FND_PIN_5, (Seg_num[number]&0x80)>>7);

}

void seg_alph_CA(int alph) {        											// 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
	HAL_GPIO_WritePin(FND_PORT_7, FND_PIN_7, (~Seg_alph[alph]&0x01));			// 함수를 호출 후 괄호 안에 숫자를 넣으면 0부터 순서대로 a,b,c... 알파벳이 나옴
	HAL_GPIO_WritePin(FND_PORT_6, FND_PIN_6, ((~Seg_alph[alph]&0x02)>>1));
	HAL_GPIO_WritePin(FND_PORT_4, FND_PIN_4, ((~Seg_alph[alph]&0x04)>>2));
	HAL_GPIO_WritePin(FND_PORT_2, FND_PIN_2, ((~Seg_alph[alph]&0x08)>>3));
	HAL_GPIO_WritePin(FND_PORT_1, FND_PIN_1, ((~Seg_alph[alph]&0x10)>>4));
	HAL_GPIO_WritePin(FND_PORT_9, FND_PIN_9, ((~Seg_alph[alph]&0x20)>>5));
	HAL_GPIO_WritePin(FND_PORT_10, FND_PIN_10, ((~Seg_alph[alph]&0x40)>>6));
	HAL_GPIO_WritePin(FND_PORT_5, FND_PIN_5, (~Seg_alph[alph]&0x80)>>7);
}

void seg_alph_CC(int alph) {        											// 캐소드 공통, 이상하게 나오면 애노드 공통 사용.
	HAL_GPIO_WritePin(FND_PORT_7, FND_PIN_7, (~Seg_alph[alph]&0x01));			// 함수를 호출 후 괄호 안에 숫자를 넣으면 0부터 순서대로 a,b,c... 알파벳이 나옴
	HAL_GPIO_WritePin(FND_PORT_6, FND_PIN_6, ((~Seg_alph[alph]&0x02)>>1));
	HAL_GPIO_WritePin(FND_PORT_4, FND_PIN_4, ((~Seg_alph[alph]&0x04)>>2));
	HAL_GPIO_WritePin(FND_PORT_2, FND_PIN_2, ((~Seg_alph[alph]&0x08)>>3));
	HAL_GPIO_WritePin(FND_PORT_1, FND_PIN_1, ((~Seg_alph[alph]&0x10)>>4));
	HAL_GPIO_WritePin(FND_PORT_9, FND_PIN_9, ((~Seg_alph[alph]&0x20)>>5));
	HAL_GPIO_WritePin(FND_PORT_10, FND_PIN_10, ((~Seg_alph[alph]&0x40)>>6));
	HAL_GPIO_WritePin(FND_PORT_5, FND_PIN_5, (~Seg_alph[alph]&0x80)>>7);
}
