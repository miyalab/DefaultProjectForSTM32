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
#include "Encoder.h"

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM Encoder Mode スーパークラス　Init関数
// Mode : TIM_ENCODERMODE_TI1  A相のみ
//        TIM_ENCODERMODE_TI2  B相のみ
//        TIM_ENCODERMODE_TI12 AB相
// count　= パルス数 / (Divide + 1)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::TIM_EncoderMode::Init(uint16_t Divide, uint32_t Mode)
{
	// ハードウェア設定用データ群
	TIM_Encoder_InitTypeDef Config ={0};
	TIM_MasterConfigTypeDef MasterConfig = {0};

	// TIM設定
	hTim.Init.Prescaler = Divide;
	hTim.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTim.Init.Period = MiYALAB::STM32F303K8::TIM::ENCODER_MAX;
	hTim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hTim.Init.RepetitionCounter = 0;
	hTim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	// TIM設定(エンコーダモード)
	Config.EncoderMode = Mode;
	Config.IC1Polarity = TIM_ICPOLARITY_RISING;
	Config.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	Config.IC1Prescaler = TIM_ICPSC_DIV1;
	Config.IC1Filter = 0;
	Config.IC2Polarity = TIM_ICPOLARITY_RISING;
	Config.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	Config.IC2Prescaler = TIM_ICPSC_DIV1;
	Config.IC2Filter = 0;

	// TIM設定(エンコーダモード)　適用
	if(HAL_TIM_Encoder_Init(&hTim, &Config) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM マスター設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	// TIM マスター設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&hTim, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 Encoder Mode クラス　コンストラクタ
// TIM1_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F303K8::TIM1_EncoderMode::TIM1_EncoderMode()
{
	__HAL_RCC_TIM1_CLK_ENABLE();
	hTim.Instance = TIM1;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 Encoder Mode クラス　デストラクタ
// TIM1_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F303K8::TIM1_EncoderMode::~TIM1_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM1_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 Encoder Mode クラス　Enable関数
// TIM1 CH1(PA8), CH2(PA9) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F303K8::TIM1_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF6_TIM1;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 Encoder Mode クラス　コンストラクタ
// TIM2_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F303K8::TIM2_EncoderMode::TIM2_EncoderMode()
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	hTim.Instance = TIM2;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 Encoder Mode クラス　デストラクタ
// TIM2_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F303K8::TIM2_EncoderMode::~TIM2_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM2_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 Encoder Mode クラス　Enable関数
// TIM2 CH1(PA0), CH2(PA1) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F303K8::TIM2_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	// パルス値初期化
	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 Encoder Mode クラス　コンストラクタ
// TIM3_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F303K8::TIM3_EncoderMode::TIM3_EncoderMode()
{
	__HAL_RCC_TIM3_CLK_ENABLE();
	hTim.Instance = TIM3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 Encoder Mode クラス　デストラクタ
// TIM3_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F303K8::TIM3_EncoderMode::~TIM3_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 Encoder Mode クラス　Enable関数
// TIM3 CH1(PB4), CH2(PB5) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F303K8::TIM3_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	// パルス値初期化
	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.01 : ファイル作成
 */
