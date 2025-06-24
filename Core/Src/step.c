/*
 * step.c
 *
 *  Created on: Jun 18, 2025
 *      Author: wonhyeok
 */

#include "step.h"
#include "delay_us.h"

void justTurn() {								// 반시계 방향으로 스텝모터를 돌리는 함수
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, 0);	// 이 함수가 한번 실행될 때 어떤 움직임을 보이는지와
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, 0);	// while, for 등 반복문에 있을 때 어떻게 동작할 지 생각해 볼 것.
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, 0);
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, 0);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, 1);
	delay_us(3000);

	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, 0);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, 0);
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, 1);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, 0);
	delay_us(3000);

	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, 0);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, 1);
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, 0);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, 0);
	delay_us(3000);

	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, 1);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, 0);
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, 0);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, 0);
	delay_us(3000);
}


void fullStop() {									// 스텝모터를 멈추게 하는 함수
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, 1);		// 왜 모든 핀의 출력을 0으로 하지 않았는지??
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, 0);		// 스텝모터의 작동 원리와 토크를 유의하며 생각해 볼 것.
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, 0);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, 0);
}






static const uint16_t speedTable[] = {1000, 800, 600, 400, 200}; // 속도 테이블 (Hz 단위)
#define SPEED_TABLE_SIZE (sizeof(speedTable) / sizeof(speedTable[0]))


void stepperSpeed(TIM_HandleTypeDef *htim, uint8_t speedLevel)
{
    if (htim->Instance == TIM10)
    {
        if (speedLevel >= SPEED_TABLE_SIZE) return;

        uint16_t frequency = speedTable[speedLevel]; // 속도 선택
        uint16_t arr = (1000000 / frequency) - 1;    // ARR 계산 (PSC = 99 고정)
        htim->Instance->PSC = 100-1;
        htim->Instance->ARR = arr;                  // ARR 설정
        __HAL_TIM_SET_COUNTER(htim, 0);             // 타이머 초기화
    }
}

static volatile uint8_t currentStep = 0; // 현재 스텝 위치
volatile uint8_t motorDirection = DIR_CW; // 초기 방향
static volatile uint16_t remainingSteps = 0;  // 남은 스텝 수

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM10) // TIM10 인터럽트 확인
    {
        if (remainingSteps > 0)
        {
            // 방향에 따라 스텝 계산
            if (motorDirection == DIR_CW)
            {
                currentStep = (currentStep + 1) % 8; // 시계 방향
            }
            else
            {
                currentStep = (currentStep == 0) ? 7 : currentStep - 1; // 반시계 방향
            }

            // 모터 스텝 출력
            HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, HALF_STEP_SEQ[currentStep][0]);
            HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, HALF_STEP_SEQ[currentStep][1]);
            HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, HALF_STEP_SEQ[currentStep][2]);
            HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, HALF_STEP_SEQ[currentStep][3]);

            // 남은 스텝 감소
            remainingSteps--;
        }
        else
        {
            // 회전 완료되었으면 타이머 정지
            HAL_TIM_Base_Stop_IT(htim);
        }
    }
}

void setMotorDirection(uint8_t direction)
{
    motorDirection = direction;
}

void rotateDegrees(uint16_t degrees, uint8_t direction, uint8_t speedLevel, TIM_HandleTypeDef *htim)
{
    // 1도 당 몇 스텝인지 계산 (28BYJ-48의 경우 4096 스텝으로 360도 회전)
    uint16_t steps = (uint16_t)((uint32_t)degrees * 4096 / 360);

    // 남은 스텝 수를 초기화
    remainingSteps = steps;

    // 속도 설정 (타이머 주파수 조정)
    stepperSpeed(htim, speedLevel);

    // 방향 설정 (시계방향 또는 반시계방향)
    motorDirection = direction;

    // 타이머 인터럽트 시작
    HAL_TIM_Base_Start_IT(htim); // 타이머 인터럽트 시작
}





















