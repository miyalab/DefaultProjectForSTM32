/*
 * Project    : nucleo64_f303k8
 * File       : main.cpp
 *
 * Controller : STM32 Nucleo32-F303K8
 *
 * Date       : 2020/11/28
 * Author     : K.Miyauchi
 */

//--------------------------
// インクルード
//--------------------------
#include <stdio.h>
#include "stm32f3xx.h"

//--------------------------
// シンボル定義
//--------------------------
constexpr uint8_t SYS_CLOCK = 72;
constexpr uint8_t APB1_TIMER = 72;
constexpr uint8_t APB2_TIMER = 72;
constexpr uint8_t APB1_PERIPHERAL = 36;
constexpr uint8_t APB2_PERIPHERAL = 72;

//--------------------------
// グローバル変数宣言
//--------------------------

//--------------------------
// ライブラリモジュール
//--------------------------

//--------------------------
// プロトタイプ宣言
//--------------------------
uint8_t HardwareSetup();

//------------------------------------------------------------------------------
// メイン関数
//------------------------------------------------------------------------------
int main(void)
{
	// マイコン機能初期化
	HardwareSetup();

	while (1){

	}
}

//------------------------------------------------------------------------------
// ハードウェア初期化関数
// システムクロック：HSE
// Nucleo32 BoardのSB4をショート, SB6をオープンにしてください
//------------------------------------------------------------------------------
uint8_t HardwareSetup()
{
	// ハードウェア設定用データ軍
	RCC_OscInitTypeDef OscInitStruct = {0};
	RCC_ClkInitTypeDef ClkInitStruct = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// HALドライバ初期化
	HAL_Init();

	// クロック許可設定
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	// OSC設定
	OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	OscInitStruct.HSEState = RCC_HSE_BYPASS;
	OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	OscInitStruct.HSIState = RCC_HSI_ON;
	OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

	// OSC設定適用
	if (HAL_RCC_OscConfig(&OscInitStruct) != HAL_OK){
		return HAL_ERROR;
	}

	// CLK設定
	ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	// CLK設定適用
	if (HAL_RCC_ClockConfig(&ClkInitStruct, FLASH_LATENCY_2) != HAL_OK){
		return HAL_ERROR;
	}

	GpioInitStruct.Pin = GPIO_PIN_3;
	GpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GpioInitStruct);

	return HAL_OK;
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
