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
 * File   : Uart.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef MIYALAB_STM32F446RE_USART_H_
#define MIYALAB_STM32F446RE_USART_H_

//--------------------------
// UART機能使用許可
//--------------------------
#define HAL_UART_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include "UsartCommon.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB {
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE {
		//----------------------------------------------------------------------
		// USART UART モード 基底クラス
		//----------------------------------------------------------------------
		class USART_UartMode {
		public:
			uint8_t Init(uint32_t Baudrate, uint32_t Length, uint32_t StopBits, uint32_t Parity);
			uint8_t Receive(uint8_t *C, uint16_t TimeOut);
			uint8_t Receive(uint8_t *Str, uint16_t Size, uint16_t TimeOut);
			uint8_t Transmit(uint8_t C, uint16_t TimeOut);
			uint8_t Transmit(uint8_t *Str, uint16_t Size, uint16_t TimeOut);
		protected:
			UART_HandleTypeDef hUart;
		};

		//----------------------------------------------------------------------
		// USART1 UART モード クラス
		//----------------------------------------------------------------------
		class USART1_UartMode: public USART_UartMode {
		public:
			USART1_UartMode();
			~USART1_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// USART2 UART モード クラス
		//----------------------------------------------------------------------
		class USART2_UartMode: public USART_UartMode {
		public:
			USART2_UartMode();
			~USART2_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// USART3 UART モード クラス
		//----------------------------------------------------------------------
		class USART3_UartMode: public USART_UartMode {
		public:
			USART3_UartMode();
			~USART3_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// UART4 UART モード クラス
		//----------------------------------------------------------------------
		class UART4_UartMode: public USART_UartMode {
		public:
			UART4_UartMode();
			~UART4_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// UART5 UART モード クラス
		//----------------------------------------------------------------------
		class UART5_UartMode: public USART_UartMode {
		public:
			UART5_UartMode();
			~UART5_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// USART6 UART モード クラス
		//----------------------------------------------------------------------
		class USART6_UartMode: public USART_UartMode {
		public:
			USART6_UartMode();
			~USART6_UartMode();
			uint8_t Enable();
		};
	}
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
		// MiYA LAB OSS
		// USART Uart Mode スーパークラス　Receive関数
		// *C : 1文字保存用
		// TimeOut: タイムアウト時間
		//--------------------------------------------------------------------------------------------
		inline uint8_t USART_UartMode::Receive(uint8_t *C, uint16_t TimeOut)
		{
			return HAL_UART_Receive(&hUart, C, 1, TimeOut);
		}

		//--------------------------------------------------------------------------------------------
		// MiYA LAB OSS
		// USART Uart Mode スーパークラス　Receive関数
		// *Str : 文字列保存用
		// Size : Sｔｒのデータサイズ
		// TimeOut: タイムアウト時間
		//--------------------------------------------------------------------------------------------
		inline uint8_t USART_UartMode::Receive(uint8_t *Str, uint16_t Size, uint16_t TimeOut)
		{
			return HAL_UART_Receive(&hUart, Str, Size, TimeOut);
		}

		//--------------------------------------------------------------------------------------------
		// MiYA LAB OSS
		// USART Uart Mode スーパークラス　Transmit関数
		// *C : 送信文字
		// TimeOut: タイムアウト時間
		//--------------------------------------------------------------------------------------------
		inline uint8_t USART_UartMode::Transmit(uint8_t C, uint16_t TimeOut)
		{
			return HAL_UART_Transmit(&hUart, &C, 1, TimeOut);
		}

		//--------------------------------------------------------------------------------------------
		// MiYA LAB OSS
		// USART Uart Mode スーパークラス　Transmit関数
		// *Str : 送信文字列
		// Size : Sｔｒのデータサイズ
		// TimeOut: タイムアウト時間
		//--------------------------------------------------------------------------------------------
		inline uint8_t USART_UartMode::Transmit(uint8_t *Str, uint16_t Size, uint16_t TimeOut)
		{
			return HAL_UART_Transmit(&hUart, Str, Size, TimeOut);
		}
	}
}


#endif /* MIYALAB_STM32F446RE_USART_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.11.24 コメントの一部を修正
 */
