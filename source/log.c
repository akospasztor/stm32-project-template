/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the implementation of the logging module.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "log.h"

#include "gpio.h"
#include "rcc.h"
#include "uart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Defines -------------------------------------------------------------------*/
/** Buffer size used for logging. */
#define LOG_BUFFER_SIZE 80
/** GPIO port of the UART TX pin used for logging. */
#define LOG_UART_GPIO_PORT_TX GPIOA
/** GPIO pin of the UART TX pin used for logging. */
#define LOG_UART_GPIO_PIN_TX GPIO_PIN_2
/** GPIO port of the UART RX pin used for logging. */
#define LOG_UART_GPIO_PORT_RX GPIOD
/** GPIO port of the UART RX pin used for logging. */
#define LOG_UART_GPIO_PIN_RX GPIO_PIN_6

/* Private variables ---------------------------------------------------------*/
/** ST HAL handle for the UART peripheral used for logging. */
static UART_HandleTypeDef logHandle;
/** Buffer used for logging. */
static uint8_t logBuffer[LOG_BUFFER_SIZE];

/* Functions -----------------------------------------------------------------*/
/**
 * @brief  Initialize the logging module.
 *
 * This initializes the used UART peripheral and corresponding GPIO pins.
 */
void LogInit(void)
{
    RccEnableUart2();
    UartInit(&logHandle, USART2, 115200);

    RccEnablePortA();
    RccEnablePortD();

    GpioConfigureAlternateFunction(LOG_UART_GPIO_PORT_TX, LOG_UART_GPIO_PIN_TX,
                                   GPIO_AF7_USART2);
    GpioConfigureAlternateFunction(LOG_UART_GPIO_PORT_RX, LOG_UART_GPIO_PIN_RX,
                                   GPIO_AF7_USART2);
}

/**
 * @brief  Deinitialize the logging module.
 *
 * This deinitializes the used UART peripheral and corresponding GPIO pins.
 */
void LogDeinit(void)
{
    UartDeinit(&logHandle);
    RccDisableUart2();

    GpioDeinit(LOG_UART_GPIO_PORT_TX, LOG_UART_GPIO_PIN_TX);
    GpioDeinit(LOG_UART_GPIO_PORT_RX, LOG_UART_GPIO_PIN_RX);
}

/**
 * @brief  Print the formatted message via the UART peripheral.
 *
 * This function writes the string pointed by format via UART and it supports
 * printf-style format specifiers.
 *
 * @param  format  The string to transmit over UART (with format specifiers).
 * @param  ...     Values for the format specifiers.
 */
void LogPrint(const char* format, ...)
{
    va_list arg;
    int32_t length = 0;

    va_start(arg, format);
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    length = vsnprintf((char*)logBuffer, LOG_BUFFER_SIZE,
                       format,  // NOLINT(clang-diagnostic-format-nonliteral)
                       arg);
    va_end(arg);

    if (length > 0)
    {
        HAL_UART_Transmit(&logHandle, (const uint8_t*)logBuffer,
                          (uint16_t)length, HAL_MAX_DELAY);
    }
}
