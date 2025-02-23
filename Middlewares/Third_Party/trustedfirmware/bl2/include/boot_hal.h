/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __BOOT_HAL_H__
#define __BOOT_HAL_H__

/* Include header section */

#ifdef __cplusplus
extern "C" {
#endif

struct arm_vector_table {
	uint32_t msp;
	uint32_t reset;
};

/*
 * \brief It clears that part of the RAM which was used by MCUBoot, expect the
 *        TFM_SHARED_DATA area, which is used to pass data to the TF-M runtime.
 *
 * \note  This function must be implemented per target platform by system
 *        integrator. If the bootloader has not loaded any secret to the shared
 *        RAM then this function can immediately return to shorten the boot-up
 *        time. Clearing RAM area can be done several way, it is platform
 *        dependent:
 *        - Overwritten with a pre-defined constant value (i.e.: 0).
 *        - Overwritten with a random value.
 *        - Change the secret if its location is known.
 *        - Set a register which can hide some part of the flash/RAM against
 *          next stage software components.
 *        - Etc.
 */
void boot_clear_bl2_ram_area(void);
int32_t boot_platform_init(void);
__attribute__((naked)) void boot_jump_to_next_image(uint32_t boot_jump_addr, uint32_t reset_handler_addr);
void jumper(struct arm_vector_table *vt);
void boot_platform_noimage(void);
#ifdef __cplusplus
}
#endif

#endif /* __BOOT_HAL_H__ */
