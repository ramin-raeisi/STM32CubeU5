/**
  ******************************************************************************
  * @file    LPBAM/LPBAM_I2C_SequentialTransfer/Inc/i2c_timing_utility.h
  * @author  MCD Application Team
  * @brief   Header of i2c_timing_utility.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_TIMING_UTILITY_H
#define __I2C_TIMING_UTILITY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Exported functions ------------------------------------------------------- */
uint32_t I2C_GetTiming(uint32_t clock_src_freq, uint32_t i2c_freq);

#endif /* __I2C_TIMING_UTILITY_H */
