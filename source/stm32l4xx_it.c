/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the implementations of interrupt handlers.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_it.h"

#include "error_handler.h"
#include "stm32l4xx_hal.h"

/******************************************************************************/
/* Cortex-M4 Processor Interruption and Exception Handlers                    */
/******************************************************************************/

/**
 * @brief  This function handles the non-maskable interrupts.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void NMI_Handler(void)
{
    ErrorHandler();
}

/**
 * @brief  This function handles the hard-fault interrupts.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void HardFault_Handler(void)
{
    ErrorHandler();
}

/**
 * @brief  This function handles the memory management faults.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void MemManage_Handler(void)
{
    ErrorHandler();
}

/**
 * @brief  This function handles the prefetch faults and memory access faults.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void BusFault_Handler(void)
{
    ErrorHandler();
}

/**
 * @brief  This function handles the undefined instruction and illegal states.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void UsageFault_Handler(void)
{
    ErrorHandler();
}

/**
 * @brief  This function handles the system service calls via SWI instruction.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles the debug monitor interrupts.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles the pendable requests for system service.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles system tick timer interrupts.
 */
// NOLINTNEXTLINE(readability-identifier-naming)
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* For the available peripheral interrupt handler names, please refer to the  */
/* startup file (startup_stm32l4xx.s).                                        */
/******************************************************************************/
