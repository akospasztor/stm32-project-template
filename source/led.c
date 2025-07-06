/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the LED driver implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "led.h"

#include "gpio.h"
#include "rcc.h"

/* Defines -------------------------------------------------------------------*/
// Message:     A conversion should not be performed between a pointer to
//              object and an integer type [misra-c2012-11.4]
// Reason:      The following GPIO port and pin defines contain conversions that
//              are addressing memory mapped registers and hardware specific
//              features.
// Risk:        Conversion of a pointer to object into an integer may produce a
//              value that cannot be represented in the chosen integer type
//              resulting in undefined behavior.
// Prevention:  Code reviews.

// cppcheck-suppress-macro [misra-c2012-11.4]
#define LED_LD2_GPIO_PORT GPIOB /**< GPIO port of the LD2 LED. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define LED_LD2_GPIO_PIN GPIO_PIN_13 /**< GPIO pin of the LD2 LED. */

// cppcheck-suppress-macro [misra-c2012-11.4]
#define LED_LD3_GPIO_PORT GPIOA /**< GPIO port of the LD3 LED. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define LED_LD3_GPIO_PIN GPIO_PIN_5 /**< GPIO pin of the LD3 LED. */

/* Functions -----------------------------------------------------------------*/
/**
 * @brief  Initialize the LD2 LED.
 */
void LedInitLd2(void)
{
    RccEnablePortB();

    GpioSetHigh(LED_LD2_GPIO_PORT, LED_LD2_GPIO_PIN);
    GpioConfigureDigitalOut(LED_LD2_GPIO_PORT, LED_LD2_GPIO_PIN);
}
/**
 * @brief  Initialize the LD3 LED.
 */
void LedInitLd3(void)
{
    RccEnablePortA();

    GpioSetLow(LED_LD3_GPIO_PORT, LED_LD3_GPIO_PIN);
    GpioConfigureDigitalOut(LED_LD3_GPIO_PORT, LED_LD3_GPIO_PIN);
}

/**
 * @brief  Turn on the LD2 LED.
 */
void LedLd2On(void)
{
    GpioSetLow(LED_LD2_GPIO_PORT, LED_LD2_GPIO_PIN);
}

/**
 * @brief  Turn off the LD2 LED.
 */
void LedLd2Off(void)
{
    GpioSetHigh(LED_LD2_GPIO_PORT, LED_LD2_GPIO_PIN);
}

/**
 * @brief  Turn on the LD3 LED.
 */
void LedLd3On(void)
{
    GpioSetHigh(LED_LD3_GPIO_PORT, LED_LD3_GPIO_PIN);
}

/**
 * @brief  Turn off the LD3 LED.
 */
void LedLd3Off(void)
{
    GpioSetLow(LED_LD3_GPIO_PORT, LED_LD3_GPIO_PIN);
}
