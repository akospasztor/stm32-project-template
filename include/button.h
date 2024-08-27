/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the button driver function prototypes.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

/* Defines -------------------------------------------------------------------*/

/* Functions------------------------------------------------------------------*/
void ButtonInit(void);
void ButtonDeinit(void);
bool ButtonIsPressed(void);

#ifdef __cplusplus
}
#endif

#endif
