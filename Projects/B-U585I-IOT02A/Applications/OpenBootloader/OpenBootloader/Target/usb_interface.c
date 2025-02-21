/**
  ******************************************************************************
  * @file    usb_interface.c
  * @author  MCD Application Team
  * @brief   Contains USB protocol commands
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
#include "usb_interface.h"
#include "stm32u5xx.h"
#include "stm32u5xx_hal.h"
#include "app_usbx_device.h"
#include "app_azure_rtos.h"
#include "openbl_core.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
uint8_t USB_Detection = 0;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief  This function is used to configure USB pins and then initialize the used USB instance.
 * @retval None.
 */
void OPENBL_USB_Configuration(void)
{
  /* Enable the USB GPIO clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  hpcd_USB_OTG_FS.Instance                     = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints           = 6;
  hpcd_USB_OTG_FS.Init.phy_itface              = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable              = DISABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable        = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable              = DISABLE;
  hpcd_USB_OTG_FS.Init.battery_charging_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1       = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable     = DISABLE;

  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    while (1);
  }

  /* Start device USB */
  HAL_PCD_Start(&hpcd_USB_OTG_FS);
}

/**
 * @brief  This function is used to detect if there is any activity on USB protocol.
 * @retval Returns 1 if interface is detected else 0.
 */
uint8_t OPENBL_USB_ProtocolDetection(void)
{
  uint8_t detected = 0;

  if (USB_Detection == 1)
  {
    /* Disable the other interfaces */
    OPENBL_DeInit();

    /* The value of the variable "detect" will always be 0 and this is due to the fact that if this function returns 1,
       the USB interface will be disabled.
       For more details check the comment in the function "OpenBootloader_DetectInterfaceThread"
       in file "openbootloader_threadx.c" */
  }
  else
  {
    detected = 0;
  }

  return detected;
}

/**
 * @brief  This function is used to De-initialize the I2C pins and instance.
 * @retval None.
 */
void OPENBL_USB_DeInit(void)
{
  __HAL_RCC_USB_CLK_DISABLE();
  HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
}

/**
  * @brief  Gets the page of a given address
  * @param  Address Address of the FLASH Memory
  * @retval The page of a given address
  */
uint32_t OPENBL_USB_GetPage(uint32_t Address)
{
  uint32_t page;

  if (Address < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Address - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = ((Address - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE) + 128U;
  }

  return page;
}
