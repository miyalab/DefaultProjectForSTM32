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
 * File   : Timer.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef MIYALAB_STM32F446RE_TIM_TIMER_H_
#define MIYALAB_STM32F446RE_TIM_TIMER_H_

//--------------------------
// TIM機能使用許可
//--------------------------
#define HAL_TIM_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_tim.h"

//--------------------------
// プロトタイプ宣言
//--------------------------
extern "C" {
	void TIM6_DAC_IRQHandler(void);
	void TIM7_IRQHandler(void);
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB {
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE {
		//----------------------------------------------------------------------
		// TIM6 Timer Mode クラス
		//----------------------------------------------------------------------
		class TIM6_TimerMode {
		public:
			~TIM6_TimerMode();
			uint8_t Init(uint16_t Divide, uint16_t Period);
		};

		//----------------------------------------------------------------------
		// TIM6 タイマー割込み関数
		//----------------------------------------------------------------------
		void TIM6_InterruptFunction();

		//----------------------------------------------------------------------
		// TIM7 Timer Mode クラス
		//----------------------------------------------------------------------
		class TIM7_TimerMode {
		public:
			~TIM7_TimerMode();
			uint8_t Init(uint16_t Divide, uint16_t Period);
		};

		//----------------------------------------------------------------------
		// TIM7 タイマー割込み関数
		//----------------------------------------------------------------------
		void TIM7_InterruptFunction();
	}
}

#endif /* MIYALAB_STM32F446RE_TIM_TIMER_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
