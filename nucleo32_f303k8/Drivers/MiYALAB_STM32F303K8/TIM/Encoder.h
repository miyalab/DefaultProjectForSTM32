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
 * File  : Encoder.h
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef MIYALAB_STM32F303K8_TIM_ENCODER_H_
#define MIYALAB_STM32F303K8_TIM_ENCODER_H_

//--------------------------
// TIM機能使用許可
//--------------------------
#define HAL_TIM_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f3xx.h"
#include "stm32f3xx_hal_tim.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F303K8
	//--------------------------------------------------------------------------
	namespace STM32F303K8{
		//----------------------------------------------------------------------
		// TIM 定数
		//----------------------------------------------------------------------
		namespace TIM{
			constexpr uint16_t ENCODER_MAX = 65535;		// TIM エンコーダ最大値
			constexpr uint16_t ENCODER_CENTER = 32767;	// TIM エンコーダ中央値
		}

		//----------------------------------------------------------------------
		// TIM Encoder Mode スーパークラス
		//----------------------------------------------------------------------
		class TIM_EncoderMode{
		public:
			uint8_t Init(uint16_t Divide, uint32_t Mode);
			int16_t Read();
			void Clear();
		protected:
			TIM_HandleTypeDef hTim;
		};

		//----------------------------------------------------------------------
		// TIM1 Encoder Mode クラス CH1(PA8), CH2(PA9)
		//----------------------------------------------------------------------
		class TIM1_EncoderMode : public TIM_EncoderMode{
		public:
			TIM1_EncoderMode();
			~TIM1_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM2 Encoder Mode クラス CH1(PA0), CH2(PA1)
		//----------------------------------------------------------------------
		class TIM2_EncoderMode : public TIM_EncoderMode{
		public:
			TIM2_EncoderMode();
			~TIM2_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM3 Encoder Mode クラス CH1(PA6), CH2(PA7)
		//----------------------------------------------------------------------
		class TIM3_EncoderMode : public TIM_EncoderMode{
		public:
			TIM3_EncoderMode();
			~TIM3_EncoderMode();
			uint8_t Enable();
		};
	}
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM Encoder Mode スーパークラス Clear関数
// パルス係数初期化
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F303K8::TIM_EncoderMode::Clear()
{
	hTim.Instance->CNT = MiYALAB::STM32F303K8::TIM::ENCODER_CENTER;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM Encoder Mode スーパークラス Read関数
// return : パルス数
//--------------------------------------------------------------------------------------------
inline int16_t MiYALAB::STM32F303K8::TIM_EncoderMode::Read()
{
	return(hTim.Instance->CNT - MiYALAB::STM32F303K8::TIM::ENCODER_CENTER);
}

#endif /* MIYALAB_STM32F303K8_TIM_ENCODER_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.01 : ファイル作成
 */
