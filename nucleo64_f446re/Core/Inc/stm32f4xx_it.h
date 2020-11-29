/*
 * File : stm32f3xx_it.h
 *
 * Controller: STM32 Nucleo32-F446RE
 *
 * Date   : 2019/11/30
 * Author : K.Miyauchi
 */
#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------
// プロトタイプ宣言
//--------------------------
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
