/**
 *******************************************************************************
 * STM32 Project Template
 *******************************************************************************
 * @file
 * @author    Akos Pasztor
 * @brief     This file contains the microcontroller-specific reset and clock
 *            control driver function prototypes.
 *******************************************************************************
 * @copyright (c) 2024 Akos Pasztor. https://akospasztor.com
 *            This software is licensed under terms that can be found in the
 *            LICENSE file in the root directory of this software component.
 *******************************************************************************
 */

#ifndef RCC_H
#define RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Functions------------------------------------------------------------------*/
void RccEnableSysCfg(void);
void RccDisableSysCfg(void);

void RccEnablePwr(void);
void RccDisablePwr(void);

void RccEnablePortA(void);
void RccDisablePortA(void);

void RccEnablePortB(void);
void RccDisablePortB(void);

void RccEnablePortC(void);
void RccDisablePortC(void);

void RccEnablePortD(void);
void RccDisablePortD(void);

void RccEnableUart2(void);
void RccDisableUart2(void);

#ifdef __cplusplus
}
#endif

#endif
