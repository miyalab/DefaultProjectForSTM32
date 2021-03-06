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

#include "Calculator.h"
#include "ADC/Adc.h"
#include "TIM/Timer.h"
#include "USART/Uart.h"

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
MiYALAB::MultiAccess<uint16_t> delayCnt;

//--------------------------
// ライブラリモジュール
//--------------------------
MiYALAB::STM32F303K8::TIM7_TimerMode Tim7;
MiYALAB::STM32F303K8::USART2_UartMode Uart2;
MiYALAB::STM32F303K8::ADC_Mode Adc;

//--------------------------
// プロトタイプ宣言
//--------------------------
uint8_t HardwareSetup();
void delay(uint16_t delaySet);

//------------------------------------------------------------------------------
// メイン関数
//------------------------------------------------------------------------------
int main()
{
	// マイコン機能初期化
	HardwareSetup();

	// UART設定
	Uart2.Init(9600, UART_WORDLENGTH_8B, UART_STOPBITS_1, UART_PARITY_NONE);
	Uart2.Enable();
	MiYALAB::STM32F303K8::stdioEnable();

	// タイマー設定
	Tim7.Init(72,1000);

	// ADC設定
	Adc.Init(ADC_RESOLUTION_12B);
	Adc.Enable(0x03ffB);

	while (1){
		printf("%d %d %d %d %d %d %d %d %d\r\n",
				Adc.Read(0x0001),Adc.Read(0x0002),Adc.Read(0x0008),Adc.Read(0x0010),
				Adc.Read(0x0020),Adc.Read(0x0040),Adc.Read(0x0080),Adc.Read(0x0100),Adc.Read(0x0200));
		delay(1000);
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

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_3;
	GpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GpioInitStruct);

	return HAL_OK;
}

//------------------------------------------------------------------------------
// TIM7 割込み関数
//------------------------------------------------------------------------------
void MiYALAB::STM32F303K8::TIM7_InterruptFunction()
{
	delayCnt.Add(1);
}

//------------------------------------------------------------------------------
// １文字送信関数(ラッパー関数)
//------------------------------------------------------------------------------
void MiYALAB::STM32F303K8::PutChar(uint8_t C)
{
	Uart2.Transmit(C, 0xff);
}

//------------------------------------------------------------------------------
// エコーバック関数(ラッパー関数)
//------------------------------------------------------------------------------
void MiYALAB::STM32F303K8::EchoBack(uint8_t C)
{
	Uart2.Transmit(C, 0xff);
}

//------------------------------------------------------------------------------
// １文字受信関数(ラッパー関数)
//------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F303K8::GetChar(uint8_t *C)
{
	return Uart2.Receive(C, 0x01);
}

//------------------------------------------------------------------------------
// プログラム停止関数
//　delaySet : 待機時間[s] = delaySet * TIM7の割り込み周期[s]
//------------------------------------------------------------------------------
void delay(uint16_t delaySet)
{
	delayCnt.Clear();
	while(delayCnt.Read() < delaySet);
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
