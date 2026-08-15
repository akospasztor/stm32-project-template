/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the button driver implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "button.h"

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

/** GPIO port of the joystick center button. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define BUTTON_GPIO_PORT GPIOC

/** GPIO pin of the joystick center button. */
// cppcheck-suppress-macro [misra-c2012-11.4]
#define BUTTON_GPIO_PIN GPIO_PIN_13

/* Functions -----------------------------------------------------------------*/
/**
 * @brief  Initialize the center button of the joystick (B2) on the discovery
 *         board.
 */
void ButtonInit(void)
{
    RccEnablePortC();
    GpioConfigureDigitalInWithPullDown(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN);
}

/**
 * @brief  Get whether the button is pressed.
 *
 * @return True if the button is pressed, otherwise false.
 */
bool ButtonIsPressed(void)
{
    return GpioIsHigh(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN);
}
