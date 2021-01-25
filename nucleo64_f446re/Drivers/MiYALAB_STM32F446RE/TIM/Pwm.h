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
 * File   : Pwm.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef MiYALAB_STM32F446RE_TIM_H_
#define MiYALAB_STM32F446RE_TIM_H_

//--------------------------
// TIM機能使用許可
//--------------------------
#define HAL_TIM_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_tim.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB {
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE {
		//----------------------------------------------------------------------
		// TIM 定数
		//----------------------------------------------------------------------
		namespace TIM {
			constexpr uint8_t CHANNEL_1 = 0x01;			// TIM チャンネル1
			constexpr uint8_t CHANNEL_2 = 0x02;			// TIM チャンネル2
			constexpr uint8_t CHANNEL_3 = 0x04;			// TIM チャンネル3
			constexpr uint8_t CHANNEL_4 = 0x08;			// TIM チャンネル4
			constexpr uint8_t CHANNEL_ALL = 0x0f;       // TIM 全チャンネル
		}

		//----------------------------------------------------------------------
		// TIM PWM Mode スーパークラス
		//----------------------------------------------------------------------
		class TIM_PwmMode {
		public:
			uint8_t Init(uint16_t Divide, uint16_t Period);
			void PwmOut1(uint16_t Duty);
			void PwmOut2(uint16_t Duty);
			void PwmOut3(uint16_t Duty);
			void PwmOut4(uint16_t Duty);
		protected:
			TIM_HandleTypeDef hTim;
		};

		//----------------------------------------------------------------------
		// TIM1 PWM Mode クラス CH1(PA8), CH2(PA9), CH3(PA10), CH4(PA11)
		//----------------------------------------------------------------------
		class TIM1_PwmMode: public TIM_PwmMode {
		public:
			TIM1_PwmMode();
			~TIM1_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM2 PWM Mode クラス CH1(PA5), CH2(PB3), CH3(PB10), CH4(PB2)
		//----------------------------------------------------------------------
		class TIM2_PwmMode: public TIM_PwmMode {
		public:
			TIM2_PwmMode();
			~TIM2_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM3 PWM Mode クラス CH1(PB4), CH2(PB5), CH3(PB0), CH4(PB1)
		//----------------------------------------------------------------------
		class TIM3_PwmMode: public TIM_PwmMode {
		public:
			TIM3_PwmMode();
			~TIM3_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM4 PWM Mode クラス CH1(PB6), CH2(PB7), CH3(PB8), CH4(PB9)
		//----------------------------------------------------------------------
		class TIM4_PwmMode: public TIM_PwmMode {
		public:
			TIM4_PwmMode();
			~TIM4_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM5 PWM Mode クラス CH1(PA0), CH2(PA1), CH3(PA2), CH4(PA3)
		//----------------------------------------------------------------------
		class TIM5_PwmMode: public TIM_PwmMode {
		public:
			TIM5_PwmMode();
			~TIM5_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM8 PWM Mode クラス  CH1(PC6), CH2(PC7), CH3(PC8), CH4(PC9)
		//----------------------------------------------------------------------
		class TIM8_PwmMode: public TIM_PwmMode {
		public:
			TIM8_PwmMode();
			~TIM8_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM12 PWM Mode クラス   CH1(PB14), CH2(PB15)
		//----------------------------------------------------------------------
		class TIM12_PwmMode: public TIM_PwmMode {
		public:
			TIM12_PwmMode();
			~TIM12_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
			void PwmOut3(uint16_t Duty)
			{
			}			// 使用不可
			void PwmOut4(uint16_t Duty)
			{
			}			// 使用不可
		};
	}
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut1関数
// チャンネル1のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut1(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_1, Duty);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut2関数
// チャンネル2のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut2(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_2, Duty);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut3関数
// チャンネル3のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut3(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_3, Duty);
}

//--------------------------------------------------------------------------------------------
/// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut4関数
// チャンネル4のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut4(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_4, Duty);
}

#endif /* MiYALAB_STM32F446RE_TIM_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
