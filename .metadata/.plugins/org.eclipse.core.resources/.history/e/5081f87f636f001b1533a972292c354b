/*
 * MIT License
 *
 * Copyright (c) 2021 MiYA LAB(K.Miyauchi)
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
 * File   : Master.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef MIYALAB_STM32F446RE_I2C_MASTER_H_
#define MIYALAB_STM32F446RE_I2C_MASTER_H_

//--------------------------
// I2C機能使用許可
//--------------------------
#define HAL_I2C_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_i2c.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB {
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE {
		//----------------------------------------------------------------------
		// I2C MasterMode スーパークラス
		//----------------------------------------------------------------------
		class I2C_MasterMode{
		public:
			uint8_t Init(uint32_t clock);
			void Transmit(uint16_t Address, uint8_t *SendData, uint16_t Size);
			void Receive(uint16_t Address, uint8_t *ReadData, uint16_t Size);

		protected:
			I2C_HandleTypeDef hI2C;
		};

		//----------------------------------------------------------------------
		// I2C1 MasterMode スーパークラス
		//----------------------------------------------------------------------
		class I2C1_MasterMode : public I2C_MasterMode{
			I2C1_MasterMode();
			~I2C1_MasterMode();
		};

		//----------------------------------------------------------------------
		// I2C2 MasterMode スーパークラス
		//----------------------------------------------------------------------
		class I2C2_MasterMode : public I2C_MasterMode{
			I2C2_MasterMode();
			~I2C2_MasterMode();
		};

		//----------------------------------------------------------------------
		// I2C3 MasterMode スーパークラス
		//----------------------------------------------------------------------
		class I2C3_MasterMode : public I2C_MasterMode{
			I2C3_MasterMode();
			~I2C3_MasterMode();
		};

	}
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE{
		inline void I2C_MasterMode::Transmit(uint16_t Address, uint8_t *SendData, uint16_t Size){
			HAL_I2C_Master_Transmit(&hI2C, Address, SendData, Size, 0xffff);
		}

		inline void I2C_MasterMode::Receive(uint16_t Address, uint8_t *ReadData, uint16_t Size){
			HAL_I2C_Master_Receive(&hI2C, Address, ReadData, Size, 0xffff);
		}
	}
}

#endif /* MIYALAB_STM32F446RE_I2C_MASTER_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2021.02.15 更新
 * 2021.01.30 ファイル作成
 */
