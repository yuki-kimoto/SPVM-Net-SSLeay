// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <openssl/ocsp.h>

static const char* FILE_NAME = "Net/SSLeay/DER.c";

int32_t SPVM__Net__SSLeay__DER__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}


int32_t SPVM__Net__SSLeay___DER__d2i_OCSP_REQUEST(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_a_ref = stack[0].oval;
  
  void* obj_ppin_ref = stack[1].oval;
  
  int64_t length = stack[2].lval;
  
  if (obj_a_ref) {
    return env->die(env, stack, "$a_ref must be undef. Currently reuse feature is not available.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_ppin_ref) {
    return env->die(env, stack, "$ppin_ref must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t ppin_ref_length = env->length(env, stack, obj_ppin_ref);
  
  if (!(ppin_ref_length == 1)) {
    return env->die(env, stack, "The length of $ppin_ref must be 1.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_ppin = env->get_elem_string(env, stack, obj_ppin_ref, 0);
  
  if (!obj_ppin) {
    return env->die(env, stack, "$ppin_ref at index 0 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  char* ppin = (char*)env->get_chars(env, stack, obj_ppin);
  
  const unsigned char* ppin_ref_tmp[1] = {0};
  ppin_ref_tmp[0] = ppin;
  
  OCSP_REQUEST* ret = d2i_OCSP_REQUEST(NULL, ppin_ref_tmp, length);
  
  if (!ret) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]d2i_OCSP_REQUEST failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    
    return error_id;
  }
  
  void* obj_ret = env->new_pointer_object_by_name(env, stack, "Net::SSLeay::OCSP_REQUEST", ret, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_ret;
  
  return 0;
}

int32_t SPVM__Net__SSLeay___DER__d2i_OCSP_RESPONSE(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_a_ref = stack[0].oval;
  
  void* obj_ppin_ref = stack[1].oval;
  
  int64_t length = stack[2].lval;
  
  if (obj_a_ref) {
    return env->die(env, stack, "$a_ref must be undef. Currently reuse feature is not available.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_ppin_ref) {
    return env->die(env, stack, "$ppin_ref must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t ppin_ref_length = env->length(env, stack, obj_ppin_ref);
  
  if (!(ppin_ref_length == 1)) {
    return env->die(env, stack, "The length of $ppin_ref must be 1.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_ppin = env->get_elem_string(env, stack, obj_ppin_ref, 0);
  
  if (!obj_ppin) {
    return env->die(env, stack, "$ppin_ref at index 0 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  char* ppin = (char*)env->get_chars(env, stack, obj_ppin);
  
  const unsigned char* ppin_ref_tmp[1] = {0};
  ppin_ref_tmp[0] = ppin;
  
  OCSP_RESPONSE* ret = d2i_OCSP_RESPONSE(NULL, ppin_ref_tmp, length);
  
  if (!ret) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]d2i_OCSP_RESPONSE failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    
    return error_id;
  }
  
  void* obj_ret = env->new_pointer_object_by_name(env, stack, "Net::SSLeay::OCSP_RESPONSE", ret, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_ret;
  
  return 0;
}

int32_t SPVM__Net__SSLeay___DER__i2d_OCSP_REQUEST(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_a = stack[0].oval;
  
  void* obj_ppout_ref = stack[1].oval;
  
  int64_t length = stack[2].lval;
  
  if (!obj_a) {
    return env->die(env, stack, "$a must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  OCSP_REQUEST* a = env->get_pointer(env, stack, obj_a);
  
  if (!obj_ppout_ref) {
    return env->die(env, stack, "$ppout_ref must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t ppout_ref_length = env->length(env, stack, obj_ppout_ref);
  
  if (!(ppout_ref_length == 1)) {
    return env->die(env, stack, "The length of $ppout_ref must be 1.", __func__, FILE_NAME, __LINE__);
  }
  
  unsigned char* ppout_ref_tmp[1] = {0};
  int32_t status = i2d_OCSP_REQUEST(a, ppout_ref_tmp);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]i2d_OCSP_REQUEST failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    
    return error_id;
  }
  
  void* obj_ppout = env->new_string_nolen(env, stack, ppout_ref_tmp[0]);
  
  env->set_elem_object(env, stack, obj_ppout_ref, 0, obj_ppout);
  
  stack[0].ival = status;
  
  return 0;
}
