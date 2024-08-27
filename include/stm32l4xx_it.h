/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the interrupt handler function prototypes.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

#ifndef STM32L4XX_IT_H
#define STM32L4XX_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Functions------------------------------------------------------------------*/
void NMI_Handler(void);         // NOLINT(readability-identifier-naming)
void HardFault_Handler(void);   // NOLINT(readability-identifier-naming)
void MemManage_Handler(void);   // NOLINT(readability-identifier-naming)
void BusFault_Handler(void);    // NOLINT(readability-identifier-naming)
void UsageFault_Handler(void);  // NOLINT(readability-identifier-naming)
void SVC_Handler(void);         // NOLINT(readability-identifier-naming)
void DebugMon_Handler(void);    // NOLINT(readability-identifier-naming)
void PendSV_Handler(void);      // NOLINT(readability-identifier-naming)
void SysTick_Handler(void);     // NOLINT(readability-identifier-naming)

#ifdef __cplusplus
}
#endif

#endif
