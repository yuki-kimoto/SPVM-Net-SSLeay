// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <openssl/ssl.h>

static const char* FILE_NAME = "Net/SSLeay/SSL_CTX.c";

int32_t SPVM__Net__SSLeay__SSL_CTX__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_ssl_method = stack[0].oval;
  
  SSL_METHOD* ssl_method = env->get_pointer(env, stack, obj_ssl_method);
  
  SSL_CTX* ssl_ctx = SSL_CTX_new(ssl_method);
  
  void* obj_ssl_ctx = env->new_pointer_object_by_name(env, stack, "Net::SSLeay::SSL_CTX", ssl_ctx, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_ssl_method;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int64_t mode = stack[1].lval;
  
  SSL_CTX* ssl_ctx = env->get_pointer(env, stack, obj_self);
  
  int64_t new_mode = SSL_CTX_set_mode(ssl_ctx, mode);
  
  stack[0].lval = new_mode;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_verify(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t mode = stack[1].ival;
  
  SSL_CTX* ssl_ctx = env->get_pointer(env, stack, obj_self);
  
  SSL_CTX_set_verify(ssl_ctx, mode, NULL);
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* ssl_ctx = env->get_pointer(env, stack, obj_self);
  
  SSL_CTX_free(ssl_ctx);
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__get0_param(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* ssl_ctx = env->get_pointer(env, stack, obj_self);
  
  X509_VERIFY_PARAM* x509_verify_param = SSL_CTX_get0_param(ssl_ctx);
  
  void* obj_x509_verify_param = env->new_pointer_object_by_name(env, stack, "Net::SSLeay::X509_VERIFY_PARAM", x509_verify_param, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_x509_verify_param;
  
  return 0;
}
