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
 * File   : Uart.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include <stdio.h>
#include <USART/Uart.h>

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
uint8_t MiYALAB::STM32F446RE::USART_UartMode::Init(uint32_t Baudrate, uint32_t Length, uint32_t StopBits, uint32_t Parity)
{
	// USART設定
	hUart.Init.BaudRate = Baudrate;
	hUart.Init.WordLength = Length;
	hUart.Init.StopBits = StopBits;
	hUart.Init.Parity = Parity;
	hUart.Init.Mode = UART_MODE_TX_RX;
	hUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	hUart.Init.OverSampling = UART_OVERSAMPLING_16;

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
MiYALAB::STM32F446RE::USART1_UartMode::USART1_UartMode()
{
	__HAL_RCC_USART1_CLK_ENABLE();
	hUart.Instance = USART1;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::USART1_UartMode::~USART1_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART1_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::USART1_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::USART2_UartMode::USART2_UartMode()
{
	__HAL_RCC_USART2_CLK_ENABLE();
	hUart.Instance = USART2;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::USART2_UartMode::~USART2_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART2_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::USART2_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART3 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::USART3_UartMode::USART3_UartMode()
{
	__HAL_RCC_USART3_CLK_ENABLE();
	hUart.Instance = USART3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART3 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::USART3_UartMode::~USART3_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART3 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::USART3_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART4 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::UART4_UartMode::UART4_UartMode()
{
	__HAL_RCC_UART4_CLK_ENABLE();
	hUart.Instance = UART4;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART4 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::UART4_UartMode::~UART4_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_UART4_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART4 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::UART4_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF8_UART4;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART5 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::UART5_UartMode::UART5_UartMode()
{
	__HAL_RCC_UART5_CLK_ENABLE();
	hUart.Instance = UART5;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART5 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::UART5_UartMode::~UART5_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_UART5_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART5 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::UART5_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_12;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF8_UART5;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);
	GpioInitStruct.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOD, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART6 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::USART6_UartMode::USART6_UartMode()
{
	__HAL_RCC_USART6_CLK_ENABLE();
	hUart.Instance = USART6;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART6 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::USART6_UartMode::~USART6_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART6_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART6 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::USART6_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_6;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// 標準入出力関数使用許可関数
// main.cppに以下の関数を定義してください。
// void MiYALAB::STM32F446RE::USART_PutChar(uint8_t C)
// uint8_t MiYALAB::STM32F446RE::USART_PutChar(uint8_t *C) : return: 0 or 1, *C:文字保存用
// void MiYALAB::STM32F446RE::USART_EchoBack(uint8_t C)
//
// floatを出力する場合は、リンカオプションに「-u _printf_float -u _scanf_float」を追加してください。
//--------------------------------------------------------------------------------------------
void MiYALAB::STM32F446RE::USART_stdioEnable()
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
}

//--------------------------------------------------------------------------------------------
// １文字送信関数(ラッパー関数)(未定義用)
//--------------------------------------------------------------------------------------------
__weak void MiYALAB::STM32F446RE::USART_PutChar(uint8_t C)
{

}

//--------------------------------------------------------------------------------------------
// １文字受信関数(ラッパー関数)(未定義用)
//--------------------------------------------------------------------------------------------
__weak uint8_t MiYALAB::STM32F446RE::USART_GetChar(uint8_t *C)
{
	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// エコーバック関数(ラッパー関数)(未定義用)
//--------------------------------------------------------------------------------------------
__weak void MiYALAB::STM32F446RE::USART_EchoBack(uint8_t C)
{

}

//--------------------------------------------------------------------------------------------
// 標準入出力関数用１文字送信関数関数
//--------------------------------------------------------------------------------------------
void __io_putchar(uint8_t ch)
{
	// 1文字送信
	MiYALAB::STM32F446RE::USART_PutChar(ch);
}

//--------------------------------------------------------------------------------------------
// 標準入出力関数用１文字受信関数関数
//--------------------------------------------------------------------------------------------
int __io_getchar(void)
{
	uint8_t Data;
	HAL_StatusTypeDef Status = HAL_BUSY;

	// 1文字受信
	while(Status != HAL_OK){
		Status = (HAL_StatusTypeDef)MiYALAB::STM32F446RE::USART_GetChar(&Data);
	}

	// コールバック
	MiYALAB::STM32F446RE::USART_EchoBack(Data);

	return(Data);
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------