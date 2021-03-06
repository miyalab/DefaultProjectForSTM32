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
 * File   : UsartCommon.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include <stdio.h>
#include "USART/UsartCommon.h"

//--------------------------------------------------------------------------------------------
// 標準入出力関数用１文字送信関数関数
//--------------------------------------------------------------------------------------------
void __io_putchar(uint8_t ch)
{
	using namespace MiYALAB::STM32F446RE;

	// 1文字送信
	USART_PutChar(ch);
}

//--------------------------------------------------------------------------------------------
// 標準入出力関数用１文字受信関数関数
//--------------------------------------------------------------------------------------------
int __io_getchar(void)
{
	using namespace MiYALAB::STM32F446RE;

	uint8_t Data;
	HAL_StatusTypeDef Status = HAL_BUSY;

	// 1文字受信
	while (Status != HAL_OK) {
		Status = (HAL_StatusTypeDef) USART_GetChar(&Data);
	}

	// コールバック
	USART_EchoBack(Data);

	return (Data);
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB {
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE {
		//--------------------------------------------------------------------------------------------
		// 標準入出力関数使用許可関数
		// main.cppに以下の関数を定義してください。
		// void USART_PutChar(uint8_t C)
		// uint8_t USART_PutChar(uint8_t *C) : return: 0 or 1, *C:文字保存用
		// void USART_EchoBack(uint8_t C)
		// floatを出力する場合は、リンカオプションに「-u _printf_float -u _scanf_float」を追加してください。
		//--------------------------------------------------------------------------------------------
		void USART_stdioEnable()
		{
			setbuf(stdout, NULL);
			setbuf(stdin, NULL);
		}

		//--------------------------------------------------------------------------------------------
		// １文字送信関数(ラッパー関数)(未定義用)
		//--------------------------------------------------------------------------------------------
		__weak void USART_PutChar(uint8_t C)
		{

		}

		//--------------------------------------------------------------------------------------------
		// １文字受信関数(ラッパー関数)(未定義用)
		//--------------------------------------------------------------------------------------------
		__weak uint8_t USART_GetChar(uint8_t *C)
		{
			return HAL_OK;
		}

		//--------------------------------------------------------------------------------------------
		// エコーバック関数(ラッパー関数)(未定義用)
		//--------------------------------------------------------------------------------------------
		__weak void USART_EchoBack(uint8_t C)
		{

		}
	}
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
