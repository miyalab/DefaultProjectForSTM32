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
 * File   : Slave.cpp
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include <SPI/Slave.h>

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI Slave Mode スーパークラス　Init関数
// DataSize  : SPI_DATASIZE_8BIT
//             SPI_DATASIZE_16BIT
// FirstBit  : SPI_FIRSTBIT_MSB
//             SPI_FIRSTBIT_LSB
// return : 0(正常)
//			other wise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::SPI_SlaveMode::Init(uint32_t DataSize, uint32_t FirstBit)
{
	// SPI設定
	hSpi.Init.Mode = SPI_MODE_SLAVE;
	hSpi.Init.Direction = SPI_DIRECTION_2LINES;
	hSpi.Init.DataSize = DataSize;
	hSpi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hSpi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hSpi.Init.NSS = SPI_NSS_HARD_INPUT;
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
// SPI3 Slave Mode クラス コンストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::SPI3_SlaveMode::SPI3_SlaveMode()
{
	__HAL_RCC_SPI3_CLK_ENABLE();
	hSpi.Instance = SPI3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Slave Mode クラス デストラクタ
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::SPI3_SlaveMode::~SPI3_SlaveMode()
{
	HAL_SPI_DeInit(&hSpi);
	__HAL_RCC_SPI3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Slave Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::SPI3_SlaveMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_15;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

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
