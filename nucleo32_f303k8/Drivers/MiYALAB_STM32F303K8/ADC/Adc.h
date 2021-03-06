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
 * File  : Adc.h
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef MIYALAB_STM32F303K8_ADC_ADC_H_
#define MIYALAB_STM32F303K8_ADC_ADC_H_

//--------------------------
// ADC機能使用許可
//--------------------------
#define HAL_ADC_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f3xx.h"
#include "stm32f3xx_hal_adc.h"
#include "stm32f3xx_hal_adc_ex.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F303K8
	//--------------------------------------------------------------------------
	namespace STM32F303K8{
		//----------------------------------------------------------------------
		// AD 定数
		//----------------------------------------------------------------------
		namespace AD{
			constexpr uint16_t IN_0 = 0x0001;		// ADC IN0端子(PA0)
			constexpr uint16_t IN_1 = 0x0002;		// ADC IN1端子(PA1)
			constexpr uint16_t IN_2 = 0x0004;		// ADC IN2端子(PA2)
			constexpr uint16_t IN_3 = 0x0008;		// ADC IN3端子(PA3)
			constexpr uint16_t IN_4 = 0x0010;		// ADC IN4端子(PA4)
			constexpr uint16_t IN_5 = 0x0020;		// ADC IN5端子(PA5)
			constexpr uint16_t IN_6 = 0x0040;		// ADC IN6端子(PA6)
			constexpr uint16_t IN_7 = 0x0080;		// ADC IN7端子(PA7)
			constexpr uint16_t IN_8 = 0x0100;		// ADC IN8端子(PB0)
			constexpr uint16_t IN_9 = 0x0200;		// ADC IN9端子(PB1)
		}

		//----------------------------------------------------------------------
		// ADC_Modeクラス
		//----------------------------------------------------------------------
		class ADC_Mode{
		public:
			~ADC_Mode();
			uint8_t Init(uint32_t Resolution);
			uint8_t Enable(uint16_t In);
			int16_t Read(uint16_t In);
		private:
			ADC_HandleTypeDef hAdc;
		};
	}
}

#endif /* MIYALAB_STM32F303K8_ADC_ADC_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.02 : ファイル作成
 */
