/*
 * Copyright (c) 2017-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __TFM_SECURE_API_H__
#define __TFM_SECURE_API_H__

#ifndef TFM_MULTI_CORE_TOPOLOGY
#include <arm_cmse.h>
#endif
#include "tfm_arch.h"
#include "tfm_svc.h"
#include "tfm_core.h"
#include "tfm_api.h"
#include "tfm_utils.h"
#include "bl2/include/tfm_boot_status.h"
#include "psa/service.h"

#ifndef TFM_MULTI_CORE_TOPOLOGY
/*!
 * \def __tfm_secure_gateway_attributes__
 *
 * \brief Attributes for secure gateway functions
 */
#define __tfm_secure_gateway_attributes__ \
        __attribute__((cmse_nonsecure_entry, noinline, section("SFN")))
#endif

/* Hide specific errors if not debugging */
#ifdef TFM_CORE_DEBUG
#define TFM_ERROR_STATUS(status) (status)
#else
#define TFM_ERROR_STATUS(status) (TFM_PARTITION_BUSY)
#endif

#ifndef TFM_LVL
#error TFM_LVL is not defined!
#endif

extern void tfm_secure_api_error_handler(void);

typedef int32_t(*sfn_t)(int32_t, int32_t, int32_t, int32_t);

struct tfm_sfn_req_s {
    uint32_t sp_id;
    sfn_t sfn;
    int32_t *args;
    uint32_t caller_part_idx;
    uint32_t ns_caller;
};

enum tfm_ns_region_e {
    TFM_NS_REGION_CODE = 0,
    TFM_NS_REGION_DATA_1,
    TFM_NS_REGION_VENEER,
    TFM_NS_REGION_PERIPH_1,
    TFM_NS_REGION_PERIPH_2,
    TFM_NS_SECONDARY_IMAGE_REGION,
    TFM_NS_REGION_DATA_2
};

enum tfm_memory_access_e {
    TFM_MEMORY_ACCESS_RO = 1,
    TFM_MEMORY_ACCESS_RW = 2,
};

extern int32_t tfm_core_validate_secure_caller(void);

extern int32_t tfm_core_get_caller_client_id(int32_t *caller_client_id);

extern int32_t tfm_core_memory_permission_check(const void *ptr,
                                                uint32_t size,
                                                int32_t access);

extern int32_t tfm_core_get_boot_data(uint8_t major_type,
                                      struct tfm_boot_data *boot_data,
                                      uint32_t len);

extern int32_t tfm_core_get_boot_value(uint16_t tlv_value,
                                      void *pt,
                                      uint32_t len);

int32_t tfm_core_sfn_request(const struct tfm_sfn_req_s *desc_ptr);

int32_t tfm_core_sfn_request_thread_mode(struct tfm_sfn_req_s *desc_ptr);

/**
 * \brief Check whether a memory range is inside a memory region.
 *
 * \param[in] p             The start address of the range to check
 * \param[in] s             The size of the range to check
 * \param[in] region_start  The start address of the region, which should
 *                          contain the range
 * \param[in] region_limit  The end address of the region, which should contain
 *                          the range
 *
 * \return TFM_SUCCESS if the region contains the range,
 *         TFM_ERROR_GENERIC otherwise.
 */
enum tfm_status_e check_address_range(const void *p, size_t s,
                                      uintptr_t region_start,
                                      uintptr_t region_limit);

void tfm_enable_irq(psa_signal_t irq_signal);
void tfm_disable_irq(psa_signal_t irq_signal);

#ifdef TFM_PSA_API
/* The following macros are only valid if secure services can be called
 * using veneer functions. This is not the case if IPC messaging is enabled
 */
#define TFM_CORE_IOVEC_SFN_REQUEST(id, fn, a, b, c, d)               \
        do {                                                         \
            ERROR_MSG("Invalid TF-M configuration detected");        \
            tfm_secure_api_error_handler();                          \
            /* This point never reached */                           \
            return (int32_t)TFM_ERROR_GENERIC;                       \
        } while (0)
#else
#define TFM_CORE_IOVEC_SFN_REQUEST(id, fn, a, b, c, d)               \
        return tfm_core_partition_request(id, fn,                    \
                (int32_t)a, (int32_t)b, (int32_t)c, (int32_t)d)

__attribute__ ((always_inline)) __STATIC_INLINE
int32_t tfm_core_partition_request(uint32_t id, void *fn,
            int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4)
{
    int32_t args[4] = {arg1, arg2, arg3, arg4};
    struct tfm_sfn_req_s desc, *desc_ptr = &desc;

    desc.sp_id = id;
    desc.sfn = (sfn_t) fn;
    desc.args = args;
    /*
     * This preprocessor condition checks if a version of GCC smaller than
     * 7.3.1 is being used to compile the code.
     * These versions are affected by a bug on the cmse_nonsecure_caller
     * intrinsic which returns incorrect results.
     * Please check Bug 85203 on GCC Bugzilla for more information.
     */
#if defined(__GNUC__) && !defined(__ARMCC_VERSION) && \
    (__GNUC__ < 7 || \
     (__GNUC__ == 7 && (__GNUC_MINOR__ < 3 || \
                       (__GNUC_MINOR__ == 3 && __GNUC_PATCHLEVEL__ < 1))))
    /*
     * Use the fact that, if called from Non-Secure, the LSB of the return
     * address is set to 0.
     */
    desc.ns_caller = (uint32_t)!(
           (intptr_t)__builtin_extract_return_addr(__builtin_return_address(0U))
           & 1);
#else
    /*
     * Convert the result of cmse_nonsecure_caller from an int to a uint32_t
     * to prevent using an int in the tfm_sfn_req_s structure.
     */
    desc.ns_caller = (cmse_nonsecure_caller() != 0) ? 1U : 0U;
#endif /* Check for GCC compiler version smaller than 7.3.1 */
    if (__get_active_exc_num() != EXC_NUM_THREAD_MODE) {
        /* The veneer of a secure service had been called from Handler mode.
         * This violates TF-M's programming model, and is considered an
         * unrecoverable error.
         */
        tfm_panic();
    } else {
        if (desc.ns_caller) {
            return tfm_core_sfn_request(desc_ptr);
        } else {
            return tfm_core_sfn_request_thread_mode(desc_ptr);
        }
    }
    return TFM_ERROR_GENERIC;
}
#endif

#endif /* __TFM_SECURE_API_H__ */
