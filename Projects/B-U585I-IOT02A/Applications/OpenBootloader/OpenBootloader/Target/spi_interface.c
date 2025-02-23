/**
  ******************************************************************************
  * @file    spi_interface.c
  * @author  MCD Application Team
  * @brief   Contains SPI HW configuration
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

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"
#include "stm32u5xx_ll_spi.h"

#include "openbl_core.h"
#include "openbl_spi_cmd.h"

#include "spi_interface.h"
#include "iwdg_interface.h"

#include "interfaces_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPI_DUMMY_BYTE                    0x00U  /* Dummy byte */
#define SPI_SYNC_BYTE                     0x5AU  /* Synchronization byte */
#define SPI_BUSY_BYTE                     0xA5U  /* Busy byte */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile uint8_t SpiRxNotEmpty = 0U;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void OPENBL_SPI_Init(void);
#if defined (__CC_ARM)
void OPENBL_SPI_ClearFlag_OVR(void);
#else
__ramfunc void OPENBL_SPI_ClearFlag_OVR(void);
#endif /* (__CC_ARM) */

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  This function is used to initialize the SPI peripheral
 * @retval None.
 */
static void OPENBL_SPI_Init(void)
{
  LL_SPI_InitTypeDef SPI_InitStruct = {0};

  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode              = LL_SPI_MODE_SLAVE;
  SPI_InitStruct.DataWidth         = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity     = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase        = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS               = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate          = LL_SPI_BAUDRATEPRESCALER_DIV2;
  SPI_InitStruct.BitOrder          = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation    = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly           = 7U;

  LL_SPI_Init(SPIx, &SPI_InitStruct);
  LL_SPI_SetFIFOThreshold(SPIx, LL_SPI_FIFO_TH_01DATA);

  /* In case the underrun flag is set, we send a busy byte */
  LL_SPI_SetUDRConfiguration(SPIx, LL_SPI_UDR_CONFIG_REGISTER_PATTERN);
  LL_SPI_SetUDRPattern(SPIx, SPI_BUSY_BYTE);

  HAL_NVIC_SetPriority(SPIx_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(SPIx_IRQn);

  LL_SPI_Enable(SPIx);
}

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  This function is used to configure SPI pins and then initialize the used SPI instance.
 * @retval None.
 */
void OPENBL_SPI_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Enable all resources clocks ---------------------------------------------*/
  /* Enable used GPIOx clocks */
  SPIx_GPIO_CLK_ENABLE();

  /* Enable SPI clock */
  SPIx_CLK_ENABLE();

  /* SPI1 pins configuration -------------------------------------------------*/
  /*
           +----------+
           |   SPI1   |
     +-----+----------+
     | MOSI|   PE15   |
     +-----+----------+
     | MISO|   PE14   |
     +-----+----------+
     | SCK |   PE13   |
     +-----+----------+
     | NSS |   PA4    |
     +-----+----------+ */

  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = SPIx_ALTERNATE;

  /* SPI MOSI pin configuration */
  GPIO_InitStruct.Pin = SPIx_MOSI_PIN;
  HAL_GPIO_Init(SPIx_MOSI_PIN_PORT, &GPIO_InitStruct);

  /* SPI MISO pin configuration */
  GPIO_InitStruct.Pin = SPIx_MISO_PIN;
  HAL_GPIO_Init(SPIx_MISO_PIN_PORT, &GPIO_InitStruct);

  /* SPI SCK pin configuration */
  GPIO_InitStruct.Pin = SPIx_SCK_PIN;
  HAL_GPIO_Init(SPIx_SCK_PIN_PORT, &GPIO_InitStruct);

  /* SPI NSS pin configuration */
  GPIO_InitStruct.Pin = SPIx_NSS_PIN;
  HAL_GPIO_Init(SPIx_NSS_PIN_PORT, &GPIO_InitStruct);

  OPENBL_SPI_Init();
}

/**
 * @brief  This function is used to De-initialize the SPI pins and instance.
 * @retval None.
 */
void OPENBL_SPI_DeInit(void)
{
  LL_SPI_DeInit(SPIx);
  LL_SPI_Enable(SPIx);
}

/**
 * @brief  This function is used to detect if there is any activity on SPI protocol.
 * @retval Returns 1 if interface is detected else 0.
 */
uint8_t OPENBL_SPI_ProtocolDetection(void)
{
  uint8_t detected;

  /* Check if there is any activity on SPI */
  if (LL_SPI_IsActiveFlag_RXP(SPIx) != 0)
  {
    /* Check that Synchronization byte has been received on SPI */
    if (LL_SPI_ReceiveData8(SPIx) == SPI_SYNC_BYTE)
    {
      detected = 1U;

      /* Enable the interrupt of Rx not empty buffer */
      LL_SPI_EnableIT_RXP(SPIx);

      /* Send synchronization byte */
      OPENBL_SPI_SendByte(SYNC_BYTE);

      OPENBL_SPI_SendAcknowledgeByte(ACK_BYTE);
    }
    else
    {
      detected = 0U;
    }
  }
  else
  {
    detected = 0U;
  }

  return detected;
}

/**
 * @brief  This function is used to get the command opcode from the host.
 * @retval Returns the command.
 */
uint8_t OPENBL_SPI_GetCommandOpcode(void)
{
  uint8_t command_opc;

  /* Check if there is any activity on SPI */
  while (OPENBL_SPI_ReadByte() != SPI_SYNC_BYTE)
  {}

  /* Get the command opcode */
  command_opc = OPENBL_SPI_ReadByte();

  /* Check the data integrity */
  if ((command_opc ^ OPENBL_SPI_ReadByte()) != 0xFFU)
  {
    command_opc = ERROR_COMMAND;
  }

  return command_opc;
}

