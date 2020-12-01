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
 * File  : Timer.cpp
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include "Timer.h"

//--------------------------
// グローバル変数宣言
//--------------------------
namespace MiYALAB{
	namespace STM32F303K8{
		TIM_HandleTypeDef hTim6;
		TIM_HandleTypeDef hTim7;
	}
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM6 Timer Mode クラス Init関数
// Cycle[s] = Divide * Period / APB1 TimerClocks[Hz]
// Divide : 分周比
// Period : カウントリセット値
//
// main.cppに以下の関数を定義してください。
// void MiYALAB::STM32F303K8::TIM6_InterruptFunction(void)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::TIM6_TimerMode::Init(uint16_t Divide, uint16_t Period)
{
	// ハードウェア設定用データ群
	TIM_MasterConfigTypeDef MasterConfig = {0};

	// クロック許可
	__HAL_RCC_TIM6_CLK_ENABLE();

	// 割込み許可
	HAL_NVIC_SetPriority(TIM6_DAC1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM6_DAC1_IRQn);

	// TIM6 設定
	MiYALAB::STM32F303K8::hTim6.Instance = TIM6;
	MiYALAB::STM32F303K8::hTim6.Init.Prescaler = Divide - 1;
	MiYALAB::STM32F303K8::hTim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	MiYALAB::STM32F303K8::hTim6.Init.Period = Period - 1;
	MiYALAB::STM32F303K8::hTim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	// TIM6設定適用 タイマーモード
	if(HAL_TIM_Base_Init(&MiYALAB::STM32F303K8::hTim6) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM6 マスター設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;

	// TIM6 マスター設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&MiYALAB::STM32F303K8::hTim6, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM6 タイマー割込み許可
	HAL_TIM_Base_Start_IT(&MiYALAB::STM32F303K8::hTim6);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM6 Timer Mode クラス　デストラクタ
// TIM6_CLK 停止
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM6_TimerMode::~TIM6_TimerMode()
{
	HAL_TIM_Base_Stop_IT(&MiYALAB::STM32F303K8::hTim6);
	HAL_NVIC_DisableIRQ(TIM6_DAC1_IRQn);
	HAL_TIM_Base_DeInit(&MiYALAB::STM32F303K8::hTim6);
	__HAL_RCC_TIM6_CLK_DISABLE();
}



//--------------------------------------------------------------------------------------------
// TIM6 割込み関数（未定義用）
//--------------------------------------------------------------------------------------------
__weak void MiYALAB::STM32F303K8::TIM6_InterruptFunction()
{
	__HAL_RCC_TIM7_CLK_ENABLE();
	hTim6.Instance = TIM7;
	HAL_NVIC_SetPriority(TIM7_DAC2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM7_DAC2_IRQn);
}

//--------------------------------------------------------------------------------------------
// TIM6 割込みハンドラ
//--------------------------------------------------------------------------------------------
void TIM6_DAC1_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&MiYALAB::STM32F303K8::hTim6);

	MiYALAB::STM32F303K8::TIM6_InterruptFunction();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM7 Timer Mode クラス Init関数
// Cycle[s] = Divide * Period / APB1 TimerClocks[Hz]
// Divide : 分周比
// Period : カウントリセット値
//
// main.cppに以下の関数を定義してください。
// void MiYALAB::STM32F303K8::TIM7_InterruptFunction(void)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::TIM7_TimerMode::Init(uint16_t Divide, uint16_t Period)
{
	// ハードウェア設定用データ群
	TIM_MasterConfigTypeDef MasterConfig = {0};

	// クロック許可
	__HAL_RCC_TIM7_CLK_ENABLE();

	// 割込み許可
	HAL_NVIC_SetPriority(TIM7_DAC2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM7_DAC2_IRQn);

	// TIM7 設定
	MiYALAB::STM32F303K8::hTim7.Instance = TIM7;
	MiYALAB::STM32F303K8::hTim7.Init.Prescaler = Divide - 1;
	MiYALAB::STM32F303K8::hTim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	MiYALAB::STM32F303K8::hTim7.Init.Period = Period - 1;
	MiYALAB::STM32F303K8::hTim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	// TIM7設定適用 タイマーモード
	if(HAL_TIM_Base_Init(&MiYALAB::STM32F303K8::hTim7) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM7 マスター設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;

	// TIM7 マスター設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&MiYALAB::STM32F303K8::hTim7, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM7 タイマー割込み許可
	HAL_TIM_Base_Start_IT(&MiYALAB::STM32F303K8::hTim7);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM7 Timer Mode クラス　デストラクタ
// TIM7_CLK 停止
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::TIM7_TimerMode::~TIM7_TimerMode()
{
	HAL_TIM_Base_Stop_IT(&MiYALAB::STM32F303K8::hTim7);
	HAL_NVIC_DisableIRQ(TIM7_DAC2_IRQn);
	HAL_TIM_Base_DeInit(&MiYALAB::STM32F303K8::hTim7);
	__HAL_RCC_TIM7_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// TIM7 割込み関数（未定義用）
//--------------------------------------------------------------------------------------------
__weak void MiYALAB::STM32F303K8::TIM7_InterruptFunction()
{

}

//--------------------------------------------------------------------------------------------
// TIM7 割込みハンドラ
//--------------------------------------------------------------------------------------------
void TIM7_DAC2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&MiYALAB::STM32F303K8::hTim7);

	MiYALAB::STM32F303K8::TIM7_InterruptFunction();
}

//--------------------------------------------------------------------------------------------
// end of file
//--------------------------------------------------------------------------------------------
/*
 * 2020.12.01 : ファイル作成
 */
