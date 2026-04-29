/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the main application implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "button.h"
#include "error_handler.h"
#include "led.h"
#include "log.h"
#include "rcc.h"
#include "stm32l4xx_hal.h"
#include "system_clock.h"

/* Private defines -----------------------------------------------------------*/
#define FIRMWARE_VERSION_MAJOR 1U /**< Major version */
#define FIRMWARE_VERSION_MINOR 0U /**< Minor version */
#define FIRMWARE_VERSION_PATCH 0U /**< Patch version */

/**
 * @brief  The main function.
 *
 * @return This function shall never return.
 */
int main(void)
{
    (void)HAL_Init();
    SystemClockConfigure();

    ButtonInit();
    LedInitLd2();
    LedInitLd3();
    LogInit();

    LogPrint("Starting application...\n");
    LogPrint("Firmware version: %u.%u.%u\n", FIRMWARE_VERSION_MAJOR,
             FIRMWARE_VERSION_MINOR, FIRMWARE_VERSION_PATCH);

    uint32_t counter = 0U;
    for (;;)
    {
        if (ButtonIsPressed())
        {
            LedLd3On();
        }
        else
        {
            LedLd3Off();
        }

        if ((counter % 10U) == 0U)
        {
            LogPrint("*");
            LedLd2On();
        }
        else
        {
            LedLd2Off();
        }

        HAL_Delay(100U);
        counter++;
    }
}
