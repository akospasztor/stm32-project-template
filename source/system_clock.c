/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the system clock driver implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "system_clock.h"

#include "error_handler.h"
#include "rcc.h"
#include "stm32l4xx_hal.h"

/* Functions -----------------------------------------------------------------*/
/**
 * @brief  Configure the system clock.
 */
void SystemClockConfigure(void)
{
    RCC_OscInitTypeDef rccOscInitStruct;
    RCC_ClkInitTypeDef rccClkInitStruct;
    RCC_PeriphCLKInitTypeDef periphClkInit;

    RccEnableSysCfg();
    RccEnablePwr();

    rccOscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
    rccOscInitStruct.MSIState            = RCC_MSI_ON;
    rccOscInitStruct.MSICalibrationValue = 0;
    rccOscInitStruct.MSIClockRange       = RCC_MSIRANGE_6;
    rccOscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    rccOscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_MSI;
    rccOscInitStruct.PLL.PLLM            = 1;
    rccOscInitStruct.PLL.PLLN            = 24;
    rccOscInitStruct.PLL.PLLP            = RCC_PLLP_DIV2;
    rccOscInitStruct.PLL.PLLQ            = RCC_PLLQ_DIV2;
    rccOscInitStruct.PLL.PLLR            = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&rccOscInitStruct) != HAL_OK)
    {
        ErrorHandler();
    }

    rccClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    rccClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    rccClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    rccClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    rccClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&rccClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        ErrorHandler();
    }

    periphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    periphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&periphClkInit) != HAL_OK)
    {
        ErrorHandler();
    }

    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        ErrorHandler();
    }
}
