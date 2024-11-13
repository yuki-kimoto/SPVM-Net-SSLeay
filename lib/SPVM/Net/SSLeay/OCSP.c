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

