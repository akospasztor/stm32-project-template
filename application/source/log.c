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

// Message:     A conversion should not be performed between a pointer to
//              object and an integer type [misra-c2012-11.4]
// Reason:      The following GPIO port and pin defines contain conversions that
//              are addressing memory mapped registers and hardware specific
//              features.
// Risk:        Conversion of a pointer to object into an integer may produce a
//              value that cannot be represented in the chosen integer type
//              resulting in undefined behavior.
// Prevention:  Code reviews.

/** GPIO port of the UART TX pin used for logging. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define LOG_UART_GPIO_PORT_TX GPIOA

/** GPIO pin of the UART TX pin used for logging. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define LOG_UART_GPIO_PIN_TX GPIO_PIN_2

/** GPIO port of the UART RX pin used for logging. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define LOG_UART_GPIO_PORT_RX GPIOD

/** GPIO port of the UART RX pin used for logging. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define LOG_UART_GPIO_PIN_RX GPIO_PIN_6

/* Private variables ---------------------------------------------------------*/
/** ST HAL handle for the UART peripheral used for logging. */
static UART_HandleTypeDef logHandle;

/* Functions -----------------------------------------------------------------*/
/**
 * @brief  Initialize the logging module.
 *
 * This initializes the used UART peripheral and corresponding GPIO pins.
 */
void LogInit(void)
{
    RccEnableUart2();

    // Message:     A conversion should not be performed between a pointer to
    //              object and an integer type [misra-c2012-11.4]
    // Reason:      The following USART1 define is addressing the memory mapped
    //              base register of the USART1 hardware peripheral.
    // Risk:        Conversion of a pointer to object into an integer may
    //              produce a value that cannot be represented in the chosen
    //              integer type resulting in undefined behavior.
    // Prevention:  Code reviews.
    // cppcheck-suppress [misra-c2012-11.4]
    UartInit(&logHandle, USART2, 115200);

    RccEnablePortA();
    RccEnablePortD();

    GpioConfigureAlternateFunction(LOG_UART_GPIO_PORT_TX, LOG_UART_GPIO_PIN_TX,
                                   GPIO_AF7_USART2);
    GpioConfigureAlternateFunction(LOG_UART_GPIO_PORT_RX, LOG_UART_GPIO_PIN_RX,
                                   GPIO_AF7_USART2);
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
    /** Buffer used for logging. */
    static uint8_t logBuffer[LOG_BUFFER_SIZE];

    // Message:     The standard header file <stdarg.h> shall not be used
    //              [misra-c2012-17.1]
    // Reason:      This function provides a flexible, printf-style method to
    //              print log messages over the UART interface. The
    //              implementation relies on the variadic functions.
    // Risk:        The Standard lists many instances of undefined behavior
    //              associated with the features of <stdarg.h>, including:
    //              - va_end not being used prior to end of a function in which
    //                va_start was used
    //              - va_arg being used in different functions on the same
    //                va_list
    //              - the type of an argument not being compatible with the
    //                type specified to va_arg
    // Prevention:  Code reviews and testing.

    va_list arg;            // cppcheck-suppress [misra-c2012-17.1]
    va_start(arg, format);  // cppcheck-suppress [misra-c2012-17.1]

    const int32_t length =
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
        vsnprintf((char*)logBuffer, LOG_BUFFER_SIZE,
                  format,  // NOLINT(clang-diagnostic-format-nonliteral)
                  arg);
    va_end(arg);  // cppcheck-suppress [misra-c2012-17.1]

    if (length > 0)
    {
        (void)HAL_UART_Transmit(&logHandle, (const uint8_t*)logBuffer,
                                (uint16_t)length, HAL_MAX_DELAY);
    }
}
