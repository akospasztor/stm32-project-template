/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the microcontroller-specific GPIO driver
 *            function prototypes.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

#include <stdbool.h>

/* Defines -------------------------------------------------------------------*/

/* Functions------------------------------------------------------------------*/
void GpioConfigureDigitalIn(GPIO_TypeDef* const port, const uint16_t pin);
void GpioConfigureDigitalInWithPullDown(GPIO_TypeDef* const port,
                                        const uint16_t pin);
void GpioConfigureDigitalInWithPullUp(GPIO_TypeDef* const port,
                                      const uint16_t pin);
void GpioConfigureDigitalOut(GPIO_TypeDef* const port, const uint16_t pin);
void GpioConfigureAlternateFunction(GPIO_TypeDef* const port,
                                    const uint16_t pin,
                                    const uint8_t alternateFunction);
void GpioDeinit(GPIO_TypeDef* const port, const uint16_t pin);

void GpioSetHigh(GPIO_TypeDef* const port, const uint16_t pin);
void GpioSetLow(GPIO_TypeDef* const port, const uint16_t pin);
void GpioToggle(GPIO_TypeDef* const port, const uint16_t pin);

bool GpioIsHigh(GPIO_TypeDef* const port, const uint16_t pin);
bool GpioIsLow(GPIO_TypeDef* const port, const uint16_t pin);

#ifdef __cplusplus
}
#endif

#endif
