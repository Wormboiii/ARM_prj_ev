/*
 * step.h
 *
 *  Created on: Jun 18, 2025
 *      Author: wonhyeok
 */

#ifndef INC_STEP_H_
#define INC_STEP_H_

#include "main.h"

//#define STEPS_PER_REV	4096
//#define DIR_CW			0	// 시계방향
//#define DIR_CCW			1	// 반시계방향
//
//#define IN1_PIN	GPIO_PIN_1
//#define IN2_PIN	GPIO_PIN_15
//#define IN3_PIN	GPIO_PIN_14
//#define IN4_PIN	GPIO_PIN_13
//
//#define IN1_PORT GPIOB
//#define IN2_PORT GPIOB
//#define IN3_PORT GPIOB
//#define IN4_PORT GPIOB
//
//void stepMotor(uint8_t step);
//void rotateSteps(uint16_t steps, uint8_t direction);
//void rotateDegrees(uint16_t degrees, uint8_t direction);
void justTurn();
void fullStop();
#include "delay_us.h"


// 프로젝트에 사용될 스태퍼모터의 갯수
#define STEPPER_UNITS     1


// 스태퍼모터 동작 방식
#define WAVE_STEP_DRIVE   0
#define FULL_STEP_DRIVE   1
#define HALF_STEP_DRIVE   2

// 스태퍼모터 동작 방향
#define DIR_CW            0
#define DIR_CCW           1

// 총 사용 스탭수
#define WAVE_RESOLUTION   2048
#define DRIVE_RESOLUTION  4096

// 아웃풋 핀
#define IN1_PIN   GPIO_PIN_1
#define IN1_PORT  GPIOB
#define IN2_PIN   GPIO_PIN_15
#define IN2_PORT  GPIOB
#define IN3_PIN   GPIO_PIN_14
#define IN3_PORT  GPIOB
#define IN4_PIN   GPIO_PIN_13
#define IN4_PORT  GPIOB


static const uint8_t WAVE_STEP_SEQ[4][4]=
    {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

static const uint8_t FULL_STEP_SEQ[4][4]=
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {1, 0, 0, 1}
    };

static const uint8_t HALF_STEP_SEQ[8][4] =
    {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {1, 0, 0, 1},
    };

void stepperSpeed(TIM_HandleTypeDef *htim, uint8_t speedLevel);
void setMotorDirection(uint8_t direction);
void rotateDegrees(uint16_t degrees, uint8_t direction, uint8_t speedLevel, TIM_HandleTypeDef *htim);


#endif /* INC_STEP_H_ */
