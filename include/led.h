/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the LED driver function prototypes.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Functions------------------------------------------------------------------*/
void LedInitLd2(void);
void LedInitLd3(void);

void LedDeinitLd2(void);
void LedDeinitLd3(void);

void LedLd2On(void);
void LedLd2Off(void);

void LedLd3On(void);
void LedLd3Off(void);

#ifdef __cplusplus
}
#endif

#endif
