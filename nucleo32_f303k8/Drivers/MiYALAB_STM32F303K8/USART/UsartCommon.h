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
 * File  : UsartCommon.h
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// UART機能使用許可
//--------------------------
#define HAL_UART_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include <stdio.h>
#include "stm32f3xx.h"
#include "stm32f3xx_hal_uart.h"

//--------------------------
// プロトタイプ宣言
//--------------------------
extern "C"{
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
	void __io_putchar(uint8_t ch);
	int __io_getchar(void);
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE* f)
#endif
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F303K8
	//--------------------------------------------------------------------------
	namespace STM32F303K8{
		//----------------------------------------------------------------------
		// USART用 標準入出力関数用ラッパー関数宣言
		//----------------------------------------------------------------------
		void stdioEnable();
		void PutChar(uint8_t C);
		uint8_t GetChar(uint8_t *C);
		void EchoBack(uint8_t C);
	}
}
//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.01 : ファイル作成
 */
