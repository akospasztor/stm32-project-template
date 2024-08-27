/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the microcontroller-specific UART driver
 *            function prototypes.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Defines -------------------------------------------------------------------*/

/* Functions------------------------------------------------------------------*/
void UartInit(UART_HandleTypeDef* const uartHandle,
              USART_TypeDef* const uartInstance,
              const uint32_t baudrate);
void UartDeinit(UART_HandleTypeDef* const uartHandle);

#ifdef __cplusplus
}
#endif

#endif
