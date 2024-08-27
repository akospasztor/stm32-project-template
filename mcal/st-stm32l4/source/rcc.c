/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the microcontroller-specific reset and clock
 *            control driver implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "rcc.h"

#include "stm32l4xx_hal.h"

/* Functions------------------------------------------------------------------*/
/**
 * @brief  Enable the SYSCFG clock.
 */
void RccEnableSysCfg(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
}

/**
 * @brief  Disable the SYSCFG clock.
 */
void RccDisableSysCfg(void)
{
    __HAL_RCC_SYSCFG_CLK_DISABLE();
}

/**
 * @brief  Enable the PWR clock.
 */
void RccEnablePwr(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
}

/**
 * @brief  Disable the PWR clock.
 */
void RccDisablePwr(void)
{
    __HAL_RCC_PWR_CLK_DISABLE();
}

/**
 * @brief  Enable the GPIOA clock.
 */
void RccEnablePortA(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
}

/**
 * @brief  Disable the GPIOA clock.
 */
void RccDisablePortA(void)
{
    __HAL_RCC_GPIOA_CLK_DISABLE();
}

/**
 * @brief  Enable the GPIOB clock.
 */
void RccEnablePortB(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

/**
 * @brief  Disable the GPIOB clock.
 */
void RccDisablePortB(void)
{
    __HAL_RCC_GPIOB_CLK_DISABLE();
}

/**
 * @brief  Enable the GPIOC clock.
 */
void RccEnablePortC(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
}

/**
 * @brief  Disable the GPIOC clock.
 */
void RccDisablePortC(void)
{
    __HAL_RCC_GPIOC_CLK_DISABLE();
}

/**
 * @brief  Enable the GPIOD clock.
 */
void RccEnablePortD(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
}

/**
 * @brief  Disable the GPIOD clock.
 */
void RccDisablePortD(void)
{
    __HAL_RCC_GPIOD_CLK_DISABLE();
}

/**
 * @brief  Enable the UART2 clock.
 */
void RccEnableUart2(void)
{
    __HAL_RCC_USART2_CLK_ENABLE();
}

/**
 * @brief  Disable the UART2 clock.
 */
void RccDisableUart2(void)
{
    __HAL_RCC_USART2_CLK_DISABLE();
}
