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
 * File  : Slave.h
 * Author: K.Miyauchi
 *
 * Version : 1.00
 */
#ifndef MIYALAB_STM32F303K8_SPI_SLAVE_H_
#define MIYALAB_STM32F303K8_SPI_SLAVE_H_

//--------------------------
// SPI機能使用許可
//--------------------------
#define HAL_SPI_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f3xx.h"
#include "stm32f3xx_hal_spi.h"
#include "stm32f3xx_hal_spi_ex.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F303K8
	//--------------------------------------------------------------------------
	namespace STM32F303K8{
		//----------------------------------------------------------------------
		// SPI Master Mode スーパークラス
		//----------------------------------------------------------------------
		class SPI_SlaveMode{
		public:
			uint8_t Init(uint32_t Prescaler, uint32_t DataSize, uint32_t FirstBit);
			void TransmitReceive(uint8_t *SendData, uint8_t *ReadData, uint16_t Size);
		protected:
			SPI_HandleTypeDef hSpi;
		};

		//----------------------------------------------------------------------
		// SPI1 Master Mode クラス
		//----------------------------------------------------------------------
		class SPI1_SlaveMode : public SPI_SlaveMode{
			SPI1_SlaveMode();
			~SPI1_SlaveMode();
			uint8_t Enable();
		};
	}
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI Slave Mode TransmitReceive関数
// SendData : 送信データ
// ReadData :　受信データ格納用
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F303K8::SPI_SlaveMode::TransmitReceive(uint8_t *SendData, uint8_t *ReadData, uint16_t Size)
{
	HAL_SPI_TransmitReceive(&hSpi, SendData, ReadData, Size, 100);
}

#endif /* MIYALAB_STM32F303K8_SPI_SLAVE_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.12.02 : ファイル作成
 */
