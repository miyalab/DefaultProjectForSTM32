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
 * File  : Adc.cpp
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include "Adc.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode クラス デストラクタ
// ADC CLK停止
//------------------------------------------------------------------------------
MiYALAB::STM32F303K8::ADC_Mode::~ADC_Mode()
{
	HAL_ADC_Stop(&hAdc);
	HAL_ADC_DeInit(&hAdc);
	__HAL_RCC_ADC1_CLK_DISABLE();
	__HAL_RCC_ADC2_CLK_DISABLE();
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode スーパークラス　Init関数
// Resolution : ADC_RESOLUTION_6B(6bit ADC)
//            : ADC_RESOLUTION_8B(8bit ADC)
//            : ADC_RESOLUTION_10B(10bit ADC)
//            : ADC_RESOLUTION_12B(12bit ADC)
// return : 0(正常)
//			otherwise(エラー)
//------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::ADC_Mode::Init(uint32_t Resolution)
{
	// クロック設定
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_ADC2_CLK_ENABLE();

	// ADC設定
	hAdc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hAdc.Init.Resolution = Resolution;
	hAdc.Init.ScanConvMode = DISABLE;
	hAdc.Init.ContinuousConvMode = DISABLE;
	hAdc.Init.DiscontinuousConvMode = DISABLE;
	hAdc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hAdc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hAdc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hAdc.Init.NbrOfConversion = 1;
	hAdc.Init.DMAContinuousRequests = DISABLE;
	hAdc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hAdc.Init.LowPowerAutoWait = DISABLE;
	hAdc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;

	// ADC1設定 適用
	hAdc.Instance = ADC1;
	if(HAL_ADC_Init(&hAdc) != HAL_OK){
		return HAL_ERROR;
	}

	// ADC2設定 適用
	hAdc.Instance = ADC2;
	if(HAL_ADC_Init(&hAdc) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode クラス　Read関数
// 指定したIN端子のADC値を読み込みます。
// In : MiYALAB::STM32F303K8::AD::IN_X(X=0~9)
// return : ADC値
//          -1(エラー)
//------------------------------------------------------------------------------
int16_t MiYALAB::STM32F303K8::ADC_Mode::Read(uint16_t In)
{
	int16_t AdcValue = 0;

	// ハードウェア設定用データ群
	ADC_ChannelConfTypeDef Config = {0};

	// チャンネル設定
	Config.Rank = 1;
	Config.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

	// IN0 ~ IN3,IN11~12 の設定
	if(In & (MiYALAB::STM32F303K8::AD::IN_0 | MiYALAB::STM32F303K8::AD::IN_1 | MiYALAB::STM32F303K8::AD::IN_2 |
			MiYALAB::STM32F303K8::AD::IN_3 | MiYALAB::STM32F303K8::AD::IN_8 | MiYALAB::STM32F303K8::AD::IN_9)){
		hAdc.Instance = ADC1;
		if((In & MiYALAB::STM32F303K8::AD::IN_0) == MiYALAB::STM32F303K8::AD::IN_0)      Config.Channel = ADC_CHANNEL_1;
		else if((In & MiYALAB::STM32F303K8::AD::IN_1) == MiYALAB::STM32F303K8::AD::IN_1) Config.Channel = ADC_CHANNEL_2;
		else if((In & MiYALAB::STM32F303K8::AD::IN_2) == MiYALAB::STM32F303K8::AD::IN_2) Config.Channel = ADC_CHANNEL_3;
		else if((In & MiYALAB::STM32F303K8::AD::IN_3) == MiYALAB::STM32F303K8::AD::IN_3) Config.Channel = ADC_CHANNEL_4;
		else if((In & MiYALAB::STM32F303K8::AD::IN_8) == MiYALAB::STM32F303K8::AD::IN_8) Config.Channel = ADC_CHANNEL_11;
		else if((In & MiYALAB::STM32F303K8::AD::IN_9) == MiYALAB::STM32F303K8::AD::IN_9) Config.Channel = ADC_CHANNEL_12;
	}
	else if(In & (MiYALAB::STM32F303K8::AD::IN_4 | MiYALAB::STM32F303K8::AD::IN_5 | MiYALAB::STM32F303K8::AD::IN_6 |
			MiYALAB::STM32F303K8::AD::IN_7)){
		hAdc.Instance = ADC2;
		if((In & MiYALAB::STM32F303K8::AD::IN_4) == MiYALAB::STM32F303K8::AD::IN_4)      Config.Channel = ADC_CHANNEL_1;
		else if((In & MiYALAB::STM32F303K8::AD::IN_5) == MiYALAB::STM32F303K8::AD::IN_5) Config.Channel = ADC_CHANNEL_2;
		else if((In & MiYALAB::STM32F303K8::AD::IN_6) == MiYALAB::STM32F303K8::AD::IN_6) Config.Channel = ADC_CHANNEL_3;
		else if((In & MiYALAB::STM32F303K8::AD::IN_7) == MiYALAB::STM32F303K8::AD::IN_7) Config.Channel = ADC_CHANNEL_4;
	}
	else return -1;

	// チャンネル設定 適用
	if(HAL_ADC_ConfigChannel(&hAdc, &Config) != HAL_OK){
		return -1;
	}

	// ADC開始
	if(HAL_ADC_Start(&hAdc) != HAL_OK){
		return -1;
	}

	// AD変換
	if(HAL_ADC_PollForConversion(&hAdc, 10) != HAL_OK){
		return -1;
	}

	// ADC値取得
	if((HAL_ADC_GetState(&hAdc) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC){
		AdcValue = HAL_ADC_GetValue(&hAdc);
	}

	// ADC停止
	if(HAL_ADC_Stop(&hAdc) != HAL_OK){
		return -1;
	}

	return AdcValue;
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode クラス　Enable関数
// 使用するADCのIN端子を設定します。
// In : MiYALAB::STM32F303K8::AD::IN_X(X=0~9)
// return : 0(正常)
//			otherwise(エラー)
//------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::ADC_Mode::Enable(uint16_t In)
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	//　GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_ANALOG;
	GpioInitStruct.Pull = GPIO_NOPULL;

	// IN0 ~ IN7 の設定
	if(In & (MiYALAB::STM32F303K8::AD::IN_0 | MiYALAB::STM32F303K8::AD::IN_1 | MiYALAB::STM32F303K8::AD::IN_2 |
			MiYALAB::STM32F303K8::AD::IN_3 | MiYALAB::STM32F303K8::AD::IN_4 | MiYALAB::STM32F303K8::AD::IN_5 |
			MiYALAB::STM32F303K8::AD::IN_6 | MiYALAB::STM32F303K8::AD::IN_7)){
		// クロック設定
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = 0x0000;

		if(In & MiYALAB::STM32F303K8::AD::IN_0)      GpioInitStruct.Pin |= GPIO_PIN_0;
		else if(In & MiYALAB::STM32F303K8::AD::IN_1) GpioInitStruct.Pin |= GPIO_PIN_1;
		else if(In & MiYALAB::STM32F303K8::AD::IN_2) GpioInitStruct.Pin |= GPIO_PIN_2;
		else if(In & MiYALAB::STM32F303K8::AD::IN_3) GpioInitStruct.Pin |= GPIO_PIN_3;
		else if(In & MiYALAB::STM32F303K8::AD::IN_4) GpioInitStruct.Pin |= GPIO_PIN_4;
		else if(In & MiYALAB::STM32F303K8::AD::IN_5) GpioInitStruct.Pin |= GPIO_PIN_5;
		else if(In & MiYALAB::STM32F303K8::AD::IN_6) GpioInitStruct.Pin |= GPIO_PIN_6;
		else if(In & MiYALAB::STM32F303K8::AD::IN_7) GpioInitStruct.Pin |= GPIO_PIN_7;
		else return HAL_ERROR;

		// GPIO設定 適用
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
	}

	// IN8 ~ IN9 の設定
	if(In & (MiYALAB::STM32F303K8::AD::IN_8 | MiYALAB::STM32F303K8::AD::IN_9)){
		// クロック設定
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = 0x0000;

		if(In & MiYALAB::STM32F303K8::AD::IN_8)      GpioInitStruct.Pin |= GPIO_PIN_0;
		else if(In & MiYALAB::STM32F303K8::AD::IN_9) GpioInitStruct.Pin |= GPIO_PIN_1;
		else return HAL_ERROR;

		// GPIO設定 適用
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
	}

	return HAL_OK;
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.02 : ファイル作成
 */
