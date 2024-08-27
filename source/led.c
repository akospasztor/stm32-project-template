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
#define LED_LD2_GPIO_PORT GPIOB       /**< GPIO port of the LD2 LED. */
#define LED_LD2_GPIO_PIN  GPIO_PIN_13 /**< GPIO pin of the LD2 LED. */

#define LED_LD3_GPIO_PORT GPIOA      /**< GPIO port of the LD3 LED. */
#define LED_LD3_GPIO_PIN  GPIO_PIN_5 /**< GPIO pin of the LD3 LED. */

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
 * @brief  Deinitialize the LD2 LED.
 */
void LedDeinitLd2(void)
{
    GpioDeinit(LED_LD2_GPIO_PORT, LED_LD2_GPIO_PIN);
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
 * @brief  Deinitialize the LD3 LED.
 */
void LedDeinitLd3(void)
{
    GpioDeinit(LED_LD3_GPIO_PORT, LED_LD3_GPIO_PIN);
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
