/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "fnd.h"
#include "step.h"
#include "lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//	이 위치에 있는 변수들은 전역 변수이기 때문에 초기값 불필요. 설정하고싶으면 할 수 있음.
int photo_int_1_state;								// 광인터럽트의 상태를 나타내는 플래그 선언, 1층 광인터럽트.
int photo_int_2_state;								// 광인터럽트의 상태를 나타내는 플래그 선언, 2층 광인터럽트.
int photo_int_3_state;								// 광인터럽트의 상태를 나타내는 플래그 선언, 3층 광인터럽트.

int button_1_state;									// 버튼의 상태를 나타내는 플래그 선언, 1층 버튼
int button_2_state;									// 버튼의 상태를 나타내는 플래그 선언, 2층 버튼
int button_3_state;									// 버튼의 상태를 나타내는 플래그 선언, 3층 버튼

int lcdState;										// LCD의 상태를 나타내는 플래그 선언
int doorState;										// 서보 모터의 상태를 나타내는 플래그 선언(문)
int buzzerState;									// 버저의 상태를 나타내는 플래그 선언
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {		// 각각 3개의 광인터럽트와 버튼을 외부 인터럽트로 사용, 만약 신호가 들어올 시의 동작 설정하는 부분
	if(GPIO_Pin == GPIO_PIN_8) {			// C8에 연결되어있는 광인터럽트 1번(1층)으로 인터럽트 신호가 들어오면
		photo_int_1_state = 1;				// 광인터럽트 1 플래그를 세우고
		photo_int_2_state = 0;				// 다른 광인터럽트 플래그를 초기화.
		photo_int_3_state = 0;
		buzzerState = 1;					// 버저 플래그를 세움.
	}
	else if(GPIO_Pin == GPIO_PIN_6) {		// C6에 연결되어있는 광인터럽트 2번(2층)으로 인터럽트 신호가 들어오면
		photo_int_1_state = 0;
		photo_int_2_state = 1;				// 광인터럽트 2 플래그를 세우고
		photo_int_3_state = 0;				// 다른 광인터럽트 플래그를 초기화.
		buzzerState = 1;					// 버저 플래그를 세움.
	}
	else if(GPIO_Pin == GPIO_PIN_5) {		// C5에 연결되어있는 광인터럽트 3번(3층)으로 인터럽트 신호가 들어오면
		photo_int_1_state = 0;
		photo_int_2_state = 0;
		photo_int_3_state = 1;				// 광인터럽트 3 플래그를 세우고 다른 광인터럽트 플래그를 초기화.
		buzzerState = 1;					// 버저 플래그를 세움.
	}
	else if(GPIO_Pin == GPIO_PIN_11) {		// C11에 연결되어 있는 버튼 1번(1층 버튼)으로 인터럽트 신호가 들어오면
		button_1_state = 1;					// 1번 버튼 플래그를 세우고 다른 버튼 플래그를 초기화.
		button_2_state = 0;
		button_3_state = 0;
		lcdState = 1;						// LCD 플래그를 세움.
	}
	else if(GPIO_Pin == GPIO_PIN_2) {		// C2에 연결되어 있는 버튼 2번(2층 버튼)으로 인터럽트 신호가 들어오면
		button_1_state = 0;
		button_2_state = 1;					// 2번 버튼 플래그를 세우고 다른 버튼 플래그를 초기화.
		button_3_state = 0;
		lcdState = 1;						// LCD 플래그를 세움.
	}
	else if(GPIO_Pin == GPIO_PIN_3) {		// C3에 연결되어 있는 버튼 3번(3층 버튼)으로 인터럽트 신호가 들어오면
		button_1_state = 0;
		button_2_state = 0;
		button_3_state = 1;					// 3번 버튼 플래그를 세우고 다른 버튼 플래그를 초기화.
		lcdState = 1;						// LCD 플래그를 세움.
	}
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM11_Init();
  MX_I2C1_Init();
  MX_TIM10_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  // 모든 타이머는 여기서 init / start 함수를 실행한 순간부터 counting 하기 시작함.
  HAL_TIM_Base_Start(&htim11);					// delay_us() 함수를 위한 11번 타이머 시작해줌
  HAL_TIM_Base_Start_IT(&htim10);				// 스텝모터 사용을 위한 10번 타이머 인터럽트 시작해줌.(for문이나 delay 등 동작시 해당 동작만을 위해 mpu의 연산을 점유하는것을 방지)
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);		// 서보모터 사용을 위한 2번 타이머 PWM을 시작해줌.
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);		// 버저 사용을 위한 5번 타이머 PWM을 시작해줌.
  i2cLcd_Init();								// LCD를 사용하기 위해 i2c 통신 활성화.


  while(1) {									// 광인터럽트 사이에 껴서 어떠한 인터럽트 신호도 받지 못하는 상황을 방지하기 위해 초기 동작 선언.
	  	  	  	  	  	  	  	  	  	  	  	// while(1)이기 때문에 항상 참, 내부 동작을 무한 반복함.
	  justTurn();								// 스텝모터를 푸는 방향으로 계속 돌게 해줌(함수명에 F3을 눌러 함수의 동작을 보고 왜 모터가 끝없이 도는지 생각해 볼 것.)
	  if(photo_int_1_state == 1) {				// 만약 스텝모터가 계속 풀리면서 내려가다가 1번 포토인터럽트(1층)에 신호가 들어오면
		  fullStop();							// 스텝모터 정지
		  button_1_state = 1;					// 버튼 1 플래그를 세움
		  lcdState = 1;							// LCD 플래그를 세움
		  break;								// break로 현재 속해있는 while(1) 무한반복문을 벗어남.
		  	  	  	  	  	  	  	  	  	  	// break로 벗어나면 그 다음에 어떤 코드로 넘어가는지 C언어의 절차 지향성을 바탕으로 생각해 볼 것.
	  }
	  else if(photo_int_2_state == 1) {			// 만약 스텝모터가 계속 풀리면서 내려가다가 2번 포토인터럽트(2층)에 신호가 들어오면
		  fullStop();							// 스텝모터 정지
		  button_2_state = 1;					// 버튼 2 플래그를 세움
		  lcdState = 1;							// LCD 플래그를 세움
		  break;								// break로 현재 속해있는 while(1) 무한반복문을 벗어남.
	  }
	  else if(photo_int_3_state == 1) {			// 만약 스텝모터가 계속 풀리면서 내려가다가 3번 포토인터럽트(3층)에 신호가 들어오면
		  fullStop();							// 스텝모터 정지
		  button_3_state = 1;					// 버튼 3 플래그를 세움
		  lcdState = 1;							// LCD 플래그를 세움
		  break;								// break로 현재 속해있는 while(1) 무한반복문을 벗어남.
	  }
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)										// 이게 진짜 메인 구조임. 위의 while문에서 break로 빠져나오면 이곳의 코드가 돌기 시작함.
  {
	// -----------------------------------------------1층, 2층, 3층에 멈춰있는 구간---------------------------------------------

	  if(photo_int_1_state == 1 && button_1_state == 1) {		// 1번 광인터럽트 플래그와 1번 버튼 플래그가 활성화 되어 있으면
		if(lcdState == 1) {										// 1번 LCD 플래그가 세워져 있는지 검사한 후 1이면
			lcdCommand(CLEAR_DISPLAY);							// LCD 클리어(이전에 띄워져 있는 글자를 먼저 지워야 함)
			delay_us(2000);										// Datasheet에서 권장하는 딜레이 시간을 준 후
			moveCursor(0, 4);									// LCD 윗줄, 좌에서 4칸 띄운 후 문구 작성(중간정렬을 위해 4칸 띄워줌)
			lcdString("Welcome");								// Welcome이라는 문자열 표시
			moveCursor(1, 3);									// LCD 아랫줄, 좌에서 3칸 띄운 후 문구 작성(중간정렬을 위해 4칸 띄워줌)
			lcdString("1st Floor");								// 이곳이 1층이라는 문자열을 표시해줌
			lcdState = 0;										/* LCD 상태를 표시해주는 플래그를 0으로 초기화 시켜줌
																	왜 초기화 해주는지, 초기화를 해주지 않으면 어떻게 움직이는지??
																 	 while문의 동작과 lcd의 데이터시트를 참고하며 생각해 볼 것.
																 */
		}
		seg_number_CA(1);										// FND에 숫자 1을 띄워줌
		fullStop();												// 서보모터 정지
		ledOn(7);
		if(buzzerState == 1) {									// 버저 플래그가 1인지 검사한 후 1이면
			TIM5->CCR2 = 194;									// PWM신호를 듀티비 50%로 출력해줌
			delay_us(65000);
			delay_us(65000);
			delay_us(65000);
			delay_us(65000);									// 대략 0.25초정도 버저 울림을 지속하다가
			TIM5->CCR2 = 0;										// PWM 신호를 듀티비 0%로 출력해준 후
			buzzerState = 0;									// 버저 플래그를 0으로 초기화
																// 듀티비 50%와 0%의 의미는 무엇인지, 플래그를 초기화 하는 이유와 초기화 해주지 않으면 어떻게 동작하는지??
																// 스피커의 작동 원리와 while문의 동작을 참고하며 생각해 볼 것.
		}
		if(doorState == 0) {									// 서보모터 플래그를 검사 후 만약 0이면
			delay_us(65000);									// 65ms만큼 기다린 후
			TIM2->CCR1 = 30;									// 서보모터를 돌리는 PWM신호의 듀티비를 바꾸어 문이 열리는 방향으로 돌림
			doorState = 1;										// 서보모터 플래그를 1로 셋팅해 줌
																// 서보모터 플래그를 1로 바꾸어 주는 이유, 바꾸지 않으면 어떻게 동작하는지???
																// while문의 동작과 딜레이의 동작 원리를 참고하며 생각해 볼 것.
		}
	}
	else if(photo_int_2_state == 1 && button_2_state == 1) {	// 2번 광인터럽트와 2번 버튼의 플래그가 활성화 되어 있으면
		if(lcdState == 1) {										// 위에 동작과 거의 유사함. 위의 if문을 참고하고 생각해 볼 것.
			lcdCommand(CLEAR_DISPLAY);
			delay_us(2000);
			moveCursor(0, 4);
			lcdString("Welcome");
			moveCursor(1, 3);
			lcdString("2nd Floor");
			lcdState = 0;
		}
		seg_number_CA(2);
		fullStop();
		ledOn(7);
		if(buzzerState == 1) {
			TIM5->CCR2 = 194;
			delay_us(65000);
			delay_us(65000);
			delay_us(65000);
			delay_us(65000);
			TIM5->CCR2 = 0;
			buzzerState = 0;
		}
		if(doorState == 0) {
			delay_us(65000);
			TIM2->CCR1 = 30;
			doorState = 1;
		}
	}
	else if(photo_int_3_state == 1 && button_3_state == 1) {	// 3번 광인터럽트와 3번 버튼의 플래그가 활성화 되어 있으면
		if(lcdState == 1) {										// 위에 동작과 거의 유사함. 위의 if문을 참고하고 생각해 볼 것.
			lcdCommand(CLEAR_DISPLAY);
			delay_us(2000);
			moveCursor(0, 4);
			lcdString("Welcome");
			moveCursor(1, 3);
			lcdString("3rd Floor");
			lcdState = 0;
		}
		seg_number_CA(3);
		fullStop();
		ledOn(7);
		if(buzzerState == 1) {
			TIM5->CCR2 = 194;
			delay_us(65000);
			delay_us(65000);
			delay_us(65000);
			delay_us(65000);
			TIM5->CCR2 = 0;
			buzzerState = 0;
		}
		if(doorState == 0) {
			delay_us(65000);
			TIM2->CCR1 = 30;
			doorState = 1;
		}
	}
	// --------------------------------------------------1층, 2층, 3층에 멈춰있는 구간-----------------------------------------------------



	// --------------------------------------------------1층에서 2,3층 올라가는 구간-------------------------------------------------------
	else if(photo_int_1_state == 1 && button_2_state == 1) {		// 1번 광인터럽트 플래그와 2번 버튼 플래그가 활성화 되어 있으면
		if(doorState == 1) {										// 서보모터 플래그가 1인지 검사 후 1이면
			TIM2->CCR1 = 125;										// 문이 닫히는 방향으로 서보모터를 돌림
			doorState = 0;											// 서보모터 플래그를 0으로 초기화
			delay_us(65000);
		}
		if(lcdState == 1) {											// LCD 플래그가 1이면
			lcdCommand(CLEAR_DISPLAY);								// LCD 초기화 후
			delay_us(2000);
			moveCursor(0, 2);
			lcdString("Please Wait");								// 기다리라는 문구를 윗줄에 표시
			moveCursor(1, 3);
			lcdString("Ascending");									// 올라가고 있다는 문구를 아랫줄에 표시
		}
		seg_number_CA(1);											// FND에 숫자 1을 표시
		ledRS(7);													// LED가 위로 올라가는 방향으로 흐르며 켜짐
		rotateDegrees(300, DIR_CW, 0, &htim10);						// 스텝모터를 위로 올라갈수 있게 감아줌(문이 닫힌 후 출발할 수 있게 서보모터 동작을 스텝모터 동작보다 위에 코드 작성)

	}
	else if(photo_int_1_state == 1 && button_3_state == 1) {		// 1번 광인터럽트 플래그와 3번 버튼 플래그가 활성화 되어 있으면
		if(doorState == 1) {										// 위의 동작과 동일, 위 if문 참고할 것.
			TIM2->CCR1 = 125;
			doorState = 0;
			delay_us(65000);
		}
		if(lcdState == 1) {
			lcdCommand(CLEAR_DISPLAY);
			delay_us(2000);
			moveCursor(0, 2);
			lcdString("Please Wait");
			moveCursor(1, 3);
			lcdString("Ascending");
		}
		seg_number_CA(1);
		ledRS(7);
		rotateDegrees(300, DIR_CW, 0, &htim10);
	}
	// -----------------------------1층에서 2,3층 올라가는 구간-------------------------------------------



	// -----------------------------2층에서 1층 내려가거나/3층 올라가는 구간-------------------------------------------
	else if(photo_int_2_state == 1 && button_1_state == 1) {		// 2번 광인터럽트 플래그와 1번 버튼 플래그가 세워져 있으면
		if(doorState == 1) {										// 서보모터 플래그가 세워져 있으면
			TIM2->CCR1 = 125;										// 문이 닫히는 방향으로 서보모터 돌림
			doorState = 0;											// 서보모터 플래그 초기화
			delay_us(65000);
		}
		if(lcdState == 1) {											// LCD 플래그가 1인지 검사 후 맞으면
			lcdCommand(CLEAR_DISPLAY);								// LCD 화면을 지우고
			delay_us(2000);
			moveCursor(0, 2);
			lcdString("Please Wait");								// 윗줄에 중앙정렬후 기다리라는 문구 표시
			moveCursor(1, 2);
			lcdString("Descending");								// 아랫줄에 중앙정렬 후 내려간다는 문구 표시
		}
		seg_number_CA(2);											// FND에 숫자 2 표시
		ledLS(7);													// LED 아래로 흐르게 표시
		rotateDegrees(300, DIR_CCW, 0, &htim10);					// 스텝모터 풀어서 밑으로 내려가게 함
	}
	else if(photo_int_2_state == 1 && button_3_state == 1) {		// 2번 광인터럽트 플래그와 3번 버튼 플래그가 세워져 있으면
		if(doorState == 1) {										// 서보모터 플래그가 세워져 있는지 검사 후 세워져 있으면
			TIM2->CCR1 = 125;										// 문이 닫히는 방향으로 서보모터 돌림
			doorState = 0;											// 서보모터 플래그 초기화
			delay_us(65000);
		}
		if(lcdState == 1) {											// LCD 플래그가 1인지 검사 후 맞으면
			lcdCommand(CLEAR_DISPLAY);								// LCD 화면을 지우고
			delay_us(2000);
			moveCursor(0, 2);
			lcdString("Please Wait");								// 윗줄에 중앙정렬 후 기다리라는 문구 표시
			moveCursor(1, 3);
			lcdString("Ascending");									// 아랫줄에 중앙정렬 후 올라간다는 문구 표시
		}
		seg_number_CA(2);											// FND에 숫자 2 표시
		ledRS(7);													// LED 위로 흐르게 표시
		rotateDegrees(300, DIR_CW, 0, &htim10);						// 스텝모터 감아서 위로 올라가게 함
	}
	// -----------------------------2층에서 1층 내려가거나/3층 올라가는 구간-------------------------------------------



	// -----------------------------3층에서 1,2층 내려가는 구간-------------------------------------------
	else if(photo_int_3_state == 1 && button_1_state == 1) {		// 3번 광인터럽트 플래그와 1번 버튼 플래그가 세워져 있으면
		if(doorState == 1) {										// 서보모터 플래그가 1인지 검사 후 맞으면
			TIM2->CCR1 = 125;										// 서보모터 문 닫히는 방향으로 돌림
			doorState = 0;											// 서보모터 플래그 초기화
			delay_us(65000);
		}
		if(lcdState == 1) {											// LCD 플래그가 1인지 검사후 맞으면
			lcdCommand(CLEAR_DISPLAY);								// LCD 화면 지운 후
			delay_us(2000);
			moveCursor(0, 2);
			lcdString("Please Wait");								// 윗줄 중앙정렬 후 기다리라는 문구 표시
			moveCursor(1, 2);
			lcdString("Descending");								// 아랫줄 중앙정렬 후 내려간다는 문구 표시
		}
		seg_number_CA(3);											// FND에 숫자 3 표시
		ledLS(7);													// LED 아래로 흐르게 표시
		rotateDegrees(300, DIR_CCW, 0, &htim10);					// 스텝모터 풀어서 아래로 내려가게 돌림
	}
	else if(photo_int_3_state == 1 && button_2_state == 1) {		// 3번 광인터럽트 플래그와 2번 버튼 플래그가 세워져 있으면
		if(doorState == 1) {										// 위의 if문과 거의 동일, 위에 구문들 참조.
			TIM2->CCR1 = 125;
			doorState = 0;
			delay_us(65000);
		}
		if(lcdState == 1) {
			lcdCommand(CLEAR_DISPLAY);
			delay_us(2000);
			moveCursor(0, 2);
			lcdString("Please Wait");
			moveCursor(1, 2);
			lcdString("Descending");
		}
		seg_number_CA(3);
		ledLS(7);
		rotateDegrees(300, DIR_CCW, 0, &htim10);
	}
	// -----------------------------3층에서 1,2층 내려가는 구간-------------------------------------------



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
