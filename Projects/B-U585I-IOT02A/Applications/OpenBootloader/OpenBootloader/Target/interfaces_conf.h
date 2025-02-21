/**
  ******************************************************************************
  * @file    interfaces_conf.h
  * @author  MCD Application Team
  * @brief   Contains Interfaces configuration
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
#ifndef INTERFACES_CONF_H
#define INTERFACES_CONF_H

#define MEMORIES_SUPPORTED                7U

/* ------------------------- Definitions for USART -------------------------- */
#define USARTx                            USART3
#define USARTx_CLK_ENABLE()               __HAL_RCC_USART3_CLK_ENABLE()
#define USARTx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_TX_PIN                     GPIO_PIN_8
#define USARTx_TX_GPIO_PORT               GPIOD
#define USARTx_RX_PIN                     GPIO_PIN_9
#define USARTx_RX_GPIO_PORT               GPIOD
#define USARTx_ALTERNATE                  GPIO_AF7_USART3

/* ------------------------- Definitions for I2C -------------------------- */
#define I2Cx                              I2C2
#define I2Cx_CLK_ENABLE()                 __HAL_RCC_I2C2_CLK_ENABLE()
#define I2Cx_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOH_CLK_ENABLE()

#define I2Cx_SCL_PIN                      GPIO_PIN_4
#define I2Cx_SCL_PIN_PORT                 GPIOH
#define I2Cx_SDA_PIN                      GPIO_PIN_5
#define I2Cx_SDA_PIN_PORT                 GPIOH
#define I2Cx_ALTERNATE                    GPIO_AF4_I2C2
#define I2C_ADDRESS                       0x000000B4U
#define OPENBL_I2C_TIMEOUT                0xFFFFF000U
#define I2C_TIMING                        0x00800000U

/* ------------------------- Definitions for FDCAN -------------------------- */
#define FDCANx                            FDCAN1
#define FDCANx_CLK_ENABLE()               __HAL_RCC_FDCAN1_CLK_ENABLE()
#define FDCANx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()

#define FDCANx_TX_PIN                     GPIO_PIN_8
#define FDCANx_TX_GPIO_PORT               GPIOB
#define FDCANx_TX_AF                      GPIO_AF9_FDCAN1
#define FDCANx_RX_PIN                     GPIO_PIN_9
#define FDCANx_RX_GPIO_PORT               GPIOB
#define FDCANx_RX_AF                      GPIO_AF9_FDCAN1

#define FDCANx_IT0_IRQn                   TIM16_FDCAN_IT0_IRQn
#define FDCANx_IT1_IRQn                   TIM17_FDCAN_IT1_IRQn
#define FDCANx_IRQHandler                 TIM16_FDCAN_IT0_IRQHandler

#define FDCANx_FORCE_RESET()              __HAL_RCC_FDCAN1_FORCE_RESET()
#define FDCANx_RELEASE_RESET()            __HAL_RCC_FDCAN1_RELEASE_RESET()

/* -------------------------- Definitions for SPI --------------------------- */
#define SPIx                              SPI1
#define SPIx_CLK_ENABLE()                 __HAL_RCC_SPI1_CLK_ENABLE()
#define SPIx_CLK_DISABLE()                __HAL_RCC_SPI1_CLK_DISABLE()
#define SPIx_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOE_CLK_ENABLE()
#define SPIx_IRQn                         SPI1_IRQn

#define SPIx_MOSI_PIN                     GPIO_PIN_15
#define SPIx_MOSI_PIN_PORT                GPIOE
#define SPIx_MISO_PIN                     GPIO_PIN_14
#define SPIx_MISO_PIN_PORT                GPIOE
#define SPIx_SCK_PIN                      GPIO_PIN_13
#define SPIx_SCK_PIN_PORT                 GPIOE
#define SPIx_NSS_PIN                      GPIO_PIN_4
#define SPIx_NSS_PIN_PORT                 GPIOA
#define SPIx_ALTERNATE                    GPIO_AF5_SPI1

#endif /* INTERFACES_CONF_H */