/**
  * @brief  This function is used to read one byte from SPI pipe.
  *         Read operation is synchronized on SPI Rx buffer not empty interrupt.
  * @retval Returns the read byte.
  */
#if defined (__CC_ARM)
uint8_t OPENBL_SPI_ReadByte(void)
#else
__ramfunc uint8_t OPENBL_SPI_ReadByte(void)
#endif /* (__CC_ARM) */
{
  uint8_t data;

  /* Wait until SPI Rx buffer not empty interrupt */
  while (SpiRxNotEmpty == 0U)
  {
    /* Refresh IWDG: reload counter */
    IWDG->KR = IWDG_KEY_RELOAD;
  }

  /* Reset the RX not empty token */
  SpiRxNotEmpty = 0U;

  /* Read the SPI data register */
  data = SPIx->RXDR;

  /* Enable the interrupt of Rx not empty buffer */
  SPIx->IER |= SPI_IER_RXPIE;

  return data;
}

/**
  * @brief  This function is used to send one busy byte each receive interrupt through SPI pipe.
  *         Read operation is synchronized on SPI Rx buffer not empty interrupt.
  * @retval Returns the read byte.
  */
#if defined (__CC_ARM)
void OPENBL_SPI_SendBusyByte(void)
#else
__ramfunc void OPENBL_SPI_SendBusyByte(void)
#endif /* (__CC_ARM) */
{
  /* Wait until SPI Rx buffer not empty interrupt */
  while (SpiRxNotEmpty == 0U)
  {
    /* Refresh IWDG: reload counter */
    IWDG->KR = IWDG_KEY_RELOAD;
  }

  /* Reset the RX not empty token */
  SpiRxNotEmpty = 0U;

  /* Transmit the busy byte */
  *((__IO uint8_t *)&SPIx->TXDR) = SPI_BUSY_BYTE;

  /* Read bytes from the host to avoid the overrun */
  OPENBL_SPI_ClearFlag_OVR();

  /* Enable the interrupt of Rx not empty buffer */
  SPIx->IER |= SPI_IER_RXPIE;
}

/**
  * @brief  This function is used to send one byte through SPI pipe.
  * @retval None.
  */
#if defined (__CC_ARM)
void OPENBL_SPI_SendByte(uint8_t Byte)
#else
__ramfunc void OPENBL_SPI_SendByte(uint8_t Byte)
#endif /* (__CC_ARM) */
{
  /* Wait until SPI transmit buffer is empty */
  while ((SPIx->SR & SPI_SR_TXP) == 0)
  {}

  /* Transmit the data */
  *((__IO uint8_t *)&SPIx->TXDR) = Byte;

  /* Clear underrun flag */
  SET_BIT(SPIx->IFCR, SPI_IFCR_UDRC);
}

/**
  * @brief  This function is used to send acknowledge byte through SPI pipe.
  * @retval None.
  */
void OPENBL_SPI_SendAcknowledgeByte(uint8_t Byte)
{
  /* Check the AN4286 for the acknowledge procedure */
  if (Byte == ACK_BYTE)
  {
    /* Send dummy byte */
    OPENBL_SPI_SendByte(SPI_DUMMY_BYTE);
  }

  OPENBL_SPI_SendByte(Byte);

  /* Wait for the host to send ACK synchronization byte */
  while (OPENBL_SPI_ReadByte() != ACK_BYTE)
  {}
}

/**
  * @brief  Handle SPI interrupt request.
  * @retval None.
  */
#if defined (__CC_ARM)
void OPENBL_SPI_IRQHandler()
#else
__ramfunc void OPENBL_SPI_IRQHandler()
#endif /* (__CC_ARM) */
{
  /* Check that SPI Rx buffer not empty interrupt has been raised */
  if (((SPIx->SR & SPI_SR_OVR) == RESET)
      && ((SPIx->SR & SPI_SR_RXP) != RESET)
      && ((SPIx->IER & SPI_IER_RXPIE) != RESET))
  {
    /* Set the RX not empty token */
    SpiRxNotEmpty = 1U;

    /* Disable the interrupt of Rx not empty buffer */
    SPIx->IER &= ~SPI_IER_RXPIE;
  }

  if (((SPIx->SR & SPI_SR_OVR) != RESET)
      && ((SPIx->SR & SPI_SR_RXP) != RESET)
      && ((SPIx->IER & SPI_IER_RXPIE) != RESET))
  {
    /* Read bytes from the host to avoid the overrun */
    OPENBL_SPI_ClearFlag_OVR();
  }
}

/**
  * @brief  This function enables the send of busy state.
  * @retval None.
  */
void OPENBL_SPI_EnableBusyState(void)
{
  /* Since we are using the underrun configuration, we don't need to enable the busy state */
}

/**
  * @brief  This function disables the send of busy state.
  * @retval None.
  */
void OPENBL_SPI_DisableBusyState(void)
{
  /*
    In this product, we use the LL_SPI_UDR_CONFIG_REGISTER_PATTERN configuration,
    where we send a busy byte in case an underrun error occurs.
    This is why we don't need to send the busy byte manually.
  */
}

/**
  * @brief  Clear overrun error flag
  * @note   Clearing this flag is done by a read access to the SPIx_DR
  *         register followed by a read access to the SPIx_SR register
  * @retval None
  */
#if defined (__CC_ARM)
void OPENBL_SPI_ClearFlag_OVR(void)
#else
__ramfunc void OPENBL_SPI_ClearFlag_OVR(void)
#endif /* (__CC_ARM) */
{
  SET_BIT(SPIx->IFCR, SPI_IFCR_OVRC);
}
