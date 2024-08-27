/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the microcontroller-specific GPIO driver
 *            implementation.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* Functions------------------------------------------------------------------*/
/**
 * @brief  Configure the provided GPIO pin as digital input.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioConfigureDigitalIn(GPIO_TypeDef* const port, const uint16_t pin)
{
    GPIO_InitTypeDef gpioInitStruct = {0U};

    gpioInitStruct.Pin  = pin;
    gpioInitStruct.Mode = GPIO_MODE_INPUT;
    gpioInitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(port, &gpioInitStruct);
}

/**
 * @brief  Configure the provided GPIO pin as digital input with pull-down.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioConfigureDigitalInWithPullDown(GPIO_TypeDef* const port,
                                        const uint16_t pin)
{
    GPIO_InitTypeDef gpioInitStruct = {0U};

    gpioInitStruct.Pin  = pin;
    gpioInitStruct.Mode = GPIO_MODE_INPUT;
    gpioInitStruct.Pull = GPIO_PULLDOWN;

    HAL_GPIO_Init(port, &gpioInitStruct);
}

/**
 * @brief  Configure the provided GPIO pin as digital input with pull-up.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioConfigureDigitalInWithPullUp(GPIO_TypeDef* const port,
                                      const uint16_t pin)
{
    GPIO_InitTypeDef gpioInitStruct = {0U};

    gpioInitStruct.Pin  = pin;
    gpioInitStruct.Mode = GPIO_MODE_INPUT;
    gpioInitStruct.Pull = GPIO_PULLUP;

    HAL_GPIO_Init(port, &gpioInitStruct);
}

/**
 * @brief  Configure the provided GPIO pin as digital output.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioConfigureDigitalOut(GPIO_TypeDef* const port, const uint16_t pin)
{
    GPIO_InitTypeDef gpioInitStruct = {0U};

    gpioInitStruct.Pin   = pin;
    gpioInitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpioInitStruct.Pull  = GPIO_NOPULL;
    gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(port, &gpioInitStruct);
}

/**
 * @brief  Configure the provided GPIO pin with alternate function.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 * @param  alternateFunction  The alternate function to be configured.
 */
void GpioConfigureAlternateFunction(GPIO_TypeDef* const port,
                                    const uint16_t pin,
                                    const uint8_t alternateFunction)
{
    GPIO_InitTypeDef gpioInitStruct = {0U};

    gpioInitStruct.Pin       = pin;
    gpioInitStruct.Mode      = GPIO_MODE_AF_PP;
    gpioInitStruct.Pull      = GPIO_NOPULL;
    gpioInitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioInitStruct.Alternate = alternateFunction;

    HAL_GPIO_Init(port, &gpioInitStruct);
}

/**
 * @brief  Deinitialize the provided GPIO pin.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioDeinit(GPIO_TypeDef* const port, const uint16_t pin)
{
    HAL_GPIO_DeInit(port, pin);
}

/**
 * @brief  Set the provided GPIO pin to high.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioSetHigh(GPIO_TypeDef* const port, const uint16_t pin)
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

/**
 * @brief  Set the provided GPIO pin to low.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioSetLow(GPIO_TypeDef* const port, const uint16_t pin)
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

/**
 * @brief  Toggle the level of the provided GPIO.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 */
void GpioToggle(GPIO_TypeDef* const port, const uint16_t pin)
{
    HAL_GPIO_TogglePin(port, pin);
}

/**
 * @brief  Get if the provided GPIO pin is high.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 * @return True if the GPIO pin is high.
 */
bool GpioIsHigh(GPIO_TypeDef* const port, const uint16_t pin)
{
    return (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET);
}

/**
 * @brief  Get if the provided GPIO pin is low.
 *
 * @param  port  The GPIO port of the pin.
 * @param  pin   The GPIO pin number.
 * @return True if the GPIO pin is low.
 */
bool GpioIsLow(GPIO_TypeDef* const port, const uint16_t pin)
{
    return (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET);
}
