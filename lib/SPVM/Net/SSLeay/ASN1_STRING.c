// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

static const char* FILE_NAME = "Net/SSLeay/ASN1_STRING.c";

int32_t SPVM__Net__SSLeay__ASN1_STRING__length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  ASN1_STRING* asn1_string = env->get_pointer(env, stack, obj_self);
  
  int32_t length = ASN1_STRING_length(asn1_string);
  
  stack[0].ival = length;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__ASN1_STRING__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  ASN1_STRING* pointer = env->get_pointer(env, stack, obj_self);
  
  if (!env->no_free(env, stack, obj_self)) {
    ASN1_STRING_free(pointer);
  }
  
  return 0;
}

