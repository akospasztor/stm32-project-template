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
/** GPIO port of the joystick center button. */
#define BUTTON_GPIO_PORT GPIOC
/** GPIO pin of the joystick center button. */
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
 * @brief  Deinitialize the center button of the joystick (B2).
 */
void ButtonDeinit(void)
{
    GpioDeinit(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN);
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
