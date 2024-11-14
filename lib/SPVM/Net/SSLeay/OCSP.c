// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <openssl/ocsp.h>

static const char* FILE_NAME = "Net/SSLeay/OCSP.c";

int32_t SPVM__Net__SSLeay__OCSP__response_status_str(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int64_t code = stack[0].lval;
  
  const char* status_str = OCSP_response_status_str(code);
  
  assert(status_str);
  
  void* obj_status_str = env->new_string_nolen(env, stack, status_str);
  
  stack[0].oval = obj_status_str;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__OCSP__response_status(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_resp = stack[0].oval;
  
  if (!obj_resp) {
    return env->die(env, stack, "The OCSP response $resp must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  OCSP_RESPONSE* resp = env->get_pointer(env, stack, obj_resp);
  
  int32_t status = OCSP_response_status(resp);
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__OCSP__basic_verify(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_bs = stack[0].oval;
  
  void* obj_certs = stack[1].oval;
  
  void* obj_st = stack[2].oval;
  
  int64_t flags = stack[3].lval;
  
  if (!obj_bs) {
    return env->die(env, stack, "The OCSP_BASICRESP object $bs must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_certs) {
    return env->die(env, stack, "The untrusted certificates $certs must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_st) {
    return env->die(env, stack, "The trusted certificat store $certs must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  OCSP_BASICRESP* bs = env->get_pointer(env, stack, obj_bs);
  
  STACK_OF(X509)* sk_X509 = sk_X509_new_null();
  
  int32_t list_length = env->length(env, stack, obj_certs);
  
  for (int32_t i = 0; i < list_length; i++) {
    void* obj_X509 = env->get_elem_object(env, stack, obj_certs, i);
    X509* X509 = env->get_pointer(env, stack, obj_X509);
    sk_X509_push(sk_X509, X509);
  }
  
  X509_STORE* st = env->get_pointer(env, stack, obj_st);
  
  int32_t status = OCSP_basic_verify(bs, sk_X509, st, flags);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]OCSP_basic_verify failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}
