/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "region_defs.h"
#include "mcuboot_config/mcuboot_config.h"
/* Enumeration that is used by the assemble.py and imgtool.py scripts
 * for correct binary generation when nested macros are used
 */

enum image_attributes
{
/* area for preparing images */
  RE_IMAGE_FLASH_SECURE_IMAGE_SIZE = (SECURE_IMAGE_MAX_SIZE),
#if MCUBOOT_IMAGE_NUMBER == 2
  RE_IMAGE_FLASH_NON_SECURE_IMAGE_SIZE = (NON_SECURE_IMAGE_MAX_SIZE),
#else
  RE_IMAGE_FLASH_NON_SECURE_IMAGE_SIZE = (NON_SECURE_IMAGE_MAX_SIZE+SECURE_IMAGE_MAX_SIZE),
#endif
/* area for flashing images */
  RE_IMAGE_FLASH_ADDRESS_SECURE = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET),
  RE_EXTERNAL_FLASH_ENABLE = (0x0),
#if (MCUBOOT_IMAGE_NUMBER == 2)
  RE_IMAGE_NUMBER = (0x2),
  RE_CODE_START_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE = (FLASH_BASE_ADDRESS+FLASH_AREA_1_OFFSET),	
  /* area for updates slot address */
#if !defined(MCUBOOT_PRIMARY_ONLY)
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_2_OFFSET),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_3_OFFSET),
  RE_PRIMARY_ONLY = (0x0),
#else
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_1_OFFSET),
  RE_PRIMARY_ONLY = (0x1),
#endif /* MCUBOOT_PRIMARY_ONLY */
#else /*(MCUBOOT_IMAGE_NUMBER == 1) */
  RE_IMAGE_NUMBER = (0x1),
  RE_CODE_START_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE = (0x0),
#if !defined(MCUBOOT_PRIMARY_ONLY)
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_2_OFFSET),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (0x0),
  RE_PRIMARY_ONLY = (0x0),
#else
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (0x0),
  RE_PRIMARY_ONLY = (0x1),
#endif /* MCUBOOT_PRIMARY_ONLY */
#endif /* (MCUBOOT_IMAGE_NUMBER == 2) */
  RE_BL2_PERSO_ADDRESS = (FLASH_BASE_ADDRESS+FLASH_AREA_PERSO_OFFSET),
  RE_BL2_BOOT_ADDRESS = (BL2_BOOT_VTOR_ADDR),
  /* area for programming hardening on page */
#if (FLASH_AREA_0_OFFSET+SECURE_IMAGE_MAX_SIZE) < (FLASH_B_SIZE)
  /* config without secure on bank 2 */
  RE_BL2_SEC1_END = (FLASH_AREA_0_OFFSET+SECURE_IMAGE_MAX_SIZE-0x1),
  RE_BL2_SEC2_START = (FLASH_B_SIZE-0x1),
  RE_BL2_SEC2_END = (0x0),
#else
  /* config with secure on bank 2 */
  RE_BL2_SEC1_END = (FLASH_B_SIZE-0x1),
  RE_BL2_SEC2_START = 0x0,
  RE_BL2_SEC2_END = (FLASH_AREA_0_OFFSET+SECURE_IMAGE_MAX_SIZE-FLASH_B_SIZE-0x1)
#endif
  RE_BL2_WRP_START = (FLASH_AREA_PERSO_OFFSET),
  RE_BL2_WRP_END = (FLASH_AREA_BL2_NOHDP_OFFSET+FLASH_AREA_BL2_NOHDP_SIZE-0x1),
  RE_BL2_HDP_END = (FLASH_AREA_BL2_NOHDP_OFFSET-0x1),
  /* area for updates slot address */

#if defined(MCUBOOT_EXT_LOADER)
  RE_IMAGE_FLASH_LOADER_ADDRESS = (FLASH_BASE_ADDRESS+FLASH_AREA_LOADER_OFFSET),
  RE_LOADER_NS_CODE_SIZE = (LOADER_NS_CODE_SIZE),
  RE_LOADER_IMAGE_S_CODE_SIZE = (LOADER_IMAGE_S_CODE_SIZE),
  RE_LOADER_WRP_START = (FLASH_AREA_LOADER_BANK_OFFSET),
  RE_LOADER_WRP_END = (FLASH_B_SIZE-0x1),
  RE_EXT_LOADER = (0x1),
#else
  RE_IMAGE_FLASH_LOADER_ADDRESS = (0x0),
  RE_LOADER_NS_CODE_SIZE = (0x0),
  RE_LOADER_IMAGE_S_CODE_SIZE = (0x0),
  RE_LOADER_WRP_START = (0x7f),
  RE_LOADER_WRP_END = (0x0),
  RE_EXT_LOADER = (0x0),
#endif /* MCUBOOT_EXT_LOADER */
  RE_CRYPTO_SCHEME = CRYPTO_SCHEME,
#if defined(MCUBOOT_ENC_IMAGES)
  RE_ENCRYPTION = (0x1),
#else
  RE_ENCRYPTION = (0x0),
#endif
#if defined(MCUBOOT_OVERWRITE_ONLY)
  RE_OVER_WRITE = (0x1)
#else
  RE_OVER_WRITE = (0x0)
#endif
};
