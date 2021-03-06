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
 * File  : Uart.cpp
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include "Uart.h"

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART Uart Mode スーパークラス　Init関数
// Baudrate : 0 < Baudrate(通信速度[bps]) << (システムクロック/10)
// Length   : UART_WORDLENGTH_8B(データ長8bit)
//            UART_WORDLENGTH_9B(データ長9bit)
// StopBits : UART_STOPBITS_1(1ストップビット)
//            UART_STOPBITS_2(2ストップビット)
// Parity   : UART_PARITY_NONE(パリティなし)
//            UART_PARITY_EVEN(偶数パリティ)
//            UART_PARITY_ODD(奇数パリティ)
// return : 0(正常)
//			other wise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::USART_UartMode::Init(uint32_t Baudrate, uint32_t Length, uint32_t StopBits, uint32_t Parity)
{
	// USART設定
	hUart.Init.BaudRate = Baudrate;
	hUart.Init.WordLength = Length;
	hUart.Init.StopBits = StopBits;
	hUart.Init.Parity = Parity;
	hUart.Init.Mode = UART_MODE_TX_RX;
	hUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	hUart.Init.OverSampling = UART_OVERSAMPLING_16;
	hUart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	hUart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	// USART設定適用(UART)
	if(HAL_UART_Init(&hUart) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::USART1_UartMode::USART1_UartMode()
{
	__HAL_RCC_USART1_CLK_ENABLE();
	hUart.Instance = USART1;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::USART1_UartMode::~USART1_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART1_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::USART1_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOB, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::USART2_UartMode::USART2_UartMode()
{
	__HAL_RCC_USART2_CLK_ENABLE();
	hUart.Instance = USART2;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F303K8::USART2_UartMode::~USART2_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART2_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::USART2_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_15;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	return HAL_OK;
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.01 : ファイル作成
 */
