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
 * File  : MiYALAB_STM32F303K8_.h
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef SRC_MIYALAB_STM32F303K8_TIM_TIMER_H_
#define SRC_MIYALAB_STM32F303K8_TIM_TIMER_H_

//--------------------------
// TIM機能使用許可
//--------------------------
#define HAL_TIM_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f3xx.h"
#include "stm32f3xx_hal_tim.h"

//--------------------------
// プロトタイプ宣言
//--------------------------
extern "C"{
	void TIM6_DAC1_IRQHandler(void);
	void TIM7_DAC2_IRQHandler(void);
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F303K8
	//--------------------------------------------------------------------------
	namespace STM32F303K8{
		class TIM6_TimerMode{
		public:
			uint8_t Init(uint16_t Divide, uint16_t Period);
			~TIM6_TimerMode();
		};

		class TIM7_TimerMode{
		public:
			uint8_t Init(uint16_t Divide, uint16_t Period);
			~TIM7_TimerMode();
		};

		void TIM6_InterruptFunction();
		void TIM7_InterruptFunction();
	}
}

#endif /* SRC_MIYALAB_STM32F303K8_TIM_TIMER_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------