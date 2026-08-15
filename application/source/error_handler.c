/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the error handler implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "error_handler.h"

#include "stm32l4xx_hal.h"

/* Functions -----------------------------------------------------------------*/
/**
 * @brief  This function is executed in case of error occurrence.
 */
void ErrorHandler(void)
{
    __disable_irq();
    for (;;)
    {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Report the name of the file and the line number where the error has
 *         occurred.
 *
 * @param  file  Pointer to the file name.
 * @param  line  Error line number.
 */
// NOLINTNEXTLINE(readability-identifier-naming,readability-non-const-parameter)
void assert_failed(uint8_t* file, uint32_t line)
{
    __disable_irq();
    for (;;)
    {
    }

    UNUSED(file);
    UNUSED(line);
}
#endif
