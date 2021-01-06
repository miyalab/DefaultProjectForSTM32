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

//--------------------------
// インクルード
//--------------------------
#include <TIM/Pwm.h>

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　Init関数
// Cycle[s] = Divide * Period / APBx_TimerClock[Hz] (x=1,2)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::TIM_PwmMode::Init(uint16_t Divide, uint16_t Period)
{
	// ハードウェア設定用データ群
	TIM_MasterConfigTypeDef MasterConfig = {0};
	TIM_BreakDeadTimeConfigTypeDef BreakDeadTimeConfig = {0};

	// TIM設定
	hTim.Init.Prescaler = Divide - 1;
	hTim.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTim.Init.Period = Period - 1;
	hTim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hTim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	// TIM設定適用 PWMモード
	if(HAL_TIM_PWM_Init(&hTim) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM マスタ設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	// TIM マスタ設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&hTim, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM1 or TIM8
	if(hTim.Instance == TIM1 || hTim.Instance == TIM8){
		// TIM ブレーキデッドタイム設定
		BreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
		BreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
		BreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
		BreakDeadTimeConfig.DeadTime = 0;
		BreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
		BreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
		BreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;

		// TIM ブレーキデッドタイム設定適用
		if(HAL_TIMEx_ConfigBreakDeadTime(&hTim, &BreakDeadTimeConfig) != HAL_OK){
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// end of file
//--------------------------------------------------------------------------------------------