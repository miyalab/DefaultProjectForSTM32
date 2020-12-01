/*
 * MIT License
 *
 * Copyright (c) 2020 MiYA LAB(K.Miyauchi)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * File  : Pwm.cpp
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include "Pwm.h"

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　Init関数
// Cycle[s] = Divide * Period / APBx_TimerClock[Hz] (x=1,2)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::TIM_PwmMode::Init(uint16_t Divide, uint16_t Period)
{
	// ハードウェア設定用データ群
	TIM_MasterConfigTypeDef MasterConfig = {0};
	TIM_BreakDeadTimeConfigTypeDef BreakDeadTimeConfig = {0};

	// TIM設定
	hTim.Init.Prescaler = Divide - 1;
	hTim.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTim.Init.Period = Period - 1;
	hTim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hTim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	// TIM設定適用 PWMモード
	if(HAL_TIM_PWM_Init(&hTim) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM マスタ設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	// TIM マスタ設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&hTim, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM1 or TIM8
	if(hTim.Instance == TIM1){
		// TIM ブレーキデッドタイム設定
		BreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
		BreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
		BreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
		BreakDeadTimeConfig.DeadTime = 0;
		BreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
		BreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
		BreakDeadTimeConfig.BreakFilter = 0;
		BreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
		BreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
		BreakDeadTimeConfig.Break2Filter = 0;
		BreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
		if (HAL_TIMEx_ConfigBreakDeadTime(&hTim, &BreakDeadTimeConfig) != HAL_OK){
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 PWM Mode クラス コンストラクタ
// TIM1_CLK 開始
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM1_PwmMode::TIM1_PwmMode()
{
	__HAL_RCC_TIM1_CLK_ENABLE();
	hTim.Instance = TIM1;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 PWM Mode クラス　デストラクタ
// TIM1_CLK 停止
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM1_PwmMode::~TIM1_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM1_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F303K8::TIM::CHANNEL_1(チャンネル1(PA8)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_2(チャンネル2(PA9)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_3(チャンネル3(PA10)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_4(チャンネル4(PA11)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::TIM1_PwmMode::Enable(uint8_t UseChannel)
{
	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_1){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_8;
		GpioInitStruct.Alternate = GPIO_AF6_TIM1;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_2){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_9;
		GpioInitStruct.Alternate = GPIO_AF6_TIM1;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_3){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_10;
		GpioInitStruct.Alternate = GPIO_AF6_TIM1;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_4){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_11;
		GpioInitStruct.Alternate = GPIO_AF11_TIM1;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 PWM Mode クラス コンストラクタ
// TIM2_CLK 開始
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM2_PwmMode::TIM2_PwmMode()
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	hTim.Instance = TIM2;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 PWM Mode クラス　デストラクタ
// TIM2_CLK 停止
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM2_PwmMode::~TIM2_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM2_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F303K8::TIM::CHANNEL_1(チャンネル1(PA0)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_2(チャンネル2(PA1)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_3(チャンネル3(PA2)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_4(チャンネル4(PA3)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::TIM2_PwmMode::Enable(uint8_t UseChannel)
{
	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF1_TIM2;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_1){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_0;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_2){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_1;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_3){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_2;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_4){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_3;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			return HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 PWM Mode クラス コンストラクタ
// TIM3_CLK 開始
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM3_PwmMode::TIM3_PwmMode()
{
	__HAL_RCC_TIM3_CLK_ENABLE();
	hTim.Instance = TIM3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 PWM Mode クラス　デストラクタ
// TIM3_CLK 停止
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM3_PwmMode::~TIM3_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F303K8::TIM::CHANNEL_1(チャンネル1(PA6)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_2(チャンネル2(PA7)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_3(チャンネル3(PB0)の使用許可)
//				MiYALAB::STM32F303K8::TIM::CHANNEL_4(チャンネル4(PB1)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::TIM3_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM3;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_1){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_6;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_2){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_3){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_0;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F303K8::TIM::CHANNEL_4){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_1;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return Ret;
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.01 : ファイル作成
 */
