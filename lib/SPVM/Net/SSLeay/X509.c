// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

static const char* FILE_NAME = "Net/SSLeay/X509.c";

int32_t SPVM__Net__SSLeay__X509__get_issuer_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  X509* x509 = env->get_pointer(env, stack, obj_self);
  
  X509_NAME* x509_name = X509_get_issuer_name(x509);
  
  void* obj_address_x509_name = env->new_pointer_object_by_name(env, stack, "Address", x509_name, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_x509_name;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::X509_NAME", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_x509_name = stack[0].oval;
  
  env->set_no_free(env, stack, obj_x509_name, 1);
  
  stack[0].oval = obj_x509_name;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__X509__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  X509* x509 = env->get_pointer(env, stack, obj_self);
  
  if (!env->no_free(env, stack, obj_self)) {
    X509_free(x509);
  }
  
  return 0;
}

