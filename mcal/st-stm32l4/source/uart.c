/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the microcontroller-specific UART driver
 *            implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"

#include "error_handler.h"

/* Functions------------------------------------------------------------------*/
/**
 * @brief  Initialize the provided UART peripheral with the provided baudrate.
 *
 * @param  uartHandle    Pointer to the HAL UART handle.
 * @param  uartInstance  The UART instance.
 * @param  baudrate      The baudrate to be configured in bps.
 */
void UartInit(UART_HandleTypeDef* const uartHandle,
              USART_TypeDef* const uartInstance,
              const uint32_t baudrate)
{
    uartHandle->Instance                    = uartInstance;
    uartHandle->Init.BaudRate               = baudrate;
    uartHandle->Init.WordLength             = UART_WORDLENGTH_8B;
    uartHandle->Init.StopBits               = UART_STOPBITS_1;
    uartHandle->Init.Parity                 = UART_PARITY_NONE;
    uartHandle->Init.Mode                   = UART_MODE_TX_RX;
    uartHandle->Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    uartHandle->Init.OverSampling           = UART_OVERSAMPLING_16;
    uartHandle->Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
    uartHandle->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if (HAL_UART_Init(uartHandle) != HAL_OK)
    {
        ErrorHandler();
    }
}

/**
 * @brief  Deinitialize the provided UART peripheral.
 *
 * @param  uartHandle  Pointer to the HAL UART handle.
 */
void UartDeinit(UART_HandleTypeDef* const uartHandle)
{
    HAL_UART_DeInit(uartHandle);
}
