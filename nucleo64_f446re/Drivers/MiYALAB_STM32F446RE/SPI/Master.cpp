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
 * File   : Master.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include <SPI/Master.h>

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI Master Mode スーパークラス　Init関数
// Prescaler : SPI_BAUDRATEPRESCALER_2,   SPI_BAUDRATEPRESCALER_4,  SPI_BAUDRATEPRESCALER_8,
//             SPI_BAUDRATEPRESCALER_16,  SPI_BAUDRATEPRESCALER_32, SPI_BAUDRATEPRESCALER_64
//             SPI_BAUDRATEPRESCALER_128, SPI_BAUDRATEPRESCALER_256
// DataSize  : SPI_DATASIZE_8BIT
//             SPI_DATASIZE_16BIT
// FirstBit  : SPI_FIRSTBIT_MSB
//             SPI_FIRSTBIT_LSB
// Clock[Hz] = APBx peripheral clocks[Hz] / Prescaler (x=1[SPI2, 3], 2[SPI1])
// return : 0(正常)
//			other wise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::SPI_MasterMode::Init(uint32_t Prescaler, uint32_t DataSize, uint32_t FirstBit)
{
	// SPI設定
	hSpi.Init.Mode = SPI_MODE_MASTER;
	hSpi.Init.Direction = SPI_DIRECTION_2LINES;
	hSpi.Init.DataSize = DataSize;
	hSpi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hSpi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hSpi.Init.NSS = SPI_NSS_SOFT;
	hSpi.Init.BaudRatePrescaler = Prescaler;
	hSpi.Init.FirstBit = FirstBit;
	hSpi.Init.TIMode = SPI_TIMODE_DISABLE;
	hSpi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hSpi.Init.CRCPolynomial = 10;

	//　SPI設定適用
	if(HAL_SPI_Init(&hSpi) != HAL_OK) {
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Master Mode クラス コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::SPI3_MasterMode::SPI3_MasterMode()
{
	__HAL_RCC_SPI3_CLK_ENABLE();
	hSpi.Instance = SPI3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Master Mode クラス デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::SPI3_MasterMode::~SPI3_MasterMode()
{
	HAL_SPI_DeInit(&hSpi);
	__HAL_RCC_SPI3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Master Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::SPI3_MasterMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	return HAL_OK;
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.11.25 ファイル作成
 */
