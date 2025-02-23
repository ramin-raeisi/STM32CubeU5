/*
 * Copyright (c) 2018-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "tfm_platform_api.h"
#include "tfm_veneers.h"
#ifdef TFM_PSA_API
#include "psa_manifest/sid.h"
#endif

__attribute__((section("SFN")))
enum tfm_platform_err_t tfm_platform_system_reset(void)
{
#ifdef TFM_PSA_API
    psa_status_t status = PSA_ERROR_CONNECTION_REFUSED;
    psa_handle_t handle = PSA_NULL_HANDLE;

    handle = psa_connect(TFM_SP_PLATFORM_SYSTEM_RESET_SID,
                         TFM_SP_PLATFORM_SYSTEM_RESET_VERSION);
    if (handle <= 0) {
        return TFM_PLATFORM_ERR_SYSTEM_ERROR;
    }

    status = psa_call(handle, PSA_IPC_CALL,
                      NULL, 0, NULL, 0);
    psa_close(handle);

    if (status < PSA_SUCCESS) {
        return TFM_PLATFORM_ERR_SYSTEM_ERROR;
    } else {
        return (enum tfm_platform_err_t) status;
    }
#else /* TFM_PSA_API */
    return (enum tfm_platform_err_t) tfm_platform_sp_system_reset_veneer(
                                                              NULL, 0, NULL, 0);
#endif /* TFM_PSA_API */
}

__attribute__((section("SFN")))
enum tfm_platform_err_t
tfm_platform_ioctl(tfm_platform_ioctl_req_t request,
                   psa_invec *input, psa_outvec *output)
{
    tfm_platform_ioctl_req_t req = request;
    struct psa_invec in_vec[2];
    size_t inlen, outlen;
#ifdef TFM_PSA_API
    psa_status_t status = PSA_ERROR_CONNECTION_REFUSED;
    psa_handle_t handle = PSA_NULL_HANDLE;
#endif /* TFM_PSA_API */

    in_vec[0].base = &req;
    in_vec[0].len = sizeof(req);
    if (input != NULL) {
        in_vec[1].base = input->base;
        in_vec[1].len = input->len;
        inlen = 2;
    } else {
        inlen = 1;
    }

    if (output != NULL) {
        outlen = 1;
    } else {
        outlen = 0;
    }
#ifdef TFM_PSA_API
    handle = psa_connect(TFM_SP_PLATFORM_IOCTL_SID,
                         TFM_SP_PLATFORM_IOCTL_VERSION);
    if (handle <= 0) {
        return TFM_PLATFORM_ERR_SYSTEM_ERROR;
    }

    status = psa_call(handle, PSA_IPC_CALL,
                      in_vec, inlen,
                      output, outlen);
    psa_close(handle);

    if (status < PSA_SUCCESS) {
        return TFM_PLATFORM_ERR_SYSTEM_ERROR;
    } else {
        return (enum tfm_platform_err_t) status;
    }
#else /* TFM_PSA_API */
    return (enum tfm_platform_err_t) tfm_platform_sp_ioctl_veneer(
                                                in_vec, inlen, output, outlen);
#endif /* TFM_PSA_API */
}


