/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*********** WARNING: This is an auto-generated file. Do not edit! ***********/

#ifndef __TFM_VENEERS_H__
#define __TFM_VENEERS_H__

#include "tfm_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/******** TFM_SP_STORAGE ********/
psa_status_t tfm_tfm_sst_set_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_sst_get_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_sst_get_info_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_sst_remove_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_sst_get_support_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);

/******** TFM_SP_ITS ********/
psa_status_t tfm_tfm_its_set_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_its_get_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_its_get_info_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_its_remove_req_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);

#ifdef TFM_PARTITION_AUDIT_LOG
/******** TFM_SP_AUDIT_LOG ********/
psa_status_t tfm_audit_core_retrieve_record_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_audit_core_add_record_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_audit_core_get_info_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_audit_core_get_record_info_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_audit_core_delete_record_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif /* TFM_PARTITION_AUDIT_LOG */

/******** TFM_SP_CRYPTO ********/
psa_status_t tfm_tfm_crypto_allocate_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_import_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_destroy_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_get_key_information_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_export_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_export_public_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_copy_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_set_key_policy_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_get_key_policy_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_get_key_lifetime_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_cipher_generate_iv_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_cipher_set_iv_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_cipher_encrypt_setup_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_cipher_decrypt_setup_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_cipher_update_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_cipher_abort_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_cipher_finish_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_hash_setup_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_hash_update_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_hash_finish_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_hash_verify_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_hash_abort_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_hash_clone_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_mac_sign_setup_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_mac_verify_setup_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_mac_update_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_mac_sign_finish_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_mac_verify_finish_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_mac_abort_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_aead_encrypt_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_aead_decrypt_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_asymmetric_sign_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_asymmetric_verify_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_asymmetric_encrypt_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_asymmetric_decrypt_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_get_generator_capacity_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_generator_read_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_generator_import_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_generator_abort_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_key_derivation_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_key_agreement_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_generate_random_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_tfm_crypto_generate_key_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);

#ifdef TFM_PARTITION_PLATFORM
/******** TFM_SP_PLATFORM ********/
psa_status_t tfm_platform_sp_system_reset_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_platform_sp_ioctl_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif /* TFM_PARTITION_PLATFORM */

/******** TFM_SP_INITIAL_ATTESTATION ********/
psa_status_t tfm_initial_attest_get_token_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_initial_attest_get_token_size_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);

#ifdef TFM_PARTITION_TEST_CORE
/******** TFM_SP_CORE_TEST ********/
psa_status_t tfm_spm_core_test_sfn_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_core_test_sfn_init_success_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_core_test_sfn_direct_recursion_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE
/******** TFM_SP_CORE_TEST_2 ********/
psa_status_t tfm_spm_core_test_2_slave_service_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_core_test_2_sfn_invert_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_core_test_2_check_caller_client_id_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_core_test_2_get_every_second_byte_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_core_test_2_prepare_test_scenario_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_core_test_2_execute_test_scenario_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
/******** TFM_SP_SECURE_TEST_PARTITION ********/
psa_status_t tfm_tfm_secure_client_service_sfn_run_tests_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_TEST_CORE_IPC
/******** TFM_SP_IPC_SERVICE_TEST ********/
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_PARTITION_TEST_CORE_IPC
/******** TFM_SP_IPC_CLIENT_TEST ********/
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
/******** TFM_IRQ_TEST_1 ********/
psa_status_t tfm_spm_irq_test_1_prepare_test_scenario_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t tfm_spm_irq_test_1_execute_test_scenario_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_APP_ROT
/******** TFM_APP_ROT ********/
psa_status_t tfm_tfm_app_rot_ioctl_sig_veneer(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif /* TFM_PARTITION_APP_ROT */

#ifdef __cplusplus
}
#endif

#endif /* __TFM_VENEERS_H__ */
