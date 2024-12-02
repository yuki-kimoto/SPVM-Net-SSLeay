// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <openssl/bio.h>
#include <openssl/err.h>

#include <openssl/asn1.h>

static const char* FILE_NAME = "Net/SSLeay/ASN1_TIME.c";

int32_t SPVM__Net__SSLeay__ASN1_TIME__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  ASN1_TIME* self = ASN1_TIME_new();
  
  if (!self) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]ASN1_TIME_new failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  void* obj_self = env->new_pointer_object_by_name(env, stack, "Net::SSLeay::ASN1_TIME", self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__ASN1_TIME__set(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int64_t t = stack[0].lval;
  
  ASN1_TIME* self = env->get_pointer(env, stack, obj_self);
  
  ASN1_TIME* ret = ASN1_TIME_set(self, t);
  
  if (!ret) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]ASN1_TIME_set failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  return 0;
}

int32_t SPVM__Net__SSLeay__ASN1_TIME__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  ASN1_TIME* self = env->get_pointer(env, stack, obj_self);
  
  if (!env->no_free(env, stack, obj_self)) {
    ASN1_TIME_free(self);
  }
  
  return 0;
}

